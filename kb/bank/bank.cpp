/*
BEGIN ANNOTATION
PROBLEM URL: https://open.kattis.com/problems/bank
TAGS: greedy, sorting
EXPLANATION:
Sort people by their value. Take people with the highest value and put them as far back as possible so that they can still be served before the bank closes. If it not possible to do that, then they are not part of the solution (don't add their cash amount to the answer).
END ANNOTATION
*/
#include <iostream>
using namespace std;
#define SET(a, c) memset(a, c, sizeof(a))

#include <algorithm>
#include <cstring>

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, o;
    cin >> n >> o;
    pair<int, int> ar[n];
    for (int tr = 0; tr < n; tr++) {
        cin >> ar[tr].first >> ar[tr].second;
    }
    sort(ar, ar + n);
    reverse(ar, ar + n);
    bool taken[o];
    SET(taken, false);
    int ans = 0;
    for (int i = 0; i < n; i++) {
        int val = ar[i].first;
        int leave = ar[i].second;
        for (int j = leave; j >= 0; j--) {
            if (taken[j]) continue;
            taken[j] = 1;
            ans += val;
            break;
        }
    }
    cout << ans;
}
