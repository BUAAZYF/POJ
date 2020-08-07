#include <cstdio>
#include <map>

using namespace std;

int t, a, b, zerod, edge_cnt;
bool istree;
map<int, int> indegree;

int main() {
    t = 1;
    while (scanf("%d%d", &a, &b) && a != -1) {
        edge_cnt = 0;
        indegree.clear();
        if (a) {
            do {
                if (indegree.find(a) == indegree.end()) indegree[a] = 0;
                if (indegree.find(b) == indegree.end()) indegree[b] = 0;
                ++indegree[b];
                ++edge_cnt;
            } while (scanf("%d%d", &a, &b) && a);
            istree = edge_cnt == (int)indegree.size() - 1;
            if (istree) {
                zerod = 0;
                for (map<int, int>::iterator it = indegree.begin(); it != indegree.end(); ++it) {
                    if (it->second > 1) {
                        istree = false;
                        break;
                    }
                    if (it->second == 0) ++zerod;
                }
                if (!(istree && zerod == 1)) istree = false;
            }
        } else
            istree = true;
        if (istree)
            printf("Case %d is a tree.\n", t);
        else
            printf("Case %d is not a tree.\n", t);
        ++t;
    }

    return 0;
}