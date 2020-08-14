#include <cstdio>

using namespace std;

int n, s, t, lastt, ans;

int main() {
    while (scanf("%d", &n) != EOF && n != -1) {
        ans = lastt = 0;
        while(n--){
            scanf("%d%d", &s, &t);
            ans += s * (t - lastt);
            lastt = t;
        }
        printf("%d miles\n", ans);
    }

    return 0;
}