#ifndef __RTC_H__
#define __RTC_H__

#if defined __SDCC
#   include <gbdk/platform.h>
#   pragma disable_warning 126
#else /* __SDCC */
#   error "Not implemented."
#endif /* __SDCC */

#define RAM_BANKS_ONLY    0x0F

#define RTC_TIMER_STOP    0b01000000

#define RTC_VALUE_SEC     0x08
#define RTC_VALUE_MIN     0x09
#define RTC_VALUE_HOUR    0x0A
#define RTC_VALUE_DAY     0x0B
#define RTC_VALUE_FLAGS   0x0C

volatile UINT8 AT(0x4000) RTC_SELECT_REG;
volatile UINT8 AT(0x6000) RTC_LATCH_REG;
volatile UINT8 AT(0xA000) RTC_VALUE_REG;

inline void rtc_select(UINT8 what) {
    SWITCH_RAM(what & RAM_BANKS_ONLY);
}

inline void rtc_start(UINT8 start) {
    rtc_select(RTC_VALUE_FLAGS);
    if (start)
        RTC_VALUE_REG &= ~RTC_TIMER_STOP;
    else
        RTC_VALUE_REG |= RTC_TIMER_STOP;
}
inline void rtc_latch(void) {
    RTC_LATCH_REG = 0;
    RTC_LATCH_REG = 1;
}

inline UINT16 rtc_get(UINT8 part) {
    UINT16 ret;
    rtc_select(part);
    ret = RTC_VALUE_REG;
    if (part == RTC_VALUE_DAY) {
        rtc_select(RTC_VALUE_FLAGS);
        if (RTC_VALUE_REG & 0x01)
            ret |= 0x0100u;
    }

    return ret;
}
inline void rtc_set(UINT8 part, UINT16 val) {
    rtc_select(part);
    RTC_VALUE_REG = val;
    if (part == RTC_VALUE_DAY) {
        rtc_select(RTC_VALUE_FLAGS);
        RTC_VALUE_REG = (RTC_VALUE_REG & 0x0E) | (UINT8)((val >> 8) & 0x01);
    }
}

#endif /* __RTC_H__ */
