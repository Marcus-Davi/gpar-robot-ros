#include "ros/ros.h"
#include <sstream>
#include "std_msgs/String.h"
#include "serial/serial.h"
#include "geometry_msgs/Twist.h"
#include "driver_HDC2450.h"


void Velocidade_motor_rpm(const geometry_msgs::Twist::ConstPtr& velocidade);

//Variáveis Globais
const float PI = 3.141592654;
float L = 0.5; // distância entre as rodas
float R = 0.02; // raio das rodas
float vd_rad;
float ve_rad;
int vd_rpm = 0; // velocidade da roda direita em rpm
int ve_rpm = 0; // velocidade da roda esquerda em rpm

std::string porta = "/dev/ttyACM0";


int main(int argc, char **argv)
{
	Driver HULK;

	ros::init(argc,argv,"hulk_node");
	ros::NodeHandle n;

	ros::Subscriber sub = n.subscribe("velocidade_hulk",1000,Velocidade_motor_rpm);

	HULK.serial_verify(porta);

	ros::Rate freq(10);

	while(ros::ok()){
	
	HULK.set_speed(vd_rpm,ve_rpm);
	
	ros::spinOnce();
	freq.sleep();
	}

return 0;
}

//Realizando o cáculo das velocidades de cada motor em rpm
void Velocidade_motor_rpm(const geometry_msgs::Twist::ConstPtr& velocidade){
	float v = velocidade->linear.x;
	float w = velocidade->angular.z;
	
	
	vd_rad = (v+w*L);
        ve_rad = (v-w*L);

	vd_rpm = (vd_rad*60/(2*PI*R));
	ve_rpm = (ve_rad*60/(2*PI*R));
	
}

	
	
	


