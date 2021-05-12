function EP = get_endpoint(GH_y,GH_z,GH_yy,EL_x,PS_y)
%% calculate hand position based on the DOF values
% the position is in m with respect to the thorax c.f.
% The calculation is based on the SIMM joint file for DAS2

%%%%%% SC joint %%%%%%%%%%%%%%%%%%%
% beginjoint sc
% segments thorax clavicle_r
% order t r2 r3 r1
% axis1 1.000000 0.000000 0.000000
% axis2 0.000000 1.000000 0.000000
% axis3 0.000000 0.000000 1.000000
% tx  constant 0.001400
% ty  constant -0.015200
% tz  constant 0.002800
% r1  constant 0.099349
% r2  constant -21.940000
% r3  constant 6.122000
% endjoint

trans = eye(4);
origin = [0.0014; -0.0152; 0.0028];
trans([1 2 3],4) = origin;
SC_T = trans*roty(-21.94)*rotz(6.122)*rotx(0.099349);

%%%%%% AC joint %%%%%%%%%%%%%%%%%%%
% beginjoint ac
% segments clavicle_r scapula_r
% order t r2 r3 r1
% axis1 1.000000 0.000000 0.000000
% axis2 0.000000 1.000000 0.000000
% axis3 0.000000 0.000000 1.000000
% tx  constant 0.207700
% ty  constant -0.000100
% tz  constant 0.028200
% r1  constant 6.719540
% r2  constant 35.603408
% r3  constant 13.672019
% endjoint

trans = eye(4);
origin = [0.2077; -0.0001; 0.0282];
trans([1 2 3],4) = origin;
AC_T = trans*roty(35.603408)*rotz(13.672019)*rotx(6.71954);

%%%%%% GH joint %%%%%%%%%%%%%%%%%%%
% beginjoint gh
% segments scapula_r humerus_r
% order t r1 r2 r3
% axis1 0.000000 1.000000 0.000000
% axis2 0.000000 0.000000 1.000000
% axis3 0.000000 1.000000 0.000000
% tx  constant 0.002000
% ty  constant -0.023000
% tz  constant -0.043900
% r1  function f1(GH_y)
% r2  function f1(GH_z)
% r3  function f1(GH_yy)
% endjoint

trans = eye(4);
origin = [0.002; -0.023; -0.0439];
trans([1 2 3],4) = origin;
GH_T = trans*roty(GH_y)*rotz(GH_z)*roty(GH_yy);

%%%%%% HU joint %%%%%%%%%%%%%%%%%%%
% beginjoint hu
% segments humerus_r ulna_r
% order t r1 r2 r3
% axis1 0.999766 0.008446 -0.019909
% axis2 0.000000 1.000000 0.000000
% axis3 0.000000 0.000000 1.000000
% tx  constant 0.005800
% ty  constant -0.290700
% tz  constant 0.004900
% r1  function f1(EL_x)
% r2  constant 0.000000
% r3  constant 0.000000
% endjoint

axis = [0.999766; 0.008446; -0.019909];
trans = eye(4);
origin = [0.0058; -0.2907; 0.0049];
trans([1 2 3],4) = origin;
HU_T = trans*rotaxis(EL_x,axis);

%%%%%% UR joint %%%%%%%%%%%%%%%%%%%
% beginjoint ur
% segments ulna_r radius_r
% order t r2 r3 r1
% axis1 1.000000 0.000000 0.000000
% axis2 -0.113295 0.974059 0.195892
% axis3 0.000000 0.000000 1.000000
% tx  constant 0.017100
% ty  constant -0.013300
% tz  constant -0.016300
% r1  constant 0.000000
% r2  function f1(PS_y)
% r3  constant 0.000000
% endjoint

axis = [-0.113295; 0.974059; 0.195892];
trans = eye(4);
origin = [0.0171; -0.0133; -0.0163];
trans([1 2 3],4) = origin;
UR_T = trans*rotaxis(PS_y,axis);

%%%%%% RC joint %%%%%%%%%%%%%%%%%%%
% beginjoint rc
% segments radius_r hand_r
% order t r3 r1 r2
% axis1 1.000000 0.000000 0.000000
% axis2 0.000000 1.000000 0.000000
% axis3 0.000000 0.000000 1.000000
% tx  constant 0.016900
% ty  constant -0.225100
% tz  constant -0.071200
% r1  constant 0.000000
% r2  constant 0.000000
% r3  constant 0.000000
% endjoint

trans = eye(4);
origin = [0.0169; -0.2251; -0.0712];
trans([1 2 3],4) = origin;
RC_T = trans;

EPlocal = [0; 0; 0; 1];
EP = SC_T*AC_T*GH_T*HU_T*UR_T*RC_T*EPlocal;


%% other functions %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

function r = rotx(a)
% calculates rotation around x axis by angle a (in degrees)
ar = pi*a / 180;
r = [1 0 0 0;0 cos(ar) sin(ar) 0; 0 -sin(ar) cos(ar) 0; 0 0 0 1];

function r = roty(b)
% calculates rotation around y axis by angle b (in degrees)
br = pi*b / 180;
r = [cos(br) 0 -sin(br) 0;0 1 0 0;sin(br) 0 cos(br) 0; 0 0 0 1];

function r = rotz(c)
% calculates rotation around z axis by angle c (in degrees)
cr = pi*c / 180;
r = [cos(cr) sin(cr) 0 0;-sin(cr) cos(cr) 0 0;0 0 1 0; 0 0 0 1];

function r = rotaxis(d,v)
% calculates rotation around vector v by angle d (in degrees)
dr = pi*d / 180;
r = [cos(dr)+(1-cos(dr))*v(1)^2         (1-cos(dr))*v(1)*v(2)+sin(dr)*v(3)   (1-cos(dr))*v(1)*v(3)-sin(dr)*v(2) 0;...
    (1-cos(dr))*v(2)*v(1)-sin(dr)*v(3)   cos(dr)+(1-cos(dr))*v(2)^2          (1-cos(dr))*v(2)*v(3)+sin(dr)*v(1) 0;...
    (1-cos(dr))*v(3)*v(1)+sin(dr)*v(2)  (1-cos(dr))*v(3)*v(2)-sin(dr)*v(1)    cos(dr)+(1-cos(dr))*v(3)^2 0;...
    0 0 0 1];
    
    
