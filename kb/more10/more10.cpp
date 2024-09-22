/*
BEGIN ANNOTATION
PROBLEM URL: https://open.kattis.com/problems/more10
TAGS:union-find, dsu
EXPLANATION: Goes through the input statements and merges
	'rhyming' sets if the 'rhyming' segment is also a word.
END ANNOTATION
*/

#include <iostream>
#include <unordered_map>

using namespace std;

int find(int p[], int x) {
    if(p[x] < 0)
        return x;
    p[x] = find(p, p[x]);
    return p[x];
}
void merge(int p[], int x, int y) {
    int px = find(p, x);
    int py = find(p, y);
    if(px == py)
        return;
    p[py] += p[px];
    p[px] = py;
}

int main()
{
    int N, i = 0, n = 0, words = 0;
    cin >> N;
    string is[N][2];
    string nt[N][2];
    string w1, w2, isnot;
    unordered_map<string, int> numbers;
    for(; N > 0; --N) {
        cin >> w1 >> isnot >> w2;
        if(isnot == "is") {
            is[i][0] = w1;
            is[i++][1] = w2;
        } else {
            nt[n][0] = w1;
            nt[n++][1] = w2;
        }
        if(numbers.find(w1) == numbers.end())
            numbers.insert(make_pair(w1, words++));
        if(w1.size() > 3 &&numbers.find(w1.substr(w1.size() - 3)) == numbers.end())
            numbers.insert(make_pair(w1.substr(w1.size() - 3), words++));
        if(numbers.find(w2) == numbers.end())
            numbers.insert(make_pair(w2, words++));
        if(w2.size() > 3 && numbers.find(w2.substr(w2.size() - 3)) == numbers.end())
            numbers.insert(make_pair(w2.substr(w2.size() - 3), words++));
    }
    int p[words];
    for(int x=0; x < words; ++x)
        p[x] = -1;
    for (auto& it: numbers)
        for(int s = 0; s < 4; ++s)
            if(s < it.first.size() && numbers.find(it.first.substr(it.first.size() - s)) != numbers.end())
                merge(p, numbers[it.first], numbers[it.first.substr(it.first.size() - s)]);
    for(int x = 0; x < i; ++x)
        merge(p, numbers[is[x][0]], numbers[is[x][1]]);
    for(int x = 0; x < n; ++x)
        if(find(p, numbers[nt[x][0]]) == find(p, numbers[nt[x][1]])) {
            cout << "wait what?" << endl;
            return 0;
        }
    cout << "yes" << endl;
    return 0;
}

