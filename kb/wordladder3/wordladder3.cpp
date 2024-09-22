/*
BEGIN ANNOTATION
PROBLEM URL: https://open.kattis.com/problems/wordladder3
TAGS: partitions
EXPLANATION:
Partition a string of a's into pairs and change them like incrementing a 5 digit base 26 number. Changing a pair from one state is two steps and can be cut off.
There are 26^4 * 2 words at most in the ladder this way
END ANNOTATION
*/


#include <iostream>

using namespace std;

int c[10], f[10];

int main(){
	int n;
	cin>>n;
	string x = "aaaaaaaaaa";
	cout<<x<<endl;
  n--;
	while(n){
    int j = 0;
    while(c[j]>24) j+=2;
    if((f[j]&&x[j]=='a')||(!f[j]&&x[j]!='z')){
      x[j]++;
      cout<<x<<endl;
      n--;
      f[j]=false;
      if(n){
        x[j+1]++;
        cout<<x<<endl;
        n--;
      }
    }
    else{
      x[j]--;
      cout<<x<<endl;
      n--;
      f[j]=true;
      if(n){
        x[j+1]--;
        cout<<x<<endl;
        n--;
      }
    }
    for(int k = 0; k<j; k++) c[k]=0;
    c[j]++;
	}
	
}