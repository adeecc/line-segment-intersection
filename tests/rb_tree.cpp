#include <gtest/gtest.h>

#include <line_segment.hpp>
#include <point.hpp>
#include <rb_tree.hpp>
#include <set>

class RBTreeTest : public ::testing::Test {
   protected:
    typedef DS::rb_tree::tree_t<int, int> _tree_int_t;
    typedef DS::rb_tree::tree_t<Geometry::Point, Geometry::Point*> _tree_pt_t;
};

TEST_F(RBTreeTest, DefaultConstructor) {
    _tree_int_t tree_int;
    ASSERT_EQ(tree_int.size(), 0);
}

TEST_F(RBTreeTest, InsertTest) {
    _tree_int_t tree_int;
    tree_int.insert(2, 12);
    ASSERT_EQ(tree_int.size(), 1);

    tree_int.insert(4, 14);
    ASSERT_EQ(tree_int.size(), 2);

    tree_int.insert(1, 11);
    ASSERT_EQ(tree_int.size(), 3);

    tree_int.insert(6, 16);
    ASSERT_EQ(tree_int.size(), 4);
}

TEST_F(RBTreeTest, EraseTest) {
    _tree_int_t tree_int;
    tree_int.insert(2, 12);
    tree_int.insert(4, 14);
    tree_int.insert(1, 11);
    tree_int.insert(6, 16);

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
    auto node = tree_int.search(4);
    ASSERT_EQ(node, tree_int.end());

    tree_int.insert(2, 12);
    tree_int.insert(4, 14);
    tree_int.insert(1, 11);
    tree_int.insert(6, 16);

    node = tree_int.search(4);
    ASSERT_EQ(node->key, 4);
    ASSERT_EQ(node->val, 14);
}

TEST_F(RBTreeTest, MinimumTest) {
}

TEST_F(RBTreeTest, MaximumTest) {
}

// TODO: Add More Tests. Especially to lower_bound
TEST_F(RBTreeTest, LowerBoundTest) {
    _tree_int_t tree;
    tree.insert(2, 3);
    tree.insert(4, 10);
    tree.insert(7, 12);

    ASSERT_EQ(tree.upper_bound(4)->key, 7);
    ASSERT_EQ(tree.lower_bound(4)->key, 4);

    tree.insert(8, 19);
    tree.erase(7);

    ASSERT_EQ(tree.upper_bound(4)->key, 8);
    ASSERT_EQ(tree.lower_bound(4)->key, 4);
}
