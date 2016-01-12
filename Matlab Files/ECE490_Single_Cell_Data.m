%Report Data code: Single cell data


clear; clc; close all;
delete(instrfind);
s = serial('/dev/cu.usbmodem1421'); %intializes serial port being read from
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
while fscanf(s)=='&'
end

%continues to read data as long as buffer has data

while true
    inputString = fscanf(s);
    disp(inputString);
    if strncmpi(inputString,'&',1)
       disp('hi');
       %make temp variable for loops
       voltage = fscanf(s);
       current = fscanf(s);
       time = fscanf(s);
       
       disp(voltage);
       disp(current);
       disp(time);
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
end


    
    

%plots all data points on graph per data_num set
%  plot(data_num, cell_voltage, 'g*', data_num, cell_current, 'b--o')



    
    
    