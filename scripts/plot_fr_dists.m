% Create histogram of firing rates from combined distributions.
% Plot using custom bin width.
% d1, d2, etc. are distributions of firing rates.

bin_width = 11;
fr_data2;

dc=[d1,d1,d1,d1,d1,d1,d1,d2,d3,d3,d3,d3,d3,d3,d4,d4,d4,d5,d5,d5,d5,d5,d5,d6,d6,d6]; % combined distributions
%dc=real_dc;
bins=linspace(0, 5, bin_width);
hc = histcounts(dc,bins);
histogram('BinCounts', hc, 'BinEdges', bins);
title("Simulated Cells' Firing Rates", 'FontSize', 15);
axis('tight');
xlabel('Firing Rate (Hz)','FontSize', 15);
ylabel('Number of Cells','FontSize', 15);