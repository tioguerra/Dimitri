#ifndef PIDCONTROLLER_H
#define PIDCONTROLLER_H

class PidController
{
  private:
    float sum;
    float difference;
    float last_reading;

  public:

    PidController(float pGain, float iGain, float dGain);
    ~PidController();
    float pGain;
    float iGain;
    float dGain;
    float update(float reading, float goal);
    void reset();

};

#endif
