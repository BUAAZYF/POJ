#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

const int MAX = 100001;

struct Node {
    int parnode;
    vector<int> subnodes;
    int val;
    bool state;
};

Node tree[MAX];
int n, m, u, v, x;
char op;

int initialtree(int node) {
    int val = 1;
    for (int i = 0; i < tree[node].subnodes.size(); ++i) {
        val += initialtree(tree[node].subnodes[i]);
    }
    tree[node].state = true;
    tree[node].val = val;
    return val;
}

void updatenode(int node) {
    int modify = (tree[node].state ? -1 : 1);
    tree[node].state = !tree[node].state;
    while (node != 0) {
        tree[node].val += modify;
        node = tree[node].parnode;
    }
}

int main() {
    //freopen("in.txt", "r", stdin);
    scanf("%d", &n);
    if(n == 0) return 0;
    for (int i = 0; i < n - 1; ++i) {
        scanf("%d%d", &u, &v);
        tree[u].subnodes.push_back(v);
        tree[v].parnode = u;
    }
    initialtree(1);

    scanf("%d\n", &m);
    for (int i = 0; i < m; ++i) {
        scanf("%c %d\n", &op, &x);
        if (op == 'C')
            updatenode(x);
        else
            printf("%d\n", tree[x].val);
    }

    return 0;
}