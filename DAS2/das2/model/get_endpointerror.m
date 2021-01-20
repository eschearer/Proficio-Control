function [goalEP, actualEP, errorP, errorO]= get_endpointerror(goal_angles,actual_angles)
% finds the endpoint translation and rotation error between goal and actual
% angles (for DAS2)
%
% DAS2 coordinate frame: origin is at GH 
%                        x is left-right (right is positive)
%                        y is up-down (up is positive)
%                        z is back-front (back is positive)
%
% inputs: goal and actual DAS2 angles (GHy,GHz,GHyy,ELx,PSy) in degrees
% outputs: - goalEP is the endpoint (x,y,z) in cm calculated from the goal angles
%          - actualEP is the endpoint (x,y,z) in cm calculated from the actual angles
%          - errorP is the endpoint distance in cm between goalEP and actualEP
%          - errorO is the angle (in degrees) between the goal and actual
%          coordinate frames of the hand

rotaxis=[   0 1 0;... %GHy
            0 0 1;... %GHz
            0 1 0;... %GHyy
            0.9997661210 0.0084460010 -0.0199090024;... %ELx in humerus c.f.
            -0.1132949791 0.9740588207 0.1958919639];   %PSy in ulnar c.f.

translation=[   0 0 0;... %GHy
                0 0 0;... %GHz
                0 0 0;... %GHyy
                0.0058 -0.2907 0.0049;... % ulnar c.f. origin in humerus c.f.
                0.0171 -0.0133 -0.0163;...% radial c.f. origin in ulnar c.f.
                0.0169 -0.2251 -0.0712];  % wrist, in radial c.f.

% first change into radians
goal_angles = goal_angles*pi/180;
actual_angles = actual_angles*pi/180;

% find transformation matrix between global and hand coordinate frames 
goalTM=eye(4);
actualTM=eye(4);
for j=1:5
    goalTM=goalTM*trans_axis(rotaxis(j,:),goal_angles(j),translation(j,:));
    actualTM=actualTM*trans_axis(rotaxis(j,:),actual_angles(j),translation(j,:));
end
goalTM=goalTM*trans_axis(rotaxis(j,:),0,translation(6,:));
actualTM=actualTM*trans_axis(rotaxis(j,:),0,translation(6,:));
% the translation part of the transformation matrix gives endpoint position
goalEP = goalTM(1:3,4)*100;
actualEP = actualTM(1:3,4)*100;
errorP = sum((goalEP-actualEP).^2).^0.5;
% the rotation part of the transformation matrix gives endpoint orientation
errorO = find_angle(goalTM(1:3,1:3),actualTM(1:3,1:3))*180/pi;

% endfunction


function TM = trans_axis(rotaxis,theta,trans)
% finds the transformation matrix for rotation theta about axis rotaxis and
% translation trans

c = cos(theta);
s = sin(theta);
t = 1-c;
X=rotaxis(1);
Y=rotaxis(2);
Z=rotaxis(3);

TM(1,1)= 1 + (X^2-1)*t;
TM(1,2)= -Z*s + X*Y*t;
TM(1,3)= Y*s + X*Z*t;
TM(2,1)= Z*s + X*Y*t;
TM(2,2)= 1 + (Y^2-1)*t;
TM(2,3)= -X*s + Y*Z*t;
TM(3,1)= -Y*s + X*Z*t;
TM(3,2)= X*s + Y*Z*t;
TM(3,3)= 1 + (Z^2-1)*t;
TM(4,4)=1;
TM(4,1)=0;
TM(4,2)=0;
TM(4,3)=0;
TM(1,4)=trans(1);
TM(2,4)=trans(2);
TM(3,4)=trans(3);

% endfunction


function psi = find_angle(R1,R2)
% finds the angle between coordinate frames R1 and R2 (about whichever axis
% that happens to be)

lx=R1(1,:)*R2(1,:)';
ly=R1(2,:)*R2(1,:)';
mx=R1(1,:)*R2(2,:)';
my=R1(2,:)*R2(2,:)';

cospsi=0.5*(lx+my+sqrt((lx-my)^2+(mx+ly)^2));
if cospsi<-1 || cospsi>1
    cospsi=0.5*(lx+my-sqrt((lx-my)^2+(mx+ly)^2));
end
psi=acos(cospsi);

% endfunction

