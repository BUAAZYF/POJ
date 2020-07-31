#include <cstdio>
#include <cstring>

using namespace std;

const int MAX = 30;

int n, m;
long long cnt[MAX], cnt_sum[MAX];
int nums[MAX];

int main() {
    // freopen("in.txt", "r", stdin);
    cnt[1] = cnt[2] = cnt_sum[1] = 9;
    cnt_sum[2] = 18;
    for (int i = 2; 2 * i < MAX; ++i) {
        cnt[i * 2] = cnt[i * 2 - 1] = cnt[i * 2 - 2] * 10;
        cnt_sum[i * 2 - 1] = cnt_sum[i * 2 - 2] + cnt[i * 2 - 1];
        cnt_sum[i * 2] = cnt_sum[i * 2 - 1] + cnt[i * 2];
    }
    while (scanf("%d", &n) != EOF && n != 0) {
        memset(nums, 0, sizeof(nums));
        for (m = MAX - 2; m >= 0; --m)
            if (cnt_sum[m] < n) break;
        ++m;
        int i = 0, j = m - 1, digit = 1, left = m;
        n -= cnt_sum[m - 1];
        while (left > 0 && n > 0) {
            if (left <= 2) {
                nums[i] = nums[j] = n - (m > 2);
                n = 0;
            } else if (n % (cnt[left] / 9) == 0) {
                digit += n / (cnt[left] / 9) - 1;
                nums[i] = nums[j] = digit;
                n = cnt[left] / 9;
            } else {
                digit += n / (cnt[left] / 9);
                nums[i] = nums[j] = digit;
                n %= (cnt[left] / 9);
            }
            digit = 0;
            left -= 2;
            ++i, --j;
        }
        for (int i = 0; i < m; ++i) printf("%d", nums[i]);
        printf("\n");
    }

    return 0;
}