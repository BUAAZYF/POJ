#include <algorithm>
#include <cstdio>

using namespace std;

const int MAX = 32005;
const int MAXC = 255;

double inline fabs(double a) {
    return a >= 0 ? a : -a;
}

int N, ans;
double L, V, maxdis;
char dir;
struct inhabitant {
    double pos;
    char name[MAXC];
    bool friend operator<(const inhabitant i1, const inhabitant i2) {
        return fabs(i1.pos) < fabs(i2.pos);
    }
} inhabitants[MAX];

int main() {
    while (scanf("%d", &N) != EOF && N) {
        scanf("%lf%lf\n", &L, &V);
        for (int i = 0; i < N; ++i) {
            scanf("%c%lf%s\n", &dir, &inhabitants[i].pos, inhabitants[i].name);
            if (dir == 'n' || dir == 'N') inhabitants[i].pos = -inhabitants[i].pos;
        }
        sort(inhabitants, inhabitants + N);
        bool forward = false;
        double curdis;
        ans = maxdis = 0;
        for (int i = 0; i < N; ++i) {
            curdis = inhabitants[i].pos >= 0 ? L - inhabitants[i].pos : -inhabitants[i].pos;
            if (curdis > maxdis) {
                ans = i;
                maxdis = curdis;
                forward = inhabitants[i].pos > 0;
            }
        }
        int cnt = 0;
        if (forward) {
            for (int i = ans + 1; i < N; ++i)
                if (inhabitants[i].pos < 0) ++cnt;
            ans += cnt;
        } else {
            for (int i = ans - 1; i >= 0; --i)
                if (inhabitants[i].pos > 0) ++cnt;
            ans -= cnt;
        }
        printf("%13.2f %s\n", int(maxdis / V * 100) / 100.0, inhabitants[ans].name);
    }

    return 0;
}