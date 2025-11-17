#ifndef CONTROLLERS_H
#define CONTROLLERS_H

#include <stddef.h>

// Funções de manipulação de dados no banco/arquivo (CRUD)
int create(const void*, size_t, const char*);
int read_data(void*, size_t, const char*, int (*match)(const void *));
void list_records(size_t size, void (*print)(const void *), int (*match)(const void *), const char*);
int update(const void*, size_t, const char*, int (*match)(const void *));
int delete(size_t, const char*, int (*match)(const void *));
int physical_delete(size_t, int (*match)(const void *), const char*);

#endif