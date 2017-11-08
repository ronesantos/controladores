// for printf
#include <stdio.h>
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

//struct js_event {
//    __u32 time; /* event timestamp in milliseconds */
//    __s16 value;    /* value */
//    __u8 type;  /* event type */
//    __u8 number;    /* axis/button number */
//};

// https://www.kernel.org/doc/Documentation/input/joystick-api.txt

int main() {
	struct js_event msg;
	char* device = "/dev/input/js0";
	
	int fd = open(device, O_RDONLY);

    char name[128];
	if (ioctl(fd, JSIOCGNAME(sizeof(name)), name) < 0)
		strncpy(name, "Unknown", sizeof(name));
	printf("Name: %s\n", name);


	char number_of_axes;
	ioctl(fd, JSIOCGAXES, &number_of_axes);
    printf("Numero de eixos: %d\n", number_of_axes);

	char number_of_buttons;
	ioctl(fd, JSIOCGBUTTONS, &number_of_buttons);
    printf("Numero de botoes: %d\n", number_of_buttons);

	while(1) {
		if(read(fd, &msg, sizeof(struct js_event)) != sizeof(struct js_event)) {
			printf("Error when reading from joystick\n");
			exit(1);
		} else {
            if(msg.type == JS_EVENT_BUTTON)
                if (msg.value == 1)
                    printf("Button %d press\n", msg.number);
                if (msg.value == 0)
                    printf("Button %d released\n", msg.number);
            if (msg.type == JS_EVENT_AXIS)
                printf("Eixo %d %d \n",  msg.number, msg.value);
            if (msg.type == JS_EVENT_INIT)
                printf("Inicializacao ");
			usleep(10000);
		}
	}
	
	return 0;
}
