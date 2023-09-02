# Process to create, compile, and run new CARLsim6 project
# This version is for use on a supercomputer
# Note: one must already be on the gpu node (salloc -p gpuq -q gpu...)
# to run this script because it exits the script to switch nodes.
# Therefore that step is not automated.

proj_name="$1" #"hello_world_2" # new project name
cs6_proj="$2" #"/home/nsutton2/git/CARLsim6/projects" # CS6 project folder
cs6_build="$3" #"/home/nsutton2/git/CARLsim6/.build" # CS6 build folder
sc_username="$4" #"gmu_username" # supercomputer username
sc_email="$5" #"gmu_email@gmu.edu" # supercomputer email
rs="_results.txt"
results_file="$6" #"/scratch/$sc_username/$proj_name$rs" # results file
hw="hello_world"
cm="CMakeLists.txt"

if [ "$#" -ne 6 ]; then
  echo "Usage: init_cs6_local.sh \"<project_name>\" \"<cs6_project_folder>\" \"<cs6_build_folder>\" \
\"<supercomputer_username\" \"<supercomputer_email>\" \"<results_file>\""
  exit 1
fi

# 1. Copy hello_world to a new folder with proj_name
cp -R "$cs6_proj/$hw" "$cs6_proj/$proj_name"

# 2. Update CMakeLists.txt to reflect the new project name
echo "" >> "$cs6_proj/$cm" # new line
echo "add_subdirectory($proj_name)" >> "$cs6_proj/$cm"

# 3. Change directories to the new project folder, and update its CMakeLists.txt
sed -i "s/$hw/$proj_name/g" "$cs6_proj/$proj_name/$cm"

# 4. Update the name of the main C++ file in src/ to reflect the new project name
mv "$cs6_proj/$proj_name/src/main_hello_world.cpp" "$cs6_proj/$proj_name/src/main_$proj_name.cpp"

# 5. Change directories to cs6_build and copy hello_world to a new proj_name folder
cp -R "$cs6_build/projects/$hw" "$cs6_build/projects/$proj_name"

# 6. Change directories to the new project folder and compile the code
cd "$cs6_build/projects/$proj_name"
make clean && make -j32 # The first compilation creates a hello_world executable instead of a proj_name executable, but it does update the MakeFile.
make clean && make -j32 #Compile one more time with the new Makefile, which will create a proj_name executable

# 7. Remove the hello_world executable
rm "$cs6_build/projects/$proj_name/$hw"

# 8. Create slurm_wrapper.sh for the cs6_build
slurm_file="$cs6_build/projects/$proj_name/slurm_wrapper.sh"
echo '#!/bin/bash' > $slurm_file
echo "#SBATCH --partition=gpuq" >> $slurm_file
echo "#SBATCH --qos=gpu" >> $slurm_file
echo "#SBATCH --gres=gpu:A100.40gb:1" >> $slurm_file
echo "#SBATCH --job-name=\"ca3_ex_net\"" >> $slurm_file
echo "#SBATCH --time=0-20:00:00" >> $slurm_file
echo "#SBATCH --output $results_file" >> $slurm_file
echo "#SBATCH --mail-type=END,FAIL" >> $slurm_file
echo "#SBATCH --mail-user=$sc_email" >> $slurm_file
echo "#SBATCH --mem=20G" >> $slurm_file
echo "srun ./$proj_name" >> $slurm_file

# 9. Submit the job to cluster
sbatch $slurm_file
