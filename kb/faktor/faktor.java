/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/faktor
TAGS: easy, math
EXPLANATION:
just loop X until ceil(X/A) >= I
END ANNOTATION
*/
import java.util.Scanner;

public class faktor {

    public static void main(String[] args)
    {
        Scanner file = new Scanner(System.in);
        double A = file.nextDouble();
        int I = file.nextInt();
        for(int x = 0;true;x++)
        {
        	if(Math.ceil(x/A) >= I)
        	{
        		System.out.println(x);
        		return;
        	}
        }
    }
    
}