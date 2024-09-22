/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/thanosthehero
TAGS: Loops, array
EXPLANATION:
Creates a list with all of the worlds and iterates
backwards, adding to kills the number that must be taken from
the current index to make it less than the next world,
if the next world is ever equal to zero, break the loop and output 1
END ANNOTATION
*/

#include <iostream>
using namespace std;
int main() {
  long count,index,kills=0;
  cin>>count;
  int worlds[count];
  index=count-2;
  for(int i=0;i<count;i++){
    cin>>worlds[i];
  }
  while(index>=0){
    if(worlds[index+1]==0){
      kills=1;
      break;
    }
    if(worlds[index]>=worlds[index+1]){
      kills+=worlds[index]-(worlds[index+1]-1);
      worlds[index]=worlds[index+1]-1;
    }
    index--;
  }
  cout<<kills;
}