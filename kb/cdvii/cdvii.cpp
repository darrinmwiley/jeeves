/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/cdvii
TAGS: sweep
EXPLANATION:
sort and sweep traffic events, adding begin events to a map and removing
them upon end event and mapping the charge
END ANNOTATION
*/
#include "bits/stdc++.h"

using namespace std;

#define pb push_back
#define boolean bool
#define li long long int

struct event{

    string plate;
    bool enter;
    int month;
    int day;
    int hour;
    int minute;
    int location;

    bool operator<(const event &e)
    {
        int comp = month * 1000000 + day * 10000 + hour * 100 + minute;
        int ecomp = e.month * 1000000 + e.day * 10000 + e.hour*100 + e.minute;
        return comp < ecomp;
    }

};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int toll[24];
    for(int i = 0;i<24;i++){
        cin >> toll[i];
    }
    string line;
    vector<event> events;
    map<string, int> charge;
    getline(cin, line);
    while(getline(cin, line))
    {
        stringstream ss(line);
        string plate;
        string time;
        string status;
        int location;
        ss >> plate >> time >> status >> location;
        charge[plate] = 0;
        int month, day, hour, minute;
        stringstream date(time);
        string x;
        getline(date, x, ':');
        month = stoi(x);
        getline(date, x, ':');
        day = stoi(x);
        getline(date, x, ':');
        hour = stoi(x);
        getline(date, x, ':');
        minute = stoi(x);
        struct event e = {plate, status == "enter", month, day, hour, minute, location};
        events.pb(e);
    }
    sort(events.begin(), events.end());
    unordered_map<string, int> start_time;
    unordered_map<string, int> start_location;
    for(auto e: events)
    {
        if(e.enter)
        {
            start_time[e.plate] = e.hour;
            start_location[e.plate] = e.location;
        }else{
            if(start_time.count(e.plate))
            {
                int st = start_time[e.plate];
                start_time.erase(e.plate);
                int sl = start_location[e.plate];
                start_location.erase(e.plate);
                int chg = charge[e.plate];
                int newchg = chg + 100 + toll[st] * (abs(e.location - sl));
                charge[e.plate] = newchg;
            }
        }
    }

    for(auto keyval: charge)
    {
        string plate = keyval.first;
        if(keyval.second != 0){
            int cost = keyval.second + 200;
            printf("%s $%d.%02d\n",plate.c_str(), cost/100, cost%100);
        }
    }
}
