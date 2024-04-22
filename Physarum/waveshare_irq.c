
#include "pico/stdlib.h"
#include "include/colony.h"
#include "include/random.h"
#include "include/physarum.h"
#include "include/waveshare_irq.h"
#include "include/waveshare_gpio.h"
#include "include/waveshare_pins.h"

extern uint8_t    ACTIVE_COLONIES;
extern uint32_t   ITERATIONS;
extern uint16_t   P_VALUE_THRESHOLD;

void gpio_callback_all(uint gpio, uint32_t events) {

// gpio_acknowledge_irq() is done automatically by gpio_set_irq...

  switch (gpio) {

    case KEY_A:        waveshare_key_A();         break;
    case KEY_B:        waveshare_key_B();         break;
    case KEY_Y:        waveshare_key_Y();         break;
    case KEY_X:        waveshare_key_X(events);   break;

    case JOY_UP:       waveshare_joy_U(events);   break;
    case JOY_DOWN:     waveshare_joy_D(events);   break;
    case JOY_LEFT:     waveshare_joy_L();         break;
    case JOY_RIGHT:    waveshare_joy_R();         break;
    case JOY_CENTRE:   waveshare_joy_C(events);   break;

  }

}

void waveshare_key_A() {

  static absolute_time_t next_toggle;  

  if (time_reached(next_toggle)) {

    rnd_colony();

    next_toggle = make_timeout_time_ms(125);

   }
      
}

void waveshare_key_B() {

  static absolute_time_t next_toggle;  

  if (time_reached(next_toggle)) {

    dec_colony();

    next_toggle = make_timeout_time_ms(125);

  }
      
}

void waveshare_key_X(uint32_t events) {

  static absolute_time_t next_toggle;  

  if (time_reached(next_toggle)) {

    inv_colony();

    next_toggle = make_timeout_time_ms(125);

  }

}

void waveshare_key_Y() {

  static absolute_time_t next_toggle;  

  if (time_reached(next_toggle)) {

    all_colony();

    next_toggle = make_timeout_time_ms(125);

  }

}

void waveshare_joy_U(uint32_t events) {

  static absolute_time_t next_toggle; 

    switch (events) {

    case GPIO_IRQ_EDGE_FALL:

      if (time_reached(next_toggle)) {

        if (ACTIVE_COLONIES < 8) {

        ++ACTIVE_COLONIES;

        rndseed();

      }

    next_toggle = make_timeout_time_ms(125);

   }

    break;

    case GPIO_IRQ_EDGE_RISE:

    next_toggle = make_timeout_time_ms(125);

    break;

    } 

}

void waveshare_joy_D(uint32_t events) {

  static absolute_time_t next_toggle;

    switch (events) {

    case GPIO_IRQ_EDGE_FALL:

     if (time_reached(next_toggle)) {

      if (ACTIVE_COLONIES > 2) {

        --ACTIVE_COLONIES;

        rndseed();
      
      }
      
      next_toggle = make_timeout_time_ms(125);
   }  

    break;

    case GPIO_IRQ_EDGE_RISE:

     next_toggle = make_timeout_time_ms(125);

    break;

    }

}

void waveshare_joy_L() {

  static absolute_time_t next_toggle;  

  if (time_reached(next_toggle)) {

    if (P_VALUE_THRESHOLD > 4) P_VALUE_THRESHOLD -= 3;

    next_toggle = make_timeout_time_ms(125);

   }

}

void waveshare_joy_R() {

  static absolute_time_t next_toggle; 

    if (time_reached(next_toggle)) {

      if (P_VALUE_THRESHOLD < 60) P_VALUE_THRESHOLD += 3;      

      next_toggle = make_timeout_time_ms(125);

    } 

}

void waveshare_joy_C(uint32_t events) { 

  static absolute_time_t next_toggle; 

  switch (events) {

    case GPIO_IRQ_EDGE_FALL:

    if (time_reached(next_toggle)) {

      physarum_defaults();

      rnd_colony();

      rndseed();

      next_toggle = make_timeout_time_ms(100);

      break;

  }

    case GPIO_IRQ_EDGE_RISE:

    next_toggle = make_timeout_time_ms(100);

    break;

  }

}
