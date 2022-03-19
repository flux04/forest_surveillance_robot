function followme(fm, raspiObj, cam)

th=640/2;
minarea=15000;
maxarea=20000;


% Set a loop that stop after 1000 frames of aquisition
while fm==1
    
    % Get the snapshot of the current frame
    data = snapshot(cam);
    
    % Now to track red objects in real time
    % we have to subtract the red component 
    % from the grayscale image to extract the red components in the image.
    diff_im = imsubtract(data(:,:,1), rgb2gray(data));
    %Use a median filter to filter out noise
    diff_im = medfilt2(diff_im, [3 3]);
    % Convert the resulting grayscale image into a binary image.
    diff_im = im2bw(diff_im,0.18);
    
    % Remove all those pixels less than 1000px
    diff_im = bwareaopen(diff_im,1000);   %increase
    
    % Label all the connected components in the image.
    bw = bwlabel(diff_im, 8);
    
    % Here we do the image blob analysis.
    % We get a set of properties for each labeled region.
    stats = regionprops(bw, 'BoundingBox', 'Centroid');
   
    imshow(data)
    hold on
    
    %This is a loop to bound the red objects in a rectangular box.
    for object = 1:length(stats)
        bb = stats(object).BoundingBox;
        bc = stats(object).Centroid;
%         area = stats(object).Area;
        area = bb(3) * bb(4);

        rectangle('Position',bb,'EdgeColor','r','LineWidth',2)
        plot(bc(1),bc(2), '-m+')
        a=text(bc(1)+15,bc(2), strcat('X: ', num2str(round(bc(1))), '    Y: ', num2str(round(bc(2)))));
        set(a, 'FontName', 'Arial', 'FontWeight', 'bold', 'FontSize', 12, 'Color', 'yellow');

        if bc(1)>(th+25)
            title('right');
            comm=2;
        elseif bc(1)<(th-25)
            title('left');
            comm=1;
        elseif bc(1)>(th-25) && bc(1)<(th+25)
            if area<minarea
                title('forward'); 
                comm=4;
            elseif area>maxarea
                title('backward');  
                comm=3;
            else 
                title('stop');
                comm=0;
            end
        else
            title('not found')
        end
         m= dec(comm);
         writeDigitalPin(raspiObj, 22, m(1));
         writeDigitalPin(raspiObj, 23, m(2));
         writeDigitalPin(raspiObj, 24, m(3));
         writeDigitalPin(raspiObj, 25, m(4));

    end
    
    hold off
    drawnow;

end
% Both the loops end here.

end