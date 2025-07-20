class Solution {
public:
    vector<string> removeSubfolders(vector<string>& folder) {
      sort(folder.begin(), folder.end(), [&](string s1, string s2){
            return s1.size() < s2.size();
        });

        unordered_map<string, int> mp;
        vector<string> ans;

        for (auto it : folder) {
            string temp;
            bool flag = true, isSubfolder = false;
            int i = 0;
            while (i < it.size()) {
                if (flag) {
                    temp += it[i++];
                    flag = false;
                } else {
                    while (i < it.size() && isalpha(it[i])) {
                        temp += it[i++];
                    }
                    flag = true;
                }
                if (mp.find(temp) != mp.end()) {
                    isSubfolder = true;
                    break;
                }
            }
            if (isSubfolder) continue;
            ans.push_back(it);
            mp[it]++;
        }
        return ans;   
    }
};