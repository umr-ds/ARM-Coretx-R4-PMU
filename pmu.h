#ifndef PMU_H
#define PMU_H

void enable_performance_monitor(void);
void performance_monitor_start(void);
void performance_monitor_stop(void);
unsigned int performance_monitor_read_counter_0(void);
unsigned int performance_monitor_read_counter_1(void);
unsigned int performance_monitor_read_counter_2(void);
unsigned int performance_monitor_read_cycle_count(void);

#endif // PMU_H
