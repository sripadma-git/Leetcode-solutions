class Solution {
public:
  bool canFormPairs(vector<int>& nums, int p, int maxDiff) {
        int count = 0;
        int i = 0;
        int n = nums.size();
        while (i < n - 1) {
            if (nums[i + 1] - nums[i] <= maxDiff) {
                count++;
                i += 2;  // skip the next index to avoid reuse
            } else {
                i++;
            }
        }
        return count >= p;
    }

    int minimizeMax(vector<int>& nums, int p) {
        sort(nums.begin(), nums.end());
        int low = 0, high = nums.back() - nums.front();
        int ans = 0;

        while (low <= high) {
            int mid = (low + high) / 2;
            if (canFormPairs(nums, p, mid)) {
                ans = mid;
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }

        return ans;
    }
};