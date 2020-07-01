#include <cstdio>

using namespace std;

typedef long long ll;

ll p, a;

bool isprime(ll a) {
    for (ll i = 2; i * i <= a; ++i) 
        if (a % i == 0) return false;
    return true;
}

ll mod_pow(ll a, ll p, ll mod) {
    if (p == 0) return 1;
    ll res = mod_pow(a * a % mod, p / 2, mod);
    if (p & 1) res = res * a % mod;
    return res;
}

int main() {
    // freopen("in.txt", "r", stdin);
    while (scanf("%lld%lld", &p, &a) != EOF && p) {
        if (isprime(p)) {
            printf("no\n");
            continue;
        }
        if (mod_pow(a, p, p) == a % p) printf("yes\n");
        else printf("no\n");
    }

    return 0;
}