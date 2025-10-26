#ifndef CONTROLLERS_H
#define CONTROLLERS_H

#include <stddef.h>

// Funções de manipulação de dados no banco/arquivo (CRUD)
void create(const void*, size_t, const char*);
int read(void*, size_t, int (*match)(const void *), const char*);
void list_records(size_t size, void (*print)(const void *), int (*match)(const void *), const char*);
int update(const void*, size_t, int (*match)(const void *), const char*);
int delete(size_t, int (*match)(const void *), const char*);
int physical_delete(size_t, int (*match)(const void *), const char*);

#endif