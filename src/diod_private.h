#ifndef DIOD_PRIVATE_H
#define DIOD_PRIVATE_H

#include "diod_printer.h"

typedef struct {
  char  buf[110];
  uint32_t msg_size;
  uint32_t usr_size;
} diod_thread_args_t;

extern thread_ops_t thread_ops;
extern int32_t (*diod_on)();
extern int32_t (*diod_off)();

extern thread_handle_t thread_h;
extern sem_handle_t sem_sign;
extern sem_handle_t sem_lock;

extern diod_thread_args_t diod_thread_args;

int32_t diod_printer_init_private(thread_ops_t* ops, int32_t (*on)(), int32_t (*off)());
int32_t diod_printer_done_private();

void diod_thread(void*);

int32_t diod_is_init();

#endif //!DIOD_PRIVATE_H