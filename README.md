# ARM Coretx R4 PMU Helper
A file containing some helpers to enable/disbale the and interact with the

## Intro
The ARM Cortex R4 has a Performance Management Unit (PMU) which can monitor various metrics like cache misses or CPU cycle counts.
This file contains helpers to use the PMU easily.
For more information, see [the official ARM documentation](http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.ddi0363e/CHDCBAAH.html).

## Usage
First, you have to enable the PMU on your CPU.
After that, you have to start the PMU and stop it again after the code to be measured.
Finally, you can read all registers.

```C
unsigned int counter_0;
unsigned int counter_1;
unsigned int counter_2;
unsigned int cycle_count;

enable_performance_monitor();
performance_monitor_start();

// CODE TO BE MEASURED

performance_monitor_stop();

counter_0 = performance_monitor_read_counter_0();
counter_1 = performance_monitor_read_counter_1();
counter_2 = performance_monitor_read_counter_2();
cycle_count = performance_monitor_read_cycle_count();
```

## Advanced usage
The Cortex R4 has a dedicated register for CPU cycle count.
Additionally, it has three registers, which can monitor various counters.
By default in this repo, `count_0` counts the number instruction cache miss (`0x01`), `count_1` counts the numebr data cache misses (`0x03`) and `count_2` counts the instructions architecturally executed (`0x08`).
However, the CPU has [a lot more counters](http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.ddi0363e/CHDCBAAH.html), which can be used.
You can set them in `pmu.c` in lines [28](https://github.com/umr-ds/ARM-Coretx-R4-PMU/blob/89be46ec4dd4a812b63a8397c1f94e264f736e0a/pmu.c#L28), [33](https://github.com/umr-ds/ARM-Coretx-R4-PMU/blob/89be46ec4dd4a812b63a8397c1f94e264f736e0a/pmu.c#L33) and [38](https://github.com/umr-ds/ARM-Coretx-R4-PMU/blob/89be46ec4dd4a812b63a8397c1f94e264f736e0a/pmu.c#L38).
