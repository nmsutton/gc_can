%{
    This script creates a random selection of a cell number given a
    population of cells.
%}

N = 1600;%1296;%1600; % population size

rn = round(rand()*N); % random number

fprintf("Cell selection: %d\n",rn);