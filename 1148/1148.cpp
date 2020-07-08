#include <algorithm>
#include <cstdio>

using namespace std;

const int MAX = 10005;

int n, region, leftx, lefty;
int codes[2 * MAX];
char lastsign, signs[2][MAX];
int ans[2][MAX];

bool alternatingseq(int s, int shift) {
    int i, j, k;
    i = j = s;
    if (codes[shift * n + s] * signs[shift][0] < 0)
        return false;
    ans[shift][0] = codes[shift * n + s];
    for (k = 1; k < n; ++k) {
        if (codes[shift * n + j] * signs[shift][k] > 0) {
            --i;
            if (i < 0) return false;
            ans[shift][k] = codes[shift * n + i];
        } else {
            ++j;
            if (j >= n) return false;
            ans[shift][k] = codes[shift * n + j];
        }
    }
    return true;
}

int main() {
    freopen("in.txt", "r", stdin);
    scanf("%d", &n);
    for (int i = 0; i < 2 * n; ++i) scanf("%d", &codes[i]);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &region);
        signs[0][i] = region == 1 || region == 4 ? 1 : -1;
        signs[1][i] = region <= 2 ? 1 : -1;
    }
    sort(codes, codes + 2 * n);
    lastsign = signs[0][n - 1];
    for (int i = n - 1; i >= 0; --i, lastsign *= -1) codes[i] *= lastsign;
    lastsign = signs[1][n - 1];
    for (int i = 2 * n - 1; i >= n; --i, lastsign *= -1) codes[i] *= lastsign;
    leftx = lefty = 0;
    for (int i = 0; i < n - 1; ++i) {
        if (signs[0][i] == signs[0][i + 1]) ++leftx;
        if (signs[1][i] == signs[1][i + 1]) ++lefty;
    }
    if(alternatingseq(leftx, 0) && alternatingseq(lefty, 1)) {
        for (int i = 0; i < n; ++i){
			if (ans[0][i] > 0) printf("+");
			printf("%d ", ans[0][i]);
			if (ans[1][i] > 0) printf("+");
			printf("%d\n", ans[1][i]);
		}
    } else
        printf("0\n");

    return 0;
}