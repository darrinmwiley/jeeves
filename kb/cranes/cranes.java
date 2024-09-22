/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/cranes
TAGS:brute force,bit manipulation
EXPLANATION:Try all 2^n possible combinations of cranes, and verify each in n^2
END ANNOTATION
*/
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.HashMap;
import java.util.HashSet;
import java.util.PriorityQueue;
import java.util.StringTokenizer;

public class cranes {

	public static void main(String[] args) throws Exception
	{
		new cranes().run();
	}

	public void run() throws Exception{
		BufferedReader file = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st;
		int zz = Integer.parseInt(file.readLine());
		for(int z = 0;z<zz;z++)
		{
			int N = Integer.parseInt(file.readLine());
			int[] x = new int[N];
			int[] y = new int[N];
			int[] r = new int[N];
			for(int i = 0;i<N;i++)
			{
				st = new StringTokenizer(file.readLine());
				x[i] = Integer.parseInt(st.nextToken());
				y[i] = Integer.parseInt(st.nextToken());
				r[i] = Integer.parseInt(st.nextToken());
			}
			boolean[][] bad = new boolean[N][N];
			for(int i = 0;i<N;i++)
			{
				for(int j = i+1;j<N;j++)
				{
					int x1 = x[i];
					int x2 = x[j];
					int y1 = y[i];
					int y2 = y[j];
					int r1 = r[i];
					int r2 = r[j];
					int d2 = (x1-x2)*(x1-x2) + (y1 - y2)*(y1 - y2);
					if(d2 <= (r1+r2) * (r1+r2))//sketch
					{
						bad[i][j] = bad[j][i] = true;
					}
				}
			}
			long best = 0;
		loop:
			for(int i = 0;i<1<<N;i++)
			{
				long ans = 0;
				for(int j = 0;j<N;j++)
				{
					if(((1<<j) & i) != 0)
						ans += r[j] * r[j];
					for(int k = j+1;k<N;k++)
					{
						if(((1<<j) & i) != 0 && ((1<<k) & i) != 0 && bad[j][k])
						{
							continue loop;
						}
					}
				}
				best = Math.max(best, ans);
			}
			System.out.println(best);
		}
	}

}
