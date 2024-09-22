/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/naturereserve
TAGS: mst
EXPLANATION:
There is never a reason to send the same data over a channel more than once.

Hence for some MST, the entire program will be transmitted once for each station
that doesn't already have it. This amounts to a constant L*(N-S). Aside from this,
the only cost is that of creating the MST by activating communication channels.

Channels that start with the program are all connected with cost 0. After that, finish
the MST and report cost + L*(S-N).
END ANNOTATION
*/

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.PriorityQueue;
import java.util.StringTokenizer;

public class NatureReserve {
	
	public static void main(String[] args) throws Exception
	{
		new NatureReserve().run();
	}
	
	public void run() throws Exception{
		BufferedReader file = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(file.readLine());
		int zz = Integer.parseInt(st.nextToken());
		
		for(int z = 0;z<zz;z++)
		{
			st = new StringTokenizer(file.readLine());
			int N = Integer.parseInt(st.nextToken());
			int M = Integer.parseInt(st.nextToken());
			long L = Integer.parseInt(st.nextToken());
			int S = Integer.parseInt(st.nextToken());
			st = new StringTokenizer(file.readLine());
			unionFind uf = new unionFind(N+1);
			for(int i = 0;i<S;i++)
				uf.union(0,Integer.parseInt(st.nextToken()));
			PriorityQueue<edge> que = new PriorityQueue<edge>();
			for(int i = 0;i<M;i++)
			{
				st = new StringTokenizer(file.readLine());
				int a = Integer.parseInt(st.nextToken());
				int b = Integer.parseInt(st.nextToken());
				int c = Integer.parseInt(st.nextToken());
				que.add(new edge(a,b,c));
			}
			long totalCost = 0;
			int connected = S+1;
			while(connected != N+1)
			{
				edge e = que.poll();
				int a = e.a;
				int b = e.b;
				int c = e.c;
				if(uf.find(a) != uf.find(b))
				{
					uf.union(a, b);
					totalCost += c;
					connected++;
				}
			}
			System.out.println(totalCost + L*(N-S));
		}
	}
	
	private class edge implements Comparable<edge>{
		int a;
		int b;
		int c;
		public edge(int a, int b, int c)
		{
			this.a = a;
			this.b = b;
			this.c = c;
		}
		@Override
		public int compareTo(edge o) {
			return Integer.compare(c,o.c);
		}
		
	}
	
	private class unionFind{
		
		int[] p;
		
		public unionFind(int sz)
		{
			p = new int[sz];
			Arrays.fill(p, -1);
		}
		
		public int find(int a)
		{
			if(p[a] < 0)
				return a;
			return p[a] = find(p[a]);
		}
		
		public void union(int a, int b)
		{
			int pa = find(a);
			int pb = find(b);
			if(pa == pb)
				return;
			p[pa] += p[pb];
			p[pb] = pa;
			
		}
		
	}
	
}
