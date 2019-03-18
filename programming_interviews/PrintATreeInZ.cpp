#include <vector>
#include <stack>
#include <string>

using namespace std;

class PrintATreeInZ {
public:
    void print_z(TreeNode* root) {
        stack<TreeNode *> stack_out, stack_in;
        stack_out.push(root);

        // true left to right, false r to l
        bool direction = true;

        while (!stack_out.empty()) {
            bool is_first = true;
            while (!stack_out.empty()) {
                TreeNode *p = stack_out.top();
                stack_out.pop();
                if (p == NULL) continue;

                if (is_first)   is_first = false;
                else            cout<<' ';
                cout<<p->val;

                if (direction) {
                    stack_in.push(p->left);
                    stack_in.push(p->right);
                }
                else {
                    stack_in.push(p->right);
                    stack_in.push(p->left);
                }
            }
            cout<<endl;
            direction = !direction;
            swap(stack_in, stack_out);
        }
    }
};
