/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/marblestree
TAGS: dfs, tree
EXPLANATION:
the only reason a marble should traverse an edge is if there is an imbalance between the two sides of the tree.
Another way of saying this is subtree size != number of marbles on a subtree.
hence the answer will be sum(abs(subtree size - subtree marbles)) over all vertices
END ANNOTATION
*/
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.time.LocalDateTime;
import java.time.LocalTime;
import java.time.format.DateTimeFormatter;
import java.util.StringTokenizer;
 
public class MarblesTree {
    
    StringTokenizer st;
    BufferedReader file;
    
    node[] nodes;
    
    public static void main(String[] args) throws Exception
    {
        new MarblesTree().run();
    }   
    
    public void run() throws Exception
    {
        //this is fast IO - faster than Scanner/System.out.println
        file = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pout = new PrintWriter(System.out);
        while(true)
        {
            int N = nextInt();
            nodes = new node[N];
            if(N == 0)
                break;
            for(int i = 0;i<N;i++)
            {
                nodes[i] = new node(i);
            }
            for(int i = 0;i<N;i++)
            {
                int node = nextInt() - 1;
                nodes[i].marbles = nextInt();
                int children = nextInt();
                nodes[i].children = new int[children];
                for(int j = 0;j<children;j++)
                {
                    int child = nextInt() - 1;
                    nodes[i].children[j] = child;
                    nodes[child].p = i;
                }
            }
            int ans = 0; 
            for(node n: nodes)
            {
                n.dfs();
                ans += Math.abs(n.subtreeMarbles - n.subtreeSize);
            }
            pout.println(ans);
        }
        pout.flush();
        pout.close();
    }
    
    private class node{
        int[] children;
        int p;
        int id;
        int marbles;
        int subtreeMarbles;
        int subtreeSize;
        boolean vis;
        public node(int id)
        {
            this.id = id;
        }
        
        public void dfs()
        {
            if(vis)
                return;
            vis = true;
            subtreeSize = 1;
            subtreeMarbles = marbles;
            for(int x:children)
            {
                nodes[x].dfs();
                subtreeSize += nodes[x].subtreeSize;
                subtreeMarbles += nodes[x].subtreeMarbles;
            }
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