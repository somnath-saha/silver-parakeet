#include <iostream>
#include <string>

using namespace std;

static int sno=0;
static int sno2=0;
 
void nCRPermutations(string s, int start, int r)
{
    if(start>r) {
        return;
    }
    if(start==r) {
        cout << (++sno2) << ". " << s.substr(0, r) << endl;
    }
    else {
        nCRPermutations(s, start+1, r);
        for(int i = start+1; i<s.size(); ++i) {
            swap(s[start], s[i]);
            nCRPermutations(s, start+1, r);
            swap(s[start], s[i]);
        }
    }
}

void printAllPermutations(string s, int start)
{
    if (start >= s.size())
    {
        return;
    }
    if (start == (s.size() - 1))
    {
        cout << (++sno) << ". " << s << endl;
    }
    else
    {
        printAllPermutations(s, start + 1);
        for (int i = start + 1; i < s.size(); ++i)
        {
            std::swap(s[start], s[i]);
            printAllPermutations(s, start + 1);
            std::swap(s[start], s[i]);
        }
    } 
}

int main()
{
    string s = "abcd";
    //printAllPermutations(s, 0);
    nCRPermutations(s, 0, 2);
    return 0;
}