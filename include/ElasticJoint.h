#ifndef ELASTICJOINT_H
#define ELASTICJOINT_H

#include "Joint.h"
#include "PidController.h"

#define KP 32
#define KI 0
#define KD 0

#define SPRING_CONSTANT 32.0
#define SPRINGANGLE2VALUE(x) ((x)*4096.0/M_PI)
#define SPRINGVALUE2ANGLE(x) ((x)*M_PI/4096.0)
#define SPRINGANGLE2TORQUE(x) (SPRING_CONSTANT*(x))
#define SPRINGTORQUE2ANGLE(x) ((x)/SPRING_CONSTANT)

class ElasticJoint : public Joint
{

  private:

    int springId;
    int springCenterValue;
    float torque;
    float goalTorque;
    PidController *pidController;

  public:

    ElasticJoint(int jointId, int springId, int jointCenterValue, int springCenterValue);
    ~ElasticJoint();

    float getTorque();

    void setGoalTorque(float torque);
    float getGoalTorque();

    void setSpringCenterValue(int value) { this->springCenterValue = value; }
    int getSpringCenterValue() { return springCenterValue; }

    virtual void update();

};

#endif
