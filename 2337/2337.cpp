#include <algorithm>
#include <cstdio>
#include <string>
#include <iostream>
#include <vector>

using namespace std;

const int MAX = 1005;
const int MAXV = 26;

int t, N, start;
string words[MAX];
vector<int> edges[MAXV];
bool visited[MAX];
int indegree[MAXV], outdegree[MAXV];
vector<int> ans;

void init() {
    fill(indegree, indegree + MAXV, 0);
    fill(outdegree, outdegree + MAXV, 0);
    fill(visited, visited + MAX, false);
    for (int i = 0; i < MAXV; ++i) edges[i].clear();
}

int find_path_start() {
    int start_node = -1, end_node = -1;
    for (int i = 0; i < MAXV; ++i) {
        if (outdegree[i] - indegree[i] > 1 || indegree[i] - outdegree[i] > 1) return -1;
        else if (outdegree[i] - indegree[i] == 1) {
            if (start_node == -1) start_node = i;
            else return -1;
        } else if (indegree[i] - outdegree[i] == 1) {
            if (end_node == -1) end_node = i;
            else  return -1;
        }
    }
    if (start_node == -1 && end_node == -1) {
        for (int i = 0; i < MAXV; ++i)
            if (outdegree[i] > 0) return i;
    }
    if (start_node == -1 || end_node == -1) return -1;
    return start_node;
}

void dfs(int node) {
    for (int i = 0; i < edges[node].size(); ++i) {
        if (visited[edges[node][i]]) continue;
        visited[edges[node][i]] = true;
        string& nxt = words[edges[node][i]];
        dfs(nxt[nxt.size() - 1] - 'a');
        ans.push_back(edges[node][i]);
    }
}

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &N);
        init();
        for (int i = 0; i < N; ++i) cin >> words[i];
        sort(words, words + N);
        for (int i = 0; i < N; ++i) {
            ++outdegree[words[i][0] - 'a'];
            ++indegree[words[i][words[i].size() - 1] - 'a'];
            edges[words[i][0] - 'a'].push_back(i);
        }
        start = find_path_start();
        if (start == -1) {
            printf("***\n");
            continue;
        }
        ans.clear();
        dfs(start);
        if (ans.size() != N) printf("***\n");
        else {
            for (int i = ans.size() - 1; i > 0; --i) printf("%s.", words[ans[i]].c_str());
            printf("%s\n", words[ans[0]].c_str());
        }
    }

    return 0;
}