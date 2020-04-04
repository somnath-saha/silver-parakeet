#include <iostream>
#include <string>

using namespace std;

static int sno=0;
 
void printAllPermutations(string s, int start)
{
    if(start==(s.size()-1)) {
        cout<<(++sno)<<". "<<s<<endl;
    }
    for(int i=start+1; i<s.size(); ++i) {
        printAllPermutations(s, start+1);
        std::swap(s[start], s[i]);
        printAllPermutations(s, start+1);
        std::swap(s[start], s[i]);
    }
}

int main()
{
    string s = "abcd";
    printAllPermutations(s, 0);
    return 0;
}