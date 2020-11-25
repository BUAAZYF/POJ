#include <algorithm>
#include <cstdio>
#include <utility>
#include <vector>

using namespace std;

const int MAX = 100005;

int n, m, left, right, k, src[MAX];
pair<int, int> arr[MAX];
vector<int> t[4 * MAX];

void build(int v, int tl, int tr) {
    if (tl == tr) {
        t[v] = vector<int>(1, arr[tl].second);
    } else {
        int tm = (tl + tr) / 2;
        build(v * 2, tl, tm);
        build(v * 2 + 1, tm + 1, tr);
        merge(t[v * 2].begin(), t[v * 2].end(), t[v * 2 + 1].begin(), t[v * 2 + 1].end(),
              back_inserter(t[v]));
    }
}

int query(int v, int tl, int tr, int l, int r, int k) {
    if (tl == tr) return t[v][0];
    int tm = (tl + tr) / 2;
    int total = upper_bound(t[v * 2].begin(), t[v * 2].end(), r) - lower_bound(t[v * 2].begin(), t[v * 2].end(), l);
    if (total >= k) return query(v * 2, tl, tm, l, r, k);
    else return query(v * 2 + 1, tm + 1, tr, l, r, k - total);
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &src[i]);
        arr[i].first = src[i];
        arr[i].second = i;
    }
    sort(arr + 1, arr + n + 1);
    build(1, 1, n);
    while (m--) {
        scanf("%d%d%d", &left, &right, &k);
        printf("%d\n", src[query(1, 1, n, left, right, k)]);
    }

    return 0;
}