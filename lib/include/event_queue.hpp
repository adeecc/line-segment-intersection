#pragma once

#include <event.hpp>
#include <rb_tree.hpp>

struct EventQueue {
    using node_type = DS::rb_tree::node_t<Event>;
    using container_type = DS::rb_tree::tree_t<Event>;
    using iterator = DS::rb_tree::iterator_t<node_type>;

    void insert(const Event& e);
    void erase(const Event& e);
    Event next();

    iterator find(const Event& e) { return _container.find(e); }
    iterator end() { return _container.end(); }

    bool empty() { return _container.size() == 0; }

   private:
    container_type _container;
};
