
/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/nonnegpartsums
TAGS: dp, implementation
EXPLANATION:
- Let pref[i] be sum of the first (i + 1) number
- Let f(k) be a cyclic shift consists of k shifts (k < n)
=> For f(k) to meets the requirements, the following conditions must be met
    If (k == 0):
        min(pref[0], pref[1], pref[2],..., pref[n-1]) >= 0
    Else:
        + min(pref[k], pref[k+1],..., pref[n-1]) - pref[k-1] >= 0
        + sum(a[k], a[k+1],..., a[n-1]) + min(pref[0], pref[1],... pref[k-1]) >= 0

- We can use a prefix-sum-like (a type of dp) to determine if f(k) meets the requirement for a certain k (refer to below code for more details) 
END ANNOTATION
*/
import java.util.*;
import java.io.*;

public class NonNegPartSums {

    public void run() throws IOException {
        while (true) {
            int n = nextInt();
            if (n == 0)
                break;

            int[] a = nextIntArray(n);

            // pref[i] stores sum(a[0], a[1],..., a[i])
            int[] pref = new int[n];

            // minPref[i] stores min(pref[0], pref[1],..., pref[i])
            int[] minPref = new int[n];

            // minPrefSuff[i] stores min(pref[i], pref[i+1],..., pref[n-1])
            int[] minPrefSuff = new int[n];

            pref[0] = minPref[0] = a[0];

            for (int i = 1; i < n; i++) {
                pref[i] = pref[i - 1] + a[i];
                minPref[i] = Math.min(minPref[i - 1], pref[i]);
            }

            minPrefSuff[n - 1] = pref[n - 1];
            for (int i = n - 2; i >= 0; i--) {
                minPrefSuff[i] = Math.min(minPrefSuff[i + 1], pref[i]);
            }

            int ret = 0;
            if (minPref[n - 1] >= 0)
                ret++;

            int currSum = 0;

            for (int i = n - 1; i >= 1; i--) {
                currSum += a[i];
                int currMin = minPrefSuff[i] - pref[i - 1];
                if (currMin < 0)
                    continue;
                if (minPref[i - 1] + currSum >= 0)
                    ret++;
            }

            out.println(ret);

        }
    }

    static final boolean RUN_TIMING = false;
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
    public int nextInt() throws IOException {
        return Integer.parseInt(next());
    }

    public int[] nextIntArray(int n) throws IOException {
        int[] arr = new int[n];
        for (int i = 0; i < n; i++)
            arr[i] = nextInt();
        return arr;
    }

    public void sort(int[] a) {
        shuffle(a);
        Arrays.sort(a);
    }

    // long data-type
    public long nextLong() throws IOException {
        return Long.parseLong(next());
    }

    public long[] nextLongArray(int n) throws IOException {
        long[] arr = new long[n];
        for (int i = 0; i < n; i++)
            arr[i] = nextLong();
        return arr;
    }

    public void sort(long[] a) {
        shuffle(a);
        Arrays.sort(a);
    }

    // double data-type
    public double nextDouble() throws IOException {
        return Double.parseDouble(next());
    }

    public double[] nextDoubleArray(int n) throws IOException {
        double[] arr = new double[n];
        for (int i = 0; i < n; i++)
            arr[i] = nextDouble();
        return arr;
    }

    // Generic type
    public <T> void sort(T[] a) {
        shuffle(a);
        Arrays.sort(a);
    }

    public String next() throws IOException {
        int len = 0;
        int c;
        do {
            c = in.read();
        } while (Character.isWhitespace(c) && c != -1);
        if (c == -1) {
            throw new NoSuchElementException("Reached EOF");
        }
        do {
            inputBuffer[len] = (char) c;
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

    public String nextLine() throws IOException {
        int len = 0;
        int c;
        while ((c = in.read()) != '\n' && c != -1) {
            if (c == '\r') {
                continue;
            }
            inputBuffer[len] = (char) c;
            len++;
        }
        return new String(inputBuffer, 0, len);
    }

    public boolean hasNext() throws IOException {
        String line = nextLine();
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
            int j = (int) (Math.random() * (n - i));
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    public void shuffle(long[] arr) {
        int n = arr.length;
        for (int i = 0; i < n; i++) {
            int j = (int) (Math.random() * (n - i));
            long temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    public void shuffle(Object[] arr) {
        int n = arr.length;
        for (int i = 0; i < n; i++) {
            int j = (int) (Math.random() * (n - i));
            Object temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    public static void main(String[] args) throws IOException {
        if (FILE_INPUT)
            in = new PushbackReader(new BufferedReader(new FileReader(new File("output.txt"))), 1 << 20);
        if (FILE_OUTPUT)
            out = new PrintWriter(new FileWriter(new File("output.txt")));

        long time = 0;
        time -= System.nanoTime();
        new NonNegPartSums().run();
        time += System.nanoTime();

        if (RUN_TIMING)
            System.err.printf("%.3f ms%n", time / 1000000.0);

        out.flush();
        in.close();
    }
}
