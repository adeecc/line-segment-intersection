/**
 * @file rb_tree.hpp
 * @brief Red Black Tree Implementation Based on Cormen, T., Leiserson, C., Rivest, R. and Stein, C., 2009. Introduction to Algorithms. 3rd ed.
 */
#pragma once

#include <cstddef>
#include <iterator>

using std::bidirectional_iterator_tag;
using std::iterator;

namespace DS::rb_tree {

/**
 * @brief enum for node colors
 *
 */
enum class Color : unsigned {
    BLACK,
    RED
};

/**
 * @brief A struct for a node in the rb-tree
 *
 */
template <typename T>
struct node_t {
    using value_type = T;
    using pointer = T *;

    /// The value stored in a node
    value_type val;

    /// Pointer to parent of node
    node_t *p{nullptr};

    /// Pointer to left child of node
    node_t *left{nullptr};

    /// Pointer to right child of node
    node_t *right{nullptr};

    /// Color of the node
    Color color{Color::BLACK};

    /**
     * @brief Determine if a node is a left child
     *
     * @return true If a node is left child
     * @return false If a node is not a left child
     */
    bool _is_a_left_child() { return (p != node_t::nil) and (p->left == this); }

    /**
     * @brief Determine if a node is a right child
     *
     * @return true If a node is right child
     * @return false If a node is not a right child
     */
    bool _is_a_right_child() { return (p != node_t::nil) and (p->right == this); }

   public:
    /**
     * @brief Construct a new node t object of nil type (i.e. the node can act as a sentinel)
     *
     */
    node_t() {
        p = this;
        left = this;
        right = this;
    }

    /**
     * @brief Construct a new node t object
     *
     * @param val value to be stored in the node
     */
    node_t(value_type val) : val(val) {
        left = node_t::nil;
        right = node_t::nil;
        p = node_t::nil;
    }

    /// The Sentinel Node
    static node_t *nil;
    /**
     * @brief Determine the node with its maximum value in its subtree
     *
     * @return node_t* the node with its maximum value in its subtree
     */
    node_t *max() { return (right == node_t::nil) ? this : right->max(); }

    /**
     * @brief Determine the node with its minimum value in its subtree
     *
     * @return node_t* the node with its minimum value in its subtree
     */
    node_t *min() { return (left == node_t::nil) ? this : left->min(); }

    /**
     * @brief Determine the successor node with least value greater than the current node
     *
     * @return node_t* the successor node
     */
    node_t *successor() {
        if (right != node_t::nil) return right->min();
        if (_is_a_left_child()) return p;
        node_t *succ = this;
        do {
            succ = succ->p;
        } while ((succ != node_t::nil) and succ->_is_a_right_child());

        if (succ != node_t::nil) {
            return succ->p;
        } else
            return node_t::nil;
    }

    /**
     * @brief Determine the predecessor node with maximum value less than the current node
     *
     * @return node_t* the predecessor node
     */
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
            return node_t::nil;
    }

    /**
     * @brief Determine the sibling of the current node
     *
     * @return node_t* sibling of the current node
     */
    node_t *sibling() {
        if (p == node_t::nil) return node_t::nil;

        return _is_a_left_child() ? p->right : p->left;
    }
};

/// Declare the NIL sentinel
template <typename T>
node_t<T> *node_t<T>::nil = new node_t<T>();

template <typename T>
/**
 * @brief A struct for an iterator of the rb-tree
 *
 */
struct iterator_t {
   private:
    /// Pointer to a node_t
    T *m_ptr = T::nil;

   public:
    /// Type Alias for iterator traits
    using iterator_category = std::bidirectional_iterator_tag;
    /// Type Alias for difference type
    using difference_type = std::ptrdiff_t;
    /// Type Alias for value type
    using value_type = T::value_type;
    /// Type Alias for pointer type
    using pointer = value_type *;
    /// Type Alias for reference type
    using reference = value_type &;

    /**
     * @brief Construct a new iterator t object
     *
     */
    iterator_t(T *ptr) : m_ptr(ptr) {}
    /**
     * @brief Copy Constructor for an interator object
     *
     * @param that
     */
    iterator_t(const iterator_t &that) : m_ptr(that.m_ptr) {}
    /**
     * @brief Move Constructor of the iterator object
     *
     */
    iterator_t(iterator_t &&) noexcept = default;

    /**
     * @brief Define the assignment operator
     *
     * @param that
     * @return iterator_t& reference to the constructed iterator
     */
    iterator_t &operator=(reference that) {
        m_ptr->val = that;
        return *this;
    }

    /**
     * @brief Define the move assignment operator
     *
     * @param that
     * @return iterator_t& reference to the constructed iterator
     */
    iterator_t &operator=(iterator_t &&) noexcept = default;

    /**
     * @brief Define the pre-increment operator
     *
     * @param that
     * @return iterator_t increment the iterator to the successor and return it.
     */
    iterator_t operator++() {
        m_ptr = m_ptr->successor();
        return *this;
    }

    /**
     * @brief Define the pos-increment operator
     *
     * @param that
     * @return iterator_t return the original iterator, and increment the value
     */
    const iterator_t operator++(int) {
        T *temp = m_ptr;
        operator++();
        return iterator_t(temp);
    }

    /**
     * @brief Define the pre-decrement operator
     *
     * @param that
     * @return iterator_t decrement the iterator to the successor and return it.
     */
    iterator_t operator--() {
        m_ptr = m_ptr->predecessor();
        return *this;
    }

    /**
     * @brief Define the pos-decrement operator
     *
     * @param that
     * @return iterator_t return the original iterator, and decrement the value
     */
    const iterator_t operator--(int) {
        T *temp = m_ptr;
        operator--();
        return iterator_t(temp);
    }

    /**
     * @brief Defining == operator on the rb-tree iterators
     *
     * @param that
     * @return true
     * @return false
     */
    bool operator==(const iterator_t &that) const {
        return m_ptr == that.m_ptr;
    }

    /**
     * @brief Defining the address-of operator on the rb-tree iterators
     *
     * @return reference to the value stored in the iterator
     */
    explicit operator T &() { return *m_ptr; }

    /**
     * @brief Defining the address-of operator on the rb-tree iterators
     *
     * @return const reference to the value stored in the iterator
     */
    explicit operator const T &() const { return *m_ptr; }

    /**
     * @brief Defining the indirection operator on the rb-tree iterators
     *
     * @return value stored in the iterator
     */
    reference operator*() { return m_ptr->val; }

    /**
     * @brief Defining the member access operator on the rb-tree iterators
     *
     * @return reference to the value stored in the iterator
     */
    T *operator->() { return m_ptr; }
};

template <typename T>
/**
 * @brief A struct for the rb-tree
 *
 */
struct tree_t {
    // Type Alias for Value Type
    using value_type = T;

    // Type Alias for Node Type
    using node_type = node_t<value_type>;

    // Type Alias for Iterator Type
    using iterator = iterator_t<node_type>;

   private:
    /// Number of Elements in the Tree
    std::size_t _size = 0;
    /// Root of the Balanced BST
    node_type *root{node_type::nil};

    void _transplant(node_type *, node_type *);
    void _delete(node_type *);
    void _delete_fixup(node_type *);

    void _left_rotate(node_type *);
    void _right_rotate(node_type *);
    void _insert_fixup(node_type *);

    node_type *_insert(node_type *z);

    node_type *_find(const value_type &val);
    node_type *_upper_bound(const value_type &val);
    node_type *_lower_bound(const value_type &val);

   public:
    /**
     * @brief Construct a new tree t object
     *
     */
    tree_t() = default;

    /**
     * @brief Find the maximum value item in the tree
     *
     * @return Iterator to the max value item in the tree
     */
    iterator max() { return empty() ? end() : iterator(root->max()); }

    /**
     * @brief Find the minimum value item in the tree
     *
     * @return Iterator to the min value item in the tree
     */
    iterator min() { return empty() ? end() : iterator(root->min()); }

    /**
     * @brief Get the leftmost node in the tree
     *
     * @return Iterator to the leftmost node in the tree
     */
    iterator begin() { return min(); }

    /**
     * @brief Find the item after the last item in the tree; the sentinel
     *
     * @return Iterator to the item after the last item in the tree, the sentinel node
     */
    iterator end() { return iterator(node_type::nil); }

    /**
     * @brief Check if tree is empty
     *
     * @return 1 if tree is empty, 0 otherwise
     */
    bool empty() { return _size == 0; }

    /**
     * @brief Insert intems into the tree
     *
     * @param val value to be inserted
     * @return Iterator to the inserted item
     */
    iterator insert(value_type val) {
        return iterator(_insert(new node_type(val)));
    }

    /**
     * @brief Erase item at iterator from the tree
     * @param it iterator to item being erased from the tree
     */
    void erase(iterator it);

    /**
     * @brief Erase item with entered value from the tree
     * @param val value to be removed from the tree
     */
    void erase(const value_type &val) { erase(find(val)); }

    /**
     * @brief Find an item in the tree
     *
     * @param val value to be searched
     * @return Iterator to the item if found, iterator to node after end otherwise
     */
    iterator find(const value_type &val) { return iterator(_find(val)); }

    /**
     * @brief Find item with with least value greater than input value in the tree
     *
     * @param val value to be searched
     * @return Iterator to the item if found, iterator to node after end otherwise
     */
    iterator upper_bound(const value_type &val) { return iterator(_upper_bound(val)); };

    /**
     * @brief Find item with with least value greater than or equal to input value in the tree
     *
     * @param val value to be searched
     * @return Iterator to the item if found, iterator to node after end otherwise
     */
    iterator lower_bound(const value_type &val) { return iterator(_lower_bound(val)); };

    /**
     * @brief Get the number of items in the tree
     *
     * @return number of items in the tree
     */
    std::size_t size() { return _size; }
};

}  // namespace DS::rb_tree

#include <rb_tree.tpp>