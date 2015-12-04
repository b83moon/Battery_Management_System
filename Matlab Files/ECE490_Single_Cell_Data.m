%Report Data code: Single cell data


clear; clc; close all;
delete(instrfind);
s = serial('/dev/cu.usbmodem1411'); %intializes serial port being read from
disp(s);
fopen(s);
disp(s);
initialization = fscanf(s); %place buffer into intialization

while initialization ~= '*' %determines if arduino has sent 
end 
    fprintf('*'); %print * back to arduino to begin reading data
disp('connection successss!');
%continues to read data as long as buffer has data

    while fscanf(s) == 1
       temp = fscanf(s,c,1);
       
       if temp == '*'
            disp('*')
       else
           cell_voltage=fscanf(s);
       end
       
       if temp == '*'
            disp('*')
       else
           cell_current=fscanf(s);
       
       end
       
       if temp == '^'
           disp('^')
       else 
           data_num=fscanf(s);
       
       end
       
    end


%plots all data points on graph per data_num set
plot(data_num, cell_voltage)
hold on
plot(data_num, cell_current)
hold on


    
    
    