/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/exhaustiveexperiment
TAGS: geometry, greedy, sweep
EXPLANATION:
first, we stretch the space by a factor of 2 so that the area of effect for helium is a diamond
next, we rotate the space so that these diamonds become squares.

The transformation for this:

X = X-Y
Y = X+Y

In our transformed coordinate system:

A positive test (X1,Y1) can cover any test (X2,Y2) such that X2 >= X1 and Y2 <= Y1
(represented by an infinite square who's top left corner is (X1,Y1))

A negative test (X1,Y1) bars any test (X2,Y2) such that X2 <= X1 and Y2 >= Y1 from being a leak source.
(represented by an infinite square who's bottom right corner is (X1,Y1))

First, we will scan through the observation set and bar all non-feasible leak sources.
Scan in order of decreasing X coordinate, keeping track of the lowest Y you've seen so far belonging to a negative test location.
If you find a candidate leak-source that is higher than the lowest Y seen so far, mark it as non-feasible

Next, we will scan through the observation set and count the number of forced leak sources.
Scan in order of increasing X coordinate, keeping track of the highest Y you've seen so far belonging to a feasible test location.

If you find a non-covered positive test location:

1) if the highest feasible Y you've seen so far cannot cover it, there is no solution
2) otherwise, you must choose some candidate source to cover this observation, and there is no downside to taking the highest one seen so far, 
as it will cover at least as large a set as any other candidate will.

Once all observations have been processed, the number of forced moves should be the minimum.

runtime O(nlogn)

END ANNOTATION
*/
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.StringTokenizer;

public class ExhaustiveExperiment {
	
	public static void main(String[] args) throws NumberFormatException, IOException
	{
		new ExhaustiveExperiment().run();		
	}
	
	char POSITIVE = 'P';
	char NEGATIVE = 'N';
	char NONE = '-';
	
	public void run() throws NumberFormatException, IOException
	{
		BufferedReader file = new BufferedReader(new InputStreamReader(System.in));
		int N = Integer.parseInt(file.readLine());
		StringTokenizer st;
		element[] elements = new element[N];
		for(int i = 0;i<N;i++)
		{
			st = new StringTokenizer(file.readLine());
			int origX = Integer.parseInt(st.nextToken());
			int origY = Integer.parseInt(st.nextToken());
			int x = origX*2 - origY;
			int y = origX*2 + origY;
			char type = st.nextToken().charAt(0);
			elements[i] = new element(x,y,type);
		}
		Arrays.sort(elements);
		int lowestY = Integer.MAX_VALUE;
		for(int i = elements.length - 1;i>=0;i--)
		{
			if(elements[i].type == NEGATIVE)
				lowestY = Math.min(elements[i].y, lowestY);
			if(elements[i].y>=lowestY)
				elements[i].feasible = false;
		}
		int used = 0;
		int highestY = Integer.MIN_VALUE;
		int highestYUsed = Integer.MIN_VALUE;
		for(int i = 0;i<elements.length;i++)
		{
			if(elements[i].feasible)
			{
				highestY = Math.max(elements[i].y,highestY);
			}
			if(elements[i].type == POSITIVE && highestYUsed < elements[i].y)
			{
				if(highestY >= elements[i].y)
				{
					highestYUsed = highestY;
					used++;
				}else {
					System.out.println("impossible");
					return;
				}
			}
		}
		System.out.println(used);
	}
	
	private class element implements Comparable<element>{
		
		int x;
		int y;
		char type;
		boolean feasible;
		
		public element(int x, int y, char type)
		{
			this.x = x;
			this.y = y;
			this.type = type;
			feasible = true;
		}

		@Override
		public int compareTo(element o) {
			int comp = Integer.compare(x, o.x);
			if(comp == 0)
				return Integer.compare(o.y,y);
			return comp;
		}
		
	}
}
