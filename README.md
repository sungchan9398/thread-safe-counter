My OS environment : WLS2 Ubuntu Linux Window10

Compare performance : If you used 'time ./a.out' you could know that mutex is faster than semaphore.
if input = 50, semaphore takes 0.060sec, and mutex takes 0.007sec.

Mutex is binary Semaphore. If many threads approximate to Mutex, Mutex just blocks approximaiting threads at the same time
But Semaphore is different. If many threads and preocess approximate to Semaphore, first, it checks changing semaphore variables.
So Semaphore takes longer time than Mutex, I think.


