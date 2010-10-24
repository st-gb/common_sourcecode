//This file's extension should be ".cpp" in order to compile with g++.

//from http://www-theorie.physik.unizh.ch/~dpotter/howto/daemonize:
#include <stdio.h> //freopen(...)
#include <stdlib.h> //exit(...)
#include <string.h> //strerror(...)
#include <unistd.h> //setsid(...)
#include <sys/types.h> //for "pid_t"
#include <sys/stat.h> //mode_t umask(mode_t cmask);
#include <fcntl.h> //open(...)
#include <syslog.h> //syslog(...)
#include <errno.h> //for "errno"
#include <pwd.h> //getpwnam(...)
#include <signal.h> //for signal(...)

/* Change this to whatever your daemon is called */
/*
#define DAEMON_NAME "mydaemon"
*/

/* Change this to the user under which to run */
#define RUN_AS_USER "daemon"

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

static void child_handler(int signum)
{
  switch(signum)
  {
  case SIGALRM: exit(EXIT_FAILURE); break;
  case SIGUSR1: exit(EXIT_SUCCESS); break;
  case SIGCHLD: exit(EXIT_FAILURE); break;
  }
}

void CreateLockFile(const char * lockfile )
{
  int lfp = -1;
  /* Create the lock file as the current user */
  if ( //pointer <> NULL and > 1 character/ 1st char <> 0
      lockfile && lockfile[0] )
  {
    lfp = open(lockfile,O_RDWR|O_CREAT,0640);
    if ( lfp < 0 )
    {
      syslog( LOG_ERR, "unable to create lock file %s, code=%d (%s)",
              lockfile, errno, strerror(errno) );
      exit(EXIT_FAILURE);
    }
  }
}

void DropUser()
{
  /* Drop user if there is one, and we were run as root */
  if ( //root has the user ID 0.
      getuid() == 0 || geteuid() == 0 )
  {
    struct passwd * pw = getpwnam(RUN_AS_USER);
    if ( pw )
    {
      syslog( LOG_NOTICE, "setting user to " RUN_AS_USER );
      setuid( pw->pw_uid );
    }
  }
}

void TrapSignals()
{
  /* Trap signals that we expect to receive */
  signal(SIGCHLD,child_handler);
  signal(SIGUSR1,child_handler);
  signal(SIGALRM,child_handler);
  //SIGHUP = Reload config signal.
  signal(SIGHUP,child_handler);
}

void ForkOffAndDie()
{
  pid_t pid_tOwnProcessID ;
  //http://en.wikipedia.org/wiki/Daemon_%28computer_software%29#Types_of_daemons:
  //"The common method for a process to become a daemon involves:[...]
  //"Staying in the background by forking and exiting (once or twice)."
  /* Fork off the parent process */
  pid_tOwnProcessID = fork();
  if (pid_tOwnProcessID < 0)
  {
    syslog( LOG_ERR, "unable to fork daemon, code=%d (%s)",
            errno, strerror(errno) );
    exit(EXIT_FAILURE);
  }
  /* If we got a good PID, then we can exit the parent process. */
  if (pid_tOwnProcessID > 0)
  {
    /* Wait for confirmation from the child via SIGTERM or SIGCHLD, or
       for two seconds to elapse (SIGALRM).  pause() should not return. */
    alarm(2);
    pause();

    exit(EXIT_FAILURE);
  }
}

void CancelCertainSignals()
{
  /* Cancel certain signals */
  signal(
    //http://en.wikipedia.org/wiki/Signal_%28computing%29#List_of_signals:
    // "Child process terminated, stopped (or continued*)"
    SIGCHLD,
    //http://en.wikipedia.org/wiki/Signal_%28computing%29:
    // "use the default signal handler"
    SIG_DFL); /* A child process dies */
  signal(SIGTSTP,
    //http://en.wikipedia.org/wiki/Signal_%28computing%29:  "ignore the signal"
    SIG_IGN); /* Various TTY signals */
  signal(SIGTTOU,
    //http://en.wikipedia.org/wiki/Signal_%28computing%29:  "ignore the signal"
    SIG_IGN);
  signal(SIGTTIN,
    //http://en.wikipedia.org/wiki/Signal_%28computing%29:  "ignore the signal"
    SIG_IGN);
  signal(//http://en.wikipedia.org/wiki/Signal_%28computing%29#List_of_signals:
    //"Hangup"
    SIGHUP,
    //http://en.wikipedia.org/wiki/Signal_%28computing%29:  "ignore the signal"
    SIG_IGN); /* Ignore hangup signal */
  signal(
    //http://en.wikipedia.org/wiki/Signal_%28computing%29#List_of_signals:
    // "Termination (request to terminate)"
    SIGTERM,
    //http://en.wikipedia.org/wiki/Signal_%28computing%29:
    // "use the default signal handler"
    SIG_DFL); /* Die on SIGTERM */
}

void CreateSessionID()
{
  pid_t sid ;
  /* Create a new SID for the child process */
  sid = setsid();
  if ( //http://www.opengroup.org/onlinepubs/009695399/functions/setsid.html:
    //"Otherwise, it shall return (pid_t)-1 and set errno to indicate the
    // error."
    sid < 0 )
  {
    syslog( LOG_ERR, "unable to create a new session, code %d (%s)",
            errno, strerror(errno) );
    exit(EXIT_FAILURE);
  }
}

void SetRootDirAsCurrentDir()
{
  //http://en.wikipedia.org/wiki/Daemon_%28computer_software%29#Types_of_daemons:
  //* Setting the root directory ("/") as the current working directory so that
  //  the process will not keep any directory in use that may be on a mounted
  //  file system (allowing it to be unmounted).
  /* Change the current working directory.  This prevents the current
     directory from being locked; hence not being able to remove it. */
  if ( ( chdir("/") ) < 0)
  {
    syslog( LOG_ERR, "unable to change directory to %s, code %d (%s)",
            "/", errno, strerror(errno) );
    exit(EXIT_FAILURE);
  }
}

void CloseInheritedOpenFiles()
{
  //"Closing all inherited open files at the time of execution that are left
  //  open by the parent process, including file descriptors 0, 1 and 2
  //  (stdin, stdout, stderr)."
  /* Redirect standard files to /dev/null */
  FILE * p_file ;
  //Assign return value to avoid g++ warning "ignoring return value of
  // ‘freopen’, declared with attribute warn_unused_result" "
  p_file = freopen( "/dev/null", "r", stdin);
  //Assign return value to avoid g++ warning "ignoring return value of
  // ‘freopen’, declared with attribute warn_unused_result" "
  p_file = freopen( "/dev/null", "w", stdout);
  //Assign return value to avoid g++ warning "ignoring return value of
  // ‘freopen’, declared with attribute warn_unused_result" "
  p_file = freopen( "/dev/null", "w", stderr);
}

//http://en.wikipedia.org/wiki/Daemon_%28computer_software%29#Types_of_daemons:
//"The common method for a process to become a daemon involves:
//* Dissociating from the controlling tty
//* Becoming a session leader
//* Becoming a process group leader
//* Staying in the background by forking and exiting (once or twice). This is
//  required sometimes for the process to become a session leader. It also
//  allows the parent process to continue its normal execution. This idiom is
//  sometimes summarized with the phrase "fork off and die"
//* Setting the root directory ("/") as the current working directory so that
//  the process will not keep any directory in use that may be on a mounted
//  file system (allowing it to be unmounted).
//* Changing the umask to 0 to allow open(), creat(), et al. calls to provide
//  their own permission masks and not to depend on the umask of the caller
//* Closing all inherited open files at the time of execution that are left
//  open by the parent process, including file descriptors 0, 1 and 2
//  (stdin, stdout, stderr). Required files will be opened later.
//* Using a logfile, the console, or /dev/null as stdin, stdout, and stderr
//static
void daemonize(
  //http://www-theorie.physik.unizh.ch/~dpotter/howto/daemonize:
  // "Creates a lock file to prevent the daemon from being run twice."
  const char * lockfile )
{
  pid_t parent;

  /* Parent process ID is the ID of "init" / already a daemon */
  if ( getppid() == 1 )
    return;

  CreateLockFile(lockfile) ;

  DropUser() ;

  TrapSignals() ;

  ForkOffAndDie() ;

  /* At this point we are executing as the child process */
  parent = getppid();

  CancelCertainSignals() ;

  /* Change the file mode mask */
  umask(0);

  CreateSessionID() ;

//  SetRootDirAsCurrentDir() ;

  CloseInheritedOpenFiles() ;

  /* Tell the parent process that we are A-okay */
  kill( parent, SIGUSR1 );
}
