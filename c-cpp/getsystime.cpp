#include <iostream>
#include <string>

#include <time.h>
#include <unistd.h>

using std::cout;
using std::endl;

/*
 * Clock_REALTIME

 * 代表机器上可以理解为当前的我们所常看的时间，其当time-of-day 被修改的时候而改变，
 * 这包括NTP对它的修改（NTP:Network Time Protocol（NTP）是用来使计算机时间同步化的一种协议，
 * 它可以使计算机对其服务器或时钟源（如石英钟，GPS等等)做同步化，它可以提供高精准度的时间校正
 * （LAN上与标准间差小于1毫秒，WAN上几十毫秒），且可介由加密确认的方式来防止恶毒的协议攻击。）
 * CLOCK_MONOTONIC
 * 代表从过去某个固定的时间点开始的绝对的逝去时间，它不受任何系统time-of-day时钟修改的影响，
 * 如果你想计算出在一台计算机上不受重启的影响，两个事件发生的间隔时间的话，那么它将是最好的选择。
 * */

timespec diff(timespec start, timespec end);

int main(int argc, const char* argv[]) {
   timespec time1, time2;

   clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time1);
   sleep(1);
   clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time2);
   cout << diff(time1, time2).tv_sec << "s "<< diff(time1, time2).tv_nsec << " nsec" << endl;

   clock_gettime(CLOCK_MONOTONIC, &time1);
   sleep(1);
   clock_gettime(CLOCK_MONOTONIC, &time2);
   cout << diff(time1, time2).tv_sec << "s "<< diff(time1, time2).tv_nsec << " nsec" << endl;

   clock_gettime(CLOCK_REALTIME, &time1);
   sleep(1);
   clock_gettime(CLOCK_REALTIME, &time2);
   cout << diff(time1, time2).tv_sec << "s "<< diff(time1, time2).tv_nsec << " nsec" << endl;

   return 0;
}

timespec diff(timespec start, timespec end) {
   timespec temp;
   if ((end.tv_nsec-start.tv_nsec)<0) {
      temp.tv_sec = end.tv_sec-start.tv_sec-1;
      temp.tv_nsec = 1000000000+end.tv_nsec-start.tv_nsec;
   } else {
      temp.tv_sec = end.tv_sec-start.tv_sec;
      temp.tv_nsec = end.tv_nsec-start.tv_nsec;
   }
   
   return temp;
}