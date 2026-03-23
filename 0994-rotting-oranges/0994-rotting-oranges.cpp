#include <vector>
#include <queue>

using namespace std;

class Solution {
public:
    int orangesRotting(vector<vector<int>>& grid) {
        int rows = grid.size();
        int cols = grid[0].size();
        queue<pair<int, int>> q;
        int freshOranges = 0;

        // Step 1: Initial scan for rotten and fresh oranges
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (grid[i][j] == 2) {
                    q.push({i, j});
                } else if (grid[i][j] == 1) {
                    freshOranges++;
                }
            }
        }

        // If there are no fresh oranges, 0 minutes are needed
        if (freshOranges == 0) return 0;

        int minutes = 0;
        vector<pair<int, int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

        // Step 2: BFS traversal
        while (!q.empty()) {
            int size = q.size();
            bool rottedAny = false;

            for (int i = 0; i < size; ++i) {
                pair<int, int> curr = q.front();
                q.pop();

                for (auto& dir : directions) {
                    int r = curr.first + dir.first;
                    int c = curr.second + dir.second;

                    // If neighbor is within bounds and is a fresh orange
                    if (r >= 0 && r < rows && c >= 0 && c < cols && grid[r][c] == 1) {
                        grid[r][c] = 2; // Make it rotten
                        q.push({r, c});
                        freshOranges--;
                        rottedAny = true;
                    }
                }
            }
            // Only increment time if we actually spread the rot in this layer
            if (rottedAny) minutes++;
        }

        // Step 3: Check if any fresh oranges are left unreachable
        return freshOranges == 0 ? minutes : -1;
    }
};