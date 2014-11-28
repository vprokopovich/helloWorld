// Class include
#include "CTrace.h"

#ifdef OS_LINUX

// System includes
#include <sys/time.h> 
#include <stdio.h>  
#include <unistd.h>
#include <stdarg.h>

CTrace* CTrace::mpInstance = 0;

CTrace::CTrace(int level)
: mTraceLevel(level)
{
}

CTrace::~CTrace()
{
}

CTrace* CTrace::getInstance()
{
   if(0 == mpInstance)
   {
      mpInstance = new CTrace();
   }
   return mpInstance;
}

void CTrace::traceDebug(const char * format,...)
{
   if(mTraceLevel == TRC_LEVEL_DEBUG)
   {
      va_list ap;
      printf("[DEBUG]: ");
      //printf("\n\033[0;40;1;32m[DEBUG]\033[0m: ");    // Uncomment this to make debug messages highlighted with green
      va_start(ap,format);
      vprintf(format,ap);
      va_end(ap);
      printf("\n");
   }
}

void CTrace::traceWarning(const char * format,...)
{
   if(mTraceLevel >= TRC_LEVEL_WARNING)
   {
      va_list ap;
      printf("\033[0;40;1;33m[WARNING]\033[0m: ");
      va_start(ap,format);
      vprintf(format,ap);
      va_end(ap);
      printf("\n");
   }
}

void CTrace::traceError(const char * format,...)
{
   if(mTraceLevel >= TRC_LEVEL_ERROR)
   {
      va_list ap;
      printf("\033[0;40;1;31m[ERROR]\033[0m: ");
      va_start(ap,format);
      vprintf(format,ap);
      va_end(ap);
      printf("\n");
   }
}

void CTrace::setTraceLevel(int level)
{
   if (level < 0 || level > 3)
   {
      return;
   }

   mTraceLevel = level;
   
   if (level == 0)
   {
      printf("CTrace: Traces are off\n");
   }
   else if(level == 1)
   {
      printf("CTrace: Error message\n");
   }
   else if(level == 2)
   {
      printf("CTrace: Warning message\n");
   }
   else if(level == 3)
   {
      printf("CTrace: Debug message\n");
   }
}

int CTrace::getTraceLevel(void)
{
   return mTraceLevel;
}

double CTrace::beginTimeCount()
{
   double timeStamp = 0;
   struct timeval clockBegin;

   gettimeofday(&clockBegin, NULL);
   timeStamp = clockBegin.tv_sec + clockBegin.tv_usec / 1000000.0; // clocks per second = 1000000.0

   return timeStamp;
}

long CTrace::endTimeCount(double beginTime, const char * desc)
{
   struct timeval clockEnd; 
   double timeInterval = 0;

   if (0 != beginTime)
   {
      gettimeofday(&clockEnd, NULL);
      timeInterval = static_cast<double>(clockEnd.tv_sec+clockEnd.tv_usec/1000000.0 - beginTime); 
   }
   else
   {
      printf("CTrace: No begin time\n");
      return 0;
   }

   if (0 != desc)
   {
      printf("CTrace: [%s] executed duration is %f seconds\n", desc,timeInterval);
   }
   else
   {
      printf("CTrace: [%s] executed duration is %f seconds","No label\n", timeInterval);
   }
   
   return timeInterval;
}

#endif

#ifdef OS_WINDOWS
int someFunc()
{
    return 3;
}
#endif