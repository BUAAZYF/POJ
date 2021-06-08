#include <algorithm>
#include <cstdio>
#include <queue>
#include <vector>

using namespace std;

const int MAX = 1005;

int min(int a, int b) {
    return a <= b ? a : b;
}

int max(int a, int b) {
    return a >= b ? a : b;
}

int N, M, x, y;
char op;
bool visited[MAX];
vector<int> graph[MAX];

bool canreach(int s, int t) {
    if (s == t) return true;
    fill(visited, visited + MAX, false);
    visited[s] = true;
    queue<int> q;
    q.push(s);
    while (!q.empty()) {
        int c = q.front();
        q.pop();
        for (int i = 0; i < graph[c].size(); ++i) {
            int& node = graph[c][i];
            if (node == t) return true;
            if (visited[node]) continue;
            visited[node] = true;
            q.push(node);
        }
    }
    return false;
}

int main() {
    scanf("%d%d\n", &N, &M);
    while (M--) {
        scanf("%c %d %d\n", &op, &x, &y);
        if (op == 'I') {
            graph[x].push_back(y);
            graph[y].push_back(x);
        } else if (op == 'D') {
            graph[x].erase(find(graph[x].begin(), graph[x].end(), y));
            graph[y].erase(find(graph[y].begin(), graph[y].end(), x));
        } else
            printf("%c\n", canreach(x, y) ? 'Y' : 'N');
    }
    return 0;
}