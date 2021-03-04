#include <iostream>

using namespace std;

int main() {
    int t = 0;
    cin >> t;
    for (int i = 0; i < t; ++i) {
        int a = 0;
        cin >> a;
        cout << ((360 % (180 - a) == 0) ? "YES" : "NO") << "\n";
    }
}

