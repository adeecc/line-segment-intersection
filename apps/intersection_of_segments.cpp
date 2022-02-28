#include <ds/rb_tree.hpp>
#include <iostream>

int main() {
    DS::rb_tree::tree_t<int, int> rb;

    rb.insert(2, 2);
    rb.insert(3, 3);
    rb.insert(4, 4);

    return 0;
}