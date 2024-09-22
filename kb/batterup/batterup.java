/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/batterup
TAGS: easy, array
EXPLANATION:
sum of non negative values, divided by number of non negative values
END ANNOTATION
*/
import java.util.Random;
import java.util.Scanner;

public class batterup
{
	
	public static void main (String[] args) throws java.lang.Exception
	{
		new batterup().run();
	}
	
	public void run() throws Exception
	{
		Scanner file = new Scanner(System.in);
		int N = file.nextInt();
		int[] ints = new int[N];
		for(int i = 0;i<N;i++)
		{
			ints[i] = file.nextInt();
		}
		double sum = 0;
		double div = 0;
		for(int x: ints)
		{
			if(x != -1)
			{
				sum += x;
				div ++;
			}
		}
		System.out.println(sum/div);
	}
}