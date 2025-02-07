
//--------------------------------------------------------------------------------------------------
// OnStepX focuser control

#include "Focuser.h"

#ifdef FOCUSER_PRESENT

#include "../../tasks/OnTask.h"

#include "../../lib/weather/Weather.h"
#include "../../lib/temperature/Temperature.h"
#include "../axis/Axis.h"
#include "../Telescope.h"

typedef struct FocuserConfiguration {
  bool present;
  uint16_t slewRateDesired;
  uint8_t  slewRateMinimum;
  uint8_t  accelerationTime;
  uint8_t  rapidStopTime;
  bool powerDown;
} FocuserConfiguration;

const FocuserConfiguration configuration[] = {
#if FOCUSER_MAX >= 1
  {AXIS4_DRIVER_MODEL != OFF, AXIS4_SLEW_RATE_DESIRED, AXIS4_SLEW_RATE_MINIMUM, AXIS4_ACCELERATION_TIME, AXIS4_RAPID_STOP_TIME, AXIS4_POWER_DOWN == ON},
#endif
#if FOCUSER_MAX >= 2
  {AXIS5_DRIVER_MODEL != OFF, AXIS5_SLEW_RATE_DESIRED, AXIS5_SLEW_RATE_MINIMUM, AXIS5_ACCELERATION_TIME, AXIS5_RAPID_STOP_TIME, AXIS5_POWER_DOWN == ON},
#endif
#if FOCUSER_MAX >= 3
  {AXIS6_DRIVER_MODEL != OFF, AXIS6_SLEW_RATE_DESIRED, AXIS6_SLEW_RATE_MINIMUM, AXIS6_ACCELERATION_TIME, AXIS6_RAPID_STOP_TIME, AXIS6_POWER_DOWN == ON},
#endif
#if FOCUSER_MAX >= 4
  {AXIS7_DRIVER_MODEL != OFF, AXIS7_SLEW_RATE_DESIRED, AXIS7_SLEW_RATE_MINIMUM, AXIS7_ACCELERATION_TIME, AXIS7_RAPID_STOP_TIME, AXIS7_POWER_DOWN == ON},
#endif
#if FOCUSER_MAX >= 5
  {AXIS8_DRIVER_MODEL != OFF, AXIS8_SLEW_RATE_DESIRED, AXIS8_SLEW_RATE_MINIMUM, AXIS8_ACCELERATION_TIME, AXIS8_RAPID_STOP_TIME, AXIS8_POWER_DOWN == ON},
#endif
#if FOCUSER_MAX >= 6
  {AXIS9_DRIVER_MODEL != OFF, AXIS9_SLEW_RATE_DESIRED, AXIS9_SLEW_RATE_MINIMUM, AXIS9_ACCELERATION_TIME, AXIS9_RAPID_STOP_TIME, AXIS9_POWER_DOWN == ON},
#endif
};

void focWrapper() { focuser.monitor(); }

// setup arrays for easy access to focuser axes
Axis *axes[6] = {NULL, NULL, NULL, NULL, NULL, NULL};

void Focuser::init() {
  // wait a moment for any background processing that may be needed
  delay(1000);

  #if AXIS4_DRIVER_MODEL != OFF
    axes[0] = &axis4;
  #endif
  #if AXIS5_DRIVER_MODEL != OFF
    axes[1] = &axis5;
  #endif
  #if AXIS6_DRIVER_MODEL != OFF
    axes[2] = &axis6;
  #endif
  #if AXIS7_DRIVER_MODEL != OFF
    axes[3] = &axis7;
  #endif
  #if AXIS8_DRIVER_MODEL != OFF
    axes[4] = &axis8;
  #endif
  #if AXIS9_DRIVER_MODEL != OFF
    axes[5] = &axis9;
  #endif

  // confirm the data structure size
  if (FocuserSettingsSize < sizeof(FocuserSettings)) { initError.nv = true; DL("ERR: Focuser::init(); FocuserSettingsSize error NV subsystem writes disabled"); nv.readOnly(true); }

  // init settings stored in NV
  if (!validKey) {
    for (int index = 0; index < FOCUSER_MAX; index++) {
      VF("MSG: Focuser"); V(index + 1); VLF(", writing default settings to NV");
      settings[index].tcf.enabled = false;
      settings[index].tcf.coef = 0.0F;
      settings[index].tcf.deadband = 1;
      settings[index].tcf.t0 = 0.0F;
      settings[index].parkState = PS_UNPARKED;
      settings[index].backlash = 0.0F;
      settings[index].position = 0.0F;
      writeSettings(index);
    }
  }

  // get settings
  for (int index = 0; index < FOCUSER_MAX; index++) {
    readSettings(index);

    // init. some defaults
    moveRate[index] = 100;
    tcfSteps[index] = 0;
    target[index] = 0;
    writeTime[index] = 0;
    parkHandle[index] = 0;

    if (configuration[index].present) {
      if (axes[index] != NULL) {

        if (active == -1) active = index;

        V("MSG: Focuser"); V(index + 1); V(", init (Axis"); V(index + 4); VL(")");
        axes[index]->init();

        // TCF defaults to disabled at startup
        settings[index].tcf.enabled = false;

        if (settings[index].position < axes[index]->settings.limits.min) {
          settings[index].position = axes[index]->settings.limits.min;
          initError.value = true;
          DLF("ERR, Focuser.init(): bad NV park pos < _LIMIT_MIN (set to _LIMIT_MIN)");
        }

        if (settings[index].position > axes[index]->settings.limits.max) {
          settings[index].position = axes[index]->settings.limits.max;
          initError.value = true;
          DLF("ERR, Focuser.init(): bad NV park pos > _LIMIT_MAX steps (set to _LIMIT_MAX)");
        }

        axes[index]->resetPositionSteps(0);
        axes[index]->setBacklashSteps(settings[index].backlash);
        axes[index]->setFrequencyMax(configuration[index].slewRateDesired);
        axes[index]->setFrequencyMin(configuration[index].slewRateMinimum);
        axes[index]->setFrequencySlew(configuration[index].slewRateDesired);
        axes[index]->setSlewAccelerationTime(configuration[index].accelerationTime);
        axes[index]->setSlewAccelerationTimeAbort(configuration[index].rapidStopTime);
        if (configuration[index].powerDown) axes[index]->setPowerDownTime(DEFAULT_POWER_DOWN_TIME);

        unpark(index);
      }
    }
  }

  // start task for temperature compensated focusing
  VF("MSG: Focusers, starting TCF task (rate 1s priority 6)... ");
  if (tasks.add(1000, 0, true, 6, focWrapper, "FocPoll")) { VL("success"); } else { VL("FAILED!"); }
}

// get focuser temperature in deg. C
float Focuser::getTemperature() {
  float t = temperature.getChannel(0);
  return t;
}

// check for DC motor focuser
bool Focuser::isDC(int index) {
  if (index < 0 || index >= FOCUSER_MAX) return false;
  return false;
}

// get DC power in %
int Focuser::getDcPower(int index) {
  if (index < 0 || index >= FOCUSER_MAX) return 0;
  return 0;
}

// set DC power in %
bool Focuser::setDcPower(int index, int value) {
  if (index < 0 || index >= FOCUSER_MAX) return false;
  if (value < 0 || value > 100) return false;
  return true;
}

// get TCF enable
bool Focuser::getTcfEnable(int index) {
  if (index < 0 || index >= FOCUSER_MAX) return false;
  return settings[index].tcf.enabled;
}

// set TCF enable
CommandError Focuser::setTcfEnable(int index, bool value) {
  if (index < 0 || index >= FOCUSER_MAX) return CE_CMD_UNKNOWN;
  if (settings[index].parkState >= PS_PARKED) return CE_PARKED;

  settings[index].tcf.enabled = value;
  if (value) {
    settings[index].tcf.t0 = getTemperature();
   } else {
     target[index] += tcfSteps[index];
     tcfSteps[index] = 0;
   }
  writeSettings(index);
  return CE_NONE;
}

// get TCF coefficient, in microns per deg. C
float Focuser::getTcfCoef(int index) {
  if (index < 0 || index >= FOCUSER_MAX) return 0.0F;
  return settings[index].tcf.coef;
}

// set TCF coefficient, in microns per deg. C
bool Focuser::setTcfCoef(int index, float value) {
  if (index < 0 || index >= FOCUSER_MAX) return false;
  if (abs(value) >= 1000.0F) return false;
  settings[index].tcf.coef = value;
  writeSettings(index);
  return true;
}

// get TCF deadband, in steps
int Focuser::getTcfDeadband(int index) {
  if (index < 0 || index >= FOCUSER_MAX) return 0;
  return settings[index].tcf.deadband;
}

// set TCF deadband, in steps
bool Focuser::setTcfDeadband(int index, int value) {
  if (index < 0 || index >= FOCUSER_MAX) return false;
  if (value < 1 || value > 10000) return false;
  settings[index].tcf.deadband = value;
  writeSettings(index);
  return true;
}

// get TCF T0, in deg. C
float Focuser::getTcfT0(int index) {
  if (index < 0 || index >= FOCUSER_MAX) return 0.0F;
  return settings[index].tcf.t0;
}

// set TCF T0, in deg. C
bool Focuser::setTcfT0(int index, float value) {
  if (index < 0 || index >= FOCUSER_MAX) return false;
  if (abs(value) > 60.0F) return false;
  settings[index].tcf.t0 = value;
  writeSettings(index);
  return true;
}

// get backlash in steps
int Focuser::getBacklash(int index) {
  if (index < 0 || index >= FOCUSER_MAX) return 0;
  return settings[index].backlash;
}

// set backlash in steps
CommandError Focuser::setBacklash(int index, int value) {
  if (index < 0 || index >= FOCUSER_MAX) return CE_CMD_UNKNOWN;
  if (value < 0 || value > 10000) return CE_PARAM_RANGE;
  if (settings[index].parkState >= PS_PARKED) return CE_PARKED;

  settings[index].backlash = value;
  writeSettings(index);
  axes[index]->setBacklash(getBacklash(index));
  return CE_NONE;
}

// start slew in the specified direction
CommandError Focuser::slew(int index, Direction dir) {
  if (index < 0 || index >= FOCUSER_MAX) return CE_CMD_UNKNOWN;
  if (axes[index] == NULL) return CE_PARAM_RANGE;
  if (settings[index].parkState >= PS_PARKED) return CE_PARKED;

  if (!axes[index]->isSlewing()) {
    axes[index]->setFrequencyBase(0.0F);
    axes[index]->resetTargetToMotorPosition();
  }
  return axes[index]->autoSlew(dir, moveRate[index]);
}

// move focuser to a specific location (in steps)
CommandError Focuser::gotoTarget(int index, long target) {
  if (index < 0 || index >= FOCUSER_MAX) return CE_CMD_UNKNOWN;
  if (axes[index] == NULL) return CE_PARAM_RANGE;
  if (settings[index].parkState >= PS_PARKED) return CE_PARKED;

  VF("MSG: Focuser"); V(index + 1); V(", goto target coordinate set ("); V(target/axes[index]->getStepsPerMeasure()); VL("um)");
  VF("MSG: Focuser"); V(index + 1); V(", starting goto at slew rate ("); V(configuration[index].slewRateDesired); VL("um/s)");

  axes[index]->setFrequencyBase(0.0F);
  axes[index]->setTargetCoordinateSteps(target + tcfSteps[index]);
  return axes[index]->autoSlewRateByDistance(configuration[index].slewRateDesired*configuration[index].accelerationTime, configuration[index].slewRateDesired);
}

// park focuser at its current location
CommandError Focuser::park(int index) {
  if (index < 0 || index >= FOCUSER_MAX)           return CE_PARAM_RANGE;
  if (axes[index] == NULL)                         return CE_NONE;
  if (settings[index].parkState == PS_PARKED)      return CE_NONE;
  if (settings[index].parkState == PS_PARKING)     return CE_PARK_FAILED;
  if (settings[index].parkState == PS_UNPARKING)   return CE_PARK_FAILED;
  if (settings[index].parkState == PS_PARK_FAILED) return CE_PARK_FAILED;

  setTcfEnable(index, false);

  VF("MSG: Focuser"); V(index + 1); VLF(", parking");
  axes[index]->setBacklash(0.0F);
  float targetMicrons = axes[index]->getInstrumentCoordinate();
  axes[index]->setTargetCoordinatePark(targetMicrons);

  CommandError e = axes[index]->autoSlewRateByDistance(configuration[index].slewRateDesired*configuration[index].accelerationTime, configuration[index].slewRateDesired);

  if (e == CE_NONE) {
    settings[index].position = targetMicrons;
    settings[index].parkState = PS_PARKING;
    writeSettings(index);
  }

  return e;
}

// unpark focuser
CommandError Focuser::unpark(int index) {
  if (index < 0 || index >= FOCUSER_MAX)           return CE_PARAM_RANGE;
  if (axes[index] == NULL)                         return CE_NONE;
  if (settings[index].parkState == PS_PARKING)     return CE_PARK_FAILED;
  if (settings[index].parkState == PS_UNPARKING)   return CE_PARK_FAILED;
  if (settings[index].parkState == PS_PARK_FAILED) return CE_PARK_FAILED;

  // setting write delay to 0 disables on-the-fly position writes and forces strict parking
  if (FOCUSER_WRITE_DELAY == 0) {
    if (settings[index].parkState != PS_PARKED) return CE_NOT_PARKED;
  }

  axes[index]->enable(true);
  V("MSG: Focuser"); V(index + 1); V(", unpark position "); V(settings[index].position); VL("um");

  // simple unpark if we didn't actually park
  if (settings[index].parkState == PS_UNPARKED) {
    axes[index]->setInstrumentCoordinate(settings[index].position);
    target[index] = lround(settings[index].position*axes[index]->getStepsPerMeasure()) - tcfSteps[index];
    writeSettings(index);
    return CE_NONE;
  }

  axes[index]->setBacklash(0.0F);
  axes[index]->setInstrumentCoordinatePark(settings[index].position);

  axes[index]->setBacklash(settings[index].backlash);
  axes[index]->setTargetCoordinate(settings[index].position);

  CommandError e = axes[index]->autoSlewRateByDistance(configuration[index].slewRateDesired*configuration[index].accelerationTime, configuration[index].slewRateDesired);

  if (e == CE_NONE) {
    settings[index].parkState = PS_UNPARKING;
    target[index] = lround(settings[index].position*axes[index]->getStepsPerMeasure()) - tcfSteps[index];
    writeSettings(index);
  }

  return e;
}

void Focuser::readSettings(int index) {
  nv.readBytes(NV_FOCUSER_SETTINGS_BASE + index*FocuserSettingsSize, &settings[index], sizeof(FocuserSettings));
  if (fabs(settings[index].tcf.coef) > 999.0F) { settings[index].tcf.coef = 0.0F;  initError.value = true; DLF("ERR, Focuser.init(): bad NV |tcf.coef| > 999.0 um/deg. C (set to 0.0)"); }
  if (settings[index].tcf.deadband < 1 )       { settings[index].tcf.deadband = 1; initError.value = true; DLF("ERR, Focuser.init(): bad NV tcf.deadband < 1 steps (set to 1)"); }
  if (settings[index].tcf.deadband > 10000 )   { settings[index].tcf.deadband = 1; initError.value = true; DLF("ERR, Focuser.init(): bad NV tcf.deadband > 10000 steps (set to 1)"); }
  if (fabs(settings[index].tcf.t0) > 60.0F)    { settings[index].tcf.t0 = 10.0F;   initError.value = true; DLF("ERR, Focuser.init(): bad NV |tcf.t0| > 60.0 deg. C (set to 10.0)"); }
  if (settings[index].backlash < 0)            { settings[index].backlash = 0;     initError.value = true; DLF("ERR, Focuser.init(): bad NV backlash < 0 steps (set to 0)"); }
  if (settings[index].backlash > 10000)        { settings[index].backlash = 0;     initError.value = true; DLF("ERR, Focuser.init(): bad NV backlash > 10000 steps (set to 0)"); }
}

void Focuser::writeSettings(int index) {
  nv.updateBytes(NV_FOCUSER_SETTINGS_BASE + index*FocuserSettingsSize, &settings[index], sizeof(FocuserSettings));
}

// poll focusers to handle parking and TCF
void Focuser::monitor() {
  secs++;

  float t = getTemperature();
  for (int index = 0; index < FOCUSER_MAX; index++) {
    if (axes[index] != NULL) {

      target[index] = axes[index]->getTargetCoordinateSteps() - tcfSteps[index];
      float targetMicrons = target[index]/axes[index]->getStepsPerMeasure();

      if (axes[index]->isSlewing() || settings[index].position == targetMicrons) writeTime[index] = secs + FOCUSER_WRITE_DELAY;

      if (!axes[index]->isSlewing()) {

        if (settings[index].parkState == PS_PARKING) {
          if (axes[index]->atTarget()) {
            axes[index]->enable(false);
            settings[index].parkState = PS_PARKED;
            writeSettings(index);
            #if DEBUG == VERBOSE
              long offset = axes[index]->getInstrumentCoordinateSteps() - axes[index]->getMotorPositionSteps();
              VF("MSG: Focuser"); V(index + 1); VF(", park motor target   "); VL(axes[index]->getTargetCoordinateSteps() - offset);
              VF("MSG: Focuser"); V(index + 1); VF(", park motor position "); VL(axes[index]->getMotorPositionSteps());
            #endif
          }
        } else

        if (settings[index].parkState == PS_UNPARKING) {
          if (axes[index]->atTarget()) {
            settings[index].parkState = PS_UNPARKED;
            writeSettings(index);
          }
        } else

        if (settings[index].parkState == PS_UNPARKED) {
          if (settings[index].tcf.enabled) {
            Y;
            if (!isnan(t)) {
              float offset = settings[index].tcf.coef * (settings[index].tcf.t0 - t);
              offset *= (float)axes[index]->getStepsPerMeasure();
              long steps = lroundf(offset/settings[index].tcf.deadband)*settings[index].tcf.deadband;
              if (tcfSteps[index] != steps) {
                VF("MSG: Focuser"); V(index + 1); V(", TCF offset changed moving to target "); 
                if (steps >= 0) { V("+ "); } else { V("- "); } V(fabs(steps/axes[index]->getStepsPerMeasure())); VL("um");
                tcfSteps[index] = steps;
                axes[index]->setTargetCoordinateSteps(target[index] + tcfSteps[index]);
              }
            }
            if (!axes[index]->atTarget()) {
              axes[index]->setSynchronized(false);
              axes[index]->setFrequencyBase(20.0F); // 20um/s
            } else {
              axes[index]->setFrequencyBase(0.0F);
            }
          } else tcfSteps[index] = 0;

          // delayed write of focuser position
          if (FOCUSER_WRITE_DELAY != 0) {
            if (secs > writeTime[index]) {
              settings[index].position = targetMicrons;
              writeSettings(index);
              VF("MSG: Focuser"); V(index + 1); V(", writing position ("); V(targetMicrons); VL("um) to NV"); 
            }
          }
        }
      }
    }
  }
}

Focuser focuser;

#endif
