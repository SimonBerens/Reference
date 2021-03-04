#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int k;
    cin >> k;
    for (int i = 0; i < k; ++i) {
        int n;
        cin >> n;
        vector<int> v(n);
        for (int j = 0; j < n; ++j) {
            cin >> v[j];
        }
        int last = 0, len = 0;
        for (int j = 0; j < n; ++j) {
            if (v[j] == last + 1) {
                last += 1;
                len += 1;
            }
        }
        cout << n - len << "\n";
    }
}