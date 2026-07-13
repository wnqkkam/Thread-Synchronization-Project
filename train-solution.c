#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t gate; //Global variable, 1=road free, 0=road busy

void* train(void* arg)
{
	while(1){
		sem_wait(&gate); //Decrease gate to use road
		printf("\n The railway gate is closed\n");

		printf("\n The train is crossing\n");
		sleep(1);

		printf("\n The railway gate is opened\n");
		sem_post(&gate); //Increase gate to release road
		sleep(5);
	}
}

void* car(void* arg)
{
	while(1){
		sem_wait(&gate); //Decrease gate to occupy road
		printf("\n The cars are crossing the railway\n");
		sem_post(&gate); //Release road for cars or train
		sleep(1);
  	}
}


int main()
{
	int thread0_id=0, thread1_id=1;

	sem_init(&gate, 0, 1); //Initialise semaphore to 1

	pthread_t t0,t1;

	pthread_create(&t0,NULL,car,&thread0_id);
	pthread_create(&t1,NULL,train,&thread1_id);

	pthread_join(t0,NULL);
	pthread_join(t1,NULL);

	sem_destroy(&gate); //Clean up semaphore

	return 0;
}
