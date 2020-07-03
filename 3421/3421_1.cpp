#include <algorithm>
#include <cstdio>
#include <cstring>
#include <set>
#include <utility>
#include <vector>

using namespace std;

const int MAX = (1 << 20) + 5;

int n;
pair<char, int> dp[MAX];
int lp[MAX + 1];
vector<int> primes;

void precomputeprime() {
    memset(lp, 0, sizeof(int) * MAX);
    lp[1] = 1;
    for (int i = 2; i <= MAX; ++i) {
        if (lp[i] == 0) {
            lp[i] = i;
            primes.push_back(i);
        }
        for (int j = 0; j < primes.size() && primes[j] <= lp[i] && i * primes[j] <= MAX; ++j)
            lp[i * primes[j]] = primes[j];
    }
}

void findfactors(int n, set<int>& factors) {
    if (n == 1) return;
    for (int i = 0; i < primes.size() && primes[i] <= n; ++i) {
        if (n % primes[i] == 0) {
            factors.insert(primes[i]);
            while (n % primes[i] == 0) n /= primes[i];
        }
    }
}

void calchain(int n) {
    if (dp[n].first > 0) return;
    if (lp[n] == n) {
        dp[n] = make_pair(2, 1);
        return;
    }
    set<int> factors;
    findfactors(n, factors);
    dp[n] = make_pair(0, 0);
    for (set<int>::iterator j = factors.begin(); j != factors.end(); ++j) {
        int k = n / *j;
        calchain(k);
        if (dp[k].first + 1 == dp[n].first)
            dp[n].second += dp[k].second;
        else if (dp[k].first + 1 > dp[n].first) {
            dp[n] = dp[k];
            ++dp[n].first;
        }
    }
}

int main() {
    // freopen("in.txt", "r", stdin);
    precomputeprime();
    dp[1] = make_pair(1, 1);
    dp[2] = make_pair(2, 1);
    while (scanf("%d", &n) != EOF) {
        calchain(n);
        printf("%d %d\n", dp[n].first - 1, dp[n].second);
    }

    return 0;
}