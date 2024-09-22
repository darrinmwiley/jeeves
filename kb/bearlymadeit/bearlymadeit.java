/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/bearlymadeit
TAGS: geometry, dijkstra, sweep, epsilon
EXPLANATION:
The observation to make is that the most efficient path is comprised of straight lines 
between the starting point, intersection points of any circles, and the ending point.

Since there are at most 25 circles, and any two circles have at most 2 intersections,
the number of locations to travel between are 2*25choose2 + 2 = 602.

Since there are a small number of vertices, we can check every pair to see if it is possible
to travel between the two without crossing the water

To determine if you can travel between two points on ice:

let segment S = the line segment between the two points.
Each circle that intersects S does so from some X = x1 to X = x2, or from some Y = y1 to Y = y2
For each circle, determine either the X or Y interval of intersection with S.
It is possible to move between two points if the union of all intervals fully covers S.

Union of a set of intervals can be done in NlogN with a sweep.

There is a degenerate case where two points have the same X or Y coordinate:
If two points have the same X coordinate, use Y intervals to determine if S is covered
If two points have the same Y coordinate, use X intervals to determine if S is covered

After constructing the graph of interesting locations and determining which you can move
between, perform dijkstras algorithm from the starting point to the ending point to get
the answer.

using an epsilon value is also important in this problem as some precision is lost throughout.

END ANNOTATION
 */
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.PriorityQueue;
import java.util.StringTokenizer;

public class bearlymadeit {
    
    int N;
    double[] cx;
    double[] cy;
    double[] r;
    
    double epsilon = .000001;
    
    double[][] dist;
    node[] nodes;
    
    public void run() throws IOException
    {
        BufferedReader file = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(file.readLine());
        double xb = Integer.parseInt(st.nextToken());
        double yb = Integer.parseInt(st.nextToken());
        double xm = Integer.parseInt(st.nextToken());
        double ym = Integer.parseInt(st.nextToken());
        N = Integer.parseInt(file.readLine());
        ArrayList<Double> x = new ArrayList<Double>();
        ArrayList<Double> y = new ArrayList<Double>();
        x.add(xb);
        y.add(yb);
        x.add(xm);
        y.add(ym);
        cx = new double[N];
        cy = new double[N];
        r = new double[N];
        for(int i = 0;i<N;i++)
        {
        		st = new StringTokenizer(file.readLine());
        		cx[i] = Integer.parseInt(st.nextToken());
        		cy[i] = Integer.parseInt(st.nextToken());
        		r[i] = Integer.parseInt(st.nextToken());
        }
        for(int i = 0;i<N;i++)
        {
        		for(int j = i+1;j<N;j++)
        		{
        			double d = dist(cx[i], cy[i], cx[j], cy[j]);
        			if(Math.abs(d-r[i]-r[j])<epsilon)
        			{
        				x.add((cx[i]+cx[j])/2.0);
        				y.add((cy[i]+cy[j])/2.0);
        			}else if(d < r[i] + r[j] && d > Math.abs(r[i] - r[j])){
	        			double a = (r[i]*r[i]-r[j]*r[j]+d*d)/(d*2);
	        			double h = Math.sqrt(r[i]*r[i]-a*a);
	        			double p2x = cx[i]+a*(cx[j] - cx[i])/d;
	        			double p2y = cy[i]+a*(cy[j] - cy[i])/d;
	        			double x1 = p2x+h*(cy[j] - cy[i])/d;
	        			double y1 = p2y-h*(cx[j] - cx[i])/d;
	        			double x2 = p2x-h*(cy[j] - cy[i])/d;
	        			double y2 = p2y+h*(cx[j] - cx[i])/d;
	        			x.add(x1);
	        			y.add(y1);
	        			x.add(x2);
	        			y.add(y2);
	        		}
        		}
        }
        nodes = new node[x.size()];
        for(int i = 0;i<nodes.length;i++)
        {
        		nodes[i] = new node(i,x.get(i),y.get(i));
        }
        dist = new double[nodes.length][nodes.length];
        for(int i = 0;i<nodes.length;i++)
        {
        		for(int j = i+1;j<nodes.length;j++)
        		{
        			if(canMove(x.get(i), y.get(i),x.get(j),y.get(j))) {
        				con(i,j);
        			}
        			dist[i][j] = dist[j][i] = dist(x.get(i), y.get(i),x.get(j),y.get(j));
        		}
        }
        boolean[] vis = new boolean[nodes.length];
        double[] fp = new double[nodes.length];
        Arrays.fill(fp, Double.POSITIVE_INFINITY);
        PriorityQueue<state> que = new PriorityQueue<state>();
        state begin = new state(0,0);
        que.add(begin);
        while(!que.isEmpty())
        {
        		state s = que.poll();
        		if(vis[s.location] || fp[s.location] <= s.cost)
        			continue;
        		vis[s.location] = true;
        		fp[s.location] = s.cost;
        		node curr = nodes[s.location];
        		for(int next: curr.con)
        		{
        			if(!vis[next] && s.cost + dist[curr.id][next] < fp[next])
        			{
        				que.add(new state(next, s.cost+dist[curr.id][next]));
        			}
        		}
        }
        if(Double.isInfinite(fp[1]))
        {
        	System.out.println("impossible");
        }else
        	System.out.println(fp[1]);
    }
    
    private class state implements Comparable<state>{
    	
    		int location;
    		double cost;
    		
    		public state(int l, double c)
    		{
    			this.location = l;
    			this.cost = c;
    		}

		@Override
		public int compareTo(state o) {
			return Double.compare(cost, o.cost);
		}
    	
    }
    
    public void con(int a, int b)
    {
    		nodes[a].con.add(b);
    		nodes[b].con.add(a);
    }
    
    private class node{
    	
    		int id;
    		double x, y;
    		ArrayList<Integer> con;
    	
    		public node(int id, double x, double y) {
    			this.id = id;
    			this.x = x;
    			this.y = y;
    			con = new ArrayList<Integer>();
    		}
    	
    }
    
    public boolean canMove(double x1, double y1, double x2, double y2)
    {
    	if(Math.abs(x1 - x2) < epsilon)
    		return canMoveY(x1, y1, x2, y2);
    	else
    		return canMoveX(x1,y1,x2,y2);
    }
    
    public boolean canMoveX(double x1, double y1, double x2, double y2)
    {
		PriorityQueue<event> que = new PriorityQueue<event>();
		for(int i = 0;i<N;i++)
		{
			segment seg = new segment(x1, y1, x2, y2);
			double[] interval = getInterval(seg, cx[i], cy[i], r[i])[0];
			if(interval != null)
			{
				que.add(new event(interval[0], true));
				que.add(new event(interval[1], false));
			}
		}
		int open = 0;
		while(!que.isEmpty())
		{
			event e = que.poll();
			if(e.open)
			{
				open++;
			}
			if(!e.open)
			{
				open--;
				if(open == 0)
				{
					if(Math.abs(e.x-Math.max(x1, x2)) < epsilon)
						return true;	
					else
						return false;
				}
			}
		}
		return false;
    }
    
    public boolean canMoveY(double x1, double y1, double x2, double y2)
    {
    		PriorityQueue<event> que = new PriorityQueue<event>();
    		for(int i = 0;i<N;i++)
    		{
    			segment seg = new segment(x1, y1, x2, y2);
    			double[] interval = getInterval(seg, cx[i], cy[i], r[i])[1];
    			if(interval != null)
    			{
    				que.add(new event(interval[0], true));
    				que.add(new event(interval[1], false));
    			}
    		}
    		int open = 0;
    		while(!que.isEmpty())
    		{
    			event e = que.poll();
    			if(e.open)
    			{
    				open++;
    			}
    			if(!e.open)
    			{
    				open--;
    				if(open == 0)
    				{
    					if(Math.abs(e.x - Math.max(y1, y2)) < epsilon)
    						return true;	
    					else
    						return false;
    				}
    			}
    		}
    		return false;
    }
    
    private class event implements Comparable<event>{
    	
		double x;
		boolean open;
		
		public event(double x, boolean open)
		{
			this.x = x;
			this.open = open;
		}
		
		public int compareTo(event o) 
		{
			if(Math.abs(x - o.x) < epsilon)
				return Boolean.compare(o.open, open);
			return Double.compare(x, o.x);
		}	   	
    }
    
    public double[][] getInterval(segment seg, double cx, double cy, double r)
    {
    		seg = new segment(seg.x1 - cx, seg.y1 - cy, seg.x2 - cx, seg.y2 - cy);
    		double det = r*r*(seg.A*seg.A+seg.B*seg.B)-seg.C*seg.C;
    		if(det <= 0)
    			return new double[][] {null, null};		
    		double denom = seg.A*seg.A+seg.B*seg.B;
    		double x1 = cx +(seg.A*seg.C+seg.B*Math.sqrt(det))/denom;
    		double x2 = cx +(seg.A*seg.C-seg.B*Math.sqrt(det))/denom;
    		double y1 = cy +(seg.B*seg.C-seg.A*Math.sqrt(det))/denom;
    		double y2 = cy +(seg.B*seg.C+seg.A*Math.sqrt(det))/denom;
    		double minx = cx + Math.min(seg.x1,seg.x2);
    		double maxx = cx + Math.max(seg.x1,seg.x2);
    		double miny = cy + Math.min(seg.y1, seg.y2);
    		double maxy = cy + Math.max(seg.y1, seg.y2);
    		double[] xans = new double[] {Math.max(minx, Math.min(x1, x2)), Math.min(maxx, Math.max(x1, x2))};
    		double[] yans = new double[] {Math.max(miny, Math.min(y1, y2)), Math.min(maxy, Math.max(y1, y2))};
    		return new double[][] {xans, yans};
    }
    
    private class segment{
    	
		double x1, y1, x2, y2;
		double A,B,C;
		
		public segment(double x1, double y1, double x2, double y2)
		{
			this.x1 = x1;
			this.y1 = y1;
			this.x2 = x2;
			this.y2 = y2;
			A = y2 - y1;
			B = x1 - x2;
			C = A*x1+B*y1;
		}
    }
    
    public double dist(double x1, double y1, double x2, double y2)
    {
    	return Math.sqrt((x1-x2)*(x1 - x2)+(y1 - y2)*(y1 - y2));
    }    
    
    public static void main(String[] args) throws IOException
    {
        new bearlymadeit().run();
    }
} 