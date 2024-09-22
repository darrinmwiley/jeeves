/*
BEGIN ANNOTATION
PROBLEM URL: http://open.kattis.com/problems/spavanac
TAGS: example tag 1, example tag 2, etc...
EXPLANATION:
example explanation,
can span multiple lines
END ANNOTATION
*/

import java.util.Scanner;

public class spavanac {
    public static void main(String[] args) throws Exception {
        int H, M;
        Scanner scnr = new Scanner(System.in);
        H = scnr.nextInt();
        M = scnr.nextInt();

        if (M < 45) {
            H--;
            M = (M-45) + 60;
        } else {
            M -= 45;
        }

        if (H < 0) {
            H += 24;
        }

        System.out.println(H + " " + M);
    }
}
