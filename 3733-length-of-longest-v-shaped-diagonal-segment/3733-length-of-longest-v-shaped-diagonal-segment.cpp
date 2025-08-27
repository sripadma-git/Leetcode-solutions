class Solution {
public:
    int lenOfVDiagonal(vector<vector<int>>& grid) {
          int n = grid.size(), m = grid[0].size();

        // 4 diagonal directions: ↗, ↘, ↙, ↖
        vector<pair<int,int>> dirs = {{-1,1},{1,1},{1,-1},{-1,-1}};
        int cw[4] = {1,2,3,0}; // clockwise mapping

        auto inb = [&](int i,int j){ return 0<=i && i<n && 0<=j && j<m; };

        // DP tables
        vector endLen(4, vector(n, vector<int>(m,0)));   // longest valid run ending at (i,j) in dir d
        vector steps(4, vector(n, vector<int>(m,-1)));   // steps since starting '1' (to know next expected value)

        // Order that guarantees predecessor is computed first (for each direction)
        auto iter_order = [&](int d){
            auto [dx,dy] = dirs[d];
            vector<pair<int,int>> cells;
            if (dx>0) {
                for (int i=0;i<n;i++) {
                    if (dy>0) for (int j=0;j<m;j++) cells.push_back({i,j});
                    else      for (int j=m-1;j>=0;j--) cells.push_back({i,j});
                }
            } else {
                for (int i=n-1;i>=0;i--) {
                    if (dy>0) for (int j=0;j<m;j++) cells.push_back({i,j});
                    else      for (int j=m-1;j>=0;j--) cells.push_back({i,j});
                }
            }
            return cells;
        };

        // Build straight (no-turn) runs that start at '1' and follow 1,2,0,2,0...
        for (int d=0; d<4; ++d) {
            auto [dx,dy] = dirs[d];
            for (auto [i,j] : iter_order(d)) {
                int v = grid[i][j];
                if (v==1) { endLen[d][i][j]=1; steps[d][i][j]=0; }
                else {
                    int pi=i-dx, pj=j-dy;
                    if (inb(pi,pj) && endLen[d][pi][pj]>0) {
                        int k = steps[d][pi][pj];
                        int need = ((k+1)&1) ? 2 : 0; // next expected value
                        if (v==need) { endLen[d][i][j]=endLen[d][pi][pj]+1; steps[d][i][j]=k+1; }
                    }
                }
            }
        }

        // Continuation tables after a clockwise turn: alternating runs starting at current cell
        vector from0(4, vector(n, vector<int>(m,0))); // start with 0 then 2,0,2...
        vector from2(4, vector(n, vector<int>(m,0))); // start with 2 then 0,2,0...

        auto iter_reverse = [&](int d){
            auto [dx,dy] = dirs[d];
            vector<pair<int,int>> cells;
            if (dx>0) {
                for (int i=n-1;i>=0;i--) {
                    if (dy>0) for (int j=m-1;j>=0;j--) cells.push_back({i,j});
                    else      for (int j=0;j<m;j++)    cells.push_back({i,j});
                }
            } else {
                for (int i=0;i<n;i++) {
                    if (dy>0) for (int j=m-1;j>=0;j--) cells.push_back({i,j});
                    else      for (int j=0;j<m;j++)    cells.push_back({i,j});
                }
            }
            return cells;
        };

        for (int d=0; d<4; ++d) {
            auto [dx,dy] = dirs[d];
            for (auto [i,j] : iter_reverse(d)) {
                int v = grid[i][j];
                int ni=i+dx, nj=j+dy;
                if (v==0) {
                    int best=1;
                    if (inb(ni,nj) && grid[ni][nj]==2) best = 1 + from2[d][ni][nj];
                    from0[d][i][j]=best;
                } else if (v==2) {
                    int best=1;
                    if (inb(ni,nj) && grid[ni][nj]==0) best = 1 + from0[d][ni][nj];
                    from2[d][i][j]=best;
                }
            }
        }

        int ans = 0;

        // Combine: either no turn, or one clockwise turn then continue
        for (int d=0; d<4; ++d) {
            for (int i=0;i<n;i++) for (int j=0;j<m;j++) {
                int t = endLen[d][i][j];
                if (!t) continue;
                ans = max(ans, t); // no-turn case

                int k = steps[d][i][j];
                int needNext = ((k+1)&1) ? 2 : 0; // expected value after (i,j)
                int nd = cw[d];                  // clockwise direction
                int x = i + dirs[nd].first, y = j + dirs[nd].second;
                if (inb(x,y)) {
                    int cont = (needNext==2) ? from2[nd][x][y] : from0[nd][x][y];
                    ans = max(ans, t + cont);
                }
            }
        }

        return ans;
    }
};