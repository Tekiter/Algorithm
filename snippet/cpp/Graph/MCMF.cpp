#include <iostream>
#include <vector>
#include <queue>

using namespace std;

constexpr int INF = 0x3ffffffe;

// cost 인접행렬은 (u, v) = c 일때 (v, u) = -c 여야함

pair<int, int> mcmf(const vector<vector<int> >& cap, const vector<vector<int> >& cost, int source, int sink) {
    int n = cap.size();
    vector<vector<int> > flow;
    flow.assign(n, vector<int>(n, 0));

    int maxflow = 0, mincost = 0;

    while (true) {
        vector<int> parent(n, -1);
        queue<int> q;
        vector<int> dist(n, INF);
        vector<bool> inqueue(n, false);

        q.push(source);
        inqueue[source] = true;
        dist[source] = 0;

        while (!q.empty()) {
            int here = q.front();
            q.pop();
            inqueue[here] = false;

            for (int there = 0; there < n; there++) {
                if (here == there) {
                    continue;
                }

                if (cap[here][there] - flow[here][there] > 0 && dist[here] + cost[here][there] < dist[there]) {
                    dist[there] = dist[here] + cost[here][there];
                    parent[there] = here;
                    if (!inqueue[there]) {
                        q.push(there);
                        inqueue[there] = true;
                    }
                }
            }
        }

        if (parent[sink] == -1) {
            break;
        }

        int flowamount = INF;
        for (int v = sink; v != source; v = parent[v]) {
            flowamount = min(flowamount, cap[parent[v]][v] - flow[parent[v]][v]);
        }

        for (int v = sink; v != source; v = parent[v]) {
            mincost += flowamount * cost[parent[v]][v];
            flow[parent[v]][v] += flowamount;
            flow[v][parent[v]] -= flowamount;
        }

        maxflow += flowamount;
    }
    return {maxflow, mincost};
}

