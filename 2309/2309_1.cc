#include<cstdio>
#include<cmath>

using namespace std;

int main(){
    int n, root;
    scanf("%d", &n);
    while(n-- > 0){
        scanf("%d", &root);
        int location = pow(2, int(log2(root))), step = location;
        while(location != root){
            step >>= 1;
            if(location < root) location += step;
            else location -= step;
        }
        printf("%d %d\n", root - (step - 1), root + (step - 1));
    }
}