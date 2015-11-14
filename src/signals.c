/*
  SillyMUD Distribution V1.1b             (c) 1993 SillyMUD Developement
 
  See license.doc for distribution terms.   SillyMUD is based on DIKUMUD
*/

#include <signal.h>
#include <stdio.h>
#include <sys/time.h>

#include "protos.h"

void checkpointing(int);
void shutdown_request(int);
void logsig(int);
void hupsig(int);

void raw_force_all( char *to_force);

void signal_setup()
{
	struct itimerval itime;
	struct timeval interval;

	signal(SIGUSR2, shutdown_request);

	/* just to be on the safe side: */

	signal(SIGHUP, hupsig);
	signal(SIGPIPE, SIG_IGN);
	signal(SIGINT, hupsig);
	signal(SIGALRM, logsig);
	signal(SIGTERM, hupsig);

	/* set up the deadlock-protection */

	interval.tv_sec = 900;    /* 15 minutes */
	interval.tv_usec = 0;
	itime.it_interval = interval;
	itime.it_value = interval;
	setitimer(ITIMER_VIRTUAL, &itime, 0);
	signal(SIGVTALRM, checkpointing);
}



void checkpointing(int sig)
{
  extern int tics;
	
  if (!tics)
    {
      log_msg("CHECKPOINT shutdown: tics not updated");
      abort();
    }
  else
    tics = 0;
}




void shutdown_request(int sig)
{
	extern int mudshutdown;

	log_msg("Received USR2 - shutdown request");
	mudshutdown = 1;
}


/* kick out players etc */
void hupsig(int sig)
{
  int i;
  extern int mudshutdown, should_reboot;

  log_msg("Received SIGHUP, SIGINT, or SIGTERM. Shutting down");

  raw_force_all("return");
  raw_force_all("save");
  for (i=0;i<30;i++) {
    SaveTheWorld();
  }
  mudshutdown = should_reboot = 1;
}

void logsig(int sig)
{
	log_msg("Signal received. Ignoring.");
}
