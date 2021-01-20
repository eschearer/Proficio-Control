function error = makebio(path, modelname)

%% Script to generate .bio file for sdbio
% using input from SIMM input .msl file, SIMM output file dofs.txt,
% and poly_results.txt file from pathpoly.

%% Define some constants

width = 0.56;

%% Build filenames and open files

musclefile = fopen([path modelname '/model/',modelname,'.msl'], 'rt');
dofsfile = fopen([path modelname '/model/dofs.txt'],'rt');
polyfile = fopen([path modelname '/model/poly_results.txt'], 'rt');
if strcmp(modelname,'das2')||strcmp(modelname,'das3')
    GHpolyfile = fopen([path modelname '/model/poly_results_GH.txt'], 'rt');
end
if strcmp(modelname,'das3')
    scappolyfile = fopen([path modelname '/model/poly_results_scap.txt'], 'rt');
end
% the bio file will be called "model.bio" for all models
biofile = fopen([path modelname '/model/model.bio'], 'wt');

%% Add comment in the top of bio file with the description of the file
fprintf(biofile, '# model.bio\n');
fprintf(biofile, '# file with joint and muscle information created by simm2bio.m, for use by SDBIO\n\n');

% and the verbose level
fprintf(biofile, 'verbose_level 0\n\n');

%% Write joints part of .bio file with data from SIMM-generated dofs.txt file
% dofs information starts at line: "dofs"
tline1 = fgetl(dofsfile);
while (not(strcmp(tline1, 'dofs')))
    tline1 = fgetl(dofsfile);
end

tline1 = fgetl(dofsfile);
if strncmp(tline1, 'number_of_dofs', 14)
    num_dofs = sscanf(tline1, '%*s%i');
end

dof_names = cell(num_dofs,1);
for i=1:num_dofs
    dof_names{i} = fscanf(dofsfile,'%s',1);
    distal_body = fscanf(dofsfile,'%s',1);
    limits = fscanf(dofsfile,'%f',2);
    fprintf(biofile, 'joint %s\n', dof_names{i});
    fprintf(biofile, '   distal_body %s\n', distal_body);
    fprintf(biofile, '   limits %f %f\n', limits(1), limits(2));
    fprintf(biofile, '   end\n\n');
end

% go to next section of dofs.txt, that has the syntax:
% <muscle name> <DOF1> <DOF2> ....
% where in <DOF>: 1 if the muscle crosses it, 0 if it doesn't
% this starts after the keyword 'momentarms'
tline1 = fgetl(dofsfile);
while (not(strcmp(tline1, 'momentarms')))
    tline1 = fgetl(dofsfile);
end

% format string for line:
% <name of muscle_1> 1*x 2*x ... n*x
% skips the name, reads the numbers
formatstr = '%*s';
for i=1:num_dofs
    formatstr = [formatstr ' %i'];
end

%% Write generic muscle data to .bio file
fprintf(biofile,'muscle default\n');
fprintf(biofile,'   a 0.25\n');
fprintf(biofile,'   vmrel 10\n');
fprintf(biofile,'   umax 0.04\n');
fprintf(biofile,'   fecmax 1.5\n');
fprintf(biofile,'   krel 1.0\n');
fprintf(biofile,'   slopfac 2.0\n');
fprintf(biofile,'   PEEslack 1.0\n');

%% Get muscle data from source files and write it to .bio file

while feof(musclefile) == 0

    tline1 = fgetl(musclefile);
    if strncmp(tline1, 'beginmuscle', 11)
        musname = sscanf(tline1, '%*s%s'); % the asterisk makes it skip this string!
        if not(strcmp(musname, 'defaultmuscle'))
            fprintf(biofile, '\n%s%s\n', 'muscle ', musname);
            % Start data from muscle file
            while not(strcmp(tline1, 'endmuscle'))
                tline1 = fgetl(musclefile);
                if strncmp(tline1, 'max_force', 9)
                    fmax = sscanf(tline1, '%*s%f');
                    fprintf(biofile, '%s%8.2f\n', ' fmax', fmax);
                end
                if strncmp(tline1, 'optimal_fiber_length', 20)
                    lceopt = sscanf(tline1, '%*s%f');
                    fprintf(biofile, '%s%10.5f', ' lceopt', lceopt);
                end
                if strncmp(tline1, 'pennation_angle', 15)
                    pennopt = sscanf(tline1, '%*s%f');
                    fprintf(biofile, '%s%10.5f', ' pennopt', pennopt);
                    fprintf(biofile, '%s%10.5f\n', ' width ', width);
                end
                if strncmp(tline1, 'tendon_slack_length', 19)
                    lslack = sscanf(tline1, '%*s%f');
                    fprintf(biofile, '%s%10.5f', ' lslack ', lslack);
                end
                if strncmp(tline1, 'activation1', 11)
                    act1 = 1/sscanf(tline1, '%*s%f');
                end
                if strncmp(tline1, 'activation2', 11)
                    act2 = 1/sscanf(tline1, '%*s%f');
                    fprintf(biofile, '%s%10.5f%10.5f\n', ' time_constants ', act1, act2);
                end
            end
            % End data from muscle file

            % Start of dofs section
            tline1 = fgetl(dofsfile);
            newmusname = sscanf(tline1,'%s',1);
            if (not(strcmp(newmusname,musname)))
                strshow = ['Error: dof file missing muscle ',musname];
                disp(strshow); %muscle missing from dofsfile
                fclose('all');
                error = 1;
                return;
            end
            whichdofs = sscanf(tline1,formatstr); % 1s and 0s

            fprintf(biofile, '%s\n', ' geometry polynomial');
            fprintf(biofile, '%s\n', ' dofs');
            for i=1:num_dofs
                if (whichdofs(i))
                    fprintf(biofile, '     %s\n', dof_names{i});
                end
            end
            fprintf(biofile, '%s\n', '     end');
            % End of dofs section

            % Start data from path poly file
            % looking for the same muscle we just read from the muscle file
            tline2 = fgetl(polyfile);
            while (not(strcmp(tline2, musname)) && (feof(polyfile)==0))
                tline2 = fgetl(polyfile);
            end
            if feof(polyfile)==0
                tline2 = fgetl(polyfile);
            else
                disp('Error: polynomial file missing muscle') %muscle missing from polyfile
                fclose('all');
                error = 1;
                return;
            end
            % if there are comments between the muscle name and the
            % 'parameters' line, ignore them
            while (strncmp(tline2, '#', 1))
                tline2 = fgetl(polyfile);
            end
            if strncmp(tline2, 'parameters', 10)
                nparam = sscanf(tline2, '%*s%f');
                fprintf(biofile, '%s%5i\n', ' parameters', nparam);
            else
                disp('Error: polynomial file missing parameter number') %muscle missing from polyfile
                fclose('all');
                error = 1;
                return;
            end
            % if there are comments between the 'parameters' line and the
            % list of coefficients, ignore them
            tline2 = fgetl(polyfile);
            while (strncmp(tline2, '#', 1))
                tline2 = fgetl(polyfile);
            end
            fprintf(biofile, '%s\n', tline2);
            for i = 1:nparam-1,
                tline2 = fgetl(polyfile);
                fprintf(biofile, '%s\n', tline2);
            end
            % End data from path poly file

            % Start data from GH poly file (only for models das2 and das3)
            if ~strcmp(modelname,'das2') && ~strcmp(modelname,'das3')
                fprintf(biofile, '%s\n', 'end');
                continue;
            end
            % looking for the same muscle we just read from the muscle file
            fseek(GHpolyfile, 0, 'bof'); % reposition the file identifier to the beginning of the GHpolyfile
            while (not(strcmp(tline2, musname)) && (feof(GHpolyfile)==0))
                tline2 = fgetl(GHpolyfile);
            end
            if ~feof(GHpolyfile) % if the muscle is not there, it's not crossing GH
                fprintf(biofile, 'GH_force_vectors\n');
                for i=1:3
                    if feof(GHpolyfile)==0
                        tline2 = fgetl(GHpolyfile);
                    else
                        disp('Error: GH polynomial file missing force direction') %muscle missing from GHpolyfile
                        fclose('all');
                        error = 1;
                        return;
                    end
                    % if there are comments between the muscle name and the
                    % 'parameters' line, ignore them
                    while (strncmp(tline2, '#', 1))
                        tline2 = fgetl(GHpolyfile);
                    end
                    if strncmp(tline2, 'parameters', 10)
                        nparam = sscanf(tline2, '%*s%f');
                        fprintf(biofile, '%s%5i\n', 'parameters', nparam);
                    else
                        disp('Error: polynomial file missing parameter number') %muscle missing from polyfile
                        fclose('all');
                        error = 1;
                        return;
                    end
                    % if there are comments between the 'parameters' line and the
                    % list of coefficients, ignore them
                    tline2 = fgetl(GHpolyfile);
                    while (strncmp(tline2, '#', 1))
                        tline2 = fgetl(GHpolyfile);
                    end
                    fprintf(biofile, '%s\n', tline2);
                    for ii = 1:nparam-1,
                        tline2 = fgetl(GHpolyfile);
                        fprintf(biofile, '%s\n', tline2);
                    end
                end
            end
            % End data from GH path poly file

            % Start data from scapula poly file (only for model das3)
            if ~strcmp(modelname,'das3')
                fprintf(biofile, '%s\n', 'end');
                continue;
            end
            % looking for the same muscle we just read from the muscle file
            fseek(scappolyfile, 0, 'bof'); % reposition the file identifier to the beginning of the scappolyfile
            while (not(strcmp(tline2, musname)) && (feof(scappolyfile)==0))
                tline2 = fgetl(scappolyfile);
            end
            if ~feof(scappolyfile) % if the muscle is not there, it's not attached to the scapula
                fprintf(biofile, 'scapula_force_vectors\n');
                for i=1:3
                    if feof(scappolyfile)==0
                        tline2 = fgetl(scappolyfile);
                    else
                        disp('Error: scapula polynomial file missing force direction') %muscle missing from scappolyfile
                        fclose('all');
                        error = 1;
                        return;
                    end
                    % if there are comments between the muscle name and the
                    % 'parameters' line, ignore them
                    while (strncmp(tline2, '#', 1))
                        tline2 = fgetl(scappolyfile);
                    end
                    if strncmp(tline2, 'parameters', 10)
                        nparam = sscanf(tline2, '%*s%f');
                        fprintf(biofile, '%s%5i\n', 'parameters', nparam);
                    else
                        disp('Error: polynomial file missing parameter number') %muscle missing from polyfile
                        fclose('all');
                        error = 1;
                        return;
                    end
                    % if there are comments between the 'parameters' line and the
                    % list of coefficients, ignore them
                    tline2 = fgetl(scappolyfile);
                    while (strncmp(tline2, '#', 1))
                        tline2 = fgetl(scappolyfile);
                    end
                    fprintf(biofile, '%s\n', tline2);
                    for ii = 1:nparam-1,
                        tline2 = fgetl(scappolyfile);
                        fprintf(biofile, '%s\n', tline2);
                    end
                end
            end
            % End data from scapula path poly file

        end
        fprintf(biofile, '%s\n', 'end');
    end
end

fprintf(biofile, '\nend\n');

%% Close files

fclose(musclefile);
fclose(dofsfile);
fclose(polyfile);
if strcmp(modelname,'das2')||strcmp(modelname,'das3')
    fclose(GHpolyfile);
end
if strcmp(modelname,'das3')
    fclose(scappolyfile);
end
fclose(biofile);
error = 0;
