% compare firing rate distributions between real and sim data

fr_data;

dc=[sml_f_low_fr,sml_f_med_fr,sml_f_high_fr,med_f_low_fr,med_f_med_fr, ...
    med_f_high_fr,lrg_f_low_fr,lrg_f_med_fr_1,lrg_f_high_fr];

fprintf("median real: %f, median sim: %f, ranksum: %f, sim nrns: %.0f\n", ...
    median(real_dc),median(dc),ranksum(dc,real_dc),length(dc));
fprintf("real nrns: %.0f, iqr real: %f, iqr sim: %f\n", ...
    length(real_dc),iqr(real_dc),iqr(dc));