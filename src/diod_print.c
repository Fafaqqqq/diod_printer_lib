#include "diod_private.h"

#include <string.h>

int32_t is_printing = 0;

int32_t diod_start_print(const char* user, MESSAGE_STATUS status, const char* str) {

  if (!diod_is_init())
    return -1;

  thread_ops.sem_wait(&sem_lock);  

  if (is_printing)
    return -1;

  diod_thread_args.buf[0] = status;

  int32_t msg_size = strlen(str);
  int32_t usr_size = strlen(user);

  strcpy(diod_thread_args.buf + 1, user);
  strcpy(diod_thread_args.buf + 10, str);

  diod_thread_args.msg_size = msg_size > 100 ? 100 : msg_size;
  diod_thread_args.usr_size = usr_size > 8 ? 8 : usr_size;

  thread_ops.sem_post(&sem_sign);

  is_printing = 1;

  thread_ops.sem_post(&sem_lock);
  return 0;
}

int32_t diod_stop_print() {
  if (!diod_is_init())
    return -1;

  thread_ops.sem_wait(&sem_lock);  
  
  if (!is_printing)
    return -1;

  thread_ops.sem_wait(&sem_sign);

  is_printing = 0;

  thread_ops.sem_post(&sem_lock);
  return 0;
}