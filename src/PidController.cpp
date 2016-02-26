#include "PidController.h"

PidController::PidController(float pGain,float iGain,float dGain)
{
  this->pGain = pGain;
  this->iGain = iGain;
  this->dGain = dGain;
  this->reset();
}

PidController::~PidController()
{
}

void PidController::reset()
{
  this->sum = 0.0;
  this->difference = 0.0;
  this->last_error = 0.0;
}

float PidController::update(float reading, float goal)
{
  // Computes current error
  float error = goal - reading;

  // Proportional term
  float p = this->pGain * error;

  // Integral term
  this->sum += error;
  float i = this->iGain * this->sum;

  // Differential term
  this->difference = error - this->last_error;
  this->last_error = error;
  float d = this->dGain * this->difference;

  return p + i + d;
}

