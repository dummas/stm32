/*
 * Copyright (c) 2013-2014, Michael E. Ferguson
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above
 *    copyright notice, this list of conditions and the following
 *    disclaimer in the documentation and/or other materials provided
 *    with the distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __ETHERBOTIX_HPP__
#define __ETHERBOTIX_HPP__

#include "stm32f4xx.h"
#include "gpio.hpp"

// Etherbotix Register table
#define REG_MODEL_NUMBER    0   // 16-bit model number
#define REG_VERSION         2
#define REG_ID              3   // Always 253 (same as arbotix)
#define REG_BAUD_RATE       4   // Applied to serial bus
#define REG_DELAY_TIME      5   // Part of serial bus timeout calculation

#define REG_DIGITAL_IN      6   // Corresponds to A0-D7 as digital input
#define REG_DIGITAL_DIR     7   // Digital A0-D7, low for input, high for output
#define REG_DIGITAL_OUT     8   // Digital A0-D7, sets high/low for output pins
#define REG_A0              10  // Read analog value from A0 (raw 12-bit value)
#define REG_A1              12  // Read analog value from A1
#define REG_A2              14  // Read analog value from A2

#define REG_ALARM_LED       17  // Turns on error led
#define REG_SYSTEM_TIME     20  // 32-bit unsigned system clock
#define REG_AUX_CURRENT     24  // 16-bit signed current in mA
#define REG_SERVO_CURRENT   26  // 16-bit signed current in mA
#define REG_MOTOR_PERIOD    31  // 8-bit motor cycle period (1-100mS, 0 deactives driver)

#define REG_MOTOR1_VEL      32  // 16-bit motor velocity (ticks/cycle, read-write)
#define REG_MOTOR2_VEL      34  // 16-bit motor velocity (ticks/cycle, read-write)
#define REG_MOTOR1_POS      36  // 32-bit signed position (ticks, read-only)
#define REG_MOTOR2_POS      40  // 32-bit signed position (ticks, read-only)
#define REG_MOTOR1_CURRENT  44  // 16-bit unsigned (raw 12-bit value from ADC)
#define REG_MOTOR2_CURRENT  46  // 16-bit unsigned (raw 12-bit value from ADC)

#define REG_MOTOR1_KP       48  // 32-bit float kp
#define REG_MOTOR1_KD       52  // 32-bit float kd
#define REG_MOTOR1_KI       56  // 32-bit float ki
#define REG_MOTOR1_WINDUP   60  // 32-bit float windup limit

#define REG_MOTOR2_KP       64  // 32-bit float kp
#define REG_MOTOR2_KD       68  // 32-bit float kd
#define REG_MOTOR2_KI       72  // 32-bit float ki
#define REG_MOTOR2_WINDUP   76  // 32-bit float windup limit

#define REG_ACC_X           80  // All these are int16
#define REG_ACC_Y           82
#define REG_ACC_Z           84
#define REG_GYRO_X          86
#define REG_GYRO_Y          88
#define REG_GYRO_Z          90
#define REG_MAG_X           92
#define REG_MAG_Y           94
#define REG_MAG_Z           96

#define DEVICE_USART3_BAUD  128
#define DEVICE_USART3_DATA  129
#define DEVICE_SPI2_BAUD    130
#define DEVICE_SPI2_DATA    131

// Activity and error LEDs
typedef Gpio<GPIOC_BASE, 14> error;
typedef Gpio<GPIOC_BASE, 15> act;

// Ethernet Pins
typedef Gpio<GPIOA_BASE, 2> eth_mdio;
typedef Gpio<GPIOC_BASE, 1> eth_mdc;
typedef Gpio<GPIOE_BASE, 7> phy_rst;

typedef Gpio<GPIOA_BASE, 1> eth_rmii_ref_clk;
typedef Gpio<GPIOA_BASE, 7> eth_rmii_crs_dv;

typedef Gpio<GPIOB_BASE, 11> eth_rmii_tx_en;
typedef Gpio<GPIOB_BASE, 12> eth_rmii_txd0;
typedef Gpio<GPIOB_BASE, 13> eth_rmii_txd1;
typedef Gpio<GPIOC_BASE, 4> eth_rmii_rxd0;
typedef Gpio<GPIOC_BASE, 5> eth_rmii_rxd1;

// Analog
typedef Gpio<GPIOA_BASE, 0> servo_sense;    // servo current: ADC123_IN0
#define SERVO_CURRENT_ANALOG_CHANNEL    0
typedef Gpio<GPIOA_BASE, 3> m2_sense;       // motor 2 current: ADC123_IN3
#define M2_CURRENT_ANALOG_CHANNEL       3
typedef Gpio<GPIOA_BASE, 4> m1_sense;       // motor 1 current: ADC12_IN4
#define M1_CURRENT_ANALOG_CHANNEL       4
typedef Gpio<GPIOB_BASE, 0> a0_sense;       // a0: ADC12_IN8
#define A0_ANALOG_CHANNEL               8
typedef Gpio<GPIOB_BASE, 1> aux_sense;      // aux. current: ADC12_IN9
#define AUX_CURRENT_ANALOG_CHANNEL      9
typedef Gpio<GPIOC_BASE, 0> voltage_sense;  // voltage: ADC123_IN10
#define VOLTAGE_ANALOG_CHANNEL          10
typedef Gpio<GPIOC_BASE, 2> a1_sense;       // a1: ADC123_IN12 (also SPI2_MISO)
#define A1_ANALOG_CHANNEL               12
typedef Gpio<GPIOC_BASE, 3> a2_sense;       // a2: ADC123_IN13 (also SPI2_MOSI)
#define A2_ANALOG_CHANNEL               13

// Motor1
typedef Gpio<GPIOE_BASE, 9> m1_pwm;         // motor1 PWM = tim1_ch1
typedef Gpio<GPIOE_BASE, 8> m1_a;           // motor1 A = tim1_ch1N
typedef Gpio<GPIOE_BASE, 11> m1_b;          // motor1 B = tim1_ch2
typedef Gpio<GPIOE_BASE, 10> m1_en;         // motor1 EN = tim1_ch2N
//typedef Gpio<GPIOE_BASE, 13> m1_en;       // motor1 EN = tim1_ch3 (alternate routing)

// Motor2
typedef Gpio<GPIOC_BASE, 6> m2_pwm;         // motor2 PWM = tim8_ch1
typedef Gpio<GPIOA_BASE, 5> m2_a;           // motor2 A = tim8_ch1N
typedef Gpio<GPIOC_BASE, 7> m2_b;           // motor2 B = tim8_ch2
typedef Gpio<GPIOB_BASE, 14> m2_en;         // motor2 EN = tim8_ch2N/tim12_CH1
//typedef Gpio<GPIOC_BASE, 8> m2_en;        // motor2 EN = tim8_ch3 (alternate routing)

// M1 encoder - tim4
typedef Gpio<GPIOD_BASE, 12> m1_enc_a;      // tim4_ch1
typedef Gpio<GPIOD_BASE, 13> m1_enc_b;      // tim4_ch2

// M2 encoder - tim3
typedef Gpio<GPIOA_BASE, 6> m2_enc_a;       // tim3_ch1
typedef Gpio<GPIOB_BASE, 5> m2_enc_b;       // tim3_ch2

// Usart1 - rs-485 bus
typedef Gpio<GPIOA_BASE, 9> usart1_tx;
typedef Gpio<GPIOA_BASE, 10> usart1_rx;
typedef Gpio<GPIOD_BASE, 15> usart1_en;

// Usart2 - ax/mx bus
typedef Gpio<GPIOD_BASE, 5> usart2_tx;
typedef Gpio<GPIOD_BASE, 6> usart2_rx;
typedef Gpio<GPIOD_BASE, 7> usart2_en;

// IMU - i2c1
typedef Gpio<GPIOB_BASE,6> imu_scl;
typedef Gpio<GPIOB_BASE,7> imu_sda;

// Expandable IO
typedef Gpio<GPIOB_BASE,10> d3;  // also SPI2_SCK, USART3_TX, TIM2_CH3
typedef Gpio<GPIOC_BASE,11> d4;  // also           USART3_RX
typedef Gpio<GPIOB_BASE,15> d5;  // also TIM12_CH2
typedef Gpio<GPIOE_BASE,5> d6;   // also TIM9_CH1
typedef Gpio<GPIOE_BASE,6> d7;   // also TIM9_CH2

#endif // __ETHERBOTIX_HPP__