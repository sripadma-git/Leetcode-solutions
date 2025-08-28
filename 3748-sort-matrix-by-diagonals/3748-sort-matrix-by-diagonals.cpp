class Solution {
public:
    vector<vector<int>> sortMatrix(vector<vector<int>>& grid) {
     int n = grid.size();
        unordered_map<int, vector<int>> diag;

        // Collect elements
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                int key = i - j;
                diag[key].push_back(grid[i][j]);
            }
        }

        // Sort each diagonal
        for (auto &p : diag) {
            int key = p.first;
            if (key >= 0) { // bottom-left incl. main diagonal
                sort(p.second.begin(), p.second.end(), greater<int>());
            } else { // top-right
                sort(p.second.begin(), p.second.end());
            }
        }

        // Refill matrix
        unordered_map<int, int> idx; // track position in each diagonal
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                int key = i - j;
                grid[i][j] = diag[key][idx[key]++];
            }
        }

        return grid;
   
    }
};