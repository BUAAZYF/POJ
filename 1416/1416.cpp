#include <cstdio>
#include <vector>

using namespace std;

int min(int a, int b) {
    return a <= b ? a : b;
}

int max(int a, int b) {
    return a >= b ? a : b;
}

int target, src, closed, cnt;
vector<int> ans;

int getmin(int num) {
    int res = 0;
    while (num > 0) {
        res += num % 10;
        num /= 10;
    }
    return res;
}

void dfs(int num, int acc, vector<int>& nums) {
    if (acc > target) return;
    if (num == 0) {
        if (acc == closed)
            ++cnt;
        else if (acc > closed) {
            closed = acc;
            cnt = 1;
            ans = nums;
        }
        return;
    }
    int idx = 1, cur = 0;
    while (num > 0) {
        cur = num % 10 * idx + cur;
        num /= 10;
        idx *= 10;
        nums.push_back(cur);
        dfs(num, acc + cur, nums);
        nums.pop_back();
    }
}

int main() {
    while (scanf("%d%d", &target, &src) != EOF && target + src != 0) {
        if (src <= target) {
            printf("%d %d\n", src, src);
            continue;
        } else if (getmin(src) > target) {
            printf("error\n");
            continue;
        }
        closed = cnt = 0;
        ans.clear();
        vector<int> nums;
        dfs(src, 0, nums);
        if (cnt > 1)
            printf("rejected\n");
        else {
            printf("%d", closed);
            for (int i = ans.size() - 1; i >= 0; --i) printf(" %d", ans[i]);
            printf("\n");
        }
    }

    return 0;
}