%Report Data code: Single cell data


clear; clc; close all;

delete(instrfind);
dataNumber = 1;
s = serial('/dev/tty.usbserial-00001014'); %intializes serial port being read from
fopen(s);
Ddisp(s);
while fscanf(s) == '*'
inputString = fscanf(s);
while ~strncmpi(inputString,'*',1)
    disp('not connected');
    inputString = fscanf(s);
    disp(inputString);
end 
fprintf(s,'*');           %print * back to arduino to begin reading data
disp('connection successss!');
<<<<<<< HEAD
while fscanf(s)=='&'
end
=======
>>>>>>> 94e3b3fbba7ec73113073245f8347ff4c6804618

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
<<<<<<< HEAD
    end
%        %display time then move on for other *
%        if temp == '*'
%             disp('*')
%        else
%            time=fscanf(s);
%        end
% 
%        %display voltage then move on for other *
%        if temp == '*'
%             disp('*')
%        else
%            cell_voltage=fscanf(s);
%        end
%        
%         %display current then move on for other *
%        if temp == '*'
%             disp('*')
%        else
%            cell_current=fscanf(s);
%        
%        end
%        
%        %wait for ^ to take in data set
%        if temp == '^'
%            disp('^')
%        else 
%            data_num=fscanf(s);
%        end
        disp('did not receive &');
        pause(1); 
=======
    else
        disp('did not receive &');
        pause(1); 
    end
    
    currentArray(dataNumber) = current;
    voltageArray(dataNumber) = voltage;
    timeArray(dataNumber) = time;
    dataNumber = dataNumber + 1;

>>>>>>> 94e3b3fbba7ec73113073245f8347ff4c6804618
end


    
    

%plots all data points on graph per data_num set
%  plot(data_num, cell_voltage, 'g*', data_num, cell_current, 'b--o')



    
    
    