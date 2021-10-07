// 给定一个二叉树和一个值，请找出所有的根节点到叶子节点的节点值之和等于 的路径，

#include <vector>

using namespace std;

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
 };

class Solution {
public:
    /**
     * 
     * @param root TreeNode类 
     * @param sum int整型 
     * @return int整型vector<vector<>>
     */
    vector <vector<int> > result;
    vector<vector<int> > pathSum(TreeNode* root, int sum) {
        path_sum(root, sum, vector<int>());
        return result;
    }
    void path_sum(TreeNode *node ,int num, vector<int>vet) {
        if(nullptr == node) {
            return;
        }

        if (nullptr == node->left && nullptr == node->right) {
            if (node->val == num) {
                vet.push_back(num);
                result.push_back(vet);
                return;
            }
        }
        vet.push_back(node->val);
        path_sum(node->left, num-node->val, vet);
        path_sum(node->right, num-node->val, vet); 
        
    }
};