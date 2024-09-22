/*
BEGIN ANNOTATION
PROBLEM URL: https://open.kattis.com/problems/evolution
TAGS: vectors, sorting
EXPLANATION:
Sort input by length and then alphabetical order and attempt to split all the strings into two distinct genetic chains.
 Processes strings starting from the longest and iterates down the list. Two lists are used for each chain in case
 two smaller strings may fit into a larger one e.g. {CCMM, ACCA, AA, CC} could produce ACCA->AA || ACCA->CC but CCMM can
 only produce CCMM -> CC. Index variables i, j, ii, and jj keep track of the number of strings in each vector A, B, C, D
 respectively. Vectors A and C hold first chain possibilities and vectors B and D hold second chain possibilities.
 Whichever two add up to n hold the correct chains.
END ANNOTATION
*/

#include <iostream>
#include <string>
#include <bits/stdc++.h>
#include "stdio.h"
using namespace std;

vector<pair<int,string>> sortList(string listA[], int a_ctr) {
    vector<pair<int,string>> newA;
    for(int i = 0; i < a_ctr; i++)
        newA.push_back(make_pair(listA[i].length(),listA[i]));
    sort(newA.begin(), newA.end());

    return newA;
}

//b is smaller than a
bool canSequence(string a, string b) {
    string test = a;
    int testIdx = 0;
    for(int j = 0; j < b.length(); j++) {
        char letter = b.at(j);
        testIdx = test.find(letter);
        if (testIdx < 0)
            return 0;
        test = test.substr(testIdx + 1);
    }
    return 1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    //=================================================================================
    //read in data
    int numElements = 1;
    string primary;

    cin >> numElements;
    string sequences[numElements];

    cin >> primary;

    int len[numElements];
    for (int i = 0; i < numElements; i++) {
        //read into arr
        cin >> sequences[i];
        len[i] = sequences[i].length();
    }
    //=================================================================================

    //=================================================================================
    //make two genetic chains
    vector<pair<int, string>> sorted_seq;
    sorted_seq = sortList(sequences, numElements);
    vector<int> sets(4000, 0);
    vector<string> listA(numElements), listB(numElements), listC(numElements), listD(numElements);

    //count string sizes
    int biggest = 0;
    if (numElements == 1) {
        if (!canSequence(primary, sorted_seq[0].second)) {
            printf("impossible");
            return 0;
        }
    } else {
        for (int i = 0; i < numElements; i++) {
            int n = sorted_seq[i].first;
            string n_str = sorted_seq[i].second;
            sets[n]++;
            if (n > biggest)
                biggest = n;
        }
    }

    //check if there are more than 3 strings of any length
    for (int i = 0; i <= biggest; i++) {
        if (sets[i] > 3 || i == primary.length()) {
            printf("impossible");
            return 0;
        }
    }

    //try to create two full chains
    int i = 0, j = 0, ii = 0, jj = 0;
    for (int k = numElements - 1; k >= 0; k--) {
        bool tst = false;
        string tmp = sorted_seq[k].second;
        if (i == 0) {
            if (!canSequence(primary, tmp)) {
                printf("impossible");
                return 0;
            }
            listA[i] = tmp;
            i++;
            listC[ii] = tmp;
            ii++;
            continue;
        }
        if (listA[i - 1].length() > tmp.length() && canSequence(listA[i - 1], tmp)) {
            listA[i] = tmp;
            i++;
            if (canSequence(listC[ii - 1], tmp)) {
                listC[ii] = tmp;
                ii++;
            }
            continue;
        }
        if (listA[i - 1].length() == tmp.length() && (ii - 1 > 0 && canSequence(listC[ii - 2], tmp))) {
            if (jj > 0 && canSequence(listD[jj-1], listA[i-1])) {
                listD[jj] = listA[i-1];
                jj++;
                listA[i-1] = tmp;
                listC[ii-1] = tmp;
                continue;
            }
        }
        if (j == 0) {
            if (!canSequence(primary, tmp)) {
                printf("impossible");
                return 0;
            }
            listB[j] = tmp;
            j++;
            listD[jj] = tmp;
            jj++;
            continue;
        }
        if (listB[j - 1].length() > tmp.length()) {
            bool temp = false;
            if (canSequence(listB[j - 1], tmp)) {
                listB[j] = tmp;
                j++;
                temp = true;
            }
            if (canSequence(listD[jj - 1], tmp)) {
                listD[jj] = tmp;
                jj++;
                continue;
            }
            if (temp) {
                continue;
            }
            else {
                printf("impossible");
                return 0;
            }
        }
        if (!tst) {
            printf("impossible");
            return 0;
        }
    }

    if (i+j == numElements) {
        printf("%d %d", i, j);
        for (int k = i-1; k >= 0; k--) {
            printf("\n%s", listA[k].c_str());
        }
        for(int k = j-1; k >= 0; k--) {
            printf("\n%s",listB[k].c_str());
        }
        return 0;
    }
    if (i+jj == numElements) {
        printf("%d %d", i, jj);
        for (int k = i-1; k >= 0; k--) {
            printf("\n%s", listA[k].c_str());
        }
        for(int k = jj-1; k >= 0; k--) {
            printf("\n%s",listD[k].c_str());
        }
        return 0;
    }
    if (ii+j == numElements) {
        printf("%d %d", ii, j);
        for (int k = ii-1; k >= 0; k--) {
            printf("\n%s", listC[k].c_str());
        }
        for(int k = j-1; k >= 0; k--) {
            printf("\n%s",listB[k].c_str());
        }
        return 0;
    }
    if (ii+jj == numElements) {
        printf("%d %d", ii, jj);
        for (int k = ii-1; k >= 0; k--) {
            printf("\n%s", listC[k].c_str());
        }
        for(int k = jj-1; k >= 0; k--) {
            printf("\n%s",listD[k].c_str());
        }
        return 0;
    }

    printf("impossible");
    return 0;
    //=================================================================================
}