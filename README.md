# Ball Chasing Robot

![screenshot](https://user-images.githubusercontent.com/40965890/96025436-c0b5a380-0e1a-11eb-8e82-25951481f3f7.png)

## Description

This project is a virtual robot that finds and moves toward a white ball.

## Dependencies

  - ROS Melodic
  - Gazebo
  - C++
  
## Launching The Project

First, create a catkin workspace and a src folder to house the project.
```
$ mkdir -p catkin_ws/src
$ cd catkin_ws/src
$ catkin_init_workspace
```

Next, put the ```my_robot``` and ```ball_chaser``` directories into the src folder. After this, go to the catkin_ws directory and build the project
```
$ catkin_make
```

To launch the project, first launch the Gazebo world.
```
$ source devel/setup.bash
$ roslaunch my_robot world.launch
```

In a new terminal, launch the ball chaser node.
```
$ source devel/setup.bash
$ roslaunch ball_chaser ball_chaser.launch

Finally, go to Gazebo, move the white ball around, and watch the robot move toward it.
