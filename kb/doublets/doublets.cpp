/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/doublets
TAGS: Graph, Shortest Paths, SSSP, BFS, Breadth First, Breadth-First, Breadth First Search, Breadth-First Search, String, Queue, Backtracking
EXPLANATION:
This problem can be solved correctly by creating a graph, where each vertex corresponds to a string. There is an edge between any two strings that form a doublet. Then, the
answer can be found by doing a breadth-first search starting at the one string and ending at the other. At each step, store the previous string's id to enable backtracking
later.

Unfortunately, this approach is too slow. To see this, consider a set of strings that are the same at all but one character. This set will form a clique in the graph. This
set can have up to 26 vertices and nCr(26, 2) = 325 edges. The key observation is that the number of edges can be reduced by adding an extra vertex for each of these cliques.
This can be done by, for each position in each word, inserting an auxiliary vertex corresponding to the string with that character replaced with a dollar sign. For instance,
if the dictionary is {"bog", "dog"}, also insert "$og", "b$g", "d$g", "bo$", and "do$". While the number of vertices increases, the total number of edges decreases by more
than enough to compensate for that in the worst case. Then, use the same algorithm before (except you must also avoid printing any of the auxiliary strings). This approach
has the added benefit of making the process of determining which edges to insert very easy; whenever you generate an auxiliary string, connect it to the string it was generated
from.
END ANNOTATION
*/

#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>

using namespace std;

unordered_map<string, int> ID;
vector<string> DICT;

int getID(const string& str)
{
    auto it = ID.find(str);
    if (it != ID.end())
        return it->second;
    ID.try_emplace(str, DICT.size());
    DICT.push_back(str);
    return DICT.size() - 1;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    string line;
    while (getline(cin, line) && !line.empty())
        getID(line);

    vector<pair<int, int>> E;
    int n = DICT.size();
    char c1 = '$';
    for (int i = 0; i < n; i++)
    {
        string str = DICT[i];
        for (char& c2 : str)
        {
            swap(c1, c2);
            E.emplace_back(i, getID(str));
            swap(c1, c2);
        }
    }

    vector<vector<int>> G(DICT.size());
    for (pair<int, int> e : E)
    {
        G[e.first].push_back(e.second);
        G[e.second].push_back(e.first);
    }

    string S, T;
    while (cin >> S >> T)
    {
        int s = getID(S), t = getID(T);
        queue<int> Q;
        Q.push(t);
        vector<int> P(DICT.size(), -1);
        bool found = false;
        while (!Q.empty() && !found)
        {
            int v = Q.front();
            Q.pop();
            for (int w : G[v])
            {
                if (P[w] >= 0) continue;
                P[w] = v;
                if (w == s)
                {
                    found = true;
                    break;
                }
                Q.push(w);
            }
        }
        if (found)
        {
            vector<int> ANS{ s };
            while (s != t)
                ANS.push_back(s = P[s]);
            for (int i : ANS)
            {
                const string& ans = DICT[i];
                if (find(ans.begin(), ans.end(), '$') == ans.end())
                    cout << ans << '\n';
            }
        }
        else
            cout << "No solution.\n";
        cout << '\n';
    }
}