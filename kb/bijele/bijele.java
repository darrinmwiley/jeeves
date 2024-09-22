/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/bijele
TAGS: trivial
EXPLANATION:
for each index, print the difference between actual and desired.
END ANNOTATION
*/
import java.util.Random;
import java.util.Scanner;

public class bijele
{
	
	public static void main (String[] args) throws java.lang.Exception
	{
		new bijele().run();
	}
	
	Random rand = new Random(2020);
	int max = Integer.MAX_VALUE;
	
	public void run() throws Exception
	{
		Scanner file = new Scanner(System.in);
		int[] good = new int[] {1,1,2,2,2,8};
		for(int i = 0;i<6;i++)
		{
			System.out.print(good[i] - file.nextInt() + " ");
		}
	}
}