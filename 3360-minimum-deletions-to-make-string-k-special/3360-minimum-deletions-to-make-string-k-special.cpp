class Solution {
public:
    int minimumDeletions(string s, int k) {
        vector<int> f(26, 0);
        for (int i = 0; i < s.length(); i++) {
            f[s[i] - 'a']++;
        }

        vector<int> v;
        for (int i = 0; i < 26; i++) {
            if (f[i] != 0) {
                v.push_back(f[i]);
            }
        }

        int ans = INT_MAX;
        for (int i = 0; i < v.size(); i++) {
            // Make v[i] as min freq
            int temp = 0;
            for (int j = 0; j < v.size(); j++) {
                if (v[j] < v[i]) {
                    temp += v[j]; // Delete all occurrences of this character
                } else if (v[j] > v[i] + k) {
                    temp += (v[j] - (v[i] + k)); // Delete excess occurrences
                }
            }
            ans = min(ans, temp);
        }

        return ans;
    }
};