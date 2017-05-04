function [I] = diffuseImage (I, diffConst)

colormap(gray(256));

[M,N,~] = size(I);
avg = sum(sum(I(:,:,1),'omitnan')) / ((M*N) - sum(sum(isnan(I(:,:,1)))));
t = 1;

while (abs(I(1,1,t) - avg) > (0.1*avg) || abs(I(round(M/2),round(N/2),t) - avg) > (0.1*avg)) && t<100
    J = I(:,:,t)*255/max(max(I(:,:,t)));
    image(J);
    pause(0.5);
    
    for m = 1:M
        for n=1:N
            if ~isnan(I(m,n,t)) && I(m,n,t)~=2000
                if m == 1
                    if n == 1
                        I(m,n,t+1) = I(m,n,t) + (diffConst*(sum(sum(I(m:m+1,n:n+1,t),'omitnan')) - ((4-sum(sum(isnan(I(m:m+1,n:n+1,t)))))*I(m,n,t))));
                    elseif n < N
                        I(m,n,t+1) = I(m,n,t) + (diffConst*(sum(sum(I(m:m+1,n-1:n+1,t),'omitnan'))- ((6-sum(sum(isnan(I(m:m+1,n-1:n+1,t)))))*I(m,n,t))));
                    else
                        I(m,n,t+1) = I(m,n,t) + (diffConst*(sum(sum(I(m:m+1,n-1:n,t),'omitnan')) - ((4-sum(sum(isnan(I(m:m+1,n-1:n,t)))))*I(m,n,t))));
                    end
                elseif m < M
                    if n == 1
                        I(m,n,t+1) = I(m,n,t) + (diffConst*(sum(sum(I(m-1:m+1,n:n+1,t),'omitnan')) - ((6-sum(sum(isnan(I(m-1:m+1,n:n+1,t)))))*I(m,n,t))));
                    elseif n < N
                        I(m,n,t+1) = I(m,n,t) + (diffConst*(sum(sum(I(m-1:m+1,n-1:n+1,t),'omitnan')) - ((9-sum(sum(isnan(I(m-1:m+1,n-1:n+1,t)))))*I(m,n,t))));
                    else
                        I(m,n,t+1) = I(m,n,t) + (diffConst*(sum(sum(I(m-1:m+1,n-1:n,t),'omitnan')) - ((6-sum(sum(isnan(I(m-1:m+1,n-1:n,t)))))*I(m,n,t))));
                    end
                else
                    if n == 1
                        I(m,n,t+1) = I(m,n,t) + (diffConst*(sum(sum(I(m-1:m,n:n+1,t),'omitnan')) - ((4-sum(sum(isnan(I(m-1:m,n:n+1,t)))))*I(m,n,t))));
                    elseif n < N
                        I(m,n,t+1) = I(m,n,t) + (diffConst*(sum(sum(I(m-1:m,n-1:n+1,t),'omitnan')) - ((6-sum(sum(isnan(I(m-1:m,n-1:n+1,t)))))*I(m,n,t))));
                    else
                        I(m,n,t+1) = I(m,n,t) + (diffConst*(sum(sum(I(m-1:m,n-1:n,t),'omitnan')) - ((4-sum(sum(isnan(I(m-1:m,n-1:n,t)))))*I(m,n,t))));
                    end
                end
            elseif isnan(I(m,n,t))
                I(m,n,t+1) = NaN;
            elseif I(m,n,t) == 2000
                I(m,n,t+1) = 2000;
            end
        end
    end
    t = t + 1;
end

end