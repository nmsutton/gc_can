#!/bin/bash
#SBATCH --partition=gpuq
#SBATCH --qos=gpu
#SBATCH --gres=gpu:A100.40gb:1
#SBATCH --ntasks-per-node=1
#SBATCH --job-name="gc_can_4"
#SBATCH --time=0-20:00:00
#SBATCH --output /scratch/nsutton2/gc_sim/gc_can_4_results.txt
#SBATCH --mem=20G
srun ./hello_world
