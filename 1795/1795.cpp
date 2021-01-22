#include <algorithm>
#include <cstdio>
#include <iostream>
#include <string>

using namespace std;

const int MAX = 15;

int inline max(int a, int b) {
    return a >= b ? a : b;
}

int inline min(int a, int b) {
    return a <= b ? a : b;
}

int T, n, x, graph[MAX][MAX], dp[1 << MAX][MAX], maxlen;
string ans, words[MAX];

void calgraph() {
    fill(&graph[0][0], &graph[0][0] + sizeof(graph) / sizeof(graph[0][0]), 0);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == j) continue;
            for (int len = min(words[i].size(), words[j].size()); len > 0; --len) {
                if (words[i].substr(words[i].size() - len) == words[j].substr(0, len)) {
                    graph[i][j] = len;
                    break;
                }
            }
        }
    }
}

string formstr(int first, int len) {
    string res = words[first], tail;
    int cur, s = ((1 << n) - 1) & ~(1 << first);
    for (int _ = 0; _ < n - 1; ++_) {
        cur = -1;
        tail = string(1, 'Z' + 1);
        for (int i = 0; i < n; ++i) {
            if (((s >> i) & 1) && dp[s][i] + graph[first][i] == len && tail > words[i].substr(graph[first][i])) {
                tail = words[i].substr(graph[first][i]);
                cur = i;
            }
        }
        len -= graph[first][cur];
        first = cur;
        res += tail;
        s &= ~(1 << first);
    }
    return res;
}

int main() {
    scanf("%d", &T);
    for (int t = 1; t <= T; ++t) {
        scanf("%d", &n);
        for (int i = 0; i < n; ++i) cin >> words[i];
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                if (i != j && words[j].find(words[i]) != string::npos) words[i] = words[j];
        sort(words, words + n);
        n = unique(words, words + n) - words;
        fill(&dp[0][0], &dp[0][0] + sizeof(dp) / sizeof(dp[0][0]), 0);
        calgraph();
        for (int k = 2; k <= n; ++k) {
            int s = (1 << k) - 1;
            while (s < 1 << n) {
                for (int i = 0; i < n; ++i) {
                    if ((s >> i) & 1) {
                        for (int j = 0; j < n; ++j) {
                            if (i == j || !((s >> j) & 1)) continue;
                            dp[s][i] = max(dp[s][i], graph[i][j] + dp[s & ~(1 << i)][j]);
                        }
                    }
                }
                int x = s & -s, y = s + x;
                s = ((s & ~y) / x >> 1) | y;
            }
        }
        maxlen = 0;
        for (int i = 0; i < n; ++i) maxlen = max(maxlen, dp[(1 << n) - 1][i]);
        ans = "";
        for (int i = 0; i < n; ++i) {
            if (dp[(1 << n) - 1][i] == maxlen) {
                ans = formstr(i, maxlen);
                break;
            }
        }
        printf("Scenario #%d:\n%s\n\n", t, ans.c_str());
    }

    return 0;
}