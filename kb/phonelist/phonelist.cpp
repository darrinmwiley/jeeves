/*
BEGIN ANNOTATION
PROBLEM URL: https://open.kattis.com/problems/phonelist
TAGS: trie
EXPLANATION:
- Sort phone list in ascending order based on length
- For each phone number, insert it into a trie
* => If a flag is met during insertion, the current phone number's prefix is the same with one of the other phone numbers => list is invalid
END ANNOTATION
*/
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
#define size(a) int((a).size())
#define present(c, x) (c.find(x) != c.end()) 
#define printVerdict(verdict) cout << (verdict ? "YES": "NO") << '\n'
#define printDecimal(d) printf("%.9f\n", d)
#define inrange(val, start, end) (val >= start && val <= end)

const ll inf = 0x3f3f3f3f;

template <class T1, class T2, class T3> 
void printTuple(tuple<T1, T2, T3> t) { cout << get<0>(t) << " " << get<1>(t) << " " << get<2>(t) << '\n'; }
template <class T1, class T2>
void printPair(pair<T1, T2> p) { cout << p.first << " " << p.second << '\n'; }
template <class T>
void printArray(vector<T> arr) { for (int i = 0; i<size(arr); i++) {cout << arr[i] << " ";} cout << '\n'; }

struct TrieNode {
	bool endWord;
	map<char, TrieNode*> list;
};

TrieNode* createNode() {
	TrieNode* ret = new TrieNode;
	// endWord determines whether the current node is the end of a phone number
	ret->endWord = false;
	return ret;
}

void buildTree(TrieNode* &root, string &phone, bool &possible) {
	TrieNode *ptr = root;
	for (int i = 0; i<size(phone); i++) {
		// If endWord is true, then the current phone number's prefix is another phone number in the list
		if (ptr->endWord) possible = false;
		if (!present(ptr->list, phone[i])) ptr->list[phone[i]] = createNode();
		ptr = ptr->list[phone[i]];
	}
	ptr->endWord = true;
}

int main() {
	std::ios_base::sync_with_stdio(false);
	cin.tie(0);
	int t; cin >> t;
	while (t--) {
		int n; cin >> n;
		bool possible = true;
		TrieNode *root = createNode();
		vector<string> phone(n);
		for (int i= 0; i<n; i++) cin >> phone[i];
		sort(phone.begin(), phone.end(), [&](string a, string b){return size(a) < size(b);});
		for (int i= 0; i<n && possible; i++) {
			buildTree(root, phone[i], possible);
		}
		printVerdict(possible);
	}
}

