#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int INF = 0x3f3f3f3f;
const int MAX = 10001;

int t, x, y, num, cost;
bool isprimes[MAX], used[MAX];
int cur[MAX], nxt[MAX], csz, nsz;
int p10[4] = {1, 10, 100, 1000};

void getnextnum(int num) {
    int digits[4], tmp, nnum;
    tmp = num;
    for(int i = 3; i >= 0; --i) {
        digits[i] = tmp % 10;
        tmp /= 10;
    }
    for(int i = 0; i < 4; ++i) {
        tmp = num - digits[i] * p10[3 - i];
        for(int j = (i == 0 ? 1: 0); j <= 9; ++j){
            nnum = tmp + j * p10[3 - i];
            if(isprimes[nnum] && !used[nnum]){
                used[nnum] = true;
                nxt[nsz++] = nnum;
            }
        }
    }
}

int main() {
    // freopen("in.txt", "r", stdin);
    for (int i = 2; i <= MAX; ++i) isprimes[i] = true;
    for (int i = 2; i <= MAX; ++i) {
        if (!isprimes[i]) continue;
        for (int j = 2 * i; j <= MAX; j += i) isprimes[j] = false;
    }
    scanf("%d", &t);
    while (t-- > 0) {
        scanf("%d%d", &x, &y);
        if (!isprimes[x] || !isprimes[y]) {
            printf("Impossible\n");
            continue;
        }
        if (x == y) {
            printf("0\n");
            continue;
        }
        cost = 0;
        memset(used, false, MAX * sizeof(bool));
        csz = 0;
        cur[csz++] = x;
        used[x] = true;
        while (!used[y] && csz) {
            nsz = 0;
            ++cost;
            for (int i = 0; i < csz; ++i) {
                getnextnum(cur[i]);
                if (used[y]) break;
            }
            csz = nsz;
            swap(cur, nxt);
        }
        if (used[y]) printf("%d\n", cost);
        else printf("Impossible\n");
    }

    return 0;
}