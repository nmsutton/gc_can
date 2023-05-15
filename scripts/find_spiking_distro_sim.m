function find_spiking_distro_sim()
    fdr_prefix="gc_can_"; % folder name prefix
    use_hopper_data=1; % access hopper data locally
    local_run=4; % local run number
    hopper_run=2; % hopper run number
    save_gridscore_file=0; % save gridscore to file
    run_on_hopper=0; % run from hopper's system 
    p1=0;
    p2=0;
    preloaded_spk_reader=0;
    sel_nrn=1;
    save_plot=0; % save rate map plot
    save_traj_plot=0;
    save_firingrate_file=1; % save firing rate to file
    create_plot=0; % show plot on screen
    spikes=[];
    spk_data=[];
    total_nrns=1600; % total neurons to record firing rates from
    
    for i=1:total_nrns
        cd gridscore
        sel_nrn=i;
        fprintf("processing neuron %d\n",i);
        [heat_map,spikes,spk_data] = gridscore_sim_function(p1,p2,local_run, ...
        run_on_hopper, use_hopper_data,fdr_prefix,hopper_run, ...
        save_gridscore_file, preloaded_spk_reader,sel_nrn,save_plot, ...
        save_traj_plot, save_firingrate_file,create_plot,spikes,spk_data);
        preloaded_spk_reader=1;
        cd ..
    end

	exitcode = 0;
end