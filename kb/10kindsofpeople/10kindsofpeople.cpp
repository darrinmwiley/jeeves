/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/10kindsofpeople
TAGS: disjoint set, union find, union, find, grid
EXPLANATION:
Creates a union find structure where each set represents a zone.
Checks whether each query has two points from the same zone, and if so, what type.
END ANNOTATION
*/
#include <iostream>
#include <vector>

using namespace std;

// A single node in the Disjoint Set.
struct Node
{
	Node* parent;
	unsigned rank;
};

// A Disjoint Set Structure
struct DisjointSet
{
	// The input map
	vector<vector<bool>> mat;

	// All nodes
	vector<vector<Node>> nodes;

	// Returns the root node of the tree containing node x.
	inline Node* Find(Node* x)
	{
		if (x->parent)
		{
			x->parent = Find(x->parent);
			return x->parent;
		}
		return x;
	}

	// Returns the root node of the set containing the node at (i, j)
	inline Node* Find(unsigned i, unsigned j)
	{
		return Find(&nodes[i][j]);
	}

	// Combines the sets to which node x and node y belong
	inline void Union(Node* x, Node* y)
	{
		x = Find(x);
		y = Find(y);
		if (x == y) return;
		if (x->rank < y->rank)
		{
			Node* temp = x;
			x = y;
			y = temp;
		}
		y->parent = x;
		if (x->rank == y->rank) x->rank++;
	}

	// Combines the sets to which the node at (xi, xj) and the node at (yi, yj) belong
	inline void Union(unsigned xi, unsigned xj, unsigned yi, unsigned yj)
	{
		Union(&nodes[xi][xj], &nodes[yi][yj]);
	}

	// Reads the input map and builds the Disjoint Set
	inline DisjointSet(unsigned r, unsigned c) :
		mat(r, vector<bool>(c)),
		nodes(r, vector<Node>(c, Node{ nullptr, 0 }))
	{
		// Reads the map into this->mat
		{
			string str;
			for (unsigned i = 0; i < r; i++)
			{
				cin >> str;
				for (unsigned j = 0; j < c; j++)
					mat[i][j] = str[j] == '1';
			}
		}

		// Merges nodes from the same zone in the leftmost column
		for (unsigned i = 1; i < r; i++)
			if (mat[i][0] == mat[i - 1][0])
				Union(i, 0, i - 1, 0);

		// Merges nodes from the same zone in the topmost row
		for (unsigned j = 1; j < c; j++)
			if (mat[0][j] == mat[0][j - 1])
				Union(0, j, 0, j - 1);

		// Merges nodes from the same zone for the rest of the map
		for (unsigned i = 1; i < r; i++)
			for (unsigned j = 1; j < c; j++)
			{
				if (mat[i][j] == mat[i - 1][j])
					Union(i, j, i - 1, j);
				if (mat[i][j] == mat[i][j - 1])
					Union(i, j, i, j - 1);
			}
	}
};

int main()
{
	// Reads input to create the disjoint set for the map.
	unsigned r, c;
	cin >> r >> c;
	DisjointSet ds(r, c);

	// Processes n queries
	unsigned n;
	cin >> n;
	unsigned r1, c1, r2, c2;
	for (unsigned i = 0; i < n; i++)
	{
		// Reads r1, c1, r2, and c1. Makes them 0-indexed
		cin >> r1 >> c1 >> r2 >> c2;
		r1--;
		c1--;
		r2--;
		c2--;

		// If they are in the same zone, prints the type of zone; prints neither otherwise.
		if (ds.Find(r1, c1) == ds.Find(r2, c2))
			cout << (ds.mat[r1][c1] ? "decimal" : "binary");
		else
			cout << "neither";
		cout << endl;
	}

	return 0;
}