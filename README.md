# mkl_cython_demo

Repo contains the materials used to create a brief demonstration of using Cython to wrap a C function which implements the Intel MKL dgemm() matrix multiplication function.

Intended for use on the Georgia Tech Pace cluster, the required modules are listed below:
module load mkl/11.2
module load intel/15.0
module load mvapich2/2.1
module load anaconda3/latest

The lib/ directory contains the c file and can be assembled into an executable using

> make mm

or the library file can be remade just using

> make

You might have to manually set the number of threads available to mkl with

> MKL_NUM_THREADS=N ./mm

because Anaconda is weird like that. That's a todo alright. As is better identifying the runtime for the c module.

Making and running the library is pretty simple as well, same

> make

from the top level and

> MKL_NUM_THREADS=N python main.py

to run it.

The flags in setup.py are very definitely excessive, most of them could be deleted without consequence.
Another potential improvement is to automatically set the number of cores using 

import mkl

mkl.get_max_threads()
mkl.set_num_threads(2)

in python.
