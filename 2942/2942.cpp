#include <cstdio>
#include <cstring>

using namespace std;

const int MAX = 1010;

int min(int a, int b) {
    return a <= b ? a : b;
}

int max(int a, int b) {
    return a >= b ? a : b;
}

int n, m, a, b, r, sp, cnt, ans;
bool hate[MAX][MAX], intable[MAX], flag;
int low[MAX], pre[MAX], color[MAX], st[MAX], block[MAX][MAX];

void dfs(int v) {
    st[sp++] = v;
    pre[v] = low[v] = ++cnt;
    for (int i = 0; i < n; ++i) {
        if (hate[v][i]) continue;
        if (pre[i] == 0) {
            dfs(i);
            low[v] = min(low[v], low[i]);
            if (low[i] >= pre[v]) {
                int k = 0;
                st[sp] = -1;
                block[r][0] = v;
                while (st[sp] != i) block[r][++k] = st[--sp];
                block[r][++k] = -1;
                if (k > 2) ++r;
            }
        } else low[v] = min(low[v], pre[i]);
    }
}

void dfs_block(int pnt, int v, int col) {
    if (flag) return;
    for (int i = 0; i < n; ++i) {
        if (!hate[v][i] && color[i] && i != pnt && i != v) {
            if (color[i] == 1) {
                color[i] = col;
                dfs_block(v, i, -col);
            } else if (color[i] == color[v]) {
                flag = true;
                return;
            }
        }
    }
}

void expell(int v) {
    int crt = 0;
    memset(color, 0, sizeof(color));
    while (block[v][crt] != -1) {
        color[block[v][crt]] = 1;
        ++crt;
    }
    flag = false;
    color[block[v][0]] = 2;
    dfs_block(-1, block[v][0], -2);
    crt = 0;
    while (block[v][crt] != -1) {
        color[block[v][crt]] = 0;
        if (flag) intable[block[v][crt]] = true;
        ++crt;
    }
}

int main() {
    freopen("in.txt", "r", stdin);
    while (scanf("%d%d", &n, &m) != EOF && n) {
        memset(&hate[0][0], false, MAX * MAX * sizeof(bool));
        while (m--) {
            scanf("%d%d", &a, &b);
            --a, --b;
            hate[a][b] = hate[b][a] = true;
        }
        r = sp = cnt = 0;
        memset(pre, 0, sizeof(pre));
        memset(low, 0, sizeof(low));
        for (int i = 0; i < n; ++i)
            if (pre[i] == 0) dfs(i);
        memset(intable, false, sizeof(intable));
        for (int i = 0; i < r; ++i) expell(i);
        ans = 0;
        for (int i = 0; i < n; ++i)
            if (!intable[i]) ++ans;
        printf("%d\n", ans);
    }

    return 0;
}