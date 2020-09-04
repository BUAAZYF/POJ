#include <cstdio>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

int N, M, x;
map<int, int> cnt;
vector<pair<int, int> > order;

bool cmp(const pair<int, int>& a, const pair<int, int>& b) {
    return a.first > b.first || a.first == b.first && a.second < b.second;
}

int main() {
    while(scanf("%d%d", &N, &M) != EOF && N) {
        cnt.clear();
        for (int i = 0;i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                scanf("%d", &x);
                if (cnt.find(x) == cnt.end()) cnt[x] = 0;
                ++cnt[x];
            }
        }
        order.clear();
        for (map<int, int>::iterator it = cnt.begin(); it != cnt.end(); ++it) 
            order.push_back(make_pair(it->second, it->first));
        sort(order.begin(), order.end(), cmp);
        printf("%d ", order[1].second);
        for (int i = 2; i < order.size(); ++i) {
            if (order[i].first != order[1].first) break;
            printf("%d ", order[i].second);
        }
        printf("\n");
    }

    return 0;
}