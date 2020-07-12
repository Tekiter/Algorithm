#include <vector>

using namespace std;

class SegmentTree {
public:
	int n;
	vector<int> tree;
	SegmentTree(const vector<int>& arr) {
		n = arr.size();
		tree.assign(n*4, 0);
		init(arr, 0, n-1, 1);
	}

	int init(const vector<int>& arr, int l, int r, int cur) {
		if (l == r) {
			return tree[cur] = arr[l];
		}
		int mid = (l+r)/2;
		int lv = init(arr, l, mid, cur*2);
		int rv = init(arr, mid+1, r, cur*2+1);

		return tree[cur] = lv + rv; 
	}

	int query(int al, int ar, int cur, int cl, int cr) {
		if (cr < al || ar < cl) {
			return 0;
		}
		if (al <= cl && cr <= ar) {
			return tree[cur];
		}

		int mid = (cl + cr) / 2;
		return query(al, ar, cur*2, cl, mid) + query(al, ar, cur*2+1, mid+1, cr);
	}

	int query(int left, int right) {
		return query(left, right, 1, 0, n-1);
	}

	int update(int idx, int val, int cur, int cl, int cr) {
		if (cr < idx || idx < cl) {
			return tree[cur];
		}
		if (cl == cr) {
			return tree[cur] = val;
		}

		int mid = (cl + cr) / 2;
		return tree[cur] = update(idx, val, cur*2, cl, mid) + update(idx, val, cur*2+1, mid+1, cr);
	}

	int update(int idx, int val) {
		return update(idx, val, 1, 0, n-1);
	}

};