#include <event_queue.hpp>

void EventQueue::insert(const Event& e) {
    auto it = _container.find(e);

    if (*it == e) {
        *it = *it | e;
    } else {
        _container.insert(e);
    }
}

void EventQueue::erase(const Event& e) { _container.erase(e); };

Event EventQueue::next() {
    if (_container.empty()) return Event();

    auto it = _container.begin();

    // TODO: Verify if this actually works
    // auto res = std::move(*it);  // Speed Moving >> Copying
    auto res = *it;
    _container.erase(it);
    return res;
}