/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/bagoftiles
TAGS: meet-in-middle, math, ncr
EXPLANATION:
1) 	split into two roughly equal groups and permute all possible subsets of each group. 
	Since there are at most 30 tiles, there will be at most 2^15 (~65,000) subsets for each group. 

2)	group subsets into equivalence classes by the combination of (sum, #tiles used). 

3)	sort one half of the subset EQ classes, and iterate through the other. 

4)	For each subset EQ class, binary search for a complimentary EQ class from the sorted list

5)	Use nCr and subtraction to figure out the number of losing configurations after counting the winning ones
END ANNOTATION
*/
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.HashMap;
import java.util.Scanner;

public class BagOfTiles {
    
    public static void main(String[] args) throws Exception
    {
        new BagOfTiles().run();
    }
    
    public void run() throws Exception
    {
    	//N choose K up to 31 for easy lookup
        int[][] choose = new int[31][31];
        for(int i = 0;i<choose.length;i++)
        {
            choose[i][0] = choose[i][i] = 1;
        }
        for(int i = 1;i<choose.length;i++)
        {
            for(int j = 1;j<i;j++)
            {
                choose[i][j] = choose[i-1][j-1] + choose[i-1][j];
            }
        }
        Scanner file = new Scanner(System.in);
        int G = file.nextInt();
        for(int zz = 0;zz<G;zz++)
        {
            int M = file.nextInt();
            int[] ints = new int[M];
            for(int i = 0;i<M;i++)
            {
                ints[i] = file.nextInt();
            }
            int n = file.nextInt();
            int t = file.nextInt();
            int[] left = new int[M/2];
            int[] right = new int[ints.length - left.length];
            //split options in half
            int ind = 0;
            for(int i = 0;i<left.length;i++)
            {
                left[i] = ints[ind++];
            }
            for(int i = 0;i<right.length;i++)
            {
                right[i] = ints[ind++];
            }
            HashMap<Integer, int[]> L = new HashMap<>();
            HashMap<Integer, int[]> R = new HashMap<>();
            //get all possible combinations for each half
            bruteForce(left, 0, 0,0,L);
            bruteForce(right, 0,0,0,R);
            ArrayList<subsets> list1 = new ArrayList<subsets>();
            ArrayList<subsets> list2 = new ArrayList<subsets>(); 
            for(Integer x: L.keySet())
            {
                int[] y = L.get(x);
                for(int i = 0;i<y.length;i++)
                {
                    if(y[i] != 0)
                    {
                        list1.add(new subsets(x,i,y[i]));
                    }
                }
            }
            for(Integer x: R.keySet())
            {
                int[] y = R.get(x);
                for(int i = 0;i<y.length;i++)
                {
                    if(y[i] != 0)
                    {
                        list2.add(new subsets(x,i,y[i]));
                    }
                }
            }
            int ans = 0;
            //sort one half, iterate through the other
            Collections.sort(list2);
            for(subsets a: list1)
            {
                if(a.sum <= t && a.num <= n)
                {
                	//search the sorted half for a complementary subset type
                	subsets complement = search(t-a.sum, n-a.num, list2);
                    if(complement != null)
                        ans += a.amt * complement.amt;
                }
            }
            System.out.printf("Game %d -- %d : %d%n", zz+1, ans, choose[M][n] - ans);
        }
    }
    
    //binary search for a subset equivalence class of a specific (sum, num)
    public subsets search(int sum, int num, ArrayList<subsets> list)
    {
        int L = -1;
        int R = list.size();
        int M = (L+R)/2;
        subsets search = new subsets(sum, num, 0);
        while(R - L > 1)
        {
            M = (L+R)/2;
            subsets candidate = list.get(M);
            int comp = search.compareTo(candidate);
            if(comp < 0)
            {
                R = M;
            }
            else if(comp > 0)
            {
                L = M;
            }else {
                return candidate;
            }
        }
        return null;
    }
    
    //recursively try all possible subsets from options
    //fills map such that map[i][j] = # of ways to make sum of i with j tiles
    public void bruteForce(int[] options, int index, int sum, int num, HashMap<Integer, int[]> map)
    {
        if(index == options.length)
        {
            if(!map.containsKey(sum))
            {
                map.put(sum, new int[16]);
            }
            map.get(sum)[num]++;
        }else {
            bruteForce(options, index+1, sum + options[index], num+1, map);//this tries using the current option
            bruteForce(options, index+1, sum, num, map);//this tries not using the current option
        }
    }
    
    //container for an equivalence class of subset
    private class subsets implements Comparable<subsets>{
        
        int sum;//tile sum for this group of subsets
        int num;//number of tiles for this group of subsets
        int amt;//how many subsets are there with this (sum, num)
        
        public subsets(int sum, int num, int amt)
        {
            this.sum = sum;
            this.num = num;
            this.amt = amt;
        }

        @Override
        public int compareTo(subsets arg0) {
            int s = Integer.compare(sum, arg0.sum);
            if(s!=0)
                return s;
            return Integer.compare(num, arg0.num);
        }
        
    }
    
}
