// Code to inflate/deflate the actuator. User may also increase/decrease PWM

#include "mbed.h"
Serial pc(USBTX, USBRX);
DigitalOut myled(LED1);
DigitalOut inletValve(p16);
PwmOut Pump(p22);
DigitalOut outletValve(p17);
AnalogIn psense(p20);
float sensorval = psense;
int yes = 0;


int main() {
 pc.printf("1:Open valves for inflation\n 3:Increase Inflation Rate\n 4:Decrease Inflation Rate\n 0:Deflate \n");    //prints instructions
    while(1){
    float isPump = Pump;    //able to print value of pump
    pc.printf("%f\n",isPump); //prints value of pump
    pc.printf("%f\n",sensorval);
    sensorval=psense;
    pc.scanf("%d",&yes); //reads a number 0-4
    wait(0.1)   ;    

    if (yes==1){ //if 1 is pressed, allows for inflation of actuator
        myled = 1;
        inletValve = 1;
        outletValve = 0;
        pc.printf("INFLATE \n");
        }
    if (yes ==0) { //if 0 is pressed, allows for deflation of actuator
        myled = 0;
        inletValve = 0;
        outletValve = 1;
        pc.printf("DEFLATE \n");
        }
    if (yes ==3) { //if 3 is pressed, increases pump by .025
        Pump = Pump + 0.025;
        }
    if (yes ==4) { //if 4 is pressed, decreases pump by .025
        Pump = Pump - 0.025;
        }
    
        }
}
