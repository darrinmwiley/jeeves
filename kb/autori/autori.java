/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/autori
TAGS: trivial
EXPLANATION:
split by dashes, print first character of each string
END ANNOTATION
*/
import java.util.Random;
import java.util.Scanner;

public class autori
{
	
	public static void main (String[] args) throws java.lang.Exception
	{
		new autori().run();
	}
	
	Random rand = new Random(2020);
	int max = Integer.MAX_VALUE;
	
	public void run() throws Exception
	{
		Scanner file = new Scanner(System.in);
		String[] lines = file.nextLine().split("-");
		for(String s: lines)
			System.out.print(s.charAt(0));
	}
}