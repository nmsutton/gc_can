% Create histogram of firing rates from combined distributions.
% Plot using custom bin width.
% d1, d2, etc. are distributions of firing rates.

bin_width = 20;

dc=[d1;d2;d2;d2;d2;d2;d3;d3;d3;d3;d3;d3;]; % combined distributions
bins=linspace(0, 5, bin_width);
hc = histcounts(dc,bins);
histogram('BinCounts', hc, 'BinEdges', bins);