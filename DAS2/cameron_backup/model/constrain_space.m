%% Script to generate motion file for SIMM, covering a constrained
%% workspace
% Setup limits and number of steps
% The position of the endpoint is constrained inside a rectangular cylinder
%
% Based on gen_motion.m by Ed Chadwick
% Dimitra Blana - 2/21/07: GH x-y-z angles instead of y-z-yy 

clear all;
close all;

Nsteps = 5;

GHyMin  = -90; GHyMax = 120; GHyStep = (GHyMax - GHyMin)/Nsteps;
GHzMin  =   0; GHzMax = 110; GHzStep = (GHzMax - GHzMin)/Nsteps;
GHyyMin = -70; GHyyMax = 90; GHyyStep = (GHyyMax - GHyyMin)/Nsteps;
ELxMin  =   0; ELxMax = 160; ELxStep = (ELxMax - ELxMin)/Nsteps;
PSyMin  =   0; PSyMax = 170; PSyStep = (PSyMax - PSyMin)/Nsteps;

workspace = [];
EPx = [];
EPy = [];
EPz = [];
figure;
for GHy = GHyMin:GHyStep:GHyMax;
    for GHz = GHzMin:GHzStep:GHzMax;
        for GHyy = GHyyMin:GHyyStep:GHyyMax;
            for ELx = ELxMin:ELxStep:ELxMax;
                for PSy = PSyMin:PSyStep:PSyMax;
                    EP = get_endpoint(GHy, GHz, GHyy, ELx, PSy);
                    EPx = [EPx;EP(1)];
                    EPy = [EPy;EP(2)];
                    EPz = [EPz;EP(3)];
                    plot3(EP(1),EP(2),EP(3),'o'); hold on;
                    [GHx_new,GHy_new,GHz_new]=yzy2xyz(GHy,GHz,GHyy);
%                    workspace = [workspace; GHy GHz GHyy ELx PSy];
                    workspace = [workspace; GHx_new GHy_new GHz_new ELx PSy];
                end
            end
        end
    end
end

xin = EPx>0;
yin = EPy<0.3;
zin = EPz<0;
allin = xin & yin & zin;

newwork = workspace(find(allin),:);
newx = EPx(find(allin));
newy = EPy(find(allin));
newz = EPz(find(allin));

figure;
for i=1:size(newx,1)
    plot3(newx(i),newy(i),newz(i),'o'); hold on;
end

datarows = size(newwork,1);


fid = fopen('constrained_motion.mot','wt');
fprintf(fid, '%s %g\n', 'datarows', datarows');
fprintf(fid, '%s\n', 'datacolumns 6');
fprintf(fid, '%s\n', 'endheader');
% fprintf(fid, '%s\n', 'GH_y_gcv GH_z_gcv GH_yy_gcv EL_x_gcv PS_y_gcv');
fprintf(fid, '%s\n', 'time GH_x_gcv GH_y_gcv GH_z_gcv EL_x_gcv PS_y_gcv');

for i=1:datarows
    fprintf(fid,'%g %g %g %g %g %g\n', 0.01*(i-1), newwork(i,1), newwork(i,2), newwork(i,3), newwork(i,4), newwork(i,5));
end
status = fclose(fid);