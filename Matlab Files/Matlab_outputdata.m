%ECE 490: Matlab Data Generation Code

%fprintf-write text to device
% s=serial('/dev/tty.KeySerial1', 'BaudRate', 9600);
%while TransferStatus !idle...

%%%%%pseudocode 
% read asterix
% send back asterix
% while true
%     serialData = read(myserialdevice,count)
%     
%     keep reading...
%     for (i=0, i< 7, i++)
%     cell1=scanned1st value
%     print cell1
%     asterix --> next coloumn
%     cellvol1=cellvoltage1
%     print voltage
%     asterix --> next coloumn
%     cellcur=cellcurrent1
%     print current 
%     asterix --> next coloumn
%     dataNumber=datanumber[i]
%     print datanumber 
%     next line, and start for loop all over
%     
%     
% stop
% 
% plot data all on one graph
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
           cell_num=fscanf(s);
       end
       
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
for cell_num = 1:8
plot(data_num, cell_voltage)
hold on
plot(data_num, cell_current)
hold on
end 

    
    
    