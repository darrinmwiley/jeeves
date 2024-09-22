/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/poetrytower
TAGS: brute force, hashing, flow, matching
EXPLANATION:
there are at most 8! different poems to verify, this is around 40,000

however, two poems are equivalent in validity if they are the same words in different orders

The number of sets of words is much smaller, 2^8, we can verify each combination and use it to verify poems.

To verify each combination, we'll use a bipartite matching via max flow. Each block can match to every letter corresponding to a letter on the block.
A block can match with any letter if it contains a '*'

If every character of a candidate string can be matched to a block, the combination is valid.

Test all and count.
END ANNOTATION
*/
import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.io.StringReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.Queue;
import java.util.StringTokenizer;
 
public class poetrytower {
    
    //this is used for actual solution output. It is very fast but will not show up on the console until the run() method terminates (or until you call pout.flush()).
    PrintWriter pout;
    
    //this is used for timing your code
    long startTimeMillis;
    long benchmark;
    
    //set this to false to remove all debug and timing output for submission.
    boolean DEBUG_FLAG = true;
    
    //node[] nodes;
    ArrayList<String> perm;
    ArrayList<String> hash;
    HashMap<String, Boolean> possible = new HashMap<String,Boolean>();
    
    int BIG = Integer.MAX_VALUE/4;
    
    //this is just the entry point of your program. 
    //it will instantiate an instance of your solution class, set it's relevent variables, and then call its run() method to do the solving.
    //this also prints all output in pout's buffer for you after run() is complete.
    public static void main(String[] args) throws Exception
    {
        long entryTime = System.currentTimeMillis();
        poetrytower t = new poetrytower();
        t.benchmark = t.startTimeMillis = entryTime;
        t.pout = new PrintWriter(System.out);
        t.run();
        t.pout.flush();
        t.pout.close();
    }   
    
    //solution code goes here
    public void run() throws Exception
    {
        Scanner file = new Scanner(System.in);
        perm = new ArrayList<String>();
        hash = new ArrayList<String>();
        int N = file.nextInt();
        int M = file.nextInt();
        String[] words = new String[M];
        char[][] dice = new char[N][6];
        for(int i = 0;i<words.length;i++)
        {
            words[i] = file.next();
        }
        for(int i = 0;i<N;i++)
        {
            dice[i] = file.next().toCharArray();
        }
        permute(words, new boolean[words.length], new char[words.length], "");
        int ans = 0;
        for(int i = 0;i<perm.size();i++)
        {
            String s = perm.get(i);
            String h = hash.get(i);
            if(test(dice, s.toCharArray(), h))
            {
                ans++;
            }
        }
        System.out.println(ans);
    }
    
    node[] nodes;
    int[][] res;
    
    public boolean test(char[][] dice, char[] goal, String hash)
    {
        if(this.possible.containsKey(hash))
        {
            return this.possible.get(hash);
        }
        nodes = new node[dice.length + goal.length + 2];
        res = new int[nodes.length][nodes.length];
        for(int i = 0;i<nodes.length;i++)
        {
            nodes[i] = new node(i);
        }
        for(int i = 0;i<dice.length;i++)
        {
            con(nodes.length - 2, i, 1);
            for(int j = 0;j<goal.length;j++)
            {
                for(int k = 0;k<dice[i].length;k++)
                {
                    if(goal[j] == dice[i][k] || dice[i][k] == '*')
                    {
                        con(i, dice.length + j, 1);
                    }
                }
            }
        }
        for(int i = 0;i<goal.length;i++)
        {
            con(dice.length + i, nodes.length - 1, 1);
        }
        int flow = 0;
        while(aug(nodes.length - 2, nodes.length - 1))
        {
            flow++;
        }
        boolean ret = flow == goal.length;
        possible.put(hash, ret);
        return ret;
    }
    
    public boolean aug(int start, int end)
    {
        Queue<Integer> que = new LinkedList<Integer>();
        que.add(start);
        int[] p = new int[nodes.length];
        boolean[] vis = new boolean[nodes.length];
        vis[start] = true;
        Arrays.fill(p, -1);
        while(!que.isEmpty())
        {
            int x = que.poll();
            for(int y: nodes[x].con)
            {
                if(res[x][y] > 0 && !vis[y])
                {
                    p[y] = x;
                    vis[y] = true;
                    que.add(y);
                }
            }
        }
        if(vis[end])
        {
            traceback(p, end);
            return true;
        }
        return false;
    }
    
    public void traceback(int[] p, int curr)
    {
        while(p[curr] != -1)
        {
            res[p[curr]][curr]--;
            res[curr][p[curr]]++;
            curr = p[curr];
        }
    }
    
    public void con(int a, int b, int c)
    {
        nodes[a].con.add(b);
        nodes[b].con.add(a);
        res[a][b] = c;
    }
    
    private class node
    {
        ArrayList<Integer> con;
        int id;
        
        public node(int id)
        {
            this.id = id;
            this.con = new ArrayList<Integer>();
        }
        
    }
    
    public void permute(String[] strs, boolean[] used, char[] hash, String curr)
    {
        if(!curr.isEmpty()) {
            perm.add(curr);
            this.hash.add(new String(hash));
        }
        for(int i = 0;i<strs.length;i++)
        {
            if(!used[i])
            {
                used[i] = true;
                hash[i] = '1';
                permute(strs, used,hash,curr+strs[i]);
                hash[i] = (char)(0);
                used[i] = false;
            }
        }
    }
    
    //prints out o if DEBUG_FLAG is true, does nothing otherwise
    //If you use pout for all real output and print() for all debugging output, you won't have to run through your code deleting prints after you get your solution working. 
    //Instead you can just set DEBUG_FLAG to false;
    public void print(Object o)
    {
        if(DEBUG_FLAG)
            System.out.println(o);
    }
    
    //call time to print a debug of how long a certain segment of your code has taken in milliseconds.
    //does nothing if DEBUG_FLAG is false
    public void time(String s)
    {
        if(DEBUG_FLAG)
        {
            long time = System.currentTimeMillis();
            System.out.println(s+": "+(time - startTimeMillis)+" ("+(time - benchmark)+" millis from last benchmark)");
            benchmark = time;
        }
    }
    
    //A fast bare-bones implementation of java.util.Scanner for fast input
    private class Scanner 
    { 
        BufferedReader br; 
        StringTokenizer st; 
  
        public Scanner() 
        { 
            this(System.in);
        } 
        
        public Scanner(File f) throws FileNotFoundException
        {
            br = new BufferedReader(new FileReader(f));
        }
        
        public Scanner(InputStream is)
        {
            br = new BufferedReader(new
                    InputStreamReader(is)); 
        }
        
        public Scanner(String content)
        {
            br = new BufferedReader(new StringReader(content));
        }
  
        String next() 
        { 
            while (st == null || !st.hasMoreElements()) 
            { 
                try
                { 
                    st = new StringTokenizer(br.readLine()); 
                } 
                catch (IOException  e) 
                { 
                    e.printStackTrace(); 
                } 
            } 
            return st.nextToken(); 
        } 
  
        int nextInt() 
        { 
            return Integer.parseInt(next()); 
        } 
  
        long nextLong() 
        { 
            return Long.parseLong(next()); 
        } 
  
        double nextDouble() 
        { 
            return Double.parseDouble(next()); 
        } 
  
        String nextLine() 
        { 
            try {
                return st.nextToken("");
            }catch(Exception ex) {
                String str = ""; 
                try
                { 
                    str = br.readLine(); 
                } 
                catch (IOException e) 
                { 
                    e.printStackTrace(); 
                } 
                return str; 
            }
        } 
    }
    
}