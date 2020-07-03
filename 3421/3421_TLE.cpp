#include <cstdio>
#include <utility>
#include <vector>

using namespace std;

const int MAX = (1 << 20) + 1;

int n, maxn, k;
pair<int, long long> dp[MAX];
int lp[MAX + 1];
vector<int> primes;

int main() {
    freopen("in.txt", "r", stdin);
    for (int i = 2; i < MAX; ++i) {
        if (lp[i] == 0) {
            lp[i] = i;
            primes.push_back(i);
        }
        for (int j = 0; j < (int)primes.size() && primes[j] <= lp[i] && i * primes[j] < MAX; ++j) 
            lp[i * primes[j]] = primes[j];
    }
    dp[1] = make_pair(1, 1LL);
    dp[2] = make_pair(2, 1LL);
    maxn = 2;
    while (scanf("%d", &n) != EOF) {
        if (n > maxn) {
            for (int i = maxn + 1; i <= n; ++i) {
                if(lp[i] == 1){
                    dp[i] = make_pair(2, 1);
                    continue;
                }
                dp[i] = make_pair(0, 0);
                for (int j = 0; j < primes.size() && primes[j] <= i; ++j) {
                    if (i % primes[j] == 0) {
                        k = i / primes[j];
                        if (dp[k].first + 1 == dp[i].first)
                            dp[i].second += dp[k].second;
                        else if (dp[k].first + 1 > dp[i].first) {
                            dp[i] = dp[k];
                            ++dp[i].first;
                        }
                    }
                }
            }
            maxn = n;
        }
        printf("%d %lld\n", dp[n].first - 1, dp[n].second);
    }

    return 0;
}