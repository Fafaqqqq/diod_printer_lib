#include "diod_private.h"

#include <stddef.h>
#include <string.h>

thread_ops_t thread_ops;

int32_t (*diod_on)();
int32_t (*diod_off)();

sem_handle_t    sem_lock = NULL;
sem_handle_t    sem_sign = NULL;
thread_handle_t thread_h = NULL;

diod_thread_args_t diod_thread_args;

int32_t diod_printer_init_private(thread_ops_t* ops, int32_t (*on)(), int32_t (*off)()) {
  
  int32_t ret;

  memcpy(&thread_ops, ops, sizeof(thread_ops));

  diod_on = on;
  diod_off = off;
  
  ret = thread_ops.sem_create(&sem_lock, 1);
  if (0 != ret)
    return -1;

  ret = thread_ops.sem_create(&sem_sign, 0);
  if (0 != ret)
    return -1;

  ret = thread_ops.thread_create(&thread_h, &diod_thread, &diod_thread_args);
  if (0 != ret)
    return -1;

  return 0;
}

int32_t diod_printer_done_private() {
  int32_t ret;

  ret = thread_ops.thread_delete(&thread_h);
  if (0 != ret)
    return -1;

  ret = thread_ops.sem_delete(&sem_sign);
  if (0 != ret)
    return -1;

  ret = thread_ops.sem_delete(&sem_lock);
  if (0 != ret)
    return -1;

  return 0;
}

