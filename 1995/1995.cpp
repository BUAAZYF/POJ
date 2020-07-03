#include <cstdio>

typedef long long ll;

ll Z, M, H, A, B, ans;

ll binpower(ll x, ll n){
    if(n == 0) return 1;
    ll res = binpower(x * x % M, n >> 1);
    if (n & 1) res = res * x % M;
    return res;
}

int main() {
    // freopen("in.txt", "r", stdin);
    scanf("%lld", &Z);
    while(Z-- > 0){
        scanf("%lld%lld", &M, &H);
        ans = 0;
        while(H-- > 0){
            scanf("%lld%lld", &A, &B);
            if(A == 0) continue;
            ans = (ans + binpower(A, B)) % M;
        }
        printf("%lld\n", ans);
    }

    return 0;
}