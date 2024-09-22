/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/intercept
TAGS: dijkstra, math, dfs
EXPLANATION:
First, run dijkstras algorithm to determine the fastest path from source to sink

Next, we will count the number of fastest paths coming out and going into each node

sort nodes by their fastest path from the source. 

Source has one fastest path coming in
the number of fastest paths coming into a node x is equal to the sum of fastest paths coming into all predecessors, such that pred's fastest path + edge weight from pred to x = x's fastest path
calculating these in order of fastest path will ensure dependencies are calculated first.

Sink has one fastest path coming out
the number of fastest paths coming out of a node x is equal to the sum of fastest paths coming out of all successors, such that x's fastest path + edge weight from x to successor = fastest path
calculating these in reverse order of fastest path will ensure dependencies are calculated first.

The total number of fastest paths through a node is the product of those coming in and those going out. Keep in mind this can grow very large very quickly.
I calculated number of paths modulo a large prime to avoid overflow. This is prone to collisions but that is unlikely.

another way of solving this problem:

remove all edges that are not part of a fastest path, and then find all articulation points

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
 
public class intercept {
    
    StringTokenizer st;
    BufferedReader file;
    
    node[] nodes;
    
    long modulus = 1000000007;
    
    public static void main(String[] args) throws Exception
    {
        new intercept().run();
    }   
    
    public void run() throws Exception
    {
        //this is fast IO - faster than Scanner/System.out.println
        file = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pout = new PrintWriter(System.out);
        
        int N = nextInt();
        int M = nextInt();
        
        nodes = new node[N];
        
        for(int i = 0;i<N;i++)
        {
            nodes[i] = new node(i);
        }
        
        for(int i = 0;i<M;i++)
        {
            int a = nextInt();
            int b = nextInt();
            long c = nextLong();
            connect(a,b,c);
        }
        
        int S = nextInt();
        int T = nextInt();
        
        state initial = new state(S, 0);
        
        PriorityQueue<state> que = new PriorityQueue<state>();
        que.add(initial);
        
        boolean[] vis = new boolean[N];
        
        while(!que.isEmpty())
        {
            state st = que.poll();
            int loc = st.location;
            long cost = st.cost;
            if(vis[loc])
            {
                continue;
            }
            vis[loc] = true;
            node curr = nodes[loc];
            curr.fp = Math.min(curr.fp, cost);
            for(int i = 0;i<curr.con.size();i++)
            {
                long newCost = cost + curr.cost.get(i);
                if(newCost < nodes[curr.con.get(i)].fp)
                {
                    nodes[curr.con.get(i)].fp = newCost;
                    state next = new state(curr.con.get(i), newCost);
                    que.add(next);
                }
            }
        }
        
        node[] forwardSort = nodes.clone();
        Arrays.sort(forwardSort, new Comparator<node>() {
            
            public int compare(node a, node b)
            {
                return Long.compare(a.fp, b.fp);
            }
            
        });
        
        node[] backwardsSort = nodes.clone();
        Arrays.sort(backwardsSort, new Comparator<node>() {
            
            public int compare(node a, node b)
            {
                return Long.compare(b.fp, a.fp);
            }
            
        });
        
        boolean[] vis2 = new boolean[N];
        
        nodes[S].fpForward = 1;
        nodes[T].fpBackwards = 1;
        
        for(node curr: forwardSort)
        {
            for(int i = 0;i<curr.con.size();i++)
            {
                if(curr.fp + curr.cost.get(i) == nodes[curr.con.get(i)].fp)
                {
                    nodes[curr.con.get(i)].fpForward += curr.fpForward;
                    if(nodes[curr.con.get(i)].fpForward > modulus)
                        nodes[curr.con.get(i)].fpForward -= modulus;
                }
            }
        }
        
        for(node curr: backwardsSort)
        {
            for(int i = 0;i<curr.pred.size();i++)
            {
                if(curr.fp - curr.predCost.get(i) == nodes[curr.pred.get(i)].fp)
                {
                    nodes[curr.pred.get(i)].fpBackwards += curr.fpBackwards;
                    if(nodes[curr.pred.get(i)].fpBackwards > modulus)
                        nodes[curr.pred.get(i)].fpBackwards -= modulus;
                }
            }
        }

        long totalPaths = nodes[T].fpForward % modulus;
        
        for(node n: nodes)
        {
            if(n.fpForward * n.fpBackwards % modulus == totalPaths)
                pout.print(n.id+" ");
        }
        
        pout.println();
        
        pout.flush();
        pout.close();
    }
    
    public void connect(int a, int b, long c)
    {
        nodes[a].con.add(b);
        nodes[a].cost.add(c);
        nodes[b].pred.add(a);
        nodes[b].predCost.add(c);
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
    
    private class state2 implements Comparable<state2>{
        
        int location;
        long cost;
        long weight;
        
        public state2(int l, long c, long w)
        {
            location = l;
            cost = c;
            weight = w;
        }
        
        public int compareTo(state2 s)
        {
            return Long.compare(cost, s.cost);
        }
        
    }
    
    private class node{
        
        int id;
        ArrayList<Integer> con;
        ArrayList<Long> cost;
        ArrayList<Integer> pred;
        ArrayList<Long> predCost;
        long fp = Long.MAX_VALUE/4;
        
        long fpForward;
        long fpBackwards;
        
        public node(int id)
        {
            this.id = id;
            this.con = new ArrayList<Integer>();
            this.cost = new ArrayList<Long>();
            this.pred = new ArrayList<Integer>();
            this.predCost = new ArrayList<Long>();
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