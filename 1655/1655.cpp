#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

const int MAX = 20005;

inline int max(int a, int b) {
    return a >= b ? a : b;
}

struct node {
    vector<int> neibors;
    vector<int> neibors_size;
} graph[MAX];

int t, n, x, y, ans, ans_idx;
bool visited[MAX];

int dfs(int x) {
    int sum = 1;
    visited[x] = true;
    for (int i = 0; i < graph[x].neibors.size(); ++i) {
        if (visited[graph[x].neibors[i]]) continue;
        if (graph[x].neibors_size[i] == 0) graph[x].neibors_size[i] = dfs(graph[x].neibors[i]);
        sum += graph[x].neibors_size[i];
    }
    return sum;
}

void calbalance(int x) {
    memset(visited, false, MAX * sizeof(bool));
    visited[x] = true; 
    int neibor_max = 0;
    for (int i = 0; i < graph[x].neibors.size(); ++i) {
        graph[x].neibors_size[i] = dfs(graph[x].neibors[i]);
        if(graph[x].neibors_size[i] >= ans) return;
        neibor_max = max(neibor_max, graph[x].neibors_size[i]);
    }
    if (neibor_max > 0) {
        ans = neibor_max;
        ans_idx = x;
    }
}

int main() {
    // freopen("in.txt", "r", stdin);
    scanf("%d", &t);
    while (t-- > 0) {
        scanf("%d", &n);
        for (int i = 1; i <= n; ++i) {
            graph[i].neibors.clear();
            graph[i].neibors_size.clear();
        }
        for (int i = 0; i < n - 1; ++i) {
            scanf("%d%d", &x, &y);
            graph[x].neibors.push_back(y);
            graph[x].neibors_size.push_back(0);
            graph[y].neibors.push_back(x);
            graph[y].neibors_size.push_back(0);
        }
        ans = MAX;
        ans_idx = n + 1;
        for (int i = 1; i <= n; ++i) calbalance(i);
        printf("%d %d\n", ans_idx, ans);
    }

    return 0;
}