/** 
TESTS/subsystem/PressureVacuumCircuit/main.cpp
M Descour, 2019

USNA WRCE honors capstone project open loop control code for a 
soft robotic pneumatic bending actuator to simulate leech-like
inchworm crawling.

Additions and refactored for Github repository D Evangelista and L DeVries.
*/

// The final code used to produce locomotion. Allows control of both suction ends as well as inflation/deflation of the actuator

#include "mbed.h"
Serial pc(USBTX, USBRX);
DigitalOut myled(LED1);
DigitalOut inletValve(p16);
PwmOut Pump(p22);
PwmOut Vacuum2(p23);
PwmOut Vacuum(p21);
DigitalOut outletValve(p17);
DigitalOut VacuumValve(p19);
AnalogIn psense(p20);
float sensorval = psense;
int yes = 0;


int main() {
 pc.printf("1: Vacuum ON 2: Vacuum OFF \n3: Vacuum 2 ON 4:Vacuum2 OFF \n5:Inflation 6:Deflation \n7:Pump Up 8:Pump Down \n 9:Pump STOP\n");    //prints instructions
 Vacuum = 1.0;
 Vacuum2 = 0.0;
 Pump = 0.20;

    while(1){
    float isVacuum = Vacuum;    //able to print value of Vacuum
    float isVacuum2 = Vacuum2;    //able to print value of Vacuum
    float isPump = Pump;    //able to print value of pump
    sensorval=psense;
    pc.printf("Vacuum: %f\n",isVacuum); //prints value of Vacuum
    pc.printf("Vacuum2: %f\n",isVacuum2); //prints value of Vacuum
    pc.printf("Pump: %f\n",isPump); //prints value of pump
    pc.printf("Pressure Sensor: %f\n",sensorval);
    pc.scanf("%d",&yes); //reads a number 0-4
    wait(0.1)   ;    

    if (yes == 1) { //if 1 is pressed, Vaccum1 On
        Vacuum = 1.0;
        }
    if (yes ==2) { //if 2 is pressed, Vacuum1 OFF
        Vacuum = 0.0;
        }
    if (yes == 3) { //if 3 is pressed, Vacuum2 ON
        Vacuum2 = 1.0;
        }
    if (yes ==4) { //if 4 is pressed, Vacuum2 OFF
        Vacuum2 = 0.0;
        }
    if (yes==5){ //if 5 is pressed, allows for inflation of actuator
        myled = 1;
        inletValve = 1;
        outletValve = 0;
        pc.printf("INFLATE \n");
        }
    if (yes ==6) { //if 6 is pressed, allows for deflation of actuator
        myled = 0;
        inletValve = 0;
        outletValve = 1;
        pc.printf("DEFLATE \n");
        }
    if (yes ==7) { //if 7 is pressed, increases pump by .025
        Pump = Pump + 0.025;
        }
    if (yes ==8) { //if 8 is pressed, decreases pump by .025
        Pump = Pump - 0.025;
        }
    if (yes ==9) { //if 9 is pressed, Pump = 0.0
        Pump = 0.0;
        }
    if (yes ==0) { //if 0 is pressed, Pump = 0.1
        Pump = 0.35;
        }    
        }
}
  
