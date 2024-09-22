/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/greatfireball
TAGS: sweep, geometry, binary search
EXPLANATION:
The first observation is the problem is monotonic. There exist some R where any radius >= R is valid and any radius <= R is invalid.

Due to this, we can binary search for this radius, simplifying the problem.

The problem becomes:

can you create a circle of radius R touching the origin and covering at least K points?

For this we will place the circle tangentially touching the origin and perform a radial sweep. 
For every point that can be covered, there are two critical angles where the circle will start and stop covering the point. 
We can sort these critical angles and sweep through them to keep track of the maximum number of points that can be covered at the same time.

After sweeping we can know the maximum number of points a certain radius circle can cover, and then we can binary search with this information to solve the original problem. 

Runtime Nlog^2N
END ANNOTATION
*/
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.PriorityQueue;
import java.util.StringTokenizer;

public class greatfireball{
    
    double[] x;
    double[] y;
    double e = .00000001;
    
    public static void main(String[] args) throws IOException
    {
        new greatfireball().run();
    }
    
    public void run() throws IOException
    {
        BufferedReader file = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(file.readLine());
        int N = Integer.parseInt(st.nextToken());
        int K = Integer.parseInt(st.nextToken());
        x = new double[N];
        y = new double[N];
        for(int i = 0;i<N;i++)
        {
            st = new StringTokenizer(file.readLine());
            x[i] = Double.parseDouble(st.nextToken());
            y[i] = Double.parseDouble(st.nextToken());
        }
        PriorityQueue<event> top = new PriorityQueue<event>();
        PriorityQueue<event> bot = new PriorityQueue<event>();
        double R = 1000000000000000.0;
        double L = 0;
        double M = (R+L)/2;
        while(R-L > e) {
            top.clear();
            bot.clear();
            M = (R+L)/2;
            for(int i = 0;i<N;i++)
            {
                event[] ev = getInterval(x[i],y[i],M, i);
                if(ev == null)
                    continue;
                for(event x:ev)
                {
                    if(x.y>0)
                        top.add(x);
                    else
                        bot.add(x);
                }
            }
            event[] events = new event[(top.size() + bot.size())];
            int xx = 0;
            while(!top.isEmpty())
                events[xx++] = top.poll();
            while(!bot.isEmpty())
                events[xx++] = bot.poll();
             boolean[] active = new boolean[N];
             int numActive = 0;
             int maxActive = 0;
             for(int i = 0;i<events.length * 2;i++)
             {
                 event event = events[i % events.length];
                 if(event.open)
                 {
                     if(!active[event.id])
                     {
                         active[event.id] = true;
                         numActive++;
                         maxActive = Math.max(numActive, maxActive);
                     }
                 }else {
                     if(active[event.id])
                     {
                         active[event.id] = false;
                         numActive--;
                     }
                 }
                 }
             if(maxActive>=K)
             {
                 R = M;
             }else {
                 L = M;
             }
        }
        if(M > 100000000000000.0)
            System.out.println(-1);
        else
            System.out.println(M);
    }
    
    public event[] getInterval(double x, double y, double R, int id)
    {
        if(x*x+y*y > 4*R*R)
            return null;
        double[] v1 = new double[] {x/2, y/2};
        double[] v2 = new double[] {-v1[1],v1[0]};
        double mag = Math.sqrt(v2[0]*v2[0] + v2[1]*v2[1]);
        double len = Math.sqrt(R*R-mag*mag);
        double scale = len/mag;
        double[] v3 = scale(v2, scale);
        double[] v4 = scale(v2,-scale);
        double[] p1 = add(v1, v3);
        double[] p2 = add(v1, v4);
        event open = new event(p1[0],p1[1],true, id);
        event close = new event(p2[0],p2[1],false, id);
        return new event[] {open,close};
    }
    
    public double cross(double[] v1, double[] v2)
    {
        return v1[0]*v2[1] - v1[1]*v2[0];
    }
    
    public double[] scale(double[] v, double s)
    {
        return new double[] {v[0] * s, v[1] * s};
    }
    
    public double[] negate(double[] v)
    {
        return new double[] {-v[0],-v[1]};
    }
    
    public double[] add(double[] v1, double[] v2)
    {
        return new double[] {v1[0] + v2[0], v1[1] + v2[1]};
    }
    
    public double[] sub(double[] v1, double[] v2)
    {
        return add(v1, negate(v2));
    }
    
    private class event implements Comparable<event>{
        
        int id;
        double x, y;
        boolean open;
        
        public event(double x, double y, boolean open, int id)
        {
            this.id = id;
            this.x = x;
            this.y = y;
            this.open = open;
        }
        
        public String toString()
        {
            return x+" "+y+" "+open;
        }

        @Override
        public int compareTo(event o) {
            int a = (int)Math.signum(x*o.y - y*o.x);
            return a;
        }
        
    }
    
}