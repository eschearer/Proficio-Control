/* Inverse das2 model */
/* This file includes routines for the optimisation of muscle forces */

#include "mex.h"
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include "sdbio.h"
#include "matrix.h"


double Fmin[MAXMUS]={0};
double Fmax[MAXMUS]={1};
double glenoid_fvectors[3][MAXMUS]={0};
double fpassive[MAXMUS]={0};
double flen[MAXMUS]={1}; 
double muscle_act[MAXMUS]={0};
double Aeq[MAXLINCON][MAXMUS]={0};
double Beq[MAXMUS]={0};
double cumm_error[5]={0};
FILE *invlogfile;
	
extern SDBIO_muscletype SDBIO_muscle[MAXMUS];
extern int SDBIO_nstder;               /* Number of calls to state derivative function deriv() */
extern int SDBIO_ndof;                 /* Number of degrees of freedom in the tree structure */
extern int SDBIO_nmuscles;                     /* number of muscles */
extern SDBIO_jointtype SDBIO_joint[MAXDOF];       /* define array of joints  */
extern double SDBIO_state[MAXSTA];     /* Array containing kinematic and muscle states */

void  init_opt(double q[], double nelem_mus[], double bind_elements[], double bind_muscles[], double max_act[], double min_act[], int nmus, double bl[], double bu[], double x0[], double Aeq2[], double Beq[]);
void get_exc(double x[], double exc[],int opt_success);
void objs(double *f,double *x,double max_act[], double min_act[]);
void cons();
int deriv_inverse(double t, double state[], double dstate[], double param[],
         double ref_angle[], double ref_vel[], double ref_acc[], double act_angle[], double act_vel[]);
void SDBIO_initcond_inverse(double *t, double q[], double qdot[], double ref_angle[], double ref_vel[], double ref_acc[], double min_act[]);

extern double  musgeo(SDBIO_muscletype *m, double q[], double lq[]);
extern double calc_pennation(double Lce, double Lceopt, double pennopt);
extern double normalize_vector(double vector[], double norm_vector[]);

/**************************************************************************
 	mex function used to interface with matlab
/**************************************************************************/
void mexFunction(int nlhs, mxArray *plhs[],
				 int nrhs, const mxArray *prhs[])
{
    double *x,*f,*c,*exc,*bl,*bu,*x0,*Aeq,*Beq,*nelem_mus,*bind_elements,*bind_muscles,*max_act,*min_act;
	double *t,*q,*qdot,*Lce,*Lcenew,*act,*state,*statedot,*ref_angle,*ref_vel,*ref_acc,*act_angle,*act_vel;
    double *param=0;
	int Nx,num_linear_con,nmus,nmuselem,nstates,buflen,opt_success;
    char *filename;
    int error_flag,i,mus_index;
    static char error_msg[100];

	Nx = mxGetScalar(prhs[0]);
		
	if(Nx == 1)
	// routine that calculates the upper and lower limits, initial values of the muscle forces, and Aeq and Beq for linear equality constraints
	{
		// get inputs
	    q = mxGetPr(prhs[1]);
		nmuselem = (int)mxGetScalar(prhs[2]);
	    nelem_mus = mxGetPr(prhs[3]);
	    bind_elements = mxGetPr(prhs[4]);
	    bind_muscles = mxGetPr(prhs[5]);
	    max_act = mxGetPr(prhs[6]);
	    min_act = mxGetPr(prhs[7]);
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
				num_linear_con = num_linear_con + nelem_mus[mus_index]-1;

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

		init_opt(q,nelem_mus,bind_elements,bind_muscles,max_act,min_act,nmus,bl,bu,x0,Aeq,Beq);
	}
	else if(Nx == 2)
	// routine that calculates the objective function
	{
		x = mxGetPr(prhs[1]);
	    max_act = mxGetPr(prhs[2]);
	    min_act = mxGetPr(prhs[3]);
		plhs[0] = mxCreateDoubleMatrix(1,1,mxREAL);
		f = mxGetPr(plhs[0]);
		
		objs(f,x,max_act,min_act);
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
	    min_act = mxGetPr(prhs[7]);
		SDBIO_initcond_inverse(t,q,qdot,ref_angle,ref_vel,ref_acc,min_act);
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
	else if(Nx == 8)
	{
	// terminate
		fclose(invlogfile);
		SDBIO_terminate();
	}
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
void  init_opt(double q[], double nelem_mus[], double bind_elements[], double bind_muscles[], double max_act[], double min_act[], int nmus, double bl[], double bu[], double x0[], double Aeq2[], double Beq[])
{
	double Lsee,GHfvector[3],mus_height,mus_width,Lq[MAXDOF],fiber_length;
	SDBIO_muscletype *m;
	int i,j,k,l,n,mus_index,elem_index,num_elem,num_elem2,num_linear_con,counter;
	double Lcen,Lce0,Lcesh,Lopt,Lm,pep1,pep2,penn_angle;
	double PEsh   =  4.00; // parallel elastic element, shape parameter
    double PExm  = 0.4; // parallel elastic element, max. extension
	pep1 = 1 / (exp(PEsh) - 1.0);
				
	for (i=0; i<SDBIO_nmuscles; i++) {
       m = &(SDBIO_muscle[i]);
	   
		// get muscle GH vectors
	   get_GH_force_vector(m, q, GHfvector);
	   	   
	   // store it in global matrix glenoid_fvectors
	   for (j=0; j<3; j++)
	   {
			glenoid_fvectors[j][i] = GHfvector[j];
//		    fprintf(invlogfile,"%15s GHx:   %f GHy:   %f GHz:   %f\n",m->name,GHfvector[0],GHfvector[1],GHfvector[2]);	
		}
	   
	   // get muscle length and moment arms
       m->lm =  musgeo(m, q, Lq);  
	   
       // store moment arms in matrix A		
      for (j=0; j < m->nmusdof; j++) {
               k = m->musdof[j];
			   Aeq[k][i] = Lq[k];
			   } 
			   
		// stiff tendon approximation	   
		mus_height = m->lm - m->lslack;   			/* the muscle "height" equals Lce for unipennate muscles */
		mus_width = m->lceopt * sin(m->pennopt);     /* we assume that this is constant */
		if (mus_height<0) fiber_length = mus_width;
		else fiber_length  = sqrt(mus_width*mus_width + mus_height*mus_height);	  
		
		/* pennation angle: between 0 and 90 degrees */
		penn_angle = calc_pennation(fiber_length,m->lceopt,m->pennopt);
				
		// force-length coefficient
		Lopt = m->lceopt*cos(m->pennopt) + m->lslack;
		Lm = m->lm / Lopt;
		Lcen = fiber_length / Lopt;
		Lce0 = m->lceopt / Lopt;
		Lcesh = 0.3 * Lce0; // force/length, width f-l relation
		flen[i] = exp(-((Lcen - Lce0)/Lcesh)*((Lcen - Lce0)/Lcesh));
		flen[i] = cos(penn_angle)*flen[i];
		
		// passive force
		pep2  =  exp((Lm-1)*(PEsh/PExm));          
		fpassive[i] = pep1 * (pep2 - 1.0) * m->fmax;
		if (fpassive[i]<0) fpassive[i]=0.0;
		
		bl[i]=fpassive[i] + flen[i]*min_act[i]*m->fmax;
		Fmin[i] = bl[i];
		bu[i]=fpassive[i] + flen[i]*max_act[i]*m->fmax; 
		Fmax[i] = bu[i];
		x0[i]=fpassive[i]+flen[i]*muscle_act[i]*m->fmax; 	
//		fprintf(invlogfile,"%15s min force: %f max force: %f fpassive: %f flen: %f\n",m->name,Fmin[i],Fmax[i],fpassive[i],flen[i]);	
//		fprintf(invlogfile,"         and moment arms: %f   %f   %f   %f   %f\n\n",Aeq[0][i],Aeq[1][i],Aeq[2][i],Aeq[3][i],Aeq[4][i]);				
  }

    // store joint moments in vector B
    for (i=0;i<SDBIO_ndof;i++) 
	{
			Beq[i]=SDBIO_joint[i].torque;
//			fprintf(invlogfile,"Beq of constraint %i=%f\n",i,Beq[i]);
	}
			
	num_linear_con = SDBIO_ndof;
	
	// extra constraints for simulation of FES
	num_elem=0;
	num_elem2=0;
	for (mus_index=0;mus_index<nmus;mus_index++)
	{
		if (bind_elements[mus_index]==1)
		{
			for (elem_index=0;elem_index<nelem_mus[mus_index]-1;elem_index++)
			{
				Aeq[num_linear_con][num_elem]=flen[num_elem+1];
				Aeq[num_linear_con][num_elem+1]=-flen[num_elem];
				Beq[num_linear_con]=flen[num_elem+1]*fpassive[num_elem]-flen[num_elem]*fpassive[num_elem+1];
//                fprintf(logfile,"Beq of constraint %i=%f\n",num_linear_con,Beq[num_linear_con]);
				num_elem++;
				num_linear_con++;
			}
		}
		num_elem=num_elem2+nelem_mus[mus_index];
		num_elem2=num_elem;
	}

	// extra constraints for simulation of cuffs
	num_elem=0;
	num_elem2=0;
	for (mus_index=0;mus_index<nmus-1;mus_index++)
	{
		num_elem2=num_elem+nelem_mus[mus_index];
		if (bind_muscles[mus_index]>0)
		{
			for (n=mus_index+1;n<nmus;n++)
			{	
				if (bind_muscles[n]==bind_muscles[mus_index])
				{
//					fprintf(logfile,"Bind %i with %i=%f\n",mus_index,n,bind_muscles[n]);
//					fprintf(logfile,"first elem: %i, second elem: %i\n",num_elem,num_elem2);
					Aeq[num_linear_con][num_elem]=flen[num_elem2];
					Aeq[num_linear_con][num_elem2]=-flen[num_elem];
					Beq[num_linear_con]=flen[num_elem2]*fpassive[num_elem]-flen[num_elem]*fpassive[num_elem2];
					num_linear_con++;
					break;
				}
				num_elem2=num_elem2+nelem_mus[n];
			}
		}
		num_elem=num_elem+nelem_mus[mus_index];
		num_elem2=num_elem; 
	}
	
	counter=0;
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
//	double howmuchfb = 0;  // how much feedback?
//	double extra_act;
	// stiff tendon approximation
	
	for (i=0;i<SDBIO_nmuscles;i++) {
		if (opt_success) 
		{	
			exc[i] = (x[i]-fpassive[i])/flen[i];	
			muscle_act[i] = exc[i]; 
		}
		else exc[i] = muscle_act[i];
//		howmuchfb = howmuchfb + pow(exc[i],2);
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
 
void objs(double *f,double *x, double max_act[], double min_act[])
{
	int i;
	double est_act;
		
   *f=0;
   for (i=0;i<SDBIO_nmuscles;i++)
	{
		if (Fmax[i]-Fmin[i]< VERY_SMALL)
			est_act = min_act[i];
		else
			est_act = min_act[i] + (max_act[i]-min_act[i])*((x[i]-Fmin[i])/(Fmax[i]-Fmin[i]));
		*f=*f+pow(est_act,2);
   }
//   fprintf(invlogfile,"objective function: %f\n",f[0]);	
   return;
}
          
/************************************************************************
	CONS: this routine calculates the value of the nonlinear inequality constraint
************************************************************************/

void cons(c,x)
double *c,*x;
{
	int i,k;
	double phi, theta;
    double aphi=0.6728; //38.55 degrees
    double atheta=0.7744; //44.37 degrees
	double body_force_vector[3],nforce[3],force[3];
//	double force_vector[3];

	*c = 0;
	
//  1 non-linear inequality:
//  glenohumeral constraint equation: the net reaction force at the glenohumeral joint needs to be directed into the glenoid 
		
	for (i=0; i<3; i++) force[i] = 0;
	
	//muscle forces
	for (k=0; k<SDBIO_nmuscles; k++)
	{
		for (i=0; i<3; i++)
			force[i] = force[i]+glenoid_fvectors[i][k]*x[k];
			
//		fprintf(invlogfile,"muscle %i: GHx: %f, GHy: %f, GHz: %f, force: %f\n",k,glenoid_fvectors[0][k],glenoid_fvectors[1][k],glenoid_fvectors[2][k],x[k]);	
	}


	// add the external force
/*	external_force(force_vector);
	sdtrans(-1,force_vector,6,body_force_vector);
	for (i=0; i<3; i++)
		force[i] = force[i]+body_force_vector[i]; */
	
	normalize_vector(force, nforce);
			
	/* calculate position of glenoid cavity */
	theta = asin(-nforce[1]);
	if (sqrt(nforce[0]*nforce[0]+nforce[2]*nforce[2])< VERY_SMALL)
		phi = 0.0;
	else
		phi = asin(nforce[2]/sqrt(nforce[0]*nforce[0]+nforce[2]*nforce[2]));

	*c=pow((theta/atheta),2)+pow((phi/aphi),2) - 1;
//	fprintf(invlogfile,"Fx: %f, Fy: %f, Fz: %f\n",force[0],force[1],force[2]);	
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
 double body_force_vector[3];
// double force_vector[3] = {0,-20,0};
// double hand_vector[3] = {0.0063,-0.1072,-0.0583};
 double P[5],I[5],D[5];

/* Clear status and increment function call counter */
 SDBIO_nstder++;
  
/* register new state for SD/FAST */
 sdstate(t, state, state+SDBIO_ndof);

 for (i=0;i<SDBIO_ndof;i++){
     q[i] = state[i];
     qdot[i] = state[i+SDBIO_ndof];
 }
 
/* apply user motion */
  for (i=0; i<SDBIO_ndof; i++) {
	sdprespos(i+7, 0, ref_angle[i]);
    sdpresvel(i+7, 0, ref_vel[i]);
    sdpresacc(i+7, 0, ref_acc[i]);
  }
  
 /* apply force to end of forearm (where the radio-carpal joint would be)  */
// sdtrans(-1,force_vector,11,body_force_vector);
// sdpointf(11,hand_vector,body_force_vector);  
  
 // calculate required torques
  sdcomptrq(qdot,tau); // torques from prescribed kinematics
  
//  for (i=0;i<MAXDOF;i++) fprintf(logfile,"torque %i: %f\n",i,tau[i]);
  
  P[0]=10;
  P[1]=30;
  P[2]=10;
  P[3]=18;
  P[4]=1;
  
  I[0]=0.001;
  I[1]=0.005;
  I[2]=0.001;
  I[3]=0.001;
  I[4]=0.000;
  
  D[0]=1;
  D[1]=1;
  D[2]=1;
  D[3]=1;
  D[4]=0.5;
    
  // torque correction
  for (i=0; i<SDBIO_ndof; i++) {
	cumm_error[i] = cumm_error[i] + ref_angle[i] - act_angle[i];  //approximation of integral part of PID
    tau_corr[i] = P[i]*(ref_angle[i] - act_angle[i]) + D[i]*(ref_vel[i] - act_vel[i]) + I[i]*(cumm_error[i]);
	SDBIO_joint[i].torque = tau[i]+tau_corr[i];
//	SDBIO_joint[i].torque = tau_corr[i];
//	SDBIO_joint[i].torque = tau[i];
	} 
 
//  for (i=0;i<SDBIO_ndof;i++) fprintf(invlogfile,"torque %i: %f\n",i,SDBIO_joint[i].torque);
  
/* Compute SD state derivatives: accelerations and velocities for generalized coordinates */

 sdderiv(dstate, dstate+SDBIO_ndof);
 	
/* Check that constraint errors are below tol.
  Although there are here no constraint, this checking should always
  be done by the user when using the Generalized Analysis Routine. */
  
}

/****************************************************************************************
      SDBIO_initcond_inverse:  Sets initial conditions q, qdot, act, and Lce for inverse dynamic model
*****************************************************************************************/
void SDBIO_initcond_inverse(double *t, double q[], double qdot[], double ref_angle[], double ref_vel[], double ref_acc[], double min_act[])
{

 int i,status;
 double dstate[MAXSTA],param[MAXCON];
  
  
 invlogfile = fopen("inverse_log.txt","w");
  
/* set initial q and qdot: */

 for (i=0; i<SDBIO_ndof; i++) {
   SDBIO_state[i] = q[i];
   SDBIO_state[i+SDBIO_ndof] = qdot[i];
 }

/* set initial muscle activations: */
 for (i=0; i<SDBIO_nmuscles; i++) muscle_act[i] = min_act[i];
 
 for (i=0;i<SDBIO_ndof;i++) cumm_error[i] = 0;
   
/* call deriv to set initial states */
 deriv_inverse(*t, SDBIO_state,dstate,param,ref_angle,ref_vel,ref_acc,ref_angle,ref_vel);

}

