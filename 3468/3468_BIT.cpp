#include <cstdio>
#include <cstring>

using namespace std;

typedef long long ll;

const int MAX = 100005;

ll N, Q, x, B1[MAX], B2[MAX], l, r;
char op;

void add(ll* b, ll idx, ll x) {
    while (idx <= N) {
        b[idx] += x;
        idx += idx & -idx;
    }
}

void range_add(ll l, ll r, ll x) {
    add(B1, l, x);
    add(B1, r + 1, -x);
    add(B2, l, x * (l - 1));
    add(B2, r + 1, -x * r);
}

ll sum(ll* b, ll idx) {
    ll total = 0;
    while (idx > 0) {
        total += b[idx];
        idx -= idx & -idx;
    }
    return total;
}

ll prefix_sum(ll idx) {
    return sum(B1, idx) * idx - sum(B2, idx);
}

ll range_sum(ll l, ll r) {
    return prefix_sum(r) - prefix_sum(l - 1);
}

int main() {
    scanf("%lld%lld", &N, &Q);
    memset(B1, 0, sizeof(B1));
    memset(B2, 0, sizeof(B2));
    for (ll i = 1; i <= N; ++i) {
        scanf("%lld", &x);
        range_add(i, i, x);
    }
    getchar();
    for (ll i = 0; i < Q; ++i) {
        scanf("%c%lld%lld", &op, &l, &r);
        if (op == 'Q')
            printf("%lld\n", range_sum(l, r));
        else {
            scanf("%lld", &x);
            range_add(l, r, x);
        }
        getchar();
    }

    return 0;
}
