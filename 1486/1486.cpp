#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

const int MAX = 30;
const int INF = 0x3f3f3f3f;

int inline min(int a, int b) {
    return a <= b ? a : b;
}

int N, V, t;
vector<int> graph[2 * MAX];
int matched[2 * MAX], slides_id[MAX];
bool inslides[MAX][MAX], used[2 * MAX];

struct {
    int xmin, ymin, xmax, ymax;
}slides[MAX];

struct {
    int x, y;
}points[MAX];

bool contains(int i, int j) {
    return slides[i].xmin <= points[j].x && slides[i].xmax >= points[j].x \
    && slides[i].ymin <= points[j].y && slides[i].ymax >= points[j].y;
}

void add_edge(int u, int v) {
    graph[u].push_back(v);
    graph[v].push_back(u);
}

bool dfs(int v) {
    used[v] = true;
    for (int i = 0; i < graph[v].size(); ++i) {
        int u = graph[v][i], w = matched[u];
        if (w < 0 || !used[w] && dfs(w)) {
            matched[v] = u;
            matched[u] = v;
            return true;
        }
    }
    return false;
}

int bipartite_matching() {
    int ans = 0;
    memset(matched, -1, sizeof(matched));
    for (int v = 0; v < V; ++v) {
        if (matched[v] >= 0) continue;
        memset(used, false, sizeof(used));
        if (dfs(v)) ++ans;
    }
    return ans;
}

int main() {
    t = 1;
    while (scanf("%d", &N) != EOF && N) {
        V = 2 * N;
        for (int i = 0; i < N; ++i) scanf("%d%d%d%d", &slides[i].xmin, &slides[i].xmax, &slides[i].ymin, &slides[i].ymax);
        for (int i = 0; i < N; ++i) scanf("%d%d", &points[i].x, &points[i].y);
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j) inslides[i][j] = contains(i, j);
        memset(slides_id, -1, sizeof(slides_id));
		for (int i = 0; i < N; ++i) {
			int match_count = 0;
			for (int k = 0; k < N; ++k) {
				if (inslides[i][k]) {
					for (int v = 0; v < V; ++v) graph[v].clear();
					for (int j = 0; j < N; ++j) {
						if (i != j) {
							for (int l = 0; l < N; ++l)
								if (k != l && inslides[j][l]) add_edge(j, N + l);
						}
					}
					if (bipartite_matching() == N - 1) {
						++match_count;
						slides_id[i] = k;
					}
				}
			}
			if (match_count != 1) slides_id[i] = -1;
		}
        printf("Heap %d\n", t++);
        bool has = false;
        for (int i = 0; i < N; ++i)
            if (slides_id[i] != -1) {
                printf("%s(%c,%d)", (has ? " " : ""), i + 'A', slides_id[i] + 1);
                has = true;
            }
        if (has) printf("\n\n");
        else printf("none\n\n");
    }

    return 0;
}