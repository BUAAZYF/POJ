#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;

const int MAX = 405;
const int MAXA = 40001;

struct block {
    int height;
    int cnt;
    int altitude;
} blocks[MAX];

bool cmp(block a, block b) {
    return a.altitude < b.altitude;
}

int K, ans;
int dp[MAXA];

int main() {
    // freopen("in.txt", "r", stdin);
    scanf("%d", &K);
    for (int i = 0; i < K; ++i) scanf("%d%d%d", &blocks[i].height, &blocks[i].altitude, &blocks[i].cnt);
    sort(blocks, blocks + K, cmp);
    fill(dp, dp + MAXA, -1);
    dp[0] = 0;
    for (int i = 0; i < K; ++i) {
        for (int j = 0; j <= blocks[i].altitude; ++j) {
            if (dp[j] >= 0) dp[j] = blocks[i].cnt;
            else if (blocks[i].height <= j && dp[j - blocks[i].height] > 0) dp[j] = dp[j - blocks[i].height] - 1;
            else dp[j] = -1;
        }
    }
    ans = 0;
    for (int j = blocks[K - 1].altitude; j >= 0; --j) {
        if (dp[j] >= 0) {
            ans = j;
            break;
        }
    }
    printf("%d\n", ans);

    return 0;
}