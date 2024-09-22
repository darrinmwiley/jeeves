/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/turbo
TAGS: sorting, range-query, segment trees
EXPLANATION:
* The number of swaps for a smaller number is the number of elements before
* it in the array, except for the ones that have been sorted already.
* The opposite is true for large numbers
* 
* Enter an array of 1s in a segment tree
* For each element in order (1, N, 2, N-2, ...), get the sum of the values
* from the index to its target side of the array to get the number of swaps.
* Afterwards, subtract 1 from that index, effectively removing it from the array.
* 
* Example
* 4 1 3 5 2 : 1 has 1 element before it, it needs 1 swap, remove it from array
* 4 3 5 2 : 5 has 1 element above it, it needs 1 swap, remove it from array
* 4 3 2 : 2 has 2 elements before it, it needs 2 swaps
* 4 3 : 4 needs 1 swap
* 
END ANNOTATION
*/

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

typedef pair<int, int> pii;

int N;
int arr[100000];
vector<pii> v;

typedef struct TreeNode{
	TreeNode *l, *r;
	int b, e;
	int v;
} Node;

Node* newNode(){
	Node *x = new Node();
	x->l = x->r = NULL;
	return x;
}

void add(Node *n, int ind, int x){
	if(ind < n->b || ind > n->e) return;
	if(n->b == n->e) {
		n->v+=x;
		return;
	}
	int m = (n->b+n->e)/2;
	if(!n->l) {
		n->l = newNode();
		n->l->b = n->b;
		n->l->e = m;
		
	}
	if(!n->r) {
		n->r = newNode();
		n->r->b = m+1;
		n->r->e = n->e;
	}
	add(n->l, ind, x);
	add(n->r, ind, x);
	n->v = n->l->v+n->r->v;
}

int getSum(Node *n, int l, int r){
	if(!n || r < n->b || l > n->e) return 0;
	if(l <= n->b && r >= n->e) return n->v;
	return getSum(n->l, l, r)+getSum(n->r, l, r);
	
}

Node* root;
int main(){
	cin >> N;
	root = newNode();
	root->b = 0;
	root->e = N-1;
	for(int i = 0; i < N; i++){
		cin >> arr[i];
		add(root, i, 1);
		v.push_back(make_pair(arr[i], i));
	}
	sort(v.begin(), v.end());
	
	int l = 0;
	int r = N-1;
	while(l < r){
		add(root, v[l].second, -1);
		cout << getSum(root, 0, v[l].second) << endl;
		add(root, v[r].second, -1);
		cout << getSum(root, v[r].second, N-1) << endl;
		l++; r--;
	}
	if(l == r) cout << "0\n";
	
	return 0;
}
