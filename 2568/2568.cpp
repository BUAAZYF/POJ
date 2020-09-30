#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

const int MAX = 55;

int n, prufer[MAX], cnt[MAX];
vector<int> graph[MAX];

void dfs(int node) {
    putchar('(');
    printf("%d", node);
    if (!graph[node].empty()) {
        putchar(' ');
        for (int i = 0; i < graph[node].size() - 1; ++i) {
            dfs(graph[node][i]);
            putchar(' ');
        }
        dfs(graph[node][graph[node].size() - 1]);
    }
    putchar(')');
}

int main() {
    char c;
    while ((c = getchar()) != EOF) {
        if (c == '\n') {
            printf("(1)\n");
            continue;
        }
        ungetc(c, stdin);
        n = 0;
        while (scanf("%d", &prufer[n++]) != EOF && getchar() != '\n') ;
        memset(cnt, 0, sizeof(cnt));
        for (int i = 0; i < n; ++i) {
            ++cnt[prufer[i]];
            graph[i].clear();
        }
        graph[n].clear();
        graph[n + 1].clear();
        for (int i = 0; i < n; ++i) {
            int idx = 0;
            for (int j = 1; j <= n + 1; ++j) {
                if (cnt[j] == 0) {
                    idx = j;
                    break;
                }
            }
            --cnt[idx];
            --cnt[prufer[i]];
            graph[prufer[i]].push_back(idx);
        }
        dfs(n + 1);
        putchar('\n');
    }

    return 0;
}