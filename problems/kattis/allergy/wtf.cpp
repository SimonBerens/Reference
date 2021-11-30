#include <iostream>
#include <cmath>
#include <queue>
#include <vector>
#include <set>
#include <unordered_map>

using namespace std;

int main() {
    int n;
    priority_queue<int> sup;
    cin>>n;
    for (int i = 0; i < n; ++i) {
        int t;
        cin>>t;
        sup.push(t);
    }
    int res = 0;
    while(!sup.empty()){
        if(sup.size()==1){
            res+=sup.top();
            break;
        }
        int first = sup.top();
        sup.pop();
        int second = sup.top();
        sup.pop();
        int remaining = first - second + 1;
        res+=second;
        sup.push(remaining);
    }
    cout<<res<<endl;
    return 0;
}