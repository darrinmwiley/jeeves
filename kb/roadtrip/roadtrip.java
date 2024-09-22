/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/roadtrip
TAGS: sorting, sweep
EXPLANATION:
each gas station has an interval of time where it will be 'active', meaning inside of this interval, you could be using gas that came from that station.
sort the endpoints of these intervals and sweep through them, maintaining a sorted list of available station to get gas from.
Always take gas from the cheapest active station.
END ANNOTATION
*/
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.math.BigInteger;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.PriorityQueue;
import java.util.StringTokenizer;

public class roadtrip {
    
    public static void main(String[] args) throws IOException {
        new roadtrip().run();
    }
    
    public void run() throws IOException
    {
        BufferedReader file = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(file.readLine());
        long N = Long.parseLong(st.nextToken());
        long G = Long.parseLong(st.nextToken());
        Comparator<station> timecomp = new Comparator<station>() {
            public int compare(station a, station b)
            {
                return Long.compare(a.time,b.time);
            }
        };
        ArrayList<station> stations = new ArrayList<station>();
        BigInteger cost = BigInteger.ZERO;
        long x = 0;
        PriorityQueue<station> events = new PriorityQueue<station>(timecomp);
        stations.add(new station(0,G,0));
        long endx = -1;
        for(int i = 0;i<N;i++)
        {
            st = new StringTokenizer(file.readLine());
            long a = Long.parseLong(st.nextToken());
            long b = Long.parseLong(st.nextToken());
            endx = Math.max(endx,a);
            station s = new station(a,a+G,b);
            events.add(s);
        }
        while(!stations.isEmpty() && !events.isEmpty())
        {
            station event = events.peek();
            station using = stations.get(0);
            if(event.time > using.expire)
            {
                cost = cost.add(BigInteger.valueOf(using.expire - x).multiply(BigInteger.valueOf(using.cost)));//expire-x * cost
                x = using.expire;
                stations.remove(0);
            }else {
                cost = cost.add(BigInteger.valueOf(using.cost).multiply(BigInteger.valueOf(event.time - x)));
                while(!stations.isEmpty() && stations.get(stations.size()-1).cost>=event.cost)
                    stations.remove(stations.size()-1);
                stations.add(events.poll());
                x = event.time;
            }
        }
        if(x!=endx)
            System.out.println("cancel road trip");
        else
            System.out.println(cost);
    }
    
    public int getPos(ArrayList<station> stations, station event)
    {
        long cost = event.cost;
        if(stations.isEmpty() || cost <= stations.get(0).cost)
            return 0;
        if(cost > stations.get(stations.size() -1).cost)
            return stations.size();
        int L = 0;
        int R = stations.size()-1;
        int M = (L+R)/2;
        int best = stations.size();
        while(R-L>1)
        {
            M = (L+R)/2;
            if(stations.get(M-1).cost < cost)
            {
                best = M;
                L = M;
            }
            if(stations.get(M).cost >= cost)//go left
            {
                R = M;
            }
        }
        return best;
    }
    
    private class station implements Comparable<station>{
        
        long time;
        long expire;
        long cost;
        public station(long t, long e, long c)
        {
            time = t;
            expire = e;
            cost = c;
        }
        @Override
        public int compareTo(station o) {
            return Long.compare(cost, o.cost);
        }
        
        public String toString()
        {
            return time+" "+cost+" "+expire;
        }
        
    }
}