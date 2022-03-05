#include <ds/rb_tree.hpp>
#include <iostream>

int main() {
    DS::rb_tree::tree_t<int, int> rb;

    rb.insert(2, 2);
    rb.insert(7, 7);
    rb.insert(32, 32);
    rb.insert(12, 12);
    rb.insert(5, 5);
    rb.insert(1, 1);

    std::cout << "Lower Bounds: " << std::endl;
    std::cout << rb._lower_bound(2)->key << std::endl;
    std::cout << rb._lower_bound(7)->key << std::endl;
    std::cout << rb._lower_bound(12)->key << std::endl;

    std::cout << "Upper Bounds: " << std::endl;
    std::cout << rb._upper_bound(7)->key << std::endl;
    std::cout << rb._upper_bound(5)->key << std::endl;
    std::cout << rb._upper_bound(12)->key << std::endl;

    std::cout << "Search: " << std::endl;
    std::cout << rb._search(12)->key << std::endl;

    rb.erase(7);
    return 0;
}