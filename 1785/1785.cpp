#include<cstdio>
#include<string>
#include<algorithm>
#include<cmath>


using namespace std;

const int SIZE = 50000;
const int LOGSIZE = 20;


pair<string, int> nodes[SIZE];
int dp[SIZE][LOGSIZE];


int maxidx(int x, int y){
	return nodes[x].second > nodes[y].second ? x : y;
}


void rmq_init(int n)
{
    for (int i = 0; i < n; ++i) dp[i][0] = i;

    for (int i = 1;(1 << i) <= n; ++i) {
		for (int j = 0; j + (1 << i) - 1 < n; ++j) {
			dp[j][i] = maxidx(dp[j][i - 1], dp[j + (1 << (i - 1))][i - 1]);
		}
    }
}

int rmq(int left, int right){
	int t = (int)(log((double)(right - left + 1)) / log(2.0));
	int p = 1 << t;
	return maxidx(dp[left][t], dp[right - p + 1][t]);
}


void formTreaps(int left, int right){
	int maxpriority = rmq(left, right);
	printf("(");
	if(maxpriority > left) formTreaps(left, maxpriority - 1);
	printf("%s/%d", nodes[maxpriority].first.c_str(), nodes[maxpriority].second);
	if(maxpriority < right ) formTreaps(maxpriority + 1, right);
	printf(")");
}


int main(){
	//freopen("in.txt", "r", stdin);
	int n;
	char c;
	string label;
	int priority;
	while(scanf("%d", &n)){
		if(n == 0) break;
		getchar();
		for(int i = 0; i < n; ++i){
			label = "";
			while((c = getchar()) != '/') label += c;
			nodes[i].first = label;
			scanf("%d", &priority);
			nodes[i].second = priority;
			getchar();
		}
		sort(nodes, nodes + n);
		rmq_init(n);
		formTreaps(0, n - 1);
		printf("\n");
	}

    return 0;
}