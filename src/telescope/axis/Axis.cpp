// -----------------------------------------------------------------------------------
// Axis motion control

#include "Axis.h"

#ifdef AXIS_PRESENT

#include "../../tasks/OnTask.h"

#include "../Telescope.h"
#include "../../lib/sense/Sense.h"
#if AXIS1_DRIVER_MODEL != OFF
  void pollAxis1() { axis1.poll(); }
  const AxisPins PinsAxis1 = { AXIS1_SENSE_LIMIT_MIN_PIN, AXIS1_SENSE_HOME_PIN, AXIS1_SENSE_LIMIT_MAX_PIN, { AXIS1_SENSE_HOME, AXIS1_SENSE_HOME_INIT, AXIS1_SENSE_LIMIT_MIN, AXIS1_SENSE_LIMIT_MAX, AXIS1_SENSE_LIMIT_INIT } };
  const AxisSettings SettingsAxis1 = { AXIS1_STEPS_PER_DEGREE*RAD_DEG_RATIO, AXIS1_REVERSE, AXIS1_PARAMETER1, AXIS1_PARAMETER2, { degToRadF(AXIS1_LIMIT_MIN), degToRadF(AXIS1_LIMIT_MAX) }, siderealToRad(TRACK_BACKLASH_RATE) };
  Axis axis1(1, &PinsAxis1, &SettingsAxis1, &motor1);
#endif
#if AXIS2_DRIVER_MODEL != OFF
  void pollAxis2() { axis2.poll(); }
  const AxisPins PinsAxis2 = { AXIS2_SENSE_LIMIT_MIN_PIN, AXIS2_SENSE_HOME_PIN, AXIS2_SENSE_LIMIT_MAX_PIN, { AXIS2_SENSE_HOME, AXIS2_SENSE_HOME_INIT, AXIS2_SENSE_LIMIT_MIN, AXIS2_SENSE_LIMIT_MAX, AXIS2_SENSE_LIMIT_INIT } };
  const AxisSettings SettingsAxis2 = { AXIS2_STEPS_PER_DEGREE*RAD_DEG_RATIO, AXIS2_REVERSE, AXIS2_PARAMETER1, AXIS2_PARAMETER2, { degToRadF(AXIS2_LIMIT_MIN), degToRadF(AXIS2_LIMIT_MAX) }, siderealToRad(TRACK_BACKLASH_RATE) };
  Axis axis2(2, &PinsAxis2, &SettingsAxis2, &motor2);
#endif
#if AXIS3_DRIVER_MODEL != OFF
  void pollAxis3() { axis3.poll(); }
  const AxisPins PinsAxis3 = { AXIS3_SENSE_LIMIT_MIN_PIN, AXIS3_SENSE_HOME_PIN, AXIS3_SENSE_LIMIT_MAX_PIN, { AXIS3_SENSE_HOME, AXIS3_SENSE_HOME_INIT, AXIS3_SENSE_LIMIT_MIN, AXIS3_SENSE_LIMIT_MAX, AXIS3_SENSE_LIMIT_INIT } };
  const AxisSettings SettingsAxis3 = { AXIS3_STEPS_PER_DEGREE, AXIS3_REVERSE, AXIS3_PARAMETER1, AXIS3_PARAMETER2, { AXIS3_LIMIT_MIN, AXIS3_LIMIT_MAX }, AXIS3_BACKLASH_RATE };
  Axis axis3(3, &PinsAxis3, &SettingsAxis3, &motor3);
#endif
#if AXIS4_DRIVER_MODEL != OFF
  void pollAxis4() { axis4.poll(); }
  const AxisPins PinsAxis4 = { AXIS4_SENSE_LIMIT_MIN_PIN, AXIS4_SENSE_HOME_PIN, AXIS4_SENSE_LIMIT_MAX_PIN, { AXIS4_SENSE_HOME, AXIS4_SENSE_HOME_INIT, AXIS4_SENSE_LIMIT_MIN, AXIS4_SENSE_LIMIT_MAX, AXIS4_SENSE_LIMIT_INIT } };
  const AxisSettings SettingsAxis4 = { AXIS4_STEPS_PER_MICRON, AXIS4_REVERSE, AXIS4_PARAMETER1, AXIS4_PARAMETER2, { AXIS4_LIMIT_MIN*1000.0F, AXIS4_LIMIT_MAX*1000.0F }, AXIS4_BACKLASH_RATE };
  Axis axis4(4, &PinsAxis4, &SettingsAxis4, &motor4);
#endif
#if AXIS5_DRIVER_MODEL != OFF
  void pollAxis5() { axis5.poll(); }
  const AxisPins PinsAxis5 = { AXIS5_SENSE_LIMIT_MIN_PIN, AXIS5_SENSE_HOME_PIN, AXIS5_SENSE_LIMIT_MAX_PIN, { AXIS5_SENSE_HOME, AXIS5_SENSE_HOME_INIT, AXIS5_SENSE_LIMIT_MIN, AXIS5_SENSE_LIMIT_MAX, AXIS5_SENSE_LIMIT_INIT } };
  const AxisSettings SettingsAxis5 = { AXIS5_STEPS_PER_MICRON, AXIS5_REVERSE, AXIS5_PARAMETER1, AXIS5_PARAMETER2, { AXIS5_LIMIT_MIN*1000.0F, AXIS5_LIMIT_MAX*1000.0F }, AXIS5_BACKLASH_RATE };
  Axis axis5(5, &PinsAxis5, &SettingsAxis5, &motor5);
#endif
#if AXIS6_DRIVER_MODEL != OFF
  void pollAxis6() { axis6.poll(); }
  const AxisPins PinsAxis6 = { AXIS6_SENSE_LIMIT_MIN_PIN, AXIS6_SENSE_HOME_PIN, AXIS6_SENSE_LIMIT_MAX_PIN, { AXIS6_SENSE_HOME, AXIS6_SENSE_HOME_INIT, AXIS6_SENSE_LIMIT_MIN, AXIS6_SENSE_LIMIT_MAX, AXIS6_SENSE_LIMIT_INIT } };
  const AxisSettings SettingsAxis6 = { AXIS6_STEPS_PER_MICRON, AXIS6_REVERSE, AXIS6_PARAMETER1, AXIS6_PARAMETER2, { AXIS6_LIMIT_MIN*1000.0F, AXIS6_LIMIT_MAX*1000.0F }, AXIS6_BACKLASH_RATE };
  Axis axis6(6, &PinsAxis6, &SettingsAxis6, &motor6);
#endif
#if AXIS7_DRIVER_MODEL != OFF
  void pollAxis7() { axis7.poll(); }
  const AxisPins PinsAxis7 = { AXIS7_SENSE_LIMIT_MIN_PIN, AXIS7_SENSE_HOME_PIN, AXIS7_SENSE_LIMIT_MAX_PIN, { AXIS7_SENSE_HOME, AXIS7_SENSE_HOME_INIT, AXIS7_SENSE_LIMIT_MIN, AXIS7_SENSE_LIMIT_MAX, AXIS7_SENSE_LIMIT_INIT } };
  const AxisSettings SettingsAxis7 = { AXIS7_STEPS_PER_MICRON, AXIS7_REVERSE, AXIS7_PARAMETER1, AXIS7_PARAMETER2, { AXIS7_LIMIT_MIN*1000.0F, AXIS7_LIMIT_MAX*1000.0F }, AXIS7_BACKLASH_RATE };
  Axis axis7(7, &PinsAxis7, &SettingsAxis7, &motor7);
#endif
#if AXIS8_DRIVER_MODEL != OFF
  void pollAxis8() { axis8.poll(); }
  const AxisPins PinsAxis8 = { AXIS8_SENSE_LIMIT_MIN_PIN, AXIS8_SENSE_HOME_PIN, AXIS8_SENSE_LIMIT_MAX_PIN, { AXIS8_SENSE_HOME, AXIS8_SENSE_HOME_INIT, AXIS8_SENSE_LIMIT_MIN, AXIS8_SENSE_LIMIT_MAX, AXIS8_SENSE_LIMIT_INIT} };
  const AxisSettings SettingsAxis8 = { AXIS8_STEPS_PER_MICRON, AXIS8_REVERSE, AXIS8_PARAMETER1, AXIS8_PARAMETER2, { AXIS8_LIMIT_MIN*1000.0F, AXIS8_LIMIT_MAX*1000.0F }, AXIS8_BACKLASH_RATE};
  Axis axis8(8, &PinsAxis8, &SettingsAxis8, &motor8);
#endif
#if AXIS9_DRIVER_MODEL != OFF
  void pollAxis9() { axis9.poll(); }
  const AxisPins PinsAxis9 = { AXIS9_SENSE_LIMIT_MIN_PIN, AXIS9_SENSE_HOME_PIN, AXIS9_SENSE_LIMIT_MAX_PIN, { AXIS9_SENSE_HOME, AXIS9_SENSE_HOME_INIT, AXIS9_SENSE_LIMIT_MIN, AXIS9_SENSE_LIMIT_MAX, AXIS9_SENSE_LIMIT_INIT} };
  const AxisSettings SettingsAxis9 = { AXIS9_STEPS_PER_MICRON, AXIS9_REVERSE, AXIS9_PARAMETER1, AXIS9_PARAMETER2, { AXIS9_LIMIT_MIN*1000.0F, AXIS9_LIMIT_MAX*1000.0F }, AXIS9_BACKLASH_RATE};
  Axis axis9(9, &PinsAxis9, &SettingsAxis9, &motor9);
#endif

// constructor
Axis::Axis(uint8_t axisNumber, const AxisPins *pins, const AxisSettings *settings, Motor *motor) {
  axisPrefix[9] = '0' + axisNumber;
  this->axisNumber = axisNumber;

  this->pins = pins;
  this->settings = *settings;
  this->motor = motor;
}

// sets up the driver step/dir/enable pins and any associated driver mode control
void Axis::init() {
  // start monitor
  V(axisPrefix); VF("start monitor task (rate "); V(SIDEREAL_IV_MS); VF("ms priority 1)... ");
  uint8_t taskHandle = 0;
  #if AXIS1_DRIVER_MODEL != OFF
    if (axisNumber == 1) { taskHandle = tasks.add(SIDEREAL_IV_MS, 0, true, 1, pollAxis1, "mtrAx1"); }
  #endif
  #if AXIS2_DRIVER_MODEL != OFF
    if (axisNumber == 2) { taskHandle = tasks.add(SIDEREAL_IV_MS, 0, true, 1, pollAxis2, "mtrAx2"); }
  #endif
  #if AXIS3_DRIVER_MODEL != OFF
    if (axisNumber == 3) { taskHandle = tasks.add(SIDEREAL_IV_MS, 0, true, 1, pollAxis3, "mtrAx3"); }
  #endif
  #if AXIS4_DRIVER_MODEL != OFF
    if (axisNumber == 4) { taskHandle = tasks.add(SIDEREAL_IV_MS, 0, true, 1, pollAxis4, "mtrAx4"); }
  #endif
  #if AXIS5_DRIVER_MODEL != OFF
    if (axisNumber == 5) { taskHandle = tasks.add(SIDEREAL_IV_MS, 0, true, 1, pollAxis5, "mtrAx5"); }
  #endif
  #if AXIS6_DRIVER_MODEL != OFF
    if (axisNumber == 6) { taskHandle = tasks.add(SIDEREAL_IV_MS, 0, true, 1, pollAxis6, "mtrAx6"); }
  #endif
  #if AXIS7_DRIVER_MODEL != OFF
    if (axisNumber == 7) { taskHandle = tasks.add(SIDEREAL_IV_MS, 0, true, 1, pollAxis7, "mtrAx7"); }
  #endif
  #if AXIS8_DRIVER_MODEL != OFF
    if (axisNumber == 8) { taskHandle = tasks.add(SIDEREAL_IV_MS, 0, true, 1, pollAxis8, "mtrAx8"); }
  #endif
  #if AXIS9_DRIVER_MODEL != OFF
    if (axisNumber == 9) { taskHandle = tasks.add(SIDEREAL_IV_MS, 0, true, 1, pollAxis9, "mtrAx9"); }
  #endif
  if (taskHandle) { VL("success"); } else { VL("FAILED!"); }

  // check for reverting axis settings in NV
  if (!validKey) {
    V(axisPrefix); VLF("writing default settings to NV");
    uint16_t axesToRevert = nv.readUI(NV_AXIS_SETTINGS_REVERT);
    bitSet(axesToRevert, axisNumber);
    nv.write(NV_AXIS_SETTINGS_REVERT, axesToRevert);
  }

  // write axis settings to NV
  // NV_AXIS_SETTINGS_REVERT bit 0 = settings at compile (0) or run time (1), bits 1 to 9 = reset axis n on next boot
  if (AxisSettingsSize < sizeof(AxisSettings)) { initError.nv = true; DL("ERR: Axis::init(); AxisSettingsSize error NV subsystem writes disabled"); nv.readOnly(true); }
  uint16_t axesToRevert = nv.readUI(NV_AXIS_SETTINGS_REVERT);
  if (!(axesToRevert & 1)) bitSet(axesToRevert, axisNumber);
  if (bitRead(axesToRevert, axisNumber)) {
    V(axisPrefix); VLF("reverting settings to Config.h defaults");
    nv.updateBytes(NV_AXIS_SETTINGS_BASE + (axisNumber - 1)*AxisSettingsSize, &settings, sizeof(AxisSettings));
  }
  bitClear(axesToRevert, axisNumber);
  nv.write(NV_AXIS_SETTINGS_REVERT, axesToRevert);

  // read axis settings from NV
  nv.readBytes(NV_AXIS_SETTINGS_BASE + (axisNumber - 1)*AxisSettingsSize, &settings, sizeof(AxisSettings));
  if (!validateAxisSettings(axisNumber, settings)) initError.value = true;

  #if DEBUG == VERBOSE
    V(axisPrefix); VF("stepsPerMeasure="); V(settings.stepsPerMeasure);
    V(", reverse="); if (settings.reverse == OFF) VL("OFF"); else if (settings.reverse == ON) VL("OFF"); else VL("?");
    V(axisPrefix); VF("backlash takeup frequency set to ");
    if (axisNumber <= 3) { V(radToDegF(settings.backlashFreq)); VL(" deg/sec."); } else { V(settings.backlashFreq); VL(" microns/sec."); }
  #endif

  // get the motor ready
  if (!motor->init(settings.reverse, settings.param1, settings.param2)) {
    VLF("MSG: Axis, nothing to do exiting!");
    return;
  }
  motor->setBacklashFrequencySteps(settings.backlashFreq*settings.stepsPerMeasure);

  // activate home and limit sense
  V(axisPrefix); VLF("adding any home and/or limit senses");
  homeSenseHandle = senses.add(pins->home, pins->sense.homeInit, pins->sense.homeTrigger);
  minSenseHandle = senses.add(pins->min, pins->sense.minMaxInit, pins->sense.minTrigger);
  maxSenseHandle = senses.add(pins->max, pins->sense.minMaxInit, pins->sense.maxTrigger);
}

// enables or disables the associated step/dir driver
void Axis::enable(bool state) {
  enabled = state;
  motor->power(state & !poweredDown);
}

// time (in ms) before automatic power down at standstill, use 0 to disable
void Axis::setPowerDownTime(int value) {
  if (value == 0) powerDownStandstill = false; else { powerDownStandstill = true; powerDownDelay = value; }
}

// time (in ms) to disable automatic power down at standstill, use 0 to disable
void Axis::setPowerDownOverrideTime(int value) {
  if (value == 0) powerDownOverride = false; else { powerDownOverride = true; powerDownOverrideEnds = millis() + value; }
}

// set backlash amount in "measures" (radians, microns, etc.)
void Axis::setBacklash(float value) {
  if (autoRate == AR_NONE) motor->setBacklashSteps(round(value*settings.stepsPerMeasure));
}

// get backlash amount in "measures" (radians, microns, etc.)
float Axis::getBacklash() {
  return motor->getBacklashSteps()/settings.stepsPerMeasure;
}

// reset motor and target angular position, in "measure" units
CommandError Axis::resetPosition(double value) {
  return resetPositionSteps(lround(value*settings.stepsPerMeasure));
}

// reset motor and target angular position, in steps
CommandError Axis::resetPositionSteps(long value) {
  if (autoRate != AR_NONE) return CE_SLEW_IN_MOTION;
  if (motor->getFrequencySteps() != 0) return CE_SLEW_IN_MOTION;
  motor->resetPositionSteps(value);
  return CE_NONE;
}

// get motor position, in "measure" units
double Axis::getMotorPosition() {
  return motor->getMotorPositionSteps()/settings.stepsPerMeasure;
}

// get index position, in "measure" units
double Axis::getIndexPosition() {
  return motor->getIndexPositionSteps()/settings.stepsPerMeasure;
}

double distance(double c1, double c2) {
  double d1 = abs(c1 - c2);
  double d2 = abs(c2 - c1);
  if (d1 <= d2) return d1; else return d2;
}

// convert from unwrapped (full range) to normal (+/- wrapAmount) coordinate
double Axis::wrap(double value) {
  if (wrapEnabled) {
    while (value > settings.limits.max) value -= wrapAmount;
    while (value < settings.limits.min) value += wrapAmount;
  }
  return value;
}

// convert from normal (+/- wrapAmount) to an unwrapped (full range) coordinate
double Axis::unwrap(double value) {
  if (wrapEnabled) {
    double position = motor->getInstrumentCoordinateSteps()/settings.stepsPerMeasure;
    while (value > position + wrapAmount/2.0L) value -= wrapAmount;
    while (value < position - wrapAmount/2.0L) value += wrapAmount;
  }
  return value;
}

// convert from normal (+/- wrapAmount) to an unwrapped (full range) coordinate
// nearest the instrument coordinate
double Axis::unwrapNearest(double value) {
  if (wrapEnabled) {
    value = unwrap(value);
    double instr = motor->getInstrumentCoordinateSteps()/settings.stepsPerMeasure;
//    V(axisPrefix);
//    VF("unwrapNearest instr "); V(radToDeg(instr));
//    VF(", before "); V(radToDeg(value));
    double dist = distance(value, instr);
    if (distance(value + wrapAmount, instr) < dist) value += wrapAmount; else
    if (distance(value - wrapAmount, instr) < dist) value -= wrapAmount;
//    VF(", after "); VL(radToDeg(value));
  }
  return value;
}

// set instrument coordinate, in "measures" (radians, microns, etc.)
void Axis::setInstrumentCoordinate(double value) {
  setInstrumentCoordinateSteps(lround(unwrap(value)*settings.stepsPerMeasure));
}

// get instrument coordinate
double Axis::getInstrumentCoordinate() {
  return wrap(motor->getInstrumentCoordinateSteps()/settings.stepsPerMeasure);
}

// set instrument coordinate park, in "measures" (radians, microns, etc.)
// with backlash disabled this indexes to the nearest position where the motor wouldn't cog
void Axis::setInstrumentCoordinatePark(double value) {
  motor->setInstrumentCoordinateParkSteps(lround(unwrapNearest(value)*settings.stepsPerMeasure), settings.subdivisions);
}

// set target coordinate park, in "measures" (degrees, microns, etc.)
// with backlash disabled this moves to the nearest position where the motor doesn't cog
void Axis::setTargetCoordinatePark(double value) {
  motor->setFrequencySteps(0);
  motor->setTargetCoordinateParkSteps(lround(unwrapNearest(value)*settings.stepsPerMeasure), settings.subdivisions);
}

// set target coordinate, in "measures" (degrees, microns, etc.)
void Axis::setTargetCoordinate(double value) {
  setTargetCoordinateSteps(lround(unwrapNearest(value)*settings.stepsPerMeasure));
}

// get target coordinate, in "measures" (degrees, microns, etc.)
double Axis::getTargetCoordinate() {
  return wrap(motor->getTargetCoordinateSteps()/settings.stepsPerMeasure);
}

// check if we're at the target coordinate during an auto slew
bool Axis::atTarget() {
  return labs(motor->getTargetDistanceSteps()) < 1;
}

// distance to target in "measures" (degrees, microns, etc.)
double Axis::getTargetDistance() {
  return labs(motor->getTargetDistanceSteps())/settings.stepsPerMeasure;
}

// distance to origin or target, whichever is closer, in "measures" (degrees, microns, etc.)
double Axis::getOriginOrTargetDistance() {
  return motor->getOriginOrTargetDistanceSteps()/settings.stepsPerMeasure;
}

// set acceleration rate in "measures" per second per second (for autoSlew)
void Axis::setSlewAccelerationRate(float mpsps) {
  if (autoRate == AR_NONE) {
    slewMpspfs = mpsps/SIDEREAL_FRAC;
    slewAccelTime = NAN;
  }
}

// set acceleration rate in seconds (for autoSlew)
void Axis::setSlewAccelerationTime(float seconds) {
  if (autoRate == AR_NONE) slewAccelTime = seconds;
}

// set acceleration for emergency stop movement in "measures" per second per second
void Axis::setSlewAccelerationRateAbort(float mpsps) {
  if (autoRate == AR_NONE) {
    abortMpspfs = mpsps/SIDEREAL_FRAC;
    abortAccelTime = NAN;
  }
}

// set acceleration for emergency stop movement in seconds (for autoSlewStop)
void Axis::setSlewAccelerationTimeAbort(float seconds) {
  if (autoRate == AR_NONE) abortAccelTime = seconds;
}

// slew with rate by distance
// \param distance: acceleration distance in measures (to frequency)
// \param frequency: optional frequency of slew in "measures" (radians, microns, etc.) per second
CommandError Axis::autoSlewRateByDistance(float distance, float frequency) {
  if (!enabled) return CE_SLEW_ERR_IN_STANDBY;
  if (autoRate != AR_NONE) return CE_SLEW_IN_SLEW;
  if (motionError(DIR_BOTH)) return CE_SLEW_ERR_OUTSIDE_LIMITS;

  if (!isnan(frequency)) setFrequencySlew(frequency);

  motor->markOriginCoordinateSteps();
  slewAccelerationDistance = distance;
  motor->setSynchronized(false);
  motor->setSlewing(true);
  autoRate = AR_RATE_BY_DISTANCE;
  rampFreq = 0.0F;
  return CE_NONE;
}

// stops, with deacceleration by distance
bool Axis::autoSlewRateByDistanceStop() {
  if (autoRate != AR_RATE_BY_DISTANCE) return false;
  autoRate = AR_NONE;
  motor->setSlewing(false);
  motor->setSynchronized(true);
  return true;
}

// auto slew with acceleration in "measures" per second per second
// \param direction: direction of motion, DIR_FORWARD or DIR_REVERSE
// \param frequency: optional frequency of slew in "measures" (radians, microns, etc.) per second
CommandError Axis::autoSlew(Direction direction, float frequency) {
  if (!enabled) return CE_SLEW_ERR_IN_STANDBY;
  if (autoRate == AR_RATE_BY_DISTANCE) return CE_SLEW_IN_SLEW;
  if (motionError(direction)) return CE_SLEW_ERR_OUTSIDE_LIMITS;
  if (direction != DIR_FORWARD && direction != DIR_REVERSE) return CE_SLEW_ERR_UNSPECIFIED;

  if (!isnan(frequency)) setFrequencySlew(frequency);

  V(axisPrefix);
  if (autoRate == AR_NONE) {
    motor->setSynchronized(true);
    motor->setSlewing(true);
    VF("autoSlew start ");
  } else { VF("autoSlew resum "); }
  if (direction == DIR_FORWARD) {
    autoRate = AR_RATE_BY_TIME_FORWARD;
    VF("fwd@ ");
  } else {
    autoRate = AR_RATE_BY_TIME_REVERSE;
    VF("rev@ ");
  }
  #if DEBUG == VERBOSE
    if (axisNumber <= 2) { V(radToDeg(slewFreq)); V("°/s, accel "); SERIAL_DEBUG.print(radToDeg(slewMpspfs)*SIDEREAL_FRAC, 3); VL("°/s/s"); }
    if (axisNumber == 3) { V(slewFreq); V("°/s, accel "); SERIAL_DEBUG.print(slewMpspfs*SIDEREAL_FRAC, 3); VL("°/s/s"); }
    if (axisNumber > 3) { V(slewFreq); V("um/s, accel "); SERIAL_DEBUG.print(slewMpspfs*SIDEREAL_FRAC, 3); VL("um/s/s"); }
  #endif

  return CE_NONE;
}

// slew to home, with acceleration in "measures" per second per second
CommandError Axis::autoSlewHome() {
  if (!enabled) return CE_SLEW_ERR_IN_STANDBY;
  if (autoRate != AR_NONE) return CE_SLEW_IN_SLEW;
  if (motionError(DIR_BOTH)) return CE_SLEW_ERR_OUTSIDE_LIMITS;

  if (pins->sense.homeTrigger != OFF) {
    motor->setSynchronized(true);
    if (homingStage == HOME_NONE) homingStage = HOME_FAST;
    if (autoRate == AR_NONE) {
      motor->setSlewing(true);
      V(axisPrefix); VF("autoSlewHome ");
      switch (homingStage) {
        case HOME_FAST: VL("fast started"); break;
        case HOME_SLOW: VL("slow started"); break;
        case HOME_FINE: VL("fine started"); break;
        case HOME_NONE: VL("?"); break;
      }
    }
    if (senses.read(homeSenseHandle)) {
      V(axisPrefix); VLF("move fwd");
      autoRate = AR_RATE_BY_TIME_FORWARD;
    } else {
      V(axisPrefix); VLF("move rev");
      autoRate = AR_RATE_BY_TIME_REVERSE;
    }
  }
  return CE_NONE;
}

// stops, with deacceleration by time
void Axis::autoSlewStop() {
  if (autoRate == AR_NONE || autoRate == AR_RATE_BY_TIME_ABORT) return;

  motor->setSynchronized(true);

  V(axisPrefix); VLF("slew stopping");
  autoRate = AR_RATE_BY_TIME_END;
  poll();
}

// emergency stops, with deacceleration by time
void Axis::autoSlewAbort() {
  if (autoRate == AR_NONE) return;

  motor->setSynchronized(true);

  V(axisPrefix); VLF("slew aborting");
  autoRate = AR_RATE_BY_TIME_ABORT;
  homingStage = HOME_NONE;
  poll();
}

// checks if slew is active on this axis
bool Axis::isSlewing() {
  return autoRate != AR_NONE;  
}

// monitor movement
void Axis::poll() {
  // make sure we're ready
  if (axisNumber == 0) return;

  // check physical limit switches
  errors.minLimitSensed = senses.read(minSenseHandle);
  errors.maxLimitSensed = senses.read(maxSenseHandle);

  // stop homing as we pass by the switch
  if (homingStage != HOME_NONE) {
    if (autoRate == AR_RATE_BY_TIME_FORWARD && !senses.read(homeSenseHandle)) autoSlewStop();
    if (autoRate == AR_RATE_BY_TIME_REVERSE && senses.read(homeSenseHandle)) autoSlewStop();
  }
  Y;

  // slewing
  if (autoRate != AR_NONE && !motor->inBacklash) {
    if (autoRate != AR_RATE_BY_TIME_ABORT) {
      if (motionError(motor->getDirection())) { autoSlewAbort(); return; }
    }
    if (autoRate == AR_RATE_BY_DISTANCE) {
      if (motor->getTargetDistanceSteps() == 0) {
        motor->setSlewing(false);
        autoRate = AR_NONE;
        freq = 0.0F;
        motor->setSynchronized(true);
        V(axisPrefix); VLF("slew stopped");
      } else {
        if (fabs(freq) > settings.backlashFreq) {
          if (motor->getTargetDistanceSteps() < 0) rampFreq -= getRampDirection()*slewMpspfs; else rampFreq += getRampDirection()*slewMpspfs;
          freq = rampFreq;
          if (freq < -slewFreq) freq = -slewFreq;
          if (freq > slewFreq) freq = slewFreq;
        } else {
          freq = (getOriginOrTargetDistance()/slewAccelerationDistance)*slewFreq;
          if (freq < settings.backlashFreq/2.0F) freq = settings.backlashFreq/2.0F;
          if (freq > settings.backlashFreq*1.05F) freq = settings.backlashFreq*1.05F;
          if (motor->getTargetDistanceSteps() < 0) freq = -freq;
          rampFreq = freq;
        }
      }
    } else
    if (autoRate == AR_RATE_BY_TIME_FORWARD) {
      freq += slewMpspfs;
      if (freq > slewFreq) freq = slewFreq;
    } else
    if (autoRate == AR_RATE_BY_TIME_REVERSE) {
      freq -= slewMpspfs;
      if (freq < -slewFreq) freq = -slewFreq;
    } else
    if (autoRate == AR_RATE_BY_TIME_END) {
      if (freq > slewMpspfs) freq -= slewMpspfs; else if (freq < -slewMpspfs) freq += slewMpspfs; else freq = 0.0F;
      if (abs(freq) <= slewMpspfs) {
        motor->setSlewing(false);
        autoRate = AR_NONE;
        freq = 0.0F;
        if (homingStage == HOME_FAST) homingStage = HOME_SLOW; else 
        if (homingStage == HOME_SLOW) homingStage = HOME_FINE; else
        if (homingStage == HOME_FINE) homingStage = HOME_NONE;
        if (homingStage != HOME_NONE) {
          float f = slewFreq/4.0F;
          if (abs(f) < 0.0003F) { if (f < 0.0F) f = -0.0003F; else f = 0.0003F; }
          setFrequencySlew(abs(f));
          autoSlewHome();
        } else {
          V(axisPrefix); VLF("slew stopped");
        }
      }
    } else
    if (autoRate == AR_RATE_BY_TIME_ABORT) {
      if (freq > abortMpspfs) freq -= abortMpspfs; else if (freq < -abortMpspfs) freq += abortMpspfs; else freq = 0.0F;
      if (fabs(freq) <= abortMpspfs) {
        motor->setSlewing(false);
        autoRate = AR_NONE;
        freq = 0.0F;
        V(axisPrefix); VLF("slew aborted");
      }
    } else freq = 0.0F;
  } else {
    freq = 0.0F;
    if (motionError(DIR_BOTH)) baseFreq = 0.0F;
  }
  Y;

  setFrequency(freq);
}

// set minimum slew frequency in "measures" (radians, microns, etc.) per second
void Axis::setFrequencyMin(float frequency) {
  minFreq = frequency;
}

// set maximum slew frequency in "measures" (radians, microns, etc.) per second
void Axis::setFrequencyMax(float frequency) {
  maxFreq = frequency;
}

// frequency for base movement in "measures" (radians, microns, etc.) per second
void Axis::setFrequencyBase(float frequency) {
  baseFreq = frequency;
}

// frequency for slews in "measures" (radians, microns, etc.) per second
void Axis::setFrequencySlew(float frequency) {
  if (minFreq != 0.0F && frequency < minFreq) frequency = minFreq;
  if (maxFreq != 0.0F && frequency > maxFreq) frequency = maxFreq;
  slewFreq = frequency;

  // adjust acceleration rates if they depend on slewFreq
  if (!isnan(slewAccelTime)) slewMpspfs = (slewFreq/slewAccelTime)/SIDEREAL_FRAC;
  if (!isnan(abortAccelTime)) abortMpspfs = (slewFreq/abortAccelTime)/SIDEREAL_FRAC;
}

// set frequency in "measures" (degrees, microns, etc.) per second (0 stops motion)
void Axis::setFrequency(float frequency) {
  if (powerDownStandstill && frequency == 0.0F) {
    if (!poweredDown) {
      if (!powerDownOverride || (long)(millis() - powerDownOverrideEnds) > 0) {
        powerDownOverride = false;
        if ((long)(millis() - powerDownTime) > 0) {
          poweredDown = true;
          motor->power(false);
          V(axisPrefix); VLF("driver powered down");
        }
      }
    }
  } else {
    if (poweredDown) {
      poweredDown = false;
      motor->power(true);
      V(axisPrefix); VLF("driver powered up");
    }
    powerDownTime = millis() + powerDownDelay;
  }

  if (frequency != 0.0F) {
    if (frequency < 0.0F) {
      if (maxFreq != 0.0F && frequency < -maxFreq) frequency = -maxFreq;
      if (minFreq != 0.0F && frequency > -minFreq) frequency = -minFreq;
    } else {
      if (minFreq != 0.0F && frequency < minFreq) frequency = minFreq;
      if (maxFreq != 0.0F && frequency > maxFreq) frequency = maxFreq;
    }
  }

  // apply base frequency as required
  if (enabled) {
    if (autoRate == AR_NONE) {
      motor->setFrequencySteps((frequency + baseFreq)*settings.stepsPerMeasure);
    } else {
      motor->setFrequencySteps(frequency*settings.stepsPerMeasure);
    }
  } else {
    motor->setFrequencySteps(0.0F);
  }
}

// get frequency in "measures" (degrees, microns, etc.) per second
float Axis::getFrequency() {
  return motor->getFrequencySteps()/settings.stepsPerMeasure;
}

// gets backlash frequency in "measures" (degrees, microns, etc.) per second
float Axis::getBacklashFrequency() {
  return settings.backlashFreq;
}

// get associated motor driver status
DriverStatus Axis::getStatus() {
  return motor->getDriverStatus();
}

void Axis::setMotionLimitsCheck(bool state) {
  limitsCheck = state;
}

// checks for an error that would disallow motion in a given direction or DIR_BOTH for any motion
bool Axis::motionError(Direction direction) {
  if (motor->getDriverStatus().fault) { V(axisPrefix); VLF("motion error driver fault"); return true; }

  if (direction == DIR_FORWARD || direction == DIR_BOTH) {
    bool result = getInstrumentCoordinateSteps() > lroundf(0.9F*INT32_MAX) ||
                  (limitsCheck && getInstrumentCoordinate() > settings.limits.max) ||
                  errors.maxLimitSensed;
    if (result == true) { V(axisPrefix); VLF("motion error forward limit"); }
    return result;
  } else

  if (direction == DIR_REVERSE || direction == DIR_BOTH) {
    bool result = getInstrumentCoordinateSteps() < lroundf(0.9F*INT32_MIN) ||
                  (limitsCheck && getInstrumentCoordinate() < settings.limits.min) ||
                  errors.minLimitSensed;
    if (result == true) { V(axisPrefix); VLF("motion error reverse limit"); }
    return result;
  }

  return false;
}

#endif