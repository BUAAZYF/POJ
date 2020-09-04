#include <cstdio>
#include <vector>

using namespace std;

const int MAX = 14;

int n;
vector<int> nums;
int ans[MAX];

int main() {
    int bad;
    for (int k = 1;k < MAX; ++k) {
        for (int m = k + 1; ; ++m) {
            nums.resize(2 * k);
            bad = k;
            for (int i = 0; i < 2 * k; ++i) nums[i] = i;
            for (int i = (m - 1) % nums.size(); ; i = (i + m - 1) % nums.size()) {
                if (nums[i] < k && bad > 0) break;
                --bad;
                nums.erase(nums.begin() + i);
                if (bad == 0) break;
            }
            if (bad == 0) {
                ans[k] = m;
                break;
            }
        }
    }
    while (scanf("%d", &n) != EOF && n) printf("%d\n", ans[n]);

    return 0;
}