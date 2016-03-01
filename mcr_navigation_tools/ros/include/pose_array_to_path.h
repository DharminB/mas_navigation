/*
 * Copyright [2016] <Bonn-Rhein-Sieg University>
 *
 * Author: Oscar Lima (olima_84@yahoo.com)
 * 
 * Subscribes to pose array topic, republishes as nav_msgs/Path topic
 * 
 */

#ifndef POSE_ARRAY_TO_PATH_H
#define POSE_ARRAY_TO_PATH_H

#include <ros/ros.h>
#include <nav_msgs/Path.h>
#include <geometry_msgs/PoseArray.h>
#include <geometry_msgs/PoseStamped.h>

class PoseArrayToPath
{
    public:
        PoseArrayToPath();
        ~PoseArrayToPath();

        // variable initialization function
        void init();

        // get parameters from param server
        void get_params();

        // callback to receive the pose array msg from ros network
        void poseArrayCallback(const geometry_msgs::PoseArray::ConstPtr& msg);
        
        // ros node main loop
        void main_loop();

    private:
        // flag used to know when we have received a callback
        bool callback_received_;

        // frequency at which the node will run
        double node_frequency_;

        // ros related variables
        ros::NodeHandle nh_;
        ros::Publisher path_pub_;
        ros::Subscriber pose_array_sub_;

        // stores pose array msg received from ros network
        geometry_msgs::PoseArray pose_array_msg_;
};
#endif  // POSE_ARRAY_TO_PATH_H
