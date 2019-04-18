#!/bin/bash
#PBS -l nodes=1:ppn=4
#PBS -l walltime=00:30:00
#PBS -q iw-shared-6
#PBS -N mkl_test
#PBS -o stdout
#PBS -e stderr

cd /nv/hp22/jgaul7/wrapped_mm

module load mkl/11.2
module load intel/15.0
module load mvapich2/2.1
module load anaconda3/latest

MKL_NUM_THREADS=4 python main.py

