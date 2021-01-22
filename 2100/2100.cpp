#include <algorithm>
#include <cstdio>
#include <vector>

using namespace std;

typedef long long ll;
typedef pair<ll, ll> Pr;

ll n;
vector<Pr> ans;

bool cmp(Pr a, Pr b) {
    return a.second - a.first >= b.second - b.first;
}

int main() {
    scanf("%lld", &n);
    ans.clear();
    ll i = 1, j = 1, cur = 0;
    while ((j - 1) * (j - 1) <= n) {
        if (cur == n) ans.push_back(make_pair(i, j - 1));
        if (cur >= n) {
            cur -= i * i;
            ++i;
        } else {
            cur += j * j;
            ++j;
        }
    }
    printf("%d\n", ans.size());
    sort(ans.begin(), ans.end(), cmp);
    for (int i = 0; i < ans.size(); ++i) {
        printf("%lld ", ans[i].second - ans[i].first + 1);
        while (ans[i].first < ans[i].second) {
            printf("%lld ", ans[i].first);
            ++ans[i].first;
        }
        printf("%lld\n", ans[i].second);
    }

    return 0;
};