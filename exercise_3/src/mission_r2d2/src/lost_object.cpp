#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <tf/transform_listener.h>
#include <gazebo_msgs/SetModelState.h>
#include <std_msgs/Bool.h>



//Class defining clients of supermarket
class lost_object{

    //Node
    ros::NodeHandle nh_;

    //Timer that will run the main code
    ros::Timer timer_place_object_;

    //TF things
    tf::TransformBroadcaster br_;
    tf::Transform transform_;
    tf::Quaternion q_;

    //Service for moving the lost object
    ros::ServiceClient move_object_client_ = nh_.serviceClient<...>(...,true);
    gazebo_msgs::SetModelState move_object_srv_;

    //Subscriber of pickup alert
    ... 
    
    //Location of object
    float x_, y_, z_;

    //Object name
    std::string object_name_;

public:

    //Constructor
    lost_object(float x, float y)
    {
        //Copy desired location to member variables
        x_ = ... 
        y_ = ... 
        z_ = 0.0;

        // Initialize pickup flag to false
        pickup_flag_ = false;

        //Give a name to the object (for compatibility with the ROS network MUST be lost_object)
        object_name_ = "lost_object";

        //Pick up alert subscriber
        pickup_sub = nh_.subscribe(..., ..., &lost_object::PickUpAlertCallback, this);

        //Start timer running at 100Hz
        timer_place_object_ = nh_.createTimer(ros::Duration(0.01), &lost_object::lost_object_loop, this);
    }

    //Loop that runs at 100Hz (this is where the algorithm is located)
    void lost_object_loop(const ros::TimerEvent& t){

        // If object has been picked up, redefine location of object
        if (pickup_flag_ == true){get_tf_pose(x_, y_, "/odom", "/base_link");}

        //Broadcast tf of object
        broadcast_tf();

        //Move object in gazebo
        move_gazebo_object_location();
    }

    //Broadcast tf
    void broadcast_tf()
    {
        //Define transform pose (position and orientation)
        transform_. ...

        //Broadcast tf
        br_.sendTransform(tf::StampedTransform(..., ..., "/odom", ...));
    }

    //Move lost object in Gazebo
    void move_gazebo_object_location()
    {

        //Modify ros service message
        move_object_srv_.request.model_state.model_name = object_name_;

        //specify position
        move_object_srv_.request.model_state.pose. ... = x_;
        move_object_srv_.request.model_state.pose. ... = y_;
        move_object_srv_.request.model_state.pose. ... = z_;

        //specify orientation
        tf::Quaternion quat;
        quat.setRPY(0,0,atan2(y_,x_));
        move_object_srv_.request.model_state.pose. ... = quat.x();
        move_object_srv_.request.model_state.pose. ... = quat.y();
        move_object_srv_.request.model_state.pose. ... = quat.z();
        move_object_srv_.request.model_state.pose. ... = quat.w();

        //Call rosservice (equivalent to publish)
        move_object_client_. ...;
    }

    //Callback function for pickup alert topic
    void PickUpAlertCallback(const std_msgs::Bool& msg)
    {
        if (...){pickup_flag_ = true;}
    }

    //Return coordinates of a frame respective to another 
    //Help: we send them as references, hence x and y member variables will be modified inside the function
    void get_tf_pose(   float& x, float& y,
                        const std::string frame1, const std::string frame2)
    {
        tf::TransformListener listener;
        tf::StampedTransform transform;
        bool transform_exception = 1;
        while (transform_exception)
        {
            try
            {
                listener. ...
                transform_exception = 0;
            }
            catch(tf::TransformException ex)
            {
                transform_exception = 1;
                continue;
            }
        }

        x = transform. ...
        y = transform. ...
    }

};

//Main function
int main(int argc, char **argv)
{
        // initialize node
        ros::init(argc, argv, "lost_object");
        ros::NodeHandle nh("~");

        double x_pos, y_pos;
        nh.param("x0", x_pos, 5.0);
        nh.param("y0", y_pos, 5.0);

        //initialize class
        lost_object lost_object(x_pos, y_pos);

        //Allow the timer to be called
        ros::spin();
}
        
        
