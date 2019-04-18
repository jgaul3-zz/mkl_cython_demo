from distutils.core import setup
from distutils.extension import Extension
from Cython.Build import cythonize
import os

os.environ["cc"] = "icc"
os.environ["LDSHARED"] = "icc -shared"

compile_args = ["-I`python3-config --exec-prefix`/include",
	"-I`python3-config --exec-prefix`/include/python3.6m",
	"-lmkl_rt", "-lopa", "-lmpl", "-lrt", "-lpthread", "-mkl", "-static-intel",
        "-lmpich", "-lintlc"]

# "-I/usr/local/pacerepov1/mvapich2/2.1/intel-15.0/include"

link_args = ["-Wl,-rpath=$ORIGIN/../lib/:`python3-config --exec-prefix`/lib",
	"-L`python3-config --exec-prefix`/lib",
	"-L/usr/local/pacerepov1/mvapich2/2.1/intel-15.0/lib",
	"-lmkl_rt", "-lopa", "-lmpl", "-lrt", "-lpthread", "-mkl", "-static-intel",
	"-lmpich", "-lintlc", "-openmp"]

examples_extension = Extension(
    name="pyexamples",
    sources=["pyexamples.pyx"],
    libraries=["mm"],
    library_dirs=["lib"],
    include_dirs=["lib"],
    extra_compile_args = compile_args,
    extra_link_args    = link_args,
)
setup(
    name="pyexamples",
    ext_modules=cythonize([examples_extension], language_level=3)
)

