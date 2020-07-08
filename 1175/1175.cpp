#include <algorithm>
#include <cmath>
#include <cstdio>
#include <vector>

using namespace std;

typedef pair<int, int> Pr;

const int MAX = 105;
const int CONN = 8;
const double EPS = 1E-8;

int W, H;
char sky[MAX][MAX];
vector<Pr> cluster;
vector<double> hash_char;
int dx[CONN] = {0, 0, 1, -1, 1, 1, -1, -1};
int dy[CONN] = {1, -1, 0, 0, 1, -1, 1, -1,};

void dfs(int x, int y) {
    cluster.push_back(make_pair(x, y));
    sky[x][y] = '0';
    int nx, ny;
    for (int i = 0; i < CONN; ++i) {
        nx = x + dx[i];
        ny = y + dy[i];
        if (nx >= 0 && nx < H && ny >= 0 && ny < W && sky[nx][ny] == '1') dfs(nx, ny);
    }
}

char assginchar() {
    double chash = 0;
    for (int i = 0; i < cluster.size(); ++i)
        for (int j = 0; j < cluster.size(); ++j)
            chash += sqrt(pow(cluster[i].first - cluster[j].first, 2) + pow(cluster[i].second - cluster[j].second, 2));
    chash += cluster.size();
    int idx = -1;
    for (int i = 0; i < hash_char.size(); ++i) {
        if (abs(chash - hash_char[i]) <= EPS) {
            idx = i;
            break;
        }
    }
    if (idx == -1) {
        hash_char.push_back(chash);
        idx = hash_char.size() - 1;
    }
    for (int i = 0; i < cluster.size(); ++i)
        sky[cluster[i].first][cluster[i].second] = 'a' + idx;
}

int main() {
    // freopen("in.txt", "r", stdin);
    scanf("%d%d", &W, &H);
    for (int i = 0; i < H; ++i) {
        getchar();
        for (int j = 0; j < W; ++j) scanf("%c", &sky[i][j]);
    }
    for (int i = 0; i < H; ++i) {
        for (int j = 0; j < W; ++j) {
            if (sky[i][j] == '1') {
                cluster.clear();
                dfs(i, j);
                assginchar();
            }
        }
    }
    for (int i = 0; i < H; ++i) {
        for (int j = 0; j < W; ++j) printf("%c", sky[i][j]); // != '0' ?  sky[i][j] : ' '
        putchar('\n');
    }

    return 0;
}