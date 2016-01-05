#ifndef DIMITRI_H
#define DIMITRI_H

#include "JointChain.h"

class Dimitri
{

  private:

    JointChain *leftArm;
    JointChain *rightArm;
    JointChain *head;
    JointChain *waist;
    
  public:

    /*
     * This constructor will initialize the Dimitri object
     * opening /dev/ttyUSBx, where x is the deviceIndex.
     * The baudrate is defined by baudNum. Use baudNum 16
     * for 115200bps.
     */
    Dimitri(int deviceIndex, int baudNum);

    ~Dimitri();

    JointChain *getLeftArm() { return leftArm; }
    JointChain *getRightArm() { return rightArm; }
    JointChain *getHead() { return head; }
    JointChain *getWaist() { return waist; }

    /* 
     * This method will subsequently call the update methods
     * of the JointChains (arms, head and waist), and these
     * in turn will update the joints themselves.
     *
     * Remember to call this method in the main loop.
     */
    void update();

    /*
     * This method enables or disables torque to the motors
     */
    void setControlMode(int mode);

    /*
     * This method sets the maximum torque to all motors
     */
    void setMaxTorque(int torque);
};

#endif 
