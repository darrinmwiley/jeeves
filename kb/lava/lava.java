/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/lava
TAGS: bfs
EXPLANATION:

consider the graph of all valid locations as vertices, and moves as edges.

there are at most 1000 white tiles, meaning the number of edges is less than 10^6.

We can BFS out for both the daughter and father's graphs and answer according to their distance to the end tile. 
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
import java.util.LinkedList;
import java.util.Queue;
import java.util.StringTokenizer;
 
public class lava {
    
    //this is used for actual solution output. It is very fast but will not show up on the console until the run() method terminates (or until you call pout.flush()).
    PrintWriter pout;
    
    //this is used for timing your code
    long startTimeMillis;
    long benchmark;
    
    //set this to false to remove all debug and timing output for submission.
    boolean DEBUG_FLAG = true;
    
    node[] nodes;
    
    int BIG = Integer.MAX_VALUE/4;
    
    //this is just the entry point of your program. 
    //it will instantiate an instance of your solution class, set it's relevent variables, and then call its run() method to do the solving.
    //this also prints all output in pout's buffer for you after run() is complete.
    public static void main(String[] args) throws Exception
    {
        long entryTime = System.currentTimeMillis();
        lava t = new lava();
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
        int childStep = file.nextInt();
        int fatherStep = file.nextInt();
        int C2 = childStep * childStep;
        int F2 = fatherStep * fatherStep;
        int R = file.nextInt();
        int C = file.nextInt();
        char[][] chars = new char[R][C];
        for(int i = 0;i<R;i++)
        {
            chars[i] = file.nextLine().toCharArray();
        }
        int nds = 0;
        for(int i = 0;i<R;i++)
        {
            for(int j = 0;j<C;j++)
            {
                if(chars[i][j] != 'B')
                {
                    nds++;
                }
            }
        }
        nodes = new node[nds];
        int index = 0;
        int startid = 0;
        int endid = 0;
        for(int i = 0;i<R;i++)
        {
            for(int j = 0;j<C;j++)
            {
                if(chars[i][j] == 'W')
                {
                    nodes[index] = new node(i,j,index++);
                }
                if(chars[i][j] == 'S')
                {
                    startid = index;
                    nodes[index] = new node(i,j,index++);
                }
                if(chars[i][j] == 'G')
                {
                    endid = index;
                    nodes[index] = new node(i,j,index++);
                }
            }
        }
        for(int i = 0;i<nodes.length;i++)
        {
            for(int j = i+1;j<nodes.length;j++)
            {
                node n1 = nodes[i];
                node n2 = nodes[j];
                int d2 = (n1.r - n2.r)*(n1.r - n2.r) + (n1.c - n2.c)*(n1.c - n2.c);
                if((n1.r == n2.r || n1.c == n2.c) && d2 <= F2)
                {
                    fatherCon(i,j);
                }
                if(d2 <= C2)
                {
                    daughterCon(i,j);
                }
            }
        }
        int daughter = bfs(startid, endid, true);
        int father = bfs(startid, endid, false);
        if(father == daughter)
        {
            if(father == BIG)
            {
                System.out.println("NO WAY");
            }else {
                System.out.println("SUCCESS");
            }
        }else {
            if(father < daughter)
            {
                System.out.println("NO CHANCE");
            }else {
                System.out.println("GO FOR IT");
            }
        }
    }
    
    public int bfs(int startid, int endid, boolean daughter)
    {
        Queue<Integer> que = new LinkedList<Integer>();
        que.add(startid);
        que.add(0);
        boolean[] vis = new boolean[nodes.length];
        vis[startid] = true;
        while(!que.isEmpty())
        {
            int location = que.poll();
            int cost = que.poll();
            if(location == endid)
            {
                return cost;
            }
            node curr = nodes[location];
            ArrayList<Integer> con = daughter? curr.daughterCon: curr.fatherCon;
            for(int x: con)
            {
                if(!vis[x])
                {
                    vis[x] = true;
                    que.add(x);
                    que.add(cost+1);
                }
            }
        }
        return BIG;
    }
    
    public void fatherCon(int a, int b)
    {
        nodes[a].fatherCon.add(b);
        nodes[b].fatherCon.add(a);
    }
    
    public void daughterCon(int a, int b)
    {
        nodes[a].daughterCon.add(b);
        nodes[b].daughterCon.add(a);
    }
    
    private class node{
        
        int r, c, id;
        ArrayList<Integer> fatherCon;
        ArrayList<Integer> daughterCon;
        
        public node(int r, int c, int id)
        {
            fatherCon = new ArrayList<Integer>();
            daughterCon = new ArrayList<Integer>();
            this.r = r;
            this.c = c;
            this.id = id;
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