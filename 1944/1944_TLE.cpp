#include <algorithm>
#include <bitset>
#include <cstdio>
#include <string>

using namespace std;

const int MAXN = 1005;
const int MAXP = 10005;

int N, P, s, e, cnt, ans;
bitset<MAXN> state, connect[MAXP];

int inline min(int a, int b) {
    return a <= b ? a : b;
}

int main() {
    while (scanf("%d%d", &N, &P) != EOF) {
        for (int i = 0; i < P; ++i) {
            scanf("%d%d", &s, &e);
            if (s > e) swap(s, e);
            connect[i] = bitset<MAXN>(string(e - s, '1') + string(s, '0'));
        }
        ans = N;
        for (int skip = 1; skip <= N; ++skip) {
            state = 0;
            for (int i = 0; i < P; ++i) {
                if (connect[i].test(skip)) state |= ~connect[i];
                else state |= connect[i];
            }
            cnt = 0;
            for (int i = 1; i <= N; ++i) cnt += state[i];
            ans = min(ans, cnt);
        }
        printf("%d\n", ans);
    }

    return 0;
}