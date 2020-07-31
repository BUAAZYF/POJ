#include <algorithm>
#include <cstdio>
#include <vector>

using namespace std;

const int INF = 0x3f3f3f3f;
const int MAXM = 205;
const int MAXN = 25;

inline int min(int a, int b) {
    return a <= b ? a : b;
}

inline int max(int a, int b) {
    return a >= b ? a : b;
}

int t, m, n, c, x, y, val, row, col;
char op;
int budgets[MAXM][MAXN];
struct cmp {
    int greater, less;
} cmps[MAXM][MAXN];
vector<int> col_points[MAXM];
int row_points_end[MAXN];

bool dfs(int x, int y_idx) {
    if (x == m && y_idx == col_points[x].size()) {
        for (int i = 1; i <= m; ++i)
            if (budgets[i][0] != 0) return false;
        for (int j = 1; j <= n; ++j)
            if (budgets[0][j] != 0) return false;
        return true;
    }
    if (y_idx == col_points[x].size()) return dfs(x + 1, 0);
    int y = col_points[x][y_idx];
    if (y_idx == col_points[x].size() - 1) {
        if (cmps[x][y].greater >= budgets[x][0] || budgets[x][0] >= cmps[x][y].less) return false;
        if (budgets[0][y] < budgets[x][0]) return false;
        budgets[x][y] = budgets[x][0];
        budgets[0][y] -= budgets[x][0];
        budgets[x][0] = 0;
        if (dfs(x, y_idx + 1)) return true;
        budgets[x][0] = budgets[x][y];
        budgets[0][y] += budgets[x][y];
        budgets[x][y] = -1;
        return false;
    }
    if (row_points_end[y] == x) {
        if (cmps[x][y].greater >= budgets[0][y] || budgets[0][y] >= cmps[x][y].less) return false;
        if (budgets[0][y] > budgets[x][0]) return false;
        budgets[x][y] = budgets[0][y];
        budgets[x][0] -= budgets[0][y];
        budgets[0][y] = 0;
        if (dfs(x, y_idx + 1)) return true;
        budgets[0][y] = budgets[x][y];
        budgets[x][0] += budgets[0][y];
        budgets[x][y] = -1;
        return false;
    }
    for (int val = cmps[x][y].greater + 1; val < cmps[x][y].less; ++val) {
        if (val > budgets[x][0] || val > budgets[0][y]) return false;
        budgets[x][y] = val;
        budgets[x][0] -= val;
        budgets[0][y] -= val;
        if (dfs(x, y_idx + 1)) return true;
        budgets[x][y] = -1;
        budgets[x][0] += val;
        budgets[0][y] += val;
    }
    return false;
}

int main() {
    // freopen("in.txt", "r", stdin);
    scanf("%d", &t);
    while (t-- > 0) {
        scanf("%d%d", &m, &n);
        for (int i = 1; i <= m; ++i)
            for (int j = 1; j <= n; ++j) {
                budgets[i][j] = -1;
                cmps[i][j].greater = -1;
                cmps[i][j].less = INF;
            }
        row = col = 0;
        bool imp = false;
        for (int i = 1; i <= m; ++i) {
            row_points_end[i] = -1;
            scanf("%d", &budgets[i][0]);
            if (budgets[i][0] < 0) imp = true;
            row += budgets[i][0];
        }
        for (int j = 1; j <= n; ++j) {
            col_points[j].clear();
            scanf("%d", &budgets[0][j]);
            if (budgets[0][j] < 0) imp = true;
            col += budgets[0][j];
        }
        scanf("%d", &c);
        while (c-- > 0) {
            scanf("%d %d %c %d", &x, &y, &op, &val);
            if (op == '=') {
                if (val < 0) {
                    imp = true;
                    continue;
                }
                if (x != 0 && y != 0) {
                    if (budgets[x][y] == -1 || budgets[x][y] == val)
                        budgets[x][y] = val;
                    else
                        imp = true;
                } else if (x == 0 && y != 0) {
                    for (int i = 1; i <= m; ++i) {
                        if (budgets[i][y] == -1 || budgets[i][y] == val)
                            budgets[i][y] = val;
                        else {
                            imp = true;
                            break;
                        }
                    }
                } else if (y == 0 && x != 0) {
                    for (int j = 1; j <= n; ++j) {
                        if (budgets[x][j] == -1 || budgets[x][j] == val)
                            budgets[x][j] = val;
                        else {
                            imp = true;
                            break;
                        }
                    }
                } else {
                    for (int i = 1; i <= m; ++i) {
                        for (int j = 1; j <= n; ++j) {
                            if (budgets[i][j] == -1 || budgets[i][j] == val)
                                budgets[i][j] = val;
                            else {
                                imp = true;
                                break;
                            }
                        }
                    }
                }
            } else if (op == '>') {
                if (val < 0) continue;
                if (x != 0 && y != 0) {
                    cmps[x][y].greater = max(cmps[x][y].greater, val);
                } else if (x == 0 && y != 0) {
                    for (int i = 1; i <= m; ++i) cmps[i][y].greater = max(cmps[i][y].greater, val);
                } else if (y == 0 && x != 0) {
                    for (int j = 1; j <= n; ++j) cmps[x][j].greater = max(cmps[x][j].greater, val);
                } else {
                    for (int i = 1; i <= m; ++i)
                        for (int j = 1; j <= n; ++j)
                            cmps[i][j].greater = max(cmps[i][j].greater, val);
                }
            } else if (op == '<') {
                if (val <= 0) {
                    imp = true;
                    continue;
                }
                if (x != 0 && y != 0) {
                    cmps[x][y].less = min(cmps[x][y].less, val);
                } else if (x == 0 && y != 0) {
                    for (int i = 1; i <= m; ++i) cmps[i][y].less = min(cmps[i][y].less, val);
                } else if (y == 0 && x != 0) {
                    for (int j = 1; j <= n; ++j) cmps[x][j].less = min(cmps[x][j].less, val);
                } else {
                    for (int i = 1; i <= m; ++i)
                        for (int j = 1; j <= n; ++j)
                            cmps[i][j].less = min(cmps[i][j].less, val);
                }
            }
        }
        if (row != col || imp) {
            printf("IMPOSSIBLE\n\n");
            continue;
        }
        for (int i = 1; i <= m; ++i) {
            if (imp) break;
            for (int j = 1; j <= n; ++j) {
                if (budgets[i][j] != -1) {
                    if (cmps[i][j].greater >= budgets[i][j] || cmps[i][j].less <= budgets[i][j]) imp = true;
                    budgets[0][j] -= budgets[i][j];
                    budgets[i][0] -= budgets[i][j];
                    if (budgets[0][j] < 0 || budgets[i][0] < 0) imp = true;
                }
            }
            for (int j = 1; j <= n; ++j) {
                if (budgets[i][j] == -1) {
                    if (cmps[i][j].greater >= cmps[i][j].less) imp = true;
                    col_points[i].push_back(j);
                    row_points_end[j] = i;
                }
            }
        }
        if (imp) {
            printf("IMPOSSIBLE\n\n");
            continue;
        }
        if (dfs(1, 0)) {
            for (int i = 1; i <= m; ++i) {
                for (int j = 1; j < n; ++j) printf("%d ", max(0, budgets[i][j]));
                printf("%d\n", max(0, budgets[i][n]));
            }
            printf("\n");
        } else
            printf("IMPOSSIBLE\n\n");
    }

    return 0;
}