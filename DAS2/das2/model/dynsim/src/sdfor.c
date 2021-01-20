/*******************************************************************************

   E:\das\das_models\trunk\das2\model\dynsim\src\sdfor.c

   Created by SIMM 4.1.1 (from joint file E:\das\das_models\trunk\das2\model\das2.jnt)

   Time of creation: 11/20/2007 04:34:33 PM

   Description: This file contains the routines needed to perform a forward
      dynamics simulation of an SD/FAST model. The specific routines that it
      contains depend on the SIMM model from which this code was generated.

*******************************************************************************/

#include "universal.h"
#include "model.h"

/*************** DEFINES (for this file only) *********************************/
#define BAUMGARTE_STAB 20

/* Defines for the joints, Qs, and body segments are now found in model.h */



/*************** STATIC GLOBAL VARIABLES (for this file only) *****************/



/**************** GLOBAL VARIABLES (used in only a few files) *****************/
extern dpModelStruct* sdm;


/*************** EXTERNED VARIABLES (declared in another file) ****************/



/*************** PROTOTYPES for STATIC FUNCTIONS (for this file only) *********/


/* INIT_QS: this routine initializes the array of structures
 * that hold information about the Qs (gencoords).
 */

void init_qs(void)
{

   int i;

   sdm->q = (dpQStruct*)simm_malloc(sdm->nq*sizeof(dpQStruct));
   mstrcpy(&sdm->q[fixed0].name,"fixed0");
   sdm->q[fixed0].type = dpFixedQ;
   sdm->q[fixed0].joint = base;
   sdm->q[fixed0].axis = 0;
   sdm->q[fixed0].conversion = 57.2957795131;
   sdm->q[fixed0].initial_value = 0.0000000000;
   sdm->q[fixed0].initial_velocity = 0.0;
   sdm->q[fixed0].range_start = -99999.9;
   sdm->q[fixed0].range_end = 99999.9;
   sdm->q[fixed0].restraint_func = NULL;
   sdm->q[fixed0].min_restraint_func = NULL;
   sdm->q[fixed0].max_restraint_func = NULL;
   sdm->q[fixed0].function_active = dpNo;
   sdm->q[fixed0].constraint_func = NULL;
   sdm->q[fixed0].constraint_num = -1;
   sdm->q[fixed0].q_ind = -1;
   sdm->q[fixed0].output = dpNo;
   sdm->q[fixed0].pd_stiffness = 0.0;
   sdm->q[fixed0].torque = 0.0;

   mstrcpy(&sdm->q[fixed1].name,"fixed1");
   sdm->q[fixed1].type = dpFixedQ;
   sdm->q[fixed1].joint = sc1;
   sdm->q[fixed1].axis = 0;
   sdm->q[fixed1].conversion = 57.2957795131;
   sdm->q[fixed1].initial_value = -21.9400000000;
   sdm->q[fixed1].initial_velocity = 0.0;
   sdm->q[fixed1].range_start = -99999.9;
   sdm->q[fixed1].range_end = 99999.9;
   sdm->q[fixed1].restraint_func = NULL;
   sdm->q[fixed1].min_restraint_func = NULL;
   sdm->q[fixed1].max_restraint_func = NULL;
   sdm->q[fixed1].function_active = dpNo;
   sdm->q[fixed1].constraint_func = NULL;
   sdm->q[fixed1].constraint_num = -1;
   sdm->q[fixed1].q_ind = -1;
   sdm->q[fixed1].output = dpNo;
   sdm->q[fixed1].pd_stiffness = 0.0;
   sdm->q[fixed1].torque = 0.0;

   mstrcpy(&sdm->q[fixed2].name,"fixed2");
   sdm->q[fixed2].type = dpFixedQ;
   sdm->q[fixed2].joint = sc2;
   sdm->q[fixed2].axis = 0;
   sdm->q[fixed2].conversion = 57.2957795131;
   sdm->q[fixed2].initial_value = 6.1220000000;
   sdm->q[fixed2].initial_velocity = 0.0;
   sdm->q[fixed2].range_start = -99999.9;
   sdm->q[fixed2].range_end = 99999.9;
   sdm->q[fixed2].restraint_func = NULL;
   sdm->q[fixed2].min_restraint_func = NULL;
   sdm->q[fixed2].max_restraint_func = NULL;
   sdm->q[fixed2].function_active = dpNo;
   sdm->q[fixed2].constraint_func = NULL;
   sdm->q[fixed2].constraint_num = -1;
   sdm->q[fixed2].q_ind = -1;
   sdm->q[fixed2].output = dpNo;
   sdm->q[fixed2].pd_stiffness = 0.0;
   sdm->q[fixed2].torque = 0.0;

   mstrcpy(&sdm->q[fixed3].name,"fixed3");
   sdm->q[fixed3].type = dpFixedQ;
   sdm->q[fixed3].joint = sc3;
   sdm->q[fixed3].axis = 0;
   sdm->q[fixed3].conversion = 57.2957795131;
   sdm->q[fixed3].initial_value = 0.0993490000;
   sdm->q[fixed3].initial_velocity = 0.0;
   sdm->q[fixed3].range_start = -99999.9;
   sdm->q[fixed3].range_end = 99999.9;
   sdm->q[fixed3].restraint_func = NULL;
   sdm->q[fixed3].min_restraint_func = NULL;
   sdm->q[fixed3].max_restraint_func = NULL;
   sdm->q[fixed3].function_active = dpNo;
   sdm->q[fixed3].constraint_func = NULL;
   sdm->q[fixed3].constraint_num = -1;
   sdm->q[fixed3].q_ind = -1;
   sdm->q[fixed3].output = dpNo;
   sdm->q[fixed3].pd_stiffness = 0.0;
   sdm->q[fixed3].torque = 0.0;

   mstrcpy(&sdm->q[fixed4].name,"fixed4");
   sdm->q[fixed4].type = dpFixedQ;
   sdm->q[fixed4].joint = ac1;
   sdm->q[fixed4].axis = 0;
   sdm->q[fixed4].conversion = 57.2957795131;
   sdm->q[fixed4].initial_value = 35.6034080000;
   sdm->q[fixed4].initial_velocity = 0.0;
   sdm->q[fixed4].range_start = -99999.9;
   sdm->q[fixed4].range_end = 99999.9;
   sdm->q[fixed4].restraint_func = NULL;
   sdm->q[fixed4].min_restraint_func = NULL;
   sdm->q[fixed4].max_restraint_func = NULL;
   sdm->q[fixed4].function_active = dpNo;
   sdm->q[fixed4].constraint_func = NULL;
   sdm->q[fixed4].constraint_num = -1;
   sdm->q[fixed4].q_ind = -1;
   sdm->q[fixed4].output = dpNo;
   sdm->q[fixed4].pd_stiffness = 0.0;
   sdm->q[fixed4].torque = 0.0;

   mstrcpy(&sdm->q[fixed5].name,"fixed5");
   sdm->q[fixed5].type = dpFixedQ;
   sdm->q[fixed5].joint = ac2;
   sdm->q[fixed5].axis = 0;
   sdm->q[fixed5].conversion = 57.2957795131;
   sdm->q[fixed5].initial_value = 13.6720190000;
   sdm->q[fixed5].initial_velocity = 0.0;
   sdm->q[fixed5].range_start = -99999.9;
   sdm->q[fixed5].range_end = 99999.9;
   sdm->q[fixed5].restraint_func = NULL;
   sdm->q[fixed5].min_restraint_func = NULL;
   sdm->q[fixed5].max_restraint_func = NULL;
   sdm->q[fixed5].function_active = dpNo;
   sdm->q[fixed5].constraint_func = NULL;
   sdm->q[fixed5].constraint_num = -1;
   sdm->q[fixed5].q_ind = -1;
   sdm->q[fixed5].output = dpNo;
   sdm->q[fixed5].pd_stiffness = 0.0;
   sdm->q[fixed5].torque = 0.0;

   mstrcpy(&sdm->q[fixed6].name,"fixed6");
   sdm->q[fixed6].type = dpFixedQ;
   sdm->q[fixed6].joint = ac3;
   sdm->q[fixed6].axis = 0;
   sdm->q[fixed6].conversion = 57.2957795131;
   sdm->q[fixed6].initial_value = 6.7195400000;
   sdm->q[fixed6].initial_velocity = 0.0;
   sdm->q[fixed6].range_start = -99999.9;
   sdm->q[fixed6].range_end = 99999.9;
   sdm->q[fixed6].restraint_func = NULL;
   sdm->q[fixed6].min_restraint_func = NULL;
   sdm->q[fixed6].max_restraint_func = NULL;
   sdm->q[fixed6].function_active = dpNo;
   sdm->q[fixed6].constraint_func = NULL;
   sdm->q[fixed6].constraint_num = -1;
   sdm->q[fixed6].q_ind = -1;
   sdm->q[fixed6].output = dpNo;
   sdm->q[fixed6].pd_stiffness = 0.0;
   sdm->q[fixed6].torque = 0.0;

   mstrcpy(&sdm->q[GH_y].name,"GH_y");
   sdm->q[GH_y].type = dpUnconstrainedQ;
   sdm->q[GH_y].joint = gh1;
   sdm->q[GH_y].axis = 0;
   sdm->q[GH_y].conversion = 57.2957795131;
   sdm->q[GH_y].initial_value = 20.0000000000;
   sdm->q[GH_y].initial_velocity = 0.0;
   sdm->q[GH_y].range_start = -90.0000000000;
   sdm->q[GH_y].range_end = 90.0000000000;
   sdm->q[GH_y].restraint_func = NULL;
   sdm->q[GH_y].min_restraint_func = NULL;
   sdm->q[GH_y].max_restraint_func = NULL;
   sdm->q[GH_y].function_active = dpNo;
   sdm->q[GH_y].constraint_func = NULL;
   sdm->q[GH_y].constraint_num = -1;
   sdm->q[GH_y].q_ind = -1;
   sdm->q[GH_y].output = dpYes;
   sdm->q[GH_y].pd_stiffness = 0.000000;
   sdm->q[GH_y].torque = 0.0;

   mstrcpy(&sdm->q[GH_z].name,"GH_z");
   sdm->q[GH_z].type = dpUnconstrainedQ;
   sdm->q[GH_z].joint = gh2;
   sdm->q[GH_z].axis = 0;
   sdm->q[GH_z].conversion = 57.2957795131;
   sdm->q[GH_z].initial_value = 30.0000000000;
   sdm->q[GH_z].initial_velocity = 0.0;
   sdm->q[GH_z].range_start = 5.0000000000;
   sdm->q[GH_z].range_end = 90.0000000000;
   sdm->q[GH_z].restraint_func = NULL;
   sdm->q[GH_z].min_restraint_func = NULL;
   sdm->q[GH_z].max_restraint_func = NULL;
   sdm->q[GH_z].function_active = dpNo;
   sdm->q[GH_z].constraint_func = NULL;
   sdm->q[GH_z].constraint_num = -1;
   sdm->q[GH_z].q_ind = -1;
   sdm->q[GH_z].output = dpYes;
   sdm->q[GH_z].pd_stiffness = 0.000000;
   sdm->q[GH_z].torque = 0.0;

   mstrcpy(&sdm->q[GH_yy].name,"GH_yy");
   sdm->q[GH_yy].type = dpUnconstrainedQ;
   sdm->q[GH_yy].joint = gh3;
   sdm->q[GH_yy].axis = 0;
   sdm->q[GH_yy].conversion = 57.2957795131;
   sdm->q[GH_yy].initial_value = -30.0000000000;
   sdm->q[GH_yy].initial_velocity = 0.0;
   sdm->q[GH_yy].range_start = -55.0000000000;
   sdm->q[GH_yy].range_end = 70.0000000000;
   sdm->q[GH_yy].restraint_func = NULL;
   sdm->q[GH_yy].min_restraint_func = NULL;
   sdm->q[GH_yy].max_restraint_func = NULL;
   sdm->q[GH_yy].function_active = dpNo;
   sdm->q[GH_yy].constraint_func = NULL;
   sdm->q[GH_yy].constraint_num = -1;
   sdm->q[GH_yy].q_ind = -1;
   sdm->q[GH_yy].output = dpYes;
   sdm->q[GH_yy].pd_stiffness = 0.000000;
   sdm->q[GH_yy].torque = 0.0;

   mstrcpy(&sdm->q[EL_x].name,"EL_x");
   sdm->q[EL_x].type = dpUnconstrainedQ;
   sdm->q[EL_x].joint = hu;
   sdm->q[EL_x].axis = 0;
   sdm->q[EL_x].conversion = 57.2957795131;
   sdm->q[EL_x].initial_value = 40.0000000000;
   sdm->q[EL_x].initial_velocity = 0.0;
   sdm->q[EL_x].range_start = 5.0000000000;
   sdm->q[EL_x].range_end = 140.0000000000;
   sdm->q[EL_x].restraint_func = NULL;
   sdm->q[EL_x].min_restraint_func = NULL;
   sdm->q[EL_x].max_restraint_func = NULL;
   sdm->q[EL_x].function_active = dpNo;
   sdm->q[EL_x].constraint_func = NULL;
   sdm->q[EL_x].constraint_num = -1;
   sdm->q[EL_x].q_ind = -1;
   sdm->q[EL_x].output = dpYes;
   sdm->q[EL_x].pd_stiffness = 0.000000;
   sdm->q[EL_x].torque = 0.0;

   mstrcpy(&sdm->q[PS_y].name,"PS_y");
   sdm->q[PS_y].type = dpUnconstrainedQ;
   sdm->q[PS_y].joint = ur;
   sdm->q[PS_y].axis = 0;
   sdm->q[PS_y].conversion = 57.2957795131;
   sdm->q[PS_y].initial_value = 90.0000000000;
   sdm->q[PS_y].initial_velocity = 0.0;
   sdm->q[PS_y].range_start = 5.0000000000;
   sdm->q[PS_y].range_end = 160.0000000000;
   sdm->q[PS_y].restraint_func = NULL;
   sdm->q[PS_y].min_restraint_func = NULL;
   sdm->q[PS_y].max_restraint_func = NULL;
   sdm->q[PS_y].function_active = dpNo;
   sdm->q[PS_y].constraint_func = NULL;
   sdm->q[PS_y].constraint_num = -1;
   sdm->q[PS_y].q_ind = -1;
   sdm->q[PS_y].output = dpYes;
   sdm->q[PS_y].pd_stiffness = 0.000000;
   sdm->q[PS_y].torque = 0.0;

   for (i=0, sdm->num_gencoords=0; i<sdm->nq; i++)
      if (sdm->q[i].type == dpUnconstrainedQ)
         sdm->num_gencoords++;

   check_for_sderror("INIT_QS");
}



/* INIT_SEGMENTS: this routine should be called before
 * read_muscles() because it does two things that need to
 * be done before you read in the muscles. First, it assigns
 * numbers to the body segments in your model. These body
 * numbers should match the numbers in the "_info" file
 * that SD/FAST makes. Thus when you read in the muscle
 * attachment points, the segment name listed for each point
 * is converted into an SD/FAST body segment number.
 * Second, this routine records the positions of the mass
 * centers of each body segment. These are the coordinates of
 * the mass centers with respect to the origins of the SIMM
 * bone file. When you read in a muscle attachment point, the
 * mass center coordinates are subtracted from it, so that the
 * muscle point is now w.r.t. the mass center of the body
 * segment, as SD/FAST expects.
 * Note that you cannot use the #defined segment numbers as indices
 * into the sdm->body_segment[] array because they start at -1.
 */

void init_segments(void)
{

   int i, j;
   sdm->body_segment = (dpBodyStruct*)simm_malloc(sdm->num_body_segments*sizeof(dpBodyStruct));

   mstrcpy(&sdm->body_segment[ground+1].name,"ground");
   sdm->body_segment[ground+1].output = dpNo;
   sdm->body_segment[ground+1].mass = 0.0;
   sdm->body_segment[ground+1].mass_center[0] = 0.000000;
   sdm->body_segment[ground+1].mass_center[1] = 0.000000;
   sdm->body_segment[ground+1].mass_center[2] = 0.000000;
   for (i=0; i<3; i++)
      for (j=0; j<3; j++)
         sdm->body_segment[ground+1].inertia[i][j] = 0.0;
   sdm->body_segment[ground+1].contactable = dpNo;

   mstrcpy(&sdm->body_segment[thorax+1].name,"thorax");
   sdm->body_segment[thorax+1].output = dpYes;
   sdgetmass(thorax, &(sdm->body_segment[thorax+1].mass));
   sdgetiner(thorax, sdm->body_segment[thorax+1].inertia);
   sdm->body_segment[thorax+1].mass_center[0] = 0.000000;
   sdm->body_segment[thorax+1].mass_center[1] = -0.148600;
   sdm->body_segment[thorax+1].mass_center[2] = 0.059100;
   sdm->body_segment[thorax+1].contactable = dpNo;

   mstrcpy(&sdm->body_segment[clavicle_1+1].name,"clavicle_1");
   sdm->body_segment[clavicle_1+1].output = dpYes;
   sdgetmass(clavicle_1, &(sdm->body_segment[clavicle_1+1].mass));
   sdgetiner(clavicle_1, sdm->body_segment[clavicle_1+1].inertia);
   sdm->body_segment[clavicle_1+1].mass_center[0] = 0.000000;
   sdm->body_segment[clavicle_1+1].mass_center[1] = 0.000000;
   sdm->body_segment[clavicle_1+1].mass_center[2] = 0.000000;
   sdm->body_segment[clavicle_1+1].contactable = dpNo;

   mstrcpy(&sdm->body_segment[clavicle_2+1].name,"clavicle_2");
   sdm->body_segment[clavicle_2+1].output = dpYes;
   sdgetmass(clavicle_2, &(sdm->body_segment[clavicle_2+1].mass));
   sdgetiner(clavicle_2, sdm->body_segment[clavicle_2+1].inertia);
   sdm->body_segment[clavicle_2+1].mass_center[0] = 0.000000;
   sdm->body_segment[clavicle_2+1].mass_center[1] = 0.000000;
   sdm->body_segment[clavicle_2+1].mass_center[2] = 0.000000;
   sdm->body_segment[clavicle_2+1].contactable = dpNo;

   mstrcpy(&sdm->body_segment[clavicle_r+1].name,"clavicle_r");
   sdm->body_segment[clavicle_r+1].output = dpYes;
   sdgetmass(clavicle_r, &(sdm->body_segment[clavicle_r+1].mass));
   sdgetiner(clavicle_r, sdm->body_segment[clavicle_r+1].inertia);
   sdm->body_segment[clavicle_r+1].mass_center[0] = 0.098300;
   sdm->body_segment[clavicle_r+1].mass_center[1] = 0.016700;
   sdm->body_segment[clavicle_r+1].mass_center[2] = 0.004200;
   sdm->body_segment[clavicle_r+1].contactable = dpNo;

   mstrcpy(&sdm->body_segment[scapula_1+1].name,"scapula_1");
   sdm->body_segment[scapula_1+1].output = dpYes;
   sdgetmass(scapula_1, &(sdm->body_segment[scapula_1+1].mass));
   sdgetiner(scapula_1, sdm->body_segment[scapula_1+1].inertia);
   sdm->body_segment[scapula_1+1].mass_center[0] = 0.000000;
   sdm->body_segment[scapula_1+1].mass_center[1] = 0.000000;
   sdm->body_segment[scapula_1+1].mass_center[2] = 0.000000;
   sdm->body_segment[scapula_1+1].contactable = dpNo;

   mstrcpy(&sdm->body_segment[scapula_2+1].name,"scapula_2");
   sdm->body_segment[scapula_2+1].output = dpYes;
   sdgetmass(scapula_2, &(sdm->body_segment[scapula_2+1].mass));
   sdgetiner(scapula_2, sdm->body_segment[scapula_2+1].inertia);
   sdm->body_segment[scapula_2+1].mass_center[0] = 0.000000;
   sdm->body_segment[scapula_2+1].mass_center[1] = 0.000000;
   sdm->body_segment[scapula_2+1].mass_center[2] = 0.000000;
   sdm->body_segment[scapula_2+1].contactable = dpNo;

   mstrcpy(&sdm->body_segment[scapula_r+1].name,"scapula_r");
   sdm->body_segment[scapula_r+1].output = dpYes;
   sdgetmass(scapula_r, &(sdm->body_segment[scapula_r+1].mass));
   sdgetiner(scapula_r, sdm->body_segment[scapula_r+1].inertia);
   sdm->body_segment[scapula_r+1].mass_center[0] = -0.053000;
   sdm->body_segment[scapula_r+1].mass_center[1] = -0.022900;
   sdm->body_segment[scapula_r+1].mass_center[2] = -0.024700;
   sdm->body_segment[scapula_r+1].contactable = dpNo;

   mstrcpy(&sdm->body_segment[humerus_1+1].name,"humerus_1");
   sdm->body_segment[humerus_1+1].output = dpYes;
   sdgetmass(humerus_1, &(sdm->body_segment[humerus_1+1].mass));
   sdgetiner(humerus_1, sdm->body_segment[humerus_1+1].inertia);
   sdm->body_segment[humerus_1+1].mass_center[0] = 0.000000;
   sdm->body_segment[humerus_1+1].mass_center[1] = 0.000000;
   sdm->body_segment[humerus_1+1].mass_center[2] = 0.000000;
   sdm->body_segment[humerus_1+1].contactable = dpNo;

   mstrcpy(&sdm->body_segment[humerus_2+1].name,"humerus_2");
   sdm->body_segment[humerus_2+1].output = dpYes;
   sdgetmass(humerus_2, &(sdm->body_segment[humerus_2+1].mass));
   sdgetiner(humerus_2, sdm->body_segment[humerus_2+1].inertia);
   sdm->body_segment[humerus_2+1].mass_center[0] = 0.000000;
   sdm->body_segment[humerus_2+1].mass_center[1] = 0.000000;
   sdm->body_segment[humerus_2+1].mass_center[2] = 0.000000;
   sdm->body_segment[humerus_2+1].contactable = dpNo;

   mstrcpy(&sdm->body_segment[humerus_r+1].name,"humerus_r");
   sdm->body_segment[humerus_r+1].output = dpYes;
   sdgetmass(humerus_r, &(sdm->body_segment[humerus_r+1].mass));
   sdgetiner(humerus_r, sdm->body_segment[humerus_r+1].inertia);
   sdm->body_segment[humerus_r+1].mass_center[0] = 0.006400;
   sdm->body_segment[humerus_r+1].mass_center[1] = -0.077600;
   sdm->body_segment[humerus_r+1].mass_center[2] = -0.003600;
   sdm->body_segment[humerus_r+1].contactable = dpNo;

   mstrcpy(&sdm->body_segment[ulna_r+1].name,"ulna_r");
   sdm->body_segment[ulna_r+1].output = dpYes;
   sdgetmass(ulna_r, &(sdm->body_segment[ulna_r+1].mass));
   sdgetiner(ulna_r, sdm->body_segment[ulna_r+1].inertia);
   sdm->body_segment[ulna_r+1].mass_center[0] = -0.000300;
   sdm->body_segment[ulna_r+1].mass_center[1] = -0.063400;
   sdm->body_segment[ulna_r+1].mass_center[2] = -0.003900;
   sdm->body_segment[ulna_r+1].contactable = dpNo;

   mstrcpy(&sdm->body_segment[radius_r+1].name,"radius_r");
   sdm->body_segment[radius_r+1].output = dpYes;
   sdgetmass(radius_r, &(sdm->body_segment[radius_r+1].mass));
   sdgetiner(radius_r, sdm->body_segment[radius_r+1].inertia);
   sdm->body_segment[radius_r+1].mass_center[0] = 0.010600;
   sdm->body_segment[radius_r+1].mass_center[1] = -0.117900;
   sdm->body_segment[radius_r+1].mass_center[2] = -0.012900;
   sdm->body_segment[radius_r+1].contactable = dpNo;

   mstrcpy(&sdm->name, "DAS2");

   check_for_sderror("INIT_SEGMENTS");

}



/* INIT_Q_RESTRAINT_FUNCTIONS: this routine initializes the restraint
 * functions which are used to keep the Qs from exceeding their ranges of motion.
 */

void init_q_restraint_functions(void)
{

   int i, numpts;

   /* There are no user-defined restraints in this model */

}


/* INIT_JOINT_FUNCTIONS: this routine initializes the constraint functions
 * for the joints which have user-defined constraints.
 */

void init_joint_functions(void)
{

   int i, numpts;

   /* There are no user-defined constraints in this model */

}


void init_wrap_objects(void)
{

   int i;

   /* The from_local_xforms in this array of wrap objects are expressed relative to
    * the origin of the SIMM segment reference frame. The to_local_xforms are filled in with
    * zeros-- those transforms are calculated later, directly from the to_local_xforms.
    */
   dpWrapObject wrap_object[] = {
   {"serr_ant", dpWrapEllipsoid, dpYes, 0, 0, 0.1470000000, 0.2079000000, 0.0944000000, 0.1000000000, 0, 0,
   {1.0000000000, 0.0000000000, 0.0000000000, 0.0000000000,
    0.0000000000, 1.0000000000, 0.0000000000, 0.0000000000,
    0.0000000000, 0.0000000000, 1.0000000000, 0.0000000000,
    0.0000000000, -0.1486000000, 0.0591000000, 1.0000000000},
   },
   {"deltoid", dpWrapSphere, dpYes, 0, 9, 0.0272000000, 0.1000000000, 0.0500000000, 0.1000000000, 0, 0,
   {0.9003973766, -0.3273212805, 0.2866100898, 0.0000000000,
    0.3656134611, 0.9263400983, -0.0906687344, 0.0000000000,
    -0.2358206125, 0.1864263975, 0.9537472606, 0.0000000000,
    0.0022000000, -0.0009000000, -0.0018000000, 1.0000000000},
   },
   {"inf_sup_sub", dpWrapSphere, dpYes, 0, 9, 0.0231000000, 0.1000000000, 0.0500000000, 0.1000000000, 0, 0,
   {0.9003973766, -0.3273212805, 0.2866100898, 0.0000000000,
    0.3656134611, 0.9263400983, -0.0906687344, 0.0000000000,
    -0.2358206125, 0.1864263975, 0.9537472606, 0.0000000000,
    -0.0017000000, 0.0018000000, -0.0013000000, 1.0000000000},
   },
   {"infra_cyl", dpWrapCylinder, dpYes, 0, 9, 0.0140000000, 0.1000000000, 0.0500000000, 0.1200000000, 0, -1,
   {0.5791280914, -0.0000193932, -0.8152365628, 0.0000000000,
    0.8152136766, 0.0075068336, 0.5791116550, 0.0000000000,
    0.0061086144, -0.9999718231, 0.0043632279, 0.0000000000,
    0.0054000000, -0.0230000000, -0.0044000000, 1.0000000000},
   },
   {"ter_min_cyl", dpWrapCylinder, dpYes, 0, 9, 0.0150000000, 0.1000000000, 0.0500000000, 0.1000000000, 0, -1,
   {0.0939328009, -0.0037702119, -0.9955714010, 0.0000000000,
    0.9955597992, 0.0064914120, 0.0939071234, 0.0000000000,
    0.0061086144, -0.9999718231, 0.0043632279, 0.0000000000,
    0.0054000000, -0.0230000000, -0.0044000000, 1.0000000000},
   },
   {"ter_lat_pec", dpWrapCylinder, dpYes, 0, 9, 0.0100000000, 0.1000000000, 0.0500000000, 0.1000000000, 0, 0,
   {0.5791280914, -0.0000193932, -0.8152365628, 0.0000000000,
    0.8152136766, 0.0075068336, 0.5791116550, 0.0000000000,
    0.0061086144, -0.9999718231, 0.0043632279, 0.0000000000,
    0.0057000000, -0.0730000000, -0.0042000000, 1.0000000000},
   },
   {"radius", dpWrapCylinder, dpYes, 0, 11, 0.0092000000, 0.1000000000, 0.0500000000, 0.2000000000, 0, -1,
   {-0.2006611547, 0.0000414784, 0.9796607062, 0.0000000000,
    0.9588386196, 0.2050864085, 0.1963875419, 0.0000000000,
    -0.2009069500, 0.9787438701, -0.0411926466, 0.0000000000,
    0.0035000000, -0.0322000000, -0.0003000000, 1.0000000000},
   },
   {"elbow", dpWrapCylinder, dpYes, 0, 10, 0.0190000000, 0.1000000000, 0.0500000000, 0.0500000000, 1, 1,
   {-0.0227947788, 0.2771517316, -0.9605557328, 0.0000000000,
    -0.0082966210, 0.9607198555, 0.2773959720, 0.0000000000,
    0.9997057388, 0.0142925467, -0.0195999737, 0.0000000000,
    0.0000000000, 0.0000000000, 0.0000000000, 1.0000000000},
   },
   {"elbow_circ", dpWrapCylinder, dpYes, 0, 10, 0.0150000000, 0.1000000000, 0.0500000000, 0.0500000000, 0, 0,
   {0.0242576970, -0.5890229797, 0.8077521238, 0.0000000000,
    0.0000000000, 0.8079898839, 0.5891963574, 0.0000000000,
    -0.9997057388, -0.0142925467, 0.0195999737, 0.0000000000,
    0.0000000000, 0.0000000000, 0.0000000000, 1.0000000000},
   },
   {"supinator", dpWrapCylinder, dpYes, 0, 11, 0.0090000000, 0.1000000000, 0.0500000000, 0.2000000000, 1, -1,
   {0.9999984769, -0.0017394595, -0.0001430096, 0.0000000000,
    0.0000000000, 0.0819385086, -0.9966373868, 0.0000000000,
    0.0017453284, 0.9966358689, 0.0819383838, 0.0000000000,
    0.0034000000, -0.1196000000, -0.0069000000, 1.0000000000},
   },
   {"pron_quad", dpWrapCylinder, dpYes, 0, 10, 0.0070000000, 0.1000000000, 0.0500000000, 0.1000000000, 1, 1,
   {0.9730582856, 0.2214046024, 0.0643239832, 0.0000000000,
    -0.0000000000, 0.2789911060, -0.9602936857, 0.0000000000,
    -0.2305592609, 0.9344217275, 0.2714746073, 0.0000000000,
    0.0365000000, -0.2064000000, -0.0577000000, 1.0000000000},
   },
   {"ulna_radius", dpWrapCylinder, dpYes, 0, 11, 0.0071000000, 0.1000000000, 0.0500000000, 0.1000000000, 0, -1,
   {-0.8619207496, -0.2121511809, 0.4605263269, 0.0000000000,
    -0.4391705574, -0.1415874261, -0.8871765452, 0.0000000000,
    0.2534202890, -0.9669254766, 0.0288665881, 0.0000000000,
    0.0146000000, -0.0891000000, 0.0003000000, 1.0000000000},
   }
   };

   sdm->num_wrap_objects = 12;

   sdm->wrap_object = (dpWrapObject*)simm_malloc(sdm->num_wrap_objects * sizeof(dpWrapObject));

   /* Copy the wrap objects into the sdm structure, and adjust the transforms so that they
    * are relative to the mass center of the segment. Then compute the to_local_xform as the
    * inverse of the from_local_xform.
    */
   for (i = 0; i < sdm->num_wrap_objects; i++)
   {
      sdm->wrap_object[i] = wrap_object[i];
      mstrcpy(&sdm->wrap_object[i].name, wrap_object[i].name);
      sdm->wrap_object[i].from_local_xform[3][XX] -= sdm->body_segment[sdm->wrap_object[i].segment+1].mass_center[XX];
      sdm->wrap_object[i].from_local_xform[3][YY] -= sdm->body_segment[sdm->wrap_object[i].segment+1].mass_center[YY];
      sdm->wrap_object[i].from_local_xform[3][ZZ] -= sdm->body_segment[sdm->wrap_object[i].segment+1].mass_center[ZZ];
      invert_4x4transform(sdm->wrap_object[i].from_local_xform, sdm->wrap_object[i].to_local_xform);
   }
}

void init_constraint_objects(void)
{

   /* There are no constraint objects in this model. */

  sdm->num_constraint_objects = 0;
  sdm->constraint_object = NULL;
}

