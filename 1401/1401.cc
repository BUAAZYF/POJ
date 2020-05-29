#include<cstdio>

using namespace std;

int main(){
    int T, n;
    scanf("%d", &T);
    while(T-- > 0){
        scanf("%d", &n);
        int count = 0;
        while(n){
            count += n / 5;
            n /= 5;
        }
        printf("%d\n", count);
    }
    return 0;
}