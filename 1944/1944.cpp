#include <algorithm>
#include <cstdio>
#include <utility>

using namespace std;

typedef pair<int, int> Pr;

const int MAXN = 1005;
const int MAXP = 10005;

int N, P, s, e, ans;
Pr connect[MAXP];

int inline min(int a, int b) {
    return a <= b ? a : b;
}

int inline max(int a, int b) {
    return a >= b ? a : b;
}

int main() {
    while (scanf("%d%d", &N, &P) != EOF) {
        for (int i = 0; i < P; ++i) {
            scanf("%d%d", &s, &e);
            if (s > e) swap(s, e);
            connect[i] = Pr(s, e);
        }
        ans = N;
        for (int skip = 1; skip <= N; ++skip) {
            s = 0, e = N + 1;
            for (int i = 0; i < P; ++i) {
                if (connect[i].first <= skip && skip <= connect[i].second) {
                    s = max(s, connect[i].first);
                    e = min(e, connect[i].second);
                } else if (connect[i].second < skip) s = max(s, connect[i].second);
                else e = min(e, connect[i].first);
            }
            ans = min(ans, s + (N - e));
        }
        printf("%d\n", ans);
    }

    return 0;
}
