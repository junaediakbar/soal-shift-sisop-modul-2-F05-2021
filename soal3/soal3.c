#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <time.h>
#include <wait.h>

char* getTime(){
  time_t current;
  struct tm * timeInfo;
  char *now = (char *)calloc(80, sizeof(char));

  time (&current);
  timeInfo = localtime (&current);
  strftime (now, 80, "%Y-%m-%d_%H:%M:%S", timeInfo);

  return now;
}

int main() {
  pid_t pid, sid;        // Variabel untuk menyimpan PID

  pid = fork();     // Menyimpan PID dari Child Process

  /* Keluar saat fork gagal
  * (nilai variabel pid < 0) */
  if (pid < 0) {
    exit(EXIT_FAILURE);
  }

  /* Keluar saat fork berhasil
  * (nilai variabel pid adalah PID dari child process) */
  if (pid > 0) {
    exit(EXIT_SUCCESS);
  }

  umask(0);

  sid = setsid();
  if (sid < 0) {
    exit(EXIT_FAILURE);
  }

  if ((chdir("/home/ardo/Sisop/Praktikum/modul2")) < 0) {
    exit(EXIT_FAILURE);
  }

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);


  while (1) {
    pid_t child_id;
    int status = 0;
    char *builder = NULL;
    char *builder2 = NULL;
    char *tempTime = NULL;

    child_id = fork();

    if (child_id < 0) {
      exit(EXIT_FAILURE); // Jika gagal membuat proses baru, program akan berhenti
    }

    if (child_id == 0) {
      builder = getTime();
      char *argv[] = {"mkdir", "-p", builder, NULL};
      execv("/bin/mkdir", argv);
    }
    else{

    }

    sleep(40);
  }
}