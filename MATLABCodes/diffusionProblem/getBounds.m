function [ boundaryPixel ] = getBounds( I )

boundaryPixel = [1 1];
m = 1;
n = 1;
k = 2;
iterations = sum(sum(I,'omitnan'))/1000;

[M,N] = size(I);

while k<=iterations
    %need to check right, bottom right, bottom, bottom left, left, top
    %left, top, top right
    if n < N
        %check right
        if I(m,n+1) == 1000 && notInArray(boundaryPixel, m, n+1)
            boundaryPixel(k,:) = [m n+1];
            n = n + 1;
            k = k + 1;
        %need to check bottom right, bottom, bottom left, left, top left,
        %top, top right
        elseif m < M
            %check bottom right
            if I(m+1,n+1) == 1000 && notInArray(boundaryPixel, m+1, n+1)
                boundaryPixel(k,:) = [m+1 n+1];
                m = m + 1;
                n = n + 1;
                k = k + 1;
            %check bottom
            elseif I(m+1,n) == 1000 && notInArray(boundaryPixel, m+1, n)
                boundaryPixel(k,:) = [m+1 n];
                m = m + 1;
                k = k + 1;
            %need to check bottom left, left, top left, top, top right
            elseif n > 1
                %check bottom left
                if I(m+1,n-1) == 1000 && notInArray(boundaryPixel, m+1, n-1)
                    boundaryPixel(k,:) = [m+1 n-1];
                    m = m + 1;
                    n = n - 1;
                    k = k + 1;
                %check left    
                elseif I(m,n-1) == 1000 && notInArray(boundaryPixel, m, n-1)
                    boundaryPixel(k,:) = [m n-1];
                    n = n - 1;
                    k = k + 1;
                %need to check top left, top, top right    
                elseif m > 1
                    %check top left
                    if I(m-1,n-1) == 1000 && notInArray(boundaryPixel, m-1, n-1)
                        boundaryPixel(k,:) = [m-1 n-1];
                        m = m - 1;
                        n = n - 1;
                        k = k + 1;
                    %check top    
                    elseif I(m-1,n) == 1000 && notInArray(boundaryPixel, m-1, n)
                        boundaryPixel(k,:) = [m-1 n];
                        m = m - 1;
                        k = k + 1;
                    %check top right
                    elseif I(m-1,n+1) == 1000 && notInArray(boundaryPixel, m-1, n+1)
                        boundaryPixel(k,:) = [m-1 n+1];
                        m = m - 1;
                        n = n + 1;
                        k = k + 1;
                    end
                end
            %need to check top, top right    
            elseif m > 1
                %check top
                if I(m-1,n) == 1000 && notInArray(boundaryPixel, m-1, n)
                    boundaryPixel(k,:) = [m-1 n];
                    m = m - 1;
                    k = k + 1;
                %check top right    
                elseif I(m-1,n+1) == 1000 && notInArray(boundaryPixel, m-1, n+1)
                    boundaryPixel(k,:) = [m-1 n+1];
                    m = m - 1;
                    n = n + 1;
                    k = k + 1;
                end
            end
        %need to check left, top left, top, top right    
        elseif n > 1
            %check left
            if I(m,n-1) == 1000 && notInArray(boundaryPixel, m, n-1)
                boundaryPixel(k,:) = [m n-1];
                n = n - 1;
                k = k + 1;
            %need to check top left, top, top right    
            elseif m > 1
                %check top left
                if I(m-1,n-1) == 1000 && notInArray(boundaryPixel, m-1, n-1)
                    boundaryPixel(k,:) = [m-1 n-1];
                    m = m - 1;
                    n = n - 1;
                    k = k + 1;
                %check top    
                elseif I(m-1,n) == 1000 && notInArray(boundaryPixel, m-1, n)
                    boundaryPixel(k,:) = [m-1 n];
                    m = m - 1;
                    k = k + 1;
                %check top right    
                elseif I(m-1,n+1) == 1000 && notInArray(boundaryPixel, m-1, n+1)
                    boundaryPixel(k,:) = [m-1 n+1];
                    m = m - 1;
                    n = n + 1;
                    k = k + 1;
                end
            end
        %check top    
        elseif I(m-1,n) == 1000 && notInArray(boundaryPixel, m-1, n)
            boundaryPixel(k,:) = [m-1 n];
            m = m - 1;
            k = k + 1;
        %check top right    
        elseif I(m-1,n+1) == 1000 && notInArray(boundaryPixel, m-1, n+1)
            boundaryPixel(k,:) = [m-1 n+1];
            m = m - 1;
            n = n + 1;
            k = k + 1;
        end
    %need to check bottom, bottom left, left, top left, top, top right    
    elseif m < M
        %check bottom
        if I(m+1,n) == 1000 && notInArray(boundaryPixel, m+1, n)
            boundaryPixel(k,:) = [m+1 n];
            m = m + 1;
            k = k + 1;
        %check bottom left
        elseif I(m+1,n-1) == 1000 && notInArray(boundaryPixel, m+1, n-1)
            boundaryPixel(k,:) = [m+1 n-1];
            m = m + 1;
            n = n - 1;
            k = k + 1;
        %check left
        elseif I(m,n-1) == 1000 && notInArray(boundaryPixel, m, n-1)
                boundaryPixel(k,:) = [m n-1];
                n = n - 1;
                k = k + 1;
        %need to check top left, top, top right
        elseif m > 1
            %check top left
            if I(m-1,n-1) == 1000 && notInArray(boundaryPixel, m-1, n-1)
                boundaryPixel(k,:) = [m-1 n-1];
                m = m - 1;
                n = n - 1;
                k = k + 1;
            %check top
            elseif I(m-1,n) == 1000 && notInArray(boundaryPixel, m-1, n)
                boundaryPixel(k,:) = [m-1 n];
                m = m - 1;
                k = k + 1;
            end
        end
    %need to check left, top left, top   
    else
        %check left
        if I(m,n-1) == 1000 && notInArray(boundaryPixel, m, n-1)
            boundaryPixel(k,:) = [m n-1];
            n = n - 1;
            k = k + 1;
        %check top left
        elseif I(m-1,n-1) == 1000 && notInArray(boundaryPixel, m-1, n-1)
            boundaryPixel(k,:) = [m-1 n-1];
            m = m - 1;
            n = n - 1;
            k = k + 1;
        %check top
        elseif I(m-1,n) == 1000 && notInArray(boundaryPixel, m-1, n)
            boundaryPixel(k,:) = [m-1 n];
            m = m - 1;
            k = k + 1;
        end
    end
end

end

