/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/fizzbuzz
TAGS: FizzBuzz, Fizz, Buzz
EXPLANATION:
Read X, Y and N
Make for loop starting from 1 to N
Check if reminder of i / X and i / Y == 0
Output FizzBuzz, Fizz, or Buzz
If i is not divisible by X or Y, display i
END ANNOTATION
*/

#include <iostream>

using namespace std;

int main()
{
    int x, y, n;
    cin >> x >> y >> n;
    
    for(int i = 1; i <= n; i++){
        if(i % x == 0 && i % y ==0){
            cout << "FizzBuzz" <<endl;
        }else if(i % x ==0){
            cout << "Fizz"<<endl;
        }else if(i % y == 0){
            cout << "Buzz" <<endl;
        }else{
            cout << i <<endl;
        }
    }
   
   return 0;
}