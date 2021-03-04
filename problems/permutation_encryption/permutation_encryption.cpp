#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
    while (true) {
        int n;
        cin >> n;
        if (n == 0)
            return 0;
        vector<int> v(n);
        for (int i = 0; i < n; ++i)
            cin >> v[i];
        string s;
        cin >> ws;
        getline(cin, s);
        string out;
        for (int i = 0; i < size(s); i += n)
            for (int j = 0; j < n; ++j)
                out += (i + v[j] - 1 >= size(s)) ? ' ' : s[i + v[j] - 1];
        cout << "'" << out << "'" << endl;
    }
}
