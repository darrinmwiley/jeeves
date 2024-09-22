/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/dicecup
TAGS: easy, counting
EXPLANATION:
1) you could count every possible combination and then print the largest ones
2) you could also figure out that the answer is always every number from min+1 to max+1
END ANNOTATION
*/
import java.util.Scanner;

public class DiceCup {

    public static void main(String[] args)
    {
        Scanner file = new Scanner(System.in);
        int x = file.nextInt();
        int y = file.nextInt();
        int min = Math.min(x,y);
        int max = Math.max(x,y);
        for(int i = min;i<=max;i++)
        {
            System.out.println(i+1);
        }
    }
    
}