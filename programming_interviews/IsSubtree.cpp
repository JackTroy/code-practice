struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
	TreeNode(int x) :
			val(x), left(NULL), right(NULL) {
	}
}
class IsSubtree {
public:
    bool HasSubtree(TreeNode* pRoot1, TreeNode* pRoot2)
    {
        if (pRoot1 == NULL || pRoot2 == NULL)   return false;

        bool equal_now = is_subtree(pRoot1, pRoot2);
        if (equal_now) return true;
        else {
            if (HasSubtree(pRoot1->left, pRoot2))       return true;
            else if (HasSubtree(pRoot1->right, pRoot2)) return true;
            else return false;
        }

    }

    bool is_subtree(TreeNode* n1, TreeNode* n2) {
        bool is_n1_null = n1 == NULL, is_n2_null = n2 == NULL;
        if (is_n2_null) return true;
        if (is_n1_null) return false;
        if (!is_node_equal(n1, n2)) return false;

        bool child_equal = is_subtree(n1->left, n2->left)
                            && is_subtree(n1->right, n2->right);

        return child_equal;
    }

    bool is_node_equal(TreeNode* n1, TreeNode* n2) {
        return n1->val == n2->val;
    }
};
