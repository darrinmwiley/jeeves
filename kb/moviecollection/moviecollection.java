/*
BEGIN ANNOTATION
PROBLEM URL: https://open.kattis.com/problems/moviecollection
TAGS: Segment Tree
EXPLANATION:
Use a segtree to keep track of movies in the stack.
Whenever a movie is located and removed, that index in the segtree
is set to 0 and a 1 is added to the end of the segtree.
Can perform each locate in log(n) time.
Keeps track of locations of movies in an array with index.
END ANNOTATION
*/
import java.io.*;
import java.util.*;
public class moviecollection {
    int[][] data;
    int len;
    int lev;
    int eles;
    public moviecollection(int len, int elements){
        int levels = 1;
        int n = 1;
        while(n < len){
            n <<= 1;
            levels++;
        }
        //this works so far
        data = new int[levels][];
        for(int i = 0; i < levels; i++){
            data[i] = new int[1<<i];
        }
        this.len = n;
        this.lev = levels;
        this.eles = elements;
        init();
    }
    private void init(){
        //initialize all places to 1
        for(int i = 0; i < eles; i++)
            data[lev - 1][i] = 1;
        
        //start at second to bottom level
        for(int l = lev - 2; l >= 0; l--){
            for(int i = 0; i < data[l].length; i++){
                data[l][i] = data[l+1][i*2] + data[l+1][i*2+1];
                if(data[l][i] == 0)
                    break;
            }
        }
    }
    public void set(int i, int x){//x = data to be added, i - index
        data[data.length - 1][i] = x;//set it at the bottom layer
        int l = lev - 2, j = i / 2;
        while(l >= 0){
            data[l][j] = data[l + 1][j * 2] + data[l + 1][j * 2 + 1];
            l--;//go up a level
            j /= 2;//half the index
        }
    }
    public int add(){
        set(eles, 1);
        eles++;
        return eles - 1;//eles++
    }
    private int get(int lo, int hi, int nlo, int nhi, int l, int i){
        lo = Math.max(lo, nlo);
        hi = Math.min(hi, nhi);
        if(hi < lo)
            return 0;
        if(lo == nlo && hi == nhi)
            return data[l][i];
        int nmid = (nlo + nhi) / 2;
        int left = get(lo, hi, nlo, nmid, l + 1, i * 2);
        int right = get(lo, hi, nmid + 1, nhi, l + 1, i * 2 + 1);
        return left + right;
    }
    public int get(int lo, int hi){
        return get(lo, hi, 0, len - 1, 0, 0);
    }
    public int get(int lo){
        return get(lo, len - 1, 0, len - 1, 0, 0);
    }
    public void print(){
        for(int[] level : data)
            System.out.println(Arrays.toString(level));
    }
    public static void main(String[] args) {
        /*
        for each query, first get the index of that thing from the array
        */
        FastIO out = new FastIO();
        int testcases = out.nextInt();
        for(int i = 0; i < testcases; i++){
            int movies = out.nextInt();
            int queries = out.nextInt();
            moviecollection st = new moviecollection(movies + queries, movies);
            //movie number: index
            int[] locs = new int[movies + 1];
            for(int j = 1; j <= movies; j++){
                locs[j] = movies - j;
            }
            // System.out.println("Movies: " + movies + Arrays.toString(locs));
            for(int j = 0; j < queries; j++){
                int curMovie = out.nextInt();
                int curIdx = locs[curMovie];
                st.set(curIdx, 0);//remove
                int ret = st.get(curIdx);//query
                locs[curMovie] = st.add();//add
                out.print(ret + " ");
            }
            out.print("\n");
        }
        out.flush();
        // moviecollection st = new moviecollection(19);
        // st.print();
        // System.out.println(st.get(3));
        // st.add();
        // System.out.println(st.get(3));
    }
}

class FastIO {
    BufferedReader br;
    StringTokenizer st;
    PrintWriter out;

    public FastIO() {
        br = new BufferedReader(new InputStreamReader(System.in));
        out = new PrintWriter(System.out);
    }

    String next() {
        while (st == null || !st.hasMoreElements()) {
            try {
                st = new StringTokenizer(br.readLine());
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
        return st.nextToken();
    }

    int nextInt() {
        return Integer.parseInt(next());
    }

    long nextLong() {
        return Long.parseLong(next());
    }

    double nextDouble() {
        return Double.parseDouble(next());
    }

    String nextLine() {
        String str = "";
        try {
            str = br.readLine();
        } catch (IOException e) {
            e.printStackTrace();
        }
        return str;
    }

    void print(Object o) {
        out.print(o);
    }

    void println(Object o) {
        out.println(o);
    }

    void printf(String s, Object... o) {
        out.printf(s, o);
    }
    void flush(){
        out.flush();
    }
}
