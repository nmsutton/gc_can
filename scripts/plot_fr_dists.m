% Create histogram of firing rates from combined distributions.
% Plot using custom bin width.
% d1, d2, etc. are distributions of firing rates.

bin_width = 0.4;%0.4;%0.43;%0.4;%0.3;%0.3;%0.4;%0.5;%11;
fr_data3;

%dc=[d1,d1,d1,d1,d1,d1,d1,d2,d3,d3,d3,d3,d3,d3,d4,d4,d4,d5,d5,d5,d5,d5,d5,d6,d6,d6]; % combined distributions
%dc=[d1,d2,d3];
%dc=[d7,d7,d7,d8,d9,d10,d11,d11,d11];
%dc=[d7,d7,d7,d7,d7,d7,d7,d7,d7,d12,d12s,d12s,d12s,d12,d10,d11, ...
%    d13s,d13s,d14s,d14s,d15s,d15s,d15s,d15s,d15s,d15s,d16s,d16s];
% dc=[d7,d7,d7,d7,d7,d7,d7,d16s,d16s,d16s,d16s,d16s,d10,d11,d12,d17s, ...
%     d17s,d17s,d17s,d17s,d17s,d17s,d17s,d17s,d17s,d17s ...
%     ];
dc=[d7,d12,d17,d14,d10,d13,d16,d11];
%bins=linspace(0, 5, bin_width);
%hc = histcounts(dc,bins);
%histogram('BinCounts', hc, 'BinEdges', bins);
%h1=histogram(real_dc);
%h1=histogram(d13);
h1=histogram(dc);
h1.BinWidth=bin_width;
title("Simulated Cells' Firing Rates", 'FontSize', 15);
axis('tight');
xlabel('Firing Rate (Hz)','FontSize', 15);
ylabel('Number of Cells','FontSize', 15);
%xlim([0 4.4]);
%xlim([0 0.75]);