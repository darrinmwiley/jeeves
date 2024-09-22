/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/diplomacy
TAGS: bfs, graph diameter
EXPLANATION:
The answer to this problem is equivalent to the diameter of the graph, where the cost of traversing an edge is 1 iff the edge has two different colored nodes.
You can calculate this in an inelegant way by BFS'ing out from every possible middle node, which runs in V^3 time worst case
END ANNOTATION
*/
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.PriorityQueue;
import java.util.StringTokenizer;

public class Diplomacy {
    
    node[] nodes;
    int N;
    int M;
    
    public static void main(String[] args) throws Exception
    {
        new Diplomacy().run();      
    }
    
    public void run() throws Exception
    {
        BufferedReader file = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(file.readLine());
        N = Integer.parseInt(st.nextToken());
        M = Integer.parseInt(st.nextToken());
        nodes = new node[N];
        st = new StringTokenizer(file.readLine());
        for(int i = 0;i<nodes.length;i++)
        {
            nodes[i] = new node(i);
            nodes[i].color = Integer.parseInt(st.nextToken());
        }
        for(int i = 0;i<M;i++)
        {
            st = new StringTokenizer(file.readLine());
            int a = Integer.parseInt(st.nextToken())-1;
            int b = Integer.parseInt(st.nextToken())-1;
            con(a,b);
        }
        int minDiam = 101;
        for(int i = 0;i<nodes.length;i++)
        {
            minDiam = Math.min(minDiam,diam(i,nodes[i].color));
        }
        System.out.println(minDiam);
    }
    
    public int diam(int node, int color)
    {
        PriorityQueue<state> que = new PriorityQueue<state>();
        state start = new state(node, 0);
        que.add(start);
        int[] min = new int[N];
        Arrays.fill(min, 101);
        while(!que.isEmpty())
        {
            state curr = que.poll();
            if(min[curr.node] <= curr.diam)
            {
                continue;
            }
            min[curr.node] = curr.diam;
            node n = nodes[curr.node];
            for(int adj: n.con)
            {
                int newCost = curr.diam + (n.color ^ nodes[adj].color);
                if(min[adj] > newCost)
                {
                    que.add(new state(adj, newCost));
                }
            }
        }
        //System.out.println(Arrays.toString(min));
        int max = 0;
        for(int x:min)
        {
            max = Math.max(max, x);
        }
        return max;
    }
    
    private class state implements Comparable<state>{
        
        int node;
        int diam;
        
        public state(int node, int diam)
        {
            this.node = node;
            this.diam = diam;
        }

        @Override
        public int compareTo(state o) {
            return diam - o.diam;
        }
        
        
        
    }
    
    public void con(int a, int b)
    {
        nodes[a].con.add(b);
        nodes[b].con.add(a);
    }
    
    private class node{
        
        int id;
        int color;
        ArrayList<Integer> con;
        
        public node(int id)
        {
            con = new ArrayList<Integer>();
            this.id = id;
        }
        
    }
}