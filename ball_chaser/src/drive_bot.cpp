#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "ball_chaser/DriveToTarget.h"

class PS {
    public:
        PS() {
            motor_pub = n.advertise<geometry_msgs::Twist>("/cmd_vel", 10);
            do_move = n.advertiseService("/ball_chaser/command_robot", &PS::handle_drive_request, this);
        }
        bool handle_drive_request(ball_chaser::DriveToTarget::Request &req, ball_chaser::DriveToTarget::Response &res) {
            ROS_INFO("DriveToTargetRequest received - linear_x:%1.2f, angular_z:%1.2f", (float)req.linear_x, (float)req.angular_z);
            geometry_msgs::Twist motor_cmd;
            motor_cmd.linear.x = req.linear_x;
            motor_cmd.angular.z = req.angular_z;
            
            motor_pub.publish(motor_cmd);
            res.msg_feedback = "Motor speeds set";
            ROS_INFO_STREAM(res.msg_feedback);
            return true;
        }
    private:
        ros::NodeHandle n;
        ros::Publisher motor_pub;
        ros::ServiceServer do_move;
};

int main(int argc, char** argv) {
    ros::init(argc, argv, "drive_bot");
    PS obj;
    ROS_INFO("ready to send motor commands");
    ros::spin();
    return 0;
}