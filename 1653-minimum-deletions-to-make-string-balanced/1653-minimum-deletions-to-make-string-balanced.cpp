class Solution {
public:
    int n;
    vector<int> dp;// dp array
    
    int f(int i, int &cntA, string& s) {
        if(i==n) return 0;
        if (dp[i] != -1) return dp[i];// avoid of redundancy
        int ans=f(i+1, cntA, s);// recursive call
        
        if (s[i]=='a') cntA++;// add 1 to cntA
        else ans=min(ans+1, cntA); // otherwise take min(ans+1, cntA)
        
        return dp[i]=ans; // write ans to dp & return it
    }
    
    int minimumDeletions(string& s) {
        n = s.size();
        dp.assign(n, -1); // fill with -1
        int cntA=0;
        return f(0, cntA, s);
    }
};


auto init = []() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    return 'c';
}();