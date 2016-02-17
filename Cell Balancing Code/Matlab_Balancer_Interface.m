%% Report Data code: Single cell data
clc; close all;
currentArray(1) = 0;
timeArray(1) = 0;
%Determine if There is old data
try
    if (Cell1CharingData.DataNumber < 1)
    end
    disp('Resume Charging Cell')
    size = size(Cell1CharingData.Time)
    previousTime = Cell1CharingData.Time(size(2));
catch 
    dataNumber = 1;
    Cell1CharingData = struct('Current',currentArray,'Time',timeArray,'DataNumber', dataNumber);
    disp('First time charging this cell')
    previousTime = 0;
end
%Name Charging Cell


%% Start Serial Handshake
delete(instrfind);
s = serial('/dev/tty.usbserial-00002214'); %intializes serial port being read from
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
    Cell1CharingData.Current(Cell1CharingData.DataNumber) = current;
    Cell1CharingData.Time(Cell1CharingData.DataNumber) = time;
    Cell1CharingData.DataNumber = Cell1CharingData.DataNumber + 1;

    plot(Cell1CharingData.Time, Cell1CharingData.Current)
    pause(0.01);   
    
    
end
%% End     
    
