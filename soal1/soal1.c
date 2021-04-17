#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <dirent.h>
#include <wait.h>
#include <string.h>
#include <time.h>
 
int checkdirexist(char *pathname)
{
    struct stat info;
    if (stat(pathname, &info) != 0)
    {
        return 0;
    }
    else if (info.st_mode & S_IFDIR)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
 
void makedir(char *lokasi)
{
    pid_t child, child1, child2, child3, child4, child5, child6;
    int status;
    child = fork();
 
    if (child == 0)
    {
        char *argv[] = {"mkdir", "-p", lokasi, NULL};
        execv("/bin/mkdir", argv);
    }
}
void extract(char *src, char *dest, char *foltype, char *origin)
{
    pid_t child;
    int status;
    child = fork();
 
    if (child == 0)
    {
        printf("===%s===", src);
        char *argv[] = {"unzip", src, "-d", origin, NULL};
        execv("/usr/bin/unzip", argv);
    }
 
    while ((waitpid(child, &status, 0)) > 0)
        ;
    pid_t child1 = fork();
 
    if (child1 == 0)
    {
        printf("====================%s================", foltype);
        char *argv[] = {"find", foltype, "-mindepth", "1", "-type", "f", "-exec", "mv",
                        "-t", dest, "{}", "+", NULL};
        execv("/usr/bin/find", argv);
    }
 
    while ((waitpid(child1, &status, 0)) > 0)
        ;
    pid_t child2 = fork();
 
    if (child2 == 0)
    {
        char *argv[] = {"rm", "-r", foltype, NULL};
        execv("/bin/rm", argv);
    }
    while ((waitpid(child2, &status, 0)) > 0)
        ;
    pid_t child3 = fork();
 
    if (child3 == 0)
    {
        char *argv[] = {"rm", "-r", src, NULL};
        execv("/bin/rm", argv);
    }
}
 
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
 
    if ((chdir("/")) < 0)
    {
        exit(EXIT_FAILURE);
    }
 
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
 
    while (1)
    {
        // Tulis program kalian di sini
        time_t now;
        struct tm *now_tm;
        int hour, min, sec, date, mon;
        now = time(NULL);
        now_tm = localtime(&now);
        hour = now_tm->tm_hour;
        min = now_tm->tm_min;
        sec = now_tm->tm_sec;
        date = now_tm->tm_mday;
        mon = now_tm->tm_mon;
        mon += 1;
 
        int shour, smin, sdate, smon;
        shour = 22;
        smin = 22;
        sdate = 9;
        smon = 4;
        char path[100] = {"/home/raharja/modul2-1/"};
        char pathfilm[100] = {"/home/raharja/modul2-1/Fylm"};
        char pathmusik[100] = {"/home/raharja/modul2-1/Musyik"};
        char pathfoto[100] = {"/home/raharja/modul2-1/Pyoto"};
        char linkfilm[100] = {"https://drive.google.com/uc?id=1ktjGgDkL0nNpY-vT7rT7O6ZI47Ke9xcp&export=download"};
        char linkmusik[100] = {"https://drive.google.com/uc?id=1ZG8nRBRPquhYXq_sISdsVcXx5VdEgi-J&export=download"};
        char linkfoto[100] = {"https://drive.google.com/uc?id=1FsrAzb9B5ixooGUs0dGiBr-rC7TS9wTD&export=download"};
        char locmusik[100] = {"/home/raharja/modul2-1/Musyik/Musik_for_Stevany.zip"};
        char locfoto[100] = {"/home/raharja/modul2-1/Fyoto/Foto_for_Stevany.zip"};
        char locfilm[100] = {"/home/raharja/modul2-1/Fylm/Film_for_Stevany.zip"};
        if (hour == shour - 6 && min == smin && date == sdate && mon == smon)
        {
            FILE *fptr;
            char fname[50] = {"/home/raharja/modul2-1/jam.txt"};
            fptr = fopen(fname, "a+");
            fprintf(fptr, "the date is %d/ %d and the time is %d : %d : %d\n", date, mon, hour, min, sec);
            fclose(fptr);
            pid_t child,
                child1, child2, child3, child4, child5, child6;
            int status;
            makedir("/home/raharja/modul2-1/Musyik");
            makedir("/home/raharja/modul2-1/Pyoto");
            makedir("/home/raharja/modul2-1/Fylm");
            sleep(5);
            child = fork();
 
            if (child == 0)
            {
 
                printf("sudah di download\n");
                char *argv[] = {"wget", "--no-check-certificate", linkmusik, "-O", "/home/raharja/modul2-1/Musik_for_Stevany.zip""Musyik.zip", NULL};
                execv("/usr/bin/wget", argv);
            }
            while ((waitpid(child, &status, 0)) > 0)
                ;
            child1 = fork();
            if (child1 == 0)
            {
 
                printf("sudah di download\n");
                char *argv[] = {"wget", "--no-check-certificate", linkfoto, "-O", "/home/raharja/modul2-1/Foto_for_Stevany.zip", NULL};
                execv("/usr/bin/wget", argv);
            }
            while ((waitpid(child1, &status, 0)) > 0)
                ;
            child2 = fork();
            if (child2 == 0)
            {
 
                printf("sudah di download\n");
                char *argv[] = {"wget", "--no-check-certificate", linkfilm, "-O", "/home/raharja/modul2-1/Film_for_Stevany.zip", NULL};
                execv("/usr/bin/wget", argv);
            }
            while ((waitpid(child2, &status, 0)) > 0)
                ;
            child3 = fork();
            if (child3 == 0)
            {
                extract(locmusik, "/home/raharja/modul2-1/Musyik", "/home/raharja/modul2-1//MUSIK", path);
                extract(locfoto, "/home/raharja/modul2-1/Pyoto", "/home/raharja/modul2-1//FOTO", path);
                extract(locfilm, "/home/raharja/modul2-1/Fylm", "/home/raharja/modul2-1//FILM", path);
            }
        }
 
        sleep(3);
    }
    exit(EXIT_SUCCESS);
}
