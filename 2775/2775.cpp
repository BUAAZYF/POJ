#include <cstdio>

using namespace std;

const int MAX = 105;
const int MOD = 9901;

int n, combine[MAX][MAX];
struct node {
    int val, left, right, size;
} tree[MAX];

void calcombine() {
    for (int i = 0; i < MAX; ++i) combine[i][0] = 1;
    for (int i = 1; i < MAX; ++i)
        for (int j = 1; j <= i; ++j) combine[i][j] = (combine[i - 1][j] + combine[i - 1][j - 1]) % MOD;
}

void buildtree() {
    int par, cur;
    for (int i = 1; i < n; ++i) {
        cur = 0;
        while (cur != -1) {
            par = cur;
            if (tree[i].val <= tree[cur].val) cur = tree[cur].left;
            else cur = tree[cur].right;
        }
        if (tree[i].val <= tree[par].val) tree[par].left = i;
        else tree[par].right = i;
    }
}

int calsize(int node) {
    if (node == -1) return 0;
    tree[node].size += calsize(tree[node].left) + calsize(tree[node].right);
    return tree[node].size;
}

int calcnt(int node) {
    if (node == -1) return 1;
    return (calcnt(tree[node].left) * calcnt(tree[node].right) % MOD) * combine[tree[node].size - 1][tree[tree[node].left].size] % MOD;
}

int main() {
    calcombine();
    while (scanf("%d", &n) != EOF && n) {
        for (int i = 0; i < n; ++i) {
            scanf("%d", &tree[i].val);
            tree[i].left = tree[i].right = -1;
            tree[i].size = 1;
        }
        buildtree();
        calsize(0);
        printf("%d\n", calcnt(0));
    }

    return 0;
}