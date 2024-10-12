#include <iostream>
#include <vector>
using namespace std;

vector<int> vitri; // Luu vi tri bat dau xuat hien

int main() {
    int n, m;
    cout << "Nhap so phan tu cua mang A va B (n, m): ";
    cin >> n >> m;

    int* A = new int[n];
    int* B = new int[m];

    cout << "Nhap mang A: ";
    for (int i = 0; i < n; i++) cin >> A[i];
    cout << "Nhap mang B: ";
    for (int i = 0; i < m; i++) cin >> B[i];

    int dem = 0;

    // Duyet qua cac vi tri co the cua B de tim mang A
    for (int i = 0; i <= m - n; i++) {
        bool khop = true;

        // Kiem tra xem thu vi tri i cua B co khop hoan toan voi A hay khong
        for (int j = 0; j < n; j++) {
            if (A[j] != B[i + j]) {
                khop = false;
                break;
            }
        }

        if (khop) {
            dem++;
            vitri.push_back(i);
        }
    }

    cout << "So lan A xuat hien trong B: " << dem << '\n';
    cout << "Cac chi so bat dau xuat hien la: ";
    for (auto i : vitri) {
        cout << i << ' ';
    }

    delete[] A;
    delete[] B;
}

