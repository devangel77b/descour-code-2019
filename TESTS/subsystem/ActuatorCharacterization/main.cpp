/** 
TESTS/subsystem/ActuatorCharacterization/main.cpp
M Descour, 2019

USNA WRCE honors capstone project open loop control code for a 
soft robotic pneumatic bending actuator to simulate leech-like
inchworm crawling.

Additions and refactored for Github repository D Evangelista and L DeVries.
*/

//Code used for Actuator Characterization. Records data for 20 seconds. Inflation begins at 5 seconds and lasts for 10 seconds.

#include "mbed.h"
Serial pc(USBTX, USBRX);
DigitalOut myled(LED1);
DigitalOut inletValve(p16);
PwmOut Pump(p22);
DigitalOut outletValve(p17);
AnalogIn psense(p20);
float sensorval;
int yes = 0;
float isPump = 0;    //able to print value of pump
int isinletValve;
float voltage_mv;
float voltage_v;
float ref_mv = 5.0*1000.0;
float Pmax = 5.0;
float Pmin = 0.0;
float Pout;
float t = 0.0;
float dt = 0.01;
int controlFlag = 4;
Ticker timer;
////////////////////////////////////////////////////////////////////////////////
// Function for getting output Pressure
////////////////////////////////////////////////////////////////////////////////
void getPout()
{
    sensorval = psense;
    voltage_mv = (sensorval * ref_mv);
    voltage_v = voltage_mv / 1000.0;
    Pout = ( ( (voltage_v - (0.10 * (ref_mv/1000.0) )) * (Pmax - Pmin) ) / (0.8 * (ref_mv/1000.0) ) ) + Pmin;
    
    if(controlFlag == 0) {
        Pump=.185;
        inletValve = 0;
        outletValve = 0;
        }
    else if(controlFlag == 1) {
        Pump=.185;
        inletValve = 1;
        outletValve = 0;
        }
    else if(controlFlag == 2) {
        Pump=0.0;
        inletValve = 0;
        outletValve = 0;   
    }
     t = t + dt; //time
     isPump = Pump;
     isinletValve = inletValve;
}
////////////////////////////////////////////////////////////////////////////////
// Main
////////////////////////////////////////////////////////////////////////////////
int main() {
    pc.baud(115200);
    pc.format(8,SerialBase::Even,1);
    timer.attach(&getPout,dt);  //attach ticker
    float runTime;
    while(1) {
        pc.scanf("%f",&runTime);  //scan in desired turn angle
        t = 0.0;
        controlFlag = 0;
        while(t <= runTime) {  //stops turret when desired position is reached
            pc.printf("%f,%f,%f,%d\n",t,Pout,isPump,isinletValve);
            if (t >= 5.0){
                controlFlag = 1;
                }
            if (t >= 15.0){
                controlFlag = 2;
                }    
            
            wait(0.0333);
        }
      
        controlFlag = 4;
        Pump = 0.0;
    }
}
            
     
