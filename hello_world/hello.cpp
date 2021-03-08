#include <iostream>

using namespace std;

string caesarCypherEncryptor(string str, int key) {
  // Write your code here.
	// 97 + 25 = 122
	int s = 0;
	for(int i=0; i<str.size(); i++) {
		s = (static_cast<int>(str[i]) + key);
		str[i] = (s > 122) ? 
		static_cast<char>(96 + (s % 122)) : static_cast<char>(s);
	}
	return str;
}

//test
int main()
{
    //cout<<"Hello World";
    cout << caesarCypherEncryptor("axm", 3);
    return 0;
}