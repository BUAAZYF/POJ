#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <functional>
#include <utility>

using namespace std;

typedef long long ll;

const int MAX = 25;
const ll CNTMAX = 1000000005;

int n;
ll c, ans;
pair<ll, ll> coins[MAX];
ll used;
ll cnt[MAX];

bool greedy(int idx, ll left) {
    if (left == 0) return true;
    if (idx == n) return false;
    if (coins[idx].second == 0) {
        return greedy(idx + 1, left);
    } else if (coins[idx].first > left) {
        if (!greedy(idx + 1, left)) {
            used = min(used, coins[idx].second);
            cnt[idx] = 1;
        }
        return true;
    } else if (coins[idx].second * coins[idx].first >= left) {
        cnt[idx] = (ll)floor((double(left) / coins[idx].first));
        if (!greedy(idx + 1, left - cnt[idx] * coins[idx].first)) ++cnt[idx];
        used = min(used, (ll)floor((double(coins[idx].second) / cnt[idx])));
        return true;
    } else {
        if (greedy(idx + 1, left - coins[idx].second * coins[idx].first)) {
            cnt[idx] = coins[idx].second;
            used = min(used, 1LL);
            used = min(used, (ll)floor((double(coins[idx].second) / cnt[idx])));
            return true;
        }
        return false;
    }
}

int main() {
    // freopen("in.txt", "r", stdin);
    scanf("%d%lld", &n, &c);
    for (int i = 0; i < n; ++i) scanf("%lld%lld", &coins[i].first, &coins[i].second);
    sort(coins, coins + n, greater<pair<ll, ll> >());
    ans = 0;
    for (int i = 0; i < n; ++i) {
        if (coins[i].second == 0) continue;
        if (coins[i].first >= c) {
            ans += coins[i].second;
        } else {
            if (c % coins[i].first == 0) {
                ans += coins[i].second / (c / coins[i].first);
                coins[i].second %= (c / coins[i].first);
            }
            while (coins[i].second != 0) {
                used = CNTMAX;
                memset(cnt, 0, sizeof(ll) * MAX);
                if (!greedy(i, c) || used == CNTMAX || used == 0) break;
                ans += used;
                for (int k = i; k < n; ++k) coins[k].second -= used * cnt[k];
            }
            ans += coins[i].second / (ll)ceil((double(c) / coins[i].first));
        }
    }
    printf("%lld\n", ans);

    return 0;
}