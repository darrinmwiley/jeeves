/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/spiderman
TAGS: dp
EXPLANATION:
let dp[i][j] = the minimum height required to do exercises [0..i] and end at height j.
you can then fill out dp[i+1][j+e[i+1]] and dp[i+1][j-e[i+1]] accordingly.
you can keep an auxiliary array keeping track of the string representation of these choices, and the solution will lie at aux[i][0]
END ANNOTATION
*/
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.PriorityQueue;
import java.util.Queue;
import java.util.StringTokenizer;
 
public class spiderman {
    
    StringTokenizer st;
    BufferedReader file;
    
    node[] nodes;
    
    //D: pick a set of the K 
    
    public static void main(String[] args) throws Exception
    {
        new spiderman().run();
    }   
    
    public void run() throws Exception
    {
        file = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pout = new PrintWriter(System.out);
        StringTokenizer st; 
        int zz = nextInt();
        for(int z = 0;z<zz;z++)
        {
            int N = nextInt();
            int[] ints = new int[N];
            for(int i = 0;i<ints.length;i++)
                ints[i] = nextInt();
            int sum = 0;
            for(int x: ints)
                sum += x;
            int[][] dp = new int[N+1][sum+1];
            String[][] ans = new String[N+1][sum+1];
            ans[0][0] = "";
            for(int[] in: dp)
                Arrays.fill(in, Integer.MAX_VALUE/2);
            dp[0][0] = 0;
            for(int i = 0;i<N;i++)
            {
                for(int j = 0;j<sum;j++)
                {
                    if(ans[i][j] != null)
                    {
                        int downj = j - ints[i];
                        int upj = j + ints[i];
                        if(downj >= 0)
                        {
                            int old = dp[i+1][downj];
                            int rep = dp[i][j];
                            if(rep < old) {
                                dp[i+1][downj] = rep;
                                ans[i+1][downj] = ans[i][j]+"D";
                            }
                        }
                        int old = dp[i+1][upj];
                        int rep = Math.max(dp[i][j], upj);
                        if(rep < old)
                        {
                            dp[i+1][upj] = rep;
                            ans[i+1][upj] = ans[i][j]+"U";
                        }
                    }
                }
            }
            String ret = ans[N][0];
            if(ret == null)
                System.out.println("IMPOSSIBLE");
            else
                System.out.println(ret);
        }
    }
    
/*
4 3 3 3 1
1 2 1
2 3 1
3 4 5
2 3 4
 */
    
    private class state implements Comparable<state>
    {
        int loc;
        long cost;
        public state(int node, long cost)
        {
            this.loc = node;
            this.cost = cost;
        }
        @Override
        public int compareTo(state arg0) {
            return Long.compare(cost, arg0.cost);
        }
    }
    
    public void connect(int a, int b, long c)
    {
        nodes[a].con.add(b);
        nodes[b].con.add(a);
        nodes[a].cost.add(c);
        nodes[b].cost.add(c);
    }
    
    private class node implements Comparable<node>{
        
        ArrayList<Long> cost;
        ArrayList<Integer> con;
        int id;
        long fp;
        
        public node(int d)
        {
            this.id = d;
            this.con = new ArrayList<Integer>();
            this.cost = new ArrayList<Long>();
            fp = Long.MAX_VALUE;
        }

        @Override
        public int compareTo(node o) {
            return Long.compare(fp, o.fp);
        }
        
    }
    
    public void newst()
    {
        try {
            st = new StringTokenizer(file.readLine());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
    
    public String readLine() throws IOException
    {
        return file.readLine();
    }
    
    public String next()
    {
        if(st == null || !st.hasMoreTokens())
            newst();
        return st.nextToken();
    }
    
    public int nextInt()
    {
        if(st == null || !st.hasMoreTokens())
            newst();
        return Integer.parseInt(st.nextToken());
    }
    
    public long nextLong()
    {
        if(st == null || !st.hasMoreTokens())
            newst();
        return Long.parseLong(st.nextToken());
    }
    
}