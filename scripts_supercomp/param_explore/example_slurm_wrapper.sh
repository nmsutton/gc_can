#!/bin/bash
#SBATCH --partition=gpuq
#SBATCH --qos=gpu
#SBATCH --gres=gpu:A100.40gb:1
#SBATCH --ntasks-per-node=1
#SBATCH --job-name="auto_mod_8"
#SBATCH --time=0-05:00:00
#SBATCH --output /scratch/nsutton2/gc_sim/auto_mod_8_results.txt
#SBATCH --mem=20G
srun sh ./auto_mod.sh
