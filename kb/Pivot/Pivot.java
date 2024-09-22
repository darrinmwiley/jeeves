/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/pivot
TAGS: sweep 
EXPLANATION: Finding min-max values on respective sides of current point
END ANNOTATION
*/
import java.io.BufferedReader;
import java.io.File;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.Arrays;
import java.util.HashMap;
import java.util.Scanner;
import java.util.StringTokenizer;
import java.io.FileReader;
 
public class Pivot {
	
	StringTokenizer st;
	BufferedReader file;
	static final boolean RUN_TIMING = false;
	int[] array;
	boolean[] pivot;
	public static void main(String[] args) throws Exception
	{
        new Pivot().run();		//<--- where program written starts running
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
		int size = nextInt();
		int largest = Integer.MIN_VALUE;
		int smallest = Integer.MAX_VALUE;
		pivot = new boolean[size];
		array = new int[size];
		Arrays.fill(pivot, true);
		
		for(int i = 0; i < size; i++) {
			array[i] = nextInt();
		}
		
		for(int i = 0; i < size; i++) {
			if(array[i] < largest) {
				pivot[i] = false;
			}
			largest = Math.max(array[i], largest);
		}
		
		for(int i = size-1; i >= 0; i--) {
			if(array[i] > smallest) {
				pivot[i] = false;
			}
			
			smallest = Math.min(array[i], smallest);
		}
		
		int answer = 0;
		for(boolean b : pivot) {
			if(b == true) {
				answer++;
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
