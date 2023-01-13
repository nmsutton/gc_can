#!/bin/bash
#SBATCH --partition=gpuq
#SBATCH --qos=gpu
#SBATCH --gres=gpu:1g.5gb:1
#SBATCH --ntasks-per-node=1
#SBATCH --job-name="gc_can_1"
#SBATCH --time=0-24:00:00
#SBATCH --output /scratch/nsutton2/gc_sim/gc_can_1_results.txt
#SBATCH --mem=20G
./rebuild.sh
