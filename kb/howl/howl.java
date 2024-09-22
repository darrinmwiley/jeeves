/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/howl
TAGS: trivial
EXPLANATION:
appending the letter O to any valid howl will create a longer howl that is still valid.
END ANNOTATION
*/
import java.io.IOException;
import java.util.Scanner;

public class howl {
    
    public static void main(String[] args) throws IOException
    {
        new howl().run();      
    }
    
    public void run() throws IOException
    {
        Scanner file = new Scanner(System.in);
        String line = file.nextLine();
        System.out.println(line+"O");
    }
    
}