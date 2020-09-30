#include <algorithm>
#include <cstdio>
#include <vector>


const int INF = 0x7fffffff;

using namespace std;

const int MAX = 2e6;

int a[MAX];
int n, x = 0;
int st[MAX];
vector<int> v;

void solve(int k, int& d) {
    if (2 * k <= x) solve(k << 1, d);
    if (2 * k + 1 <= x) solve((k << 1) + 1, ++d);
    v.push_back(a[k] - d);
}

int main() {
    scanf("%d", &n);
    while (scanf("%d", &a[++x]) != EOF) ;
    int d = 0;
    --x;
    solve(1, d);
    st[0] = -INF;
    int top = 0;
    for (int i = 0, len = v.size(); i < len; ++i) {
        if (v[i] >= st[top]) st[++top] = v[i];
        else {
            int k = upper_bound(st, st + top + 1, v[i]) - st;
            st[k] = v[i];
        }
    }
    printf("%d\n", x - top);
    return 0;
}