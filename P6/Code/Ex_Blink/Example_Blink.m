UNO = arduino();

for i=1:10
    writeDigitalPin(UNO,'D13',1);
    pause(1);
    writeDigitalPin(UNO,'D13',0);
    pause(1);
end