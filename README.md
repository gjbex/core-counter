core-counter
============

Check available cores and OMP threads

Usage
-----
Run `core-counter` as follows to retrieve the number of avaiable cores
(or hyperthreads, if enabled):
```bash
$ core-counter
20
```

To check the number of threads OpenMP will default to, run:
```bash
$ export OMP_NUM_THREADS=4
$ core-counter -num_threads
4
```


Build instructions
------------------
Simply use the standard mantra:
```bash
$ ./configure
$ make
$ make install
```

Note that the application is statically built to minimize dependencies.


Changes
-------

Release 1.1
* To minimize dependencies, a static build is done.
* Clean up of autotools artefacts in repository
* Extended README with some documentation

Release 1.0
* Initial release
