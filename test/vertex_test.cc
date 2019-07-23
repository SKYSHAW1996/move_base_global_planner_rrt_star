

#include <gtest/gtest.h>
#include "youibot_rrt/vertex.h"

TEST(VertexTest, SingleVertex) {
  youibot_rrt::Vertex vertex(5.0, 7.5, 3, 2);

  // test get location
  EXPECT_FLOAT_EQ(vertex.get_location().first, 5.0);
  EXPECT_FLOAT_EQ(vertex.get_location().second, 7.5);

  // test get index
  EXPECT_EQ(vertex.get_index(), 3);

  // test get_parent
  EXPECT_EQ(vertex.get_parent(), 2);

  // use setter methods and retest
  vertex.set_location(3.0, 6.23);
  vertex.set_index(12);
  vertex.set_parent(1);

  // test get location
  EXPECT_FLOAT_EQ(vertex.get_location().first, 3.0);
  EXPECT_FLOAT_EQ(vertex.get_location().second, 6.23);

  // test get index
  EXPECT_EQ(vertex.get_index(), 12);

  // test get_parent
  EXPECT_EQ(vertex.get_parent(), 1);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
