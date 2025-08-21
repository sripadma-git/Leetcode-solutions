class Solution {
public:
    int m, n;
    vector<vector<int>> left; // stores consecutive 1s to the left

    int countEndingAt(int i, int j, vector<vector<int>>& mat) {
        if (i < 0 || j < 0 || mat[i][j] == 0) return 0;

        int total = 0;
        int minWidth = left[i][j];

        for (int k = i; k >= 0 && mat[k][j] == 1; --k) {
            minWidth = min(minWidth, left[k][j]);
            total += minWidth;
        }

        return total;
    }

    int numSubmat(vector<vector<int>>& mat) {
        m = mat.size();
        n = mat[0].size();
        left.assign(m, vector<int>(n, 0));

        // Precompute consecutive 1s to the left
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (mat[i][j] == 1) {
                    left[i][j] = (j == 0) ? 1 : left[i][j - 1] + 1;
                }
            }
        }

        int count = 0;
        // Apply recursive logic to each cell
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                count += countEndingAt(i, j, mat);
            }
        }

        return count;
    }
};