#ifndef JOINT_H
#define JOINT_H

#include "Util.h"
#include <cmath>

#define OFFSET 4096.0
#define ANGLE2VALUE(x) ((x)*2048.0/M_PI + OFFSET)
#define VALUE2ANGLE(x) (((x) - OFFSET)*M_PI/2048.0)

#define ANGLE_TEACH_THRESHOLD DEG2RAD(5.0)
#define TORQUE_TEACH_THRESHOLD DEG2RAD(25.0)

typedef enum
{
  ANGLE,  // Use this mode for position control
  TORQUE, // Use this mode for torque control
  OFF,    // Use this mode to turn off the torque
  TEACH,  // Use this mode to teach poses to the robot
} ControlMode;

class Joint
{

  protected:

    float angle;
    float motorAngle;
    int controlMode;
    int jointId;
    bool isElastic;
    float goalAngle;
    float maxAngle;
    float minAngle;
    float maxTorque;
    int jointCenterValue;
    void readMotorAngle();
    virtual void readAngle();
    void writeGoalAngle(float angle);

  public:

    Joint(int jointId, int jointCenterValue);
    virtual ~Joint();

    float getAngle();
    float getNormalizedAngle();

    void setMaxAngle(float angle);
    float getMaxAngle();
    void setMinAngle(float angle);
    float getMinAngle();
    void setAngleLimits(float minAngle, float maxAngle);
    void setMaxTorque(int torque);
    int getMaxTorque();

    void setControlMode(int mode);
    void setGoalAngle(float angle);
    void setNormalizedGoalAngle(float angle);
    float getGoalAngle();
    float getNormalizedGoalAngle();

    void setJointCenterValue(float value) { this->jointCenterValue = value; }
    int getJointCenterValue() { return this->jointCenterValue; }

    virtual void update();

};

#endif
