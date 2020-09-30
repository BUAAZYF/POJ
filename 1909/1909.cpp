#include <cstdio>
#include <cstring>
#include <utility>
#include <vector>

using namespace std;

const int MAX = 10005;

inline int abs(int a) {
    return a >= 0 ? a : -a;
}

int n, m, par, num, nxt, root, ans;
bool haspar[MAX];
struct node {
    int val;
    vector<int> nxt;
} trees[MAX];

pair<int, int> dfs(int root) {
    int val = 0, nodenum = 0;
    pair<int, int> cur;
    vector<int>& nxt = trees[root].nxt;
    for (int i = 0; i < nxt.size(); ++i) {
        cur = dfs(nxt[i]);
        val += cur.first;
        nodenum += cur.second;
    }
    ans += abs(trees[root].val + val - nodenum - 1);
    return make_pair(trees[root].val + val, nodenum + 1);
}

int main() {
    while (scanf("%d", &n) != EOF && n) {
        memset(haspar, false, sizeof(haspar));
        for (int i = 0; i < n; ++i) {
            scanf("%d%d%d", &par, &num, &m);
            trees[par].val = num;
            trees[par].nxt.clear();
            for (int j = 0; j < m; ++j) {
                scanf("%d", &nxt);
                trees[par].nxt.push_back(nxt);
                haspar[nxt] = true;
            }
        }
        root = 0;
        for (int i = 1; i <= n; ++i) {
            if (!haspar[i]) {
                root = i;
                break;
            }
        }
        ans = 0;
        dfs(root);
        printf("%d\n", ans);
    }

    return 0;
}