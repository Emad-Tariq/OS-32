#ifndef USER_H
#define USER_H

void exit(void);
void yield(void);
void sleep(unsigned int ticks);
void write(const char *str);
int spawn(const char *filename);

#endif