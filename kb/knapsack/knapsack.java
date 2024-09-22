/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/knapsack
TAGS: dp, knapsack
EXPLANATION:
standard knapsack implementation
END ANNOTATION
*/
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.StringTokenizer;

class knapsack
{
    
    public static void main (String[] args) throws java.lang.Exception
    {
        new knapsack().solve();
    }
    
    ArrayList<Integer> primes = new ArrayList<Integer>();
    HashMap<Integer,Integer> map = new HashMap<Integer,Integer>();
    
    public void solve() throws Exception
    {
        BufferedReader file = new BufferedReader(new InputStreamReader(System.in));
        String line;
        StringTokenizer st;
        while((line = file.readLine())!= null)
        {
            st = new StringTokenizer(line);
            int K = Integer.parseInt(st.nextToken());
            int N = Integer.parseInt(st.nextToken());
            int[] W = new int[N];
            int[] V = new int[N];
            for(int i = 0;i<N;i++)
            {
                st = new StringTokenizer(file.readLine());
                V[i] = Integer.parseInt(st.nextToken());
                W[i] = Integer.parseInt(st.nextToken());
            }
            int[][] dp = new int[N+1][K+1];
            for(int i = 1;i<dp.length;i++)
            {
                for(int j = 1;j<dp[i].length;j++)
                {
                    dp[i][j] = dp[i-1][j];
                    if(j >= W[i-1])
                        dp[i][j] = Math.max(dp[i][j], dp[i-1][j-W[i-1]] + V[i-1]);
                }
            }
            
            int r = dp.length-1;
            int c = dp[r].length-1;
            ArrayList<Integer> list = new ArrayList<Integer>();
            while(r != 0)
            {
                if(dp[r][c] != dp[r-1][c])
                {
                    c -= W[r-1];
                    list.add(r-1);
                }
                r--;
            }
            System.out.println(list.size());
            for(int i = 0;i<list.size();i++) {
                System.out.print(list.get(i)+" ");
            }
            System.out.println();
        }
    }
}