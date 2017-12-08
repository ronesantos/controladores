#include "joystick.h"
#include <stdio.h>

void print_event(button_event *bnt_event){
    printf("aaaaaaaaaaaaaaaaaaaaaaaaaaaaa\n");
}

void joystick_callback(button_event *event) {
    print_event(event);

}


int main(int argc, char *argv[]) {
    joystick_inicialize();   
    return 0;
}
