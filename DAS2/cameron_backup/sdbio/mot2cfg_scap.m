function error = mot2cfg_scap(path, modelname)

%% script to generate SCAPPOLY.CFG from the SIMM output file dofs.txt
% Dimitra Blana - 7/23/08

%% define parameters and open files

% name of SIMM output motion file that includes the GH force vectors
filename = 'scap_fvectors.mot';

% polynomial order
% note: it doesn't have to be the same for all muscles
poly_order = 4;

% which DOFs are ACy and GHy
if strcmp(modelname,'das3')
    DOF_ACy = 4;
    DOF_GHy = 7;
else
    disp('Error: if model is not das3, it should not include the scapulothoracic constraint');
    error = 1;
    return;
end

dofsfile = fopen([path modelname '/model/dofs.txt'], 'rt');
configfile = fopen([path modelname '/model/scappoly.cfg'], 'wt');

%% format of the bit about the momentarms in the SIMM output file dofs.txt
%
% momentarms
% <name of muscle_1> 1*x 2*x ... n*x   // where x is 1 if the muscle
%                                      // crosses that DOF, and 0 if it doesn't
% <name of muscle_2> 1*x 2*x ... n*x
% ...
% endmomentarms
% we'll use this to figure out which muscles attach on the scapula

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

%% format of SCAPPOLY.CFG
%
% <name of muscle_1>
% <1 if it attaches on the scapula, 0 if it doesn't>    if 0, skip to next muscle
% <number of DOFs it crosses> <polynomial order>
% <name of SIMM motion file>
% <columm # of xforce_vector> <DOF_a column #> <DOF_b column #> ...
% <name of SIMM motion file>
% <columm # of yforce_vector> <DOF_a column #> <DOF_b column #> ...
% <name of SIMM motion file>
% <columm # of zforce_vector> <DOF_a column #> <DOF_b column #> ...
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
% ...<xforce_vector of muscle_1> <yforce_vector of muscle_1>...
counter=1+num_dofs; % counter of force vectors

for i=1:num_mus
    fprintf(configfile,'%s\n',muscles{i}); % muscle name
    attaches_scap = whichdofs(i,DOF_ACy)+whichdofs(i,DOF_GHy); 
    %attaches_scap is 1 if the muscle crosses ACy or GHy, 0 if neither, 2
    %if both. We don't want both!
    if (attaches_scap==2), attaches_scap=0; end
    fprintf(configfile,'%i\n',attaches_scap);
    if (attaches_scap)  %continue only if attaches_scap == 1
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
