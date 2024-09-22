/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/importspaghetti
TAGS: graph, bfs
EXPLANATION:
model every file as a vertex of a graph, and each dependency as a directed edge.

for each vertex v, find the shortest nontrivial path from v->v, and report the smallest one if it exists
END ANNOTATION
*/

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.Queue;
import java.util.StringTokenizer;

public class ImportSpaghetti {
    
    int INF = 1000;
    
    public static void main(String[] args) throws Exception
    {
        new ImportSpaghetti().run();        
    }
    
    node[] nodes;
    
    int bestCost = 1000;
    String ans = "SHIP IT";
    
    public void run() throws Exception
    {
        BufferedReader file = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st;
        int N = Integer.parseInt(file.readLine());
        st = new StringTokenizer(file.readLine());
        HashMap<String, Integer> nameToId = new HashMap<String, Integer>();
        for(int i = 0;i<N;i++)
        {
            nameToId.put(st.nextToken(), i);
        }
        nodes = new node[N];
        for(int i = 0;i<N;i++)
        {
            st = new StringTokenizer(file.readLine());
            String nam = st.nextToken();
            int num = Integer.parseInt(st.nextToken());
            int id = nameToId.get(nam);
            nodes[id] = new node(i,nam);
            for(int j = 0;j<num;j++)
            {
                String[] next = file.readLine().split(" ", 2)[1].split(", ");
                for(String s: next)
                {
                    con(id, nameToId.get(s));
                }
            }
        }
        for(int i = 0;i<N;i++)
        {
            fastestLoop(i);
        }
        System.out.println(ans);
    }
    
    public void fastestLoop(int location)
    {
        Queue<state> que = new LinkedList<state>();
        boolean[] vis = new boolean[nodes.length];
        int[] pred = new int[nodes.length];
        pred[location] = -1;
        vis[location] = true;
        que.add(new state(location, 0));
        while(!que.isEmpty())
        {
            state st = que.poll();
            int L = st.location;
            int C = st.cost;
            if(nodes[L].connectedTo[location])
            {
                if(bestCost > C) {
                    bestCost = C;
                    backtrack(pred, L);
                }
                return;
            }
            for(int x: nodes[L].con)
            {
                if(!vis[x])
                {
                    vis[x] = true;
                    pred[x] = L;
                    que.add(new state(x, C + 1));
                }
            }
        }
    }
    
    public void backtrack(int[] pred, int location)
    {
        int curr = location;
        String ans2 = "";
        while(true)
        {
            ans2 = nodes[curr].name+" "+ans2;
            if(pred[curr] != -1)
            {
                curr = pred[curr];
            }else {
                break;
            }
        }
        ans = ans2.trim();
    }
    
    public void con(int a, int b)
    {
        nodes[a].con.add(b);
        nodes[a].connectedTo[b] = true;
    }
    
    private class node{
        
        int id;
        String name;
        ArrayList<Integer> con;
        boolean[] connectedTo;
        
        public node(int id, String n)
        {
            this.id = id;
            name = n;
            con = new ArrayList<Integer>();
            connectedTo = new boolean[500];
        }
    }
    
    private class state{
        
        int location;
        int cost;
        
        public state(int l, int c)
        {
            this.location = l;
            this.cost = c;
        }
        
    }
    
}