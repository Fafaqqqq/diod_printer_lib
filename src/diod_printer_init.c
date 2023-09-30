#include "diod_private.h"

int32_t diod_init = 0; 

int32_t diod_printer_init(diod_printer_attrs* attrs) {
  if (!attrs)
    return -1;

  if (!attrs->diod_on  ||
      !attrs->diod_off ||
      !attrs->thread_ops.thread_create ||
      !attrs->thread_ops.thread_delete ||
      !attrs->thread_ops.sem_create ||
      !attrs->thread_ops.sem_delete ||
      !attrs->thread_ops.sem_wait ||
      !attrs->thread_ops.sem_post)
    return -1;

  int32_t ret = diod_printer_init_private(&attrs->thread_ops, attrs->diod_on, attrs->diod_off);

  if (0 != ret)
    return -1;

  diod_init = 1;

  return 0;
}

int32_t diod_printer_done() {
  if (!diod_init)
    return -1;

  return diod_printer_done_private();
}

int32_t diod_is_init() {
  return diod_init;
}

