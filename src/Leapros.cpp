#include<iostream>
#include<algorithm>
#include"Leapros.h"

void RosListener::onInit(const Leap::Controller& controller){
    std::cout << "Initialized" <<std::endl;
    vel_pub = nh_.advertise<geometry_msgs::Twist>("/cmd_vel",1);
    teleop_.linear.x = 0;
    teleop_.linear.y = 0;
    teleop_.linear.z = 0;
    teleop_.angular.x = 0;
    teleop_.angular.y = 0;
    teleop_.angular.z = 0;
}

void RosListener::onConnect(const Leap::Controller& controller){
    std::cout<< "Connected" <<std::endl;
    controller.enableGesture(Leap::Gesture::TYPE_CIRCLE);
    controller.enableGesture(Leap::Gesture::TYPE_SWIPE);
    controller.enableGesture(Leap::Gesture::TYPE_KEY_TAP);
    controller.enableGesture(Leap::Gesture::TYPE_SCREEN_TAP);
}

void RosListener::onDisconnect(const Leap::Controller& controller){
    std::cout<< "Disconnected" <<std::endl;
}

void RosListener::onExit(const Leap::Controller& controller){
    std::cout<< "Exited" <<std::endl;
}

void RosListener::onFrame(const Leap::Controller& controller){
    const Leap::Frame frame = controller.frame();

  //  std::cout<<"tools: "<<frame.tools().count()<<std::endl;
    //std::cout<<"hands:"<<frame.hands().count()<<std::endl;
    //std::cout<<"fingers:"<<frame.fingers().count()<<std::endl;

    const Leap::ToolList tools= frame.tools();
    const Leap::Tool tool = *tools.begin();
    const Leap::HandList hands=frame.hands();
    const Leap::Hand hand=*hands.begin();
    const Leap::Vector normal = hand.palmNormal();
    const Leap::Vector direction = hand.direction();
  //  const Leap::Hand hand=*hand.begin();
    //const Leap::GestureList gestures=frame.gestures();

//    std::cout<<hand.id()<<std::endl;
  //  std::cout<<hand.palmPosition()<<std::endl;
  //  std::cout<<hand.direction()<<std::endl;
//    std::cout<<hand.sphereRadius()<<std::endl;
  //  std::cout<<"pitch:"<<direction.pitch()<<std::endl;
    //std::cout<<"roll:"<<normal.roll()<<std::endl;
    //std::cout<<"yaw:"<<direction.yaw()<<std::endl;


    if (hand.id() != -1){
        std::cout<<"Hand, id: "<< hand.id() <<std::endl;
      //  std::cout<<"Tool position: "<<tool.tipPosition()
        //     <<", direction: "<<tool.direction()[0] << std::endl;
        float sphereRadius = hand.sphereRadius();
        float x_speed=0.025*sphereRadius-1.75;
  //      float y_speed = hand.direction()[2];
        float z_rspeed = direction.yaw();
        //float sphere = hand.sphereRadius();

        //std::cout<<x_speed<<std::endl;
        //std::cout<<z_rspeed<<std::endl;
        //std::cout<<"hand's sphere is"<<sphere<<std::endl;

        // linear speed
        if (sphereRadius > 80){teleop_.linear.x = x_speed;}
        else if (sphereRadius < 60){teleop_.linear.x = x_speed;}
        else{teleop_.linear.x = 0;}


        //angular speed
        if (z_rspeed > 0.25 || z_rspeed < -0.25){teleop_.angular.z = z_rspeed;}
        else{teleop_.angular.z = 0;}

        vel_pub.publish(teleop_);

    }
    else{
        teleop_.linear.x = 0;
        teleop_.angular.z = 0;
        vel_pub.publish(teleop_);
    }
}
