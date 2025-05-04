class Solution {
public:
   int numEquivDominoPairs(vector<vector<int>>& dominoes) {
        int freq[100]={0}, cnt=0;
        for(auto& d: dominoes){
            int d0=d[0], d1=d[1], x=(d0<d1)?10*d0+d1:10*d1+d0;
            cnt+=freq[x];// number of pairs for x is increasing by freq[x]
            freq[x]++; // increase freq[x] by 1
        }
        return cnt;
        
    }
};