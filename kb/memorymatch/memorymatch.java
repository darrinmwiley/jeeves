/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/memorymatch
TAGS: casework
EXPLANATION:
the problem falls into 3 possible cases.

1) you've seen at least 1 of every card type, in this case you can flip them all
2) you've seen both of all but one card type, in this case you can flip them all
3) in any other case, you can only flip cards that you've seen both locations for
END ANNOTATION
*/
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.HashMap;
import java.util.HashSet;
import java.util.StringTokenizer;
 
public class memorymatch {
    
    StringTokenizer st;
    BufferedReader file;
    
    public static void main(String[] args) throws Exception
    {
        new memorymatch().run();
    }
    
    char[] order = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ".toCharArray();
    HashMap<Character, Integer> map = new HashMap<>();
    public void run() throws Exception
    {
        for(int i = 0;i<order.length;i++)
        {
            map.put(order[i], i);
        }
        //this is fast IO - faster than Scanner/System.out.println
        file = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pout = new PrintWriter(System.out);
        
        int N = nextInt();
        int K = nextInt();
        
        String[] strs = new String[N];
        HashSet<String> done = new HashSet<String>();
        HashMap<String,Integer> occ = new HashMap<String,Integer>();
        HashSet<String> seen = new HashSet<String>();
        
        for(int i = 0;i<K;i++)
        {
            int a = nextInt();
            int b = nextInt();
            String aa = next();
            String bb = next();
            if(aa.equals(bb))
            {
                done.add(aa);
            }
            if(strs[a-1] == null) {
                if(!occ.containsKey(aa))
                    occ.put(aa,0);
                    strs[a-1] = aa;
                    occ.put(aa, occ.get(aa)+1);
            }
            if(strs[b-1] == null) {
                strs[b-1] = bb;
                if(!occ.containsKey(bb))
                    occ.put(bb,0);
                occ.put(bb, occ.get(bb)+1);
            }
            seen.add(aa);
            seen.add(bb);
        }
        
        //System.out.println(seen);
        //System.out.println(occ);
        //System.out.println(done);
        
        if(seen.size() == N/2)
        {
            System.out.println(N/2 - done.size());
            return;
        }
        
        int twos = 0;
        
        for(String s: occ.keySet())
        {
            if(occ.get(s) == 2)
            {
                twos++;
            }
        }
        
        //System.out.println("twos "+twos);
        //System.out.println(N/2 - 1);
        
        if(twos == N/2 - 1)
        {
            System.out.println(N/2 - done.size());
            return;
        }
        
        int ans = 0;
        for(String s: occ.keySet())
        {
            if(occ.get(s) == 2 && !done.contains(s))
                ans++;
        }
        
        System.out.println(ans);
        
        pout.flush();
        pout.close();
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