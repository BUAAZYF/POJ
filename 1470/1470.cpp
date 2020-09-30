#include <cstdio>
#include <cstring>

using namespace std;

const int MAX = 905;

int n, m, p, s, u, v;
int par[MAX], cnt[MAX];
bool isanc[MAX];

int main() {
    while (scanf("%d", &n) != EOF) {
        memset(par, 0, sizeof(par));
        memset(cnt, 0, sizeof(cnt));
        for (int i = 0;i < n; ++i) {
            scanf("%d", &p);
            while (getchar() != '(') ;
            scanf("%d", &m);
            while (getchar() != ')') ;
            for (int j = 0; j < m; ++j) {
                scanf("%d", &s);
                par[s] = p;
            }
        }
        scanf("%d", &m);
        for (int i = 0; i < m; ++i) {
            while (getchar() != '(') ;
            scanf("%d%d", &u, &v);
            while (getchar() != ')') ;
            memset(isanc, false, sizeof(isanc));
            while (u != 0) {
                isanc[u] = true;
                u = par[u];
            }
            while (v != 0) {
                if (isanc[v]) {
                    ++cnt[v];
                    break;
                }
                v = par[v];
            }
        }
        for (int i = 1; i <= n; ++i)
            if (cnt[i] != 0) printf("%d:%d\n", i, cnt[i]);
    }

    return 0;
}