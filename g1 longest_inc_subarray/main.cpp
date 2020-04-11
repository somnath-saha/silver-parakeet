#include <iostream>
#include <vector>

using namespace std;

int longIncSubarray(vector<int> a)
{
    if(a.size()==0) {
        return 0;
    }
    int res = 1, retVal=1;
    for(int i = 1; i<a.size(); i++) {
        if(a[i]>a[i-1]) {
            res++;
        }
        else if(res>1) {
            retVal = std::max(retVal, res);
            res=1;
        }
    }
    return max(retVal, res);
}

// 1 2 3 4 2 5 6 3 0
//test
int main()
{
    vector<vector<int>> v;
    v.push_back({1, 2, 3, 4, 5, 6, 3, 4, 5, 6, 7, 8, 9});
    v.push_back(vector<int>());
    v.push_back({5, 4, 3, 2, 1});
    v.push_back({1});
    v.push_back({-1, 3, -2, 0});
    v.push_back({0, 0, 0});
    for(auto& a: v) {
        cout<<longIncSubarray(a)<<", ";
    }
    return 0;
}
