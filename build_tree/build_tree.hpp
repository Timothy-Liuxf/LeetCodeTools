#pragma once

#ifndef BUILD_TREE_HPP__
#define BUILD_TREE_HPP__

#ifndef  __cplusplus
#error The header <build_tree.hpp> is only for C++!
#endif // ! __cplusplus

#include <vector>
#include <optional>
#include <queue>
#include <utility>
#include <stdexcept>
#include <string>
#include <regex>

#define LEETCODE_NAMESPACE_BEGIN namespace leetcode {
#define LEETCODE_NAMESPACE_END }

LEETCODE_NAMESPACE_BEGIN

struct tree_node
{
    int val;
    tree_node* left;
    tree_node* right;
    explicit constexpr tree_node(int val = 0, tree_node* left = nullptr, tree_node* right = nullptr) noexcept
        : val(val), left(left), right(right) {}
};

inline void destroy_tree(tree_node*& head)
{
    if (head == nullptr) return;
    destroy_tree(head->left);
    destroy_tree(head->right);
    delete head;
    head = nullptr;
}

inline tree_node* build_tree(std::vector<std::optional<int>> input)
{
    if (input.empty() || !input[0].has_value()) return nullptr;

    tree_node* head = new tree_node(input[0].value());
    try
    {
        std::queue<tree_node*> leaves;
        leaves.emplace(head);
        for (auto itr = begin(input) + 1; itr != end(input) && !leaves.empty(); ++itr)
        {
            auto tmp_node = leaves.front();
            leaves.pop();
            if (itr->has_value())
            {
                tmp_node->left = new tree_node(itr->value());
                leaves.emplace(tmp_node->left);
            }
            ++itr;
            if (itr != end(input) && itr->has_value())
            {
                tmp_node->right = new tree_node(itr->value());
                leaves.emplace(tmp_node->right);
            }
        }
    }
    catch (...)
    {
        destroy_tree(head);
        throw;
    }
    return head;
}


// Use regex to simplify this function?

inline std::vector<std::optional<int>> get_nodes(const std::string& input)
{
    if (input.size() < 2 || input.front() != '[' || input.back() != ']')
    {
        throw std::invalid_argument("The input string is invalid!");
    }
    std::string::size_type pos = 1;
    std::vector<std::optional<int>> ret;
    while (true)
    {
        auto find_pos = input.find_first_not_of(' ', pos);
        if (find_pos == input.size() - 1) break;

        if (input[find_pos] == 'n')
        {
            if (find_pos + 4 >= input.size() || input.compare(find_pos, 4, "null") != 0)
                throw std::invalid_argument("The input string is invalid!");
            ret.emplace_back(std::nullopt);
            pos = find_pos + 4;
        }
        else
        {
            auto end_pos = input.find_first_not_of("0123456789", find_pos);
            if (end_pos == find_pos) throw std::invalid_argument("The input string is invalid!");
            auto val = std::stoi(input.substr(find_pos, end_pos - find_pos));
            ret.emplace_back(val);
            pos = end_pos;
        }
        pos = input.find_first_not_of(' ', pos);
        if (pos == input.size() - 1) break;
        if (input[pos] != ',') throw std::invalid_argument("The input string is invalid!");
        ++pos;
    }
    return ret;
}

// Regex version

inline std::vector<std::optional<int>> get_nodes_by_regex(const std::string& input)
{
    if (input.size() < 2 || input.front() != '[' || input.back() != ']')
    {
        throw std::invalid_argument("The input string is invalid!");
    }
    if (input.find_first_not_of(' ', 1) == input.size() - 1)
    {
        return {};
    }

    std::regex rgx_num(" *[0-9]+ *");
    std::regex rgx_null(" *null *");
    std::string::size_type pos = 1;
    std::vector<std::optional<int>> ret;

    while (pos < input.size() - 1)
    {
        auto end_pos = input.find_first_of(',', pos);
        if (end_pos == std::string::npos)
        {
            end_pos = input.size() - 1;
        }

        if (std::regex_match(begin(input) + pos, begin(input) + end_pos, rgx_num))
        {
            ret.emplace_back(stoi(input.substr(pos, end_pos - pos)));
        }
        else if (std::regex_match(begin(input) + pos, begin(input) + end_pos, rgx_null))
        {
            ret.emplace_back(std::nullopt);
        }
        else
        {
            throw std::invalid_argument("The input string is invalid!");
        }

        pos = end_pos + 1;
    }

    return ret;
}

LEETCODE_NAMESPACE_END

#endif
