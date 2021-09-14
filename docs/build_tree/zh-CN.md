# 开发文档

## build_tree

#### 结构

##### `struct leetcode::tree_node`

二叉树的结点，成员如下：  

+ `int val`：结点的值。  

+ `tree_node* left`：指向左孩子的指针。 

+ `tree_node* right`：指向右孩子的指针。

+ `explicit constexpr tree_node(int val, tree_node* left, tree_node* right) noexcept`：构造函数。  

  参数： 

  + `val`：成员 `val` 的初始值。  
  + `left`：成员 `left` 的初始值。  
  + `right`：成员 `right` 的初始值。  

#### 函数

##### `leetcode::build_tree`

`inline tree_node* leetcode::build_tree(std::vector<std::optional<int>> input)`：

+ 描述

  根据要创建的二叉树的描述创建一棵二叉树。  

+ 参数

  + `input`：一个 `std::optional<int>` 的列表（作为 `std::vector` 储存）。该列表可以由函数 [`leetcode::get_nodes`](#user-content-leetcode::get_nodes) 或 [`leetcode::get_nodes_by_regex`](#user-content-leetcode::get_nodes_by_regex) 生成。  

+ 返回值

  一棵二叉树，结点由 `operator new` 分配。

##### `leetcode::destroy_tree`

`inline void destroy_tree(tree_node*& head)`：

+ 描述

  销毁一棵二叉树。

+ 参数
  + `head`：要销毁的树的引用。该树的结点应当由 `operator new` 分配。  

##### `leetcode::get_nodes`

`inline std::vector<std::optional<int>> get_nodes(const std::string& input)`：

+ 描述

  将一个字符串形式表示的代表二叉树的数组转换成存储树节点值的列表。如果字符串非法，将抛出 `std::invalid_argument` 异常。  

+ 参数

  + `const std::string& input`：一个描述二叉树的字符串的常引用。该字符串应当以 “[” 开始，以 “]” 结束，并且它应当以 “,” 来分隔各个值，使用 “null” 来代表此处不存在子树。字符串中的空格将被忽略。  

+ 返回值  

  一个存储树结点值的列表（`std::vector<std::optional<int>>`）。如果该处有结点，则元素的值将为结点值；否则该元素的值将会是 `std::nullopt`。  

+ 例子  

  例如，如果参数是 `"[ 1, 2, null, 3, 4, null, 5, 6, 7, 8, null, null, 9, null, 10 ]" `，那么返回值将会是 `{ 1, 2, std::nullopt, 3, 4, std::nullopt, 5, 6, 7, 8, std::nullopt, std::nullopt, 9, std::nullopt, 10 }`。  

##### `leetcode::get_nodes_by_regex`

`inline std::vector<std::optional<int>> get_nodes_by_regex(const std::string& input)`：

+ 描述  

  本函数的功能与函数 [`leetcode::get_nodes`](#user-content-leetcode::get_nodes) 相同。但本函数使用正则表达式 `std::regex` 实现。总的来说，使用此函数编译速度较慢。  

