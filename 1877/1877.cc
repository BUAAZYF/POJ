#include <algorithm>
#include <cstdio>

using namespace std;

const int MAX = 31;
const int INF = 10000;

int t, m, n, water;
double intercept, now, ans, percentage;
int cnt, elevations[MAX * MAX];

int main() {
    t = 1;
    while (scanf("%d%d", &m, &n) != EOF && m) {
        for (int i = 0; i < m * n; ++i) scanf("%d", &elevations[i]);
        elevations[m * n] = INF;
        scanf("%d", &water);
        sort(elevations, elevations + m * n);
        for (int i = 0; i < m * n; ++i) {
            intercept = elevations[i + 1] - elevations[i];
            now = 100 * (i + 1);
            if (water > intercept * now) {
                water -= intercept * now;
                continue;
            } else {
                ans = double(water) / now + elevations[i];
                percentage = 100 * (double)(i + 1) / (double)(m * n);
                break;
            }
        }
        printf("Region %d\nWater level is %.2lf meters.\n"
        "%.2lf percent of the region is under water.\n\n", t++, ans, percentage);
    }

    return 0;
}