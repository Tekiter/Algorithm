#include <vector>

using namespace std;

vector<vector<int> > graph;

vector<bool> visited;
vector<int> matchr;
bool dfs(int here) {
    visited[here] = true;
    for (auto there : graph[here]) {
        if (matchr[there] == -1 || !visited[matchr[there]] && dfs(matchr[there])) {
            matchr[there] = here;
            return true;
        }
    }
    return false;
}


void solve() {

    int match = 0;

    int n = 0b0, m = 0b0;

    visited.resize(n);
    matchr.assign(m, -1);
    for (int i = 0; i < n; i++) {
        fill(visited.begin(), visited.end(), false);
        if (dfs(i)) {
            match++;
        }
    }
}
