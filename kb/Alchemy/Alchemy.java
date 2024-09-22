/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/alchemy
TAGS: case work, implementation, graph, greedy
EXPLANATION:
as there are 2,000 circles, we are targeting a N^2 or N^2logN runtime.

We can also afford to check if circle c1 contains circle c2 for each (c1,c2), as
this takes only N^2 time. With this information we can create a tree where
v is a direct descendant of u if circle u is the smallest circle containing
circle v. Now we can generalize the problem to ordering the nodes of a tree
optimally.

Each circle's (a,b) falls into one of the following categories:

{oo, +o, o+, -o, o-, ++, --, ++-, -++, +--, --+, +=-, -=+}

oo:  a is zero and b is zero. We don't care how much we flip this
+o:  a is positive and b is zero. We want to flip this the largest odd number
     of times possible, with an optional extra flip at the end
     (or zero if this is not possible)
o+:  a is zero and b is positive. We want to flip this the largest even number
     of times possible, with an optional extra flip at the end
-o:  a is negative and b is zero. We want to avoid flipping this.
o-:  a is zero and b is negative. We want to avoid flipping this more than once.
++:  a is positive and b is positive. We want to flip this as many times as
     possible
--:  a is negative and b is negative. We want to avoid flipping this.
++-: a is positive, b is negative, and the net energy of two flips is positive.
     We want to flip this the largest odd number of times possible,
     (or zero if this is not possible)
-++: a is negative, b is positive, and the net energy of two flips is positive.
     We want to flip this the largest even number of times possible
+--: a is positive, b is negative, and the net energy of two flips is negative.
     We want to flip this only once if possible, and avoid flipping it
     otherwise.
--+: a is negative, b is positive, and the net energy of two flips is negative.
     We want to avoid flipping this.
+=-: a is positive, b is negative, and the net energy of two flips is zero.
     We want to flip this any odd number of times.
-=+: a is negative, b is positive, and the net energy of two flips is zero.
     We want to avoid flipping this an odd number of times.

next we realize that the maximum energy achievable for any circle can be
achieved for every circle at the same time. If a circle has X ancestors, you can
flip it anywhere from 0 to X times, as the number of times a circle flips is
equivalent to how many of its ancestors come after it in the ordering. To argue
that any combination of flip numbers for the set of circles is achievable,
consider the idea of splicing circles into the ordering in order of decreasing
radii. As each newly inserted circle is smaller than every other, no existing
flip values will change, regardless of where the new circle is ordered. The
number of times the newly added circle will flip can be chosen from 0 to X
depending on how many ancestors the circle precedes. This is simply a proof that
every circle can provide a maximal amount energy at the same time though, and
will not give us the lexicographically smallest solution.

To get the lexicographically smallest ordering, we can greedily perform the
following:

while(some nodes are unordered){
  select the smallest node n such that putting n next would not compromise
  optimality
}

How do we know if choosing some node will compromise optimality? We can use the
idea of blocking. Depending on its category, each circle will block certain
ancestor nodes from being ordered until after is has been ordered itself.

Keep in mind that the terms 'last' ancestor and similar do not refer to the
largest or smallest, but the last which is put into the ordering, irrespective
of it's position on the tree.

oo:  we don't care about how many parent nodes come after this, so no blocking
     here
+o:  We want the maximum odd number of flips. Hence, if at any point the number
     of unordered ancestors we have has is odd, we should block them all.
o+:  We want the maximum even number of flips. Hence, if at any point the number
     of unordered ancestors we have is even, we should block them all.
-o:  We don't want to flip this, so we want this to come after every ancestor.
     Hence, ancestors will block this.
o-:  We don't want to flip this more than once. This is hard to encode into
     blocking, but we can just check for it. We only want to order this type of
     circle sometime after all but one of it's ancestors has been ordered.
++:  We want to flip this as many times as possible, so we will block every
     ancestor
--:  We want to avoid flipping this, so ancestors will block this.
++-: We want the maximum odd number of flips. Hence, if at any point the number
     of unordered ancestors we have has is odd, we should block them all.
     In addition to this, we only want to order this when ancestors left to
     order is odd, as an even number of flips would compromise the maximum
     energy. This is a more restrictive case of '+o'
-++: We want the maximum even number of flips. Hence, if at any point the number
     of unordered ancestors we have has is even, we should block them all.
     In addition to this, we only want to order this when ancestors left to
     order is even, as an odd number of flips would compromise the maximum
     energy. This is a more restrictive case of 'o+'
+--: We want to flip this only once, so if at any point the number of ancestors
     remaining to be ordered is one, we must block it.
--+: We want to avoid flipping this, so all ancestors will block this.
+=-: We want to flip this any odd number of times, so if at any point the number
     of ancestors remaining to be ordered is one, we must block it.
     In addition to this, we only want to order this when the number of
     unordered ancestors is odd, as an even number of flips would compromise the
     maximum energy.
-=+: We want to avoid flipping this an odd number of times. In other words, we
     can flip it any even number of times without compromising the maximum
     energy. We don't need to block anything here, as this could always go last
     (because there would be an even 0 ancestors afterwards). However we do have
     the additional constraint that we can only order this when there are an
     even number of ancestors left to be ordered.

To implement this idea of blocking, I had each node keep track of each node it
was blocking, as well as the number of nodes it was being blocked by. Whenever
a node was placed into the ordering, I would iterate through the list of nodes
that it was blocking, and decrement their blocked-by counter by 1. Any node with
a block counter of 0 (along with the other case-wise criteria above met) could
be ordered without compromising the maximum energy.

After each node is ordered, I also iterate through each unordered node, checking
their blocking criteria to see if they would need to begin blocking their
ancestors due to the change. Checking all nodes to update blocking criteria is
an O(N) operation, and this happens for each node that is added to the ordering,
giving us an overall O(N^2) complexity for these checks.

Due to the way the cases are formulated, each node will only begin blocking
once. Since there are N nodes, and each node can block at most N other nodes,
updating each once will also only be O(N^2) complexity.

This gives us an overall O(N^2) runtime.

There is definitely a more elegant solution than this.
END ANNOTATION
*/
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashSet;
import java.util.StringTokenizer;

public class Alchemy {

    int N;
    circle[] circles;
    int xx = 0;
    boolean[] used;
    int[] ans;
    int sum;
    boolean[] constraining;

    public static void main(String[] args) throws NumberFormatException, IOException
    {
        new Alchemy().run();
    }

    public void run() throws NumberFormatException, IOException
    {
        BufferedReader file = new BufferedReader(new InputStreamReader(System.in));
        N = Integer.parseInt(file.readLine());
        StringTokenizer st;
        circles = new circle[N];
        for(int i = 0;i<N;i++)
        {
            st = new StringTokenizer(file.readLine());
            int x = Integer.parseInt(st.nextToken());
            int y = Integer.parseInt(st.nextToken());
            int r = Integer.parseInt(st.nextToken());
            int a = Integer.parseInt(st.nextToken());
            int b = Integer.parseInt(st.nextToken());
            circles[i] = new circle(i,x,y,r,a,b);
        }

        constraining = new boolean[N];
        circle[] orig = circles.clone();
        Arrays.sort(circles);
        for(int i = 0;i<circles.length;i++)
        {
            for(int j = i+1;j<circles.length;j++)
            {
                int x1 = circles[i].x;
                int x2 = circles[j].x;
                int y1 = circles[i].y;
                int y2 = circles[j].y;
                int r1 = circles[i].r;
                int r2 = circles[j].r;
                int d1 = (x1-x2)*(x1-x2)+(y1-y2)*(y1-y2);
                int d2 = (r1+r2)*(r1+r2);
                if(d1 < d2)
                {
                    orig[circles[i].id].parents.add(circles[j].id);
                    orig[circles[j].id].children.add(circles[i].id);
                }
            }
        }
        circles = orig;
        sum = calculateAnswer(circles);
        used = new boolean[N];
        ans = new int[N];
        update();
     loop:
        for(int x = 0;x<N;x++)
        {
            for(int i = 0;i<circles.length;i++)
            {
                circle c = circles[i];
                String cla = c.classification;
                if(used[i] || c.indegree != 0)
                    continue;
                if(cla.equals("oo"))
                {
                    select(i);
                    continue loop;
                }else if(cla.equals("o+"))
                {
                    select(i);
                    continue loop;
                }else if(cla.equals("+o"))
                {
                    select(i);
                    continue loop;
                }else if(cla.equals("o-"))
                {
                    if(c.parents.size() <= 1) {
                        select(i);
                        continue loop;
                    }
                }else if(cla.equals("-o"))
                {
                    select(i);
                    continue loop;
                }else if(cla.equals("--"))
                {
                    select(i);
                    continue loop;
                }else if(cla.equals("++"))
                {
                    select(i);
                    continue loop;
                }else if(cla.equals("+--")) {
                    if(c.parents.size() <= 1) {
                        select(i);
                        continue loop;
                    }
                }else if(cla.equals("++-"))
                {
                    if((c.parents.size() & 1) == 1 || c.parents.isEmpty()) {
                        select(i);
                        continue loop;
                    }
                }else if(cla.equals("-++"))
                {
                    if((c.parents.size() & 1) == 0) {
                        select(i);
                        continue loop;
                    }
                }else if(cla.equals("--+"))
                {
                    select(i);
                    continue loop;
                }else if(cla.equals("+=-"))
                {
                    if((c.parents.size() & 1) == 1 || c.parents.isEmpty()) {
                        select(i);
                        continue loop;
                    }
                }else if(cla.equals("-=+"))
                {
                    if((c.parents.size() & 1) == 0)
                    {
                        select(i);
                        continue loop;
                    }
                }
            }
        }

        PrintWriter pout = new PrintWriter(System.out);
        pout.println(sum);
        for(int x: ans)
        {
            pout.print(x+1+" ");
        }
        pout.flush();
    }

    public int calculateAnswer(circle[] circles)
    {
        int ans = 0;
        for(circle c: circles)
        {
            int max = 0;
            int curr = 0;
            for(int i = 1;i<=c.parents.size();i++)
            {
                if((i&1) == 1)
                    curr += c.a;
                else curr += c.b;
                max = Math.max(max, curr);
            }
            ans += max;
        }
        return ans;
    }

    public void select(int n)
    {
        used[n] = true;
        ans[xx++] = n;
        for(int x:circles[n].children)
        {
            circles[x].parents.remove(n);
        }
        for(int x: circles[n].out)
        {
            circles[x].indegree--;
        }
        update();
    }

    public void update()
    {
        for(int i = 0;i<circles.length;i++)
        {
            if(used[i])
                continue;
            circle c = circles[i];
            String cla = c.classification;
            if(cla.equals("oo"))
            {
            }else if(cla.equals("o+"))
            {
                if(!constraining[i] && (c.parents.size() & 1) == 0)
                {
                    for(int par: c.parents)
                    {
                        c.out.add(par);
                        circles[par].indegree++;
                    }
                    constraining[i] = true;
                }
            }else if(cla.equals("+o"))
            {
                if(!constraining[i] && (c.parents.size() & 1) == 1)
                {
                    for(int par: c.parents)
                    {
                        c.out.add(par);
                        circles[par].indegree++;
                    }
                    constraining[i] = true;
                }
            }else if(cla.equals("-o"))
            {
                if(!constraining[i]){
                    for(int par: c.parents)
                    {
                        circles[par].out.add(i);
                        c.indegree++;
                    }
                    constraining[i] = true;
                }
            }else if(cla.equals("--"))
            {
                if(!constraining[i]){
                    for(int par: c.parents)
                    {
                        circles[par].out.add(i);
                        c.indegree++;
                    }
                    constraining[i] = true;
                }
            }else if(cla.equals("++"))
            {
                if(!constraining[i]){
                    for(int par: c.parents)
                    {
                        c.out.add(par);
                        circles[par].indegree++;
                    }
                    constraining[i] = true;
                }
            }else if(cla.equals("+--")) {
                if(!constraining[i] && c.parents.size() == 1)
                {
                    for(int par: c.parents)
                    {
                        c.out.add(par);
                        circles[par].indegree++;
                    }
                    constraining[i] = true;
                }
            }else if(cla.equals("++-"))
            {
                if(!constraining[i] && (c.parents.size() & 1) == 1)
                {
                    for(int par: c.parents)
                    {
                        c.out.add(par);
                        circles[par].indegree++;
                    }
                    constraining[i] = true;
                }
            }else if(cla.equals("-++"))
            {
                if(!constraining[i] && (c.parents.size() & 1) == 0)
                {
                    for(int par: c.parents)
                    {
                        c.out.add(par);
                        circles[par].indegree++;
                    }
                    constraining[i] = true;
                }
            }else if(cla.equals("--+"))
            {
                if(!constraining[i]){
                    for(int par: c.parents)
                    {
                        circles[par].out.add(i);
                        c.indegree++;
                    }
                    constraining[i] = true;
                }
            }else if(cla.equals("+=-"))
            {
                if(!constraining[i] && c.parents.size() == 1)
                {
                    for(int par: c.parents)
                    {
                        c.out.add(par);
                        circles[par].indegree++;
                    }
                    constraining[i] = true;
                }
            }
        }
    }

    private class circle implements Comparable<circle>{

        int id,x,y,r,a,b;
        String classification;
        ArrayList<Integer> out;//things this is blocking
        int indegree;
        HashSet<Integer> parents;
        ArrayList<Integer> children;

        public circle(int id, int x, int y, int r, int a, int b)
        {
            this.id = id;
            this.x = x;
            this.y = y;
            this.r = r;
            this.a = a;
            this.b = b;
            this.children = new ArrayList<Integer>();
            this.parents = new HashSet<Integer>();
            this.out = new ArrayList<Integer>();
            if(a == 0 && b == 0)
                classification = "oo";
            else if(a == 0 && b > 0)
                classification = "o+";
            else if(a > 0 && b == 0)
                classification = "+o";
            else if(a == 0 && b < 0)
                classification = "o-";
            else if(a < 0 && b == 0)
                classification = "-o";
            else if(a < 0 && b < 0)
                classification = "--";
            else if(a > 0 && b > 0)
                classification = "++";
            else if(a > 0 && b < 0 && a+b < 0)
                classification = "+--";
            else if(a > 0 && b < 0 && a+b > 0)
                classification = "++-";
            else if(a < 0 && b > 0 && a+b > 0)
                classification = "-++";
            else if(a < 0 && b > 0 && a+b < 0)
                classification = "--+";
            else if(a > 0 && a+b == 0)
                classification = "+=-";
            else if(a < 0 && a+b == 0)
                classification = "-=+";
        }

        @Override
        public int compareTo(circle o) {
            return Integer.compare(r, o.r);
        }
    }
}
