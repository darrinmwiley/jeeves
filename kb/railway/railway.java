/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/railway
TAGS: graph, bfs
EXPLANATION:
represent each (switch, letter, direction) as a vertex of a graph. 

This will result in 6*N vertices and 4*N + 2*M edges

After constructing the graph, find the shortest non-trivial path from 
(1,A,outbound) to (1,A,outbound), and trace back through the path to determine
each switch configuration.
END ANNOTATION
*/

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.Queue;
import java.util.StringTokenizer;

public class railway {
	
	//inward - a goes to b or c, b and c go to a
	//outward - go to other junctions
	
	int N,M;
	node[] nodes;
	
	public static void main(String[] args) throws Exception
	{
		new railway().run();
	}
	
	public void run() throws Exception{
		//reach 1a without previous being 1b or 1c
		BufferedReader file = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(file.readLine());
		N = Integer.parseInt(st.nextToken());
		M = Integer.parseInt(st.nextToken());
		nodes = new node[N*6];
		for(int i = 0;i<nodes.length;i++)
		{
			nodes[i] = new node(i);
		}
		for(int i = 0;i<N;i++)
		{
			int ao = getId(i,'A',0);
			int ai = getId(i,'A',1);
			int bo = getId(i,'B',0);
			int bi = getId(i,'B',1);
			int co = getId(i,'C',0);
			int ci = getId(i,'C',1);
			con(ai,bo);
			con(ai,co);
			con(ci,ao);
			con(bi,ao);
		}
		for(int i = 0;i<M;i++)
		{
			st = new StringTokenizer(file.readLine());
			String a = st.nextToken();
			String b = st.nextToken();
			int ai = Integer.parseInt(a.substring(0,a.length() - 1))-1;
			int bi = Integer.parseInt(b.substring(0,b.length() - 1))-1;
			char ac = a.charAt(a.length() - 1);
			char bc = b.charAt(b.length() - 1);
			int aout = getId(ai, ac, 0);
			int ain = getId(ai,ac,1);
			int bout = getId(bi,bc,0);
			int bin = getId(bi,bc,1);
			con(aout,bin);
			con(bout, ain);
		}
		
		Queue<Integer> que = new LinkedList<Integer>();
		que.add(1);
		boolean[] vis = new boolean[nodes.length];
		int[] p = new int[nodes.length];
		Arrays.fill(p, -1);
		while(!que.isEmpty())
		{
			int x = que.poll();
			for(int y: nodes[x].con)
			{
				if(!vis[y])
				{
					vis[y] = true;
					p[y] = x;
					que.add(y);
				}
			}
		}
		if(p[1] == -1)
		{
			System.out.println("Impossible");
			return;
		}else {
			char[] chars = new char[N];
			Arrays.fill(chars, 'B');
			int current = 1;
			do
			{
				int junction = (current/6);
				char track = "ABC".charAt((current/2)%3);
				if(track == 'C')
					chars[junction] = 'C';
				current = p[current];
			}while(current != 1);
			System.out.println(chars);
		}
	}
	
	public void con(int a, int b)
	{
		nodes[a].con.add(b);
	}
	
	public int getId(int junction, char letter, int inward)
	{
		return junction * 6 + (letter - 'A')*2 + inward;
	}
	
	private class node{
		public ArrayList<Integer> con;
		int id;
		
		public node(int id)
		{
			this.id = id;
			this.con = new ArrayList<>();
		}
	}
}
