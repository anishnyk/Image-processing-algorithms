function [diffuseArray, particleArray, delta, shapeNumber] = diffuseProblem(I, diffConst)

diffuseArray = diffuseImage(I, diffConst);
[~, ~, T] = size(diffuseArray);

boundArray = getBounds(I);
[K,~] = size(boundArray);

particleArray = zeros(K,3,T);
maxParticles = zeros(T,1);
minParticles = zeros(T,1);
delta = zeros(T,1);

for t=1:T
    particleArray(:,1:2,t) = boundArray;
    for k=1:K
        particleArray(k,3,t) = diffuseArray(particleArray(k,1,t), particleArray(k,2,t), t);
    end
    
    maxParticles(t) = max(particleArray(:,3,t));
    minParticles(t) = min(particleArray(:,3,t));
    delta(t) = maxParticles(t) - minParticles(t);
end

maxDelta = max(delta);
for t=1:T
    if delta(t) == maxDelta
        bestTime = t;
        shapeNumber(:) = particleArray(:,3,bestTime);
    end
end

end