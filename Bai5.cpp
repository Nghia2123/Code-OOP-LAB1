#include <iostream>
using namespace std;

// Ham kiem tra nam nhuan
bool laNamNhuan(int nam) {
	return (nam % 4 == 0 && nam % 100 != 0) || (nam % 400 == 0);
}

// Ham tinh so ngay trong thang
int ngayTrongThang(int thang, int nam) {
	if (thang == 2) {
		return laNamNhuan(nam) ? 29 : 28;
	}
	if (thang == 4 || thang == 6 || thang == 9 || thang == 11) {
		return 30;
	}
	return 31;
}

// Ham tinh ngay ke tiep
void ngayKeTiep(int ngay, int thang, int nam) {
	ngay++;
	if (ngay > ngayTrongThang(thang, nam)) {
		ngay = 1;
		thang++;
		if (thang > 12) {
			thang = 1;
			nam++;
		}
	}
	cout << "Ngay ke tiep la: " 
		<< ngay << "/" << thang << "/" << nam << '\n';
}

// Ham tinh ngay truoc do
void ngayTruoc(int ngay, int thang, int nam) {
	ngay--;
	if (ngay < 1) {
		thang--;
		if (thang < 1) {
			thang = 12;
			nam--;
		}
		ngay = ngayTrongThang(thang, nam);
	}
	cout << "Ngay truoc do la: " 
		<< ngay << "/" << thang << "/" << nam << '\n';
}

// Ham tinh ngay thu bao nhieu trong nam
void ngayTrongNam(int ngay, int thang, int nam) {
	int demNgay = 0;
	for (int t = 1; t < thang; t++) {
		demNgay += ngayTrongThang(t, nam);
	}
	demNgay += ngay;
	cout << "Ngay nay la ngay thu " 
		<< demNgay << " trong nam." << '\n'; 
}

int main() {
	int ngay, thang, nam;
	do {
		cout << "Nhap ngay: "; cin >> ngay;
		cout << "Nhap thang: "; cin >> thang;
		cout << "Nhap nam: "; cin >> nam;
		if (ngay < 1 || ngay > 31 || thang < 1 
			|| thang > 12 || nam < 1 || 
				ngay > ngayTrongThang(thang, nam)) {
			cout << 
			"Ngay thang nam khong hop le. Vui long nhap lai!" << "\n\n";
		}
	} while (ngay < 1 || ngay > 31 || thang < 1 
			|| thang > 12 || nam < 1 || 
				ngay > ngayTrongThang(thang, nam));
	
	ngayKeTiep(ngay, thang, nam);
	ngayTruoc(ngay, thang, nam);
	ngayTrongNam(ngay, thang, nam);
}
