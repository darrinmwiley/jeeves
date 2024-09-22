/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/goodcoalition
TAGS: math, dp
EXPLANATION:
let dp[i] = the log probability of success for the best possible coalition of i people.
We use log probability for a few reasons. 
First, it avoids precision loss due to underflow
Second, it makes the problem almost identical to single use coins dp to find the minimum number of coins used to make a certain amount, the only difference being that you are maximizing instead of minimizing.

dp[i] = argmax(dp[i-x] + ln(y)) over all parties where x is the number of people and y is their probability of success

the answer to the problem is argmax(e^(dp[i])) where 75 < i <= 150 (the majority coalition with highest probability of success) 
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
import java.util.StringTokenizer;
 
public class goodcoalition {
	
	StringTokenizer st;
	BufferedReader file;
	PrintWriter pout;
	
	public static void main(String[] args) throws Exception
	{
		new goodcoalition().run();
	}	
	
	double epsilon = 0;
	
	public void run() throws Exception
	{
		file = new BufferedReader(new InputStreamReader(System.in));
		
		PrintWriter pout = new PrintWriter(System.out);
		
		int zz = nextInt();
		for(int z = 0;z<zz;z++)
		{
			double[] dp = new double[151];
			boolean[] poss = new boolean[151];
			poss[0] = true;
			int N = nextInt();
			int[] val = new int[N];
			double[] prob = new double[N];
			Arrays.fill(dp, -1000);
			dp[0] = 0;
			for(int i = 0;i<N;i++)
			{
				val[i] = nextInt();
				prob[i] = Math.log(nextInt()/100.0);
			}
			for(int i = 0;i<N;i++)
			{
				for(int j = 151;j>=val[i];j--)
				{
					if(poss[j - val[i]])
					{
						poss[j] = true;
						dp[j] = Math.max(dp[j], dp[j - val[i]] + prob[i]);
					}
				}
			}
			double max = -1000;
			for(int i = 76;i<=150;i++)
			{
				max = Math.max(max, dp[i]);
			}
			//System.out.println(Arrays.toString(dp));
			System.out.println(Math.exp(max)*100);
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