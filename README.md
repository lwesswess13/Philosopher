*This project has been created as part of the 42 curriculum by sbouchib.*

## Description
The Philosophers project aims to teach the basics of threading a process and using mutexes to avoid data races. The project simulates a classic synchronization problem: the Dining Philosophers problem.
One or more philosophers sit at a round table and alternate between eating, sleeping, and thinking. They each share a fork with their neighbors. A philosopher needs two forks to eat. The goal is to design an algorithm that ensures no philosopher will starve, correctly orchestrating the threads and the shared resources (forks) via mutexes.

**Key Notions to Understand:**
- **Threads (`pthread_create`, `pthread_join`):** Threads represent individual execution flows within a single process. Here, each philosopher is a thread running concurrently.
- **Mutexes (`pthread_mutex_init`, `pthread_mutex_lock`, `pthread_mutex_unlock`):** Mutexes (Mutual Exclusions) are used to protect shared data from concurrent access. In this project, forks (and states like printing, meal tracking, death checking) must be protected by mutexes to avoid data races.
- **Data Races:** A data race occurs when two threads access the same variable simultaneously, and at least one is writing. Using mutexes avoids this.
- **Context Switching and Deadlocks:** Careful order of acquiring locks is needed to ensure no deadlock occurs (e.g., all philosophers grab their left fork simultaneously and wait forever for the right one).

## Instructions
**Compilation:**
To compile the project, run:
```bash
make
```

**Execution:**
Run the program with the following arguments:
```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```
- `number_of_philosophers`: The number of philosophers (and forks).
- `time_to_die`: Time (in ms) a philosopher can survive without eating.
- `time_to_eat`: Time (in ms) it takes for a philosopher to eat.
- `time_to_sleep`: Time (in ms) a philosopher spends sleeping.
- `number_of_times_each_philosopher_must_eat`: (Optional) The simulation stops if all philosophers have eaten at least this many times.

**Cleaning up:**
- `make clean`: Removes object files.
- `make fclean`: Removes object files and the executable.
- `make re`: Recompiles the project from scratch.

## Resources
- [POSIX Threads Programming (pthreads)](https://hpc-tutorials.llnl.gov/posix/)
- [Dining Philosophers Problem - Wikipedia](https://en.wikipedia.org/wiki/Dining_philosophers_problem)
- AI Usage: AI was utilized during the development of this project to generate boilerplate structure, draft this README, and identify edge cases (such as handling single philosophers or memory leak checks on initialization failure). The generated codes and configurations were fully reviewed, tested, and understood prior to submission.
