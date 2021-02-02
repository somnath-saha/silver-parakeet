#include <iostream>
#include <vector>
using namespace std;

class SegmentTree {
	
	vector<int> v;
    static int const maxval = 9999;

	void constructTree(const vector<int>& arr, int low, int high, int pos)
	{
        cout<<"low = "<<low<<" | high = "<<high<<" | pos = "<<pos<<endl;
		if(low==high) {
            cout<<arr[low] <<" at pos."<<endl;
			v[pos] = arr[low];
            return;
		}
        int mid = (low + high) / 2;
        int left = 2*pos + 1;
        int right = 2*pos + 2;
        constructTree(arr, low, mid, left);
        constructTree(arr, mid+1, high, right);
        v[pos] = std::min(v[left], v[right]);
	}
    
    int query(int l, int h, int low, int high, int pos)
    {
        if(l>high || h<low) {
            return maxval;
        }
        if(l==low && h==high) {
            return v[pos];
        }
        if(l>=low && h<=high) {
            int mid = (low + high) / 2;
            return std::min(query(l, h, low, mid, 2*pos+1), 
                            query(l, h, mid+1, high, 2*pos+2));
        }
        return -1;
    }
public:
	SegmentTree(const vector<int>& arr) 
	{
		v = vector<int>((2*arr.size()+1), 9999);
		constructTree(arr, 0, arr.size()-1, 0);
	}
    void Query(int l, int h) 
    {
        cout<<"Query ("<<l<<","<<h<<"): "<<query(l, h, 0, v.size()-1, 0)<<endl;
    }
	void Print()
	{
		for(auto i: v) {
			cout<<i<<" ";
		}
		cout<<endl;
	}

};

int main() 
{
	SegmentTree st({1,2,5,2,6,7});
	st.Print();
    st.Query(2, 4);
	return 0;
}