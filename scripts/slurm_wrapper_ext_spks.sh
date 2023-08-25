#!/bin/bash
#SBATCH --partition=normal
#SBATCH --job-name="gc_can_ext_spks"
#SBATCH --output /scratch/nsutton2/gc_sim/gc_can_ext_spks_results.txt
#SBATCH --time=0-20:00:00
#SBATCH --nodes=1                     # Request N nodes
#SBATCH --cpus-per-task=1            # Request n   cores per node
#SBATCH --mem-per-cpu=200GB             # Request nGB RAM per core
./extract_spike_times.sh
