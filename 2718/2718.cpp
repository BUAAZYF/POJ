#include <algorithm>
#include <cstdio>
#include <vector>

using namespace std;

const int LIMIT = 100000;

int T, n, digit, mindiff, num;
char sep;
vector<int> digits, first, second;
vector<int> first_nums;

void getmindiff() {
    first_nums.resize(0);
    do {
        if (first[0] == 0 && first.size() > 1) continue;
        num = 0;
        for (int i = 0; i < first.size(); ++i) num = num * 10 + first[i];
        first_nums.push_back(num);
    } while (next_permutation(first.begin(), first.end()));
    do {
        if (second[0] == 0 && second.size() > 1) continue;
        num = 0;
        for (int i = 0; i < second.size(); ++i) num = num * 10 + second[i];
        for (int j = 0; j < first_nums.size(); ++j) mindiff = min(mindiff, abs(num - first_nums[j]));
    } while (next_permutation(second.begin(), second.end()));
}

void solve() {
    n = digits.size();
    vector<int> bs(n, 0);
    for (int i = 0; i < (n + 1) / 2; ++i) bs[i] = 1;
    sort(bs.begin(), bs.end());
    do {
        first.resize(0);
        second.resize(0);
        for (int i = 0; i < n; ++i) {
            if (bs[i] == 1)
                first.push_back(digits[i]);
            else
                second.push_back(digits[i]);
        }
        getmindiff();
    } while (next_permutation(bs.begin(), bs.end()));
}

int main() {
    // freopen("in.txt", "r", stdin);
    scanf("%d\n", &T);
    while (T-- > 0) {
        digits.resize(0);
        mindiff = LIMIT;
        while (true) {
            scanf("%d", &digit);
            digits.push_back(digit);
            if ((sep = getchar()) != ' ') break;
        }
        solve();
        printf("%d\n", mindiff);
    }

    return 0;
}