% compare firing rate distributions between real and sim data

ssr_data;

%%%%    %%%%    %%%%    %%%%    %%%%  
% { New Methods } %
fprintf("New Methods:\n");
fprintf("Size: median real: %f, median sim: %f, ranksum: %f, sim nrns: %.0f\n", ...
    median(real_size_new_methods),median(sim_size_new_methods),ranksum(sim_size_new_methods,real_size_new_methods),length(sim_size_new_methods));
fprintf("real nrns: %.0f, iqr real: %f, iqr sim: %f\n", ...
    length(real_size_new_methods),iqr(real_size_new_methods),iqr(sim_size_new_methods));
fprintf("Spacing: median real: %f, median sim: %f, ranksum: %f, sim nrns: %.0f\n", ...
    median(real_spac_new_methods),median(sim_spac_new_methods),ranksum(sim_spac_new_methods,real_spac_new_methods),length(sim_spac_new_methods));
fprintf("real nrns: %.0f, iqr real: %f, iqr sim: %f\n", ...
    length(real_spac_new_methods),iqr(real_spac_new_methods),iqr(sim_spac_new_methods));
fprintf("Angles: median real: %f, median sim: %f, ranksum: %f, sim nrns: %.0f\n", ...
    median(real_ang_new_methods),median(sim_ang_new_methods),ranksum(sim_ang_new_methods,real_ang_new_methods),length(sim_ang_new_methods));
fprintf("real nrns: %.0f, iqr real: %f, iqr sim: %f\n", ...
    length(real_ang_new_methods),iqr(real_ang_new_methods),iqr(sim_ang_new_methods));
fprintf("\n\nPrior Methods:\n");
%%%%    %%%%    %%%%    %%%%    %%%%  

% choose stat reports
report_sizes=1; % average (mean) firing rates
report_spacing=1; % peak firing rates
report_angles=1; % grid scores

%%%%    %%%%    %%%%    %%%%    %%%%    
if report_sizes
    fprintf("Field sizes stats:\n");
    
    sim_sizes=[sml_scale_low_fr_sizes,sml_scale_med_fr_sizes,sml_scale_high_fr_sizes,med_scale_low_fr_sizes,med_scale_med_fr_sizes,med_scale_high_fr_sizes, ...
        lrg_scale_low_fr_sizes,lrg_scale_med_fr_sizes,lrg_scale_high_fr_sizes];
    
    fprintf("median real: %f, median sim: %f, ranksum: %f, sim nrns: %.0f\n", ...
        median(real_sizes),median(sim_sizes),ranksum(sim_sizes,real_sizes),length(sim_sizes));
    fprintf("real nrns: %.0f, iqr real: %f, iqr sim: %f\n", ...
        length(real_sizes),iqr(real_sizes),iqr(sim_sizes));
end
%%%%    %%%%    %%%%    %%%%    %%%%    
if report_spacing
    fprintf("Field spacing stats:\n");
    
    sim_spacing=[sml_scale_low_fr_spacing,sml_scale_med_fr_spacing,sml_scale_high_fr_spacing,med_scale_low_fr_spacing,med_scale_med_fr_spacing,med_scale_high_fr_spacing, ...
        lrg_scale_low_fr_spacing,lrg_scale_med_fr_spacing,lrg_scale_high_fr_spacing];
    
    fprintf("median real: %f, median sim: %f, ranksum: %f, sim nrns: %.0f\n", ...
        median(real_spacings),median(sim_spacing),ranksum(sim_spacing,real_spacings),length(sim_spacing));
    fprintf("real nrns: %.0f, iqr real: %f, iqr sim: %f\n", ...
        length(real_spacings),iqr(real_spacings),iqr(sim_spacing));
end
%%%%    %%%%    %%%%    %%%%    %%%%    
if report_angles
    fprintf("Field angles stats:\n");

    sim_angles=[sml_scale_low_fr_angles,sml_scale_med_fr_angles,sml_scale_high_fr_angles,med_scale_low_fr_angles,med_scale_med_fr_angles,med_scale_high_fr_angles, ...
         lrg_scale_low_fr_angles,lrg_scale_med_fr_angles,lrg_scale_high_fr_angles];
    
    fprintf("median real: %f, median sim: %f, ranksum: %f, sim nrns: %.0f\n", ...
        median(real_angles),median(sim_angles),ranksum(sim_angles,real_angles),length(sim_angles));
    fprintf("real nrns: %.0f, iqr real: %f, iqr sim: %f\n", ...
        length(real_angles),iqr(real_angles),iqr(sim_angles));
end