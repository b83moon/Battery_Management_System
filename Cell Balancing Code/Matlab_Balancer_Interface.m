%% READ ME
% make sure to rename Charging Cell to correct number and Charge Number
% Make sure to save workspace and check for workspace before charging
% make sure DC-DC Voltage is 3.66 Volts
% control c stops the code
% note that charging will continue if you stop matlab




%% Report Data code: Single cell data
clc; close all;
currentArray(1) = 0;
timeArray(1) = 0;
%Determine if There is old data
try
    if (Cell1CharingData1.DataNumber > 1)
    end
    disp('Resume Charging Cell')
    PreviousDataPoints = length(Cell1CharingData1.Time);
        %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%Name Charging Cell%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    previousTime = Cell1CharingData1.Time(PreviousDataPoints);
catch 
    dataNumber = 1;
        %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%Name Charging Cell%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    Cell1CharingData1 = struct('Current',currentArray,'Time',timeArray,'DataNumber', dataNumber);
    disp('First time charging this cell')
    previousTime = 0;
end
%Name Charging Cell


%% Start Serial Handshake
delete(instrfind);
s = serial('/dev/tty.usbserial-00001014'); %intializes serial port being read from
fopen(s);
inputString = fscanf(s);
while ~strncmpi(inputString,'*',1)
    disp('not connected');
    inputString = fscanf(s);
    disp(inputString);
end 
fprintf(s,'*');           %print * back to arduino to begin reading data
disp('connection successss!');



%% continues to read data as long as buffer has data
while true
    %% Receive and Handle Serial Data
    inputString = fscanf(s);
    disp(inputString);
    if strncmpi(inputString,'&',1)
       %make temp variable for loops
       currentStr = fscanf(s);
       current = str2num(currentStr);
       
       timeStr = fscanf(s);
       time = str2num(timeStr);
       
       disp(current);
       disp(time);
    else
        disp('did not receive &');
        pause(1); 
    end
    
    
    %%  Put Data into Structure Plot Data
    Cell1CharingData1.Current(Cell1CharingData1.DataNumber) = current;
    Cell1CharingData1.Time(Cell1CharingData1.DataNumber) = time + previousTime;
    Cell1CharingData1.DataNumber = Cell1CharingData1.DataNumber + 1;

    plot(Cell1CharingData1.Time, Cell1CharingData1.Current)
    pause(0.01);   
    
    
end
%% End     
    
