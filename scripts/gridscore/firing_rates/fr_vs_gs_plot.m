% Test Significance of Linear Regression Model of firing rate vs.
% grid3score.
% A small p-value indicates that the model fits significantly better than a 
% degenerate model consisting of only an intercept term.
% This is a linear hypothesis test on linear regression model coefficients.
% reference: https://www.mathworks.com/help/stats/linearmodel.coeftest.html

load fr;
load gs;

% plot
scatter(fr,gs,'filled')
ls=lsline;
set(ls,'LineWidth',3)
set(ls,'Color',[.5 .7 .7])
ylim([0.0 2.0])
title('Firing Rate vs. Grid3Score')
xlabel('Firing Rate') 
ylabel('Grid3Score') 

% significance test
tbl = table(fr,gs);
mdl = fitlm(tbl,'fr ~ gs')
[p,F] = coefTest(mdl)
