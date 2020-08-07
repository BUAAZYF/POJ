#include <cmath>
#include <cstdio>

using namespace std;

const double INF = 300.0;

char op;
float h, t, d, x;

int main() {
    while (scanf("%c %f", &op, &x) != EOF && op != 'E') {
        h = t = d = INF;
        if (op == 'T') t = x;
        else if (op == 'D') d = x;
        else h = x;
        getchar();
        scanf("%c %f\n", &op, &x);
        if (op == 'T') t = x;
        else if (op == 'D') d = x;
        else h = x;
        if (h == INF)
            h = t + 0.5555 * (6.11 * exp(5417.7530 * (1 / 273.16 - 1 / (d + 273.16))) - 10);
        else if (t == INF)
            t = h - 0.5555 * (6.11 * exp(5417.7530 * (1 / 273.16 - 1 / (d + 273.16))) - 10);
        else
            d = 1 / ((1 / 273.16) - ((log((((h - t) / 0.5555) + 10.0) / 6.11)) / 5417.7530)) - 273.16;
        h = round(h * 10) / 10.0;
        d = round(d * 10) / 10.0;
        t = round(t * 10) / 10.0;
        printf("T %.1f D %.1f H %.1f\n", t, d, h);
    }

    return 0;
}