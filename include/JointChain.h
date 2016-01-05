#ifndef JOINTCHAIN_H
#define JOINTCHAIN_H

#include "Joint.h"
#include "ElasticJoint.h"

#define MAX_JOINTS_IN_JOINTCHAIN 16

typedef enum {
    ELBOW,
    ARMYAW,
    ARMROLL,
    ARMPITCH,
} ArmJoints;

typedef enum {
    WAISTYAW,
    WAISTROLL,
    WAISTPITCH,
} WaistJoints;

typedef enum {
    TILT,
    PAN,
} HeadJoints;

class JointChain
{

  private:

    Joint *joints[MAX_JOINTS_IN_JOINTCHAIN];
    int totalJoints;

  public:

    JointChain();

    virtual ~JointChain();

    /*
     * This method enables or disables torque to the motors
     */
    void setControlMode(int mode);

    /*
     * Sets the maximum torque for the joints
     */
    void setMaxTorque(int torque);

    /*
     * This method adds a Joint object to the chain
     */
    void addJoint(Joint *joint);

    /*
     * This method returns a joint object from the chain
     */
    Joint *getJoint(int jointIndex) {return joints[jointIndex];}

    /*
     * This method returns the count of joints in the chain
     */
    int getTotalJoints() { return totalJoints; }

    void update();

};

#endif
