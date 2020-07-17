#include <algorithm>
#include <cstdio>
#include <vector>

using namespace std;

const int MAX = 100005;

int inline max(int a, int b) {
    return a >= b ? a : b;
}

int inline min(int a, int b) {
    return a <= b ? a : b;
}

struct calve{
    int score, aid;
    bool operator<(const calve& b) const{
        return this->aid < b.aid;
    }
}calves[MAX];

int N, C, F, left, right, ans;
vector<int> scores;

int main() {
    // freopen("in.txt", "r", stdin);
    scanf("%d%d%d", &N, &C, &F);
    for (int i = 0; i < C; ++i){
        scanf("%d%d", &calves[i].score, &calves[i].aid);
        scores.push_back(calves[i].score);
    }
    sort(scores.begin(), scores.end());
    left = 0, right = (int)scores.size() - 1;
    ans = -1;
    sort(calves, calves + C);
    int less_cnt, more_cnt, mid_cnt, aid;
    N >>= 1;
    while(left <= right){
        less_cnt = more_cnt = mid_cnt = 0;
        aid = F;
        int mid = (left + right) >> 1;
        for (int i = 0; i < C; ++i){
            if (calves[i].aid > aid) break;
            if (calves[i].score < scores[mid] && less_cnt < N){
                ++less_cnt;
                aid -= calves[i].aid;
            } else if (calves[i].score > scores[mid] && more_cnt < N){
                ++more_cnt;
                aid -= calves[i].aid;
            } else if (calves[i].score == scores[mid]){
                ++mid_cnt;
                aid -= calves[i].aid;
            }
        }
        if(less_cnt + mid_cnt + more_cnt >= 2 * N + 1){
            ans = max(ans, scores[mid]);
            left = mid + 1;
        } else right = mid - 1;
        
    }
    printf("%d\n", ans);

    return 0;
}