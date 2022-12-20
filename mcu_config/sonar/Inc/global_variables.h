#ifndef _GLOBAL_VARIABLES_H__
#define _GLOBAL_VARIABLES_H__

#include "stm32l4xx_hal.h"
#include "stdbool.h"

inline void set_thereshold(int n)
{
    extern uint32_t thereshold;
    thereshold = n;
}
inline uint32_t get_thereshold(void)
{
    extern uint32_t thereshold;
    return thereshold;
}

inline void set_zero_cross(int n, uint8_t x)
{
    extern int zero_cross[3];
    zero_cross[x] = n;
}
inline int get_zero_cross(uint8_t x)
{
    extern int zero_cross[3];
    return zero_cross[x];
}

inline void set_pulse_count(int n)
{
    extern int pulse_count;
    pulse_count = n;
}
inline int get_pulse_count(void)
{
    extern int pulse_count;
    return pulse_count;
}

inline void set_pulse_width(int n)
{
    extern int pulse_width;
    pulse_width = n;
}
inline int get_pulse_width(void)
{
    extern int pulse_width;
    return pulse_width;
}

inline void set_wait_time(int n)
{
    extern int wait_time;
    wait_time = n;
}
inline int get_wait_time(void)
{
    extern int wait_time;
    return wait_time;
}

inline void set_timing_array(uint32_t n, uint8_t x, uint8_t y)
{
    extern uint32_t timing_array[][3];
    timing_array[x][y] = n;
}
inline uint32_t get_timing_array(uint8_t x, uint8_t y)
{
    extern uint32_t timing_array[][3];
    return timing_array[x][y];
}

inline void set_ready_to_send(bool n)
{
    extern int send_flag;
    send_flag = n;
}
inline bool get_ready_to_send(void)
{
    extern int send_flag;
    return send_flag;
}

#endif