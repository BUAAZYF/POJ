#include <algorithm>
#include <cstdio>
#include <vector>

using namespace std;

int main() {
    freopen("in.txt", "r", stdin);
    int n, sum;
    scanf("%d%d\n", &n, &sum);
    vector<int> arr(n);
    for (int i = 0; i < n; ++i) arr[i] = i + 1;
    do {
        vector<int> cur(arr);
        int sz = n;
        while (sz > 1) {
            for (int i = 0; i < sz - 1; ++i) cur[i] += cur[i + 1];
            --sz;
        }
        if (sum == cur[0]) {
            for (int i = 0; i < n - 1; ++i) printf("%d ", arr[i]);
            printf("%d\n", arr[n - 1]);
            break;
        }
    } while (next_permutation(arr.begin(), arr.end()));

    return 0;
}