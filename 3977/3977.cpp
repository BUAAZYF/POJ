#include <algorithm>
#include <cstdio>
#include <utility>

using namespace std;

typedef long long ll;
typedef pair<ll, ll> Pr;

const int SIZE = 36;
const int MAX = 1 << (SIZE / 2);
const ll INF = 35 * 1000000000000000LL;

ll inline llmax(ll a, ll b) {
    return a >= b ? a : b;
}

ll n, m1, m2, cur, cnt, a[SIZE], minval, mincnt;
Pr first[MAX], second[MAX];

void mergesame(Pr arr[MAX], ll &m) {
    sort(arr + 1, arr + m + 1);
    ll i = 2, j = 2;
    while (j <= m) {
        if (arr[j].first != arr[j - 1].first) {
            arr[i] = arr[j];
            ++i;
        }
        ++j;
    }
    m = i - 1;
}

int main() {
    while (scanf("%lld", &n) != EOF && n) {
        for (int i = 1; i <= n; ++i) scanf("%lld", &a[i]);
        if (n == 1) {
            printf("%lld %d\n", llabs(a[1]), 1);
            continue;
        }
        minval = mincnt = INF;
        m1 = (1 << (n / 2)) - 1, m2 = (1 << (n - n / 2)) - 1;
        for (ll i = 1; i <= m1; ++i) {
            cnt = 0, cur = 0;
            for (ll j = 1; j <= n / 2; ++j) {
                if (i & (1 << (j - 1))) {
                    cur += a[j];
                    ++cnt;
                }
            }
            if (llabs(cur) < minval || llabs(cur) == minval && cnt < mincnt) {
                minval = llabs(cur);
                mincnt = cnt;
            }
            first[i].first = cur;
            first[i].second = cnt;
        }
        for (ll i = 1; i <= m2; ++i) {
            cnt = 0, cur = 0;
            for (ll j = n / 2 + 1; j <= n; ++j) {
                if (i & (1 << (j - n / 2 - 1))) {
                    cur += a[j];
                    ++cnt;
                }
            }
            if (llabs(cur) < minval || llabs(cur) == minval && cnt < mincnt) {
                minval = llabs(cur);
                mincnt = cnt;
            }
            second[i].first = cur;
            second[i].second = cnt;
        }
        mergesame(first, m1);
        mergesame(second, m2);
        for (ll i = 1; i <= m1; ++i) {
            ll pos = lower_bound(second + 1, second + m2 + 1, Pr(-first[i].first, 0)) - second;
            if (pos > m2) pos = m2;
            if (pos < 1) pos = 1;
            for (ll j = llmax(1LL, pos - 1); j <= pos; ++j) {
                cur = llabs(first[i].first + second[j].first);
                cnt = first[i].second + second[j].second;
                if (cur < minval || cur == minval && cnt < mincnt) {
                    minval = cur;
                    mincnt = cnt;
                }
            }
        }
        printf("%lld %lld\n", minval, mincnt);
    }

    return 0;
}