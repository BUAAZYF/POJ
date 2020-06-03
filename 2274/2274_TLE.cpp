#include <algorithm>
#include <cstdio>
#include <map>
#include <queue>
#include <vector>

using namespace std;

const int MAX = 1000000;
const int MAXV = 100;
const int MAXPQ = 10000;

struct item {
    double mtime;
    double mplace;
    int a;
    int b;
};

struct cmp {
    bool operator()(const item& a, const item& b) {
        return a.mtime > b.mtime || (a.mtime == b.mtime && a.mplace > b.mplace);
    }
};

int main() {
    freopen("in.txt", "r", stdin);
    int n, x, v, cnt, nx, nv;
    double mtime, mplace;
    scanf("%d", &n);
    vector<pair<int, int> > spaceships(n);
    vector<pair<int, int> > positions(n);
    map<int, int> pos_num;
    priority_queue<item, vector<item>, cmp> pq;
    for (int i = 0; i < n; ++i) {
        scanf("%d%d", &x, &v);
        spaceships[i] = make_pair(v, x);
        positions[i] = make_pair(x, v);
        pos_num[x] = i + 1;
    }
    sort(spaceships.begin(), spaceships.end(), greater<pair<int, int> >());
    for (size_t i = 0; i < spaceships.size(); ++i) {
        pair<int, int> spaceship = spaceships[i];
        v = spaceship.first;
        x = spaceship.second;
        vector<pair<int, int> >::iterator pos = upper_bound(positions.begin(), positions.end(), make_pair(x, MAXV));
        --pos;
        positions.erase(pos);
        cnt = (cnt + (positions.end() - pos)) % MAX;
        while (pos != positions.end()) {
            nx = pos->first;
            nv = pos->second;
            mtime = double(nx - x) / (v - nv);
            mplace = mtime * v + x;
            if (pq.empty() || pq.size() < MAXPQ) {
                pq.push(item{mtime, mplace, pos_num[x], pos_num[nx]});
            } else if (mtime < pq.top().mtime || (mtime == pq.top().mtime && mplace < pq.top().mplace)) {
                pq.pop();
                pq.push(item{mtime, mplace, pos_num[x], pos_num[nx]});
            }
            ++pos;
        }
    }
    vector<pair<int, int> > ans(pq.size());
    for (int i = 0; i < ans.size(); ++i) {
        ans[i] = make_pair(pq.top().a, pq.top().b);
        pq.pop();
    }
    printf("%d\n", static_cast<int>(ans.size()));
    for (int i = 0; i < ans.size(); ++i) {
        printf("%d %d\n", ans[i].first, ans[i].second);
    }

    return 0;
}