//--------------------------------------------------------------------------------------------------
// telescope mount control
#pragma once

#include "../../../Common.h"

#ifdef MOUNT_PRESENT

#include "../guide/Guide.h"

#pragma pack(1)
typedef struct AltitudeLimits {
  float min;
  float max;
} AltitudeLimits;

#define LimitSettingsSize 16
typedef struct LimitSettings {
  AltitudeLimits altitude;
  float pastMeridianE;
  float pastMeridianW;
} LimitSettings;
#pragma pack()

typedef struct MerdianError {
  uint8_t east;
  uint8_t west;
} MerdianError;

typedef struct MinMaxError {
  uint8_t min;
  uint8_t max;
} MinMaxError;

typedef struct AxisError {
  MinMaxError axis1;
  MinMaxError axis2;
} AxisError;

typedef struct LimitsError {
  MinMaxError   altitude;
  AxisError     limit;
  AxisError     limitSense;
  MerdianError  meridian;
  bool          motorFault;
} LimitsError;

class Limits {
  public:
    void init();

    bool command(char *reply, char *command, char *parameter, bool *supressFrame, bool *numericReply, CommandError *commandError);

    // constrain meridian limits to the allowed range
    void constrainMeridianLimits();

    // target coordinate check ahead of sync, goto, etc.
    CommandError validateCoords(Coordinate *coords);

    // true if an limit related error is exists
    bool isError();

    // return general error code
    uint8_t errorCode();

    // enable or disable limit enforcement
    inline void enabled(bool state) { limitsEnabled = state; }

    // check if limits are being enforced
    inline bool isEnabled() { return limitsEnabled; }

    void poll();

    LimitSettings settings = { { degToRadF(-10.0F), degToRadF(85.0F) }, degToRadF(15.0F), degToRadF(15.0F) };

  private:
    void stop(GuideAction stopDirection);
    void stopAxis1(GuideAction stopDirection);
    void stopAxis2(GuideAction stopDirection);

    bool limitsEnabled = false;
    LimitsError error;
};

extern Limits limits;

#endif
