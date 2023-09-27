% compare firing rate distributions between real and sim data

fr_data;

% choose stat reports
report_mean_fr=1; % average (mean) firing rates
report_peak_fr=0; % peak firing rates
report_gridscores=0; % grid scores
report_gridscores_lim1=0; % grid scores of limited cells version 1
report_gridscores_lim2=0; % grid scores of limited cells version 2

%%%%    %%%%    %%%%    %%%%    %%%%    
if report_mean_fr
    fprintf("Avg. firing rates stats:\n");
    
    dc=[sml_f_low_fr,sml_f_med_fr,sml_f_high_fr,med_f_low_fr,med_f_med_fr, ...
        med_f_high_fr,lrg_f_low_fr,lrg_f_med_fr,lrg_f_high_fr];
    
    fprintf("median real: %f, median sim: %f, ranksum: %f, sim nrns: %.0f\n", ...
        median(real_dc),median(dc),ranksum(dc,real_dc),length(dc));
    fprintf("real nrns: %.0f, iqr real: %f, iqr sim: %f\n", ...
        length(real_dc),iqr(real_dc),iqr(dc));
end
%%%%    %%%%    %%%%    %%%%    %%%%    
if report_peak_fr
    fprintf("Peak firing rates stats:\n");
    
    dc_peak=[sml_f_low_fr_peak, sml_f_med_fr_peak, sml_f_high_fr_peak, med_f_low_fr_peak, ...
        med_f_med_fr_peak, med_f_high_fr_peak, lrg_f_low_fr_peak, lrg_f_med_fr_peak, ...
        lrg_f_high_fr_peak];
    
    fprintf("median real: %f, median sim: %f, ranksum: %f, sim nrns: %.0f\n", ...
        median(real_dc_peak),median(dc_peak),ranksum(dc_peak,real_dc_peak),length(dc_peak));
    fprintf("real nrns: %.0f, iqr real: %f, iqr sim: %f\n", ...
        length(real_dc_peak),iqr(real_dc_peak),iqr(dc_peak));
end
%%%%    %%%%    %%%%    %%%%    %%%%    
if report_gridscores
    fprintf("Gridscore stats:\n");

    dc_gridscore=[sml_f_low_fr_gridscore, sml_f_med_fr_gridscore, sml_f_high_fr_gridscore, ...
        med_f_low_fr_gridscore, med_f_med_fr_gridscore, med_f_high_fr_gridscore, ...
        lrg_f_low_fr_gridscore, lrg_f_med_fr_gridscore, lrg_f_high_fr_gridscore];
    
    fprintf("median real: %f, median sim: %f, ranksum: %f, sim nrns: %.0f\n", ...
        median(real_dc_gridscore),median(dc_gridscore),ranksum(dc_gridscore,real_dc_gridscore),length(dc_gridscore));
    fprintf("real nrns: %.0f, iqr real: %f, iqr sim: %f\n", ...
        length(real_dc_gridscore),iqr(real_dc_gridscore),iqr(dc_gridscore));
end
%%%%    %%%%    %%%%    %%%%    %%%%    
if report_gridscores_lim1
    fprintf("Limited sim version stats (9 sim cells vs all real cells):\n");
    
    fprintf("median real: %f, median sim: %f, ranksum: %f, sim nrns: %.0f\n", ...
        median(real_dc),median(sim_dc_avg_lim),ranksum(sim_dc_avg_lim,real_dc),length(sim_dc_avg_lim));
    fprintf("real nrns: %.0f, iqr real: %f, iqr sim: %f\n", ...
        length(real_dc),iqr(real_dc),iqr(sim_dc_avg_lim));
    fprintf("median real: %f, median sim: %f, ranksum: %f, sim nrns: %.0f\n", ...
        median(real_dc_peak),median(sim_dc_peak_lim),ranksum(sim_dc_peak_lim,real_dc_peak),length(sim_dc_peak_lim));
    fprintf("real nrns: %.0f, iqr real: %f, iqr sim: %f\n", ...
        length(real_dc_peak),iqr(real_dc_peak),iqr(sim_dc_peak_lim));
    fprintf("median real: %f, median sim: %f, ranksum: %f, sim nrns: %.0f\n", ...
        median(real_dc_gridscore),median(sim_dc_gridscore_lim),ranksum(sim_dc_gridscore_lim,real_dc_gridscore),length(sim_dc_gridscore_lim));
    fprintf("real nrns: %.0f, iqr real: %f, iqr sim: %f\n", ...
        length(real_dc_gridscore),iqr(real_dc_gridscore),iqr(sim_dc_gridscore_lim));
end
%%%%    %%%%    %%%%    %%%%    %%%%    
if report_gridscores_lim2
    fprintf("Limited sim version stats (9 sim cells vs 9 real cells):\n");
    
    fprintf("median real: %f, median sim: %f, ranksum: %f, sim nrns: %.0f\n", ...
        median(real_dc_avg_lim),median(sim_dc_avg_lim),ranksum(sim_dc_avg_lim,real_dc_avg_lim),length(sim_dc_avg_lim));
    fprintf("real nrns: %.0f, iqr real: %f, iqr sim: %f\n", ...
        length(real_dc_avg_lim),iqr(real_dc_avg_lim),iqr(sim_dc_avg_lim));
    fprintf("median real: %f, median sim: %f, ranksum: %f, sim nrns: %.0f\n", ...
        median(real_dc_peak_lim),median(sim_dc_peak_lim),ranksum(sim_dc_peak_lim,real_dc_peak_lim),length(sim_dc_peak_lim));
    fprintf("real nrns: %.0f, iqr real: %f, iqr sim: %f\n", ...
        length(real_dc_peak_lim),iqr(real_dc_peak_lim),iqr(sim_dc_peak_lim));
    fprintf("median real: %f, median sim: %f, ranksum: %f, sim nrns: %.0f\n", ...
        median(real_dc_gridscore_lim),median(sim_dc_gridscore_lim),ranksum(sim_dc_gridscore_lim,real_dc_gridscore_lim),length(sim_dc_gridscore_lim));
    fprintf("real nrns: %.0f, iqr real: %f, iqr sim: %f\n", ...
        length(real_dc_gridscore_lim),iqr(real_dc_gridscore_lim),iqr(sim_dc_gridscore_lim));
end