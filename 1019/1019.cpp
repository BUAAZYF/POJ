#include <cmath>
#include <cstdio>

using namespace std;

const int MAX = 31270;

int t, n;
unsigned int len[MAX], presum[MAX], digits[MAX];

int cntdigit(int x) {
    if (digits[x] != 0) return digits[x];
    int xx = x;
    while (xx > 0) {
        xx /= 10;
        ++digits[x];
    }
    return digits[x];
}

int precompute() {
    len[1] = presum[1] = 1;
    for (int i = 2; i < MAX; ++i) {
        len[i] = len[i - 1] + cntdigit(i);
        presum[i] = presum[i - 1] + len[i];
    }
}

int getdigit(int x) {
    int idx = 1;
    while (idx < MAX && presum[idx] < x) ++idx;
    x -= presum[idx - 1];
    idx = 1;
    while (x > 0) {
        x -= cntdigit(idx);
        ++idx;
    }
    int ans = 0;
    --idx;
    x += cntdigit(idx);
    x = cntdigit(idx) + 1 - x;
    for (int i = 1; i <= x; ++i) {
        ans = idx % 10;
        idx /= 10;
    }
    return ans;
}

int main() {
    precompute();
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        printf("%d\n", getdigit(n));
    }

    return 0;
}