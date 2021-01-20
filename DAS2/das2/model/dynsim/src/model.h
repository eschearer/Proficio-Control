/*******************************************************************************

   E:\das\das_models\trunk\das2\model\dynsim\src\model.h

   Created by SIMM 4.1.1 (from joint file E:\das\das_models\trunk\das2\model\das2.jnt)

   Time of creation: 11/20/2007 04:34:33 PM

*******************************************************************************/

/*********** Joints ************/
#define                   base  0
#define                    sc1  1
#define                    sc2  2
#define                    sc3  3
#define                    ac1  4
#define                    ac2  5
#define                    ac3  6
#define                    gh1  7
#define                    gh2  8
#define                    gh3  9
#define                     hu 10
#define                     ur 11

/************* Qs **************/
#define                 fixed0  0   /* = sdindx(base,0) */
#define                 fixed1  1   /* = sdindx(sc1,0) */
#define                 fixed2  2   /* = sdindx(sc2,0) */
#define                 fixed3  3   /* = sdindx(sc3,0) */
#define                 fixed4  4   /* = sdindx(ac1,0) */
#define                 fixed5  5   /* = sdindx(ac2,0) */
#define                 fixed6  6   /* = sdindx(ac3,0) */
#define                   GH_y  7   /* = sdindx(gh1,0) */
#define                   GH_z  8   /* = sdindx(gh2,0) */
#define                  GH_yy  9   /* = sdindx(gh3,0) */
#define                   EL_x 10   /* = sdindx(hu,0) */
#define                   PS_y 11   /* = sdindx(ur,0) */

/******* Constrained Qs ********/

/******** Body Segments ********/
#define                 ground -1
#define                 thorax  0
#define             clavicle_1  1
#define             clavicle_2  2
#define             clavicle_r  3
#define              scapula_1  4
#define              scapula_2  5
#define              scapula_r  6
#define              humerus_1  7
#define              humerus_2  8
#define              humerus_r  9
#define                 ulna_r 10
#define               radius_r 11
