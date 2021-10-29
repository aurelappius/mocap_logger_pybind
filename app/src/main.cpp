#include "default_participant.h"
#include "default_subscriber.h"
#include "sub_callback.h"
#include <iostream>
#include <fstream>
#include <string.h>
#include <time.h>
#include <chrono>
#include <thread>
//std::thread thread_object(callable)

#include <pybind11/embed.h> // everything needed for embedding
namespace py = pybind11;

using std::chrono::milliseconds;
using std::chrono::seconds;
using std::this_thread::sleep_for;

void showplot(){
    //pybind11 initialization
    py::scoped_interpreter guard{}; // start the interpreter and keep it alive
    //py::module_ plotter = py::module_::import("plotter");
    py::eval_file("plotter.py");
}


int main() {

// Famocap_msgDDS objects
// Create participant. Arguments-> Domain id, QOS name
DefaultParticipant dp(0, "mocap_subscriber");

// Create publisher with msg type
DDSSubscriber mocap_sub(idl_msg::MocapPubSubType(), &sub::mocap_msg, "mocap_pose", dp.participant());


// Initalize mocap_publisher
mocap_sub.init();
//////////////////////////////////////////////////////////

//create fstream
auto timenow = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
std::string Date = ctime(&timenow);
std::replace( Date.begin(), Date.end(), ' ', '_');
Date.pop_back();
std::ofstream myLog;
std::ofstream pyTrans;
//std::string name="no_name";
//std::cout << "file name: ";
//std::cin >> name;
myLog.open ("log/Flight_"+Date+".csv");
pyTrans.open ("log/temp.csv");
//pyTrans<<"0,0,0,0,0,0,0\n";
//myfile << "Frame, Framerate, Latency, x, y, z, roll, pitch, yaw,\n";
std::cout << "Started logging to flight_" << Date << ".csv\n";

//start plotting thread
std::thread thread_obj(showplot);

//py::object result = plotter.attr("initialize")();
auto t_0 = std::chrono::duration_cast<milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
for(;;) {
    mocap_sub.listener->wait_for_data();
    //outstream to console
    auto t = std::chrono::duration_cast<milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count()-t_0;
    //std::cout<<"time since start: "<<t/1000.0<<std::endl;
    //std::cout << "Timestamp: " << sub::mocap_msg.header.timestamp << std::endl;
    // std::cout << "roll: " << sub::mocap_msg.pose.orientation_euler.roll << std::endl;
    // std::cout << "pitch: " << sub::mocap_msg.pose.orientation_euler.pitch << std::endl;
    // std::cout << "yaw: " << sub::mocap_msg.pose.orientation_euler.yaw << std::endl;
    // std::cout << "x: " << sub::mocap_msg.pose.position.x << std::endl;
    // std::cout << "y: " << sub::mocap_msg.pose.position.y << std::endl;
    // std::cout << "z: " << sub::mocap_msg.pose.position.z << std::endl;
    //outstream to file
    myLog << t << ",";
    myLog << sub::mocap_msg.pose.position.x << ",";
    myLog << sub::mocap_msg.pose.position.y << ",";
    myLog << sub::mocap_msg.pose.position.z << ",";
    myLog << sub::mocap_msg.pose.orientation_euler.roll << ",";
    myLog << sub::mocap_msg.pose.orientation_euler.pitch << ",";
    myLog << sub::mocap_msg.pose.orientation_euler.yaw << "\n";

    pyTrans << t << ",";
    pyTrans << sub::mocap_msg.pose.position.x << ",";
    pyTrans << sub::mocap_msg.pose.position.y << ",";
    pyTrans << sub::mocap_msg.pose.position.z << ",";
    pyTrans << sub::mocap_msg.pose.orientation_euler.roll << ",";
    pyTrans << sub::mocap_msg.pose.orientation_euler.pitch << ",";
    pyTrans << sub::mocap_msg.pose.orientation_euler.yaw << "\n";
    //std::cout<<timer.count()<<"\n";
    //py::object result = plotter.attr("add_data")(sub::mocap_msg.pose.position.x,sub::mocap_msg.pose.position.y,sub::mocap_msg.pose.position.z,sub::mocap_msg.pose.orientation_euler.roll,sub::mocap_msg.pose.orientation_euler.pitch,sub::mocap_msg.pose.orientation_euler.yaw,sub::mocap_msg.header.timestamp-t_zero);
    // if(i%10==0){
    //       py::object result = plotter.attr("show_plot")();
    // }
    //std::cout << std::endl;
}
}