#include<cstdio>
#include<cstring>


using namespace std;

int abs(int a){
	return a >= 0 ? a : -a;
}


int main(){
	int n, petrol;
	scanf("%d", &n);
	for(int scenario = 1; scenario <= n; ++scenario){
		scanf("%d", &petrol);
		int edge = 2 * petrol + 1;
		char board[edge][edge];
		printf("Scenario #%d:\n", scenario);
		for(int slice = 1; slice <= edge; ++slice){
			memset(board, '.', edge * edge);
			printf("slice #%d:\n", slice);
			int margin = abs(petrol - slice + 1);
			int cur = petrol;
			for(int i = margin; i < edge - margin; ++i){
				board[i][petrol] = cur + '0';
				int left = petrol - 1, right = petrol + 1;
				for(int j = cur + 1; j <= petrol; ++j){
					board[i][left] = board[i][right] = j + '0';
					--left;
					++right;
				}
				if(i < petrol) --cur; else ++cur;
			}
			for(int i = 0; i < edge; ++i){
				for (int j = 0; j < edge; ++j){
					printf("%c", board[i][j]);
				}
				printf("\n");
			}
		}
		printf("\n");
	}

    return 0;
}