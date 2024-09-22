/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/qcqc
TAGS: interactive, dsu, union-find, randomized, SALTY
EXPLANATION:
first, find one good machine. We can do this in 6 queries by maintaining by eliminating half
of all machines over and over again and maintaining the strict majority invariant.

We do this by pairing machines and letting them test each other. 

If both machines say each
other are good, we know they are either both good or both bad. In this case, discard one 
and keep one. Since there are more good than bad to begin with, halving both won't hurt

If at least one machine calls the other bad, either one is bad or both. In this case, we discard both.
Since we're getting rid of at least as many bad as good here, this is fine as well.

Some care must be taken with an odd number of candidates. If there are odd candidates and an odd number
of pairs call each other good, we want to discard. Otherwise we want to keep. An helped me figure this out,
I'm gonna leave why as an exercise to the reader.

While narrowing down candidates for a good machine, also randomly pair eliminated machines and have them
test each other. due to the majority constraint, there is a probability of at least 1/4 that two machines will
call each other good. Any time this happens, we know their results are identical.

maintain a unionfind data structure keeping track of connected components (which machines are the same).

It will take at most 6 queries to find one good computer, for smaller cases it's less and we have more
breathing room to compensate for the fewer number of CC's

After finding a good machine, follow the following iterative process:

1) use the connected components from the union find to propagate all information .
we want to mark as many good and bad machines as possible. The more bad machines we have
marked, the less work we have remaining. The more good machines we have marked, the stronger
we can make our queries, as each can test a connected component.
2) for every connected component that we don't know the answer to, use a good machine (if one is available)
in the next query to test it. (I tested in order of greatest CC size to least, it's intuitive why this is a good idea)
3) propagate new information and repeat

once all machines are known, output the result obvi

END ANNOTATION
*/
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.Comparator;
import java.util.HashMap;
import java.util.Random;
import java.util.Scanner;
import java.util.TreeSet;

public class qcqc {
	
	PrintWriter pout = new PrintWriter(System.out);
	Scanner file = new Scanner(System.in);
	Random rand = new Random(42069);
	
	int GOOD = 1;
	int BAD = 0;
	int UNKNOWN = 2;
	
	public static void main(String[] args) throws NumberFormatException, IOException
	{
		new qcqc().run();	
	}
	
	public void run() throws IOException
	{
		int B = file.nextInt();
		for(int z = 0;z<B;z++)
		{
			int N = file.nextInt();
			ArrayList<Integer> candidates = new ArrayList<Integer>();
			boolean[] discard = new boolean[N];
			boolean[][] compared = new boolean[N][N];
			ArrayList<Integer> all = new ArrayList<Integer>();
			UnionFind uf = new UnionFind(N);
			for(int i = 0;i<N;i++)
			{
				all.add(i);
			}
			for(int i = 0;i<N;i++)
				candidates.add(i);
			Collections.shuffle(candidates, rand);
			while(candidates.size() != 1)
			{
				int[] query = new int[N];
				Arrays.fill(query, -1);
				for(int i =1;i<candidates.size();i+=2)
				{
					int a = candidates.get(i-1);
					int b = candidates.get(i);
					query[a] = b;
					query[b] = a;
				}
			loop:
				for(int i = 0;i<all.size();i++)
				{
					if(discard[i] && query[i] == -1)
					{
						for(int j = i+1;j<all.size();j++)
						{
							if(discard[j] && query[j] == -1)
							{
								if(i != j && uf.find(i) != uf.find(j) && !compared[i][j])
								{
									compared[i][j] = compared[j][i] = true;
									query[i] = j;
									query[j] = i;
									continue loop;
								}
							}
						}
					}
				}
				int[] response = interact(query);
				int doubleGood = 0;
				for(int i = 0;i<candidates.size();i++)
				{
					if(i == candidates.size() - 1 && candidates.size() % 2 == 1)
					{
						if(doubleGood % 2 == 1)
							discard[candidates.get(i)] = true;
					}else {
						int a = candidates.get(i);
						int b = query[a];
						if(a > b || discard[a] || discard[b])
							continue;
						if(response[a] == BAD || response[b] == BAD)
						{
							discard[a] = discard[b] = true;
						}else {
							uf.union(a, b);
							discard[a] = true;
							doubleGood++;
						}
					}
				}
				for(int i = 0;i<response.length;i++)
				{
					int a = i;
					int b = query[i];
					if(b != -1 && a != -1 && discard[a] && discard[b])
					{
						if(response[a] == GOOD && response[b] == GOOD)
						{
							uf.union(a, b);
						}
					}
				}
				Collections.shuffle(all, rand);
				candidates.clear();
				for(int i: all)
				{
					if(!discard[i])
						candidates.add(i);
				}
			}
			Comparator<ArrayList> bySize = new Comparator<ArrayList>() {
				public int compare(ArrayList a, ArrayList b)
				{
					return Integer.compare(b.size(), a.size());
				}
			};
			int[] verdict = new int[N];
			Arrays.fill(verdict, UNKNOWN);
			ArrayList<Integer> good = new ArrayList<Integer>();
			ArrayList<Integer> cc = uf.cc(candidates.get(0));
			for(int x: cc)
				verdict[x] = GOOD;
			while(!finished(verdict))
			{
				int used = 0;
				updateGood(verdict, good);
				ArrayList<ArrayList<Integer>> ccs = uf.cc();
				Collections.sort(ccs, bySize);
				int[] query = new int[N];
				Arrays.fill(query, -1);
				for(ArrayList<Integer> component: ccs)
				{
					int rep = component.get(0);
					if(verdict[rep] == UNKNOWN && used < good.size())
					{
						int pair = good.get(used++);
						query[pair] = rep;
					}
				}
				int[] response = interact(query);
				for(int i = 0;i<response.length;i++)
				{
					if(response[i] != UNKNOWN)
						verdict[query[i]] = response[i];
				}
				updateVerdict(verdict, uf);
				updateGood(verdict, good);
			}
			pout.print("answer ");
			for(int x: verdict)
				pout.print(x);
			pout.println();
			pout.flush();
		}
	}
	
	public boolean finished(int[] verdict)
	{
		for(int i: verdict)
			if(i == UNKNOWN)
				return false;
		return true;
	}
	
	public void updateVerdict(int[] verdict, UnionFind uf)
	{
		ArrayList<ArrayList<Integer>> ccs = uf.cc();
	loop:
		for(int i = 0;i<ccs.size();i++)
		{
			ArrayList<Integer> cc = ccs.get(i);
			for(int j: cc)
			{
				if(verdict[j] != UNKNOWN)
				{
					for(int k: cc)
					{
						verdict[k] = verdict[j];
					}
					continue loop;
				}
			}
		}
		
	}
	
	public void updateGood(int[] verdict, ArrayList<Integer> good)
	{
		good.clear();
		for(int i = 0;i<verdict.length;i++)
			if(verdict[i] == GOOD)
				good.add(i);
	}
	
/*
10101:

1
5
//test 0 3 2 5 4
-1010
//test 0 3 4 5 4


0101110
//test 4 7 0 1 6 5 2 
10-0111
//test 2 1 6 5 4 3 0 
101110-
//test 0 0 0 0 0 3 0 
-----0-
 */
	
	public int[] interact(int[] query)
	{
		pout.print("test ");
		for(int x: query)
			pout.print(x+1+" ");
		pout.println();
		pout.flush();
		String response = file.next();
		int[] ans = new int[query.length];
		for(int i =0;i<ans.length;i++)
		{
			if(response.charAt(i) == '0')
				ans[i] = BAD;
			else if(response.charAt(i) == '1')
				ans[i] = GOOD;
			else ans[i] = UNKNOWN;
		}
		return ans;
	}
	
	private class UnionFind
	{
		
		int[] p;
		
		public UnionFind(int sz)
		{
			p = new int[sz];
			Arrays.fill(p, -1);
		}
		
		public int find(int x)
		{
			if(p[x] < 0)
				return x;
			return p[x] = find(p[x]);
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
		
		public ArrayList<Integer> cc(int x)
		{
			int px = find(x);
			ArrayList<Integer> ret = new ArrayList<Integer>();
			for(int i = 0;i<p.length;i++)
			{
				if(find(i) == px)
					ret.add(x);
			}
			return ret;
		}
		
		public ArrayList<ArrayList<Integer>> cc()
		{
			HashMap<Integer, ArrayList<Integer>> map = new HashMap<>();
			for(int i =0 ;i<p.length;i++)
			{
				int px = find(i);
				if(!map.containsKey(px))
					map.put(px, new ArrayList<Integer>());
				map.get(px).add(i);
			}
			ArrayList<ArrayList<Integer>> list = new ArrayList<ArrayList<Integer>>();
			for(int x: map.keySet())
				list.add(map.get(x));
			return list;
		}
	}
	
}
