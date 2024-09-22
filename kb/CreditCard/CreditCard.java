/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/creditcard
TAGS: math, implementation
EXPLANATION:
straightforward implementation problem
make sure to follow the instructions in the correct order and watch out for floating point precision errors
END ANNOTATION
*/
import java.util.ArrayList;
import java.util.Scanner;

public class CreditCard {

    public static void main(String[] args) {
        Scanner console = new Scanner(System.in);
        
        int tests = console.nextInt();
        ArrayList<String> arr = new ArrayList<>();
        
        for(int i = 0; i < tests; i++)
        {
            double rate = console.nextDouble()/100.0;
            double balance = console.nextDouble();
            double monthly = console.nextDouble();
            int payments = 0;
            
            while(balance > 0.001)
            {
                if(payments > 1200)
                {
                    break;
                }
                balance += Math.round(balance *  rate * 100) / 100.0;
                balance -= monthly;
                balance = Math.round(balance * 100.0)/100.0;
                payments++;
            }
            
            if(payments <= 1200)
            {
                arr.add("" + payments);
            }else {
                arr.add("impossible");
            }
        }
        
        for(String str : arr)
        {
            System.out.println(str);
        }
    }

}