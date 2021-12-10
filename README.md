# philosophers

## Description

This project is the dining philosophers problem in C.

Learn multi-threads/multi-process programming with the use of mutex and semaphore.

## Requirement

- gcc or Clang
- GNU Make

## Features
### philo
philosopher with threads and mutex

### philo_bonus
philosopher with processes and semaphore

## Usage

```
git clone https://github.com/ryo-manba/philosophers
cd philosophers/philo # or philo_bonus
make
```
```
./philo 1 2 3 4 [5]
  1 - number of philosophers
  2 - time to die
  3 - time to eat
  4 - time to sleep
  5 - number of times each philosopher must eat
```

## Sample
```
./philo 2 410 200 200
[timestamp] [id] [action]
1639121815297 1 has taken a fork
1639121815297 1 has taken a fork
1639121815297 1 is eating
1639121815497 1 is sleeping
1639121815497 2 has taken a fork
```

## Author

[twitter](https://twitter.com/ryo_manba)

## Licence

All code is released under the [MIT](https://github.com/ryo-manba/philosophers/blob/main/LICENSE) license
