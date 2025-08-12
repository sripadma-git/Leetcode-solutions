class Solution {
public:
     const int MOD = 1e9 + 7;
    int solve(int num, int target,int x, vector<vector<int>>& dp){
        if(num == 0){
            if(target == 0) return 1;
            return 0;
        }
        long long power = 1;
        for(int i = 0; i < x; i++) power *= num;
        if(dp[num][target] != -1) return dp[num][target];
        long long take = 0;
        if(power <= target){
            take = solve(num-1,target-power,x,dp);
        }
        long long not_take = solve(num-1,target,x,dp);
        return dp[num][target] = (take+not_take)%MOD;
    }
    int numberOfWays(int n, int x) {
        vector<vector<int>> dp(n+1,vector<int>(n+1,-1));
        return solve(n,n,x,dp);
        
    }
};