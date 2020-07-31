#include <algorithm>
#include <cstdio>
#include <map>
#include <utility>

using namespace std;

const int MAX = 1005;

inline int min(int a, int b) {
    return a <= b ? a : b;
}

inline int max(int a, int b) {
    return a >= b ? a : b;
}

int n, m, xx1, yy1, xx2, yy2;
pair<int, int> partitions[MAX], toys[MAX];
int partitions_cnt[MAX];
bool used[MAX];
map<int, int> cnt;

bool isleft(int xx1, int yy1, int xx2, int yy2, int xx3, int yy3) {
    return (xx1 - xx3) * (yy2 - yy3) - (yy1 - yy3) * (xx2 - xx3) > 0;
}

int main() {
    while (scanf("%d%d%d%d%d%d", &n, &m, &xx1, &yy1, &xx2, &yy2) != EOF && n) {
        cnt.clear();
        fill(partitions_cnt, partitions_cnt + MAX, 0);
        fill(used, used + MAX, false);
        for (int i = 0; i < n; ++i) scanf("%d%d", &partitions[i].first, &partitions[i].second);
        for (int i = 0; i < m; ++i) {
            scanf("%d%d", &toys[i].first, &toys[i].second);
            if (toys[i].first < xx1 || toys[i].first > xx2 || toys[i].second > yy1 || toys[i].second < yy2) {
                --i;
                --m;
            }
        }
        sort(partitions, partitions + n);
        sort(toys, toys + m);
        int ti = 0;
        for (int pi = 0; pi < n; ++pi) {
            while (ti < m && toys[ti].first < min(partitions[pi].first, partitions[pi].second)) {
                if (!used[ti]) {
                    ++partitions_cnt[pi];
                    used[ti] = true;
                }
                ++ti;
            }
            int tmp_ti = ti;
            while (tmp_ti < m && toys[ti].first < max(partitions[pi].first, partitions[pi].second)) {
                if (!used[tmp_ti] && isleft(partitions[pi].second, yy2, partitions[pi].first, yy1, toys[tmp_ti].first, toys[tmp_ti].second)) {
                    used[tmp_ti] = true;
                    ++partitions_cnt[pi];
                }
                ++tmp_ti;
            }
        }
        while (ti < m) {
            if (!used[ti]) ++partitions_cnt[n];
            ++ti;
        }
        for (int i = 0; i <= n; ++i) {
            if (partitions_cnt[i] == 0) continue;
            if (cnt.find(partitions_cnt[i]) == cnt.end()) cnt[partitions_cnt[i]] = 0;
            ++cnt[partitions_cnt[i]];
        }
        printf("Box\n");
        for (map<int, int>::iterator it = cnt.begin(); it != cnt.end(); ++it)
            printf("%d: %d\n", it->first, it->second);
    }

    return 0;
}