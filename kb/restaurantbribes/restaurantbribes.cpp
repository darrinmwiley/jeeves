/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/restaurantbribes
TAGS: brute force, math
EXPLANATION:
We can consider each of the bribeable people independently. The cost of bribing someone to give p points is (a * p) ^ 2.
Let friends(x) be the number of friends of x who can be bribed. Then the revenue for bribing person y to give p points is
the summation of (100 * p / friends(z) - (a * p) ^ 2) over all unbribeable friends z of y. Thus, the profit
is sum(100 * p / friends(z) - (a * p) ^ 2) - (a * p) ^ 2. Since p is between 0 and 10, we can brute force all p
for each person and take the maximum.
END ANNOTATION
*/

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1E5;
vector<int> adjList[MAXN + 1];
bool bribe[MAXN + 1];
int friends[MAXN + 1];
int d[MAXN + 1];

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m, k;
    cin >> n >> m >> k;
    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        adjList[a].push_back(b);
        adjList[b].push_back(a);
    }
    for (int i = 0; i < k; i++)
    {
        int x;
        cin >> x;
        cin >> d[x];
        bribe[x] = true;
    }
    for (int i = 1; i <= n; i++)
    {
        for (int adj : adjList[i])
        {
            if (bribe[adj])
                friends[i]++;
        }
    }
    double ans = 0;
    for (int i = 1; i <= n; i++)
    {
        if (!bribe[i])
            continue;
        double temp = 0;
        for (int p = 1; p <= 10; p++)
        {
            double cost = (double) (d[i] * p) * (d[i] * p);
            double revenue = 0;
            for (int adj : adjList[i])
            {
                if (bribe[adj])
                    continue;
                revenue += (double) 100 * p / friends[adj];
            }
            temp = max(temp, revenue - cost);
        }
        ans += temp;
    }
    cout << fixed << setprecision(7) << ans << "\n";
    return 0;
}
