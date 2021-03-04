#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    if (m < 0 || n - (m + 2) < 0) {
        cout << -1 << "\n";
    } else {

        int i = 0;
        for (; i < n - m - 2; ++i) {
            cout << 2 * i + 1<< " " << 2 * i + 2 << "\n";
        }
        cout << 2 * i + 1<< " " <<2 * i + (m + 1) * 3 + 2 << "\n";
        i += 1;
        for (; i < n; ++i) {
            cout << 2 * i + 1<< " " << 2 * i + 2 << "\n";
        }
    }
}