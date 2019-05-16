/** 
TESTS/integrated/LocomotionNoUser/main.cpp
M Descour, 2019

USNA WRCE honors capstone project open loop control code for a 
soft robotic pneumatic bending actuator to simulate leech-like
inchworm crawling.

Additions and refactored for Github repository D Evangelista and L DeVries.
*/

// An attempt at programmed locomotion without user input.

#include "mbed.h"
Serial pc(USBTX, USBRX);
DigitalOut myled(LED1);
DigitalOut inletValve(p16);
PwmOut Pump(p22);
PwmOut Vacuum2(p23);
PwmOut Vacuum(p21);
DigitalOut outletValve(p17);
DigitalOut VacuumValve(p18);
DigitalOut VacuumValve2(p19);
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
      if (yes==7){ //if 5 is pressed, allows for inflation of actuator
        myled = 1;
        inletValve = 1;
        outletValve = 0;
        pc.printf("INFLATE \n");
        }
    if (yes ==8) { //if 6 is pressed, allows for deflation of actuator
        myled = 0;
        inletValve = 0;
        outletValve = 1;
        pc.printf("DEFLATE \n");
        } 

    if (yes == 1) { //if 1 is pressed, Vaccum1 On
        while(1){
        Vacuum2 = 1.0;
        VacuumValve2 = 0;
        Pump = 0.225;
        Vacuum = 0.0;
        VacuumValve = 1;
        wait(3);
        Pump = 0.55;
        wait(3);
        Vacuum = 1.0;
        VacuumValve = 0;
        wait(0.5);
        Pump = .25;
        Vacuum2 = 0.0;
        VacuumValve2 = 1;
        }
        
        }
}
  }
