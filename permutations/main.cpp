#include <iostream>
#include <string>

using namespace std;

static int sno=0;
static int sno2=0;
 
void nCRPermutations(string s, int start, int r)
{
    if(start>=r) {
        return;
    }
    cout << (++sno2) << ". " << s << endl;
    nCRPermutations(s, start, r);
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
    string s = "awqd";
    printAllPermutations(s, 0);
    return 0;
}