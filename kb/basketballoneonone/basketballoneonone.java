/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/basketballoneonone
TAGS: trivial
EXPLANATION:
the winner always makes the last shot
END ANNOTATION
*/
import java.io.IOException;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Scanner;

public class basketballoneonone {
    
    public static void main(String[] args) throws NumberFormatException, IOException
    {
        new basketballoneonone().run();      
    }
    
    public void run()
    {
        Scanner file = new Scanner(System.in);
        char[] line = file.nextLine().toCharArray();
        int a = 0;
        int b = 0;
        for(int i = 0;i < line.length;i+=2)
        {
            if(line[i] == 'A')
                a+= line[i+1]-'0';
            else
                b+=line[i+1]-'0';
        }
        if(a>b)
            System.out.println("A");
        else
            System.out.println("B");
    }
    
}