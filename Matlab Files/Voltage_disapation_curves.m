% create a socket connection to raspberry pi to log the data 

import BMS_Functions.*
clear;
clc; 
close all;
funct
% s = serial('/dev/tty.usbmodem1411','baudRate',9600);
% 
% while true
%     incomingData = s.BytesAvailable; 
%     if incomingData ~= 0 
%         LogData();
% 
%         
%    
%     end
% end


f = LogData();


