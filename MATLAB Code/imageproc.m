function imageproc(fm, raspiObj, cam)

load animalnet.mat

%Initialize DNN and the input size
nett        = animalnet;
inputSize  = [224, 224,3]; %net.Layers(1).InputSize;

%Initialize text to display
textToDisplay = '......';

% Main loop
start = tic;
fprintf('Entering into while loop.\n');
while fm==0
    %Capture image from webcam
    img = snapshot(cam);
    
    elapsedTime = toc(start);
    %Process frames at 1 per second
    if elapsedTime > 1
        %Resize the image
        imgSizeAdjusted = imresize(img,inputSize(1:2));
        %Classify the input image
        [label,score] = nett.classify(imgSizeAdjusted);
        maxScore = max(score);
        
        labelStr = cellstr(label);
        textToDisplay = sprintf('Label : %s \nScore : %f',labelStr{:},maxScore);
        start = tic;
    end
    
    %Display the predicted label
    img_label = insertText(img,[0,0],textToDisplay);
    displayImage(raspiObj,img_label);
end
clear all;
end