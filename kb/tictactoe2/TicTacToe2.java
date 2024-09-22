/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/tictactoe2
TAGS:brute force, simulation
EXPLANATION:there are at most 3^9 (~2000) games, so we can just brute force them all. 
Simulate every possible way to play the game, adding each game state to a structure as you go.
Then you can simply query the structure.
END ANNOTATION
*/
import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Scanner;


public class TicTacToe2 {
    
    HashSet<String> good;
    
    int[][][] toTest = new int[][][] {
        new int[][] {
            new int[] {0,0,0},
            new int[] {0,1,2}
        },
        new int[][] {
            new int[] {1,1,1},
            new int[] {0,1,2}
        },
        new int[][] {
            new int[] {2,2,2},
            new int[] {0,1,2}
        },
        new int[][] {
            new int[] {0,1,2},
            new int[] {0,0,0}
        },
        new int[][] {
            new int[] {0,1,2},
            new int[] {1,1,1}           
        },
        new int[][] {
            new int[] {0,1,2},
            new int[] {2,2,2}           
        },
        new int[][] {
            new int[] {0,1,2},
            new int[] {0,1,2}           
        },
        new int[][] {
            new int[] {0,1,2},
            new int[] {2,1,0}           
        },
    };
    
    public static void main(String[] args) throws Exception
    {
        new TicTacToe2().run();
    }
    
    public void run()
    {
        good = new HashSet<String>();
        char[][] cha = new char[3][3];
        for(int i = 0;i<3;i++)
        {
            for(int j = 0;j<3;j++)
            {
                cha[i][j] = '.';
            }
        }
        bf(cha);
        //for(String s: good)
        //  System.out.println(s);
        Scanner file = new Scanner(System.in);
        int N = file.nextInt();
        for(int i = 0;i<N;i++)
        {
            char[][] chars = new char[3][3];
            for(int j = 0;j<3;j++)
            {
                chars[j] = file.next().toCharArray();
            }
            String hash = new String(chars[0]) + new String(chars[1]) + new String(chars[2]);
            //System.out.println(hash);
            if(good.contains(hash))
                System.out.println("yes");
            else
                System.out.println("no");
        }
    }
    
    public void bf(char[][] chars)
    {
        String hash = new String(chars[0]) + new String(chars[1]) + new String(chars[2]);
        good.add(hash);
        if(testWin(chars) != '.')
            return;
        char next = getTurn(chars);
        for(int i = 0;i<3;i++)
        {
            for(int j = 0;j<3;j++)
            {
                if(chars[i][j] == '.')
                {
                    chars[i][j] = next;
                    bf(chars);
                    chars[i][j] = '.';
                }
            }
        }
    }
    
    public char getTurn(char[][] chars)
    {
        int x = 0;
        int o = 0;
        for(int i = 0;i<3;i++)
        {
            for(int j = 0;j<3;j++)
            {
                if(chars[i][j] == 'X')
                {
                    x++;
                }else if(chars[i][j] == 'O')
                {
                    o++;
                }
            }
        }
        if(x == o)
            return 'X';
        else
            return 'O';
    }
    
    public char testWin(char[][] chars)
    {
    loop:
        for(int[][] in: toTest)
        {
            char start = chars[in[0][0]][in[1][0]];
            if(start == '.')
                continue;
            for(int i = 1;i<3;i++)
            {
                char ch = chars[in[0][i]][in[1][i]];
                if(ch != start)
                    continue loop;
            }
            return start;
        }
        return '.';
    }
    
}