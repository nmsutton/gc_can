# Find firing rate distribution for simulation results.
# This code allows for firing rate results measured after
# rate map smoothing and occupancy normalization.
# This can be run from the command line without the matlab gui.
#
# Settings should be set in gridscore_sim_function.m.

# this is the alt version for 36x36 grid cell layer size

module load matlab # load matlab on remote computer

matlab -nodisplay -r "find_spiking_distro_sim_alt; exit"