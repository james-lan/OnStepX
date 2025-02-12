//--------------------------------------------------------------------------------------------------
// telescope mount control
#pragma once

#include "../../../Common.h"

#ifdef MOUNT_PRESENT

#include "../Mount.h"

#if PEC_STEPS_PER_WORM_ROTATION == 0
  #define AXIS1_PEC OFF
#else
  #define AXIS1_PEC ON
#endif

enum PecState: uint8_t {PEC_NONE, PEC_READY_PLAY, PEC_PLAY, PEC_READY_RECORD, PEC_RECORD};

#pragma pack(1)
#define PecSettingsSize 6
typedef struct PecSettings {
  bool recorded:1;
  PecState state;
  long wormRotationSteps;
} PecSettings;
#pragma pack()

class Pec {
  public:
    void init();

    bool command(char *reply, char *command, char *parameter, bool *supressFrame, bool *numericReply, CommandError *commandError);

    void poll();

    // tracking rate (in x) due to PEC playing
    float rate = 0.0F;

  private:
    #if AXIS1_PEC == ON
      // disable PEC
      void disable();

      // applies low pass filter to smooth noise in PEC data and linear regression
      void cleanup();
    #endif
  
    float     stepsPerSiderealSecond    = 0.0F;
    int       stepsPerSiderealSecondI   = 0;
    float     stepsPerSiderealFrac      = 0.0F;
    long      bufferSize                = 0;      // in bytes
    #if AXIS1_PEC == ON
      uint8_t  monitorHandle            = 0;
      uint8_t  senseHandle              = 0;

      PecSettings settings = { false, PEC_NONE, PEC_STEPS_PER_WORM_ROTATION };

      bool     wormIndexState           = false;
      bool     wormIndexSenseThisSecond = false;
      long     wormRotationSteps        = 0;      // step position in worm rotation sequence
      long     wormSenseSteps           = 0;      // step position

      bool     firstRecording           = false;
      uint32_t recordStopTimeFs         = 0;
      uint32_t wormRotationStartTimeFs  = 0;      // start time of worm rotation sequence, in fracsecs or milliseconds
      long     wormRotationSeconds      = 0;      // time for a worm rotation, in seconds

      float    accGuideAxis1            = 0.0F;

      bool     bufferStart              = false;
      long     bufferIndex              = 0;      // index into the pec buffer
      int8_t*  buffer;
    #endif
};

extern Pec pec;

#endif
