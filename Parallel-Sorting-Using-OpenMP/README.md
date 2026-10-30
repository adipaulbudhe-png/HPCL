# Parallel Sorting Using OpenMP

## Project Overview
Implementation and comparison of Sequential Merge Sort and Parallel Merge Sort using OpenMP tasks.

## Objectives
- Implement sequential Merge Sort.
- Implement parallel Merge Sort using OpenMP.
- Execute on PARAM Rudra HPC.
- Compare execution times for different input sizes.
- Verify sorting correctness.

## Technologies Used
- C++
- OpenMP
- GCC 12.3
- SLURM
- PARAM Rudra HPC

## Benchmark Results

| Input Size | Sequential (ms) | Parallel (ms) | Speedup |
|---:|---:|---:|---:|
| 100,000 | 9.91737 | 4.47692 | 2.21522x |
| 500,000 | 53.3184 | 20.9737 | 2.54216x |
| 1,000,000 | 114.348 | 44.0103 | 2.5982x |

All three test cases passed correctness verification.

## Execution Environment
- Cluster: PARAM Rudra
- Node: rdcn20
- Partition: standard
- OpenMP Threads: 4
- SLURM Job ID: 72632

## Project Files
- merge_sort.cpp – Source code
- merge_sort.sh – SLURM submission script
- benchmark_results.txt – Benchmark results
- merge_sort_72632.out – Execution log
- merge_sort_72632.err – Error log

## Conclusion
The parallel implementation achieved better execution times than sequential Merge Sort across all tested input sizes, reaching an observed speedup of approximately 2.60x for one million elements.
