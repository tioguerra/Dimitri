#ifndef UTIL_H
#define UTIL_H

#define RAD2DEG(x) ((x)*180.0/M_PI)
#define DEG2RAD(x) ((x)*M_PI/180.0)

void createPose(float (&pose)[13],
                float lroll, float lpitch, float lyaw, float lelbow,
                float rroll, float rpitch, float ryaw, float relbow,
                float wroll, float wpitch, float wyaw,
                float hpan, float htilt);

void createPoseDeg(float (&pose)[13],
                   float lroll, float lpitch, float lyaw, float lelbow,
                   float rroll, float rpitch, float ryaw, float relbow,
                   float wroll, float wpitch, float wyaw,
                   float hpan, float htilt);

#endif

