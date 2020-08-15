#include <vector>
#include <queue>

using namespace std;

typedef long long ll;
constexpr int INF = 0x3ffffffe;

int networkFlow(const vector<vector<int> >& cap, int source, int sink) {
    int n = cap.size();
    vector<vector<int> > flow;
    flow.assign(n, vector<int>(n, 0));

    int ret = 0;

    while (true) {
        vector<int> parent(n, -1);
        queue<int> q;

        parent[source] = source;
        q.push(source);

        while (!q.empty() && parent[sink] == -1) {
            int here = q.front();
            q.pop();

            for (int there = 0; there < n; there++) {
                if (here == there) {
                    continue;
                }
                if (parent[there] == -1 && cap[here][there] - flow[here][there] > 0) {
                    parent[there] = here;
                    q.push(there);
                }
            }
        }

        if (parent[sink] == -1) {
            break;
        }

        int howmany = INF;
        for (int v = sink; v != source; v = parent[v]) {
            howmany = min(howmany, cap[parent[v]][v] - flow[parent[v]][v]);
        }

        for (int v = sink; v != source; v = parent[v]) {
            flow[parent[v]][v] += howmany;
            flow[v][parent[v]] -= howmany;
        }

        ret += howmany;
    }
    return ret;
}