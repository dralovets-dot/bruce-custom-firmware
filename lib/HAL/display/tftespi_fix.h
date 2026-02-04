// Fix for T-Embed CC1101: disable touch when TOUCH_CS is -1
#ifndef TFTESPI_FIX_H
#define TFTESPI_FIX_H

// This macro will be used to conditionally enable touch functions
#ifndef TOUCH_CS
#define TOUCH_CS -1  // Default to no touch
#endif

// Helper macro to check if touch is available
#define TOUCH_AVAILABLE() (TOUCH_CS >= 0)

#endif // TFTESPI_FIX_H
