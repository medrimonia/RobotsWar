#include "ATR.hpp"

#include <terminal.h>

#include "NekobotMotors.hpp"

// EXP3
TERMINAL_PARAMETER_DOUBLE(atrExp3Back2Humerus  , "",   70.0);
TERMINAL_PARAMETER_DOUBLE(atrExp3Humerus2Radius, "",   30.0);
TERMINAL_PARAMETER_DOUBLE(atrExp3Back2Femur    , "",  -83.0);
TERMINAL_PARAMETER_DOUBLE(atrExp3Femur2Tibia   , "",   0.0);
TERMINAL_PARAMETER_DOUBLE(atrExp3Tibia2Foot    , "",  -20.0);

// EXP2
TERMINAL_PARAMETER_DOUBLE(atrExp2Back2Humerus  , "",    5.0);
TERMINAL_PARAMETER_DOUBLE(atrExp2Humerus2Radius, "",   80.0);
TERMINAL_PARAMETER_DOUBLE(atrExp2Back2Femur    , "",  -83.0);
TERMINAL_PARAMETER_DOUBLE(atrExp2Femur2Tibia   , "",   0.0);
TERMINAL_PARAMETER_DOUBLE(atrExp2Tibia2Foot    , "",  -20.0);

// EXP1
TERMINAL_PARAMETER_DOUBLE(atrExp1Back2Humerus  , "",  -25.0);
TERMINAL_PARAMETER_DOUBLE(atrExp1Humerus2Radius, "",  120.0);
TERMINAL_PARAMETER_DOUBLE(atrExp1Back2Femur    , "",  -83.0);
TERMINAL_PARAMETER_DOUBLE(atrExp1Femur2Tibia   , "",   0.0);
TERMINAL_PARAMETER_DOUBLE(atrExp1Tibia2Foot    , "",  -20.0);

// FINAL
TERMINAL_PARAMETER_DOUBLE(atrBack2Humerus  , "",  -56.0);
TERMINAL_PARAMETER_DOUBLE(atrHumerus2Radius, "",  150.0);
TERMINAL_PARAMETER_DOUBLE(atrBack2Femur    , "",  -83.0);
TERMINAL_PARAMETER_DOUBLE(atrFemur2Tibia   , "",    0.0);
TERMINAL_PARAMETER_DOUBLE(atrTibia2Foot    , "",  -20.0);

// STEP3
TERMINAL_PARAMETER_DOUBLE(atrS3Back2Humerus  , "",  -51.0);
TERMINAL_PARAMETER_DOUBLE(atrS3Humerus2Radius, "",  150.0);
TERMINAL_PARAMETER_DOUBLE(atrS3Back2Femur    , "",  -70.0);
TERMINAL_PARAMETER_DOUBLE(atrS3Femur2Tibia   , "",   0.0);
TERMINAL_PARAMETER_DOUBLE(atrS3Tibia2Foot    , "",  -20.0);

// STEP 2
TERMINAL_PARAMETER_DOUBLE(atrS2Back2Humerus  , "",  -30.0);
TERMINAL_PARAMETER_DOUBLE(atrS2Humerus2Radius, "",  150.0);
TERMINAL_PARAMETER_DOUBLE(atrS2Back2Femur    , "",    0.0);
TERMINAL_PARAMETER_DOUBLE(atrS2Femur2Tibia   , "",    0.0);
TERMINAL_PARAMETER_DOUBLE(atrS2Tibia2Foot    , "",  -20.0);

// STEP 1
TERMINAL_PARAMETER_DOUBLE(atrPrepBack2Humerus  , "", - 50.0);
TERMINAL_PARAMETER_DOUBLE(atrPrepHumerus2Radius, "",  150.0);
TERMINAL_PARAMETER_DOUBLE(atrPrepBack2Femur    , "",   70.0);
TERMINAL_PARAMETER_DOUBLE(atrPrepFemur2Tibia   , "", - 20.0);
TERMINAL_PARAMETER_DOUBLE(atrPrepTibia2Foot    , "",    0.0);

// INIT
TERMINAL_PARAMETER_DOUBLE(atrInitForeX, "Initial IK posture", - 20.0);
TERMINAL_PARAMETER_DOUBLE(atrInitRearX, "Initial IK posture",    0.0);
TERMINAL_PARAMETER_DOUBLE(atrInitAvgZ , "Initial IK posture",  130.0);
TERMINAL_PARAMETER_DOUBLE(atrInitPitch, "Initial IK posture", - 20.0);

TERMINAL_PARAMETER_INT(atrState, "Current Part of ATR", 0);

#define ATR_STATE_INIT         0
#define ATR_STATE_PREPARATION  1
#define ATR_STATE_STEP2        2
#define ATR_STATE_STEP3        3
#define ATR_STATE_FINAL        4
#define ATR_STATE_EXP1         5
#define ATR_STATE_EXP2         6
#define ATR_STATE_EXP3         7


TERMINAL_PARAMETER_DOUBLE(atrInitTime, "Time to init"     ,  1.0 );
TERMINAL_PARAMETER_DOUBLE(atrPrepTime, "From init to prep",  0.25);
TERMINAL_PARAMETER_DOUBLE(atrStabilizeTime, "On preparation state",  1.0);
TERMINAL_PARAMETER_DOUBLE(atrS2Time, "From prep to S2",  2.5);
TERMINAL_PARAMETER_DOUBLE(atrS3Time, "From S2 to S3",  3.5);
TERMINAL_PARAMETER_DOUBLE(atrFinalTime, "From S3 to final",  1.5);
TERMINAL_PARAMETER_DOUBLE(atrExp1Time, "From final to exp1",  2.5);
TERMINAL_PARAMETER_DOUBLE(atrExp2Time, "From exp1 to exp2",  2.5);
TERMINAL_PARAMETER_DOUBLE(atrExp3Time, "From exp2 to exp3",  3.5);

void initATR(double time)
{
  atrState = ATR_STATE_INIT;
  setAllFromIK(time, atrInitForeX, atrInitRearX, atrInitAvgZ, atrInitPitch);
}

void setPrepATR(double time)
{
  if (atrState != ATR_STATE_PREPARATION) {
    atrState = ATR_STATE_PREPARATION;
    startSmoothing(time, atrPrepTime);
  }
  setFromAngles(time, atrPrepBack2Humerus, atrPrepHumerus2Radius,
                atrPrepBack2Femur, atrPrepFemur2Tibia, atrPrepTibia2Foot);
}

void setS2ATR(double time)
{
  if (atrState != ATR_STATE_STEP2) {
    atrState = ATR_STATE_STEP2;
    startSmoothing(time, atrS2Time);
  }
  setFromAngles(time, atrS2Back2Humerus, atrS2Humerus2Radius,
                atrS2Back2Femur, atrS2Femur2Tibia, atrS2Tibia2Foot);
}

void setS3ATR(double time)
{
  if (atrState != ATR_STATE_STEP3) {
    atrState = ATR_STATE_STEP3;
    startSmoothing(time, atrS3Time);
  }
  setFromAngles(time, atrS3Back2Humerus, atrS3Humerus2Radius,
                atrS3Back2Femur, atrS3Femur2Tibia, atrS3Tibia2Foot);
}

void setFinalATR(double time)
{
  if (atrState != ATR_STATE_FINAL) {
    atrState = ATR_STATE_FINAL;
    startSmoothing(time, atrFinalTime);
  }
  setFromAngles(time, atrBack2Humerus, atrHumerus2Radius,
                atrBack2Femur, atrFemur2Tibia, atrTibia2Foot);
}

void setExp1ATR(double time)
{
  if (atrState != ATR_STATE_EXP1) {
    atrState = ATR_STATE_EXP1;
    startSmoothing(time, atrExp1Time);
  }
  setFromAngles(time, atrExp1Back2Humerus, atrExp1Humerus2Radius,
                atrExp1Back2Femur, atrExp1Femur2Tibia, atrExp1Tibia2Foot);
}

void setExp2ATR(double time)
{
  if (atrState != ATR_STATE_EXP2) {
    atrState = ATR_STATE_EXP2;
    startSmoothing(time, atrExp2Time);
  }
  setFromAngles(time, atrExp2Back2Humerus, atrExp2Humerus2Radius,
                atrExp2Back2Femur, atrExp2Femur2Tibia, atrExp2Tibia2Foot);
}

void setExp3ATR(double time)
{
  if (atrState != ATR_STATE_EXP3) {
    atrState = ATR_STATE_EXP3;
    startSmoothing(time, atrExp3Time);
  }
  setFromAngles(time, atrExp3Back2Humerus, atrExp3Humerus2Radius,
                atrExp3Back2Femur, atrExp3Femur2Tibia, atrExp3Tibia2Foot);
}

void performATR(double time, double startTime)
{
  double elapsedTime = time - startTime;
  if (elapsedTime < atrInitTime) {
    initATR(time);
    return;
  }
  elapsedTime -= atrInitTime;
  if (elapsedTime < atrPrepTime + atrStabilizeTime) {
    setPrepATR(time);
    return;
  }
  elapsedTime -= atrPrepTime;
  if (elapsedTime < atrS2Time) {
    setS2ATR(time);
    return;
  }
  elapsedTime -= atrS2Time;
  if (elapsedTime < atrS3Time) {
    setS3ATR(time);
    return;
  }
  elapsedTime -= atrS3Time;
  setFinalATR(time);
// DANGER ZONE !
  if (elapsedTime < atrFinalTime) {
    setFinalATR(time);
    return;
  }
  elapsedTime -= atrFinalTime;
  if (elapsedTime < atrExp1Time) {
    setExp1ATR(time);
    return;
  }
  elapsedTime -= atrExp1Time;
  if (elapsedTime < atrExp2Time) {
    setExp2ATR(time);
    return;
  }
  elapsedTime -= atrExp2Time;
  setExp3ATR(time);
}

void backFromAtr(double time, double startTime)
{
  double totalATRTime = atrInitTime
}
