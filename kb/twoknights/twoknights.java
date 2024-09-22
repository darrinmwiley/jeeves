/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/twoknights
TAGS: dfs, implementation
EXPLANATION:
you can encode your state to a tuple (r1, c1, r2, c2, index), representing the locations of the two knights and how much of the poem you have already typed.
state size is 10*10*4*4*100 = 160,000. This is feasible.
If you can code the transition function cleanly, the problem is just a DFS implementation.
END ANNOTATION
*/
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.LinkedList;
import java.util.Queue;

public class twoknights {
    
    public static void main(String[] args) throws Exception
    {
        new twoknights().run();      
    }
    
    char SHIFT = '@';
    
    char[][] lower = new char[][] {
        "qwertyuiop".toCharArray(),
        "asdfghjkl;".toCharArray(),
        "zxcvbnm,./".toCharArray(),
        "@@      @@".toCharArray()
    };
    
    char[][] upper = new char[][] {
        "QWERTYUIOP".toCharArray(),
        "ASDFGHJKL:".toCharArray(),
        "ZXCVBNM<>?".toCharArray(),
        "@@      @@".toCharArray()
    };
    
    //r1,c1,r2,c2,index
    char[] line;
    boolean[][][][][] vis;
    int[][] d = new int[][] {{-2,-2,-1,-1,1,1,2,2},{-1,1,-2,2,-2,2,-1,1}};
    
    public void run() throws Exception
    {
        BufferedReader file = new BufferedReader(new InputStreamReader(System.in));
    loop:
        while(true)
        {
            line = file.readLine().toCharArray();
            if(line[0] == '*')
            {
                return;
            }
            Queue<state> que = new LinkedList<state>();
            vis = new boolean[4][10][4][10][line.length+1];
            vis[3][0][3][9][0] = true;
            state begin = new state(3,0,3,9,0);
            que.add(begin);
            while(!que.isEmpty())
            {
                state current = que.poll();
                int r1 = current.R1;
                int c1 = current.C1;
                int r2 = current.R2;
                int c2 = current.C2;
                int index = current.index;
                if(index == line.length)
                {
                    System.out.println(1);
                    continue loop;
                }
                for(int i = 0;i<8;i++)
                {
                    //first horse
                    state first = transition(current, r1+d[0][i],c1+d[1][i],r2,c2);
                    if(first != null && !vis[first.R1][first.C1][first.R2][first.C2][first.index]){
                        vis[first.R1][first.C1][first.R2][first.C2][first.index] = true;
                        que.add(first);
                    }
                    //second horse
                    state second = transition(current, r1, c1, r2+d[0][i],c2+d[1][i]);
                    if(second != null && !vis[second.R1][second.C1][second.R2][second.C2][second.index]){
                        vis[second.R1][second.C1][second.R2][second.C2][second.index] = true;
                        que.add(second);
                    }
                }
            }
            System.out.println(0);
        }
    }
    
    public boolean valid(int r, int c)
    {
        return Math.min(r,c) >= 0 && r<upper.length && c < upper[r].length;
    }
    
    public char getChar(int moveR, int moveC, int stayR, int stayC)
    {
        if(isShift(stayR, stayC))
            return upper[moveR][moveC];
        return lower[moveR][moveC];
    }
    
    public boolean isShift(int r, int c)
    {
        return lower[r][c] == SHIFT;
    }
    
    //assumes that only one horse is moving
    public state transition(state state, int r1, int c1, int r2, int c2)
    {
        char need = line[state.index];
        if(!valid(r1,c1) || !valid(r2,c2))
        {
            return null;
        }
        if(r1 == r2 && c1 == c2)
        {
            return null;
        }
        //first horse move
        if(state.R1 != r1)
        {
            char next = getChar(r1,c1,r2,c2);
            if(next != need && next != SHIFT)
                return null;
            if(next == SHIFT)
                return new state(r1,c1,r2,c2,state.index);
            else
                return new state(r1,c1,r2,c2,state.index+1);
        }else {//second horse move
            char next = getChar(r2,c2,r1,c1);
            if(next != need && next != SHIFT)
                return null;
            if(next == SHIFT)
                return new state(r1,c1,r2,c2,state.index);
            else
                return new state(r1,c1,r2,c2,state.index+1);
        }
    }
    
    private class state
    {
        int R1,C1,R2,C2,index;
        
        public state(int r1,int c1,int r2,int c2,int index){
            R1 = r1;
            C1 = c1;
            R2 = r2;
            C2 = c2;
            this.index = index;
        }
        
        public String toString()
        {
            return R1+" "+C1+" "+R2+" "+C2+" "+index;
        }
    }
}

