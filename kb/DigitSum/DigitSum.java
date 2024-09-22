/*
BEGIN ANNOTATION
PROBLEM URL: https://open.kattis.com/problems/digitsum
TAGS: dp
EXPLANATION:
- There will 2 types of dp involved: unbounded_dp and bounded_dp
    + unbounded_dp[i] will stores digit sum of all numbers that have at most i digits
    + bounded_dp[i] will stores digit sum of all numbers that are <= the number formed by the last i digits of a given number
- Unbounded_dp:
    + Base case: unbounded_dp[1] = 45 (digit sum of all numbers that has at most 1 digit is 45 (sum from 0 to 9))
    + Recurrence relation: unbounded_dp[i] = sum(unbounded_dp[i-1] + j*pow(10, i-1)) for all j such that (0 <= j < 10)
- Bounded_dp: 
    + Base case: bounded_dp[i] = last_digit*(last_digit + 1)/2 (arithmetic sum from 0 to last_digit)
    + Recurrence realtion: 
        Let p be the number of digits on the right of the i-th digit (from the right) 
        Let digit[i] be the i-th digit from the right
        Let x be the number that is created by concatenating all digits to the right of digit[i] 
        bounded_dp[i] = sum(unbounded_dp[p] + j*pow(10, p)) + digit[i]*(x+1) + bounded_dp[i+1] for all j such that (0 <= j < digit[i])
- Approach:
    + Compute unbounded_dp up to the number of digits in B
    + Let solve(x) be bounded_dp[0] for a given x
    + The result will be solve(b) - solve(a-1)

- For better understanding about Digit Sum DP, refer to Codeburner's DP Material 
END ANNOTATION
*/
import java.util.*;
import java.io.*;
import java.math.*;
 
public class DigitSum {
    long[] unboundedDp;
    long[] pow10;

    public void prayGod() throws IOException {
        int t = ipar();
        while (t-- > 0) {
            String a = (lpar()-1)+"", b = lpar()+"";

            unboundedDp = new long[b.length() + 1];
            pow10 = new long[b.length() + 1];
            unboundedDp[1] = 45;
            pow10[1] = 10;

            for (int i = 2; i<=b.length(); i++) {
                pow10[i] = pow10[i-1] * 10;
                for (int j = 0; j<10; j++) unboundedDp[i] += unboundedDp[i-1] + j*pow10[i-1];
            }
            
            out.println(solve(b) - solve(a));
        }
    }

    public long solve(String val) {
        if (val.equals("-1")) return 0;

        long[] boundedDp = new long[val.length()];
        long curr = val.charAt(val.length()-1) - 48;
        boundedDp[val.length()-1] = curr*(curr+1)/2;
        
        for (int i = val.length()-2; i>=0; i--) {
            int bound = val.charAt(i)-48;
            for (int j = 0; j<bound; j++) boundedDp[i] += unboundedDp[val.length()-i-1] + j*pow10[val.length()-i-1];
            boundedDp[i] += bound*(curr+1) + boundedDp[i+1];
            curr += bound * pow10[val.length()-i-1];
        }
        
        return boundedDp[0];
    } 
 
    static final boolean RUN_TIMING = true;
    static final boolean AUTOFLUSH = false;
    static final boolean FILE_INPUT = false;
    static final boolean FILE_OUTPUT = false;
 
    static int iinf = 0x3f3f3f3f;
    static long inf = (long) 1e18 + 10;
    static int mod = (int) 1e9 + 7;
 
    static char[] inputBuffer = new char[1 << 20];
    static PushbackReader in = new PushbackReader(new BufferedReader(new InputStreamReader(System.in)), 1 << 20);
    static PrintWriter out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)), AUTOFLUSH);
 
    // int data-type
    public int ipar() throws IOException { return Integer.parseInt(spar()); }
    public int[] iapar(int n) throws IOException {
        int[] arr = new int[n];
        for (int i = 0; i < n; i++) arr[i] = ipar();
        return arr;
    }
    public void sort(int[] a) {
        shuffle(a);
        Arrays.sort(a);
    }
    public static void printArray(int[] arr) {
        for (int i = 0; i<arr.length; i++) out.print(arr[i] + " ");
        out.println();
    }
 
    // long data-type
    public long lpar() throws IOException { return Long.parseLong(spar()); }
    public long[] lapar(int n) throws IOException {
        long[] arr = new long[n];
        for (int i = 0; i < n; i++) arr[i] = lpar();
        return arr;
    }
    public static void printArray(long[] arr) {
        for (int i = 0; i<arr.length; i++) out.print(arr[i] + " ");
        out.println();
    }
    public void sort(long[] a) {
        shuffle(a);
        Arrays.sort(a);
    }
 
    // double data-type
    public double dpar() throws IOException {
        return Double.parseDouble(spar());
    }
    public double[] dapar(int n) throws IOException {
        double[] arr = new double[n];
        for (int i = 0; i < n; i++) arr[i] = dpar();
        return arr;
    }
    public static void printArray(double[] arr) {
        for (int i = 0; i<arr.length; i++) out.print(arr[i] + " ");
        out.println();
    }
 
    // Generic type
    public <T> void sort(T[] a) {
        shuffle(a);
        Arrays.sort(a);
    }
    public static <T> void printArray(T[] arr) {
        for (int i = 0; i<arr.length; i++) out.print(arr[i] + " ");
        out.println();
    }
 
    public String spar() throws IOException {
        int len = 0;
        int c;
        do {
            c = in.read();
        } while (Character.isWhitespace(c) && c != -1);
        if (c == -1) {
            throw new NoSuchElementException("Reached EOF");
        }
        do {
            inputBuffer[len] = (char)c;
            len++;
            c = in.read();
        } while (!Character.isWhitespace(c) && c != -1);
        while (c != '\n' && Character.isWhitespace(c) && c != -1) {
            c = in.read();
        }
        if (c != -1 && c != '\n') {
            in.unread(c);
        }
        return new String(inputBuffer, 0, len);
    }
 
    public String linepar() throws IOException {
        int len = 0;
        int c;
        while ((c = in.read()) != '\n' && c != -1) {
            if (c == '\r') {
                continue;
            }
            inputBuffer[len] = (char)c;
            len++;
        }
        return new String(inputBuffer, 0, len);
    }
 
    public boolean haspar() throws IOException {
        String line = linepar();
        if (line.isEmpty()) {
            return false;
        }
        in.unread('\n');
        in.unread(line.toCharArray());
        return true;
    }
 
    public void shuffle(int[] arr) {
        int n = arr.length;
        for (int i = 0; i < n; i++) {
            int j = (int)(Math.random() * (n-i));
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
 
    public void shuffle(long[] arr) {
        int n = arr.length;
        for (int i = 0; i < n; i++) {
            int j = (int)(Math.random() * (n-i));
            long temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
 
    public void shuffle(Object[] arr) {
        int n = arr.length;
        for (int i = 0; i < n; i++) {
            int j = (int)(Math.random() * (n-i));
            Object temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
 
    public static void main(String[] args) throws IOException {
        if (FILE_INPUT) in = new PushbackReader(new BufferedReader(new FileReader(new File("test.txt"))), 1 << 20);
        if (FILE_OUTPUT) out = new PrintWriter(new FileWriter(new File("output.txt")));
 
        long time = 0;
        time -= System.nanoTime();
        new DigitSum().prayGod();
        time += System.nanoTime();
        
        if (RUN_TIMING) System.err.printf("%.3f ms%n", time / 1000000.0);
        
        out.flush();
        in.close();
    }
}