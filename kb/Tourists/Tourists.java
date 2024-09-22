/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/tourists
TAGS: graph, tree, sparse table, LCA, harmonic
EXPLANATION:
notice since the graph is connected and there are n-1 edges, it must be a tree.
also notice that due to sum of a harmonic series, the number of (N, N*K) pairs in the graph is O(NlogN)
We can sum the distance between each of these NlogN pairs as you know the path between two nodes in a tree goes through their lowest common ancestor
this LCA can be calculated in log(N) time with NlogN precomputation with binary lifting
https://www.geeksforgeeks.org/lca-in-a-tree-using-binary-lifting-technique/
overall runtime Nlog^2(N)
END ANNOTATION
*/
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Stack;
import java.util.StringTokenizer;


public class Tourists {
    
    public static void main(String[] args) throws Exception
    {
        new Tourists().run();
    }

    node[] nodes;
    
    public void run() throws NumberFormatException, IOException
    {
        BufferedReader file = new BufferedReader(new InputStreamReader(System.in));
        int N = Integer.parseInt(file.readLine());
        StringTokenizer st;
        nodes = new node[N];
        for(int i = 0;i<N;i++)
        {
            nodes[i] = new node(i);
        }
        for(int i = 0;i<N-1;i++)
        {
            st = new StringTokenizer(file.readLine());
            int a = Integer.parseInt(st.nextToken()) - 1 ;
            int b = Integer.parseInt(st.nextToken()) - 1;
            nodes[a].con.add(b);
            nodes[b].con.add(a);
        }
        nodes[0].depth = 0;
        nodes[0].parent = -1;
        dfs(0, -1);
        for(node n: nodes)
            n.parents[0] = n.parent;
        for(int i = 1;i<18;i++)
        {
            for(int j = 0;j<nodes.length;j++)
                nodes[j].addParent(i);
        }
        
        long sum = 0;
        for(int i = 1;i<=nodes.length;i++)
        {
            for(int j = i*2;j<=nodes.length;j += i)
            {
                sum += between(i-1, j-1);
            }
        }
        System.out.println(sum);
    }
    
    public void dfs(int v, int p)
    {
        Stack<Integer> call = new Stack<Integer>();
        call.add(p);
        call.add(v);
        while(!call.isEmpty())
        {
            v = call.pop();
            p = call.pop();
            if(p != -1)
            {
                nodes[v].parent = p;
                nodes[v].depth = nodes[p].depth + 1;
            }
            for(int x: nodes[v].con)
                if(x != p)
                {
                    call.add(v);
                    call.add(x);
                }
        }
    }
    
    public int between(int a, int b)
    {
        int lcaDepth = lca(a,b);
        return nodes[b].depth - lcaDepth + nodes[a].depth - lcaDepth + 1;
    }
    
    public int lca2(int a, int b)
    {
        int adep = nodes[a].depth;
        int bdep = nodes[b].depth;
        int minDep = Math.min(adep, bdep);
        int L = 0;
        int R = minDep + 1;
        int M = (L+R)/2;//depth
        while(R - L > 1)
        {
            M = ((L+R)/2);
            int aid = nodes[a].getParent(adep - M);
            int bid = nodes[b].getParent(bdep - M);
            if(aid == bid)
            {
                L = M;
            }else {
                R = M;
            }
        }
        return L;
    }
    
    public int lca(int a, int b)
    {
        int adep = nodes[a].depth;
        int bdep = nodes[b].depth;
        int minDep = Math.min(adep, bdep);
        for(int i = 17;i>=0;i--)
        {
            if(nodes[a].depth - minDep >= (1<<i))
                a = nodes[a].parents[i];
                
            if(nodes[b].depth - minDep >= (1<<i))
                b = nodes[b].parents[i];
        }
        if(a == b)
            return nodes[a].depth;
        for(int i = 17;i>=0;i--)
        {
            int pa = nodes[a].parents[i];
            int pb = nodes[b].parents[i];
            if(pa != pb)
            {
                a = pa;
                b = pb;
            }
        }
        return nodes[a].depth - 1;
    }
    
    private class node{
        
        int depth;
        int parent;
        int[] parents;
        ArrayList<Integer> con;
        int id;
        
        public node(int id)
        {
            this.id = id;
            con = new ArrayList<Integer>();
            parents = new int[18];
        }
        
        public int getParent(int index)
        {
            int ans = id;
            int x = 0;
            while(index != 0)
            {
                if((index & 1) == 1)
                    ans = nodes[ans].parents[x];
                x++;
            }
            return ans;
        }
        
        //sketch
        public void addParent(int x)
        {
            /*if(index == -1)
                return id;
            if(this.depth < (1 << index))
                return -1;
            if(parents.size() <= index) {
                int ret = nodes[parents.get(index - 1)].get2Parent(index - 1);
                parents.add(ret);
            }
            return parents.get(index);*/
            if(parents[x-1] == -1)
                parents[x] = -1;
            else {
                int half = parents[x-1];
                parents[x] = (nodes[half].parents[x-1]);
            }
        }
        
    }
    
}
