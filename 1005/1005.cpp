#include <cmath>
#include <cstdio>

using namespace std;

const double PI = 3.14159265358979;

int N;
double x, y;

int main() {
    scanf("%d", &N);
    for (int t = 1; t <= N; ++t) {
        scanf("%lf%lf", &x, &y);
        printf("Property %d: This property will begin eroding in year %d.\n", t, (int)ceil(PI * (x * x + y * y) / 2 / 50));
    }
    printf("END OF OUTPUT.\n");

    return 0;
}