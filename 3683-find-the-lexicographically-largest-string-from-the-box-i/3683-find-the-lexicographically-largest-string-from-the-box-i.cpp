class Solution {
public:
    string answerString(string word, int numFriends) {
        if (numFriends == 1) return word;
        int n = word.size();
        int limit = n - numFriends + 1;
        vector<int> arr(n);
        for (int idx = 0; idx < n; ++idx) {
            arr[idx] = static_cast<unsigned char>(word[idx]);
        }
        int i = 0, j = 1, k = 0;
        while (j + k < n) {
            if (arr[i + k] == arr[j + k]) {
                ++k;
            } else if (arr[i + k] < arr[j + k]) {
                i = j;
                j = i + 1;
                k = 0;
            } else {
                j = j + k + 1;
                k = 0;
            }
        }
        return word.substr(i, limit); 
    }
};