#include<cstdio>
#include<cmath>


using namespace std;


int main(){
	int t;
	int move[10][2] = {{0, 0}, {-1, -1}, {0, -1}, {1, -1}, {-1, 0}, {0, 0}, {1, 0}, {-1, 1}, {0, 1}, {1, 1}};
	scanf("%d", &t);
	char c;
	int direction;
	long long ans;
	while (t-- > 0){
		ans = 0;
		long long cur[2] = {0, 0}, nxt[2] = {0, 0};
		while ((c = getchar()) != '5')
		{
			direction = c - '0';
			nxt[0] = cur[0] + move[direction][0];
			nxt[1] = cur[1] + move[direction][1];
			ans += cur[0] * nxt[1] - cur[1] * nxt[0];
			cur[0] = nxt[0];
			cur[1] = nxt[1];
		}
		getchar();
		ans = (long long)fabs(ans);
		if(ans % 2 == 0) printf("%lld\n", ans/2);
		else printf("%lld.5\n", ans/2);
	}
	
    return 0;
}