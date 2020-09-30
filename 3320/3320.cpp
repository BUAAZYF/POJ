#include <cstdio>
#include <map>
#include <set>

using namespace std;

const int MAX = 1000005;

int N, last, cur, ans;
int pages[MAX];
set<int> ideas;
map<int, int> ideas_cnt;

int inline min(int a, int b) {
    return a <= b ? a : b;
}

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; ++i) {
        scanf("%d", &pages[i]);
        ideas.insert(pages[i]);
    }
    last = cur = 0;
    ans = N;
    while (true) {
        while (cur < N && ideas_cnt.size() < ideas.size()) {
            if (ideas_cnt.find(pages[cur]) == ideas_cnt.end()) ideas_cnt[pages[cur]] = 0;
            ++ideas_cnt[pages[cur]];
            ++cur;
        }
        if (ideas_cnt.size() < ideas.size()) break;
        ans = min(ans, cur - last);
        --ideas_cnt[pages[last]];
        if (ideas_cnt[pages[last]] == 0) ideas_cnt.erase(pages[last]);
        ++last;
    }
    printf("%d\n", ans);

    return 0;
}