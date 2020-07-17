/**
 * Created by Tekiter
 * 
 * 구간의 합을 구하고, Lazy Population이 적용된 세그먼트 트리이다.
 * 
 */

#include <vector>

using namespace std;

template <class T>
class SegmentTree {
public:
	int n;
	vector<T> tree;
	vector<T> lazy;
	SegmentTree(const vector<T>& arr) {
		n = arr.size();
		tree.assign(n*4, 0);
		lazy.assign(n*4, 0);
		init(arr, 0, n-1, 1);
	}



	T query(int al, int ar, int cur, int cl, int cr) {
		update_lazy(cur, cl, cr);
		if (cr < al || ar < cl) {
			return 0;
		}
		if (al <= cl && cr <= ar) {
			return tree[cur];
		}

		int mid = (cl + cr) / 2;
		return query(al, ar, cur*2, cl, mid) + query(al, ar, cur*2+1, mid+1, cr);
	}

	T query(int left, int right) {
		return query(left, right, 1, 0, n-1);
	}

	T update(int idx, T val, int cur, int cl, int cr) {
		update_lazy(cur, cl, cr);
		if (cr < idx || idx < cl) {
			return tree[cur];
		}
		if (cl == cr) {
			return tree[cur] = val;
		}

		int mid = (cl + cr) / 2;
		return tree[cur] = update(idx, val, cur*2, cl, mid) + update(idx, val, cur*2+1, mid+1, cr);
	}

	T update(int idx, T val) {
		return update(idx, val, 1, 0, n-1);
	}


	void update_range(int al, int ar, T diff, int cur, int cl, int cr) {
		update_lazy(cur, cl, cr);
		if (cr < al || ar < cl) {
			return;
		}

		if (al <= cl && cr <= ar) {
			tree[cur] += diff * (cr - cl + 1);
			if (cl != cr) {
				lazy[cur*2] += diff;
				lazy[cur*2+1] += diff;
			}
			return;
		}
		int mid = (cl + cr) / 2;
		update_range(al, ar, diff, cur*2, cl, mid);
		update_range(al, ar, diff, cur*2+1, mid+1, cr);
		tree[cur] = tree[cur*2] + tree[cur*2+1];
	}

	void update_range(int left, int right, T val) {
		update_range(left, right, val, 1, 0, n-1);
	}

	
private:

	T init(const vector<T>& arr, int l, int r, int cur) {
		if (l == r) {
			return tree[cur] = arr[l];
		}
		int mid = (l+r)/2;
		T lv = init(arr, l, mid, cur*2);
		T rv = init(arr, mid+1, r, cur*2+1);

		return tree[cur] = lv + rv; 
	}

	void update_lazy(int cur, int cl, int cr) {
		if (lazy[cur] != 0) {
			tree[cur] += lazy[cur] * (cr - cl + 1);
			if (cl != cr) {
				lazy[cur*2] += lazy[cur];
				lazy[cur*2+1] += lazy[cur];
			}
			lazy[cur] = 0;
		}
	}
};