#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define USB_PRINTER_HANDLE_PID_FILE "/var/run/pofd.pid"
int parse_pid_files(char *pid_file, int *pid, int *sigAddNum, int *sigRmvNum)
{       
        struct stat pstat;
        FILE *pid_fp = NULL;
        char line[256] = {[0 ... 255] = 0};

        if ( stat(pid_file, &pstat) != 0)
        {
                printf( "Cannot stat pid_file(%s)! do nothing and return!\n", pid_file);
                return -1;
        }

        if ( (pid_fp = fopen(pid_file, "r")) == NULL) {
                printf( "fopen pid_file(%s) failed! do nothing and return!\n", pid_file);
                
                return -1;
        }

        if (fgets(line, 255, pid_fp) != NULL)
        {
                char progname[128] = {[0 ... 127] = 0};
                int num = 0;
                
                if ( (num = sscanf(line, "%d %s %d %d", pid, progname, sigAddNum, sigRmvNum)) != 4 ) {
                        printf( "sscanf return number=%d!", num);
                        return -1;
                }
                
                printf( "After successful reading from handle file, the pid=%d, progname=%s, sig_add_num=0x%x, sig_rmv_num=0x%x!\n", 
                                        *pid, progname, *sigAddNum, *sigRmvNum);
                fclose(pid_fp);
        }

        return 0;
}
int main()
{       
	int pid;
    int sigAddNum = -1;
    int sigRmvNum = -1;        
    if (parse_pid_files(USB_PRINTER_HANDLE_PID_FILE, &pid,  &sigAddNum, &sigRmvNum) != 0)
    	return -1;
    if (sigAddNum < 0 || sigRmvNum < 0)
        return -1;        
    kill(pid, sigRmvNum);
    return 0;
}
