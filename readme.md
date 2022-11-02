# Documentation

This program aims to tackle the popular producer-consumer problem where data inconsistencies may arise if one resource is used by more than one process at a time.

This program has been set up in a way that creates memory which is both accessible by producer and consumer and stored  in “table”.

It ensures that there is mutual exclusion, progress (to avoid deadlock), and bounded waiting to avoid starvation.

The use of semaphores is enforced to avoid data loss or corruption of any sort which may have an adverse effect on overall program functionality.


# To run the program,

gcc producer.c -pthread -lrt -o producer
gcc consumer.c -pthread -lrt -o consumer
./producer & ./consumer &

<img width="807" alt="Screen Shot 2022-11-01 at 2 10 55 PM" src="https://user-images.githubusercontent.com/25392258/199383401-0c010854-bae9-48ba-a540-d4f0ef518c56.png">


# Issues

Although the program produces 0 errors on first try, running the code multiple times may cause memory related issues which may affect the way the program runs when executed.

If you encounter this pproblem, quit and reopen the terminal.

