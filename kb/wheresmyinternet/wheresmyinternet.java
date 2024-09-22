/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/wheresmyinternet
TAGS: dfs, graph
EXPLANATION:
create a graph of connected homes and then dfs out from house 1. Anything reachable is connected.
END ANNOTATION
*/
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.StringTokenizer;

public class wheresmyinternet {
    
    //if you do this you don't have to throw static on everything
    public static void main(String[] args) throws Exception {
        new wheresmyinternet().run();
    }
    
    //move stuff methods are gonna need up here
    vertex[] nodes;
    ArrayList<Integer> found;
    int[] shadow;
    
    public void run() throws Exception
    {
        BufferedReader input = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(input.readLine());
        PrintWriter pout = new PrintWriter(System.out);
        int n = Integer.parseInt(st.nextToken());
        int m = Integer.parseInt(st.nextToken());
        nodes = new vertex[n];
        for(int i = 0;i<n;i++)
        {
            nodes[i] = new vertex(i);
        }
        for(int i=0;i<m;i++) {
            st = new StringTokenizer(input.readLine());
            int x = Integer.parseInt(st.nextToken());
            int y = Integer.parseInt(st.nextToken());
            con(x-1, y-1);
        }
        shadow = new int[n];
        
        found = new ArrayList<Integer>();
        recur(0);
        if(found.size()==n) pout.println("Connected");
        else {
            for(int i=0;i<shadow.length;i++) {
                if(shadow[i]==0) pout.println(i+1); 
            }
        }
        pout.flush();
    }
    
    public void recur(int i) {
        shadow[i]=1;
        found.add(i);
        for(int j:nodes[i].con) {
            if(shadow[j]==0) {
                recur(j);
            }
        }
    }
    
    public void con(int a, int b)
    {
        nodes[a].con.add(b);
        nodes[b].con.add(a);
    }
    
    private class vertex{
        
        ArrayList<Integer> con;
        int id;//tracks index in array
        public vertex(int id)
        {
            con = new ArrayList<Integer>();
            this.id = id;
        }
        
    }
}