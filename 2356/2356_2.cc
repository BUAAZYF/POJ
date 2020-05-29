#include<cstdio>
#include<algorithm>

using namespace std;

int main(){
    int n;
    scanf("%d", &n);
    int nums[10000], reminder[10000];
    fill_n(reminder, n, -2);
    reminder[0] = -1;
    int cursum = 0;
    bool found = false;
    for(int i = 0; i < n; ++i) scanf("%d", &nums[i]);
    for(int i = 0; i < n; ++i){
        cursum = (cursum + nums[i]) % n;
        if(reminder[cursum] != -2){
            found = true;
            printf("%d\n", i - reminder[cursum]);
            for(int j = reminder[cursum] + 1; j <= i; ++j) printf("%d\n", nums[j]);
            break;
        }
        reminder[cursum] = i;
    }
    if(!found) printf("0\n");

    return 0;
}