function manual(raspiObj, comm)


m= dec(comm)
    
    writeDigitalPin(raspiObj, 22, m(1));
    writeDigitalPin(raspiObj, 23, m(2));
    writeDigitalPin(raspiObj, 24, m(3));
    writeDigitalPin(raspiObj, 25, m(4));
    
    

end

