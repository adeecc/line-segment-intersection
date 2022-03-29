#include <gtest/gtest.h>

#include <event.hpp>
#include <event_queue.hpp>

TEST(EventQueueTets, Insertion) {
    double y = 4.5;
    EventQueue q;

    point_t pt(3, 4);
    ComparableSegment seg_upper(segment_t(3, 4, 5, 6), &y);
    ComparableSegment seg_lower(segment_t(5, 6, 3, 4), &y);
    ComparableSegment seg_contain(segment_t(2, 5, 5, 2), &y);

    q.insert(Event(pt, seg_upper, Event::Type::UPPER));
    q.insert(Event(pt, seg_lower, Event::Type::LOWER));
    q.insert(Event(pt, seg_contain, Event::Type::CONTAIN));

    auto it = q.find(Event(pt, ComparableSegment({pt, pt}, &y), Event::Type::OTHER));
    
    ASSERT_EQ((*it).upper.size(), 1);
    ASSERT_EQ((*it).upper[0], seg_upper);

    ASSERT_EQ((*it).lower.size(), 1);
    ASSERT_EQ((*it).lower[0], seg_lower);

    ASSERT_EQ((*it).contain.size(), 1);
    ASSERT_EQ((*it).contain[0], seg_contain);
}