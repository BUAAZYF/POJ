#include <cstdio>
#include <cstring>

using namespace std;

const int MAX = 10000;

bool isgenerator[MAX + 1];

int generate(int x){
    int xx = x;
    while(xx > 0){
        x += xx % 10;
        xx /= 10;
    }
    return x;
}
int main() {
    memset(isgenerator, false, sizeof(isgenerator));
    int gen;
    for (int i = 1; i <= MAX; ++i){
        gen = generate(i);
        if(gen <= MAX) isgenerator[gen] = true;
        if(!isgenerator[i]) printf("%d\n", i);
    }

    return 0;
}