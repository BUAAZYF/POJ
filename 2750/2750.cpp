#include <cstdio>

using namespace std;

const int MAX = 100005;

inline int min(int a, int b) {
    return a <= b ? a : b;
}

inline int max(int a, int b) {
    return a >= b ? a : b;
}

struct node {
    int sum;
    int minpref, minsuff, minseg;
    int maxpref, maxsuff, maxseg;
};

node combine(node a, node b) {
    node res;
    res.sum = a.sum + b.sum;
    res.minpref = min(a.minpref, a.sum + b.minpref);
    res.minsuff = min(b.minsuff, b.sum + a.minsuff);
    res.minseg = min(min(a.minseg, b.minseg), a.minsuff + b.minpref);
    res.maxpref = max(a.maxpref, a.sum + b.maxpref);
    res.maxsuff = max(b.maxsuff, b.sum + a.maxsuff);
    res.maxseg = max(max(a.maxseg, b.maxseg), a.maxsuff + b.maxpref);
    return res;
}

node make_node(int val) {
    node res;
    res.sum = val;
    res.minpref = res.minsuff = res.minseg = val;
    res.maxpref = res.maxsuff = res.maxseg = val;
    return res;
}

int N, M, atrractive[MAX], pos, val, cursum, curmin;
node tree[4 * MAX];

void build(int arr[], int v, int tl, int tr) {
    if (tl == tr) {
        tree[v] = make_node(arr[tl]);
    } else {
        int tm = (tl + tr) >> 1;
        build(arr, v << 1, tl, tm);
        build(arr, (v << 1) + 1, tm + 1, tr);
        tree[v] = combine(tree[v << 1], tree[(v << 1) + 1]);
    }
}

void update(int v, int tl, int tr, int pos, int val) {
    if (tl == tr) {
        tree[v] = make_node(val);
    } else {
        int tm = (tl + tr) >> 1;
        if (pos <= tm) update(v << 1, tl, tm, pos, val);
        else update((v << 1) + 1, tm + 1, tr, pos, val);
        tree[v] = combine(tree[v << 1], tree[(v << 1) + 1]);
    }
}

int main() {
    // freopen("in.txt", "r", stdin);
    scanf("%d", &N);
    for (int i = 1; i <= N; ++i) scanf("%d", &atrractive[i]);
    build(atrractive, 1, 1, N);
    scanf("%d", &M);
    while (M-- > 0) {
        scanf("%d%d", &pos, &val);
        update(1, 1, N, pos, val);
        if (tree[1].maxseg == tree[1].sum && tree[1].sum > 0)
            printf("%d\n", tree[1].sum - tree[1].minseg);
        else
            printf("%d\n", max(tree[1].maxseg, tree[1].sum - tree[1].minseg));
    }

    return 0;
}