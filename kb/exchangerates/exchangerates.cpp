/*
BEGIN ANNOTATION
PROBLEM URL: https://open.kattis.com/problems/exchangerates
TAGS: math
EXPLANATION: 
to solve I kept track of the largest amount of US and CAN dollars you can have at the end of any day
the largest amount of any currency possible on any day is the
  max (prevMax, exchangeRateOtherToThis * 0.97 * otherCurrencyPrevMax)
END ANNOTATION
*/
# include <iostream>
# include <cmath>
# include <iomanip>
using namespace std;

int main() {
	int d;
	cin >> d;
	while (d != 0) {
		double maxCAN = 1000.00, maxUS = 0;
		for(int i = 0; i < d; i++) {

			double exchUStoCAN;
			cin >> exchUStoCAN;
			double exchCANtoUS = 1 / exchUStoCAN;
			// convert maximum number of US dollars we can have to CAN dollars (97 is .97 * 100 for rounding)
			double CAN = floor(maxUS * exchUStoCAN * 97) / 100;
			if(CAN > maxCAN) {
				maxCAN = CAN;
			}
			// convert maximum number of CAN dollars we can have to US dollars (97 is .97 * 100 for rounding) 
			double US = floor(maxCAN * exchCANtoUS * 97) / 100;
			if(US > maxUS) {
				maxUS = US;
			}
		}

		// print out with 2 decimal places
		cout << fixed << setprecision(2) << maxCAN << endl;
		cin >> d;
	}
}