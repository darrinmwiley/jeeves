/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/AirConditioned
TAGS: sort, sweep
EXPLANATION: Sort end-points and cover intervals at latest point in time.
END ANNOTATION
*/

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.PriorityQueue;
import java.util.Queue;
import java.util.StringTokenizer;

public class AirConditioned {
	

	private class points implements Comparable<points>{
		int interval_id;
		int x;
		boolean beginning = false;
		public points(int id, int x, boolean beg) {
			interval_id = id;
			this.x = x;
			beginning = beg;
		}
		@Override
		public int compareTo(points o) {
			//System.out.println(x + " " + beginning + " " + interval_id);
			//System.out.println(o.x + " " + o.beginning + " " + o.interval_id);
			// TODO Auto-generated method stub
			int comp = Integer.compare(x, o.x);
			//System.out.println(comp);
			//System.out.println();
			if(comp == 0) {
				return Boolean.compare(o.beginning, beginning);
			}
			return comp;
		}
	}
	
	private class interval{
		int id;
	}
	
	
	StringTokenizer st;
	BufferedReader file;
	static final boolean RUN_TIMING = false;
	boolean[] active;
	ArrayList<Integer> list = new ArrayList<Integer>();
	
	public static void main(String[] args) throws Exception
	{
        new AirConditioned().run();		//<--- where program written starts running
	}	
	
	public void run() throws Exception
	{
		long time = 0;
       	time -= System.nanoTime();
		
		//this is fast IO - faster than Scanner/System.out.println
		//If needed to input file it would be: new BufferedReader(new FileReader(new File(filename)));
		//file = new BufferedReader(new FileReader(new File("text.txt")));
       	file = new BufferedReader(new InputStreamReader(System.in));
		PrintWriter pout = new PrintWriter(System.out);
		
		//solution code goes here
		int answer = 0;
		
		Queue<points> events = new PriorityQueue<points>();
		
		int cases = nextInt();
		active = new boolean[cases];
		
		for (int i = 0; i < cases; i++) {
			int first = nextInt();
			int second = nextInt();
			points f_point = new points(i,first,true);
			points l_point = new points(i,second,false);
			events.add(f_point);
			events.add(l_point);
		}
		
		while(!events.isEmpty()) {
			points p = events.poll();
			//System.out.println(p.x + " " + p.beginning + " " + p.interval_id);
			if(p.beginning) {
				active[p.interval_id] = true;
				list.add(p.interval_id);
			}else {
				if(active[p.interval_id] == true) {
					answer++;
					for(int i: list) {
						active[i] = false;
					}
				}
				
			}
		}
		
		pout.println(answer);
		
		time += System.nanoTime();
        if (RUN_TIMING) {
            System.out.printf("%.3f ms%n", time / 1000000.0);
        }
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

  	public void shuffle(int[] arr) {
        	int n = arr.length;
        	for (int i = 0; i < n; i++) {
           		int j = (int)(Math.random() * (n-i));
            		int temp = arr[i];
            		arr[i] = arr[j+i];
            		arr[j+i] = temp;
        	}
  	}
	public void shuffle(long[] arr) {
        	int n = arr.length;
        	for (int i = 0; i < n; i++) {
           		int j = (int)(Math.random() * (n-i));
            		long temp = arr[i];
            		arr[i] = arr[j+i];
            		arr[j+i] = temp;
        	}
	}
	public void shuffle(Object[] arr) {
        	int n = arr.length;
        	for (int i = 0; i < n; i++) {
           		int j = (int)(Math.random() * (n-i));
            		Object temp = arr[i];
            		arr[i] = arr[j+i];
            		arr[j+i] = temp;
        }
    }
	
}
