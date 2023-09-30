#include "diod_printer.h"

#include <stdlib.h>

#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

static int32_t _diod_default_create_thread(thread_handle_t* handle, thread_func_t func, thread_attr_t attr) {
  if (!func || !handle)
    return -1;

  pthread_t thread_h;
  pthread_attr_t threasd_attr;

  pthread_attr_init(&threasd_attr);

  pthread_create(&thread_h, &threasd_attr, (void *(*)(void *))func, attr);

  *handle = (thread_handle_t)thread_h;

  return 0;
}

static int32_t _diod_default_delete_thread(thread_handle_t* handle) {
  if (!handle)
    return -1;
  pthread_t thread_h = (pthread_t)*handle;

  return pthread_cancel(thread_h);
}

static void _diod_default_sleep(uint32_t milliseconds) {
  usleep(1000 * milliseconds);
}

static int32_t _diod_default_create_sem(sem_handle_t* sem, int32_t state) {
  if (!sem)
    return -1;

  sem_t* sem_handle = (sem_t*)malloc(sizeof(*sem_handle));

  if (!sem_handle)
    return -1;

  if (0 != sem_init(sem_handle, 0, state)) {
    free(sem_handle);
    return -1;
  }

  *sem = sem_handle;

  return 0; 
}

static int32_t _diod_default_delete_sem(sem_handle_t* sem) {
  if (!sem || !*sem)
    return -1;

  sem_t* sem_handle = (sem_t*)*sem;

  if (0 != sem_destroy(sem_handle)) {
    return -1;
  }

  free(sem_handle);

  *sem = NULL;

  return 0; 
}

static int32_t _diod_default_wait_sem(const sem_handle_t* sem) {
  if (!sem || !*sem)
    return -1;

  sem_t* sem_handle = (sem_t*)*sem;
  
  return sem_wait(sem_handle); 
}

static int32_t _diod_default_post_sem(const sem_handle_t* sem) {
  if (!sem || !*sem)
    return -1;

  sem_t* sem_handle = (sem_t*)*sem;

  return sem_post(sem_handle); 
}

static int32_t _diod_default_on() {return 0;}
static int32_t _diod_default_off() {return 0;}

int32_t diod_printer_get_default_attrs(diod_printer_attrs* attrs) {
  if (!attrs) 
    return -1;

  attrs->diod_on  = &_diod_default_on;
  attrs->diod_off = &_diod_default_off;
  attrs->thread_ops.thread_create = &_diod_default_create_thread;
  attrs->thread_ops.thread_delete = &_diod_default_delete_thread;
  attrs->thread_ops.thread_sleep  = &_diod_default_sleep;
  attrs->thread_ops.sem_create = &_diod_default_create_sem;
  attrs->thread_ops.sem_delete = &_diod_default_delete_sem;
  attrs->thread_ops.sem_wait = &_diod_default_wait_sem;
  attrs->thread_ops.sem_post = &_diod_default_post_sem;

 return 0; 
}
