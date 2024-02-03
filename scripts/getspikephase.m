function [angle, magnitude, varargout]=getspikephase(activitytimes, netPer, varargin)
if isempty(varargin)
    modactivitytimes = mod(activitytimes, netPer);
else
    peaks=varargin{1};
    modactivitytimes=zeros(length(activitytimes),1);
    peaks=[peaks(1:end-1)'; peaks(end):mean(diff(peaks)):(max(activitytimes)+mean(diff(peaks)))];
    for a=1:length(activitytimes)
        % these next two lines take up most of the time in this function
        idx=find(activitytimes(a)>=peaks(1:end-1) & activitytimes(a)<peaks(2:end),1,'first');  
        try
            if isempty(idx)
                % modactivitytimes(a) remains at 0
            else
                modactivitytimes(a)=(activitytimes(a)-peaks(idx))/(peaks(idx+1)-peaks(idx))*netPer;
            end
        catch me
            %me
            fprintf("error in getspikephase.m ");
            %disp(a);
        end
    end
end
n=length(activitytimes);
xbar = 1/n*sum(sin(modactivitytimes*pi/(netPer/2)));
ybar = 1/n*sum(cos(modactivitytimes*pi/(netPer/2)));

magnitude=sqrt(xbar^2+ybar^2);
if xbar>0
    angle = acos(ybar/magnitude);
else
    angle = 2*pi - acos(ybar/magnitude);
end

if nargout>2
    varargout{1}=modactivitytimes;
end