#include <algorithm>
#include <cstdio>
#include <map>
#include <vector>
#include <cmath>

using namespace std;

typedef long long ll;

inline ll ll_abs(ll a) {
    return a >= 0 ? a : -a;
}

inline ll min(ll a, ll b) {
    return a <= b ? a : b;
}

ll gcd(ll x, ll y) {
    if (y == 0) return x;
    return gcd(y, x % y);
}

ll mult(ll a, ll b, ll mod) {
    ll result = 0;
    while (b) {
        if (b & 1) result = (result + a) % mod;
        a = (a + a) % mod;
        b >>= 1;
    }
    return result;
}

ll binpower(ll base, ll e, ll mod) {
    ll result = 1;
    base %= mod;
    while (e) {
        if (e & 1) result = mult(result, base, mod);
        base = mult(base, base, mod);
        e >>= 1;
    }
    return result;
}

bool check_composite(ll n, ll a, ll d, int s) {
    ll x = binpower(a, d, n);
    if (x == 1 || x == n - 1)
        return false;
    for (int r = 1; r < s; ++r) {
        x = mult(x, x, n);
        if (x == n - 1) return false;
    }
    return true;
}

const int primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
bool millerRabin(ll n) {
    if (n < 2 || n > 2 && n % 2 == 0) return false;
    int r = 0;
    ll d = n - 1;
    while ((d & 1) == 0) {
        d >>= 1;
        ++r;
    }

    for (int i = 0, sz = sizeof(primes) / sizeof(int); i < sz; ++i) {
        if (n == primes[i]) return true;
        if (check_composite(n, primes[i], d, r)) return false;
    }
    return true;
}

ll f(ll x, ll c, ll mod) {
    return (mult(x, x, mod) + c) % mod;
}

ll brent(ll n, ll c = 120) {
    ll g = 1;
    ll q = 1;
    ll xs, x, y;
    x = rand() % (n - 1) + 1;
    int m = 128;
    ll l = 1;
    while (g == 1) {
        y = x;
        for (int i = 1; i < l; ++i) x = f(x, c, n);
        int k = 0;
        while (k < l && g == 1) {
            xs = x;
            for (int i = 0; i < m && i < l - k; ++i) {
                x = f(x, c, n);
                q = mult(q, ll_abs(y - x), n);
            }
            g = gcd(q, n);
            k += m;
        }
        l *= 2;
    }
    if (g == n) {
        do {
            xs = f(xs, c, n);
            g = gcd(ll_abs(xs - y), n);
        } while (g == 1);
    }
    return g;
}

map<ll, int> factors;
vector<ll> part;
void findfactors(ll n) {
    if (n == 1) return;
    while (n != 1 && !millerRabin(n)) {
        ll p = brent(n);
        n /= p;
        if (millerRabin(p)) ++factors[p];
        else findfactors(p);
    }
    if (n > 1) ++factors[n];
}

ll g, l, ra, rb, minsum;

void dfs(int idx, ll a, ll b) {
    if (idx == part.size()) {
        if (a != 1 &&  b != 1 && a + b < minsum) {
            minsum = a + b;
            ra = a, rb = b;
        }
        return;
    }
    dfs(idx + 1, a, b * part[idx]);
    dfs(idx + 1, a * part[idx], b);
}

int main() {
    freopen("in.txt", "r", stdin);
    while (scanf("%lld%lld", &g, &l) != EOF) {
        if (g == l) {
            printf("%lld %lld\n", l, l);
            continue;
        }
        l /= g;
        minsum = l + 1;
        ra = 1, rb = l;
        if (millerRabin(l)) {
            printf("%lld %lld\n", g, l * g);
            continue;
        }
        factors.clear();
        part.clear();
        findfactors(l);
        for (map<ll, int>::iterator it = factors.begin(); it != factors.end(); ++it)
            part.push_back((ll)pow(it->first, it->second));
        dfs(0, 1, 1);
        if(ra > rb){
            ll tmp = ra;
            ra = rb;
            rb = tmp;
        }
        printf("%lld %lld\n", ra * g, rb * g);
    }

    return 0;
}