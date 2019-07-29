1. This project, named Rapidly-exploring Random Tree Star(RRT*) global planner, is used for AGV navigation.

2. There are four parameters, which users could configure to adjust the performence of the RRT* global planner.
 2.1 "step_size" default="2": this parameter defines the step size from the ClosetTreeNode to the RandomNode for generating the TempNewTreeNode. This should be configured according to the size of the map.
 2.2 "delta" default="0.5": this parameter defines the incremental step size that divides the interval between the ClosetTreeNode and the TempNewTreeNode for collision checking.
 2.3 "max_iterations" default="200000": this defines the maximum iterations times the algorithm tries to find a feasible path. If the algorithm tries over the "max iterations" times and does not find a path, the algoritm would return false.
 2.4 "goal_radius" default="0.8": defines a goal tolerance for path searching.
 2.5 "checking_radius" default="4": defines the radius that TempNewTreeNode uses to find its neighbor nodes.
