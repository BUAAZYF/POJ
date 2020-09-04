#include <cstdio>
#include <list>
#include <map>
#include <utility>

using namespace std;

int t, n, m, pri, ans;
list<pair<char, bool> > jobs;
map<int, int, greater<int> > cnt;

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d", &n, &m);
        cnt.clear();
        jobs.clear();
        for (int i = 0; i < n; ++i) {
            scanf("%d", &pri);
            if (i == m) jobs.push_back(make_pair(pri, true));
            else jobs.push_back(make_pair(pri, false));
            if (cnt.find(pri) == cnt.end()) cnt[pri] = 0;
            ++cnt[pri];
        }
        ans = 0;
        list<pair<char, bool> >::iterator it, tmp;
        bool mvend, found = false;
        while (true) {
            it = jobs.begin();
            for (int i = 0; i < n; ++i) {
                mvend = true;
                if (it->first == cnt.begin()->first) {
                    --cnt.begin()->second;
                    mvend = false;
                    ++ans;
                    --n;
                    if (it->second) {
                        found = true;
                        break;
                    }
                    if (cnt.begin()->second == 0) cnt.erase(it->first);
                }
                tmp = it;
                ++tmp;
                if (mvend) jobs.push_back(*it);
                jobs.erase(it);
                it = tmp;
            }
            if (found) break;
        }
        printf("%d\n", ans);
    }

    return 0;
}