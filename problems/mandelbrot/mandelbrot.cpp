#include <bits/stdc++.h>
using namespace std;

typedef long double ld;

int main() {
    ld x, y;
    int r, case_no = 1;
    while (cin >> x >> y >> r) {
        bool out = false;
        complex<ld> z, c(x, y);
        for (int i = 0; i <= r; ++i) {
            if (abs(z) > 2) {
                cout << "Case " << case_no << ": OUT\n";
                out = true;
                break;
            }
            z = z * z + c;
        }
        if (!out) {
            cout << "Case " << case_no << ": IN\n";
        }
        case_no++;
    }
}