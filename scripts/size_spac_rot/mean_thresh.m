% load("sml_low_thsh_37perc.mat"); load("sml_high_thsh_37perc.mat");
% load("med_low_thsh_37perc.mat"); load("med_high_thsh_37perc.mat");
% load("lrg_low_thsh_37perc.mat"); load("lrg_high_thsh_37perc.mat");
load("sml_low_thsh.mat"); load("sml_high_thsh.mat");
load("med_low_thsh.mat"); load("med_high_thsh.mat");
load("lrg_low_thsh.mat"); load("lrg_high_thsh.mat");
load("sml_ids.mat"); load("selected_sml_scale.mat");
load("med_ids.mat"); load("selected_med_scale.mat");
load("lrg_ids.mat"); load("selected_lrg_scale.mat");

fprintf("sml low mean: %02f high mean: %02f general mean: %02f\n",mean(sml_low_thsh),mean(sml_high_thsh),mean([sml_low_thsh',sml_high_thsh']));
fprintf("med low mean: %02f high mean: %02f general mean: %02f\n",mean(med_low_thsh),mean(med_high_thsh),mean([med_low_thsh',med_high_thsh']));
fprintf("lrg low mean: %02f high mean: %02f general mean: %02f\n",mean(lrg_low_thsh),mean(lrg_high_thsh),mean([lrg_low_thsh',lrg_high_thsh']));
fprintf("all low mean: %02f high mean: %02f general mean: %02f\n",mean([sml_low_thsh',med_low_thsh',lrg_low_thsh']),mean([sml_high_thsh',med_high_thsh',lrg_high_thsh']),mean([sml_low_thsh',sml_high_thsh',med_low_thsh',med_high_thsh',lrg_low_thsh',lrg_high_thsh']));

sml_within_thsh=0;
mean_sml = mean([sml_low_thsh',sml_high_thsh']);
for i=1:length(sml_low_thsh)
    if mean_sml >= sml_low_thsh(i) && mean_sml <= sml_high_thsh(i)
        sml_within_thsh = sml_within_thsh + 1;
    end
end
sml_select_within_thsh=0;
for i=1:length(selected_sml_scale)
%     fprintf("%02f ",find(sml_ids==selected_sml_scale(i)));
    if mean_sml >= sml_low_thsh(find(sml_ids==selected_sml_scale(i))) && mean_sml <= sml_high_thsh(find(sml_ids==selected_sml_scale(i)))
        sml_select_within_thsh = sml_select_within_thsh + 1;
    end
end

fprintf("percent of small grid scale cells within threshold: %02f%%\n",sml_within_thsh/length(sml_low_thsh));
fprintf("percent of selected small grid scale cells within threshold: %02f%%\n",sml_select_within_thsh/length(selected_sml_scale));

med_within_thsh=0;
mean_med = mean([med_low_thsh',med_high_thsh']);
for i=1:length(med_low_thsh)
    if mean_med >= med_low_thsh(i) && mean_med <= med_high_thsh(i)
        med_within_thsh = med_within_thsh + 1;
    end
end
med_select_within_thsh=0;
for i=1:length(selected_med_scale)
%     fprintf("%02f ",find(med_ids==selected_med_scale(i)));
    if mean_med >= med_low_thsh(find(med_ids==selected_med_scale(i))) && mean_med <= med_high_thsh(find(med_ids==selected_med_scale(i)))
        med_select_within_thsh = med_select_within_thsh + 1;
    end
end

fprintf("percent of medium grid scale cells within threshold: %02f%%\n",med_within_thsh/length(med_low_thsh));
fprintf("percent of selected medium grid scale cells within threshold: %02f%%\n",med_select_within_thsh/length(selected_med_scale));

lrg_within_thsh=0;
mean_lrg = mean([lrg_low_thsh',lrg_high_thsh']);
for i=1:length(lrg_low_thsh)
    if mean_lrg >= lrg_low_thsh(i) && mean_lrg <= lrg_high_thsh(i)
        lrg_within_thsh = lrg_within_thsh + 1;
    end
end
lrg_select_within_thsh=0;
for i=1:length(selected_lrg_scale)
%     fprintf("%02f ",find(lrg_ids==selected_lrg_scale(i)));
    if mean_lrg >= lrg_low_thsh(find(lrg_ids==selected_lrg_scale(i))) && mean_lrg <= lrg_high_thsh(find(lrg_ids==selected_lrg_scale(i)))
        lrg_select_within_thsh = lrg_select_within_thsh + 1;
    end
end

fprintf("percent of large grid scale cells within threshold: %02f%%\n",med_within_thsh/length(med_low_thsh));
fprintf("percent of selected large grid scale cells within threshold: %02f%%\n",med_select_within_thsh/length(selected_med_scale));