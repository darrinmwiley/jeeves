/*
BEGIN ANNOTATION
PROBLEM URL: https://open.kattis.com/problems/ovalwatch
TAGS: Hashmap, Treeset
EXPLANATION:
Look at comments
END ANNOTATION
*/
import java.io.*;
import java.util.*;

public class ovalwatch {
    public static void main(String[] args) {
        FastIO out = new FastIO();
        int players = out.nextInt();
        int legs = out.nextInt();
        //make a map that keeps track of the treesets
        //make a treeset for every vertical line
        //put all of the vertical values in that treeset
        Map<Integer, TreeSet<Integer>> map = new HashMap<>();

        for(int i = 0; i < legs; i++){
            int a = out.nextInt();
            int b = out.nextInt();
            if(!map.containsKey(a)){
                TreeSet<Integer> set = new TreeSet<>();
                set.add(b);
                map.put(a, set);
            }else{
                map.get(a).add(b);
            }
        }
        // System.out.println(map);
        //look at map<i> and at map<i-1>
        //get the smaller of the two
        for(int i = 0; i < players; i++){
            int curx = i;
            int cury = 0;
            // System.out.println("curx: " +curx + " cury: " + cury);
            while(true){
                boolean right = map.containsKey(curx);
                boolean left = map.containsKey(curx-1);
                if(!right && !left){
                    break;
                }else if(right && left){
                    SortedSet<Integer> tempRight = map.get(curx).tailSet(cury);
                    SortedSet<Integer> tempLeft = map.get(curx-1).tailSet(cury);
                    if(tempRight.size() == 0 && tempLeft.size() == 0){
                        break;
                    }else if(tempRight.size() == 0){
                        for(int e : tempLeft){
                            cury = e + 1;
                            curx--;
                            break;
                        }
                    }else if(tempLeft.size() == 0){
                        for(int e : tempRight){
                            cury = e + 1;
                            curx++;
                            break;
                        }
                    }else{
                        int a = -1;
                        int b = -1;
                        for(int e : tempLeft){
                            a = e;
                            break;
                        }
                        for(int e : tempRight){
                            b = e;
                            break;
                        }
                        if(b < a){
                            cury = b + 1;
                            curx++;
                        }else{
                            cury = a + 1;
                            curx--;
                        }
                    }

                }else if(right){
                    SortedSet<Integer> temp = map.get(curx).tailSet(cury);
                    if(temp.size() == 0)
                        break;
                    for(int e : temp){
                        cury = e + 1;
                        curx++;
                        break;
                    }
                }else if(left){
                    SortedSet<Integer> temp = map.get(curx-1).tailSet(cury);
                    if(temp.size() == 0)
                        break;
                    for(int e : temp){
                        cury = e + 1;
                        curx--;
                        break;
                    }
                }
            }
            out.print(curx + " ");
        }
        out.flush();
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
