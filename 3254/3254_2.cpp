#include <algorithm>
#include <cstdio>
#include <vector>

using namespace std;

const int MAX = 13;
const int MOD = 100000000;

int N, M, x, dp[MAX][1 << MAX], infertile[MAX];
vector<int> valid;

int main() {
    while (scanf("%d%d", &M, &N) != EOF) {
        fill(infertile, infertile + MAX, 0);
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                scanf("%d", &x);
                if (!x) infertile[i + 1] |= 1 << j;
            }
        }
        valid.clear();
        for (int i = 0; i < 1 << N; ++i)
            if (!(i & (i << 1))) valid.push_back(i);
        fill(dp[0], dp[0] + (1 << N), 1);
        for (int i = 1; i <= M; ++i) {
            fill(dp[i], dp[i] + (1 << N), 0);
            for (int j = 0; j < (1 << N); ++j) {
                if (~j & infertile[i]) continue;
                for (int k = 0; k < valid.size(); ++k) {
                    int u = valid[k];
                    if (u & j) continue;
                    dp[i][j] += dp[i - 1][u | infertile[i - 1]];
                    dp[i][j] %= MOD;
                }
            }
        }
        printf("%d\n", dp[M][infertile[M]]);
    }

    return 0;
}