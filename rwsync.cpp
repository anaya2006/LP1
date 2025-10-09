#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
using namespace std;

sem_t mutex;        // protects read_count and write_waiting
sem_t rw_mutex;     // for writers exclusive access
sem_t turnstile;    // for writer priority control

int read_count = 0;
int write_waiting = 0;

void* reader(void* arg) {
    int id = *(int*)arg;
    delete (int*)arg;

    sem_wait(&turnstile);   // wait if writers waiting (writer priority)
    sem_post(&turnstile);

    sem_wait(&mutex);
    read_count++;
    if (read_count == 1)
        sem_wait(&rw_mutex);  // first reader locks resource for readers
    sem_post(&mutex);

    cout << "Reader " << id << " is reading\n";
    sleep(2);  // simulate reading

    sem_wait(&mutex);
    read_count--;
    if (read_count == 0)
        sem_post(&rw_mutex);  // last reader releases resource
    sem_post(&mutex);

    cout << "Reader " << id << " finished reading\n";
    return nullptr;
}

void* writer(void* arg) {
    int id = *(int*)arg;
    delete (int*)arg;

    sem_wait(&mutex);
    write_waiting++;
    if (write_waiting == 1)
        sem_wait(&turnstile);   // block readers when writers waiting
    sem_post(&mutex);

    sem_wait(&rw_mutex);  // exclusive access for writer

    cout << "Writer " << id << " is writing\n";
    sleep(3);  // simulate writing

    cout << "Writer " << id << " finished writing\n";
    sem_post(&rw_mutex);

    sem_wait(&mutex);
    write_waiting--;
    if (write_waiting == 0)
        sem_post(&turnstile);   // allow readers when no writers waiting
    sem_post(&mutex);

    return nullptr;
}

int main() {
    int num_readers, num_writers;
    cout << "Enter number of readers: ";
    cin >> num_readers;
    cout << "Enter number of writers: ";
    cin >> num_writers;

    pthread_t readers[num_readers], writers[num_writers];

    sem_init(&mutex, 0, 1);
    sem_init(&rw_mutex, 0, 1);
    sem_init(&turnstile, 0, 1);

    // create reader threads
    for (int i = 0; i < num_readers; i++) {
        int* id = new int(i + 1);
        pthread_create(&readers[i], nullptr, reader, id);
    }

    // create writer threads
    for (int i = 0; i < num_writers; i++) {
        int* id = new int(i + 1);
        pthread_create(&writers[i], nullptr, writer, id);
    }

    // wait for readers
    for (int i = 0; i < num_readers; i++)
        pthread_join(readers[i], nullptr);

    // wait for writers
    for (int i = 0; i < num_writers; i++)
        pthread_join(writers[i], nullptr);

    sem_destroy(&mutex);
    sem_destroy(&rw_mutex);
    sem_destroy(&turnstile);

    return 0;
}
/*OUTPUT
pc@pc-Lenovo-S510:~$ g++ rwsync.cpp -pthread -o rw
pc@pc-Lenovo-S510:~$ ./rw
Enter number of readers: 4
Enter number of writers: 3
Reader 2 is reading
Reader 3 is reading
Reader 1 is reading
Reader 4 is reading
Reader Reader 12 finished reading
 finished reading
Writer 1 is writing
Reader 3 finished reading
Reader 4 finished reading
Writer 1 finished writing
Writer 2 is writing
Writer 2 finished writing
Writer 3 is writing
Writer 3 finished writing
pc@pc-Lenovo-S510:~$ 
*/
