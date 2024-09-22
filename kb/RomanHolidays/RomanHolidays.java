/*
BEGIN ANNOTATION
PROBLEM URL: https://open.kattis.com/problems/romanholidays
TAGS: math
EXPLANATION:

* Observation #1: 
 + If we have a list of x strings (sorted lexicographically), all of which are lexicographically smaller than some letter C, 
 then by adding C to the front of all x strings, we are able to create x strings that can be added to the back of the original list without violating the 
 lexicographical order. The same can be applied if we add another "D" to the newly-created x strings
    e.g: 
     + If we have the following list of ["A", "B", "C"], by adding a "D" to the front of all strings in the list, we will have the following new list:
        ["A", "B", "C", "DA", "DB", "DC"]. Here it can be seen that all the new strings are appended to the back of the list and the lexicographical order is maintained
     + By adding another "D" into the newly-created string, we will have the following list: 
       ["A", "B", "C", "DA", "DB", "DC", "DDA", "DDB", "DDC"]
       
* Observation #2: 
 + If we have a list of x strings (sorted lexicographically), all of which are lexicographically greater than some letter C, 
 then by adding C to the front of all x strings, we are able to create x strings that can be added to the front of the original list without violating the
 lexicographical order. The same can be applied if we add another "D" to the newly-created x strings
     e.g: 
      + If we have the following list of ["E", "F", "G"], by adding a "D" to the front of all strings in the list, we will have the following new list:
         ["DE", "DF", "DG", "E", "F", "G"]. Here it can be seen that all the new strings are appended to the front of the list and the lexicographical order is maintained
      + By adding another "D" into the newly-created string, we will have the following list: 
         ["DDE", "DDF", "DDG", "DE", "DF", "DG", "E", "F", "G"]

* In both cases, the list can be divided into sub-lists based on the number of "D" an element has

* Approach: 
 + (1) Split all the roman numerals of numbers that are smaller than 1000 into 2 group: 
 group in which all roman numerals are lexicographically smaller than 'M' and that in which all roman numerals are greater than 'M'
  => It can be seen that observation 1 can be applied to the first group and observation 2 can be applied to the second group
 
 + For each value received from the input, do the following: 
    + Retrieve its roman numeral and split the result into 2 parts: the "M" part and the non-"M" part
    + If the non-M part is greater than "M" (lexicographically), then the result will be negative index. Else, it will be positive index
    => The result will have the following formula:
     + Positive index:
        Let x be the size of group 1 (defined in (1))
        Let y be the length of current M-part
        Let z be number of values in group 1 (defined in (1)) that has roman numerals smaller than current non-"M" part
        
        If y == 0: the result will be the z
        If y == 1: the result will be x + z + 1
        If y > 1: the result will be x + (x+1) * (y-1) + z + 1
        
     + Negative index: 
       Let x be the size of group 2 (defined in (1))
       Let y be the length of current non-M part
       Let z be number of values in group 2 (defined in (2)) that has roman numerals greater than or equal the current non-"M" part
       
       The result wil be -(z + x*y)
    
    e.g: 
      * 1038 will have the 2 following parts: "M" and "XXXVIII"
      * The non-M part is greater than M, so we know that the result will be negative
      * The result for 1038 will be
       -(1 + 54*1) = -55

END ANNOTATION
*/
import java.util.*;
import java.io.*;
import java.math.*;

public class RomanHolidays {

    final String[] ones = {"", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"};
    final String[] tens = {"", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"};
    final String[] hundreds = {"", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"};

    boolean[] before_m = new boolean[1000];

    class RomanObj implements Comparable<RomanObj> {
        int val;
        String romanNumeral;
        public RomanObj(int v, String rom) {
            val = v;
            romanNumeral = rom;
        }
        public int compareTo(RomanObj other) {
            return romanNumeral.compareTo(other.romanNumeral);
        }
    }

    public String IntegerToRoman(int val) {
        StringBuilder str = new StringBuilder();
        str.append(hundreds[val/100]);
        val %= 100;
        str.append(tens[val/10]);
        val %= 10;
        str.append(ones[val]);
        return str.toString();
    }

    public void prayGod() throws IOException {
        ArrayList<RomanObj> beforeM = new ArrayList<RomanObj>();
        ArrayList<RomanObj> afterM = new ArrayList<RomanObj>();
    
        before_m[0] = true;
        for (int i = 1; i<1000; i++) {
            String roman = IntegerToRoman(i);
            if (roman.charAt(0) > 'M') {
                afterM.add(new RomanObj(i, roman));
                before_m[i] = false;
            }
            else {
                beforeM.add(new RomanObj(i, roman));
                before_m[i] = true;
            }
        }

        Collections.sort(beforeM);
        Collections.sort(afterM);

        int n = ipar();
        while (n-- > 0) {
            int x = ipar();
            int mCount = x/1000, rem = x%1000;
            if (before_m[rem]) {
                int pos = -1;
                for (int i = 0; i<beforeM.size(); i++) {
                    if (beforeM.get(i).val == rem) {
                        pos = i;
                        break;
                    }
                }
                int ret = pos + 1;
                if (mCount > 0) ret += beforeM.size() + (mCount-1) * (beforeM.size() + 1) + 1;
                out.println(ret);
            }
            else {
                int pos = -1;
                for (int i = 0; i<afterM.size(); i++) {
                    if (afterM.get(i).val == rem) {
                        pos = i;
                        break;
                    }
                }
                int ret = afterM.size() - pos;
                if (mCount > 0) ret += mCount * afterM.size();
                out.println(-ret);
            }
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
        if (FILE_OUTPUT) out = new PrintWriter(new FileWriter(new File("RomanHolidays.txt")));

        long time = 0;
        time -= System.nanoTime();
        new RomanHolidays().prayGod();
        time += System.nanoTime();
        
        if (RUN_TIMING) System.err.printf("%.3f ms%n", time / 1000000.0);
        
        out.flush();
        in.close();
    }
}
