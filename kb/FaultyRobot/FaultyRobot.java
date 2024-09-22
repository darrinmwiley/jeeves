/*
BEGIN ANNOTATION
PROBLEM URL: https://open.kattis.com/problems/faultyrobot
TAGS: dfs
EXPLANATION:
- Do a dfs on the graph while keeping track of 2 states: the current position, and whether the bug occurred
- If the bug occurred
  + If there is a forced path, follow the forced path
  + Else mark the node as possible stop and return
- If the bug has not occurred yet
  + If there is a forced path, consider the case in which the bug occurs at the current position and does not occur at the current position
  + DFS to non-forced neighbor (consider the case in which the bug occurs at the current position)
END ANNOTATION
*/
import java.util.*;
import java.io.*;
import java.math.*;

public class FaultyRobot {
    int n,m,ret;
    ArrayList<ArrayList<Integer>> graph;
    int[] forced;
    boolean[] possibleStop;
    boolean[][] visited;

    public void prayGod() throws IOException {
        n = ipar();
        m = ipar();
        ret = 0;

        forced = new int[n];
        Arrays.fill(forced, -1);

        graph = new ArrayList<ArrayList<Integer>>();
        for (int i = 0; i<n; i++) graph.add(new ArrayList<Integer>());

        possibleStop = new boolean[n];
        visited = new boolean[n][2];

        for (int i = 0; i<m; i++) {
            int a = ipar(), b = ipar();
            if (a < 0) forced[-a-1] = b-1;
            else graph.get(a-1).add(b-1);
        }

        dfs(0, false);
        dfs(0, true);

        out.println(ret);
    } 

    public void dfs(int currNode, boolean bugOccurred) {
        if (visited[currNode][bugOccurred ? 1 : 0]) return;
        visited[currNode][bugOccurred ? 1 : 0] = true;

        if (bugOccurred) {
            if (forced[currNode] == -1) {
                if (!possibleStop[currNode]) {
                    possibleStop[currNode] = true;
                    ret++;
                }
                return;
            }
            dfs(forced[currNode], bugOccurred);
        }
        else {
            if (forced[currNode] != -1) {
                dfs(forced[currNode], false);
                dfs(forced[currNode], true);
            }
            for (int neighbor : graph.get(currNode)) dfs(neighbor, true);
        }
    }

    static final boolean RUN_TIMING = true;
    static final boolean AUTOFLUSH = false;
    static final boolean FILE_INPUT = false;
    static final boolean FILE_OUTPUT = false;

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
        new FaultyRobot().prayGod();
        time += System.nanoTime();
        
        if (RUN_TIMING) System.err.printf("%.3f ms%n", time / 1000000.0);
        
        out.flush();
        in.close();
    }
}
