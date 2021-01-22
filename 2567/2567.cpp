#include <cstdio>
#include <set>

using namespace std;

const int MAX = 55;

int inline max(int a, int b) {
    return a >= b ? a : b;
}

int n, prufer[MAX], cnt[MAX];
set<int> graph[MAX];

void dfs(int parent) {
    char c;
    int node;
    while ((c = getchar()) != EOF && c != '(')
        ;
    if (scanf("%d", &node) == EOF) return;
    n = max(n, node);
    if (parent != 0) {
        graph[parent].insert(node);
        graph[node].insert(parent);
    }
    while (true) {
        while ((c = getchar()) != EOF && c != '(' && c != ')')
            ;
        if (c == ')') return;
        ungetc(c, stdin);
        dfs(node);
    }
}

int main() {
    while (true) {
        n = 0;
        dfs(0);
        getchar();
        if (n == 0) break;
        if (n == 1) {
            putchar('\n');
            continue;
        }
        for (int step = 1; step < n; ++step) {
            for (int i = 1; i <= n; ++i) {
                if (graph[i].size() == 1) {
                    printf("%d%c", *graph[i].begin(), step == n - 1 ? '\n' : ' ');
                    graph[*graph[i].begin()].erase(i);
                    graph[i].clear();
                    break;
                }
            }
        }
    }
    return 0;
}