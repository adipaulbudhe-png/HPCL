#!/bin/bash
#SBATCH --job-name=merge_sort
#SBATCH --partition=standard
#SBATCH --nodes=1
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=4
#SBATCH --time=00:10:00
#SBATCH --output=merge_sort_%j.out
#SBATCH --error=merge_sort_%j.err

module load compiler/gcc/12.3

cd /home/mit104/parallel_sorting

export OMP_NUM_THREADS=$SLURM_CPUS_PER_TASK
export OMP_PLACES=cores
export OMP_PROC_BIND=close

echo "Starting Parallel Merge Sort"
echo "Allocated CPUs: $SLURM_CPUS_PER_TASK"
echo "Running on: $(hostname)"

./merge_sort

echo "Job completed."

