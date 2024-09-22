/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/fencing
TAGS: casework
EXPLANATION:
fist, generate the convex hull of the points, and use distance formula to determine perimeter.

next, use single use coins dp to determine the smallest cost of obtaining enough wood to build the fence.
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
import java.util.Arrays;
import java.util.StringTokenizer;
 
public class fencing {
    
    //this is used for actual solution output. It is very fast but will not show up on the console until the run() method terminates (or until you call pout.flush()).
    PrintWriter pout;
    
    //this is used for timing your code
    long startTimeMillis;
    long benchmark;
    
    //set this to false to remove all debug and timing output for submission.
    boolean DEBUG_FLAG = true;
    
    //this is just the entry point of your program. 
    //it will instantiate an instance of your solution class, set it's relevent variables, and then call its run() method to do the solving.
    //this also prints all output in pout's buffer for you after run() is complete.
    public static void main(String[] args) throws Exception
    {
        long entryTime = System.currentTimeMillis();
        fencing t = new fencing();
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
        int N = file.nextInt();
        int M = file.nextInt();
        int[] value = new int[N];
        int[] cost = new int[N];
        int vsum = 0;
        for(int i = 0;i<N;i++)
        {
            value[i] = file.nextInt();
            vsum += value[i];
            cost[i] = file.nextInt();
        }
        pt[] pts = new pt[M];
        for(int i = 0;i<M;i++)
        {
            pts[i] = new pt(file.nextInt(),file.nextInt());
        }
        pt[] ch = hull(pts);
        double dist = 0;
        for(int i = 0;i<ch.length;i++)
        {
            dist += dist(ch[i],ch[(i+1)%ch.length]);
        }
        int ceil = (int)(Math.ceil(dist));
        int[] dp = new int[vsum+1];
        Arrays.fill(dp, Integer.MAX_VALUE/4);
        dp[0] = 0;
        for(int i = 0;i<N;i++)
        {
            for(int j = dp.length - 1;j>=value[i];j--)
            {
                dp[j] = Math.min(dp[j],dp[j-value[i]] + cost[i]);
            }
        }
        int min = Integer.MAX_VALUE;
        for(int i = ceil;i<dp.length;i++)
        {
            min = Math.min(min, dp[i]);
        }
        System.out.println(min);
    }
    
    public long cross(pt O, pt A, pt B) {
        return (A.x - O.x) * (long) (B.y - O.y) - (A.y - O.y) * (long) (B.x - O.x);
    }
    
    public pt[] hull(pt[] pts) {
        if (pts.length > 1) {
            int n = pts.length, k = 0;
            pt[] hull = new pt[2 * n];

            Arrays.sort(pts);

            for (int i = 0; i < n; ++i) {
                while (k >= 2 && cross(hull[k - 2], hull[k - 1], pts[i]) <= 0)
                    k--;
                hull[k++] = pts[i];
            }

            for (int i = n - 2, t = k + 1; i >= 0; i--) {
                while (k >= t && cross(hull[k - 2], hull[k - 1], pts[i]) <= 0)
                    k--;
                hull[k++] = pts[i];
            }
            if (k > 1) {
            	hull = Arrays.copyOfRange(hull, 0, k - 1);
            }
            return hull;
        } else if (pts.length <= 1) {
            return pts;
        } else {
            return null;
        }
    }
    
    public double dist(pt a, pt b)
    {
        return Math.sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
    }
    
    private class pt implements Comparable<pt> {
        int x, y;
        
        public pt(int x, int y)
        {
            this.x = x;
            this.y = y;
        }

        public int compareTo(pt p) {
            if (this.x == p.x) {
                return this.y - p.y;
            } else {
                return this.x - p.x;
            }
        }

        public String toString() {
            return "(" + x + "," + y + ")";
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
    