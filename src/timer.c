/*
 * setitimer.c - simple use of the interval timer
 */

#include <sys/time.h>       /* for setitimer */
#include <unistd.h>     /* for pause */
#include <signal.h>     /* for signal */
#include <stdio.h>
#include <stdlib.h>
#include "deadman_client.h"

#define INTERVAL 5000       /* number of milliseconds to go off */

/* function prototype */
void DoStuff(void);

int main(int argc, char *argv[]) {

  struct itimerval it_val;  /* for setting itimer */

  /* Upon SIGALRM, call DoStuff().
   * Set interval timer.  We want frequency in ms, 
   * but the setitimer call needs seconds and useconds. */
  if (signal(SIGALRM, (void (*)(int)) DoStuff) == SIG_ERR) {
    perror("Unable to catch SIGALRM");
    exit(1);
  }
  it_val.it_value.tv_sec =     INTERVAL/1000;
  it_val.it_value.tv_usec =    (INTERVAL*1000) % 1000000;   
  it_val.it_interval = it_val.it_value;
  if (setitimer(ITIMER_REAL, &it_val, NULL) == -1) {
    perror("error calling setitimer()");
    exit(1);
  }

  while (1) 
    pause();

}

int doStuff = 1;
/*
 * DoStuff
 */
void DoStuff(void) {
	if (doStuff) {
		doStuff = 0;
        printf("Do stuff\n");
		/*// make connection to deadman switch*/
		/*// make connection add state*/
        printf("Checking deadman switch\n");
        int deadmanSwitchReply = callClient();
        if (deadmanSwitchReply == 0) {
            // kill the dragon controller
            printf("Kill dragon controller.\n");
        } else if (deadmanSwitchReply == 1) {
            //do nothing
            printf("Do nothing\n");
            doStuff = 1;
            deadmanSwitchReply = 0;
        } else {
            //there is a bug in callClient
            //kill the dragon controller
            printf("Kill dragon controller.\n");
        }
	} else {
		// kill dragon controller
	    printf("Kill dragon controller.\n");
        /*doStuff = 1;*/
	}
}


