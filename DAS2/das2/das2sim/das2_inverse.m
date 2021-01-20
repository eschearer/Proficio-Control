function das2_inverse(block)
%   das2_inverse: M-file S-function that runs the inverse DAS2 model
%   including the load sharing problem that is solved using fmincon
%
%   Dimitra Blana - June 12th 2007


setup(block);

%endfunction

%% set constants

function [] = set_constants

global NDOF;
global NMUSELEM;
global NSTATES;

NDOF = 5;           % number of kinematic degrees of freedom
NMUSELEM = 102;     % number of muscles
NSTATES = 10;       % number of system state variables = 2*NDOF
                    % note: fiber length and muscle activation are not
                    % states for the inverse model 

%endfunction

%% functions used for the load sharing problem at the S-function output

function [] = set_opt_constraints

global MAX_ACT;
global MIN_ACT;
global ELEM_PER_MUS;
global BIND_ELEMENTS;
global BIND_MUSCLES;

ELEM_PER_MUS =  [  4,  7,  4,  3,  6,  3,  4,  4, 11,  1,  2,  4,  6,  6,  2,  5,  7,  3,  1,  1,  5,  3,  5,  5];
% if bind_elements == 1 --> all elements of that muscle have the same activation (simulation of FES)
%BIND_ELEMENTS = [  1,  1,  1,  0,  1,  0,  0,  1,  0,  1,  1,  0,  1,  1,  1,  1,  1,  0,  0,  0,  1,  1,  1,  1];
%BIND_ELEMENTS = [  1,  1,  1,  0,  1,  0,  0,  1,  1,  1,  1,  0,  1,  1,  1,  1,  1,  0,  0,  0,  1,  1,  1,  1];
% if bind_muscles ~= 0 --> the muscles with the same bind_muscles number have the same activation (simulation of nerve cuffs)
%BIND_MUSCLES =  [  0,  0,  0,  0,  3,  0,  0,  3,  0,  0,  0,  0,  0,  0,  0,  2,  0,  0,  0,  0,  0,  0,  2,  2];
%BIND_MUSCLES =  [  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  2,  0,  0,  0,  0,  0,  0,  2,  2];
%mf_fraction =   [0.5,0.5,0.5,  0,0.5,  0,  0,0.5,0,0.5,0.5,  0,0.5,0.5,0.5,0.5,0.5,  0,  0,  0,0.5,0.5,0.5,0.5];
%mf_fraction =   [1,1,1,0,1,0,0,1,0,1,1,0,1,1,1,1,1,0,0,0,1,1,1,1];
% max_act_mus =        [1,1,1,0,1,0,0,1,1,1,1,0,1,1,1,1,1,0,0,0,1,1,1,1];
% min_act_mus =   0.02*[1,1,1,0,1,0,0,1,1,1,1,0,1,1,1,1,1,0,0,0,1,1,1,1];

BIND_ELEMENTS =    [  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0];
BIND_MUSCLES =     [  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0];
max_act_mus =      [  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1];
min_act_mus = 0.02*[  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1];

MAX_ACT = ones(sum(ELEM_PER_MUS),1);
MIN_ACT = ones(sum(ELEM_PER_MUS),1);

counter=1;
for i=1:length(ELEM_PER_MUS)
    for j=1:ELEM_PER_MUS(i)
        MAX_ACT(counter) = max_act_mus(i);
        MIN_ACT(counter) = min_act_mus(i);
        if MIN_ACT(counter)>MAX_ACT(counter), MAX_ACT(counter)=MIN_ACT(counter); end
        counter = counter+1;
    end
end

%endfunction

function [bl,bu,x0,Aeq,Beq] = init_opt(q)

global MAX_ACT;
global MIN_ACT;
global ELEM_PER_MUS;
global BIND_ELEMENTS;
global BIND_MUSCLES;
global NMUSELEM;

[bl,bu,x0,Aeq,Beq] = sdbiomex2(1,q,NMUSELEM,ELEM_PER_MUS,BIND_ELEMENTS,BIND_MUSCLES,MAX_ACT,MIN_ACT);

%endfunction

function f = objfun(x)

global MAX_ACT;
global MIN_ACT;

f = sdbiomex2(2,x,MAX_ACT,MIN_ACT);
%endfunction

function [c,ceq] = constr(x)
c = sdbiomex2(3,x);
%c=0;
ceq=0;
%endfunction

function exc = calc_exc(x,opt_success)
exc = sdbiomex2(4,x,opt_success);
%endfunction

function exc = load_sharing(q)

% determine the muscle activations
[bl,bu,x0,Aeq,Beq] = init_opt(q);
%save opt_vars bl bu x0 Aeq Beq;
options = optimset('Display','Off','GradObj','off','GradConstr','off','MaxFunEvals',50000,...
    'MaxIter',500,'LargeScale','Off');
%    'MaxIter',500,'TolCon',0.001,'TolX',0.000001,'LargeScale','Off');
%[x,feval,exitflag] = fmincon(@objfun,x0,[],[],Aeq,Beq,bl,bu,@constr,options);
[x,feval,exitflag,output] = fmincon(@objfun,x0,[],[],Aeq,Beq,bl,bu,@constr,options);
save opt_vars bl bu x0 Aeq Beq output;
if (exitflag>0)
    opt_success=1;
else opt_success=0;
end
exitflag
exc = calc_exc(x,opt_success);

%endfunction

%% functions for model initialization

function [] = SDBIO_init(filename)
sdbiomex2(5,filename);
%endfunction


function [] = SDBIO_initcond(q,qdot,ref_angle,ref_vel,ref_acc)
global MIN_ACT;
t = 0;
sdbiomex2(6,t,q,qdot,ref_angle,ref_vel,ref_acc,MIN_ACT);
%endfunction

%% functions for Derivatives part of the S-function

function statedot = deriv_inverse(t,state,ref_angle,ref_vel,ref_acc,act_angle,act_vel)
statedot = sdbiomex2(7,t,state,ref_angle,ref_vel,ref_acc,act_angle,act_vel);
%endfunction

function qdot = das2ode_inv(q,qdes,qdotdes,qddotdes,qactual,qdotactual)
% computes the derivatives of the state variables
%
% q             input: state (angles, angvels)
% qdes          input: desired angles
% qdotdes		input: desired velocities
% qddotdes		input: desired accelerations
% qactual		input: actual angles
% qdotactual	input: actual velocities
% qdot          output: derivative of x

t=0;

% copy and rearrange state variables from x[] into state[]
% straight copy for angles and angular velocities */
state = q;

% get state derivatives
statedot = deriv_inverse(t, state, qdes, qdotdes, qddotdes, qactual, qdotactual);

% copy state derivatives back to qdot
qdot = statedot;

%endfunction

%% functions at simulation termination

function [] = SDBIO_terminate
sdbiomex2(8);
%endfunction

%% S-function methods

function setup(block)
global NDOF;
global NMUSELEM;
global NSTATES;

set_constants;
set_opt_constraints;

% Register number of ports
block.NumInputPorts  = 5;
block.NumOutputPorts = 2;

% Setup port properties to be inherited or dynamic
block.SetPreCompInpPortInfoToDynamic;
block.SetPreCompOutPortInfoToDynamic;

% Override input port properties
block.InputPort(1).DatatypeID  = 0;  % double
block.InputPort(1).Complexity  = 'Real';
block.InputPort(1).Dimensions = NDOF;
block.InputPort(1).SampleTime = [0.0,0.0];

block.InputPort(2).DatatypeID  = 0;  % double
block.InputPort(2).Complexity  = 'Real';
block.InputPort(2).Dimensions = NDOF;
block.InputPort(2).SampleTime = [0.0,0.0];

block.InputPort(3).DatatypeID  = 0;  % double
block.InputPort(3).Complexity  = 'Real';
block.InputPort(3).Dimensions = NDOF;
block.InputPort(3).SampleTime = [0.0,0.0];

block.InputPort(4).DatatypeID  = 0;  % double
block.InputPort(4).Complexity  = 'Real';
block.InputPort(4).Dimensions = NDOF;
block.InputPort(4).SampleTime = [0.0,0.0];

block.InputPort(5).DatatypeID  = 0;  % double
block.InputPort(5).Complexity  = 'Real';
block.InputPort(5).Dimensions = NDOF;
block.InputPort(5).SampleTime = [0.0,0.0];

% Override output port properties
block.OutputPort(1).DatatypeID  = 0; % double
block.OutputPort(1).Complexity  = 'Real';
block.OutputPort(1).Dimensions = NMUSELEM;
block.OutputPort(1).SampleTime = [0.004,0.0];
%block.OutputPort(1).SampleTime = [0.0,0.0];

block.OutputPort(2).DatatypeID  = 0; % double
block.OutputPort(2).Complexity  = 'Real';
block.OutputPort(2).Dimensions = NDOF;
block.OutputPort(2).SampleTime = [0.0,0.0];

% Setup states
block.NumContStates = NSTATES;

% Register sample times
%  [0 offset]            : Continuous sample time
%  [positive_num offset] : Discrete sample time
%
%  [-1, 0]               : Port-based sample time
%  [-2, 0]               : Variable sample time
% block.SampleTimes = [0, 0];

% Specify if Accelerator should use TLC or call back into
% M-file
block.SetAccelRunOnTLC(false);

filename = '../model/model';
SDBIO_init(filename);

block.RegBlockMethod('SetInputPortSamplingMode', @SetInpPortFrameData);
block.RegBlockMethod('SetInputPortSampleTime', @SetInpPortSampleTime);
block.RegBlockMethod('SetOutputPortSampleTime', @SetOutPortSampleTime);
block.RegBlockMethod('InitializeConditions', @InitializeConditions);
block.RegBlockMethod('Start', @Start);
block.RegBlockMethod('Outputs', @Outputs);
block.RegBlockMethod('Derivatives', @Derivatives);
block.RegBlockMethod('Terminate', @Terminate);

%endfunction

function SetInpPortFrameData(block, idx, fd)

block.InputPort(idx).SamplingMode = fd;
block.OutputPort(1).SamplingMode  = 'sample';
block.OutputPort(2).SamplingMode  = 'sample';

%endfunction

function InitializeConditions(block)

% Initialize states
%init_angles = [0.2;0.5;-0.2;0;2.96];
init_angles = [7.7740757e-001;  6.8587315e-001; -4.9240670e-001;  1.4087543e+000;  8.6671694e-001];
%init_angles = [0.2; 0.5; -0.2; 0.5; 1.2];
init_vel = [0;0;0;0;0];
block.ContStates.Data =	[init_angles; init_vel];
ref_angle = block.InputPort(1).Data;
ref_vel = block.InputPort(2).Data;
ref_acc = block.InputPort(3).Data;
SDBIO_initcond(init_angles,init_vel,ref_angle,ref_vel,ref_acc);

%endfunction

function Start(block)

%endfunction

function Outputs(block)
global NDOF;

q = block.ContStates.Data(1:NDOF);
if (block.OutputPort(1).IsSampleHit)
    block.OutputPort(1).Data = load_sharing(q);
%    block.OutputPort(1).Data = ones(102,1);
end
block.OutputPort(2).Data = q;

%endfunction

function Derivatives(block)

% q             state: angles, angvels, Lce, actiation
% qdes          input: desired angles
% qdotdes		input: desired velocities
% qddotdes		input: desired accelerations
% qactual		input: actual angles
% qdotactual	input: actual velocities

q = block.ContStates.Data;
qdes = block.InputPort(1).Data;
qdotdes = block.InputPort(2).Data;
qddotdes = block.InputPort(3).Data;
qactual = block.InputPort(4).Data;
qdotactual = block.InputPort(5).Data;

block.Derivatives.Data = das2ode_inv(q,qdes,qdotdes,qddotdes,qactual,qdotactual);

%endfunction

function Terminate(block)
SDBIO_terminate;
%endfunction

