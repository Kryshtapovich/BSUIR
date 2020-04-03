#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <fstream>
#include <pthread.h>
#include <string.h>

#define MAX_THREADS 100

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t address_lock = PTHREAD_MUTEX_INITIALIZER;

struct thread_data {
    int  thread_id;
    char *message;
    std::fstream *output;
};

void *thread_function(void *threadarg) {
    struct thread_data *my_data;
    while(1) {
        my_data = (struct thread_data *) threadarg;
        std::cout << "Thread Id: " << my_data->thread_id ;
        std::cout << " Message: " << my_data->message << std::endl;
        pthread_mutex_lock(&lock);
        std::string message = std::to_string(my_data->thread_id) + ": " + std::string(my_data->message);
        *my_data->output << message << std::endl;
        pthread_mutex_unlock(&lock);
        sleep(1);
    }
}

int main (int argc, char** argv) {
    pthread_t threads[MAX_THREADS];
    struct thread_data td[MAX_THREADS];
    int rc, i = 0;
    char* filename = argv[1];
    printf("%s\n", filename);
    std::fstream output(filename, std::ios::out | std::ios::app);
    
    std::string choice = "qwe";

    while(strcmp(choice.c_str(), "q") != 0) {
        printf("q - exit\nc - create thread\nd - delete last thread\n");
        std::cin >> choice;
        if (strcmp(choice.c_str(), "c") == 0) {
            std::cout << "main() : creating thread, " << i << std::endl;
            td[i].thread_id = i;
            td[i].message = argv[2];
            td[i].output = &output;
            rc = pthread_create(&threads[i], NULL, thread_function, (void *)&td[i]);
            i++;
            if (rc) {
                std::cout << "Error: unable to create thread," << rc << std::endl;
                exit(-1);
            }
        } else if (strcmp(choice.c_str(), "d") == 0) {
            rc = pthread_cancel(threads[i - 1]);
            if (rc) {
                std::cout << "Error: unable to cancel thread," << rc << std::endl;
                exit(-1);
            }
            i--;
        }
    }
    pthread_exit(NULL);
}
