// This code actually works for every numbers, but RE in POJ.

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <set>
#include <utility>
#include <vector>

using namespace std;

const int MAX = (1 << 20) + 5;

int n;
pair<short, int> dp[MAX];
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
        for (int j = 0; j < (int)primes.size() && primes[j] <= lp[i] && i * primes[j] <= MAX; ++j)
            lp[i * primes[j]] = primes[j];
    }
}

inline int int_abs(int a) {
    return a >= 0 ? a : -a;
}

int gcd(int x, int y) {
    if (y == 0) return x;
    return gcd(y, x % y);
}

int mult(int a, int b, int mod) {
    return int(long(a) * b % mod);
}

int f(int x, int c, int mod) {
    return (mult(x, x, mod) + c) % mod;
}

int brent(int n, int c = 120) {
    int g = 1;
    int q = 1;
    int xs, x, y;
    x = rand() % (n - 1) + 1;
    int m = rand() % 128 + 1;
    int l = 1;
    while (g == 1) {
        y = x;
        for (int i = 1; i < l; ++i) x = f(x, c, n);
        int k = 0;
        while (k < l && g == 1) {
            xs = x;
            for (int i = 0; i < m && i < l - k; ++i) {
                x = f(x, c, n);
                q = mult(q, int_abs(y - x), n);
            }
            g = gcd(q, n);
            k += m;
        }
        l *= 2;
    }
    if (g == n) {
        do {
            xs = f(xs, c, n);
            g = gcd(int_abs(xs - y), n);
        } while (g == 1);
    }
    return g;
}

void findfactors(int n, set<int>& factors) {
    if (n == 1) return;
    while (lp[n] != n) {
        int p = brent(n);
        if (lp[p] == p) factors.insert(p);
        else findfactors(p, factors);
        while (n % p == 0) n /= p;
    }
    if (n > 1) factors.insert(n);
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