#include <sys/mman.h>
#include <fcntl.h>
#include <semaphore.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define BUFFER_SIZE 2

#define errExit(msg)    do { perror(msg); exit(EXIT_FAILURE); \
                                   } while (0)
                                   
/* Define a structure that will be imposed on the shared
memory object */

struct shmbuf {
sem_t  sem1;           
sem_t  sem2;            
int buf[BUFFER_SIZE];   /* Data being transferred */
};


int main(int argc, char *argv[]){

    srand(time(NULL)); // generates numbers

    char *shmpath = "Data Table";

    /* Create shared memory object; size set to the size
    of our structure. */

    int fd = shm_open(shmpath, O_CREAT | O_EXCL | O_RDWR, S_IRUSR | S_IWUSR);
    if (fd == -1) 

        fd = shm_open(shmpath, O_RDWR, 0);

    if (fd == -1)

        errExit("shm_open");

    if (fd == -1)
        errExit("shm_open");

    if (ftruncate(fd, sizeof(struct shmbuf)) == -1)
        errExit("ftruncate");

    /* Map the object into the caller's address space. */

    struct shmbuf *shmp = mmap(NULL, sizeof(*shmp),
                                PROT_READ | PROT_WRITE,
                                MAP_SHARED, fd, 0);
    if (shmp == MAP_FAILED)
        errExit("mmap");

    /* Initialize semaphores as process-shared, with value 0. */

    if (sem_init(&shmp->sem1, 1, 0) == -1)
        errExit("sem_init-sem1");
    if (sem_init(&shmp->sem2, 1, 0) == -1)
        errExit("sem_init-sem2");

    /* Wait for 'sem1' to be posted by peer before touching
        shared memory. */

    for (int i = 0; i < 10; i++) { // loop 10 times
        
        
        shmp->buf[0] = rand();
        shmp->buf[1] = rand();

        printf("\nAdded item in pos 1: %d\n", shmp->buf[0]);
        printf("Added item in pos 2: %d\n", shmp->buf[1]);
        

        /* Post 'sem2' to tell the peer that it can now
        access the modified data in shared memory. */

        if (sem_post(&shmp->sem1) == -1)
            errExit("sem_post");

        if (sem_wait(&shmp->sem2) == -1)
        errExit("sem_wait");
    }

    /* Unlink the shared memory object. */

    shm_unlink(shmpath);

    exit(EXIT_SUCCESS);
}
