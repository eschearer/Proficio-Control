#define S_FUNCTION_NAME das2sim_inverse
#define S_FUNCTION_LEVEL 2

/* constants that are specific to the DAS2 arm model */
#define NDOF 5		/* number of kinematic degrees of freedom */
#define NMUS 102	/* number of muscles */
#define NSTATES 10	/* number of system state variables = 2*NDOF*/

/*
 * Need to include simstruc.h for the definition of the SimStruct and
 * its associated macro definitions.
 */
#include "simstruc.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "../../sdbio/sdbio.h"
#include "../../sdbio/f2c.h"
#include "../../sdbio/cfsqpusr.h"


/* global variables */

double initial_states[NSTATES];
double Fmin[NMUS]={0};
double Fmax[NMUS]={1};
double fpassive[NMUS]={0};
double flen[NMUS]={1}; 
double muscle_act[NMUS]={0};
double Aeq[MAXLINCON][NMUS]={0};
double Beq[NMUS]={0};
double glenoid_fvectors[3][NMUS]={0};
double cumm_error[NDOF]={0};
double elem_max_force[NMUS]={1};
double elem_min_force[NMUS]={0};

extern SDBIO_muscletype SDBIO_muscle[MAXMUS];
extern int SDBIO_ncon;                 /* Number of kinematic constraints */
extern SDBIO_jointtype SDBIO_joint[MAXDOF];       /* define array of joints  */
extern double SDBIO_state[MAXSTA];     /* Array containing kinematic and muscle states */
extern FILE *logfile;
int mus_model=1;
int num_exF=0;
		
void get_muscle_exc(double q[], double mexc[]);
int deriv_inverse(double, double [], double [], double [], double [], double [], double [], double []);
void SDBIO_initcond_inverse(double q[], double qdot[]);
void objs();
void cons();

extern double musgeo(SDBIO_muscletype *m, double q[], double lq[]);
extern int SDBIO_init(char *fileprefix, char error_msg[]);
extern double  Force_LengthCE(SDBIO_muscletype *m, double Lce);
extern double  Force_LengthPEE(SDBIO_muscletype *m, double Lce);
extern double  Force_LengthSEE(SDBIO_muscletype *m, double Lsee);
extern double  Force_VelCE(SDBIO_muscletype *m, double Fce, double Lce, double Act);
extern double  musmod(SDBIO_muscletype *m, double Lce, double act, double state[], int flag);
extern double  musmod_DSEM(SDBIO_muscletype *m, double Lce, double act, double state[], int flag);
extern double calc_pennation(double Lce, double Lceopt, double pennopt);
extern void SDBIO_terminate();
extern void get_force_vector(SDBIO_muscletype *m, double q[], double nGHforce_vec[]);
extern double normalize_vector(double vector[], double norm_vector[]);
extern void SDBIO_getmuscleforces_simple(double q[], double F[]);
extern void check_GH_stability(double q[],double *GHcheck);


// SDFAST routines
extern void sdderiv(double oqdot[2],double oudot[2]);
extern void sdstate(double timein,double qin[5],double uin[5]);
extern void sdprespos(int joint,int axis,double prval);
extern void sdpresvel(int joint,int axis,double prval);
extern void sdpresacc(int joint,int axis,double prval);
extern void sdcomptrq(double udotin[5],double trqout[5]);


/* Function: mdlInitializeSizes ===============================================
 * Abstract:
 *    The sizes information is used by Simulink to determine the S-function
 *    block's characteristics (number of inputs, outputs, states, etc.).
 */
static void mdlInitializeSizes(SimStruct *S)
{

   FILE *biofile;
   char file[100];
   char *filename, *sfilename; /* so we will use dasn_info and dasn.bio */
   static char error_msg[100];
   FILE *statesfile;
   int i;
   float help;
   
   if (mus_model==1)
		sfilename = "ordered_states1.txt";
   if (mus_model==2)
		sfilename = "ordered_states2.txt";

   filename = "../model/model"; 
   strcpy(file, filename);
   strcat(file, ".bio");
   if ((biofile = fopen(file,"r")) == NULL) 
   filename = "a:/model";
   else 
   fclose(biofile);

	if (SDBIO_init(filename,error_msg))
	{
		ssSetErrorStatus(S,error_msg);
		return;
	}		

   /* initial state values */
    if ((statesfile = fopen(sfilename,"r")) == NULL) 
    {
		ssSetErrorStatus(S,"Could not open initial states file");
        return;
    }
    else 
    {
		for (i=0; i<NDOF; i++) 
		{
			fscanf(statesfile, "%f", &help);
			initial_states[i] = help;
		}
		fclose(statesfile);
    } 
	
	initial_states[5]  = 0;
    initial_states[6]  = 0;
    initial_states[7]  = 0;
    initial_states[8]  = 0;
    initial_states[9]  = 0;
	
	SDBIO_initcond_inverse((double *)&initial_states[0], (double *)&initial_states[NDOF]);

    ssSetNumSFcnParams(S, 0);  /* Number of expected parameters */
    if (ssGetNumSFcnParams(S) != ssGetSFcnParamsCount(S)) {
        /* Return if number of expected != number of actual parameters */
        return;
    }

    ssSetNumContStates(S, NSTATES);
    ssSetNumDiscStates(S, 0);

    if (!ssSetNumInputPorts(S, 1)) return;
    ssSetInputPortWidth(S, 0, 5*NDOF);
    ssSetInputPortRequiredContiguous(S, 0, true); /*direct input signal access*/
    /*
     * Set direct feedthrough flag (1=yes, 0=no).
     * A port has direct feedthrough if the input is used in either
     * the mdlOutputs or mdlGetTimeOfNextVarHit functions.
     * See matlabroot/simulink/src/sfuntmpl_directfeed.txt.
     */
    ssSetInputPortDirectFeedThrough(S, 0, 1);

    if (!ssSetNumOutputPorts(S, 4)) return;
	ssSetOutputPortWidth(S, 0, NMUS);
	ssSetOutputPortWidth(S, 1, NDOF);
	ssSetOutputPortWidth(S, 2, 1);
	ssSetOutputPortWidth(S, 3, NMUS);

    ssSetNumSampleTimes(S, 2);
    ssSetNumRWork(S, 0);
    ssSetNumIWork(S, 0);
    ssSetNumPWork(S, 0);
    ssSetNumModes(S, 0);
    ssSetNumNonsampledZCs(S, 0);

    /* Take care when specifying exception free code - see sfuntmpl_doc.c */
    ssSetOptions(S, (SS_OPTION_EXCEPTION_FREE_CODE |
                     SS_OPTION_USE_TLC_WITH_ACCELERATOR |
		     SS_OPTION_WORKS_WITH_CODE_REUSE));
			 
}



/* Function: mdlInitializeSampleTimes =========================================
 * Abstract:
 *    This function is used to specify the sample time(s) for your
 *    S-function. You must register the same number of sample times as
 *    specified in ssSetNumSampleTimes.
 */
static void mdlInitializeSampleTimes(SimStruct *S)
{
    ssSetSampleTime(S, 0, CONTINUOUS_SAMPLE_TIME);
    ssSetOffsetTime(S, 0, 0.0);
	ssSetSampleTime(S, 1, 0.02);
    ssSetOffsetTime(S, 1, 0.0);

}


#define MDL_INITIALIZE_CONDITIONS   /* Change to #undef to remove function */
#if defined(MDL_INITIALIZE_CONDITIONS)
  /* Function: mdlInitializeConditions ========================================
   * Abstract:
   *    In this function, you should initialize the continuous and discrete
   *    states for your S-function block.  The initial states are placed
   *    in the state vector, ssGetContStates(S) or ssGetRealDiscStates(S).
   *    You can also perform any other initialization activities that your
   *    S-function may require. Note, this routine will be called at the
   *    start of simulation and if it is present in an enabled subsystem
   *    configured to reset states, it will be call when the enabled subsystem
   *    restarts execution to reset the states.
   */
  static void mdlInitializeConditions(SimStruct *S)
  {
		real_T *xC   = ssGetContStates(S);
		int i;

		for (i=0; i<NSTATES; i++) 
			xC[i] = initial_states[i];
  }
#endif /* MDL_INITIALIZE_CONDITIONS */



/* Function: mdlOutputs =======================================================
 * Abstract:
 *    In this function, you compute the outputs of your S-function
 *    block. Generally outputs are placed in the output vector, ssGetY(S).
 */
static void mdlOutputs(SimStruct *S, int_T tid)
{
    real_T        *mexc  = (real_T *)ssGetOutputPortRealSignal(S,0);
    real_T        *xx  = (real_T *)ssGetOutputPortRealSignal(S,1);
    real_T        *GHcheck  = (real_T *)ssGetOutputPortRealSignal(S,2);
    real_T        *F  = (real_T *)ssGetOutputPortRealSignal(S,3);
    const real_T  *xC = ssGetContStates(S);
	int i;

	if (ssIsSampleHit(S, 1, tid)) {		
		get_muscle_exc((double *)&xC[0],mexc);		/* compute muscle excitations */
        check_GH_stability((double *)&xC[0],GHcheck); /* check if glenohumeral stability is maintained */
        SDBIO_getmuscleforces_simple((double *)&xC[0],F);		/* compute muscle forces */
	}
	
	for (i=0; i<NDOF; i++) xx[i] = xC[i]; /* write states to xx */
	
}



#define MDL_DERIVATIVES  /* Change to #undef to remove function */
#if defined(MDL_DERIVATIVES)
  /* Function: mdlDerivatives =================================================
   * Abstract:
   *    In this function, you compute the S-function block's derivatives.
   *    The derivatives are placed in the derivative vector, ssGetdX(S).
   */
  static void mdlDerivatives(SimStruct *S)
  {
    const real_T   *kinem  = (const real_T*) ssGetInputPortSignal(S,0);
    real_T         *dx  = ssGetdX(S);
    real_T         *xC  = ssGetContStates(S);
	double t;
	
	t = ssGetT(S);

    if (deriv_inverse(t,xC,dx,(double *)&kinem[0],(double *)&kinem[NDOF],(double *)&kinem[2*NDOF],(double *)&kinem[3*NDOF],(double *)&kinem[4*NDOF]))
    {
		ssSetErrorStatus(S,"Error in deriv: constraint errors are above tolerance");
        return;
     }  
  }
#endif /* MDL_DERIVATIVES */ 


/* Function: mdlTerminate =====================================================
 * Abstract:
 *    In this function, you should perform any actions that are necessary
 *    at the termination of a simulation.  For example, if memory was
 *    allocated in mdlStart, this is the place to free it.
 */
static void mdlTerminate(SimStruct *S)
{
	SDBIO_terminate();
}



/*********************************************************
     user_grf:   defines ground reaction force 
*********************************************************/
void user_grf(char *name, int grfpoint, double *p, double *v, double *f)
{
	f[0] = 0; f[1] = 0; f[2] = 0;	/* always return zero */
}

/************************************************************
     user_force:  defines external forces to be applied to system
*******************************************************************/
void user_force(char *name,double t,double *p,double *v,double *f)
{
	f[0] = 0; f[1] = 0; f[2] = 0;	/* always return zero */
}

/****************************************************************
    user_joint: applies passive moments when joint goes outside limits
******************************************************************/
void user_joint(char *name, double e, double ve, double *m)
{
    double a = 5000;
    double b = 0.1;
//    *m = -a * e - b * ve;    /* passive moment */
	if (e < 0)
		if (ve < 0)
			*m = a * e * e * (1 + b * ve * ve);
		else
			*m = a * e * e * (1 - b * ve * ve);
	else
		if (ve < 0)
			*m = -a * e * e * (1 + b * ve * ve);
		else
			*m = -a * e * e * (1 - b * ve * ve);

}

/****************************************************************
    user_torque: applies other joint moments
******************************************************************/
void user_torque(double t, double *q, double *qdot, double *m)
{
int i;
for (i=0; i<NDOF; i++) m[i] = 0;
}

/****************************************************************
   scapthor_force: calculates force when the scapula goes through the thorax
******************************************************************/
void scapthor_force(double e, double ve, double *F, double *K)
{
    double a,b; 
    a = K[0];
	b = K[1];

	if (e < 0)
		if (ve < 0)
			*F = a * e * e * (1 + b * ve * ve);
		else
			*F = a * e * e * (1 - b * ve * ve);
	else
		if (ve < 0)
			*F = -a * e * e * (1 + b * ve * ve);
		else
			*F = -a * e * e * (1 - b * ve * ve);
}

/*********************************************************************************
       deriv_inverse:          returns derivatives for all state variables for inverse dynamic model 
**********************************************************************************/
int deriv_inverse(double t, double state[], double dstate[],
         double ref_angle[], double ref_vel[], double ref_acc[], double act_angle[], double act_vel[]) {
 int i;
 double q[MAXDOF], qdot[MAXDOF], tau[MAXDOF], tau_corr[MAXDOF];
// double errs[MAXCON];  /* Constraint error array */
 double P[NDOF],I[NDOF],D[NDOF];
  
/* register new state for SD/FAST */
 sdstate(t, state, state+NDOF);

 for (i=0;i<NDOF;i++){
     q[i] = state[i];
     qdot[i] = state[i+NDOF];
 }
 
/* apply user motion */
  for (i=0; i<NDOF; i++) {
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
  
  P[0]=10;
  P[1]=15;
  P[2]=10;
  P[3]=10;
  P[4]=5;
  
  I[0]=0.015;
  I[1]=0.015;
  I[2]=0.010;
  I[3]=0.015;
  I[4]=0.005;
  
  D[0]=0.20;
  D[1]=0.30;
  D[2]=0.20;
  D[3]=0.20;
  D[4]=0.10;
    
  // torque correction
  for (i=0; i<NDOF; i++) {
	cumm_error[i] = cumm_error[i] + ref_angle[i] - act_angle[i];  //approximation of integral part of PID
    tau_corr[i] = P[i]*(ref_angle[i] - act_angle[i]) + D[i]*(ref_vel[i] - act_vel[i]) + I[i]*(cumm_error[i]);
	SDBIO_joint[i].torque = tau[i]+tau_corr[i];
//	SDBIO_joint[i].torque = tau[i];
	} 
   
/* Compute SD state derivatives: accelerations and velocities for generalized coordinates */

    sdderiv(dstate, dstate+NDOF);
//    fprintf(logfile,"dstate: %f %f %f %f\n",dstate[0],dstate[1],dstate[2],dstate[3]);
 
 /* Check that constraint errors are below tol.
	  Although there are here no constraint, this checking should always
	  be done by the user when using the Generalized Analysis Routine. */

/*	 if (SDBIO_ncon == 0) return 0;

	 sdverr(errs);                     // Velocity constraint errors 
	 for (i=0; i<SDBIO_ncon; i++) {
	    if (fabs(errs[i]) > CONSTRAINT_TOL) return 1;
	 }
			   
	 sdperr(errs);                     //  Position constraint errors 
	 for (i=0; i<SDBIO_ncon; i++) {
	    if (fabs(errs[i]) > CONSTRAINT_TOL) return 1;
	 } */
			   
	 return 0;
 	  
}

/****************************************************************************************
      SDBIO_initcond_inverse:  Sets initial conditions q, qdot, act, and Lce for inverse dynamic model
*****************************************************************************************/
void SDBIO_initcond_inverse(double q[], double qdot[])
{

 int i;
 double dstate[MAXSTA];
 double t=0;
 SDBIO_muscletype *m;
 
/* set initial q and qdot: */

 for (i=0; i<NDOF; i++) {
   SDBIO_state[i] = q[i];
   SDBIO_state[i+NDOF] = qdot[i];
 }
   
/* set initial muscle activations: */
// for (i=0; i<NMUS; i++) muscle_act[i] = actmin;  // muscle activation for inverse muscle model
 for (i=0; i<NMUS; i++) {
	m = &(SDBIO_muscle[i]);
	muscle_act[i] = 0;  // muscle activation for inverse muscle model
	m->F = 0;
 }
 
 for (i=0;i<NDOF;i++) cumm_error[i] = 0;
   
/* call deriv to set initial states */
 deriv_inverse(t,SDBIO_state,dstate,q,qdot,qdot,q,qdot);
}

/**********************************************************************************
        get_muscle_exc:  calculates muscle excitations required for inverse dynamic simulation
**********************************************************************************/
void get_muscle_exc(double q[], double mexc[])
{
	double Lq[MAXDOF],GHfvector[3];
	double fiber_length, mus_height,mus_width,penn_angle;
	SDBIO_muscletype *m;
	int i,j,k,mus_index,elem_index,num_elem,num_elem2,num_linear_con;
	int nparam,nineqn,nineq,neqn,neq,nf,mode,iprint,miter,ncsrl,ncsrn,nfsr,mesh_pts[1],inform;
	double bigbnd,eps,epseqn,epscon,udelta;
    double x[NMUS],bl[NMUS],bu[NMUS],f[1],g[NDOF],lambda[NDOF+NMUS+1];
	double force_fraction_max[24],force_fraction_min[24];
    void *cd;
	double Lcen,Lce0,Lcesh,Lopt,Lm,pep1,pep2;
	double PEsh   =  4.00; // parallel elastic element, shape parameter
    double PExm  = 0.4; // parallel elastic element, max. extension
	pep1 = 1 / (exp(PEsh) - 1.0);

	// temporarily here: will be inputs to the routine
	int elem_per_mus[24] = {4, 7, 4, 3, 6, 3, 4, 4, 11, 1, 2, 4, 6, 6, 2, 5, 7, 3, 1, 1, 5, 3, 5, 5};
	//  0<force_fraction<1 : fraction of force the muscle can produce (simulation of paralysis or denervation)
	//  0<force_fraction<1 : fraction of force the muscle can produce (simulation of paralysis or denervation)

	// if bind_elements == 1 --> all elements of that muscle have the same activation (simulation of FES)
	int bind_elements[24] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	// if bind_muscles ~= 0 --> the muscles with the same bind_muscles number have the same activation (simulation of nerve cuffs)
	int bind_muscles[24] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

	for (i=0;i<24;i++) {
		force_fraction_max[i]=1;	
		force_fraction_min[i]=0;	
	}

    mode=100;
    iprint=0;
    miter=1000;  
    bigbnd=1.e21;
	eps=0.0011;
    epseqn=0.001;
    epscon=0.001;
    udelta=0.0;
    nparam=NMUS;
    nf=1;
    ncsrl=ncsrn=nfsr=mesh_pts[0]=0;
			
	/*  nineqn: # nonlinear inequality constraints
		nineq : # nonlinear + linear inequality constraints
		neqn  : # nonlinear equality constraints
		neq  : # nonlinear + linear equality constraints */
	nineqn=1;
	nineq=1;
	neqn=0;
	neq=NDOF;
			
	// make sure that if a cuff is applied to a muscle, 
	// it is also under FES stimulation (all elements have the same activation)
	for (i=0;i<24;i++)
		if (bind_muscles[i]>0)
			bind_elements[i]=1;

	// find maximum and minimum force for each muscle element
	mus_index = 0;
	elem_index = 0;
	for (i=0; i<NMUS; i++) {
		if (elem_index>=elem_per_mus[mus_index])
		// calculate index for maximum force fraction max_force
		{
			mus_index++;
			elem_index=0;
		}
		elem_max_force[i] = force_fraction_max[mus_index];
		elem_min_force[i] = force_fraction_min[mus_index];
//		fprintf(logfile,"min=%f, max=%f, mus_index=%d, elem_index=%d, i=%d\n",force_fraction_min[mus_index],force_fraction_max[mus_index],mus_index,elem_index,i);
		elem_index++;
	}

	for (i=0; i<NMUS; i++) {
        m = &(SDBIO_muscle[i]);
	   	   
		// get muscle GH vectors
	    get_force_vector(m, q, GHfvector);
	   	   
	    // store it in global matrix glenoid_fvectors
	    for (j=0; j<3; j++)
	    {
			glenoid_fvectors[j][i] = GHfvector[j];
//		    fprintf(invlogfile,"%15s GHx:   %f GHy:   %f GHz:   %f\n",m->name,GHfvector[0],GHfvector[1],GHfvector[2]);	
		}
		
	    // get muscle length and moment arms
        m->lm = musgeo(m, q, Lq);  
 	   
        // store moment arms in matrix A		
        for (j=0; j < m->nmusdof; j++) {
               k = m->musdof[j];
			   Aeq[k][i] = Lq[k];
//			   fprintf(logfile,"%15s: Aeq[%d][%d] = %f\n",m->name,k,i,Aeq[k][i]); 
	    }
			   
		// stiff tendon approximation	   
		mus_height = m->lm - m->lslack;   			/* the muscle "height" equals Lce for unipennate muscles */
		mus_width = m->lceopt * sin(m->pennopt);     /* we assume that this is constant */
		if (mus_height<0) fiber_length = mus_width;
		else fiber_length  = sqrt(mus_width*mus_width + mus_height*mus_height);	  
		
		/* pennation angle: between 0 and 90 degrees */
		penn_angle = calc_pennation(fiber_length,m->lceopt,m->pennopt);

		if (mus_model==1) {
		    flen[i] = Force_LengthCE(m, fiber_length)/m->fmax; 	
			fpassive[i] = Force_LengthPEE(m, fiber_length); 		
		} 
		else if (mus_model==2) {
			Lopt = m->lceopt*cos(m->pennopt) + m->lslack;
			Lm = m->lm / Lopt;
			Lcen = fiber_length / Lopt;
			Lce0 = m->lceopt / Lopt;
			Lcesh = 0.3 * Lce0; 
			flen[i] = exp(-((Lcen - Lce0)/Lcesh)*((Lcen - Lce0)/Lcesh));			
		    flen[i] = cos(penn_angle)*flen[i];
			pep2  =  exp((Lm-1)*(PEsh/PExm));          
			fpassive[i] = pep1 * (pep2 - 1.0) * m->fmax;
			if (fpassive[i]<0) fpassive[i]=0.0;
//			fpassive[i]=0;
		} 
				
		bl[i]=fpassive[i] + flen[i]*elem_min_force[i]*m->fmax;
		Fmin[i] = bl[i];
		bu[i]=fpassive[i] + flen[i]*elem_max_force[i]*m->fmax; 
		Fmax[i] = bu[i];
		x[i]=fpassive[i]+flen[i]*muscle_act[i]*m->fmax; 	
//		fprintf(logfile,"%15s: Lopt=%f lm = %f fiber length = %f fpassive=%f flen=%f penn angle=%f\n",m->name,Lopt,m->lm,fiber_length, fpassive[i],flen[i],penn_angle); 	
//		fprintf(logfile,"%15s: bl = %f bu = %f\n",m->name,bl[i],bu[i]); 	
    }

    // store joint moments in vector B
    for (i=0;i<NDOF;i++) {
		Beq[i]=SDBIO_joint[i].torque;
//		fprintf(logfile,"Beq[%d]=%f\n",i,Beq[i]);
	}
	num_linear_con = NDOF;
	
	// extra constraints for simulation of FES
/*	num_elem=0;
	num_elem2=0;
	for (mus_index=0;mus_index<NMUS;mus_index++)
	{
		if (bind_elements[mus_index]==1)
		{
			for (elem_index=0;elem_index<elem_per_mus[mus_index]-1;elem_index++)
			{
				Aeq[num_linear_con][num_elem]=flen[num_elem+1];
				Aeq[num_linear_con][num_elem+1]=-flen[num_elem];
				Beq[num_linear_con]=flen[num_elem+1]*fpassive[num_elem]-flen[num_elem]*fpassive[num_elem+1];
//                fprintf(logfile,"Beq of constraint %i=%f\n",num_linear_con,Beq[num_linear_con]);
				num_elem++;
				num_linear_con++;
			}
		}
		num_elem=num_elem2+elem_per_mus[mus_index];
		num_elem2=num_elem;
	}

	// extra constraints for simulation of cuffs
	num_elem=0;
	num_elem2=0;
	for (mus_index=0;mus_index<NMUS-1;mus_index++)
	{
		num_elem2=num_elem+elem_per_mus[mus_index];
		if (bind_muscles[mus_index]>0)
		{
			for (n=mus_index+1;n<NMUS;n++)
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
				num_elem2=num_elem2+elem_per_mus[n];
			}
		}
		num_elem=num_elem+elem_per_mus[mus_index];
		num_elem2=num_elem; 
	}

	neq = num_linear_con; */
	
/*	fprintf(logfile,"min:\n");
	for (i=0;i<NMUS;i++) fprintf(logfile,"%f ",bl[i]);
	fprintf(logfile,"\nmax:\n");
	for (i=0;i<NMUS;i++) fprintf(logfile,"%f ",bu[i]);
	fprintf(logfile,"\ninitial:\n");
	for (i=0;i<NMUS;i++) fprintf(logfile,"%f ",x[i]);
	fprintf(logfile,"\n\n");	
	fprintf(logfile,"Aeq:\n");
	for (i=0;i<NDOF;i++)
	{
		for (j=0;j<NMUS;j++)
			fprintf(logfile,"%3.5f ",Aeq[i][j]);
		fprintf(logfile,"\n");
	}
	fprintf(logfile,"Beq:\n");
	for (i=0;i<NDOF;i++)
		fprintf(logfile,"%3.5f\n",Beq[i]); */
	
	// perform optimisation
	cfsqp(nparam,nf,nfsr,nineqn,nineq,neqn,neq,ncsrl,ncsrn,mesh_pts,
     mode,iprint,miter,&inform,bigbnd,eps,epseqn,udelta,bl,bu,x,
     f,g,lambda,objs,cons,grobfd,grcnfd,cd);
	 
//	 fprintf(logfile,"\noptimisation output: %d\n",inform);
	 
    // stiff tendon approximation
	for (i=0;i<NMUS;i++) {
		m = &(SDBIO_muscle[i]);
		if (!inform) {	
			mexc[i] = (x[i]-fpassive[i])/(flen[i]*m->fmax);	
			m->F = x[i];
			muscle_act[i] = mexc[i]; 
		}
		else 
			mexc[i] = muscle_act[i];
	}	
	
}

/***************************************************************
	OBJS: this routine calculates the value of the objective function
****************************************************************/
 
void objs(nparam,j,x,fj,cd)
int nparam,j;
double *x,*fj;
void *cd;
{
	int i;
	double est_act;
	
	*fj=0;
	
    for (i=0;i<NMUS;i++)
	{
		if (Fmax[i]-Fmin[i]< VERY_SMALL)
			est_act = elem_min_force[i];
		else
			est_act = elem_min_force[i] + (elem_max_force[i]-elem_min_force[i])*((x[i]-Fmin[i])/(Fmax[i]-Fmin[i]));
		*fj=*fj+pow(est_act,2);		
    }
//	fprintf(logfile,"%f\n",*fj);
}
          
/***********************************************************
	CONS: this routine calculates the values of the constraints
************************************************************/

void cons(nparam,j,x,gj,cd)
int nparam,j;
double *x,*gj;
void *cd;

/*  J: Jth constraint to be computed
    order of constraints
    nineqn: # nonlinear inequality constraints
    nineq : # nonlinear + linear inequality constraints
    neqn  : # nonlinear equality constraints
    neq   : # nonlinear + linear equality constraints */

{
	int i,k;
	double phi, theta;
    double aphi=0.6728; //38.55 degrees
    double atheta=0.7744; //44.37 degrees
//	double body_force_vector[3];
	double nforce[3],force[3];
//	double force_vector[3];

	*gj=0;
	
//  1 non-linear inequality:
//  glenohumeral constraint equation: the net reaction force at the glenohumeral joint needs to be directed into the glenoid 
	if (j==1)
	{
		for (i=0; i<3; i++) force[i] = 0;
	
		//muscle forces
		for (k=0; k<NMUS; k++)
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

		*gj=pow((theta/atheta),2)+pow((phi/aphi),2) - 0.5;
//	fprintf(logfile,"Fx: %f, Fy: %f, Fz: %f\n",force[0],force[1],force[2]);	
		return;
	}
	
/*   linear equalities: motion equations
	Aeq*x-Beq=0
		where Aeq: moment arm matrix
			x: muscle forces vector
			Beq: joint moments vector 
*/
	
    for(i=1;i<NDOF+1;i++)
		if (j==i+1)
		{
			*gj=-Beq[i-1];
			for (k=0;k<NMUS;k++) 
				*gj=*gj+Aeq[i-1][k]*x[k];
			
		} 
//	for (k=0;k<NMUS;k++)
//		fprintf(logfile,"%f  ",x[k]);
//	fprintf(logfile,"\n");
} 

/*=============================*
 * Required S-function trailer *
 *=============================*/

#ifdef  MATLAB_MEX_FILE    /* Is this file being compiled as a MEX-file? */
#include "simulink.c"      /* MEX-file interface mechanism */
#else
#include "cg_sfun.h"       /* Code generation registration function */
#endif
