% get GH workspace from recorded data
% and create SIMM motion file for DAS2 moment arm and GH reaction force
% polynomial estimation
%
% Dimitra Blana - June 4th 2007
%
% We recorded 35 trials with the subject moving his humerus through all
% possible configurations

clear all;
close all;

% change this into the data folder:
path = 'C:\das2_2007_05_31_145113\';

% column number of bony landmarks in data files:
ELid=1:3;
EMid=4:6;
PXid=7:9;
IJid=10:12;
C7id=13:15;
T8id=16:18;
SCid=19:21;
AAid=22:24;
TSid=25:27;
AIid=28:30;
ACid=31:33;
PCid=34:36;

numframes = zeros(35,1);
frequency = zeros(35,1);
humeral_angles = [];

%% get data out of every trial
for k=1:35
    % create file name
    if k<10
        filename = [path 'das2_2007_05_31_145113_00' num2str(k) '_3d.xls'];
    else
        filename = [path 'das2_2007_05_31_145113_0' num2str(k) '_3d.xls'];
    end

    % find number of frames for this trial
    % this is written in the first line that looks like this:
    % Number of frames: ##
    excelfile = fopen(filename, 'rt');
    tline = fgetl(excelfile);
    if strncmp(tline, 'Number of frames: ', 18)
        numframes(k) = sscanf(tline,'%*s%*c%*s%*c%*s%*c%i');
    end
    % also read frequency from the second line:
    % Frequency: ##
    tline = fgetl(excelfile);
    if strncmp(tline, 'Frequency: ', 11)
        frequency(k) = sscanf(tline,'%*s%i');
    end
    fclose(excelfile);

    % read the data we're interested in
    % the first bony landmark is at column 170 (169 zero based)
    % the last bony landmark is at column 205
    % the first line of data (after the header) is line 6
    data=dlmread(filename,'\t',[5 169 4+numframes(k) 204]);

    [data,nodata]=fix_data_fprinp(data,1);

        % resample at 3Hz
        data=resample(data,1,10);
        frequency(k) = frequency(k)/10;
    
        [nData,nBL]=size(data);
        maxt = nData/frequency(k);
        time = 1/frequency(k):1/frequency(k):maxt;
    
        data=GcsDsem(data,1);
    
        % This is fixed and was calculated and saved from the first timestep in the trial, don't include in for loop
        PX=data(:,PXid)';
        IJ=data(:,IJid)';
        SC=data(:,SCid)';
        C7=data(:,C7id)';
        T8=data(:,T8id)';
    
        if k==1
            zero_thorax = asthor(IJ(:,1),PX(:,1),C7(:,1),T8(:,1));
        else
            load zero
        end
    
        data=change_global(data,zero_thorax);
    
        PX=data(:,PXid)';
        IJ=data(:,IJid)';
        SC=data(:,SCid)';
        C7=data(:,C7id)';
        T8=data(:,T8id)';
        AA=data(:,AAid)';
        TS=data(:,TSid)';
        AI=data(:,AIid)';
        AC=data(:,ACid)';
        PC=data(:,PCid)';
        EL=data(:,ELid)';
        EM=data(:,EMid)';
    
        % Done only one time from the first frame on first trial (i.e. resting position)
        if k==1
            zero_clav=asclav(SC(:,1),AC(:,1),[0;1;0]);   	   % clavicle w.r.t. thorax
            zero_scap=asscap(AA(:,1),TS(:,1),AI(:,1));         % scapula w.r.t. thorax
            save zero zero_clav zero_scap zero_thorax
        end
    
        for i=1:nData
            GH(1:3,i)=ghest_aa(PC(:,i),AC(:,i),AA(:,i),TS(:,i),AI(:,i));
        end
    
        % plot3(IJf(1,:),IJf(2,:),IJf(3,:),'b+');
        % hold on;
        % plot3(ELf(1,:),ELf(2,:),ELf(3,:),'go');
        % plot3(EMf(1,:),EMf(2,:),EMf(3,:),'g+');
        % plot3(GHf(1,:),GHf(2,:),GHf(3,:),'r+');
        % xlabel('x'); ylabel('y'); zlabel('z');
    
    
        for i=1:nData
            %  calculation of local coordinate systems
            T=asthor(IJ(:,i),PX(:,i),C7(:,i),T8(:,i)); 	% thorax w.r.t. global
            C=asclav(SC(:,i),AC(:,i),T(:,2));             % clavicle w.r.t. global
            S=asscap(AA(:,i),TS(:,i),AI(:,i));           % scapula w.r.t. global
            H=ashum(GH(:,i),EM(:,i),EL(:,i));     		% humerus w.r.t. global
    
    
            % **************************************************************
            %    estimation of axial rotation of the clavicle
            %    if you don't do the correction, the axial rotation is always zero
            %
            %    the first frame has to be the zero position
            Ccorr=[zero_clav;C];
            Scorr=[zero_scap;S];
            [Cn,ROTr]=axclav(Ccorr,Scorr);
            C = Cn(4:6,:);
    
            % **************************************************************
            %    calculation of rotation matrices w.r.t. the thorax
            %    coordinate system (bone rotations)
    
            %    Bone rotations w.r.t. thorax:
            %    G*Rti = Ti  -> Rti = G'*Ti
            %    Ti*Rci = Ci  -> Rci = Ti'*Ci
            %    Ti*Rsi = Si  -> Rsi = Ti'*Si
            %    Ti*Rhi = Hi  -> Rhi = Ti'*Hi
            %    The forearm rotations are w.r.t. humerus:
            %    Hi*Rfi = Fi  -> Rfi = Hi'*Fi
            Tg(3*i-2:3*i,:)=T;         % Thorax w.r.t. global
            Ct(3*i-2:3*i,:)=T'*C;      % Clavicle w.r.t. thorax
            St(3*i-2:3*i,:)=T'*S;      % Scapula w.r.t. thorax
            Ht(3*i-2:3*i,:)=T'*H;      % Humerus w.r.t. thorax
        end
    
        % **************************************************************
        %    calculation of euler angles
        %          Rotation order:
        %             1          XYZ    (thor)
        %             2          XZY
        %             3          YZX    (clav,scap)
        %             4          ZYX
        %             5          ZXY    (for)
        %             6          YZY    (hum)
        %             7          XY
    
        % for SIMM: rotations have to be w.r.t. the local coordinate frame
        % for DSEM: rotations have to be w.r.t. the thorax
        % for all but the forearm that is w.r.t. the humerus
        % IJ is w.r.t. the global coordinate frame
    
        Thorg=unwrap(roteuler(Tg,1));
        Clavt=unwrap(roteuler(Ct,3));
        Scapt=unwrap(roteuler(St,3));
        Humt=unwrap(roteuler(Ht,6));
    
        humeral_angles = [humeral_angles;Humt*180/pi];
    
        %plots
    %         figure;
    %         subplot(2,2,1); plot(time,Thorg*180/pi);
    %         title('thoracic angles'); legend('x','y','z');
    %
    %         subplot(2,2,2); plot(time,Clavt*180/pi);
    %         title('clavicular angles'); legend('y','z','x');
    %
    %         subplot(2,2,3); plot(time,Scapt*180/pi);
    %         title('scapular angles'); legend('y','z','x');
    %
    %         subplot(2,2,4); plot(time,Humt*180/pi);
    %         title('humeral angles'); legend('y','z','y');
    %
    %         pause;

    clear Thorg Clavt Scapt Humt Tg Ct St Ht time data;
end

% plot all humeral angles
% scatter3(humeral_angles(:,1),humeral_angles(:,2),humeral_angles(:,3));
% xlabel('y'); ylabel('z'); zlabel('yy');


%% constrain space so that humeral elevation is below 90 degrees
%GHspace = humeral_angles(find(humeral_angles(:,2)<90),:);

yin = humeral_angles(:,1)>-90 & humeral_angles(:,1)<90;
zin = humeral_angles(:,2)>5 & humeral_angles(:,2)<90;
yyin = humeral_angles(:,3)>-55 & humeral_angles(:,3)<70;
allin = yin & zin & yyin;

GHspace = humeral_angles(find(allin),:);

%% choose only unique combination of angles (remove duplicates)
newGHspace = GHspace(1,:);
for i=2:size(GHspace,1)
    new=1;
    cand = GHspace(i,:);  % candidate set of angles
    for j=1:size(newGHspace,1)
        comp = newGHspace(j,:); % set of angles already chosen that we compare to
        if sqrt((cand(1)- comp(1))^2 + (cand(2)- comp(2))^2 +(cand(3)- comp(3))^2)<5
            new=0;
            break;
        end
    end
    if new
        newGHspace = [newGHspace;cand];
    end
end

% plot constrained humeral angles
% figure;
% scatter3(newGHspace(:,1),newGHspace(:,2),newGHspace(:,3));
% xlabel('y'); ylabel('z'); zlabel('yy');

%% create SIMM motion file including all possible elbow flexion/extension
% and pronation/supination angles
Nsteps = 10;
ELxMin  =   5; ELxMax = 140; ELxStep = (ELxMax - ELxMin)/Nsteps;
PSyMin  =   5; PSyMax = 160; PSyStep = (PSyMax - PSyMin)/Nsteps;

workspace = [];
for ELx = ELxMin:ELxStep:ELxMax;
    for PSy = PSyMin:PSyStep:PSyMax;
        ELxvec = ELx*ones(size(newGHspace,1),1);
        PSyvec = PSy*ones(size(newGHspace,1),1);
        workspace = [workspace; newGHspace ELxvec PSyvec];
    end
end

datarows = size(workspace,1);

fid = fopen('das2LimitMotion.mot','wt');
fprintf(fid, '%s %g\n', 'datarows', datarows');
fprintf(fid, '%s\n', 'datacolumns 6');
fprintf(fid, '%s\n', 'endheader');
fprintf(fid, '%s\n', 'time GH_y_gcv GH_z_gcv GH_yy_gcv EL_x_gcv PS_y_gcv');

for i=1:datarows
    fprintf(fid,'%10.5f %10.5f %10.5f %10.5f %10.5f %10.5f\n', 0.01*(i-1), workspace(i,1), workspace(i,2), workspace(i,3), workspace(i,4), workspace(i,5));
end
fclose(fid);