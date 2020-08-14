#include <algorithm>
#include <cstdio>
#include <vector>

using namespace std;

const int MAX = 1000005;

int a, d, n;
vector<int> ugly;
int t2 = 1, t3 = 1, t5 = 1;
int cnt = 2;

int nthUglyNumber(int n) {
    if (n <= ugly.size()) return ugly[n - 1];
    while (cnt < n) {
        int v2 = t2 << 1, v3 = t3 * 3, v5 = t5 * 5;
        int minUgly = min(v2, min(v3, v5));
        if (find(ugly.begin(), ugly.end(), minUgly) == ugly.end()) {
            ++cnt;
            ugly.push_back(minUgly);
        }
        if (minUgly == v2) t2 = *upper_bound(ugly.begin(), ugly.end(), t2);
        if (minUgly == v3) t3 = *upper_bound(ugly.begin(), ugly.end(), t3);
        if (minUgly == v5) t5 = *upper_bound(ugly.begin(), ugly.end(), t5);
    }

    return ugly[n - 1];
}
int main() {
    ugly.push_back(1);
    ugly.push_back(2);
    while (scanf("%d", &n) != EOF && n)
        printf("%d\n", nthUglyNumber(n));

    return 0;
}