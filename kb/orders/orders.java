/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/orders
TAGS: dp, knapsack
EXPLANATION:

run a modified knapsack where instead of storing cost, you store the number of ways to make that amount.

0 = zero ways
1 = one way
2 = more than one way (we only care if it is ambiguous or not)

dp[i][j] = min(2, dp[i-1][j] + dp[i][j-cost[i]])

After this, trace back through the dp matrix to reproduce the sequence if it is possible and unambiguous.
If dp[i][j] == dp[i-1][j], you know you did not use the previous item. Otherwise you know you did.

END ANNOTATION
*/
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.PriorityQueue;
import java.util.Queue;
import java.util.Stack;
import java.util.StringTokenizer;
 
public class orders {
	
	StringTokenizer st;
	BufferedReader file;
	PrintWriter pout;
	
	public static void main(String[] args) throws Exception
	{
		new orders().run();
	}	
	
	double epsilon = 0;
	
	public void run() throws Exception
	{
		file = new BufferedReader(new InputStreamReader(System.in));
		
		PrintWriter pout = new PrintWriter(System.out);
		
		int N = nextInt();
		int[] cost = new int[N];
		for(int i = 0;i<N;i++)
			cost[i] = nextInt();
		int M = nextInt();
		int[][] dp = new int[N+1][30001];
		dp[0][0] = 1;
		for(int i = 1;i<dp.length;i++)
		{
			for(int j = 0;j<dp[i].length;j++)
			{
				int up = dp[i-1][j];
				int left = 0;
				if(j >= cost[i-1])
					left = dp[i][j-cost[i-1]];
				dp[i][j] = Math.min(2, up+left);
			}
		}
		
		for(int i = 0;i<M;i++)
		{
			int x = nextInt();
			if(dp[N][x] == 0)
			{
				pout.println("Impossible");
			}else if(dp[N][x] == 2)
			{
				pout.println("Ambiguous");
			}else {
				Stack<Integer> st = new Stack<Integer>();
				int r = N;
				int c = x;
				while(r != 0 && c != 0)
				{
					if(dp[r][c] == dp[r-1][c])
					{
						r--;
					}else {
						st.push(r);
						c-= cost[r-1];
					}
				}
				while(!st.isEmpty())
				{
					pout.print(st.pop()+" ");
				}
				pout.println();
			}
		}
		
		pout.flush();
		pout.close();
	}
	
	public void newst()
	{
		try {
			st = new StringTokenizer(file.readLine());
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	
	public String readLine() throws IOException
	{
		return file.readLine();
	}
	
	public String next()
	{
		if(st == null || !st.hasMoreTokens())
			newst();
		return st.nextToken();
	}
	
	public int nextInt()
	{
		if(st == null || !st.hasMoreTokens())
			newst();
		return Integer.parseInt(st.nextToken());
	}
	
	public long nextLong()
	{
		if(st == null || !st.hasMoreTokens())
			newst();
		return Long.parseLong(st.nextToken());
	}
	
}