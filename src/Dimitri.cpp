#include "Dimitri.h"
#include "dynamixel.h"
#include "Util.h"

// 1:4326,101:14273,2:4517,102:16048,3:5334,103:1867,4:8179,104:11073,5:4289,105:60247,6:6174,106:7678,7:5322,107:2660,8:4145,108:61423,9:7185,10:5817,11:4161,12:7657,13:8036
// 3:5324,103:1921,4:8181,104:11023,5:4147,105:60563,6:6181,106:7717

// 1:4395,101:14306,2:4578,102:15967,3:5296,103:6306,4:4097,104:11047,5:4248,105:60227,6:6218,106:58349,7:5373,107:2671,8:4142,108:61285,9:7156,10:5800,11:4116,12:7658,13:8051

// 1:4299,101:14364,2:4530,102:16029,3:5316,103:6203,4:4093,104:11058,5:4283,105:60225,6:6236,106:58160,7:5324,107:2682,8:4156,108:61190,9:7153,10:5802,11:4121,12:7647,13:8042

//1:8340,101:14366,2:4529,102:15972,3:5323,103:5789,4:4169,104:11007,5:4274,105:60212,6:6223,106:57986,7:5379,107:2660,8:5021,108:1633,9:7153,10:5800,11:4130,12:7655,13:8036

// 1:8421,101:14328,2:4542,102:16015,3:5326,103:5738,4:4156,104:10964,5:4304,105:60065,6:6218,106:922,7:5384,107:2650,8:7279,108:2031,9:7156,10:5802,11:4110,12:7651,13:8037

// 1:4475,101:14190,2:4538,102:15977,3:5320,103:5281,4:4107,104:11082,5:4280,105:60251,6:6216,106:3773,7:5325,107:2654,8:7273,108:4224,9:7153,10:5801,11:4169,12:7641,13:8115

// 1:4536,101:14172,2:4518,102:15998,3:5336,103:5406,4:8186,104:11063,5:4294,105:60274,6:7242,106:7442,7:5378,107:2642,8:7290,108:4243,9:7155,10:5801,11:4149,12:7655,13:8049

// 1:4422,101:14217,2:4546,102:15965,3:5301,103:5326,4:4091,104:11049,5:4354,105:60225,6:65,106:3240,7:5348,107:2653,8:7208,108:4481,9:7155,10:5802,11:4179,12:7655,13:8098

// 1:4472,101:14134,2:4570,102:15988,3:5283,103:5380,4:4092,104:11049,5:4324,105:60214,6:5202,106:64568,7:5361,107:2671,8:7241,108:4428,9:7155,10:5801,11:4149,12:7656,13:8106

// 4:8175,104:11148

// 1:4524,101:14082,2:4522,102:15990,3:5355,103:5288,4:8186,104:11106,5:4257,105:60240,6:4699,106:1208,7:5439,107:2651,8:7227,108:4449,9:7155,10:5801,11:4148,12:7656,13:8063

// 1:4410,101:14110,2:4553,102:15941,3:5378,103:5267,4:4034,104:11073,5:4289,105:60244,6:6721,106:58526,7:5373,107:2648,8:7276,108:4387,9:7155,10:5804,11:4126,12:7657,13:7994

// 1:3441,101:14151,2:4940,102:15964,3:4678,103:5488,4:5272,104:10451,5:5533,105:59780,6:5426,106:60705,7:5711,107:2630,8:6193,108:4501,9:7161,10:5801,11:4134,12:7674,13:4233

// 1:8321,101:14360,2:4617,102:16001,3:5372,103:5425,4:4114,104:10826,5:4322,105:60040,6:6257,106:60488,7:5298,107:2646,8:7134,108:4678,9:7157,10:5815,11:4102,12:4629,13:4239

// 1:8508,101:14126,2:4633,102:15991,3:5371,103:5562,4:4120,104:10876,5:4343,105:60068,6:6218,106:60500,7:5321,107:2661,8:7283,108:4587,9:7177,10:5785,11:4124,12:4634,13:4261

// 1:4375,101:14113,2:4584,102:15998,3:5262,103:5535,4:8244,104:11021,5:4313,105:60123,6:6262,106:60499,7:5375,107:2673,8:7197,108:4632,9:7163,10:5835,11:4159,12:4675,13:4222

// 1:7810,101:578,2:4602,102:15994,3:9436,103:5413,4:4126,104:10934,5:4304,105:60139,6:6230,106:60468,7:5405,107:2666,8:7253,108:4591,9:7133,10:5801,11:4120,12:4634,13:152

// ,9:7164,10:5820,11:4126,12:4620,13:123

// 1:7698,101:633,2:4486,102:15972,3:9421,103:5384,4:4166,104:10909,5:4301,105:60163,6:6256,106:60451,7:5381,107:2698,8:7281,108:4550,9:7164,10:5804,11:4139,12:4601,13:126

// 1:7794,101:631,2:4504,102:15996,3:5296,103:5334,4:4137,104:10880,5:4313,105:60076,6:6242,106:60402,7:5354,107:2669,8:7283,108:4629,9:7141,10:5789,11:4137,12:4585,13:4222

// 1:7696,101:684,2:4557,102:15947,3:5305,103:5288,4:4155,104:10851,5:4327,105:60115,6:6230,106:60471,7:5281,107:2667,8:7317,108:4598,9:7175,10:5831,11:4239,12:4595,13:4205

// 1:7791,101:737,2:4626,102:15915,3:5336,103:5268,4:4045,104:10807,5:4388,105:59968,6:6230,106:60555,7:5320,107:2657,8:7256,108:4716,9:7141,10:5817,11:8261,12:4559,13:4213,

// 1:7742,101:696,2:4577,102:15916,3:5344,103:5206,4:4117,104:10874,5:4394,105:60007,6:6228,106:60468,7:5309,107:2650,8:7257,108:4711,9:7140,10:5855,11:4095,12:4560,13:4245

// 1:7810,101:598,2:4567,102:15960,3:5313,103:5286,4:4140,104:10908,5:4389,105:60085,6:6222,106:60538,7:5306,107:2661,8:7287,108:4705,9:7174,10:5804,11:4162,12:4568,13:4257

// 1:7736,101:855,2:4616,102:15905,3:5346,103:5215,4:8243,104:10876,5:4332,105:-1,6:6257,106:60538,7:5362,107:2656,8:7221,108:4828,9:7134,10:5748,11:4124,12:4546,13:4230

// 1:7735,101:756,2:4617,102:15910,3:4365,103:5188,4:8434,104:10778,5:4600,105:60151,6:5310,106:60564,7:5362,107:2659,8:7220,108:4789,9:7131,10:5768,11:4136,12:4514,13:4214

// 1:7687,101:859,2:-1,102:15923,3:5354,103:5251,4:4106,104:11024,5:4437,105:60168,6:6234,106:60453,7:-1,107:2649,8:7283,108:4821,9:7171,10:5802,11:4130,12:4576,13:4240

// 1:7738,101:891,2:4636,102:15933,3:5355,103:5197,4:4205,104:10685,5:4322,105:-1,6:6203,106:60513,7:-1,107:2660,8:7298,108:4807,9:7170,10:5803,11:4131,12:4573,13:4230

// 1:7738,101:894,2:4634,102:15883,3:5319,103:5176,4:4205,104:10745,5:4356,105:60163,6:6211,106:60431,7:5361,107:2662,8:7275,108:4700,9:7170,10:5811,11:8276,12:4601,13:4222

// 1:7754,101:973,2:4594,102:15937,3:5362,103:5248,4:4151,104:10826,5:4346,105:60586,6:6180,106:60526,7:5452,107:59514,8:5051,108:59311,9:7186,10:5794,11:4123,12:4493,13:4271

// 1:7754,101:991,2:4587,102:15922,3:5340,103:5232,4:4116,104:10848,5:4332,105:60564,6:6225,106:60473,7:5496,107:59410,8:7258,108:59321,9:7166,10:5801,11:4181,12:4500,13:4228

// 1:7790,101:902,2:4616,102:15934,3:5333,103:5228,4:4144,104:10808,5:4382,105:60677,6:6226,106:60560,7:5451,107:59502,8:7292,108:59328,9:7234,10:5752,11:4143,12:4470,13:4225

// 1:7701,101:-1,2:4609,102:15881,3:5352,103:5205,4:4188,104:10669,5:4383,105:63722,6:6205,106:60465,7:5505,107:59492,8:7184,108:59280,9:7101,10:5769,11:4146,12:4548,13:4254

// 1:7805,101:-1,2:4566,102:15893,3:5365,103:5201,4:4200,104:10710,5:4345,105:63729,6:6250,106:60528,7:5413,107:59585,8:7258,108:59288,9:7162,10:5801,11:4109,12:4494,13:4234

// 1:7792,101:-1,2:4558,102:15920,3:5328,103:5190,4:8193,104:10895,5:4411,105:63884,6:6242,106:60495,7:5415,107:59582,8:7193,108:59375,9:7164,10:5803,11:4133,12:4525,13:4242

// 1:7656,101:-1,2:8713,102:15885,3:5361,103:5056,4:4170,104:10635,5:4301,105:63987,6:6322,106:60295,7:5501,107:59526,8:7217,108:59304,9:7164,10:5803,11:4130,12:4538,13:4204

Dimitri::Dimitri(int deviceIndex, int baudnum)
{
  // Initialize the communications channel
  dxl_initialize(deviceIndex, baudnum);

  // Builds right arm
  this->rightArm = new JointChain();

  //this->rightArm->addJoint(new ElasticJoint(1, 101, 7810-4095, 800));
  this->rightArm->addJoint(new Joint(1, 7810-4095));
  this->rightArm->addJoint(new ElasticJoint(2, 102, 8713-4095, 16002));
  this->rightArm->addJoint(new ElasticJoint(3, 103, 5050-4095, 5418));
  this->rightArm->addJoint(new ElasticJoint(4, 104, 4170-4095, 11042));

  // Builds left arm
  this->leftArm = new JointChain();
  this->leftArm->addJoint(new ElasticJoint(8, 108, 7258-4095, 59311));
  this->leftArm->addJoint(new ElasticJoint(7, 107, 5452-4095, 59514));
  this->leftArm->addJoint(new ElasticJoint(6, 106, 6100-4095, 60500));
  this->leftArm->addJoint(new ElasticJoint(5, 105, 4600-4095, 63550));

  // Builds head
  this->head = new JointChain();
  this->head->addJoint(new Joint(9, 7161-4095));
  this->head->addJoint(new Joint(10, 5802-4095));

  // Builds waist
  this->waist = new JointChain();
  this->waist->addJoint(new Joint(11, 4123-4095));
  this->waist->addJoint(new Joint(12, 4613-4095));
  this->waist->addJoint(new Joint(13, 4222-4095));

  // Set the joint limits for the arms
  this->rightArm->getJoint(ARMROLL)->setAngleLimits(DEG2RAD(-90.0),DEG2RAD(80.0));
  this->leftArm->getJoint(ARMROLL)->setAngleLimits(DEG2RAD(-90.0),DEG2RAD(80.0));
  this->rightArm->getJoint(ARMPITCH)->setAngleLimits(DEG2RAD(-150.0),DEG2RAD(210.0));
  this->leftArm->getJoint(ARMPITCH)->setAngleLimits(DEG2RAD(-150.0),DEG2RAD(210.0));
  this->rightArm->getJoint(ARMYAW)->setAngleLimits(DEG2RAD(-30.0),DEG2RAD(190.0));
  this->leftArm->getJoint(ARMYAW)->setAngleLimits(DEG2RAD(-30.0),DEG2RAD(190.0));
  this->rightArm->getJoint(ELBOW)->setAngleLimits(DEG2RAD(-100.0),DEG2RAD(0.0));
  this->leftArm->getJoint(ELBOW)->setAngleLimits(DEG2RAD(-100.0),DEG2RAD(0.0));

  // Set the joint limits for the head
  this->head->getJoint(HEADPAN)->setAngleLimits(DEG2RAD(-135.0),DEG2RAD(135.0));
  this->head->getJoint(HEADTILT)->setAngleLimits(DEG2RAD(-70.0),DEG2RAD(70.0));

  // Set the joint limits for the waist
  this->waist->getJoint(WAISTYAW)->setAngleLimits(DEG2RAD(-25.0),DEG2RAD(25.0));
  this->waist->getJoint(WAISTROLL)->setAngleLimits(DEG2RAD(-20.0),DEG2RAD(20.0));
  this->waist->getJoint(WAISTPITCH)->setAngleLimits(DEG2RAD(-30.0),DEG2RAD(25.0));

  // Records the initial time
  this->initial_time = clock();
}

Dimitri::~Dimitri()
{
  // Delete left arm
  dxl_terminate();
  for (int i = 0 ; i < leftArm->getTotalJoints() ; i++)
  {
    delete this->leftArm->getJoint(i);
  }
  delete this->leftArm;

  // Delete right arm
  for (int i = 0 ; i < rightArm->getTotalJoints() ; i++)
  {
    delete this->rightArm->getJoint(i);
  }
  delete this->rightArm;

  // Delete head
  for (int i = 0 ; i < head->getTotalJoints() ; i++)
  {
    delete this->head->getJoint(i);
  }
  delete this->head;

  // Delete waist
  for (int i = 0 ; i < waist->getTotalJoints() ; i++)
  {
    delete this->waist->getJoint(i);
  }
  delete this->waist;
}

void Dimitri::update()
{
  this->leftArm->update();
  this->rightArm->update();
  this->head->update();
  this->waist->update();
}

void Dimitri::setControlMode(int mode)
{
  this->leftArm->setControlMode(mode);
  this->rightArm->setControlMode(mode);
  this->head->setControlMode(mode);
  this->waist->setControlMode(mode);
}

void Dimitri::setMaxTorque(int torque)
{
  this->leftArm->setMaxTorque(torque);
  this->rightArm->setMaxTorque(torque);
  this->head->setMaxTorque(torque);
  this->waist->setMaxTorque(torque);
}

void Dimitri::setPose(float lroll, float lpitch, float lyaw, float lelbow,
         float rroll, float rpitch, float ryaw, float relbow,
         float wroll, float wpitch, float wyaw,
         float hpan, float htilt)
{
  this->leftArm->getJoint(ARMROLL)->setGoalAngle(lroll);
  this->leftArm->getJoint(ARMPITCH)->setGoalAngle(lpitch);
  this->leftArm->getJoint(ARMYAW)->setGoalAngle(lyaw);
  this->leftArm->getJoint(ELBOW)->setGoalAngle(lelbow);
  this->rightArm->getJoint(ARMROLL)->setGoalAngle(rroll);
  this->rightArm->getJoint(ARMPITCH)->setGoalAngle(rpitch);
  this->rightArm->getJoint(ARMYAW)->setGoalAngle(ryaw);
  this->rightArm->getJoint(ELBOW)->setGoalAngle(relbow);
  this->waist->getJoint(WAISTROLL)->setGoalAngle(wroll);
  this->waist->getJoint(WAISTPITCH)->setGoalAngle(wpitch);
  this->waist->getJoint(WAISTYAW)->setGoalAngle(wyaw);
  this->head->getJoint(HEADPAN)->setGoalAngle(hpan);
  this->head->getJoint(HEADTILT)->setGoalAngle(htilt);
}

void Dimitri::setNormalizedPose(float lroll, float lpitch, float lyaw, float lelbow,
         float rroll, float rpitch, float ryaw, float relbow,
         float wroll, float wpitch, float wyaw,
         float hpan, float htilt)
{
  this->leftArm->getJoint(ARMROLL)->setNormalizedGoalAngle(lroll);
  this->leftArm->getJoint(ARMPITCH)->setNormalizedGoalAngle(lpitch);
  this->leftArm->getJoint(ARMYAW)->setNormalizedGoalAngle(lyaw);
  this->leftArm->getJoint(ELBOW)->setNormalizedGoalAngle(lelbow);
  this->rightArm->getJoint(ARMROLL)->setNormalizedGoalAngle(rroll);
  this->rightArm->getJoint(ARMPITCH)->setNormalizedGoalAngle(rpitch);
  this->rightArm->getJoint(ARMYAW)->setNormalizedGoalAngle(ryaw);
  this->rightArm->getJoint(ELBOW)->setNormalizedGoalAngle(relbow);
  this->waist->getJoint(WAISTROLL)->setNormalizedGoalAngle(wroll);
  this->waist->getJoint(WAISTPITCH)->setNormalizedGoalAngle(wpitch);
  this->waist->getJoint(WAISTYAW)->setNormalizedGoalAngle(wyaw);
  this->head->getJoint(HEADPAN)->setNormalizedGoalAngle(hpan);
  this->head->getJoint(HEADTILT)->setNormalizedGoalAngle(htilt);
}

void Dimitri::setPose(float pose[])
{
  for (int i = 0 ; i < 21 ; i++)
  {
    switch (i)
    {
      case LROLL:
        this->leftArm->getJoint(ARMROLL)->setGoalAngle(pose[i]);
        break;
      case LPITCH:
        this->leftArm->getJoint(ARMPITCH)->setGoalAngle(pose[i]);
        break;
      case LYAW:
        this->leftArm->getJoint(ARMYAW)->setGoalAngle(pose[i]);
        break;
      case LELBOW:
        this->leftArm->getJoint(ELBOW)->setGoalAngle(pose[i]);
        break;
      case RROLL:
        this->rightArm->getJoint(ARMROLL)->setGoalAngle(pose[i]);
        break;
      case RPITCH:
        this->rightArm->getJoint(ARMPITCH)->setGoalAngle(pose[i]);
        break;
      case RYAW:
        this->rightArm->getJoint(ARMYAW)->setGoalAngle(pose[i]);
        break;
      case RELBOW:
        this->rightArm->getJoint(ELBOW)->setGoalAngle(pose[i]);
        break;
      case WROLL:
        this->waist->getJoint(WAISTROLL)->setGoalAngle(pose[i]);
        break;
      case WPITCH:
        this->waist->getJoint(WAISTPITCH)->setGoalAngle(pose[i]);
        break;
      case WYAW:
        this->waist->getJoint(WAISTYAW)->setGoalAngle(pose[i]);
        break;
      case HPAN:
        this->head->getJoint(HEADPAN)->setGoalAngle(pose[i]);
        break;
      case HTILT:
        this->head->getJoint(HEADTILT)->setGoalAngle(pose[i]);
        break;
    }
  }
}

void Dimitri::setNormalizedPose(float pose[])
{
  for (int i = 0 ; i < 21 ; i++)
  {
    switch (i)
    {
      case LROLL:
        this->leftArm->getJoint(ARMROLL)->setNormalizedGoalAngle(pose[i]);
        break;
      case LPITCH:
        this->leftArm->getJoint(ARMPITCH)->setNormalizedGoalAngle(pose[i]);
        break;
      case LYAW:
        this->leftArm->getJoint(ARMYAW)->setNormalizedGoalAngle(pose[i]);
        break;
      case LELBOW:
        this->leftArm->getJoint(ELBOW)->setNormalizedGoalAngle(pose[i]);
        break;
      case RROLL:
        this->rightArm->getJoint(ARMROLL)->setNormalizedGoalAngle(pose[i]);
        break;
      case RPITCH:
        this->rightArm->getJoint(ARMPITCH)->setNormalizedGoalAngle(pose[i]);
        break;
      case RYAW:
        this->rightArm->getJoint(ARMYAW)->setNormalizedGoalAngle(pose[i]);
        break;
      case RELBOW:
        this->rightArm->getJoint(ELBOW)->setNormalizedGoalAngle(pose[i]);
        break;
      case WROLL:
        this->waist->getJoint(WAISTROLL)->setNormalizedGoalAngle(pose[i]);
        break;
      case WPITCH:
        this->waist->getJoint(WAISTPITCH)->setNormalizedGoalAngle(pose[i]);
        break;
      case WYAW:
        this->waist->getJoint(WAISTYAW)->setNormalizedGoalAngle(pose[i]);
        break;
      case HPAN:
        this->head->getJoint(HEADPAN)->setNormalizedGoalAngle(pose[i]);
        break;
      case HTILT:
        this->head->getJoint(HEADTILT)->setNormalizedGoalAngle(pose[i]);
        break;
    }
  }
}

void Dimitri::getNormalizedPose(float pose[])
{
  for (int i = 0 ; i < 13 ; i++)
  {
    switch (i)
    {
      case LROLL:
        pose[i] = this->leftArm->getJoint(ARMROLL)->getNormalizedAngle();
        break;
      case LPITCH:
        pose[i] = this->leftArm->getJoint(ARMPITCH)->getNormalizedAngle();
        break;
      case LYAW:
        pose[i] = this->leftArm->getJoint(ARMYAW)->getNormalizedAngle();
        break;
      case LELBOW:
        pose[i] = this->leftArm->getJoint(ELBOW)->getNormalizedAngle();
        break;
      case RROLL:
        pose[i] = this->rightArm->getJoint(ARMROLL)->getNormalizedAngle();
        break;
      case RPITCH:
        pose[i] = this->rightArm->getJoint(ARMPITCH)->getNormalizedAngle();
        break;
      case RYAW:
        pose[i] = this->rightArm->getJoint(ARMYAW)->getNormalizedAngle();
        break;
      case RELBOW:
        pose[i] = this->rightArm->getJoint(ELBOW)->getNormalizedAngle();
        break;
      case WROLL:
        pose[i] = this->waist->getJoint(WAISTROLL)->getNormalizedAngle();
        break;
      case WPITCH:
        pose[i] = this->waist->getJoint(WAISTPITCH)->getNormalizedAngle();
        break;
      case WYAW:
        pose[i] = this->waist->getJoint(WAISTYAW)->getNormalizedAngle();
        break;
      case HPAN:
        pose[i] = this->head->getJoint(HEADPAN)->getNormalizedAngle();
        break;
      case HTILT:
        pose[i] = this->head->getJoint(HEADTILT)->getNormalizedAngle();
        break;
    }
  }
}

void Dimitri::getPose(float pose[])
{
  for (int i = 0 ; i < 13 ; i++)
  {
    switch (i)
    {
      case LROLL:
        pose[i] = this->leftArm->getJoint(ARMROLL)->getAngle();
        break;
      case LPITCH:
        pose[i] = this->leftArm->getJoint(ARMPITCH)->getAngle();
        break;
      case LYAW:
        pose[i] = this->leftArm->getJoint(ARMYAW)->getAngle();
        break;
      case LELBOW:
        pose[i] = this->leftArm->getJoint(ELBOW)->getAngle();
        break;
      case RROLL:
        pose[i] = this->rightArm->getJoint(ARMROLL)->getAngle();
        break;
      case RPITCH:
        pose[i] = this->rightArm->getJoint(ARMPITCH)->getAngle();
        break;
      case RYAW:
        pose[i] = this->rightArm->getJoint(ARMYAW)->getAngle();
        break;
      case RELBOW:
        pose[i] = this->rightArm->getJoint(ELBOW)->getAngle();
        break;
      case WROLL:
        pose[i] = this->waist->getJoint(WAISTROLL)->getAngle();
        break;
      case WPITCH:
        pose[i] = this->waist->getJoint(WAISTPITCH)->getAngle();
        break;
      case WYAW:
        pose[i] = this->waist->getJoint(WAISTYAW)->getAngle();
        break;
      case HPAN:
        pose[i] = this->head->getJoint(HEADPAN)->getAngle();
        break;
      case HTILT:
        pose[i] = this->head->getJoint(HEADTILT)->getAngle();
        break;
    }
  }
}

void Dimitri::getPose(float &lroll, float &lpitch, float &lyaw, float &lelbow,
                 float &rroll, float &rpitch, float &ryaw, float &relbow,
                 float &wroll, float &wpitch, float &wyaw,
                 float &hpan, float &htilt)
{
  lroll = this->leftArm->getJoint(ARMROLL)->getAngle();
  lpitch = this->leftArm->getJoint(ARMPITCH)->getAngle();
  lyaw = this->leftArm->getJoint(ARMYAW)->getAngle();
  lelbow = this->leftArm->getJoint(ELBOW)->getAngle();
  rroll = this->rightArm->getJoint(ARMROLL)->getAngle();
  rpitch = this->rightArm->getJoint(ARMPITCH)->getAngle();
  ryaw = this->rightArm->getJoint(ARMYAW)->getAngle();
  relbow = this->rightArm->getJoint(ELBOW)->getAngle();
  wroll = this->waist->getJoint(WAISTROLL)->getAngle();
  wpitch = this->waist->getJoint(WAISTPITCH)->getAngle();
  wyaw = this->waist->getJoint(WAISTYAW)->getAngle();
  hpan = this->head->getJoint(HEADPAN)->getAngle();
  htilt = this->head->getJoint(HEADTILT)->getAngle();
}

void Dimitri::getNormalizedPose(float &lroll, float &lpitch, float &lyaw, float &lelbow,
                 float &rroll, float &rpitch, float &ryaw, float &relbow,
                 float &wroll, float &wpitch, float &wyaw,
                 float &hpan, float &htilt)
{
  lroll = this->leftArm->getJoint(ARMROLL)->getNormalizedAngle();
  lpitch = this->leftArm->getJoint(ARMPITCH)->getNormalizedAngle();
  lyaw = this->leftArm->getJoint(ARMYAW)->getNormalizedAngle();
  lelbow = this->leftArm->getJoint(ELBOW)->getNormalizedAngle();
  rroll = this->rightArm->getJoint(ARMROLL)->getNormalizedAngle();
  rpitch = this->rightArm->getJoint(ARMPITCH)->getNormalizedAngle();
  ryaw = this->rightArm->getJoint(ARMYAW)->getNormalizedAngle();
  relbow = this->rightArm->getJoint(ELBOW)->getNormalizedAngle();
  wroll = this->waist->getJoint(WAISTROLL)->getNormalizedAngle();
  wpitch = this->waist->getJoint(WAISTPITCH)->getNormalizedAngle();
  wyaw = this->waist->getJoint(WAISTYAW)->getNormalizedAngle();
  hpan = this->head->getJoint(HEADPAN)->getNormalizedAngle();
  htilt = this->head->getJoint(HEADTILT)->getNormalizedAngle();
}

void Dimitri::delay(double seconds)
{

    // Records the initial time for each cycle
    clock_t initial_time = clock();

    double elapsed_time = 0;
    
    do {

      // Performs update
      this->update();

      // Calculates the elapsed time in this cycle so far
      elapsed_time = double(clock() - initial_time) / CLOCKS_PER_SEC;

    } while (elapsed_time < seconds);

}

void Dimitri::tick( double seconds )
{

    double elapsed_time = 0;
    time_t current_time;

    do {

      // Calculates the elapsed time in this cycle so far
      current_time = clock();
      elapsed_time = double(current_time - this->initial_time) / CLOCKS_PER_SEC;

    } while (elapsed_time < seconds);

    this->initial_time = current_time;
}

void Dimitri::tickUpdate( double seconds )
{
  this->update();
  this->tick( seconds );
}

