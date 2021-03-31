#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;
const int MAX = 20005;
const int MOD = 1000000007;

int inline min(int a, int b) {
    return a <= b ? a : b;
}

int inline max(int a, int b) {
    return a >= b ? a : b;
}

int N, K, milk[MAX], ans;
vector<ll> cnt;

int main() {
    while (scanf("%d%d", &N, &K) != EOF) {
        for (int i = 0; i < N; ++i) scanf("%d", &milk[i]);
        ll cur, s;
        int lo = 1, hi = N - K + 1;
        ans = 0;
        while (lo <= hi) {
            int mid = (lo + hi) / 2;
            bool found = false;
            cur = 0, s = 1;
            for (int i = 0; i < mid; ++i) {
                cur = cur * MOD + milk[i];
                s *= MOD;
            }
            cnt.clear();
            for (int i = 0; i + mid <= N; ++i) {
                cnt.push_back(cur);
                cur = cur * MOD - s * milk[i] + milk[i + mid];
            }
            sort(cnt.begin(), cnt.end());
            int ct = 1;
            for (int i = 1; i < cnt.size(); ++i) {
                if (cnt[i] == cnt[i - 1]) {
                    ++ct;
                    if (ct >= K) {
                        found = true;
                        break;
                    }
                } else ct = 1;
            }
            if (found) {
                ans = max(ans, mid);
                lo = mid + 1;
            } else hi = mid - 1;
        }
        printf("%d\n", ans);
    }

    return 0;
}