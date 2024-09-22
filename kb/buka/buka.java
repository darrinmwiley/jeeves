/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/buka
TAGS: BigInteger, arbitrary precision
EXPLANATION:
basic arbitrary precision problem
END ANNOTATION
 */
import java.io.IOException;
import java.math.BigInteger;
import java.util.ArrayList;
import java.util.PriorityQueue;
import java.util.Scanner;

public class buka {
    
    public void run() throws IOException
    {
        Scanner file = new Scanner(System.in);
        BigInteger a = file.nextBigInteger();
        char op = file.next().charAt(0);
        BigInteger b = file.nextBigInteger();
        if(op == '+')
        {
        	System.out.println(a.add(b));
        }else {
        	System.out.println(a.multiply(b));
        }
    } 
    
    public static void main(String[] args) throws IOException
    {
        new buka().run();
    }
} 