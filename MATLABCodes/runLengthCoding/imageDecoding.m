function imageDecoding( runArray )

% decodes a run length coded array to regenerate the image

[~, K] = size(runArray);

N = sqrt(sum(runArray(1, 2:2:end)));
image = zeros(N);
k = 1;
i = 1;

for m = 1:N
    for n = 1:N
        if i <= runArray(1, k + 1)
            image(m, n) = runArray(1, k);
            i = i + 1;
        else
            k = k + 2;
            image(m, n) = runArray(1, k);
            i = 2;
        end
    end
end

imagesc(image);
        
end

