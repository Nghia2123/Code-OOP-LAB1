#include <iostream>
using namespace std;

// Tim uoc chung lon nhat cua 2 so
int gcd(int a, int b) {
	if (b == 0) return a;
	return gcd(b, a%b);
}

// Rut gon phan so
void rutGonPhanSo(int& tu, int& mau) {
	int UC = gcd(tu, mau);
	tu /= UC;
	mau /= UC;
	
	if (mau < 0) {
		tu = -tu;
		mau = -mau;
	}
}

// Xuat phan so theo dang 
void xuatPhanSo(int tu, int mau) {
	if (mau == 1 || tu == 0) cout << tu << '\n';
	else cout << tu << "/" << mau << '\n';
}

// Tinh tong, hieu, tich, thuong 2 phan so va xuat ket qua
void xuatKetQua(int tu1, int mau1, int tu2, int mau2) {
	int tTu, tMau;

	tTu = tu1 * mau2 + tu2 * mau1;
	tMau = mau1 * mau2;
	rutGonPhanSo(tTu, tMau);
	cout << "Tong 2 phan so: "; xuatPhanSo(tTu, tMau);

	tTu = tu1 * mau2 - tu2 * mau1;
	tMau = mau1 * mau2;
	rutGonPhanSo(tTu, tMau);
	cout << "Hieu 2 phan so: "; xuatPhanSo(tTu, tMau);

	tTu = tu1 * tu2;
	tMau = mau1 * mau2;
	rutGonPhanSo(tTu, tMau);
	cout << "Tich 2 phan so: "; xuatPhanSo(tTu, tMau);

	tTu = tu1 * mau2;
	tMau = mau1 * tu2;
	rutGonPhanSo(tTu, tMau);
	cout << "Thuong 2 phan so: "; xuatPhanSo(tTu, tMau);
}

int main() {
	int tu1, mau1, tu2, mau2;
	cout << "Nhap phan so thu nhat\n";
	cout << "+ Nhap tu so: "; cin >> tu1;
	cout << "+ Nhap mau so: "; cin >> mau1;
	if (mau1 == 0) {
		cout << "Mau so phai khac 0, nhap lai mau so: "; cin >> mau1;
	}
	cout << '\n';

	cout << "Nhap phan so thu hai\n";
	cout << "+ Nhap tu so: "; cin >> tu2;
	cout << "+ Nhap mau so: "; cin >> mau2;
	if (mau2 == 0) {
		cout << "Mau so phai khac 0, nhap lai mau so: "; cin >> mau2;
	}
	cout << '\n';

	xuatKetQua(tu1, mau1, tu2, mau2);
}