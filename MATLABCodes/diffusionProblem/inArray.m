function check = notInArray(arr, m, n)

L = length(arr);
check = 1;

for l=1:L
    if arr(l,1) == m && arr(l,2) == n
        check = 0;
        break;
    end
end     

end

