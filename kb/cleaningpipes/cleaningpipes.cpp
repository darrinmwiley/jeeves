/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/cleaningpipes
TAGS: Math, Geometry, Graph, Vector, Line, Line Segment, Intersection, Line Segment Intersection, Bipartite, Bipartite Graph, Coloring, Graph Coloring, DFS, Depth-First Search, Depth First Search, Cycle
EXPLANATION:
We are given a set of line segments and must find a subset of them that includes each intersection exactly once (excluding wells). First, let us compute those intersections.
The problem is small enough that this can be brute-forced for all pairs of line segments. Skipping pairs with the same well, simply check whether both line segments have
endpoints on opposite sides of the line containing the other. For segment AB and line CD, consider the 2D cross products of the vector CD with CA and with CB. If either cross
product is 0 or they have opposite signs, segment AB intersects line CD. Note that we do not need the specific location of the intersection for this problem (although that could
be computed with similar logic).

Now, we have a collection of segments and all of the intersections between them. Construct a graph where each node represents a segment and two nodes are connected iff their
segments intersect. No three segments intersect at the same point (besides wells), so each edge corresponds to a unique intersection. Thus, the problem is reduced to finding
a way to partition the vertices into two groups (those with a robot and those without), such that each edge has one vertex in each group; in other words, a 2-coloring. This
can be computed using DFS: at before adding a node to the stack, check its color. If it is uncolored, color it the opposite of the current node (or arbitrarily if it is the
first node). If it is already colored, do not add it to the stack; if that color is the same as that of the current node, the 2-coloring has failed and the answer is impossible.
END ANNOTATION
*/

#include <iostream>
#include <vector>
#include <tuple>

using namespace std;

struct vec2
{
    int x, y;
};

inline vec2 operator-(vec2 l, vec2 r)
{
    return vec2{ l.x - r.x, l.y - r.y };
}

inline int cross(vec2 l, vec2 r)
{
    return l.x * r.y - l.y * r.x;
}

int main()
{
    int w, p;
    cin >> w >> p;

    vector<vec2> W(w);
    for (vec2& vec : W)
        cin >> vec.x >> vec.y;

    vector<int> S(p);
    vector<vec2> E(p);
    for (int i = 0; i < p; i++)
    {
        cin >> S[i] >> E[i].x >> E[i].y;
        S[i]--;
    }

    vector<pair<int, int>> GE;
    GE.reserve(500000);
    for (int j = 1; j < p; j++) for (int i = 0; i < j; i++)
    {
        if (S[i] == S[j]) continue;
        vec2 a = W[S[i]], b = E[i], c = W[S[j]], d = E[j];
        int
            cpa = cross(a - c, d - c),
            cpb = cross(b - c, d - c),
            cpc = cross(c - a, b - a),
            cpd = cross(d - a, b - a);
        bool
            iab = cpa == 0 || cpb == 0 || (cpa > 0) != (cpb > 0),
            icd = cpc == 0 || cpd == 0 || (cpc > 0) != (cpd > 0);
        if (iab && icd)
            GE.emplace_back(i, j);
    }

    vector<vector<int>> G(p);
    for (pair<int, int> e : GE)
    {
        G[e.first].push_back(e.second);
        G[e.second].push_back(e.first);
    }

    vector<int> C(p, -1);
    vector<int> stck;
    bool bipartite = true;
    for (int i = 0; i < p; i++)
    {
        if (C[i] >= 0) continue;
        C[i] = 0;
        stck.push_back(i);
        while (bipartite && !stck.empty())
        {
            int v = stck.back();
            stck.pop_back();
            int c = C[v];
            for (int w : G[v])
            {
                if (C[w] < 0)
                {
                    C[w] = !c;
                    stck.push_back(w);
                }
                else if (C[w] == c)
                {
                    bipartite = false;
                    break;
                }
            }
            if (!bipartite)
                break;
        }
    }

    cout << (bipartite ? "possible" : "impossible");
}