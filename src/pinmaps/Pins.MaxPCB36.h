// -------------------------------------------------------------------------------------------------
// Pin map for OnStep MaxPCB 3.6 Teensy4.1 PCB
#pragma once

// clue that the direction pins are shared so we can set direction early before each step
#define SHARED_DIRECTION_PINS

#if defined(ARDUINO_TEENSY41)

// Serial ports (see Pins.defaults.h for SERIAL_A)
// Serial1: RX1 Pin 0, TX1 Pin 1
// Serial2: RX4 Pin 7, TX4 Pin 8

#if SERIAL_B_BAUD_DEFAULT != OFF
  #define SERIAL_B              Serial1
#endif
#if SERIAL_C_BAUD_DEFAULT != OFF
  #define SERIAL_C              Serial2
#endif
#if defined(USB_DUAL_SERIAL) || defined(USB_TRIPLE_SERIAL)
  #define SERIAL_D              SerialUSB1
  #define SERIAL_D_BAUD_DEFAULT 9600
#endif
#if defined(USB_TRIPLE_SERIAL)
  #define SERIAL_E              SerialUSB2
  #define SERIAL_E_BAUD_DEFAULT 9600
#endif

// The multi-purpose pins (Aux3..Aux8 can be analog pwm/dac if supported)
#define AUX0_PIN               23               // Status LED
#define AUX2_PIN               20               // PPS
#define AUX3_PIN               21               // Home SW
#define AUX4_PIN               22               // 1-Wire, Home SW
#define AUX5_PIN               1                // TX1 
#define AUX6_PIN               0                // RX1
#define AUX7_PIN               9                // Limit SW
#define AUX8_PIN               10               // Status2 LED, Reticle LED

// Misc. pins
#ifndef ONE_WIRE_PIN
  #define ONE_WIRE_PIN         AUX4_PIN         // Default Pin for OneWire bus (note: this pin has a 0.1uF capacitor that must be removed for OneWire to function)
#endif
#define ADDON_GPIO0_PIN        OFF              // ESP8266 GPIO0 (shared with AXIS2_DIR_PIN)
#define ADDON_RESET_PIN        OFF              // ESP8266 RST

// The PEC index sense is a logic level input, resets the PEC index on rising edge then waits for 60 seconds before allowing another reset
#define PEC_SENSE_PIN          2                // PEC Sense, analog or digital

// The status LED is a two wire jumper with a 10k resistor in series to limit the current to the LED
#define STATUS_LED_PIN         AUX0_PIN         // Default LED Cathode (-)
#define STATUS_MOUNT_LED_PIN   AUX0_PIN         // Default LED Cathode (-)
#define STATUS_ROTATOR_LED_PIN AUX0_PIN         // Default LED Cathode (-)
#define STATUS_FOCUSER_LED_PIN AUX0_PIN         // Default LED Cathode (-)
#define RETICLE_LED_PIN        AUX8_PIN         // Default LED Cathode (-)

// For a piezo buzzer
#define STATUS_BUZZER_PIN      17               // Tone

// The PPS pin is a 3.3V logic input, OnStep measures time between rising edges and adjusts the internal sidereal clock frequency
#ifdef MAXSTM_AUX0_PPS
  #define SENSE_PPS_PIN        AUX0_PIN         // PPS time source, GPS for example (MaxSTM version 3.6)
#else
  #define SENSE_PPS_PIN        AUX2_PIN         // PPS time source, GPS for example (MaxSTM version 3.61 and later)
#endif

// The limit switch sense is a logic level input normally pull high (2k resistor,) shorted to ground it stops gotos/tracking
#define SENSE_LIMIT_PIN        AUX7_PIN

// Axis1 RA/Azm step/dir driver
#define AXIS1_ENABLE_PIN       33
#define AXIS1_M0_PIN           34               // SPI MOSI
#define AXIS1_M1_PIN           35               // SPI SCK
#define AXIS1_M2_PIN           36               // SPI CS
#define AXIS1_M3_PIN           37               // SPI MISO
#define AXIS1_STEP_PIN         38
#define AXIS1_DIR_PIN          39
#define AXIS1_DECAY_PIN        AXIS1_M2_PIN
#define AXIS1_SENSE_HOME_PIN   AUX3_PIN

// Axis2 Dec/Alt step/dir driver
#define AXIS2_ENABLE_PIN       40
#define AXIS2_M0_PIN           41               // SPI MOSI
#define AXIS2_M1_PIN           13               // SPI SCK
#define AXIS2_M2_PIN           14               // SPI CS
#define AXIS2_M3_PIN           37               // SPI MISO
#define AXIS2_STEP_PIN         15
#define AXIS2_DIR_PIN          16
#define AXIS2_DECAY_PIN        AXIS2_M2_PIN
#define AXIS2_SENSE_HOME_PIN   AUX4_PIN

// For rotator stepper driver
#define AXIS3_ENABLE_PIN       11
#define AXIS3_M0_PIN           12               // SPI MOSI
#define AXIS3_M1_PIN           24               // SPI SCK
#define AXIS3_M2_PIN           25               // SPI CS
#define AXIS3_M3_PIN           37               // SPI MISO
#define AXIS3_STEP_PIN         26
#define AXIS3_DIR_PIN          27
#define AXIS3_DECAY_PIN        AXIS3_M2_PIN

// For focuser1 stepper driver
#define AXIS4_ENABLE_PIN       28
#define AXIS4_M0_PIN           29               // SPI MOSI
#define AXIS4_M1_PIN           30               // SPI SCK
#define AXIS4_M2_PIN           31               // SPI CS
#define AXIS4_M3_PIN           37               // SPI MISO
#define AXIS4_STEP_PIN         32
#define AXIS4_DIR_PIN          27
#define AXIS4_DECAY_PIN        AXIS4_M2_PIN

// For focuser2 stepper driver
#define AXIS5_ENABLE_PIN       11
#define AXIS5_M0_PIN           12               // SPI MOSI
#define AXIS5_M1_PIN           24               // SPI SCK
#define AXIS5_M2_PIN           25               // SPI CS
#define AXIS5_M3_PIN           37               // SPI MISO
#define AXIS5_STEP_PIN         26
#define AXIS5_DIR_PIN          27
#define AXIS5_DECAY_PIN        AXIS5_M2_PIN

// ST4 interface
#define ST4_RA_W_PIN           3                // ST4 RA- West
#define ST4_DEC_S_PIN          4                // ST4 DE- South
#define ST4_DEC_N_PIN          5                // ST4 DE+ North
#define ST4_RA_E_PIN           6                // ST4 RA+ East

#else
#error "Wrong processor for this configuration!"

#endif
