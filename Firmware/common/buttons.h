#ifndef BUTTONS_H_
#define BUTTONS_H_

#define BUTTONS_SR_DATA  _BV(PORTD7)
#define BUTTONS_SR_CLEAR _BV(PORTB2)
#define BUTTONS_SR_CLK   _BV(PORTB1)
#define BUTTONS_COL_0    _BV(PORTD2)
#define BUTTONS_COL_1    _BV(PORTD3)
#define BUTTONS_COL_2    _BV(PORTD4)
#define BUTTONS_COL_3    _BV(PORTD5)
#define BUTTONS_COL_4    _BV(PORTD6)

#define BUTTON_ON_OFF _BV(PORTC2)
#define BUTTON_UP     _BV(PORTC3)
#define BUTTON_LEFT   _BV(PORTC4)
#define BUTTON_RIGHT  _BV(PORTC5)
#define BUTTON_DOWN   _BV(PORTC6)

#define BUTTONS_NUM_ROWS 8

#define BUTTONS_SR_PULSE() PORTB &= ~BUTTONS_SR_CLK;PORTB |= BUTTONS_SR_CLK


extern const char BUTTON_MAP[25];


void buttons_initialize();
char buttons_get_special();
int buttons_getPressed();
#ifdef console
    void set_button(char);
#endif

#endif /* BUTTONS_H_ */