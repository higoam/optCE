% Alpine 1
test.fun = @(x) abs(x(1)*sin(x(1)) + 0.1*x(1)) + abs(x(2)*sin(x(2)) + 0.1*x(2));
test.lb = [-10 -10];
test.ub = [10 10];
test.xstar = [0,0];
test.ystar = 0; 
testset{1} = test;

% Cosine
test.fun = @(x) -0.1*(cos(5*pi.*x(1)) + cos(5*pi.*x(2))) +(x(1).*x(1) + x(2).*x(2));
test.lb = [-1 -1];
test.ub = [1 1];
test.ub = [500 500];
test.xstar = [0,0];
test.ystar = -0.2;
testset{2} = test;

% Styblinski
test.fun = @(x) (x(1).^4 -16*x(1).^2 + 5*x(1) + x(2).^4 -16*x(2).^2 + 5*x(2))/2;
test.lb = [-5 -5];
test.ub = [5 5];
test.ub = [500 500];
test.xstar = [-2.903534,-2.903534];
test.ystar = -78.332;
testset{3} = test;

% Zirilli
test.fun = @(x) 0.25*x(1).^4 -0.5*x(1).*x(1) + 0.1*x(1) + 0.5*x(2).*x(2);
test.lb = [-10 -10];
test.ub = [10 10];
test.ub = [500 500];
test.xstar = [-1.0465,0];
test.ystar = -0.3525;
testset{4} = test;

% Booth
test.fun = @(x) (x(1)+2*x(2)-7)*(x(1)+2*x(2)-7)+(2*x(1)+x(2)-5)*(2*x(1)+x(2)-5);
test.lb = [-10 -10];
test.ub = [10 10];
test.xstar = [1,3];
test.ystar = 0;
testset{5} = test;

% Himmelblau
test.fun = @(x) (x(1)^2 + x(2) -11)^2 + (x(1) + x(2)^2 -7)^2;
test.lb = [-5 -5];
test.ub = [5 5];
test.xstar = [3,2];
test.ystar = 0;
testset{6} = test;

% Leon
test.fun = @(x) 100*(x(2)-x(1)^2)^2 + (1-x(1))^2;
test.lb = [-1.2 -1.2];
test.ub = [1.2 1.2];
test.xstar = [1,1];
test.ystar = 0;
testset{7} = test;

% Zettl
test.fun = @(x) (x(1).*x(1) + x(2).*x(2) -2*x(1)).*(x(1).*x(1) + x(2).*x(2) -2*x(1)) + 0.25*x(1);
test.lb = [-5 -5];
test.ub = [10 10];
test.ub = [500 500];
test.xstar = [-0.0299,0];
test.ystar = -0.003791;
testset{8} = test;

% Sum Square 
test.fun = @(x) 1*x(1).*x(1) + 2*x(2).*x(2);
test.lb = [-10 -10];
test.ub = [10 10];
test.ub = [500 500];
test.xstar = [0,0];
test.ystar = 0;
testset{9} = test;

% Rotated Ellipse
test.fun = @(x) 7*x(1).^2 -6*sqrt(3)*x(1).*x(2) + 13*x(2).^2;
test.lb = [-500 -500];
test.ub = [500 500];
test.ub = [500 500];
test.xstar = [0,0];
test.ystar = 0;
testset{10} = test;