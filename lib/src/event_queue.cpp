#include <event_queue.hpp>

void EventQueue::insert(const point_t& pt, Event* e) {
    auto node_ptr = _container.search(pt);
    if (node_ptr->key == pt) {
        *(node_ptr->val) = *(node_ptr->val) | *e;  // Merge the events
    } else {
        _container.insert(pt, e);
    }
}

void EventQueue::erase(const point_t& pt) { _container.erase(pt); };

Event* EventQueue::next() {
    if (_container.size() == 0) return nullptr;

    auto min = _container.minimum();

    // TODO: Verify if this actually works
    auto res = std::move(min->val);  // Speed Moving >> Copying
    _container.erase(min->key);

    return res;
}