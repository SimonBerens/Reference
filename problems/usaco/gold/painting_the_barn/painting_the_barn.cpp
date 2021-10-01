#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>

using namespace __gnu_pbds;
template<typename K> using hset = gp_hash_table<K, null_type>;
template<typename K, typename V> using hmap = gp_hash_table<K, V>;


using namespace std;

using ll = long long;

using vi = vector<int>;
using vvi = vector<vector<int>>;

template<typename T>
using minq = priority_queue<T, vector<T>, greater<T>>;
template<typename T>
using maxq = priority_queue<T>;

ll M = 1000000007;

int solve(const vvi &t) {
    int R = t.size(), C = t[0].size();
    vvi pc(R + 1, vi(C));
    for (int c = 0; c < C; ++c) {
        for (int r = 1; r <= R; ++r) {
            pc[r][c] = pc[r - 1][c] + t[r - 1][c];
        }
    }

    int best_res = 0;
    vi br_bet_0_(R + 1);
    for (int rhi = 0; rhi < R; ++rhi) {
        br_bet_0_[rhi + 1] = br_bet_0_[rhi];
        for (int rlo = 0; rlo <= rhi; ++rlo) {
            int best_rect_bet_rlo_rhi = 0;
            int cur_rect = 0;
            for (int c = 0; c < C; ++c) {
                cur_rect += pc[rhi + 1][c] - pc[rlo][c];
                cur_rect = max(cur_rect, 0);
                best_rect_bet_rlo_rhi = max(best_rect_bet_rlo_rhi, cur_rect);
            }
            br_bet_0_[rhi + 1] = max(br_bet_0_[rhi + 1], best_rect_bet_rlo_rhi);
            best_res = max(best_res, best_rect_bet_rlo_rhi + br_bet_0_[rlo]);
        }
    }

    return best_res;
}


vvi rotate(const vvi &t) {
    vvi out = t;
    int n = out.size();
    int a = 0;
    int b = n-1;
    while(a<b){
        for(int i=0;i<(b-a);++i){
            swap(out[a][a+i], out[a+i][b]);
            swap(out[a][a+i], out[b][b-i]);
            swap(out[a][a+i], out[b-i][a]);
        }
        ++a;
        --b;
    }
    return out;
}


int main() {
    freopen("paintbarn.in", "r", stdin);
    freopen("paintbarn.out", "w", stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, k;
    cin >> n >> k;
    vvi g(201, vi(201));
    for (int i = 0; i < n; ++i) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        g[y1][x1] += 1;
        g[y2][x2] += 1;
        g[y2][x1] -= 1;
        g[y1][x2] -= 1;
    }
    int curk = 0;
    vvi p(202, vi(202));
    for (int r = 1; r <= 201; ++r) {
        for (int c = 1; c <= 201; ++c) {
            p[r][c] = p[r - 1][c] + p[r][c - 1] - p[r - 1][c - 1] + g[r - 1][c - 1];
            curk += p[r][c] == k;
        }
    }
    vvi t(200, vi(200));
    for (int r = 0; r < 200; ++r) {
        for (int c = 0; c < 200; ++c) {
            int x = p[r + 1][c + 1];
            t[r][c] = x == k ? -1 : (x == k - 1 ? 1 : 0);
        }
    }
    vvi t1 = rotate(t), t2 = rotate(t1), t3 = rotate(t2);
    cout << curk + max({solve(t), solve(t1), solve(t2), solve(t3)}) << '\n';
}