import mkl

cdef extern from "mm.c":
    int test1()
    int test2()

def py_mm1():
    # mkl.set_num_threads(20)
    return test1()

def py_mm2():
    # mkl.set_num_threads(20)
    return test2()

