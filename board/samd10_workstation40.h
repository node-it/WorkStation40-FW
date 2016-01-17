/*
 * ----------------------------------------------------------------------------
 *            _____ _           _                   _
 *           | ____| | ___  ___| |_ _ __ ___  _ __ (_) ___
 *           |  _| | |/ _ \/ __| __| '__/ _ \| '_ \| |/ __|
 *           | |___| |  __/ (__| |_| | | (_) | | | | | (__
 *           |_____|_|\___|\___|\__|_|  \___/|_| |_|_|\___|
 *            ____                   _   ____
 *           / ___|_      _____  ___| |_|  _ \ ___  __ _ ___
 *           \___ \ \ /\ / / _ \/ _ \ __| |_) / _ \/ _` / __|
 *            ___) \ V  V /  __/  __/ |_|  __/  __/ (_| \__ \
 *           |____/ \_/\_/ \___|\___|\__|_|   \___|\__,_|___/
 *
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <pontus@sweetpeas.se> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return - Pontus Oldberg
 * ----------------------------------------------------------------------------
 *
 */

#ifndef SAMD10_WORKSTATION40_H_INCLUDED
#define SAMD10_WORKSTATION40_H_INCLUDED

#include <compiler.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \ingroup group_common_boards
 * \defgroup samd10_workstation_group SAM D10 WorkStation40 board
 *
 * @{
 */

void system_board_init(void);

/**
 * \defgroup samd11_batman_features_group Features
 *
 * Symbols that describe features and capabilities of the board.
 *
 * @{
 */

/** Name string macro */
#define BOARD_NAME                "SAMD10_WORKSTATION40"

/** \name Resonator definitions
 *  @{ */
#define BOARD_FREQ_SLCK_XTAL      (32768U)
#define BOARD_FREQ_SLCK_BYPASS    (32768U)
#define BOARD_FREQ_MAINCK_XTAL    0 /* Not Mounted */
#define BOARD_FREQ_MAINCK_BYPASS  0 /* Not Mounted */
#define BOARD_MCK                 CHIP_FREQ_CPU_MAX
#define BOARD_OSC_STARTUP_US      15625
/** @} */

/** \name LED1 definitions
 *  @{ */
#define LED1_PIN                  PIN_PA02
#define LED1_ACTIVE               false
#define LED1_INACTIVE             !LED1_ACTIVE
#define LED1_GPIO                 LED1_PIN
/** @} */

/** \name BOOT pin definitions
 *  @{ */
#define BOOT_PIN                   PIN_PA15
#define BOOT_ACTIVE                false
#define BOOT_INACTIVE              !BOOT_ACTIVE
#define BOOT_EIC_PIN               PIN_PA15A_EIC_NMI
#define BOOT_EIC_MUX               MUX_PA15A_EIC_NMI
#define BOOT_EIC_PINMUX            PINMUX_PA15A_EIC_NMI
#define BOOT_EIC_LINE              1
/** @} */

/** Number of on-board LEDs */
#define LED_COUNT                 1

/** \name Extension header #1 pin definitions
 *  @{
 */
#define ADC_PIN_0                 6
#define ADC_PIN_1                 9
#define ADC_PIN_2                 8
#define ADC_PIN_3                 5
#define ADC_PIN_4                 4
#define ADC_PIN_5                 3
#define ADC_PIN_6                 2
#define ADC_PIN_7                 1

#if 0
#define EXT1_PIN_0                PIN_PA08
#define EXT1_PIN_1                PIN_PA09
#define EXT1_PIN_2                PIN_PA10
#define EXT1_PIN_3                PIN_PA11
#define EXT1_PIN_4                PIN_PA14
#define EXT1_PIN_5                PIN_PA15
#define EXT1_PIN_6                PIN_PA16
#define EXT1_PIN_7                PIN_PA17
/** @} */

/** \name Extension header #2 pin definitions (not used, defined to avoid compiling errors)
 *  @{
 */
#define EXT2_PIN_3                   -1 /* Not available on this board */
#define EXT2_PIN_4                   -1 /* Not available on this board */
#define EXT2_PIN_5                   -1 /* Not available on this board */
#define EXT2_PIN_6                   -1 /* Not available on this board */
#define EXT2_PIN_7                   -1 /* Not available on this board */
#define EXT2_PIN_8                   -1 /* Not available on this board */
#define EXT2_PIN_9                   -1 /* Not available on this board */
#define EXT2_PIN_10                  -1 /* Not available on this board */
#define EXT2_PIN_11                  -1 /* Not available on this board */
#define EXT2_PIN_12                  -1 /* Not available on this board */
#define EXT2_PIN_13                  -1 /* Not available on this board */
#define EXT2_PIN_14                  -1 /* Not available on this board */
#define EXT2_PIN_15                  -1 /* Not available on this board */
#define EXT2_PIN_16                  -1 /* Not available on this board */
#define EXT2_PIN_17                  -1 /* Not available on this board */
#define EXT2_PIN_18                  -1 /* Not available on this board */
/** @} */


/** \name Extension header #3 pin definitions
 *  @{
 */
#define EXT3_PIN_3                   -1 /* Not available on this board */
#define EXT3_PIN_4                   -1 /* Not available on this board */
#define EXT3_PIN_5                   -1 /* Not available on this board */
#define EXT3_PIN_6                   -1 /* Not available on this board */
#define EXT3_PIN_7                   -1 /* Not available on this board */
#define EXT3_PIN_8                   -1 /* Not available on this board */
#define EXT3_PIN_9                   -1 /* Not available on this board */
#define EXT3_PIN_10                  -1 /* Not available on this board */
#define EXT3_PIN_11                  -1 /* Not available on this board */
#define EXT3_PIN_12                  -1 /* Not available on this board */
#define EXT3_PIN_13                  -1 /* Not available on this board */
#define EXT3_PIN_14                  -1 /* Not available on this board */
#define EXT3_PIN_15                  -1 /* Not available on this board */
#define EXT3_PIN_16                  -1 /* Not available on this board */
#define EXT3_PIN_17                  -1 /* Not available on this board */
#define EXT3_PIN_18                  -1 /* Not available on this board */
/** @} */
#endif

#ifdef __cplusplus
}
#endif

#endif  /* SAMD10_WORKSTATION40_H_INCLUDED */
