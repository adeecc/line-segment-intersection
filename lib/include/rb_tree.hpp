/**
 * @file rb_tree.hpp
 * @brief Red Black Tree Implementation Based on Cormen, T., Leiserson, C., Rivest, R. and Stein, C., 2009. Introduction to Algorithms. 3rd ed. 
 */
#pragma once

#include <cstddef>
#include <iterator>

using std::bidirectional_iterator_tag;
using std::iterator;

namespace DS {
namespace rb_tree {

/**
 * @brief enum for node colors
 * 
 */
enum class Color : unsigned {
    BLACK, 
    RED
};

template <typename T>
/**
 * @brief A struct for a node in the rb-tree
 * 
 */
struct node_t {
    using value_type = T;
    using pointer = T *;

    value_type val;

    node_t *p{nullptr}, *left{nullptr}, *right{nullptr};

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
    * @brief Construct a new node t object
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
     * @param val 
     */
    node_t(value_type val) : val(val) {
        left = node_t::nil;
        right = node_t::nil;
        p = node_t::nil;
    }

    static node_t *nil;
   
    bool is_leaf() noexcept;

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
struct iterator_t {
   private:
    /// Pointer to a node_t
    T *m_ptr = T::nil;  

   public:
    /// Type Alias for iterator traits
    using iterator_category = std::bidirectional_iterator_tag;
    /// Type Alias for " "
    using difference_type = std::ptrdiff_t;
    /// Type Alias for " "
    using value_type = T::value_type;
    /// Type Alias for " "
    using pointer = value_type *;
    /// Type Alias for " "
    using reference = value_type &;

    /**
     * @brief Construct a new iterator t object
     * 
     */
    iterator_t(T *ptr) : m_ptr(ptr) {}
    /**
     * @brief Construct a new iterator t object
     * 
     * @param that 
     */
    iterator_t(const iterator_t &that) : m_ptr(that.m_ptr) {}
    /**
     * @brief Construct a new iterator t object
     * 
     */
    iterator_t(iterator_t &&) = default;

    // Operators
    /**
     * @brief Defining = operator for finding a node with particular value in the rb-tree
     * 
     * @param that 
     * @return iterator_t& as an iterator to the node with the specified value
     */
    iterator_t &operator=(const reference that) {
        m_ptr->val = that;
        return *this;
    }
    
    iterator_t &operator=(iterator_t &&) = default;
    
    /**
     * @brief Defining ++ operator as retrieving the successor node in the rb-tree
     * 
     * @return iterator_t as an iterator to the successor node
     */
    iterator_t operator++() {
        m_ptr = m_ptr->successor();
        return *this;
    }

    iterator_t operator++(int) {
        T *temp = m_ptr;
        operator++();
        return iterator_t(temp);
    }
    /**
     * @brief Defining -- operator as retrieving the predecessor node in the rb-tree
     * 
     * @return iterator_t as an iterator to the predecessor node
     */
    iterator_t operator--() {
        m_ptr = m_ptr->predecessor();
        return *this;
    }

    iterator_t operator--(int) {
        T *temp = m_ptr;
        operator--();
        return iterator_t(temp);
    }
    /**
     * @brief Defining == operator on the rb-tree pointers
     * 
     * @param that 
     * @return true 
     * @return false 
     */
    bool operator==(const iterator_t &that) const {
        return m_ptr == that.m_ptr;
    }

    /**
     * @brief ---------------
     * 
     * @return T & 
     */
    operator T &() { return *m_ptr; }
    operator const T &() const { return *m_ptr; }
    
    /**
     * @brief ---------------
     * 
     * @return reference 
     */
    reference operator*() { return m_ptr->val; }
    T *operator->() { return m_ptr; }
};

template <typename T>
struct tree_t {

    using value_type = T;
    // Type Alias for Node
    using node_type = node_t<value_type>;
    // Type Alias for Iterator
    using iterator = iterator_t<node_type>;

   private:
    /// Number of Elements in the Tree
    std::size_t _size = 0;   
    /// Root         
    node_type *root{node_type::nil}; 
    
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
   /**
    * @brief Construct a new tree t object
    * 
    */
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