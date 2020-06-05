#include <algorithm>
#include <cstdio>
#include <utility>

using namespace std;

const int MAXN = 25005;

int N, T, start, end, ans;
pair<int, int> cows[MAXN];

int main() {
    // freopen("in.txt", "r", stdin);
    scanf("%d%d", &N, &T);
    for (int i = 0; i < N; ++i) scanf("%d%d", &(cows[i].first), &(cows[i].second));
    sort(cows, cows + N);
    ans = 0;
    int i = 0, t = 1, j, et;
    bool hastime;
    while (i < N && t <= T) {
        hastime = false;
        et = t;
        j = i;
        while (j < N) {
            if (cows[j].first > t) break;
            hastime = true;
            et = max(et, cows[j].second + 1);
            ++j;
        }
        if (!hastime) break;
        ++ans;
        t = et;
        i = j;
    }
    printf("%d\n", t > T ? ans : -1);

    return 0;
}