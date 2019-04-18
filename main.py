import pyexamples
# import mpi4py
from timeit import default_timer as timer
from time import clock
import faulthandler

faulthandler.enable()

start = timer()
startc = clock()
# pyexamples.py_mm1()
end = timer()
endc = clock()
# print(end - start)
# print(endc - startc)

start = timer()
startc = clock()
pyexamples.py_mm2()
end = timer()
endc = clock()
#print(end - start)
#print(endc - startc)

