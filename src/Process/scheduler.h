#ifndef SCHEDULER_H
#define SCHEDULER_H

extern volatile unsigned int system_ticks;

void scheduler_init();
int schedule();
void update();
void process_sleep(unsigned int ticks);

#endif