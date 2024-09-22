/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/spiral
TAGS: bfs, sieve, implementation
EXPLANATION:
to create the spiral, follow a pattern of right, up, left, down where you increase your step count by 1 every 2 directions
use a sieve to find out which numbers are prime, and then just implement bfs between numbers.
to be safe I generated far more grid than needed
END ANNOTATION
*/
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.Queue;
import java.util.StringTokenizer;

class spiral
{
    
    public static void main (String[] args) throws java.lang.Exception
    {
        new spiral().solve();
    }
    
    boolean[] prime;
    int[][] d = new int[][] {{0,-1,0,1},{1,0,-1,0}};
    int[] rloc = new int[1000000];
    int[] cloc = new int[1000000];
    
    public void solve() throws Exception
    {
        BufferedReader file = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st;
        int DIM = 315;
        prime = new boolean[DIM*DIM + 1];
        boolean[][] vis = new boolean[DIM][DIM];
        Arrays.fill(prime, true);
        for(int i = 2;i<prime.length;i++)
        {
            if(prime[i])
            {
                for(int j = i*2;j<prime.length;j+=i)
                {
                    prime[j] = false;
                }
            }
        }
        
        prime[1] = false;
        
        int[][] ints = new int[DIM][DIM];
        int r = DIM/2;
        int c = DIM/2;
        int index = 1;
        int step = 1;
        int dir = 0;
        boolean start = true;
        
        while(r < DIM && c < DIM && r >= 0 && c >= 0)
        {
            for(int i = 0;i<step;i++)
            {
                ints[r][c] = index++;
                rloc[ints[r][c]] = r;
                cloc[ints[r][c]] = c;
                r += d[0][dir];
                c += d[1][dir];
            }
            dir++;
            dir %= 4;
            if(dir % 2 == 0 && !start)
            {
                step++;
            }
            start = false;
        }
        
        /*for(int i = 0;i<DIM;i++)
        {
            for(int j = 0;j<DIM;j++)
            {
                if(!prime[ints[i][j]])
                    System.out.print("      ");
                else
                    System.out.printf("%5d ", ints[i][j]);
            }
            System.out.println();
        }*/
        
        String line;
        int cas = 1;
    loop:
        while((line = file.readLine()) != null)
        {
            st = new StringTokenizer(line);
            int begin = Integer.parseInt(st.nextToken());
            int end = Integer.parseInt(st.nextToken());
            Queue<Integer> que = new LinkedList<Integer>();
            que.add(rloc[begin]);
            que.add(cloc[begin]);
            que.add(0);
            for(int i = 0;i<DIM;i++)
            {
                for(int j = 0;j<DIM;j++)
                {
                    vis[i][j] = false;
                }
            }
            while(!que.isEmpty())
            {
                int rr = que.poll();
                int cc = que.poll();
                int cost = que.poll();
                vis[rr][cc] = true;
                if(rr == rloc[end] && cc == cloc[end])
                {
                    System.out.println("Case "+(cas++)+": "+cost);
                    continue loop;
                }
                for(int i = 0;i<4;i++)
                {
                    int newr = rr+d[0][i];
                    int newc = cc+d[1][i];
                    if(Math.min(newr,newc) >=0 && Math.max(newr, newc) < DIM && !vis[newr][newc] && !prime[ints[newr][newc]])
                    {
                        vis[newr][newc] = true;
                        que.add(newr);
                        que.add(newc);
                        que.add(cost+1);
                    }
                }
            }
            System.out.println("Case "+(cas++)+": impossible");
            
        }
    }
    
}