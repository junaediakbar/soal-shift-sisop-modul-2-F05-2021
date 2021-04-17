#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <wait.h>
#include <dirent.h>
 
int main()
{
    pid_t pid, sid; // Variabel untuk menyimpan PID
 
    pid = fork(); // Menyimpan PID dari Child Process
 
    /* Keluar saat fork gagal
  * (nilai variabel pid < 0) */
    if (pid < 0)
    {
        exit(EXIT_FAILURE);
    }
 
    /* Keluar saat fork berhasil
  * (nilai variabel pid adalah PID dari child process) */
    if (pid > 0)
    {
        exit(EXIT_SUCCESS);
    }
 
    umask(0);
 
    sid = setsid();
    if (sid < 0)
    {
        exit(EXIT_FAILURE);
    }
 
    if ((chdir("/home/juned/modul2-1")) < 0)
    {
        exit(EXIT_FAILURE);
    }
 
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
 
    int status, status1, status2, status3, status4, status5, status6, status7, status8, status9, status10, status11, status12;
 
    while (1)
    {
        char path[100] = {"/home/juned/modul2-1/"};
        char pathfilm[100] = {"/home/juned/modul2-1/Fylm"};
        char pathmusik[100] = {"/home/juned/modul2-1/Musyik"};
        char pathfoto[100] = {"/home/juned/modul2-1/Fyoto"};
        char linkfilm[100] = {"https://drive.google.com/uc?id=1ktjGgDkL0nNpY-vT7rT7O6ZI47Ke9xcp&export=download"};
        char linkmusik[100] = {"https://drive.google.com/uc?id=1ZG8nRBRPquhYXq_sISdsVcXx5VdEgi-J&export=download"};
        char linkfoto[100] = {"https://drive.google.com/uc?id=1FsrAzb9B5ixooGUs0dGiBr-rC7TS9wTD&export=download"};
        char locmusik[100] = {"/home/juned/modul2-1/Musik_for_Stevany.zip"};
        char locfoto[100] = {"/home/juned/modul2-1/Foto_for_Stevany.zip"};
        char locfilm[100] = {"/home/juned/modul2-1/Fylm.zip"};
        pid_t child, child1, child2, child3, child4, child5, child6, child7, child8, child9, child10, child11, child12, child13, child14, child15, child16, child17, child18;
 
        time_t now = time(NULL);
        struct tm *t = localtime(&now);
 
        //soal e
        if (t->tm_mon == 3 && t->tm_mday == 9 && t->tm_hour == 16 && t->tm_min == 22 && t->tm_sec == 0)
        {
            child = fork();
            if (child < 0)
                exit(0);
            if (child == 0)
            {
                //Soal 1a
                child1 = fork();
                if (child1 < 0)
                    exit(0);
                if (child1 == 0)
                {
                    char *argv[] = {"mkdir", "-p", pathmusik, NULL};
                    execv("/bin/mkdir", argv);
                }
                child2 = fork();
                if (child2 < 0)
                    exit(0);
                if (child2 == 0)
                {
                    char *argv[] = {"mkdir", "-p", pathfoto, NULL};
                    execv("/bin/mkdir", argv);
                }
                child3 = fork();
                if (child3 < 0)
                    exit(0);
                if (child3 == 0)
                {
                    char *argv[] = {"mkdir", "-p", pathfilm, NULL};
                    execv("/bin/mkdir", argv);
                }
                //Soal 1b
                while (wait(&status) > 0)
                    ;
                child4 = fork();
                if (child4 < 0)
                    exit(0);
                if (child4 == 0)
                {
                    printf("sudah didownload\n");
                    char *arg[] = {"wget", "--no-check-certificate", linkmusik, "-O", "Musik_for_Stevany.zip", "-o", "/dev/null", NULL};
                    execv("/usr/bin/wget", arg);
                }
                while (wait(&status1) > 0)
                    ;
                child5 = fork();
                if (child5 < 0)
                    exit(0);
                if (child5 == 0)
                {
                    printf("sudah didownload\n");
                    char *arg[] = {"wget", "--no-check-certificate", linkfoto, "-O", "Foto_for_Stevany.zip", "-o", "/dev/null", NULL};
                    execv("/usr/bin/wget", arg);
                }
                while (wait(&status2) > 0)
                    ;
                child6 = fork();
                if (child5 < 0)
                    exit(0);
                if (child6 == 0)
                {
                    printf("sudah didownload\n");
                    char *arg[] = {"wget", "--no-check-certificate", linkfilm, "-O", "Film_for_Stevany.zip", "-o", "/dev/null", NULL};
                    execv("/usr/bin/wget", arg);
                }
                //soal1c
                while (wait(&status3) > 0)
                    ;
                child7 = fork();
                if (child7 < 0)
                    exit(0);
                if (child7 == 0)
                {
                    char *arg[] = {"unzip", "-o", "-q", "./Musik_for_Stevany.zip", NULL};
                    execv("/usr/bin/unzip", arg);
                }
                while (wait(&status4) > 0)
                    ;
                child8 = fork();
                if (child8 < 0)
                    exit(0);
                if (child8 == 0)
                {
                    char *arg[] = {"unzip", "-o", "-q", "./Foto_for_Stevany.zip", NULL};
                    execv("/usr/bin/unzip", arg);
                }
                while (wait(&status5) > 0)
                    ;
                child9 = fork();
                if (child9 < 0)
                    exit(0);
                if (child9 == 0)
                {
                    char *arg[] = {"unzip", "-o", "-q", "./Film_for_Stevany.zip", NULL};
                    execv("/usr/bin/unzip", arg);
                }
 
                // Soal 1d
                while (wait(&status6) > 0)
                    ;
                child10 = fork();
                if (child10 < 0)
                    exit(0);
                if (child10 == 0)
                {
                    char *argv[] = {"find", "./MUSIK", "-mindepth", "1", "-type", "f", "-exec", "mv",
                                    "-t", "./Musyik", "{}", "+", NULL};
                    execv("/usr/bin/find", argv);
                }
                while (wait(&status7) > 0)
                    ;
                child11 = fork();
                if (child11 < 0)
                    exit(0);
                if (child11 == 0)
                {
                    char *argv[] = {"find", "./FOTO", "-mindepth", "1", "-type", "f", "-exec", "mv",
                                    "-t", "./Fyoto", "{}", "+", NULL};
                    execv("/usr/bin/find", argv);
                }
                while (wait(&status8) > 0)
                    ;
                child12 = fork();
                if (child12 < 0)
                    exit(0);
                if (child12 == 0)
                {
                    char *argv[] = {"find", "./FILM", "-mindepth", "1", "-type", "f", "-exec", "mv",
                                    "-t", "./Fylm", "{}", "+", NULL};
                    execv("/usr/bin/find", argv);
                }
                //Hapus File
                while (wait(&status9) > 0)
                    ;
                child13 = fork();
                if (child13 < 0)
                    exit(0);
                if (child13 == 0)
                {
                    char *argv[] = {"rm", "-r", "Musik_for_Stevany.zip", "Foto_for_Stevany.zip", "Film_for_Stevany.zip", NULL};
                    execv("/bin/rm", argv);
                }
                while (wait(&status10) > 0)
                    ;
                exit(0);
            }
        }
 
        //soal f
        else if (t->tm_mon == 3 && t->tm_mday == 9 && t->tm_hour == 22 && t->tm_min == 22 && t->tm_sec == 0)
        {
            child14 = fork();
            if (child14 == 0)
            {
                child15 = fork();
                if (child15 < 0)
                    exit(0);
                if (child15 == 0)
                {
                    char *arg[] = {"zip", "-q", "-rm", "Lopyu_Stevany.zip", "./Musyik", "./Fylm", "./Fyoto", NULL};
                    execv("/usr/bin/zip", arg);
                }
                while (wait(&status11) > 0)
                    ;
                child16 = fork();
                if (child16 < 0)
                    exit(0);
                if (child16 == 0)
                {
                    char *arg[] = {"rm", "-r", "./MUSIK", "./FILM", "./FOTO", NULL};
                    execv("/bin/rm", arg);
                }
                while (wait(&status11) > 0)
                    ;
                exit(0);
            }
        }
 
        while (wait(&status12) > 0)
            ;
        sleep(1);
    }
}
