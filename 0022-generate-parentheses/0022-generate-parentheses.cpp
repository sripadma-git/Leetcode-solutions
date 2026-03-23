#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    void backtrack(vector<string>& result, string current, int open, int close, int n) {
        // Base case: if the string length reaches 2*n, we found a valid combination
        if (current.length() == 2 * n) {
            result.push_back(current);
            return;
        }

        // Rule 1: We can always add an opening bracket if we have some left
        if (open < n) {
            backtrack(result, current + "(", open + 1, close, n);
        }

        // Rule 2: We can only add a closing bracket if it won't exceed the number of open ones
        if (close < open) {
            backtrack(result, current + ")", open, close + 1, n);
        }
    }

    vector<string> generateParenthesis(int n) {
        vector<string> result;
        backtrack(result, "", 0, 0, n);
        return result;
    }
};