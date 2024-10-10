#include <iostream>
#include <numeric>
#include <algorithm>
using namespace std;
//Ham gcd de tim uoc chung lon nhat cua 2 so
int gcd(int a, int b) {
	if (b == 0) return a;
	return gcd(b, a % b);
}
//Ham rutGon() de rut gon phan so
void rutGon(int& tu, int& mau) {
	int ucln = gcd(tu, mau);
	tu /= ucln;
	mau /= ucln;
	if (mau < 0) {
		tu = -tu;
		mau = -mau;
	}	
}
int main() {
	int tu, mau;
	cout << "Nhap phan so\n";
	cout << "+ Nhap tu so: "; cin >> tu;
	cout << "+ Nhap mau so: "; cin >> mau;
	while (mau == 0) {
		cout << "+ Mau so phai khac 0. Nhap lai mau so: ";
		cin >> mau;
	}
	rutGon(tu, mau);
	cout << "Phan so sau khi rut gon: ";
	if (mau == 1 || tu == 0) cout << tu << '\n';
	else cout << tu << "/" << mau << '\n';
}
