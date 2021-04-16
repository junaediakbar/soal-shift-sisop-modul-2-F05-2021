#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <wait.h>
#include <time.h>
void ganti(char *lokasi, char *file, char *nama);
void pindah(char *lokasi, char *file, char *nama)
{
  int status;

  pid_t child2 = fork();
  if (child2 == 0)
  {
    char *argv[] = {"mkdir", "-p", lokasi, NULL};
    execv("/bin/mkdir", argv);
  }
  while ((waitpid(child2, &status, 0)) > 0)
    ;
  pid_t child3 = fork();

  if (child3 == 0)
  {
    char nick[100];
    char petname[100];
    char umur[100];
    char ket[100];

    strcpy(nick, nama);
    char delim[] = ";";
    char *ptr = strtok(nick, delim);
    int id = 1;

    while (ptr != NULL)
    {
      if (id == 2)
      {
        sprintf(petname, "%s", ptr);
      }
      if (id == 3)
      {
        sprintf(umur, "%s", ptr);
        strtok(umur, "_");
        strtok(umur, "j");
        if (umur[strlen(umur) - 1] == '.')
        {
          umur[strlen(umur) - 1] = '\0';
        }
      }
      ptr = strtok(NULL, delim);
      id++;
    }

    char loc[100];
    strcpy(ket, lokasi);
    strcpy(loc, lokasi);
    strcat(loc, "/");
    strcat(loc, petname);
    strcat(loc, ".jpg");

    FILE *fptr;
    char st[100];
    char fname[50];
    strcpy(fname, lokasi);
    strcat(fname, "/keterangan.txt");
    fptr = fopen(fname, "a+");

    fprintf(fptr, "nama : %s\n", petname);
    fprintf(fptr, "umur : %s tahun\n\n", umur);

    fclose(fptr);

    char *argv[] = {"mv", file, loc, NULL};
    execv("/bin/mv", argv);
  }
}
void copy(char *src, char *dest)
{
  pid_t child1 = fork();
  if (child1 == 0)
  {
    char *argv[] = {"cp", src, dest, NULL};
    execv("/bin/cp", argv);
  }
}

int main()
{
  pid_t child, child1, child2, child3, child4, child5, child6;
  int status;
  child = fork();
  if (child == 0)
  {
    char *argv[] = {"unzip", "/home/juned/modul2/pets.zip", "-d",
                    "/home/juned/modul2/petshop", NULL};
    execv("/usr/bin/unzip", argv);
  }
  while ((waitpid(child, &status, 0)) > 0)
    ;
  child1 = fork();
  if (child1 == 0)
  {
    char *argv[] = {"find", "/home/juned/modul2/petshop", "-mindepth", "1", "-type", "d", "-exec", "rm",
                    "-r", "{}", "+", NULL};
    execv("/usr/bin/find", argv);
  }

  while ((waitpid(child1, &status, 0)) > 0)
    ;
  child2 = fork();
  if (child2 == 0)
  {
    DIR *dp;
    struct dirent *ep;
    char path[] = {"/home/juned/modul2/petshop"};

    dp = opendir(path);

    if (dp != NULL)
    {
      while ((ep = readdir(dp)))
      {
        //puts(ep->d_name);

        char str[100];

        char new[100];
        memset(str, 0, sizeof(str));
        memset(new, 0, sizeof(new));
        strcpy(str, ep->d_name);

        if (ep->d_name[0] != '.')
        {
          int i = 0;

          while (str[i] != ';')
          {
            new[i] = str[i];
            i++;
            if (str[i] == ';')
            {
              break;
            }
          }
          i = 0;
          char lokasi[100] = {"/home/juned/modul2/petshop/"};
          char file[100] = {"/home/juned/modul2/petshop/"};

          strcat(lokasi, new);
          strcat(file, ep->d_name);
          if (strchr(str, '_') != NULL)
          {

            char file[100];
            strcpy(file, str);
            char *file2 = strtok(file, "_");
            file2 = strtok(NULL, "_");
            char fol2[100];
            strcpy(fol2, file2);
            char *folder2 = strtok(fol2, ";");

            char src[100] = {"/home/juned/modul2/petshop/"};
            char src2[100] = {"/home/juned/modul2/petshop/"};
            char dest[100] = {"/home/juned/modul2/petshop/"};
            strcat(src, str);
            strcat(dest, file2);
            copy(src, dest);
            strcat(src2, folder2);
            pindah(src2, dest, file2);
          }
          pindah(lokasi, file, ep->d_name);
        }
      }

      (void)closedir(dp);
    }
    else
      perror("Couldn't open the directory");
  }
}