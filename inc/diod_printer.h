#ifndef DIOD_PRINTER_H
#define DIOD_PRINTER_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef void* thread_handle_t;
typedef void* thread_attr_t;
typedef void* sem_handle_t;
typedef void (*thread_func_t)(thread_attr_t);

typedef struct {
  int32_t (*thread_create)(thread_handle_t*, thread_func_t, thread_attr_t);
  int32_t (*thread_delete)(thread_handle_t*);
  void    (*thread_sleep)(uint32_t);
  int32_t (*sem_create)(sem_handle_t*, int32_t);
  int32_t (*sem_delete)(sem_handle_t*);
  int32_t (*sem_wait)(const sem_handle_t*);
  int32_t (*sem_post)(const sem_handle_t*);
} thread_ops_t;

typedef struct {
  thread_ops_t thread_ops;
  int32_t (*diod_on)();
  int32_t (*diod_off)();
} diod_printer_attrs;

typedef enum MESSAGE_STATUS {
  MESSAGE_OK,
  MESSAGE_WARNING,
  MESSAGE_ERROR,
} MESSAGE_STATUS;

int32_t diod_printer_get_default_attrs(diod_printer_attrs* attrs);

int32_t diod_printer_init(diod_printer_attrs*);
int32_t diod_printer_done();

int32_t diod_start_print_fmt(const char* user, MESSAGE_STATUS status, const char* format, ...);
int32_t diod_start_print(const char* user, MESSAGE_STATUS status, const char* str);
int32_t diod_stop_print();

#ifdef __cplusplus
}
#endif

#endif // !DIOD_PRINTER_H
