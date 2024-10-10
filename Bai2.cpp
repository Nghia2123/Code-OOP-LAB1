#include <iostream>
using namespace std;

// Ham xuat phan so
void xuatPhanSo(int tu, int mau) {
	cout << tu << '/' << mau << '\n';
}
// Ham so sanh 2 phan so
void soSanhPhanSo(int tu1, int mau1, int tu2, int mau2) {
	//Dao dau neu mau so am
	if (mau1 < 0) {
		tu1 = -tu1;
		mau1 = -mau1;
	}

	if (mau2 < 0) {
		tu2 = -tu2;
		mau2 = -mau2;
	}

	int tTu1 = tu1 * mau2;
	int tTu2 = tu2 * mau1;

	//So sanh
	if (tTu1 > tTu2) {
		cout << "Phan so lon hon la: ";
		xuatPhanSo(tu1, mau1);
	}
	else if (tTu1 < tTu2) {
		cout << "Phan so lon hon la: ";
		xuatPhanSo(tu2, mau2);
	}
	else 
		cout << "Hai phan so bang nhau\n";
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

	soSanhPhanSo(tu1, mau1, tu2, mau2);
}