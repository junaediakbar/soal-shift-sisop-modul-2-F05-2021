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

//Fungsi menyusun waktu berdasarkan format yang diminta
char* getTime(time_t now){
    struct tm *timeInfo = localtime(&now);
    char *current = (char *)calloc(80, sizeof(char));
    strftime (current, 80, "%Y-%m-%d_%H:%M:%S", timeInfo);
    return current;
}

//Algoritma enkripsi caesar cypher
char *encrypt(char *message, int s){
char ch;
char *ans = (char *)calloc(80, sizeof(char));
    for(int i = 0; message[i] != '\0'; ++i){
		ch = message[i];
		
        //handle huruf kecil
		if(ch >= 'a' && ch <= 'z'){
			ch = ch + s;
			
			if(ch > 'z'){
				ch = ch - 'z' + 'a' - 1;
			}
			
			ans[i] = ch;
		}

        //handle kapital
		else if(ch >= 'A' && ch <= 'Z'){
			ch = ch + s;
			
			if(ch > 'Z'){
				ch = ch - 'Z' + 'A' - 1;
			}
			
			ans[i] = ch;
		}
        
        //handle spasi
        else if(ch == ' '){
            ans[i] = ch;
        }
	}
    return ans;
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

    if ((chdir("/home/ardo/Sisop/Praktikum/modul2/")) < 0) {
        exit(EXIT_FAILURE);
    }

    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    //program utama
    while (1) {
        pid_t child_id;
        char *builder = NULL;
        int status;
        
    //Ambil waktu sekarang (untuk folder)
        time_t current;
        current = time(NULL);
        builder = getTime(current);

    //proses membuat folder
        child_id = fork();
        if (child_id < 0) {
            exit(EXIT_FAILURE);
        }

        if (child_id == 0) {
            char *argv[] = {"mkdir", "-p", builder, NULL};
            execv("/usr/bin/mkdir", argv);
        }
        
    // proses untuk setiap folder yang telah dibuat
        pid_t child_id1;
        child_id1 = fork();
        if (child_id1 < 0) {
            exit(EXIT_FAILURE);
        }

        if(child_id1 == 0){
            int i;
            for(i = 1; i <= 10; i++){

            //proses untuk mengambil satu persatu gambar sesuai ketentuan yang diminta
                pid_t child_id2;
                child_id2 = fork();
                if (child_id2 < 0) {
                    exit(EXIT_FAILURE);
                }

                if(child_id2 == 0){
                    current = time(NULL);
                    char *builder2 = NULL;

                    builder2 = getTime(current);

                    char *postDir = (char *)calloc(160, sizeof(char));
                    char *link = (char *)calloc(80, sizeof(char));
                    sprintf(postDir, "./%s/%s", builder, builder2);
                    sprintf(link, "https://picsum.photos/%ld", (current%1000)+50);

                    char *argv2[] = {"wget", "-O", postDir, link, NULL};
                    execv("/usr/bin/wget", argv2);
                }
            sleep(5);
            }
            
            while ((wait(&status)) > 0);

        //Buat Status.TXT di folder sebelum di zipping
            char *temp = (char *)calloc(80, sizeof(char));
            sprintf(temp, "%s", "Download Success");
            int s = 5;

            char *isi = (char *)calloc(80, sizeof(char));
            isi = encrypt(temp, s);

            //susun direktori tujuan (file status.txt)
            char *postDir2 = (char *)calloc(120, sizeof(char));
            sprintf(postDir2, "./%s/status.txt", builder);

            FILE *fp;
            fp = fopen(postDir2, "a+");
            fprintf(fp,"%s", isi);
            fclose(fp);
            
        //proses zipping
            pid_t child_id4;
            child_id4 = fork();
            if (child_id4 < 0) {
                exit(EXIT_FAILURE);
            }

            if(child_id4 == 0){
                char *fileName = (char *)calloc(90, sizeof(char));
                sprintf(fileName, "%s.zip", builder);
                char *argv4[] = {"zip", "-r", fileName, builder, NULL};
                execv("/usr/bin/zip", argv4);sss
            }

            //perintah hapus directory yang telah dibuat (setelah proses zipping selesai)
            while((wait(&status)) > 0){
                char *argv5[] = {"rm", "-r", builder, NULL};
                execv("/usr/bin/rm", argv5);
            }
        }
        sleep(40);
    }
}