#include <cstdio>
#include <cstring>

using namespace std;

const int MAX = 100000;
const int MAXSUB = 20;

struct Node {
    int subnodes[MAXSUB];
    int sz;
    Node() : sz(0) {}
};

Node tree[MAX];
int left[MAX], right[MAX];
int bit[MAX + 10];
bool pick[MAX];
int n, m, u, v, x;
char op;

int cnt = 1;
inline void dfs(int node) {
    left[node] = cnt++;
    for (int i = 0; i < tree[node].sz; ++i)
        dfs(tree[node].subnodes[i]);
    right[node] = cnt;
}

inline void add(int idx, int x) {
    for (int i = idx; i <= n; i += (i & -i))
        bit[i] += x;
}

inline int sum(int idx) {
    int s = 0;
    for (int i = idx; i > 0; i -= (i & -i))
        s += bit[i];
    return s;
}

int main() {
    //freopen("in.txt", "r", stdin);
    scanf("%d", &n);
    for (int i = 0; i < n - 1; ++i) {
        scanf("%d%d", &u, &v);
        --u;
        --v;
        tree[u].subnodes[tree[u].sz++] = v;
    }
    dfs(0);

    memset(pick, false, sizeof(pick));
    for (int i = 0; i <= n; ++i) bit[i] = 1;
    for (int i = 1; i <= n; ++i) {
        int j = i + (i & -i);
        if (j <= n) bit[j] += bit[i];
    }
    scanf("%d\n", &m);
    for (int i = 0; i < m; ++i) {
        scanf("%c %d\n", &op, &x);
        --x;
        if (op == 'C') {
            add(left[x], pick[x] ? 1 : -1);
            pick[x] = !pick[x];
        } else
            printf("%d\n", sum(right[x] - 1) - sum(left[x] - 1));
    }

    return 0;
}