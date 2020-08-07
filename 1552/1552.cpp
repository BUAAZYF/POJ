#include <cstdio>
#include <set>

using namespace std;

int x, ans;
set<int> nums;

int main() {
    while (scanf("%d", &x) != EOF && x != -1) {
        nums.clear();
        do {
            nums.insert(x);
        } while (scanf("%d", &x) != EOF && x);
        ans = 0;
        for (set<int>::iterator it = nums.begin(); it != nums.end(); ++it)
            if (*it % 2 == 0 && nums.find(*it / 2) != nums.end()) ++ans;
        printf("%d\n", ans);
    }

    return 0;
}