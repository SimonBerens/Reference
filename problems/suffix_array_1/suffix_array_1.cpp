#include <bits/stdc++.h>

using namespace std;

string s;
int n;
vector<int> sa, m, eq;
typedef pair<int, int> pii;

void verify(int k) {
    for (int i = 0; i < sa.size(); ++i) {
        assert(i == m[sa[i]]);
    }
    for (int i = 1; i < sa.size(); ++i) {
        string a = s.substr(sa[i], k), b = s.substr(sa[i - 1], k);
        assert((eq[i] == eq[i - 1]) == (a == b));
    }
}

int rot_idx(int i, int k) {
    return m[(sa[i] + k) % n];
}

void counting_sort(int k) {
    int max_eq = eq.back();
    vector<int> counts(max_eq + 1);
    for (int i = 0; i < n; ++i) {
        counts[eq[rot_idx(i, k)]]++;
    }
    vector<int> buckets(max_eq + 1);
    buckets[0] = 0;
    for (int i = 1; i <= max_eq; ++i) {
        buckets[i] = buckets[i - 1] + counts[i - 1];
    }
    vector<int> new_sa(n);
    for (int i = 0; i < n; ++i) {
        new_sa.at(buckets[eq[rot_idx(i, k)]]++) = sa[i];
    }
    sa = new_sa;
}


void radix_sort(int k) {
    counting_sort(k);
    counting_sort(0);
}


int main() {
    cin >> s;
//    s.assign(400000, 'a');
    s += '$';
    n = s.size();
    sa.assign(n, 0);
    iota(sa.begin(), sa.end(), 0);
    sort(sa.begin(), sa.end(), [](int i, int j) -> bool {
        return s[i] < s[j];
    });
    m.assign(n, 0); // map suffix to its pos in the suffix array
    for (int i = 0; i < n; ++i) {
        m[sa[i]] = i;
    }
    eq.assign(n, 0);
    for (int i = 1; i < n; ++i) {
        eq[i] = eq[i - 1] + (s[sa[i]] != s[sa[i - 1]]);
    }

    for (int k = 1; k <= n ; k *= 2) {
        radix_sort(k);
        for (int i = 0; i < n; ++i) {
            m[sa[i]] = i;
        }
        vector<int> new_eq(n);
        for (int i = 1; i < n; ++i) {
            new_eq[i] = new_eq[i - 1] + (pii{eq[i], eq[rot_idx(i, k)]} > pii{eq[i - 1], eq[rot_idx(i - 1, k)]});
        }
        eq = move(new_eq);
//        verify(2 * k);
    }

    for (int a : sa) {
        cout << a << " ";
    }
    cout << "\n";
}