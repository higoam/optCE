function [xstar,fstar] = optima(func,lb,ub,method)
numvar=length(lb);
for i=1:numvar
    x0(i)=(ub(i)-lb(i)).*rand+lb(i);
end
if method=='ga'
    A=[eye(numvar);(-1)*eye(numvar)];
    b=[ub,(-1)*lb]';
    xstar=ga(func,numvar,A,b);
end
if method=='pt'
    A=[eye(numvar);(-1)*eye(numvar)];
    b=[ub,(-1)*lb]';
    xstar=patternsearch(func,x0,A,b);
end
if method=='np'
    A=[eye(numvar);(-1)*eye(numvar)];
    b=[ub,(-1)*lb]';
    xstar=fmincon(func,x0,A,b);
end
if method=='sw'
    xstar=particleswarm(func,numvar,lb,ub);
end
if method=='sa'
    xstar=simulannealbnd(func,x0,lb,ub);
end
fstar=feval(func,xstar);
end