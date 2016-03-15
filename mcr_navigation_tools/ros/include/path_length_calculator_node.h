/*
 * Copyright [2016] <Bonn-Rhein-Sieg University>
 *
 * Author: Oscar Lima (olima_84@yahoo.com)
 * 
 * Listens to nav_msgs Path topic (which contains a global plan for the mobile base) as an array  
 * of poses and calculates the path lenght based on the distance between two points of each pose.
 * 
 */

#ifndef PATH_LENGTH_CALCULATOR_NODE_H
#define PATH_LENGTH_CALCULATOR_NODE_H

#include <ros/ros.h>
#include <ros/rate.h>
#include <nav_msgs/Path.h>
#include <std_msgs/Float64.h>
#include <std_msgs/String.h>
#include <mcr_navigation_tools/path_length_calculator.h>

class PathLengthCalcNode
{
    public:
        PathLengthCalcNode();
        ~PathLengthCalcNode();

        // variable initialization function
        void init();

        // get parameters from param server
        void getParams();

        // ros node main loop
        void update();

        // callback for event_in msg
        void eventInCallback(const std_msgs::String::ConstPtr& msg);

        // callback to receive navigation path msg
        void globalPlanCallback(const nav_msgs::Path::ConstPtr& msg);

    private:
        // flag used to know when we have received a callback
        bool callback_received_;

        // frequency at which the node will run
        double node_frequency_;

        // ros related variables
        ros::NodeHandle nh_;
        ros::Publisher pub_event_out_;
        ros::Publisher path_length_pub_;
        ros::Subscriber sub_event_in_;
        ros::Subscriber global_plan_sub_;

        // for receiving event in msg
        std_msgs::String event_in_msg_;

        // generic class that receives a path msg and returns path length
        PathLengthCalculator path_length_calculator_;

        // stores the path received in the callback
        nav_msgs::Path global_plan_;

        // flag to indicate that path msg was received from ros network
        bool global_plan_is_available_;
};
#endif  // PATH_LENGTH_CALCULATOR_NODE_H
