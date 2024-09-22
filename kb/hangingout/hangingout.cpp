/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/hangingout
TAGS: easy
EXPLANATION:
parse each event and calculate answer accordingly
END ANNOTATION
*/
#include "bits/stdc++.h"

using namespace std;

#define pb push_back
#define boolean bool
#define li long long int

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int L, N;
	cin >> L >> N;
	int t = 0;
	int ans = 0;
	for(int i = 0;i<N;i++)
    {
        string x;
        cin >>x;
        if(x == "enter")
        {
            cin >>x;
            int y = stoi(x);
            if(t+y > L)
            {
                ans++;
            }else{
                t += y;
            }
        }else{
            cin >> x;
            int y = stoi(x);
            t -= y;
        }
    }
    cout << ans << endl;
}
