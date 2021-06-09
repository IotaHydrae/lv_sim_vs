#include "utils.h"

//-----------------------------------------------------------------------------
//      @Function   :  Name of function
//      @Description:  Just description for function
//      @Input      :  Param inputs
//      @Output     :  Function output
//      @Returns    :  Result
//      @Others     :  Others info for this function
//-----------------------------------------------------------------------------
void FLT_get_time_now(ptime_s time) 
{
    #ifdef PLATFORM_WINDOWS
    SYSTEMTIME sys = {0}; 
    GetLocalTime( &sys ); 
    time->hour = sys.wHour;
    time->minute = sys.wMinute;
    time->second = sys.wSecond;

    #elif defined(PLATFORM_LINUX)

    #endif
    
}

void FLT_get_time_elapsed(ptime_s time)
{
    time->second+=1;
    if(time->second == 60){
        time->second=0;
        time->minute+=1;
    }

    if(time->minute == 60){
        time->minute=0;
        time->hour+=1;
    }

    if(time->hour == 24){
        time->hour=0;
    }
}

inline void FLT_taskkill(lv_task_t *task)
{
    lv_task_del(task);
}

inline void FLT_taskkill_all(void)
{

}
