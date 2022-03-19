function imagemode(raspiObj, cam, fm)    %%TRY TAKING app.rpi as input from app
close all;

    if fm==0
        imageproc(fm, raspiObj, cam);
    elseif fm==1
        followme(fm, raspiObj, cam);
    elseif fm==2
        object_id_raspi(fm, raspiObj, cam);
%     elseif fm==3
%         clear cam;
%         clear raspiObj;
    end
end