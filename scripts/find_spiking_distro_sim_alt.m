function find_spiking_distro_sim()
    fdr_prefix="gc_can_"; % folder name prefix
    use_supcomp_data=0; % access supercomputer data on a local computer
    local_run=4;%2;%4; % local run number
    supcomp_run=1; % supercomputer run number
    save_gridscore_file=1; % save gridscore to file
    run_on_supcomp=0; % run from supercomputer's system 
    p1=0;
    p2=0;
    preloaded_spk_reader=0;
    sel_nrn=1;
    save_plot=0; % save rate map plot
    save_traj_plot=0;
    save_firingrate_file=0; % save firing rate to file
    save_firingpeak_file=0; % save firing peak to file
    create_plot=0; % show plot on screen
    spikes=[];
    spk_data=[];
    total_nrns=1296; % total neurons to record firing rates from
    alt_data=1;
    create_ac=1;
    save_field_size=1;
    save_field_spacing=1;
    save_field_rotation=1;
    use_newly_generated_rm=0;
    use_newly_generated_ac=1;
    saved_nonfld_filt_perc=.31;%.38;%.26;
    
    for i=1:total_nrns
        try
            cd gridscore
            sel_nrn=i;
            fprintf("processing neuron %d\n",i);
            [heat_map,spikes,spk_data] = gridscore_sim_function_alt(p1,p2,local_run, ...
            run_on_supcomp, use_supcomp_data,fdr_prefix,supcomp_run, ...
            save_gridscore_file, preloaded_spk_reader,sel_nrn,save_plot, ...
            save_traj_plot, save_firingrate_file, save_firingpeak_file, create_plot, ...
            spikes, spk_data, alt_data, create_ac, save_field_size, ...
            save_field_spacing, save_field_rotation, use_newly_generated_rm, ...
            use_newly_generated_ac, saved_nonfld_filt_perc);
            preloaded_spk_reader=1;
            cd ..
        catch
            % error causes neuron to be skipped rather than exiting program
            fprintf('error processing neuron %d, skipped.\n', i);
        end
    end

	exitcode = 0;
end
