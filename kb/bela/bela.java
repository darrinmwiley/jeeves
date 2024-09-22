/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/bela
TAGS: easy, casework
EXPLANATION:
for each card, determine if it is dominant and add it's respective value
END ANNOTATION
*/
import java.io.IOException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Scanner;

public class bela {
    public static void main(String[] args) throws NumberFormatException, IOException
    {
        Scanner file = new Scanner(System.in);
        int N = file.nextInt();
        int sum = 0;
        char dominant = file.next().charAt(0);
        String chars = "AKQJT987";
        int[] dom = new int[]{11,4,3,20,10,14,0,0};
        int[] reg = new int[]{11,4,3,2,10,0,0,0};
        for(int i = 0;i<N*4;i++)
        {
            String next = file.next();
            char b = next.charAt(0);
            char a = next.charAt(1);
            if(a==dominant)
            {
                sum+=dom[chars.indexOf(b)];
            }else
                sum+=reg[chars.indexOf(b)];
        }
        System.out.println(sum);
    }
}