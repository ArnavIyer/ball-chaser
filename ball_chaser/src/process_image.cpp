#include "ros/ros.h"
#include "ball_chaser/DriveToTarget.h"
#include <sensor_msgs/Image.h>

class ImgProc {
    public:
        ImgProc() {
            camera_watch = n.subscribe("/camera/rgb/image_raw", 10, &ImgProc::process_img, this);
            request_move = n.serviceClient<ball_chaser::DriveToTarget>("/ball_chaser/command_robot/");
        }
        void moveBot(float a, float b) {
            ball_chaser::DriveToTarget srv;
            srv.request.linear_x = a;
            srv.request.angular_z = b;
            request_move.call(srv);
        }
        void process_img(const sensor_msgs::Image img) {
            int index = -1;
            for (int i = 0; i<img.data.size(); i+=3) {
                if (img.data[i]==255 && img.data[i+1]==255 && img.data[i+2]==255) {
                    index = i;
                    break;
                }
            }
            if (index != -1) index = (index% (img.width*3))/3;
            if (index == -1) {
                moveBot(0.0,0.0);
            } else if (index < img.width /3) {
                moveBot(0.0,0.5);
            } else if (index < img.width * 2/3) {
                moveBot(0.5,0.0);
            } else {
                moveBot(0.0, -0.5);
            }
        }
    private:
        ros::NodeHandle n;
        ros::Subscriber camera_watch;
        ros::ServiceClient request_move;
};

int main(int argc, char** argv) {
    ros::init(argc, argv, "process_image");
    ImgProc obj;
    ROS_INFO("ready to process images");
    ros::spin();
    return 0;
}