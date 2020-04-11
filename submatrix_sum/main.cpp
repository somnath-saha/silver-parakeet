/*
Find submatrix which has given sum k
*/

#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;
static int oper = 0;

int getSum(vector<vector<int>> &v, int ib, int jb, int ie, int je)
{
    int res = 0;
    for (int i = ib; i < ie; ++i)
    {
        for (int j = jb; j < je; ++j)
        {
            res += v[i][j];
            oper++;
        }
    }
    return res;
}

//Time Complexity for vector dim n x n => n^6
//Space Complexity for vector dim n x n => 1
int getSubmatrix(vector<vector<int>> &v, int k)
{
    int r = v.size();
    if (r == 0)
        return 0;
    int c = v[0].size();
    if (c == 0)
        return 0;
    int res = 0;
    //Find sum for all possible subarrays
    for (int re = r; re > 0; --re)
    {
        for (int ce = c; ce > 0; --ce)
        {
            for (int ib = 0; ib < re; ++ib)
            {
                for (int jb = 0; jb < ce; ++jb)
                {
                    if (getSum(v, ib, jb, re, ce) == k)
                    {
                        cout << "Found at (" << ib << "," << jb << ") to (" << (re - 1) << "," << (ce - 1) << ")" << endl;
                    }
                }
            }
        }
    }
    return 1;
}

//Time Complexity for vector dim n x n => n^4
//Space Complexity for vector dim n x n => n^2
int getSubmatrix2(vector<vector<int>> &v, int k)
{
    oper = 0;
    int r = v.size();
    if (r == 0)
        return 0;
    int c = v[0].size();
    if (c == 0)
        return 0;

    //Find sum array
    vector<vector<int>> sArr(r, vector<int>(c, 0));
    for (int i = 0; i < r; ++i)
    {
        for (int j = 0; j < c; ++j)
        {
            sArr[i][j] = v[i][j] -
                         ((i - 1 >= 0) && (j - 1 >= 0) ? sArr[i - 1][j - 1] : 0) +
                         ((i - 1 >= 0) ? sArr[i - 1][j] : 0) +
                         (j - 1 >= 0 ? sArr[i][j - 1] : 0);
            oper++;
        }
    }
    //Find sum for all possible subarrays
    int res = 0;
    for (int re = r; re > 0; --re)
    {
        for (int ce = c; ce > 0; --ce)
        {
            for (int ib = 0; ib < re; ++ib)
            {
                for (int jb = 0; jb < ce; ++jb)
                {
                    res = sArr[re - 1][ce - 1] -
                          ((re - 1 >= 0 && jb - 1 >= 0) ? sArr[re - 1][jb - 1] : 0) -
                          ((ib >= 1 && ce >= 1) ? sArr[ib - 1][ce - 1] : 0) +
                          ((ib >= 1 && jb >= 1) ? sArr[ib - 1][jb - 1] : 0);
                    oper++;
                    if (res == k)
                    {
                        cout << "Found at (" << ib << "," << jb << ") to (" << (re - 1) << "," << (ce - 1) << ")" << endl;
                    }
                }
            }
        }
    }
    return 1;
}

void getSubmatrix3(const vector<vector<int>> &v, int k)
{
    oper = 0;
    int rt = v.size();
    if (rt <= 0)
        return;
    int ct = v[0].size();
    vector<int> sum(ct, 0), sumCol(ct, 0);
    unordered_map<int, vector<int>> m;
    for (int rb = 0; rb < rt; ++rb)
    {
        for (int r = rb; r < rt; ++r)
        {
            cout<<"rb:"<<rb<<" r:"<<r<<endl;
            for (int c = 0; c < ct; ++c)
            {
                sumCol[c] += v[r][c];
                sum[c] = sumCol[c];
                cout << sum[c] << " ";
                oper += 2;
            }
            cout << endl;
            if (sum[0] == k)
            {
                cout << "Found for (" << rb << "," << 0 << ") to ("
                     << r << "," << 0 << ")." << endl;
            }
            for (int c = 1; c < ct; ++c)
            {
                sum[c] += sum[c - 1];
                auto iter = m.find(sum[c] - k);
                if (iter != m.end())
                {
                    auto cb = iter->second;
                    cout<<"Find "<<(sum[c]-k)<<" found."<<endl;
                    for (auto i : cb)
                    {
                        cout << "Found for (" << rb << "," << i
                             << ") to (" << r << "," << c << ")." << endl;
                    }
                }
                else {
                    cout<<"Find "<<(sum[c]-k)<<" fails."<<endl;
                }
                iter = m.find(sum[c]);
                if (iter == m.end())
                {
                    vector<int> l(1, sum[c]);
                    m[sum[c]] = l;
                }
                else
                {
                    iter->second.push_back(sum[c]);
                }
                oper += 4;
            }
            m.clear();
        }
        std::fill(sumCol.begin(), sumCol.end(), 0);
        oper += ct;
        cout<<"End for rb "<<rb<<"."<<endl;
    }
}

void fillData(vector<vector<int>> &v, int choice);

int main()
{
    vector<vector<int>> v;
    for (int i = 1; i <= 1; ++i)
    {
        fillData(v, i);
        /*getSubmatrix(v, 12);
        cout << "Did " << oper << " operations for getSubmatrix choice " << i << endl;
        getSubmatrix2(v, 12);
        cout << "Did " << oper << " operations for getSubmatrix2 choice " << i << endl;*/
        getSubmatrix3(v, 12);
        cout << "Did " << oper << " operations for getSubmatrix3 choice " << i << endl;
    }
    return 0;
}

void fillData(vector<vector<int>> &v, int choice)
{
    v.clear();
    switch (choice)
    {
    case 1:
    {
        v.push_back(vector<int>({1, 2, 3}));
        v.push_back(vector<int>({4, 5, 6}));
        v.push_back(vector<int>({7, 8, 4}));
        break;
    }
    case 2:
    {
        v.push_back(vector<int>({1, 2, 3, -8}));
        v.push_back(vector<int>({4, 5, 6, -4}));
        v.push_back(vector<int>({7, 8, 4, 24}));
        break;
    }
    case 3:
    {
        v.push_back(vector<int>({1, 2, 3, -8}));
        v.push_back(vector<int>({4, 5, 6, -4}));
        break;
    }
    default:
    {
        break;
    }
    }
}