clc; clear all;

box_functions_SEFM;
numfunc=size(testset,2);
n=2;    % Number of times of execution

for j=1:n
    
    for i=1:numfunc
        display('GA optimization...')
        display(strcat('Testcase -',num2str(i),'/',num2str(numfunc)));
        testcase=testset{i};
        tic
        [x,y]=optima(testcase.fun,testcase.lb,testcase.ub,'ga');
        time=toc;
        result.xstar=x;
        result.ystar=y;
        result.time=time;
        geneticalgorithmresult{i,j}=result;
    end
    
    for i=1:numfunc
        display('Particle Swarm optimization...')
        display(strcat('Testcase -',num2str(i),'/',num2str(numfunc)))
        testcase=testset{i};
        tic
        [x,y]=optima(testcase.fun,testcase.lb,testcase.ub,'sw');
        time=toc;
        result.xstar=x;
        result.ystar=y;
        result.time=time;
        particleswarmresult{i,j}=result;
    end
    
    for i=1:numfunc
        display('Pattern Search optimization...')
        display(strcat('Testcase -',num2str(i),'/',num2str(numfunc)))
        testcase=testset{i};
        tic
        [x,y]=optima(testcase.fun,testcase.lb,testcase.ub,'pt');
        time=toc;
        result.xstar=x;
        result.ystar=y;
        result.time=time;
        patternsearchresult{i,j}=result;
    end
    
    for i=1:numfunc
        display('Simulated Annealing optimization...')
        display(strcat('Testcase -',num2str(i),'/',num2str(numfunc)))
        testcase=testset{i};
        tic
        [x,y]=optima(testcase.fun,testcase.lb,testcase.ub,'sa');
        time=toc;
        result.xstar=x;
        result.ystar=y;
        result.time=time;
        simulatedannealingresult{i,j}=result;
    end
    
    for i=1:numfunc
        display('Nonlinear Programming optimization...')
        display(strcat('Testcase -',num2str(i),'/',num2str(numfunc)))
        testcase=testset{i};
        tic
        [x,y]=optima(testcase.fun,testcase.lb,testcase.ub,'np');
        time=toc;
        result.xstar=x;
        result.ystar=y;
        result.time=time;
        nonlinearprogrammingresult{i,j}=result;
    end
    
end

%%
totaltime=zeros(numfunc,1);
acounter=zeros(numfunc,1);

%% Genetic Algorithm

datatest=geneticalgorithmresult;

for i=1:numfunc
    for j=1:n
        totaltime(i)=totaltime(i)+datatest{i,j}.time;
        if ((abs(testset{i}.xstar(1)-datatest{i,j}.xstar(1))<0.01) && ...
            (abs(testset{i}.xstar(2)-datatest{i,j}.xstar(2))<0.01) && ...
            (abs(testset{i}.ystar-datatest{i,j}.ystar)<0.001))
            acounter(i)=acounter(i)+1;
        end
    end
    meantime(i)=totaltime(i)/n;
    arate(i)=acounter(i)/n;
end

gafinal.totaltime=totaltime;
gafinal.meantime=meantime;
gafinal.arate=arate;

%% Particle Swarm

totaltime=zeros(numfunc,1);
acounter=zeros(numfunc,1);
datatest=particleswarmresult;

for i=1:numfunc
    for j=1:n
        totaltime(i)=totaltime(i)+datatest{i,j}.time;        
        if ((abs(testset{i}.xstar(1)-datatest{i,j}.xstar(1))<0.01) && ...
            (abs(testset{i}.xstar(2)-datatest{i,j}.xstar(2))<0.01) && ...
            (abs(testset{i}.ystar-datatest{i,j}.ystar)<0.001))
        acounter(i)=acounter(i)+1;
        end 
    end
    meantime(i)=totaltime(i)/n;
    arate(i)=acounter(i)/n;
end

swarmfinal.totaltime=totaltime;
swarmfinal.meantime=meantime;
swarmfinal.arate=arate;

%% Pattern Search

totaltime=zeros(numfunc,1);
acounter=zeros(numfunc,1);
datatest=patternsearchresult;

for i=1:numfunc
    for j=1:n
        totaltime(i)=totaltime(i)+datatest{i,j}.time;        
        if ((abs(testset{i}.xstar(1)-datatest{i,j}.xstar(1))<0.01) && ...
            (abs(testset{i}.xstar(2)-datatest{i,j}.xstar(2))<0.01) && ...
            (abs(testset{i}.ystar-datatest{i,j}.ystar)<0.001))
        acounter(i)=acounter(i)+1;
        end  
    end
    meantime(i)=totaltime(i)/n;
    arate(i)=acounter(i)/n;
end

patternfinal.totaltime=totaltime;
patternfinal.meantime=meantime;
patternfinal.arate=arate;

%% Simmulated Annealing

totaltime=zeros(numfunc,1);
acounter=zeros(numfunc,1);
datatest=simulatedannealingresult;

for i=1:numfunc
    for j=1:n
        totaltime(i)=totaltime(i)+datatest{i,j}.time;
        if ((abs(testset{i}.xstar(1)-datatest{i,j}.xstar(1))<0.01) && ...
            (abs(testset{i}.xstar(2)-datatest{i,j}.xstar(2))<0.01) && ...
            (abs(testset{i}.ystar-datatest{i,j}.ystar)<0.001))
            acounter(i)=acounter(i)+1;
        end
    end
    meantime(i)=totaltime(i)/n;
    arate(i)=acounter(i)/n;
end

simulatedfinal.totaltime=totaltime;
simulatedfinal.meantime=meantime;
simulatedfinal.arate=arate;

%% Non-Linear Programming

totaltime=zeros(numfunc,1);
acounter=zeros(numfunc,1);
datatest=nonlinearprogrammingresult;

for i=1:numfunc
    for j=1:n
        totaltime(i)=totaltime(i)+datatest{i,j}.time;        
        if ((abs(testset{i}.xstar(1)-datatest{i,j}.xstar(1))<0.01) && ...
            (abs(testset{i}.xstar(2)-datatest{i,j}.xstar(2))<0.01) && ...
            (abs(testset{i}.ystar-datatest{i,j}.ystar)<0.001))
            acounter(i)=acounter(i)+1;
         end
    end
    meantime(i)=totaltime(i)/n;
    arate(i)=acounter(i)/n;
end

npfinal.totaltime=totaltime;
npfinal.meantime=meantime;
npfinal.arate=arate;

%% Results
clc
display('Hit Rate')
result = [gafinal.arate' swarmfinal.arate' patternfinal.arate' simulatedfinal.arate' npfinal.arate']
display('Average Time')
resultime = [gafinal.meantime' swarmfinal.meantime' patternfinal.meantime' simulatedfinal.meantime' npfinal.meantime']
