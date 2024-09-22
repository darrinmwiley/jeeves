/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/listgame2
TAGS: knapsack, factorization
EXPLANATION:
simplify the problem by taking one of each prime, and then do knapsack on prime factors
END ANNOTATION
*/
import java.math.BigInteger;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Scanner;

public class ListGame2 {
    
    int[] dimensions;
    int[] mult;
    
    public static void main(String[] args)
    {
        new ListGame2().run();
    }
    
    public void run()
    {
        Scanner file = new Scanner(System.in);
        long N = file.nextLong();
        long newN = N;
        int toAdd = 0;
        ArrayList<Long> factors = new ArrayList<Long>();
        ArrayList<Long> primes = new ArrayList<Long>();
        int root = (int)(Math.sqrt(N));
        for(int i = 1;i<=root;i++)
        {
            if(N%i==0)
            {
                boolean prime = prime(i);
                if(!prime){
                    factors.add((long)(i));
                }
                else{
                    newN/=i;
                    toAdd++;
                    if(!dividesOnlyOnce(N,i))
                        primes.add((long)(i));
                }   
                if(i!=root)
                {
                    prime = prime(N/i);
                    if(!prime)
                        factors.add(N/i);
                    else{
                        newN/=(N/i);
                        toAdd++;
                    }
                }
            }
        }
        int sub = subproblem(newN,primes);
        System.out.println(sub+toAdd);
    }
    
    public boolean dividesOnlyOnce(long N, long K)
    {
        return N%(K*K)!=0;
    }
    
    public ArrayList<Long> permuteFactorsWrapper(Long N, ArrayList<Long> primes)
    {
        int[] max = new int[primes.size()];
        for(int i = 0;i<primes.size();i++)
        {
            long x = N;
            long y = primes.get(i);
            while(x%y==0)
            {
                
                max[i]++;
                x/=y;
            }
        }
        ArrayList<Long> factors = new ArrayList<Long>();
        permuteFactors(0,0,new int[max.length],max,primes,factors);
        return factors;
    }
    
    public void permuteFactors(int index, int total, int[] current, int[] max,ArrayList<Long> primes,ArrayList<Long> factors)
    {
        if(index==current.length)
        {
            if(total>1)
                factors.add(getFactor(current,primes));
            return;
        }
        for(int i = 0;i<=max[index];i++)
        {
            current[index] = i;
            permuteFactors(index+1,total+i,current,max,primes,factors);
            current[index] = 0;
        }
    }
    
    public long getFactor(int[] current, ArrayList<Long> primes)
    {
        long ans = 1;
        for(int i = 0;i<current.length;i++)
        {
            for(int j = 0;j<current[i];j++)
                ans*=primes.get(i);
        }
        return ans;
    }
    
    public int subproblem(long N,ArrayList<Long> primes)
    {
        //System.out.println(N+" "+primes);
        ArrayList<Long> factors = permuteFactorsWrapper(N,primes);
        //System.out.println(factors);
        int numPrimes = primes.size();
        dimensions = new int[numPrimes+1];
        Arrays.fill(dimensions,1);
        for(int i = 0;i<primes.size();i++)
        {
            long x = N;
            long y = primes.get(i);
            while(x%y==0)
            {
                x/=y;
                dimensions[i+1]++;
            }
        }
        dimensions[0] = factors.size()+1;
        mult = new int[dimensions.length];
        mult[mult.length-1] = 1;
        for(int i = mult.length-2;i>=0;i--)
            mult[i] = dimensions[i+1]*mult[i+1];
        int[][] costs = new int[factors.size()][primes.size()];
        for(int i = 0;i<primes.size();i++)
            for(int j = 0;j<factors.size();j++)
            {
                long x = factors.get(j);
                long y = primes.get(i);
                while(x%y==0)
                {
                    x/=y;
                    costs[j][i]++;
                }
            }
        int numOptions = 1;
        for(int i = 1;i<dimensions.length;i++)
            numOptions*=dimensions[i];
        int[] dp = new int[(costs.length+1)*numOptions];
        for(int i = 1;i<=costs.length;i++)
        {
            for(int j = 0;j<numOptions;j++)
            {
                int sub = subtract(i,j,costs[i-1]);
                if(sub!=-1)
                    dp[i*(numOptions)+j] = Math.max(dp[(i-1)*(numOptions)+j], dp[sub]+1);
                else
                    dp[i*(numOptions)+j] = dp[(i-1)*(numOptions)+j];
            }
        }
        return (dp[dp.length-1]);
    }
    
    public int getIndex(int[] spots)
    {
        int index = 0;
        for(int i = 0;i<spots.length;i++)
            if(spots[i]!=-1)
                index+=spots[i]*mult[i];
        return index;
    }
    
    public int[] getSpots(int first, int index)
    {
        int[] ans = new int[dimensions.length];
        ans[0] = first;
        for(int i = 1;i<ans.length;i++)
        {
            ans[i] = index/mult[i];
            index%=mult[i];
        }
        return ans;
    }
    
    public int subtract(int first, int index, int[] cost)
    {
        int[] spots = getSpots(first-1,index);
        for(int i = 1;i<spots.length;i++)
            if(spots[i]>=cost[i-1])
                spots[i]-=cost[i-1];
            else
                return -1;
        return getIndex(spots);
    }
    
    public boolean prime(long x)
    {
        return new BigInteger(x+"").isProbablePrime(25);
    }
    
}