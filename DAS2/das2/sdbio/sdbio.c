/* File:        sdbio.c
 Authors:      Ton van den Bogert
               Anne Su

05/04/2000      Version 1.0 by Anne Su
10/05/2004      Version 3.0 by Ton van den Bogert
               - streamlined the code
               - replaced SDBIO_setinithgt by SDBIO_getmincontact
               (missing functionality from Version 2.0 must still be added:
                       - polynomial muscle path models
                       - VRML export
               )
12/08/2004      Version 3.1 by Ton van den Bogert
                       Removed unused code and streamlined getstick()
                       Added 1 N/m linear force term to PEE and SEE properties
01/08/2006      Version 3.2 by Ton van den Bogert
                       Added getVRML function
02/13/2006      Version 3.3 by Ton van den Bogert
                       Fixed bug that stopped contraction if muscle is *just* slack
06/28/2006 Version 3.4 by Ton van den Bogert
                       Added function SDBIO_getmuscleforces(q,Lce,F)
                       Added function SDBIO_getVRML2(q,iseg,wrldata)
06/29/2006 Version 3.5 by Ton van den Bogert
                       Added code for polynomial muscle path model
07/21/2006      Version 3.6 by Ton van den Bogert
                       Fixed bugs in SDBIO_getmuscleforces and SDBIO_getVRML2
                       SDBIO_init will now read SD/Fast info files with _info and _i extensions, report error to stdout if file does not exist.
                       All console output and error messages from sdbio.c now goes to a file sdbio.log.  Inspect this file after each run when testing.
                       PEEslack muscle property is added: PEE slack length in multiples of Lceopt.
                       Many code improvements

08/15/2006 Version 3.7 by Ton van den Bogert
			Eliminated excessive LOG file output while reading info file
			Fixed bug in read_muscle which affected polynomial path models
			

Known problems:

SDBIO generally ignores errors.  For example, if a _info file is missing, an error message is written on
sdbio.log but the simulation proceeds and produces incorrect results.  The exit() mechanism can't be used
because it kills Matlab when sdbio.c is embedded in a MEX DLL.  Possible solution: consistent passing of
error flags all the way through, and refusal to simulate when errors have occurred.

*/

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include "sdbio.h"
#include <malloc.h>


#define VERSION 3.8              /* sdbio.c release number */
#define BAUMGARTE_STAB 20.0

/*****************************************************************************/
/* Global variables for ODE solver and multibody system */

int verbose;            /* Level of output to the screen */
FILE *logfile;
int SDBIO_nstder;               /* Number of calls to state derivative function deriv() */
int SDBIO_neq;                  /* Number of state variables to integrate */
int SDBIO_nbod;                 /* Number of bodies  */
int SDBIO_ndof;                 /* Number of degrees of freedom in the tree structure */
int SDBIO_ncon;                 /* Number of kinematic constraints */
int SDBIO_njnt;                 /* Number of joints (as calculated by SD/FAST) */
int SDBIO_nactivejnt;   /* Number of active limb joints (that are described in the *.bio file) */
int SDBIO_ngrf;                 /* Number of grf elements  */
int SDBIO_nextforce;    /* Number of external contact force elements */
int SDBIO_npres;                /* Number of prescribed joints */
int SDBIO_roadmap[MAXDOF];      /* Array linking q's with body numbers  */
int SDBIO_statemap[MAXDOF][2];  /* Array linking q's with joint and axis numbers  */
double SDBIO_state[MAXSTA];     /* Array containing kinematic and muscle states
  elements 0 through (SDBIO_ndof-1) are q's; SDBIO_ndof through (2*SDBIO_ndof-1) are qdots;
  2*SDBIO_ndof through 2*SDBIO_ndof+2*SDBIO_nmuscles are the muscle states, alternating between the
  Lce and Act of each muscle in the order defined in the *.bio file */
char SDBIO_bodies[MAXDOF][NAMLEN];  /* Array of body names corresponding to body numbers */
int numder;                      /* Number of calls to deriv() in each call to SDBIO_simulate */
int SDBIO_inb[MAXDOF];           /* Array linking body numbers with parent(inb) body numbers */
double SDBIO_stepsize;           /* step size in current simulation, passed from main function */
double actmin = 0.02;                   /* the minimum level of muscle activation */
double sim_stepsize = 0.001;				/* the stepsize of the simulation */
double sim_time = 0;				/* the current time of the simulation */
extern int mus_model;                   /* the muscle model used: 1 for the 2-state model that takes velocity into account, 
												              2 for 2-state model from DSEM
												              3 for the simple 1-state (activation only) model */

extern int num_exF;

															  
/* Global variables for 2-state DSEM muscle model */
double SEsh   =  3.00; // series elastic element, shape parameter
double MVvm   = -4.50; // force/velocity, max. velocity CE
double MVml   =  1.30; // force/velocity, max. eccentric force
double MVsh   =  0.30; // force/velocity, shape parameter
double MVshl  =  0.50; // force/velocity, shape parameter (eccentric)
double MVer   =  0.50; // force/velocity, scaling maximal velocity CE
double PEsh   =  4.00; // parallel elastic element, shape parameter
double PV     =  0.10; // parallel viscous
															  
/*****************************************************************************/
/* Global variables containing muscle model information */

int SDBIO_nmuscles;                       /* number of muscles */
int SDBIO_nligaments;                     /* number of ligaments */

SDBIO_muscletype SDBIO_muscle[MAXMUS];    /* the array of all muscles */
SDBIO_muscletype musdef;                  /* the default muscle */

SDBIO_ligamenttype SDBIO_ligament[MAXLIG];  /* the array of all ligaments */
SDBIO_ligamenttype ligdef;                  /* the default ligament */

/* Global variables for constraints needed in DAS3 but not previous versions */
int conoid_constr = 0;
int scap_thor_constr = 0;
double k_scapthor[2] = {0};
double conoid_clav[3]={0};
double conoid_scap[3]={0};
double AI[3]={0};
double TS[3]={0};
double AC[3]={0};
double SC[3]={0};
int AIok[1]={1};
int TSok[1]={1};
double AIcontact[3]={0};
double TScontact[3]={0};
double AInormal[3]={0};
double TSnormal[3]={0};
double conoid_frc=0;
double AI_frc=0;
double TS_frc=0;
double conoid_length = 0;
double elcenter[3] = {0};
double elrad[3] = {0};
double gravityvec[3];

/* only in DAS2 and/or DAS3 */
int clavnum,scapnum,humnum,ulnanum,radnum;
double scapmass,hummass,ulnamass,radmass;

/*****************************************************************************/
/*  Global variables containing information about joints  */
SDBIO_jointtype SDBIO_joint[MAXDOF];       /* define array of joints  */

/*****************************************************************************/
/*   Global variables containing ground reaction force information  */
SDBIO_forcetype SDBIO_grf[MAXCNTELE], SDBIO_extforce[MAXCNTELE];     /* define array of ground reaction forces */

/*****************************************************************************/
/* Functions used in the SDBIO package
       sdvinteg.............Variable-step integrator (from sdlib)
       deriv................Returns derivatives for SD/FAST states and user states
       musprep..............preprocess some muscle properties to speed up computations
       musmod...............state equation for 3-component Hill model
       musgeo...............calculates a muscle's length and moment arms
*******************************************************************************/
void    sdvinteg(int (*deriv)(double, double [], double [], double [], int *),
                double *time, double y[], double dy[], double param[],
                double dt, double *step, int neq, double tol, double work[],
                int *err, int *which);
int     deriv(double, double [], double [], double [], double [], int[]);
void    musprep(SDBIO_muscletype *m);
double  Force_VelCE(SDBIO_muscletype *m, double Fce, double Lce, double Act);
double  Force_LengthCE(SDBIO_muscletype *m, double Lce);
double  Force_LengthPEE(SDBIO_muscletype *m, double Lce);
double  Force_LengthSEE(SDBIO_muscletype *m, double Lsee);
double  musmod(SDBIO_muscletype *m, double Lce, double act, double state[], int flag);
double  musgeo(SDBIO_muscletype *m, double q[], double lq[]);
double  liggeo(SDBIO_ligamenttype *m, double q[], double lq[]);
int    SDBIO_getbio(char *fileprefix, char error_msg[]);
int    SDBIO_getinfo(char *fileprefix, char error_msg[]);
void    grf();
void    ext_force();
void    SDBIO_getstick(double stick[]);
double  optLce(SDBIO_muscletype *m, double act);
double  isofunc(SDBIO_muscletype *m, double Lce, double act);
double user_force(char *name,double t,double p[MAXCNTPTS][3],double v[MAXCNTPTS][3], double f[][3]);
void SDBIO_terminate();

void sduperr(double t,double q[],double errs[]);

// SD-FAST routine definitions
extern void sdinit(void);
extern void sdinfo(int info[50]);
extern void sdjnt(int joint,int info[50],int tran[6]);
extern void sdstab(double velin, double posin);
extern void sdhinget(int joint,int axis,double torque);
extern void sdderiv(double oqdot[2],double oudot[2]);
extern void sdverr(double errs[2]);
extern void sdperr(double errs[2]);
extern int sdindx(int joint,int axis);
extern void sdgetgrav(double gravout[3]);

/* routines added by Dimitra Blana for implementation of inverse dynamic model, simple 1-state muscle model, and calculation of pennation angle */
void SDBIO_initcond_inverse(double *t, double q[], double qdot[],double ref_angle[], double ref_vel[], double ref_acc[]);
void SDBIO_initcond_simple(double *t, double q[], double qdot[], double act[]);
void SDBIO_getmuscleforces_simple(double q[], double F[]);
void    musmod_simple(SDBIO_muscletype *m, double act, double state[], int flag);
double calc_pennation(double Lce, double Lceopt, double pennopt);
double calc_fibervel(SDBIO_muscletype *m,double Lce);
double calc_force_vel(SDBIO_muscletype *m,double fiber_vel,double Act);
double **init_mat(int n, int m);
double normalize_vector(double vector[], double norm_vector[]);
void check_GH_stability(double q[],double *GHcheck);
double  musmod_DSEM(SDBIO_muscletype *m, double Lce, double act, double state[], int flag);
void normellips(double pt[], double norm_pt[]);
double apply_scapthor_force(double BL[],int BLok[], double BLcontact[], double n_normBLthor[]);
void mult_vec_by_3x3mat(double mat[][3], double vector[], double result[]);

/**********************************************************************************
       SDBIO_init:     Initializes global variables for SDBIO package
**********************************************************************************/
int SDBIO_init(char *fileprefix, char error_msg[]) {

       FILE *refmap;
       int info[50], jntinfo[50], slider[6];
       int i;
       char filename[100];
	   
       verbose = 0; /* initialize value for verbose level; may be changed within *.bio file */
	   sdgetgrav(gravityvec);           // gravity vector

       strcpy(filename, fileprefix);
       strcat(filename, ".log");
	   if ((logfile = fopen(filename, "w")) == NULL)
       {
			strcpy(error_msg,"Could not open log file");
			return 1;
       }
       fprintf(logfile,"Initializing SDBIO version %5.1f\n",VERSION);

/* Initialization of SD/FAST and obtain system info */
       sdinit();	   
       sdinfo(info);
       SDBIO_nbod = info[1];
       SDBIO_ndof = info[2];
       SDBIO_ncon = info[9]+info[10];
       SDBIO_njnt = info[1] + info[4];    /* # of joints = (# bodies) + (# loop joints)  */
       if (info[7] != 0) {
            fprintf(logfile,"Ball or 6DOF joints not allowed.");
			strcpy(error_msg,"Ball or 6DOF joints not allowed.");
			fclose(logfile);
			return 1;
       }

/* count the number of prescribed DOFs */
       SDBIO_npres = 0;
       for (i=0;i<SDBIO_njnt; i++) {
            sdjnt(i,jntinfo,slider);
            SDBIO_npres = SDBIO_npres + jntinfo[6];
       }

/* Get Roadmap from Info file */
       if (SDBIO_getinfo(fileprefix,error_msg))  /* get information from *_info file */
	   {
			fclose(logfile);
			return 1;
		}

/* Get biomechanical model components from .BIO file */
       if (SDBIO_getbio(fileprefix,error_msg))
	   {
			fclose(logfile);
			return 1; 
		}
					
/* Write a roadmap on ..map.out file */
       strcpy(filename, fileprefix);
       strcat(filename, "map.out");
       if ((refmap = fopen(filename,"w")) == NULL) {	   
            fprintf(logfile,"Could not create map.out file.\n");
			strcpy(error_msg,"Could not create map.out file.");
			fclose(logfile);
			return 1;
	   }
       fprintf(refmap, "User Reference Map for %s\n\n", fileprefix);
       for (i=0;i<SDBIO_nbod;i++)
            fprintf(refmap,"body %d is %s\n", i, SDBIO_bodies[i]);
       fprintf(refmap, "\n");
       /* correct only if all active joints only have one dof */
       for (i=0; i<(SDBIO_ndof - SDBIO_nactivejnt);i++)
            fprintf(refmap,"q = %d corresponds to body %d (%s)\n", i, SDBIO_roadmap[i], SDBIO_bodies[SDBIO_roadmap[i]]);
       for (i=0;i<SDBIO_nactivejnt;i++)
            fprintf(refmap, "q = %d corresponds to joint %d (%s)\n", SDBIO_joint[i].q, SDBIO_statemap[SDBIO_joint[i].q][0], SDBIO_joint[i].name);
       fprintf(refmap, "\n");
       for (i=0;i<SDBIO_nmuscles;i++)
            fprintf(refmap, "muscle %d is %s\n", i, SDBIO_muscle[i].name);
       fclose(refmap);

       for (i=0; i<SDBIO_nmuscles; i++)
            musprep(&(SDBIO_muscle[i]));            /* some parameter conversions to save time later */

/* initialize other model information */
	   if (mus_model==1) // SDBIO 2-state model
			SDBIO_neq = 2 * SDBIO_ndof + 2 * SDBIO_nmuscles; 
	   if (mus_model==2) // DSEM 2-state model
			SDBIO_neq = 2 * SDBIO_ndof + 2 * SDBIO_nmuscles; 
	   if (mus_model==3) // 1-state model
			SDBIO_neq = 2 * SDBIO_ndof + SDBIO_nmuscles; 

/* set Baumgarte parameters for user constraint stabilization in SD/Fast */
       sdstab(2*BAUMGARTE_STAB, BAUMGARTE_STAB*BAUMGARTE_STAB);

	   return 0;
}

/**********************************************************************************
       SDBIO_terminate:     Closes files and clears global variables for SDBIO package
**********************************************************************************/
void SDBIO_terminate() {
	fclose(logfile);
	}
	
/**********************************************************************************
       SDBIO_simulate: Runs a simulation for a fixed time interval
**********************************************************************************/
void SDBIO_simulate(double *t, double duration)
{
/* Run one simulation

Input:
       t.............. Time (also output)
       duration....... Duration of simulation

Working variables
       dstate....              Derivatives of system states
       vstep.........          The variable step size
       param....               Constraint tolerance array
       work[6*NEQ].... Workspace for integrator
       err........             Integrator error flag
       which.......            Additional error information returned by sdvinteg
       status.....             Constraint violation error flag (see p. R-36)
       ctol......              Constraint tolerance (not used at this time)
       tol.......                      Integration tolerance (should be read from input file at some point)
*/
       static double dstate[MAXSTA];           /* should be preserved between calls!! */
       static double vstep;                    /* should be preserved betweeb calls!! */
       double param[MAXCON];
       double work[6*MAXSTA];
       int err, which, status;
       double ctol = 0.001;
       double tol  = 0.001;

       SDBIO_stepsize = duration;

/* Put the constraint tolerance(s) in the constraint tolerance array */
   param[0] = ctol;

/* Calculate the initial derivatives dstate needed by the integrator */
//   deriv(*t, SDBIO_state, dstate, stims,0);
   vstep = duration/5; /* start with large step size, will be adjusted to satisfy tol */

/* Call of RK4 variable step integrator for interval t to t + duration */
//   sdvinteg(deriv, t, SDBIO_state, dstate, param, duration, &vstep,
//            SDBIO_neq, tol, work, &err, &which);

/* Error checks */
       if (err) {
               switch (err) {
                       case 1: /* Integration continues however normally */
                       fprintf(logfile,"\nAt time t = %fs, sdvinteg returned err = %d\n", *t, err);
                       fprintf(logfile,"Function exhibiting the 1st alleged discontinuity ");
                       fprintf(logfile,"during the interval has got index %d\n", which);
               case 2: /* Integrator is then stalled: iteration stopped. */
                       fprintf(logfile,"\nAt time t = %fs, sdvinteg returned err = %d\n", *t, err);
                       fprintf(logfile,"Index of the function exhibiting the ");
                       fprintf(logfile,"non-recoverable behavior is %d\n", which);
           case 3: /* Integrator is then stalled: iteration stopped. */
                       fprintf(logfile,"\nAt time t = %fs, sdvinteg returned err = %d\n", *t, err);
                       fprintf(logfile,"Cause: function deriv returns ");
                       fprintf(logfile,"non-zero status: %d", which);
               }
       }

}

/*******************************************************************
      SDBIO_initcond:  Sets initial conditions q, qdot, act, and Lce
*************************************************************************/
void SDBIO_initcond(double *t, double q[], double qdot[], double mus_states[])
{

	 int i;
	 double Lq[MAXDOF],dstate[MAXSTA],act[MAXMUS],Lm,mus_width,mus_height;
	 SDBIO_muscletype *m;
	 SDBIO_ligamenttype *l;

/* set initial q and qdot: */

	 for (i=0; i<SDBIO_ndof; i++) {
		SDBIO_state[i] = q[i];
		SDBIO_state[i+SDBIO_ndof] = qdot[i];
	 }

/* set initial muscle activations: */

	 for (i=0; i<SDBIO_nmuscles; i++) {
		SDBIO_state[2*SDBIO_ndof + 2 * i + 1] = mus_states[2*i+1];
		act[i] = mus_states[2*i+1];
	 }

/* set initial CE length, either calculated or explicitly defined: */
	 
	 for (i=0; i<SDBIO_nmuscles; i++)
	 {
		m = &SDBIO_muscle[i];
		if (mus_states[2*i] == 99)       /* muscle is just slack */
		{
			Lm = musgeo(m, SDBIO_state, Lq);             /* calculate muscle length */
			mus_height = Lm - m->lslack;   				 /* the muscle "height" equals Lce for unipennate muscles */
			mus_width = m->lceopt * sin(m->pennopt);     /* we assume that this is constant */

			if (mus_height<0) {
				/* if pennation angle is 90 degrees (or more), the muscle produces zero force */
					mus_height=0;
					SDBIO_state[2*SDBIO_ndof+2*i] = mus_width; 
			}
			else {
				SDBIO_state[2*SDBIO_ndof+2*i] = sqrt(mus_width*mus_width + mus_height*mus_height);
			//	fprintf(logfile,"Lce1 %f\n",SDBIO_state[2*SDBIO_ndof+2*i]);
			}
		}
		else if (mus_states[2*i] == 98)  /* isometric, lcedot = 0 */
			SDBIO_state[2*SDBIO_ndof+2*i] = optLce(m,SDBIO_state[2*SDBIO_ndof + 2 * i + 1]);
		else
			SDBIO_state[2*SDBIO_ndof+2*i] = mus_states[2*i];
			
		// fprintf(logfile,"Lce2 %f\n",SDBIO_state[2*SDBIO_ndof+2*i]);
		mus_states[2*i] = SDBIO_state[2*SDBIO_ndof+2*i];
	 }
	 
	 // set initial length of ligaments
	 for (i=0; i<SDBIO_nligaments; i++)
	 {
		l = &SDBIO_ligament[i];
		l->prev_l = liggeo(l,SDBIO_state,Lq);
	 }

/* call deriv to set initial states */

	 deriv(*t, SDBIO_state, dstate, act,0,0);

}


/***************************************************************
     SDBIO_getmincontact :  obtain min value of contact coordinates
     so user can position model so that grf points (foot)
     are just touching the contact surface
**************************************************************/
void SDBIO_getmincontact(int coord, double *minvalue) {

 int i, j;
 double pos[3], temp[3];

 *minvalue = 1e6;
 for (i=0;i<SDBIO_ngrf;i++) {
   for (j=0;j<SDBIO_grf[i].ncntpts;j++) {
     temp[0] = SDBIO_grf[i].cntpts[j][0];  /* get position of contact points wrt body */
     temp[1] = SDBIO_grf[i].cntpts[j][1];
     temp[2] = SDBIO_grf[i].cntpts[j][2];
     sdpos(SDBIO_grf[i].body[j], temp, pos); /* get global position of contact points */
     if (pos[coord] < *minvalue) *minvalue = pos[coord];
   }
 }
}

/*******************************************
     optLce:  solves the Lce at which the muscle is at steady state: dLce/dt = 0
        adapted from Matlab's fzero.m
*****************************************/
double optLce(SDBIO_muscletype *m, double act) {

   double Lce, dLce, tol, a, b, c, d, e, fa, fb, fc, x, toler, bmax, s, p, q, r;

   Lce = m->lceopt * (1 - m->width); /* initial guess */
   dLce = 1/20.0;  /* step size */
   tol = 0.0000001;

   a = Lce - dLce; fa = isofunc(m,a, act);
   b = Lce + dLce; fb = isofunc(m,b,act);

   /* find change of sign */
   while ((fa > 0) == (fb > 0)) {
               dLce = 2 * dLce;
               a = Lce - dLce;  fa = isofunc(m,a, act);
               if ((fa > 0) != (fb > 0)) break;
               b = Lce + dLce; fb = isofunc(m,b,act);
   }
   fc = fb;
   /* Main loop */
   while (fb != 0){
       /* Insure that b is the best result so far, a is the previous
          value of b, and c is on the opposite of the zero from b */
               if ((fb > 0) == (fc > 0)) {
                       c = a; fc = fa;
                       d = b - a; e = d;
               }
               if (fabs(fc) < fabs(fb)) {
                       a = b; b = c; c = a;
                       fa = fb; fb = fc; fc = fa;
               }
               /* convergence test and possible exit */
               x = 0.5 * (c - b);
               bmax = fabs(b);
               bmax = (bmax > 1.0) ? bmax : 1.0;
               toler = 2.0 * tol * bmax;
               if ((fabs(x) <= toler) + (fb == 0)) break;

               /* choose bisection or interpolation */
               if ((fabs(e) < toler) + (fabs(fa) <= fabs(fb)))
                       { d = x; e = x; }        /* Bisection */
               else {/* Interpolation */
                       s = fb / fa;
                       if (a == c) { /* linear interpolation */
                               p = 2.0 * x * s;
                               q = 1.0 - s;
                       }
                       else { /* inverse quadratic interpolation */
                               q = fa / fc;
                               r = fb / fc;
                               p = s * (2.0 * x * q *(q - r) - (b - a) * (r - 1.0));
                               q = (q - 1.0) * (r - 1.0) * (s - 1.0);
                       }
                       if (p > 0)
                               q = -q;
                       else
                               p = -p;
                       /* is interpolated point acceptable? */
                       if (((2.0 * p) < (3.0 * x * q - fabs(toler * q))) * (p < fabs(0.5 * e * q)))
                               { e = d; d = p / q; }
                       else
                               { d = x; e = x; }
               }

               /* next point */
               a = b;
               fa = fb;
               if (fabs(d) > toler) b = b + d;
               else if (b > c) b = b - toler;
               else b = b + toler;
               fb = isofunc(m,b, act);
   }
   return b;
}

/**************************************************************
        isofunc:  function to solve for initmus(98)
                computes the force imbalance when assuming isometric CE
**************************************************************/
double isofunc(SDBIO_muscletype *m, double Lce, double act) {

   double Fce, Fsee, Fpee, Lq[MAXDOF];

   m->lm = musgeo(m, SDBIO_state, Lq);
       act = (act > actmin) ? act : actmin;

       Fce = act*Force_LengthCE(m, Lce);
   Fsee = Force_LengthSEE(m, m->lm - Lce);
   Fpee = Force_LengthPEE(m, Lce);

       return Fce + Fpee - Fsee;

}

/**********************************************************************
        SDBIO_getcount
*******************************************************************/
void SDBIO_getcount(int *der) {
   *der = numder;
}

/**********************************************************************************
       SDBIO_getq:     passes generalized coordinates, q, to main program
**********************************************************************************/
void SDBIO_getq(double q[]) {
   int i;

   for (i=0; i<SDBIO_ndof; i++)
               q[i] = SDBIO_state[i];

}

/**********************************************************************************
       SDBIO_getqdot:  passes generalized speeds, qdot, to main program
**********************************************************************************/
void SDBIO_getqdot(double qdot[]) {
   int i;

   for (i=0; i<SDBIO_ndof; i++)
               qdot[i] = SDBIO_state[i+ SDBIO_ndof];

}

/**********************************************************************************
       SDBIO_getmuscle:        passes muscle forces, F, to main program
**********************************************************************************/
void SDBIO_getmuscle(double F[], double m[])
{
   int i, j, k;
   k = -1;
   for (i=0; i<SDBIO_nmuscles; i++) {
       F[i] = SDBIO_muscle[i].F;
       for (j=0; j<SDBIO_muscle[i].nmusdof; j++){
           k = k + 1;
           m[k] =  SDBIO_muscle[i].F * SDBIO_muscle[i].lm1[j]; /* moment in each joint of each muscle, in order */
       }

   }

}

/**********************************************************************************
       SDBIO_getmuscleforces:  passes muscle forces, F, to main program
	   
       It also returns the muscle-tendon length - Dimitra Blana, June 27th 2008
	  
       This version does not rely on what was left behind from deriv() 
**********************************************************************************/
void SDBIO_getmuscleforces(double q[], double mus_states[], double F[], double Lm[])
{
   int i;
   double Lmn, Lsee, Lq[MAXDOF],penn_angle,Lopt,Lcen,Lt,Lce0,SExm,PExm,sep1,pep1,sep2,pep2,Fse,Fpe;
   SDBIO_muscletype *m;

   for (i=0; i<SDBIO_nmuscles; i++) {
		m = &(SDBIO_muscle[i]);
		Lm[i] =  musgeo(m, q, Lq);                    /* compute muscle-tendon length of muscle i */
		
		/* pennation angle: between 0 and 90 degrees */
		penn_angle = calc_pennation(mus_states[2*i],m->lceopt,m->pennopt);
		   
		if (mus_model==1) {
	        Lsee = Lm[i] - mus_states[2*i]*cos(penn_angle);	
			F[i] = Force_LengthSEE(m,Lsee);
			
		}
		else if (mus_model==2) {
			Lopt = m->lceopt*cos(m->pennopt) + m->lslack;

		/* Express lengths as proportions of Lopt  */
		    Lmn = Lm[i] / Lopt;
		    Lcen = mus_states[2*i] / Lopt;
		    Lt = m->lslack / Lopt;
		    Lce0 = m->lceopt / Lopt;

		/* Some parameters */
		    SExm  = 0.05 * Lt + 0.04 * Lce0; // series elastic element, max. extension
		    PExm  = 0.4 * 1; // parallel elastic element, max. extension
		    sep1 = 1 / (exp(SEsh) - 1.0);
		    pep1 = 1 / (exp(PEsh) - 1.0);
		   
		   
		/* Determination of force in SEE from current SEE length */
		    Lsee = Lmn - Lcen*cos(penn_angle)-Lt;
		    if (Lsee < 0) Lsee = 0;
		   		  
		// Force in SE (= Force in CE)
		    sep2 = exp(Lsee*SEsh/SExm) - 1.0;
		    Fse = sep1 * sep2;
		                  
		/**********  Parallel elastic element  ***********/
		    pep2  =  exp((Lmn-1)*(PEsh/PExm));          
		    Fpe = pep1 * (pep2 - 1.0);
		    if (Fpe<0) Fpe=0.0;
		                                 
		/*********** Total muscle force ************/
		    F[i] = (Fse + Fpe) * m->fmax;	
		}
	
   }

}


/****************************************************************************
       SDBIO_getstick:  passes location of model's critical points to main program
                     for the creation of a stick figure
******************************************************************************/
void SDBIO_getstick(double stick[])
{
   int i,j;
   double pos[3], btj[3], temp[3];
   double com[] = {0,0,0};


   j = 0;

/* get global XYZ coordinates of all joints */

   for (i=0;i<SDBIO_njnt;i++) {
       sdgetbtj(i, btj);
       sdpos(i,btj,pos);
       stick[j++] = pos[0];
       stick[j++] = pos[1];
       stick[j++] = pos[2];
   }

/* get global XYZ coordinates of first & last point of each GRF element */

   for (i=0;i<SDBIO_ngrf;i++) {
       temp[0] = SDBIO_grf[i].cntpts[0][0];  /* get position of first contact point */
       temp[1] = SDBIO_grf[i].cntpts[0][1];
       temp[2] = SDBIO_grf[i].cntpts[0][2];
       sdpos(SDBIO_grf[i].body[0], temp, pos);
       stick[j++] = pos[0];
       stick[j++] = pos[1];                         /* MUST BE ALTERED FOR THE HORSE MODEL*/
       stick[j++] = pos[2];
       temp[0] = SDBIO_grf[i].cntpts[SDBIO_grf[i].ncntpts - 1][0]; /* get position of last contact point */
       temp[1] = SDBIO_grf[i].cntpts[SDBIO_grf[i].ncntpts - 1][1];
       temp[2] = SDBIO_grf[i].cntpts[SDBIO_grf[i].ncntpts - 1][2];
       sdpos(SDBIO_grf[i].body[SDBIO_grf[i].ncntpts - 1], temp, pos);
       stick[j++] = pos[0];
       stick[j++] = pos[1];
       stick[j++] = pos[2];
   }

}

/*******************************
   SDBIO_getVRML()
*******************************/
void SDBIO_getVRML(int iseg, double VRMLdata[7])
{
 int i;
 double eulerpara4, VRMLpoint[3], Segcos[3][3], Segloc[3], ContactCM[3], ContactPos[3];

 for (i=0; i<3; i++) VRMLpoint[i] = 0;

 sdpos(iseg, VRMLpoint, Segloc);    /* get global XYZ of the body segment's center of mass */
 VRMLdata[0] = Segloc[0];
 VRMLdata[1] = Segloc[1];
 VRMLdata[2] = Segloc[2];
 sdorient(iseg, Segcos);
 sddc2quat(Segcos, &VRMLdata[3], &VRMLdata[4], &VRMLdata[5], &eulerpara4);
 VRMLdata[6]=2*acos(eulerpara4);
}

/*******************************
   SDBIO_getVRML2()
   This version does not rely on state left behind by deriv()
*******************************/

void SDBIO_getVRML2(double q[], int iseg, double VRMLdata[7])
{
 int i;
 double eulerpara4, VRMLpoint[3], Segcos[3][3], Segloc[3], ContactCM[3], ContactPos[3];
 double qdotzeros[MAXSTA];
 double tmptime = 0.0;

 /* register new state for SD/FAST, set qdots to zeros, they don't matter here */
 for (i=0; i<SDBIO_ndof; i++) qdotzeros[i] = 0.0;
 sdstate(tmptime, q, qdotzeros);       /* not fully tested for side effects on SDBIO_simulate yet */

 /* get global XYZ of center of mass, later maybe we want joint for easier 3D graphics modeling */
 for (i=0; i<3; i++) VRMLpoint[i] = 0;
 sdpos(iseg, VRMLpoint, Segloc);
 VRMLdata[0] = Segloc[0];
 VRMLdata[1] = Segloc[1];
 VRMLdata[2] = Segloc[2];

 /* get attitude matrix and convert to quaternions and then to angle-axis for VRML */
 sdorient(iseg, Segcos);
 sddc2quat(Segcos, &VRMLdata[3], &VRMLdata[4], &VRMLdata[5], &eulerpara4);
 VRMLdata[6]=2*acos(eulerpara4);
}

/********************************************************************************
        SDBIO_getLCE:   passes length of CE, LCE, to main program
***************************************************************************/
void SDBIO_getLce(double LCE[], double lceopt[], double Lm[])
{
int i;
 for (i=0; i<SDBIO_nmuscles; i++) {
    LCE[i] = SDBIO_state[2*SDBIO_ndof+2*i];
    /*     lceopt[i] = SDBIO_muscle[i].lceopt;
           Lm[i] = SDBIO_muscle[i].lm; */
    /*   printf("LCE[%d] = %f\n", i, LCE[i]);*/
 }
}

/******************************************************************************
     SDBIO_getAct: passes activation state to main program
***************************************************************************/
void SDBIO_getAct(double Act[])
{
int i;
 for (i=0; i<SDBIO_nmuscles; i++) {
    Act[i] = SDBIO_state[2*SDBIO_ndof + 2*i + 1];
    /*    printf("Act[%d] = %f\n", i,  Act[i]); */
 }
}


/***************************************************************************
       SDBIO_getgrf: computes total grf and moments about global origin
************************************************************************/
void SDBIO_getgrf(int side, double ground[]) /* if only one side in a model, side = 0 */
{
   int i, j;
   double temp[3], loc[3];

   double force[] = {0,0,0};
   double xmoments = 0;
   double ymoments = 0;
   double zmoments = 0;

   for (i=0; i<3; i++) {
       for (j=0; j<SDBIO_grf[side].ncntpts; j++) {
           force[i] = force[i] + SDBIO_grf[side].force[j][i];
               }
   }

   for (i=0;i<SDBIO_grf[side].ncntpts;i++) {
       for (j=0;j<3;j++)
               temp[j] = SDBIO_grf[side].cntpts[i][j];
       sdpos(SDBIO_grf[side].body[i],temp, loc);
       xmoments = xmoments - loc[2] * SDBIO_grf[side].force[i][1] + loc[1] * SDBIO_grf[side].force[i][2];
       ymoments = ymoments + loc[2] * SDBIO_grf[side].force[i][0] - loc[0] * SDBIO_grf[side].force[i][2];
       zmoments = zmoments + loc[0] * SDBIO_grf[side].force[i][1] - loc[1] * SDBIO_grf[side].force[i][2];
   }

   /* calculate COP */ /* WARNING!!!! the following must be checked for 2-D/3-D correctness */
#if 0
   /* for 2-D */
   if (force[1] == 0) x = 0;
   else
       x = zmoments / force[1];
   if (force[1] == 0) z = 0;
   else
       z = -xmoments / force[1];

   Ty = ymoments - z * force[0] + x * force[2];    /* calculate vertical torque at COP */

   /* for 3-D */
   if (force[2] == 0) x = 0;
   else
       x = -ymoments / force[2];
   if (force[2] == 0) y = 0;
   else
       y = xmoments / force[2];

   Tz = zmoments + x * force[1] - y * force[0];    /* calculate vertical torque at COP */
#endif
   ground[0] = force[0]; ground[1] = force[1]; ground[2] = force[2];
   /*printf("force = %f %f %f\n", force[0], force[1], force[2]);*/
   ground[3] = xmoments; ground[4] = ymoments; ground[5] = zmoments;

}

/******************************************************************************
   SDBIO_getJntReac:  passes joint reaction forces and torques to main program
**********************************************************************************/
void SDBIO_getJntReac(double forces[][3], double torques[][3]) {

   sdreac(forces, torques);

}

/**********************************************************************************
       sduforce:       defines the applied forces/torques to the system
**********************************************************************************/
void sduforce() {
}


/***********************************************************************
       INTERNAL FUNCTIONS
***********************************************************************
       deriv:          returns derivatives for all state variables
***********************************************************************/
int deriv(double t, double state[], double dstate[], double stims[], double exF[], int exF_bodies[]) 
{
	 int i, j, d;
	 double def, veldef, jnt_moment;
	 double q[MAXDOF], qdot[MAXDOF], moments[MAXMUS*MAXMUSDOF];
	 SDBIO_muscletype *m;
	 SDBIO_ligamenttype *l;
	 double errs[MAXCON];  /* Constraint error array */
	 double Lq[MAXDOF];
	 int force_cf,appl_cf;
	 double force_vector[3],body_force_vector[3],appl_origin[3],appl_vector[3];
	
	 if (t>sim_time) 
	 {
		sim_stepsize = t-sim_time;
		sim_time=t;
	  } 
	   
	/* register new state for SD/FAST */
	 sdstate(t, state, state+SDBIO_ndof);

	 for (i=0;i<SDBIO_ndof;i++){
	     q[i] = state[i];
	     qdot[i] = state[i+SDBIO_ndof];
	 }

	 user_torque(t,q,qdot,moments);
	 for (i=0;i<SDBIO_ndof;i++)
	     sdhinget(SDBIO_statemap[i][0], SDBIO_statemap[i][1], moments[i]);

//  external_force(force_vector);
	 
	 for (i=0; i<SDBIO_nactivejnt; i++) {
		   if (SDBIO_joint[i].limitcheck == 1) {
			    if (state[SDBIO_joint[i].q] <= SDBIO_joint[i].lowerlim) {
				       def = state[SDBIO_joint[i].q] - SDBIO_joint[i].lowerlim;
				       veldef = state[SDBIO_joint[i].q + SDBIO_ndof];
				       user_joint(SDBIO_joint[i].name, def, veldef, &jnt_moment);
				       sdhinget(SDBIO_statemap[SDBIO_joint[i].q][0],SDBIO_statemap[SDBIO_joint[i].q][1], jnt_moment);
			     }
			     else if (state[SDBIO_joint[i].q] >= SDBIO_joint[i].upperlim) {
				       def = state[SDBIO_joint[i].q] - SDBIO_joint[i].upperlim;
				       veldef = state[SDBIO_joint[i].q + SDBIO_ndof];
				       user_joint(SDBIO_joint[i].name, def, veldef, &jnt_moment);
				       sdhinget(SDBIO_statemap[SDBIO_joint[i].q][0],SDBIO_statemap[SDBIO_joint[i].q][1], jnt_moment);
			     } 
		   }
	 }


/* apply ground reaction force */

	 if (SDBIO_ngrf != 0) grf();

/* apply other external forces */

	 if (SDBIO_nextforce != 0) ext_force(t);
	 

/* apply external forces */
if ((num_exF>0)&&(exF!=0))
{
	for (i=0; i<num_exF; i++) {
		force_cf = exF_bodies[2*i];
		for (j=0; j < 3; j++) force_vector[j]=exF[6*i+j];
		appl_cf = exF_bodies[2*i+1];
		sdgetbtj(appl_cf,appl_origin);
		for (j=0; j < 3; j++) appl_vector[j]=exF[6*i+j+3]+appl_origin[j];
		sdtrans(force_cf,force_vector,appl_cf,body_force_vector);
		sdpointf(appl_cf,appl_vector,body_force_vector);  
//	    fprintf(logfile,"force = %f %f %f\n", force_vector[0],force_vector[1],force_vector[2]);
//	    fprintf(logfile,"body force = %f %f %f\n", body_force_vector[0],body_force_vector[1],body_force_vector[2]);
//	    fprintf(logfile,"force_cf=%d, appl_cf=%d\n", force_cf,appl_cf);
//		fprintf(logfile,"Size of int types is %d bytes\n", (int)sizeof(int));	
	}
}

/* apply ligament forces */
	for (i=0; i<SDBIO_nligaments; i++) {
		l = &(SDBIO_ligament[i]);
		l->lm =  liggeo(l, state, Lq);
		
		l->F=0;   // <-- calculate force here

		// elastic force
		if (l->lm < l->lslack) {
			l->F = -l->klig_comp * (l->lm - l->lslack) * (l->lm - l->lslack);
		}
		else {
			l->F = l->klig_tension * (l->lm - l->lslack) * (l->lm - l->lslack);
		}
				
		for (j=0; j < l->nmusdof; j++) {
		   d = l->musdof[i];
		   sdhinget(l->musjnt[j], l->musaxis[j], l->F*Lq[d]);
		}
	};
	
/* check if scapula is inside the thorax and apply appropriate force */
	if (scap_thor_constr)
	{
		AI_frc = apply_scapthor_force(AI,AIok, AIcontact, AInormal);
		TS_frc = apply_scapthor_force(TS,TSok, TScontact, TSnormal);
	}
	
/* Set derivatives of muscle states (active state and Lce) and apply muscle forces */

	 j = 2 * SDBIO_ndof;
	 for (i=0; i<SDBIO_nmuscles; i++) {
	    m = &(SDBIO_muscle[i]);
	    m->ns = stims[i];
		
		// SDBIO 2-state model
		if (mus_model==1) {
			dstate[j] = musmod(&(SDBIO_muscle[i]), state[j], state[j+1], state, 1); /* ODE for contraction */
			j++;
		    /* calculate rate of change of active state using He's activation model */
		    dstate[j] = (m->c1*m->ns + m->c2)*(m->ns - state[j]);
		    j++;
		}
		// DSEM 2-state model
		else if (mus_model==2) {
//			fprintf(logfile,"in deriv...\n"); 
			dstate[j] = musmod_DSEM(&(SDBIO_muscle[i]), state[j], state[j+1], state, 1); /* ODE for contraction */
			j++;
			dstate[j] = m->ns - state[j];
			if (dstate[j]<0.0)
				dstate[j] = dstate[j]/m->taud;
			else
				dstate[j] = dstate[j]/m->taua;
			j++;
		}
		// 1-state model
	    else if (mus_model==3) {
			musmod_simple(&(SDBIO_muscle[i]),state[j],state, 1);
		    /* calculate rate of change of active state using He's activation model */
		    dstate[j] = (m->c1*m->ns + m->c2)*(m->ns - state[j]);
		    j++;
		}
	 }
/* Compute SD state derivatives: accelerations and velocities for generalized coordinates */

	 sdderiv(dstate, dstate+SDBIO_ndof);

/* Check that constraint errors are below tol.
	  Although there are here no constraint, this checking should always
	  be done by the user when using the Generalized Analysis Routine. */

	 if (SDBIO_ncon == 0) return 0;

	 sdverr(errs);                     /* Velocity constraint errors */
	 for (i=0; i<SDBIO_ncon; i++) {
//	    if (fabs(errs[i]) > CONSTRAINT_TOL) fprintf(logfile,"velocity error above tolerance: %f\n",errs[i]);
//	    if (fabs(errs[i]) > CONSTRAINT_TOL) return 1;
	 }
			   
	 sdperr(errs);                     /* Position constraint errors */
	 for (i=0; i<SDBIO_ncon; i++) {
//	    if (fabs(errs[i]) > CONSTRAINT_TOL) fprintf(logfile,"position error above tolerance: %f\n",errs[i]);
//	    if (fabs(errs[i]) > CONSTRAINT_TOL) return 1;
	 }
			   
	 return 0;
}

double apply_scapthor_force(double BL[],int BLok[], double BLcontact[], double n_normBLthor[])
{
	double BLthor[3],BLdist,normBLthor[3],BLerror[3],poserror,velerror,BLvelthor[3],BLfrc,normBL[3],n_normBL[3],BLfrc_v[3];
	int i;

	sdpos(scapnum,BL,BLthor);
	// check if the bony landmark is inside (BLdist<0) or outside (BLdist>0) the thorax
	BLdist = pow(BLthor[0]-elcenter[0],2)/(pow(elrad[0],2))+pow(BLthor[1]-elcenter[1],2)/(pow(elrad[1],2))+pow(BLthor[2]-elcenter[2],2)/(pow(elrad[2],2))-1;		
	if (BLdist>0) 
	{
		BLok[0]=1;		
		return 0;
	}
	else
	{
		if (BLok[0]==1) 
		{
			BLok[0]=0;
			for (i=0; i<3; i++) BLcontact[i]=BLthor[i]; // this is the point where BL "enters" the thorax ("contact" point)
//	        fprintf(logfile,"BLcontact=%f %f %f\n",BLcontact[0],BLcontact[1],BLcontact[2]);
			for (i=0; i<3; i++) normBLthor[i] = 2*(BLthor[i]-elcenter[i])/pow(elrad[i],2); // normal to the thorax at the "contact" point
			normalize_vector(normBLthor, n_normBLthor);
		}
		/*  Position error: only the component that is normal to the thorax
		 This is the projection of vector: <"contact" point -BL> (named BLerror) onto "normal" vector
		 Since the "normal" vector is normalized, this projection is given by the dot-product of the two vectors
		 We assume that BL is close enough to the "contact" point that the same vector is normal to the ellipsoid both at BL and "contact" */
		for (i=0; i<3; i++) BLerror[i]=BLcontact[i]-BLthor[i];
//	    fprintf(logfile,"BLcontact=%f %f %f\n",BLcontact[0],BLcontact[1],BLcontact[2]);
//	    fprintf(logfile,"BLthor=%f %f %f\n",BLthor[0],BLthor[1],BLthor[2]);
		poserror = BLerror[0]*n_normBLthor[0]+BLerror[1]*n_normBLthor[1]+BLerror[2]*n_normBLthor[2];

		// Velocity error: only the component of the velocity that is normal to the thorax (we use the "normal" vector calculated before)
		sdvel(scapnum,BL,BLvelthor);
		velerror = BLvelthor[0]*n_normBLthor[0]+BLvelthor[1]*n_normBLthor[1]+BLvelthor[2]*n_normBLthor[2];
		
		// This routine is in das3sim
		scapthor_force(poserror, -velerror, &BLfrc, k_scapthor);

//	    fprintf(logfile,"poserror = %f velerror = %f force = %f\n",poserror,velerror,BLfrc);
//	    fprintf(logfile,"BLvel=%f %f %f\n",BLvelthor[0],BLvelthor[1],BLvelthor[2]);
//	    fprintf(logfile,"BL=%f %f %f\n",BL[0],BL[1],BL[2]);
		sdtrans(0, n_normBLthor, scapnum, normBL);
		normalize_vector(normBL, n_normBL);
		for (i=0; i<3; i++) BLfrc_v[i]=BLfrc*n_normBL[i];
		sdpointf(scapnum,BL,BLfrc_v);
		
		return BLfrc;
	}
}

/***********************************************************************
       musprep:        preprocess some muscle properties to speed up computations
***********************************************************************/
void musprep(SDBIO_muscletype *m) {
   m->width = m->rwidth * m->lceopt; /* rwidth here = WIDTH in vanSoest and Bobbert (1993) */
   m->b = m->vmrel * m->arel * m->lceopt;
   m->p1 = (m->fecmax -1) * m->b / m->slopfac / (m->arel + 1);
   m->fecmax1 = 1 + 0.85 * (m->fecmax - 1);
   m->s = m->p1 * (m->fecmax - 1 ) / pow((m->fecmax - m->fecmax1),2);
   m->vs1 = m->p1 * ((m->fecmax - 1) / (m->fecmax - m->fecmax1) - 1) - m->s * m->fecmax1;
   m->c1 = 1 / m->taua - 1 / m->taud;
   m->c2 = 1 / m->taud;
   m->Ksee = m->fmax / (m->umax * m->umax * m->lslack * m->lslack);
   m->k = m->krel * m->fmax / (m->width * m->width);
   m->peeslackm = m->peeslack * m->lceopt;
}

/*******************************************************************
       Force_LengthCE:  Returns force in CE from Force-Length relationship
*****************************************************************/
double Force_LengthCE(SDBIO_muscletype *m, double Lce) {

   double F_Lce;

   F_Lce = m->fmax * (1 - (Lce - m->lceopt) * (Lce - m->lceopt) / (m->width * m->width));
   F_Lce = (F_Lce > 0.01*m->fmax) ? F_Lce : 0.01*m->fmax;
   return F_Lce;
}

/*******************************************************************
       Force_LengthSEE:  Returns force in SEE from Force-Length relationship
*****************************************************************/
double Force_LengthSEE(SDBIO_muscletype *m, double Lsee) {

   double Fsee;

   if (Lsee < m->lslack) {
       Fsee = 0;
   }
   else {
       Fsee = m->Ksee * (Lsee - m->lslack) * (Lsee - m->lslack);
   }
   return (Fsee + (Lsee - m->lslack));         /* second term is 1 N/m bidirectional spring */
}

/*******************************************************************
       Force_LengthPEE:  Returns force in PEE from Force-Length relationship
*****************************************************************/
double Force_LengthPEE(SDBIO_muscletype *m, double Lce) {

   double Fpee;

//   if (Lce > m->lceopt)
   if (Lce > m->peeslackm)
        Fpee = m->k * (Lce - m->peeslackm) * (Lce - m->peeslackm);
   else
        Fpee = 0;
//   if (Fpee < 0.1) Fpee = 0.1;
   return (Fpee + (Lce - m->peeslackm));               /* second term is 1 N/m bidirectional spring */
}

/****************************************************************
      Force_VelCE:  Returns Lcedot based on Force-Velocity relationship
*********************************************************************/
double Force_VelCE(SDBIO_muscletype *m, double Fce, double Lce, double Act) {

   double factor, g;
		
   if (Fce < 0) Fce = Fce/1000;
   if (Act<=actmin) 
		return Fce/10; // viscous element with a parameter of 0.01 N/mm/sec taken from Kirsch et al 94 (IEEE Trans BME Vol 41 No 8)
	
   if (Fce < 0) Fce = 0;
//   Act = (Act > actmin) ? Act : actmin;
   factor = 1 - exp(-3.82 * Act) + Act * exp(-3.82);

   g = Fce / Act / Force_LengthCE(m, Lce);

   if (g > m->fecmax1)         /* eccentric linear part */
       return m->vs1 + m->s * g;
   else if (g > 1)             /* eccentric hyperbolic part */
        return m->p1 * ((m->fecmax - 1) / (m->fecmax - g) - 1);
   else if (g > 0)             /* concentric Hill equation */
        return factor * m->b * (g - 1) / (m->arel + g);
   else
        return -factor * m->b / (m->arel + g) + Fce*1000;       /* 1000 m/s/N extra shortening under compression */
}

/***********************************************************************
       musmod:         state equation for 3-component Hill model

       Input:          m............The muscle element
                       Lce..........Its current Lce
                       act..........Its current active state
                       state[]......Entire state array
       Returns:        Lcedot.......The Lcedot for this muscle
       Side-effect:    applies muscle forces to SD/FAST model
***********************************************************************/
double musmod(SDBIO_muscletype *m, double Lce, double act, double state[], int flag) {

   double Lq[MAXDOF];
   double Lsee, Fsee, Fce, Fpee, penn_angle, Vce;
   int i,j;
	   
/* Calculate total muscle length and moment arms */
   m->lm =  musgeo(m, state, Lq);

/* pennation angle: between 0 and 90 degrees */
   penn_angle = calc_pennation(Lce,m->lceopt,m->pennopt);
   
/* Determination of force in SEE from current SEE length */
   Lsee = m->lm - Lce*cos(penn_angle);
   Fsee = Force_LengthSEE(m,Lsee);
   m->F = Fsee;
//   fprintf(logfile,"%s: penn_angle=%f  force=%f\n",m->name, penn_angle,m->F);
   
/* Application of torques due to muscle forces: only for forward model */
   if (flag)
	   for (i=0; i < m->nmusdof; i++) {
		   j = m->musdof[i];
		   sdhinget(m->musjnt[i], m->musaxis[i], m->F*Lq[j]);
	   }

/* subtract passive force to get CE force  */
   Fpee = Force_LengthPEE(m,Lce); /* ok to use Lce = Lpee, right? */
   Fce = Fsee/cos(penn_angle) - Fpee;  
//   if (Fce < 0) Fce = 0;
	/* NOTE: compressive force (Fce<0) should eventually be allowed and will be correctly handled by Force_VelCE 
	this is important for collocation and optimal control methods */

/* return lengthening velocity of CE, which is a function of CE force */
   Vce = Force_VelCE(m, Fce, Lce, act);
//    fprintf(logfile,"%15s: muscle force=%10f Fce=%10f Fse=%10f Fpe=%10f Vce=%10f Lce=%10f Lm=%10f\n",m->name,m->F,Fce,Fsee,Fpee,Vce,Lce,m->lm); 
//    if (act<0.02)
//		fprintf(logfile,"%15s: act=%10f\n",m->name,act); 

   return Vce;

}

/***********************************************************************
       musgeo:         calculates a muscle's length and moment arms
       Input:          m->...........The muscle element
                       q............The current generalized coordinates
       Returns:        (function)...The current muscle+tendon length
                       lq...........Partial derivatives of length w.r.t. generalized coordinates
       Notes:
       1. The "pulley"  method will not work for BALL joints, but we should make those out of three hinges anyway...
***********************************************************************/
double musgeo(SDBIO_muscletype *m, double q[], double lq[]) {

	 int i,j,k;
	 double length, term, qnonzero;

	 for (i=0; i<SDBIO_ndof ; i++) lq[i] = 0.0;            /* initialize all moment arms to 0 */

/* see if this is a pulley geometry model */
	 if (m->geotype == 1) {
		   length = m->lm0;                                    /* this is the length where all muscle DOF's are zero */
		   for (i=0; i<m->nmusdof; i++) {
			     j = m->musdof[i];
			     lq[j] = m->lm1[i];                                /* moment arm for DOF j */
			     length = length - m->lm1[i] * q[j];               /* length change due to DOF j */
		   }
	 }

/* see if this is a polynomial geometry model */
	 else if (m->geotype == 2) {
		   length = 0.0;
		   for(i=0; i < m->npolterms; i++) {
		   /* add this term's contribution to the muscle length */
			     term = m->polcoeff[i];
			     for(j=0; j < m->nmusdof; j++) {
				    for(k=0; k < m->expon[i][j]; k++)
						term = term * q[m->musdof[j]];	/* this creates q to the power expon[][] */
			     }
			     length = length + term;				 
		   
		         // moment arms: minus derivatives of length with respect to every q
				 for (j=0; j < m->nmusdof; j++) {
					if ((m->expon[i][j] > 0) && (q[ m->musdof[j] ] != 0.0)) 
						lq[ m->musdof[j] ] = lq[ m->musdof[j] ] - m->expon[i][j] * term / q[ m->musdof[j] ];
			}
		}
	 }
	 return length;
}

/***********************************************************************
       liggeo:         calculates a ligament's length and moment arms
       Input:          l->...........The ligament
                       q............The current generalized coordinates
       Returns:        (function)...The current length
                       lq...........Partial derivatives of length w.r.t. generalized coordinates
 ***********************************************************************/
double liggeo(SDBIO_ligamenttype *l, double q[], double lq[]) {

	 int i,j,k;
	 double length, term, qnonzero;

	 for (i=0; i<SDBIO_ndof ; i++) lq[i] = 0.0;            /* initialize all moment arms to 0 */

		   length = 0.0;
		   for(i=0; i < l->npolterms; i++) {
		   /* add this term's contribution to the muscle length */
			     term = l->polcoeff[i];
			     for(j=0; j < l->nmusdof; j++) {
				    for(k=0; k < l->expon[i][j]; k++)
					    term = term * q[l->musdof[j]];	/* this creates q to the power expon[][] */
			     }
			     length = length + term;	

		         // moment arms: minus derivatives of length with respect to every q
				 for (j=0; j < l->nmusdof; j++) {
					if ((l->expon[i][j] > 0) && (q[ l->musdof[j] ] != 0.0)) 
						lq[ l->musdof[j] ] = lq[ l->musdof[j] ] - l->expon[i][j] * term / q[ l->musdof[j] ];
				 
				}
			}
	 return length;
}

/**********************************************************************
     grf:  calculates ground reaction forces on each contact element and applies it to the skeleton
**********************************************************************/
void grf()
{
   int i,j,k;
   double loc[3], vel[3], f[3], flocal[3], temp[3];

   for (i=0;i<SDBIO_ngrf;i++) {
       for (j=0;j<SDBIO_grf[i].ncntpts;j++) {    /* for each ground contact point */
           for (k=0;k<3;k++)
               temp[k] = SDBIO_grf[i].cntpts[j][k];
           sdpos(SDBIO_grf[i].body[j],temp, loc);       /* get location of grf point in global frame */
           sdvel(SDBIO_grf[i].body[j],temp, vel);       /* get velocity of grf point in global frame */
           user_grf(SDBIO_grf[i].name,j,loc,vel,f);    /* get user-defined reaction force */
           for (k=0;k<3;k++)
               SDBIO_grf[i].force[j][k] = f[k];      /* array of the forces in the global coordinate system */

           sdtrans(-1,f,SDBIO_grf[i].body[j],flocal);   /* transform force into local frame */

           sdpointf(SDBIO_grf[i].body[j],temp,flocal);  /* apply local force to body */
       }

   }
   /* consider creating pointer to SDBIO_grf[i] and use -> to reference instead. Will decrease computing time */
}


/************************************************************************
      ext_force : applies user_defined external forces to the system
*********************************************************************/
void ext_force(double t)
{
   int i,j,k;
   double loc[MAXCNTPTS][3], vel[MAXCNTPTS][3], f[MAXCNTPTS][3], flocal[3], temp[3];

   for (i=0;i<SDBIO_nextforce;i++) {
       for (j=0;j<SDBIO_extforce[i].ncntpts;j++) {    /* for each contact point */
           for (k=0;k<3;k++)
               temp[k] = SDBIO_extforce[i].cntpts[j][k];
           sdpos(SDBIO_extforce[i].body[j],temp, loc[j]);       /* get location of point in global frame */
           sdvel(SDBIO_extforce[i].body[j],temp, vel[j]);       /* get velocity of point in global frame */
       }
       user_force(SDBIO_extforce[i].name, t, loc, vel, f);
       for (j=0;j<SDBIO_extforce[i].ncntpts;j++) {
           /*printf("f[%d] in ext_force = %f %f %f\n", j, f[j][0], f[j][1], f[j][2]);*/
           for (k=0;k<3;k++)
               temp[k] = SDBIO_extforce[i].cntpts[j][k];
           sdtrans(-1,f[j],SDBIO_extforce[i].body[j],flocal);
           sdpointf(SDBIO_extforce[i].body[j],temp,flocal);  /* apply local force to body */
       }
   }
}

/*******************************************************************
        find_joint
        given a joint name, determine the corresponding SDFAST dof number, joint number,  and joint axis number
	returns  -1 if name was not found
	returns  -2 if name was "end"
*********************************************************************/
void find_joint(char *name, int *dof, int *joint, int *axis) {

    int i;
    char *end = {"end"};

	if (strcmp(name, end) == 0) {
	  *dof = -2;
	  return;
	}
       for (i=0; i<SDBIO_nactivejnt; i++)
               if (strcmp(name, SDBIO_joint[i].name) == 0) {
                       *dof   = SDBIO_joint[i].q;
                       *joint = SDBIO_statemap[SDBIO_joint[i].q][0]; /* define DOF joint number */
                       *axis  = SDBIO_statemap[SDBIO_joint[i].q][1]; /* define DOF joint axis */
                       return;
               }
    *dof = -1;              // dof = -1 signifies that no joint with that name was found
}

/*******************************************************************
        find_body
        given a body name, determine the corresponding SDFAST body number
	returns  -3 if name was not found
	returns  -2 if name was "end"
*********************************************************************/
void find_body(char *name, int *num) {

    int i;
    char *end = {"end"};

	if (strcmp(name, end) == 0) {
	  *num = -2;
	  return;
	}
       for (i=0; i<SDBIO_njnt; i++) 
               if (strcmp(name, SDBIO_bodies[i]) == 0) {
                       *num   = i;
                       return;
               } 
    *num = -3;              // num = -3 signifies that no body with that name was found
}

/*******************************************************************
       read_muscle: read one muscle element from BIO file
********************************************************************/
int read_muscle(FILE *biofile, SDBIO_muscletype *muscle) {

 char s[20], s2[20], geotype[20], geopart[20];         /* to hold strings read from file */
 char *a = {"a"};
 char *end = {"end"};
 char *vmrel = {"vmrel"};
 char *fmax = {"fmax"};
 char *umax = {"umax"};
 char *fecmax = {"fecmax"};
 char *lceopt = {"lceopt"};
 char *pennopt = {"pennopt"};
 char *lslack = {"lslack"};
 char *peeslack = "PEEslack";
 char *width = {"width"};
 char *geometry = {"geometry"};
 char *point = {"point-to-point"};
 char *pulley = {"pulley"};
 char *dofs = {"dofs"};
 char *polynomial = {"polynomial"};
 char *parameters = {"parameters"};
 char *krel = {"krel"};
 char *slopfac = {"slopfac"};
 char *time_constants = {"time_constants"};
 char *GHfvectors = {"GH_force_vectors"};
 char *scapfvectors = {"scapula_force_vectors"};
 int i, j, k, dofcount, dof, joint, axis;
 float penn_degrees;

 muscle->crossGH = 0; /* this is the default: the muscle does not cross GH. If it does, crossGH will be 1 */
 muscle->attach_scap = 0; /* this is the default: the muscle does not attach on the scapula. If it does, attach_scap will be 1 */
 
 do {

// read muscle property keyword
   fscanf (biofile, "%s", s);

// test for known keywords
       if      (strcmp(s,a) == 0)                      fscanf(biofile,"%f", &muscle->arel);
       else if (strcmp(s,vmrel) == 0)                  fscanf(biofile, "%f", &muscle->vmrel);
       else if (strcmp(s,umax) == 0)                   fscanf(biofile,"%f", &muscle->umax);
       else if (strcmp(s,fecmax) == 0)                 fscanf(biofile, "%f", &muscle->fecmax);
       else if (strcmp(s,krel) == 0)                   fscanf(biofile, "%f", &muscle->krel);
       else if (strcmp(s,slopfac) == 0)                fscanf(biofile, "%f", &muscle->slopfac);
       else if (strcmp(s,time_constants) == 0) {
               fscanf(biofile, "%f", &muscle->taua);
               fscanf(biofile, "%f", &muscle->taud);
       }
      else if (strcmp(s,fmax) == 0)                   fscanf(biofile, "%f", &muscle->fmax);
      else if (strcmp(s,lceopt) == 0)                 fscanf(biofile, "%f", &muscle->lceopt);
	  else if (strcmp(s,lslack) == 0)                 fscanf(biofile, "%f", &muscle->lslack);
      else if (strcmp(s,pennopt) == 0) {                 
				fscanf(biofile, "%f", &penn_degrees); /* pennation angle at optimal fiber length is in degrees in the bio file */
				muscle->pennopt = penn_degrees * PI / 180;
	  }
      else if (strcmp(s,peeslack) == 0)               fscanf(biofile, "%f", &muscle->peeslack);
      else if (strcmp(s,width) == 0)                  fscanf(biofile, "%f", &muscle->rwidth);
      else if (strcmp(s,geometry) == 0) {
               fscanf(biofile, "%s", geotype);  /* define type of geometry */
               if (strcmp(geotype, point) == 0) {  /* get data according to type of geometry */
                       fprintf(logfile,"Point to point geometry type not implemented yet.\n");
					   return 1;
               }
               else if (strcmp(geotype, pulley) == 0) {
                       muscle->geotype = 1;
                       fscanf(biofile, "%f", &muscle->lm0);
                       dofcount = -1;
                       do {
                               fscanf(biofile, "%s", geopart);
                               find_joint(geopart, &dof, &joint, &axis);
				if (dof == -1) {
				  fprintf(logfile,"Error in BIO file: unknown joint name: %s\n",geopart);
				  return 1;
				}
                               if (dof >= 0) {
                                       dofcount++;
                                       muscle->musdof[dofcount] = dof;
                                       muscle->musjnt[dofcount] = joint; /* define DOF joint number */
                                       muscle->musaxis[dofcount] = axis;  /* define DOF joint axis */
                                       fscanf(biofile, "%f",&muscle->lm1[dofcount]);  /* get moment arm for this DOF */
                               }
                       } while (strcmp(geopart,end) != 0);
                       muscle->nmusdof = dofcount + 1; /* store total number of DOF spanned by this muscle */
               }
               else if (strcmp(geotype, polynomial) == 0) {
                       muscle->geotype = 2;
                       fscanf(biofile, "%s", s2);
                       if (strcmp(s2,dofs) != 0) {
                               fprintf(logfile,"ERROR in polynomial muscle description: keyword dofs expected.\n");
							   return 1;
						}
                       dofcount = -1;
                       do {
                               fscanf(biofile, "%s", geopart);
							   if (strcmp(geopart,"AC_y")==0) muscle->attach_scap = 1;
							   if (strcmp(geopart,"GH_y")==0) muscle->crossGH = 1;
                               find_joint(geopart, &dof, &joint, &axis);
				if (dof == -1) {
				  fprintf(logfile,"Error in BIO file: unknown joint name: %s\n",geopart);
				  return 1;
				}
				if (dof >= 0) {
					dofcount++;
					muscle->musdof[dofcount] = dof;
					muscle->musjnt[dofcount] = joint; /* define DOF joint number */
					muscle->musaxis[dofcount] = axis;  /* define DOF joint axis */
 				}
			} while (strcmp(geopart,end) != 0);
			muscle->nmusdof = dofcount + 1;
			fscanf(biofile, "%s", s2);
			if (strcmp(s2,parameters) != 0) {
				fprintf(logfile,"ERROR in polynomial muscle description: keyword parameters expected.\n");
				return 1;
			}
			fscanf(biofile, "%d", &muscle->npolterms);
			for (i=0; i<muscle->npolterms; i++) {
				for (j=0; j<muscle->nmusdof; j++) /* read exponents */ {
			           		fscanf(biofile, "%d", &muscle->expon[i][j]);
				}
				fscanf(biofile, "%f", &muscle->polcoeff[i]);
			}
		}
               else {
					fprintf(logfile,"unknown muscle geometry type: %s\n", geotype);
					return 1;
			   }
   }

      else if ((strcmp(s,GHfvectors) == 0)||(strcmp(s,scapfvectors) == 0)) {
	  /* this muscle crosses GH or attaches on the scapula, so we need to read the force vector polynomial terms */
	      for (i=0;i<3;i++) { /* three polynomials: for x, y, and z components of the force */
		    fscanf(biofile, "%s", s2);
			if (strcmp(s2,parameters) != 0) {
				fprintf(logfile,"ERROR in polynomial GH muscle force description: keyword parameters expected.\n");
				return 1;
			}
			fscanf(biofile, "%d", &muscle->nFpolterms[i]);
			for (k=0; k<muscle->nFpolterms[i]; k++) {
				for (j=0; j<muscle->nmusdof; j++) /* read exponents */ {
						if (i==0)
			           		fscanf(biofile, "%d", &muscle->xFexpon[k][j]);
						if (i==1)
			           		fscanf(biofile, "%d", &muscle->yFexpon[k][j]);
						if (i==2)
			           		fscanf(biofile, "%d", &muscle->zFexpon[k][j]);
				}
				if (i==0)
					fscanf(biofile, "%f", &muscle->xFpolcoeff[k]);
				if (i==1)
					fscanf(biofile, "%f", &muscle->yFpolcoeff[k]);
				if (i==2)
					fscanf(biofile, "%f", &muscle->zFpolcoeff[k]);
			}
		  }
	  }
	  
	  else if (strcmp(s,end) == 0) { /* end of muscle element */
     if (verbose > 2)
       fprintf(logfile,"end of muscle element\n");
   }
   else {
		fprintf(logfile,"unknown muscle property: %s\n", s);
		return 1;
   }
 } while (strcmp(s,end) != 0);  /* stop muscle loop at "end" */
 
 return 0;
}

/*******************************************************************
       read_ligament: read one ligament from BIO file
********************************************************************/
int read_ligament(FILE *biofile, SDBIO_ligamenttype *ligament) {

 char s[20], s2[20], geotype[20], geopart[20];         /* to hold strings read from file */
 char *end = {"end"};
 char *klig_tension = {"klig_tension"};
 char *klig_comp = {"klig_comp"};
 char *b = {"b"};
 char *lslack = {"lslack"};
 char *geometry = {"geometry"};
 char *polynomial = {"polynomial"};
 char *dofs = {"dofs"};
 char *parameters = {"parameters"};
 char *GHfvectors = {"GH_force_vectors"};
 char *scapfvectors = {"scapula_force_vectors"};
 int i, j, k, dofcount, dof, joint, axis;
 float penn_degrees;

 ligament->crossGH = 0; /* this is the default: the ligament does not cross GH. If it does, crossGH will be 1 */
 do {

// read ligament keyword
   fscanf (biofile, "%s", s);

// test for known keywords
       if      (strcmp(s,klig_tension) == 0)           fscanf(biofile,"%f", &ligament->klig_tension);
       else if (strcmp(s,klig_comp) == 0)              fscanf(biofile, "%f", &ligament->klig_comp);
       else if (strcmp(s,b) == 0)                      fscanf(biofile, "%f", &ligament->b);
	   else if (strcmp(s,lslack) == 0)                 fscanf(biofile, "%f", &ligament->lslack);
       else if ((strcmp(s,geometry) == 0) | (strcmp(s,polynomial) == 0)) ; // geometry is polynomial; ignore these keywords
	   else if (strcmp(s,dofs) == 0) {
            dofcount = -1;
            do {
                fscanf(biofile, "%s", geopart);
			   if (strcmp(geopart,"AC_y")==0) ligament->attach_scap = 1;
			   if (strcmp(geopart,"GH_y")==0) ligament->crossGH = 1;
                find_joint(geopart, &dof, &joint, &axis);
				if (dof == -1) {
				  fprintf(logfile,"Error in BIO file: unknown joint name: %s\n",geopart);
				  return 1;
				}
				if (dof >= 0) {
					dofcount++;
					ligament->musdof[dofcount] = dof;
					ligament->musjnt[dofcount] = joint; /* define DOF joint number */
					ligament->musaxis[dofcount] = axis;  /* define DOF joint axis */
 				}
			} while (strcmp(geopart,end) != 0);
			ligament->nmusdof = dofcount + 1;
			fscanf(biofile, "%s", s2);
			if (strcmp(s2,parameters) != 0) {
				fprintf(logfile,"ERROR in polynomial ligament description: keyword parameters expected.\n");
				return 1;
			}
			fscanf(biofile, "%d", &ligament->npolterms);
			for (i=0; i<ligament->npolterms; i++) {
				for (j=0; j<ligament->nmusdof; j++) /* read exponents */ {
			           		fscanf(biofile, "%d", &ligament->expon[i][j]);
				}
				fscanf(biofile, "%f", &ligament->polcoeff[i]);
			}
		}   

      else if ((strcmp(s,GHfvectors) == 0)||(strcmp(s,scapfvectors) == 0)) {
	  /* this ligament crosses GH or attaches on the scapula, so we need to read the force vector polynomial terms */
	      for (i=0;i<3;i++) { /* three polynomials: for x, y, and z components of the force */
		    fscanf(biofile, "%s", s2);
			if (strcmp(s2,parameters) != 0) {
				fprintf(logfile,"ERROR in polynomial GH ligament force description: keyword parameters expected.\n");
				return 1;
			}
			fscanf(biofile, "%d", &ligament->nFpolterms[i]);
			for (k=0; k<ligament->nFpolterms[i]; k++) {
				for (j=0; j<ligament->nmusdof; j++) /* read exponents */ {
						if (i==0)
			           		fscanf(biofile, "%d", &ligament->xFexpon[k][j]);
						if (i==1)
			           		fscanf(biofile, "%d", &ligament->yFexpon[k][j]);
						if (i==2)
			           		fscanf(biofile, "%d", &ligament->zFexpon[k][j]);
				}
				if (i==0)
					fscanf(biofile, "%f", &ligament->xFpolcoeff[k]);
				if (i==1)
					fscanf(biofile, "%f", &ligament->yFpolcoeff[k]);
				if (i==2)
					fscanf(biofile, "%f", &ligament->zFpolcoeff[k]);
			}
		  }
	  }
	  
	  else if (strcmp(s,end) == 0) { /* end of ligament*/
     if (verbose > 2)
       fprintf(logfile,"end of ligament\n");
   }
   else {
		fprintf(logfile,"unknown muscle property: %s\n", s);
		return 1;
   }
 } while (strcmp(s,end) != 0);  /* stop ligament loop at "end" */
 
 return 0;
}

/**********************************************************************
      SDBIO_getbio:      gets biological parts of model from <model>.bio

**********************************************************************/

int SDBIO_getbio(char *fileprefix, char error_msg[])
{
	 FILE *biofile;
	 int njoints, nmuscle, nligament, i, j, grfcount, extcount;
	 float lowerlim[1], upperlim[1],kscapthor[2],coord[1];
	 char keyword[20], jointname[NAMLEN], jointopt[20], musclename[NAMLEN], ligname[NAMLEN], temp[20];

	 char *verbose_level = {"verbose_level"};
	 char *pound = {"#"};
	 char *joint = {"joint"};
	 char *limits = {"limits"};
//	 char *axis = {"axis"};
	 char *q = {"q"};
// char *qdot = {"qdot"};
// char *Lce = {"Lce"};
// char *act = {"act"};
	 char *muscle = {"muscle"};
	 char *ligament = {"ligament"};
	 char *def = {"default"};
	 char *end = {"end"};
	 char *distal_body = {"distal_body"};
	 char *grf = {"grf"};
	 char *ext_force = {"ext_force"};
	 char *conoid = {"conoid_constraint"};
	 char *scapthor = {"scapulothoracic_constraint"};
	 char *EC = {"ellipsoid_center"};
	 char *ER = {"ellipsoid_radii"};
	 char filename[100];
	 
	 strcpy(filename, fileprefix);
	 strcat(filename, ".bio");
	 if ((biofile = fopen(filename, "r")) == NULL)
	 {
		    strcpy(error_msg,"Could not open .bio file");
			fprintf(logfile,"Could not open .bio file\n");
			return 1;
	 }

	 njoints = -1;
	 nmuscle = -1;
	 nligament = -1;
	 grfcount = -1;
	 extcount = -1;

     do {
	    fscanf(biofile, "%s", keyword);
	    if (verbose > 2)
			   fprintf(logfile,"keyword = %s\n", keyword);

/* read a comment line */
	    if ((strcmp(keyword,pound) == 0) || (keyword[0] == pound[0]))
	    fscanf(biofile, "%[^\n]\n", temp);

/* read verbose_level */
	    else if (strcmp(keyword,verbose_level) == 0)
	    fscanf(biofile, "%d", &verbose);

/* read conoid _constraint - only in DAS3 */		
		else if (strcmp(keyword,conoid) == 0)
		{
			find_body("clavicle_r",&clavnum);
			find_body("scapula_r",&scapnum);
			find_body("humerus_r",&humnum);
			find_body("radius_r",&radnum);
			find_body("ulna_r",&ulnanum);
			
			sdgetmass(scapnum,&scapmass);     // mass of scapula
			sdgetmass(humnum,&hummass);     // mass of humerus
			sdgetmass(ulnanum,&ulnamass);     // mass of ulna
			sdgetmass(radnum,&radmass);     // mass of radius

			sdgetbtj(scapnum, AC);  // actually -AC
			sdgetbtj(clavnum, SC);  // actually -SC
			if (verbose > 2) fprintf(logfile,"scapnum: %d, clavnum: %d\n",scapnum,clavnum);
			conoid_constr=1;
			fscanf(biofile, "%f", &coord[0]);
			conoid_length = coord[0];
		    if (verbose > 2) fprintf(logfile,"conoid constraint is active, with length: %f\n",conoid_length);
			if (verbose > 2) fprintf(logfile,"AC: [%f %f %f]\n",AC[0],AC[1],AC[2]);
			if (verbose > 2) fprintf(logfile,"SC: [%f %f %f]\n",SC[0],SC[1],SC[2]);
			for (j=0;j<2;j++)
			{
				fscanf(biofile, "%s", keyword);
				if (strcmp(keyword,"clavicle") == 0)
					for (i=0;i<3;i++)
					{
						fscanf(biofile, "%f", &coord[0]);
						conoid_clav[i]=coord[0]+SC[i];
					}
				else if (strcmp(keyword,"scapula") == 0)
					for (i=0;i<3;i++)
					{
						fscanf(biofile, "%f", &coord[0]);
						conoid_scap[i]=coord[0]+AC[i];
					}
				else 
				{
					fprintf(logfile,"Unexpected keyword: %s. Conoid ligament coordinates expected.\n", keyword);
					strcpy(error_msg,"Error reading conoid ligament coordinates from bio file.");
					return 1;
				}
			}
			if (verbose > 2) fprintf(logfile,"conoid origin on the clavicle: [%f %f %f]\n",conoid_clav[0],conoid_clav[1],conoid_clav[2]);
			if (verbose > 2) fprintf(logfile,"conoid insertion on the scapula: [%f %f %f]\n",conoid_scap[0],conoid_scap[1],conoid_scap[2]);
		}
		
/* read scapulothoracic_constraint - only in DAS3 */		
		else if (strcmp(keyword,scapthor) == 0)
		{
		    find_body("scapula_r",&scapnum);
		    sdgetbtj(scapnum, AC);
			scap_thor_constr=1;
			fscanf(biofile, "%f", &kscapthor[0]);
			k_scapthor[0] = kscapthor[0];
			fscanf(biofile, "%f", &kscapthor[1]);
			k_scapthor[1] = kscapthor[1];
		    if (verbose > 2) fprintf(logfile,"scapulothoracic constraint is active, with Kpos: %f and Kvel: %f\n",k_scapthor[0],k_scapthor[1]);
			for (j=0;j<4;j++)
			{
				fscanf(biofile, "%s", keyword);
				if (strcmp(keyword,"TS") == 0)
					for (i=0;i<3;i++)
					{
						fscanf(biofile, "%f", &coord[0]);
						TS[i]=coord[0]+AC[i];
					}
				else if (strcmp(keyword,"AI") == 0)
					for (i=0;i<3;i++)
					{
						fscanf(biofile, "%f", &coord[0]);
						AI[i]=coord[0]+AC[i];
					}
				else if (strcmp(keyword,EC) == 0)
					for (i=0;i<3;i++)
					{
						fscanf(biofile, "%f", &coord[0]);
						elcenter[i]=coord[0];
					}
				else if (strcmp(keyword,ER) == 0)
					for (i=0;i<3;i++)
					{
						fscanf(biofile, "%f", &coord[0]);
						elrad[i]=coord[0];
					}
				else 
				{
					fprintf(logfile,"Unexpected keyword: %s. AI, TS and thorax ellipsoid info expected.\n", keyword);
					strcpy(error_msg,"Error reading AI, TS and thorax ellipsoid info from bio file.");
					return 1;
				}
			}
		}

/* read a joint definition  */
	    else if (strcmp(keyword,joint) == 0) {
		     njoints = njoints + 1;
		     fscanf(biofile, "%s", SDBIO_joint[njoints].name);  /* read in name of joint */
			 strcpy(jointname, SDBIO_joint[njoints].name);
		     if (verbose > 2)
				fprintf(logfile,"SDBIO_joint[%d].name = %s\n", njoints, SDBIO_joint[njoints].name);
		     SDBIO_joint[njoints].limitcheck = 0;              /* set to no limits as default */
		     do {
			       fscanf(biofile, "%s", jointopt);
			       if (strcmp(jointopt,q) == 0) {
			         fscanf(biofile, "%d", &SDBIO_joint[njoints].q);
			         if (verbose > 2)
						fprintf(logfile,"SDBIO_joint[%d].q = %d\n", njoints, SDBIO_joint[njoints].q);
				   }
				   else if (strcmp(jointopt,distal_body) == 0) {
		                fscanf(biofile, "%s", SDBIO_joint[njoints].distal);  /* store distal body name */
		                for (i=0; i<SDBIO_nbod; i++) {
		                     if (strcmp(SDBIO_joint[njoints].distal,SDBIO_bodies[i]) == 0)    /* match distal body name */
									SDBIO_joint[njoints].q = sdindx(i,0);
		                }
		           }
		           else if (strcmp(jointopt, limits) == 0) {
				         SDBIO_joint[njoints].limitcheck = 1;
				         fscanf(biofile, "%f", &lowerlim[0]);
				         lowerlim[0] = lowerlim[0] * PI /180;
				         SDBIO_joint[njoints].lowerlim = lowerlim[0];
				         fscanf(biofile, "%f", &upperlim[0]);
				         upperlim[0] = upperlim[0] * PI / 180;
				         SDBIO_joint[njoints].upperlim = upperlim[0];
		           }
		           else if (strcmp(jointopt,end) == 0) {
		               if (verbose > 2)
		                     fprintf(logfile,"end of joint %s\n", jointname);
		           }
		           else {
						fprintf(logfile,"Unexpected keyword in joint %s: %s\n", jointname, jointopt);
					    strcpy(error_msg,"Error reading joint from bio file. See log file for details.");
						return 1;
			       }
		     } while (strcmp(jointopt,end) != 0);
		     SDBIO_nactivejnt = njoints + 1;
	    }

/* read a ligament*/
	   else if (strcmp(keyword,ligament) == 0) {
		     fscanf(biofile, "%s",ligname);  /* get ligament name */
		     if (verbose > 2) fprintf(logfile,"ligament name = %s\n", ligname);
		     if (strcmp(ligname,def) == 0) {
			       if (read_ligament(biofile, &ligdef)) {         /* store this in the "default" ligament */
					    strcpy(error_msg,"Error reading default muscle from bio file. See log file for details.");
						return 1;				   
				   }
		     }
			   
		     else {
			       nligament = nligament + 1;
			       if (verbose > 2) fprintf(logfile,"nligament = %d\n", nligament);
			       SDBIO_ligament[nligament] = ligdef;         /* set all properties to default initially */
			       strcpy(SDBIO_ligament[nligament].name, ligname);   /* store ligament name */
			       if (read_ligament(biofile, &SDBIO_ligament[nligament])) {
					    strcpy(error_msg,"Error reading muscle from bio file. See log file for details.");
						return 1;				   
				   }
		     }
		     SDBIO_nligaments = nligament + 1;
	   }
	   
/* read a muscle element */
	   else if (strcmp(keyword,muscle) == 0) {
		     fscanf(biofile, "%s", musclename);  /* get muscle name */
		     if (verbose > 2) fprintf(logfile,"muscle name = %s\n", musclename);
		     if (strcmp(musclename,def) == 0) {
			       if (read_muscle(biofile, &musdef)) {         /* store this in the "default" muscle */
					    strcpy(error_msg,"Error reading default muscle from bio file. See log file for details.");
						return 1;				   
				   }
		     }
			   
		     else {
			       nmuscle = nmuscle + 1;
			       if (verbose > 2) fprintf(logfile,"nmuscle = %d\n", nmuscle);
			       SDBIO_muscle[nmuscle] = musdef;         /* set all properties to default initially */
			       strcpy(SDBIO_muscle[nmuscle].name, musclename);   /* store muscle name */
			       if (read_muscle(biofile, &SDBIO_muscle[nmuscle])) {
					    strcpy(error_msg,"Error reading muscle from bio file. See log file for details.");
						return 1;				   
				   }
		     }
		     SDBIO_nmuscles = nmuscle + 1;
	   }

/* read a ground contact element */

	   else if (strcmp(keyword,grf) == 0) {
		     grfcount = grfcount + 1;
		     fscanf(biofile,"%s",&SDBIO_grf[grfcount].name);  /* get name of ground contact element */
		     if (verbose > 2)
					fprintf(logfile,"grf name = %s\n",SDBIO_grf[grfcount].name);
		     fscanf(biofile,"%d",&SDBIO_grf[grfcount].ncntpts); /* get number of contact points in the element */
		     for (i=0;i<SDBIO_grf[grfcount].ncntpts;i++) {
			       fscanf(biofile,"%s", temp);
			       for (j=0;j<SDBIO_nbod;j++) {
						if (strcmp(temp,SDBIO_bodies[j]) == 0) {  /* identify body */
							SDBIO_grf[grfcount].body[i] = j;
							if (verbose >2)
								fprintf(logfile,"SDBIO_grf[%d].body[%d] = %d\n", grfcount, i, j);
								break;
						}
				   }
			       for (j=0; j<3; j++) {
						fscanf(biofile,"%f",&SDBIO_grf[grfcount].cntpts[i][j]); /* get body coordinates of each point */
						if (verbose > 2)
							fprintf(logfile,"%s set %d = %f\n", SDBIO_grf[grfcount].name, i, SDBIO_grf[grfcount].cntpts[i][j]);
			       }
		     }
		     SDBIO_ngrf = grfcount + 1;
	   }

	   else if (strcmp(keyword,ext_force) == 0) {
	        extcount = extcount + 1;
	        fscanf(biofile,"%s",&SDBIO_extforce[extcount].name);  /* get name of force element */
	        if (verbose > 2)
	            fprintf(logfile,"ext_force name = %s\n",SDBIO_extforce[extcount].name);
	        fscanf(biofile,"%d",&SDBIO_extforce[extcount].ncntpts); /* get number of contact points in the element */
	        for(i=0;i<SDBIO_extforce[extcount].ncntpts;i++) {
	            fscanf(biofile,"%s", temp);
	            for (j=0;j<SDBIO_nbod;j++) {
	                if (strcmp(temp,SDBIO_bodies[j]) == 0) {  /* identify body */
	                    SDBIO_extforce[extcount].body[i] = j;
	                    break;
	                }
	            }
	            for (j=0;j<3;j++){
	                fscanf(biofile,"%f",&SDBIO_extforce[extcount].cntpts[i][j]); /* get body coordinates of each point */
	            }
	        }
	        SDBIO_nextforce = extcount + 1;
	   }

	    /* keyword "end" signals end of file */
	    else if (strcmp(keyword,end) == 0) {
	        if (verbose > 2)
	            fprintf(logfile,"%s of file\n", end); 
		}
	    else
	        fprintf(logfile,"unexpected word (%s) in structure\n", keyword);
	 } while ((strcmp(keyword,end) != 0) || (fscanf(biofile, "%s", keyword) != EOF));


	 if (verbose > 2)	{
	 fprintf(logfile,"SDBIO_njnt = %d\n", SDBIO_njnt);
	 fprintf(logfile,"SDBIO_nmuscles = %d\n", SDBIO_nmuscles);
	 fprintf(logfile,"SDBIO_ngrf = %d\n", SDBIO_ngrf);
	 }

	 fclose(biofile);
	 
	 return 0;

}


/********************************************************************************
       SDBIO_getinfo
		
	parses the _info or _i file generated by SD/Fast, to obtain model information
******************************************************************************/
int SDBIO_getinfo(char *fileprefix, char error_msg[])
{
 FILE *infofile;
 int numtemp, numtemp1, i,j;
 char temp[50], type[20];
 char *dash3 = {"---"};
 char *dash5 = {"-----"};
 char *planar = {"Planar"};
 char *Sliding = {"Sliding"};
 char *pin = {"Pin"};
 char *Bushing = {"Bushing"};
 char *Gimbal = {"Gimbal"};
 char *Ujoint = {"U-joint"};
 char *weld = {"Weld"};
 char filename[100];
 
 /* try opening _i file */
       strcpy(filename, fileprefix);
       strcat(filename, "_i");
       if ((infofile = fopen(filename,"r")) == NULL) {
       /* if that does not work, try _info file (generated by UNIX version of SD/Fast */
               strcpy(filename, fileprefix);
               strcat(filename, "_info");
           if ((infofile = fopen(filename,"r")) == NULL) {
					   strcpy(error_msg,"Could not read _info or _i file");
				       fprintf(logfile,"Could not read _info or _i file\n");
                       return 1;
               }
       }
	   
       do {
               fscanf(infofile, "%s", temp);
       } while (strcmp(temp,dash3) != 0);
       fscanf(infofile, "%[^\n]\n",temp);  /* bypass line of dashes */
       fscanf(infofile, "%[^\n]\n", temp); /* bypass "ground" line */

       for (i=0; i<SDBIO_nbod; i++) {                     /* create SDBIO_roadmap */
               fscanf(infofile, "%d", &numtemp);
           fscanf(infofile, "%s", &SDBIO_bodies[numtemp]);  /* SDBIO_bodies[body#] = bodyname */
               fprintf(logfile,"%d %s\n",numtemp, SDBIO_bodies[numtemp]);
           fscanf(infofile, "%d", &SDBIO_inb[numtemp]);
               fscanf(infofile, "%s", &SDBIO_joint[numtemp].type);  /* !!! SDBIO_joint order now has to be the same as the body order !!!*/
           if (strcmp(SDBIO_joint[numtemp].type,planar) == 0) {
                       for (j=0; j<3; j++) {
                               fscanf(infofile,"%d",&numtemp);
                               SDBIO_roadmap[numtemp] = i;                      /* SDBIO_roadmap[q] = body # */
                       }
                       fscanf(infofile, "%[^\n]\n", temp);
               }
               else if (strcmp(SDBIO_joint[numtemp].type,Sliding) == 0) {
                       fscanf(infofile,"%d",&numtemp);
                       SDBIO_roadmap[numtemp] = i;
                       fscanf(infofile, "%[^\n]\n", temp);
               }
               else if (strcmp(SDBIO_joint[numtemp].type,pin) == 0) {
                       fscanf(infofile,"%d",&numtemp);
                       SDBIO_roadmap[numtemp] = i;
                       fscanf(infofile, "%[^\n]\n", temp);
               }
               else if (strcmp(SDBIO_joint[numtemp].type,Bushing) == 0) {
                       for (j=0; j<3; j++) {
                               fscanf(infofile,"%d",&numtemp);
                               SDBIO_roadmap[numtemp] = i;                      /* SDBIO_roadmap[q] = body # */
                       }
                       fscanf(infofile, "%s", temp);
                       for (j=3; j<6; j++) {
                               fscanf(infofile,"%d",&numtemp);
                               SDBIO_roadmap[numtemp] = i;                      /* SDBIO_roadmap[q] = body # */
                       }
               }
               else if (strcmp(SDBIO_joint[numtemp].type,Gimbal) == 0) {
                       for (j=0; j<3; j++) {
                               fscanf(infofile,"%d",&numtemp);
                               SDBIO_roadmap[numtemp] = i;                      /* SDBIO_roadmap[q] = body # */
                       }
                       fscanf(infofile, "%[^\n]\n", temp);
               }
               else if (strcmp(SDBIO_joint[numtemp].type,Ujoint) == 0) {
                       for (j=0; j<2; j++) {
                               fscanf(infofile,"%d",&numtemp);
                               SDBIO_roadmap[numtemp] = i;                      /* SDBIO_roadmap[q] = body # */
                       }
                       fscanf(infofile, "%[^\n]\n", temp);
               }
			   else if (strcmp(SDBIO_joint[numtemp].type,weld) == 0) {
						fscanf(infofile, "%[^\n]\n", temp);
				}
               else  ;
       }

       do {
               fscanf(infofile, "%s", temp);
       } while (strcmp(temp,dash5) != 0);

       fscanf(infofile, "%[^\n]\n", temp);  /* bypass line of dashes */
       for (i=0; i<SDBIO_ndof; i++) {           /* create SDBIO_statemap */
               fscanf(infofile, "%d", &numtemp1);
               fscanf(infofile, "%s", temp);
               fscanf(infofile, "%d", &SDBIO_statemap[numtemp1][0]);  /* SDBIO_statemap[q][0] = joint # */
               fscanf(infofile, "%d", &SDBIO_statemap[numtemp1][1]);  /* SDBIO_statemap[q][1] = axis # */
               fscanf(infofile, "%s", type);
               if (strcmp(type,planar) == 0) {
                       fscanf(infofile, "%[^\n]\n", temp);
                       for (j=0; j<2;j++) {
                               fscanf(infofile, "%d", &numtemp);
                               fscanf(infofile, "%s", temp);
                               SDBIO_statemap[numtemp][0] = SDBIO_statemap[numtemp1][0];
                               fscanf(infofile, "%d", &SDBIO_statemap[numtemp][1]);
                               fscanf(infofile, "%[^\n]\n", temp);
                       }
               }
               else if (strcmp(type,Bushing) == 0) {
                       fscanf(infofile, "%[^\n]\n", temp);
                       for (j=0; j<5;j++) {
                               fscanf(infofile, "%d", &numtemp);
                               fscanf(infofile, "%s", temp);
                               fscanf(infofile, "%s", temp);
                               SDBIO_statemap[numtemp][0] = SDBIO_statemap[numtemp1][0];
                               fscanf(infofile, "%d", &SDBIO_statemap[numtemp][1]);
                               fscanf(infofile, "%[^\n]\n", temp);
                       }
               }
               else if (strcmp(type,Gimbal) == 0) {
                       fscanf(infofile, "%[^\n]\n", temp);
                       for (j=0; j<2;j++) {
                               fscanf(infofile, "%d", &numtemp);
                               fscanf(infofile, "%s", temp);
                               fscanf(infofile, "%s", temp);
                               SDBIO_statemap[numtemp][0] = SDBIO_statemap[numtemp1][0];
                               fscanf(infofile, "%d", &SDBIO_statemap[numtemp][1]);
                               fscanf(infofile, "%[^\n]\n", temp);
                       }
               }
               else if (strcmp(type,Ujoint) == 0) {
                       fscanf(infofile, "%[^\n]\n", temp);
                       for (j=0; j<1;j++) {
                               fscanf(infofile, "%d", &numtemp);
                               fscanf(infofile, "%s", temp);
                           fscanf(infofile, "%s", temp);
                               SDBIO_statemap[numtemp][0] = SDBIO_statemap[numtemp1][0];
                               fscanf(infofile, "%d", &SDBIO_statemap[numtemp][1]);
                               fscanf(infofile, "%[^\n]\n", temp);
                       }
               }
               else
                       fscanf(infofile, "%[^\n]\n", temp);
       }

       fclose(infofile);
	   return 0;
}


/******************************************************** 
	routines added by Dimitra Blana  for implementation of
	- inverse dynamic model
	- simple 1-state muscle model
	- 2-state muscle model from DSEM
	- calculation of pennation angle 
	- check for glenohumeral stability
**********************************************************/


/********************************************************************************************************
      SDBIO_initcond_simple:  Sets initial conditions q, qdot, lceprev and act for simple muscle model (1 state: activation)
*********************************************************************************************************/
void SDBIO_initcond_simple(double *t, double q[], double qdot[], double act[])
{

 int i,j;
 double dstate[MAXSTA];

/* set initial q and qdot: */

 for (i=0; i<SDBIO_ndof; i++) {
   SDBIO_state[i] = q[i];
   SDBIO_state[i+SDBIO_ndof] = qdot[i];
 }

sim_stepsize = 0.001; 
fprintf(logfile,"sim_stepsize = %f\n", sim_stepsize);

/* set initial muscle activations and "previous" Lce values: */

 for (i=0; i<SDBIO_nmuscles; i++){
   SDBIO_state[2*SDBIO_ndof + 2 * i + 1] = act[i]; 
   for (j=0;j<4;j++)
	SDBIO_muscle[i].lceprev[j]=1000;
 }

/* call deriv to set initial states */

 deriv(*t, SDBIO_state, dstate, act,0,0);

}


/*************************************************************************
       SDBIO_getmuscleforces_simple:  passes muscle forces, F, to main program
**************************************************************************/
void SDBIO_getmuscleforces_simple(double q[], double F[])
{
   int i;

   for (i=0; i<SDBIO_nmuscles; i++) 
		F[i]=SDBIO_muscle[i].F;

}

/***********************************************************************
       musmod_simple:         state equation for Hill model without velocity dependence
	                                activation is the only muscle state

       Input:          m............The muscle element
                       act..........Its current active state
			state[]......Entire state array
        Side-effect:    applies muscle forces to SD/FAST model
***********************************************************************/
void musmod_simple(SDBIO_muscletype *m, double act, double state[], int flag) {

       double Lq[MAXDOF];
       double Fce, Fpee, Lce, penn_angle, Fmuscle, Fvel_factor, fiber_vel, mus_height, mus_width;
       int i,j;

/* Calculate total muscle length and moment arms */
   m->lm =  musgeo(m, state, Lq);
   
   mus_height = m->lm - m->lslack;   			/* the muscle "height" equals Lce for unipennate muscles */
   mus_width = m->lceopt * sin(m->pennopt);     /* we assume that this is constant */

   if (mus_height<0) {
   /* if pennation angle is 90 degrees (or more), the muscle produces zero force */
		mus_height=0;
		Lce = mus_width;
		m->F = 0; }
   else {
		Lce = sqrt(mus_width*mus_width + mus_height*mus_height);
		Fce = Force_LengthCE(m,Lce); 							/* force in CE */
		Fpee = Force_LengthPEE(m,Lce); 							/* force in PEE */
		fiber_vel = calc_fibervel(m,Lce);  						/* muscle-tendon velocity */
		Fvel_factor = calc_force_vel(m,fiber_vel,act); 			/* velocity factor based on force-velocity relationship */
   
		Fmuscle = act*Fvel_factor*Fce+Fpee;

		penn_angle = calc_pennation(Lce,m->lceopt,m->pennopt);
		Fmuscle = cos(penn_angle)*Fmuscle;
   
		m->F = Fmuscle; }
	
//	m->F = 0;

//   fprintf(logfile,"%15s: Lce=%10f Lmt=%10f Fvelfactor=%10f Fce=%10f Fpee=%10f fiber_vel=%10f F=%10f\n",m->name,Lce,m->lm,Fvel_factor,Fce,Fpee,fiber_vel,m->F); 

/* Application of torques due to muscle forces */
    if (flag)
       for (i=0; i < m->nmusdof; i++) {
               j = m->musdof[i];
               sdhinget(m->musjnt[i], m->musaxis[i], m->F*Lq[j]);
   }
}

/******************************************************************************
       musmod_DSEM:         state equation for 3-component Hill model from forward DSEM

       Input:          m............The muscle element
                       Lce..........Its current Lce
                       act..........Its current active state
                       state[]......Entire state array
       Returns:        Lcedot.......The Lcedot for this muscle
       Side-effect:    applies muscle forces to SD/FAST model
******************************************************************************/
double musmod_DSEM(SDBIO_muscletype *m, double Lce, double act, double state[], int flag) {

    double Lq[MAXDOF];
    double Lse, Fse, Fpe, Fce, penn_angle, Vce, Lopt, Lm, Lcen, Lce0, Lt;
    double SExm, PExm, Lcesh, sep1, sep2, pep1, pep2, ltrat, rf, Vm, vmax, prev_lm;
	int i,j;
	   	   
	act = (act > actmin) ? act : actmin;
	
/* muscle length at optimal fiber length */
	Lopt = m->lceopt*cos(m->pennopt) + m->lslack;

/* Calculate total muscle length and moment arms */
	prev_lm = m->lm;
    m->lm =  musgeo(m, state, Lq);
	if (prev_lm==0) prev_lm=m->lm;
	Vm = (m->lm - prev_lm) / sim_stepsize;  // estimate of muscle velocity
	Vm=Vm/Lopt;
//    fprintf(logfile,"%15s: prev_lm=%10f new_lm=%10f Vm=%10f\n",m->name,prev_lm,m->lm,Vm); 

/* Express lengths as proportions of Lopt  */
    Lm = m->lm / Lopt;
    Lcen = Lce / Lopt;
    Lt = m->lslack / Lopt;
    Lce0 = m->lceopt / Lopt;
   
/* Some parameters */
    SExm  = 0.05 * Lt + 0.04 * Lce0; // series elastic element, max. extension
    PExm  = 0.4 * 1; // parallel elastic element, max. extension
    Lcesh = 0.3 * Lce0; // force/length, width f-l relation
    sep1 = 1 / (exp(SEsh) - 1.0);
    pep1 = 1 / (exp(PEsh) - 1.0);
   
/* pennation angle: between 0 and 90 degrees */
    penn_angle = calc_pennation(Lce,m->lceopt,m->pennopt);
   
/* Determination of force in SEE from current SEE length */
    Lse = Lm - Lcen*cos(penn_angle)-Lt;
    if (Lse < 0) Lse = 0;
   
    ltrat = exp(-((Lcen - Lce0)/Lcesh)*((Lcen - Lce0)/Lcesh));
    ltrat = cos(penn_angle)*ltrat;
		  
// Force in SE (= Force in CE)
    sep2 = exp(Lse*SEsh/SExm) - 1.0;
    Fse = sep1 * sep2;

// Normalized force (rf = f/fmax(l,act))
    rf = Fse / (act*ltrat);
        
// Scaling maximal velocity 
    vmax = MVvm*(1 - (MVer*(1 - ltrat*act)));
                                   
/*************Calculation Vce from normalized force-velocity ******************/
// Concentric contraction (rf < 1) 
    if (rf<=1.0)
		Vce = -MVsh * vmax * (rf - 1)/(rf + MVsh);
			
//Eccentric contraction (rf >= 1) 
    else
	{          
// 1 < rf <= maximal force (= MVml)
		if (rf<=MVml)
            Vce = vmax * MVshl * MVsh*((rf-1)/(rf-1 - (1 + MVsh*MVshl)*(MVml - 1)));
		else
		{
            Vce = (Vm > -MVvm) ? Vm : -MVvm;
            Fse = ltrat * act * MVml;
		}
    }      
    Vce = Vce*Lopt;
                  
/**********  Parallel elastic element  ***********/
    pep2  =  exp((Lm-1)*(PEsh/PExm));          
    Fpe = pep1 * (pep2 - 1.0);
    if (Fpe<0) Fpe=0.0;
                                 
/*********** Total muscle force ************/
    m->F = (Fse + Fpe) * m->fmax;	
//	fprintf(logfile,"in musmod_DSEM: %15s: muscle force=%10f\n",m->name,m->F); 
	
/**** Application of torques due to muscle forces: only for forward model ****/
    if (flag)
       for (i=0; i < m->nmusdof; i++) {
               j = m->musdof[i];
               sdhinget(m->musjnt[i], m->musaxis[i], m->F*Lq[j]);
	   }
   
//    fprintf(logfile,"%15s: muscle force=%10f Fce=%10f Fse=%10f Fpe=%10f\n",m->name,m->F,Fce,Fse,Fpe); 
   
    return Vce;
}

/**********************************************************************************
       calc_pennation: calculates the pennation angle, which is always between 0 and 90 degrees
***********************************************************************************/
double calc_pennation(double Lce, double Lceopt, double pennopt)
{

   double penn;

   if (Lce < VERY_SMALL) Lce = VERY_SMALL;
   penn = Lceopt * sin(pennopt) /Lce;

   if (penn <= 0.0)
      return (0.0);
   else if (penn >= 1.0)
      return (PI/2);
   else
      return (asin(penn));

}

/*****************************************************************************
       calc_fibervel : calculates the fiber velocity, by approximating the Lce derivative
******************************************************************************/
double calc_fibervel(SDBIO_muscletype *m,double Lce)
{

    m->lceprev[0] = m->lceprev[1];
    m->lceprev[1] = m->lceprev[2];
    m->lceprev[2] = m->lceprev[3];
    m->lceprev[3] = Lce;
	if (m->lceprev[0]==1000)
		return 0;  /* this happens in the first three steps */
	else
		return (1/(20*sim_stepsize))*(21*m->lceprev[3]-13*m->lceprev[2]-17*m->lceprev[1]+9*m->lceprev[0]);
  
}

/***********************************************************************
      calc_force_vel:  Returns velocity factor based on Force-Velocity relationship
************************************************************************/
double calc_force_vel(SDBIO_muscletype *m,double fiber_vel,double Act) 
{

   double factor, linear_limit, force_vel;

   Act = (Act > actmin) ? Act : actmin;
   factor = 1 - exp(-3.82 * Act) + Act * exp(-3.82);

   linear_limit = m->p1 * ((m->fecmax - 1) / (m->fecmax - m->fecmax1) - 1); /* the (eccentric) velocity where the curve changes from linear to hyperbolic */
   
   if (fiber_vel>linear_limit)
			force_vel =  fiber_vel - (m->vs1/m->s);  /* eccentric linear part */
   else if (fiber_vel>0)
			force_vel =  m->fecmax - ((m->fecmax-1)/(1+fiber_vel/m->p1)); /* eccentric hyperbolic part */
   else 
			force_vel = ((m->arel)*fiber_vel + factor*m->b)/(factor*m->b - fiber_vel); /* concentric Hill equation */
			
/* make sure the velocity factor is between 0 and fecmax */
	if (force_vel<0)
			force_vel=0;
	if (force_vel>m->fecmax)
			force_vel=m->fecmax;
			
	return force_vel;
	
}

/******************************************************************************
	get_force_vector: calculates the muscle force vector at the current state
*******************************************************************************/

void get_force_vector(SDBIO_muscletype *m, double q[], double nforce_vec[]) {

 int i,j,k;
 double term, qnonzero;
 double force_vec[3];

 for (i=0; i<3 ; i++) force_vec[i] = 0.0;            /* initialize the force vector to 0 */

 // x component
 for(i=0; i < m->nFpolterms[0]; i++) {
   /* add this term's contribution to the force component  */
		term = m->xFpolcoeff[i];
		for(j=0; j < m->nmusdof; j++) {
			qnonzero = q[m->musdof[j]];
			for(k=0; k < m->xFexpon[i][j]; k++)
				term = term * qnonzero;	/* this creates q to the power expon[][] */
		}
     force_vec[0] = force_vec[0] + term;
	}
	
 // y component
 for(i=0; i < m->nFpolterms[1]; i++) {
   /* add this term's contribution to the force component  */
		term = m->yFpolcoeff[i];
		for(j=0; j < m->nmusdof; j++) {
			qnonzero = q[m->musdof[j]];
			for(k=0; k < m->yFexpon[i][j]; k++)
				term = term * qnonzero;	/* this creates q to the power expon[][] */
		}
     force_vec[1] = force_vec[1] + term;
	}

 // z component	
 for(i=0; i < m->nFpolterms[2]; i++) {
   /* add this term's contribution to the force component  */
		term = m->zFpolcoeff[i];
		for(j=0; j < m->nmusdof; j++) {
			qnonzero = q[m->musdof[j]];
			for(k=0; k < m->zFexpon[i][j]; k++)
				term = term * qnonzero;	/* this creates q to the power expon[][] */
		}
     force_vec[2] = force_vec[2] + term;
	}
   normalize_vector(force_vec, nforce_vec);
// fprintf(logfile,"%s: GHx=%f  GHy=%f  GHz = %f F = %f\n",m->name, GHforce_vec[0],GHforce_vec[1],GHforce_vec[2],m->F);
 return;
}

/************************************************************************************* 
	check_GH_stability: check if glenohumeral stability is maintained (called by main program)
**************************************************************************************/
void check_GH_stability(double q[], double *GHcheck)
{
   int i,j;
   double GHforce_vec[3], nforce[3], corr_nforce[3], theta, phi, gravityvec_scap[3],linaccgr[3],linacc[3];
   SDBIO_muscletype *m;
   double aphi=38.55, atheta=44.37;
   double glenoid_orient[3][3] = {{ 0.9816,0.1177, 0.1502},
								  {-0.1164,0.9930,-0.0178},
								  {-0.1513,0,      0.9885}};
   double COM[3]={0},GHforce[3]={0};

   for (i=0; i<SDBIO_nmuscles; i++) {
		m = &(SDBIO_muscle[i]);
		if (m->crossGH) {  // only include muscles that cross GH
				get_force_vector(m, q, GHforce_vec);
 				for (j=0; j<3; j++)
					GHforce[j] +=(m->F)*GHforce_vec[j];
		}
	}
	
	//  add gravity force of humerus, radius and ulna
	sdtrans(-1, gravityvec, scapnum, gravityvec_scap);
	for (j=0; j<3; j++) GHforce[j]+=(hummass+radmass+ulnamass)*gravityvec_scap[j];

	// subtract force due to linear acceleration
	// humerus
	sdacc(humnum,COM,linaccgr); // acceleration of humerus COM in ground c.f.
	sdtrans(-1,linaccgr,scapnum,linacc);
	for (j=0; j<3; j++) GHforce[j]-=hummass*linacc[j];
	// ulna
	sdacc(ulnanum,COM,linaccgr); // acceleration of ulna COM in ground c.f.
	sdtrans(-1,linaccgr,scapnum,linacc);
	for (j=0; j<3; j++) GHforce[j]-=ulnamass*linacc[j];
	// radius
	sdacc(radnum,COM,linaccgr); // acceleration of radius COM in ground c.f.
	sdtrans(-1,linaccgr,scapnum,linacc);
	for (j=0; j<3; j++) GHforce[j]-=radmass*linacc[j]; 
			
    normalize_vector(GHforce, nforce);
	
    /* calculate position of glenoid cavity */
	mult_vec_by_3x3mat(glenoid_orient,nforce,corr_nforce);
   
	theta = asin(-corr_nforce[1])*180/PI;
	if (sqrt(corr_nforce[0]*corr_nforce[0]+corr_nforce[2]*corr_nforce[2]) < VERY_SMALL)
		phi = 0.0;
	else
		phi = asin(corr_nforce[2]/sqrt(corr_nforce[0]*corr_nforce[0]+corr_nforce[2]*corr_nforce[2]))*180/PI;

	*GHcheck = pow((theta/atheta),2)+pow((phi/aphi),2);
	
//	fprintf(logfile,"radius COM linear acceleration: [%f %f %f]\n",linacc[0],linacc[1],linacc[2]);
	
}

/************************************************************************************* 
	get_conoid_force: get the force at the conoid ligament (called by main program)
**************************************************************************************/
void get_conoid_force(double *conoidfrc)
{
	*conoidfrc = conoid_frc;
}

/************************************************************************************* 
	get_scapthor_force: get the scapulothoracic force(called by main program)
**************************************************************************************/
void get_scapthor_force(double *scapthorfrc)
{
	scapthorfrc[0] = AI_frc;
	scapthorfrc[1] = TS_frc;
}

/*************************************************
	INIT_MAT: allocates space for n x m matrix
	from Dynamics Pipeline
**************************************************/

double **init_mat(int n, int m)
{
    int i;
    double **ptr = calloc(n,sizeof(double*));	/* allocate rows */
    if (!ptr) return (double**)-1;
    for (i=0 ; i<n ; i++)
    {
	ptr[i] = calloc(m,sizeof(double));	/* allocate columns */
        if (!ptr) return (double**)-1;
    };
    return (double**) ptr;
}

/*******************************************************
	NORMALIZE_VECTOR: normalizes a 1x3 vector
	from Dynamics Pipeline
********************************************************/

double normalize_vector(double vector[], double norm_vector[])
{

   double magnitude;

   magnitude = sqrt((vector[0]*vector[0])+(vector[1]*vector[1])+(vector[2]*vector[2]));

   if (magnitude < VERY_SMALL)
   {
      norm_vector[0] = vector[0];
      norm_vector[1] = vector[1];
      norm_vector[2] = vector[2];
   }
   else
   {
      norm_vector[0] = vector[0]/magnitude;
      norm_vector[1] = vector[1]/magnitude;
      norm_vector[2] = vector[2]/magnitude;
   }

   return (magnitude);

};

/* CROSS_VECTORS: computes the cross product of two 1x3 vectors */

void cross_vectors(double vector1[], double vector2[], double result[])
{
   result[0] = vector1[1] * vector2[2] - vector1[2] * vector2[1];
   result[1] = vector1[2] * vector2[0] - vector1[0] * vector2[2];
   result[2] = vector1[0] * vector2[1] - vector1[1] * vector2[0];
}

/* MULT_VEC_by3X3MATRIX: mat*vector */

void mult_vec_by_3x3mat(double mat[][3], double vector[], double result[])
{

   result[0] = mat[0][0]*vector[0] + mat[0][1]*vector[1] + mat[0][2]*vector[2];
   result[1] = mat[1][0]*vector[0] + mat[1][1]*vector[1] + mat[1][2]*vector[2];
   result[2] = mat[2][0]*vector[0] + mat[2][1]*vector[1] + mat[2][2]*vector[2];

}

/* CALCDIST: calculates the distance between two 3D points. */

double calcdist(double p1[], double p2[])
{

   double vec[3];

   vec[0] = p2[0] - p1[0];
   vec[1] = p2[1] - p1[1];
   vec[2] = p2[2] - p1[2];

   return (sqrt(vec[0]*vec[0]+vec[1]*vec[1]+vec[2]*vec[2]));

}

/* VECTORANGLE: calculates the angle between two vectors */
double vectorangle(double v1[], double v2[])
{
   double nv1[3], nv2[3];

   normalize_vector(v1,nv1);
   normalize_vector(v2,nv2);

   return (acos(nv1[0]*nv2[0]+nv1[1]*nv2[1]+nv1[2]*nv2[2]));

}

void sduperr(double t,double q[],double errs[])
{
// This routine computes the position error (perr) for the
// distance constraint. If d is the desired distance and
// p1 and p2 are the current global frame locations of
// points pt1 and pt2, then
// perr = ((p1-p2)*(p1-p2) - d**2)/2

	int i;
	double p1[3],p2[3],dot;

	int body1 = clavnum; // clavicle
	int body2 = scapnum; // scapula
	double d = conoid_length;
	
	sdpos(body1,conoid_clav,p1);
	sdpos(body2,conoid_scap,p2);
	dot = 0;
	for (i=0; i<3; i++) dot = dot + pow(p1[i]-p2[i],2);
	errs[0] = sqrt(dot)-d;
//	fprintf(logfile,"conoid length: %f\n",sqrt(dot));
	return;
};

void sduverr(double t,double q[],double u[],double errs[])
{
// This routine computes the velocity error (verr) for the distance
// constraint, which must be the derivative of the position
// error function above. If v1 and v2 are the current global
// frame velocities of points pt1 and pt2, then
// verr = (v1-v2)*(p1-p2)

	int i;
	double p1[3],p2[3],v1[3],v2[3];

	int body1 = clavnum; // clavicle
	int body2 = scapnum; // scapula

	sdpos(body1,conoid_clav,p1);
	sdpos(body2,conoid_scap,p2);
	sdvel(body1,conoid_clav,v1);
	sdvel(body2,conoid_scap,v2);
	errs[0] = 0;
	for (i=0; i<3; i++) errs[0] = errs[0] + (v1[i]-v2[i])*(p1[i]-p2[i]);
//	fprintf(logfile,"vel error: %f\n",errs[0]);
	return;
};

void sduaerr(double t,double q[],double u[],double udot[],double errs[])
{
// This routine computes the acceleration error (aerr) for the
// distance constraint, which must be the derivative of the velocity
// error function above. If a1 and a2 are the current global frame
// accelerations of points pt1 and pt2, then
// aerr = (a1-a2)*(p1-p2) + (v1-v2)*(v1-v2)

	int i;
	double p1[3],p2[3],v1[3],v2[3],a1[3],a2[3];
	
	int body1 = clavnum; // clavicle
	int body2 = scapnum; // scapula

	sdpos(body1,conoid_clav,p1);
	sdpos(body2,conoid_scap,p2);
	sdvel(body1,conoid_clav,v1);
	sdvel(body2,conoid_scap,v2);
	sdacc(body1,conoid_clav,a1);
	sdacc(body2,conoid_scap,a2);
	errs[0] = 0;
	for (i=0; i<3; i++) errs[0] = errs[0] + (a1[i]-a2[i])*(p1[i]-p2[i]) + pow(v1[i]-v2[i],2);
//	fprintf(logfile,"acc error: %f\n",errs[0]);
	return;
};

void sduconsfrc(double t,double q[],double u[],double mults[])
{
// This routine applies appropriate forces to the two points to cause
// the distance between them to remain as desired. By inspection of
// the verr function above, we see the terms involving velocities are:
// v1*(p1-p2) and -v2*(p1-p2)
// Thus, if we call the passed-in multiplier m, the forces to be
// applied are:
// f1 = m*(p1-p2) and f2 = -m*(p1-p2) = -f1
// f1 is to be applied to pt1 and f2 is to be applied to pt2. Note that
// these forces are in the global frame and must be converted into the
// appropriate body-local frame before being applied.

	int i;
	double p1[3],p2[3],frc[3];

	int body1 = clavnum; // clavicle
	int body2 = scapnum; // scapula

	sdpos(body1,conoid_clav,p1);
	sdpos(body2,conoid_scap,p2);
	for (i=0; i<3; i++) frc[i] = mults[0]*(p1[i]-p2[i]);
	sdtrans(0,frc,body1,frc);
	sdpointf(body1,conoid_clav,frc);
	for (i=0; i<3; i++) frc[i] = -frc[i];
	sdtrans(body1,frc,body2,frc);
	sdpointf(body2,conoid_scap,frc);
	conoid_frc = -mults[0]*calcdist(p1,p2);
	return;
}
