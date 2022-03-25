#include <gtest/gtest.h>

#include <line_segment.hpp>
#include <point.hpp>
#include <rb_tree.hpp>
#include <set>

class RBTreeTest : public ::testing::Test {
   protected:
    typedef DS::rb_tree::tree_t<int> _tree_int_t;
    typedef DS::rb_tree::tree_t<Geometry::Point> _tree_pt_t;
};

TEST_F(RBTreeTest, DefaultConstructor) {
    _tree_int_t tree_int;
    ASSERT_EQ(tree_int.size(), 0);
}

TEST_F(RBTreeTest, InsertTest) {
    _tree_int_t tree_int;
    tree_int.insert(2);
    ASSERT_EQ(tree_int.size(), 1);

    tree_int.insert(4);
    ASSERT_EQ(tree_int.size(), 2);

    tree_int.insert(1);
    ASSERT_EQ(tree_int.size(), 3);

    tree_int.insert(6);
    ASSERT_EQ(tree_int.size(), 4);
}

TEST_F(RBTreeTest, EraseTest) {
    _tree_int_t tree_int;
    tree_int.insert(2);
    tree_int.insert(4);
    tree_int.insert(1);
    tree_int.insert(6);

    ASSERT_EQ(tree_int.size(), 4);

    tree_int.erase(6);
    ASSERT_EQ(tree_int.size(), 3);

    tree_int.erase(4);
    ASSERT_EQ(tree_int.size(), 2);

    tree_int.erase(2);
    ASSERT_EQ(tree_int.size(), 1);

    tree_int.erase(1);
    ASSERT_EQ(tree_int.size(), 0);
}

TEST_F(RBTreeTest, SearchTest) {
    _tree_int_t tree_int;
    auto it = tree_int.find(4);
    ASSERT_EQ(it, tree_int.end());

    tree_int.insert(2);
    tree_int.insert(4);
    tree_int.insert(1);
    tree_int.insert(6);

    it = tree_int.find(4);
    ASSERT_EQ(*it, 4);
}

TEST_F(RBTreeTest, MinimumTest) {
}

TEST_F(RBTreeTest, MaximumTest) {
}

// TODO: Add More Tests. Especially to lower_bound
TEST_F(RBTreeTest, LowerBoundTest) {
    _tree_int_t tree;
    tree.insert(2);
    tree.insert(4);
    tree.insert(7);

    ASSERT_EQ(*tree.upper_bound(4), 7);
    ASSERT_EQ(*tree.lower_bound(4), 4);

    tree.insert(8);
    tree.erase(7);

    ASSERT_EQ(*tree.upper_bound(4), 8);
    ASSERT_EQ(*tree.lower_bound(4), 4);
}
