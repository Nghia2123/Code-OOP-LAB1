#include <iostream>
#include <string>
#include <istream>
using namespace std;

struct HocSinh {
	string hoTen = "";
	double diemToan = 0, diemVan = 0, diemNgoaiNgu = 0;
	
	void xuatThongTin() {
		cout << "Ho ten: " << hoTen << '\n';
		cout << "Diem toan: " << diemToan << '\n';
		cout << "Diem van: " << diemVan << '\n';
		cout << "Diem ngoai ngu: " << diemNgoaiNgu << '\n';
	}
};

struct QLHocSinh {
	int n;
	HocSinh *ds;

	bool co1TuTrongHoTen(const std::string& hoten) {
		int wordCount = 0;
		bool inWord = false;

		for (char c : hoten) {
			// Kiem tra ki tu khong phai la khoang trang
			if (c != ' ') {
				if (!inWord) {
					inWord = true;  // Bat dau mot tu moi
					wordCount++;
				}
			}
			else {
				inWord = false;  // Ket thuc tu
			}

			// Neu co 2 tu, tra ve true
			if (wordCount >= 2) {
				return true;
			}
		}

		return false;  // Khong co du 2 tu
	}

	bool ktraHoTenHopLe(string ten) {
		if (ten.find("  ") != string::npos) {
			return false;
		}

		size_t b = 0;
		size_t k = ten.find(' ');

		while (b <= ten.rfind(' ') + 1) {
			if (ten[b] < 'A' || ten[b] > 'Z') {
				return false;
			}

			if (k == string::npos) k = ten.length();

			for (b = b + 1; b < k; b++)
				if (ten[b] < 'a' || ten[b] > 'z') {
					return false;
				}

			b = k + 1;
			k = ten.find(' ', b);
		}

		return true;
	}

	void nhapThongTin(HocSinh& a, int i) {
		// Nhap ho ten
		cin.ignore();
		do {
			cout << "Nhap ho ten hoc sinh thu " << i << ": ";
			getline(cin, a.hoTen);
			if (a.hoTen.length() == 0) {
				cout << "Ho ten khong duoc de trong! Vui long nhap lai: \n\n";
				continue;
			}

			if (!co1TuTrongHoTen(a.hoTen)) {
				cout << "Ho ten phai co it nhat 2 tu! Vui long nhap lai: \n\n";
				continue;
			}

			if (ktraHoTenHopLe(a.hoTen)) break;
			else cout << "Sai dinh dang! Vui long nhap lai: \n\n";
		} while (true);

		// Nhap diem
		do {
			cout << "Nhap diem toan: ";
			cin >> a.diemToan;
			if (a.diemToan < 0 || a.diemToan > 10) {
				cout << "Diem toan phai nam trong khoang tu 0 den 10";
				cout <<"! Vui long nhap lai: ";
				cout << "\n\n";
				continue;
			}

			cout << "Nhap diem van: ";
			cin >> a.diemVan;
			if (a.diemVan < 0 || a.diemVan > 10) {
				cout << "Diem van phai nam trong khoang tu 0 den 10";
				cout <<"! Vui long nhap lai: ";
				cout << "\n\n";
				continue;
			}

			cout << "Nhap diem ngoai ngu: ";
			cin >> a.diemNgoaiNgu;
			if (a.diemNgoaiNgu < 0 || a.diemNgoaiNgu > 10) {
				cout << "Diem ngoai ngu phai nam trong khoang tu 0 den 10";
				cout <<"! Vui long nhap lai: ";
				cout << "\n\n";
				continue;
			}
			break;
		} while (true);
		cout << '\n';
	}

	void nhapDanhSach() {
		cout << "Nhap so luong hoc sinh: ";
		cin >> n;
		ds = new HocSinh[n];
		for (int i = 0; i < n; i++) 
			nhapThongTin(ds[i], i + 1);
	}

	double diemTB(HocSinh a) {
		return (a.diemToan * 2 + a.diemVan + a.diemNgoaiNgu) / 4;
	}

	void phanLoai(HocSinh a) {
		double TB = diemTB(a);
		if (TB >= 9) cout << "Xuat sac";
		else if (TB >= 8) cout << "Gioi";
		else if (TB >= 6.5) cout << "Kha";
		else if (TB >= 5) cout << "Trung binh";
		else cout << "Yeu";
		cout << "\n\n";
	}

	// Tim hoc sinh co diem trung binh cao nhat
	void diemTBCaoNhat() {
		double m = diemTB(ds[0]);
		int vt = 0;
		for (int i = 0; i < n; i++)
			if (diemTB(ds[i]) > m) {
				m = diemTB(ds[i]);
				vt = i;
			}
		cout << "Hoc sinh co diem trung binh cao nhat:\n";
		ds[vt].xuatThongTin();
		cout << "Diem trung binh: "; cout << diemTB(ds[vt]) << '\n';
		cout << "Hoc luc: "; phanLoai(ds[vt]);
	}

	// Tim hoc sinh theo ten
	void timHSTheoTen() {
		int dem = 0;
		string ten;

		cout << "Nhap ten hoc sinh can tim: "; getline(cin, ten);
		
		string temp = ten;
		for (char& c : ten) {
			c = std::tolower(c);
		}

		for (int i = 0; i < n; i++) {
			string hs = ds[i].hoTen;

			for (char& c : hs) {
				c = std::tolower(c);
			}

			if (hs.find(ten) != string::npos) {
				dem++;
			}
		}

		if (dem == 0) cout << "Khong tim thay hoc sinh nao co ten " << temp << '\n';
		else cout << "Tim thay " << dem << " hoc sinh co ten " << temp << '\n';

		cout << '\n';
	}

	// Danh sach hoc sinh co diem toan thap nhat
	void DSDiemToanThapNhat() {
		double m = ds[0].diemToan;
		for (int i = 0; i < n; i++)
			if (ds[i].diemToan < m) m = ds[i].diemToan;
		cout << "Diem toan thap nhat: " << m << '\n';
		cout << "Danh sach hoc sinh co diem toan thap nhat:\n";
		for (int i = 0; i < n; i++)
			if (ds[i].diemToan == m) cout << ds[i].hoTen << '\n';
	}
};

int main() {
	QLHocSinh a;
	a.nhapDanhSach();

	for (int i = 0; i < a.n; i++) {
		HocSinh hs = a.ds[i];
		cout << "Hoc sinh " << hs.hoTen << ":\n";
		cout << "+ " << "Diem trung binh: " << a.diemTB(hs) << '\n';
		cout << "+ "; a.phanLoai(hs); 
		cout << '\n';
	}

	a.diemTBCaoNhat();

	cin.ignore();
	a.timHSTheoTen();

	a.DSDiemToanThapNhat();
}