#include<pthread.h>
#include<stdio.h>
#include<unistd.h>

void *function1(); //Pembuatan Fungsi 1 untuk melakukan increment
void *function2(); //Pembuatan Fungsi 2 untuk melakukan decrement
int shared=1; //Variabel Shared yang merupakan nilai yang akan di 
			  //akses bersamaan oleh fungsi pertama dan kedua

int main()
{
	pthread_t thread1, thread2; //pembuatan thread ke 1 dan 2
	pthread_create(&thread1, NULL, function1, NULL); //thread 1 akan diakses oleh Fungsi 1
	pthread_create(&thread2, NULL, function2, NULL); //thread 2 akan diakses oleh Fungsi 2
	pthread_join(thread1, NULL); //gabungkan kedua thread agar ketika thread 1 sleep, thread  
	pthread_join(thread2, NULL); //2 akan dijalankan dan sebaliknya
	printf("Hasil Akhir dari Proses adalah %d", shared); //outputkan hasil akhir dari race condition
	return 0;
}

void *function1()
{
	int m; //variable m secara lokal dalam fungsi pertama
    m=shared;
    m++; //increment nilai m secara lokal
    printf("nilai fungsi 1 secara lokal = %d\n", m);
    sleep(1); //lakukan sleep sehingga thread 2 berjalan
    shared=m; 
    printf("proses ke 1 = %d\n", shared);
}

void* function2() 
{
    int n; //variable n secara lokal dalam fungsi pertama
    n=shared;
    n--; //decrement nilai n secara lokal
    printf("nilai fungsi 2 secara lokal = %d\n", n);
    sleep(1); //lakukan sleep sehingga thread 1 berjalan
  	shared=n; //update nilai variable shared yang global
    printf("proses ke 2 = %d\n", shared);
}