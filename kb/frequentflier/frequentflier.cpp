/*
BEGIN ANNOTATION
PROBLEM URL: https://open.kattis.com/problems/frequentflier
TAGS: greedy,heap
EXPLANATION: 
In my implementation, I process as month intervals [-m+1,0] to 
    [n-1,m+n-2] with the upper and lower bounds increasing by 1 for 
    each interval. For an interval, I will be paying for >= min(k,f)
    flights where f is the number of flights in the interval. For 
    >= f cases, obviously I must pay for all the flights in the 
    interval. The >= k case is more interesting, you have to choose
    the flights to pay for intelligently.
My idea is to share as many flights with later intervals as possible.
    This way, I can minimize the number of extra flights I must choose
    when I reach those later intervals. The best way to share is to
    keep marking the latest flights as payed until I've marked k
    flights. The later flights are shared with more later intervals.
The way I choose the latest flights is by maintaining a priority queue
    which tracks the latest month which still has an unpayed flight.
    When processing an interval, push the latest month in the interval,
    then mark flights from the month at the top of the priority queue 
    to get the latest flights, popping whenever no flights are left
    so it doesn't look at that month again.
I think the algorithm running time is O(n log(n) + m), since for each 
    interval, the "if (dif > k-sum)" happens at most once, and for
    each month, it gets pushed and popped at most once.
END ANNOTATION
*/

#include <bits/stdc++.h>

using namespace std;
using ll = long long;
#define PAD 200000
int n,m;
ll k;
// 0-padding
ll fPad[3*PAD];
ll payPad[3*PAD];
ll* f=fPad+PAD; // pay[i] = # flights in month i
ll* pay=payPad+PAD; // pay[i] = # flights payed in month i.

int main() {
    cin >> n >> m >> k;
    for (int i=0;i<n;i++) cin >> f[i];
    int lower=-m+1,upper=0;
    priority_queue<int,vector<int>,less<int>> pq; // max heap
    ll sum=0; // # flights marked in current interval
    while (lower < n) {
        pq.push(upper);
        while (!pq.empty()
                && pq.top() >= lower
                && sum<k
                ) { 
            int idx=pq.top();
            int dif=f[idx]-pay[idx];
            if (dif > k-sum) {
                pay[idx] += k-sum;
                sum += k-sum;
            }
            else {
                sum += dif;
                pay[idx]=f[idx];
                pq.pop(); 
            }
        }
        sum -= pay[lower];
        lower++,upper++;
    }
    sum=0;
    for (ll i : payPad) sum += i;
    cout << sum << endl;
}