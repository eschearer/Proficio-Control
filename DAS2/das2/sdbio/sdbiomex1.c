/* Inverse das1 model */
/* This file includes routines for the optimisation of muscle forces */

#include "mex.h"
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include "sdbio.h"
#include "matrix.h"

double Fmin[MAXMUS];
double Fmax[MAXMUS];
double fpassive[MAXMUS];
double flen[MAXMUS]; 
double muscle_act[MAXMUS];
double Aeq[MAXLINCON][MAXMUS];
double Beq[MAXMUS];
double cumm_error[2];

extern SDBIO_muscletype SDBIO_muscle[MAXMUS];
extern int SDBIO_nstder;               /* Number of calls to state derivative function deriv() */
extern int SDBIO_ndof;                 /* Number of degrees of freedom in the tree structure */
extern int SDBIO_nmuscles;                     /* number of muscles */
extern SDBIO_jointtype SDBIO_joint[MAXDOF];       /* define array of joints  */
extern double SDBIO_state[MAXSTA];     /* Array containing kinematic and muscle states */
extern FILE *logfile;
 
void  init_opt(double q[], int nmus, double bl[], double bu[], double x0[], double Aeq2[], double Beq[]);
void get_exc(double x[], double exc[],int opt_success);
void objs();
int deriv_inverse(double t, double state[], double dstate[], double param[],
         double ref_angle[], double ref_vel[], double ref_acc[], double act_angle[], double act_vel[]);
void SDBIO_initcond_inverse(double *t, double q[], double qdot[], double ref_angle[], double ref_vel[], double ref_acc[]);	
	 
extern double  musgeo(SDBIO_muscletype *m, double q[], double lq[]);
extern double  Force_VelCE(SDBIO_muscletype *m, double Fce, double Lce, double Act);
extern double  Force_LengthCE(SDBIO_muscletype *m, double Lce);
extern double  Force_LengthPEE(SDBIO_muscletype *m, double Lce);
extern double  Force_LengthSEE(SDBIO_muscletype *m, double Lsee);
extern double  musmod(SDBIO_muscletype *m, double Lce, double act, double state[]);

/**************************************************************************
 	mex function used to interface with matlab
/**************************************************************************/
void mexFunction(int nlhs, mxArray *plhs[],
				 int nrhs, const mxArray *prhs[])
{
    double *x,*f,*c,*exc,*bl,*bu,*x0,*Aeq,*Beq;
	double *t,*q,*qdot,*Lce,*Lcenew,*act,*state,*statedot,*ref_angle,*ref_vel,*ref_acc,*act_angle,*act_vel;
    double *param=0;
	int Nx,num_linear_con,nmus,nmuselem,nstates,buflen,opt_success;
    char *filename;
    int error_flag,i,mus_index;
    static char error_msg[100];
	FILE *logfile;
	
	
	Nx = mxGetScalar(prhs[0]);
		
	if(Nx == 1)
	// routine that calculates the upper and lower limits, initial values of the muscle forces, and Aeq and Beq for linear equality constraints
	{
		// get inputs
	    q = mxGetPr(prhs[1]);
	    nmuselem = mxGetScalar(prhs[2]);
		nmus = nmuselem;

		// number of linear equality constraints
		num_linear_con = 2;
						
		// prepare output			
		plhs[0] = mxCreateDoubleMatrix(nmuselem,1,mxREAL);
		bl = mxGetPr(plhs[0]);
		plhs[1] = mxCreateDoubleMatrix(nmuselem,1,mxREAL);
		bu = mxGetPr(plhs[1]);
		plhs[2] = mxCreateDoubleMatrix(nmuselem,1,mxREAL);
		x0 = mxGetPr(plhs[2]);
		plhs[3] = mxCreateDoubleMatrix(num_linear_con,nmuselem,mxREAL);
		Aeq = mxGetPr(plhs[3]);
		plhs[4] = mxCreateDoubleMatrix(num_linear_con,1,mxREAL);
		Beq = mxGetPr(plhs[4]); 

		init_opt(q,nmus,bl,bu,x0,Aeq,Beq);
	}
	else if(Nx == 2)
	// routine that calculates the objective function
	{
		x = mxGetPr(prhs[1]);
		plhs[0] = mxCreateDoubleMatrix(1,1,mxREAL);
		f = mxGetPr(plhs[0]);
		objs(f,x);
	}
	else if(Nx == 3)
	// routine that calculates the constraints
	{
	// no nonlinear constraints in das1
	}
	else if(Nx == 4)
	// routine that calculates the muscle excitations from the muscle forces
	{
		x = mxGetPr(prhs[1]);
		nmus = mxGetM(prhs[1]);
		opt_success = (int)mxGetScalar(prhs[2]);
		plhs[0] = mxCreateDoubleMatrix(nmus,1,mxREAL);
		exc = mxGetPr(plhs[0]);
		get_exc(x,exc,opt_success);
		
	}
	else if(Nx == 5)
	// model initialization routine
	{
		buflen = (mxGetM(prhs[1]) * mxGetN(prhs[1])) + 1;
		filename = mxCalloc(buflen, sizeof(char));
		mxGetString(prhs[1], filename, buflen);
		SDBIO_init(filename,&error_flag,error_msg);
	}
	else if(Nx == 6)
	// initialize states
	{
		t = mxGetPr(prhs[1]);
		q = mxGetPr(prhs[2]);
		qdot = mxGetPr(prhs[3]);
		ref_angle = mxGetPr(prhs[4]);
		ref_vel = mxGetPr(prhs[5]);
		ref_acc = mxGetPr(prhs[6]);
		SDBIO_initcond_inverse(t,q,qdot,ref_angle,ref_vel,ref_acc);
	}
	else if(Nx == 7)
	// calculate derivatives
	{
		t = mxGetPr(prhs[1]);
		state = mxGetPr(prhs[2]);
		nstates = mxGetM(prhs[2]);
		ref_angle = mxGetPr(prhs[3]);
		ref_vel = mxGetPr(prhs[4]);
		ref_acc = mxGetPr(prhs[5]);
		act_angle = mxGetPr(prhs[6]);
		act_vel = mxGetPr(prhs[7]);
		plhs[0] = mxCreateDoubleMatrix(nstates,1,mxREAL);
		statedot = mxGetPr(plhs[0]);
		deriv_inverse(*t,state,statedot,param,ref_angle,ref_vel,ref_acc,act_angle,act_vel);
	}
	else if(Nx==8)
	// terminate
		SDBIO_terminate();
}		


/* routines used in forward DAS that are not used here */

/******************************************************
    user_stim:         defines stimulation levels
******************************************************/ 
void user_stim(double *t, double q[], double qdot[], double stim[]) 
{   

	*stim = 0;

}  

/*********************************************************
     user_grf:   defines ground reaction force 
*********************************************************/
void user_grf(char *name, int grfpoint, double *p, double *v, double *f)
{
	*f = 0;	/* always return zero */
}

/************************************************************
     user_force:  defines external forces to be applied to system
*******************************************************************/
void user_force(char *name,double t,double *p,double *v,double *f)
{
	*f = 0;	/* always return zero */
}

/****************************************************************
    user_joint: applies passive moments when joint goes outside limits
******************************************************************/
void user_joint(char *name, double e, double ve, double *m)
{
	*m = 0;
}

/****************************************************************
    user_torque: applies other joint moments
******************************************************************/
void user_torque(double t, double *q, double *qdot, double *m)
{
	*m = 0;
}

/******************************************************
    external_force         defines stimulation levels
******************************************************/ 
void external_force(double extf[]) 
{     
  *extf = 0;
}  

/*******************************************************************************************************************************
        init_opt:  calculates the upper and lower limits, initial values of muscle forces, and sets up A,B and glenoid_fvectors needed for optimisation
********************************************************************************************************************************/
void  init_opt(double q[], int nmus, double bl[], double bu[], double x0[], double Aeq2[], double Beq[])
{
	double Lsee,mus_height,mus_width,Lq[MAXDOF];
	double fiber_length, act_min, act_max,Lm;
	SDBIO_muscletype *m;
	int i,j,k,l,n,mus_index,elem_index,num_elem,num_elem2,num_linear_con,counter=0;

					
	for (i=0; i<SDBIO_nmuscles; i++) {
       m = &(SDBIO_muscle[i]);
	   	   
	   // get muscle length and moment arms
       Lm =  musgeo(m, q, Lq);   	
	   
       // store moment arms in matrix A		
      for (j=0; j < m->nmusdof; j++) {
               k = m->musdof[j];
			   Aeq[k][i] = Lq[k];
			   } 
			   
		// stiff tendon approximation	   
		mus_height = Lm - m->lslack;   			/* the muscle "height" equals Lce for unipennate muscles */
		mus_width = m->lceopt * sin(m->pennopt);     /* we assume that this is constant */
		if (mus_height<0) fiber_length = mus_width;
		else fiber_length  = sqrt(mus_width*mus_width + mus_height*mus_height);	  

		act_min = 0.02;
		act_max = 1; 
		
		flen[i] = Force_LengthCE(m, fiber_length); // force from force-length relationship
		fpassive[i] = Force_LengthPEE(m, fiber_length); // passive force from PEE
		
		bl[i]=fpassive[i] + flen[i]*act_min;
		Fmin[i] = bl[i];
		bu[i]=fpassive[i] + flen[i]*act_max; 
		Fmax[i] = bu[i];
		x0[i]=fpassive[i]+flen[i]*muscle_act[i]; 		
//		fprintf(logfile,"%15s: lslack=%f nmusdof=%d fpassive=%f flen=%f pennopt=%f\n",m->name,m->lslack,m->nmusdof,fpassive[i],flen[i],m->pennopt); 	
   }

    // store joint moments in vector B
    for (i=0;i<SDBIO_ndof;i++) 
			Beq[i]=SDBIO_joint[i].torque;
			
	num_linear_con = SDBIO_ndof;
		
	for (j=0;j<SDBIO_nmuscles;j++)	
		for (i=0;i<num_linear_con;i++)				
		{
			*(Aeq2+counter)=Aeq[i][j];
			counter++;
		}
	
    return;
}

/**********************************************************************
        get_exc: this routine calculates the excitation based on the muscle force
**********************************************************************/

void get_exc(double x[], double exc[],int opt_success)
{
	int i;
	double howmuchfb = 0;  // how much feedback?
	double extra_act;
	// stiff tendon approximation
	
	for (i=0;i<SDBIO_nmuscles;i++) {
		if (opt_success) {	
			exc[i] = (x[i]-fpassive[i])/flen[i];	
			muscle_act[i] = exc[i]; }
		else exc[i] = muscle_act[i];
		howmuchfb = howmuchfb + pow(exc[i],2);
	} 
/*	if (howmuchfb>0.01) {
		extra_act = (howmuchfb-0.01)/2;
		for (i=18;i<24;i++)
			exc[i] = exc[i]+extra_act;  // infraspinatus
		for (i=31;i<35;i++)
			exc[i] = exc[i]+extra_act;  // supraspinatus
	}  */
	return;
}

/***************************************************************
	OBJS: this routine calculates the value of the objective function
****************************************************************/
 
void objs(f,x)
double *f,*x;
{
	int i;
	double est_act, act_min, act_max;
	
	act_min = 0.02;
	act_max = 1;
	
   *f=0;
   for (i=0;i<SDBIO_nmuscles;i++)
	{
		if (Fmax[i]==Fmin[i])
			est_act = act_min;
		else
			est_act = act_min + (act_max-act_min)*((x[i]-Fmin[i])/(Fmax[i]-Fmin[i]));
		*f=*f+pow(est_act,2);
   }
   return;
}

/*********************************************************************************
       deriv_inverse:          returns derivatives for all state variables for inverse dynamic model 
**********************************************************************************/
int deriv_inverse(double t, double state[], double dstate[], double param[],
         double ref_angle[], double ref_vel[], double ref_acc[], double act_angle[], double act_vel[]) {
 int i, j;
 double def, veldef, jnt_moment;
 double q[MAXDOF], qdot[MAXDOF], tau[MAXDOF], tau_corr[MAXDOF], moments[MAXMUS*MAXMUSDOF];
 double stims[MAXMUS];
 SDBIO_muscletype *m;
 double errs[MAXCON];  /* Constraint error array */
 double P[2],I[2],D[2];
  
/* register new state for SD/FAST */
 sdstate(t, state, state+SDBIO_ndof);

 for (i=0;i<SDBIO_ndof;i++){
     q[i] = state[i];
     qdot[i] = state[i+SDBIO_ndof];
 }
 
/* apply user motion */
  for (i=0; i<SDBIO_ndof; i++) {
	sdprespos(i, 0, ref_angle[i]);
    sdpresvel(i, 0, ref_vel[i]);
    sdpresacc(i, 0, ref_acc[i]);
  }
  
 /* apply force to end of forearm (where the radio-carpal joint would be)  */
// sdtrans(-1,force_vector,11,body_force_vector);
// sdpointf(11,hand_vector,body_force_vector);  
  
 // calculate required torques
  sdcomptrq(qdot,tau); // torques from prescribed kinematics
  
//  for (i=0;i<2;i++) fprintf(logfile,"torque %i: %f\n",i,tau[i]);
  
  P[0]=1;
  P[1]=1;
  
  I[0]=0.0000;
  I[1]=0.0000;
  
  D[0]=0.001;
  D[1]=0.001;
    
  // torque correction
  for (i=0; i<SDBIO_ndof; i++) {
	cumm_error[i] = cumm_error[i] + ref_angle[i] - act_angle[i];  //approximation of integral part of PID
    tau_corr[i] = P[i]*(ref_angle[i] - act_angle[i]) + D[i]*(ref_vel[i] - act_vel[i]) + I[i]*(cumm_error[i]);
//	SDBIO_joint[i].torque = tau[i]+tau_corr[i];
	SDBIO_joint[i].torque = tau[i];
	} 
 
//  for (i=0;i<SDBIO_ndof;i++) fprintf(logfile,"correct torque %i: %f\n",i,SDBIO_joint[i].torque);
  
/* Compute SD state derivatives: accelerations and velocities for generalized coordinates */

 sdderiv(dstate, dstate+SDBIO_ndof);
 	
/* Check that constraint errors are below tol.
  Although there are here no constraint, this checking should always
  be done by the user when using the Generalized Analysis Routine. */
  
}

/****************************************************************************************
      SDBIO_initcond_inverse:  Sets initial conditions q, qdot, act, and Lce for inverse dynamic model
*****************************************************************************************/
void SDBIO_initcond_inverse(double *t, double q[], double qdot[], double ref_angle[], double ref_vel[], double ref_acc[])
{

 int i,status;
 double Lq[MAXDOF], dstate[MAXSTA],param[MAXCON];
 SDBIO_muscletype *m;
  
/* set initial q and qdot: */

 for (i=0; i<SDBIO_ndof; i++) {
   SDBIO_state[i] = q[i];
   SDBIO_state[i+SDBIO_ndof] = qdot[i];
 }

/* set initial muscle activations: */
// for (i=0; i<SDBIO_nmuscles; i++) muscle_act[i] = actmin;  // muscle activation for inverse muscle model
 for (i=0; i<SDBIO_nmuscles; i++) muscle_act[i] = 0.02;  // muscle activation for inverse muscle model
 
 for (i=0;i<SDBIO_ndof;i++) cumm_error[i] = 0;
   
/* call deriv to set initial states */
 deriv_inverse(*t, SDBIO_state,dstate,param,ref_angle,ref_vel,ref_acc,ref_angle,ref_vel);

}
