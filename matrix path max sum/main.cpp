#include <iostream>
#include <vector>

using namespace std;

bool debug = false;

void _OptimizeSum(vector<vector<int>>& g,
                  vector<vector<bool>>& visited,
                  pair<int, int> currPos,
                  pair<int, int>& res, pair<int, int>& maxVal)
{
    int r = g.size();
    int c = g[0].size();
    if(currPos.first<0 || currPos.first>=r ||
       currPos.second<0 || currPos.second>=c || visited[currPos.first][currPos.second])
    {
        return;
    }
    visited[currPos.first][currPos.second] = true;
    res.first += 1;
    res.second += g[currPos.first][currPos.second];
    if(debug) cout<<"At currPos:"<<currPos.first<<","<<currPos.second<<" res"<<res.first<<","<<res.second<<endl;
    if(currPos.first==0 && currPos.second==c-1) {
        if(res.second>maxVal.second) {
            if(debug) cout<<"MaxVal updated."<<endl;
            maxVal = res;
        }
        else if(res.second==maxVal.second && res.first<maxVal.first) {
            if(debug) cout<<"MaxVal updated."<<endl;
            maxVal = res;
        }
    }
    _OptimizeSum(g, visited, make_pair(currPos.first-1, currPos.second), res, maxVal);
    _OptimizeSum(g, visited, make_pair(currPos.first, currPos.second+1), res, maxVal);
    visited[currPos.first][currPos.second] = false;
    res.first -= 1;
    res.second -= g[currPos.first][currPos.second];
}

int OptimizeSum(vector<vector<int>>& g)
{
    int r = g.size();
    int c = g[0].size();
    vector<vector<bool>> visited(r, vector<bool>(c, false));
    pair<int, int> currPos({r-1, 0}), res({0, 0}), maxVal({0, 0});
    _OptimizeSum(g, visited, currPos, res, maxVal);
    return maxVal.second;
}

int main()
{
    vector<vector<int>> g;
    /*
    g.push_back(vector<int>({ 0, 1, 5}));
    g.push_back(vector<int>({ 0, 8, 0}));
    g.push_back(vector<int>({ 1, 1, 0}));
     */
    
    g.push_back(vector<int>({ 0, 0, 0, 0, 1, 5}));
    g.push_back(vector<int>({ 0, 0, 0, 0, 8, 0}));
    g.push_back(vector<int>({ 0, 1, 1, 1, 1, 0}));
    g.push_back(vector<int>({ 0, 0, 0, 0, 0, 0}));
    
    int res = OptimizeSum(g);
    cout<<"Max Path Value: "<<res<<endl;
}

