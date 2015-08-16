function theta = linReg(X, yTrain)
    theta = inverse(transpose(X) * X) * transpose(X) * yTrain;
end

f = scanf('%i', [1]);
n = scanf('%i', [1]);
XTrain = zeros(n, f);
yTrain = zeros(n, 1);
for i = 1 : n
    for j = 1 : f
        XTrain(i, j) = scanf('%g', [1]);
    end
    yTrain(i, 1) = scanf('%g', [1]);
end
XTrain = [ones(size(XTrain, 1), 1) XTrain];

theta = linReg(XTrain, yTrain);

t = scanf('%i', [1]);
XTest = zeros(t, f);
for i = 1 : t
    for j = 1 : f
        XTest(i, j) = scanf('%g', [1]);
    end
end
XTest = [ones(size(XTest, 1), 1) XTest];

yTest = XTest * theta;
for i = 1 : t
    printf('%g\n', yTest(i, 1));
end