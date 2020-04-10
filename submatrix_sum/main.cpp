/*
Find submatrix which has given sum k
*/

#include <iostream>
#include <vector>

using namespace std;
static int oper =0;

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
                        cout <<"Found at ("<<ib<<","<<jb<<") to ("<<(re-1)<<","<<(ce-1)<<")"<<endl;
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
                            ((i-1>=0)&&(j-1>=0)?sArr[i-1][j-1]:0) + 
                            ((i-1>=0)?sArr[i-1][j]:0) + 
                            (j-1>=0?sArr[i][j-1]:0);
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
                    res = sArr[re-1][ce-1]- 
                            ((re-1>=0 && jb-1>=0) ? sArr[re-1][jb-1]:0)- 
                            ((ib>=1 && ce >=1) ? sArr[ib-1][ce-1]:0)+ 
                            ((ib>=1 && jb >=1) ? sArr[ib-1][jb-1]:0); 
                    oper++;
                    if (res == k)
                    {
                        cout <<"Found at ("<<ib<<","<<jb<<") to ("<<(re-1)<<","<<(ce-1)<<")"<<endl;
                    }
                }
            }
        }
    }
    return 1;
}

void fillData(vector<vector<int>>& v, int choice);

int main()
{
    vector<vector<int>> v;
    for (int i = 1; i <= 3; ++i)
    {
        fillData(v, i);
        getSubmatrix(v, 12);
        cout << "Did " << oper << " operations for getSubmatrix choice " << i << endl;
        getSubmatrix2(v, 12);
        cout << "Did " << oper << " operations for getSubmatrix2 choice " << i << endl;
    }
    return 0;
}

void fillData(vector<vector<int>>& v, int choice) 
{
    v.clear();
    switch(choice) {
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
        default: {
            break;
        }
    }
}