#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

ll DP[12][2][2];

ll dp(const string &num, int pos, bool limited, bool all_z) {
    if (pos < 0) {
        return 0;
    }

    auto &loc = DP[pos][limited][all_z];
    if (loc == -1) {

        int limit = 9;
        if (limited) {
            limit = num[pos] - '0';
        }

        ll res = 0;
        res += dp(num, pos - 1, limited && num[pos] == '0', all_z);


        if (limited && num[pos] == '0') {
            string s = num.substr(0, pos );
            reverse(s.begin(), s.end());
            res += stoll(s) + 1;
        } else if (!all_z) {
            res += (ll) pow(10, pos);
        }

        for (int d = 1; d <= limit; ++d) {
            res += dp(num, pos - 1, limited && d == limit, false);
        }

        return loc = res;
    } else {
        return loc;
    }
}


ll num_zeros_below_k(ll k) {
    if (k < 0) {
        return 0;
    }

    memset(DP, -1, sizeof(DP));
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            DP[0][i][j] = 1;
        }
    }
    string s = to_string(k);
    reverse(s.begin(), s.end());
    return dp(s, s.size() - 1, true, true);
}

int main() {
    while (true) {
        ll m, n;
        cin >> m >> n;
        if (m < 0) break;
        cout << num_zeros_below_k(n) - num_zeros_below_k(m - 1) << "\n";
    }
}