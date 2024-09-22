/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/whatsinit
TAGS: brute force, memoization
EXPLANATION:
the state of a problem can be boiled down to (index, previous amount, current sum).
the size of the state space is then (1000)*(101)*(101) =~ 10,000,000
brute force every possible state, and keep track of the min and max feasible amount for each ingredient.
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
import java.util.HashMap;
import java.util.StringTokenizer;
 
public class whatsinit {
	
	//this is used for actual solution output. It is very fast but will not show up on the console until the run() method terminates (or until you call pout.flush()).
	PrintWriter pout;
	
	//this is used for timing your code
	long startTimeMillis;
	long benchmark;
	
	int[]min,max;
	String[] names;
	int N;
	
	int[] trueMin, trueMax;
	HashMap<String, Boolean> map;
	//set this to false to remove all debug and timing output for submission.
	boolean DEBUG_FLAG = true;
	
	//this is just the entry point of your program. 
	//it will instantiate an instance of your solution class, set it's relevent variables, and then call its run() method to do the solving.
	//this also prints all output in pout's buffer for you after run() is complete.
	public static void main(String[] args) throws Exception
	{
		long entryTime = System.currentTimeMillis();
		whatsinit t = new whatsinit();
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
		N = file.nextInt();
		min = new int[N];
		max = new int[N];
		trueMin = new int[N];
		Arrays.fill(trueMin, Integer.MAX_VALUE);
		trueMax = new int[N];
		names = new String[N];
		map = new HashMap<String,Boolean>();
		for(int i = 0;i<N;i++)
		{
			names[i] = file.next();
			String str = file.next();
			if(str.equals("?"))
			{
				min[i] = 0;
				max[i] = 100; 
			}else {
				int amt = Integer.parseInt(str);
				min[i] = max[i] = amt;
			}
		}
		possible(0, 100, 0);
		for(int i = 0;i<N;i++)
		{
			System.out.println(names[i]+" "+trueMin[i]+" "+trueMax[i]);
		}
	}
	
	public boolean possible(int index, int prevAmount, int sum)
	{
		String instance = index+" "+prevAmount+" "+sum;
		if(map.containsKey(instance))
			return map.get(instance);
		if(sum > 100)
			return false;
		if(index == N)
			return sum == 100;
		boolean flag = false;
		for(int i = min[index];i<=Math.min(max[index],prevAmount);i++)
		{
			boolean poss = possible(index+1, i, sum+i);
			if(poss)
			{
				trueMin[index] = Math.min(i, trueMin[index]);
				trueMax[index] = Math.max(i, trueMax[index]);
				flag = true;
			}
		}
		map.put(instance, flag);
		return flag;
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