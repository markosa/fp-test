/*
 * Configuration.h
 *
 *  Created on: Sep 22, 2018
 *      Author: markos
 */

#ifndef CONFIGURATION_H_
#define CONFIGURATION_H_

#include <Arduino.h>
#include <pins_arduino.h>

/**
 * 
 * GLOBAL
 * 
 **/
#define LOCAL_TEST 0
#define DEBUG 1
#define debug_print(fmt, ...)                  \
    do                                         \
    {                                          \
        if (DEBUG)                             \
            fprintf(stderr, fmt, __VA_ARGS__); \
    } while (0)

/**
 * 
 * MENU
 * 
 **/
#define MENU_MAX_MAIN_NODES 5
#define MENU_MAX_SUB_NODES 5

/**
 * 
 * BUTTON SWITCH BOARD
 * 
 **/

static const int BUTTON_SWITCH_BOARD_ANALOG_PIN = A7;
static const int BUTTON_SWITCH_BOARD_DEBOUNCE_THRESHOLD = 250;

/**
 * 
 * MOTOR H.BRIDGE CONTROL PINS
 * 
 **/

static const int HBRIDGE_PWM_PIN = PD3;
static const int HBRIDGE_ENA_A_PIN = PD2;
static const int HBRIDGE_ENA_B_PIN = PD4;
static const int HBRIDGE_MOTOR_SHUTDOWN_THRESHOLD = 10;

/**
 * 
 * PIEZO SPEAKER / BUZZER CONTROL PIN
 * 
 **/

static const int ALARM_BUZZER_PIN = PD5; // D5
static const int ALARM_BUZZER_TONE = 1000;

/**
 * 
 * LCD 
 * 
 **/

#define LCD_I2C_ADDR 0x27
#define LCD_WIDTH 20
#define LCD_HEIGHT 20

/**
 * 
 * VALUE KNOB / ROTARY ENCODER PINS
 * 
 **/

static const int ROTARY_ENCODER_SW_PIN = 9;  // D9
static const int ROTARY_ENCODER_DT_PIN = 3;  // D8
static const int ROTARY_ENCODER_CLK_PIN = 2; // D7
static const unsigned int ROTARY_ENCODER_DEBOUNCE_THRESHOLD = 5;

#endif /* CONFIGURATION_H_ */
