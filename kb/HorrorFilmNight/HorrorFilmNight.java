/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/horrorfilmnight
TAGS: dp, state flag
EXPLANATION:
dp[D][S] = the maximum number of movies that can be watched by day D in state S

State can be one of the following: 
0: someone must like the next movie watched
1: Emma must like the next movie watched
2: Marcos must like the next movie watched
END ANNOTATION
*/

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.StringTokenizer;

public class HorrorFilmNight {
	
	public static void main(String[] args) throws Exception
	{
		new HorrorFilmNight().run();
	}
	
	public void run() throws Exception{
		BufferedReader file = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(file.readLine());
		int N = Integer.parseInt(st.nextToken());
		boolean[] a = new boolean[1000001];
		for(int i = 0;i<N;i++)
		{
			int elem = Integer.parseInt(st.nextToken());
			a[elem] = true;
		}
		st = new StringTokenizer(file.readLine());
		int M = Integer.parseInt(st.nextToken());
		boolean[] b = new boolean[1000001];
		for(int i = 0;i<M;i++)
		{
			int elem = Integer.parseInt(st.nextToken());
			b[elem] = true;
		}
		int[][] dp = new int[1000001][4];
		for(int i = 0;i<dp.length;i++)
			Arrays.fill(dp[i], -1);
		dp[0][0] = 0;
		for(int i = 0;i<dp.length-1;i++)
		{
			for(int j = 0;j<4;j++)
			{
				if(dp[i][j] != -1)
				{
					int after = getAfter(a[i], b[i]);
					dp[i+1][j] = Math.max(dp[i+1][j],dp[i][j]);
					if(j == 0 && (a[i] || b[i]))
					{
						dp[i+1][after] = Math.max(dp[i+1][after], dp[i][j] + 1);
					}
					if(j == 1 && a[i])
					{
						dp[i+1][after] = Math.max(dp[i+1][after], dp[i][j] + 1);
					}
					if(j == 2 && b[i])
					{
						dp[i+1][after] = Math.max(dp[i+1][after], dp[i][j] + 1);
					}
				}
			}
		}
		int max = 0;
		for(int i = 0;i<4;i++)
		{
			max = Math.max(dp[dp.length - 1][i], max);
		}
		System.out.println(max);
	}
	
	public int getAfter(boolean aLike, boolean bLike)
	{
		if(aLike && bLike)
		{
			return 0;
		}
		if(bLike && !aLike)
		{
			return 1;
		}
		if(aLike && ! bLike)
		{
			return 2;
		}
		return 3;
	}
}
