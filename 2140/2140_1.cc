#include<cstdio>

using namespace std;

int main(){
    int n;
    scanf("%d", &n);
    if(n == 1){
        printf("1\n");
        return 0;
    }
    int res = 0;
    for(int i = 1;i < n; ++i){
        double m = (2.0 * n / i - i + 1) / 2;
        if(m <= 0) break;
        if(int(m) == m) res += 1;
    }
    printf("%d\n", res);
    return 0;
}