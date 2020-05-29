#include<cstdio>
#include<vector>

using namespace std;

#define MAXNUM 1000000
int main(){
    bool numbers[MAXNUM + 1];
    vector<int> prime;
    for(int i = 3;i <= MAXNUM; i += 2){
        if(numbers[i]) continue;
        prime.push_back(i);
        for(int k = i * 2; k <= MAXNUM; k += i) numbers[k] = true;
    }
    int n;
    bool found;
    while(true){
        scanf("%d", &n);
        if(n == 0) break;
        found = false;
        for(int i = 0; i < prime.size() && prime[i] <= n / 2; ++i){
            if(!numbers[n - prime[i]]){
                printf("%d = %d + %d\n", n, prime[i], n - prime[i]);
                found = true;
                break;
            }
        }
        if(!found) printf("Goldbach's conjecture is wrong.\n");
    }

    return 0;
}