#define S_FUNCTION_NAME das2sim
#define S_FUNCTION_LEVEL 2

/* constants that are specific to the DAS1 arm model */
#define NDOF 5		/* number of kinematic degrees of freedom */
#define NMUS 102	/* number of muscles */
#define NSTATES 214	/* number of system state variables = 2*NDOF+2*NMUS */

/*
 * Need to include simstruc.h for the definition of the SimStruct and
 * its associated macro definitions.
 */
#include "simstruc.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "../sdbio/sdbio.h"



/* global variables */

double initial_states[NSTATES];
int mus_model = 1;
int num_exF=0;
double gravityvec[3];

extern int SDBIO_init(char *fileprefix, char error_msg[]);
extern int deriv(double, double [], double [], double [], double [], int[]);
extern void SDBIO_initcond(double *t, double q[], double qdot[], double mus_states[]);
extern void SDBIO_getmuscleforces_simple(double q[], double F[]);
extern void SDBIO_getmuscleforces(double q[],double Lce[],double F[],double Lm[]);
extern void check_GH_stability(double q[],double *GHcheck);
extern void SDBIO_terminate();
extern void find_body(char *name, int *num);
extern void sdgetmass(int, double []); 

/*====================*
 * S-function methods *
 *====================*/

/* Function: mdlInitializeSizes ===============================================
 * Abstract:
 *    The sizes information is used by Simulink to determine the S-function
 *    block's characteristics (number of inputs, outputs, states, etc.).
 */
static void mdlInitializeSizes(SimStruct *S)
{

   FILE *biofile;
   char file[100];
   char *filename, *sfilename;
   static char error_msg[100];
   int i;
   float help;
   FILE *statesfile;
   double t = 0.0;
   int num_inputs;
   char *scap = {"scapula_r"}, *hum = {"humerus_r"}, *rad={"radius_r"}, *ulna={"ulna_r"};
   
   if (mus_model==1)
		sfilename = "ordered_states1.txt";
   if (mus_model==2)
		sfilename = "ordered_states2.txt";
		
   filename = "../model/model"; 
   strcpy(file, filename);
   strcat(file, ".bio");
   if ((biofile = fopen(file,"r")) == NULL) 
       filename = "c:/model";
   else 
       fclose(biofile);

   
   if (SDBIO_init(filename,error_msg))
   {
		ssSetErrorStatus(S,error_msg);
		return;
	}
	
    if ((statesfile = fopen(sfilename,"r")) == NULL) 
    {
		ssSetErrorStatus(S,"Could not open initial states file");
        return;
    }
    else 
    {
		for (i=0; i<NSTATES; i++) 
		{
			fscanf(statesfile, "%f", &help);
			initial_states[i] = help;
		}
		fclose(statesfile);
    } 

   	SDBIO_initcond(&t, (double *)&initial_states[0], (double *)&initial_states[NDOF], (double *)&initial_states[2*NDOF]);

	ssSetNumSFcnParams(S, 1);
	ssSetSFcnParamTunable(S,0,0);
		
	if (ssGetSFcnParamsCount(S)==1)
		num_exF = mxGetScalar(ssGetSFcnParam(S,0));
	else
	{
        /* Return if number of expected != number of actual parameters */
        ssSetErrorStatus(S, "Unexpected number of parameters. Should be one: the number of external forces.");
        return;
    }

    ssSetNumContStates(S, NSTATES);
    ssSetNumDiscStates(S, 0);

	if (num_exF>0) num_inputs=3; else num_inputs=1;

    if (!ssSetNumInputPorts(S, num_inputs)) return;
    ssSetInputPortWidth(S, 0, NMUS);
    ssSetInputPortRequiredContiguous(S, 0, true); /*direct input signal access*/
    /*
     * Set direct feedthrough flag (1=yes, 0=no).
     * A port has direct feedthrough if the input is used in either
     * the mdlOutputs or mdlGetTimeOfNextVarHit functions.
     * See matlabroot/simulink/src/sfuntmpl_directfeed.txt.
     */
    ssSetInputPortDirectFeedThrough(S, 0, 1);

	// second input: only if there are external forces
	if (num_exF>0) {
	    ssSetInputPortWidth(S, 1, 6*num_exF);
	    ssSetInputPortRequiredContiguous(S, 1, true); 
        ssSetInputPortDirectFeedThrough(S, 1, 1);
		
	    ssSetInputPortWidth(S, 2, 2*num_exF);
        ssSetInputPortDataType(S, 2, SS_INT32);
	    ssSetInputPortRequiredContiguous(S, 2, true); 
        ssSetInputPortDirectFeedThrough(S, 2, 1);
	}

    if (!ssSetNumOutputPorts(S, 4)) return;
    ssSetOutputPortWidth(S, 0, NMUS); // forces
	ssSetOutputPortWidth(S, 1, NDOF); // angles
	ssSetOutputPortWidth(S, 2, 1);  // GH stability check (ok if <1)
    ssSetOutputPortWidth(S, 3, NMUS);  // musculo-tendon lenghts

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
    
	 xC[5]  = 0;
	 xC[6]  = 0;
	 xC[7]  = 0;
	 xC[8]  = 0;
	 xC[9]  = 0; 
  }
#endif /* MDL_INITIALIZE_CONDITIONS */


/* Function: mdlOutputs =======================================================
 * Abstract:
 *    In this function, you compute the outputs of your S-function
 *    block. Generally outputs are placed in the output vector, ssGetY(S).
 */
static void mdlOutputs(SimStruct *S, int_T tid)
{
    real_T        *F  = (real_T *)ssGetOutputPortRealSignal(S,0);
    real_T        *xx  = (real_T *)ssGetOutputPortRealSignal(S,1);
    real_T        *GHcheck  = (real_T *)ssGetOutputPortRealSignal(S,2);
    real_T        *Lm  = (real_T *)ssGetOutputPortRealSignal(S,3);
    const real_T   *xC = ssGetContStates(S);
	int i;

	if (ssIsSampleHit(S, 1, tid)) {
        SDBIO_getmuscleforces((double *)&xC[0],(double *)&xC[2*NDOF],F,Lm);		/* compute muscle forces */
        check_GH_stability((double *)&xC[0],GHcheck); /* check if glenohumeral stability is maintained */
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
    const real_T   *u  = (const real_T*) ssGetInputPortSignal(S,0);
    real_T         *dx  = ssGetdX(S);
    real_T         *xC  = ssGetContStates(S);
    real_T *exF;
	int32_T *exF_bodies;
	double t;
	
	if (num_exF>0) {
		exF  = (real_T*) ssGetInputPortSignal(S,1);
		exF_bodies  = (int32_T*) ssGetInputPortSignal(S,2);
	} 

	t = ssGetT(S);
    if (deriv(t,xC,dx,(double *)u,(double *)exF, (int *)exF_bodies))
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



/**********************************************************
    PDcontroller:         calculates torques to correct for forward error
***********************************************************/ 
void PDcontroller(double q[],double qdot[], double tau_corr[])
{   

  int i;
  for (i=0; i<NDOF; i++) tau_corr[i] = 0;

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
   scapthor_force: calculates force when the scapula goes through the thorax
******************************************************************/
void scapthor_force(double e, double ve, double *F, double *K)
{

}

/****************************************************************
    user_torque: applies other joint moments
******************************************************************/
void user_torque(double t, double *q, double *qdot, double *m)
{
int i;
for (i=0; i<NDOF; i++) m[i] = 0;
}

/****************************************
      user_motion
****************************************/

void user_motion(double t) {}

/*******************************************************************
       user_joint_sq: applies passive moments when joint goes outside limits
*****************************************************************/
void user_joint_sq(double dof, double upperlimit, double lowerlimit, double vel, double *moment) 
{

   double a = 1000;

   if (dof >= upperlimit) 
               *moment = -a * (dof - upperlimit) * (dof - upperlimit);
   else if (dof<=lowerlimit)
               *moment = a * (dof - lowerlimit) * (dof - lowerlimit);
   else
               *moment = 0;
}

/*=============================*
 * Required S-function trailer *
 *=============================*/

#ifdef  MATLAB_MEX_FILE    /* Is this file being compiled as a MEX-file? */
#include "simulink.c"      /* MEX-file interface mechanism */
#else
#include "cg_sfun.h"       /* Code generation registration function */
#endif
