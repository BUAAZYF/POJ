#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <string>

using namespace std;

const int MAXV = 35;

double inline max(double a, double b) { return a >= b ? a : b; }

int t, n, m;
double rate, graph[MAXV][MAXV];
string curr1, curr2;
map<string, int> currencies;

int main() {
    t = 0;
    while (scanf("%d", &n) != EOF && n) {
        ++t;
        memset(graph, 0, sizeof(graph));
        currencies.clear();
        for (int i = 0; i < n; ++i) {
            cin >> curr1;
            currencies[curr1] = i;
            graph[i][i] = 1;
        }
        scanf("%d", &m);
        while (m--) {
            cin >> curr1 >> rate >> curr2;
            graph[currencies[curr1]][currencies[curr2]] = rate;
        }
        for (int k = 0; k < n; ++k)
            for (int i = 0; i < n; ++i)
                for (int j = 0; j < n; ++j) graph[i][j] = max(graph[i][j], graph[i][k] * graph[k][j]);
        bool arbitrage = false;
        for (int i = 0; i < n; ++i)
            if (graph[i][i] > 1) {
                arbitrage = true;
                break;
            }
        printf("Case %d: %s\n", t, arbitrage ? "Yes" : "No");
    }

    return 0;
}