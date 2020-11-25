#include <algorithm>
#include <cmath>
#include <cstdio>
#include <map>
#include <vector>

using namespace std;

const int MAX = 205;

int sx, sy, ex, ey, n;
pair<int, int> cur;
map<pair<int, int>, int> stops_idx;
pair<int, int> stops[MAX];
vector<vector<int> > subways;
double mat[MAX][MAX];
double dis[MAX];
int used[MAX];

double caldis(int x1, int y1, int x2, int y2) {
    return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

int main() {
    scanf("%d%d%d%d", &sx, &sy, &ex, &ey);
    if (sx == ex && sy == ey) {
        printf("0\n");
        return 0;
    }
    stops_idx[make_pair(sx, sy)] = 0;
    stops_idx[make_pair(ex, ey)] = 1;
    stops[0] = make_pair(sx, sy);
    stops[1] = make_pair(ex, ey);
    n = 2;
    while (scanf("%d%d", &cur.first, &cur.second) != EOF) {
        subways.push_back(vector<int>());
        do {
            if (stops_idx.find(cur) == stops_idx.end()) {
                stops_idx[cur] = n;
                stops[n] = cur;
                ++n;
            }
            subways[subways.size() - 1].push_back(stops_idx[cur]);
        } while (scanf("%d%d", &cur.first, &cur.second) != EOF && cur.first != -1);
    }
    n = stops_idx.size();
    for (int k = 0; k < subways.size(); ++k) {
        vector<int>& sw = subways[k];
        for (int i = 0; i < sw.size() - 1; ++i) {
            int j = i + 1;
            mat[sw[i]][sw[j]] = mat[sw[j]][sw[i]] = caldis(stops[sw[i]].first, stops[sw[i]].second, stops[sw[j]].first, stops[sw[j]].second) / 40000.0;
        }
    }
    for (int i = 0; i < n; ++i)
        for (int j = i + 1; j < n; ++j)
            if (mat[i][j] == 0) mat[i][j] = mat[j][i] = caldis(stops[i].first, stops[i].second, stops[j].first, stops[j].second) / 10000.0;
    dis[0] = 0;
    for (int i = 1; i < n; ++i) dis[i] = mat[0][i];
    fill(used, used + n, false);
    used[0] = true;
    while (true) {
        int v = -1;
        for (int u = 1; u < n; ++u)
            if (!used[u] && (v == -1 || dis[u] < dis[v])) v = u;
        if (v == -1) break;
        used[v] = true;
        for (int u = 1; u < n; ++u) dis[u] = min(dis[u], dis[v] + mat[v][u]);
    }
    printf("%d\n", (int)round(dis[1] * 60));

    return 0;
}