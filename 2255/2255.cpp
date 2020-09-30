#include <cstdio>
#include <string>
#include <iostream>

using namespace std;

string preorder, inorder, postorder;
struct node {
    char val;
    node*left , *right;
    node(char v): val(v), left(NULL), right(NULL){}
} * root;

node* buildtree(int pl, int pr, int il, int ir) {
    if (pl > pr) return NULL;
    node* root = new node(preorder[pl]);
    if (pl == pr) return root;
    int ii = il;
    while (ii <= ir) {
        if (inorder[ii] == preorder[pl]) break;
        ++ii;
    }
    root->left = buildtree(pl + 1, pl + ii - il, il, ii - 1);
    root->right = buildtree(pl + ii - il + 1, pr, ii + 1, ir);
    return root;
}

void postvisit(node* root) {
    if (root->left) postvisit(root->left);
    if (root->right) postvisit(root->right);
    postorder += root->val;
}

int main() {
    while (cin >> preorder >> inorder) {
        root = buildtree(0, preorder.size() - 1, 0, preorder.size() - 1);
        postorder = "";
        postvisit(root);
        cout << postorder << endl;
    }
    return 0;
}