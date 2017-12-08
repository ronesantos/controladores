
// for usleep
#include <unistd.h>
// for open()
#include <fcntl.h>   
// for js_event
#include <linux/joystick.h>
// for exit
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <pthread.h>

// https://www.kernel.org/doc/Documentation/input/joystick-api.txt

typedef struct {
    int type;
    int event; /* 0-pressed; 1- released*/
    int eixo;
    int value;

} button_event;

void joystick_callback();

void *thread(void *vargp){
   struct js_event msg;
	char* device = "/dev/input/js0";
	
	int fd = open(device, O_RDONLY);

    char name[128];
	if (ioctl(fd, JSIOCGNAME(sizeof(name)), name) < 0)
		strncpy(name, "Unknown", sizeof(name));

	char number_of_axes;
	ioctl(fd, JSIOCGAXES, &number_of_axes);

	char number_of_buttons;
	ioctl(fd, JSIOCGBUTTONS, &number_of_buttons);
    button_event *btn_event = malloc(sizeof(btn_event));

	while(1) {
		if(read(fd, &msg, sizeof(struct js_event)) != sizeof(struct js_event)) {
			exit(1);
		} else {
            if(msg.type == JS_EVENT_BUTTON){
                 btn_event->type = JS_EVENT_BUTTON;
                if (msg.value == 1) {
                    btn_event->event = 0;
                    btn_event->value = msg.number;
                    joystick_callback(btn_event);
                } else if (msg.value == 0) {
                   
                    btn_event->event = 1;
                    btn_event->value = msg.number;
                    joystick_callback(btn_event);

               }

            } else if (msg.type == JS_EVENT_AXIS){
                    btn_event->type = JS_EVENT_AXIS;
                    btn_event->eixo = msg.number;
                    btn_event->value = msg.value;
                joystick_callback(btn_event);
            }
            if (msg.type == JS_EVENT_INIT){
            }
			usleep(10000);
		}
	}
	

    pthread_exit((void *)NULL);
}


 void joystick_inicialize(){
    pthread_t tid;
    pthread_create(&tid, NULL, thread, NULL);
    pthread_join(tid, NULL);
    pthread_exit((void *)NULL);

}


