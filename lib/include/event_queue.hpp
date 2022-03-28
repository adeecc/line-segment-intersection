/**
 * @file event_queue.hpp
 * @brief Event Queue Declaration, with Events stored in a balanced binary tree.
 *
 */
#pragma once

#include <event.hpp>
#include <rb_tree.hpp>

/**
 * @brief A struct for mainting a Event queue
 *
 */

struct EventQueue {
    /// Type Alias for rb-tree node
    using node_type = DS::rb_tree::node_t<Event>;
    /// Type Alias for rb-tree tree
    using container_type = DS::rb_tree::tree_t<Event>;
    /// Type Alias for rb-tree iterator
    using iterator = DS::rb_tree::iterator_t<node_type>;

    /**
     * @brief This method inserts an event in the Event queue
     *
     * @param e
     */
    void insert(const Event& e);

    /**
     * @brief This method removes an event from the Event queue
     *
     * @param e
     */
    void erase(const Event& e);

    /**
     * @brief Find, Remove and Return the next Event in the Queue
     *
     * @return next event to be evaluated
     */
    Event next();

    /**
     * @brief Finding an event in the Event queue
     *
     * @param e
     * @return iterator to the event in the Event queue
     */
    iterator find(const Event& e) { return _container.find(e); }

    /**
     * @brief Obtaining the first event
     *
     * @return iterator to the first event in Event queue
     */
    iterator begin() { return _container.begin(); }

    /**
     * @brief Obtaining the event after the last event in the queue
     *
     * @return iterator to the event after the last event in the queue
     */
    iterator end() { return _container.end(); }

    /**
     * @brief Obtaining the last event
     *
     * @return iterator to the last event in Event queue
     */
    bool empty() { return _container.size() == 0; }

   private:
    /// Container to hold the event queue
    container_type _container;
};
