#include <cstdio>
#include <cstring>

using namespace std;

const int MAX = 1005;

int t, n, df, dg, dh, dmul;
bool f[MAX], g[MAX], h[MAX], mul[2 * MAX];

int main() {
    scanf("%d", &t);
    while (t--) {
        memset(mul, false, sizeof(mul));
        scanf("%d", &df);
        for(int i = 0; i < df; ++i) scanf("%d", &f[i]);
        scanf("%d", &dg);
        for(int i = 0; i < dg; ++i) scanf("%d", &g[i]);
        scanf("%d", &dh);
        for(int i = 0; i < dh; ++i) scanf("%d", &h[i]);
        for(int i = 0; i < df; ++i)
            for (int j = 0; j < dg; ++j) 
                mul[i + j] ^= (f[i] * g[j]);
        dmul = df + dg - 1;
        int idx = 0;
        while (idx < dmul && !mul[idx]) ++idx; 
        while (idx + dh <= dmul) {
            for(int i = 0; i < dh; ++i) mul[idx + i] ^= h[i];
            while (idx < dmul && !mul[idx]) ++idx; 
        }
        if (idx == dmul) printf("1 0\n");
        else {
            printf("%d ", dmul - idx);
            while(idx < dmul - 1) printf("%d ", mul[idx++]);
            printf("%d\n", mul[idx]);
        }
    }
    
    return 0;
}