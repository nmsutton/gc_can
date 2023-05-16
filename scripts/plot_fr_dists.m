% Create histogram of firing rates from combined distributions.
% Plot using custom bin width.
% d1, d2, etc. are distributions of firing rates.

bin_width = 0.2;%0.4;%0.43;%0.4;%0.3;%0.3;%0.4;%0.5;%11;
fr_data3;

%dc=[d1,d1,d1,d1,d1,d1,d1,d2,d3,d3,d3,d3,d3,d3,d4,d4,d4,d5,d5,d5,d5,d5,d5,d6,d6,d6]; % combined distributions
%dc=[d1,d2,d3];
dc=real_dc;
%bins=linspace(0, 5, bin_width);
%hc = histcounts(dc,bins);
%histogram('BinCounts', hc, 'BinEdges', bins);
%h1=histogram(dc);
h1=histogram(d10);
h1.BinWidth=bin_width;
title("Simulated Cells' Firing Rates", 'FontSize', 15);
axis('tight');
xlabel('Firing Rate (Hz)','FontSize', 15);
ylabel('Number of Cells','FontSize', 15);