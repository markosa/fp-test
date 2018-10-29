/*
 * Main.cpp
 *
 *  Created on: Sep 20, 2018
 *      Author: markos
 */

#include <stdio.h>
#include "Configuration.h"
#include "Settings.h"
#include "Button.h"
#include "Menu.h"
#include "MenuNode.h"
#include "System.h"
#include "Alarm.h"
#include "Motor.h"
#include "ButtonBoard.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "RotaryEncoder.h"
#include <pins_arduino.h>
void setupMenu();
void init();

static Button BUTTON_PRGSET(0, 100, "PRGSET");
static Button BUTTON_SET(101, 200, "SET");
static Button BUTTON_STA(201, 300, "STA");
static Button BUTTON_RUN(301, 400, "RUN");
static Button BUTTON_ALARM(401, 500, "ALARM");
static Button *ALL_BUTTONS[] = {&BUTTON_PRGSET, &BUTTON_SET, &BUTTON_STA, &BUTTON_RUN, &BUTTON_ALARM};
const static int ALL_BUTTONS_length = sizeof(ALL_BUTTONS) / sizeof(ALL_BUTTONS[0]);

static Settings settings = Settings();
static Menu menu = Menu();

static System fpSystem = System();

void callBack(int value)
{
    debug_print("Callback: %d  \n", value);
}

static MenuNode PRGSET_MAIN = MenuNode("PRGSET MENU", &BUTTON_PRGSET, &callBack);
static MenuNode PRGSET_DEV = MenuNode("PRGSET DEV", &BUTTON_PRGSET, &callBack);
static MenuNode PRGSET_STOP = MenuNode("PRGSET STOP", &BUTTON_PRGSET, &callBack);
static MenuNode PRGSET_FIX = MenuNode("PRGSET FIX", &BUTTON_PRGSET, &callBack);

static MenuNode SET_MAIN = MenuNode("SET MENU", &BUTTON_SET, &callBack);
static MenuNode SET_SPEED = MenuNode("SET SPEED", &BUTTON_SET, &callBack);
static MenuNode SET_TRANSITION = MenuNode("SET TRANS", &BUTTON_SET, &callBack);

static MenuNode STA_MAIN = MenuNode("STA MENU", &BUTTON_STA, &callBack);
static MenuNode STA_STOP = MenuNode("STA STOP", &BUTTON_STA, &callBack);

static MenuNode RUN_MAIN = MenuNode("RUN MENU", &BUTTON_RUN, &callBack);
static MenuNode RUN_CONFIRM_DEV_START = MenuNode("RUN DEV CONFIRM", &BUTTON_RUN, &callBack);
static MenuNode RUN_STOP = MenuNode("RUN STOP", &BUTTON_RUN, &callBack);
static MenuNode RUN_FIX = MenuNode("RUN FIX", &BUTTON_RUN, &callBack);
static MenuNode RUN_WASH = MenuNode("RUN WASH", &BUTTON_RUN, &callBack);

static MenuNode ALARM_MAIN = MenuNode("ALARM MENU", &BUTTON_ALARM, &callBack);

static MenuNode *PRGSET_SUB[] = {&PRGSET_DEV, &PRGSET_STOP, &PRGSET_FIX};
static MenuNode *SET_SUB[] = {&SET_SPEED, &SET_TRANSITION};
static MenuNode *STA_SUB[] = {&STA_STOP};
static MenuNode *RUN_SUB[] = {&RUN_CONFIRM_DEV_START, &RUN_STOP, &RUN_FIX, &RUN_WASH};

static unsigned int lastButtonSwitchBoardReadTime = 0;
// static RotaryEncoder rotaryEncoder = RotaryEncoder(ROTARY_ENCODER_DT_PIN, ROTARY_ENCODER_CLK_PIN, ROTARY_ENCODER_SW_PIN);
static Alarm alarm = Alarm();
static Motor motor = Motor();
static ButtonBoard bb = ButtonBoard(BUTTON_SWITCH_BOARD_ANALOG_PIN, BUTTON_SWITCH_BOARD_DEBOUNCE_THRESHOLD, *ALL_BUTTONS, ALL_BUTTONS_length);

LiquidCrystal_I2C lcd(LCD_I2C_ADDR, LCD_WIDTH, LCD_HEIGHT);

int rotaryEncoderValue()
{
    return 100;
}

void setupInterrupts()
{
}

void handleMotor()
{
}

void handleProgram()
{
}

void setupMenu()
{
    menu.add(&PRGSET_MAIN, PRGSET_SUB, (sizeof(PRGSET_SUB) / sizeof(PRGSET_SUB[0])));
    menu.add(&SET_MAIN, SET_SUB, (sizeof(SET_SUB) / sizeof(SET_SUB[0])));
    menu.add(&STA_MAIN, STA_SUB, (sizeof(STA_SUB) / sizeof(STA_SUB[0])));
    menu.add(&RUN_MAIN, RUN_SUB, (sizeof(RUN_SUB) / sizeof(RUN_SUB[0])));
    menu.add(&ALARM_MAIN, NULL, 0);
}

void mainScreenTest()
{
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("D: 15.50m  S: 00.50m");
    lcd.setCursor(0, 1);
    lcd.print("F: 10.00m  W: 10.00m");
    lcd.setCursor(0, 2);
    lcd.print("        @50RPM");
    lcd.setCursor(0, 3);
    lcd.blink_on();
    lcd.print("frp> ready");

    lcd.cursor_off();
}

void setup()
{
    Serial.begin(9600);
    Serial.println("Booting \n");
    lcd.init(); // initialize the lcd
    lcd.clear();
    // Print a message to the LCD.
    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.print("FRP Version 0.1");
    lcd.setCursor(0, 1);
    lcd.print("Initializing...");

    fpSystem.state = INIT;
    settings.load();

    settings.debugPrintSettings();

    // Setup button board control pin

    setupMenu();
    //rotaryEncoder.enable();

    setupInterrupts();

    alarm.once();
    bb.enable();

    mainScreenTest();
    fpSystem.state = IDLE;
}

void loop()
{

    bb.handle();
    alarm.handle();

    if (bb.isActive())
    {
        Button *buttonPressed = bb.getButton();
        menu.move(buttonPressed, 100);
    }
}
