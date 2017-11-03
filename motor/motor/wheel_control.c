/*
 * wheel_control.c
 *
 * Created: 11/2/2017 5:12:53 PM
 *  Author: jakno732
 */

//variables for using timer in testing
unsigned    int period_counter  = 0;
unsigned    int second_counter  = 0;
            int has_counted     = 0;


 /*
     todo:
     . 16MHz/8MHz setup
     . turn
     . initial speed
     . action on command
 */

 int init_dir_pins(void)
 {
     PORTC |=  (1 << PORTC1) | (0 << PORTC0);
     return 0;
 }


 /*set duty percentage of PWM1
 int set_left_PWM(float duty)
 {
     int uptime = 255 - duty*255; //timer increments to be up
     OCR0A = uptime;
     OCR0B = uptime;
 }
 
 /*set duty percentage of PWM2 (right wheel side)*/
 int set_right_PWM(float duty)

 int init_wheel_control()
 {
    /* OLD SETTINGS
    TCCR0A |=  0b11110001;
    TCCR0A &= ~0b00000010;
    TCCR0B = 0b00000001;	//no pre-scaling. nothing is 1 since PWM
    */
    
    //set OC0A and OC0B on compare match when up-counting, clear on down-counting
    TCCR0A |= 1<<COM0A1 | 1<<COM0A0 
    TCCR0A |= 1<<COM0B1 | 1<<COM0B0 

    //Phase correct PWM
    TCCR0A &= ~(1<<WGM01)
    TCCR0A |=   1<<WGM00 
    TCCR0B &= ~(1<<WGM02)

    //set PB3, PB4 as output for DIR1 and DIR2
    DDRB |= (1<<DDB3) | (1<<DDB4);
    
    //initial values for DIR1 and DIR2
    PORTC |=  (1<<PORTC3);
    PORTC &= ~(1<<PORTC4);

    // enable interupt for compare match A and B on timer TCNT0
    TIMSK0 |= (1<<OCIE0B)|(1<<OCIE0A);	

    set_PWM(0); //set both wheel sides to 0

    return 0;
 }

 int seconds(unsigned int seconds){
    if ( TCNT0 > 200 && !(has_counted)){
        has_counted = 1;
        period_counter += 1;
    }
    else if ( TCNT0 < 200 ){
        has_counted = 0;
    }
    if ( period_counter >= 15770 ){ // 15770Hz is measured in oscilloscope (8Mhz)
        second_counter += 1;
        period_counter = 0;
    }
    if (second_counter > seconds){
        second_counter = 0;
        return 1;
    }
    else
    {
        return 0;
    }
 }


 // f = 1/T; T=1/f; 16000 cycles > 1s
 int main(void)
 {
    init_dir_pins();
    init_PWM();

    while(!seconds(5));		//wait 5 sec
    set_PWM(0.5);
    while(!seconds(2));	//wait 5 sec
    set_PWM(0);

    while(1)
    {

    }
    return 0;
 }
