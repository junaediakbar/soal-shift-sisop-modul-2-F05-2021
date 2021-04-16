# soal-shift-sisop-modul-2-F05-2021
## soal1
## soal2
## soal3
Soal3 ini dikerjakan dengan mengimplementasikan materi *Daemon Process* 
yang telah diajarkan pada modul2. <br>
Cara mengimplementasikannya adalah :
```
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>

//include untuk menggunakan fungsi time di C
#include <time.h>

//include untuk menggunakan fungsi wait pada program
#include <wait.h>


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
       
	   
	   //program utama
    
	
	}
}
```
### Soal 3A
Buatlah sebuah program dimana setiap 40 detik membuat sebuah direktori
baru dengan nama sesuai timestamp  [YYYY-mm-dd_HH:ii:ss].<br><br>

Untuk menyelesaikan permasalahan, kami membuat sebuah fungsi yang dapat mengambil waktu
pada saat ini dan menyusunnya sehingga membentuk string yang diinginkan. Berikut fungsinya :
```
char* getTime(time_t now){
    struct tm *timeInfo = localtime(&now);
    char *current = (char *)calloc(80, sizeof(char));
    strftime (current, 80, "%Y-%m-%d_%H:%M:%S", timeInfo);
    return current;
}
```
Penjelasan mengenai perintah perintah diatas adalah :
- `struct tm *timeInfo = localtime(&temp);` digunakan untuk menyimpan data time_t yang telah dioper
ke dalam sebuah struct dan memasangkannya sesuai dengan handlernya masing - masing.
- `char *current = (char *)calloc(80, sizeof(char));` digunakan untuk membuat string yang akan menyimpan 
hasil akhir dari fungsi.
- `strftime (current, 80, "%Y-%m-%d_%H:%M:%S", timeInfo);` digunakan untuk memasukkan waktu kedalam string
hasil sesuai dengan format yang diminta pada soal.


<br><br> Sedangkan pada program utamanya (*yang dituliskan setelah while*), berisikan :
```
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

sleep(40)
```
Penjelasan mengenai perintah perintah diatas adalah :
- `pid_t child_id;` digunakan untuk menyimpan nilai PID dari child_id yang akan dibuat.
- `char *builder = NULL;` akan digunakan untuk menyimpan string folder yang terbentuk
dari fungsi getTime yang sebelumnya telah dibuat.
- `current = time(NULL);` digunakan untuk megambil dan menyimpan data waktu saat ini dalam
EPOCH seconds ke dalam variabel current yang telah dibuat.
- `child_id = fork();` digunakan untuk membuat proses baru untuk membuat directory.
- `sleep(40)`, setelah membuat folder, proses akan menunggu ke 40 detik selanjutnya.<br><br>

Ketika proses dijalankan, ilustrasi pada working directory akan terlihat sebagai berikut :<br>
<img src="images/soal3/3a.png">

### Soal 3B
Isi direkotori yang telah dibuat dengan 10 gambar dari *https://picsum.photos/*. Setiap 
gambar didownload setiap 5 detik, dengang bentuk persegi berukuran (n%1000) + 50 pixel 
dimana n adalah detik Epoch Unix. Penamaan untuk setiap gambar adalah [YYYY-mm-dd_HH:ii:ss]<br><br>

Dengan demikian, pada program utama ditambahkan perintah - perintah berikut :
```
...

pid_t child_id1;
child_id1 = fork();
if (child_id1 < 0) {
exit(EXIT_FAILURE);
}

//proses mengambil 10 gambar
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
	...
```
Penjelasan mengenai perintah perintah diatas adalah :
- `child_id1 = fork();` digunakan untuk membuat proses baru kembali sebagai handler "proses pada setiap folder yang dibuat"
- `child_id2 = fork();` digunakan untuk membuat proses baru kembali sebagai handler "proses pengambilan gambar satu persatu"
- `current = time(NULL);` digunakan untuk megambil dan menyimpan data waktu saat ini dalam EPOCH seconds
ke dalam variabel current yang telah dibuat.
- `char *builder2 = NULL;` , `char *postDir = (char *)calloc(160, sizeof(char));`,
`char *link = (char *)calloc(80, sizeof(char));` digunakan untuk menyimpan string yang akan membantu jalannya program.
- `sprintf([s1], [format], [s2])` digunakan untuk menyimpan susunan string yang ditentukan [format] berdasarkan source string [s2] tertentu ke dalam 
suatu string tujuan [s1].
- `execv("/usr/bin/wget", argv2);` digunakan untuk menjalankan perintah wget untuk mendownload file.

Ketika proses dijalankan, pada directory yang telah dibuat di proses 3a ilustrasinya akan terlihat sebagai berikut :<br>
<img src="images/soal3/3b.png">


### Soal 3C
Setelah file direktori diisi 10 gambar, buat file "status.txt" yang isinya hasil ekripsi dari string "Download Success"
dengan shift 5 menggunakan Caesar Chiper. Setelah selesai ditambahkan, zip direktori tersebut, kemudian delete directorynya sehingga yang tersisa
hanyalah file hasil zip saja.<br><br>

Karena pada perintah soal diinstruksikan memasukkan algoritma Caesar Chiper, maka ditambahkan fungsi :
```

...

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

...

```

Penjelasan mengenai perintah perintah diatas adalah :
- `char *ans = (char *)calloc(80, sizeof(char));` digunakan untuk membuat string yang akan menyimpan
jawaban.
- `ch = message[i];` mengambil karakter dari source string yang diberikan.
- Untuk mengecek apakah karakter adalah huruf kecil dan huruf besar, dimasukkan perintah 
`if(ch >= 'a' && ch <= 'z')` dan `else if(ch >= 'A' && ch <= 'Z')`.
- Jika iya, maka `ch = ch + s;` untuk menambahkan shift pada karakter.
- Jika nilai ASCII dari hasil penjumlahan melebihi range ASCII karakter alfabet, maka
fungsi akan menghandle dengan `ch = ch - 'Z' + 'A' - 1;` dan `ch = ch - 'z' + 'a' - 1;`.
- `else if(ch == ' ')` digunakan untuk menghandle karakter spasi.<br><br>

Sedangkan, pada program utama juga ditambahkan perintah :
```
while ((wait(&status)) > 0);

//Buat Status.TXT di folder sebelum di zipping
	char *temp = (char *)calloc(80, sizeof(char));
	sprintf(temp, "%s", "Download Success");
	int s = 5;

	char *isi = (char *)calloc(80, sizeof(char));
	isi = encrypt(temp, s);

	//susun direktori tujuan (file status.txt)
	char *postDir2 = (char *)calloc(240, sizeof(char));
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
		execv("/usr/bin/zip", argv4);
	}

	//perintah hapus directory yang telah dibuat (setelah proses zipping selesai)
	while((wait(&status)) > 0){
		char *argv5[] = {"rm", "-r", builder, NULL};
		execv("/usr/bin/rm", argv5);
```

Penjelasan mengenai perintah perintah diatas adalah :
- `while ((wait(&status)) > 0);` digunakan untuk menunggu proses sebelumnya telah selesai dijalankan.
- `isi = encrypt(temp, s);` untuk menjalankan fungsi enkripsi yang telah dibuat sebelumnya.
- `sprintf(postDir2, "./%s/status.txt", builder);` untuk menyusun string lokasi dari *status.txt* yang
akan dibuat.
- Untuk membuat file *status.txt*, digunakan perintah `fp = fopen(postDir2, "a+");` sekaligus
memberikan akses read (r) dan appending (a) pada file *status.txt* yang telah dibuat.
- `fprintf(fp,"%s", isi);` digunakan untuk menuliskan string hasil enkripsi (*[isi]*) 
ke dalam *status.txt*.
- `child_id4 = fork();` digunakan untuk membuat proses baru kembali sebagai handler "proses zipping".
- `execv("/usr/bin/zip", argv4);` digunakan untuk menjalankan perintah zip file dengan nama
yang telah ditentukan ke lokasi tertentu.
 - `execv("/usr/bin/rm", argv5);` digunakan untuk menjalankan perintah remove recursive untuk menghapus
 directory sehingga menyisakan file zip saja.
 
Ketika proses pembuatan *status.txt* dijalankan, pada directory yang telah dibuat di proses 3a ilustrasinya akan terlihat sebagai berikut :<br>
<img src="images/soal3/3cAfterTouch.PNG">

<br> Di dalam *status.txt* akan terlihat string hasil enkripsi yang telah dibuat :<br>
<img src="images/soal3/3cStatusTxt.PNG">

<br> Setelah itu, akan terbentuk proses untuk zip dan juga remove directory yang telah kita buat. Ilustrasi gambarnya adalah sebagai berikut :
<img src="images/soal3/3cZipInside.PNG">

### Soal 3D
Belum ada ide cara membuat 2 executable program dari satu source code<br>

### Soal 3E
Melihat soal 3 ini pengerjaannya berkelanjutan (kontinu dari A - E), jadi 3E belum dicoba karena 3D masih belum.
