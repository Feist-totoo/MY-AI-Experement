#include <iostream>
#include <vector>
#include <queue>

using namespace std;

typedef long long ll;

struct Point { ll x, y; };
struct State { int u, redUsed; };

ll get_dist_sq(Point a, Point b) {
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

int main() {
    int n, m;
    ll r1, r2;
    if (!(cin >> n >> m >> r1 >> r2)) return 0;

    vector<Point> pts(n + 1);
    for (int i = 1; i <= n; ++i) cin >> pts[i].x >> pts[i].y;

    ll r1_sq = r1 * r1;
    ll r2_sq = r2 * r2;

    // dist[点][是否使用过红瓶] = 消耗蓝瓶数
    vector<vector<int>> dist(n + 1, vector<int>(2, -1));
    queue<State> q;

    dist[1][0] = 0;
    q.push({1, 0});

    while (!q.empty()) {
        State cur = q.front();
        q.pop();

        for (int v = 1; v <= n; ++v) {
            if (cur.u == v) continue;
            ll d2 = get_dist_sq(pts[cur.u], pts[v]);

            // 1. 尝试用蓝瓶 (距离 <= r1)
            if (d2 <= r1_sq) {
                if (dist[v][cur.redUsed] == -1 || dist[v][cur.redUsed] > dist[cur.u][cur.redUsed] + 1) {
                    dist[v][cur.redUsed] = dist[cur.u][cur.redUsed] + 1;
                    q.push({v, cur.redUsed});
                }
            }

            // 2. 尝试用红瓶 (距离 <= r2，且当前还没用过红瓶)
            if (cur.redUsed == 0 && d2 <= r2_sq) {
                if (dist[v][1] == -1 || dist[v][1] > dist[cur.u][0]) {
                    dist[v][1] = dist[cur.u][0]; // 红色药瓶不计入蓝瓶消耗
                    q.push({v, 1});
                }
            }
        }
    }

    if (dist[n][0] != -1 && dist[n][0] <= m) {
        cout << 0 << " " << dist[n][0] << endl;
    } else if (dist[n][1] != -1 && dist[n][1] <= m) {
        cout << 1 << " " << dist[n][1] << endl;
    } else {
        cout << "-1 -1" << endl;
    }

    return 0;
}