#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAX = 1005;
const int MAXP = 22;

int N, C, c, p, t, r;

struct submission{
    int c, p, t, r;
    friend bool operator<(const submission& a, const submission& b) {
        return a.t < b.t;
    }
}submissions[MAX];

struct team {
    int acc, cost, id, cnt;
    bool solved[MAXP];
    int prob[MAXP];
    team() {}
    team(int _id): acc(0), cost(0), id(_id), cnt(0) {
        memset(solved, false, sizeof(solved));
        memset(prob, 0, sizeof(prob));
    }
    friend bool operator<(const team& a, const team& b) {
        return a.cnt > b.cnt || a.cnt == b.cnt && a.cost < b.cost ||
        a.cnt == b.cnt && a.cost == b.cost && a.id < b.id;
    }
}teams[MAX];

int main() {
    scanf("%d%d", &C, &N);
    for (int i = 1; i <= C; ++i) teams[i] = team(i);
    for (int i = 0;i < N; ++i) scanf("%d%d%d%d", &submissions[i].c, &submissions[i].p, &submissions[i].t, &submissions[i].r);
    sort(submissions, submissions + N);
    for (int i = 0;i < N; ++i) {
        c = submissions[i].c, p = submissions[i].p;
        t = submissions[i].t, r = submissions[i].r;
        if (teams[c].solved[p]) continue;
        if (!r) teams[c].prob[p] += 1200;
        else {
            teams[c].solved[p] = true;
            teams[c].prob[p] += t;
        }
    }
    for (int i = 1; i <= C; ++i) {
        for (int j = 1; j <= MAXP; ++j) {
            if (teams[i].solved[j]) {
                teams[i].cost += teams[i].prob[j];
                ++teams[i].cnt;
            }
        }
    }
    sort(teams + 1, teams + C + 1);
    for (int i = 1; i < C; ++i) printf("%d ", teams[i].id);
    printf("%d\n", teams[C].id);

    return 0;
}