% figure for IZ param ranges

ranges=[0.62 0.98; 0.004 0.005; -23.77 11.69; 3 119; 118 131; -62.65 -58.53; ...
    -43.6 -43.52; 7.85 11.48; -52.68 -49.52];

for i=1:9
    r1=ranges(i,1); r2=ranges(i,2);
    data_range = linspace(r1, r2, 10);
    s_plot = subplot(9, 1, i);
    plot(s_plot,data_range,1)
    %xlim([r1 r2])
    %{
    xticklabels({r1+((r2-r1)*0),r1+((r2-r1)*0.125),r1+((r2-r1)*0.25), ...
        r1+((r2-r1)*0.375),r1+((r2-r1)*0.5),r1+((r2-r1)*0.625), ...
        r1+((r2-r1)*0.75),r1+((r2-r1)*0.875),r1+((r2-r1)*1)});
    %}
    set(gca,'XLim',[r1 r2],'XTick',[r1:(r2-r1)/10:r2])
end