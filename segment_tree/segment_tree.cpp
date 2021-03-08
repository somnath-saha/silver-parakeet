#include <iostream>
#include <vector>
using namespace std;

class SegmentTree {
	
	vector<int> v;
    static int const maxval = 9999;

	void constructTree(const vector<int>& arr, int low, int high, int pos)
	{
        //cout<<"low = "<<low<<" | high = "<<high<<" | pos = "<<pos<<endl;
		if(low==high) {
            //cout<<arr[low] <<" at pos."<<endl;
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
        //cout<<"low = "<<low<<" | high = "<<high<<" | pos = "<<pos<<endl;
        if(l>high || h<low) {
            return maxval;
        }
        if(l<=low && h>=high) {
            return v[pos];
        }
        int mid = (low + high) / 2;
        return std::min(query(l, h, low, mid, 2 * pos + 1),
                        query(l, h, mid + 1, high, 2 * pos + 2));

    }

public:
	SegmentTree(const vector<int>& arr) 
	{
		v = vector<int>((2*arr.size()+1), 9999);
		constructTree(arr, 0, arr.size()-1, 0);
        int k=0;
        for(auto i: arr) {
			cout<<k++<<":"<<i<<" ";
		}
		cout<<endl;
	}
    void Query(int l, int h) 
    {
        cout << "\nQuery (" << l << "," << h << "): " << query(l, h, 0, (v.size() - 1) / 2, 0) << endl;
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
	SegmentTree st({1,2,5,20,6,7,7,90,78,1});
	st.Print();
    st.Query(2, 4);
    st.Query(7, 8);
    st.Query(7, 9);
    st.Query(4, 7);
    st.Query(0, 4);
    st.Query(0, 8);
	return 0;
}