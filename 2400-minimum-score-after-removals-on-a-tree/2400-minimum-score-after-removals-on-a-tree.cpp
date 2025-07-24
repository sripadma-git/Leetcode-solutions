class Solution {
public:
    int minimumScore(vector<int>& nums, vector<vector<int>>& edges) {
        int n = nums.size();
        vector<vector<int>> g(n);
        for (auto& e : edges) {
            int a = e[0], b = e[1];
            g[a].push_back(b);
            g[b].push_back(a);
        }

        vector<int> subxor(n), in(n), out(n), par(n, -1);
        int time = 0;

        function<void(int, int)> dfs = [&](int u, int p) {
            in[u] = time++;
            subxor[u] = nums[u];
            par[u] = p;
            for (int v : g[u]) {
                if (v != p) {
                    dfs(v, u);
                    subxor[u] ^= subxor[v];
                }
            }
            out[u] = time++;
        };

        dfs(0, -1);
        int total = subxor[0], ans = INT_MAX;

        auto is_ancestor = [&](int u, int v) {
            return in[u] <= in[v] && out[v] <= out[u];
        };

        for (int i = 1; i < n; i++) {
            for (int j = 1; j < n; j++) {
                if (i == j) continue;

                int x = 0, y = 0, z = 0;
                if (is_ancestor(i, j)) {
                    x = subxor[j];
                    y = subxor[i] ^ subxor[j];
                    z = total ^ subxor[i];
                } else if (is_ancestor(j, i)) {
                    x = subxor[i];
                    y = subxor[j] ^ subxor[i];
                    z = total ^ subxor[j];
                } else {
                    x = subxor[i];
                    y = subxor[j];
                    z = total ^ x ^ y;
                }

                int mx = max({x, y, z});
                int mn = min({x, y, z});
                ans = min(ans, mx - mn);
            }
        }

        return ans; 
    }
};