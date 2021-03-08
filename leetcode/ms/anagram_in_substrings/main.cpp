#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

void print(const unordered_map<char, int>& m)
{
    for(auto& c: m) {
        cout<<c.first<<" - "<<c.second<<" | ";
    }
    cout<<endl;
}

bool HasAnagram(string s1, string s2)
{
    //4:15
    unordered_map<char, int> m, m2;
    for(const char& c: s2) {
        auto iter = m.find(c);
        if(iter == m.end()) {
            m[c] = 1;
        }
        else {
            m[c]++;
        }
    }
    //print(m);
    m2 = m;
    int i = 0, n = s1.size(), beg = 0;
    bool inProcess = false;
    while(i < n) {
        //cout<<"i = "<<i<<" ";
        //print(m);
        auto iter = m.find(s1[i]);
        if(iter == m.end()) {
            if(inProcess) {
                inProcess = false;
                i = beg + 1;
                beg = i;
                m = m2;
            }
            else {
                i++;
                beg++;
            }
        }
        else {
            inProcess = true;
            iter->second --;
            if(iter->second == 0) {
                m.erase(iter);
            }
            if(m.empty()) {
                return true;
            }
            i++;
        }
        //getchar();
    }
    return false;
}

int main()
{
    vector<vector<string>> testcases({{"microsoft", "tfos"}, 
                                        {"abcdef", "abe"},
                                        {"abcdef", "efg"},
                                        {"somnath", "amn"},
                                        {"aaaard", "dar"},
                                        {"microsoft", "toos"}});
    for(vector<string>& v: testcases) {
        cout<<HasAnagram(v[0], v[1])<<endl;
    }
    return 0;
}