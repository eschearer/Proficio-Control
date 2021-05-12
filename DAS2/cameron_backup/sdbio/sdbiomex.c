#include "mex.h"
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include "sdbio.h"
#include "matrix.h"

/**************************************************************************
 	mex function used to interface with matlab
/**************************************************************************/
void mexFunction(int nlhs, mxArray *plhs[],
				 int nrhs, const mxArray *prhs[])
{
    double *x,*f,*c,*exc,*bl,*bu,*x0,*Aeq,*Beq,*elem_per_mus,*bind_elements,*bind_muscles,*force_fraction;
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
		nmuselem = (int)mxGetScalar(prhs[2]);
	    elem_per_mus = mxGetPr(prhs[3]);
	    bind_elements = mxGetPr(prhs[4]);
	    bind_muscles = mxGetPr(prhs[5]);
	    force_fraction = mxGetPr(prhs[6]);
		nmus = mxGetN(prhs[3]);
		
		// make sure that if a cuff is applied to a muscle, 
		// it is also under FES stimulation (all elements have the same activation)
		for (mus_index=0;mus_index<nmus;mus_index++)
			if (bind_muscles[mus_index]>0)
				bind_elements[mus_index]=1; 

		// calculate number of linear equality constraints
		num_linear_con = 0;
	
		// moment constraints
		num_linear_con = num_linear_con + 5;
	
		// FES constraints
		for (mus_index=0;mus_index<nmus;mus_index++)
			if (bind_elements[mus_index]==1)
				num_linear_con = num_linear_con + elem_per_mus[mus_index]-1;

		// cuff constraints
		for (mus_index=0;mus_index<nmus-1;mus_index++)
			if (bind_muscles[mus_index]>0)
				for (i=mus_index+1;i<nmus;i++)
					if (bind_muscles[i]==bind_muscles[mus_index])
					{
						num_linear_con++;					
						break;
					}
					
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

		init_opt(q,elem_per_mus,bind_elements,bind_muscles,force_fraction,nmus,bl,bu,x0,Aeq,Beq);
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
		x = mxGetPr(prhs[1]);
		plhs[0] = mxCreateDoubleMatrix(1,1,mxREAL);
		c = mxGetPr(plhs[0]);
		cons(c,x);
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
