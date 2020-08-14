#include <vector>

using namespace std;

template <class T>
class SegmentTree {
public:
	int n;
	vector<vector<T> > tree;
	SegmentTree(int n) {
		this->n = n;
		tree.assign(n*4, {});
	}


	T query(int al, int ar, int cur, int cl, int cr, T k) {
		if (cr < al || ar < cl) {
			return 0;
		}
		if (al <= cl && cr <= ar) {
			return tree[cur].end() - upper_bound(tree[cur].begin(), tree[cur].end(), k);
		}

		int mid = (cl + cr) / 2;
		return query(al, ar, cur*2, cl, mid, k) + query(al, ar, cur*2+1, mid+1, cr, k);
	}

	T query(int left, int right, T k) {
		return query(left, right, 1, 0, n-1, k);
	}

	void update(int idx, T val, int cur, int cl, int cr) {
		if (cr < idx || idx < cl) {
			return;
		}
		if (cl == cr) {
			tree[cur].push_back(val);
            return;
		}

        tree[cur].push_back(val);
		int mid = (cl + cr) / 2;
		update(idx, val, cur*2, cl, mid);
        update(idx, val, cur*2+1, mid+1, cr);
	}

	void update(int idx, T val) {
		update(idx, val, 1, 0, n-1);
	}

    void sort(int cl, int cr, int cur) {
        if (cl == cr) {
            return;
        }
        std::sort(tree[cur].begin(), tree[cur].end());

        int mid = (cl + cr) / 2;
        sort(cl, mid, cur*2);
        sort(mid+1, cr, cur*2+1);
    }

    void sort() {
        sort(0, n-1, 1);
    }

};