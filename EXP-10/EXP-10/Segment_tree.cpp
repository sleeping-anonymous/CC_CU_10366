#include <bits/stdc++.h>
using namespace std;

class SegmentTree {
    vector<int> tree;
    int n;

public:
    SegmentTree(vector<int>& arr) {
        n = arr.size();
        tree.resize(4 * n);
        build(arr, 1, 0, n - 1);
    }

    // ── Build ────────────────────────────────────────────────────
    void build(vector<int>& arr, int node, int start, int end) {
        if (start == end) {
            tree[node] = arr[start];
            return;
        }
        int mid = (start + end) / 2;
        build(arr, 2 * node,     start, mid);
        build(arr, 2 * node + 1, mid + 1, end);
        tree[node] = tree[2 * node] + tree[2 * node + 1];  // change for min/max
    }

    // ── Point Update ─────────────────────────────────────────────
    void update(int node, int start, int end, int idx, int val) {
        if (start == end) {
            tree[node] = val;
            return;
        }
        int mid = (start + end) / 2;
        if (idx <= mid)
            update(2 * node,     start, mid,     idx, val);
        else
            update(2 * node + 1, mid + 1, end,   idx, val);
        tree[node] = tree[2 * node] + tree[2 * node + 1];
    }

    // ── Range Query ──────────────────────────────────────────────
    int query(int node, int start, int end, int l, int r) {
        if (r < start || end < l)        // completely outside
            return 0;                     // identity for sum (INT_MAX for min)
        if (l <= start && end <= r)       // completely inside
            return tree[node];
        int mid = (start + end) / 2;
        int left  = query(2 * node,     start, mid,     l, r);
        int right = query(2 * node + 1, mid + 1, end,   l, r);
        return left + right;
    }

    // ── Public wrappers ──────────────────────────────────────────
    void update(int idx, int val)  { update(1, 0, n - 1, idx, val); }
    int  query(int l, int r)       { return query(1, 0, n - 1, l, r); }
};


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    vector<int> arr = {1, 3, 5, 7, 9, 11};
    int n = arr.size();

    SegmentTree st(arr);

    // Query sum in range [1, 3]  →  3 + 5 + 7 = 15
    cout << "Sum [1,3] = " << st.query(1, 3) << "\n";   // 15

    // Update index 2 to 10
    st.update(2, 10);

    // Query again [1, 3]  →  3 + 10 + 7 = 20
    cout << "Sum [1,3] after update = " << st.query(1, 3) << "\n";  // 20

    // Full range query [0, 5]
    cout << "Sum [0,5] = " << st.query(0, 5) << "\n";   // 41

    return 0;
}