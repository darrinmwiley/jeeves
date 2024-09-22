/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/hidingchickens
TAGS: dp, hashing
EXPLANATION:
Because the fox can only hold 2 chickens at a time, there are O(n^2) unique "moves" that can be made

I consider a move as a roundtrip from the roost to some number (1 or 2) of hiding spots and back.

Also take note that after hiding the last chicken, the fox does not have to return to the coop, so special moves exist for this situation.

We want to find the minimum cost subset of moves that is mutually exclusive and collectively exhaustive of all the hiding spots.

I used a 1d DP to do this, where each bit in the binary representation of the DP index represented whether or not that hiding place had been filled.

To ensure the last move happened last, I ran through the DP twice, once with the non-last variants of each move, and then with the last variants.
END ANNOTATION
*/
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Scanner;

public class HidingChickens{
    
    public static void main(String[] args)
    {
        new HidingChickens().run();
    }
    
    double[] X;
    double[] Y;
    boolean[][][] vis;
    double[][][] minCost;
    double[][] dist;
    
    double oo = 1000000000;
    
    public void run()
    {
    	Scanner file = new Scanner(System.in);
    	double x = file.nextDouble();
    	double y = file.nextDouble();
    	int N = file.nextInt();
    	vis = new boolean[N+1][3][1<<N];
    	minCost = new double[N+1][3][1<<N];
    	for(int i = 0;i<minCost.length;i++)
    		for(int j = 0;j<minCost[i].length;j++)
    			Arrays.fill(minCost[i][j], oo);
    	X = new double[N+1];
    	Y = new double[N+1];
    	X[0] = x;
    	Y[0] = y;
    	for(int i = 0;i<N;i++)
    	{
    		X[i+1] = file.nextDouble();
    		Y[i+1] = file.nextDouble();
    	}
    	dist = new double[N+1][N+1];
    	for(int i = 0;i<dist.length;i++)
    	{
    		for(int j = 0;j<dist.length;j++)
    		{
    			dist[i][j] = dist(X[i],Y[i],X[j],Y[j]);
    		}
    	}
    	ArrayList<move> moves = new ArrayList<move>();
    	for(int i = 0;i<N;i++)
    	{
    		moves.add(new move(new int[] {i}));
    		for(int j = i+1;j<N;j++)
    		{
    			moves.add(new move(new int[] {i,j}));
    		}
    	}
    	double[] minCost = new double[1 << N];
    	Arrays.fill(minCost, oo);
    	minCost[0] = 0;
    	//all moves but last
    	for(move m: moves)
    	{
    		int hash = m.hash;
    		for(int i = 0;i<minCost.length;i++)
    		{
    			if(minCost[i] != oo && (i & hash) == 0)
    			{
    				int newHash = i + hash;
    				double newCost = minCost[i] + m.cost;
    				if(newCost < minCost[newHash])
    				{
    					minCost[newHash] = newCost;
    				}
    			}
    		}
    	}
    	//last move
    	for(move m: moves)
    	{
    		int hash = m.hash;
    		for(int i = 0;i<minCost.length;i++)
    		{
    			if(minCost[i] != oo && (i & hash) == 0 && (i | hash) == (1<<N)-1)
    			{
    				int newHash = i + hash;
    				double newCost = minCost[i] + m.endCost;
    				if(newCost < minCost[newHash])
    				{
    					minCost[newHash] = newCost;
    				}
    			}
    		}
    	}
    	System.out.println(minCost[minCost.length - 1]);
    }
    
    private class move
    {
    	int hash;
    	double cost;
    	double endCost;
    	
    	public move(int[] locations)
    	{
    		hash = 0;
    		for(int x: locations)
    			hash += 1 << x;
    		if(locations.length == 1)
    		{
    			endCost = dist[0][locations[0]+1];
    			cost = endCost * 2;
    		}else {
    			cost = dist[0][locations[0]+1] + dist[locations[0]+1][locations[1]+1] + dist[0][locations[1]+1];
    			endCost = cost - Math.max(dist[0][locations[0]+1], dist[0][locations[1]+1]);
    		}
    	}
    }
    
    public double dist(double x1, double y1, double x2, double y2)
    {
    	return Math.sqrt((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1));
    }
}
