#include <algorithm>
#include <cmath>
#include <cstdio>

using namespace std;

const int MAX = 205;
const int INF = 0x3f3f3f3f;

int t, n;
bool updated;
int x[MAX], y[MAX];
double graph[MAX][MAX], dis[MAX];

int main() {
    t = 1;
    while (scanf("%d", &n) != EOF && n) {
        for (int i = 0; i < n; ++i) scanf("%d%d", &x[i], &y[i]);
        for (int i = 0; i < n; ++i) {
            graph[i][i] = 0;
            for (int j = i + 1; j < n; ++j)
                graph[i][j] = graph[j][i] = sqrt(pow(x[i] - x[j], 2) + pow(y[i] - y[j], 2));
            dis[i] = graph[0][i];
        }
        for (int k = 0; k < n; ++k) {
            updated = false;
            for (int i = 1; i < n; ++i) {
                for (int j = 1; j < n; ++j) {
                    if (dis[j] > max(dis[i], graph[i][j])) {
                        dis[j] = max(dis[i], graph[i][j]);
                        updated = true;
                    }
                }
            }
            if (!updated) break;
        }
        // ".f%"" is POJ G++ feature
        printf("Scenario #%d\nFrog Distance = %.3f\n\n", t++, dis[1]);
    }

    return 0;
}