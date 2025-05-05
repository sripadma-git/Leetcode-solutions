class Solution {
public:
    int md = 1e9+7;

    int check(int n, vector<int>& v) {
        if (n == 0) return 1;
        if (n == 1) return 1;
        if (n == 2) return 2;
        if (v[n] != -1) return v[n];

        v[n] = (check(n - 1, v) * 2LL % md + check(n - 3, v)) % md;
        return v[n];
    }

    int numTilings(int n) {
        vector<int> v(n + 1, -1);
        return check(n, v);
        
    }
};