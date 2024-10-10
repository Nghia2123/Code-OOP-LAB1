#include <iostream>
#include <cmath>
using namespace std;

int n = 0;

/* Ham tinh sin theo cong thuc: 
sin(x) = x - x ^ 3 / 3!+ x ^ 5 / 5!- x ^ 7 / 7!+ ...*/
double hamSin(double x) {
	double sinx = 0;

	double t = x; 
	while (abs(t) >= 0.00001) {
		sinx += t;
		n++;
		t = pow(-1, n) * pow(x, 2*n+1) / tgamma(2*n+2); // tinh t theo cong thuc
	}
	
	return sinx;
}

int main() {
	double x;
	cout << "Nhap x (dang radian): "; cin >> x;
	cout << "sin("<<x<<") = " << hamSin(x);
}	