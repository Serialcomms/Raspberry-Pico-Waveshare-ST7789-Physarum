#include "stdio.h"
#include "pico/stdlib.h"
#include "pico/divider.h"
#include "pico/bootrom.h"
#include "include/colony.h"
#include "include/physarum.h"
#include "include/core_0_menu.h"
#include "include/waveshare_irq.h"
#include "include/physarum.h"

extern bool animate;

extern uint32_t Q;

extern uint16_t colony[];

extern uint32_t   ITERATIONS;
extern uint32_t   ITERATION_NUM;
extern uint16_t   P_VALUE_THRESHOLD;
extern uint8_t    ACTIVE_COLONIES;

void select_menu_option(char choice) {

    switch (choice) {
        
      case 'U' :   menu_option_U();   break;
      case 'D' :   menu_option_D();   break;
      case 'L' :   menu_option_L();   break;
      case 'R' :   menu_option_R();   break;

      case 'A' :   menu_option_A();   break;
      case 'B' :   menu_option_B();   break;
      case 'C' :   menu_option_C();   break;
      case 'X' :   menu_option_X();   break;
      case 'Y' :   menu_option_Y();   break;

      case '~' :   reboot_pico_usb();   break;
      
      default :    menu_default();    break;                     

    }

}

void reboot_pico_usb() {

  reset_usb_boot(1 << PICO_DEFAULT_LED_PIN , 0);

}

void menu_option_A() {

  rnd_colony();

  print_physarum("KEY_A");

}

void menu_option_B() {

  dec_colony();

  print_physarum("KEY_B");

}

void menu_option_X() {

  inv_colony();

  print_physarum("KEY_X");

}

void menu_option_Y() {

  all_colony();
  
  print_physarum("KEY_Y");

}

void menu_option_U() {

  if (ACTIVE_COLONIES < 8) {

    ++ACTIVE_COLONIES;

    rnd_colony();
  
    rndseed();

  }
  
  print_physarum("JOY_U");

}

void menu_option_D() {

  if (ACTIVE_COLONIES > 2) {

    --ACTIVE_COLONIES;

    rnd_colony();
  
    rndseed();

  }

  print_physarum("JOY_D");

}

void menu_option_L() {

  if (P_VALUE_THRESHOLD > 4) P_VALUE_THRESHOLD -= 1;

  print_physarum("JOY_L");

}

void menu_option_R() {

  if (P_VALUE_THRESHOLD < 60) P_VALUE_THRESHOLD += 1;

  print_physarum("JOY_R");

}


void menu_option_C() {

  physarum_defaults();

  rnd_colony();

  rndseed();

  print_physarum("JOY_C");
  
}

void menu_default() {

  printf("Select Menu Option U, D, L, R, C (Joypad) or A, B, X, Y (Keys)\n\r");

}

void print_physarum(uint8_t *KEY_NAME) {

  printf(KEY_NAME);

  printf(", Physarum: Colonies=%d, Density=%d)\n\r", ACTIVE_COLONIES, P_VALUE_THRESHOLD);

}