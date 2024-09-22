/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/knightsearch
TAGS: dfs
EXPLANATION:
let node[i][j][k] be location (i,j) in the grid where you've seen the first K letters. 
Solution exists if you can dfs from some [i1][j1][0] to any [i2][j2][10]
END ANNOTATION
*/
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.LinkedList;
import java.util.Queue;
import java.util.StringTokenizer;

public class knightsearch {

    public static void main(String[] args) throws Exception
    {
        new knightsearch().run();
    }
    
    char[] search = "ICPCASIASG".toCharArray();
    int[][] d = new int[][] {{-2,-2,-1,-1,1,1,2,2},{-1,1,-2,2,-2,2,-1,1}};
    int N;
    
    public void run() throws Exception{
        BufferedReader file = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st;
        N = Integer.parseInt(file.readLine());
        char[] line = file.readLine().toCharArray();
        char[][] chars = new char[N][N];
        int index = 0;
        for(int i = 0;i<N;i++)
        {
            for(int j = 0;j<N;j++)
            {
                chars[i][j] = line[index++];
            }
        }
        boolean[][][] vis = new boolean[N][N][10];
        Queue<Integer> que = new LinkedList<Integer>();
        for(int i = 0;i<N;i++)
        {
            for(int j= 0;j<N;j++)
            {
                if(chars[i][j] == 'I')
                {
                    vis[i][j][0] = true;
                    que.add(i);
                    que.add(j);
                    que.add(0);
                }
            }
        }
        while(!que.isEmpty())
        {
            int r = que.poll();
            int c = que.poll();
            int i = que.poll();
            if(i == 9)
            {
                System.out.println("YES");
                return;
            }
            for(int x = 0;x<8;x++)
            {
                int rr = r+d[0][x];
                int cc = c+d[1][x];
                if(val(rr,cc) && chars[rr][cc] == search[i+1])
                {
                    vis[rr][cc][i+1] = true;
                    que.offer(rr);
                    que.offer(cc);
                    que.offer(i+1);
                }
            }
        }
        System.out.println("NO");
    }
    
    public boolean val(int r, int c)
    {
        return Math.min(r,c)>= 0 && r < N && c < N;
    }
    
}