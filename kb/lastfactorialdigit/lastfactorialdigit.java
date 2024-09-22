/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/lastfactorialdigit
TAGS: trivial
EXPLANATION:
if input is more than 5, print zero. Otherwise calculate
END ANNOTATION
*/
import java.util.Random;
import java.util.Scanner;

class lastfactorialdigit
{
	
	public static void main (String[] args) throws java.lang.Exception
	{
		new lastfactorialdigit().run();
	}
	
	Random rand = new Random(2020);
	int max = Integer.MAX_VALUE;
	
	public void run() throws Exception
	{
		Scanner file = new Scanner(System.in);
		int N = file.nextInt();
		int[] ans = new int[] {1,1,2,6,4};
		for(int i = 0;i<N;i++)
		{
			int x = file.nextInt();
			if(x >= 5)
				System.out.println(0);
			else 
				System.out.println(ans[x]);
		}
	}
}