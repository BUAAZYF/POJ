#include <cstdio>

using namespace std;

int poly;
bool ishigh, isend;

int inline abs(int x){
    return x >= 0 ? x : -x;
}

int main() {
    while (true) {
        isend = ishigh = false;
        for(int i = 8; i >= 0; --i){
            if(scanf("%d", &poly) == EOF){
                isend = true;
                break;
            }
            if (poly == 0) continue;
            if (!ishigh){
                ishigh = true;
                if(i == 0 || abs(poly) > 1) printf("%d", poly);
                if (i != 0 && poly == -1) printf("-");
                if (i == 1) printf("x");
                if (i > 1) printf("x^%d", i);
            } else {
                printf(" %c ", poly > 0 ? '+' : '-');
                if(i == 0 || abs(poly) > 1) printf("%d", abs(poly));
                if (i == 1) printf("x");
                if (i > 1) printf("x^%d", i);
            }
        }
        if (isend) break;
        if(!ishigh) printf("0");
        printf("\n");  
    }

    return 0;
}