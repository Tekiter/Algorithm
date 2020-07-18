/**
 * Created by Tekiter
 * 
 * https://www.acmicpc.net/problem/11437 문제의 풀이
 *
 */

#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <cassert>
#include <queue>

using namespace std;

#define RANGE(x, n) (int x = 0; x < n; x++)
#define FASTIOS ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

#ifdef BOJ
#define endl	'\n'
#endif

constexpr int INF = 0x3ffffffe;

typedef pair<int, int> intpair;

class SegmentTree {
	int n;
	vector<intpair> tree;

public:
	SegmentTree(const vector<intpair>& arr) {
		n = arr.size();
		tree.assign(n*4, {INF, -1});
		init(arr, 1, 0, n-1);
	}

	intpair init(const vector<intpair>& arr, int cur, int cl, int cr) {
		if (cl == cr) {
			return tree[cur] = arr[cl];
		}

		int mid = (cl + cr) / 2;
		intpair lv = init(arr, cur*2, cl, mid);
		intpair rv = init(arr, cur*2+1, mid+1, cr);
		return tree[cur] = min(lv, rv);
	}

	intpair query(int al, int ar, int cur, int cl, int cr) {
		if (cr < al || ar < cl) {
			return {INF, -1};
		}
		if (al <= cl && cr <= ar) {
			return tree[cur];
		}

		int mid = (cl + cr) / 2;

		return min(
			query(al, ar, cur*2, cl, mid),
			query(al, ar, cur*2+1, mid+1, cr)
		);
	}

	intpair query(int left, int right) {
		return query(left, right, 1, 0, n-1);
	}

	
};

int n;
vector<vector<int> > tree;
vector<pair<int, int> > arr;
vector<bool> visited;
vector<int> conv;

void dfs(int cur, int depth) {
	visited[cur] = true;
	arr.push_back({depth, cur});
	conv[cur] = arr.size() - 1;

	for (auto v : tree[cur]) {
		if (!visited[v]) {
			dfs(v, depth+1);
			arr.push_back({depth, cur});
		}
	}
}

int main(int argc, char **argv) {
    FASTIOS
	
	cin >> n;
	tree.assign(n, vector<int>());
	for RANGE(i, n-1) {
		int a, b;
		cin >> a >> b;
		a--, b--;
		tree[a].push_back(b);
		tree[b].push_back(a);
	}

	visited.assign(n, false);
	conv.assign(n, -1);
	dfs(0, 0);


	SegmentTree segtree(arr);

	int m;
	cin >> m;
	for RANGE(i, m) {
		int a, b;
		cin >> a >> b;
		a--, b--;
		if (conv[a] > conv[b]) {
			a^=b;b^=a;a^=b;
		}
		// assert(conv[a] <= conv[b]);
		auto v = segtree.query(conv[a], conv[b]);
		cout << v.second+1 << endl;
	}
} 