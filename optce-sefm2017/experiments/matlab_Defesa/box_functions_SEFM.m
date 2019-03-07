%  1 - Adjiman
test.fun = @(x) cos(x(1)).*sin(x(2)) - (x(1)./(x(2).*x(2)+1));
test.lb = [-1 -1];
test.ub = [2 1];
test.ub = [500 500];
test.xstar = [2,0.10578];
test.ystar = -2.02181;
testset{1} = test;

%  2 - Alpine 1
test.fun = @(x) abs(x(1)*sin(x(1)) + 0.1*x(1)) + abs(x(2)*sin(x(2)) + 0.1*x(2));
test.lb = [-10 -10];
test.ub = [10 10];
test.xstar = [0,0];
test.ystar = 0; 
testset{2} = test;

%  3 - Bohachevsky 1
test.fun = @(x) x(1).^2 + 2*x(2).^2 -0.3*cos(3*pi.*x(1)) -0.4*cos(4*pi.*x(1)) + 0.7;
test.lb = [-50 -50];
test.ub = [50 50];
test.xstar = [0,0];
test.ystar = 0; 
testset{3} = test;

%  4 - Bohachevsky 3
test.fun = @(x) x(1).^2 + 2*x(2).^2 -0.3*cos(3*pi.*x(1) +4*pi.*x(2)) +0.3;
test.lb = [-50 -50];
test.ub = [50 50];
test.xstar = [0,0];
test.ystar = 0; 
testset{4} = test;

%  5 - Branin RCOS 01
test.fun = @(x) (x(2) -((5.1*x(1).*x(1))/(4*pi*pi))  +((5*x(1))/pi)    -6).^2 +10*(1 -(1/(8*pi)))*cos( x(1) + 10 );
test.lb = [-5 0];
test.ub = [10 15];
test.xstar = [pi,12.275];
test.ystar = 0.39788; 
testset{5} = test;

%  6 - Camel Six
test.fun = @(x) (4 -2.1*x(1).^2 + (x(1).^4)/3 ).*x(1).^2 + x(1).*x(2) + (-4 +4*x(2).^2).*x(2).^2; 
test.lb = [-3 -2];
test.ub = [3 2];
test.xstar = [0.0898,-0.7126];
test.ystar = -1.0316; 
testset{6} = test;

%  7 - Camel Three
test.fun = @(x) 2*x(1).*x(1) -1.05*x(1).^4 + ((x(1).^6)/6) + x(1).*x(2) + x(2).*x(2);
test.lb = [-5 -5];
test.ub = [5 5];
test.xstar = [0,0];
test.ystar = 0; 
testset{7} = test;

%  8 - Cosine
test.fun = @(x) -0.1*(cos(5*pi.*x(1)) + cos(5*pi.*x(2))) +(x(1).*x(1) + x(2).*x(2));
test.lb = [-1 -1];
test.ub = [1 1];
test.ub = [500 500];
test.xstar = [0,0];
test.ystar = -0.2;
testset{8} = test;

% 9 - Egg Crate
test.fun = @(x) x(1)*x(1) + x(2)*x(2) + 25*(sin(x(1))*sin(x(1)) + sin(x(2))*sin(x(2)));
test.lb = [-5 -5];
test.ub = [5 5];
test.xstar = [0,0];
test.ystar = 0;
testset{9} = test;

% 10 - Engvall
test.fun = @(x) x(1).^4 + x(2).^4 + 2*x(1).^2*x(2).^2 -4*X(1) + 3;
test.lb = [-10 -10];
test.ub = [10 10];
test.xstar = [1,0];
test.ystar = 0;
testset{10} = test;

% 11 - Godstein Price
test.fun = @(x) (1 + ((x(1) + x(2) + 1).^2) * (19 - (14 * x(1)) + (3 * (x(1) .^2)) - 14*x(2) + (6 .* x(1).*x(2)) + (3 * (x(2).^2)))).*(30 + ((2 * x(1) - 3 * x(2)).^2) .* (18 - 32 * x(1) + 12 * (x(1) .^2) + 48 * x(2) - (36 .* x(1).*x(2)) + (27 * (x(2).^2))) );
test.lb = [-2 -2];
test.ub = [2 2];
test.xstar = [0,-1];
test.ystar = 3;
testset{11} = test;

% 12 - MC Cormick
test.fun = @(x) sin(x(1) + x(2)) + (x(1) - x(2)).^2 + -1.5*x(1) + 2.5*x(2) + 1;
test.lb = [-2 -3];
test.ub = [4 4];
test.xstar = [-0.547,-1.547];
test.ystar = -1.913;
testset{12} = test;

% 13 - Rotated Ellipse 01
test.fun = @(x) 7*x(1).^2 -6*sqrt(3)*x(1).*x(2) + 13*x(2).^2;
test.lb = [-500 -500];
test.ub = [500 500];
test.xstar = [0,0];
test.ystar = 0;
testset{13} = test;

% 14 - Scahffer 1
test.fun = @(x) 0.5 + ( sin( (x(1).^2 + x(2).^2).^2 ).^2 -0.5 )/( 1 + 0.001*(x(1).^2 + x(2).^2).^2 );
test.lb = [-100 -100];
test.ub = [100 100];
test.xstar = [0,0];
test.ystar = 0;
testset{14} = test;

% 15 - Styblinski Tang
test.fun = @(x) (x(1).^4 -16*x(1).^2 + 5*x(1) + x(2).^4 -16*x(2).^2 + 5*x(2))/2;
test.lb = [-5 -5];
test.ub = [5 5];
test.xstar = [-2.903534,-2.903534];
test.ystar = -78.332;
testset{15} = test;

% 16 - Trecanni
test.fun = @(x) x(1).^4 -4*x(1).^3 +4*x(1) + x(2).^2;
test.lb = [-5 -5];
test.ub = [5 5];
test.xstar = [0,0];
test.ystar = 0;
testset{16} = test;

% 17 - Tsoulos
test.fun = @(x) x(1).^2 + x(2).^2 -cos(18*x(1)) -cos(18*x(2));
test.lb = [-1 -1];
test.ub = [1 1];
test.xstar = [0,0];
test.ystar = -2;
testset{17} = test;

% 18 - Ursem 1
test.fun = @(x) -sin(2*x(1) - 0.5*pi) - 3*cos(x(2)) -0.5*x(1);
test.lb = [-2.5 -2];
test.ub = [3 2];
test.ub = [500 500];
test.xstar = [1.697136,0];
test.ystar = -4.8168;
testset{18} = test;

% 19 - Wayburn Seader 2
test.fun = @(x) (1.613 -4*(x(1) -0.3125).^2 -4*(x(2) -1.625).^2).^2 + (x(2) -1).^2
test.lb = [-100 -100];
test.ub = [100 100];
test.xstar = [0.200,1];
test.ystar = 0;
testset{19} = test;

% 20 - Zirilli
test.fun = @(x) 0.25*x(1).^4 -0.5*x(1).*x(1) + 0.1*x(1) + 0.5*x(2).*x(2);
test.lb = [-10 -10];
test.ub = [10 10];
test.ub = [500 500];
test.xstar = [-1.0465,0];
test.ystar = -0.3525;
testset{20} = test;

% 21 - Booth
test.fun = @(x) (x(1)+2*x(2)-7)*(x(1)+2*x(2)-7)+(2*x(1)+x(2)-5)*(2*x(1)+x(2)-5);
test.lb = [-10 -10];
test.ub = [10 10];
test.xstar = [1,3];
test.ystar = 0;
testset{21} = test;

% 22 - Dixon & Price
test.fun = @(x) (x(1) -1)*(x(1) -1) + 2*(2*x(2)*x(2) - x(2)-1)*(2*x(2)*x(2) - x(2)-1);
test.lb = [-10 -10];
test.ub = [10 10];
test.xstar = [1,0.7];
test.ystar = 0;
testset{22} = test;

% 23 - Himmelblau
test.fun = @(x) (x(1)^2 + x(2) -11)^2 + (x(1) + x(2)^2 -7)^2;
test.lb = [-5 -5];
test.ub = [5 5];
test.xstar = [3,2];
test.ystar = 0;
testset{23} = test;

% 24 - Leon
test.fun = @(x) 100*(x(2)-x(1)^2)^2 + (1-x(1))^2;
test.lb = [-1.2 -1.2];
test.ub = [1.2 1.2];
test.xstar = [1,1];
test.ystar = 0;
testset{24} = test;

% 25 - Price 1
test.fun = @(x) (abs(x(1)) -5).^2 + (abs(x(2))  -5).^2;
test.lb = [-10 -10];
test.ub = [10 10];
test.xstar = [-5,-5];
test.ystar = 0;
testset{25} = test;

% 26 - Price 4
test.fun = @(x) (2*x(1).^3.*x(2) - x(2).^3).^2 + (6*x(1) -x(2).^2 + x(2)).^2;
test.lb = [-500 -500];
test.ub = [500 500];
test.xstar = [0,0];
test.ystar = 0;
testset{26} = test;

% 27 - Rosenbrock
test.fun = @(x) 100*(x(2) -x(1).*x(1)).^2 + (x(1) -1).^2;
test.lb = [-5 -5];
test.ub = [10 10];
test.xstar = [1,1];
test.ystar = 0;
testset{27} = test;

% 28 - Powell Sum
test.fun = @(x) abs(x(1))^2 + abs(x(2))^3;
test.lb = [-1 -1];
test.ub = [1 1];
test.xstar = [0,0];
test.ystar = 0;
testset{28} = test;

% 29 - Schuwefel 2.25
test.fun = @(x) (x(1) -1)^2 + (x(1) -x(1).*x(1))^2 + (x(2) -1)^2 + (x(1) -x(2).*x(2))^2;
test.lb = [-10 -10];
test.ub = [10 10];
test.xstar = [1,1];
test.ystar = 0;
testset{29} = test;

% 30 - Wayburn Seader 1
test.fun = @(x) (x(1).^6 + x(2).^4 -17)^2 + (2*x(1) + x(2) -4)^2;
test.lb = [-100 -100];
test.ub = [100 100];
test.xstar = [1,2];
test.ystar = 0;
testset{30} = test;

% 31 - Chung Reynolds
test.fun = @(x) (x(1).*x(1) + x(2).*x(2)).^2;
test.lb = [-100 -100];
test.ub = [100 100];
test.xstar = [0,0];
test.ystar = 0;
testset{31} = test;

% 32 - Cube
test.fun = @(x) 100*(x(2)-x(1)^3)^2 + (1-x(1))^2;
test.lb = [-10 -10];
test.ub = [10 10];
test.xstar = [1,1];
test.ystar = 0;
testset{32} = test;

% 33 - Matyas
test.fun = @(x) 0.26*(x(1).^2 + x(2).^2) -0.48*x(1).*x(2);
test.lb = [-10 -10];
test.ub = [10 10];
test.ub = [500 500];
test.xstar = [0,0];
test.ystar = 0;
testset{33} = test;

% 34 - Rotated Ellipse 02
test.fun = @(x)  x(1).*x(1) -x(1).*x(2) +x(2).*x(2);
test.lb = [-500 -500];
test.ub = [500 500];
test.xstar = [0,0];
test.ystar = 0;
testset{34} = test;

% 35 - Schumer
test.fun = @(x) x(1).^4 + x(2).^4;
test.lb = [-10 -10];
test.ub = [10 10];
test.xstar = [0,0];
test.ystar = 0;
testset{35} = test;

% 36 - Schwefel 2.20
test.fun = @(x) abs(x(1)) + abs(x(2));
test.lb = [-100 -100];
test.ub = [100 100];
test.xstar = [0,0];
test.ystar = 0;
testset{36} = test;

% 37 - Sphere 
test.fun = @(x) x(1).*x(1) + x(2).*x(2);
test.lb = [0 0];
test.ub = [500 500];
test.xstar = [0,0];
test.ystar = 0;
test.ub = [10 10];
testset{37} = test;

% 38 - Sum Square 
test.fun = @(x) 1*x(1).*x(1) + 2*x(2).*x(2);
test.lb = [-10 -10];
test.ub = [10 10];
test.xstar = [0,0];
test.ystar = 0;
testset{38} = test;

% 39 - Zakharov
test.fun = @(x) x(1).*x(1) + x(2).*x(2) + (0.5*1*x(1) + 0.5*2*x(2))^2 + (0.5*1*x(1) + 0.5*2*x(2))^4;
test.lb = [-5 -5];
test.ub = [10 10];
test.xstar = [0,0];
test.ystar = 0;
testset{39} = test;

% 40 - Zettl
test.fun = @(x) (x(1).*x(1) + x(2).*x(2) -2*x(1)).*(x(1).*x(1) + x(2).*x(2) -2*x(1)) + 0.25*x(1);
test.lb = [-5 -5];
test.ub = [10 10];
test.xstar = [-0.0299,0];
test.ystar = -0.003791;
testset{40} = test;



