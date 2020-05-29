#include<cstdio>
#include<cmath>

using namespace std;

int main(){
    int n, root;
    scanf("%d", &n);
    while(n-- > 0){
        scanf("%d", &root);
        int level = 0;
        for(int i = root; i % 2 == 0; i >>= 1) ++level;
        int offset = int(pow(2, level)) - 1;
        printf("%d %d\n", root - offset, root + offset);
    }
}