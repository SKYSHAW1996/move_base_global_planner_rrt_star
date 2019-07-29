/*
 * @author SIKAI XIAO
 * @file youibot_rrt/include/youibot_rrt/youibot_rrt.h
 *
 */

#ifndef INCLUDE_YOUIBOT_RRT_YOUIBOT_RRT_H_
#define INCLUDE_YOUIBOT_RRT_YOUIBOT_RRT_H_

/** include ROS libraries **/
#include <ros/ros.h>

#include <move_base_msgs/MoveBaseAction.h>

/** for global path planner interface **/
#include <costmap_2d/costmap_2d_ros.h>
#include <costmap_2d/costmap_2d.h>
#include <nav_core/base_global_planner.h>
#include <geometry_msgs/PoseStamped.h>
#include <angles/angles.h>
#include <base_local_planner/world_model.h>
#include <base_local_planner/costmap_model.h>

/** include standard libraries **/
#include <iostream>
#include <cmath>
#include <set>
#include <string>
#include <vector>
#include <utility>
#include <boost/random.hpp>

/** Local includes **/
#include "youibot_rrt/vertex.h"

namespace youibot_rrt {
class RRTPlanner : public nav_core::BaseGlobalPlanner {
 public:
     /**
     * @brief Constructor for RRTPlanner
     */
     RRTPlanner();

     /**
     * @brief Constructor for RRTPlanner
     * @param costmap_ros cost_map ros wrapper
     * @param name name to associate to the node
     */
     RRTPlanner(std::string name, costmap_2d::Costmap2DROS* costmap_ros);

     /** overridden classes from interface nav_core::BaseGlobalPlanner
     * @brief Initialize the ros handle
     * @param name ROS NodeHandle name
     * @param costmap_ros cost_map ros wrapper
     */
     void initialize(std::string name,
                     costmap_2d::Costmap2DROS* costmap_ros);

     /**
     * @brief follows the virtual method of the base class
     * @param start start pose
     * @param goal goal pose
     * @param plan generated path
     * @return bool, true
     */
     bool makePlan(const geometry_msgs::PoseStamped& start,
                   const geometry_msgs::PoseStamped& goal,
                   std::vector<geometry_msgs::PoseStamped>& plan);

    /**
    * @brief returns the obstacle map
    * @return std::vector<bool> Unsafe cells are false, safe cells are true
    */
    std::vector<bool> getObstacleMap() {
      return obstacle_map_;
    }

    /**
    * @brief returns the rrt vertex tree
    */
    std::vector<youibot_rrt::Vertex> getVertexTree() {
      return vertex_list_;
    }

     /**
     * @brief Gets a random point in the map space
     * @return returns an x,y pair
     */
     std::pair<float, float> GetRandomPoint(const geometry_msgs::PoseStamped& goal);

     /**
     * @brief Gets the closest vertex to the given point
     * @param random_point A point in the map space
     * @param vertex_list the rrt vertex tree
     * @return the index of the closest vertex to the given point
     */
     int GetClosestVertex(std::pair<float, float> random_point);

    /**
    * @brief adds a new vertex to the rrt vertex tree
    * @param new_vertex the new vertex to be added
    */
    void addVertex(youibot_rrt::Vertex new_vertex) {
      vertex_list_.push_back(new_vertex);
    }

     /**
     * @brief Euclidean distance between two points
     * @param start_point starting point
     * @param end_point ending point
     * @return euclidean distance between the points
     */
     float GetDistance(std::pair<float, float> start_point,
                       std::pair<float, float> end_point);

     /**
     * @brief Moves from the closest vertex towards the random point
     * @detail Begins at the closest point and attempts to move step_size_
     * towards the random point. Each step along the way at delta_ intervals
     * is checked for obstacles. If an obstacle is encountered the function
     * returns false. If it makes it from the closest vertex to step_size_
     * towards the random point a new vertex is created and added to
     * vertex_list_ and the function returns true.
     * @return true if a move was made, false if blocked by obstacle
     */
     bool MoveTowardsPoint(int closest_vertex,
                           std::pair<float, float> random_point);

     /**
     * @brief Is vertex within goal_radius_ of the goal
     * @param the vertex to be checked
     * @return true if within goal_radius_
     */
     bool ReachedGoal(int new_vertex);

     /**
     * @brief builds the plan from vertices and returns in PoseStamped
     * @param goal_index the index of the vertex that has reached the goal
     * @param start the starting location of the robot as passed to makePlan
     * @param goal the goal location of the robot as passed to makePlan
     * @return a vector of geometry_msgs:PoseStamped from the start to the goal
     */
     std::vector<geometry_msgs::PoseStamped>
       BuildPlan(int goal_index,
                 const geometry_msgs::PoseStamped& start,
                 const geometry_msgs::PoseStamped& goal);

     /**
     * @brief returns the best path
     * @param start starting point of robot
     * @param goal goal point
     * @return returns the index of the point that reaches the goal
     */
     int FindPath(const geometry_msgs::PoseStamped& start,
                  const geometry_msgs::PoseStamped& goal);

     /**
     * @brief Checks if the path is safe between start_point and end_point
     * @param start_point starting point location
     * @param end_point ending point location
     * @return true if path between points does not intersect obstacles
     */
     bool IsSafe(std::pair<float, float> start_point,
                 std::pair<float, float> end_point);

 private:
     ros::Publisher plan_pub_;
     /**
     * @brief ROS node handle
     */
     ros::NodeHandle node_handle_;

     /**
     * @brief obstacles
     */
     std::vector<bool> obstacle_map_;

     /**
     * @brief The ROS wrapper for the costmap the controller will use
     */
     costmap_2d::Costmap2DROS* costmap_ros_;

     /**
     * @brief The ROS wrapper for the costmap the controller will use
     */
     costmap_2d::Costmap2D* costmap_;

     /**
     * @brief the max number of iterations to try and find a path
     */
     int max_iterations_;

     /**
     * @brief the current number of iterations
     */
     int current_iterations_;

     /**
     * @brief World model associated to the costmap
     */
     base_local_planner::WorldModel* world_model_;

     /**
     * @brief Check if the global planner is initialized
     */
     bool initialized_;

     /**
     * @brief How close to the goal is close enough
     */
     float goal_radius_;

     /**
     * @brief Size of the step the RRT planner takes
     */
     float step_size_;

     /**
     * @brief Size of the sub-step used for collision checking
     */
     float delta_;

     /**
     * @brief x coordinate of robot origin
     */
     float x_origin_;

     /**
     * @brief y coordinate of robot origin
     */
     float y_origin_;

     /**
     * @brief x coordinate of goal
     */
     float x_goal_;

     /**
     * @brief y coordinate of goal
     */
     float y_goal_;

     /**
     * @brief width of 2d map in cells
     */
     unsigned int map_width_cells_;

     /**
     * @brief height of 2d map in cells
     */
     unsigned int map_height_cells_;

     /**
     * @brief List of vertices
     */
     std::vector<youibot_rrt::Vertex> vertex_list_;
     /**
     * @brief flag of whether getting succuseful path
     */
     bool plan_succuse_flag = false;
      /**
     * @brief Heurestic cost checking radius
     */
     float checking_radius_;
};
}  // namespace youibot_rrt
#endif  // INCLUDE_YOUIBOT_RRT_YOUIBOT_RRT_H_
