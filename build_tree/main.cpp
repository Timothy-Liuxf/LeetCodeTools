#include "build_tree.hpp"

#include <stack>
#include <iostream>
#include <iterator>
#include <unordered_map>

using namespace std;

using TreeNode = leetcode::tree_node;

class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root)
    {
        vector<int> ret;
        stack<TreeNode*> stk;
        while (root || !stk.empty())
        {
            while (root)
            {
                ret.emplace_back(root->val);
                stk.emplace(root);
                root = root->left;
            }
            root = stk.top()->right;
            stk.pop();
        }
        return ret;
    }

    vector<int> inorderTraversal(TreeNode* root)
    {
        stack<TreeNode*> stk;
        vector<int> res;
        TreeNode* tmp;
        while (root) { stk.emplace(root); root = root->left; }
        while (!stk.empty())
        {
            tmp = stk.top();
            stk.pop();
            res.emplace_back(tmp->val);
            tmp = tmp->right;
            while (tmp) { stk.emplace(tmp); tmp = tmp->left; }
        }
        return res;
    }

    vector<int> postorderTraversal(TreeNode* root)
    {
        vector<int> ret;
        stack<TreeNode*> stk;
        unordered_map<TreeNode*, bool> visited;
        if (!root) return ret;
        stk.emplace(root);
        bool flag;
        while (!stk.empty())
        {
            root = stk.top();
            flag = false;
            if (root->right && !visited[root->right])
            {
                flag = true;
                stk.emplace(root->right);
            }
            if (root->left && !visited[root->left])
            {
                flag = true;
                stk.emplace(root->left);
            }
            if (!flag)
            {
                stk.pop();
                visited[root] = true;
                ret.emplace_back(root->val);
            }
        }
        return ret;
    }
};

int main()
{
    try
    {
        auto lst = leetcode::get_nodes("[1,5,8, 9,null,10,7,   null,null,null,9,null,8,8,null]");
        for (const auto& itms : lst)
        {
            cout << (itms.has_value() ? std::to_string(itms.value()) : "nullopt") << ", ";
        }
        endl(cout);

        auto head = leetcode::build_tree(lst);
        try
        {
            Solution s;
            auto preorder = s.preorderTraversal(head);
            auto intorder = s.inorderTraversal(head);
            auto postorder = s.postorderTraversal(head);

            ostream_iterator<int> os(cout, ", ");
            cout << "pre: ";
            copy(begin(preorder), end(preorder), os);
            endl(cout);
            cout << "int: ";
            copy(begin(intorder), end(intorder), os);
            endl(cout);
            cout << "post: ";
            copy(begin(postorder), end(postorder), os);
            endl(cout);
        }
        catch (...)
        {
            destroy_tree(head);
        }
        leetcode::destroy_tree(head);
    }
    catch (std::exception& e)
    {
        cout << e.what() << endl;
    }
    return 0;
}
