/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/simon
TAGS:implementation
EXPLANATION:Check if "simon says" is a prefix of the string.
END ANNOTATION
*/

#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    string line;
    getline(cin, line);
    while (t--)
    {
        getline(cin, line);
        if (line.substr(0, 10) == "simon says")
            cout << line.substr(min(11, (int) line.length())) << "\n";
        else
            cout << "\n";
    }
    return 0;
}
