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
% add quadratic features
for f1 = 1 : f
	for f2 = f1 : f
		XTrain = [XTrain XTrain(:, f1) .* XTrain(:, f2)];
	end
end
% add cubic features
for f1 = 1 : f
	for f2 = f1 : f
		for f3 = f2 : f
			XTrain = [XTrain XTrain(:, f1) .* XTrain(:, f2) .* XTrain(:, f3)];
		end
	end
end
% add constant coefficient
XTrain = [ones(size(XTrain, 1), 1) XTrain];

theta = linReg(XTrain, yTrain);

t = scanf('%i', [1]);
XTest = zeros(t, f);
for i = 1 : t
    for j = 1 : f
        XTest(i, j) = scanf('%g', [1]);
    end
end
for f1 = 1 : f
	for f2 = f1 : f
		XTest = [XTest XTest(:, f1) .* XTest(:, f2)];
	end
end
for f1 = 1 : f
	for f2 = f1 : f
		for f3 = f2 : f
			XTest = [XTest XTest(:, f1) .* XTest(:, f2) .* XTest(:, f3)];
		end
	end
end
XTest = [ones(size(XTest, 1), 1) XTest];

yTest = XTest * theta;
for i = 1 : t
    printf('%g\n', yTest(i, 1));
end