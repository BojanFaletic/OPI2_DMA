#include "DMA.hpp"
#include <pthread.h>

#define SCHED_PRIORITY 30 // Linux scheduler priority. Higher = more realtime

int main() {
  DMA<3> d1;

  // increese priority
  struct sched_param sp;
  sp.sched_priority = SCHED_PRIORITY;
  int ret = pthread_setschedparam(pthread_self(), SCHED_FIFO, &sp);
  if (ret) {
    printf("Warning: pthread_setschedparam (increase thread priority) returned "
           "non-zero: %i\n",
           ret);
  }

  d1.test();
}