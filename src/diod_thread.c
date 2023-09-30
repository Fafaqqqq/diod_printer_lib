#include "diod_private.h"

#include <stdio.h>
#include <string.h>

#define BITS_PER_NUM 8

static void _diod_print_bits(const char* buf, uint32_t start_bit, uint32_t stop_bit) {

  for (uint32_t i = start_bit; i <= stop_bit; i++) {
    uint32_t idx = i / BITS_PER_NUM;
    uint8_t num = buf[idx];
    uint8_t bit_num = 7 - (i % BITS_PER_NUM);
    uint8_t bit = (num & (1 << bit_num)) >> bit_num;
    
    if (bit)
      diod_on();
    else
      diod_off();
    
    thread_ops.thread_sleep(40);
  }
}

static void _diod_print_str(const char* str) {
  
  int32_t len = strlen(str);

  for (uint32_t i = 0; i < len; i++) {
    uint8_t ch = str[i];
    uint8_t bits = 8;
    
    for (uint32_t j = 0; j < bits; j++) {
      uint8_t bit = (ch & 0x80) >> 7;
      ch <<= 1;

      if (bit)
        diod_on();
      else
        diod_off();

      thread_ops.thread_sleep(40);
    }
  }
}

void diod_thread(void * args) {
  diod_thread_args_t* diod_args = (diod_thread_args_t*)args;

  while (1) {
    thread_ops.sem_wait(&sem_sign);
    _diod_print_bits(diod_args->buf, 6, 7);
    _diod_print_bits(diod_args->buf, 8, 8 * (diod_args->usr_size + 1));
    _diod_print_bits(diod_args->buf, 80, 8 * (diod_args->msg_size) + 80);
    
    thread_ops.sem_post(&sem_sign);
    thread_ops.thread_sleep(120);
  }
}