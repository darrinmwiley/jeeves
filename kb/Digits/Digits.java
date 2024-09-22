/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/digits
TAGS: implementation, math
EXPLANATION:
the series converges very quickly, so you can naively check. 
edge cases of 0, 1, and very large values that you can't parse (just take length instead)
END ANNOTATION
*/
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;


public class Digits {
    
    public static void main(String[] args) throws Exception
    {
        new Digits().run();
    }
    
    public void run() throws IOException
    {
        BufferedReader file = new BufferedReader(new InputStreamReader(System.in));
       loop:
        while(true)
        {
            String next = file.readLine();
            if(next.equals("END"))
                return;
            else {
                int ans = 0;
                if(next.equals("1"))
                {
                    System.out.println(1);
                    continue;
                }
                int last = -1;
                int x1 = next.length();
                int index = 1;
                while(true)
                {
                    if(last == x1) {
                        System.out.println(index);
                        continue loop;
                    }
                    last = x1;
                    x1 = (x1+"").length();
                    index++;
                }
            }
        }
    }
    
}