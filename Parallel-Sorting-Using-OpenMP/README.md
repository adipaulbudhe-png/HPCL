# Parallel Sorting Using OpenMP

## Project Overview
This project implements and compares Sequential Merge Sort and Parallel Merge Sort using OpenMP tasks.

## Objectives
- Implement sequential Merge Sort.
- Implement parallel Merge Sort using OpenMP.
- Execute the program on PARAM Rudra HPC.
- Compare execution time for different input sizes.
- Verify sorting correctness.

## Technologies Used
- C++
- OpenMP
- GCC 12.3
- SLURM Workload Manager
- PARAM Rudra HPC Cluster

## Benchmark Results

| Input Size | Sequential Time (ms) | Parallel Time (ms) | Speedup |
|---:|---:|---:|---:|
| 100,000 | 9.91737 | 4.47692 | 2.21522x |
| 500,000 | 53.3184 | 20.9737 | 2.54216x |
| 1,000,000 | 114.348 | 44.0103 | 2.5982x |

All three test cases passed correctness verification.

## Execution Environment
- Cluster: PARAM Rudra
- Partition: standard
- Compute Node: rdcn20
- OpenMP Threads: 4
- SLURM Job ID: 72632

## Files
- `merge_sort.cpp` – C++ source code.
- `merge_sort.sh` – SLURM job submission script.
- `benchmark_results.txt` – Saved benchmark output.
- `merge_sort_72632.out` – SLURM execution log.
- `merge_sort_72632.err` – Error log.

## Conclusion
The parallel implementation achieved better execution times than the sequential implementation for all tested input sizes. The observed speedup increased with larger input sizes, reaching approximately 2.60x for one million elements.
