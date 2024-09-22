/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/goofy
TAGS: geometry
EXPLANATION:
Pen and paper helps.
Trig, Pythagorean Theorem, and coordinate geometry.
END ANNOTATION
*/


/** Simple yet moderately fast I/O routines.
 *
 * Example usage:
 *
 * Kattio io = new Kattio(System.in, System.out);
 *
 * while (io.hasMoreTokens()) {
 *    int n = io.getInt();
 *    double d = io.getDouble();
 *    double ans = d*n;
 *
 *    io.println("Answer: " + ans);
 * }
 *
 * io.close();
 *
 *
 * Some notes:
 *
 * - When done, you should always do io.close() or io.flush() on the
 *   Kattio-instance, otherwise, you may lose output.
 *
 * - The getInt(), getDouble(), and getLong() methods will throw an
 *   exception if there is no more data in the input, so it is generally
 *   a good idea to use hasMoreTokens() to check for end-of-file.
 *
 * @author: Kattis
 */

import java.util.StringTokenizer;
import java.io.BufferedReader;
import java.io.BufferedOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.io.OutputStream;

class Kattio extends PrintWriter {
    public Kattio(InputStream i) {
        super(new BufferedOutputStream(System.out));
        r = new BufferedReader(new InputStreamReader(i));
    }
    public Kattio(InputStream i, OutputStream o) {
        super(new BufferedOutputStream(o));
        r = new BufferedReader(new InputStreamReader(i));
    }

    public boolean hasMoreTokens() {
        return peekToken() != null;
    }

    public int getInt() {
        return Integer.parseInt(nextToken());
    }

    public double getDouble() {
        return Double.parseDouble(nextToken());
    }

    public long getLong() {
        return Long.parseLong(nextToken());
    }

    public String getWord() {
        return nextToken();
    }



    private BufferedReader r;
    private String line;
    private StringTokenizer st;
    private String token;

    private String peekToken() {
        if (token == null)
            try {
                while (st == null || !st.hasMoreTokens()) {
                    line = r.readLine();
                    if (line == null) return null;
                    st = new StringTokenizer(line);
                }
                token = st.nextToken();
            } catch (IOException e) { }
        return token;
    }

    private String nextToken() {
        String ans = peekToken();
        token = null;
        return ans;
    }
}

public class Goofy {
    public static void main(String[] args) {
        Kattio console = new Kattio(System.in, System.out);
        
        int numPoints = console.getInt();
        for(int i = 0; i < numPoints; i++) {
            double X = console.getDouble();
            double Y = console.getDouble();
            
            double theta = Math.atan(1 / Math.sqrt(X*X+Y*Y-1));
            double tanExp0 = Math.tan(Math.atan(Y/X) + theta);
            double tanExp1 = Math.tan(Math.atan(Y/X) - theta);
            console.println("(" + (0-tanExp0) + "," + 1 + "," + (Y-X*tanExp0) + "," +  (0-tanExp1) + "," + 1 + "," + (Y-X*tanExp1) + ")");
        }
        
        console.close();
    }
}

