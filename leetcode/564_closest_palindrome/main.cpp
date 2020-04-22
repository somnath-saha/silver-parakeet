#include<iostream>
#include<vector>

using namespace std;

typedef long long ll;

class Solution {
public:
    int n = 0;
    bool debug = false;
    bool isPalindrome(string& s) 
    {
        for(int i=0; i<n/2; ++i) {
            if(s[i]!=s[n-i-1]) {
                return false;
            }
        }
        return true;
    }
    bool allnines(string& s) 
    {
        for(int i=0; i<n; ++i) {
            if(s[i]!='9') {
                return false;
            }
        }
        long long x = stoll(s);
        if(x==9) {
            s = "8";
        }
        else {
            s = to_string(x+2);
        }
        return true;
    }
    void generatePalindrome(string& s)  
    {
        /*if(s[n-1]!='0') {
            createPalindrome(s);
            return;
        }*/
        ll origNumber = stoll(s);
        string sHigher = to_string(origNumber+1);
        if(!isPalindrome(sHigher)) {
            createPalindrome(sHigher);
        }
        string sLower = to_string(origNumber-1);
        if(!isPalindrome(sLower)) {
            createPalindrome(sLower);
        }
        if(sHigher==s) {
            s = sLower;
            return;
        }
        if(sLower==s) {
            s = sHigher;
            return;
        }
        ll hNo = stoll(sHigher);
        ll lNo = stoll(sLower);
        if( hNo-origNumber > origNumber-lNo ) {
            s = sLower;
            return;
        }
        s = sHigher;
    }
    void createPalindrome(string& s) 
    {
        int i = 0;
        while(i < n/2) {
            if(debug) cout<<"Checking at index "<<n-i-1<<" and "<<i<<endl;
            if(s[n-i-1]!=s[i]) {
                if(debug) cout<<"Doing replacement"<<endl;
                s[n-i-1] = s[i];
            }
            i++;
        }
    }
    string nearestPalindromic(string s) 
    {
        n = s.size();
        if(allnines(s)) {
            return s;
        }
        if(debug) cout<<s<<": Not all nines."<<endl;
        if(isPalindrome(s)) {
            if(n%2==1) {
                s[n/2] = s[n/2]-1;
            }
            else {
                s[n/2] = s[n/2-1] = s[n/2]-1;
            }
            if(!(s.size()>1 && s[0]=='0')) {
                return s;
            }
        }
        if(debug) {
            cout<<s<<": Not already palindrome."<<endl;
        }
        generatePalindrome(s);
        return s;
    }
};

int main()
{
    vector<string> nums({"11",
                    "80",
                    "10",
                    "1213",
                    "9",
                    "999999999999999999",
                    "999999",
                    "123321",
                    "12321",
                    "1",
                    "12" });
    Solution sln;
    for(string s: nums) {
        cout<<sln.nearestPalindromic(s)<<endl;
    }
}