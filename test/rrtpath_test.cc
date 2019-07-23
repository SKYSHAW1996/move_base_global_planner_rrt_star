

#include "youibot_rrt/youibot_rrt.h"
#include <gtest/gtest.h>



TEST(RRTPlanner, addVertex) {
  youibot_rrt::RRTPlanner* rrt = new youibot_rrt::RRTPlanner();
  youibot_rrt::Vertex v(1.0, 2.0, 0, -1);
  rrt->addVertex(v);
  std::vector<youibot_rrt::Vertex> tree = rrt->getVertexTree();
  EXPECT_EQ(tree.size(), 1);
}

int main(int argc, char** argv) {
  ros::init(argc, argv, "rrt_test");
  testing::InitGoogleTest(&argc, argv);
  
  return RUN_ALL_TESTS();
}

