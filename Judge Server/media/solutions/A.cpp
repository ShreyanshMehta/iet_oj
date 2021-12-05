#include<bits/stdc++.h>
using namespace std;

#define ll long long

vector<vector<int>>adj;

void bfs(int x, vector<int>&dis) {
    dis.assign(dis.size(), 1e9);
    dis[x] = 0;
    queue<int>q;
    q.push(x);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (auto v : adj[u]) {
            if (dis[v] > dis[u] + 1) {
                dis[v] = dis[u] + 1;
                q.push(v);
            }
        }
    }
}

int main() {
    int tc = 1;
    cin >> tc;
    while (tc--) {
        int n, q;
        cin >> n >> q;
        adj.assign(n, vector<int>({}));
        for (int i = 0; i < n - 1; i++) {
            int u, v;
            cin >> u >> v;
            u--, v--;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        vector<int>dis(n);
        bfs(0, dis);
        int node = max_element(dis.begin(), dis.end()) - dis.begin();
        bfs(node, dis);
        ll diameter = *max_element(dis.begin(), dis.end());
        dis.assign(n, 1e9);
        priority_queue<int>que;
        for (int i = 0; i < n; i++) {
            if (adj[i].size() == 1) {
                que.push(i);
                dis[i] = 0;
            }
        }
        while (!que.empty()) {
            auto u = que.top();
            que.pop();
            for (auto v : adj[u]) {
                if (dis[v] > dis[u] + 1) {
                    dis[v] = dis[u] + 1;
                    que.push(v);
                }
            }
        }

        for (int i = 0; i < q; i++) {
            ll u, t;
            cin >> u >> t;
            ll ans = 0;
            if (t) ans += diameter - dis[u - 1];
            if (t - 1 >= 0) ans += diameter * (t - 1);
            cout << ans << " ";
        }
        cout << endl;
    }
}
