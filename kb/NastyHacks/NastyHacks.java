/*
BEGIN ANNOTATION
PROBLEM URL: https://open.kattis.com/problems/nastyhacks
TAGS: math
EXPLANATION:
simple
END ANNOTATION
*/


import java.io.BufferedOutputStream;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.util.StringTokenizer;


public class NastyHacks {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Kattio io = new Kattio(System.in);
		int round =  io.getInt();
		for(int i=0; i<round; i++)
		{
			int rNotAd = io.getInt();
			int rAd =io.getInt();
			int cost =io.getInt();
			
			int extraR = rAd - cost;
			if (extraR>rNotAd)
			{
				System.out.println("advertise\r\n");
			}else if (extraR==rNotAd)
			{
				System.out.println("does not matter\r\n");
			}else {
				System.out.println("do not advertise\r\n"
						+ "");
			}
		}
	}
}

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