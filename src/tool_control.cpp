/*************************************************************************
	> File Name: tool_control.cpp
	> Author:
	> Mail:
	> Created Time: 
 ************************************************************************/

#include<iostream>
#include"Leapros.h"
#include"Leap.h"

int main(int argc, char **argv){

    ros::init(argc, argv, "leap_tool_control");
    RosListener listener;
    Leap::Controller controller;

    controller.addListener(listener);
    std::cout <<"Press Enter to quit..."<<std::endl;
    std::cin.get();
    controller.removeListener(listener);

}
