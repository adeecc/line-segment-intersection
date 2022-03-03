#include <ds/rb_tree.hpp>
#include <iostream>

int main() {
    DS::rb_tree::tree_t<int, int> rb;

    rb.insert(2, 2);
    rb.insert(3, 3);
    rb.insert(4, 4);
    rb.insert(5, 5);
    rb.insert(12, 12);
    rb.insert(13, 13);
    rb.insert(7, 7);
    rb.insert(8, 8);

    rb.erase(12);
    
    return 0;
}