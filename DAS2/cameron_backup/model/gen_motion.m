%% Script to generate motion files for SIMM, covering the entire workspace
% Setup limits and number of steps
%
% writes GH x-y-z angles to SIMM motion file (instead of y-z-yy) - DB, 2/21/07 
% added time column so that exporting the moment arms from the dynamics
% pipeline is easier - DB, 2/26/07


Nsteps = 6;

GHyMin  =   0; GHyMax  =  90; GHyStep = (GHyMax - GHyMin)/Nsteps;
GHzMin  =   5; GHzMax  =  80; GHzStep = (GHzMax - GHzMin)/Nsteps;
GHyyMin = -60; GHyyMax =  40; GHyyStep = (GHyyMax - GHyyMin)/Nsteps;
ELxMin  =   5; ELxMax  = 140; ELxStep = (ELxMax - ELxMin)/Nsteps;
PSyMin  =   5; PSyMax  = 160; PSyStep = (PSyMax - PSyMin)/Nsteps;

%% Full motion (all DOF)

datarows = (Nsteps+1)^5;

fid = fopen('full_motion.mot','wt');
fprintf(fid, '%s %g\n', 'datarows', datarows');
fprintf(fid, '%s\n', 'datacolumns 6');
fprintf(fid, '%s\n', 'endheader');
% fprintf(fid, '%s\n', 'time GH_y GH_z GH_yy EL_x PS_y');
fprintf(fid, '%s\n', 'time GH_y_gcv GH_z_gcv GH_yy_gcv EL_x_gcv PS_y_gcv');

time = 0;
for GHy = GHyMin:GHyStep:GHyMax;
    for GHz = GHzMin:GHzStep:GHzMax;
        for GHyy = GHyyMin:GHyyStep:GHyyMax;
            for ELx = ELxMin:ELxStep:ELxMax;
                for PSy = PSyMin:PSyStep:PSyMax;
                   [GHx_new,GHy_new,GHz_new]=yzy2xyz(GHy,GHz,GHyy);
                  % fprintf(fid,'%g %g %g %g %g %g\n',0.01*time, GHx_new, GHy_new, GHz_new, ELx, PSy);
                   fprintf(fid,'%g %g %g %g %g %g\n',0.01*time, GHy, GHz, GHyy, ELx, PSy);
                   time = time+1;
                end
            end
        end
    end
end

status = fclose(fid)

return

%% GH plus FE

datarows = (Nsteps+1)^4;

fid = fopen('GHplusFE.mot','wt');
fprintf(fid, '%s %g\n', 'datarows', datarows');
fprintf(fid, '%s\n', 'datacolumns 4');
fprintf(fid, '%s\n', 'endheader');
% fprintf(fid, '%s\n', 'GH_y GH_z GH_yy EL_x');
fprintf(fid, '%s\n', 'GH_x_gcv GH_y_gcv GH_z_gcv EL_x_gcv');

for GHy = GHyMin:GHyStep:GHyMax;
    for GHz = GHzMin:GHzStep:GHzMax;
        for GHyy = GHyyMin:GHyyStep:GHyyMax;
            for ELx = ELxMin:ELxStep:ELxMax;
                [GHx_new,GHy_new,GHz_new]=yzy2xyz(GHy,GHz,GHyy);
                fprintf(fid,'%g %g %g %g\n',GHx_new, GHy_new, GHz_new, ELx);                
                % fprintf(fid,'%g %g %g %g\n',GHy, GHz, GHyy, ELx);                
            end
        end
    end
end

status = fclose(fid)


%% GH motion only

datarows = (Nsteps+1)^3;

fid = fopen('GHonly.mot','wt');
fprintf(fid, '%s %g\n', 'datarows', datarows');
fprintf(fid, '%s\n', 'datacolumns 3');
fprintf(fid, '%s\n', 'endheader');
% fprintf(fid, '%s\n', 'GH_y GH_z GH_yy');
fprintf(fid, '%s\n', 'GH_x_gcv GH_y_gcv_gcv GH_z');

for GHy = GHyMin:GHyStep:GHyMax;
    for GHz = GHzMin:GHzStep:GHzMax;
        for GHyy = GHyyMin:GHyyStep:GHyyMax;
            [GHx_new,GHy_new,GHz_new]=yzy2xyz(GHy,GHz,GHyy);
            fprintf(fid,'%g %g %g\n',GHx_new, GHy_new, GHz_new);                
            % fprintf(fid,'%g %g %g\n',GHy, GHz, GHyy);           
        end
    end
end

status = fclose(fid)

%% Elbow FE and PS

datarows = (Nsteps+1)^2;

fid = fopen('FEplusPS.mot','wt');
fprintf(fid, '%s %g\n', 'datarows', datarows');
fprintf(fid, '%s\n', 'datacolumns 2');
fprintf(fid, '%s\n', 'endheader');
fprintf(fid, '%s\n', 'EL_x PS_y');

for ELx = ELxMin:ELxStep:ELxMax;
    for PSy = PSyMin:PSyStep:PSyMax;
        fprintf(fid,'%g %g\n',ELx, PSy);
    end
end

status = fclose(fid)

%% Elbow FE only

datarows = Nsteps+1;

fid = fopen('FEonly.mot','wt');
fprintf(fid, '%s %g\n', 'datarows', datarows');
fprintf(fid, '%s\n', 'datacolumns 1');
fprintf(fid, '%s\n', 'endheader');
fprintf(fid, '%s\n', 'EL_x');

for ELx = ELxMin:ELxStep:ELxMax;
    fprintf(fid,'%g\n',ELx);
end

status = fclose(fid)

%% PS only

datarows = Nsteps+1;

fid = fopen('PSonly.mot','wt');
fprintf(fid, '%s %g\n', 'datarows', datarows');
fprintf(fid, '%s\n', 'datacolumns 1');
fprintf(fid, '%s\n', 'endheader');
fprintf(fid, '%s\n', 'PS_y');

for PSy = PSyMin:PSyStep:PSyMax;
    fprintf(fid,'%g\n',PSy);
end

status = fclose(fid)
