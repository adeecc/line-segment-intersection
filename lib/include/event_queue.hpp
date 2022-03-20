#pragma once

#include <event.hpp>
#include <rb_tree.hpp>

struct EventQueue {
    using container_t = DS::rb_tree::tree_t<point_t, Event*>;
    using node_t = DS::rb_tree::node_t<point_t, Event*>;

    void insert(const point_t& pt, Event* e);
    void erase(const point_t& pt);
    Event* next();

    node_t* search(const point_t& pt) { return _container.search(pt); }
    node_t* end() { return _container.end(); }

    bool empty() { return _container.size() == 0; }

   private:
    container_t _container;
};
