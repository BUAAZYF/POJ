#include <cstdio>
#include <cstring>

using namespace std;

const int MAX = 30;
const int INF = 0x3f3f3f3f;

double inline max(int a, int b) {
    return a >= b ? a : b;
}

double inline min(int a, int b) {
    return a <= b ? a : b;
}

int t, n;
int dp[MAX][MAX][MAX];
char c;
char ans[MAX];
int cnt[MAX];

void initdp() {
    for (int i = 0; i < MAX; ++i)
        for (int j = 0; j < MAX; ++j)
            for (int k = 0; k < MAX; ++k)
                dp[i][j][k] = INF;
}

int idxchar(char c){
    if (c >= 'a' && c <= 'z') return c - 'a';
    switch (c) {
        case '+': return 26; break;
        case '*': return 27; break;
        case '/': return 28; break;
        case '?': return 29; break;
        default: break;
    }
    return -1;
}

char idx2char(int idx){
    if (idx >= 0 && idx <= 25) return char(idx + 'a');
    switch(idx){
        case 26: return '+'; break;
        case 27: return '*'; break;
        case 28: return '/'; break;
        case 29: return '?'; break;
        default: break;
    }
    return ' ';
}

int main() {
    // freopen("in.txt", "r", stdin);
    scanf("%d", &t);
    while (t-- > 0) {
        scanf("%d\n", &n);
        initdp();
        memset(cnt, 0, sizeof(cnt));
        for (int i = 0; i < n; ++i)
            while ((c = getchar()) != EOF && c != '\n') ++cnt[idxchar(c)];
        dp[0][0][11] = cnt[0];
        for (int i = 1; i < MAX; ++i) {
            for (int j = 0; j < i; ++j) {
                for (int k = 0; k < 12; ++k) {
                    dp[i][j][k] = min(dp[i][j][k], dp[i - 1][j][k] + cnt[i] * (i - j + 1));
                    if (k > 0) dp[i][i][k - 1] = min(dp[i][i][k - 1], dp[i - 1][j][k] + cnt[i]);
                }
            }
        }
        int lasti = MAX - 1;
        for (int k = 0; k < 12; ++k) {
            int nexti = -1, mincost = INF;
            for (int j = 0; j < MAX; ++j) {
                if (dp[lasti][j][k] < mincost) {
                    mincost = dp[lasti][j][k];
                    nexti = j;
                }
            }
            lasti = nexti - 1;
            ans[k] = idx2char(nexti);
        }
        for(int k = 10; k >= 0; --k) putchar(ans[k]);
        putchar('\n');
    }

    return 0;
}