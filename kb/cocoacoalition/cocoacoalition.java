/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/cocoacoalition
TAGS: casework, math
EXPLANATION:
1) you can do any amount in 3 moves
   
   assume that for a given case b > m. 
   If that is not the case, you can obviously make a horizontal and vertical cut to the bottom row and have a 2 cut solution. 
    
   with the first move, you can get within m squares of the goal.
   with the second move, you can slice the bottom m squares from the board
   with the third move, you can make a vertical cut to that slice to make up the difference
2) a 1 cut solution exists only if n or m divides a - obvious that some number of rows or columns would have to make the exact amount
3) a 2 cut solution exists if there is a cut that leaves a 1 cut solution
END ANNOTATION
*/
import java.math.BigInteger;
import java.util.HashSet;
import java.util.Scanner;

public class cocoacoalition {
    
    public static void main(String[] args)
    {
        new cocoacoalition().run();       
    }
    
    public void run()
    {
    		Scanner file = new Scanner(System.in);
    		long n = file.nextLong();
    		long m = file.nextLong();
    		long a = file.nextLong();
    		if(oneMove(n,m,a))
    		{
    			System.out.println(1);
    			return;
    		}
    		if(twoMove(n,m,a,false))
    		{
    			System.out.println(2);
    			return;
    		}
    		System.out.println(3);
    }
    
    public boolean twoMove(long n, long m, long a, boolean swap)
    {
    		for(int i = 1;i<n;i++)
    		{
    			long part1 = m*i;
    			long part2 = n*m - part1;
    			if(oneMove(i, m, a - part2) || oneMove(i,m, a))
    				return true;
    			if(oneMove(n-i, m, a - part1) || oneMove(n-i,m,a))
    				return true;
    		}
    		if(swap)
    			return false;
    		return twoMove(m,n,a,true);
    }
    
    public boolean oneMove(long n, long m, long a)
    {
    		return a > 0 && n*m >= a && (a%n == 0 || a % m == 0);
    }
}