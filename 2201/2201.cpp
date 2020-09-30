#include <algorithm>
#include <cstdio>

using namespace std;

const int MAX = 50005;
const int INF = 0x3f3f3f3f;

int n, k, a;
struct node {
    int k, a, id;
    int par, left, right;
    node(int _k, int _a, int _id) : k(_k), a(_a), id(_id), par(0), left(0), right(0) {}
} * tree[MAX], *order[MAX];
int rmq[MAX * 4];

bool cmp(const node* a, const node* b) {
    return a->k < b->k;
}

void buildsegmenttree(int v, int tl, int tr) {
    if (tl == tr) {
        rmq[v] = tl;
    } else {
        int tm = (tl + tr) / 2;
        buildsegmenttree(v * 2, tl, tm);
        buildsegmenttree(v * 2 + 1, tm + 1, tr);
        if (tree[rmq[v * 2]]->a <= tree[rmq[v * 2 + 1]]->a)
            rmq[v] = rmq[v * 2];
        else
            rmq[v] = rmq[v * 2 + 1];
    }
}

int queryrmq(int v, int tl, int tr, int l, int r) {
    if (l > r) return INF;
    if (l == tl && r == tr) return rmq[v];
    int tm = (tl + tr) / 2;
    int t1 = queryrmq(v * 2, tl, tm, l, min(r, tm));
    int t2 = queryrmq(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r);
    if (t1 == INF) return t2;
    if (t2 == INF) return t1;
    if (tree[t1]->a <= tree[t2]->a) return t1;
    else return t2;
}

int buildtree(int low, int high, int par) {
    int root = queryrmq(1, 1, n, low, high);
    tree[root]->par = par;
    if (root - 1 >= low) tree[root]->left = buildtree(low, root - 1, tree[root]->id);
    if (root + 1 <= high) tree[root]->right = buildtree(root + 1, high, tree[root]->id);
    return tree[root]->id;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d%d", &k, &a);
        tree[i] = new node(k, a, i);
        order[i] = tree[i];
    }
    sort(tree + 1, tree + n + 1, cmp);
    buildsegmenttree(1, 1, n);
    buildtree(1, n, 0);
    printf("YES\n");
    for (int i = 1; i <= n; ++i)
        printf("%d %d %d\n", order[i]->par, order[i]->left, order[i]->right);

    return 0;
}