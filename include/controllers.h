#ifndef CONTROLLERS_H
#define CONTROLLERS_H
    
void create(const void*, size_t);
int read(void*, size_t, int (*match)(const void *));
int update(const void*, size_t, int (*match)(const void *));
int delete(size_t, int (*match)(const void *));

#endif