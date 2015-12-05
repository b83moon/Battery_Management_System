%Report Data code: Single cell data


clear; clc; close all;
delete(instrfind);
s = serial('/dev/cu.usbserial-ADAOESO6w'); %intializes serial port being read from
fopen(s);
disp(s);
while fscanf(s) ~= '*'
    disp('not connected');
end 
fprintf(s,'*');           %print * back to arduino to begin reading data
disp('connection successss!');
disp(fscanf(s));

%continues to read data as long as buffer has data
while true
    durp = fscanf(s);
    disp(durp);
    if  durp == 'y'
       disp('hi');
       %make temp variable for loops
       voltage = fscanf(s);
       current = fscanf(s);
       time = fscanf(s);
       disp(voltage);
       disp(current);
       disp(time);
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
    else
        disp('did not receive &');
        pause(1); 
    end

end
    
    

%plots all data points on graph per data_num set
 plot(data_num, cell_voltage, 'g*', data_num, cell_current, 'b--o')



    
    
    