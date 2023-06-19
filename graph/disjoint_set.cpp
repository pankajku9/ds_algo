    #include <vector>

    using namespace std;

    void make_set(vector<int> &par)
    {
        for (int i = 0; i < par.size();i++)
            par[i] = i;
    }
    
    int set_find(vector<int> &par, int x)
    {
        if (par[x] == x)
            return x;
        return set_find(par, par[x]);
    }

    void set_union(vector<int> &par, int x, int y)
    {
        int a = set_find(par, x);
        int b = set_find(par, y);
        
        /* Make a as parent of b */
        par[b] = a;
    }

    int main()
    {
        vector<int> par(3);
        make_set(par);

    }