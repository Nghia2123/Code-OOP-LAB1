#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include <regex>
using namespace std;

// Struct de luu thong tin chuyen bay
struct ChuyenBay {
    string maChuyenBay;
    string ngayBay; // Dinh dang: yyyy-mm-dd
    string gioBay;  // Dinh dang: HH:MM
    string noiDi;
    string noiDen;
};

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

/* Kiem tra tinh hop le cua ma chuyen bay
(toi da 5 ky tu, khong khoang trang hoac ky tu dac biet)*/
bool kiemTraMaChuyenBay(const string& ma) {
    return regex_match(ma, regex("^[a-zA-Z0-9]{1,5}$"));
}

// Kiem tra tinh hop le cua ngay bay (dinh dang dd-mm-yyyy)
bool kiemTraNgayBay(const string& tdiem) {
	bool check = regex_match(tdiem, 
            regex("((0[1-9]|[12][0-9]|3[01])-(0[1-9]|1[0-2])-(19|20)[0-9]{2})"));
	string ngay, thang, nam;
	ngay = tdiem.substr(0, 2);
	thang = tdiem.substr(3, 2);
	nam = tdiem.substr(6, 4);
	if (check) {
		int ngayInt = stoi(ngay);
		int thangInt = stoi(thang);
		int namInt = stoi(nam);
		return ngayInt <= ngayTrongThang(thangInt, namInt);
	}
	return false;
}

// Kiem tra tinh hop le cua gio bay (dinh dang HH:MM)
bool kiemTraGioBay(const string& gio) {
    return regex_match(gio, regex("^(0[0-9]|1[0-9]|2[0-3]):[0-5][0-9]$"));
}

/*Kiem tra tinh hop le cua ten dia danh
(toi da 20 ky tu, khong so hoac ky tu dac biet)*/
bool kiemTraDiaDanh(const string& diaDanh) {
    if (regex_match(diaDanh, regex("^[a-zA-Z ]{1,20}$"))) {
        if (diaDanh.find("  ") != string::npos) {
			return false;
		}

		size_t b = 0;
		size_t k = diaDanh.find(' ');

        if (diaDanh[0] == 'T' && (diaDanh[1] == 'P' || diaDanh[1] == 'p')) {
            b = 3;
            k = diaDanh.find(' ', b);
        }

		while (b <= diaDanh.rfind(' ') + 1) {
			if (diaDanh[b] < 'A' || diaDanh[b] > 'Z') {
				return false;
			}

			if (k == string::npos) k = diaDanh.length();

			for (b = b + 1; b < k; b++)
				if (diaDanh[b] < 'a' || diaDanh[b] > 'z') {
					return false;
				}

			b = k + 1;
			k = diaDanh.find(' ', b);
		}

		return true;
	}
    return false;
}

// Ham nhap thong tin cho mot chuyen bay
void nhapChuyenBay(ChuyenBay& cb) {
    do {
        cout << "Nhap ma chuyen bay (toi da 5 ky tu): ";
        cin >> cb.maChuyenBay;
        if (!kiemTraMaChuyenBay(cb.maChuyenBay)) {
            cout << "Ma chuyen bay khong hop le. Vui long nhap lai!" << endl;
        }
    } while (!kiemTraMaChuyenBay(cb.maChuyenBay));

    do {
        cout << "Nhap ngay bay (dd-mm-yyyy): ";
        cin >> cb.ngayBay;
        if (!kiemTraNgayBay(cb.ngayBay)) {
            cout << "Ngay bay khong hop le. Vui long nhap lai!" << endl;
        }
    } while (!kiemTraNgayBay(cb.ngayBay));

    do {
        cout << "Nhap gio bay (HH:MM): ";
        cin >> cb.gioBay;
        if (!kiemTraGioBay(cb.gioBay)) {
            cout << "Gio bay khong hop le. Vui long nhap lai!" << endl;
        }
    } while (!kiemTraGioBay(cb.gioBay));

    cin.ignore(); // Bo qua ky tu xuong dong con lai trong bo dem

    do {
        cout << "Nhap noi di: ";
        getline(cin, cb.noiDi);
        if (!kiemTraDiaDanh(cb.noiDi)) {
            cout << "Noi di khong hop le. Vui long nhap lai!" << endl;
        }
    } while (!kiemTraDiaDanh(cb.noiDi));

    do {
        cout << "Nhap noi den: ";
        getline(cin, cb.noiDen);
        if (!kiemTraDiaDanh(cb.noiDen)) {
            cout << "Noi den khong hop le. Vui long nhap lai!" << endl;
        }
    } while (!kiemTraDiaDanh(cb.noiDen));
	
}

// Ham xuat thong tin mot chuyen bay
void xuatChuyenBay(const ChuyenBay& cb) {
    cout << "Ma chuyen bay: " << cb.maChuyenBay << endl;
    cout << "Ngay bay: " << cb.ngayBay << endl;
    cout << "Gio bay: " << cb.gioBay << endl;
    cout << "Noi di: " << cb.noiDi << endl;
    cout << "Noi den: " << cb.noiDen << endl;
    cout << "-----------------------------" << endl;
}

// Ham tim kiem chuyen bay theo ma, noi di hoac noi den
bool timKiemChuyenBay(const vector<ChuyenBay>& ds, const string& key, const int& select) {
    bool found = false;
    for (const auto& cb : ds) {
        if (select == 3 && cb.maChuyenBay == key) {
			xuatChuyenBay(cb);
			found = true;
		}
		else if (select == 4 && cb.noiDi == key) {
			xuatChuyenBay(cb);
			found = true;
		}
		else if (select == 5 && cb.noiDen == key) {
			xuatChuyenBay(cb);
			found = true;
        }
    }
    return found;
}

// Ham sap xep danh sach chuyen bay theo ngay va gio khoi hanh
void sapXepChuyenBay(vector<ChuyenBay>& ds) {
    sort(ds.begin(), ds.end(), [](const ChuyenBay& a, const ChuyenBay& b) {
        if (a.ngayBay == b.ngayBay) {
            return a.gioBay < b.gioBay;
        }
        return a.ngayBay < b.ngayBay;
        });
}

/*Hien thi danh sach tat ca cac chuyen bay khoi hanh
tu mot noi cu the trong mot ngay duoc chi dinh*/
void hthiCBayTheoNoiDi(const vector<ChuyenBay>& ds, 
                        const string& noiDi, const string& ngay) {
    bool found = false;
    for (const auto& cb : ds) {
        if (cb.noiDi == noiDi && cb.ngayBay == ngay) {
            xuatChuyenBay(cb);
            found = true;
        }
    }
    if (!found) {
        cout << "Khong co chuyen bay nao khoi hanh tu " << noiDi << 
                " vao ngay " << ngay << endl;
    }
}

// Dem so luong chuyen bay tu mot noi di den mot noi den nhat dinh
int demChuyenBay(const vector<ChuyenBay>& ds, 
                    const string& noiDi, const string& noiDen) {
    int count = 0;
    for (const auto& cb : ds) {
        if (cb.noiDi == noiDi && cb.noiDen == noiDen) {
            count++;
        }
    }
    return count;
}

void menu() {
    cout << "\n=== CHUONG TRINH QUAN LY CHUYEN BAY ===\n";
    cout << "1. Nhap thong tin cac chuyen bay\n";
    cout << "2. Xuat danh sach chuyen bay\n";
    cout << "3. Tim kiem chuyen bay theo ma chuyen bay\n";
    cout << "4. Tim kiem chuyen bay theo noi di\n";
    cout << "5. Tim kiem chuyen bay theo noi den\n";
    cout << "6. Liet ke chuyen bay theo noi di va ngay\n";
    cout << "7. Dem chuyen bay theo noi di va noi den\n";
    cout << "0. Thoat\n";
}

int main() {
    vector<ChuyenBay> danhSachChuyenBay;
    int luaChon;

    // Vi du chi tiet
    // Gia su ban co danh sach cac chuyen bay voi thong tin day du, chuong trinh can:
    // - Kiem tra xem ma chuyen bay "VN123" co ton tai khong.
    // - Sap xep danh sach cac chuyen bay theo ngay gio khoi hanh.
    // - Liet ke tat ca cac chuyen bay khoi hanh tu "Ha Noi" vao ngay 01/01/2024.
    // - Dem so chuyen bay tu "Ha Noi" den "TP. Ho Chi Minh".
    
    do {
        menu();
        cout << "Nhap lua chon: ";
        cin >> luaChon; cout << '\n';
        cin.ignore();
        switch (luaChon) {
            case 1: {
                cout << "Nhap so luong chuyen bay: ";
                int soLuong;
                cin >> soLuong;

                // Nhap thong tin chi tiet cho moi chuyen bay
                for (int i = 0; i < soLuong; i++) {
                    ChuyenBay cb;
                    cout << "\nNhap thong tin cho chuyen bay thu " << i + 1 << endl;
                    nhapChuyenBay(cb);
                    danhSachChuyenBay.push_back(cb);
                }
				sapXepChuyenBay(danhSachChuyenBay);
                break;
            }

            case 2: {
                for (const auto& cb : danhSachChuyenBay) {
                    xuatChuyenBay(cb);
                }
                break;
            }

            case 3: {
                string maChuyenBay;
                cout << "Nhap ma chuyen bay can tim: ";
				getline(cin, maChuyenBay);
                if (!timKiemChuyenBay(danhSachChuyenBay, maChuyenBay, luaChon)) {
                    cout << "Khong tim thay ma chuyen bay '" << maChuyenBay << "'." << endl;
                }
                break;
            }

            case 4: {
                string noiDi;
                cout << "Nhap noi di can tim: ";
				getline(cin, noiDi);
                if (!timKiemChuyenBay(danhSachChuyenBay, noiDi, luaChon)) {
                    cout << "Khong tim thay noi di '" << noiDi << "'." << endl;
                }
                break;
            }

            case 5: {
                string noiDen;
                cout << "Nhap noi den can tim: ";
                getline(cin, noiDen);
                if (!timKiemChuyenBay(danhSachChuyenBay, noiDen, luaChon)) {
                    cout << "Khong tim thay noi den '" << noiDen << "'." << endl;
                }
                break;
            }

            case 6: {
                string noiDi, ngay;
                cout << "Nhap noi di: ";
                getline(cin, noiDi);
                cout << "Nhap ngay (dd-mm-yyyy): ";
				getline(cin, ngay);
                hthiCBayTheoNoiDi(danhSachChuyenBay, noiDi, ngay);
                break;
            }

            case 7: {
                string noiDi, noiDen;
                cout << "Nhap noi di: ";
				getline(cin, noiDi);
                cout << "Nhap noi den: ";
				getline(cin, noiDen);
                int soChuyen = demChuyenBay(danhSachChuyenBay, noiDi, noiDen);
                cout << "So luong chuyen bay tu '" << noiDi << "' den '" << noiDen << "': " << soChuyen << endl;
                break;
            }

            case 0: {
                cout << "Ket thuc chuong trinh." << endl;
                break;
            }
        }
    } while (luaChon != 0);
 
    return 0;
}
