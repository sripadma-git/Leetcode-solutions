class Solution {
    // Segment Tree Arrays
    vector<int> count;      // How many active rectangles cover this node
    vector<double> length;  // The actual physical length covered by this node
    vector<double> X;       // Coordinate compressed X values
    // Update function for Segment Tree
    // node: current tree node index
    // start, end: index range in the X vector (defines the X-interval covered by this node)
    // l, r: index range of the update query
    // val: +1 (add rectangle) or -1 (remove rectangle)
    void update(int node, int start, int end, int l, int r, int val) {
        if (l >= end || r <= start) return; // Out of range
        if (l <= start && end <= r) {
            count[node] += val;
        } else {
            int mid = (start + end) / 2;
            update(node * 2, start, mid, l, r, val);
            update(node * 2 + 1, mid, end, l, r, val);
        }
        // Calculate length for this node
        if (count[node] > 0) {
            // If this node is covered by at least one rectangle, its length is the full physical span
            length[node] = X[end] - X[start];
        } else if (end - start == 1) {
            // Leaf node with count 0 -> length is 0
            length[node] = 0;
        } else {
            // Internal node with count 0 -> sum of children
            length[node] = length[node * 2] + length[node * 2 + 1];
        }
    }
public:
    double separateSquares(vector<vector<int>>& squares) {
        // Step 1: Coordinate Compression for X-axis
        X.clear();
        for (auto& sq : squares) {
            X.push_back((double)sq[0]);
            X.push_back((double)sq[0] + sq[2]);
        }
        sort(X.begin(), X.end());
        X.erase(unique(X.begin(), X.end()), X.end());
        // Map original X values to their index in the compressed array
        // Using lower_bound during update is efficient enough
        int n_coords = X.size();
        // Step 2: Create Events for Vertical Sweep Line
        // Event: {y_coordinate, type (+1/-1), x_start, x_end}
        struct Event {
            double y;
            int type;
            double x1, x2;
            // Sort by Y
            bool operator<(const Event& other) const {
                return y < other.y;
            }
        };
        vector<Event> events;
        for (auto& sq : squares) {
            events.push_back({(double)sq[1], 1, (double)sq[0], (double)sq[0] + sq[2]});
            events.push_back({(double)sq[1] + sq[2], -1, (double)sq[0], (double)sq[0] + sq[2]});
        }
        sort(events.begin(), events.end());
        // Step 3: Initialize Segment Tree
        // Size needs to be 4 * number of elementary intervals
        count.assign(4 * n_coords, 0);
        length.assign(4 * n_coords, 0.0);
        // Step 4: Run Sweep Line
        // We will store the strips to calculate the split point later
        struct Strip {
            double y;       // Bottom y of this strip
            double height;  // Height of this strip (next_y - y)
            double width;   // Union width active in this strip
        };
        vector<Strip> strips;
        double total_area = 0;
        for (int i = 0; i < events.size(); ++i) {
            // Update Segment Tree with current event
            // Find indices in X array
            int l_idx = lower_bound(X.begin(), X.end(), events[i].x1) - X.begin();
            int r_idx = lower_bound(X.begin(), X.end(), events[i].x2) - X.begin();
            update(1, 0, n_coords - 1, l_idx, r_idx, events[i].type);
            // If this is not the last event, calculate area of the strip between this and next event
            if (i + 1 < events.size()) {
                double h = events[i+1].y - events[i].y;
                if (h > 0) {
                    double active_width = length[1]; // Root of segment tree holds total union width
                    total_area += active_width * h;
                    strips.push_back({events[i].y, h, active_width});
                }
            }
        }
        // Step 5: Find the Y where Area Below == Total / 2
        double target = total_area / 2.0;
        double current_area = 0;
        for (auto& strip : strips) {
            double strip_area = strip.width * strip.height;
            if (current_area + strip_area >= target) {
                // The answer is inside this strip
                double needed = target - current_area;
                // needed = width * extra_height
                // extra_height = needed / width
                return strip.y + (needed / strip.width);
            }
            current_area += strip_area;
        }
        return events.back().y; // Fallback (should not reach here)
    }
};