/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/wordequations
TAGS: dp, greedy, dfs, dag
EXPLANATION:
it will never hurt us to take each letter at the earliest possible time. we can be greedy in that regard.

let dp[i][j] = the max number of letters that word i can cover, starting from position j

if word i is a leaf, we can naively calculate this

if word i is not a leaf, we will use as many letters as possible from the left child and then as many as possible from the right child, referencing dp in both cases.

make sure to solve subproblems in topological order. It is easy to do this using DFS.

END ANNOTATION
*/
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.Arrays;
import java.util.HashMap;

class wordequations
{
	BufferedReader file;
	int[] p;
	char[][] strs;
	int[] L;
	int[] R;
	int[][] dp;
	char[] make;
	boolean[] vis;
	
	public static void main (String[] args) throws java.lang.Exception
	{
		new wordequations().run();
	}
	
	public void run() throws Exception
	{
		file = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pout = new PrintWriter(System.out);
        int zz = Integer.parseInt(file.readLine());
        for(int z = 0;z<zz;z++)
        {
        	int N = Integer.parseInt(file.readLine());
        	HashMap<String, Integer> index = new HashMap<String,Integer>();
        	p = new int[N];
        	strs = new char[N][];
        	L = new int[N];
        	R = new int[N];
        	vis = new boolean[N];
        	Arrays.fill(p, -1);
        	Arrays.fill(L, -1);
        	Arrays.fill(R, -1);
        	for(int i = 0;i<N;i++)
        	{
        		String[] line = file.readLine().split(" ");
        		if(!index.containsKey(line[0]))
        		{
        			index.put(line[0], index.size());
        		}
        		int ind = index.get(line[0]);
        		if(line.length == 3)
        		{
        			strs[ind] = line[2].toCharArray();
        		}else {
        			if(!index.containsKey(line[2]))
            		{
            			index.put(line[2], index.size());
            		}
        			if(!index.containsKey(line[4]))
            		{
            			index.put(line[4], index.size());
            		}
        			int lind = index.get(line[2]);
        			int rind = index.get(line[4]);
        			p[lind] = ind;
        			p[rind] = ind;
        			L[ind] = lind;
        			R[ind] = rind;
        		}
        	}
        	String start = file.readLine();
        	make = file.readLine().toCharArray();
        	dp = new int[N][make.length];
        	int startIndex = index.get(start);
        	dfs(startIndex);
        	if(dp[startIndex][0] == make.length) {
        		System.out.println("YES");
        	}else
        		System.out.println("NO");
        }
        
	}
	
	public void dfs(int index)
	{
		if(vis[index])
			return;
		vis[index] = true;
		if(L[index] != -1) {
			dfs(L[index]);
			dfs(R[index]);
			for(int i = 0;i<dp[index].length;i++)
			{
				int lmax = dp[L[index]][i];
				if(i+lmax>=make.length)
					dp[index][i] = lmax;
				else {
					dp[index][i] = dp[R[index]][i+lmax]+lmax;
				}
			}
		}else {
			char[] chars = strs[index];
			for(int i = 0;i<dp[index].length;i++)
			{
				int ans = 0;
				for(int j = 0;j<chars.length;j++)
				{
					if(i+ans < make.length && chars[j] == make[i+ans])
					{
						ans++;
					}
				}
				dp[index][i] = ans;
			}
		}
		
	}
	
}