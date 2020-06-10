#include <algorithm>
#include <cstdio>
#include <utility>

using namespace std;

typedef long long ll;

const int MAX = 100005;

int n;
pair<ll, ll> cows[MAX];
ll curtime, ans;

struct cmp {
    bool operator()(const pair<ll, ll>& a, const pair<ll, ll>& b) {
        return (double)a.second / a.first < (double)b.second / b.first;
    }
};

int main() {
    // freopen("in.txt", "r", stdin);
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) scanf("%lld%lld", &cows[i].second, &cows[i].first);
    sort(cows, cows + n, cmp());
    ans = 0;
    for (int i = 0; i < n; ++i) {
        ans += curtime * cows[i].first;
        curtime += 2 * cows[i].second;
    }
    printf("%lld\n", ans);

    return 0;
}