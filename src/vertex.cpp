/*
 * @author SIKAI XIAO
 * @file youibot_rrt/src/vertex.cc
 */

#include "youibot_rrt/vertex.h"

namespace youibot_rrt {
  Vertex::Vertex(float x, float y, int index, int parent_index, float distance_cost) {
    x_ = x;
    y_ = y;
    index_ = index;
    parent_index_ = parent_index;
    distance_cost_ = distance_cost;
  }

  void Vertex::set_location(float x, float y) {
    x_ = x;
    y_ = y;
  }

  void Vertex::set_index(int index) {
    index_ = index;
  }

  void Vertex::set_parent(int parent_index) {
    parent_index_ = parent_index;
  }

  void Vertex::set_distance_cost(int distance_cost) {
    distance_cost_ = distance_cost;
  }

  std::pair<float, float> Vertex::get_location() {
    return std::pair<float, float>(x_, y_);
  }

  int Vertex::get_index() {
    return index_;
  }

  int Vertex::get_parent() {
    return parent_index_;
  }

  float Vertex::get_distance_cost(){
      return distance_cost_;
  }
}  // namespace youibot_rrt
