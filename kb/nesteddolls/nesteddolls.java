/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/nesteddolls
TAGS: sorting, dp, LIS
EXPLANATION:
the answer is the largest set of dolls where none of them fit each other. 
You know this set will be pareto optimal, so the problem becomes finding the largest pareto optimal set.
to do so, sort by one dimension and then find the longest increasing subsequence (in nlogn) of the resulting sort.
END ANNOTATION
*/
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.StringTokenizer;

public class nesteddolls {

    public static void main(String[] args) throws Exception
    {
        new nesteddolls().run();
    }
        
    /*D sketch -
      try every possible starting point, find length of LIS and LDS starting at that point.
    */
    
    public void insert(int i, ArrayList<Integer> list)
    {
        //System.out.println("inserting "+i+" to "+list);
        if(list.isEmpty())
            list.add(i);
        else if(i>=list.get(list.size()-1))
            list.add(i);
        else if(i<list.get(0))
            list.set(0,i);
        else
        {
            int low = 0;
            int high = list.size();
            int m = (low+high)/2;
            while(high-low>1)
            {
                if(list.get(m)>i)
                    high = m;
                else
                    low = m;
                m = (low+high)/2;
            }
            if(list.get(high-1)<=i&&list.get(high)>i)
                list.set(high,i);
        }
    }
    
    public int lis(int[] ints)
    {
            int[] dp = new int[ints.length];
            Arrays.fill(dp, 1);
            for(int i = dp.length - 1;i>=0;i--)
            {
                for(int j = i+1;j<dp.length;j++)
                {
                    if(ints[i] <= ints[j])
                    {
                        dp[i] = Math.max(dp[i], dp[j]+1);
                    }
                }
            }
            int max = 0;
            for(int x: dp)
            {
                max = Math.max(max, x);
            }
            return max;
    }
    
    //to find pareto frontier, find the tallest doll 
    public void run() throws Exception{
        BufferedReader file = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st;
        int zz = Integer.parseInt(file.readLine());
        for(int z = 0;z<zz;z++)
        {
            int N = Integer.parseInt(file.readLine());
            int[] w = new int[N];
            int[] h = new int[N];
            st = new StringTokenizer(file.readLine());
            for(int i = 0;i<N;i++)
            {
                w[i] = Integer.parseInt(st.nextToken());
                h[i] = Integer.parseInt(st.nextToken());
            }
            doll[] dolls = new doll[N];
            for(int i = 0;i<N;i++)
            {
                dolls[i] = new doll(w[i], h[i]);
            }
            Arrays.sort(dolls);
            int[] ints = new int[N];
            for(int i = 0;i<dolls.length;i++)
            {
                ints[i] = dolls[i].h;
            }
            ArrayList<Integer> list = new ArrayList<Integer>();
            for(int x: ints)
            {
                insert(x, list);
            }
            int ans = list.size();
            System.out.println(ans);
        }
    }
    
    private class doll implements Comparable<doll>{
        
        int w, h;
        
        public doll(int w, int h)
        {
            this.w = w;
            this.h = h;
        }
        
        public int compareTo(doll d)
        {
            int a = Integer.compare(d.w, w);
            if(a == 0)
                return Integer.compare(h, d.h);
            return a;
        }
    }

    
  
}