#include <iostream>
#include <vector>
#include <queue>
#include <cmath>

using namespace std;

typedef long long ll;
typedef pair<ll, ll> pii;

int main() {
    while (true) {
        int n, b;
        cin >> n >> b;
        if (n == -1)
            return 0;
        auto comp = [](const pii &p1, const pii &p2) -> bool {
            return p1.first * p2.second < p2.first * p1.second;
        };
        priority_queue<pii, vector<pii>, decltype(comp)> pq(comp);
        for (int i = 0; i < n; ++i) {
            int tmp;
            cin >> tmp;
            pq.emplace(tmp, 1);
        }
        b -= n;
        while (b--) {
            const auto[citpop, citballot] = pq.top();
            pq.pop();
            pq.emplace(citpop, citballot + 1);
        }
        const auto[citpop, citballot] = pq.top();
        cout << ceil(double(citpop) / citballot) << "\n";

    }
}