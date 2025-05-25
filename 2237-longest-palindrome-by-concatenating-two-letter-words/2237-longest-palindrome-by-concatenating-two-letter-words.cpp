class Solution {
public:
    int longestPalindrome(vector<string>& words) {
         int i, ans = 0, f = 1;
        string aux;
        unordered_map<string, int>freq;   
        for(i = 0; i<words.size(); i++){
            freq[words[i]]++;
        }
        for(i = 0; i<words.size(); i++){
            aux = words[i];
            reverse(aux.begin(), aux.end());
            if((aux != words[i] && freq[words[i]] && freq[aux]) || (aux == words[i] && freq[aux]>=2)){
                ans+=4;
                freq[words[i]]--;
                freq[aux]--;
            }
            else if(aux == words[i] && freq[aux] && f){
                ans+=2;
                freq[aux]--;
                f = 0;
            }
        }
        return ans;
    }
};