/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/minspantree
TAGS: MST, DSU
EXPLANATION:
standard min spanning tree using Kruskal's algorithm and Union Find
END ANNOTATION
*/
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Comparator;
import java.util.PriorityQueue;
import java.util.StringTokenizer;

public class minspantree {
    
    public static void main(String[] args) throws IOException
    {
        new minspantree().run();
    }
    
    public void run() throws NumberFormatException, IOException
    {
        BufferedReader file = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(file.readLine());
        int N = Integer.parseInt(st.nextToken());
        int E = Integer.parseInt(st.nextToken());
    loop:
        while(N!=0)
        {
            PriorityQueue<edge> que = new PriorityQueue<edge>();
            for(int i = 0;i<E;i++)
            {
                st = new StringTokenizer(file.readLine());
                edge e = new edge(Integer.parseInt(st.nextToken()),Integer.parseInt(st.nextToken()),Integer.parseInt(st.nextToken()));
                que.add(e);
            }
            int cost = 0;
            int x = 0;
            Comparator<edge> comp = new Comparator<edge>(){
                
                public int compare(edge a, edge b)
                {
                    if(a.a==b.a)
                        return Integer.compare(a.b,b.b);
                    return Integer.compare(a.a,b.a);
                }
                
            };
            PriorityQueue<edge> used = new PriorityQueue<edge>(comp);
            UnionFind uf = new UnionFind(N);
            while(!que.isEmpty()&&x!=N-1)
            {
                edge e = que.poll();
                int pa = uf.find(e.a);
                int pb = uf.find(e.b);
                if(pa!=pb)
                {
                    cost+=e.c;
                    uf.union(pa,pb);
                    used.offer(e);
                    x++;
                }
            }
            if(x!=N-1)
            {
                st = new StringTokenizer(file.readLine());
                N = Integer.parseInt(st.nextToken());
                E = Integer.parseInt(st.nextToken());
                System.out.println("Impossible");
                continue loop;
            }
            System.out.println(cost);
            while(!used.isEmpty())
            {
                edge e = used.poll();
                System.out.println(e.a+" "+e.b);
            }
            st = new StringTokenizer(file.readLine());
            N = Integer.parseInt(st.nextToken());
            E = Integer.parseInt(st.nextToken());
        }
    }
    
    class edge implements Comparable<edge>{
        
        int a;
        int b;
        int c;
        public edge(int a, int b, int c)
        {
            this.a = Math.min(a, b);
            this.b = Math.max(a, b);
            this.c = c;
        }
        @Override
        public int compareTo(edge o) {
            return c-o.c;
        }
        
    }
    
    class UnionFind{
        
        int[] ints;
        
        public UnionFind(int N)
        {
            ints = new int[N];
            Arrays.fill(ints, -1);
        }
        
        public int find(int a)
        {
            if(ints[a]<0)
                return a;
            return ints[a] = find(ints[a]);
        }
        
        public void union(int a, int b)
        {
            int aa = find(a);
            int bb = find(b);
            if(aa==bb)
                return;
            ints[aa]+=ints[bb];
            ints[bb] = aa;
        }
        
    }
    
}