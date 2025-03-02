/*
 * Title       OnStepX
 * by          Howard Dutton
 *
 * Copyright (C) 2021 Howard Dutton
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Description:
 *   Full featured telescope control for
 *   Equatorial and Alt-Az mounts
 *   Rotator
 *   Focusers
 *   Accessories (automatic covers, dew heaters, etc.)
 *
 * Author: Howard Dutton
 *   http://www.stellarjourney.com
 *   hjd1964@gmail.com
 *
 * Revision history, and newer versions:
 *   See GitHub: https://github.com/hjd1964/OnStep
 *
 * Documentation:
 *   https://groups.io/g/onstep/wiki/home
 *
 * Discussion, Questions, ...etc
 *   https://groups.io/g/onstep
 */

// Use tabs "Config..." to configure OnStep to your requirements

// Firmware version ----------------------------------------------------------------------------------------------------------------
#define FirmwareName                "On-Step"
#define FirmwareVersionMajor        10
#define FirmwareVersionMinor        03     // minor version 00 to 99
#define FirmwareVersionPatch        "k"    // for example major.minor patch: 10.03c
#define FirmwareVersionConfig       1      // internal, for tracking configuration file changes

#include "src/Common.h"
NVS nv;
#include "src/lib/sense/Sense.h"
#include "src/tasks/OnTask.h"

#include "src/telescope/Telescope.h"
extern Telescope telescope;

#if DEBUG == PROFILER
  extern void profiler();
#endif

#if DEBUG == CONSOLE
  extern void debugConsole();
#endif

void systemServices() {
  nv.poll();
}

void sensesPoll() {
  senses.poll();
}

void setup() {
  #if DEBUG != OFF
    SERIAL_DEBUG.begin(SERIAL_DEBUG_BAUD);
    delay(2000);
  #endif

  // start low level hardware
  VLF("MSG: Setup, HAL initalize");
  HAL_INIT();
  delay(2000);

  // start system service task
  VF("MSG: Setup, start system service task (rate 10ms priority 7)... ");
  // add task for system services, runs at 10ms intervals so commiting 1KB of NV takes about 10 seconds
  // the cache is scanned (for writing) at 2000 bytes/second but can be slower while reading data into the cache at startup
  if (tasks.add(10, 0, true, 7, systemServices, "SysSvcs")) { VL("success"); } else { VL("FAILED!"); }

  // start input sense polling task
  VF("MSG: Setup, start input sense polling task (rate 1ms priority 7)... ");
  if (tasks.add(1, 0, true, 7, sensesPoll, "SenPoll")) { VL("success"); } else { VL("FAILED!"); }

  // start telescope object
  telescope.init(FirmwareName, FirmwareVersionMajor, FirmwareVersionMinor, FirmwareVersionPatch, FirmwareVersionConfig);

  // start command channel tasks
  commandChannelInit();

  tasks.yield(2000);

  // start task manager debug events
  #if DEBUG == PROFILER
    tasks.add(142, 0, true, 7, profiler, "Profilr");
  #endif
  #if DEBUG == CONSOLE
    tasks.add(1000, 0, true, 7, debugConsole);
  #endif
}

void loop() {
  tasks.yield();
}
