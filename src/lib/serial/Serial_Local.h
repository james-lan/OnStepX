// -----------------------------------------------------------------------------------
// Local Serial for sending commands internal to OnStepX
#pragma once

#include "Arduino.h"

class SerialLocal : public Stream {
  public:
    inline void begin() { begin(9600); }
    void begin(long baud);
    void end();

    void transmit(const char *data);
    char *recv();

    int read(void);

    inline int available(void) { 
      uint8_t p = recv_head;
      uint8_t c = 0;
      while (recv_buffer[p] && p != recv_tail && c < 255) { c++; p++; }
      return c;
    }

    inline int peek(void) { if (!available()) return -1; char c = recv_buffer[recv_head]; return c; }

    inline void flush(void) { }

    inline size_t write(uint8_t data) {
      if (xmit_tail == xmit_index) return 0; 
      xmit_buffer[xmit_tail] = data;
      xmit_tail++; xmit_tail &= 0b111111;
      xmit_buffer[xmit_tail] = 0;
      return 1;
    }
    size_t write(const uint8_t* data, size_t count) {
      for (int i = 0; i < (int)count; i++) { if (!write(data[i])) return i; }
      return count;
    }
    inline size_t write(unsigned long n) { return write((uint8_t)n); }
    inline size_t write(long n) { return write((uint8_t)n); }
    inline size_t write(unsigned int n) { return write((uint8_t)n); }
    inline size_t write(int n) { return write((uint8_t)n); }

    using Print::write;

    char recv_buffer[256] = "";
    uint8_t recv_head = 0;
    uint8_t recv_tail = 0;

  protected:
    char xmit_buffer[64] = "";
    char xmit_result[64] = "";
    uint8_t xmit_index = 0;
    uint8_t xmit_tail = 0;
};

extern SerialLocal serialLocal;
#define SERIAL_LOCAL serialLocal
