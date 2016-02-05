#ifndef _GLOBALPLANNERWO_H
#define _GLOBALPLANNERWO_H

/********************************************************************
 * Copyright [2015] <Bonn-Rhein-Sieg University>
 * Author: Torsten Jandt
 *         torsten.jandt@smail.inf.h-brs.de
 *********************************************************************/

#include <global_planner/planner_core.h>

namespace mcr_global_planner
{
class GlobalPlannerWO : public global_planner::GlobalPlanner
{
    private:
        // Minimun distance between two poses.
        double pose_distance_;
        // Maximum amount of poses that should be driven in onmi mode only
        int omni_poses_;
        // Publisher used to publish the pose-array
        ros::Publisher pub_plan;
        bool initialized;

        /*
         * Filters the plan by removing poses and adds orientations to remaining ones.
         */
        void filterPlan(const geometry_msgs::PoseStamped &start, const geometry_msgs::PoseStamped &goal,
                        std::vector< geometry_msgs::PoseStamped > &plan);
        /*
         * Initialization for this wrapper class.
         */
        void initializeThis(std::string name, costmap_2d::Costmap2D *costmap, std::string frame_id);

        /*
         * Used to publish the plan with orientations as PoseArray
         */
        void publishVisualPlan(const geometry_msgs::PoseStamped &start, const geometry_msgs::PoseStamped &goal,
                               std::vector< geometry_msgs::PoseStamped > &plan);

        /*
         * Calculates the distance between two poses.
         */
        double calcDistance(const geometry_msgs::Pose &pose1, const geometry_msgs::Pose &pose2);
        double calcDistance(const geometry_msgs::PoseStamped &pose1, const geometry_msgs::PoseStamped &pose2);

        /*
         * Calculates the rotation from pose to another
         */
        double calcRotation(const geometry_msgs::Pose &from, const geometry_msgs::Pose &to);
        double calcRotation(const geometry_msgs::PoseStamped &from, const geometry_msgs::PoseStamped &to);

        /*
         * Calculates the rotation using the right rotation direction with precalced values.
         */
        double calcOmniRotation(const double from, const double way1, const double way2, const double weight);

        /*
         * Calculates the rotation using the right rotation direction.
         */
        double calcOmniRotation(const double from, const double to, const double weight);

        /*
         * mod like helper method
         */
        double modlike(double number, double limit);

    public:
        GlobalPlannerWO();
        GlobalPlannerWO(std::string name, costmap_2d::Costmap2D *costmap, std::string frame_id);

        void initialize(std::string name, costmap_2d::Costmap2DROS *costmap_ros);
        void initialize(std::string name, costmap_2d::Costmap2D *costmap, std::string frame_id);

        bool makePlan(const geometry_msgs::PoseStamped &start, const geometry_msgs::PoseStamped &goal,
                      std::vector< geometry_msgs::PoseStamped > &plan);
        bool makePlan(const geometry_msgs::PoseStamped &start, const geometry_msgs::PoseStamped &goal, double tolerance,
                      std::vector< geometry_msgs::PoseStamped > &plan);
};
}

#endif


