#pragma once

#include <cstddef>
#include <iterator>

using std::bidirectional_iterator_tag;
using std::iterator;

namespace DS {
namespace rb_tree {

enum class Color : unsigned {
    BLACK,
    RED
};

template <typename T>
struct node_t {
    using value_type = T;
    using pointer = T *;

    value_type val;

    node_t *p{nullptr}, *left{nullptr}, *right{nullptr};

    Color color{Color::BLACK};

    bool _is_a_left_child() { return (p != node_t::nil) and (p->left == this); }
    bool _is_a_right_child() { return (p != node_t::nil) and (p->right == this); }

   public:
    node_t() {
        p = this;
        left = this;
        right = this;
    }

    node_t(value_type val) : val(val) {
        left = node_t::nil;
        right = node_t::nil;
        p = node_t::nil;
    }

    static node_t *nil;

    bool is_leaf() noexcept;

    node_t *max() { return (right == node_t::nil) ? this : right->max(); }
    node_t *min() { return (left == node_t::nil) ? this : left->min(); }

    node_t *successor() {
        if (right != node_t::nil) return right->min();
        if (_is_a_left_child()) return p;

        // node does NOT have a right subtree and is NOT a left child.
        // find for the next ancestor which is a left child
        node_t *succ = this;
        do {
            succ = succ->p;
        } while ((succ != node_t::nil) and succ->_is_a_right_child());

        if (succ != node_t::nil) {
            return succ->p;
        } else
            return nullptr;
    }

    node_t *predecessor() {
        if (left != node_t::nil) return left->max();
        if (_is_a_right_child()) return p;

        node_t *pred = this;
        do {
            pred = pred->p;
        } while ((pred != node_t::nil) and pred->_is_a_left_child());

        if (pred != node_t::nil) {
            return pred->p;
        } else
            return nullptr;
    }

    node_t *sibling() {
        if (p == node_t::nil) return nullptr;

        return _is_a_left_child() ? p->right : p->left;
    }
};

// Decalre the NIL sentinel
template <typename T>
node_t<T> *node_t<T>::nil = new node_t<T>();

template <typename T>
struct iterator_t {
   private:
    T *m_ptr = nullptr;  // Pointer to a node_t

   public:
    // Type definitions
    using iterator_category = std::bidirectional_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = T::value_type;
    using pointer = value_type *;
    using reference = value_type &;

    // Constructors:
    iterator_t(T *ptr) : m_ptr(ptr) {}
    iterator_t(const iterator_t &that) : m_ptr(that.m_ptr) {}
    iterator_t(iterator_t &&) = default;

    // Operators
    iterator_t &operator=(const reference that) {
        m_ptr->val = that;
        return *this;
    }

    iterator_t &operator=(iterator_t &&) = default;

    iterator_t operator++() {
        m_ptr = m_ptr->successor();
        return *this;
    }

    iterator_t operator++(int) {
        T *temp = m_ptr;
        operator++();
        return iterator_t(temp);
    }

    iterator_t operator--() {
        m_ptr = m_ptr->predecessor();
        return *this;
    }

    iterator_t operator--(int) {
        T *temp = m_ptr;
        operator--();
        return iterator_t(temp);
    }

    bool operator==(const iterator_t &that) const {
        return m_ptr == that.m_ptr;
    }

    operator T &() { return *m_ptr; }
    operator const T &() const { return *m_ptr; }

    reference operator*() { return m_ptr->val; }
    T *operator->() { return m_ptr; }
};

template <typename T>
struct tree_t {
    using value_type = T;
    using node_type = node_t<value_type>;
    using iterator = iterator_t<node_type>;

   private:
    std::size_t _size = 0;            // Number of Elements in the Tree
    node_type *root{node_type::nil};  // Root

    void _transplant(node_type *, node_type *);
    void _delete(node_type *);
    void _delete_fixup(node_type *);

    void _left_rotate(node_type *);
    void _right_rotate(node_type *);
    void _insert_fixup(node_type *);

    node_type *_insert(node_type *node);

    node_type *_find(const value_type &val);
    node_type *_upper_bound(const value_type &val);
    node_type *_lower_bound(const value_type &val);

   public:
    tree_t() {}

    iterator max() { return empty() ? end() : iterator(root->max()); }
    iterator min() { return empty() ? end() : iterator(root->min()); }
    iterator begin() { return min(); }
    iterator end() { return iterator(node_type::nil); }
    bool empty() { return _size == 0; }

    iterator insert(value_type val) {
        return iterator(_insert(new node_type(val)));
    }

    void erase(iterator pos);
    void erase(const value_type &val) { erase(find(val)); }

    iterator find(const value_type &val) { return iterator(_find(val)); }
    iterator upper_bound(const value_type &val) { return iterator(_upper_bound(val)); };
    iterator lower_bound(const value_type &val) { return iterator(_lower_bound(val)); };

    std::size_t size() { return _size; }
};

}  // namespace rb_tree
}  // namespace DS

#include <rb_tree.tpp>