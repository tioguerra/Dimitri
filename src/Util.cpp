#include "Util.h"
#include "Dimitri.h"

void createPose(float (&pose)[13],
                float lroll, float lpitch, float lyaw, float lelbow,
                float rroll, float rpitch, float ryaw, float relbow,
                float wroll, float wpitch, float wyaw,
                float hpan, float htilt)
{
  pose[RELBOW] = relbow;
  pose[RYAW] = ryaw;
  pose[RROLL] = rroll;
  pose[RPITCH] = rpitch;
  pose[LELBOW] = lelbow;
  pose[LYAW] = lyaw;
  pose[LROLL] = lroll;
  pose[LPITCH] = lpitch;
  pose[HTILT] = htilt;
  pose[HPAN] = hpan;
  pose[WYAW] = wyaw;
  pose[WROLL] = wroll;
  pose[WPITCH] = wpitch;
}

void createPoseDeg(float (&pose)[13],
                   float lroll, float lpitch, float lyaw, float lelbow,
                   float rroll, float rpitch, float ryaw, float relbow,
                   float wroll, float wpitch, float wyaw,
                   float hpan, float htilt)
{
  pose[RELBOW] = DEG2RAD(relbow);
  pose[RYAW] = DEG2RAD(ryaw);
  pose[RROLL] = DEG2RAD(rroll);
  pose[RPITCH] = DEG2RAD(rpitch);
  pose[LELBOW] = DEG2RAD(lelbow);
  pose[LYAW] = DEG2RAD(lyaw);
  pose[LROLL] = DEG2RAD(lroll);
  pose[LPITCH] = DEG2RAD(lpitch);
  pose[HTILT] = DEG2RAD(htilt);
  pose[HPAN] = DEG2RAD(hpan);
  pose[WYAW] = DEG2RAD(wyaw);
  pose[WROLL] = DEG2RAD(wroll);
  pose[WPITCH] = DEG2RAD(wpitch);
}

