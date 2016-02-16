%Report Data code: Single cell data


clear; clc; close all;

delete(instrfind);
dataNumber = 1;
s = serial('/dev/tty.usbserial-00002014'); %intializes serial port being read from
fopen(s);
inputString = fscanf(s);
while ~strncmpi(inputString,'*',1)
    disp('not connected');
    inputString = fscanf(s);
    disp(inputString);
end 
fprintf(s,'*');           %print * back to arduino to begin reading data
disp('connection successss!');

%continues to read data as long as buffer has data
while true
    inputString = fscanf(s);
    if strncmpi(inputString,'&',1)
       %make temp variable for loops
       voltageStr = fscanf(s);
       voltage = str2num(voltageStr);
       currentStr = fscanf(s);
       current = str2num(currentStr);
       timeStr = fscanf(s);
       time = str2num(timeStr);
       
       disp(voltage);
       disp(current);
       disp(time);
    else
        disp('did not receive &');
        pause(1); 
    end
    

    currentArray(dataNumber) = current;
    voltageArray(dataNumber) = voltage;
    timeArray(dataNumber) = time;
    dataNumber = dataNumber + 1;

    plot(timeArray, currentArray)
    hold on;
    plot(timeArray, voltageArray)
    pause(0.01);
end
    
    

% %plots all data points on graph per data_num set
%  plot(data_num, cell_voltage, 'g*', data_num, cell_current, 'b--o')

