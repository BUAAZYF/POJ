#include <cstdio>
#include <vector>

using namespace std;

int t, n, m, idx, cnt;
vector<int> nums;

int main() {
    t = 1;
    while (scanf("%d%d", &n, &m) != EOF) {
        nums.resize(n);
        for (int i = 0; i < n; ++i) nums[i] = i + 1;
        for (int i = 0; i < 20; ++i) {
            scanf("%d", &cnt);
            if (m == nums.size()) continue;
            idx = 0;
            while (nums.size() > m && idx + cnt <= nums.size()) {
                nums.erase(nums.begin() + idx + cnt - 1);
                idx += cnt - 1;
            }
        }
        printf("Selection #%d\n", t++);
        for (int i = 0; i < m - 1; ++i) printf("%d ", nums[i]);
        printf("%d\n\n", nums[m - 1]);
    }

    return 0;
}