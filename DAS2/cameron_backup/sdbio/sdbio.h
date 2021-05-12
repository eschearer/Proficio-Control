/* Header file for SDBIO library, version 3.7 */

/* Constants */
#define  PI 3.14159265358979
#define VERY_SMALL 1e-6
#define CONSTRAINT_TOL 0.001

/*****************************************************************************/
/* Constants defining model size limits */

#define MAXSTA  	500         /* maximum number of system states (2*NDOF + muscle states) */
#define MAXDOF  	200         /* maximum number of DOF */
#define MAXCON  	5           /* maximum number of kinematic constraints */
#define MAXLINCON  	100         /* maximum number of linear equality constraints in muscle force optimization */
#define MAXMUS  	200         /* max number of muscles in model */
#define MAXLIG  	20          /* max number of ligaments in model */
#define NAMLEN  	40          /* length of names */
#define MAXMUSDOF 	10           /* max number of DOF between a muscle's origin and insertion */
#define MAXCNTELE 	10          /* max number of contact elements  */
#define MAXCNTPTS 	100         /* max number of contact points per element */
#define MAXPOLTERMS 35          /* max number of polynomial terms in muscle geometry */

/*****************************************************************************/

/* define structure containing muscle info */
typedef struct SDBIO_muscletype
{
/* parameters read from input file: */
   char  name[NAMLEN]; /* Name of muscle */
   float lceopt;               /* Optimal length of CE */
   float pennopt;             /* Pennation angle at optimal length of CE, in radians */   
   float rwidth;               /* Max. relative length change of CE */
   float fmax;                 /* Maximal isometric force of CE */
   float arel;                 /* a/Fmax for F-v relationship */
   float vmrel;                /* b*Fmax/a/Lceopt (max. contraction velocity in Lceopt/s) */
   float taua, taud;           /* Activation-deactivation time constants */
   float lslack;               /* Slack length of the SEE, in meters */
   float peeslack;             /* Slack length of the PEE, in multiples of Lceopt */
   float umax;                 /* Strain in SEE at Fmax */
   int   geotype;              /* Geometry type: 1 = pulley, 2 = polynomial */
   float lm0;                  /* Muscle+tendon length when all DOF related to that muscle are zero*/
   float lm1[MAXMUSDOF];       /* First order regression coefficients for muscle length */
   int   nmusdof;              /* how many DOFs between origin and insertion */
   int   musdof[MAXMUSDOF];    /* list of DOFs between origin and insertion */
   int   musjnt[MAXMUSDOF];    /* joint identifier */
   int   musaxis[MAXMUSDOF];   /* axis identifier  */
   int   npolterms;            /* number of terms in polynomial */
   float polcoeff[MAXPOLTERMS];        /* polynomial coefficients */
   int   expon[MAXPOLTERMS][MAXMUSDOF];        /* polynomial exponents */
   int   crossGH;            /* 1 if the muscle cross GH, 0 otherwise */
   int   attach_scap;        /* 1 if the muscle attaches on the scapula, 0 otherwilse */
   int   nFpolterms[3];            /* number of terms in GH force vector polynomial */
   float xFpolcoeff[MAXPOLTERMS];        /* polynomial coefficients for the x direction of force */
   float yFpolcoeff[MAXPOLTERMS];        /* polynomial coefficients for the y direction of force */
   float zFpolcoeff[MAXPOLTERMS];        /* polynomial coefficients for the z direction of force */
   int   xFexpon[MAXPOLTERMS][MAXMUSDOF];        /* polynomial exponents for the x direction of force */
   int   yFexpon[MAXPOLTERMS][MAXMUSDOF];        /* polynomial exponents for the y direction of force */
   int   zFexpon[MAXPOLTERMS][MAXMUSDOF];        /* polynomial exponents for the z direction of force */
   float fecmax;               /* maximum eccentric force */
   float krel;                 /* relative stiffness */
   float k;                    /* stiffness */
   float slopfac;              /* slope factor */
/* derived parameters (see musprep() function in sdbio.c) */
   double width, p1, fecmax1, s, vs1, b, c1, c2, Ksee;
       double peeslackm;                       // Slack length of the PEE, in meters
/* variables generated during simulation */
   double lm;                          /* Total muscle length and moment arms */
   double ns;                          /* neural stimulation level */
   double F;                           /* muscle force */
   float  lceprev[4];                  /* previous values of Lce for estimation of fiber velocity */
}SDBIO_muscletype;

/* define structure containing ligament info */
typedef struct SDBIO_ligamenttype
{
/* parameters read from input file: */
   char  name[NAMLEN]; /* Name of muscle */
   float klig_tension;          /* stiffness in tension */
   float klig_comp;             /* stiffness in compression */  
   float b;                     /* viscous parameter */  
   float lslack;               /* Slack length, in meters */
   int   nmusdof;              /* how many DOFs between origin and insertion */
   int   musdof[MAXMUSDOF];    /* list of DOFs between origin and insertion */
   int   musjnt[MAXMUSDOF];    /* joint identifier */
   int   musaxis[MAXMUSDOF];   /* axis identifier  */
   int   npolterms;            /* number of terms in polynomial */
   float polcoeff[MAXPOLTERMS];        /* polynomial coefficients */
   int   expon[MAXPOLTERMS][MAXMUSDOF];        /* polynomial exponents */
   int   crossGH;            /* 1 if the ligament cross GH, 0 otherwise */
   int   attach_scap;        /* 1 if the ligament attaches on the scapula, 0 otherwilse */
   int   nFpolterms[3];            /* number of terms in force vector polynomial */
   float xFpolcoeff[MAXPOLTERMS];        /* polynomial coefficients for the x direction of force */
   float yFpolcoeff[MAXPOLTERMS];        /* polynomial coefficients for the y direction of force */
   float zFpolcoeff[MAXPOLTERMS];        /* polynomial coefficients for the z direction of force */
   int   xFexpon[MAXPOLTERMS][MAXMUSDOF];        /* polynomial exponents for the x direction of force */
   int   yFexpon[MAXPOLTERMS][MAXMUSDOF];        /* polynomial exponents for the y direction of force */
   int   zFexpon[MAXPOLTERMS][MAXMUSDOF];        /* polynomial exponents for the z direction of force */
   double lm;                          /* Total length  */
   double F;                           /* ligament force */
   double prev_l;					   /* length at previous timestep */
}SDBIO_ligamenttype;

/*****************************************************************************
/*  Global variables containing information about joints  */

typedef struct SDBIO_jointtype
{
   char name[NAMLEN];      /* Name of joint  */
   char distal[NAMLEN];    /* Name of distal body  */
   char type[NAMLEN];      /* Joint type */
   int limitcheck;         /* 0 = no joint limits, 1 = joint limits */
   double lowerlim;        /* lower joint limit */
   double upperlim;        /* upper joint limit */
   int q;                  /* Corresponding DOF */
   double torque;          /* torque if DOF is prescribed */
}SDBIO_jointtype;

/*****************************************************************************
/*   Global variables containing ground reaction force information  */

typedef struct SDBIO_forcetype
{
   char name[NAMLEN];                  /* Name of grf element  */
   int body[MAXCNTPTS];                /* Number of body segment  */
   int ncntpts;                                /* Number of grf points */
   float cntpts[MAXCNTPTS][3];                 /* XYZ coordinates of grf points wrt the body segment */
   double initglobal[MAXCNTPTS][3];    /*Initial global position of the grf points to calculate the height of the model */
   float force[MAXCNTPTS][3];                  /* Array of forces that were applied to system in global coordinates */
   float moment[MAXCNTPTS][3];                 /* Array of moments in global coordinate system */
}SDBIO_forcetype;

/*****************************************************************************
/* Function prototypes */

/* modeling and simulation functions */

int SDBIO_init(		    // initialize SDBIO
	char *fileprefix,		    // name of the model; SDBIO_init will load <name>_info and <name>.bio
    char error_msg[]);	    // description of the error

void SDBIO_initcond(		// set initial conditions
	double *t, 				// current time
	double q[], 			// generalized coordinates
	double qdot[], 			// generalized velocities
	double mus_states[]); 	// muscle active states

void SDBIO_simulate(	// simulate for one time interval
	double *tstart, 	// start time
	double tstep);		// duration


/* functions to extract current state information from SDBIO */

void SDBIO_getq(		// obtain current generalized coordinates
	double q[]);

void SDBIO_getqdot(		// obtain current generalized velocities
	double qdot[]);

void SDBIO_getmuscle(		// obtain muscle forces and moment exerted by each muscle at each joint
	double F[], 
	double m[]);

void SDBIO_getmuscleforces(	// obtain muscle forces from DOFs and Lce
	double q[],
	double Lce[],
	double F[],
	double Lm[]);

void SDBIO_getLCE(		// obtain current muscle contractile element lengths
	double Lce[]);
	
void SDBIO_getAct(		// obtain current muscle active states
	double Act[]);
	
void SDBIO_getgrf(		// obtain current ground reaction force & moment
	int element, 		// number of GRF element for which information is needed
	double ground[6]);	// total 3D force and moment produced by contact points in GRF element

void SDBIO_getmincontact(	// get minimum value of a coordinate of all contact points
	int coord, 				// 0,1,2 for X,Y, or Z coordinate
	double *minvalue);		// the result is returned here
	
void SDBIO_getVRML(			// obtain position and orientation of a body segment, in VRML format
	int segment_number,		// segment number, see SD/Fast _info file for numbering
	double VRMLdata[7]);

void SDBIO_getVRML2(		// obtain position and orientation of a body segment, in VRML format, from q
	double q[],
	int segment_number,		// segment number, see SD/Fast _info file for numbering
	double VRMLdata[7]);

/* extract diagnostic information */
	
void SDBIO_getcount(		// number of evals of ODE within SDBIO_simulate
	int *der);

/* functions to be coded by the application programmer */

void user_stim(double *t, double q[], double qdot[], double stim[]);
void user_motion();
void user_grf(char *name, int grfpoint, double *p, double *v, double *f);
void user_torque(double t, double *q, double *qdot, double *m);
void user_joint(char *name, double e, double ve, double *f);
void user_general(double t, double *q, double *qdot);
