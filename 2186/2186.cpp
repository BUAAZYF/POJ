#include <algorithm>
#include <cstdio>
#include <vector>
#include <stack>

using namespace std;

const int MAX = 10005;

int inline min(int a, int b) {
    return a <= b ? a : b;
}

int N, M, A, B, id, ans;
vector<int> edges[MAX];
int ids[MAX], low[MAX];
bool onstk[MAX];
stack<int> stk;
vector<vector<int> > scc;
vector<int> scc_outdegree;

void init() {
    id = 0;
    fill(ids, ids + N + 1, -1);
    fill(low, low + N + 1, 0);
    fill(onstk, onstk + N + 1, false);
    for (int i = 1; i <= N; ++i)
        edges[i].clear();
    while (!stk.empty()) stk.pop();
    scc.clear();
    scc_outdegree.clear();
}

void dfs(int node) {
    stk.push(node);
    onstk[node] = true;
    ids[node] = low[node] = id++;
    for (int i = 0; i < edges[node].size(); ++i) {
        int nxt = edges[node][i];
        if (ids[nxt] == -1) dfs(nxt);
        if (onstk[nxt]) low[node] = min(low[node], low[nxt]);
    }
    if (ids[node] == low[node]) {
        scc.push_back(vector<int>());
        while (stk.top() != node) {
            onstk[stk.top()] = false;
            low[stk.top()] = low[node];
            scc[scc.size() - 1].push_back(stk.top());
            stk.pop();
        }
        onstk[stk.top()] = false;
        low[stk.top()] = low[node];
        scc[scc.size() - 1].push_back(stk.top());
        stk.pop();
    }
}  

int main() {
    while (scanf("%d%d", &N, &M) != EOF) {
    init();
    while (M--) {
        scanf("%d%d", &A, &B);
        edges[A].push_back(B);
    }
    for(int i = 1; i <= N; ++i) 
        if (ids[i] == -1) dfs(i);
    scc_outdegree = vector<int>(scc.size(), 0);
    for (int i = 0; i < scc.size(); ++i) {
        for (int j = 0; j < scc[i].size(); ++j) {
            vector<int>& neibors = edges[scc[i][j]];
            for (int k = 0; k < neibors.size(); ++k) {
                if (low[scc[i][j]] != low[neibors[k]]) ++scc_outdegree[i];
            }
        }
    }
    int zero_cnt = 0, zero_idx;
    for (int i = 0; i < scc_outdegree.size(); ++i) {
        if (scc_outdegree[i] == 0) {
            ++zero_cnt;
            zero_idx = i;
        }
    }
    if (zero_cnt == 1) ans = scc[zero_idx].size();
    else if (zero_cnt == 0) ans = N;
    else ans = 0;
    printf("%d\n", ans);
    }

    return 0;
}