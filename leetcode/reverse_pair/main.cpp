#include<iostream>
#include<vector>

using namespace std;

class Solution {
    int count;
public:
    void Merge(vector<int>& nums, int b, int m, int e)
    {
        vector<int> temp(nums.size(), 0);
        if((b>=e) || m>e) {
            return;
        }
        //cout<<"Run for b,m,e="<<b<<","<<m<<","<<e<<endl;
        int fB = b, fE = m, sB = m+1, sE=e, res=b;
        while(fB<=fE && sB<=sE) {
            if(nums[fB]>2*(long long)nums[sB]) {
                count += fE-fB+1;
                sB++;
            }
            else {
                fB++;
            }
        }
        fB = b, fE = m, sB = m+1, sE=e, res=b;
        while(fB<=fE && sB<=sE) {
            if(nums[fB]<=nums[sB]) {
                temp[res++] = nums[fB++];
            }
            else {
                temp[res++] = nums[sB++];
            }
        }
        while(fB<=fE) {
            temp[res++] = nums[fB++]; 
        }
        while(sB<=sE) {
            temp[res++] = nums[sB++];
        }
        for(int i=b; i<=e; ++i) {
            nums[i] = temp[i];
        }
    }
    void MergeSort(vector<int>& nums, int b, int e) {
        if(b>=e) {
            return;
        }
        //cout<<"Run for (b,e)="<<b<<","<<e<<endl;
        int m = (b+e)/2;
        MergeSort(nums, b, m);
        MergeSort(nums, m+1, e);
        Merge(nums, b, m, e);
    }
    int reversePairs(vector<int>& nums) {
        count=0;
        MergeSort(nums, 0, nums.size()-1);
        return count;
    }
};

int main()
{
    //vector<int> nums({1,3,2,3,1});
    vector<int> nums({2,4,3,5,1});
    Solution sln;
    int res = sln.reversePairs(nums);
    cout<<"Value: "<<res<<endl;
}