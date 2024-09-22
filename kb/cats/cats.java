/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/cats
TAGS: mst 
EXPLANATION:
create a min spanning tree and make sure the amount of milk is <= than MST cost + # cats
END ANNOTATION
*/
import java.util.LinkedList;
import java.util.PriorityQueue;
import java.util.Queue;
import java.util.Scanner;


public class cats {
    
    public void run()
    {
        Scanner file = new Scanner(System.in);
        int zz = file.nextInt();
        file.nextLine();
        for(int z = 0;z<zz;z++)
        {
            int M = file.nextInt();
            int C = file.nextInt();
            boolean[] con = new boolean[C];
            PriorityQueue<Edge> que = new PriorityQueue<Edge>();
            for(int i = 0;i<(C*(C-1))/2;i++)
                que.add(new Edge(file.nextInt(),file.nextInt(),file.nextInt()));
            Edge e = que.poll();
            con[e.a] = true;
            con[e.b] = true;
            int sum = e.wt;
            int treeSize = 2;
            while(treeSize!=C)
            {
                Queue<Edge> refill = new LinkedList<Edge>();
                while(true)
                {   
                    Edge edge = que.poll();
                    if(con[edge.a]&&con[edge.b])
                        continue;
                    if(con[edge.a]^con[edge.b])
                    {
                        con[edge.a] = true;
                        con[edge.b] = true;
                        sum+=edge.wt;
                        treeSize++;
                        break;
                    }
                    refill.add(edge);
                }
                que.addAll(refill);
            }
            boolean b = sum+C <= M;
            System.out.println(b?"yes":"no");
        }
    }
    
    public static void main(String[] args)
    {
        new cats().run();
    }
    
}
class Edge implements Comparable<Edge>{
    public final int a,b,wt;
    public Edge(int x, int y, int z)
    {
        a = x;
        b = y;
        wt = z;
    }
    
    public int compareTo(Edge e)
    {
        return wt-e.wt;
    }
}