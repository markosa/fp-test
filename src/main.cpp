/*
 * Main.cpp
 *
 *  Created on: Sep 20, 2018
 *      Author: markos
 */

#include <stdio.h>
#include <LiquidCrystal.h>
#include "Configuration.h"
#include "Settings.h"
#include "Button.h"
#include "Menu.h"
#include "MenuNode.h"
#include "System.h"
#include "Alarm.h"

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

static Alarm alarmHandler = Alarm();

int rotaryEncoderValue()
{
    return 100;
}

void handleButtonSwitchBoard()
{

    if ((millis() - lastButtonSwitchBoardReadTime) > BUTTON_SWITCH_BOARD_DEBOUNCE_THRESHOLD)
    {
        int adcValue = analogRead(BUTTON_SWITCH_BOARD_ANALOG_PIN);
        Button *pressedButton = NULL;
        for (int i = 0; i < ALL_BUTTONS_length; i++)
        {
            Button *b = ALL_BUTTONS[i];
            if (adcValue >= b->getAdMin() && adcValue <= b->getAdMax())
            {
                pressedButton = b;
                lastButtonSwitchBoardReadTime = millis();
                break;
            };
        }
        if (pressedButton != NULL)
            menu.move(pressedButton, rotaryEncoderValue());
    }
    else
    {
        debug_print("handleButtonSwitchBoard: not in debounce threshold", NULL);
    }
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

void setup()
{
    Serial.begin(9600);
    Serial.println("Booting \n");

    fpSystem.state = INIT;
    settings.load();
    settings.debugPrintSettings();

    // Setup button board control pin
    pinMode(BUTTON_SWITCH_BOARD_ANALOG_PIN, INPUT);

    setupMenu();

    setupInterrupts();

    fpSystem.state = IDLE;

    alarmHandler.once();
}

void loop()
{

    alarmHandler.handle();
}
/*
int main(void)
{
    if (LOCAL_TEST)
    {
        setup();

        while (1)
        {
            char c;
            printf("\nq=PRGSET w=SET e=STA r=RUN t=ALARM\n");

            c = getchar();
            getchar();
            printf("Pressed: %c\n", c);
            Button *buttonPressed = NULL;
            switch (c)
            {
            case 'q':
                printf("PRGSET****\n");
                buttonPressed = &BUTTON_PRGSET;
                break;
            case 'w':
                printf("SET****\n");
                buttonPressed = &BUTTON_SET;

                break;
            case 'e':
                printf("STA****\n");
                buttonPressed = &BUTTON_STA;

                break;
            case 'r':
                printf("RUN****\n");
                buttonPressed = &BUTTON_RUN;

                break;
            case 't':
                printf("ALARM****\n");
                buttonPressed = &BUTTON_ALARM;

                break;
            }
            if (buttonPressed == NULL)
            {
                printf("null\n");
            }

            menu.move(buttonPressed, 100);
            MenuNode *current = menu.getCurrentNode();
        }
    }

    return 0;
}
*/