/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/cardiology
TAGS: math, graph, dfs
EXPLANATION:

Observation 1: For a given candidate P, there is a contiguous region of size R that any location will move to next from index PR to (P+1)R - 1. This touches at most (R/C)+1 rows

Observation 2: for a given candidate P, card (r,c) will move to ((PR + r) / C, (PR + r) % C). Notice how this is not dependent on c at all. Hence any element from the same row will
behave the same. 

For every possible P, build a graph where each of the ~(R/C) relevant rows are represented by a node, and there is an edge between U and V if U transitions to V.

DFS to find the stable location each node leads to and the maximum number of hops and take the best one. 

C potential choices of P, graph of size R/C for each test, overall O(R) runtime.

END ANNOTATION
*/
import java.util.Arrays;
import java.util.Scanner;

public class cardiology {

	public static void main(String[] args)
	{
		new cardiology().run();
	}
	
	int oo = Integer.MAX_VALUE;
	
	int[] to,dest,len;
	
	int[] bto, bdest, blen;
	
	public void run()
	{
		Scanner file = new Scanner(System.in);
		long R = file.nextLong();
		long C = file.nextLong();
		int[] ans = solve(R,C);
		long bestP = -1;
		long I = -1;
		long J = -1;
		long dist = oo;
		long L = 0;
	loop:
		for(long P = 0;P<C;P++)
		{
			long minRow = P*R / C;
			long maxRow = ((P+1)*R - 1) / C;
			to = new int[(int)(maxRow - minRow + 1)];
			len = new int[to.length];
			dest = new int[to.length];
			Arrays.fill(dest, -1);
			for(long r = minRow;r<=maxRow;r++) {
				to[(int)(r-minRow)] = (int)((P*R + r) / C - minRow);
			}
			for(int i = 0;i<to.length;i++)
				dfs(i);
			for(int i = 1;i<to.length;i++)
				if(dest[i] != dest[i-1])
					continue loop;
			long r = dest[0] + minRow;
			long c = (P*R + r) % C;
			long d = centerDist(r,c,R,C);
			len = new int[to.length];
			Arrays.fill(len,oo);
			for(int i = 0;i<to.length;i++)
			{
				long toR = to[i]+minRow;
				long toC = (P * R + i + minRow) % C;
				if(toR == r && toC == c)
					len[i] = 1;
			}
			long maxLen = 0;
			for(int i =0;i<len.length;i++)
			{
				dfs2(i);
				maxLen = Math.max(maxLen, len[i]);
			}
			if(d < dist) {
				dist = d;
				I = r;
				J = c;
				bestP = P;
				L = maxLen;
			}
		}
		System.out.printf("%d %d %d %d",bestP+1,I+1,J+1,L+1);
	}
	
	public int[] solve(long R, long C)
	{
		long bestP = -1;
		long I = -1;
		long J = -1;
		long dist = oo;
		long L = 0;
	loop:
		for(long P = 0;P<C;P++)
		{
			long minRow = P*R / C;
			long maxRow = ((P+1)*R - 1) / C;
			to = new int[(int)(maxRow - minRow + 1)];
			len = new int[to.length];
			dest = new int[to.length];
			Arrays.fill(dest, -1);
			for(long r = minRow;r<=maxRow;r++)
				to[(int)(r-minRow)] = (int)((P*R + r) / C - minRow);
			for(int i = 0;i<to.length;i++)
				dfs(i);
			for(int i = 1;i<to.length;i++)
				if(dest[i] != dest[i-1])
					continue loop;
			long r = dest[0] + minRow;
			long c = (P*R + r) % C;
			long d = centerDist(r,c,R,C);
			len = new int[to.length];
			Arrays.fill(len,oo);
			for(int i = 0;i<to.length;i++)
			{
				long toR = to[i]+minRow;
				long toC = (P * R + i + minRow) % C;
				if(toR == r && toC == c)
					len[i] = 1;
			}
			long maxLen = 0;
			for(int i =0;i<len.length;i++)
			{
				dfs2(i);
				maxLen = Math.max(maxLen, len[i]);
			}
			if(d < dist) {
				dist = d;
				I = r;
				J = c;
				bestP = P;
				L = maxLen;
			}
		}
		return new int[] {(int) (bestP+1), (int) (I+1), (int) (J+1), (int) (L+1)};
	}
	
	public int centerDist(long r, long c, long R, long C)
	{
		long[][] centers = new long[][] {{R/2-1,R/2,R/2-1,R/2},{C/2-1,C/2-1,C/2,C/2}};
		if((R & 1) == 1 && (C & 1) == 1)
			centers = new long[][] {{R/2},{C/2}};
		if((R & 1) == 0 && (C & 1) == 1)
			centers = new long[][] {{R/2-1,R/2},{C/2,C/2}};
		if((R & 1) == 1 && (C & 1) == 0)
			centers = new long[][] {{R/2,R/2},{C/2-1,C/2}};
		long minDist = oo;
		for(int i = 0;i<centers[0].length;i++)
		{
			minDist = Math.min(minDist, Math.abs(r-centers[0][i]) + Math.abs(c - centers[1][i]));
		}
		return (int) minDist;
	}
	
	public int dfs2(int r)
	{
		if(len[r] != oo)
			return len[r];
		return len[r] = dfs2(to[r]) + 1;
	}
	
	public int dfs(int r)
	{
		if(dest[r] != -1)
			return dest[r];
		if(to[r] == r)
			return dest[r] = r;
		return dest[r] = dfs(to[r]);
	}
	
	
	
}
