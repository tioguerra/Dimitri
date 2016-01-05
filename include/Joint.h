#ifndef JOINT_H
#define JOINT_H

#include <cmath>

#define OFFSET 4096.0
#define ANGLE2VALUE(x) ((x)*2048.0/M_PI + OFFSET)
#define VALUE2ANGLE(x) (((x) - OFFSET)*M_PI/2048.0)

typedef enum
{
  ANGLE,
  TORQUE,
  OFF
} ControlMode;

class Joint
{

  protected:

    float angle;
    int controlMode;
    int jointId;
    bool isElastic;
    float goalAngle;
    float maxAngle;
    float minAngle;
    float maxTorque;
    int jointCenterValue;

  public:

    Joint(int jointId, int jointCenterValue);
    virtual ~Joint();

    float getAngle();

    void setMaxAngle(float angle);
    float getMaxAngle();
    void setMinAngle(float angle);
    float getMinAngle();
    void setMaxTorque(int torque);
    int getMaxTorque();

    void setControlMode(int mode);
    void setGoalAngle(float angle);
    float getGoalAngle();

    void setJointCenterValue(float value) { this->jointCenterValue = value; }
    int getJointCenterValue() { return this->jointCenterValue; }

    virtual void update();

};

#endif
