/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/grassseed
TAGS: GrassSeed, Seed, Grass
EXPLANATION:
- Make cost, numLawns, and TotalCost variables of double number type and set them to zero
- Read in cost and numLawns
- loop from 1 to numLawns
- Within the loop, make width, length, and lawnAreaCost variables of double number type and set them to zero
- Read in width and length
- Set lawnAreaCost to (width * length) * cost
- Add lawnAreaCost to totalCost
- Output totalCost
END ANNOTATION
*/

#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
    double cost, numLawns;
    cin >> cost >> numLawns;
    
    double totalCost = 0;
    
    for(int i = 0; i < numLawns; i++){
        double width, length, lawnArea = 0;
        cin >> width >> length;
        
        lawnArea = (width * length) * cost;
        
        totalCost += lawnArea;
    }
    
    cout << fixed << setprecision(7) << totalCost;
   return 0;
}