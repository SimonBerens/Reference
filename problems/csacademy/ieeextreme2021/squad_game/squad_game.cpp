#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template <typename K> using hset = gp_hash_table<K, null_type>;
template <typename K, typename V> using hmap = gp_hash_table<K, V>;


using namespace std;

#define all(x) (x).begin(), (x).end()
#define pb push_back
#define eb emplace_back
#define smax(x, y) (x = max(x, y))
#define smin(x, y) (x = min(x, y))

using ll = long long;
using ld = long double;

template <typename T>
using vv = vector<vector<T>>;

using vi = vector<int>;
using ii = array<int, 2>;
using vii = vector<ii>;
using vvi = vv<int>;

using vll = vector<ll>;
using l2 = array<ll, 2>;
using vl2 = vector<l2>;
using vvll = vv<ll>;

template <typename T>
using minq = priority_queue<T, vector<T>, greater<T>>;
template <typename T>
using maxq = priority_queue<T>;

const ll M = 1000000007;

const int N = 1e5 + 9;
const long long INF = 2000000000000000007;
const int d = 2; ///dimension

struct point {
    int p[d];
    bool operator !=(const point &a) const {
        bool ok = 1;
        for(int i = 0; i < d; i++) ok &= (p[i] == a.p[i]);
        return !ok;
    }
};

struct kd_node {
    int axis, value;
    point p;
    kd_node *left, *right;
};

struct cmp_points {
    int axis;
    cmp_points() {}
    cmp_points(int x): axis(x) {}
    bool operator () (const point &a, const point &b) const {
        return a.p[axis] < b.p[axis];
    }
};

typedef kd_node* node_ptr;

int tests, n;
point arr[N], pts[N];
node_ptr root;
long long ans;

long long squared_distance(point a, point b) {
    long long ans = 0;
    for(int i = 0; i < d; i++) ans += (a.p[i] - b.p[i]) * 1ll * (a.p[i] - b.p[i]);
    return ans;
}

void build_tree(node_ptr &node, int from, int to, int axis) {
    if(from > to) {
        node = NULL;
        return;
    }

    node = new kd_node();

    if(from == to) {
        node->p = arr[from];
        node->left = NULL;
        node->right = NULL;
        return;
    }

    int mid = (from + to) / 2;

    nth_element(arr + from, arr + mid, arr + to + 1, cmp_points(axis));
    node->value = arr[mid].p[axis];
    node->axis = axis;
    build_tree(node->left, from, mid, (axis + 1) % d);
    build_tree(node->right, mid + 1, to, (axis + 1) % d);
}

void nearest_neighbor(node_ptr node, point q, long long &ans) {
    if(node == NULL) return;

    if(node->left == NULL && node->right == NULL) {
        if(q != node->p) ans = min(ans, squared_distance(node->p, q)); ///Beware!!! take care here
        return;
    }

    if(q.p[node->axis] <= node->value) {
        nearest_neighbor(node->left, q, ans);
        if(q.p[node->axis] + sqrt(ans) >= node->value) nearest_neighbor(node->right, q, ans);
    }

    else {
        nearest_neighbor(node->right, q, ans);
        if(q.p[node->axis] - sqrt(ans) <= node->value) nearest_neighbor(node->left, q, ans);
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    vector<vector<array<int, 3>>> groups(3, vector<array<int, 3>>(n));
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < 2; ++k) {
                cin >> groups[i][j][k];
            }
            groups[i][j][2] = j;
        }
    }
    for (int i = 0; i < 3; ++i) {
        sort(all(groups[i]));
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < 3; ++j) {
            cout << groups[j][i][2] + 1 << ' ';
        }
        cout << '\n';
    }

}