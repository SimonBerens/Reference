#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef pair<ll, ll> pll;

//pll DP[16][160][2][2];
array<array<array<array<pll, 2>, 2>, 160>, 16> DP;

pll dp(const string &upper, const string &lower, int pos, int s, bool u_bounded, bool l_bounded) {
    if (pos == -1) {
        if (s == 0) {
            return {0, 1};
        } else {
            return {0, 0};
        }
    }

    if (s < 0) {
        return {0, 0};
    }


    auto & loc = DP.at(pos).at(s).at(u_bounded).at(l_bounded);
//    auto & loc = DP[pos][s][u_bounded][l_bounded];
    if (loc.first != -1) {
        return loc;
    }

    int l_limit = 0, u_limit = 9;
    if (l_bounded) {
        l_limit = lower[pos] - '0';
    }
    if (u_bounded) {
        u_limit = upper[pos] - '0';
    }

    ll cnt = 0;
    ll lowest = numeric_limits<ll>::max();

    for (int d = l_limit; d <= u_limit; ++d) {
        auto [dp_lowest, dp_cnt] = dp(upper, lower, pos - 1, s - d, u_bounded && d == u_limit, l_bounded && d == l_limit);
        if (dp_cnt != 0) {
            cnt += dp_cnt;
            lowest = min(lowest, d * ((ll) pow(10, pos)) + dp_lowest);
        }
    }

    if (cnt == 0) {
        return loc = {0, 0};
    } else {
        return loc = {lowest, cnt};
    }
}


int main() {
    ll a, b, s;
    cin >> a >> b >> s;

    for (int i = 0; i < 16; ++i) {
        for (int j = 0; j < 160; ++j) {
            for (int k = 0; k < 2; ++k) {
                for (int l = 0; l < 2; ++l) {
                    DP[i][j][k][l] = {-1, -1};
                }
            }
        }
    }

    string a_str = to_string(a), b_str = to_string(b);
    a_str = string(b_str.size() - a_str.size(), '0') + a_str;
    reverse(a_str.begin(), a_str.end());
    reverse(b_str.begin(), b_str.end());
    auto [lowest, cnt] = dp(b_str, a_str, b_str.size() - 1, s, true, true);
    cout << cnt << "\n"
         << lowest << "\n";
}