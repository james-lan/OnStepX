// -------------------------------------------------------------------------------------------------
// Loads pinmap model for current configuration
#pragma once

#if PINMAP == Classic
  #define PINMAP_STR "Classic"
  #include "Pins.Classic.h"
#endif
#if PINMAP == ClassicShield
  #define PINMAP_STR "Classic (Steve's Shield)"
  #include "Pins.Classic.h"
#endif
#if PINMAP == MiniPCB
  #define PINMAP_STR "MiniPCB v1"
  #include "Pins.MiniPCB.h"
#endif
#if PINMAP == MiniPCB13
  #define PINMAP_STR "MiniPCB v1.3"
  #include "Pins.MiniPCB.h"
#endif
#if PINMAP == MiniPCB2
  #define PINMAP_STR "MiniPCB v2"
  #include "Pins.MiniPCB.h"
#endif
#if PINMAP == MaxPCB
  #define PINMAP_STR "MaxPCB v1"
  #include "Pins.MaxPCB.h"
#endif
#if PINMAP == MaxPCB2
  #define PINMAP_STR "MaxPCB v2"
  #include "Pins.MaxPCB.h"
#endif
#if PINMAP == MaxPCB3
  #ifdef ARDUINO_TEENSY41
    #define PINMAP_STR "MaxPCB v3.6"
    #include "Pins.MaxPCB36.h"
  #else
    #define PINMAP_STR "MaxPCB v3"
    #include "Pins.MaxPCB3.h"
  #endif
#endif
#if PINMAP == MaxESP2
  #define PINMAP_STR "MaxESP v2"
  #include "Pins.MaxESP2.h"
#endif
#if PINMAP == MaxESP3
  #define PINMAP_STR "MaxESP v3"
  #include "Pins.MaxESP3.h"
#endif
#if PINMAP == UNO
  #define PINMAP_STR "UNO W/CNC v3"
  #include "Pins.UNO.h"
#endif
#if PINMAP == CNC3
  #define PINMAP_STR "CNC v3"
  #include "Pins.CNC3.h"
#endif
#if PINMAP == Ramps14
  #define PINMAP_STR "RAMPS v1.4"
  #include "Pins.Ramps14.h"
#endif
#if PINMAP == MksGenL1
  #define PINMAP_STR "MKS Gen-L v1"
  #include "Pins.Ramps14.h"
#endif
#if PINMAP == MksGenL2
  #define PINMAP_STR "MKS Gen-L v2"
  #include "Pins.Ramps14.h"
#endif
#if PINMAP == MksGenL21
  #define PINMAP_STR "MKS Gen-L v2.1"
  #include "Pins.Ramps14.h"
#endif
#if PINMAP == STM32Blue
  #define PINMAP_STR "STM32 Bluepill"
  #include "Pins.STM32B.h"
#endif
#if PINMAP == FYSETC_S6
  #define PINMAP_STR "FYSETC S6"
  #include "Pins.FYSETC_S6.h"
#endif
#if PINMAP == FYSETC_S6_2
  #define PINMAP_STR "FYSETC S6 v2"
  #include "Pins.FYSETC_S6.h"
#endif
#if PINMAP == MaxSTM3 || PINMAP == MaxSTM3I
  #define PINMAP_STR "MaxSTM v3"
  #include "Pins.MaxSTM.h"
#endif
#if PINMAP == ClassicInstein
  #define PINMAP_STR "Classic (Instein)"
  #include "Pins.Classic.h"
#endif
#if PINMAP == InsteinESP1
  #define PINMAP_STR "Instein (ESP32)"
  #include "Pins.InsteinESP1.h"
#endif

// all unassigned pins OFF
#include "../pinmaps/Pins.defaults.h"

#include "Validate.h"