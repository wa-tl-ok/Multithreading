# Multithreading
Multithreading. Why do you need multithreading?

Multithreading is an important tool in programming - it helps to execute threads in parallel and independently. Threads are independently executed sequences of instructions. This allows for efficient use of processor resources and increas program performance.

std::thread is a class from the C++ standard library that allows you to create and manage threads.

    1) std::thread t(F) - creating a thread calling function F.
    2) t.join() - waiting for thread to complete execution.
    3) t.detach() - thread detachment.
    4) t.joinable() - check if the thread can be connected.
    5) t.get_id() - getting thread ID.
    6) t1.swap(t2) - swap two std::thread objects.

Multithreading is especially useful in situations:

    1) Performance improvement: parallelization computing can speed up tasks, especially if tasks can be performed independently of each other.
    2) I/O Processing: When the processor is waiting (complete the I/O operation), another thread can work, it allows for more efficient use timeout (This also makes for a more responsive user experience interface).

Synchronization between threads is necessary for preventing access conflicts to shared resources and ensuring the correct execution of parallel operations. When multiple threads access shared data, consistency and race conditions occur.

Examples of synchronization mechanisms in C++:

    1) Mutexes (std::mutex, std::shared_mutex) and locks (std::lock_guard, std::shared_lock, std::unique_lock): are used to provide mutual exclusion when accessing shared data. 
        a) std::mutex is a class from the C++ Standard Library. Mutexes allow you to block access to a resource to only one thread at a time.
            a') A thread that wants to access a protected resource locks the mutex using the lock() method (This method locks the mutex. If the mutex is already locked by another thread, the current thread will wait until the mutex is unlocked).
            a'') When the thread finishes working with the protected resource, it unlocks the mutex using the method unlock().
        b) Shared_mutex provides a shared mutex that allows multiple threads to have simultaneous read access to a shared resource, but blocks write access when one thread attempts to modify the data. This allows for higher concurrency when many threads require only reading data.
            b') A thread that wants read access to a protected resource locks the shared_mutex using the lock_shared() method (this method locks a shared mutex. Multiple threads can lock a shared mutex at the same time as long as there are no threads that lock it for exclusive access).
            b'') A thread that wants exclusive access to writing to a protected resource, blocks shared_mutex using the lock() method (this method locks the mutex for exclusive access. If the mutex is already locked for exclusive access or shared access, the current thread will be wait until the mutex is unlocked).
            b''') When the thread finishes working with the protected resource, it unlocks the shared_mutex using the method unlock() (this method unlocks the mutex, allowing other threads block it for exclusive or shared access)
        c) std::lock_guard is a class from the C++ standard library, which provides an automatic locking mechanism and unlocking the mutex (std::mutex). It serves to provide secure access to shared data in a multi-threaded environment.
            c') When a std::lock_guard instance is instantiated, a mutex is passed in that should be locked.
            c'') When leaving the scope of std::lock_guard, such as when a function or block of code terminates, the std::lock_guard destructor automatically unlocks the mutex using a call to unlock().

    Examples:
    https://pastebin.com/DyZALmKe - std::mutex - lock; unlock;
    https://pastebin.com/DQhwR6A2 - std::shared_mutex - lock; unlock;
    https://pastebin.com/cxG5SFie - std::lock_guard - lock; unlock;
    
    2) Condition variables (std::condition_variable): used for synchronization between threads when one thread is waiting for a certain event to occur in another thread.
    Condition variable is a means synchronization, which allows threads to wait for a certain conditions before continuing execution. Condition variable allows threads to communicate by signaling each other state of shared data or events.
    Some of the main methods of the std::condition_variable class include:
        a) wait(lock): Blocks the current thread until received notification from another thread or until a certain condition is met. The lock parameter must be an object of type std::unique_lock<std::mutex> or std::lock_guard<std::mutex>, which will automatically released and blocked when wait is called.
        b) wait_for(lock, duration): Blocks the current thread until will not receive a notification from another thread or until a certain condition will be met, but no more specified period of time (duration). The lock parameter must be an object of type std::unique_lock<std::mutex> or std::lock_guard<std::mutex>, which will automatically released and blocked when wait_for is called. Returns std::cv_status::timeout if the timeout has expired.
        c) wait_until(lock, time_point): Blocks the current thread until notification is received from another thread or until a certain condition will not be met, but no later than specified point in time (time_point). The lock parameter must be an object of type std::unique_lock<std::mutex> or std::lock_guard<std::mutex>, which will automatically released and blocked when wait_until is called. Returns std::cv_status::timeout if the timeout has expired.
        d) notify_one(): Notifies one of the threads waiting on conditional variable. If there are blocked threads then one of them will be unlocked and will be able to continue performance.
        e) notify_all(): Notifies all threads waiting on the conditional variable. All blocked threads will are unlocked and will be able to continue execution.
    
    3) Atomic operations (std::atomic): Used to provide atomic reading and writing of data, which prevents race conditions.
    std::atomic support atomic read and write operations, as well as other operations such as exchange (swap), compare and exchange (compare-swap), addition (fetch_add), subtraction (fetch_sub), increase (fetch_inc), decrease (fetch_dec), return the current value of an atomic variable (load), write a new value to an atomic variable (store).
    std::memory_order_relaxed mode provides the lowest degree of synchronization and is used when the order of operations is not important.
    
    Examples:
    https://pastebin.com/ig2Gtde0 - std::atomic;


A deadlock is a situation where two or more threads communicate with each other and block while waiting for resources that other threads are holding. As a result, none of the threads can continue their work, and the program ends up in a closed state.

Examples:

    1) Mutual blocking : Thread A is locking resource X and waiting to be released resource Y.
                         Thread B is locking resource Y and waiting to be released resource X.
    2) Lack of resources : Thread A1 holds resource b1 and waits for release resource b2.
                           Thread A2 holds resource b2 and waits for release resource b3.
                                                    ...
                           Thread An holds resource bn and waits for release resource b1.


Semaphore is a means of synchronization, used to control access to a shared resource or restrictions on the number of threads that can simultaneously perform a specific operation. The semaphore has an internal integer value and supports two main operations:

    1) Wait: Decrements the semaphore value by one. If the value becomes negative, then the flow executing the wait operation blocks and waits until the semaphore value will not become positive.
    2) Signal: Increments the semaphore value by one. If there are threads that wait on a semaphore, then one of them is unlocked and can continue its execution.

An example of using a semaphore would be a situation where we have a limited number of resources (such as printing devices) and multiple threads that want to access these resources. A semaphore can be used to limit the number of threads that can print simultaneously to avoid contention or resource overload. 

    Example: https://pastebin.com/9iUHJQaL

Combining all the knowledge we have gained, we will write a queue with a fixed size : https://pastebin.com/vAJkW644


Let's talk about std::future and std::promise : they are components of the C++ standard library designed to exchange values or exceptions between threads.

    std::promise is used to set a value or exception that can be obtained in the future using std::future.
    std::future is an object that is associated with std::promise and allows you to get the value or exception that was set in std::promise.
    https://pastebin.com/K2BcLfB9 - std::future and std::promise

A thread pool is a mechanism in which a group of threads is created and maintained that can perform tasks asynchronously. A thread pool allows you to reuse threads to process multiple tasks, instead of creating and terminating threads for each individual task.

The basic idea of a streaming pool is that the creation and management of streams is performed outside the main logic of the application. Instead of creating a new thread for each task that needs to be completed, the thread pool pre-creates a pool of threads and stores them in a pool of ready-to-run tasks.

Advantages of using a streaming pool:

    1) Efficient use of resources: The streaming pool allows you to manage the number of threads, which helps to avoid excessive creation of threads and simplifies resource management.
    2) Performance improvement: A thread pool can run multiple tasks in parallel, which increases productivity and reduces task execution time.

Streaming pools are widely used to handle parallel and asynchronous tasks in multithreaded applications such as servers, data processing systems, web applications, and others. When it comes to tasks with a return value in the streaming pool, you can use the std::future and std::promise mechanisms to get the results of task execution.
