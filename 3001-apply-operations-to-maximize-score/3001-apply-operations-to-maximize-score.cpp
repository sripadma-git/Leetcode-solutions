class Solution {
public:
    int maximumScore(vector<int>& nums, int k) {
         priority_queue<pair<int,int>>pq;
        vector<int>score;
        int n = nums.size(), mod = 1e9+7;
        
        for(int i = 0 ; i < n ; i++){
            score.push_back(findPrimeFactor(nums[i]));
            pq.push({nums[i], i});
        }
        
        vector<int>next = NextMax(score);
        vector<int>prev = PrevMax(score);
        long long ans = 1;
        
        while(!pq.empty() && k > 0){
            int num = pq.top().first;
            int i = pq.top().second;
            pq.pop();
            long long op = min((long long)k, (long long)(next[i] - i) *
                                    (i - prev[i]));
            ans = (ans * modExp(num, op, mod)) % mod;
            k -= op;
        }
        return ans;
    }

    vector<int> NextMax(vector<int>&nums){
        int n = nums.size();
        vector<int>maxi(n, n);
        stack<int>st;
        for(int i = n-1; i >= 0 ; i--){
            while(!st.empty() && nums[st.top()] <= nums[i]) st.pop();
            if(!st.empty()) maxi[i] = st.top();
            st.push(i);
        }
        return maxi;
    }

    vector<int> PrevMax(vector<int>&nums){
        int n = nums.size();
        vector<int>maxi(n, -1);
        stack<int>st;
        for(int i = 0; i < n ; i++){
            while(!st.empty() && nums[st.top()] < nums[i]) st.pop();
            if(!st.empty()) maxi[i] = st.top();
            st.push(i);
        }
        return maxi;
    }

    int findPrimeFactor(int num){
        bool flag = 0;
        while(num%2 == 0){
            flag = 1;
            num /= 2;
        }
        int cnt = 0;
        if(flag) cnt = 1;
        for(int i = 3 ; i*i <= num ; i += 2){
            flag = 0;
            while(num%i == 0){
                flag = 1;
                num /= i;
            }
            if(flag) cnt++;
        }
        if(num > 1) cnt++;
        return cnt;
    }

    long long modExp(long long base, long long exp, long long mod) {
        long long res = 1;
        while (exp > 0) {
            if (exp % 2 == 1)  
                res = (res * base) % mod;
            base = (base * base) % mod;
            exp /= 2;
        }
        return res;
    }
};