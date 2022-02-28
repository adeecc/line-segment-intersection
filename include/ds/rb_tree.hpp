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
    std::size_t _size;                  // Number of Elements in the Tree
    node_ptr_t nil = new node_t<K, V>;  // Sentinel node_ptr_t
    node_ptr_t root{nil};               // Root node_ptr_t

    void _left_rotate(node_ptr_t);
    void _right_rotate(node_ptr_t);

    void _delete(node_ptr_t);
    void _delete_fixup(node_ptr_t);

    void _insert_fixup(node_ptr_t);

   public:
    node_ptr_t insert(K key, V val);
    void erase(K key);

    std::size_t size() const { return _size; }
};

template <typename K, typename V>
void tree_t<K, V>::_left_rotate(node_ptr_t x) {
    node_ptr_t y = x->right;
    x->right = y->left;

    if (y->left != nil)
        y->left->p = x;

    y->p = x->p;

    if (y->p == nil)
        root = y;
    else {
        if (x == x->p->left)
            x->p->left = y;
        else
            x->p->right = y;
    }

    y->left = x;
    x->p = y;
}

template <typename K, typename V>
void tree_t<K, V>::_right_rotate(node_ptr_t y) {
    node_ptr_t x = y->left;
    y->left = x->right;

    if (x->right != nil)
        x->right->p = y;

    x->p = y->p;

    if (y->p == nil)
        root = x;
    else {
        if (y == y->p->left)
            y->p->left = x;
        else
            y->p->right = x;
    }

    x->right = y;
    y->p = x;
}

template <typename K, typename V>
node_t<K, V> *tree_t<K, V>::insert(K key, V val) {
    node_ptr_t z = new node_t<K, V>;
    z->key = key;
    z->val = val;

    node_ptr_t x = root, y = nil;

    while (x != nil) {
        y = x;
        if (key < x->key)
            x = x->left;
        else
            x = x->right;
    }

    z->p = y;

    if (y == nil)
        root = z;
    else {
        if (z->key < y->key)
            y->left = z;
        else
            y->right = z;
    }

    z->left = nil;
    z->right = nil;
    z->color = Color::RED;

    _insert_fixup(z);

    ++_size;
    return z;
}

template <typename K, typename V>
void tree_t<K, V>::_insert_fixup(node_ptr_t z) {
    while (z->p->color == Color::RED) {
        if (z->p == z->p->p->left) {
            node_ptr_t y = z->p->p->right;
            if (y->color == Color::RED) {
                z->p->color = y->color = Color::BLACK;
                z->p->p->color = Color::RED;
                z = z->p->p;
            } else {
                if (z == z->p->right) {
                    z = z->p;
                    _left_rotate(z);
                }

                z->p->color = Color::BLACK;
                z->p->p->color = Color::RED;
                _right_rotate(z->p->p);
            }
        } else {
            node_ptr_t y = z->p->p->left;

            if (y->color == Color::RED) {
                z->p->color = y->color = Color::BLACK;
                z->p->p->color = Color::RED;
                z = z->p->p;
            } else {
                if (z == z->p->left) {
                    z = z->p;
                    _right_rotate(z);
                }

                z->p->color = Color::BLACK;
                z->p->p->color = Color::RED;
                _left_rotate(z->p->p);
            }
        }
    }

    root->color = Color::BLACK;
}

template <typename K, typename V>
void tree_t<K, V>::_delete(node_ptr_t) {}

template <typename K, typename V>
void tree_t<K, V>::_delete_fixup(node_ptr_t) {}

template <typename K, typename V>
void tree_t<K, V>::erase(K key) {}

}  // namespace rb_tree
}  // namespace DS
