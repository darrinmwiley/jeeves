/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/treasurediving
TAGS: graph, dijkstra, TSP
EXPLANATION:
First, contract the graph to an IxI distance graph between idols, as well as an array of length I representing the distance from the start to each idol. 
This can be done using I+1 runs of Dijkstra, each starting at an idol or start position.
Next, run Traveling Salesperson Problem on all of the idols where dp[i][j] is equal to the cost of visiting all of the idols in i's hash and ending at location j, starting from position 0.
Last, the answer is argmax(bitCount(i)) where dp[i][j] + distFromStart(j) < a for some j
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
 
public class treasurediving {
	
	StringTokenizer st;
	BufferedReader file;
	PrintWriter pout;
	
	node[] nodes;
	
	public static void main(String[] args) throws Exception
	{
		new treasurediving().run();
	}	
	
	public void run() throws Exception
	{	
		file = new BufferedReader(new InputStreamReader(System.in));
		
		PrintWriter pout = new PrintWriter(System.out);
		
		int zz = nextInt();
		for(int z = 0;z<zz;z++)
		{
			int N = nextInt();
			int M = nextInt();
			nodes = new node[N];
			for(int i = 0;i<N;i++)
				nodes[i] = new node(i);
			for(int i = 0;i<M;i++)
			{
				int a = nextInt();
				int b = nextInt();
				int c = nextInt();
				connect(a,b,c);
			}
			int I = nextInt();
			int[] idols = new int[I];
			for(int i = 0;i<idols.length;i++)
			{
				idols[i] = nextInt();
			}
			int air = nextInt();
			int[] beginDist = new int[I];
			int[] fp2 = fp(0);
			for(int i = 0;i<idols.length;i++)
			{
				beginDist[i] = fp2[idols[i]];
			}
			int[][] dists = new int[I][I];
			for(int i = 0;i<idols.length;i++)
			{
				int[] fp = fp(idols[i]);
				for(int j = i+1;j<idols.length;j++)
				{
					dists[i][j] = fp[idols[j]];
					dists[j][i] = fp[idols[j]];
				}
			}
			int ans = solve(beginDist, dists, air);
			pout.println(ans);
		}
		
		pout.flush();
		pout.close();
	}
	
	public int solve(int[] beginDist, int[][] dists, int air)
	{
		int[][] dp = new int[1<<dists.length][dists.length];
		for(int i = 0;i<dp.length;i++)
		{
			Arrays.fill(dp[i], 1000001);
		}
		for(int i = 0;i<beginDist.length;i++)
		{
			dp[1<<i][i] = beginDist[i];
		}
		for(int i = 3;i<dp.length;i++)
		{
			if(Integer.bitCount(i) == 1)
				continue;
			for(int j = 0;j<dists.length;j++)
			{
				if((i & (1<<j)) != 0)//this location is visited, could be last
				{
					for(int k = 0;k<dists.length;k++)
					{
						if(k != j && (i & (1<<k)) != 0)//choose this as candidate second to last
						{
							//compare with visiting everything except for j, ending with k, then go to j from k
							dp[i][j] = Math.min(dp[i][j], dp[i ^ (1<<j)][k] + dists[k][j]);
						}
					}
				}
			}
		}
		int max = 0;
		for(int i = 0;i<dp.length;i++)
		{
			for(int j = 0;j<dists.length;j++)
			{
				int cost = dp[i][j] + beginDist[j];
				if(cost <= air)
				{
					max = Math.max(max, Integer.bitCount(i));
				}
			}
		}
		return max;
	}
	
	public int[] fp(int start)
	{
		int[] fp = new int[nodes.length];
		boolean[] vis = new boolean[nodes.length];
		Queue<state> que = new PriorityQueue<state>();
		state initial = new state(start, 0);
		Arrays.fill(fp, Integer.MAX_VALUE/4);
		fp[start] = 0;
		que.add(initial);
		while(!que.isEmpty())
		{
			state curr = que.poll();
			int loc = curr.loc;
			int cost = curr.cost;
			if(vis[loc])
				continue;
			vis[loc] = true;
			node n = nodes[loc];
			for(int i = 0;i<n.con.size();i++)
			{
				int next = n.con.get(i);
				int cs = n.cost.get(i);
				if(!vis[next] && cost + cs < fp[next])
				{
					fp[next] = cost + cs;
					state succ = new state(next, cost+cs);
					que.add(succ);
				}
			}
		}
		return fp;
	}
	
	private class state implements Comparable<state>{
		
		int loc;
		int cost;
		
		public state(int l, int c)
		{
			loc = l;
			cost = c;
		}
		
		public int compareTo(state s)
		{
			return Integer.compare(cost, s.cost);
		}
		
	}
	
	public void connect(int a, int b, int c)
	{
		nodes[a].con.add(b);
		nodes[b].con.add(a);
		nodes[a].cost.add(c);
		nodes[b].cost.add(c);
	}
	
	private class node{
		
		ArrayList<Integer> con;
		ArrayList<Integer> cost;
		int id;
		
		public node(int id)
		{
			this.id = id;
			con = new ArrayList<Integer>();
			cost = new ArrayList<Integer>();
		}
			
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