*This project has been created as part of the 42 curriculum by cecompte.*

## Description

This project is an implementation of the classic **Dining Philosophers Problem**, a fundamental concurrency and synchronization problem in computer science. The project demonstrates key concepts in multithreading, including:

### Goal
To solve the dining philosophers problem using POSIX threads (pthreads) and mutex locks. The implementation must prevent deadlocks and race conditions while simulating philosophers who alternate between thinking and eating, requiring shared resources (forks) to eat.

### Overview
The project simulates `n` philosophers sitting around a circular table with `n` forks. Each philosopher needs two forks to eat. The program manages thread synchronization using mutexes to ensure:
- No two philosophers can use the same fork simultaneously
- Philosophers don't starve
- Deadlock is prevented
- Race conditions are avoided

## Instructions

### Requirements
- GCC or Clang compiler
- POSIX-compliant system (Linux, macOS, etc.)
- GNU Make
- pthreads library (usually included with the C standard library)

### Compilation
Navigate to the `philo` directory and run:
```bash
cd philo
make
```

This will compile the project and generate an executable named `philo`.

### Execution
```bash
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]
```

#### Arguments
- `number_of_philosophers`: Number of philosophers and forks (must be > 0)
- `time_to_die`: Milliseconds before a philosopher dies if they haven't eaten (must be > 0)
- `time_to_eat`: Milliseconds it takes to eat (must be > 0)
- `time_to_sleep`: Milliseconds a philosopher sleeps after eating (must be > 0)
- `number_of_times_each_philosopher_must_eat` (optional): If specified, the program stops when all philosophers have eaten this many times

#### Example
```bash
./philo 5 800 200 200
./philo 4 410 200 200 10
```

### Cleanup
To remove compiled object files and the executable:
```bash
make clean
```

To remove everything including object files:
```bash
make fclean
```

## Resources

### Classic References
- **Dining Philosophers Problem**: https://en.wikipedia.org/wiki/Dining_philosophers_problem
- **POSIX Threads (pthreads)**: https://man7.org/linux/man-pages/man7/pthreads.7.html
- **Mutex Synchronization**: https://man7.org/linux/man-pages/man3/pthread_mutex_lock.3p.html
- **Mutexes and Deadlock Prevention**: https://www.geeksforgeeks.org/introduction-to-mutex/
- **Thread Safety and Race Conditions**: https://en.wikipedia.org/wiki/Race_condition


## Technical Choices

### Threading Model
- One thread per philosopher for concurrent execution
- Each philosopher independently manages their eating, thinking, and sleeping cycles
- Centralized fork management through a fork array with individual mutexes

### Synchronization Strategy
- `pthread_mutex_t` for protecting shared resources (forks and meal counters)
- Timestamp-based monitoring to detect philosopher starvation
- Separate monitor thread (when applicable) to track philosopher states

### Project Structure
```
philo/
├── src/              # Source files
│   ├── main.c       # Program entry point and thread creation
│   ├── init.c       # Initialization and setup
│   ├── routine.c    # Philosopher behavior logic
│   ├── monitor.c    # Monitoring for starvation
│   └── utils.c      # Utility functions
├── includes/        # Header files
│   └── philo.h      # Main header with structures and definitions
├── Makefile         # Build configuration
└── philo            # Compiled executable
```

## Notes
- Ensure that `time_to_die`, `time_to_eat`, and `time_to_sleep` are reasonable values to observe proper behavior
- The program may require careful timing tuning to avoid false starvation detection
- For debugging, consider using `valgrind` to check for memory leaks and thread issues

