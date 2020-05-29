#include<cstdio>
#include<cmath>

# define M_PI 3.14159265358979323846
using namespace std;

int main(){
    int scenario, n;
    float R;
    scanf("%d", &scenario);
    for(int s = 1; s <= scenario; ++s){
        scanf("%f %d", &R, &n);
        float r = R * sin(M_PI / n) / (1 + sin(M_PI / n));
        printf("Scenario #%d:\n%.3f\n\n", s, r);
    }
    return 0;
}