/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/runningmom
TAGS: graph, dfs
EXPLANATION:
dfs out, and when you reach an in progress node you know everything on the current path is safe.
END ANNOTATION
*/
import java.io.FileNotFoundException;
import java.util.Arrays;
import java.util.PriorityQueue;
import java.util.Scanner;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Scanner;


public class RunningMoM {
    
    int UNVISITED = 0;
    int IN_PROGRESS = 1;
    int COMPLETE = 2;
    
    Vertex[] vertices;
    int[] vertexStatus;
    boolean[] vertexSafe;
    
    public void run() throws Exception
    {
        Scanner input = new Scanner(System.in);
        
        //creates a mapping between name and vertex id
        HashMap<String, Integer> nameToID = new HashMap<String,Integer>();
        
        vertexSafe = new boolean[10000];//there will be at most 5000*2 cities
        vertices = new Vertex[10000];
        vertexStatus = new int[10000];
        for(int i = 0;i<10000;i++)
        {
            vertices[i] = new Vertex(i);
        }
        int numFlights = input.nextInt();
        for(int i = 0;i<numFlights;i++)
        {
            String city1 = input.next();
            String city2 = input.next();
            if(!nameToID.containsKey(city1))
            {
                nameToID.put(city1, nameToID.size());
            }
            if(!nameToID.containsKey(city2))
            {
                nameToID.put(city2, nameToID.size());
            }
            int id1 = nameToID.get(city1);
            int id2 = nameToID.get(city2);
            addEdge(id1, id2);
        }
        for(int i = 0;i<10000;i++)
            if(vertexStatus[i] == UNVISITED)
                dfs(i);
        while(input.hasNext())
        {
            String city = input.next();
            int id = nameToID.get(city);
            if(vertexSafe[id])
            {
                System.out.println(city+" safe");
            }else
                System.out.println(city+" trapped");
        }
    }
    
    public void dfs(int currentLocation)
    {
        vertexStatus[currentLocation] = IN_PROGRESS;
        for(int x: vertices[currentLocation].neighbors)
        {
            //specific to this problem - only predecessors in the DFS will be marked as in progress, which means if you can reach one, you are part of a loop, hence you are safe//
            if(vertexStatus[x] == IN_PROGRESS)
                vertexSafe[currentLocation] = true;
            
            if(vertexStatus[x] == UNVISITED)
                dfs(x);
            
            //specific to this problem - if you can reach a safe vertex, you are safe//
            if(vertexSafe[x])
                vertexSafe[currentLocation] = true;
        }
        vertexStatus[currentLocation] = COMPLETE;
    }
    
    //adds a directed edge between a and b
    public void addEdge(int a, int b)
    {
        vertices[a].neighbors.add(b);
    }
    
    private class Vertex{
    
        ArrayList<Integer> neighbors;
        int id;
        
        public Vertex(int id)
        {
            this.id = id;
            neighbors = new ArrayList<Integer>();
        }

    }
    
    public static void main(String[] args) throws Exception
    {
        new RunningMoM().run();
    }
}