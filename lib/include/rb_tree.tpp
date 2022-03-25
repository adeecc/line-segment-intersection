#pragma once

namespace DS {
namespace rb_tree {

template <typename T>
void tree_t<T>::_left_rotate(node_type *x) {
    node_type *y = x->right;
    x->right = y->left;

    if (y->left != node_type::nil)
        y->left->p = x;

    y->p = x->p;

    if (y->p == node_type::nil)
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

template <typename T>
void tree_t<T>::_right_rotate(node_type *y) {
    node_type *x = y->left;
    y->left = x->right;

    if (x->right != node_type::nil)
        x->right->p = y;

    x->p = y->p;

    if (y->p == node_type::nil)
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

template <typename T>
tree_t<T>::node_type *tree_t<T>::_insert(node_type *z) {
    node_type *x = root, *y = node_type::nil;

    while (x != node_type::nil) {
        y = x;
        if (z->val < x->val)
            x = x->left;
        else
            x = x->right;
    }

    z->p = y;

    if (y == node_type::nil)
        root = z;
    else {
        if (z->val < y->val)
            y->left = z;
        else
            y->right = z;
    }

    z->left = node_type::nil;
    z->right = node_type::nil;
    z->color = Color::RED;

    _insert_fixup(z);

    ++_size;
    return z;
}

template <typename T>
void tree_t<T>::_insert_fixup(node_type *z) {
    while (z->p->color == Color::RED) {
        if (z->p == z->p->p->left) {
            node_type *y = z->p->p->right;
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
            node_type *y = z->p->p->left;

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

template <typename T>
tree_t<T>::node_type *tree_t<T>::_find(const value_type &val) {
    node_type *x = root;
    while (x != node_type::nil && x->val != val) {
        if (x->val > val) {
            x = x->left;
        } else {
            x = x->right;
        }
    }
    return x;
}

template <typename T>
tree_t<T>::node_type *tree_t<T>::_upper_bound(const value_type &val) {
    node_type *x = root;
    node_type *upper_bound = node_type::nil;

    while (x != node_type::nil) {
        if (x->val <= val) {
            x = x->right;
        } else {
            upper_bound = x;
            x = x->left;
        }
    }

    return upper_bound;
}

template <typename T>
tree_t<T>::node_type *tree_t<T>::_lower_bound(const value_type &val) {
    node_type *x = root;
    node_type *lower_bound = node_type::nil;

    while (x != node_type::nil) {
        if (x->val < val) {
            x = x->right;
        } else {
            lower_bound = x;
            x = x->left;
        }
    }

    return lower_bound;
}

template <typename T>
void tree_t<T>::_transplant(node_type *u, node_type *v) {
    if (u->p == node_type::nil)
        root = v;

    else if (u == u->p->left)
        u->p->left = v;

    else
        u->p->right = v;

    v->p = u->p;
}

template <typename T>
void tree_t<T>::_delete(node_type *z) {
    node_type *y = z;
    Color y_original_color = y->color;

    node_type *x;
    if (z->left == node_type::nil) {
        x = z->right;
        _transplant(z, z->right);
    } else if (z->right == node_type::nil) {
        x = z->left;
        _transplant(z, z->left);
    }

    else {
        y = z->right->min();
        y_original_color = y->color;
        x = y->right;

        if (y->p == z) {
            x->p = y;
        } else {
            _transplant(y, y->right);
            y->right = z->right;
            y->right->p = y;
        }

        _transplant(z, y);
        y->left = z->left;
        y->left->p = y;
        y->color = z->color;
    }

    delete z;

    if (y_original_color == Color::BLACK)
        _delete_fixup(x);
}

template <typename T>
void tree_t<T>::_delete_fixup(node_type *x) {
    node_type *w;
    while (x != root && x->color == Color::BLACK) {
        if (x == x->p->left) {
            w = x->p->right;
            if (w->color == Color::RED) {
                w->color = Color::BLACK;
                x->p->color = Color::RED;
                _left_rotate(x->p);
                w = x->p->right;
            }

            if (w->left->color == Color::BLACK && w->right->color == Color::BLACK) {
                w->color = Color::RED;
                x = x->p;
            } else {
                if (w->right->color == Color::BLACK) {
                    w->left->color = Color::BLACK;
                    w->color = Color::RED;
                    _right_rotate(w);
                    w = x->p->right;
                }

                w->color = x->p->color;
                x->p->color = Color::BLACK;
                w->right->color = Color::BLACK;
                _left_rotate(x->p);
                x = root;
            }
        } else {
            w = x->p->left;
            if (w->color == Color::RED) {
                w->color = Color::BLACK;
                x->p->color = Color::RED;
                _right_rotate(x->p);
                w = x->p->left;
            }

            if (w->right->color == Color::BLACK && w->left->color == Color::BLACK) {
                w->color = Color::RED;
                x = x->p;
            } else {
                if (w->left->color == Color::BLACK) {
                    w->right->color = Color::BLACK;
                    w->color = Color::RED;
                    _left_rotate(w);
                    w = x->p->left;
                }

                w->color = x->p->color;
                x->p->color = Color::BLACK;
                w->left->color = Color::BLACK;
                _right_rotate(x->p);
                x = root;
            }
        }
    }

    x->color = Color::BLACK;
}

template <typename T>
void tree_t<T>::erase(iterator it) {
    node_type *tmp = _find(*it);
    if (tmp == node_type::nil)
        return;

    _delete(tmp);
    _size--;
}

}  // namespace rb_tree
}  // namespace DS