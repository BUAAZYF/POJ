#include <cmath>
#include <cstdio>
#include <queue>

using namespace std;

#define mid ((l)+(r))/2)
const double eps = 1e-8;
const int MAX = 250005;
const int MOD = 1000000;

struct CAR {
    int x, v;
} car[MAX];

struct heap {
    double t, dis;
    int car1, car2;
    heap(double t, double dis, int car1, int car2)
        : t(t), dis(dis), car1(car1), car2(car2) {}
    bool operator<(heap x) const {
        if (fabs(t - x.t) < eps) return dis > x.dis;
        return t > x.t;
    }
};

int n, ans;
int speed[105];
int pre[MAX], nxt[MAX];

priority_queue<heap> q;

int main() {
    //freopen("in.txt", "r", stdin);
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        pre[i] = i - 1;
        nxt[i] = i + 1;
        scanf("%d %d", &car[i].x, &car[i].v);
        ++speed[car[i].v];
        for (int j = car[i].v + 1; j <= 100; ++j) ans = (ans + speed[j]) % MOD;
    }
    printf("%d\n", ans);
    for (int i = 1; i < n; ++i) {
        if (car[i].v > car[i + 1].v) {
            double t = (car[i + 1].x - car[i].x) / (double)(car[i].v - car[i + 1].v);
            q.push(heap(t, car[i].x + t * car[i].v, i, i + 1));
        }
    }
    for (int i = 1; i <= 10000 && !q.empty();) {
        heap hp = q.top();
        q.pop();
        if (nxt[hp.car1] != hp.car2 || pre[hp.car2] != hp.car1) continue;
        nxt[hp.car1] = nxt[hp.car2];
        pre[hp.car2] = pre[hp.car1];
        nxt[hp.car2] = hp.car1;
        pre[hp.car1] = hp.car2;
        nxt[pre[hp.car2]] = hp.car2;
        pre[nxt[hp.car1]] = hp.car1;
        if (nxt[hp.car1] <= n && car[hp.car1].v > car[nxt[hp.car1]].v) {
            double t =
                (double)(car[nxt[hp.car1]].x + car[nxt[hp.car1]].v * hp.t - hp.dis) /
                (car[hp.car1].v - car[nxt[hp.car1]].v);
            q.push(heap(hp.t + t, hp.dis + car[hp.car1].v * t, hp.car1, nxt[hp.car1]));
        }
        if (pre[hp.car2] && car[pre[hp.car2]].v > car[hp.car2].v) {
            double t =
                (double)(hp.dis - car[pre[hp.car2]].v * hp.t - car[pre[hp.car2]].x) /
                (car[pre[hp.car2]].v - car[hp.car2].v);
            q.push(heap(hp.t + t, hp.dis + car[hp.car2].v * t, pre[hp.car2], hp.car2));
        }
        printf("%d %d\n", hp.car1, hp.car2);
        ++i;
    }
    return 0;
}