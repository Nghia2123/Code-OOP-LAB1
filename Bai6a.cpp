#include <iostream>
#include <vector>
using namespace std;

int dem;
vector<int> vitri; // Luu vi tri bat dau xuat hien

// Thuat toan KMP tim chuoi A trong chuoi B
void KMP(int *A, int *B, int n, int m) {
    int *p = new int[n+1]{0};

    for (int i=0, j=2; j<=n; j++) {
        while (i > 0 && A[i+1] != A[j])
            i = p[i];
        if (A[i+1] == A[j])
            p[j] = ++i;
    }

    for (int i=0, j=1; j<=m; j++) {
        while (i > 0 && B[j] != A[i+1]) {
            i = p[i];
        }
        if (B[j] == A[i+1])
            i++;
    
        if (i == n) {
            vitri.push_back(j-n);
            i = p[i];
            dem++;
        }
    }
}

int main() {
    int n, m;
    cout << "Nhap so phan tu cua mang A va B (n, m): ";
    cin >> n >> m;

    int* A = new int[n+1];
    int* B = new int[m+1];

    cout << "Nhap mang A: ";
    for (int i = 1; i <= n; i++) cin >> A[i];
    cout << "Nhap mang B: ";
    for (int i = 1; i <= m; i++) cin >> B[i];
    KMP(A, B, n, m);

    if (dem == 0) {
        cout << "Khong tim thay A trong B.\n";
        return 0;
    }
    else{
        cout << "So lan A xuat hien trong B: " << dem << '\n';
        cout << "Cac chi so bat dau xuat hien la: ";
        for (auto i : vitri) {
            cout << i << ' ';
        }
    }

    delete[] A;
    delete[] B;
}

