#!/bin/bash
#SBATCH --partition=gpuq
#SBATCH --qos=gpu
#SBATCH --gres=gpu:1g.10gb:1
#SBATCH --ntasks-per-node=1
#SBATCH --job-name="gc_can_fp_1"
#SBATCH --time=0-20:00:00
#SBATCH --output /scratch/nsutton2/gc_sim/gc_can_fp_1_results.txt
#SBATCH --mem=5G
./find_spiking_distro_sim.sh

