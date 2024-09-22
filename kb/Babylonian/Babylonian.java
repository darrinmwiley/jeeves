/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/babylonian
TAGS: base conversion, math
EXPLANATION:
convert base 60 to base 10
END ANNOTATION
*/

import java.io.IOException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Scanner;

public class Babylonian {
	
	public static void main(String[] args) throws NumberFormatException, IOException, InterruptedException
	{
		new Babylonian().run();		
	}
	
	public void run() throws NumberFormatException, IOException, InterruptedException
	{
		Scanner file = new Scanner(System.in);
		int N = file.nextInt(); file.nextLine();
		for(int z = 0;z<N;z++)
		{
			String[] line = file.nextLine().split(",",-1);
			long ans = 0;
			for(String s: line)
			{
				ans *= 60;
				if(!s.isEmpty())
					ans += Integer.parseInt(s);
			}
			System.out.println(ans);
		}
	}
	
}
