/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/parking2
TAGS: easy, math, observation
EXPLANATION:
it doesn't matter where you start, you'll travel the entire range distance twice.
END ANNOTATION
*/
import java.util.Scanner;

public class parking2 {
	
	public static void main(String[] args)
	{
		new parking2().run();		
	}
	
	public void run()
	{
		Scanner file = new Scanner(System.in);
		int zz = file.nextInt();
		for(int z = 0;z<zz;z++)
		{
			int N = file.nextInt();
			int min = Integer.MAX_VALUE;
			int max = Integer.MIN_VALUE;
			for(int i = 0;i<N;i++)
			{
				int x = file.nextInt();
				min = Math.min(x, min);
				max = Math.max(x,max);
			}
			System.out.println((max-min)*2);
		}
	}
	
}
