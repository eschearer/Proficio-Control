function error = mot2cfg_GH(path, modelname)

%% script to generate GHPOLY.CFG from the SIMM output file dofs.txt
% Dimitra Blana - 5/29/07

%% define parameters and open files

% name of SIMM output motion file that includes the GH force vectors
filename = 'GH_fvectors.mot';

% polynomial order
% note: it doesn't have to be the same for all muscles
poly_order = 4;

% which DOF is GHy
if strcmp(modelname,'das2')
    DOF_GHy = 1;
elseif strcmp(modelname,'das3')
    DOF_GHy = 7;
else
    disp('Error: if model is neither das2 nor das3, it should not include GH');
    error = 1;
    return;
end

dofsfile = fopen([path modelname '/model/dofs.txt'], 'rt');
configfile = fopen([path modelname '/model/GHpoly.cfg'], 'wt');

%% format of the bit about the momentarms in the SIMM output file dofs.txt
%
% momentarms
% <name of muscle_1> 1*x 2*x ... n*x   // where x is 1 if the muscle
%                                      // crosses that DOF, and 0 if it doesn't
% <name of muscle_2> 1*x 2*x ... n*x
% ...
% endmomentarms
% we'll use this to figure out which muscles cross the GH joint

% first read the number of dofs from the line with syntax: 
% number_of_dofs #
line = fgetl(dofsfile);
while (not(strncmp(line, 'number_of_dofs', 14)) && (feof(dofsfile)==0))
    line = fgetl(dofsfile);
end
if feof(dofsfile)==0
    num_dofs = sscanf(line, '%*s%i');  
else
    disp('Error: SIMM dof file does not contain number of dofs');
    fclose('all');
    error = 1;
    return;
end

% now look for keyword momentarms
line = fgetl(dofsfile);
while (not(strcmp(line, 'momentarms')) && (feof(dofsfile)==0))
    line = fgetl(dofsfile);
end
if feof(dofsfile)==0
    line = fgetl(dofsfile);
else
    disp('Error: SIMM dof file does not contain moment arm info');
    fclose('all');
    error = 1;
    return;
end

% format string for line: 
% <name of muscle_1> 1*x 2*x ... n*x 
% skips the name, reads the numbers
formatstr = '%*s';
for i=1:num_dofs
    formatstr = [formatstr ' %i'];
end

%% format of GHPOLY.CFG
%
% <name of muscle_1>
% <1 if it crosses GH, 0 if it doesn't>    if 0, skip to next muscle
% <number of DOFs it crosses> <polynomial order>
% <name of SIMM motion file>
% <columm # of xforce_vector about GH> <DOF_a column #> <DOF_b column #> ...
% <name of SIMM motion file>
% <columm # of yforce_vector about GH> <DOF_a column #> <DOF_b column #> ...
% <name of SIMM motion file>
% <columm # of zforce_vector about GH> <DOF_a column #> <DOF_b column #> ...
% <name of muscle_2>
% ... repeat for all muscles...

num_mus = 0;
while (not(strcmp(line, 'endmomentarms')))
    num_mus=num_mus+1;
    muscles{num_mus} = sscanf(line,'%s',1);  % muscle name
    whichdofs(num_mus,:) = sscanf(line,formatstr); % 1s and 0s
    line = fgetl(dofsfile);
end

% format string for line:
% <columm # of force_vector about GH> <DOF_a column #> <DOF_b column #> ...
% num_dofs >= num_dofs_mus, but it doesn't matter
formatstr = '';
for i=1:1+num_dofs
    formatstr = [formatstr '%i '];
end

% format of data rows in the SIMM motion file: 
% <time> <value of DOF_1> <value of DOF_2> ...
% ...<xforce_vector of muscle_1 for GH> <yforce_vector of muscle_1 for GH>...
counter=1+num_dofs; % counter of force vectors

for i=1:num_mus
    fprintf(configfile,'%s\n',muscles{i}); % muscle name
    cross_GH = whichdofs(i,DOF_GHy); %cross_GH is 1 if the muscle crosses GHy, 0 otherwise
    fprintf(configfile,'%i\n',cross_GH);
    if cross_GH  %continue only if cross_GH == 1
        num_dofs_mus = sum(whichdofs(i,:)); %number of DOFs it crosses (add the 1s)
        fprintf(configfile,'%i %i\n',num_dofs_mus,poly_order);
		for j=1:3
			counter=counter+1;
			fprintf(configfile,'%s\n',filename); % name of SIMM motion file
			fprintf(configfile,formatstr,counter,1+find(whichdofs(i,:))); 
			%1+ because time is the first column
			fprintf(configfile,'\n');
		end
    end
end

%% close files

fclose(dofsfile);
fclose(configfile);
error = 0;
