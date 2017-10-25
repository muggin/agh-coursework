#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// ----------------------------------------------------------

#define ROWS 5
#define COLS 3

pthread_mutex_t mutex;
pthread_cond_t cond;
int test_array [COLS][ROWS];
int col_sums [COLS];

void* create_array(void*);
void* sum_columns(void*);
void print_array(void);
// ----------------------------------------------------------

int main(){
	 
	 int sum_thread = COLS;
	 int total_sum = 0;
	 pthread_t gen_thread;
     pthread_t sum_threads [COLS];
     pthread_attr_t attr;

     // mutex initialization
     pthread_mutex_init(&mutex, NULL);

     // conditional initialization
     pthread_cond_init(&cond, NULL);
 
	 // attribute initlization
     pthread_attr_init(&attr);
     pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

	 pthread_create(&gen_thread, &attr, create_array, NULL);
     pthread_join(gen_thread, NULL); 

	 for (int ti = 0; ti < sum_thread; ti++)
	 {
		pthread_create(&sum_threads[ti], &attr, sum_columns, (void *) ti);
	 }

	 for (int ti = 0; ti < sum_thread; ti++) {
     	pthread_join(sum_threads[ti], NULL);
	 }

	 print_array();

	 for (int i = 0; i < COLS; i++) {
		 total_sum += col_sums[i];
	 }
     printf("\nFinishing...\n");
     return 0;
}

void* create_array(void* arg) {
	srand(time(NULL));
	pthread_mutex_lock(&mutex);
	for (int i = 0; i < COLS; i++)
	{
		for (int j = 0; j < ROWS; j++)
		{
			test_array[i][j] = (int)(rand() % 10);
		}
	}
	pthread_mutex_unlock(&mutex);
	return ((void *) 0);
}

void* sum_columns(void* arg) {
	int column_sum = 0;
	int column_idx = (int) arg;

	for (int i = 0; i < ROWS; i++)
	{
		column_sum += test_array[column_idx][i];
	}

	pthread_mutex_lock(&mutex);
	col_sums[column_idx] = column_sum;
	pthread_mutex_unlock(&mutex);
	return ((void *) 0);
}

void print_array(void) {

	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			printf ("%d ", test_array[j][i]);
		}
		printf("\n");
	}
}

