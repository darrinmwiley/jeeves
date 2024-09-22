/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/connectthedots
TAGS: implementation
EXPLANATION:
scan through the input to find the location of every dot
replace '.' with either '|' or '-'
replace '| and '-' with '+' if you travel over in both directions
be sure not to replace dot characters
END ANNOTATION
*/
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.StringTokenizer;
 
public class connectthedots {
    
    StringTokenizer st;
    BufferedReader file;
    
    public static void main(String[] args) throws Exception
    {
        new connectthedots().run();
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
        
        String line;
        
        ArrayList<String> lines = new ArrayList<String>();
        boolean print = false;
        while((line = file.readLine()) != null)
        {
            if(print) {
                pout.println();
                print = false;
            }
            if(line.isEmpty())
            {
                solve(lines, pout);
                lines.clear();
                print = true;
            }else {
                lines.add(line);
            }
            pout.flush();
        }
        solve(lines, pout);
        pout.flush();
        pout.close();
    }
    
    public void solve(ArrayList<String> lines, PrintWriter pout)
    {
        HashMap<Integer, Integer> rloc = new HashMap<Integer,Integer>();
        HashMap<Integer, Integer> cloc = new HashMap<Integer,Integer>();
        char[][] chars = new char[lines.size()][];
        int x = 0;
        for(String s: lines)
            chars[x] = lines.get(x++).toCharArray();
        int maxIndex = 0;
        for(int i = 0;i<chars.length;i++)
        {
            for(int j = 0;j<chars[i].length;j++)
            {
                if(chars[i][j] != '.')
                {
                    int index = map.get(chars[i][j]);
                    maxIndex = Math.max(maxIndex, index);
                    rloc.put(index, i);
                    cloc.put(index, j);
                }
            }
        }
        for(int i = 0;i<maxIndex;i++)
        {
            int currR = rloc.get(i);
            int currC = cloc.get(i);
            int nextR = rloc.get(i+1);
            int nextC = cloc.get(i+1);
            int dr = (int)Math.signum(nextR - currR);
            int dc = (int)Math.signum(nextC - currC);
            int dist = Math.max(Math.abs(nextC - currC), Math.abs(nextR - currR));
            for(int j = 0;j<=dist;j++)
            {
                int r = currR + dr*j;
                int c = currC + dc*j;
                if(dr != 0) {//vertical
                    if(chars[r][c] == '.')
                    {
                        chars[r][c] = '|';
                    }else if(chars[r][c] == '-')
                    {
                        chars[r][c] = '+';
                    }
                }else {
                    if(chars[r][c] == '.')
                    {
                        chars[r][c] = '-';
                    }else if(chars[r][c] == '|')
                    {
                        chars[r][c] = '+';
                    }
                }
                
            }
        }
        for(char[] ch: chars)
        {
            pout.println(new String(ch));
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