#include <vector>
#include <algorithm>
#include <stack>

using namespace std;


int sccIdx;
int vertexIdx;
vector<int> scc;
vector<int> discovered;
stack<int> stk;

int dfs(int here, const vector<vector<int> >& graph) {
    int ret = discovered[here] = vertexIdx++;
    stk.push(here);

    for (auto there : graph[here]) {
        if (discovered[there] == -1) {
            ret = min(ret, dfs(there, graph));
        }
        else if (scc[there] == -1) {
            ret = min(ret, discovered[there]);
        }
    }

    if (ret == discovered[here]) {
        while (true) {
            int tp = stk.top();
            stk.pop();
            scc[tp] = sccIdx;
            if (tp == here) {
                break;
            }
        }
        sccIdx++;
    }

    return ret;
}

vector<int> makeScc(const vector<vector<int> >& graph) {
    int n = graph.size();
    scc.assign(n, -1);
    discovered.assign(n, -1);
    sccIdx = 0;
    vertexIdx = 0;

    for (int i = 0; i < n; i++) {
        if (discovered[i] == -1) {
            dfs(i, graph);
        }
    }
    return scc;
}