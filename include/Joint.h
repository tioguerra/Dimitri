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

  public:

    Joint(int jointId, int jointCenterValue);
    virtual ~Joint();

    // Returns last read angle of the joint
    float getAngle();
    // Returns last read angle normalized to
    // have a value between 0 and 1
    float getNormalizedAngle();

    // Sets the angle limits
    // (affects normalization range)
    void setMaxAngle(float angle);
    float getMaxAngle();
    void setMinAngle(float angle);
    float getMinAngle();
    void setAngleLimits(float minAngle, float maxAngle);

    // Define maximum torque to the motors
    // (number between 0 and 1023)
    void setMaxTorque(int torque);
    int getMaxTorque();

    // Sets the control mode
    // (see enum ControlMode above)
    void setControlMode(int mode);

    // Sets the goal angle
    void setGoalAngle(float angle);
    float getGoalAngle();
    // Sets the goal angle in normalized
    // form (number between 0 and 1)
    void setNormalizedGoalAngle(float angle);
    float getNormalizedGoalAngle();

    // Convenience function to transform
    // angle from radians to normalized
    // form
    float normalizeAngle(float angle);

    // Calibration of the center value of
    // the joint
    void setJointCenterValue(float value) { this->jointCenterValue = value; }
    int getJointCenterValue() { return this->jointCenterValue; }

    // This has to called once every cycle
    // to update angle readings and
    // angle goals
    virtual void update();

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

};

#endif
