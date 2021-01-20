function [xnew,ynew,znew] = yzy2xyz(y,z,yy)
%% transforms y-z-y to x-y-z euler angles (in degrees)

R = roty(y*pi/180)*rotz(z*pi/180)*roty(yy*pi/180);
[xnew,ynew,znew] = rotxyz(R);
xnew=xnew*180/pi;
ynew=ynew*180/pi;
znew=znew*180/pi;

%% other functions %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function [Ry]=roty(th)
% creates rotation matrix
% for rotations or th radians around the y axis

Ry(1,1)=cos(th);
Ry(1,3)=sin(th);
Ry(2,2)=1;
Ry(3,1)=-sin(th);
Ry(3,3)= cos(th);

function [Rz]=rotz(th)
% calculates the rotation matrix
% for rotations of th radians around the z axis

Rz(1,1)=cos(th);
Rz(1,2)=-sin(th);
Rz(2,1)= sin(th);
Rz(2,2)= cos(th);
Rz(3,3)=1;

function [x,y,z] = rotxyz(R)
% calculates the Euler angles around the x,y, and z axes
% from the rotation matrix R

y1 = asin(R(1,3));
sz = -R(1,2)/cos(y1);
cz =  R(1,1)/cos(y1);
z1 = atan2(sz,cz);
sx = -R(2,3)/cos(y1);
cx =  R(3,3)/cos(y1);
x1 = atan2(sx,cx);
if y1>=0 
  y2 = pi - y1;
else
  y2 = -pi -y1;
end
sz = -R(1,2)/cos(y2);
cz =  R(1,1)/cos(y2);
z2 = atan2(sz,cz);
sx = -R(2,3)/cos(y2);
cx =  R(3,3)/cos(y2);
x2 = atan2(sx,cx);
if (-pi/2 <= y1 & y1 <= pi/2)
  y=y1;
  z=z1;
  x=x1;
else
  y=y2;
  z=z2;
  x=x2;
end