/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/reconnaissance
TAGS: ternary search, binary search
EXPLANATION:
The distance between the farthest two cars is either monotonic or bitonic. In other words, one of these cases is true:

1) distance never changes
2) distance increases forever
3) distance decreases, reaches a critical point, and then increases forever

In any of these cases, you can use ternary search to find the critical point. 
In case 1, it will be anywhere. 
In case 2, it will be at T = 0
In case 3, it will be at a single point.

The implementation of the ternary search is very similar to binary search in this case, as you query a T and T+epsilon to see how the function is growing.
END ANNOTATION
*/
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class reconnaissance {
    
    public static void main(String[] args) throws Exception
    {
        new reconnaissance().run();      
    }
    
    int N;
    int[] pos;
    int[] vel;
    
    public void run() throws Exception
    {
        BufferedReader file = new BufferedReader(new InputStreamReader(System.in));
        N = Integer.parseInt(file.readLine());
        StringTokenizer st;
        pos = new int[N];
        vel = new int[N];
        for(int i = 0;i<N;i++)
        {
            st = new StringTokenizer(file.readLine());
            pos[i] = Integer.parseInt(st.nextToken());
            vel[i] = Integer.parseInt(st.nextToken());
        }
        double R = 1000000;
        double L = 0;
        double M = (L+R)/2;
        double best = 100000;
        for(int i = 0;i<1000;i++)
        {
            M = (L+R)/2;
            double dist = getDistance(M);
            double dist2 = getDistance(M+.0000001);
            if(dist == dist2)
            {
                System.out.println(dist);
                return;
            }
            if(dist<dist2)
            {
                R = M;
            }else {
                L = M;
            }
        }
        System.out.println(getDistance(M));
    }
    
    public double getDistance(double time)
    {
        double min = Double.POSITIVE_INFINITY;
        double max = Double.NEGATIVE_INFINITY;
        for(int i = 0;i<N;i++)
        {
            double x = pos[i] + vel[i]*time;
            min = Math.min(min,x);
            max = Math.max(max,x);
        }
        //System.out.println(time+" "+max+" "+min);
        return max - min;
    }
}