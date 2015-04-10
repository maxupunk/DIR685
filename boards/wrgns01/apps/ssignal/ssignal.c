#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <linux/input.h>
#include <fcntl.h>
#include <linux/keyboard.h>

int g_sem_id;//semaphore id

void press_button(int value_code);

static int sem_wait(const int sem_id)
{
	struct sembuf sem_b;

	sem_b.sem_num = 0;
	sem_b.sem_op = -1;
	sem_b.sem_flg = SEM_UNDO;
	return semop(sem_id, &sem_b, 1);
}
static int sem_signal(const int sem_id)
{
	struct sembuf sem_b;
	sem_b.sem_num = 0;
	sem_b.sem_op = 1;
	sem_b.sem_flg = SEM_UNDO;
	return semop(sem_id, &sem_b, 1);
}

void press_button(int value_code)
{
	struct input_event event;
	int fd;
	fd=open("/dev/input/event0",O_RDWR);
	if (fd < 0)
	{
       perror("Can't open device...\n");
       sem_signal(g_sem_id);
       exit(1);
    }     	
	event.type = EV_KEY;
    event.code = value_code;
    event.value = 1;    	
    gettimeofday(&event.time,0);
    
    if(write(fd,&event,sizeof(event))==-1)
       	printf("write failed \n");
    fflush(0);
    event.type = EV_KEY;
    event.code = value_code;
    event.value = 0;    	
    gettimeofday(&event.time,0);
    if(write(fd,&event,sizeof(event))==-1)
     	printf("write failed \n");
   	fflush(0);
	close(fd);	
}

void list_keys()
{
	printf("List of keys that can be used\n\n");
	printf(	"  KEY_RESERVED            0\n"
 		   	"  KEY_ESC                 1\n"
 			"  KEY_1                   2\n"
 			"  KEY_2                   3\n"
			"  KEY_3                   4\n"
			"  KEY_4                   5\n"
			"  KEY_5                   6\n"
			"  KEY_6                   7\n"
			"  KEY_7                   8\n"
			"  KEY_8                   9\n"
			"  KEY_9                   10\n"
			"  KEY_0                   11\n"
			"  KEY_MINUS               12\n"
			"  KEY_EQUAL               13\n"
			"  KEY_BACKSPACE           14\n"
			"  KEY_TAB                 15\n"
			"  KEY_Q                   16\n"
			"  KEY_W                   17\n"
			"  KEY_E                   18\n"
			"  KEY_R                   19\n"
			"  KEY_T                   20\n"
			"  KEY_Y                   21\n"
			"  KEY_U                   22\n"
			"  KEY_I                   23\n"
			"  KEY_O                   24\n"
			"  KEY_P                   25\n"
			"  KEY_LEFTBRACE           26\n"
			"  KEY_RIGHTBRACE          27\n"
			"  KEY_ENTER               28\n"
			"  KEY_LEFTCTRL            29\n"
			"  KEY_A                   30\n"
			"  KEY_S                   31\n"
			"  KEY_D                   32\n"
			"  KEY_F                   33\n"
			"  KEY_G                   34\n"
			"  KEY_H                   35\n"
			"  KEY_J                   36\n"
			"  KEY_K                   37\n"
			"  KEY_L                   38\n"
			"  KEY_SEMICOLON           39\n"
			"  KEY_APOSTROPHE          40\n"
			"  KEY_GRAVE               41\n"
			"  KEY_LEFTSHIFT           42\n"
			"  KEY_BACKSLASH           43\n"
			"  KEY_Z                   44\n"
			"  KEY_X                   45\n"
			"  KEY_C                   46\n"
			"  KEY_V                   47\n"
			"  KEY_B                   48\n"
			"  KEY_N                   49\n"
			"  KEY_M                   50\n"
			"  KEY_COMMA               51\n"
			"  KEY_DOT                 52\n"
			"  KEY_SLASH               53\n"
			"  KEY_RIGHTSHIFT          54\n"
			"  KEY_KPASTERISK          55\n"
			"  KEY_LEFTALT             56\n"
			"  KEY_SPACE               57\n"
			"  KEY_CAPSLOCK            58\n"
			"  KEY_F1                  59\n"
			"  KEY_F2                  60\n"
			"  KEY_F3                  61\n"
			"  KEY_F4                  62\n"
			"  KEY_F5                  63\n"
			"  KEY_F6                  64\n"
			"  KEY_F7                  65\n"
			"  KEY_F8                  66\n"
			"  KEY_F9                  67\n"
			"  KEY_F10                 68\n"
			"  KEY_NUMLOCK             69\n"
			"  KEY_SCROLLLOCK          70\n"
			"  KEY_KP7                 71\n"
			"  KEY_KP8                 72\n"
			"  KEY_KP9                 73\n"
			"  KEY_KPMINUS             74\n"
			"  KEY_KP4                 75\n"
			"  KEY_KP5                 76\n"
			"  KEY_KP6                 77\n" 
			"  KEY_KPPLUS              78\n"
			"  KEY_KP1                 79\n"
			"  KEY_KP2                 80\n"
			"  KEY_KP3                 81\n"
			"  KEY_KP0                 82\n"
			"  KEY_KPDOT               83\n\n");
}

void main(int argc, char *argv[])
{
	if(argc < 2)
	{
		printf("Usage : ssignal [KEY_X]\n");
		printf("To see available keys use : -h\n");
		return;
	}
	
	if(strncmp(argv[1],"-h",2)==0)
	{
		list_keys();
		return;
	}
	
	press_button(atoi(argv[1]));
}
