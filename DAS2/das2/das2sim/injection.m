function injection(block)
%   injection: M-file S-function that adds a signal (input 2) to specified elements
%   of the input vector (input 1)
%   the elements are specified in the parameters dialog
%
%   Dimitra Blana - September 11th 2007

setup(block);

%endfunction

%% S-function methods

function setup(block)

% Register number of ports
block.NumInputPorts  = 2;
block.NumOutputPorts = 1;
block.NumDialogPrms     = 1;
block.DialogPrmsTunable = {'Nontunable'};

% Setup port properties to be inherited or dynamic
block.SetPreCompInpPortInfoToDynamic;
block.SetPreCompOutPortInfoToDynamic;

block.InputPort(1).DatatypeID  = 0;  % double
block.InputPort(1).Complexity  = 'Real';
block.InputPort(1).Dimensions = 102;

block.InputPort(2).DatatypeID  = 0;  % double
block.InputPort(2).Complexity  = 'Real';
block.InputPort(2).Dimensions = 1;
  
block.OutputPort(1).DatatypeID  = 0; % double
block.OutputPort(1).Complexity  = 'Real';
block.OutputPort(1).Dimensions = 102;

block.SampleTimes = [-1 0];

block.RegBlockMethod('Outputs', @Outputs);

block.SetAccelRunOnTLC(false);

%endfunction
function Outputs(block)

input_act = block.InputPort(1).Data;
extra_act = block.InputPort(2).Data;
index = block.DialogPrm(1).Data;

new_act = input_act;
for i=index
    new_act(i)=input_act(i)+extra_act;
end

block.OutputPort(1).Data = new_act;

%endfunction
