#include <cstdio>

using namespace std;

typedef long long ll;

ll gcd(ll x, ll y) {
    if (y == 0) return x;
    return gcd(y, x % y);
}

ll g, l, tmp, a, b;

int main() {
    // freopen("in.txt", "r", stdin);
    while (scanf("%lld%lld", &g, &l) != EOF) {
        if(g == l){
            printf("%d %lld\n", 1, g);
            continue;
        }
        
        for (ll i = 2, upper = l / g; i * i <= upper; ++i) {
            if (upper % i == 0 && gcd(i, upper / i) == 1) {
                a = i;
                b = upper / i;
                break;
            }
        }
        a *= g;
        b *= g;
        printf("%lld %lld\n", a, b);
    }

    return 0;
}