#include<cstdio>
#include<cmath>

#define PI 3.141592653589793

using namespace std;

int main(){
    double x1, y1, x2, y2, x3, y3, a, b, c, p, S, R;
    while(scanf("%lf%lf%lf%lf%lf%lf", &x1, &y1, &x2, &y2, &x3, &y3) != EOF){
        a = sqrt((x1 - x2) * (x1 - x2)  + (y1 - y2) * (y1 - y2));
        b = sqrt((x1 - x3) * (x1 - x3)  + (y1 - y3) * (y1 - y3));
        c = sqrt((x2 - x3) * (x2 - x3)  + (y2 - y3) * (y2 - y3));
        p = (a + b + c) / 2;
        S = sqrt(p * (p - a) * (p - b) * (p - c));
        R = a * b * c / 4 / S;
        printf("%.2f\n", 2 * PI * R);
    }

    return 0;
}