#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <ctime>
#include <cstdio>
#include <algorithm>
using namespace std;

// Struct bieu dien thong tin cua mot so tiet kiem
struct SoTietKiem {
    string maSo;        // Ma so (toi da 5 ky tu)
    string loaiTietKiem; // Loai tiet kiem (toi da 10 ky tu)
    string hoTenKH;     // Ho ten khach hang (toi da 30 ky tu)
    string cmnd;        // Chung minh nhan dan (9 hoac 12 so)
    tm ngayMoSo;        // Ngay mo so (ngay, thang, nam)
    double soTienGui;   // So tien gui (so duong)
    double laiSuat;     // Lai suat (%/nam)
	double thanggui;    // Thoi gian gui (thang)
};

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

//Kiem tra ho ten
bool ktraHoTenHopLe(string ten) {
        if (ten.empty()) return false;
        if (ten.length() > 30) return false;
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

// Kiem tra ma so hop le
bool kiemTraMaSo(const string& maSo) {
    if (maSo.empty()) return false;
    if (maSo.find(' ') != string::npos) return false;
    if (maSo.length() > 5) return false;
    for (char c : maSo) {
        if (!isalnum(c)) return false;
    }
    return true;
}

// Kiem tra loai tiet kiem hop le
bool kiemTraLoaiTietKiem(const string& loaiTietKiem) {
	if (loaiTietKiem.empty()) return false;
	if (loaiTietKiem.length() > 10) return false;
    if (loaiTietKiem != "ngan han" 
        && loaiTietKiem != "dai han" 
        && loaiTietKiem !="khongkyhan") return false; 
	return true;
}

// Kiem tra CMND hop le
bool kiemTraCMND(const string& cmnd) {
    if (cmnd.length() != 9 && cmnd.length() != 12) {
        return false;
    }
    
    for (char c : cmnd) 
        if (!isdigit(c)) return false;
    return true;
}

// Kiem tra ngay hop le
bool kiemTraNgayHopLe(int ngay, int thang, int nam) {
    if (nam < 1900 || nam > 2100 || thang < 1 || thang > 12 || ngay < 1) return false;
    int ngayTrongThang[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if ((nam % 4 == 0 && nam % 100 != 0) || nam % 400 == 0) 
        ngayTrongThang[1] = 29; // Nam nhuan
    return ngay <= ngayTrongThang[thang - 1];
}

// Nhap thong tin ngay
tm nhapNgay() {
    tm ngay;
    int ngayNhap, thangNhap, namNhap;
    do {
        cout << "Nhap ngay, thang, nam (dd mm yyyy): ";
        cin >> ngayNhap >> thangNhap >> namNhap;
        if (!kiemTraNgayHopLe(ngayNhap, thangNhap, namNhap)) 
            cout << "Ngay khong hop le. Vui long nhap lai.\n";
        else 
            break;
    } while (true);
    ngay.tm_mday = ngayNhap;
    ngay.tm_mon = thangNhap - 1; // tm_mon tinh tu 0
    ngay.tm_year = namNhap - 1900; // tm_year tinh tu 1900
    ngay.tm_hour = 0;
    ngay.tm_min = 0;    
    ngay.tm_sec = 0;
    return ngay;
}

// Nhap du lieu cho mot so tiet kiem
void nhapSoTietKiem(SoTietKiem& stk) {
    do {
        cout << "Nhap ma so: ";
        getline(cin, stk.maSo);
        if(!kiemTraMaSo(stk.maSo)) 
            cout << "Ma so khong hop le. Vui long nhap lai.\n";
        else 
            break;
    } while (true);

    do {
        cout << "Nhap loai tiet kiem (ngan han, dai han, khongkyhan): ";
        getline(cin, stk.loaiTietKiem);
		if (!kiemTraLoaiTietKiem(stk.loaiTietKiem))
			cout << "Loai tiet kiem khong hop le. Vui long nhap lai.\n";
		else
			break;
    } while (true);

	// Chon lai suat theo loai tiet kiem
	if (stk.loaiTietKiem == "ngan han")
		stk.laiSuat = 2.5;
	else if (stk.loaiTietKiem == "dai han")
		stk.laiSuat = 5;
	else
		stk.laiSuat = 1.2;

    do {
        cout << "Nhap ho ten khach hang: ";
        getline(cin, stk.hoTenKH);
        if (!co1TuTrongHoTen(stk.hoTenKH)){ 
            cout << "Ho ten phai co it nhat "
                <<"2 tu! Vui long nhap lai.\n";
            continue;
        }
        if(!ktraHoTenHopLe(stk.hoTenKH)) 
            cout << "Ho ten khong hop le. Vui long nhap lai.\n";
        else 
            break;
    } while (true);

    do {
        cout << "Nhap CMND (dung 9 hoac 12 so): ";
        getline(cin, stk.cmnd);
        if (!kiemTraCMND(stk.cmnd)) 
            cout << "CMND khong hop le. Vui long nhap lai.\n";
        else 
            break;
    } while (true);

    cout << "Nhap ngay mo so:\n";
    stk.ngayMoSo = nhapNgay();

    do {
        cout << "Nhap so tien gui: ";
        cin >> stk.soTienGui;
        if (stk.soTienGui <= 0) 
            cout << "So tien gui phai la so duong. Vui long nhap lai.\n";
    } while (stk.soTienGui <= 0);

    cout << '\n';
}

// Tinh so ngay giua hai ngay
int tinhSoNgayGiuaHaiNgay(const tm& ngay1, const tm& ngay2) {
    time_t t1 = mktime(const_cast<tm*>(&ngay1));
    time_t t2 = mktime(const_cast<tm*>(&ngay2));
    return static_cast<int>(difftime(t2, t1) / (60 * 60 * 24));;
}

// Tinh toan tien lai
double tinhTienLai(const SoTietKiem& stk) {
    time_t now = time(0);
    tm* ngayHienTai = localtime(&now);

    int soNgayGui = tinhSoNgayGiuaHaiNgay(stk.ngayMoSo, *ngayHienTai);
    double laiSuat = stk.laiSuat;

    double soTienLai = (stk.soTienGui * laiSuat * soNgayGui) / (365 * 100);
    return soTienLai;
}

// Xuat thong tin so tiet kiem
void xuatSoTietKiem(const SoTietKiem& stk) {
    cout << "================================================\n";
    cout << "                   SO TIET KIEM                 \n";
    cout << "================================================\n";
    cout << left << setw(30) << "Ma so:" << stk.maSo << endl;
    cout << left << setw(30) << "Loai tiet kiem:" << stk.loaiTietKiem << endl;
    cout << left << setw(30) << "Ho ten KH:" << stk.hoTenKH << endl;
    cout << left << setw(30) << "CMND:" << stk.cmnd << endl;
    cout << left << setw(30) << "Ngay mo so:" 
         << stk.ngayMoSo.tm_mday << "/" << stk.ngayMoSo.tm_mon + 1 
         << "/" << stk.ngayMoSo.tm_year+1900 << endl;

    cout << left << setw(30) << "So tien gui:" 
            << fixed << setprecision(2) << stk.soTienGui << " VND" << endl;

    cout << left << setw(30) << "Lai suat:" 
            << fixed << setprecision(2) << stk.laiSuat << "%/nam" << endl;

    cout << "================================================\n\n";
}

// Chuc nang rut tien
void rutTien(SoTietKiem& stk, double soTienRut) {
    if (soTienRut > stk.soTienGui) {
        cout << "So tien rut khong duoc vuot qua so du!" << "\n\n";
        return;
    }

    time_t now = time(0);
    tm *ngayHienTai = localtime(&now);
    ngayHienTai->tm_mon += 1;
    ngayHienTai->tm_year += 1900;

    int soNgayGui = tinhSoNgayGiuaHaiNgay(stk.ngayMoSo, *ngayHienTai);
    int laiSuat = stk.laiSuat;
    bool chonRut = 0;
    
    // Dieu chinh lai suat neu rut truoc han
    if ((stk.loaiTietKiem == "ngan han" && soNgayGui < 180) ||
        (stk.loaiTietKiem == "dai han" && soNgayGui < 365)) {
        cout << "Rut truoc han. Lai suat se duoc cap nhat thap hon." << "\n";
        cout << "Ban co muon rut khong? (1: Co, 0: Khong): ";
        cin >> chonRut;
        if (!chonRut) {
            cout << "Ban da huy rut tien." << "\n\n";
            return;
        }
        else {
            cout << "Ban da chon rut tien." << "\n";
            stk.laiSuat = 0.5;
        }
    }

    stk.soTienGui -= soTienRut;

    cout << "Rut tien thanh cong. So du hien tai: " << stk.soTienGui << "\n\n";
}

// Tim kiem so tiet kiem theo CMND
SoTietKiem* timSoTietKiemTheoCMND(vector<SoTietKiem>& danhSach, 
                                    const string& cmnd) {
    for (auto& stk : danhSach) {
        if (stk.cmnd == cmnd) return &stk;
    }
    return nullptr;
}

// Tim kiem so tiet kiem theo ma so
SoTietKiem* timSoTietKiemTheoMaSo(vector<SoTietKiem>& danhSach, 
                                    const string& maSo) {
    for (auto& stk : danhSach) {
        if (stk.maSo == maSo) return &stk;
    }
    return nullptr;
}

// Sap xep danh sach theo so tien gui giam dan
void sapXepTheoSoTien(vector<SoTietKiem>& danhSach) {
    sort(danhSach.begin(), danhSach.end(), 
        [](const SoTietKiem& a, const SoTietKiem& b) {
            return a.soTienGui > b.soTienGui;
        });
}

// Sap xep danh sach theo ngay mo so tang dan
void sapXepTheoNgayMoSo(vector<SoTietKiem>& danhSach) {
    sort(danhSach.begin(), danhSach.end(), 
        [](const SoTietKiem& a, const SoTietKiem& b) {
            // so sanh nam, thang, ngay
            if (a.ngayMoSo.tm_year != b.ngayMoSo.tm_year)
                return a.ngayMoSo.tm_year < b.ngayMoSo.tm_year;
            if (a.ngayMoSo.tm_mon != b.ngayMoSo.tm_mon)
                return a.ngayMoSo.tm_mon < b.ngayMoSo.tm_mon;
            return a.ngayMoSo.tm_mday < b.ngayMoSo.tm_mday;
        });
}

int main() {
    vector<SoTietKiem> danhSach;
    int luaChon;
    do {
        cout << "1. Them so tiet kiem\n";
        cout << "2. Xuat danh sach so tiet kiem\n";
        cout << "3. Rut tien\n";
        cout << "4. Tim so tiet kiem theo CMND\n";
        cout << "5. Tim so tiet kiem theo ma so\n";
        cout << "6. Sap xep theo so tien gui giam dan\n";
        cout << "7. Sap xep theo ngay mo so tang dan\n";
        cout << "8. Liet ke so tiet kiem mo trong khoang thoi gian cu the\n";
        cout << "9. Cap nhat lai suat\n";
        cout << "10. Tinh tien lai\n";
        cout << "0. Thoat\n";
        cout << "Nhap lua chon: ";
        cin >> luaChon;
        cin.ignore();
        switch (luaChon) {
        case 1: {
            SoTietKiem stk;
            nhapSoTietKiem(stk);
            danhSach.push_back(stk);
            break;
        }
        case 2: {
            for (const auto& stk : danhSach) {
                xuatSoTietKiem(stk);
            }
            break;
        }
        case 3: {
            string cmnd;
            double soTienRut;
            cout << "Nhap CMND cua so can rut: ";
			getline(cin, cmnd);
            SoTietKiem* stk = timSoTietKiemTheoCMND(danhSach, cmnd);
            if (stk) {
                cout << "Nhap so tien muon rut: ";
                cin >> soTienRut;
                rutTien(*stk, soTienRut);
            }
            else {
                cout << "Khong tim thay so tiet kiem voi CMND nay.\n" << endl;
            }
            break;
        }
        case 4: {
            string cmnd;
            cout << "Nhap CMND de tim: ";
			getline(cin, cmnd);
            SoTietKiem* stk = timSoTietKiemTheoCMND(danhSach, cmnd);
            if (stk) {
                xuatSoTietKiem(*stk);
            }
            else {
                cout << "Khong tim thay so tiet kiem voi CMND nay.\n" << endl;
            }
            break;
        }
        case 5: {
            string maSo;
            cout << "Nhap ma so de tim: ";
			getline(cin, maSo);
            SoTietKiem* stk = timSoTietKiemTheoMaSo(danhSach, maSo);
            if (stk) {
                xuatSoTietKiem(*stk);
            }
            else {
                cout << "Khong tim thay so tiet kiem voi ma so nay.\n" << endl;
            }
            break;
        }
        case 6: {
            sapXepTheoSoTien(danhSach);
            cout << "Danh sach da duoc sap xep theo so tien gui giam dan.\n" << endl;
            break;
        }
        case 7: {
            sapXepTheoNgayMoSo(danhSach);
            cout << "Danh sach da duoc sap xep theo ngay mo so tang dan.\n" << endl;
            break;
        }
		case 8: {
            cout << "Nhap thoi gian bat dau:\n";
			tm ngayBatDau = nhapNgay();
			cout << "Nhap thoi gian ket thuc:\n";
			tm ngayKetThuc = nhapNgay();
            cout << "Danh sach so tiet kiem mo tu ngay "
                << ngayBatDau.tm_mday << '-' << ngayBatDau.tm_mon << '-'
                << ngayBatDau.tm_year << " den ngay "
                << ngayKetThuc.tm_mday << '-' << ngayKetThuc.tm_mon
                << '-' << ngayKetThuc.tm_year << ":\n";
            bool check = false;
			for (const auto& stk : danhSach) {
				if (tinhSoNgayGiuaHaiNgay(ngayBatDau, stk.ngayMoSo) >= 0 &&
					tinhSoNgayGiuaHaiNgay(stk.ngayMoSo, ngayKetThuc) >= 0) {
					xuatSoTietKiem(stk);
                    check = true;
				}
			}
            cout << '\n';
            if (!check) {
            cout 
            << "Khong co so tiet kiem nao mo trong khoang thoi gian nay.\n\n";
            }
            break;
		}
        case 9: {
            string maSo;
            cout << "Nhap ma so de cap nhat lai suat: ";
            getline(cin, maSo);
            SoTietKiem* stk = timSoTietKiemTheoMaSo(danhSach, maSo);
            if (stk) {
                cout << "Nhap lai suat moi: ";
                cin >> stk->laiSuat;
                cout << "Cap nhat lai suat thanh cong.\n";
                cout << "Tien lai den hien tai: " 
                    << tinhTienLai(*stk) << " VND\n\n";
            }
            else {
                cout << "Khong tim thay so tiet kiem voi ma so nay.\n" << endl;
            }
            break;
        }
        case 10: {
            string maSo;
            cout << "Nhap ma so de tinh tien lai: ";
            getline(cin, maSo);
            SoTietKiem* stk = timSoTietKiemTheoMaSo(danhSach, maSo);
            if (stk) {
                cout << "Tien lai den hien tai: " 
                    << tinhTienLai(*stk) << " VND\n\n";
            }
            else {
                cout << "Khong tim thay so tiet kiem voi ma so nay.\n" << endl;
            }
        }
        case 0:
            cout << "Thoat chuong trinh." << endl;
            break;
        default:
            cout << "Lua chon khong hop le. Vui long thu lai.\n" << endl;
        }
    } while (luaChon != 0);

    return 0;
}
