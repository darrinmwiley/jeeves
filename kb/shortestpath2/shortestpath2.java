/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/shortestpath2
TAGS: dijkstra
EXPLANATION:
straightforward dijkstra's algorithm, just calculate the cost of traversing an edge at the next opportunity. 

Watch out for the edge case of P = 0, where the edge is only available at a single time.
END ANNOTATION
*/
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Comparator;
import java.util.LinkedList;
import java.util.PriorityQueue;
import java.util.Queue;
import java.util.StringTokenizer;
 
public class shortestpath2 {
    
    StringTokenizer st;
    BufferedReader file;
    
    node[] nodes;
    
    long modulus = 1000000007;
    
    public static void main(String[] args) throws Exception
    {
        new shortestpath2().run();
    }   
    
    public void run() throws Exception
    {
        //this is fast IO - faster than Scanner/System.out.println
        file = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pout = new PrintWriter(System.out);
       loop:
        while(true)
        {
            int N = nextInt();
            int M = nextInt();
            int q = nextInt();
            int s = nextInt();
            
            if(N == 0)
            {
                break loop;
            }
            nodes = new node[N];
            
            for(int i = 0;i<N;i++)
            {
                nodes[i] = new node(i);
            }
            for(int i = 0;i<M;i++)
            {
                int u = nextInt();
                int v = nextInt();
                int t0 = nextInt();
                int p = nextInt();
                int d = nextInt();
                connect(u,v,t0,p,d);
            }
            
            PriorityQueue<state> que = new PriorityQueue<state>();
            state initial = new state(s, 0);
            que.add(initial);
            
            boolean[] vis = new boolean[N];
            
            while(!que.isEmpty())
            {
                state curr = que.poll();
                if(vis[curr.location])
                {
                    continue;
                }
                nodes[curr.location].fp = Math.min(nodes[curr.location].fp, curr.cost);
                vis[curr.location] = true;
                node n = nodes[curr.location];
                for(edge e:n.con)
                {
                    if(e.getCostAfter(curr.cost) < nodes[e.v].fp)
                    {
                        nodes[e.v].fp = e.getCostAfter(curr.cost);
                        state next = new state(e.v, e.getCostAfter(curr.cost));
                        que.add(next);
                    }
                }
            }
            
            for(int i = 0;i<q;i++)
            {
                int query = nextInt();
                long fp = nodes[query].fp;
                if(fp == Long.MAX_VALUE / 4)
                {
                    pout.println("Impossible");
                }else {
                    pout.println(fp);
                }
            }
            pout.println();
        }
 
        pout.flush();
        pout.close();
    }
    
    public void connect(int u, int v, int t0, int p, int d)
    {
        nodes[u].con.add(new edge(v,t0,p,d));
    }
    
    private class edge{
        
        int v;
        int t0;
        int p;
        int d;
        
        public edge(int v, int t0, int p, int d)
        {
            this.v = v;
            this.t0 = t0;
            this.p = p;
            this.d = d;
        }
        
        public long getCostAfter(long t)
        {
            if(t0 >= t)
                return t0 + d;
            if(p == 0)
            {
                return Long.MAX_VALUE/4;
            }
            else if((t - t0) % p == 0)
            {
                return t + d;
            }else {
                long num = (t-t0)/p;
                return t0 + (num+1)*p + d;
            }   
        }
        
    }
    
    private class state implements Comparable<state>{
        
        int location;
        long cost;
        
        public state(int l, long c)
        {
            location = l;
            cost = c;
        }
        
        public int compareTo(state s)
        {
            return Long.compare(cost,  s.cost);
        }
        
    }
    
    private class node{
        
        int id;
        ArrayList<edge> con;
        long fp = Long.MAX_VALUE/4;
        
        public node(int id)
        {
            this.id = id;
            this.con = new ArrayList<edge>();
        }
        
    }
    
    
    //don't worry about this, just a helper method
    public void newst()
    {
        try {
            st = new StringTokenizer(file.readLine());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
    
    //consumes the entire next line of input
    public String readLine() throws IOException
    {
        return file.readLine();
    }
    
    //get's the next word of input
    public String next()
    {
        if(st == null || !st.hasMoreTokens())
            newst();
        return st.nextToken();
    }
    
    //tries to parse the next piece of input as an int
    public int nextInt()
    {
        if(st == null || !st.hasMoreTokens())
            newst();
        return Integer.parseInt(st.nextToken());
    }
    
    //tries to parse the next piece of input as a long
    public long nextLong()
    {
        if(st == null || !st.hasMoreTokens())
            newst();
        return Long.parseLong(st.nextToken());
    }
    
}