#include <cstdio>
#include <map>

using namespace std;

const int MAX = 20005;
const int INF = 1000005;

int inline min(int a, int b) {
    return a <= b ? a : b;
}

int inline max(int a, int b) {
    return a >= b ? a : b;
}

int N, K, ans;
int milk[MAX];

struct Node {
    int begin;
    int end;
    int depth;
    Node* parent;
    map<int, Node*> children;
    Node* suffixLink;
    Node(int begin, int end, int depth, Node* parent) {
        this->begin = begin;
        this->end = end;
        this->parent = parent;
        this->depth = depth;
        this->children.clear();
    }
};

class SuffixTree {
public:
    Node* buildSuffixTree(int* s) {
        Node* root = new Node(0, 0, 0, NULL);
        Node* node = root;
        for (int i = 0, tail = 0; i < N; ++i, ++tail) {
            Node* last = NULL;
            while (tail >= 0) {
                Node* ch = node->children.find(s[i - tail]) != node->children.end() ? node->children[s[i - tail]] : NULL;
                while (ch != NULL && tail >= ch->end - ch->begin) {
                    tail -= ch->end - ch->begin;
                    node = ch;
                    ch = ch->children.find(s[i - tail]) != ch->children.end() ?ch->children[s[i - tail]]: NULL;
                }
                if (ch == NULL) {
                    node->children[s[i]] = new Node(i, N, node->depth + node->end - node->begin, node);
                    if (last != NULL) last->suffixLink = node;
                    last = NULL;
                } else {
                    int t = s[ch->begin + tail];
                    if (t == s[i]) {
                        if (last != NULL) last->suffixLink = node;
                        break;
                    } else {
                        Node* splitNode = new Node(ch->begin, ch->begin + tail, node->depth + node->end - node->begin, node);
                        splitNode->children[s[i]] = new Node(i, N, ch->depth + tail, splitNode);
                        splitNode->children[t] = ch;
                        ch->begin += tail;
                        ch->depth += tail;
                        ch->parent = splitNode;
                        node->children[s[i - tail]] = splitNode;
                        if (last != NULL) last->suffixLink = splitNode;
                        last = splitNode;
                    }
                }
                if (node == root) --tail;
                else node = node->suffixLink;
            }
        }
        return root;
    }
    int dfs(Node* node, int len) {
        if (node->children.empty()) return 1;
        int cnt = 0;
        len += node->end - node->begin;
        for (map<int, Node*>::iterator it = node->children.begin(); it != node->children.end(); ++it) {
            cnt += dfs(it->second, len);
            delete it->second;
        }
        if (cnt >= K && len > ans) ans = len;
        return cnt;
    }
};

int main() {
    while (scanf("%d%d", &N, &K) != EOF) {
        for (int i = 0; i < N; ++i) scanf("%d", &milk[i]);
        ++N;
        milk[N - 1] = INF;
        ans = 0;
        SuffixTree st = SuffixTree();
        Node* root = st.buildSuffixTree(milk);
        st.dfs(root, 0);
        printf("%d\n", ans);

    }
    return 0;
}