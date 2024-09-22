/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/cold
TAGS: trivial, array
EXPLANATION:
count the number of elements less than zero
END ANNOTATION
*/
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.Scanner;
import java.util.StringTokenizer;

public class cold {
    
	public static void main(String[] args)
    {
        Scanner file = new Scanner(System.in);
        int zz = file.nextInt();
        int n = 0;
        for(int z = 0;z<zz;z++)
        {
            if(file.nextInt()<0)
                n++;
        }
        System.out.println(n);
    }
}