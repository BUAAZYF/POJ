#include <cstdio>
#include <cstring>
#include <set>

using namespace std;

int main() {
    int T, N, parent, child, query_x, query_y;
    int ancestors[10001];
    scanf("%d", &T);
    while (T-- > 0) {
        memset(ancestors, 0, 10001 * sizeof(int));
        scanf("%d", &N);
        for (int i = 0; i < N - 1; ++i) {
            scanf("%d%d", &parent, &child);
            ancestors[child] = parent;
        }
        scanf("%d%d", &query_x, &query_y);
        set<int> ancs;
        while (query_x != 0) {
            ancs.insert(query_x);
            query_x = ancestors[query_x];
        }
        while (query_y != 0) {
            if (ancs.find(query_y) != ancs.end()) break;
            query_y = ancestors[query_y];
        }
        printf("%d\n", query_y);
    }

    return 0;
}