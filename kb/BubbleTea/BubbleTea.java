/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/bubbletea
TAGS: greedy
EXPLANATION:
find the cheapest possible drink and then make as many as possible
END ANNOTATION
*/
import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Scanner;


public class BubbleTea {
    
    public static void main(String[] args) throws Exception
    {
        new BubbleTea().run();
    }
    
    public void run()
    {
        Scanner file = new Scanner(System.in);
        int N = file.nextInt();
        int[] prices = new int[N];
        for(int i = 0;i<N;i++)
            prices[i] = file.nextInt();
        int M = file.nextInt();
        int[] topping = new int[M];
        for(int i = 0;i<M;i++)
            topping[i] = file.nextInt();
        int minPrice = 2000;
        for(int i = 0;i<N;i++)
        {
            int K = file.nextInt();
            for(int j = 0;j<K;j++)
            {
                minPrice = Math.min(minPrice, prices[i] + topping[file.nextInt() - 1]);
            }
        }
        long money = file.nextLong();
        System.out.println(Math.max(0, money / minPrice - 1));
    }
    
}