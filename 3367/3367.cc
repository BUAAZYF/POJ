#include <cctype>
#include <cstdio>
#include <cstring>
#include <stack>
#include <vector>

using namespace std;

struct Node {
    char c;
    struct Node* left;
    struct Node* right;
    Node() {
        left = right = NULL;
    }
};

struct Node nodes[10000];

void inorder(struct Node* root, char* orders) {
    if (root == NULL) return;
    int idx = 0;
    vector<struct Node*> cur, next;
    cur.push_back(root);
    while (!cur.empty()) {
        next.clear();
        for (int i = 0; i < cur.size(); ++i) {
            orders[idx++] = cur[i]->c;
            if (cur[i]->right) cur.push_back(cur[i]->right);
            if (cur[i]->left) cur.push_back(cur[i]->left);
        }
        swap(cur, next);
    }
}

int main() {
    int T;
    char c;
    char orders[10000];
    stack<struct Node*> stk;
    scanf("%d\n", &T);
    while (T-- > 0) {
        int n = 0;
        while ((c = getchar()) != '\n') {
            struct Node* node = nodes + n;
            node->c = c;
            node->left = node->right = NULL;
            if (isupper(c)) {
                struct Node* left_node = stk.top();
                stk.pop();
                struct Node* right_node = stk.top();
                stk.pop();
                node->left = left_node, node->right = right_node;
            }
            stk.push(node);
            ++n;
        }
        inorder(stk.top(), orders);
        stk.pop();
        for (int i = n - 1; i >= 0; --i) putchar(orders[i]);
        putchar('\n');
    }

    return 0;
}