#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

template<typename T>
void print_vector(vector<T> & vec)
{
    for(auto a : vec)
        cout << " " << a;
    cout<<endl;
}

class SegementTree {
    vector<int> data;
    int N;

 public:   
    SegementTree(int n) {
        N = n;
        int num = pow(2, ceil(log2(n)) + 1);
        data = vector<int>(num);
    }

    void print() {
        print_vector(data);
    }
    
    int left(int i){
        return 2*i+1;
    }
        
    int right(int i){
        return 2*i+2;
    }
    
    int _build(int l, int r, int p) {
        if (l > r)
            return 0;
        if (l == r) {
            data[p] = 1;
            return data[p];
        }
        
        int mid = l + (r - l) / 2;
        int left = _build(l, mid, p *2 +1);
        int right = _build(mid +1, r, p * 2 + 2);
        data[p] = left + right;
        
        return left + right;
    }
    
    void  build() {
        _build(0, N -1, 0);
    }
    
    int _query(int key, int l, int r, int p) {
        
        if(l > r)
            return -1;
            
        if(l == r)
            return l;
            
        int lv = data[left(p)];
        int rv = data[right(p)];
        int mid = l + (r -l) /2;
        
        if( lv >= key)
            return _query(key, l, mid, left(p));
            
        return _query(key - lv, mid + 1, r, right(p));
    }
    
    int query(int key) {
        return _query(key, 0, N -1, 0);
    }
    
    void _update(int i, int value, int l, int r, int p)
    {
        if(l > r)
            return;
            
        if (l == r) {
            data[p] = value;
            return;
        }
        
        int mid=(l+r)/2;
        if (i <= mid)
            _update(i, value, l, mid, left(p));
        else
            _update(i, value, mid +1, r, right(p));
            
        data[p] = data[left(p)] + data[right(p)];
    }
    
    void update(int idx, int val)
    {
        _update(idx, val, 0, N -1, 0);
    }
};

int main() {
    vector<int> input = { -1, 0, 1, 3, 4};

    //auto seg = build_tree(input);

    SegementTree T1(6);
    T1.build();
    T1.print();
    

    //cout <<"RMQ 1:4 = "<< RMQ(seg, 0, input.size() -1, 1, 4, 0) << endl;
    // cout <<"RMQ 1:3 = "<< RMQ(seg, 0, input.size() -1, 1, 3, 0) << endl;
}

