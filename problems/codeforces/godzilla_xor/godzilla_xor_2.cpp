#include <bits/stdc++.h>

using namespace std;

vector<int> basis;

void add(int x) {
    // make sure leading 1 of each "it" is unique
    for (auto &it: basis)
        if ((x ^ it) < x) // if this is true then
            x ^= it;
    if (x) {
        // make sure leading 1 of "x" is unique
        for (auto &it: basis)
            if ((x ^ it) < it)
                it ^= x;
        basis.push_back(x);
        sort(basis.begin(), basis.end());
    }
}

int get(int k) {
    k--;
    int ans = 0;
    for (int i = 0; i < basis.size(); i++)
        if ((k >> i) & 1)
            ans ^= basis[i];
    return ans;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    while (n--) {
        int t, x;
        cin >> t >> x;
        if (t == 1)
            add(x);
        else
            cout << get(x) << "\n";
    }
}