// -----------------------------------------------------------------------------------
// Local Serial for sending commands internal to OnStepX
#include "Serial_Local.h"

void SerialLocal::begin(long baud) {
  // init the buffers
  xmit_index = 0; xmit_buffer[0] = 0; recv_head = 0; recv_tail = 0; recv_buffer[0] = 0;
  (void)(baud);
}

void SerialLocal::end() { }

void SerialLocal::transmit(const char *data) {
  int data_len = strlen(data);
  for (int i = 0; i < data_len; i++) {
    recv_buffer[recv_tail] = data[i];
    recv_tail++;
  }
}

char *SerialLocal::recv() {
  int i = 0;
  xmit_result[i] = 0;
  while (xmit_buffer[xmit_index] != 0) {
    xmit_result[i++] = xmit_buffer[xmit_index++];
    xmit_index &= 0b111111;
  }
  return xmit_result;
}

int SerialLocal::read(void) {
  if (!available()) return -1;
  recv_buffer[recv_tail] = 0;
  char c = recv_buffer[recv_head];
  if (c) recv_head++;
  return c;
}

SerialLocal serialLocal;
