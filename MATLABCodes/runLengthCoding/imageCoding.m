function [runArray] = imageCoding (filePath)
% MATLAB code to implement run-length coding in grayscale images

% Read the image with the right format and display
I = imread(filePath);

image = I(:,:,1);
[M, N] = size(image);

colormap(gray(256));
imagesc(image);

% Generate the run array
pixelArray = zeros(1, 256);
k = 1;
runArray(k) = -1;
for m = 1:M
    for n = 1:N
        pixelArray(1, image(m, n) + 1) = pixelArray(1, image(m, n) + 1) + 1;
        
        if image(m, n) == runArray(k)
            runArray(k + 1) = runArray(k + 1) + 1;
        else
            if m*n ~= 1
                k = k + 2;
            end
            runArray(k) = image(m, n);
            runArray(k + 1) = 1; 
        end
    end
end

end

