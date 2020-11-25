#include <cstdio>
#include <cstring>
#include <set>

using namespace std;

const int MAXN = 1005;

int N, idx, ans;
bool flag, visited[2 * MAXN];
int uni[2 * MAXN], opt[2 * MAXN], cnt[2 * MAXN];
char state[20];

int inline max(int a, int b) {
    return a >= b ? a : b;
}
int find(int x) {
    if (x != uni[x]) uni[x] = find(uni[x]);
    return uni[x];
}

void merge(int x, int y) {
    x = find(x);
    y = find(y);
    if (x < y) uni[y] = x;
    else uni[x] = y;
}

bool same(int x, int y) {
    return find(x) == find(y);
}

int main() {
    while (scanf("%d", &N) != EOF && N) {
        for (int i = 1; i <= 2 * N; ++i) uni[i] = i;
        flag = false;
        for (int i = 1; i <= N; ++i) {
            scanf("%s", &state[0]);
            scanf("%d", &idx);
            scanf("%s", &state[0]);
            scanf("%s", &state[0]);
            if (flag) continue;
            if (strcmp(state, "true.") == 0) {
                if (same(i, idx + N) || same(i + N, idx)) flag = true;
                else merge(i, idx), merge(i + N, idx + N);
            } else {
                if (same(i, idx) || same(i + N, idx + N)) flag = true;
                else merge(i, idx + N), merge(i + N, idx);
            }
        }
        if (flag) printf("Inconsistent\n");
        else {
            memset(cnt, 0, sizeof(cnt));
            memset(visited, false, sizeof(visited));
            for (int i = 1; i <= N; ++i) {
                ++cnt[find(i)];
                opt[find(i)] = find(i + N);
                opt[find(i + N)] = find(i);
            }
            ans = 0;
            for (int i = 1; i <= N; ++i) {
                if (visited[find(i)] || visited[find(i + N)]) continue;
                ans += max(cnt[find(i)], cnt[find(i + N)]);
                visited[find(i)] = visited[find(i + N)] = true;
            }
            printf("%d\n", ans);
        }
    }

    return 0;
}
