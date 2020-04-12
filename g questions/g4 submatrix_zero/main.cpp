#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <vector>

using namespace std;

int getMaxSubMatrixSize(vector<vector<int>> const &v)
{
    int rt = v.size();
    if (rt == 0)
        return 0;
    int ct = v[0].size();
    vector<int> cSum(ct, 0), sum(ct, 0);
    int res = 0;
    unordered_map<int, int> m;
    for (int rb = 0; rb < rt; ++rb)
    {
        for (int r = rb; r < rt; ++r)
        {
            for (int c = 0; c < ct; ++c)
            {
                cSum[c] += v[r][c];
                sum[c] = cSum[c];
            }
            if (sum[0] == 0)
            {
                res = max(res, r - rb + 1);
            }
            m[sum[0]] = 0;
            for (int c = 1; c < ct; ++c)
            {
                sum[c] += sum[c - 1];
                if (sum[c] == 0)
                {
                    res = max(res, (c + 1) * (r - rb + 1));
                }
                auto iter = m.find(sum[c]);
                if (iter != m.end())
                {
                    res = max(res, (c - iter->second) * (r - rb + 1));
                }
                else
                {
                    m[sum[c]] = c;
                }
            }
            m.clear();
        }
        std::fill(cSum.begin(), cSum.end(), 0);
    }
    return res;
}

void fillData(vector<vector<int>> &v, int choice);

int main()
{
    vector<vector<int>> v;
    int k = 0;
    for (int i = 1; i <= 5; ++i)
    {
        fillData(v, i);
        cout<<"Result for "<<i<<":"<<getMaxSubMatrixSize(v)<<endl;
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
        v.push_back(vector<int>({4, 0, 6}));
        v.push_back(vector<int>({7, 8, 4}));
        break;
    }
    case 2:
    {
        v.push_back(vector<int>({1, 2, 3, -8}));
        v.push_back(vector<int>({4, -38, 6, -4}));
        v.push_back(vector<int>({7, 8, 4, 24}));
        break;
    }
    case 3:
    {
        v.push_back(vector<int>({1, 2, 3, -8}));
        v.push_back(vector<int>({4, 5, 6, -4}));
        break;
    }    
    case 4:
    {
        v.push_back(vector<int>({9, 7, 16, 15}));
        v.push_back(vector<int>({1, -6, -7,  3 }));
        v.push_back(vector<int>({1,  8,  7,  9}));
        v.push_back(vector<int>({7, -2,  0, 10}));
        break;
    }
    case 5:
    {
        v.push_back(vector<int>({1, 2, 3}));
        v.push_back(vector<int>({-3, -2, -1}));
        v.push_back(vector<int>({1, -6, 5}));
    }
    default:
    {
        break;
    }
    }
}