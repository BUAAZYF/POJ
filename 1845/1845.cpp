#include <cstdio>
#include <vector>

using namespace std;

typedef long long ll;

const int MAX = 10050;
const ll MOD = 9901;

int a, b, p;
ll ans;
bool notprime[MAX];
vector<int> primes;

ll mul(ll a, ll p, ll M) {
    ll res = 0;
    for (; p; p >>= 1, a = (a + a) % M)
        if (p & 1) res = (res + a) % M;
    return res;
}

ll modpow(ll a, ll p, ll M) {
    ll res = 1;
    for (; p; p >>= 1, a = mul(a, a, M))
        if (p & 1) res = mul(res, a, M);
    return res;
}

void init_primes() {
    primes.clear();
    for (int i = 2; i < MAX; ++i) {
        if (notprime[i]) continue;
        primes.push_back(i);
        for (int j = i * 2; j < MAX; j += i) notprime[j] = true;
    }
}

int main() {
    init_primes();
    while (scanf("%d%d", &a, &b) != EOF) {
        ans = 1;
        for (int i = 0; primes[i] * primes[i] <= a; ++i) {
            p = 0;
            while (a % primes[i] == 0) {
                ++p;
                a /= primes[i];
            }
            if (p != 0) {
                ll m = MOD * (primes[i] - 1);
                ans *= (modpow(primes[i], (ll)p * (ll)b + 1, m) + m - 1) / (primes[i] - 1);
                ans %= MOD;
            }
        }
        if (a > 1) {
            ll m = MOD * (a - 1);
            ans *= (modpow(a, b + 1, m) + m - 1) / (a - 1);
            ans %= MOD;
        }
        printf("%d\n", (int)ans);
    }

    return 0;
}