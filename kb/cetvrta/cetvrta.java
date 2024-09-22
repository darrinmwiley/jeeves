/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/cetvrta
TAGS: easy, xor
EXPLANATION:
xor all X and all Y to get the missing X and Y. This is because two are guaranteed to match and they will xor each other out.
END ANNOTATION
*/
import java.util.*;

public class cetvrta{
    
    public static void main(String[] args)
    {
        int x = 0;
        int y = 0;
        Scanner file = new Scanner(System.in);
        for(int i = 0;i<3;i++)
        {
            x^=file.nextInt();
            y^=file.nextInt();
        }
        System.out.println(x+" "+y);
    }
    
}