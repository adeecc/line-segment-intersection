#pragma once

#include <cstddef>

namespace DS {
namespace rb_tree {

enum class Color : unsigned {
    BLACK,
    RED
};

template <typename K, typename V>
struct node_t {
    K key;
    V val;
    node_t *p{nullptr}, *left{nullptr}, *right{nullptr};

    Color color{Color::BLACK};

   public:
    bool is_leaf() noexcept;
};

template <typename K, typename V>
struct tree_t {
    using node_ptr_t = node_t<K, V> *;

   private:
    std::size_t _size = 0;              // Number of Elements in the Tree
    node_ptr_t nil = new node_t<K, V>;  // Sentinel node_ptr_t
    node_ptr_t root{nil};               // Root node_ptr_t

    node_ptr_t _minimum(node_ptr_t);

    void _transplant(node_ptr_t, node_ptr_t);
    void _delete(node_ptr_t);
    void _delete_fixup(node_ptr_t);

    void _left_rotate(node_ptr_t);
    void _right_rotate(node_ptr_t);
    void _insert_fixup(node_ptr_t);

    void _predecessor_util(node_ptr_t x, node_ptr_t &pre, K key);
    void _successor_util(node_ptr_t x, node_ptr_t &suc, K key);

   public:
    node_ptr_t search(K key);
    node_ptr_t upper_bound(K key);
    node_ptr_t lower_bound(K key);
    node_ptr_t insert(K key, V val);
    void erase(K key);

    std::size_t size() { return _size; }

    node_ptr_t begin() { return _minimum(root); }
    node_ptr_t end() { return nil; }

    // TODO: Forward and Backward Traversal
    node_ptr_t predecessor(K key);
    node_ptr_t successor(K key);
};

}  // namespace rb_tree
}  // namespace DS

#include <rb_tree.tpp>