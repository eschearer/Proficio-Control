/*
Generated 14-Nov-2007 16:57:48 by SD/FAST, Order(N) formulation
(sdfast B.2.8 #30123) on machine ID unknown
Copyright (c) 1990-1997 Symbolic Dynamics, Inc.
Copyright (c) 1990-1997 Parametric Technology Corp.
RESTRICTED RIGHTS LEGEND: Use, duplication, or disclosure by the U.S.
Government is subject to restrictions as set forth in subparagraph
(c)(1)(ii) of the Rights in Technical Data and Computer Software
clause at DFARS 52.227-7013 and similar clauses in the FAR and NASA
FAR Supplement.  Symbolic Dynamics, Inc., Mountain View, CA 94041


ROADMAP (../model/dynsim/src/das2.sd)

Bodies         Inb
No  Name       body Joint type  Coords q
--- ---------- ---- ----------- ----------------
 -1 $ground                                     
  0 thorax      -1  Weld                        
  1 clavicle_1   0  Weld                        
  2 clavicle_2   1  Weld                        
  3 clavicle_r   2  Weld                        
  4 scapula_1    3  Weld                        
  5 scapula_2    4  Weld                        
  6 scapula_r    5  Weld                        
  7 humerus_1    6  Pin           0             
  8 humerus_2    7  Pin           1             
  9 humerus_r    8  Pin           2             
 10 ulna_r       9  Pin           3             
 11 radius_r    10  Pin           4             

*/
#include <math.h>
#include <stdio.h>

typedef struct {
    int ground_,nbod_,ndof_,ncons_,nloop_,nldof_,nloopc_,nball_,nlball_,npres_,
      nuser_;
    int jtype_[12],inb_[12],outb_[12],njntdof_[12],njntc_[12],njntp_[12],firstq_
      [12],ballq_[12],firstm_[12],firstp_[12];
    int trans_[5];
} sdgtopo_t;
#define ground (sdgtopo.ground_)
#define nbod (sdgtopo.nbod_)
#define ndof (sdgtopo.ndof_)
#define ncons (sdgtopo.ncons_)
#define nloop (sdgtopo.nloop_)
#define nldof (sdgtopo.nldof_)
#define nloopc (sdgtopo.nloopc_)
#define nball (sdgtopo.nball_)
#define nlball (sdgtopo.nlball_)
#define npres (sdgtopo.npres_)
#define nuser (sdgtopo.nuser_)
#define jtype (sdgtopo.jtype_)
#define inb (sdgtopo.inb_)
#define outb (sdgtopo.outb_)
#define njntdof (sdgtopo.njntdof_)
#define njntc (sdgtopo.njntc_)
#define njntp (sdgtopo.njntp_)
#define firstq (sdgtopo.firstq_)
#define ballq (sdgtopo.ballq_)
#define firstm (sdgtopo.firstm_)
#define firstp (sdgtopo.firstp_)
#define trans (sdgtopo.trans_)

typedef struct {
    double grav_[3],mk_[12],ik_[12][3][3],pin_[5][3];
    double rk_[12][3],ri_[12][3],pres_[5],stabvel_,stabpos_;
    int mfrcflg_,roustate_,vpkflg_,inerflg_,mmflg_,mmlduflg_,wwflg_,ltauflg_,
      fs0flg_,ii_,mmap_[5];
    int gravq_[3],mkq_[12],ikq_[12][3][3],pinq_[5][3],rkq_[12][3],riq_[12][3],
      presq_[5],stabvelq_,stabposq_;
    double mtot_,psmkg_,rhead_[12][3],rcom_[12][3],mkrcomt_[12][3][3],psikg_[3][
      3],psrcomg_[3],psrkg_[3],psrig_[3],psmk_[5],psik_[5][3][3],psrcom_[5][3],
      psrk_[5][3],psri_[5][3];
} sdginput_t;
#define grav (sdginput.grav_)
#define mk (sdginput.mk_)
#define ik (sdginput.ik_)
#define pin (sdginput.pin_)
#define rk (sdginput.rk_)
#define ri (sdginput.ri_)
#define pres (sdginput.pres_)
#define stabvel (sdginput.stabvel_)
#define stabpos (sdginput.stabpos_)
#define rhead (sdginput.rhead_)
#define rcom (sdginput.rcom_)
#define psrcomg (sdginput.psrcomg_)
#define psrcom (sdginput.psrcom_)
#define mkrcomt (sdginput.mkrcomt_)
#define psmk (sdginput.psmk_)
#define psik (sdginput.psik_)
#define psrk (sdginput.psrk_)
#define psri (sdginput.psri_)
#define psmkg (sdginput.psmkg_)
#define psikg (sdginput.psikg_)
#define psrkg (sdginput.psrkg_)
#define psrig (sdginput.psrig_)
#define mtot (sdginput.mtot_)
#define mfrcflg (sdginput.mfrcflg_)
#define roustate (sdginput.roustate_)
#define vpkflg (sdginput.vpkflg_)
#define inerflg (sdginput.inerflg_)
#define mmflg (sdginput.mmflg_)
#define mmlduflg (sdginput.mmlduflg_)
#define wwflg (sdginput.wwflg_)
#define ltauflg (sdginput.ltauflg_)
#define fs0flg (sdginput.fs0flg_)
#define ii (sdginput.ii_)
#define mmap (sdginput.mmap_)
#define gravq (sdginput.gravq_)
#define mkq (sdginput.mkq_)
#define ikq (sdginput.ikq_)
#define pinq (sdginput.pinq_)
#define rkq (sdginput.rkq_)
#define riq (sdginput.riq_)
#define presq (sdginput.presq_)
#define stabvelq (sdginput.stabvelq_)
#define stabposq (sdginput.stabposq_)

typedef struct {
    double curtim_,q_[5],qn_[5],u_[5],cnk_[5][3][3],cnb_[12][3][3];
    double rnk_[5][3],vnk_[5][3],wk_[5][3],rnb_[12][3],vnb_[12][3],wb_[12][3],
      wbrcom_[12][3],com_[3],rnkg_[3];
    double Cik_[5][3][3],rikt_[5][3][3],Iko_[5][3][3],mkrk_[5][3][3],Cib_[12][3
      ][3];
    double Wkk_[5][3],Vkk_[5][3],dik_[5][3],rpp_[5][3],rpk_[5][3],rik_[5][3],
      rik2_[5][3];
    double rpri_[5][3],Wik_[5][3],Vik_[5][3],Wirk_[5][3],rkWkk_[5][3],Wkrpk_[5][
      3],VikWkr_[5][3];
    double perr_[1],verr_[1],aerr_[1],mult_[1],ufk_[12][3],utk_[12][3],mfk_[12][
      3],mtk_[12][3];
    double utau_[5],mtau_[5],uacc_[5],uvel_[5],upos_[5];
    double s0_,c0_,s1_,c1_,s2_,c2_,s3_,c3_,s4_,c4_;
} sdgstate_t;
#define curtim (sdgstate.curtim_)
#define q (sdgstate.q_)
#define qn (sdgstate.qn_)
#define u (sdgstate.u_)
#define cnk (sdgstate.cnk_)
#define cnb (sdgstate.cnb_)
#define rnkg (sdgstate.rnkg_)
#define rnk (sdgstate.rnk_)
#define rnb (sdgstate.rnb_)
#define vnk (sdgstate.vnk_)
#define vnb (sdgstate.vnb_)
#define wk (sdgstate.wk_)
#define wb (sdgstate.wb_)
#define com (sdgstate.com_)
#define Cik (sdgstate.Cik_)
#define Cib (sdgstate.Cib_)
#define rikt (sdgstate.rikt_)
#define Iko (sdgstate.Iko_)
#define mkrk (sdgstate.mkrk_)
#define Wkk (sdgstate.Wkk_)
#define Vkk (sdgstate.Vkk_)
#define dik (sdgstate.dik_)
#define rpp (sdgstate.rpp_)
#define rpk (sdgstate.rpk_)
#define rik (sdgstate.rik_)
#define rik2 (sdgstate.rik2_)
#define rpri (sdgstate.rpri_)
#define Wik (sdgstate.Wik_)
#define Vik (sdgstate.Vik_)
#define Wirk (sdgstate.Wirk_)
#define rkWkk (sdgstate.rkWkk_)
#define Wkrpk (sdgstate.Wkrpk_)
#define VikWkr (sdgstate.VikWkr_)
#define wbrcom (sdgstate.wbrcom_)
#define perr (sdgstate.perr_)
#define verr (sdgstate.verr_)
#define aerr (sdgstate.aerr_)
#define mult (sdgstate.mult_)
#define ufk (sdgstate.ufk_)
#define utk (sdgstate.utk_)
#define utau (sdgstate.utau_)
#define mfk (sdgstate.mfk_)
#define mtk (sdgstate.mtk_)
#define mtau (sdgstate.mtau_)
#define uacc (sdgstate.uacc_)
#define uvel (sdgstate.uvel_)
#define upos (sdgstate.upos_)
#define s0 (sdgstate.s0_)
#define c0 (sdgstate.c0_)
#define s1 (sdgstate.s1_)
#define c1 (sdgstate.c1_)
#define s2 (sdgstate.s2_)
#define c2 (sdgstate.c2_)
#define s3 (sdgstate.s3_)
#define c3 (sdgstate.c3_)
#define s4 (sdgstate.s4_)
#define c4 (sdgstate.c4_)

typedef struct {
    double fs0_[5],qdot_[5],Otk_[5][3],Atk_[5][3],AiOiWi_[5][3],Fstar_[5][3];
    double Tstar_[5][3],Fstark_[5][3],Tstark_[5][3],IkWk_[5][3],WkIkWk_[5][3],
      gk_[5][3],IkbWk_[12][3],WkIkbWk_[12][3];
    double w0w0_[12],w1w1_[12],w2w2_[12],w0w1_[12],w0w2_[12],w1w2_[12];
    double w00w11_[12],w00w22_[12],w11w22_[12],ww_[1][1],qraux_[1];
    double DD_[5],PH1_[5][3],PH2_[5][3],HL1_[5][3],HL2_[5][3],G1_[5][3],G2_[5][3
      ];
    double P11_[5][3][3],Pd_[5][3][3],P22_[5][3][3],L11_[5][3][3],L21_[5][3][3],
      L22_[5][3][3],D11_[5][3][3],D22_[5][3][3];
    double N11_[5][3][3],N21_[5][3][3],N22_[5][3][3],psi11_[5][3][3],psi12_[5][3
      ][3],psi21_[5][3][3],psi22_[5][3][3];
    double psiD11_[5][3][3],psiD12_[5][3][3],psiD21_[5][3][3],psiD22_[5][3][3];
    double sL11_[3][3],sL21_[3][3],sL22_[3][3],sD1_[3][3],sD2_[3][3];
    double sD1INV_[3][3],sD2INV_[3][3],sL11D1_[3][3],sL22D2_[3][3],sD1L21_[3][3]
      ;
    double ping_[5][3],hngpt_[5][3];
    int wmap_[1],multmap_[1],jpvt_[1],wsiz_,wrank_;
} sdglhs_t;
#define qdot (sdglhs.qdot_)
#define Otk (sdglhs.Otk_)
#define Atk (sdglhs.Atk_)
#define AiOiWi (sdglhs.AiOiWi_)
#define Fstar (sdglhs.Fstar_)
#define Tstar (sdglhs.Tstar_)
#define fs0 (sdglhs.fs0_)
#define Fstark (sdglhs.Fstark_)
#define Tstark (sdglhs.Tstark_)
#define IkWk (sdglhs.IkWk_)
#define IkbWk (sdglhs.IkbWk_)
#define WkIkWk (sdglhs.WkIkWk_)
#define WkIkbWk (sdglhs.WkIkbWk_)
#define gk (sdglhs.gk_)
#define w0w0 (sdglhs.w0w0_)
#define w1w1 (sdglhs.w1w1_)
#define w2w2 (sdglhs.w2w2_)
#define w0w1 (sdglhs.w0w1_)
#define w0w2 (sdglhs.w0w2_)
#define w1w2 (sdglhs.w1w2_)
#define w00w11 (sdglhs.w00w11_)
#define w00w22 (sdglhs.w00w22_)
#define w11w22 (sdglhs.w11w22_)
#define ww (sdglhs.ww_)
#define qraux (sdglhs.qraux_)
#define PH1 (sdglhs.PH1_)
#define PH2 (sdglhs.PH2_)
#define P11 (sdglhs.P11_)
#define Pd (sdglhs.Pd_)
#define P22 (sdglhs.P22_)
#define L11 (sdglhs.L11_)
#define L21 (sdglhs.L21_)
#define L22 (sdglhs.L22_)
#define D11 (sdglhs.D11_)
#define D22 (sdglhs.D22_)
#define N11 (sdglhs.N11_)
#define N21 (sdglhs.N21_)
#define N22 (sdglhs.N22_)
#define HL1 (sdglhs.HL1_)
#define HL2 (sdglhs.HL2_)
#define psi11 (sdglhs.psi11_)
#define psi12 (sdglhs.psi12_)
#define psi21 (sdglhs.psi21_)
#define psi22 (sdglhs.psi22_)
#define psiD11 (sdglhs.psiD11_)
#define psiD12 (sdglhs.psiD12_)
#define psiD21 (sdglhs.psiD21_)
#define psiD22 (sdglhs.psiD22_)
#define sL11 (sdglhs.sL11_)
#define sL21 (sdglhs.sL21_)
#define sL22 (sdglhs.sL22_)
#define sD1 (sdglhs.sD1_)
#define sD2 (sdglhs.sD2_)
#define sD1INV (sdglhs.sD1INV_)
#define sD2INV (sdglhs.sD2INV_)
#define sL11D1 (sdglhs.sL11D1_)
#define sL22D2 (sdglhs.sL22D2_)
#define sD1L21 (sdglhs.sD1L21_)
#define DD (sdglhs.DD_)
#define G1 (sdglhs.G1_)
#define G2 (sdglhs.G2_)
#define ping (sdglhs.ping_)
#define hngpt (sdglhs.hngpt_)
#define wmap (sdglhs.wmap_)
#define multmap (sdglhs.multmap_)
#define jpvt (sdglhs.jpvt_)
#define wsiz (sdglhs.wsiz_)
#define wrank (sdglhs.wrank_)

typedef struct {
    double fs_[5],udot_[5],tauc_[5],dyad_[12][3][3],fc_[5][3],tc_[5][3];
    double ank_[5][3],onk_[5][3],Onkb_[5][3],AOnkri_[5][3],Ankb_[5][3],AnkAtk_[5
      ][3],anb_[12][3],onb_[12][3],dyrcom_[12][3];
    double ffk_[5][3],ttk_[5][3],fccikt_[5][3],ffkb_[12][3],ttkb_[12][3];
} sdgrhs_t;
#define fs (sdgrhs.fs_)
#define udot (sdgrhs.udot_)
#define ank (sdgrhs.ank_)
#define anb (sdgrhs.anb_)
#define onk (sdgrhs.onk_)
#define onb (sdgrhs.onb_)
#define Onkb (sdgrhs.Onkb_)
#define AOnkri (sdgrhs.AOnkri_)
#define Ankb (sdgrhs.Ankb_)
#define AnkAtk (sdgrhs.AnkAtk_)
#define dyrcom (sdgrhs.dyrcom_)
#define ffk (sdgrhs.ffk_)
#define ttk (sdgrhs.ttk_)
#define fccikt (sdgrhs.fccikt_)
#define ffkb (sdgrhs.ffkb_)
#define ttkb (sdgrhs.ttkb_)
#define dyad (sdgrhs.dyad_)
#define fc (sdgrhs.fc_)
#define tc (sdgrhs.tc_)
#define tauc (sdgrhs.tauc_)

typedef struct {
    double temp_[3000],tmat1_[3][3],tmat2_[3][3],tvec1_[3],tvec2_[3],tvec3_[3],
      tvec4_[3],tvec5_[3];
    double tsc1_,tsc2_,tsc3_;
} sdgtemp_t;
#define temp (sdgtemp.temp_)
#define tmat1 (sdgtemp.tmat1_)
#define tmat2 (sdgtemp.tmat2_)
#define tvec1 (sdgtemp.tvec1_)
#define tvec2 (sdgtemp.tvec2_)
#define tvec3 (sdgtemp.tvec3_)
#define tvec4 (sdgtemp.tvec4_)
#define tvec5 (sdgtemp.tvec5_)
#define tsc1 (sdgtemp.tsc1_)
#define tsc2 (sdgtemp.tsc2_)
#define tsc3 (sdgtemp.tsc3_)

sdgtopo_t sdgtopo = {
/*  Topological information
*/
    /* ground */ 1,
    /* nbod */ 12,
    /* ndof */ 5,
    /* ncons */ 0,
    /* nloop */ 0,
    /* nldof */ 0,
    /* nloopc */ 0,
    /* nball */ 0,
    /* nlball */ 0,
    /* npres */ 0,
    /* nuser */ 0,
    /* jtype[0] */ 9,
    /* jtype[1] */ 9,
    /* jtype[2] */ 9,
    /* jtype[3] */ 9,
    /* jtype[4] */ 9,
    /* jtype[5] */ 9,
    /* jtype[6] */ 9,
    /* jtype[7] */ 1,
    /* jtype[8] */ 1,
    /* jtype[9] */ 1,
    /* jtype[10] */ 1,
    /* jtype[11] */ 1,
    /* inb[0] */ -1,
    /* inb[1] */ 0,
    /* inb[2] */ 1,
    /* inb[3] */ 2,
    /* inb[4] */ 3,
    /* inb[5] */ 4,
    /* inb[6] */ 5,
    /* inb[7] */ 6,
    /* inb[8] */ 7,
    /* inb[9] */ 8,
    /* inb[10] */ 9,
    /* inb[11] */ 10,
    /* outb[0] */ 0,
    /* outb[1] */ 1,
    /* outb[2] */ 2,
    /* outb[3] */ 3,
    /* outb[4] */ 4,
    /* outb[5] */ 5,
    /* outb[6] */ 6,
    /* outb[7] */ 7,
    /* outb[8] */ 8,
    /* outb[9] */ 9,
    /* outb[10] */ 10,
    /* outb[11] */ 11,
    /* njntdof[0] */ 0,
    /* njntdof[1] */ 0,
    /* njntdof[2] */ 0,
    /* njntdof[3] */ 0,
    /* njntdof[4] */ 0,
    /* njntdof[5] */ 0,
    /* njntdof[6] */ 0,
    /* njntdof[7] */ 1,
    /* njntdof[8] */ 1,
    /* njntdof[9] */ 1,
    /* njntdof[10] */ 1,
    /* njntdof[11] */ 1,
    /* njntc[0] */ 0,
    /* njntc[1] */ 0,
    /* njntc[2] */ 0,
    /* njntc[3] */ 0,
    /* njntc[4] */ 0,
    /* njntc[5] */ 0,
    /* njntc[6] */ 0,
    /* njntc[7] */ 0,
    /* njntc[8] */ 0,
    /* njntc[9] */ 0,
    /* njntc[10] */ 0,
    /* njntc[11] */ 0,
    /* njntp[0] */ 0,
    /* njntp[1] */ 0,
    /* njntp[2] */ 0,
    /* njntp[3] */ 0,
    /* njntp[4] */ 0,
    /* njntp[5] */ 0,
    /* njntp[6] */ 0,
    /* njntp[7] */ 0,
    /* njntp[8] */ 0,
    /* njntp[9] */ 0,
    /* njntp[10] */ 0,
    /* njntp[11] */ 0,
    /* firstq[0] */ 0,
    /* firstq[1] */ 0,
    /* firstq[2] */ 0,
    /* firstq[3] */ 0,
    /* firstq[4] */ 0,
    /* firstq[5] */ 0,
    /* firstq[6] */ 0,
    /* firstq[7] */ 0,
    /* firstq[8] */ 1,
    /* firstq[9] */ 2,
    /* firstq[10] */ 3,
    /* firstq[11] */ 4,
    /* ballq[0] */ -104,
    /* ballq[1] */ -104,
    /* ballq[2] */ -104,
    /* ballq[3] */ -104,
    /* ballq[4] */ -104,
    /* ballq[5] */ -104,
    /* ballq[6] */ -104,
    /* ballq[7] */ -104,
    /* ballq[8] */ -104,
    /* ballq[9] */ -104,
    /* ballq[10] */ -104,
    /* ballq[11] */ -104,
    /* firstm[0] */ -1,
    /* firstm[1] */ -1,
    /* firstm[2] */ -1,
    /* firstm[3] */ -1,
    /* firstm[4] */ -1,
    /* firstm[5] */ -1,
    /* firstm[6] */ -1,
    /* firstm[7] */ -1,
    /* firstm[8] */ -1,
    /* firstm[9] */ -1,
    /* firstm[10] */ -1,
    /* firstm[11] */ -1,
    /* firstp[0] */ -1,
    /* firstp[1] */ -1,
    /* firstp[2] */ -1,
    /* firstp[3] */ -1,
    /* firstp[4] */ -1,
    /* firstp[5] */ -1,
    /* firstp[6] */ -1,
    /* firstp[7] */ -1,
    /* firstp[8] */ -1,
    /* firstp[9] */ -1,
    /* firstp[10] */ -1,
    /* firstp[11] */ -1,
    /* trans[0] */ 0,
    /* trans[1] */ 0,
    /* trans[2] */ 0,
    /* trans[3] */ 0,
    /* trans[4] */ 0,
};
sdginput_t sdginput = {
/* Model parameters from the input file */

/* gravity */
    /* grav[0] */ 0.,
    /* grav[1] */ -9.80665,
    /* grav[2] */ 0.,

/* mass */
    /* mk[0] */ 20.,
    /* mk[1] */ 0.,
    /* mk[2] */ 0.,
    /* mk[3] */ .156,
    /* mk[4] */ 0.,
    /* mk[5] */ 0.,
    /* mk[6] */ .7054,
    /* mk[7] */ 0.,
    /* mk[8] */ 0.,
    /* mk[9] */ 2.0519,
    /* mk[10] */ .5464,
    /* mk[11] */ .5464,

/* inertia */
    /* ik[0][0][0] */ 1.29841,
    /* ik[0][0][1] */ 0.,
    /* ik[0][0][2] */ 0.,
    /* ik[0][1][0] */ 0.,
    /* ik[0][1][1] */ .55245,
    /* ik[0][1][2] */ 0.,
    /* ik[0][2][0] */ 0.,
    /* ik[0][2][1] */ 0.,
    /* ik[0][2][2] */ 1.29841,
    /* ik[1][0][0] */ 0.,
    /* ik[1][0][1] */ 0.,
    /* ik[1][0][2] */ 0.,
    /* ik[1][1][0] */ 0.,
    /* ik[1][1][1] */ 0.,
    /* ik[1][1][2] */ 0.,
    /* ik[1][2][0] */ 0.,
    /* ik[1][2][1] */ 0.,
    /* ik[1][2][2] */ 0.,
    /* ik[2][0][0] */ 0.,
    /* ik[2][0][1] */ 0.,
    /* ik[2][0][2] */ 0.,
    /* ik[2][1][0] */ 0.,
    /* ik[2][1][1] */ 0.,
    /* ik[2][1][2] */ 0.,
    /* ik[2][2][0] */ 0.,
    /* ik[2][2][1] */ 0.,
    /* ik[2][2][2] */ 0.,
    /* ik[3][0][0] */ 6.4e-6,
    /* ik[3][0][1] */ -6.7e-6,
    /* ik[3][0][2] */ -9.5e-6,
    /* ik[3][1][0] */ -6.7e-6,
    /* ik[3][1][1] */ 2.63e-5,
    /* ik[3][1][2] */ 2.9e-6,
    /* ik[3][2][0] */ -9.5e-6,
    /* ik[3][2][1] */ 2.9e-6,
    /* ik[3][2][2] */ 2.43e-5,
    /* ik[4][0][0] */ 0.,
    /* ik[4][0][1] */ 0.,
    /* ik[4][0][2] */ 0.,
    /* ik[4][1][0] */ 0.,
    /* ik[4][1][1] */ 0.,
    /* ik[4][1][2] */ 0.,
    /* ik[4][2][0] */ 0.,
    /* ik[4][2][1] */ 0.,
    /* ik[4][2][2] */ 0.,
    /* ik[5][0][0] */ 0.,
    /* ik[5][0][1] */ 0.,
    /* ik[5][0][2] */ 0.,
    /* ik[5][1][0] */ 0.,
    /* ik[5][1][1] */ 0.,
    /* ik[5][1][2] */ 0.,
    /* ik[5][2][0] */ 0.,
    /* ik[5][2][1] */ 0.,
    /* ik[5][2][2] */ 0.,
    /* ik[6][0][0] */ .001,
    /* ik[6][0][1] */ 0.,
    /* ik[6][0][2] */ 0.,
    /* ik[6][1][0] */ 0.,
    /* ik[6][1][1] */ .001,
    /* ik[6][1][2] */ 0.,
    /* ik[6][2][0] */ 0.,
    /* ik[6][2][1] */ 0.,
    /* ik[6][2][2] */ .001,
    /* ik[7][0][0] */ 0.,
    /* ik[7][0][1] */ 0.,
    /* ik[7][0][2] */ 0.,
    /* ik[7][1][0] */ 0.,
    /* ik[7][1][1] */ 0.,
    /* ik[7][1][2] */ 0.,
    /* ik[7][2][0] */ 0.,
    /* ik[7][2][1] */ 0.,
    /* ik[7][2][2] */ 0.,
    /* ik[8][0][0] */ 0.,
    /* ik[8][0][1] */ 0.,
    /* ik[8][0][2] */ 0.,
    /* ik[8][1][0] */ 0.,
    /* ik[8][1][1] */ 0.,
    /* ik[8][1][2] */ 0.,
    /* ik[8][2][0] */ 0.,
    /* ik[8][2][1] */ 0.,
    /* ik[8][2][2] */ 0.,
    /* ik[9][0][0] */ .0132,
    /* ik[9][0][1] */ 0.,
    /* ik[9][0][2] */ 0.,
    /* ik[9][1][0] */ 0.,
    /* ik[9][1][1] */ .001988,
    /* ik[9][1][2] */ 0.,
    /* ik[9][2][0] */ 0.,
    /* ik[9][2][1] */ 0.,
    /* ik[9][2][2] */ .0132,
    /* ik[10][0][0] */ .0030585,
    /* ik[10][0][1] */ 0.,
    /* ik[10][0][2] */ 0.,
    /* ik[10][1][0] */ 0.,
    /* ik[10][1][1] */ .00045325,
    /* ik[10][1][2] */ 0.,
    /* ik[10][2][0] */ 0.,
    /* ik[10][2][1] */ 0.,
    /* ik[10][2][2] */ .0030585,
    /* ik[11][0][0] */ .0030585,
    /* ik[11][0][1] */ 0.,
    /* ik[11][0][2] */ 0.,
    /* ik[11][1][0] */ 0.,
    /* ik[11][1][1] */ .00045325,
    /* ik[11][1][2] */ 0.,
    /* ik[11][2][0] */ 0.,
    /* ik[11][2][1] */ 0.,
    /* ik[11][2][2] */ .0030585,

/* tree hinge axis vectors */
    /* pin[0][0] */ 0.,
    /* pin[0][1] */ 1.,
    /* pin[0][2] */ 0.,
    /* pin[1][0] */ 0.,
    /* pin[1][1] */ 0.,
    /* pin[1][2] */ 1.,
    /* pin[2][0] */ 0.,
    /* pin[2][1] */ 1.,
    /* pin[2][2] */ 0.,
    /* pin[3][0] */ .999766121,
    /* pin[3][1] */ .008446001,
    /* pin[3][2] */ -.0199090024,
    /* pin[4][0] */ -.1132949791,
    /* pin[4][1] */ .9740588207,
    /* pin[4][2] */ .1958919639,

/* tree bodytojoint vectors */
    /* rk[0][0] */ 0.,
    /* rk[0][1] */ .1486,
    /* rk[0][2] */ -.0591,
    /* rk[1][0] */ 0.,
    /* rk[1][1] */ 0.,
    /* rk[1][2] */ 0.,
    /* rk[2][0] */ 0.,
    /* rk[2][1] */ 0.,
    /* rk[2][2] */ 0.,
    /* rk[3][0] */ -.0983,
    /* rk[3][1] */ -.0167,
    /* rk[3][2] */ -.0042,
    /* rk[4][0] */ 0.,
    /* rk[4][1] */ 0.,
    /* rk[4][2] */ 0.,
    /* rk[5][0] */ 0.,
    /* rk[5][1] */ 0.,
    /* rk[5][2] */ 0.,
    /* rk[6][0] */ .053,
    /* rk[6][1] */ .0229,
    /* rk[6][2] */ .0247,
    /* rk[7][0] */ 0.,
    /* rk[7][1] */ 0.,
    /* rk[7][2] */ 0.,
    /* rk[8][0] */ 0.,
    /* rk[8][1] */ 0.,
    /* rk[8][2] */ 0.,
    /* rk[9][0] */ -.0064,
    /* rk[9][1] */ .0776,
    /* rk[9][2] */ .0036,
    /* rk[10][0] */ .0003,
    /* rk[10][1] */ .0634,
    /* rk[10][2] */ .0039,
    /* rk[11][0] */ -.0106,
    /* rk[11][1] */ .1179,
    /* rk[11][2] */ .0129,

/* tree inbtojoint vectors */
    /* ri[0][0] */ 0.,
    /* ri[0][1] */ 0.,
    /* ri[0][2] */ 0.,
    /* ri[1][0] */ .0014,
    /* ri[1][1] */ .1334,
    /* ri[1][2] */ -.0563,
    /* ri[2][0] */ 0.,
    /* ri[2][1] */ 0.,
    /* ri[2][2] */ 0.,
    /* ri[3][0] */ 0.,
    /* ri[3][1] */ 0.,
    /* ri[3][2] */ 0.,
    /* ri[4][0] */ .1094,
    /* ri[4][1] */ -.0168,
    /* ri[4][2] */ .024,
    /* ri[5][0] */ 0.,
    /* ri[5][1] */ 0.,
    /* ri[5][2] */ 0.,
    /* ri[6][0] */ 0.,
    /* ri[6][1] */ 0.,
    /* ri[6][2] */ 0.,
    /* ri[7][0] */ .055,
    /* ri[7][1] */ -.0001,
    /* ri[7][2] */ -.0192,
    /* ri[8][0] */ 0.,
    /* ri[8][1] */ 0.,
    /* ri[8][2] */ 0.,
    /* ri[9][0] */ 0.,
    /* ri[9][1] */ 0.,
    /* ri[9][2] */ 0.,
    /* ri[10][0] */ -.0006,
    /* ri[10][1] */ -.2131,
    /* ri[10][2] */ .0085,
    /* ri[11][0] */ .0174,
    /* ri[11][1] */ .0501,
    /* ri[11][2] */ -.0124,

/* tree prescribed motion */
    /* pres[0] */ 0.,
    /* pres[1] */ 0.,
    /* pres[2] */ 0.,
    /* pres[3] */ 0.,
    /* pres[4] */ 0.,

/* stabilization parameters */
    /* stabvel */ 0.,
    /* stabpos */ 0.,

/* miscellaneous */
    /* mfrcflg */ 0,
    /* roustate */ 0,
    /* vpkflg */ 0,
    /* inerflg */ 0,
    /* mmflg */ 0,
    /* mmlduflg */ 0,
    /* wwflg */ 0,
    /* ltauflg */ 0,
    /* fs0flg */ 0,
    /* ii */ 0,
    /* mmap[0] */ 0,
    /* mmap[1] */ 1,
    /* mmap[2] */ 2,
    /* mmap[3] */ 3,
    /* mmap[4] */ 4,

/* Which parameters were "?" (1) or "<nominal>?" (3) */
    /* gravq[0] */ 0,
    /* gravq[1] */ 0,
    /* gravq[2] */ 0,
    /* mkq[0] */ 0,
    /* mkq[1] */ 0,
    /* mkq[2] */ 0,
    /* mkq[3] */ 0,
    /* mkq[4] */ 0,
    /* mkq[5] */ 0,
    /* mkq[6] */ 0,
    /* mkq[7] */ 0,
    /* mkq[8] */ 0,
    /* mkq[9] */ 0,
    /* mkq[10] */ 0,
    /* mkq[11] */ 0,
    /* ikq[0][0][0] */ 0,
    /* ikq[0][0][1] */ 0,
    /* ikq[0][0][2] */ 0,
    /* ikq[0][1][0] */ 0,
    /* ikq[0][1][1] */ 0,
    /* ikq[0][1][2] */ 0,
    /* ikq[0][2][0] */ 0,
    /* ikq[0][2][1] */ 0,
    /* ikq[0][2][2] */ 0,
    /* ikq[1][0][0] */ 0,
    /* ikq[1][0][1] */ 0,
    /* ikq[1][0][2] */ 0,
    /* ikq[1][1][0] */ 0,
    /* ikq[1][1][1] */ 0,
    /* ikq[1][1][2] */ 0,
    /* ikq[1][2][0] */ 0,
    /* ikq[1][2][1] */ 0,
    /* ikq[1][2][2] */ 0,
    /* ikq[2][0][0] */ 0,
    /* ikq[2][0][1] */ 0,
    /* ikq[2][0][2] */ 0,
    /* ikq[2][1][0] */ 0,
    /* ikq[2][1][1] */ 0,
    /* ikq[2][1][2] */ 0,
    /* ikq[2][2][0] */ 0,
    /* ikq[2][2][1] */ 0,
    /* ikq[2][2][2] */ 0,
    /* ikq[3][0][0] */ 0,
    /* ikq[3][0][1] */ 0,
    /* ikq[3][0][2] */ 0,
    /* ikq[3][1][0] */ 0,
    /* ikq[3][1][1] */ 0,
    /* ikq[3][1][2] */ 0,
    /* ikq[3][2][0] */ 0,
    /* ikq[3][2][1] */ 0,
    /* ikq[3][2][2] */ 0,
    /* ikq[4][0][0] */ 0,
    /* ikq[4][0][1] */ 0,
    /* ikq[4][0][2] */ 0,
    /* ikq[4][1][0] */ 0,
    /* ikq[4][1][1] */ 0,
    /* ikq[4][1][2] */ 0,
    /* ikq[4][2][0] */ 0,
    /* ikq[4][2][1] */ 0,
    /* ikq[4][2][2] */ 0,
    /* ikq[5][0][0] */ 0,
    /* ikq[5][0][1] */ 0,
    /* ikq[5][0][2] */ 0,
    /* ikq[5][1][0] */ 0,
    /* ikq[5][1][1] */ 0,
    /* ikq[5][1][2] */ 0,
    /* ikq[5][2][0] */ 0,
    /* ikq[5][2][1] */ 0,
    /* ikq[5][2][2] */ 0,
    /* ikq[6][0][0] */ 0,
    /* ikq[6][0][1] */ 0,
    /* ikq[6][0][2] */ 0,
    /* ikq[6][1][0] */ 0,
    /* ikq[6][1][1] */ 0,
    /* ikq[6][1][2] */ 0,
    /* ikq[6][2][0] */ 0,
    /* ikq[6][2][1] */ 0,
    /* ikq[6][2][2] */ 0,
    /* ikq[7][0][0] */ 0,
    /* ikq[7][0][1] */ 0,
    /* ikq[7][0][2] */ 0,
    /* ikq[7][1][0] */ 0,
    /* ikq[7][1][1] */ 0,
    /* ikq[7][1][2] */ 0,
    /* ikq[7][2][0] */ 0,
    /* ikq[7][2][1] */ 0,
    /* ikq[7][2][2] */ 0,
    /* ikq[8][0][0] */ 0,
    /* ikq[8][0][1] */ 0,
    /* ikq[8][0][2] */ 0,
    /* ikq[8][1][0] */ 0,
    /* ikq[8][1][1] */ 0,
    /* ikq[8][1][2] */ 0,
    /* ikq[8][2][0] */ 0,
    /* ikq[8][2][1] */ 0,
    /* ikq[8][2][2] */ 0,
    /* ikq[9][0][0] */ 0,
    /* ikq[9][0][1] */ 0,
    /* ikq[9][0][2] */ 0,
    /* ikq[9][1][0] */ 0,
    /* ikq[9][1][1] */ 0,
    /* ikq[9][1][2] */ 0,
    /* ikq[9][2][0] */ 0,
    /* ikq[9][2][1] */ 0,
    /* ikq[9][2][2] */ 0,
    /* ikq[10][0][0] */ 0,
    /* ikq[10][0][1] */ 0,
    /* ikq[10][0][2] */ 0,
    /* ikq[10][1][0] */ 0,
    /* ikq[10][1][1] */ 0,
    /* ikq[10][1][2] */ 0,
    /* ikq[10][2][0] */ 0,
    /* ikq[10][2][1] */ 0,
    /* ikq[10][2][2] */ 0,
    /* ikq[11][0][0] */ 0,
    /* ikq[11][0][1] */ 0,
    /* ikq[11][0][2] */ 0,
    /* ikq[11][1][0] */ 0,
    /* ikq[11][1][1] */ 0,
    /* ikq[11][1][2] */ 0,
    /* ikq[11][2][0] */ 0,
    /* ikq[11][2][1] */ 0,
    /* ikq[11][2][2] */ 0,
    /* pinq[0][0] */ 0,
    /* pinq[0][1] */ 0,
    /* pinq[0][2] */ 0,
    /* pinq[1][0] */ 0,
    /* pinq[1][1] */ 0,
    /* pinq[1][2] */ 0,
    /* pinq[2][0] */ 0,
    /* pinq[2][1] */ 0,
    /* pinq[2][2] */ 0,
    /* pinq[3][0] */ 0,
    /* pinq[3][1] */ 0,
    /* pinq[3][2] */ 0,
    /* pinq[4][0] */ 0,
    /* pinq[4][1] */ 0,
    /* pinq[4][2] */ 0,
    /* rkq[0][0] */ 0,
    /* rkq[0][1] */ 0,
    /* rkq[0][2] */ 0,
    /* rkq[1][0] */ 0,
    /* rkq[1][1] */ 0,
    /* rkq[1][2] */ 0,
    /* rkq[2][0] */ 0,
    /* rkq[2][1] */ 0,
    /* rkq[2][2] */ 0,
    /* rkq[3][0] */ 0,
    /* rkq[3][1] */ 0,
    /* rkq[3][2] */ 0,
    /* rkq[4][0] */ 0,
    /* rkq[4][1] */ 0,
    /* rkq[4][2] */ 0,
    /* rkq[5][0] */ 0,
    /* rkq[5][1] */ 0,
    /* rkq[5][2] */ 0,
    /* rkq[6][0] */ 0,
    /* rkq[6][1] */ 0,
    /* rkq[6][2] */ 0,
    /* rkq[7][0] */ 0,
    /* rkq[7][1] */ 0,
    /* rkq[7][2] */ 0,
    /* rkq[8][0] */ 0,
    /* rkq[8][1] */ 0,
    /* rkq[8][2] */ 0,
    /* rkq[9][0] */ 0,
    /* rkq[9][1] */ 0,
    /* rkq[9][2] */ 0,
    /* rkq[10][0] */ 0,
    /* rkq[10][1] */ 0,
    /* rkq[10][2] */ 0,
    /* rkq[11][0] */ 0,
    /* rkq[11][1] */ 0,
    /* rkq[11][2] */ 0,
    /* riq[0][0] */ 0,
    /* riq[0][1] */ 0,
    /* riq[0][2] */ 0,
    /* riq[1][0] */ 0,
    /* riq[1][1] */ 0,
    /* riq[1][2] */ 0,
    /* riq[2][0] */ 0,
    /* riq[2][1] */ 0,
    /* riq[2][2] */ 0,
    /* riq[3][0] */ 0,
    /* riq[3][1] */ 0,
    /* riq[3][2] */ 0,
    /* riq[4][0] */ 0,
    /* riq[4][1] */ 0,
    /* riq[4][2] */ 0,
    /* riq[5][0] */ 0,
    /* riq[5][1] */ 0,
    /* riq[5][2] */ 0,
    /* riq[6][0] */ 0,
    /* riq[6][1] */ 0,
    /* riq[6][2] */ 0,
    /* riq[7][0] */ 0,
    /* riq[7][1] */ 0,
    /* riq[7][2] */ 0,
    /* riq[8][0] */ 0,
    /* riq[8][1] */ 0,
    /* riq[8][2] */ 0,
    /* riq[9][0] */ 0,
    /* riq[9][1] */ 0,
    /* riq[9][2] */ 0,
    /* riq[10][0] */ 0,
    /* riq[10][1] */ 0,
    /* riq[10][2] */ 0,
    /* riq[11][0] */ 0,
    /* riq[11][1] */ 0,
    /* riq[11][2] */ 0,
    /* presq[0] */ 0,
    /* presq[1] */ 0,
    /* presq[2] */ 0,
    /* presq[3] */ 0,
    /* presq[4] */ 0,
    /* stabvelq */ 3,
    /* stabposq */ 3,

/* End of values from input file */

};
sdgstate_t sdgstate;
sdglhs_t sdglhs;
sdgrhs_t sdgrhs;
sdgtemp_t sdgtemp;


void sdinit(void)
{
/*
Initialization routine


 This routine must be called before the first call to sdstate(), after
 supplying values for any `?' parameters in the input.
*/
    double sumsq,norminv;
    int i,j,k;


/* Check that all `?' parameters have been assigned values */

    for (k = 0; k < 3; k++) {
        if (gravq[k] == 1) {
            sdseterr(7,25);
        }
    }
    for (k = 0; k < 12; k++) {
        if (mkq[k] == 1) {
            sdseterr(7,26);
        }
        for (i = 0; i < 3; i++) {
            if (rkq[k][i] == 1) {
                sdseterr(7,29);
            }
            if (riq[k][i] == 1) {
                sdseterr(7,30);
            }
            for (j = 0; j < 3; j++) {
                if (ikq[k][i][j] == 1) {
                    sdseterr(7,27);
                }
            }
        }
    }
    for (k = 0; k < 5; k++) {
        for (i = 0; i < 3; i++) {
            if (pinq[k][i] == 1) {
                sdseterr(7,28);
            }
        }
    }

/* Normalize pin vectors if necessary */


/* Zero out ping and hngpt */

    for (i = 0; i < 5; i++) {
        for (j = 0; j < 3; j++) {
            ping[i][j] = 0.;
            hngpt[i][j] = 0.;
        }
    }

/* Compute pseudobody-related constants */

    rcom[0][0] = -.00602385937664778;
    rcom[0][1] = -.00485546319997696;
    rcom[0][2] = .00217496045327734;
    rcom[1][0] = -.00462385937664778;
    rcom[1][1] = .128544536800023;
    rcom[1][2] = -.0541250395467227;
    rcom[2][0] = -.00462385937664778;
    rcom[2][1] = .128544536800023;
    rcom[2][2] = -.0541250395467227;
    rcom[3][0] = .0936761406233522;
    rcom[3][1] = .145244536800023;
    rcom[3][2] = -.0499250395467227;
    rcom[4][0] = .203076140623352;
    rcom[4][1] = .128444536800023;
    rcom[4][2] = -.0259250395467227;
    rcom[5][0] = .203076140623352;
    rcom[5][1] = .128444536800023;
    rcom[5][2] = -.0259250395467227;
    rcom[6][0] = .150076140623352;
    rcom[6][1] = .105544536800023;
    rcom[6][2] = -.0506250395467227;
    rcom[7][0] = 0.;
    rcom[7][1] = 0.;
    rcom[7][2] = 0.;
    rcom[8][0] = 0.;
    rcom[8][1] = 0.;
    rcom[8][2] = 0.;
    rcom[9][0] = 0.;
    rcom[9][1] = 0.;
    rcom[9][2] = 0.;
    rcom[10][0] = 0.;
    rcom[10][1] = 0.;
    rcom[10][2] = 0.;
    rcom[11][0] = 0.;
    rcom[11][1] = 0.;
    rcom[11][2] = 0.;

/* Compute mass properties-related constants */

    mtot = 24.0061;
    sdserialno(&i);
    if (i != 30123) {
        sdseterr(7,41);
    }
    roustate = 1;
}

/* Convert state to form using 1-2-3 Euler angles for ball joints. */

void sdst2ang(double st[5],
    double stang[5])
{
    int i;

    for (i = 0; i < 5; i++) {
        stang[i] = st[i];
    }
}

/* Convert 1-2-3 form of state back to Euler parameters for ball joints. */

void sdang2st(double stang[5],
    double st[5])
{
    int i;

    for (i = 0; i < 5; i++) {
        st[i] = stang[i];
    }
}

/* Normalize Euler parameters in state. */

void sdnrmsterr(double st[5],
    double normst[5],
    int routine)
{
    int i;

    for (i = 0; i < 5; i++) {
        normst[i] = st[i];
    }
}

void sdnormst(double st[5],
    double normst[5])
{

    sdnrmsterr(st,normst,0);
}

void sdstate(double timein,
    double qin[5],
    double uin[5])
{
/*
Compute kinematic information and store it in sdgstate.

Generated 14-Nov-2007 16:57:48 by SD/FAST, Order(N) formulation
(sdfast B.2.8 #30123) on machine ID unknown
Copyright (c) 1990-1997 Symbolic Dynamics, Inc.
Copyright (c) 1990-1997 Parametric Technology Corp.
RESTRICTED RIGHTS LEGEND: Use, duplication, or disclosure by the U.S.
Government is subject to restrictions as set forth in subparagraph
(c)(1)(ii) of the Rights in Technical Data and Computer Software
clause at DFARS 52.227-7013 and similar clauses in the FAR and NASA
FAR Supplement.  Symbolic Dynamics, Inc., Mountain View, CA 94041
*/
    int i,j,qchg,uchg;

    if ((roustate != 1) && (roustate != 2) && (roustate != 3)) {
        sdseterr(8,22);
        return;
    }
    if (roustate == 1) {
        for (i = 0; i < 5; i++) {
            if (presq[i] == 1) {
                sdseterr(8,31);
            }
        }
    }
/*
See if time or any qs have changed since last call
*/
    if ((roustate != 1) && (timein == curtim)) {
        qchg = 0;
        for (i = 0; i < 5; i++) {
            if (qin[i] != q[i]) {
                qchg = 1;
                break;
            }
        }
    } else {
        qchg = 1;
    }
/*
If time and qs are unchanged, check us
*/
    if (qchg == 0) {
        uchg = 0;
        for (i = 0; i < 5; i++) {
            if (uin[i] != u[i]) {
                uchg = 1;
                break;
            }
        }
    } else {
        uchg = 1;
    }
    curtim = timein;
    roustate = 2;
    if (qchg == 0) {
        goto skipqs;
    }
/*
Position-related variables need to be computed
*/
    vpkflg = 0;
    mmflg = 0;
    mmlduflg = 0;
    wwflg = 0;
    for (i = 0; i < 5; i++) {
        q[i] = qin[i];
    }
/*
Compute sines and cosines of q
*/
    s0 = sin(q[0]);
    c0 = cos(q[0]);
    s1 = sin(q[1]);
    c1 = cos(q[1]);
    s2 = sin(q[2]);
    c2 = cos(q[2]);
    s3 = sin(q[3]);
    c3 = cos(q[3]);
    s4 = sin(q[4]);
    c4 = cos(q[4]);
/*
Compute across-axis direction cosines Cik
*/
    Cik[3][0][0] = (.999532296690549+(.000467703309451228*c3));
    Cik[3][0][1] = (.00844402565765746+((.019909002399912*s3)-(
      .00844402565765746*c3)));
    Cik[3][0][2] = ((.0199043461022517*c3)+((.00844600099996266*s3)-
      .0199043461022517));
    Cik[3][1][0] = (.00844402565765746-((.00844402565765746*c3)+(
      .019909002399912*s3)));
    Cik[3][1][1] = (7.13349328913703e-5+(.999928665067109*c3));
    Cik[3][1][2] = ((.000168151454177916*c3)-(.000168151454177916+(
      .99976612099558*s3)));
    Cik[3][2][0] = ((.0199043461022517*c3)-(.0199043461022517+(
      .00844600099996266*s3)));
    Cik[3][2][1] = ((.000168151454177916*c3)+((.99976612099558*s3)-
      .000168151454177916));
    Cik[3][2][2] = (.000396368376559701+(.99960363162344*c3));
    Cik[4][0][0] = (.0128357522893549+(.987164247710645*c4));
    Cik[4][0][1] = ((.110355973734112*c4)-(.110355973734112+(.195891963900652*s4
      )));
    Cik[4][0][2] = ((.0221935759560562*c4)+((.974058820703242*s4)-
      .0221935759560562));
    Cik[4][1][0] = ((.110355973734112*c4)+((.195891963900652*s4)-
      .110355973734112));
    Cik[4][1][1] = (.948790586189791+(.0512094138102092*c4));
    Cik[4][1][2] = (.190810295342311+((.113294979100377*s4)-(.190810295342311*c4
      )));
    Cik[4][2][0] = ((.0221935759560562*c4)-(.0221935759560562+(.974058820703242*
      s4)));
    Cik[4][2][1] = (.190810295342311-((.113294979100377*s4)+(.190810295342311*c4
      )));
    Cik[4][2][2] = (.0383736615208543+(.961626338479146*c4));
/*
Compute across-joint direction cosines Cib
*/
/*
Compute gravity
*/
    gk[2][0] = -(9.80665*(s1*c2));
    gk[2][2] = -(9.80665*(s1*s2));
    gk[3][0] = ((Cik[3][2][0]*gk[2][2])+((Cik[3][0][0]*gk[2][0])-(9.80665*(
      Cik[3][1][0]*c1))));
    gk[3][1] = ((Cik[3][2][1]*gk[2][2])+((Cik[3][0][1]*gk[2][0])-(9.80665*(
      Cik[3][1][1]*c1))));
    gk[3][2] = ((Cik[3][2][2]*gk[2][2])+((Cik[3][0][2]*gk[2][0])-(9.80665*(
      Cik[3][1][2]*c1))));
    gk[4][0] = ((Cik[4][2][0]*gk[3][2])+((Cik[4][0][0]*gk[3][0])+(Cik[4][1][0]*
      gk[3][1])));
    gk[4][1] = ((Cik[4][2][1]*gk[3][2])+((Cik[4][0][1]*gk[3][0])+(Cik[4][1][1]*
      gk[3][1])));
    gk[4][2] = ((Cik[4][2][2]*gk[3][2])+((Cik[4][0][2]*gk[3][0])+(Cik[4][1][2]*
      gk[3][1])));
/*
Compute cnk & cnb (direction cosines in N)
*/
    cnk[1][0][0] = (c0*c1);
    cnk[1][0][1] = -(s1*c0);
    cnk[1][2][0] = -(s0*c1);
    cnk[1][2][1] = (s0*s1);
    cnk[2][0][0] = ((cnk[1][0][0]*c2)-(s0*s2));
    cnk[2][0][2] = ((cnk[1][0][0]*s2)+(s0*c2));
    cnk[2][1][0] = (s1*c2);
    cnk[2][1][2] = (s1*s2);
    cnk[2][2][0] = ((cnk[1][2][0]*c2)-(s2*c0));
    cnk[2][2][2] = ((cnk[1][2][0]*s2)+(c0*c2));
    cnk[3][0][0] = ((Cik[3][2][0]*cnk[2][0][2])+((Cik[3][0][0]*cnk[2][0][0])+(
      Cik[3][1][0]*cnk[1][0][1])));
    cnk[3][0][1] = ((Cik[3][2][1]*cnk[2][0][2])+((Cik[3][0][1]*cnk[2][0][0])+(
      Cik[3][1][1]*cnk[1][0][1])));
    cnk[3][0][2] = ((Cik[3][2][2]*cnk[2][0][2])+((Cik[3][0][2]*cnk[2][0][0])+(
      Cik[3][1][2]*cnk[1][0][1])));
    cnk[3][1][0] = ((Cik[3][2][0]*cnk[2][1][2])+((Cik[3][0][0]*cnk[2][1][0])+(
      Cik[3][1][0]*c1)));
    cnk[3][1][1] = ((Cik[3][2][1]*cnk[2][1][2])+((Cik[3][0][1]*cnk[2][1][0])+(
      Cik[3][1][1]*c1)));
    cnk[3][1][2] = ((Cik[3][2][2]*cnk[2][1][2])+((Cik[3][0][2]*cnk[2][1][0])+(
      Cik[3][1][2]*c1)));
    cnk[3][2][0] = ((Cik[3][2][0]*cnk[2][2][2])+((Cik[3][0][0]*cnk[2][2][0])+(
      Cik[3][1][0]*cnk[1][2][1])));
    cnk[3][2][1] = ((Cik[3][2][1]*cnk[2][2][2])+((Cik[3][0][1]*cnk[2][2][0])+(
      Cik[3][1][1]*cnk[1][2][1])));
    cnk[3][2][2] = ((Cik[3][2][2]*cnk[2][2][2])+((Cik[3][0][2]*cnk[2][2][0])+(
      Cik[3][1][2]*cnk[1][2][1])));
    cnk[4][0][0] = ((Cik[4][2][0]*cnk[3][0][2])+((Cik[4][0][0]*cnk[3][0][0])+(
      Cik[4][1][0]*cnk[3][0][1])));
    cnk[4][0][1] = ((Cik[4][2][1]*cnk[3][0][2])+((Cik[4][0][1]*cnk[3][0][0])+(
      Cik[4][1][1]*cnk[3][0][1])));
    cnk[4][0][2] = ((Cik[4][2][2]*cnk[3][0][2])+((Cik[4][0][2]*cnk[3][0][0])+(
      Cik[4][1][2]*cnk[3][0][1])));
    cnk[4][1][0] = ((Cik[4][2][0]*cnk[3][1][2])+((Cik[4][0][0]*cnk[3][1][0])+(
      Cik[4][1][0]*cnk[3][1][1])));
    cnk[4][1][1] = ((Cik[4][2][1]*cnk[3][1][2])+((Cik[4][0][1]*cnk[3][1][0])+(
      Cik[4][1][1]*cnk[3][1][1])));
    cnk[4][1][2] = ((Cik[4][2][2]*cnk[3][1][2])+((Cik[4][0][2]*cnk[3][1][0])+(
      Cik[4][1][2]*cnk[3][1][1])));
    cnk[4][2][0] = ((Cik[4][2][0]*cnk[3][2][2])+((Cik[4][0][0]*cnk[3][2][0])+(
      Cik[4][1][0]*cnk[3][2][1])));
    cnk[4][2][1] = ((Cik[4][2][1]*cnk[3][2][2])+((Cik[4][0][1]*cnk[3][2][0])+(
      Cik[4][1][1]*cnk[3][2][1])));
    cnk[4][2][2] = ((Cik[4][2][2]*cnk[3][2][2])+((Cik[4][0][2]*cnk[3][2][0])+(
      Cik[4][1][2]*cnk[3][2][1])));
    cnb[0][0][0] = 1.;
    cnb[0][0][1] = 0.;
    cnb[0][0][2] = 0.;
    cnb[0][1][0] = 0.;
    cnb[0][1][1] = 1.;
    cnb[0][1][2] = 0.;
    cnb[0][2][0] = 0.;
    cnb[0][2][1] = 0.;
    cnb[0][2][2] = 1.;
    cnb[1][0][0] = 1.;
    cnb[1][0][1] = 0.;
    cnb[1][0][2] = 0.;
    cnb[1][1][0] = 0.;
    cnb[1][1][1] = 1.;
    cnb[1][1][2] = 0.;
    cnb[1][2][0] = 0.;
    cnb[1][2][1] = 0.;
    cnb[1][2][2] = 1.;
    cnb[2][0][0] = 1.;
    cnb[2][0][1] = 0.;
    cnb[2][0][2] = 0.;
    cnb[2][1][0] = 0.;
    cnb[2][1][1] = 1.;
    cnb[2][1][2] = 0.;
    cnb[2][2][0] = 0.;
    cnb[2][2][1] = 0.;
    cnb[2][2][2] = 1.;
    cnb[3][0][0] = 1.;
    cnb[3][0][1] = 0.;
    cnb[3][0][2] = 0.;
    cnb[3][1][0] = 0.;
    cnb[3][1][1] = 1.;
    cnb[3][1][2] = 0.;
    cnb[3][2][0] = 0.;
    cnb[3][2][1] = 0.;
    cnb[3][2][2] = 1.;
    cnb[4][0][0] = 1.;
    cnb[4][0][1] = 0.;
    cnb[4][0][2] = 0.;
    cnb[4][1][0] = 0.;
    cnb[4][1][1] = 1.;
    cnb[4][1][2] = 0.;
    cnb[4][2][0] = 0.;
    cnb[4][2][1] = 0.;
    cnb[4][2][2] = 1.;
    cnb[5][0][0] = 1.;
    cnb[5][0][1] = 0.;
    cnb[5][0][2] = 0.;
    cnb[5][1][0] = 0.;
    cnb[5][1][1] = 1.;
    cnb[5][1][2] = 0.;
    cnb[5][2][0] = 0.;
    cnb[5][2][1] = 0.;
    cnb[5][2][2] = 1.;
    cnb[6][0][0] = 1.;
    cnb[6][0][1] = 0.;
    cnb[6][0][2] = 0.;
    cnb[6][1][0] = 0.;
    cnb[6][1][1] = 1.;
    cnb[6][1][2] = 0.;
    cnb[6][2][0] = 0.;
    cnb[6][2][1] = 0.;
    cnb[6][2][2] = 1.;
    cnb[7][0][0] = c0;
    cnb[7][0][1] = 0.;
    cnb[7][0][2] = s0;
    cnb[7][1][0] = 0.;
    cnb[7][1][1] = 1.;
    cnb[7][1][2] = 0.;
    cnb[7][2][0] = -s0;
    cnb[7][2][1] = 0.;
    cnb[7][2][2] = c0;
    cnb[8][0][0] = cnk[1][0][0];
    cnb[8][0][1] = cnk[1][0][1];
    cnb[8][0][2] = s0;
    cnb[8][1][0] = s1;
    cnb[8][1][1] = c1;
    cnb[8][1][2] = 0.;
    cnb[8][2][0] = cnk[1][2][0];
    cnb[8][2][1] = cnk[1][2][1];
    cnb[8][2][2] = c0;
    cnb[9][0][0] = cnk[2][0][0];
    cnb[9][0][1] = cnk[1][0][1];
    cnb[9][0][2] = cnk[2][0][2];
    cnb[9][1][0] = cnk[2][1][0];
    cnb[9][1][1] = c1;
    cnb[9][1][2] = cnk[2][1][2];
    cnb[9][2][0] = cnk[2][2][0];
    cnb[9][2][1] = cnk[1][2][1];
    cnb[9][2][2] = cnk[2][2][2];
    cnb[10][0][0] = cnk[3][0][0];
    cnb[10][0][1] = cnk[3][0][1];
    cnb[10][0][2] = cnk[3][0][2];
    cnb[10][1][0] = cnk[3][1][0];
    cnb[10][1][1] = cnk[3][1][1];
    cnb[10][1][2] = cnk[3][1][2];
    cnb[10][2][0] = cnk[3][2][0];
    cnb[10][2][1] = cnk[3][2][1];
    cnb[10][2][2] = cnk[3][2][2];
    cnb[11][0][0] = cnk[4][0][0];
    cnb[11][0][1] = cnk[4][0][1];
    cnb[11][0][2] = cnk[4][0][2];
    cnb[11][1][0] = cnk[4][1][0];
    cnb[11][1][1] = cnk[4][1][1];
    cnb[11][1][2] = cnk[4][1][2];
    cnb[11][2][0] = cnk[4][2][0];
    cnb[11][2][1] = cnk[4][2][1];
    cnb[11][2][2] = cnk[4][2][2];
/*
Compute q-related auxiliary variables
*/
    rik[0][0] = ((.0698250395467227*s0)+(.205076140623352*c0));
    rik[0][2] = ((.205076140623352*s0)-(.0698250395467227*c0));
    rik[3][0] = (((.0085*Cik[3][2][0])-((.0006*Cik[3][0][0])+(.2131*Cik[3][1][0]
      )))-.0003);
    rik[3][1] = (((.0085*Cik[3][2][1])-((.0006*Cik[3][0][1])+(.2131*Cik[3][1][1]
      )))-.0634);
    rik[3][2] = (((.0085*Cik[3][2][2])-((.0006*Cik[3][0][2])+(.2131*Cik[3][1][2]
      )))-.0039);
    rik[4][0] = (.0106+(((.0174*Cik[4][0][0])+(.0501*Cik[4][1][0]))-(.0124*
      Cik[4][2][0])));
    rik[4][1] = ((((.0174*Cik[4][0][1])+(.0501*Cik[4][1][1]))-(.0124*
      Cik[4][2][1]))-.1179);
    rik[4][2] = ((((.0174*Cik[4][0][2])+(.0501*Cik[4][1][2]))-(.0124*
      Cik[4][2][2]))-.0129);
    rikt[0][1][0] = ((.205076140623352*s0)-(.0698250395467227*c0));
    rikt[0][1][2] = -((.0698250395467227*s0)+(.205076140623352*c0));
    rikt[3][0][0] = -((.0049*Cik[3][1][0])+(.2907*Cik[3][2][0]));
    rikt[3][0][1] = -((.0049*Cik[3][1][1])+(.2907*Cik[3][2][1]));
    rikt[3][0][2] = -((.0049*Cik[3][1][2])+(.2907*Cik[3][2][2]));
    rikt[3][1][0] = ((.0049*Cik[3][0][0])-(.0058*Cik[3][2][0]));
    rikt[3][1][1] = ((.0049*Cik[3][0][1])-(.0058*Cik[3][2][1]));
    rikt[3][1][2] = ((.0049*Cik[3][0][2])-(.0058*Cik[3][2][2]));
    rikt[3][2][0] = ((.0058*Cik[3][1][0])+(.2907*Cik[3][0][0]));
    rikt[3][2][1] = ((.0058*Cik[3][1][1])+(.2907*Cik[3][0][1]));
    rikt[3][2][2] = ((.0058*Cik[3][1][2])+(.2907*Cik[3][0][2]));
    rikt[4][0][0] = ((.0163*Cik[4][1][0])-(.0133*Cik[4][2][0]));
    rikt[4][0][1] = ((.0163*Cik[4][1][1])-(.0133*Cik[4][2][1]));
    rikt[4][0][2] = ((.0163*Cik[4][1][2])-(.0133*Cik[4][2][2]));
    rikt[4][1][0] = -((.0163*Cik[4][0][0])+(.0171*Cik[4][2][0]));
    rikt[4][1][1] = -((.0163*Cik[4][0][1])+(.0171*Cik[4][2][1]));
    rikt[4][1][2] = -((.0163*Cik[4][0][2])+(.0171*Cik[4][2][2]));
    rikt[4][2][0] = ((.0133*Cik[4][0][0])+(.0171*Cik[4][1][0]));
    rikt[4][2][1] = ((.0133*Cik[4][0][1])+(.0171*Cik[4][1][1]));
    rikt[4][2][2] = ((.0133*Cik[4][0][2])+(.0171*Cik[4][1][2]));
/*
Compute rnk & rnb (mass center locations in N)
*/
    rnk[2][0] = (.2111+(((.0064*cnk[2][0][0])-(.0776*cnk[1][0][1]))-(.0036*
      cnk[2][0][2])));
    rnk[2][1] = ((((.0064*cnk[2][1][0])-(.0776*c1))-(.0036*cnk[2][1][2]))-.0383)
      ;
    rnk[2][2] = ((((.0064*cnk[2][2][0])-(.0776*cnk[1][2][1]))-(.0036*
      cnk[2][2][2]))-.0129);
    rnk[3][0] = ((rnk[2][0]+((.0085*cnk[2][0][2])-((.0006*cnk[2][0][0])+(.2131*
      cnk[1][0][1]))))-((.0039*cnk[3][0][2])+((.0003*cnk[3][0][0])+(.0634*
      cnk[3][0][1]))));
    rnk[3][1] = ((rnk[2][1]+((.0085*cnk[2][1][2])-((.0006*cnk[2][1][0])+(.2131*
      c1))))-((.0039*cnk[3][1][2])+((.0003*cnk[3][1][0])+(.0634*cnk[3][1][1]))))
      ;
    rnk[3][2] = ((rnk[2][2]+((.0085*cnk[2][2][2])-((.0006*cnk[2][2][0])+(.2131*
      cnk[1][2][1]))))-((.0039*cnk[3][2][2])+((.0003*cnk[3][2][0])+(.0634*
      cnk[3][2][1]))));
    rnk[4][0] = ((rnk[3][0]+(((.0174*cnk[3][0][0])+(.0501*cnk[3][0][1]))-(.0124*
      cnk[3][0][2])))+(((.0106*cnk[4][0][0])-(.1179*cnk[4][0][1]))-(.0129*
      cnk[4][0][2])));
    rnk[4][1] = ((rnk[3][1]+(((.0174*cnk[3][1][0])+(.0501*cnk[3][1][1]))-(.0124*
      cnk[3][1][2])))+(((.0106*cnk[4][1][0])-(.1179*cnk[4][1][1]))-(.0129*
      cnk[4][1][2])));
    rnk[4][2] = ((rnk[3][2]+(((.0174*cnk[3][2][0])+(.0501*cnk[3][2][1]))-(.0124*
      cnk[3][2][2])))+(((.0106*cnk[4][2][0])-(.1179*cnk[4][2][1]))-(.0129*
      cnk[4][2][2])));
    rnb[0][0] = 0.;
    rnb[0][1] = -.1486;
    rnb[0][2] = .0591;
    rnb[1][0] = .0014;
    rnb[1][1] = -.0152;
    rnb[1][2] = .0028;
    rnb[2][0] = .0014;
    rnb[2][1] = -.0152;
    rnb[2][2] = .0028;
    rnb[3][0] = .0997;
    rnb[3][1] = .00149999999999997;
    rnb[3][2] = .007;
    rnb[4][0] = .2091;
    rnb[4][1] = -.0153;
    rnb[4][2] = .031;
    rnb[5][0] = .2091;
    rnb[5][1] = -.0153;
    rnb[5][2] = .031;
    rnb[6][0] = .1561;
    rnb[6][1] = -.0382;
    rnb[6][2] = .00629999999999999;
    rnb[7][0] = .2111;
    rnb[7][1] = -.0383;
    rnb[7][2] = -.0129;
    rnb[8][0] = .2111;
    rnb[8][1] = -.0383;
    rnb[8][2] = -.0129;
    rnb[9][0] = rnk[2][0];
    rnb[9][1] = rnk[2][1];
    rnb[9][2] = rnk[2][2];
    rnb[10][0] = rnk[3][0];
    rnb[10][1] = rnk[3][1];
    rnb[10][2] = rnk[3][2];
    rnb[11][0] = rnk[4][0];
    rnb[11][1] = rnk[4][1];
    rnb[11][2] = rnk[4][2];
/*
Compute com (system mass center location in N)
*/
    com[0] = (.0416560790799005*(.12566614+((.5464*rnk[4][0])+((.5464*rnk[3][0])
      +(2.0519*rnk[2][0])))));
    com[1] = (.0416560790799005*((.5464*rnk[4][1])+((.5464*rnk[3][1])+((2.0519*
      rnk[2][1])-2.99871228))));
    com[2] = (.0416560790799005*((.5464*rnk[4][2])+((.5464*rnk[3][2])+(
      1.18753602+(2.0519*rnk[2][2])))));
    skipqs: ;
    if (uchg == 0) {
        goto skipus;
    }
/*
Velocity-related variables need to be computed
*/
    inerflg = 0;
    for (i = 0; i < 5; i++) {
        u[i] = uin[i];
    }
/*
Compute u-related auxiliary variables
*/
/*
Compute wk & wb (angular velocities)
*/
    wk[1][0] = (u[0]*s1);
    wk[1][1] = (u[0]*c1);
    wk[2][0] = ((wk[1][0]*c2)-(u[1]*s2));
    wk[2][1] = (u[2]+wk[1][1]);
    wk[2][2] = ((u[1]*c2)+(wk[1][0]*s2));
    wk[3][0] = ((.99976612099558*u[3])+((Cik[3][2][0]*wk[2][2])+((Cik[3][0][0]*
      wk[2][0])+(Cik[3][1][0]*wk[2][1]))));
    wk[3][1] = ((.00844600099996266*u[3])+((Cik[3][2][1]*wk[2][2])+((
      Cik[3][0][1]*wk[2][0])+(Cik[3][1][1]*wk[2][1]))));
    wk[3][2] = (((Cik[3][2][2]*wk[2][2])+((Cik[3][0][2]*wk[2][0])+(Cik[3][1][2]*
      wk[2][1])))-(.019909002399912*u[3]));
    wk[4][0] = (((Cik[4][2][0]*wk[3][2])+((Cik[4][0][0]*wk[3][0])+(Cik[4][1][0]*
      wk[3][1])))-(.113294979100377*u[4]));
    wk[4][1] = ((.974058820703242*u[4])+((Cik[4][2][1]*wk[3][2])+((Cik[4][0][1]*
      wk[3][0])+(Cik[4][1][1]*wk[3][1]))));
    wk[4][2] = ((.195891963900652*u[4])+((Cik[4][2][2]*wk[3][2])+((Cik[4][0][2]*
      wk[3][0])+(Cik[4][1][2]*wk[3][1]))));
    wb[0][0] = 0.;
    wb[0][1] = 0.;
    wb[0][2] = 0.;
    wb[1][0] = 0.;
    wb[1][1] = 0.;
    wb[1][2] = 0.;
    wb[2][0] = 0.;
    wb[2][1] = 0.;
    wb[2][2] = 0.;
    wb[3][0] = 0.;
    wb[3][1] = 0.;
    wb[3][2] = 0.;
    wb[4][0] = 0.;
    wb[4][1] = 0.;
    wb[4][2] = 0.;
    wb[5][0] = 0.;
    wb[5][1] = 0.;
    wb[5][2] = 0.;
    wb[6][0] = 0.;
    wb[6][1] = 0.;
    wb[6][2] = 0.;
    wb[7][0] = 0.;
    wb[7][1] = u[0];
    wb[7][2] = 0.;
    wb[8][0] = wk[1][0];
    wb[8][1] = wk[1][1];
    wb[8][2] = u[1];
    wb[9][0] = wk[2][0];
    wb[9][1] = wk[2][1];
    wb[9][2] = wk[2][2];
    wb[10][0] = wk[3][0];
    wb[10][1] = wk[3][1];
    wb[10][2] = wk[3][2];
    wb[11][0] = wk[4][0];
    wb[11][1] = wk[4][1];
    wb[11][2] = wk[4][2];
/*
Compute auxiliary variables involving wk
*/
    Wirk[3][0] = ((.0085*wk[2][1])+(.2131*wk[2][2]));
    Wirk[3][1] = -((.0006*wk[2][2])+(.0085*wk[2][0]));
    Wirk[3][2] = ((.0006*wk[2][1])-(.2131*wk[2][0]));
    Wirk[4][0] = -((.0124*wk[3][1])+(.0501*wk[3][2]));
    Wirk[4][1] = ((.0124*wk[3][0])+(.0174*wk[3][2]));
    Wirk[4][2] = ((.0501*wk[3][0])-(.0174*wk[3][1]));
    Wkrpk[2][0] = ((.0776*wk[2][2])-(.0036*wk[2][1]));
    Wkrpk[2][1] = ((.0036*wk[2][0])+(.0064*wk[2][2]));
    Wkrpk[2][2] = -((.0064*wk[2][1])+(.0776*wk[2][0]));
    Wkrpk[3][0] = ((.0634*wk[3][2])-(.0039*wk[3][1]));
    Wkrpk[3][1] = ((.0039*wk[3][0])-(.0003*wk[3][2]));
    Wkrpk[3][2] = ((.0003*wk[3][1])-(.0634*wk[3][0]));
    Wkrpk[4][0] = ((.1179*wk[4][2])-(.0129*wk[4][1]));
    Wkrpk[4][1] = ((.0106*wk[4][2])+(.0129*wk[4][0]));
    Wkrpk[4][2] = -((.0106*wk[4][1])+(.1179*wk[4][0]));
    WkIkWk[2][0] = (.011212*(wk[2][1]*wk[2][2]));
    WkIkWk[2][2] = -(.011212*(wk[2][0]*wk[2][1]));
    WkIkWk[3][0] = (.00260525*(wk[3][1]*wk[3][2]));
    WkIkWk[3][2] = -(.00260525*(wk[3][0]*wk[3][1]));
    WkIkWk[4][0] = (.00260525*(wk[4][1]*wk[4][2]));
    WkIkWk[4][2] = -(.00260525*(wk[4][0]*wk[4][1]));
/*
Compute temporaries for use in SDRHS
*/
    w0w0[8] = (wk[1][0]*wk[1][0]);
    w0w0[9] = (wk[2][0]*wk[2][0]);
    w0w0[10] = (wk[3][0]*wk[3][0]);
    w0w0[11] = (wk[4][0]*wk[4][0]);
    w1w1[7] = (u[0]*u[0]);
    w1w1[8] = (wk[1][1]*wk[1][1]);
    w1w1[9] = (wk[2][1]*wk[2][1]);
    w1w1[10] = (wk[3][1]*wk[3][1]);
    w1w1[11] = (wk[4][1]*wk[4][1]);
    w2w2[8] = (u[1]*u[1]);
    w2w2[9] = (wk[2][2]*wk[2][2]);
    w2w2[10] = (wk[3][2]*wk[3][2]);
    w2w2[11] = (wk[4][2]*wk[4][2]);
    w0w1[8] = (wk[1][0]*wk[1][1]);
    w0w1[9] = (wk[2][0]*wk[2][1]);
    w0w1[10] = (wk[3][0]*wk[3][1]);
    w0w1[11] = (wk[4][0]*wk[4][1]);
    w0w2[8] = (u[1]*wk[1][0]);
    w0w2[9] = (wk[2][0]*wk[2][2]);
    w0w2[10] = (wk[3][0]*wk[3][2]);
    w0w2[11] = (wk[4][0]*wk[4][2]);
    w1w2[8] = (u[1]*wk[1][1]);
    w1w2[9] = (wk[2][1]*wk[2][2]);
    w1w2[10] = (wk[3][1]*wk[3][2]);
    w1w2[11] = (wk[4][1]*wk[4][2]);
    w00w11[8] = -(w0w0[8]+w1w1[8]);
    w00w11[9] = -(w0w0[9]+w1w1[9]);
    w00w11[10] = -(w0w0[10]+w1w1[10]);
    w00w11[11] = -(w0w0[11]+w1w1[11]);
    w00w22[8] = -(w0w0[8]+w2w2[8]);
    w00w22[9] = -(w0w0[9]+w2w2[9]);
    w00w22[10] = -(w0w0[10]+w2w2[10]);
    w00w22[11] = -(w0w0[11]+w2w2[11]);
    w11w22[8] = -(w1w1[8]+w2w2[8]);
    w11w22[9] = -(w1w1[9]+w2w2[9]);
    w11w22[10] = -(w1w1[10]+w2w2[10]);
    w11w22[11] = -(w1w1[11]+w2w2[11]);
/*
Compute vnk & vnb (mass center linear velocities in N)
*/
    vnk[2][0] = ((cnk[2][0][2]*Wkrpk[2][2])+((cnk[1][0][1]*Wkrpk[2][1])+(
      cnk[2][0][0]*Wkrpk[2][0])));
    vnk[2][1] = ((cnk[2][1][2]*Wkrpk[2][2])+((cnk[2][1][0]*Wkrpk[2][0])+(
      Wkrpk[2][1]*c1)));
    vnk[2][2] = ((cnk[2][2][2]*Wkrpk[2][2])+((cnk[1][2][1]*Wkrpk[2][1])+(
      cnk[2][2][0]*Wkrpk[2][0])));
    vnk[3][0] = ((vnk[2][0]+((cnk[2][0][2]*Wirk[3][2])+((cnk[1][0][1]*Wirk[3][1]
      )+(cnk[2][0][0]*Wirk[3][0]))))+((cnk[3][0][2]*Wkrpk[3][2])+((cnk[3][0][0]*
      Wkrpk[3][0])+(cnk[3][0][1]*Wkrpk[3][1]))));
    vnk[3][1] = ((vnk[2][1]+((cnk[2][1][2]*Wirk[3][2])+((cnk[2][1][0]*Wirk[3][0]
      )+(Wirk[3][1]*c1))))+((cnk[3][1][2]*Wkrpk[3][2])+((cnk[3][1][0]*
      Wkrpk[3][0])+(cnk[3][1][1]*Wkrpk[3][1]))));
    vnk[3][2] = ((vnk[2][2]+((cnk[2][2][2]*Wirk[3][2])+((cnk[1][2][1]*Wirk[3][1]
      )+(cnk[2][2][0]*Wirk[3][0]))))+((cnk[3][2][2]*Wkrpk[3][2])+((cnk[3][2][0]*
      Wkrpk[3][0])+(cnk[3][2][1]*Wkrpk[3][1]))));
    vnk[4][0] = ((vnk[3][0]+((cnk[3][0][2]*Wirk[4][2])+((cnk[3][0][0]*Wirk[4][0]
      )+(cnk[3][0][1]*Wirk[4][1]))))+((cnk[4][0][2]*Wkrpk[4][2])+((cnk[4][0][0]*
      Wkrpk[4][0])+(cnk[4][0][1]*Wkrpk[4][1]))));
    vnk[4][1] = ((vnk[3][1]+((cnk[3][1][2]*Wirk[4][2])+((cnk[3][1][0]*Wirk[4][0]
      )+(cnk[3][1][1]*Wirk[4][1]))))+((cnk[4][1][2]*Wkrpk[4][2])+((cnk[4][1][0]*
      Wkrpk[4][0])+(cnk[4][1][1]*Wkrpk[4][1]))));
    vnk[4][2] = ((vnk[3][2]+((cnk[3][2][2]*Wirk[4][2])+((cnk[3][2][0]*Wirk[4][0]
      )+(cnk[3][2][1]*Wirk[4][1]))))+((cnk[4][2][2]*Wkrpk[4][2])+((cnk[4][2][0]*
      Wkrpk[4][0])+(cnk[4][2][1]*Wkrpk[4][1]))));
    vnb[0][0] = 0.;
    vnb[0][1] = 0.;
    vnb[0][2] = 0.;
    vnb[1][0] = 0.;
    vnb[1][1] = 0.;
    vnb[1][2] = 0.;
    vnb[2][0] = 0.;
    vnb[2][1] = 0.;
    vnb[2][2] = 0.;
    vnb[3][0] = 0.;
    vnb[3][1] = 0.;
    vnb[3][2] = 0.;
    vnb[4][0] = 0.;
    vnb[4][1] = 0.;
    vnb[4][2] = 0.;
    vnb[5][0] = 0.;
    vnb[5][1] = 0.;
    vnb[5][2] = 0.;
    vnb[6][0] = 0.;
    vnb[6][1] = 0.;
    vnb[6][2] = 0.;
    vnb[7][0] = 0.;
    vnb[7][1] = 0.;
    vnb[7][2] = 0.;
    vnb[8][0] = 0.;
    vnb[8][1] = 0.;
    vnb[8][2] = 0.;
    vnb[9][0] = vnk[2][0];
    vnb[9][1] = vnk[2][1];
    vnb[9][2] = vnk[2][2];
    vnb[10][0] = vnk[3][0];
    vnb[10][1] = vnk[3][1];
    vnb[10][2] = vnk[3][2];
    vnb[11][0] = vnk[4][0];
    vnb[11][1] = vnk[4][1];
    vnb[11][2] = vnk[4][2];
/*
Compute qdot (kinematical equations)
*/
    qdot[0] = u[0];
    qdot[1] = u[1];
    qdot[2] = u[2];
    qdot[3] = u[3];
    qdot[4] = u[4];
    skipus: ;
/*
Initialize applied forces and torques to zero
*/
    for (i = 0; i < 12; i++) {
        for (j = 0; j < 3; j++) {
            ufk[i][j] = 0.;
            utk[i][j] = 0.;
        }
    }
    for (i = 0; i < 5; i++) {
        utau[i] = 0.;
    }
    ltauflg = 0;
    fs0flg = 0;
/*
 Used 0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain  297 adds/subtracts/negates
                    384 multiplies
                      0 divides
                    480 assignments
*/
}

void sdqdot(double oqdot[5])
{
/*
Return position coordinate derivatives for tree joints.
*/
    int i;

    if ((roustate != 2) && (roustate != 3)) {
        sdseterr(63,23);
        return;
    }
    for (i = 0; i <= 4; i++) {
        oqdot[i] = qdot[i];
    }
}

void sdu2qdot(double uin[5],
    double oqdot[5])
{
/*
Convert velocities to qdots.
*/
    int i;

    if ((roustate != 2) && (roustate != 3)) {
        sdseterr(64,23);
        return;
    }
    for (i = 0; i <= 4; i++) {
        oqdot[i] = uin[i];
    }
/*
 Used 0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain    0 adds/subtracts/negates
                      0 multiplies
                      0 divides
                      5 assignments
*/
}

void sdpsstate(double lqin[1])
{

    if (roustate != 2) {
        sdseterr(9,23);
        return;
    }
}

void sddoping(void)
{

    if (vpkflg == 0) {
/*
Compute ping (jt pins in ground frame)
*/
        ping[0][1] = 1.;
        ping[1][0] = s0;
        ping[1][2] = c0;
        ping[2][0] = cnk[1][0][1];
        ping[2][1] = c1;
        ping[2][2] = cnk[1][2][1];
        ping[3][0] = (((.00844600099996266*cnk[3][0][1])+(.99976612099558*
          cnk[3][0][0]))-(.019909002399912*cnk[3][0][2]));
        ping[3][1] = (((.00844600099996266*cnk[3][1][1])+(.99976612099558*
          cnk[3][1][0]))-(.019909002399912*cnk[3][1][2]));
        ping[3][2] = (((.00844600099996266*cnk[3][2][1])+(.99976612099558*
          cnk[3][2][0]))-(.019909002399912*cnk[3][2][2]));
        ping[4][0] = ((.195891963900652*cnk[4][0][2])+((.974058820703242*
          cnk[4][0][1])-(.113294979100377*cnk[4][0][0])));
        ping[4][1] = ((.195891963900652*cnk[4][1][2])+((.974058820703242*
          cnk[4][1][1])-(.113294979100377*cnk[4][1][0])));
        ping[4][2] = ((.195891963900652*cnk[4][2][2])+((.974058820703242*
          cnk[4][2][1])-(.113294979100377*cnk[4][2][0])));
/*
Compute hngpt (hinge pts in ground frame)
*/
        hngpt[0][0] = .2111;
        hngpt[0][1] = -.0383;
        hngpt[0][2] = -.0129;
        hngpt[1][0] = .2111;
        hngpt[1][1] = -.0383;
        hngpt[1][2] = -.0129;
        hngpt[2][0] = (rnk[2][0]+((.0036*cnk[2][0][2])+((.0776*cnk[1][0][1])-(
          .0064*cnk[2][0][0]))));
        hngpt[2][1] = (rnk[2][1]+((.0036*cnk[2][1][2])+((.0776*c1)-(.0064*
          cnk[2][1][0]))));
        hngpt[2][2] = (rnk[2][2]+((.0036*cnk[2][2][2])+((.0776*cnk[1][2][1])-(
          .0064*cnk[2][2][0]))));
        hngpt[3][0] = (rnk[3][0]+((.0039*cnk[3][0][2])+((.0003*cnk[3][0][0])+(
          .0634*cnk[3][0][1]))));
        hngpt[3][1] = (rnk[3][1]+((.0039*cnk[3][1][2])+((.0003*cnk[3][1][0])+(
          .0634*cnk[3][1][1]))));
        hngpt[3][2] = (rnk[3][2]+((.0039*cnk[3][2][2])+((.0003*cnk[3][2][0])+(
          .0634*cnk[3][2][1]))));
        hngpt[4][0] = (rnk[4][0]+((.0129*cnk[4][0][2])+((.1179*cnk[4][0][1])-(
          .0106*cnk[4][0][0]))));
        hngpt[4][1] = (rnk[4][1]+((.0129*cnk[4][1][2])+((.1179*cnk[4][1][1])-(
          .0106*cnk[4][1][0]))));
        hngpt[4][2] = (rnk[4][2]+((.0129*cnk[4][2][2])+((.1179*cnk[4][2][1])-(
          .0106*cnk[4][2][0]))));
        vpkflg = 1;
    }
/*
 Used 0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain   39 adds/subtracts/negates
                     45 multiplies
                      0 divides
                     27 assignments
*/
}

void sddoltau(void)
{

/*
Compute effect of loop hinge torques
*/
/*
 Used 0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain    0 adds/subtracts/negates
                      0 multiplies
                      0 divides
                      0 assignments
*/
}

void sddoiner(void)
{

/*
Compute inertial accelerations and related temps
*/
    if (inerflg == 0) {
/*
Compute Otk (inertial angular acceleration)
*/
        Otk[1][0] = (u[1]*wk[1][1]);
        Otk[1][1] = -(u[1]*wk[1][0]);
        Otk[2][0] = ((Otk[1][0]*c2)-(u[2]*wk[2][2]));
        Otk[2][2] = ((Otk[1][0]*s2)+(u[2]*wk[2][0]));
        Otk[3][0] = (((Cik[3][2][0]*Otk[2][2])+((Cik[3][0][0]*Otk[2][0])+(
          Cik[3][1][0]*Otk[1][1])))-((.00844600099996266*(u[3]*wk[3][2]))+(
          .019909002399912*(u[3]*wk[3][1]))));
        Otk[3][1] = (((.019909002399912*(u[3]*wk[3][0]))+(.99976612099558*(u[3]*
          wk[3][2])))+((Cik[3][2][1]*Otk[2][2])+((Cik[3][0][1]*Otk[2][0])+(
          Cik[3][1][1]*Otk[1][1]))));
        Otk[3][2] = (((.00844600099996266*(u[3]*wk[3][0]))-(.99976612099558*(
          u[3]*wk[3][1])))+((Cik[3][2][2]*Otk[2][2])+((Cik[3][0][2]*Otk[2][0])+(
          Cik[3][1][2]*Otk[1][1]))));
        Otk[4][0] = (((.195891963900652*(u[4]*wk[4][1]))-(.974058820703242*(u[4]
          *wk[4][2])))+((Cik[4][2][0]*Otk[3][2])+((Cik[4][0][0]*Otk[3][0])+(
          Cik[4][1][0]*Otk[3][1]))));
        Otk[4][1] = (((Cik[4][2][1]*Otk[3][2])+((Cik[4][0][1]*Otk[3][0])+(
          Cik[4][1][1]*Otk[3][1])))-((.113294979100377*(u[4]*wk[4][2]))+(
          .195891963900652*(u[4]*wk[4][0]))));
        Otk[4][2] = (((.113294979100377*(u[4]*wk[4][1]))+(.974058820703242*(u[4]
          *wk[4][0])))+((Cik[4][2][2]*Otk[3][2])+((Cik[4][0][2]*Otk[3][0])+(
          Cik[4][1][2]*Otk[3][1]))));
/*
Compute Atk (inertial linear acceleration)
*/
        Atk[2][0] = (((.0776*Otk[2][2])-(.0036*Otk[1][1]))+((wk[2][1]*
          Wkrpk[2][2])-(wk[2][2]*Wkrpk[2][1])));
        Atk[2][1] = (((.0036*Otk[2][0])+(.0064*Otk[2][2]))+((wk[2][2]*
          Wkrpk[2][0])-(wk[2][0]*Wkrpk[2][2])));
        Atk[2][2] = (((wk[2][0]*Wkrpk[2][1])-(wk[2][1]*Wkrpk[2][0]))-((.0064*
          Otk[1][1])+(.0776*Otk[2][0])));
        AiOiWi[3][0] = (Atk[2][0]+(((.0085*Otk[1][1])+(.2131*Otk[2][2]))+((
          Wirk[3][2]*wk[2][1])-(Wirk[3][1]*wk[2][2]))));
        AiOiWi[3][1] = (Atk[2][1]+(((Wirk[3][0]*wk[2][2])-(Wirk[3][2]*wk[2][0]))
          -((.0006*Otk[2][2])+(.0085*Otk[2][0]))));
        AiOiWi[3][2] = (Atk[2][2]+(((.0006*Otk[1][1])-(.2131*Otk[2][0]))+((
          Wirk[3][1]*wk[2][0])-(Wirk[3][0]*wk[2][1]))));
        Atk[3][0] = (((AiOiWi[3][2]*Cik[3][2][0])+((AiOiWi[3][0]*Cik[3][0][0])+(
          AiOiWi[3][1]*Cik[3][1][0])))+(((.0634*Otk[3][2])-(.0039*Otk[3][1]))+((
          wk[3][1]*Wkrpk[3][2])-(wk[3][2]*Wkrpk[3][1]))));
        Atk[3][1] = (((AiOiWi[3][2]*Cik[3][2][1])+((AiOiWi[3][0]*Cik[3][0][1])+(
          AiOiWi[3][1]*Cik[3][1][1])))+(((.0039*Otk[3][0])-(.0003*Otk[3][2]))+((
          wk[3][2]*Wkrpk[3][0])-(wk[3][0]*Wkrpk[3][2]))));
        Atk[3][2] = (((AiOiWi[3][2]*Cik[3][2][2])+((AiOiWi[3][0]*Cik[3][0][2])+(
          AiOiWi[3][1]*Cik[3][1][2])))+(((.0003*Otk[3][1])-(.0634*Otk[3][0]))+((
          wk[3][0]*Wkrpk[3][1])-(wk[3][1]*Wkrpk[3][0]))));
        AiOiWi[4][0] = (Atk[3][0]+(((Wirk[4][2]*wk[3][1])-(Wirk[4][1]*wk[3][2]))
          -((.0124*Otk[3][1])+(.0501*Otk[3][2]))));
        AiOiWi[4][1] = (Atk[3][1]+(((.0124*Otk[3][0])+(.0174*Otk[3][2]))+((
          Wirk[4][0]*wk[3][2])-(Wirk[4][2]*wk[3][0]))));
        AiOiWi[4][2] = (Atk[3][2]+(((.0501*Otk[3][0])-(.0174*Otk[3][1]))+((
          Wirk[4][1]*wk[3][0])-(Wirk[4][0]*wk[3][1]))));
        Atk[4][0] = (((AiOiWi[4][2]*Cik[4][2][0])+((AiOiWi[4][0]*Cik[4][0][0])+(
          AiOiWi[4][1]*Cik[4][1][0])))+(((.1179*Otk[4][2])-(.0129*Otk[4][1]))+((
          wk[4][1]*Wkrpk[4][2])-(wk[4][2]*Wkrpk[4][1]))));
        Atk[4][1] = (((AiOiWi[4][2]*Cik[4][2][1])+((AiOiWi[4][0]*Cik[4][0][1])+(
          AiOiWi[4][1]*Cik[4][1][1])))+(((.0106*Otk[4][2])+(.0129*Otk[4][0]))+((
          wk[4][2]*Wkrpk[4][0])-(wk[4][0]*Wkrpk[4][2]))));
        Atk[4][2] = (((AiOiWi[4][2]*Cik[4][2][2])+((AiOiWi[4][0]*Cik[4][0][2])+(
          AiOiWi[4][1]*Cik[4][1][2])))+(((wk[4][0]*Wkrpk[4][1])-(wk[4][1]*
          Wkrpk[4][0]))-((.0106*Otk[4][1])+(.1179*Otk[4][0]))));
        inerflg = 1;
    }
/*
 Used 0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain   96 adds/subtracts/negates
                    126 multiplies
                      0 divides
                     25 assignments
*/
}

void sddofs0(void)
{

/*
Compute effect of all applied loads
*/
    if (fs0flg == 0) {
        sddoltau();
        sddoiner();
/*
Compute Fstar (forces)
*/
        Fstar[2][0] = ((2.0519*(Atk[2][0]-gk[2][0]))-ufk[9][0]);
        Fstar[2][1] = ((2.0519*(Atk[2][1]+(9.80665*c1)))-ufk[9][1]);
        Fstar[2][2] = ((2.0519*(Atk[2][2]-gk[2][2]))-ufk[9][2]);
        Fstar[3][0] = ((.5464*(Atk[3][0]-gk[3][0]))-ufk[10][0]);
        Fstar[3][1] = ((.5464*(Atk[3][1]-gk[3][1]))-ufk[10][1]);
        Fstar[3][2] = ((.5464*(Atk[3][2]-gk[3][2]))-ufk[10][2]);
        Fstar[4][0] = ((.5464*(Atk[4][0]-gk[4][0]))-ufk[11][0]);
        Fstar[4][1] = ((.5464*(Atk[4][1]-gk[4][1]))-ufk[11][1]);
        Fstar[4][2] = ((.5464*(Atk[4][2]-gk[4][2]))-ufk[11][2]);
/*
Compute Tstar (torques)
*/
        Tstar[2][0] = ((WkIkWk[2][0]+(.0132*Otk[2][0]))-utk[9][0]);
        Tstar[2][1] = ((.001988*Otk[1][1])-utk[9][1]);
        Tstar[2][2] = ((WkIkWk[2][2]+(.0132*Otk[2][2]))-utk[9][2]);
        Tstar[3][0] = ((WkIkWk[3][0]+(.0030585*Otk[3][0]))-utk[10][0]);
        Tstar[3][1] = ((.00045325*Otk[3][1])-utk[10][1]);
        Tstar[3][2] = ((WkIkWk[3][2]+(.0030585*Otk[3][2]))-utk[10][2]);
        Tstar[4][0] = ((WkIkWk[4][0]+(.0030585*Otk[4][0]))-utk[11][0]);
        Tstar[4][1] = ((.00045325*Otk[4][1])-utk[11][1]);
        Tstar[4][2] = ((WkIkWk[4][2]+(.0030585*Otk[4][2]))-utk[11][2]);
/*
Compute fs0 (RHS ignoring constraints)
*/
        fs0[4] = (utau[4]-(((.0030324545364801*Fstar[4][2])+((
          .000614949586952047*Fstar[4][1])+(.010530303756815*Fstar[4][0])))+((
          .195891963900652*Tstar[4][2])+((.974058820703242*Tstar[4][1])-(
          .113294979100377*Tstar[4][0])))));
        Fstark[3][0] = (Fstar[3][0]+((Cik[4][0][2]*Fstar[4][2])+((Cik[4][0][0]*
          Fstar[4][0])+(Cik[4][0][1]*Fstar[4][1]))));
        Fstark[3][1] = (Fstar[3][1]+((Cik[4][1][2]*Fstar[4][2])+((Cik[4][1][0]*
          Fstar[4][0])+(Cik[4][1][1]*Fstar[4][1]))));
        Fstark[3][2] = (Fstar[3][2]+((Cik[4][2][2]*Fstar[4][2])+((Cik[4][2][0]*
          Fstar[4][0])+(Cik[4][2][1]*Fstar[4][1]))));
        tvec1[0] = (Tstar[4][0]+((Fstar[4][2]*rik[4][1])-(Fstar[4][1]*rik[4][2])
          ));
        tvec1[1] = (Tstar[4][1]+((Fstar[4][0]*rik[4][2])-(Fstar[4][2]*rik[4][0])
          ));
        tvec1[2] = (Tstar[4][2]+((Fstar[4][1]*rik[4][0])-(Fstar[4][0]*rik[4][1])
          ));
        Tstark[3][0] = (Tstar[3][0]+((Cik[4][0][2]*tvec1[2])+((Cik[4][0][0]*
          tvec1[0])+(Cik[4][0][1]*tvec1[1]))));
        Tstark[3][1] = (Tstar[3][1]+((Cik[4][1][2]*tvec1[2])+((Cik[4][1][0]*
          tvec1[0])+(Cik[4][1][1]*tvec1[1]))));
        Tstark[3][2] = (Tstar[3][2]+((Cik[4][2][2]*tvec1[2])+((Cik[4][2][0]*
          tvec1[0])+(Cik[4][2][1]*tvec1[1]))));
        fs0[3] = (utau[3]-((((.00390506057260274*Fstark[3][1])-(
          .00129517015605427*Fstark[3][0]))-(.0633826382708198*Fstark[3][2]))+((
          (.00844600099996266*Tstark[3][1])+(.99976612099558*Tstark[3][0]))-(
          .019909002399912*Tstark[3][2]))));
        Fstark[2][0] = (Fstar[2][0]+((Cik[3][0][2]*Fstark[3][2])+((Cik[3][0][0]*
          Fstark[3][0])+(Cik[3][0][1]*Fstark[3][1]))));
        Fstark[2][1] = (Fstar[2][1]+((Cik[3][1][2]*Fstark[3][2])+((Cik[3][1][0]*
          Fstark[3][0])+(Cik[3][1][1]*Fstark[3][1]))));
        Fstark[2][2] = (Fstar[2][2]+((Cik[3][2][2]*Fstark[3][2])+((Cik[3][2][0]*
          Fstark[3][0])+(Cik[3][2][1]*Fstark[3][1]))));
        tvec1[0] = (Tstark[3][0]+((Fstark[3][2]*rik[3][1])-(Fstark[3][1]*
          rik[3][2])));
        tvec1[1] = (Tstark[3][1]+((Fstark[3][0]*rik[3][2])-(Fstark[3][2]*
          rik[3][0])));
        tvec1[2] = (Tstark[3][2]+((Fstark[3][1]*rik[3][0])-(Fstark[3][0]*
          rik[3][1])));
        Tstark[2][0] = (Tstar[2][0]+((Cik[3][0][2]*tvec1[2])+((Cik[3][0][0]*
          tvec1[0])+(Cik[3][0][1]*tvec1[1]))));
        Tstark[2][1] = (Tstar[2][1]+((Cik[3][1][2]*tvec1[2])+((Cik[3][1][0]*
          tvec1[0])+(Cik[3][1][1]*tvec1[1]))));
        Tstark[2][2] = (Tstar[2][2]+((Cik[3][2][2]*tvec1[2])+((Cik[3][2][0]*
          tvec1[0])+(Cik[3][2][1]*tvec1[1]))));
        fs0[2] = (utau[2]-(Tstark[2][1]-((.0036*Fstark[2][0])+(.0064*
          Fstark[2][2]))));
        Fstark[1][0] = (((Fstark[2][0]*c2)+(Fstark[2][2]*s2))-ufk[8][0]);
        Fstark[1][1] = (Fstark[2][1]-ufk[8][1]);
        Fstark[1][2] = (((Fstark[2][2]*c2)-(Fstark[2][0]*s2))-ufk[8][2]);
        tvec1[0] = (Tstark[2][0]+((.0036*Fstark[2][1])-(.0776*Fstark[2][2])));
        tvec1[1] = (Tstark[2][1]-((.0036*Fstark[2][0])+(.0064*Fstark[2][2])));
        tvec1[2] = (Tstark[2][2]+((.0064*Fstark[2][1])+(.0776*Fstark[2][0])));
        Tstark[1][0] = (((tvec1[0]*c2)+(tvec1[2]*s2))-utk[8][0]);
        Tstark[1][1] = (tvec1[1]-utk[8][1]);
        Tstark[1][2] = (((tvec1[2]*c2)-(tvec1[0]*s2))-utk[8][2]);
        fs0[1] = (utau[1]-Tstark[1][2]);
        Fstark[0][0] = (((Fstark[1][0]*c1)-(Fstark[1][1]*s1))-ufk[7][0]);
        Fstark[0][1] = (((Fstark[1][0]*s1)+(Fstark[1][1]*c1))-ufk[7][1]);
        Fstark[0][2] = (Fstark[1][2]-ufk[7][2]);
        Tstark[0][0] = (((Tstark[1][0]*c1)-(Tstark[1][1]*s1))-utk[7][0]);
        Tstark[0][1] = (((Tstark[1][0]*s1)+(Tstark[1][1]*c1))-utk[7][1]);
        Tstark[0][2] = (Tstark[1][2]-utk[7][2]);
        fs0[0] = (utau[0]-Tstark[0][1]);
        fs0flg = 1;
    }
/*
 Used -0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain  124 adds/subtracts/negates
                    103 multiplies
                      0 divides
                     56 assignments
*/
}

void sddomm(int routine)
{
    int dumroutine,errnum;

    if (mmflg == 0) {
/*
Compute gains (DD, G)
*/
        DD[4] = 1532.60616412784;
        N11[4][0][0] = ((Cik[4][0][0]-(.00597787430190843*Cik[4][0][1]))-(
          .0294782408671551*Cik[4][0][2]));
        N11[4][0][1] = (Cik[4][0][1]-(.00172207402231696*Cik[4][0][2]));
        N11[4][1][0] = ((Cik[4][1][0]-(.00597787430190843*Cik[4][1][1]))-(
          .0294782408671551*Cik[4][1][2]));
        N11[4][1][1] = (Cik[4][1][1]-(.00172207402231696*Cik[4][1][2]));
        N11[4][2][0] = ((Cik[4][2][0]-(.00597787430190843*Cik[4][2][1]))-(
          .0294782408671551*Cik[4][2][2]));
        N11[4][2][1] = (Cik[4][2][1]-(.00172207402231696*Cik[4][2][2]));
        N21[4][0][0] = (((.107177506493147*Cik[4][0][2])+((.00956312361345238*
          Cik[4][0][0])-(.0204420492066602*Cik[4][0][1])))+((rikt[4][0][0]-(
          .00597787430190843*rikt[4][0][1]))-(.0294782408671551*rikt[4][0][2])))
          ;
        N21[4][0][1] = ((rikt[4][0][1]-(.00172207402231696*rikt[4][0][2]))+((
          .00997730994262283*Cik[4][0][2])+((.0134631680612868*Cik[4][0][0])-(
          .000440595050171299*Cik[4][0][1]))));
        N21[4][0][2] = (rikt[4][0][2]-((.0030969234032417*Cik[4][0][2])+((
          .0128820668125597*Cik[4][0][1])+(.116108880725584*Cik[4][0][0]))));
        N21[4][1][0] = (((.107177506493147*Cik[4][1][2])+((.00956312361345238*
          Cik[4][1][0])-(.0204420492066602*Cik[4][1][1])))+((rikt[4][1][0]-(
          .00597787430190843*rikt[4][1][1]))-(.0294782408671551*rikt[4][1][2])))
          ;
        N21[4][1][1] = ((rikt[4][1][1]-(.00172207402231696*rikt[4][1][2]))+((
          .00997730994262283*Cik[4][1][2])+((.0134631680612868*Cik[4][1][0])-(
          .000440595050171299*Cik[4][1][1]))));
        N21[4][1][2] = (rikt[4][1][2]-((.0030969234032417*Cik[4][1][2])+((
          .0128820668125597*Cik[4][1][1])+(.116108880725584*Cik[4][1][0]))));
        N21[4][2][0] = (((.107177506493147*Cik[4][2][2])+((.00956312361345238*
          Cik[4][2][0])-(.0204420492066602*Cik[4][2][1])))+((rikt[4][2][0]-(
          .00597787430190843*rikt[4][2][1]))-(.0294782408671551*rikt[4][2][2])))
          ;
        N21[4][2][1] = ((rikt[4][2][1]-(.00172207402231696*rikt[4][2][2]))+((
          .00997730994262283*Cik[4][2][2])+((.0134631680612868*Cik[4][2][0])-(
          .000440595050171299*Cik[4][2][1]))));
        N21[4][2][2] = (rikt[4][2][2]-((.0030969234032417*Cik[4][2][2])+((
          .0128820668125597*Cik[4][2][1])+(.116108880725584*Cik[4][2][0]))));
        N22[4][0][0] = ((.124001479926711*Cik[4][0][2])+(Cik[4][0][0]+(
          .0913744465726291*Cik[4][0][1])));
        N22[4][0][1] = (Cik[4][0][1]-(4.97242868623871*Cik[4][0][2]));
        N22[4][1][0] = ((.124001479926711*Cik[4][1][2])+(Cik[4][1][0]+(
          .0913744465726291*Cik[4][1][1])));
        N22[4][1][1] = (Cik[4][1][1]-(4.97242868623871*Cik[4][1][2]));
        N22[4][2][0] = ((.124001479926711*Cik[4][2][2])+(Cik[4][2][0]+(
          .0913744465726291*Cik[4][2][1])));
        N22[4][2][1] = (Cik[4][2][1]-(4.97242868623871*Cik[4][2][2]));
        P11[3][0][0] = (.5464+((.541760007373106*(Cik[4][0][2]*Cik[4][0][2]))+((
          .495661952894657*(N11[4][0][0]*N11[4][0][0]))+(.546209253716642*(
          N11[4][0][1]*N11[4][0][1])))));
        P11[3][0][1] = ((.541760007373106*(Cik[4][0][2]*Cik[4][1][2]))+((
          .495661952894657*(N11[4][0][0]*N11[4][1][0]))+(.546209253716642*(
          N11[4][0][1]*N11[4][1][1]))));
        P11[3][0][2] = ((.541760007373106*(Cik[4][0][2]*Cik[4][2][2]))+((
          .495661952894657*(N11[4][0][0]*N11[4][2][0]))+(.546209253716642*(
          N11[4][0][1]*N11[4][2][1]))));
        P11[3][1][0] = P11[3][0][1];
        P11[3][1][1] = (.5464+((.541760007373106*(Cik[4][1][2]*Cik[4][1][2]))+((
          .495661952894657*(N11[4][1][0]*N11[4][1][0]))+(.546209253716642*(
          N11[4][1][1]*N11[4][1][1])))));
        P11[3][1][2] = ((.541760007373106*(Cik[4][1][2]*Cik[4][2][2]))+((
          .495661952894657*(N11[4][1][0]*N11[4][2][0]))+(.546209253716642*(
          N11[4][1][1]*N11[4][2][1]))));
        P11[3][2][0] = P11[3][0][2];
        P11[3][2][1] = P11[3][1][2];
        P11[3][2][2] = (.5464+((.541760007373106*(Cik[4][2][2]*Cik[4][2][2]))+((
          .495661952894657*(N11[4][2][0]*N11[4][2][0]))+(.546209253716642*(
          N11[4][2][1]*N11[4][2][1])))));
        Pd[3][0][0] = ((.541760007373106*(Cik[4][0][2]*N21[4][0][2]))+((
          .495661952894657*(N11[4][0][0]*N21[4][0][0]))+(.546209253716642*(
          N11[4][0][1]*N21[4][0][1]))));
        Pd[3][0][1] = (((.541760007373106*(Cik[4][0][2]*N21[4][1][2]))+((
          .495661952894657*(N11[4][0][0]*N21[4][1][0]))+(.546209253716642*(
          N11[4][0][1]*N21[4][1][1]))))-.00213096);
        Pd[3][0][2] = (.03464176+((.541760007373106*(Cik[4][0][2]*N21[4][2][2]))
          +((.495661952894657*(N11[4][0][0]*N21[4][2][0]))+(.546209253716642*(
          N11[4][0][1]*N21[4][2][1])))));
        Pd[3][1][0] = (.00213096+((.541760007373106*(Cik[4][1][2]*N21[4][0][2]))
          +((.495661952894657*(N11[4][1][0]*N21[4][0][0]))+(.546209253716642*(
          N11[4][1][1]*N21[4][0][1])))));
        Pd[3][1][1] = ((.541760007373106*(Cik[4][1][2]*N21[4][1][2]))+((
          .495661952894657*(N11[4][1][0]*N21[4][1][0]))+(.546209253716642*(
          N11[4][1][1]*N21[4][1][1]))));
        Pd[3][1][2] = (((.541760007373106*(Cik[4][1][2]*N21[4][2][2]))+((
          .495661952894657*(N11[4][1][0]*N21[4][2][0]))+(.546209253716642*(
          N11[4][1][1]*N21[4][2][1]))))-.00016392);
        Pd[3][2][0] = (((.541760007373106*(Cik[4][2][2]*N21[4][0][2]))+((
          .495661952894657*(N11[4][2][0]*N21[4][0][0]))+(.546209253716642*(
          N11[4][2][1]*N21[4][0][1]))))-.03464176);
        Pd[3][2][1] = (.00016392+((.541760007373106*(Cik[4][2][2]*N21[4][1][2]))
          +((.495661952894657*(N11[4][2][0]*N21[4][1][0]))+(.546209253716642*(
          N11[4][2][1]*N21[4][1][1])))));
        Pd[3][2][2] = ((.541760007373106*(Cik[4][2][2]*N21[4][2][2]))+((
          .495661952894657*(N11[4][2][0]*N21[4][2][0]))+(.546209253716642*(
          N11[4][2][1]*N21[4][2][1]))));
        P22[3][0][0] = (.005263098328+(((9.71785999195511e-5*(N22[4][0][1]*
          N22[4][0][1]))+(.00285383227725854*(N22[4][0][0]*N22[4][0][0])))+((
          .541760007373106*(N21[4][0][2]*N21[4][0][2]))+((.495661952894657*(
          N21[4][0][0]*N21[4][0][0]))+(.546209253716642*(N21[4][0][1]*
          N21[4][0][1]))))));
        P22[3][0][1] = ((((9.71785999195511e-5*(N22[4][0][1]*N22[4][1][1]))+(
          .00285383227725854*(N22[4][0][0]*N22[4][1][0])))+((.541760007373106*(
          N21[4][0][2]*N21[4][1][2]))+((.495661952894657*(N21[4][0][0]*
          N21[4][1][0]))+(.546209253716642*(N21[4][0][1]*N21[4][1][1])))))-
          1.0392528e-5);
        P22[3][0][2] = ((((9.71785999195511e-5*(N22[4][0][1]*N22[4][2][1]))+(
          .00285383227725854*(N22[4][0][0]*N22[4][2][0])))+((.541760007373106*(
          N21[4][0][2]*N21[4][2][2]))+((.495661952894657*(N21[4][0][0]*
          N21[4][2][0]))+(.546209253716642*(N21[4][0][1]*N21[4][2][1])))))-
          6.39288e-7);
        P22[3][1][0] = P22[3][0][1];
        P22[3][1][1] = (.00046160992+(((9.71785999195511e-5*(N22[4][1][1]*
          N22[4][1][1]))+(.00285383227725854*(N22[4][1][0]*N22[4][1][0])))+((
          .541760007373106*(N21[4][1][2]*N21[4][1][2]))+((.495661952894657*(
          N21[4][1][0]*N21[4][1][0]))+(.546209253716642*(N21[4][1][1]*
          N21[4][1][1]))))));
        P22[3][1][2] = ((((9.71785999195511e-5*(N22[4][1][1]*N22[4][2][1]))+(
          .00285383227725854*(N22[4][1][0]*N22[4][2][0])))+((.541760007373106*(
          N21[4][1][2]*N21[4][2][2]))+((.495661952894657*(N21[4][1][0]*
          N21[4][2][0]))+(.546209253716642*(N21[4][1][1]*N21[4][2][1])))))-
          .000135102864);
        P22[3][2][0] = P22[3][0][2];
        P22[3][2][1] = P22[3][1][2];
        P22[3][2][2] = (.00525483676+(((9.71785999195511e-5*(N22[4][2][1]*
          N22[4][2][1]))+(.00285383227725854*(N22[4][2][0]*N22[4][2][0])))+((
          .541760007373106*(N21[4][2][2]*N21[4][2][2]))+((.495661952894657*(
          N21[4][2][0]*N21[4][2][0]))+(.546209253716642*(N21[4][2][1]*
          N21[4][2][1]))))));
        PH1[3][0] = (((.00844600099996266*Pd[3][0][1])+(.99976612099558*
          Pd[3][0][0]))-(.019909002399912*Pd[3][0][2]));
        PH1[3][1] = (((.00844600099996266*Pd[3][1][1])+(.99976612099558*
          Pd[3][1][0]))-(.019909002399912*Pd[3][1][2]));
        PH1[3][2] = (((.00844600099996266*Pd[3][2][1])+(.99976612099558*
          Pd[3][2][0]))-(.019909002399912*Pd[3][2][2]));
        PH2[3][0] = (((.00844600099996266*P22[3][0][1])+(.99976612099558*
          P22[3][0][0]))-(.019909002399912*P22[3][0][2]));
        PH2[3][1] = (((.00844600099996266*P22[3][1][1])+(.99976612099558*
          P22[3][1][0]))-(.019909002399912*P22[3][1][2]));
        PH2[3][2] = (((.00844600099996266*P22[3][2][1])+(.99976612099558*
          P22[3][2][0]))-(.019909002399912*P22[3][2][2]));
        DD[3] = (((.00844600099996266*PH2[3][1])+(.99976612099558*PH2[3][0]))-(
          .019909002399912*PH2[3][2]));
        if (DD[3] < 1e-13) {
            sdseterr(17,47);
        } else {
            DD[3] = (1./DD[3]);
        }
        G1[3][0] = (DD[3]*PH1[3][0]);
        G1[3][1] = (DD[3]*PH1[3][1]);
        G1[3][2] = (DD[3]*PH1[3][2]);
        G2[3][0] = (DD[3]*PH2[3][0]);
        G2[3][1] = (DD[3]*PH2[3][1]);
        G2[3][2] = (DD[3]*PH2[3][2]);
        P11[3][0][0] = (P11[3][0][0]-(G1[3][0]*PH1[3][0]));
        P11[3][0][1] = (P11[3][0][1]-(G1[3][1]*PH1[3][0]));
        P11[3][0][2] = (P11[3][0][2]-(G1[3][2]*PH1[3][0]));
        P11[3][1][1] = (P11[3][1][1]-(G1[3][1]*PH1[3][1]));
        P11[3][1][2] = (P11[3][1][2]-(G1[3][2]*PH1[3][1]));
        P11[3][2][2] = (P11[3][2][2]-(G1[3][2]*PH1[3][2]));
        Pd[3][0][0] = (Pd[3][0][0]-(G2[3][0]*PH1[3][0]));
        Pd[3][0][1] = (Pd[3][0][1]-(G2[3][1]*PH1[3][0]));
        Pd[3][0][2] = (Pd[3][0][2]-(G2[3][2]*PH1[3][0]));
        Pd[3][1][0] = (Pd[3][1][0]-(G2[3][0]*PH1[3][1]));
        Pd[3][1][1] = (Pd[3][1][1]-(G2[3][1]*PH1[3][1]));
        Pd[3][1][2] = (Pd[3][1][2]-(G2[3][2]*PH1[3][1]));
        Pd[3][2][0] = (Pd[3][2][0]-(G2[3][0]*PH1[3][2]));
        Pd[3][2][1] = (Pd[3][2][1]-(G2[3][1]*PH1[3][2]));
        Pd[3][2][2] = (Pd[3][2][2]-(G2[3][2]*PH1[3][2]));
        P22[3][0][0] = (P22[3][0][0]-(G2[3][0]*PH2[3][0]));
        P22[3][0][1] = (P22[3][0][1]-(G2[3][1]*PH2[3][0]));
        P22[3][0][2] = (P22[3][0][2]-(G2[3][2]*PH2[3][0]));
        P22[3][1][1] = (P22[3][1][1]-(G2[3][1]*PH2[3][1]));
        P22[3][1][2] = (P22[3][1][2]-(G2[3][2]*PH2[3][1]));
        P22[3][2][2] = (P22[3][2][2]-(G2[3][2]*PH2[3][2]));
        sD1INV[0][0] = 0.;
        if (P11[3][0][0] >= 1e-13) {
            sD1INV[0][0] = (1./P11[3][0][0]);
        }
        sL11[1][0] = (P11[3][0][1]*sD1INV[0][0]);
        sL11[2][0] = (P11[3][0][2]*sD1INV[0][0]);
        sL11D1[1][1] = (P11[3][1][1]-(P11[3][0][1]*sL11[1][0]));
        sL11D1[2][1] = (P11[3][1][2]-(P11[3][0][2]*sL11[1][0]));
        sL11D1[2][2] = (P11[3][2][2]-(P11[3][0][2]*sL11[2][0]));
        sD1INV[1][1] = 0.;
        if (sL11D1[1][1] >= 1e-13) {
            sD1INV[1][1] = (1./sL11D1[1][1]);
        }
        sL11[2][1] = (sD1INV[1][1]*sL11D1[2][1]);
        sL11D1[2][2] = (sL11D1[2][2]-(sL11[2][1]*sL11D1[2][1]));
        sD1INV[2][2] = 0.;
        if (sL11D1[2][2] >= 1e-13) {
            sD1INV[2][2] = (1./sL11D1[2][2]);
        }
        sD1L21[1][0] = (Pd[3][1][0]-(Pd[3][0][0]*sL11[1][0]));
        sD1L21[1][1] = (Pd[3][1][1]-(Pd[3][0][1]*sL11[1][0]));
        sD1L21[1][2] = (Pd[3][1][2]-(Pd[3][0][2]*sL11[1][0]));
        sD1L21[2][0] = (Pd[3][2][0]-((Pd[3][0][0]*sL11[2][0])+(sD1L21[1][0]*
          sL11[2][1])));
        sD1L21[2][1] = (Pd[3][2][1]-((Pd[3][0][1]*sL11[2][0])+(sD1L21[1][1]*
          sL11[2][1])));
        sD1L21[2][2] = (Pd[3][2][2]-((Pd[3][0][2]*sL11[2][0])+(sD1L21[1][2]*
          sL11[2][1])));
        sL21[0][0] = (Pd[3][0][0]*sD1INV[0][0]);
        sL21[0][1] = (sD1INV[1][1]*sD1L21[1][0]);
        sL21[0][2] = (sD1INV[2][2]*sD1L21[2][0]);
        sL21[1][0] = (Pd[3][0][1]*sD1INV[0][0]);
        sL21[1][1] = (sD1INV[1][1]*sD1L21[1][1]);
        sL21[1][2] = (sD1INV[2][2]*sD1L21[2][1]);
        sL21[2][0] = (Pd[3][0][2]*sD1INV[0][0]);
        sL21[2][1] = (sD1INV[1][1]*sD1L21[1][2]);
        sL21[2][2] = (sD1INV[2][2]*sD1L21[2][2]);
        sL22D2[0][0] = (P22[3][0][0]-((sD1L21[2][0]*sL21[0][2])+((Pd[3][0][0]*
          sL21[0][0])+(sD1L21[1][0]*sL21[0][1]))));
        sL22D2[1][0] = (P22[3][0][1]-((sD1L21[2][0]*sL21[1][2])+((Pd[3][0][0]*
          sL21[1][0])+(sD1L21[1][0]*sL21[1][1]))));
        sL22D2[1][1] = (P22[3][1][1]-((sD1L21[2][1]*sL21[1][2])+((Pd[3][0][1]*
          sL21[1][0])+(sD1L21[1][1]*sL21[1][1]))));
        sL22D2[2][0] = (P22[3][0][2]-((sD1L21[2][0]*sL21[2][2])+((Pd[3][0][0]*
          sL21[2][0])+(sD1L21[1][0]*sL21[2][1]))));
        sL22D2[2][1] = (P22[3][1][2]-((sD1L21[2][1]*sL21[2][2])+((Pd[3][0][1]*
          sL21[2][0])+(sD1L21[1][1]*sL21[2][1]))));
        sL22D2[2][2] = (P22[3][2][2]-((sD1L21[2][2]*sL21[2][2])+((Pd[3][0][2]*
          sL21[2][0])+(sD1L21[1][2]*sL21[2][1]))));
        sD2INV[0][0] = 0.;
        if (sL22D2[0][0] >= 1e-13) {
            sD2INV[0][0] = (1./sL22D2[0][0]);
        }
        sL22[1][0] = (sD2INV[0][0]*sL22D2[1][0]);
        sL22[2][0] = (sD2INV[0][0]*sL22D2[2][0]);
        sL22D2[1][1] = (sL22D2[1][1]-(sL22[1][0]*sL22D2[1][0]));
        sL22D2[2][1] = (sL22D2[2][1]-(sL22[1][0]*sL22D2[2][0]));
        sL22D2[2][2] = (sL22D2[2][2]-(sL22[2][0]*sL22D2[2][0]));
        sD2INV[1][1] = 0.;
        if (sL22D2[1][1] >= 1e-13) {
            sD2INV[1][1] = (1./sL22D2[1][1]);
        }
        sL22[2][1] = (sD2INV[1][1]*sL22D2[2][1]);
        sL22D2[2][2] = (sL22D2[2][2]-(sL22[2][1]*sL22D2[2][1]));
        N11[3][0][0] = ((Cik[3][0][0]+(Cik[3][0][1]*sL11[1][0]))+(Cik[3][0][2]*
          sL11[2][0]));
        N11[3][0][1] = (Cik[3][0][1]+(Cik[3][0][2]*sL11[2][1]));
        N11[3][1][0] = ((Cik[3][1][0]+(Cik[3][1][1]*sL11[1][0]))+(Cik[3][1][2]*
          sL11[2][0]));
        N11[3][1][1] = (Cik[3][1][1]+(Cik[3][1][2]*sL11[2][1]));
        N11[3][2][0] = ((Cik[3][2][0]+(Cik[3][2][1]*sL11[1][0]))+(Cik[3][2][2]*
          sL11[2][0]));
        N11[3][2][1] = (Cik[3][2][1]+(Cik[3][2][2]*sL11[2][1]));
        N21[3][0][0] = (((Cik[3][0][2]*sL21[2][0])+((Cik[3][0][0]*sL21[0][0])+(
          Cik[3][0][1]*sL21[1][0])))+((rikt[3][0][0]+(rikt[3][0][1]*sL11[1][0]))
          +(rikt[3][0][2]*sL11[2][0])));
        N21[3][0][1] = ((rikt[3][0][1]+(rikt[3][0][2]*sL11[2][1]))+((
          Cik[3][0][2]*sL21[2][1])+((Cik[3][0][0]*sL21[0][1])+(Cik[3][0][1]*
          sL21[1][1]))));
        N21[3][0][2] = (rikt[3][0][2]+((Cik[3][0][2]*sL21[2][2])+((Cik[3][0][0]*
          sL21[0][2])+(Cik[3][0][1]*sL21[1][2]))));
        N21[3][1][0] = (((Cik[3][1][2]*sL21[2][0])+((Cik[3][1][0]*sL21[0][0])+(
          Cik[3][1][1]*sL21[1][0])))+((rikt[3][1][0]+(rikt[3][1][1]*sL11[1][0]))
          +(rikt[3][1][2]*sL11[2][0])));
        N21[3][1][1] = ((rikt[3][1][1]+(rikt[3][1][2]*sL11[2][1]))+((
          Cik[3][1][2]*sL21[2][1])+((Cik[3][1][0]*sL21[0][1])+(Cik[3][1][1]*
          sL21[1][1]))));
        N21[3][1][2] = (rikt[3][1][2]+((Cik[3][1][2]*sL21[2][2])+((Cik[3][1][0]*
          sL21[0][2])+(Cik[3][1][1]*sL21[1][2]))));
        N21[3][2][0] = (((Cik[3][2][2]*sL21[2][0])+((Cik[3][2][0]*sL21[0][0])+(
          Cik[3][2][1]*sL21[1][0])))+((rikt[3][2][0]+(rikt[3][2][1]*sL11[1][0]))
          +(rikt[3][2][2]*sL11[2][0])));
        N21[3][2][1] = ((rikt[3][2][1]+(rikt[3][2][2]*sL11[2][1]))+((
          Cik[3][2][2]*sL21[2][1])+((Cik[3][2][0]*sL21[0][1])+(Cik[3][2][1]*
          sL21[1][1]))));
        N21[3][2][2] = (rikt[3][2][2]+((Cik[3][2][2]*sL21[2][2])+((Cik[3][2][0]*
          sL21[0][2])+(Cik[3][2][1]*sL21[1][2]))));
        N22[3][0][0] = ((Cik[3][0][0]+(Cik[3][0][1]*sL22[1][0]))+(Cik[3][0][2]*
          sL22[2][0]));
        N22[3][0][1] = (Cik[3][0][1]+(Cik[3][0][2]*sL22[2][1]));
        N22[3][1][0] = ((Cik[3][1][0]+(Cik[3][1][1]*sL22[1][0]))+(Cik[3][1][2]*
          sL22[2][0]));
        N22[3][1][1] = (Cik[3][1][1]+(Cik[3][1][2]*sL22[2][1]));
        N22[3][2][0] = ((Cik[3][2][0]+(Cik[3][2][1]*sL22[1][0]))+(Cik[3][2][2]*
          sL22[2][0]));
        N22[3][2][1] = (Cik[3][2][1]+(Cik[3][2][2]*sL22[2][1]));
        psiD11[3][0][0] = (N11[3][0][0]*P11[3][0][0]);
        psiD11[3][0][1] = (N11[3][0][1]*sL11D1[1][1]);
        psiD11[3][0][2] = (Cik[3][0][2]*sL11D1[2][2]);
        psiD11[3][1][0] = (N11[3][1][0]*P11[3][0][0]);
        psiD11[3][1][1] = (N11[3][1][1]*sL11D1[1][1]);
        psiD11[3][1][2] = (Cik[3][1][2]*sL11D1[2][2]);
        psiD11[3][2][0] = (N11[3][2][0]*P11[3][0][0]);
        psiD11[3][2][1] = (N11[3][2][1]*sL11D1[1][1]);
        psiD11[3][2][2] = (Cik[3][2][2]*sL11D1[2][2]);
        psiD21[3][0][0] = (N21[3][0][0]*P11[3][0][0]);
        psiD21[3][0][1] = (N21[3][0][1]*sL11D1[1][1]);
        psiD21[3][0][2] = (N21[3][0][2]*sL11D1[2][2]);
        psiD21[3][1][0] = (N21[3][1][0]*P11[3][0][0]);
        psiD21[3][1][1] = (N21[3][1][1]*sL11D1[1][1]);
        psiD21[3][1][2] = (N21[3][1][2]*sL11D1[2][2]);
        psiD21[3][2][0] = (N21[3][2][0]*P11[3][0][0]);
        psiD21[3][2][1] = (N21[3][2][1]*sL11D1[1][1]);
        psiD21[3][2][2] = (N21[3][2][2]*sL11D1[2][2]);
        psiD22[3][0][0] = (N22[3][0][0]*sL22D2[0][0]);
        psiD22[3][0][1] = (N22[3][0][1]*sL22D2[1][1]);
        psiD22[3][0][2] = (Cik[3][0][2]*sL22D2[2][2]);
        psiD22[3][1][0] = (N22[3][1][0]*sL22D2[0][0]);
        psiD22[3][1][1] = (N22[3][1][1]*sL22D2[1][1]);
        psiD22[3][1][2] = (Cik[3][1][2]*sL22D2[2][2]);
        psiD22[3][2][0] = (N22[3][2][0]*sL22D2[0][0]);
        psiD22[3][2][1] = (N22[3][2][1]*sL22D2[1][1]);
        psiD22[3][2][2] = (Cik[3][2][2]*sL22D2[2][2]);
        P11[2][0][0] = (2.0519+((Cik[3][0][2]*psiD11[3][0][2])+((N11[3][0][0]*
          psiD11[3][0][0])+(N11[3][0][1]*psiD11[3][0][1]))));
        P11[2][0][1] = ((Cik[3][1][2]*psiD11[3][0][2])+((N11[3][1][0]*
          psiD11[3][0][0])+(N11[3][1][1]*psiD11[3][0][1])));
        P11[2][0][2] = ((Cik[3][2][2]*psiD11[3][0][2])+((N11[3][2][0]*
          psiD11[3][0][0])+(N11[3][2][1]*psiD11[3][0][1])));
        P11[2][1][0] = P11[2][0][1];
        P11[2][1][1] = (2.0519+((Cik[3][1][2]*psiD11[3][1][2])+((N11[3][1][0]*
          psiD11[3][1][0])+(N11[3][1][1]*psiD11[3][1][1]))));
        P11[2][1][2] = ((Cik[3][2][2]*psiD11[3][1][2])+((N11[3][2][0]*
          psiD11[3][1][0])+(N11[3][2][1]*psiD11[3][1][1])));
        P11[2][2][0] = P11[2][0][2];
        P11[2][2][1] = P11[2][1][2];
        P11[2][2][2] = (2.0519+((Cik[3][2][2]*psiD11[3][2][2])+((N11[3][2][0]*
          psiD11[3][2][0])+(N11[3][2][1]*psiD11[3][2][1]))));
        Pd[2][0][0] = ((N21[3][0][2]*psiD11[3][0][2])+((N21[3][0][0]*
          psiD11[3][0][0])+(N21[3][0][1]*psiD11[3][0][1])));
        Pd[2][0][1] = (((N21[3][1][2]*psiD11[3][0][2])+((N21[3][1][0]*
          psiD11[3][0][0])+(N21[3][1][1]*psiD11[3][0][1])))-.00738684);
        Pd[2][0][2] = (.15922744+((N21[3][2][2]*psiD11[3][0][2])+((N21[3][2][0]*
          psiD11[3][0][0])+(N21[3][2][1]*psiD11[3][0][1]))));
        Pd[2][1][0] = (.00738684+((N21[3][0][2]*psiD11[3][1][2])+((N21[3][0][0]*
          psiD11[3][1][0])+(N21[3][0][1]*psiD11[3][1][1]))));
        Pd[2][1][1] = ((N21[3][1][2]*psiD11[3][1][2])+((N21[3][1][0]*
          psiD11[3][1][0])+(N21[3][1][1]*psiD11[3][1][1])));
        Pd[2][1][2] = (.01313216+((N21[3][2][2]*psiD11[3][1][2])+((N21[3][2][0]*
          psiD11[3][1][0])+(N21[3][2][1]*psiD11[3][1][1]))));
        Pd[2][2][0] = (((N21[3][0][2]*psiD11[3][2][2])+((N21[3][0][0]*
          psiD11[3][2][0])+(N21[3][0][1]*psiD11[3][2][1])))-.15922744);
        Pd[2][2][1] = (((N21[3][1][2]*psiD11[3][2][2])+((N21[3][1][0]*
          psiD11[3][2][0])+(N21[3][1][1]*psiD11[3][2][1])))-.01313216);
        Pd[2][2][2] = ((N21[3][2][2]*psiD11[3][2][2])+((N21[3][2][0]*
          psiD11[3][2][0])+(N21[3][2][1]*psiD11[3][2][1])));
        P22[2][0][0] = (.025582641968+(((Cik[3][0][2]*psiD22[3][0][2])+((
          N22[3][0][0]*psiD22[3][0][0])+(N22[3][0][1]*psiD22[3][0][1])))+((
          N21[3][0][2]*psiD21[3][0][2])+((N21[3][0][0]*psiD21[3][0][0])+(
          N21[3][0][1]*psiD21[3][0][1])))));
        P22[2][0][1] = (.001019055616+(((Cik[3][1][2]*psiD22[3][0][2])+((
          N22[3][1][0]*psiD22[3][0][0])+(N22[3][1][1]*psiD22[3][0][1])))+((
          N21[3][1][2]*psiD21[3][0][2])+((N21[3][1][0]*psiD21[3][0][0])+(
          N21[3][1][1]*psiD21[3][0][1])))));
        P22[2][0][2] = (4.7275776e-5+(((Cik[3][2][2]*psiD22[3][0][2])+((
          N22[3][2][0]*psiD22[3][0][0])+(N22[3][2][1]*psiD22[3][0][1])))+((
          N21[3][2][2]*psiD21[3][0][2])+((N21[3][2][0]*psiD21[3][0][0])+(
          N21[3][2][1]*psiD21[3][0][1])))));
        P22[2][1][0] = P22[2][0][1];
        P22[2][1][1] = (.002098638448+(((Cik[3][1][2]*psiD22[3][1][2])+((
          N22[3][1][0]*psiD22[3][1][0])+(N22[3][1][1]*psiD22[3][1][1])))+((
          N21[3][1][2]*psiD21[3][1][2])+((N21[3][1][0]*psiD21[3][1][0])+(
          N21[3][1][1]*psiD21[3][1][1])))));
        P22[2][1][2] = ((((Cik[3][2][2]*psiD22[3][1][2])+((N22[3][2][0]*
          psiD22[3][1][0])+(N22[3][2][1]*psiD22[3][1][1])))+((N21[3][2][2]*
          psiD21[3][1][2])+((N21[3][2][0]*psiD21[3][1][0])+(N21[3][2][1]*
          psiD21[3][1][1]))))-.000573218784);
        P22[2][2][0] = P22[2][0][2];
        P22[2][2][1] = P22[2][1][2];
        P22[2][2][2] = (.025640095168+(((Cik[3][2][2]*psiD22[3][2][2])+((
          N22[3][2][0]*psiD22[3][2][0])+(N22[3][2][1]*psiD22[3][2][1])))+((
          N21[3][2][2]*psiD21[3][2][2])+((N21[3][2][0]*psiD21[3][2][0])+(
          N21[3][2][1]*psiD21[3][2][1])))));
        PH1[2][0] = Pd[2][0][1];
        PH1[2][1] = Pd[2][1][1];
        PH1[2][2] = Pd[2][2][1];
        PH2[2][0] = P22[2][0][1];
        PH2[2][1] = P22[2][1][1];
        PH2[2][2] = P22[2][2][1];
        if (PH2[2][1] < 1e-13) {
            sdseterr(routine,47);
        } else {
            DD[2] = (1./PH2[2][1]);
        }
        G1[2][0] = (DD[2]*PH1[2][0]);
        G1[2][1] = (DD[2]*PH1[2][1]);
        G1[2][2] = (DD[2]*PH1[2][2]);
        G2[2][0] = (DD[2]*PH2[2][0]);
        G2[2][2] = (DD[2]*PH2[2][2]);
        P11[2][0][0] = (P11[2][0][0]-(G1[2][0]*PH1[2][0]));
        P11[2][0][1] = (P11[2][0][1]-(G1[2][1]*PH1[2][0]));
        P11[2][0][2] = (P11[2][0][2]-(G1[2][2]*PH1[2][0]));
        P11[2][1][1] = (P11[2][1][1]-(G1[2][1]*PH1[2][1]));
        P11[2][1][2] = (P11[2][1][2]-(G1[2][2]*PH1[2][1]));
        P11[2][2][2] = (P11[2][2][2]-(G1[2][2]*PH1[2][2]));
        Pd[2][0][0] = (Pd[2][0][0]-(G2[2][0]*PH1[2][0]));
        Pd[2][0][1] = (Pd[2][0][1]-PH1[2][0]);
        Pd[2][0][2] = (Pd[2][0][2]-(G2[2][2]*PH1[2][0]));
        Pd[2][1][0] = (Pd[2][1][0]-(G2[2][0]*PH1[2][1]));
        Pd[2][1][1] = (Pd[2][1][1]-PH1[2][1]);
        Pd[2][1][2] = (Pd[2][1][2]-(G2[2][2]*PH1[2][1]));
        Pd[2][2][0] = (Pd[2][2][0]-(G2[2][0]*PH1[2][2]));
        Pd[2][2][1] = (Pd[2][2][1]-PH1[2][2]);
        Pd[2][2][2] = (Pd[2][2][2]-(G2[2][2]*PH1[2][2]));
        P22[2][0][0] = (P22[2][0][0]-(G2[2][0]*PH2[2][0]));
        P22[2][0][1] = (P22[2][0][1]-PH2[2][0]);
        P22[2][0][2] = (P22[2][0][2]-(G2[2][2]*PH2[2][0]));
        P22[2][1][1] = (P22[2][1][1]-PH2[2][1]);
        P22[2][1][2] = (P22[2][1][2]-PH2[2][2]);
        P22[2][2][2] = (P22[2][2][2]-(G2[2][2]*PH2[2][2]));
        sD1INV[0][0] = 0.;
        if (P11[2][0][0] >= 1e-13) {
            sD1INV[0][0] = (1./P11[2][0][0]);
        }
        sL11[1][0] = (P11[2][0][1]*sD1INV[0][0]);
        sL11[2][0] = (P11[2][0][2]*sD1INV[0][0]);
        sL11D1[1][1] = (P11[2][1][1]-(P11[2][0][1]*sL11[1][0]));
        sL11D1[2][1] = (P11[2][1][2]-(P11[2][0][2]*sL11[1][0]));
        sL11D1[2][2] = (P11[2][2][2]-(P11[2][0][2]*sL11[2][0]));
        sD1INV[1][1] = 0.;
        if (sL11D1[1][1] >= 1e-13) {
            sD1INV[1][1] = (1./sL11D1[1][1]);
        }
        sL11[2][1] = (sD1INV[1][1]*sL11D1[2][1]);
        sL11D1[2][2] = (sL11D1[2][2]-(sL11[2][1]*sL11D1[2][1]));
        sD1INV[2][2] = 0.;
        if (sL11D1[2][2] >= 1e-13) {
            sD1INV[2][2] = (1./sL11D1[2][2]);
        }
        sD1L21[1][0] = (Pd[2][1][0]-(Pd[2][0][0]*sL11[1][0]));
        sD1L21[1][1] = (Pd[2][1][1]-(Pd[2][0][1]*sL11[1][0]));
        sD1L21[1][2] = (Pd[2][1][2]-(Pd[2][0][2]*sL11[1][0]));
        sD1L21[2][0] = (Pd[2][2][0]-((Pd[2][0][0]*sL11[2][0])+(sD1L21[1][0]*
          sL11[2][1])));
        sD1L21[2][1] = (Pd[2][2][1]-((Pd[2][0][1]*sL11[2][0])+(sD1L21[1][1]*
          sL11[2][1])));
        sD1L21[2][2] = (Pd[2][2][2]-((Pd[2][0][2]*sL11[2][0])+(sD1L21[1][2]*
          sL11[2][1])));
        sL21[0][0] = (Pd[2][0][0]*sD1INV[0][0]);
        sL21[0][1] = (sD1INV[1][1]*sD1L21[1][0]);
        sL21[0][2] = (sD1INV[2][2]*sD1L21[2][0]);
        sL21[1][0] = (Pd[2][0][1]*sD1INV[0][0]);
        sL21[1][1] = (sD1INV[1][1]*sD1L21[1][1]);
        sL21[1][2] = (sD1INV[2][2]*sD1L21[2][1]);
        sL21[2][0] = (Pd[2][0][2]*sD1INV[0][0]);
        sL21[2][1] = (sD1INV[1][1]*sD1L21[1][2]);
        sL21[2][2] = (sD1INV[2][2]*sD1L21[2][2]);
        sL22D2[0][0] = (P22[2][0][0]-((sD1L21[2][0]*sL21[0][2])+((Pd[2][0][0]*
          sL21[0][0])+(sD1L21[1][0]*sL21[0][1]))));
        sL22D2[1][0] = (P22[2][0][1]-((sD1L21[2][0]*sL21[1][2])+((Pd[2][0][0]*
          sL21[1][0])+(sD1L21[1][0]*sL21[1][1]))));
        sL22D2[1][1] = (P22[2][1][1]-((sD1L21[2][1]*sL21[1][2])+((Pd[2][0][1]*
          sL21[1][0])+(sD1L21[1][1]*sL21[1][1]))));
        sL22D2[2][0] = (P22[2][0][2]-((sD1L21[2][0]*sL21[2][2])+((Pd[2][0][0]*
          sL21[2][0])+(sD1L21[1][0]*sL21[2][1]))));
        sL22D2[2][1] = (P22[2][1][2]-((sD1L21[2][1]*sL21[2][2])+((Pd[2][0][1]*
          sL21[2][0])+(sD1L21[1][1]*sL21[2][1]))));
        sL22D2[2][2] = (P22[2][2][2]-((sD1L21[2][2]*sL21[2][2])+((Pd[2][0][2]*
          sL21[2][0])+(sD1L21[1][2]*sL21[2][1]))));
        sD2INV[0][0] = 0.;
        if (sL22D2[0][0] >= 1e-13) {
            sD2INV[0][0] = (1./sL22D2[0][0]);
        }
        sL22[1][0] = (sD2INV[0][0]*sL22D2[1][0]);
        sL22[2][0] = (sD2INV[0][0]*sL22D2[2][0]);
        sL22D2[1][1] = (sL22D2[1][1]-(sL22[1][0]*sL22D2[1][0]));
        sL22D2[2][1] = (sL22D2[2][1]-(sL22[1][0]*sL22D2[2][0]));
        sL22D2[2][2] = (sL22D2[2][2]-(sL22[2][0]*sL22D2[2][0]));
        sD2INV[1][1] = 0.;
        if (sL22D2[1][1] >= 1e-13) {
            sD2INV[1][1] = (1./sL22D2[1][1]);
        }
        sL22[2][1] = (sD2INV[1][1]*sL22D2[2][1]);
        sL22D2[2][2] = (sL22D2[2][2]-(sL22[2][1]*sL22D2[2][1]));
        N11[2][0][0] = (c2+(sL11[2][0]*s2));
        N11[2][0][1] = (sL11[2][1]*s2);
        N11[2][2][0] = ((sL11[2][0]*c2)-s2);
        N11[2][2][1] = (sL11[2][1]*c2);
        N21[2][0][0] = ((sL21[0][0]*c2)+(sL21[2][0]*s2));
        N21[2][0][1] = ((sL21[0][1]*c2)+(sL21[2][1]*s2));
        N21[2][0][2] = ((sL21[0][2]*c2)+(sL21[2][2]*s2));
        N21[2][2][0] = ((sL21[2][0]*c2)-(sL21[0][0]*s2));
        N21[2][2][1] = ((sL21[2][1]*c2)-(sL21[0][1]*s2));
        N21[2][2][2] = ((sL21[2][2]*c2)-(sL21[0][2]*s2));
        N22[2][0][0] = (c2+(sL22[2][0]*s2));
        N22[2][0][1] = (sL22[2][1]*s2);
        N22[2][2][0] = ((sL22[2][0]*c2)-s2);
        N22[2][2][1] = (sL22[2][1]*c2);
        psiD11[2][0][0] = (N11[2][0][0]*P11[2][0][0]);
        psiD11[2][0][1] = (N11[2][0][1]*sL11D1[1][1]);
        psiD11[2][0][2] = (sL11D1[2][2]*s2);
        psiD11[2][1][0] = (P11[2][0][0]*sL11[1][0]);
        psiD11[2][2][0] = (N11[2][2][0]*P11[2][0][0]);
        psiD11[2][2][1] = (N11[2][2][1]*sL11D1[1][1]);
        psiD11[2][2][2] = (sL11D1[2][2]*c2);
        psiD21[2][0][0] = (N21[2][0][0]*P11[2][0][0]);
        psiD21[2][0][1] = (N21[2][0][1]*sL11D1[1][1]);
        psiD21[2][0][2] = (N21[2][0][2]*sL11D1[2][2]);
        psiD21[2][1][0] = (P11[2][0][0]*sL21[1][0]);
        psiD21[2][1][1] = (sL11D1[1][1]*sL21[1][1]);
        psiD21[2][1][2] = (sL11D1[2][2]*sL21[1][2]);
        psiD21[2][2][0] = (N21[2][2][0]*P11[2][0][0]);
        psiD21[2][2][1] = (N21[2][2][1]*sL11D1[1][1]);
        psiD21[2][2][2] = (N21[2][2][2]*sL11D1[2][2]);
        psiD22[2][0][0] = (N22[2][0][0]*sL22D2[0][0]);
        psiD22[2][0][1] = (N22[2][0][1]*sL22D2[1][1]);
        psiD22[2][0][2] = (sL22D2[2][2]*s2);
        psiD22[2][1][0] = (sL22[1][0]*sL22D2[0][0]);
        psiD22[2][2][0] = (N22[2][2][0]*sL22D2[0][0]);
        psiD22[2][2][1] = (N22[2][2][1]*sL22D2[1][1]);
        psiD22[2][2][2] = (sL22D2[2][2]*c2);
        P11[1][0][0] = ((psiD11[2][0][2]*s2)+((N11[2][0][0]*psiD11[2][0][0])+(
          N11[2][0][1]*psiD11[2][0][1])));
        P11[1][0][1] = (psiD11[2][0][1]+(psiD11[2][0][0]*sL11[1][0]));
        P11[1][0][2] = ((psiD11[2][0][2]*c2)+((N11[2][2][0]*psiD11[2][0][0])+(
          N11[2][2][1]*psiD11[2][0][1])));
        P11[1][1][0] = P11[1][0][1];
        P11[1][1][1] = (sL11D1[1][1]+(psiD11[2][1][0]*sL11[1][0]));
        P11[1][1][2] = ((N11[2][2][0]*psiD11[2][1][0])+(N11[2][2][1]*
          sL11D1[1][1]));
        P11[1][2][0] = P11[1][0][2];
        P11[1][2][1] = P11[1][1][2];
        P11[1][2][2] = ((psiD11[2][2][2]*c2)+((N11[2][2][0]*psiD11[2][2][0])+(
          N11[2][2][1]*psiD11[2][2][1])));
        Pd[1][0][0] = ((N21[2][0][2]*psiD11[2][0][2])+((N21[2][0][0]*
          psiD11[2][0][0])+(N21[2][0][1]*psiD11[2][0][1])));
        Pd[1][0][1] = ((psiD11[2][0][2]*sL21[1][2])+((psiD11[2][0][0]*sL21[1][0]
          )+(psiD11[2][0][1]*sL21[1][1])));
        Pd[1][0][2] = ((N21[2][2][2]*psiD11[2][0][2])+((N21[2][2][0]*
          psiD11[2][0][0])+(N21[2][2][1]*psiD11[2][0][1])));
        Pd[1][1][0] = ((N21[2][0][0]*psiD11[2][1][0])+(N21[2][0][1]*sL11D1[1][1]
          ));
        Pd[1][1][1] = ((psiD11[2][1][0]*sL21[1][0])+(sL11D1[1][1]*sL21[1][1]));
        Pd[1][1][2] = ((N21[2][2][0]*psiD11[2][1][0])+(N21[2][2][1]*sL11D1[1][1]
          ));
        Pd[1][2][0] = ((N21[2][0][2]*psiD11[2][2][2])+((N21[2][0][0]*
          psiD11[2][2][0])+(N21[2][0][1]*psiD11[2][2][1])));
        Pd[1][2][1] = ((psiD11[2][2][2]*sL21[1][2])+((psiD11[2][2][0]*sL21[1][0]
          )+(psiD11[2][2][1]*sL21[1][1])));
        Pd[1][2][2] = ((N21[2][2][2]*psiD11[2][2][2])+((N21[2][2][0]*
          psiD11[2][2][0])+(N21[2][2][1]*psiD11[2][2][1])));
        P22[1][0][0] = (((N21[2][0][2]*psiD21[2][0][2])+((N21[2][0][0]*
          psiD21[2][0][0])+(N21[2][0][1]*psiD21[2][0][1])))+((psiD22[2][0][2]*s2
          )+((N22[2][0][0]*psiD22[2][0][0])+(N22[2][0][1]*psiD22[2][0][1]))));
        P22[1][0][1] = ((psiD22[2][0][1]+(psiD22[2][0][0]*sL22[1][0]))+((
          psiD21[2][0][2]*sL21[1][2])+((psiD21[2][0][0]*sL21[1][0])+(
          psiD21[2][0][1]*sL21[1][1]))));
        P22[1][0][2] = (((N21[2][2][2]*psiD21[2][0][2])+((N21[2][2][0]*
          psiD21[2][0][0])+(N21[2][2][1]*psiD21[2][0][1])))+((psiD22[2][0][2]*c2
          )+((N22[2][2][0]*psiD22[2][0][0])+(N22[2][2][1]*psiD22[2][0][1]))));
        P22[1][1][0] = P22[1][0][1];
        P22[1][1][1] = ((sL22D2[1][1]+(psiD22[2][1][0]*sL22[1][0]))+((
          psiD21[2][1][2]*sL21[1][2])+((psiD21[2][1][0]*sL21[1][0])+(
          psiD21[2][1][1]*sL21[1][1]))));
        P22[1][1][2] = (((N21[2][2][2]*psiD21[2][1][2])+((N21[2][2][0]*
          psiD21[2][1][0])+(N21[2][2][1]*psiD21[2][1][1])))+((N22[2][2][0]*
          psiD22[2][1][0])+(N22[2][2][1]*sL22D2[1][1])));
        P22[1][2][0] = P22[1][0][2];
        P22[1][2][1] = P22[1][1][2];
        P22[1][2][2] = (((N21[2][2][2]*psiD21[2][2][2])+((N21[2][2][0]*
          psiD21[2][2][0])+(N21[2][2][1]*psiD21[2][2][1])))+((psiD22[2][2][2]*c2
          )+((N22[2][2][0]*psiD22[2][2][0])+(N22[2][2][1]*psiD22[2][2][1]))));
        PH1[1][0] = Pd[1][0][2];
        PH1[1][1] = Pd[1][1][2];
        PH1[1][2] = Pd[1][2][2];
        PH2[1][0] = P22[1][0][2];
        PH2[1][1] = P22[1][1][2];
        PH2[1][2] = P22[1][2][2];
        if (PH2[1][2] < 1e-13) {
            sdseterr(routine,47);
        } else {
            DD[1] = (1./PH2[1][2]);
        }
        G1[1][0] = (DD[1]*PH1[1][0]);
        G1[1][1] = (DD[1]*PH1[1][1]);
        G1[1][2] = (DD[1]*PH1[1][2]);
        G2[1][0] = (DD[1]*PH2[1][0]);
        G2[1][1] = (DD[1]*PH2[1][1]);
        P11[1][0][0] = (P11[1][0][0]-(G1[1][0]*PH1[1][0]));
        P11[1][0][1] = (P11[1][0][1]-(G1[1][1]*PH1[1][0]));
        P11[1][0][2] = (P11[1][0][2]-(G1[1][2]*PH1[1][0]));
        P11[1][1][1] = (P11[1][1][1]-(G1[1][1]*PH1[1][1]));
        P11[1][1][2] = (P11[1][1][2]-(G1[1][2]*PH1[1][1]));
        P11[1][2][2] = (P11[1][2][2]-(G1[1][2]*PH1[1][2]));
        Pd[1][0][0] = (Pd[1][0][0]-(G2[1][0]*PH1[1][0]));
        Pd[1][0][1] = (Pd[1][0][1]-(G2[1][1]*PH1[1][0]));
        Pd[1][0][2] = (Pd[1][0][2]-PH1[1][0]);
        Pd[1][1][0] = (Pd[1][1][0]-(G2[1][0]*PH1[1][1]));
        Pd[1][1][1] = (Pd[1][1][1]-(G2[1][1]*PH1[1][1]));
        Pd[1][1][2] = (Pd[1][1][2]-PH1[1][1]);
        Pd[1][2][0] = (Pd[1][2][0]-(G2[1][0]*PH1[1][2]));
        Pd[1][2][1] = (Pd[1][2][1]-(G2[1][1]*PH1[1][2]));
        Pd[1][2][2] = (Pd[1][2][2]-PH1[1][2]);
        P22[1][0][0] = (P22[1][0][0]-(G2[1][0]*PH2[1][0]));
        P22[1][0][1] = (P22[1][0][1]-(G2[1][1]*PH2[1][0]));
        P22[1][0][2] = (P22[1][0][2]-PH2[1][0]);
        P22[1][1][1] = (P22[1][1][1]-(G2[1][1]*PH2[1][1]));
        P22[1][1][2] = (P22[1][1][2]-PH2[1][1]);
        P22[1][2][2] = (P22[1][2][2]-PH2[1][2]);
        sD1INV[0][0] = 0.;
        if (P11[1][0][0] >= 1e-13) {
            sD1INV[0][0] = (1./P11[1][0][0]);
        }
        sL11[1][0] = (P11[1][0][1]*sD1INV[0][0]);
        sL11[2][0] = (P11[1][0][2]*sD1INV[0][0]);
        sL11D1[1][1] = (P11[1][1][1]-(P11[1][0][1]*sL11[1][0]));
        sL11D1[2][1] = (P11[1][1][2]-(P11[1][0][2]*sL11[1][0]));
        sL11D1[2][2] = (P11[1][2][2]-(P11[1][0][2]*sL11[2][0]));
        sD1INV[1][1] = 0.;
        if (sL11D1[1][1] >= 1e-13) {
            sD1INV[1][1] = (1./sL11D1[1][1]);
        }
        sL11[2][1] = (sD1INV[1][1]*sL11D1[2][1]);
        sL11D1[2][2] = (sL11D1[2][2]-(sL11[2][1]*sL11D1[2][1]));
        sD1INV[2][2] = 0.;
        if (sL11D1[2][2] >= 1e-13) {
            sD1INV[2][2] = (1./sL11D1[2][2]);
        }
        sD1L21[1][0] = (Pd[1][1][0]-(Pd[1][0][0]*sL11[1][0]));
        sD1L21[1][1] = (Pd[1][1][1]-(Pd[1][0][1]*sL11[1][0]));
        sD1L21[1][2] = (Pd[1][1][2]-(Pd[1][0][2]*sL11[1][0]));
        sD1L21[2][0] = (Pd[1][2][0]-((Pd[1][0][0]*sL11[2][0])+(sD1L21[1][0]*
          sL11[2][1])));
        sD1L21[2][1] = (Pd[1][2][1]-((Pd[1][0][1]*sL11[2][0])+(sD1L21[1][1]*
          sL11[2][1])));
        sD1L21[2][2] = (Pd[1][2][2]-((Pd[1][0][2]*sL11[2][0])+(sD1L21[1][2]*
          sL11[2][1])));
        sL21[0][0] = (Pd[1][0][0]*sD1INV[0][0]);
        sL21[0][1] = (sD1INV[1][1]*sD1L21[1][0]);
        sL21[0][2] = (sD1INV[2][2]*sD1L21[2][0]);
        sL21[1][0] = (Pd[1][0][1]*sD1INV[0][0]);
        sL21[1][1] = (sD1INV[1][1]*sD1L21[1][1]);
        sL21[1][2] = (sD1INV[2][2]*sD1L21[2][1]);
        sL21[2][0] = (Pd[1][0][2]*sD1INV[0][0]);
        sL21[2][1] = (sD1INV[1][1]*sD1L21[1][2]);
        sL21[2][2] = (sD1INV[2][2]*sD1L21[2][2]);
        sL22D2[0][0] = (P22[1][0][0]-((sD1L21[2][0]*sL21[0][2])+((Pd[1][0][0]*
          sL21[0][0])+(sD1L21[1][0]*sL21[0][1]))));
        sL22D2[1][0] = (P22[1][0][1]-((sD1L21[2][0]*sL21[1][2])+((Pd[1][0][0]*
          sL21[1][0])+(sD1L21[1][0]*sL21[1][1]))));
        sL22D2[1][1] = (P22[1][1][1]-((sD1L21[2][1]*sL21[1][2])+((Pd[1][0][1]*
          sL21[1][0])+(sD1L21[1][1]*sL21[1][1]))));
        sL22D2[2][0] = (P22[1][0][2]-((sD1L21[2][0]*sL21[2][2])+((Pd[1][0][0]*
          sL21[2][0])+(sD1L21[1][0]*sL21[2][1]))));
        sL22D2[2][1] = (P22[1][1][2]-((sD1L21[2][1]*sL21[2][2])+((Pd[1][0][1]*
          sL21[2][0])+(sD1L21[1][1]*sL21[2][1]))));
        sL22D2[2][2] = (P22[1][2][2]-((sD1L21[2][2]*sL21[2][2])+((Pd[1][0][2]*
          sL21[2][0])+(sD1L21[1][2]*sL21[2][1]))));
        sD2INV[0][0] = 0.;
        if (sL22D2[0][0] >= 1e-13) {
            sD2INV[0][0] = (1./sL22D2[0][0]);
        }
        sL22[1][0] = (sD2INV[0][0]*sL22D2[1][0]);
        sL22[2][0] = (sD2INV[0][0]*sL22D2[2][0]);
        sL22D2[1][1] = (sL22D2[1][1]-(sL22[1][0]*sL22D2[1][0]));
        sL22D2[2][1] = (sL22D2[2][1]-(sL22[1][0]*sL22D2[2][0]));
        sL22D2[2][2] = (sL22D2[2][2]-(sL22[2][0]*sL22D2[2][0]));
        sD2INV[1][1] = 0.;
        if (sL22D2[1][1] >= 1e-13) {
            sD2INV[1][1] = (1./sL22D2[1][1]);
        }
        sL22[2][1] = (sD2INV[1][1]*sL22D2[2][1]);
        sL22D2[2][2] = (sL22D2[2][2]-(sL22[2][1]*sL22D2[2][1]));
        N11[1][0][0] = (c1-(sL11[1][0]*s1));
        N11[1][1][0] = (s1+(sL11[1][0]*c1));
        N21[1][0][0] = ((sL21[0][0]*c1)-(sL21[1][0]*s1));
        N21[1][0][1] = ((sL21[0][1]*c1)-(sL21[1][1]*s1));
        N21[1][0][2] = ((sL21[0][2]*c1)-(sL21[1][2]*s1));
        N21[1][1][0] = ((sL21[0][0]*s1)+(sL21[1][0]*c1));
        N21[1][1][1] = ((sL21[0][1]*s1)+(sL21[1][1]*c1));
        N21[1][1][2] = ((sL21[0][2]*s1)+(sL21[1][2]*c1));
        N22[1][0][0] = (c1-(sL22[1][0]*s1));
        N22[1][1][0] = (s1+(sL22[1][0]*c1));
        psiD11[1][0][0] = (N11[1][0][0]*P11[1][0][0]);
        psiD11[1][0][1] = -(sL11D1[1][1]*s1);
        psiD11[1][1][0] = (N11[1][1][0]*P11[1][0][0]);
        psiD11[1][1][1] = (sL11D1[1][1]*c1);
        psiD11[1][2][0] = (P11[1][0][0]*sL11[2][0]);
        psiD11[1][2][1] = (sL11[2][1]*sL11D1[1][1]);
        psiD21[1][0][0] = (N21[1][0][0]*P11[1][0][0]);
        psiD21[1][0][1] = (N21[1][0][1]*sL11D1[1][1]);
        psiD21[1][0][2] = (N21[1][0][2]*sL11D1[2][2]);
        psiD21[1][1][0] = (N21[1][1][0]*P11[1][0][0]);
        psiD21[1][1][1] = (N21[1][1][1]*sL11D1[1][1]);
        psiD21[1][1][2] = (N21[1][1][2]*sL11D1[2][2]);
        psiD21[1][2][0] = (P11[1][0][0]*sL21[2][0]);
        psiD21[1][2][1] = (sL11D1[1][1]*sL21[2][1]);
        psiD21[1][2][2] = (sL11D1[2][2]*sL21[2][2]);
        psiD22[1][0][0] = (N22[1][0][0]*sL22D2[0][0]);
        psiD22[1][0][1] = -(sL22D2[1][1]*s1);
        psiD22[1][1][0] = (N22[1][1][0]*sL22D2[0][0]);
        psiD22[1][1][1] = (sL22D2[1][1]*c1);
        psiD22[1][2][0] = (sL22[2][0]*sL22D2[0][0]);
        psiD22[1][2][1] = (sL22[2][1]*sL22D2[1][1]);
        P11[0][0][0] = ((N11[1][0][0]*psiD11[1][0][0])-(psiD11[1][0][1]*s1));
        P11[0][0][1] = ((N11[1][1][0]*psiD11[1][0][0])+(psiD11[1][0][1]*c1));
        P11[0][0][2] = ((psiD11[1][0][0]*sL11[2][0])+(psiD11[1][0][1]*sL11[2][1]
          ));
        P11[0][1][0] = P11[0][0][1];
        P11[0][1][1] = ((N11[1][1][0]*psiD11[1][1][0])+(psiD11[1][1][1]*c1));
        P11[0][1][2] = ((psiD11[1][1][0]*sL11[2][0])+(psiD11[1][1][1]*sL11[2][1]
          ));
        P11[0][2][0] = P11[0][0][2];
        P11[0][2][1] = P11[0][1][2];
        P11[0][2][2] = (sL11D1[2][2]+((psiD11[1][2][0]*sL11[2][0])+(
          psiD11[1][2][1]*sL11[2][1])));
        Pd[0][0][0] = ((N21[1][0][0]*psiD11[1][0][0])+(N21[1][0][1]*
          psiD11[1][0][1]));
        Pd[0][0][1] = ((N21[1][1][0]*psiD11[1][0][0])+(N21[1][1][1]*
          psiD11[1][0][1]));
        Pd[0][0][2] = ((psiD11[1][0][0]*sL21[2][0])+(psiD11[1][0][1]*sL21[2][1])
          );
        Pd[0][1][0] = ((N21[1][0][0]*psiD11[1][1][0])+(N21[1][0][1]*
          psiD11[1][1][1]));
        Pd[0][1][1] = ((N21[1][1][0]*psiD11[1][1][0])+(N21[1][1][1]*
          psiD11[1][1][1]));
        Pd[0][1][2] = ((psiD11[1][1][0]*sL21[2][0])+(psiD11[1][1][1]*sL21[2][1])
          );
        Pd[0][2][0] = ((N21[1][0][2]*sL11D1[2][2])+((N21[1][0][0]*
          psiD11[1][2][0])+(N21[1][0][1]*psiD11[1][2][1])));
        Pd[0][2][1] = ((N21[1][1][2]*sL11D1[2][2])+((N21[1][1][0]*
          psiD11[1][2][0])+(N21[1][1][1]*psiD11[1][2][1])));
        Pd[0][2][2] = ((sL11D1[2][2]*sL21[2][2])+((psiD11[1][2][0]*sL21[2][0])+(
          psiD11[1][2][1]*sL21[2][1])));
        P22[0][0][0] = (((N21[1][0][2]*psiD21[1][0][2])+((N21[1][0][0]*
          psiD21[1][0][0])+(N21[1][0][1]*psiD21[1][0][1])))+((N22[1][0][0]*
          psiD22[1][0][0])-(psiD22[1][0][1]*s1)));
        P22[0][0][1] = (((N21[1][1][2]*psiD21[1][0][2])+((N21[1][1][0]*
          psiD21[1][0][0])+(N21[1][1][1]*psiD21[1][0][1])))+((N22[1][1][0]*
          psiD22[1][0][0])+(psiD22[1][0][1]*c1)));
        P22[0][0][2] = (((psiD21[1][0][2]*sL21[2][2])+((psiD21[1][0][0]*
          sL21[2][0])+(psiD21[1][0][1]*sL21[2][1])))+((psiD22[1][0][0]*
          sL22[2][0])+(psiD22[1][0][1]*sL22[2][1])));
        P22[0][1][0] = P22[0][0][1];
        P22[0][1][1] = (((N21[1][1][2]*psiD21[1][1][2])+((N21[1][1][0]*
          psiD21[1][1][0])+(N21[1][1][1]*psiD21[1][1][1])))+((N22[1][1][0]*
          psiD22[1][1][0])+(psiD22[1][1][1]*c1)));
        P22[0][1][2] = (((psiD21[1][1][2]*sL21[2][2])+((psiD21[1][1][0]*
          sL21[2][0])+(psiD21[1][1][1]*sL21[2][1])))+((psiD22[1][1][0]*
          sL22[2][0])+(psiD22[1][1][1]*sL22[2][1])));
        P22[0][2][0] = P22[0][0][2];
        P22[0][2][1] = P22[0][1][2];
        P22[0][2][2] = ((sL22D2[2][2]+((psiD22[1][2][0]*sL22[2][0])+(
          psiD22[1][2][1]*sL22[2][1])))+((psiD21[1][2][2]*sL21[2][2])+((
          psiD21[1][2][0]*sL21[2][0])+(psiD21[1][2][1]*sL21[2][1]))));
        PH1[0][0] = Pd[0][0][1];
        PH1[0][1] = Pd[0][1][1];
        PH1[0][2] = Pd[0][2][1];
        PH2[0][0] = P22[0][0][1];
        PH2[0][1] = P22[0][1][1];
        PH2[0][2] = P22[0][2][1];
        if (PH2[0][1] < 1e-13) {
            sdseterr(routine,47);
        } else {
            DD[0] = (1./PH2[0][1]);
        }
        sderror(&dumroutine,&errnum);
        if (errnum == 0) {
            mmflg = 1;
        }
    }
/*
 Used 0.02 seconds CPU time,
 0 additional bytes of memory.
 Equations contain  551 adds/subtracts/negates
                    815 multiplies
                     19 divides
                    489 assignments
*/
}

void sdlhs(int routine)
{
/* Compute all remaining state- and force-dependent quantities
*/

    roustate = 2;
    sddomm(routine);
    sddofs0();
}

void sdmfrc(double imult[1])
{

}

void sdequivht(double tau[5])
{
/* Compute tree hinge torques to match effect of applied loads
*/
    double fstareq[5][3],tstareq[5][3];

    if ((roustate != 2) && (roustate != 3)) {
        sdseterr(56,23);
        return;
    }
/*
Compute fstareq (forces)
*/
    fstareq[2][0] = -(ufk[9][0]+(2.0519*gk[2][0]));
    fstareq[2][1] = ((20.122265135*c1)-ufk[9][1]);
    fstareq[2][2] = -(ufk[9][2]+(2.0519*gk[2][2]));
    fstareq[3][0] = -(ufk[10][0]+(.5464*gk[3][0]));
    fstareq[3][1] = -(ufk[10][1]+(.5464*gk[3][1]));
    fstareq[3][2] = -(ufk[10][2]+(.5464*gk[3][2]));
    fstareq[4][0] = -(ufk[11][0]+(.5464*gk[4][0]));
    fstareq[4][1] = -(ufk[11][1]+(.5464*gk[4][1]));
    fstareq[4][2] = -(ufk[11][2]+(.5464*gk[4][2]));
/*
Compute tstareq (torques)
*/
/*
Compute taus (RHS ignoring constraints and inertial forces)
*/
    tau[4] = (utau[4]-(((.0030324545364801*fstareq[4][2])+((.000614949586952047*
      fstareq[4][1])+(.010530303756815*fstareq[4][0])))+(((.113294979100377*
      utk[11][0])-(.974058820703242*utk[11][1]))-(.195891963900652*utk[11][2])))
      );
    Fstark[3][0] = (fstareq[3][0]+((Cik[4][0][2]*fstareq[4][2])+((Cik[4][0][0]*
      fstareq[4][0])+(Cik[4][0][1]*fstareq[4][1]))));
    Fstark[3][1] = (fstareq[3][1]+((Cik[4][1][2]*fstareq[4][2])+((Cik[4][1][0]*
      fstareq[4][0])+(Cik[4][1][1]*fstareq[4][1]))));
    Fstark[3][2] = (fstareq[3][2]+((Cik[4][2][2]*fstareq[4][2])+((Cik[4][2][0]*
      fstareq[4][0])+(Cik[4][2][1]*fstareq[4][1]))));
    tvec1[0] = (((fstareq[4][2]*rik[4][1])-(fstareq[4][1]*rik[4][2]))-utk[11][0]
      );
    tvec1[1] = (((fstareq[4][0]*rik[4][2])-(fstareq[4][2]*rik[4][0]))-utk[11][1]
      );
    tvec1[2] = (((fstareq[4][1]*rik[4][0])-(fstareq[4][0]*rik[4][1]))-utk[11][2]
      );
    Tstark[3][0] = (((Cik[4][0][2]*tvec1[2])+((Cik[4][0][0]*tvec1[0])+(
      Cik[4][0][1]*tvec1[1])))-utk[10][0]);
    Tstark[3][1] = (((Cik[4][1][2]*tvec1[2])+((Cik[4][1][0]*tvec1[0])+(
      Cik[4][1][1]*tvec1[1])))-utk[10][1]);
    Tstark[3][2] = (((Cik[4][2][2]*tvec1[2])+((Cik[4][2][0]*tvec1[0])+(
      Cik[4][2][1]*tvec1[1])))-utk[10][2]);
    tau[3] = (utau[3]-((((.00390506057260274*Fstark[3][1])-(.00129517015605427*
      Fstark[3][0]))-(.0633826382708198*Fstark[3][2]))+(((.00844600099996266*
      Tstark[3][1])+(.99976612099558*Tstark[3][0]))-(.019909002399912*
      Tstark[3][2]))));
    Fstark[2][0] = (fstareq[2][0]+((Cik[3][0][2]*Fstark[3][2])+((Cik[3][0][0]*
      Fstark[3][0])+(Cik[3][0][1]*Fstark[3][1]))));
    Fstark[2][1] = (fstareq[2][1]+((Cik[3][1][2]*Fstark[3][2])+((Cik[3][1][0]*
      Fstark[3][0])+(Cik[3][1][1]*Fstark[3][1]))));
    Fstark[2][2] = (fstareq[2][2]+((Cik[3][2][2]*Fstark[3][2])+((Cik[3][2][0]*
      Fstark[3][0])+(Cik[3][2][1]*Fstark[3][1]))));
    tvec1[0] = (Tstark[3][0]+((Fstark[3][2]*rik[3][1])-(Fstark[3][1]*rik[3][2]))
      );
    tvec1[1] = (Tstark[3][1]+((Fstark[3][0]*rik[3][2])-(Fstark[3][2]*rik[3][0]))
      );
    tvec1[2] = (Tstark[3][2]+((Fstark[3][1]*rik[3][0])-(Fstark[3][0]*rik[3][1]))
      );
    Tstark[2][0] = (((Cik[3][0][2]*tvec1[2])+((Cik[3][0][0]*tvec1[0])+(
      Cik[3][0][1]*tvec1[1])))-utk[9][0]);
    Tstark[2][1] = (((Cik[3][1][2]*tvec1[2])+((Cik[3][1][0]*tvec1[0])+(
      Cik[3][1][1]*tvec1[1])))-utk[9][1]);
    Tstark[2][2] = (((Cik[3][2][2]*tvec1[2])+((Cik[3][2][0]*tvec1[0])+(
      Cik[3][2][1]*tvec1[1])))-utk[9][2]);
    tau[2] = (utau[2]-(Tstark[2][1]-((.0036*Fstark[2][0])+(.0064*Fstark[2][2])))
      );
    Fstark[1][0] = (((Fstark[2][0]*c2)+(Fstark[2][2]*s2))-ufk[8][0]);
    Fstark[1][1] = (Fstark[2][1]-ufk[8][1]);
    Fstark[1][2] = (((Fstark[2][2]*c2)-(Fstark[2][0]*s2))-ufk[8][2]);
    tvec1[0] = (Tstark[2][0]+((.0036*Fstark[2][1])-(.0776*Fstark[2][2])));
    tvec1[1] = (Tstark[2][1]-((.0036*Fstark[2][0])+(.0064*Fstark[2][2])));
    tvec1[2] = (Tstark[2][2]+((.0064*Fstark[2][1])+(.0776*Fstark[2][0])));
    Tstark[1][0] = (((tvec1[0]*c2)+(tvec1[2]*s2))-utk[8][0]);
    Tstark[1][1] = (tvec1[1]-utk[8][1]);
    Tstark[1][2] = (((tvec1[2]*c2)-(tvec1[0]*s2))-utk[8][2]);
    tau[1] = (utau[1]-Tstark[1][2]);
    Fstark[0][0] = (((Fstark[1][0]*c1)-(Fstark[1][1]*s1))-ufk[7][0]);
    Fstark[0][1] = (((Fstark[1][0]*s1)+(Fstark[1][1]*c1))-ufk[7][1]);
    Fstark[0][2] = (Fstark[1][2]-ufk[7][2]);
    Tstark[0][0] = (((Tstark[1][0]*c1)-(Tstark[1][1]*s1))-utk[7][0]);
    Tstark[0][1] = (((Tstark[1][0]*s1)+(Tstark[1][1]*c1))-utk[7][1]);
    Tstark[0][2] = (Tstark[1][2]-utk[7][2]);
    tau[0] = (utau[0]-Tstark[0][1]);
/*
Op counts below do not include called subroutines
*/
/*
 Used 0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain  108 adds/subtracts/negates
                     93 multiplies
                      0 divides
                     47 assignments
*/
}

void sdfs0(void)
{

/*
Compute Fs (ignoring multiplier forces)
*/
    fs[0] = fs0[0];
    fs[1] = fs0[1];
    fs[2] = fs0[2];
    fs[3] = fs0[3];
    fs[4] = fs0[4];
/*
 Used 0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain    0 adds/subtracts/negates
                      0 multiplies
                      0 divides
                      5 assignments
*/
}

void sdfsmult(void)
{
    int i;

/*
Compute Fs (multiplier-generated forces only)
*/
    for (i = 0; i < 5; i++) {
        fs[i] = 0.;
    }
/*
 Used 0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain    0 adds/subtracts/negates
                      0 multiplies
                      0 divides
                      5 assignments
*/
}

void sdfsfull(void)
{

/*
Compute Fs (including all forces)
*/
    sdfsmult();
    fs[0] = (fs[0]+fs0[0]);
    fs[1] = (fs[1]+fs0[1]);
    fs[2] = (fs[2]+fs0[2]);
    fs[3] = (fs[3]+fs0[3]);
    fs[4] = (fs[4]+fs0[4]);
/*
 Used 0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain    5 adds/subtracts/negates
                      0 multiplies
                      0 divides
                      5 assignments
*/
}

void sdfsgenmult(void)
{
    int i;

/*
Compute Fs (generic multiplier-generated forces)
*/
    for (i = 0; i < 5; i++) {
        fs[i] = 0.;
    }
/*
 Used 0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain    0 adds/subtracts/negates
                      0 multiplies
                      0 divides
                      5 assignments
*/
}

void sdfsgenfull(void)
{

/*
Compute Fs (incl generic mult & other forces)
*/
    sdfsgenmult();
    fs[0] = (fs[0]+fs0[0]);
    fs[1] = (fs[1]+fs0[1]);
    fs[2] = (fs[2]+fs0[2]);
    fs[3] = (fs[3]+fs0[3]);
    fs[4] = (fs[4]+fs0[4]);
/*
 Used 0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain    5 adds/subtracts/negates
                      0 multiplies
                      0 divides
                      5 assignments
*/
}

void sdfulltrq(double udotin[5],
    double multin[1],
    double trqout[5])
{
/* Compute hinge torques which would produce indicated udots
*/
    double fstarr[5][3],tstarr[5][3],Otkr[5][3],Atir[5][3],Atkr[5][3];

    if ((roustate != 2) && (roustate != 3)) {
        sdseterr(61,23);
        return;
    }
/*
Account for inertial accelerations and supplied udots
*/
    Otkr[1][0] = ((u[1]*wk[1][1])+(udotin[0]*s1));
    Otkr[1][1] = ((udotin[0]*c1)-(u[1]*wk[1][0]));
    Otkr[2][0] = (((Otkr[1][0]*c2)-(udotin[1]*s2))-(u[2]*wk[2][2]));
    Otkr[2][1] = (Otkr[1][1]+udotin[2]);
    Otkr[2][2] = ((u[2]*wk[2][0])+((Otkr[1][0]*s2)+(udotin[1]*c2)));
    Otkr[3][0] = (((.99976612099558*udotin[3])-((.00844600099996266*(u[3]*
      wk[3][2]))+(.019909002399912*(u[3]*wk[3][1]))))+((Cik[3][2][0]*Otkr[2][2])
      +((Cik[3][0][0]*Otkr[2][0])+(Cik[3][1][0]*Otkr[2][1]))));
    Otkr[3][1] = (((.00844600099996266*udotin[3])+((.019909002399912*(u[3]*
      wk[3][0]))+(.99976612099558*(u[3]*wk[3][2]))))+((Cik[3][2][1]*Otkr[2][2])+
      ((Cik[3][0][1]*Otkr[2][0])+(Cik[3][1][1]*Otkr[2][1]))));
    Otkr[3][2] = (((Cik[3][2][2]*Otkr[2][2])+((Cik[3][0][2]*Otkr[2][0])+(
      Cik[3][1][2]*Otkr[2][1])))+(((.00844600099996266*(u[3]*wk[3][0]))-(
      .99976612099558*(u[3]*wk[3][1])))-(.019909002399912*udotin[3])));
    Otkr[4][0] = (((Cik[4][2][0]*Otkr[3][2])+((Cik[4][0][0]*Otkr[3][0])+(
      Cik[4][1][0]*Otkr[3][1])))+(((.195891963900652*(u[4]*wk[4][1]))-(
      .974058820703242*(u[4]*wk[4][2])))-(.113294979100377*udotin[4])));
    Otkr[4][1] = (((.974058820703242*udotin[4])-((.113294979100377*(u[4]*
      wk[4][2]))+(.195891963900652*(u[4]*wk[4][0]))))+((Cik[4][2][1]*Otkr[3][2])
      +((Cik[4][0][1]*Otkr[3][0])+(Cik[4][1][1]*Otkr[3][1]))));
    Otkr[4][2] = (((.195891963900652*udotin[4])+((.113294979100377*(u[4]*
      wk[4][1]))+(.974058820703242*(u[4]*wk[4][0]))))+((Cik[4][2][2]*Otkr[3][2])
      +((Cik[4][0][2]*Otkr[3][0])+(Cik[4][1][2]*Otkr[3][1]))));
    Atkr[2][0] = (((.0776*Otkr[2][2])-(.0036*Otkr[2][1]))+((wk[2][1]*Wkrpk[2][2]
      )-(wk[2][2]*Wkrpk[2][1])));
    Atkr[2][1] = (((.0036*Otkr[2][0])+(.0064*Otkr[2][2]))+((wk[2][2]*Wkrpk[2][0]
      )-(wk[2][0]*Wkrpk[2][2])));
    Atkr[2][2] = (((wk[2][0]*Wkrpk[2][1])-(wk[2][1]*Wkrpk[2][0]))-((.0064*
      Otkr[2][1])+(.0776*Otkr[2][0])));
    Atir[3][0] = (Atkr[2][0]+(((.0085*Otkr[2][1])+(.2131*Otkr[2][2]))+((
      Wirk[3][2]*wk[2][1])-(Wirk[3][1]*wk[2][2]))));
    Atir[3][1] = (Atkr[2][1]+(((Wirk[3][0]*wk[2][2])-(Wirk[3][2]*wk[2][0]))-((
      .0006*Otkr[2][2])+(.0085*Otkr[2][0]))));
    Atir[3][2] = (Atkr[2][2]+(((.0006*Otkr[2][1])-(.2131*Otkr[2][0]))+((
      Wirk[3][1]*wk[2][0])-(Wirk[3][0]*wk[2][1]))));
    Atkr[3][0] = (((Atir[3][2]*Cik[3][2][0])+((Atir[3][0]*Cik[3][0][0])+(
      Atir[3][1]*Cik[3][1][0])))+(((.0634*Otkr[3][2])-(.0039*Otkr[3][1]))+((
      wk[3][1]*Wkrpk[3][2])-(wk[3][2]*Wkrpk[3][1]))));
    Atkr[3][1] = (((Atir[3][2]*Cik[3][2][1])+((Atir[3][0]*Cik[3][0][1])+(
      Atir[3][1]*Cik[3][1][1])))+(((.0039*Otkr[3][0])-(.0003*Otkr[3][2]))+((
      wk[3][2]*Wkrpk[3][0])-(wk[3][0]*Wkrpk[3][2]))));
    Atkr[3][2] = (((Atir[3][2]*Cik[3][2][2])+((Atir[3][0]*Cik[3][0][2])+(
      Atir[3][1]*Cik[3][1][2])))+(((.0003*Otkr[3][1])-(.0634*Otkr[3][0]))+((
      wk[3][0]*Wkrpk[3][1])-(wk[3][1]*Wkrpk[3][0]))));
    Atir[4][0] = (Atkr[3][0]+(((Wirk[4][2]*wk[3][1])-(Wirk[4][1]*wk[3][2]))-((
      .0124*Otkr[3][1])+(.0501*Otkr[3][2]))));
    Atir[4][1] = (Atkr[3][1]+(((.0124*Otkr[3][0])+(.0174*Otkr[3][2]))+((
      Wirk[4][0]*wk[3][2])-(Wirk[4][2]*wk[3][0]))));
    Atir[4][2] = (Atkr[3][2]+(((.0501*Otkr[3][0])-(.0174*Otkr[3][1]))+((
      Wirk[4][1]*wk[3][0])-(Wirk[4][0]*wk[3][1]))));
    Atkr[4][0] = (((Atir[4][2]*Cik[4][2][0])+((Atir[4][0]*Cik[4][0][0])+(
      Atir[4][1]*Cik[4][1][0])))+(((.1179*Otkr[4][2])-(.0129*Otkr[4][1]))+((
      wk[4][1]*Wkrpk[4][2])-(wk[4][2]*Wkrpk[4][1]))));
    Atkr[4][1] = (((Atir[4][2]*Cik[4][2][1])+((Atir[4][0]*Cik[4][0][1])+(
      Atir[4][1]*Cik[4][1][1])))+(((.0106*Otkr[4][2])+(.0129*Otkr[4][0]))+((
      wk[4][2]*Wkrpk[4][0])-(wk[4][0]*Wkrpk[4][2]))));
    Atkr[4][2] = (((Atir[4][2]*Cik[4][2][2])+((Atir[4][0]*Cik[4][0][2])+(
      Atir[4][1]*Cik[4][1][2])))+(((wk[4][0]*Wkrpk[4][1])-(wk[4][1]*Wkrpk[4][0])
      )-((.0106*Otkr[4][1])+(.1179*Otkr[4][0]))));
/*
Accumulate all forces and torques
*/
    fstarr[2][0] = (ufk[9][0]+(2.0519*(gk[2][0]-Atkr[2][0])));
    fstarr[2][1] = (ufk[9][1]-(2.0519*(Atkr[2][1]+(9.80665*c1))));
    fstarr[2][2] = (ufk[9][2]+(2.0519*(gk[2][2]-Atkr[2][2])));
    fstarr[3][0] = (ufk[10][0]+(.5464*(gk[3][0]-Atkr[3][0])));
    fstarr[3][1] = (ufk[10][1]+(.5464*(gk[3][1]-Atkr[3][1])));
    fstarr[3][2] = (ufk[10][2]+(.5464*(gk[3][2]-Atkr[3][2])));
    fstarr[4][0] = (ufk[11][0]+(.5464*(gk[4][0]-Atkr[4][0])));
    fstarr[4][1] = (ufk[11][1]+(.5464*(gk[4][1]-Atkr[4][1])));
    fstarr[4][2] = (ufk[11][2]+(.5464*(gk[4][2]-Atkr[4][2])));
    tstarr[2][0] = (utk[9][0]-(WkIkWk[2][0]+(.0132*Otkr[2][0])));
    tstarr[2][1] = (utk[9][1]-(.001988*Otkr[2][1]));
    tstarr[2][2] = (utk[9][2]-(WkIkWk[2][2]+(.0132*Otkr[2][2])));
    tstarr[3][0] = (utk[10][0]-(WkIkWk[3][0]+(.0030585*Otkr[3][0])));
    tstarr[3][1] = (utk[10][1]-(.00045325*Otkr[3][1]));
    tstarr[3][2] = (utk[10][2]-(WkIkWk[3][2]+(.0030585*Otkr[3][2])));
    tstarr[4][0] = (utk[11][0]-(WkIkWk[4][0]+(.0030585*Otkr[4][0])));
    tstarr[4][1] = (utk[11][1]-(.00045325*Otkr[4][1]));
    tstarr[4][2] = (utk[11][2]-(WkIkWk[4][2]+(.0030585*Otkr[4][2])));
/*
Now calculate the torques
*/
    trqout[4] = -(utau[4]+(((.0030324545364801*fstarr[4][2])+((
      .000614949586952047*fstarr[4][1])+(.010530303756815*fstarr[4][0])))+((
      .195891963900652*tstarr[4][2])+((.974058820703242*tstarr[4][1])-(
      .113294979100377*tstarr[4][0])))));
    Fstark[3][0] = (fstarr[3][0]+((Cik[4][0][2]*fstarr[4][2])+((Cik[4][0][0]*
      fstarr[4][0])+(Cik[4][0][1]*fstarr[4][1]))));
    Fstark[3][1] = (fstarr[3][1]+((Cik[4][1][2]*fstarr[4][2])+((Cik[4][1][0]*
      fstarr[4][0])+(Cik[4][1][1]*fstarr[4][1]))));
    Fstark[3][2] = (fstarr[3][2]+((Cik[4][2][2]*fstarr[4][2])+((Cik[4][2][0]*
      fstarr[4][0])+(Cik[4][2][1]*fstarr[4][1]))));
    tvec1[0] = (tstarr[4][0]+((fstarr[4][2]*rik[4][1])-(fstarr[4][1]*rik[4][2]))
      );
    tvec1[1] = (tstarr[4][1]+((fstarr[4][0]*rik[4][2])-(fstarr[4][2]*rik[4][0]))
      );
    tvec1[2] = (tstarr[4][2]+((fstarr[4][1]*rik[4][0])-(fstarr[4][0]*rik[4][1]))
      );
    Tstark[3][0] = (tstarr[3][0]+((Cik[4][0][2]*tvec1[2])+((Cik[4][0][0]*
      tvec1[0])+(Cik[4][0][1]*tvec1[1]))));
    Tstark[3][1] = (tstarr[3][1]+((Cik[4][1][2]*tvec1[2])+((Cik[4][1][0]*
      tvec1[0])+(Cik[4][1][1]*tvec1[1]))));
    Tstark[3][2] = (tstarr[3][2]+((Cik[4][2][2]*tvec1[2])+((Cik[4][2][0]*
      tvec1[0])+(Cik[4][2][1]*tvec1[1]))));
    trqout[3] = -(utau[3]+((((.00390506057260274*Fstark[3][1])-(
      .00129517015605427*Fstark[3][0]))-(.0633826382708198*Fstark[3][2]))+(((
      .00844600099996266*Tstark[3][1])+(.99976612099558*Tstark[3][0]))-(
      .019909002399912*Tstark[3][2]))));
    Fstark[2][0] = (fstarr[2][0]+((Cik[3][0][2]*Fstark[3][2])+((Cik[3][0][0]*
      Fstark[3][0])+(Cik[3][0][1]*Fstark[3][1]))));
    Fstark[2][1] = (fstarr[2][1]+((Cik[3][1][2]*Fstark[3][2])+((Cik[3][1][0]*
      Fstark[3][0])+(Cik[3][1][1]*Fstark[3][1]))));
    Fstark[2][2] = (fstarr[2][2]+((Cik[3][2][2]*Fstark[3][2])+((Cik[3][2][0]*
      Fstark[3][0])+(Cik[3][2][1]*Fstark[3][1]))));
    tvec1[0] = (Tstark[3][0]+((Fstark[3][2]*rik[3][1])-(Fstark[3][1]*rik[3][2]))
      );
    tvec1[1] = (Tstark[3][1]+((Fstark[3][0]*rik[3][2])-(Fstark[3][2]*rik[3][0]))
      );
    tvec1[2] = (Tstark[3][2]+((Fstark[3][1]*rik[3][0])-(Fstark[3][0]*rik[3][1]))
      );
    Tstark[2][0] = (tstarr[2][0]+((Cik[3][0][2]*tvec1[2])+((Cik[3][0][0]*
      tvec1[0])+(Cik[3][0][1]*tvec1[1]))));
    Tstark[2][1] = (tstarr[2][1]+((Cik[3][1][2]*tvec1[2])+((Cik[3][1][0]*
      tvec1[0])+(Cik[3][1][1]*tvec1[1]))));
    Tstark[2][2] = (tstarr[2][2]+((Cik[3][2][2]*tvec1[2])+((Cik[3][2][0]*
      tvec1[0])+(Cik[3][2][1]*tvec1[1]))));
    trqout[2] = -(utau[2]+(Tstark[2][1]-((.0036*Fstark[2][0])+(.0064*
      Fstark[2][2]))));
    Fstark[1][0] = (ufk[8][0]+((Fstark[2][0]*c2)+(Fstark[2][2]*s2)));
    Fstark[1][1] = (Fstark[2][1]+ufk[8][1]);
    Fstark[1][2] = (ufk[8][2]+((Fstark[2][2]*c2)-(Fstark[2][0]*s2)));
    tvec1[0] = (Tstark[2][0]+((.0036*Fstark[2][1])-(.0776*Fstark[2][2])));
    tvec1[1] = (Tstark[2][1]-((.0036*Fstark[2][0])+(.0064*Fstark[2][2])));
    tvec1[2] = (Tstark[2][2]+((.0064*Fstark[2][1])+(.0776*Fstark[2][0])));
    Tstark[1][0] = (utk[8][0]+((tvec1[0]*c2)+(tvec1[2]*s2)));
    Tstark[1][1] = (tvec1[1]+utk[8][1]);
    Tstark[1][2] = (utk[8][2]+((tvec1[2]*c2)-(tvec1[0]*s2)));
    trqout[1] = -(Tstark[1][2]+utau[1]);
    Fstark[0][0] = (ufk[7][0]+((Fstark[1][0]*c1)-(Fstark[1][1]*s1)));
    Fstark[0][1] = (ufk[7][1]+((Fstark[1][0]*s1)+(Fstark[1][1]*c1)));
    Fstark[0][2] = (Fstark[1][2]+ufk[7][2]);
    Tstark[0][0] = (utk[7][0]+((Tstark[1][0]*c1)-(Tstark[1][1]*s1)));
    Tstark[0][1] = (utk[7][1]+((Tstark[1][0]*s1)+(Tstark[1][1]*c1)));
    Tstark[0][2] = (Tstark[1][2]+utk[7][2]);
    trqout[0] = -(Tstark[0][1]+utau[0]);
/*
Op counts below do not include called subroutines
*/
/*
 Used 0.02 seconds CPU time,
 0 additional bytes of memory.
 Equations contain  235 adds/subtracts/negates
                    239 multiplies
                      0 divides
                     82 assignments
*/
}

void sdcomptrq(double udotin[5],
    double trqout[5])
{
/* Compute hinge torques to produce these udots, ignoring constraints
*/
    double multin[1];

    if ((roustate != 2) && (roustate != 3)) {
        sdseterr(60,23);
        return;
    }
    sdfulltrq(udotin,multin,trqout);
}

void sdmulttrq(double multin[1],
    double trqout[5])
{
/* Compute hinge trqs which would be produced by these mults.
*/
    int i;

    if ((roustate != 2) && (roustate != 3)) {
        sdseterr(65,23);
        return;
    }
    for (i = 0; i < 5; i++) {
        trqout[i] = 0.;
    }
}

void sdrhs(void)
{
/*
Generated 14-Nov-2007 16:57:48 by SD/FAST, Order(N) formulation
(sdfast B.2.8 #30123) on machine ID unknown
Copyright (c) 1990-1997 Symbolic Dynamics, Inc.
Copyright (c) 1990-1997 Parametric Technology Corp.
RESTRICTED RIGHTS LEGEND: Use, duplication, or disclosure by the U.S.
Government is subject to restrictions as set forth in subparagraph
(c)(1)(ii) of the Rights in Technical Data and Computer Software
clause at DFARS 52.227-7013 and similar clauses in the FAR and NASA
FAR Supplement.  Symbolic Dynamics, Inc., Mountain View, CA 94041
*/

/*
Compute hinge torques for tree hinges
*/
    tauc[0] = utau[0];
    tauc[1] = utau[1];
    tauc[2] = utau[2];
    tauc[3] = utau[3];
    tauc[4] = utau[4];
    sddoiner();
/*
Compute onk & onb (angular accels in N)
*/
    Onkb[1][0] = (udot[0]*s1);
    Onkb[1][1] = (udot[0]*c1);
    Onkb[2][0] = ((Onkb[1][0]*c2)-(udot[1]*s2));
    Onkb[2][1] = (Onkb[1][1]+udot[2]);
    Onkb[2][2] = ((Onkb[1][0]*s2)+(udot[1]*c2));
    Onkb[3][0] = ((.99976612099558*udot[3])+((Cik[3][2][0]*Onkb[2][2])+((
      Cik[3][0][0]*Onkb[2][0])+(Cik[3][1][0]*Onkb[2][1]))));
    Onkb[3][1] = ((.00844600099996266*udot[3])+((Cik[3][2][1]*Onkb[2][2])+((
      Cik[3][0][1]*Onkb[2][0])+(Cik[3][1][1]*Onkb[2][1]))));
    Onkb[3][2] = (((Cik[3][2][2]*Onkb[2][2])+((Cik[3][0][2]*Onkb[2][0])+(
      Cik[3][1][2]*Onkb[2][1])))-(.019909002399912*udot[3]));
    Onkb[4][0] = (((Cik[4][2][0]*Onkb[3][2])+((Cik[4][0][0]*Onkb[3][0])+(
      Cik[4][1][0]*Onkb[3][1])))-(.113294979100377*udot[4]));
    Onkb[4][1] = ((.974058820703242*udot[4])+((Cik[4][2][1]*Onkb[3][2])+((
      Cik[4][0][1]*Onkb[3][0])+(Cik[4][1][1]*Onkb[3][1]))));
    Onkb[4][2] = ((.195891963900652*udot[4])+((Cik[4][2][2]*Onkb[3][2])+((
      Cik[4][0][2]*Onkb[3][0])+(Cik[4][1][2]*Onkb[3][1]))));
    onk[1][0] = (Onkb[1][0]+Otk[1][0]);
    onk[1][1] = (Onkb[1][1]+Otk[1][1]);
    onk[2][0] = (Onkb[2][0]+Otk[2][0]);
    onk[2][1] = (Onkb[2][1]+Otk[1][1]);
    onk[2][2] = (Onkb[2][2]+Otk[2][2]);
    onk[3][0] = (Onkb[3][0]+Otk[3][0]);
    onk[3][1] = (Onkb[3][1]+Otk[3][1]);
    onk[3][2] = (Onkb[3][2]+Otk[3][2]);
    onk[4][0] = (Onkb[4][0]+Otk[4][0]);
    onk[4][1] = (Onkb[4][1]+Otk[4][1]);
    onk[4][2] = (Onkb[4][2]+Otk[4][2]);
    onb[0][0] = 0.;
    onb[0][1] = 0.;
    onb[0][2] = 0.;
    onb[1][0] = 0.;
    onb[1][1] = 0.;
    onb[1][2] = 0.;
    onb[2][0] = 0.;
    onb[2][1] = 0.;
    onb[2][2] = 0.;
    onb[3][0] = 0.;
    onb[3][1] = 0.;
    onb[3][2] = 0.;
    onb[4][0] = 0.;
    onb[4][1] = 0.;
    onb[4][2] = 0.;
    onb[5][0] = 0.;
    onb[5][1] = 0.;
    onb[5][2] = 0.;
    onb[6][0] = 0.;
    onb[6][1] = 0.;
    onb[6][2] = 0.;
    onb[7][0] = 0.;
    onb[7][1] = udot[0];
    onb[7][2] = 0.;
    onb[8][0] = onk[1][0];
    onb[8][1] = onk[1][1];
    onb[8][2] = udot[1];
    onb[9][0] = onk[2][0];
    onb[9][1] = onk[2][1];
    onb[9][2] = onk[2][2];
    onb[10][0] = onk[3][0];
    onb[10][1] = onk[3][1];
    onb[10][2] = onk[3][2];
    onb[11][0] = onk[4][0];
    onb[11][1] = onk[4][1];
    onb[11][2] = onk[4][2];
/*
Compute acceleration dyadics
*/
    dyad[0][0][0] = 0.;
    dyad[0][0][1] = 0.;
    dyad[0][0][2] = 0.;
    dyad[0][1][0] = 0.;
    dyad[0][1][1] = 0.;
    dyad[0][1][2] = 0.;
    dyad[0][2][0] = 0.;
    dyad[0][2][1] = 0.;
    dyad[0][2][2] = 0.;
    dyad[1][0][0] = 0.;
    dyad[1][0][1] = 0.;
    dyad[1][0][2] = 0.;
    dyad[1][1][0] = 0.;
    dyad[1][1][1] = 0.;
    dyad[1][1][2] = 0.;
    dyad[1][2][0] = 0.;
    dyad[1][2][1] = 0.;
    dyad[1][2][2] = 0.;
    dyad[2][0][0] = 0.;
    dyad[2][0][1] = 0.;
    dyad[2][0][2] = 0.;
    dyad[2][1][0] = 0.;
    dyad[2][1][1] = 0.;
    dyad[2][1][2] = 0.;
    dyad[2][2][0] = 0.;
    dyad[2][2][1] = 0.;
    dyad[2][2][2] = 0.;
    dyad[3][0][0] = 0.;
    dyad[3][0][1] = 0.;
    dyad[3][0][2] = 0.;
    dyad[3][1][0] = 0.;
    dyad[3][1][1] = 0.;
    dyad[3][1][2] = 0.;
    dyad[3][2][0] = 0.;
    dyad[3][2][1] = 0.;
    dyad[3][2][2] = 0.;
    dyad[4][0][0] = 0.;
    dyad[4][0][1] = 0.;
    dyad[4][0][2] = 0.;
    dyad[4][1][0] = 0.;
    dyad[4][1][1] = 0.;
    dyad[4][1][2] = 0.;
    dyad[4][2][0] = 0.;
    dyad[4][2][1] = 0.;
    dyad[4][2][2] = 0.;
    dyad[5][0][0] = 0.;
    dyad[5][0][1] = 0.;
    dyad[5][0][2] = 0.;
    dyad[5][1][0] = 0.;
    dyad[5][1][1] = 0.;
    dyad[5][1][2] = 0.;
    dyad[5][2][0] = 0.;
    dyad[5][2][1] = 0.;
    dyad[5][2][2] = 0.;
    dyad[6][0][0] = 0.;
    dyad[6][0][1] = 0.;
    dyad[6][0][2] = 0.;
    dyad[6][1][0] = 0.;
    dyad[6][1][1] = 0.;
    dyad[6][1][2] = 0.;
    dyad[6][2][0] = 0.;
    dyad[6][2][1] = 0.;
    dyad[6][2][2] = 0.;
    dyad[7][0][0] = -w1w1[7];
    dyad[7][0][1] = 0.;
    dyad[7][0][2] = udot[0];
    dyad[7][1][0] = 0.;
    dyad[7][1][1] = 0.;
    dyad[7][1][2] = 0.;
    dyad[7][2][0] = -udot[0];
    dyad[7][2][1] = 0.;
    dyad[7][2][2] = -w1w1[7];
    dyad[8][0][0] = w11w22[8];
    dyad[8][0][1] = (w0w1[8]-udot[1]);
    dyad[8][0][2] = (onk[1][1]+w0w2[8]);
    dyad[8][1][0] = (udot[1]+w0w1[8]);
    dyad[8][1][1] = w00w22[8];
    dyad[8][1][2] = (w1w2[8]-onk[1][0]);
    dyad[8][2][0] = (w0w2[8]-onk[1][1]);
    dyad[8][2][1] = (onk[1][0]+w1w2[8]);
    dyad[8][2][2] = w00w11[8];
    dyad[9][0][0] = w11w22[9];
    dyad[9][0][1] = (w0w1[9]-onk[2][2]);
    dyad[9][0][2] = (onk[2][1]+w0w2[9]);
    dyad[9][1][0] = (onk[2][2]+w0w1[9]);
    dyad[9][1][1] = w00w22[9];
    dyad[9][1][2] = (w1w2[9]-onk[2][0]);
    dyad[9][2][0] = (w0w2[9]-onk[2][1]);
    dyad[9][2][1] = (onk[2][0]+w1w2[9]);
    dyad[9][2][2] = w00w11[9];
    dyad[10][0][0] = w11w22[10];
    dyad[10][0][1] = (w0w1[10]-onk[3][2]);
    dyad[10][0][2] = (onk[3][1]+w0w2[10]);
    dyad[10][1][0] = (onk[3][2]+w0w1[10]);
    dyad[10][1][1] = w00w22[10];
    dyad[10][1][2] = (w1w2[10]-onk[3][0]);
    dyad[10][2][0] = (w0w2[10]-onk[3][1]);
    dyad[10][2][1] = (onk[3][0]+w1w2[10]);
    dyad[10][2][2] = w00w11[10];
    dyad[11][0][0] = w11w22[11];
    dyad[11][0][1] = (w0w1[11]-onk[4][2]);
    dyad[11][0][2] = (onk[4][1]+w0w2[11]);
    dyad[11][1][0] = (onk[4][2]+w0w1[11]);
    dyad[11][1][1] = w00w22[11];
    dyad[11][1][2] = (w1w2[11]-onk[4][0]);
    dyad[11][2][0] = (w0w2[11]-onk[4][1]);
    dyad[11][2][1] = (onk[4][0]+w1w2[11]);
    dyad[11][2][2] = w00w11[11];
/*
Compute ank & anb (mass center linear accels in N)
*/
    Ankb[2][0] = ((.0776*Onkb[2][2])-(.0036*Onkb[2][1]));
    Ankb[2][1] = ((.0036*Onkb[2][0])+(.0064*Onkb[2][2]));
    Ankb[2][2] = -((.0064*Onkb[2][1])+(.0776*Onkb[2][0]));
    AOnkri[3][0] = (Ankb[2][0]+((.0085*Onkb[2][1])+(.2131*Onkb[2][2])));
    AOnkri[3][1] = (Ankb[2][1]-((.0006*Onkb[2][2])+(.0085*Onkb[2][0])));
    AOnkri[3][2] = (Ankb[2][2]+((.0006*Onkb[2][1])-(.2131*Onkb[2][0])));
    Ankb[3][0] = (((.0634*Onkb[3][2])-(.0039*Onkb[3][1]))+((AOnkri[3][2]*
      Cik[3][2][0])+((AOnkri[3][0]*Cik[3][0][0])+(AOnkri[3][1]*Cik[3][1][0]))));
    Ankb[3][1] = (((.0039*Onkb[3][0])-(.0003*Onkb[3][2]))+((AOnkri[3][2]*
      Cik[3][2][1])+((AOnkri[3][0]*Cik[3][0][1])+(AOnkri[3][1]*Cik[3][1][1]))));
    Ankb[3][2] = (((.0003*Onkb[3][1])-(.0634*Onkb[3][0]))+((AOnkri[3][2]*
      Cik[3][2][2])+((AOnkri[3][0]*Cik[3][0][2])+(AOnkri[3][1]*Cik[3][1][2]))));
    AOnkri[4][0] = (Ankb[3][0]-((.0124*Onkb[3][1])+(.0501*Onkb[3][2])));
    AOnkri[4][1] = (Ankb[3][1]+((.0124*Onkb[3][0])+(.0174*Onkb[3][2])));
    AOnkri[4][2] = (Ankb[3][2]+((.0501*Onkb[3][0])-(.0174*Onkb[3][1])));
    Ankb[4][0] = (((.1179*Onkb[4][2])-(.0129*Onkb[4][1]))+((AOnkri[4][2]*
      Cik[4][2][0])+((AOnkri[4][0]*Cik[4][0][0])+(AOnkri[4][1]*Cik[4][1][0]))));
    Ankb[4][1] = (((.0106*Onkb[4][2])+(.0129*Onkb[4][0]))+((AOnkri[4][2]*
      Cik[4][2][1])+((AOnkri[4][0]*Cik[4][0][1])+(AOnkri[4][1]*Cik[4][1][1]))));
    Ankb[4][2] = (((AOnkri[4][2]*Cik[4][2][2])+((AOnkri[4][0]*Cik[4][0][2])+(
      AOnkri[4][1]*Cik[4][1][2])))-((.0106*Onkb[4][1])+(.1179*Onkb[4][0])));
    AnkAtk[2][0] = (Ankb[2][0]+Atk[2][0]);
    AnkAtk[2][1] = (Ankb[2][1]+Atk[2][1]);
    AnkAtk[2][2] = (Ankb[2][2]+Atk[2][2]);
    ank[2][0] = ((AnkAtk[2][2]*cnk[2][0][2])+((AnkAtk[2][0]*cnk[2][0][0])+(
      AnkAtk[2][1]*cnk[1][0][1])));
    ank[2][1] = ((AnkAtk[2][2]*cnk[2][1][2])+((AnkAtk[2][0]*cnk[2][1][0])+(
      AnkAtk[2][1]*c1)));
    ank[2][2] = ((AnkAtk[2][2]*cnk[2][2][2])+((AnkAtk[2][0]*cnk[2][2][0])+(
      AnkAtk[2][1]*cnk[1][2][1])));
    AnkAtk[3][0] = (Ankb[3][0]+Atk[3][0]);
    AnkAtk[3][1] = (Ankb[3][1]+Atk[3][1]);
    AnkAtk[3][2] = (Ankb[3][2]+Atk[3][2]);
    ank[3][0] = ((AnkAtk[3][2]*cnk[3][0][2])+((AnkAtk[3][0]*cnk[3][0][0])+(
      AnkAtk[3][1]*cnk[3][0][1])));
    ank[3][1] = ((AnkAtk[3][2]*cnk[3][1][2])+((AnkAtk[3][0]*cnk[3][1][0])+(
      AnkAtk[3][1]*cnk[3][1][1])));
    ank[3][2] = ((AnkAtk[3][2]*cnk[3][2][2])+((AnkAtk[3][0]*cnk[3][2][0])+(
      AnkAtk[3][1]*cnk[3][2][1])));
    AnkAtk[4][0] = (Ankb[4][0]+Atk[4][0]);
    AnkAtk[4][1] = (Ankb[4][1]+Atk[4][1]);
    AnkAtk[4][2] = (Ankb[4][2]+Atk[4][2]);
    ank[4][0] = ((AnkAtk[4][2]*cnk[4][0][2])+((AnkAtk[4][0]*cnk[4][0][0])+(
      AnkAtk[4][1]*cnk[4][0][1])));
    ank[4][1] = ((AnkAtk[4][2]*cnk[4][1][2])+((AnkAtk[4][0]*cnk[4][1][0])+(
      AnkAtk[4][1]*cnk[4][1][1])));
    ank[4][2] = ((AnkAtk[4][2]*cnk[4][2][2])+((AnkAtk[4][0]*cnk[4][2][0])+(
      AnkAtk[4][1]*cnk[4][2][1])));
    anb[0][0] = 0.;
    anb[0][1] = 0.;
    anb[0][2] = 0.;
    anb[1][0] = 0.;
    anb[1][1] = 0.;
    anb[1][2] = 0.;
    anb[2][0] = 0.;
    anb[2][1] = 0.;
    anb[2][2] = 0.;
    anb[3][0] = 0.;
    anb[3][1] = 0.;
    anb[3][2] = 0.;
    anb[4][0] = 0.;
    anb[4][1] = 0.;
    anb[4][2] = 0.;
    anb[5][0] = 0.;
    anb[5][1] = 0.;
    anb[5][2] = 0.;
    anb[6][0] = 0.;
    anb[6][1] = 0.;
    anb[6][2] = 0.;
    anb[7][0] = 0.;
    anb[7][1] = 0.;
    anb[7][2] = 0.;
    anb[8][0] = 0.;
    anb[8][1] = 0.;
    anb[8][2] = 0.;
    anb[9][0] = ank[2][0];
    anb[9][1] = ank[2][1];
    anb[9][2] = ank[2][2];
    anb[10][0] = ank[3][0];
    anb[10][1] = ank[3][1];
    anb[10][2] = ank[3][2];
    anb[11][0] = ank[4][0];
    anb[11][1] = ank[4][1];
    anb[11][2] = ank[4][2];
    roustate = 3;
/*
 Used -0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain  126 adds/subtracts/negates
                    105 multiplies
                      0 divides
                    240 assignments
*/
}

void sdmassmat(double mmat[5][5])
{
/* Calculate the system mass matrix
*/
    int i,j;
    double udotin[5],mmrow[5],biastrq[5];

    if ((roustate != 2) && (roustate != 3)) {
        sdseterr(57,23);
        return;
    }
    for (i = 0; i < 5; i++) {
        udotin[i] = 0.;
    }
    sdcomptrq(udotin,biastrq);
    for (i = 0; i < 5; i++) {
        udotin[i] = 1.;
        sdcomptrq(udotin,mmrow);
        udotin[i] = 0.;
        for (j = i; j <= 4; j++) {
            mmat[i][j] = mmrow[j]-biastrq[j];
            mmat[j][i] = mmat[i][j];
        }
    }
/*
Check for singular mass matrix
*/
    for (i = 0; i < 5; i++) {
        if (mmat[i][i] <= 1e-13) {
            sdseterr(57,47);
        }
    }
}

void sdfrcmat(double fmat[5])
{
/* Return the system force matrix (RHS), excluding constraints
*/
    int i;

    if ((roustate != 2) && (roustate != 3)) {
        sdseterr(58,23);
        return;
    }
    sddofs0();
    for (i = 0; i < 5; i++) {
        fmat[i] = fs0[i];
    }
}

void sdpseudo(double lqout[1],
    double luout[1])
{
/*
Return pseudo-coordinates for loop joints.

*/
/*
There are no loop joints in this system.

*/
}

void sdpsqdot(double lqdout[1])
{
/*
Return pseudo-coordinate derivatives for loop joints.

*/
/*
There are no loop joints in this system.

*/
}

void sdpsudot(double ludout[1])
{
/*
Return pseudo-coordinate accelerations for loop joints.

*/
/*
There are no loop joints in this system.

*/
}

void sdperr(double errs[1])
{

}

void sdverr(double errs[1])
{

}

void sdaerr(double errs[1])
{

}
int 
sdchkbnum(int routine,
    int bnum)
{

    if ((bnum < -1) || (bnum > 11)) {
        sdseterr(routine,15);
        return 1;
    }
    return 0;
}
int 
sdchkjnum(int routine,
    int jnum)
{

    if ((jnum < 0) || (jnum > 11)) {
        sdseterr(routine,16);
        return 1;
    }
    return 0;
}
int 
sdchkucnum(int routine,
    int ucnum)
{

    if ((ucnum < 0) || (ucnum > -1)) {
        sdseterr(routine,21);
        return 1;
    }
    return 0;
}
int 
sdchkjaxis(int routine,
    int jnum,
    int axnum)
{
    int maxax;

    if (sdchkjnum(routine,jnum) != 0) {
        return 1;
    }
    if ((axnum < 0) || (axnum > 6)) {
        sdseterr(routine,17);
        return 1;
    }
    maxax = njntdof[jnum]-1;
    if ((jtype[jnum] == 4) || (jtype[jnum] == 6) || (jtype[jnum] == 21)) {
        maxax = maxax+1;
    }
    if (axnum > maxax) {
        sdseterr(routine,18);
        return 1;
    }
    return 0;
}
int 
sdchkjpin(int routine,
    int jnum,
    int pinno)
{
    int maxax,pinok;

    if (sdchkjnum(routine,jnum) != 0) {
        return 1;
    }
    if ((pinno < 0) || (pinno > 5)) {
        sdseterr(routine,17);
        return 1;
    }
    if (njntdof[jnum] >= 3) {
        maxax = 2;
    } else {
        maxax = njntdof[jnum]-1;
    }
    if (jtype[jnum] == 4) {
        maxax = -1;
    }
    if (jtype[jnum] == 7) {
        maxax = 0;
    }
    pinok = 0;
    if (pinno <= maxax) {
        pinok = 1;
    }
    if (pinok == 0) {
        sdseterr(routine,18);
        return 1;
    }
    return 0;
}
int 
sdindx(int joint,
    int axis)
{
    int offs,gotit;

    if (sdchkjaxis(36,joint,axis) != 0) {
        return 0;
    }
    gotit = 0;
    if (jtype[joint] == 4) {
        if (axis == 3) {
            offs = ballq[joint];
            gotit = 1;
        }
    } else {
        if ((jtype[joint] == 6) || (jtype[joint] == 21)) {
            if (axis == 6) {
                offs = ballq[joint];
                gotit = 1;
            }
        }
    }
    if (gotit == 0) {
        offs = firstq[joint]+axis;
    }
    return offs;
}

void sdpresacc(int joint,
    int axis,
    double prval)
{

}

void sdpresvel(int joint,
    int axis,
    double prval)
{

}

void sdprespos(int joint,
    int axis,
    double prval)
{

}

void sdgetht(int joint,
    int axis,
    double *torque)
{

    if (sdchkjaxis(30,joint,axis) != 0) {
        return;
    }
    if (roustate != 3) {
        sdseterr(30,24);
        return;
    }
    *torque = tauc[sdindx(joint,axis)];
}

void sdhinget(int joint,
    int axis,
    double torque)
{

    if (sdchkjaxis(10,joint,axis) != 0) {
        return;
    }
    if (roustate != 2) {
        sdseterr(10,23);
        return;
    }
    if (mfrcflg != 0) {
        mtau[sdindx(joint,axis)] = mtau[sdindx(joint,axis)]+torque;
    } else {
        fs0flg = 0;
        utau[sdindx(joint,axis)] = utau[sdindx(joint,axis)]+torque;
    }
}

void sdpointf(int body,
    double point[3],
    double force[3])
{
    double torque[3];

    if (sdchkbnum(11,body) != 0) {
        return;
    }
    if (roustate != 2) {
        sdseterr(11,23);
        return;
    }
    if (body == -1) {
        return;
    }
    torque[0] = point[1]*force[2]-point[2]*force[1];
    torque[1] = point[2]*force[0]-point[0]*force[2];
    torque[2] = point[0]*force[1]-point[1]*force[0];
    if (mfrcflg != 0) {
        mfk[body][0] = mfk[body][0]+force[0];
        mtk[body][0] = mtk[body][0]+torque[0];
        mfk[body][1] = mfk[body][1]+force[1];
        mtk[body][1] = mtk[body][1]+torque[1];
        mfk[body][2] = mfk[body][2]+force[2];
        mtk[body][2] = mtk[body][2]+torque[2];
    } else {
        fs0flg = 0;
        ufk[body][0] = ufk[body][0]+force[0];
        utk[body][0] = utk[body][0]+torque[0];
        ufk[body][1] = ufk[body][1]+force[1];
        utk[body][1] = utk[body][1]+torque[1];
        ufk[body][2] = ufk[body][2]+force[2];
        utk[body][2] = utk[body][2]+torque[2];
    }
}

void sdbodyt(int body,
    double torque[3])
{

    if (sdchkbnum(12,body) != 0) {
        return;
    }
    if (roustate != 2) {
        sdseterr(12,23);
        return;
    }
    if (body == -1) {
        return;
    }
    if (mfrcflg != 0) {
        mtk[body][0] = mtk[body][0]+torque[0];
        mtk[body][1] = mtk[body][1]+torque[1];
        mtk[body][2] = mtk[body][2]+torque[2];
    } else {
        fs0flg = 0;
        utk[body][0] = utk[body][0]+torque[0];
        utk[body][1] = utk[body][1]+torque[1];
        utk[body][2] = utk[body][2]+torque[2];
    }
}

void sddoww(int routine)
{

    roustate = 2;
    if (wwflg == 0) {
        wwflg = 1;
    }
/*
 Used -0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain    0 adds/subtracts/negates
                      0 multiplies
                      0 divides
                      0 assignments
*/
}

void sdxudot0(int routine,
    double oudot0[5])
{
/*
Compute unconstrained equations
*/
    int i;
    double eps[5],Z1[5][3],Z2[5][3],A1[5][3],A2[5][3],K1[5][3],K2[5][3];

    sdlhs(routine);
/*
Solve equations for udots
*/
    eps[4] = fs0[4];
    Z1[3][0] = ((2.53942597262158*(Cik[4][0][2]*eps[4]))+((.514968628275491*(
      Cik[4][0][1]*eps[4]))+(8.81824493589611*(Cik[4][0][0]*eps[4]))));
    Z1[3][1] = ((2.53942597262158*(Cik[4][1][2]*eps[4]))+((.514968628275491*(
      Cik[4][1][1]*eps[4]))+(8.81824493589611*(Cik[4][1][0]*eps[4]))));
    Z1[3][2] = ((2.53942597262158*(Cik[4][2][2]*eps[4]))+((.514968628275491*(
      Cik[4][2][1]*eps[4]))+(8.81824493589611*(Cik[4][2][0]*eps[4]))));
    Z2[3][0] = (((1.96336861556918*(Cik[4][0][2]*eps[4]))+((.535960331588656*(
      Cik[4][0][1]*eps[4]))-(.823822716994287*(Cik[4][0][0]*eps[4]))))+((
      2.53942597262158*(eps[4]*rikt[4][0][2]))+((.514968628275491*(eps[4]*
      rikt[4][0][1]))+(8.81824493589611*(eps[4]*rikt[4][0][0])))));
    Z2[3][1] = (((1.96336861556918*(Cik[4][1][2]*eps[4]))+((.535960331588656*(
      Cik[4][1][1]*eps[4]))-(.823822716994287*(Cik[4][1][0]*eps[4]))))+((
      2.53942597262158*(eps[4]*rikt[4][1][2]))+((.514968628275491*(eps[4]*
      rikt[4][1][1]))+(8.81824493589611*(eps[4]*rikt[4][1][0])))));
    Z2[3][2] = (((1.96336861556918*(Cik[4][2][2]*eps[4]))+((.535960331588656*(
      Cik[4][2][1]*eps[4]))-(.823822716994287*(Cik[4][2][0]*eps[4]))))+((
      2.53942597262158*(eps[4]*rikt[4][2][2]))+((.514968628275491*(eps[4]*
      rikt[4][2][1]))+(8.81824493589611*(eps[4]*rikt[4][2][0])))));
    eps[3] = (fs0[3]-(((.00844600099996266*Z2[3][1])+(.99976612099558*Z2[3][0]))
      -(.019909002399912*Z2[3][2])));
    Z1[3][0] = (Z1[3][0]+(eps[3]*G1[3][0]));
    Z1[3][1] = (Z1[3][1]+(eps[3]*G1[3][1]));
    Z1[3][2] = (Z1[3][2]+(eps[3]*G1[3][2]));
    Z2[3][0] = (Z2[3][0]+(eps[3]*G2[3][0]));
    Z2[3][1] = (Z2[3][1]+(eps[3]*G2[3][1]));
    Z2[3][2] = (Z2[3][2]+(eps[3]*G2[3][2]));
    Z1[2][0] = ((Cik[3][0][2]*Z1[3][2])+((Cik[3][0][0]*Z1[3][0])+(Cik[3][0][1]*
      Z1[3][1])));
    Z1[2][1] = ((Cik[3][1][2]*Z1[3][2])+((Cik[3][1][0]*Z1[3][0])+(Cik[3][1][1]*
      Z1[3][1])));
    Z1[2][2] = ((Cik[3][2][2]*Z1[3][2])+((Cik[3][2][0]*Z1[3][0])+(Cik[3][2][1]*
      Z1[3][1])));
    Z2[2][0] = (((Cik[3][0][2]*Z2[3][2])+((Cik[3][0][0]*Z2[3][0])+(Cik[3][0][1]*
      Z2[3][1])))+((rikt[3][0][2]*Z1[3][2])+((rikt[3][0][0]*Z1[3][0])+(
      rikt[3][0][1]*Z1[3][1]))));
    Z2[2][1] = (((Cik[3][1][2]*Z2[3][2])+((Cik[3][1][0]*Z2[3][0])+(Cik[3][1][1]*
      Z2[3][1])))+((rikt[3][1][2]*Z1[3][2])+((rikt[3][1][0]*Z1[3][0])+(
      rikt[3][1][1]*Z1[3][1]))));
    Z2[2][2] = (((Cik[3][2][2]*Z2[3][2])+((Cik[3][2][0]*Z2[3][0])+(Cik[3][2][1]*
      Z2[3][1])))+((rikt[3][2][2]*Z1[3][2])+((rikt[3][2][0]*Z1[3][0])+(
      rikt[3][2][1]*Z1[3][1]))));
    eps[2] = (fs0[2]-Z2[2][1]);
    Z1[2][0] = (Z1[2][0]+(eps[2]*G1[2][0]));
    Z1[2][1] = (Z1[2][1]+(eps[2]*G1[2][1]));
    Z1[2][2] = (Z1[2][2]+(eps[2]*G1[2][2]));
    Z2[2][0] = (Z2[2][0]+(eps[2]*G2[2][0]));
    Z2[2][1] = (eps[2]+Z2[2][1]);
    Z2[2][2] = (Z2[2][2]+(eps[2]*G2[2][2]));
    Z1[1][0] = ((Z1[2][0]*c2)+(Z1[2][2]*s2));
    Z1[1][1] = Z1[2][1];
    Z1[1][2] = ((Z1[2][2]*c2)-(Z1[2][0]*s2));
    Z2[1][0] = ((Z2[2][0]*c2)+(Z2[2][2]*s2));
    Z2[1][1] = Z2[2][1];
    Z2[1][2] = ((Z2[2][2]*c2)-(Z2[2][0]*s2));
    eps[1] = (fs0[1]-Z2[1][2]);
    Z1[1][0] = (Z1[1][0]+(eps[1]*G1[1][0]));
    Z1[1][1] = (Z1[1][1]+(eps[1]*G1[1][1]));
    Z1[1][2] = (Z1[1][2]+(eps[1]*G1[1][2]));
    Z2[1][0] = (Z2[1][0]+(eps[1]*G2[1][0]));
    Z2[1][1] = (Z2[1][1]+(eps[1]*G2[1][1]));
    Z2[1][2] = (eps[1]+Z2[1][2]);
    Z1[0][0] = ((Z1[1][0]*c1)-(Z1[1][1]*s1));
    Z1[0][1] = ((Z1[1][0]*s1)+(Z1[1][1]*c1));
    Z1[0][2] = Z1[1][2];
    Z2[0][0] = ((Z2[1][0]*c1)-(Z2[1][1]*s1));
    Z2[0][1] = ((Z2[1][0]*s1)+(Z2[1][1]*c1));
    Z2[0][2] = Z2[1][2];
    eps[0] = (fs0[0]-Z2[0][1]);
    udot[0] = (DD[0]*eps[0]);
    K2[1][0] = (udot[0]*s1);
    K2[1][1] = (udot[0]*c1);
    udot[1] = ((DD[1]*eps[1])-((G2[1][0]*K2[1][0])+(G2[1][1]*K2[1][1])));
    K2[2][0] = ((K2[1][0]*c2)-(udot[1]*s2));
    K2[2][2] = ((K2[1][0]*s2)+(udot[1]*c2));
    udot[2] = ((DD[2]*eps[2])-((G2[2][2]*K2[2][2])+(K2[1][1]+(G2[2][0]*K2[2][0])
      )));
    A2[2][1] = (K2[1][1]+udot[2]);
    K1[3][0] = ((K2[2][2]*rikt[3][2][0])+((A2[2][1]*rikt[3][1][0])+(K2[2][0]*
      rikt[3][0][0])));
    K1[3][1] = ((K2[2][2]*rikt[3][2][1])+((A2[2][1]*rikt[3][1][1])+(K2[2][0]*
      rikt[3][0][1])));
    K1[3][2] = ((K2[2][2]*rikt[3][2][2])+((A2[2][1]*rikt[3][1][2])+(K2[2][0]*
      rikt[3][0][2])));
    K2[3][0] = ((Cik[3][2][0]*K2[2][2])+((A2[2][1]*Cik[3][1][0])+(Cik[3][0][0]*
      K2[2][0])));
    K2[3][1] = ((Cik[3][2][1]*K2[2][2])+((A2[2][1]*Cik[3][1][1])+(Cik[3][0][1]*
      K2[2][0])));
    K2[3][2] = ((Cik[3][2][2]*K2[2][2])+((A2[2][1]*Cik[3][1][2])+(Cik[3][0][2]*
      K2[2][0])));
    udot[3] = ((DD[3]*eps[3])-(((G1[3][2]*K1[3][2])+((G1[3][0]*K1[3][0])+(
      G1[3][1]*K1[3][1])))+((G2[3][2]*K2[3][2])+((G2[3][0]*K2[3][0])+(G2[3][1]*
      K2[3][1])))));
    A2[3][0] = (K2[3][0]+(.99976612099558*udot[3]));
    A2[3][1] = (K2[3][1]+(.00844600099996266*udot[3]));
    A2[3][2] = (K2[3][2]-(.019909002399912*udot[3]));
    K1[4][0] = (((A2[3][2]*rikt[4][2][0])+((A2[3][0]*rikt[4][0][0])+(A2[3][1]*
      rikt[4][1][0])))+((Cik[4][2][0]*K1[3][2])+((Cik[4][0][0]*K1[3][0])+(
      Cik[4][1][0]*K1[3][1]))));
    K1[4][1] = (((A2[3][2]*rikt[4][2][1])+((A2[3][0]*rikt[4][0][1])+(A2[3][1]*
      rikt[4][1][1])))+((Cik[4][2][1]*K1[3][2])+((Cik[4][0][1]*K1[3][0])+(
      Cik[4][1][1]*K1[3][1]))));
    K1[4][2] = (((A2[3][2]*rikt[4][2][2])+((A2[3][0]*rikt[4][0][2])+(A2[3][1]*
      rikt[4][1][2])))+((Cik[4][2][2]*K1[3][2])+((Cik[4][0][2]*K1[3][0])+(
      Cik[4][1][2]*K1[3][1]))));
    K2[4][0] = ((A2[3][2]*Cik[4][2][0])+((A2[3][0]*Cik[4][0][0])+(A2[3][1]*
      Cik[4][1][0])));
    K2[4][1] = ((A2[3][2]*Cik[4][2][1])+((A2[3][0]*Cik[4][0][1])+(A2[3][1]*
      Cik[4][1][1])));
    K2[4][2] = ((A2[3][2]*Cik[4][2][2])+((A2[3][0]*Cik[4][0][2])+(A2[3][1]*
      Cik[4][1][2])));
    udot[4] = ((1532.60616412784*eps[4])-(((1.96336861556918*K2[4][2])+((
      .535960331588656*K2[4][1])-(.823822716994287*K2[4][0])))+((
      2.53942597262158*K1[4][2])+((.514968628275491*K1[4][1])+(8.81824493589611*
      K1[4][0])))));
    A2[4][0] = (K2[4][0]-(.113294979100377*udot[4]));
    A2[4][1] = (K2[4][1]+(.974058820703242*udot[4]));
    A2[4][2] = (K2[4][2]+(.195891963900652*udot[4]));
    for (i = 0; i <= 4; i++) {
        oudot0[i] = udot[i];
    }
/*
 Used -0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain  133 adds/subtracts/negates
                    194 multiplies
                      0 divides
                     80 assignments
*/
}

void sdudot0(double oudot0[5])
{

    if ((roustate != 2) && (roustate != 3)) {
        sdseterr(66,23);
        return;
    }
    sdxudot0(66,oudot0);
}

void sdsetudot(double iudot[5])
{
/*
Assign udots and advance to stage Dynamics Ready
*/
    int i;

    if ((roustate != 2) && (roustate != 3)) {
        sdseterr(68,23);
        return;
    }
    for (i = 0; i <= 4; i++) {
        udot[i] = iudot[i];
    }
    sdrhs();
}

void sdxudotm(int routine,
    double imult[1],
    double oudotm[5])
{
/*
Compute udots due only to multipliers
*/
    int i;
    double eps[5],Z1[5][3],Z2[5][3],A1[5][3],A2[5][3],K1[5][3],K2[5][3];

    sdlhs(routine);
    for (i = 0; i <= 4; i++) {
        udot[i] = 0.;
    }
    for (i = 0; i <= 4; i++) {
        oudotm[i] = udot[i];
    }
/*
 Used -0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain    0 adds/subtracts/negates
                      0 multiplies
                      0 divides
                     10 assignments
*/
}

void sdudotm(double imult[1],
    double oudotm[5])
{

    if ((roustate != 2) && (roustate != 3)) {
        sdseterr(67,23);
        return;
    }
    sdxudotm(67,imult,oudotm);
}

void sdderiv(double oqdot[5],
    double oudot[5])
{
/*
This is the derivative section for a 12-body ground-based
system with 5 hinge degree(s) of freedom.
*/
    int i;
    double udot0[5],udot1[5];
    double eps[5],Z1[5][3],Z2[5][3],A1[5][3],A2[5][3],K1[5][3],K2[5][3];

    if ((roustate != 2) && (roustate != 3)) {
        sdseterr(17,23);
        return;
    }
    if (stabvelq == 1) {
        sdseterr(17,32);
    }
    if (stabposq == 1) {
        sdseterr(17,33);
    }
    wsiz = 0;
/*
Compute unconstrained equations
*/
    sdxudot0(17,udot0);
    sdrhs();
    wrank = 0;
    for (i = 0; i <= 4; i++) {
        oqdot[i] = qdot[i];
    }
    for (i = 0; i <= 4; i++) {
        oudot[i] = udot[i];
    }
/*
 Used -0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain    0 adds/subtracts/negates
                      0 multiplies
                      0 divides
                     10 assignments
*/
}
/*
Compute residuals for use with DAE integrator
*/

void sdresid(double eqdot[5],
    double eudot[5],
    double emults[1],
    double resid[10])
{
    int i;
    double uderrs[5];

    if ((roustate != 2) && (roustate != 3)) {
        sdseterr(16,23);
        return;
    }
    if (stabposq == 1) {
        sdseterr(16,33);
    }
    sdfulltrq(eudot,emults,uderrs);
    for (i = 0; i < 5; i++) {
        resid[i] = eqdot[i]-qdot[i];
    }
    for (i = 0; i < 5; i++) {
        resid[5+i] = uderrs[i];
    }
    for (i = 0; i < 5; i++) {
        udot[i] = eudot[i];
    }
    sdrhs();
/*
 Used -0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain    5 adds/subtracts/negates
                      0 multiplies
                      0 divides
                     15 assignments
*/
}

void sdmult(double omults[1],
    int *owrank,
    int omultmap[1])
{

    if (roustate != 3) {
        sdseterr(34,24);
        return;
    }
    *owrank = wrank;
}

void sdreac(double force[12][3],
    double torque[12][3])
{
/*
Generated 14-Nov-2007 16:57:48 by SD/FAST, Order(N) formulation
(sdfast B.2.8 #30123) on machine ID unknown
Copyright (c) 1990-1997 Symbolic Dynamics, Inc.
Copyright (c) 1990-1997 Parametric Technology Corp.
RESTRICTED RIGHTS LEGEND: Use, duplication, or disclosure by the U.S.
Government is subject to restrictions as set forth in subparagraph
(c)(1)(ii) of the Rights in Technical Data and Computer Software
clause at DFARS 52.227-7013 and similar clauses in the FAR and NASA
FAR Supplement.  Symbolic Dynamics, Inc., Mountain View, CA 94041
*/

    if (roustate != 3) {
        sdseterr(31,24);
        return;
    }
/*
Compute reaction forces for non-weld tree joints
*/
    fc[4][0] = ((.5464*(AnkAtk[4][0]-gk[4][0]))-ufk[11][0]);
    fc[4][1] = ((.5464*(AnkAtk[4][1]-gk[4][1]))-ufk[11][1]);
    fc[4][2] = ((.5464*(AnkAtk[4][2]-gk[4][2]))-ufk[11][2]);
    tc[4][0] = ((WkIkWk[4][0]+(.0030585*onk[4][0]))-(utk[11][0]+((.1179*fc[4][2]
      )-(.0129*fc[4][1]))));
    tc[4][1] = ((.00045325*onk[4][1])-(utk[11][1]+((.0106*fc[4][2])+(.0129*
      fc[4][0]))));
    tc[4][2] = ((WkIkWk[4][2]+(.0030585*onk[4][2]))-(utk[11][2]-((.0106*fc[4][1]
      )+(.1179*fc[4][0]))));
    fccikt[4][0] = ((Cik[4][0][2]*fc[4][2])+((Cik[4][0][0]*fc[4][0])+(
      Cik[4][0][1]*fc[4][1])));
    fccikt[4][1] = ((Cik[4][1][2]*fc[4][2])+((Cik[4][1][0]*fc[4][0])+(
      Cik[4][1][1]*fc[4][1])));
    fccikt[4][2] = ((Cik[4][2][2]*fc[4][2])+((Cik[4][2][0]*fc[4][0])+(
      Cik[4][2][1]*fc[4][1])));
    ffk[3][0] = (ufk[10][0]-fccikt[4][0]);
    ffk[3][1] = (ufk[10][1]-fccikt[4][1]);
    ffk[3][2] = (ufk[10][2]-fccikt[4][2]);
    ttk[3][0] = (utk[10][0]-(((.0124*fccikt[4][1])+(.0501*fccikt[4][2]))+((
      Cik[4][0][2]*tc[4][2])+((Cik[4][0][0]*tc[4][0])+(Cik[4][0][1]*tc[4][1]))))
      );
    ttk[3][1] = (utk[10][1]-(((Cik[4][1][2]*tc[4][2])+((Cik[4][1][0]*tc[4][0])+(
      Cik[4][1][1]*tc[4][1])))-((.0124*fccikt[4][0])+(.0174*fccikt[4][2]))));
    ttk[3][2] = (utk[10][2]-(((.0174*fccikt[4][1])-(.0501*fccikt[4][0]))+((
      Cik[4][2][2]*tc[4][2])+((Cik[4][2][0]*tc[4][0])+(Cik[4][2][1]*tc[4][1]))))
      );
    fc[3][0] = ((.5464*(AnkAtk[3][0]-gk[3][0]))-ffk[3][0]);
    fc[3][1] = ((.5464*(AnkAtk[3][1]-gk[3][1]))-ffk[3][1]);
    fc[3][2] = ((.5464*(AnkAtk[3][2]-gk[3][2]))-ffk[3][2]);
    tc[3][0] = ((WkIkWk[3][0]+(.0030585*onk[3][0]))-(ttk[3][0]+((.0634*fc[3][2])
      -(.0039*fc[3][1]))));
    tc[3][1] = ((.00045325*onk[3][1])-(ttk[3][1]+((.0039*fc[3][0])-(.0003*
      fc[3][2]))));
    tc[3][2] = ((WkIkWk[3][2]+(.0030585*onk[3][2]))-(ttk[3][2]+((.0003*fc[3][1])
      -(.0634*fc[3][0]))));
    fccikt[3][0] = ((Cik[3][0][2]*fc[3][2])+((Cik[3][0][0]*fc[3][0])+(
      Cik[3][0][1]*fc[3][1])));
    fccikt[3][1] = ((Cik[3][1][2]*fc[3][2])+((Cik[3][1][0]*fc[3][0])+(
      Cik[3][1][1]*fc[3][1])));
    fccikt[3][2] = ((Cik[3][2][2]*fc[3][2])+((Cik[3][2][0]*fc[3][0])+(
      Cik[3][2][1]*fc[3][1])));
    ffk[2][0] = (ufk[9][0]-fccikt[3][0]);
    ffk[2][1] = (ufk[9][1]-fccikt[3][1]);
    ffk[2][2] = (ufk[9][2]-fccikt[3][2]);
    ttk[2][0] = (utk[9][0]-(((Cik[3][0][2]*tc[3][2])+((Cik[3][0][0]*tc[3][0])+(
      Cik[3][0][1]*tc[3][1])))-((.0085*fccikt[3][1])+(.2131*fccikt[3][2]))));
    ttk[2][1] = (utk[9][1]-(((.0006*fccikt[3][2])+(.0085*fccikt[3][0]))+((
      Cik[3][1][2]*tc[3][2])+((Cik[3][1][0]*tc[3][0])+(Cik[3][1][1]*tc[3][1]))))
      );
    ttk[2][2] = (utk[9][2]-(((.2131*fccikt[3][0])-(.0006*fccikt[3][1]))+((
      Cik[3][2][2]*tc[3][2])+((Cik[3][2][0]*tc[3][0])+(Cik[3][2][1]*tc[3][1]))))
      );
    fc[2][0] = ((2.0519*(AnkAtk[2][0]-gk[2][0]))-ffk[2][0]);
    fc[2][1] = ((2.0519*(AnkAtk[2][1]+(9.80665*c1)))-ffk[2][1]);
    fc[2][2] = ((2.0519*(AnkAtk[2][2]-gk[2][2]))-ffk[2][2]);
    tc[2][0] = ((WkIkWk[2][0]+(.0132*onk[2][0]))-(ttk[2][0]+((.0776*fc[2][2])-(
      .0036*fc[2][1]))));
    tc[2][1] = ((.001988*onk[2][1])-(ttk[2][1]+((.0036*fc[2][0])+(.0064*fc[2][2]
      ))));
    tc[2][2] = ((WkIkWk[2][2]+(.0132*onk[2][2]))-(ttk[2][2]-((.0064*fc[2][1])+(
      .0776*fc[2][0]))));
    fccikt[2][0] = ((fc[2][0]*c2)+(fc[2][2]*s2));
    fccikt[2][1] = fc[2][1];
    fccikt[2][2] = ((fc[2][2]*c2)-(fc[2][0]*s2));
    ffk[1][0] = (ufk[8][0]-fccikt[2][0]);
    ffk[1][1] = (ufk[8][1]-fccikt[2][1]);
    ffk[1][2] = (ufk[8][2]-fccikt[2][2]);
    ttk[1][0] = (utk[8][0]-((tc[2][0]*c2)+(tc[2][2]*s2)));
    ttk[1][1] = (utk[8][1]-tc[2][1]);
    ttk[1][2] = (utk[8][2]-((tc[2][2]*c2)-(tc[2][0]*s2)));
    fc[1][0] = -ffk[1][0];
    fc[1][1] = -ffk[1][1];
    fc[1][2] = -ffk[1][2];
    tc[1][0] = -ttk[1][0];
    tc[1][1] = -ttk[1][1];
    tc[1][2] = -ttk[1][2];
    fccikt[1][0] = ((fc[1][0]*c1)-(fc[1][1]*s1));
    fccikt[1][1] = ((fc[1][0]*s1)+(fc[1][1]*c1));
    fccikt[1][2] = fc[1][2];
    ffk[0][0] = (ufk[7][0]-fccikt[1][0]);
    ffk[0][1] = (ufk[7][1]-fccikt[1][1]);
    ffk[0][2] = (ufk[7][2]-fccikt[1][2]);
    ttk[0][0] = (utk[7][0]-((tc[1][0]*c1)-(tc[1][1]*s1)));
    ttk[0][1] = (utk[7][1]-((tc[1][0]*s1)+(tc[1][1]*c1)));
    ttk[0][2] = (utk[7][2]-tc[1][2]);
    fc[0][0] = -ffk[0][0];
    fc[0][1] = -ffk[0][1];
    fc[0][2] = -ffk[0][2];
    tc[0][0] = -ttk[0][0];
    tc[0][1] = -ttk[0][1];
    tc[0][2] = -ttk[0][2];
    force[7][0] = fc[0][0];
    torque[7][0] = tc[0][0];
    force[7][1] = fc[0][1];
    torque[7][1] = tc[0][1];
    force[7][2] = fc[0][2];
    torque[7][2] = tc[0][2];
    force[8][0] = fc[1][0];
    torque[8][0] = tc[1][0];
    force[8][1] = fc[1][1];
    torque[8][1] = tc[1][1];
    force[8][2] = fc[1][2];
    torque[8][2] = tc[1][2];
    force[9][0] = fc[2][0];
    torque[9][0] = tc[2][0];
    force[9][1] = fc[2][1];
    torque[9][1] = tc[2][1];
    force[9][2] = fc[2][2];
    torque[9][2] = tc[2][2];
    force[10][0] = fc[3][0];
    torque[10][0] = tc[3][0];
    force[10][1] = fc[3][1];
    torque[10][1] = tc[3][1];
    force[10][2] = fc[3][2];
    torque[10][2] = tc[3][2];
    force[11][0] = fc[4][0];
    torque[11][0] = tc[4][0];
    force[11][1] = fc[4][1];
    torque[11][1] = tc[4][1];
    force[11][2] = fc[4][2];
    torque[11][2] = tc[4][2];
/*
Compute reaction forces for tree weld joints
*/
    force[6][0] = -(ufk[6][0]-((force[7][0]*c0)+(force[7][2]*s0)));
    torque[6][0] = (((.0229*(ufk[6][2]+((force[7][0]*s0)-(force[7][2]*c0))))-(
      .0247*((ufk[6][1]-6.91761091)-force[7][1])))-(utk[6][0]-(((.0001*((
      force[7][0]*s0)-(force[7][2]*c0)))+(.0192*force[7][1]))+((torque[7][0]*c0)
      +(torque[7][2]*s0)))));
    force[6][1] = -((ufk[6][1]-6.91761091)-force[7][1]);
    torque[6][1] = (((.0247*(ufk[6][0]-((force[7][0]*c0)+(force[7][2]*s0))))-(
      .053*(ufk[6][2]+((force[7][0]*s0)-(force[7][2]*c0)))))-(utk[6][1]+(((.0192
      *((force[7][0]*c0)+(force[7][2]*s0)))-(.055*((force[7][0]*s0)-(force[7][2]
      *c0))))-torque[7][1])));
    force[6][2] = -(ufk[6][2]+((force[7][0]*s0)-(force[7][2]*c0)));
    torque[6][2] = (((.053*((ufk[6][1]-6.91761091)-force[7][1]))-(.0229*(
      ufk[6][0]-((force[7][0]*c0)+(force[7][2]*s0)))))-(utk[6][2]+(((
      torque[7][0]*s0)-(torque[7][2]*c0))-((.0001*((force[7][0]*c0)+(force[7][2]
      *s0)))+(.055*force[7][1])))));
    force[5][0] = -(ufk[5][0]-force[6][0]);
    torque[5][0] = -(utk[5][0]-torque[6][0]);
    force[5][1] = -(ufk[5][1]-force[6][1]);
    torque[5][1] = -(utk[5][1]-torque[6][1]);
    force[5][2] = -(ufk[5][2]-force[6][2]);
    torque[5][2] = -(utk[5][2]-torque[6][2]);
    force[4][0] = -(ufk[4][0]-force[5][0]);
    torque[4][0] = -(utk[4][0]-torque[5][0]);
    force[4][1] = -(ufk[4][1]-force[5][1]);
    torque[4][1] = -(utk[4][1]-torque[5][1]);
    force[4][2] = -(ufk[4][2]-force[5][2]);
    torque[4][2] = -(utk[4][2]-torque[5][2]);
    force[3][0] = -(ufk[3][0]-force[4][0]);
    torque[3][0] = (((.0042*((ufk[3][1]-1.5298374)-force[4][1]))-(.0167*(
      ufk[3][2]-force[4][2])))-(utk[3][0]+(((.0168*force[4][2])+(.024*
      force[4][1]))-torque[4][0])));
    force[3][1] = -((ufk[3][1]-1.5298374)-force[4][1]);
    torque[3][1] = (((.0983*(ufk[3][2]-force[4][2]))-(.0042*(ufk[3][0]-
      force[4][0])))-(utk[3][1]+(((.1094*force[4][2])-(.024*force[4][0]))-
      torque[4][1])));
    force[3][2] = -(ufk[3][2]-force[4][2]);
    torque[3][2] = (((.0167*(ufk[3][0]-force[4][0]))-(.0983*((ufk[3][1]-
      1.5298374)-force[4][1])))-(utk[3][2]-(torque[4][2]+((.0168*force[4][0])+(
      .1094*force[4][1])))));
    force[2][0] = -(ufk[2][0]-force[3][0]);
    torque[2][0] = -(utk[2][0]-torque[3][0]);
    force[2][1] = -(ufk[2][1]-force[3][1]);
    torque[2][1] = -(utk[2][1]-torque[3][1]);
    force[2][2] = -(ufk[2][2]-force[3][2]);
    torque[2][2] = -(utk[2][2]-torque[3][2]);
    force[1][0] = -(ufk[1][0]-force[2][0]);
    torque[1][0] = -(utk[1][0]-torque[2][0]);
    force[1][1] = -(ufk[1][1]-force[2][1]);
    torque[1][1] = -(utk[1][1]-torque[2][1]);
    force[1][2] = -(ufk[1][2]-force[2][2]);
    torque[1][2] = -(utk[1][2]-torque[2][2]);
    force[0][0] = -(ufk[0][0]-force[1][0]);
    torque[0][0] = (((.0591*((ufk[0][1]-196.133)-force[1][1]))+(.1486*(ufk[0][2]
      -force[1][2])))-(utk[0][0]-(torque[1][0]+((.0563*force[1][1])+(.1334*
      force[1][2])))));
    force[0][1] = -((ufk[0][1]-196.133)-force[1][1]);
    torque[0][1] = -((.0591*(ufk[0][0]-force[1][0]))+(utk[0][1]+(((.0014*
      force[1][2])+(.0563*force[1][0]))-torque[1][1])));
    force[0][2] = -(ufk[0][2]-force[1][2]);
    torque[0][2] = -((.1486*(ufk[0][0]-force[1][0]))+(utk[0][2]+(((.1334*
      force[1][0])-(.0014*force[1][1]))-torque[1][2])));
/*
 Used 0.01 seconds CPU time,
 0 additional bytes of memory.
 Equations contain  278 adds/subtracts/negates
                    159 multiplies
                      0 divides
                    138 assignments
*/
}

void sdmom(double lm[3],
    double am[3],
    double *ke)
{
/*
Compute system linear and angular momentum, and kinetic energy.

Generated 14-Nov-2007 16:57:48 by SD/FAST, Order(N) formulation
(sdfast B.2.8 #30123) on machine ID unknown
Copyright (c) 1990-1997 Symbolic Dynamics, Inc.
Copyright (c) 1990-1997 Parametric Technology Corp.
RESTRICTED RIGHTS LEGEND: Use, duplication, or disclosure by the U.S.
Government is subject to restrictions as set forth in subparagraph
(c)(1)(ii) of the Rights in Technical Data and Computer Software
clause at DFARS 52.227-7013 and similar clauses in the FAR and NASA
FAR Supplement.  Symbolic Dynamics, Inc., Mountain View, CA 94041
*/
    double lk[12][3],hnk[12][3];

    if ((roustate != 2) && (roustate != 3)) {
        sdseterr(19,23);
        return;
    }
    lm[0] = ((.5464*vnk[4][0])+((.5464*vnk[3][0])+(2.0519*vnk[2][0])));
    lm[1] = ((.5464*vnk[4][1])+((.5464*vnk[3][1])+(2.0519*vnk[2][1])));
    lm[2] = ((.5464*vnk[4][2])+((.5464*vnk[3][2])+(2.0519*vnk[2][2])));
    temp[0] = (((.5464*((rnk[3][1]*vnk[3][2])-(rnk[3][2]*vnk[3][1])))+((.0030585
      *(cnk[3][0][2]*wk[3][2]))+((.00045325*(cnk[3][0][1]*wk[3][1]))+(.0030585*(
      cnk[3][0][0]*wk[3][0])))))+((2.0519*((rnk[2][1]*vnk[2][2])-(rnk[2][2]*
      vnk[2][1])))+((.0132*(cnk[2][0][2]*wk[2][2]))+((.001988*(cnk[1][0][1]*
      wk[2][1]))+(.0132*(cnk[2][0][0]*wk[2][0]))))));
    am[0] = ((((.5464*((rnk[4][1]*vnk[4][2])-(rnk[4][2]*vnk[4][1])))+((.0030585*
      (cnk[4][0][2]*wk[4][2]))+((.00045325*(cnk[4][0][1]*wk[4][1]))+(.0030585*(
      cnk[4][0][0]*wk[4][0])))))+temp[0])-((com[1]*lm[2])-(com[2]*lm[1])));
    temp[0] = (((.5464*((rnk[3][2]*vnk[3][0])-(rnk[3][0]*vnk[3][2])))+((.0030585
      *(cnk[3][1][2]*wk[3][2]))+((.00045325*(cnk[3][1][1]*wk[3][1]))+(.0030585*(
      cnk[3][1][0]*wk[3][0])))))+((2.0519*((rnk[2][2]*vnk[2][0])-(rnk[2][0]*
      vnk[2][2])))+((.0132*(cnk[2][1][2]*wk[2][2]))+((.001988*(wk[2][1]*c1))+(
      .0132*(cnk[2][1][0]*wk[2][0]))))));
    am[1] = ((((.5464*((rnk[4][2]*vnk[4][0])-(rnk[4][0]*vnk[4][2])))+((.0030585*
      (cnk[4][1][2]*wk[4][2]))+((.00045325*(cnk[4][1][1]*wk[4][1]))+(.0030585*(
      cnk[4][1][0]*wk[4][0])))))+temp[0])-((com[2]*lm[0])-(com[0]*lm[2])));
    temp[0] = (((.5464*((rnk[3][0]*vnk[3][1])-(rnk[3][1]*vnk[3][0])))+((.0030585
      *(cnk[3][2][2]*wk[3][2]))+((.00045325*(cnk[3][2][1]*wk[3][1]))+(.0030585*(
      cnk[3][2][0]*wk[3][0])))))+((2.0519*((rnk[2][0]*vnk[2][1])-(rnk[2][1]*
      vnk[2][0])))+((.0132*(cnk[2][2][2]*wk[2][2]))+((.001988*(cnk[1][2][1]*
      wk[2][1]))+(.0132*(cnk[2][2][0]*wk[2][0]))))));
    am[2] = ((((.5464*((rnk[4][0]*vnk[4][1])-(rnk[4][1]*vnk[4][0])))+((.0030585*
      (cnk[4][2][2]*wk[4][2]))+((.00045325*(cnk[4][2][1]*wk[4][1]))+(.0030585*(
      cnk[4][2][0]*wk[4][0])))))+temp[0])-((com[0]*lm[1])-(com[1]*lm[0])));
    temp[0] = (((.5464*((vnk[3][2]*vnk[3][2])+((vnk[3][0]*vnk[3][0])+(vnk[3][1]*
      vnk[3][1]))))+((.0030585*(wk[3][2]*wk[3][2]))+((.00045325*(wk[3][1]*
      wk[3][1]))+(.0030585*(wk[3][0]*wk[3][0])))))+((2.0519*((vnk[2][2]*
      vnk[2][2])+((vnk[2][0]*vnk[2][0])+(vnk[2][1]*vnk[2][1]))))+((.0132*(
      wk[2][2]*wk[2][2]))+((.001988*(wk[2][1]*wk[2][1]))+(.0132*(wk[2][0]*
      wk[2][0]))))));
    *ke = (.5*(((.5464*((vnk[4][2]*vnk[4][2])+((vnk[4][0]*vnk[4][0])+(vnk[4][1]*
      vnk[4][1]))))+((.0030585*(wk[4][2]*wk[4][2]))+((.00045325*(wk[4][1]*
      wk[4][1]))+(.0030585*(wk[4][0]*wk[4][0])))))+temp[0]));
/*
 Used -0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain   71 adds/subtracts/negates
                    127 multiplies
                      0 divides
                     11 assignments
*/
}

void sdsys(double *mtoto,
    double cm[3],
    double icm[3][3])
{
/*
Compute system total mass, and instantaneous center of mass and
inertia matrix.

Generated 14-Nov-2007 16:57:48 by SD/FAST, Order(N) formulation
(sdfast B.2.8 #30123) on machine ID unknown
Copyright (c) 1990-1997 Symbolic Dynamics, Inc.
Copyright (c) 1990-1997 Parametric Technology Corp.
RESTRICTED RIGHTS LEGEND: Use, duplication, or disclosure by the U.S.
Government is subject to restrictions as set forth in subparagraph
(c)(1)(ii) of the Rights in Technical Data and Computer Software
clause at DFARS 52.227-7013 and similar clauses in the FAR and NASA
FAR Supplement.  Symbolic Dynamics, Inc., Mountain View, CA 94041
*/
    double ikcnkt[5][3][3];

    if ((roustate != 2) && (roustate != 3)) {
        sdseterr(20,23);
        return;
    }
    *mtoto = 24.0061;
    cm[0] = com[0];
    cm[1] = com[1];
    cm[2] = com[2];
    temp[0] = (((.5464*((rnk[3][1]*rnk[3][1])+(rnk[3][2]*rnk[3][2])))+((.0030585
      *(cnk[3][0][2]*cnk[3][0][2]))+((.00045325*(cnk[3][0][1]*cnk[3][0][1]))+(
      .0030585*(cnk[3][0][0]*cnk[3][0][0])))))+((2.0519*((rnk[2][1]*rnk[2][1])+(
      rnk[2][2]*rnk[2][2])))+((.0132*(cnk[2][0][2]*cnk[2][0][2]))+((.001988*(
      cnk[1][0][1]*cnk[1][0][1]))+(.0132*(cnk[2][0][0]*cnk[2][0][0]))))));
    icm[0][0] = (1.811977140222+((((.5464*((rnk[4][1]*rnk[4][1])+(rnk[4][2]*
      rnk[4][2])))+((.0030585*(cnk[4][0][2]*cnk[4][0][2]))+((.00045325*(
      cnk[4][0][1]*cnk[4][0][1]))+(.0030585*(cnk[4][0][0]*cnk[4][0][0])))))+
      temp[0])-(24.0061*((com[1]*com[1])+(com[2]*com[2])))));
    temp[0] = ((((.0030585*(cnk[3][0][2]*cnk[3][1][2]))+((.00045325*(
      cnk[3][0][1]*cnk[3][1][1]))+(.0030585*(cnk[3][0][0]*cnk[3][1][0]))))-(
      .5464*(rnk[3][0]*rnk[3][1])))+(((.0132*(cnk[2][0][2]*cnk[2][1][2]))+((
      .001988*(cnk[1][0][1]*c1))+(.0132*(cnk[2][0][0]*cnk[2][1][0]))))-(2.0519*(
      rnk[2][0]*rnk[2][1]))));
    icm[0][1] = (.00417628450800001+((24.0061*(com[0]*com[1]))+((((.0030585*(
      cnk[4][0][2]*cnk[4][1][2]))+((.00045325*(cnk[4][0][1]*cnk[4][1][1]))+(
      .0030585*(cnk[4][0][0]*cnk[4][1][0]))))-(.5464*(rnk[4][0]*rnk[4][1])))+
      temp[0])));
    temp[0] = ((((.0030585*(cnk[3][0][2]*cnk[3][2][2]))+((.00045325*(
      cnk[3][0][1]*cnk[3][2][1]))+(.0030585*(cnk[3][0][0]*cnk[3][2][0]))))-(
      .5464*(rnk[3][0]*rnk[3][2])))+((((.0132*(cnk[2][0][2]*cnk[2][2][2]))+((
      .001988*(cnk[1][0][1]*cnk[1][2][1]))+(.0132*(cnk[2][0][0]*cnk[2][2][0]))))
      -(2.0519*(rnk[2][0]*rnk[2][2])))-.000812083922000001));
    icm[0][2] = ((24.0061*(com[0]*com[2]))+((((.0030585*(cnk[4][0][2]*
      cnk[4][2][2]))+((.00045325*(cnk[4][0][1]*cnk[4][2][1]))+(.0030585*(
      cnk[4][0][0]*cnk[4][2][0]))))-(.5464*(rnk[4][0]*rnk[4][2])))+temp[0]));
    icm[1][0] = icm[0][1];
    temp[0] = (((.5464*((rnk[3][0]*rnk[3][0])+(rnk[3][2]*rnk[3][2])))+((.0030585
      *(cnk[3][1][2]*cnk[3][1][2]))+((.00045325*(cnk[3][1][1]*cnk[3][1][1]))+(
      .0030585*(cnk[3][1][0]*cnk[3][1][0])))))+((2.0519*((rnk[2][0]*rnk[2][0])+(
      rnk[2][2]*rnk[2][2])))+((.0132*(cnk[2][1][2]*cnk[2][1][2]))+((.001988*(c1*
      c1))+(.0132*(cnk[2][1][0]*cnk[2][1][0]))))));
    icm[1][1] = (.6421074253+((((.5464*((rnk[4][0]*rnk[4][0])+(rnk[4][2]*
      rnk[4][2])))+((.0030585*(cnk[4][1][2]*cnk[4][1][2]))+((.00045325*(
      cnk[4][1][1]*cnk[4][1][1]))+(.0030585*(cnk[4][1][0]*cnk[4][1][0])))))+
      temp[0])-(24.0061*((com[0]*com[0])+(com[2]*com[2])))));
    temp[0] = ((((.0030585*(cnk[3][1][2]*cnk[3][2][2]))+((.00045325*(
      cnk[3][1][1]*cnk[3][2][1]))+(.0030585*(cnk[3][1][0]*cnk[3][2][0]))))-(
      .5464*(rnk[3][1]*rnk[3][2])))+(((.0132*(cnk[2][1][2]*cnk[2][2][2]))+((
      .001988*(cnk[1][2][1]*c1))+(.0132*(cnk[2][1][0]*cnk[2][2][0]))))-(2.0519*(
      rnk[2][1]*rnk[2][2]))));
    icm[1][2] = (.175816223564+((24.0061*(com[1]*com[2]))+((((.0030585*(
      cnk[4][1][2]*cnk[4][2][2]))+((.00045325*(cnk[4][1][1]*cnk[4][2][1]))+(
      .0030585*(cnk[4][1][0]*cnk[4][2][0]))))-(.5464*(rnk[4][1]*rnk[4][2])))+
      temp[0])));
    icm[2][0] = icm[0][2];
    icm[2][1] = icm[1][2];
    temp[0] = (((.5464*((rnk[3][0]*rnk[3][0])+(rnk[3][1]*rnk[3][1])))+((.0030585
      *(cnk[3][2][2]*cnk[3][2][2]))+((.00045325*(cnk[3][2][1]*cnk[3][2][1]))+(
      .0030585*(cnk[3][2][0]*cnk[3][2][0])))))+((2.0519*((rnk[2][0]*rnk[2][0])+(
      rnk[2][1]*rnk[2][1])))+((.0132*(cnk[2][2][2]*cnk[2][2][2]))+((.001988*(
      cnk[1][2][1]*cnk[1][2][1]))+(.0132*(cnk[2][2][0]*cnk[2][2][0]))))));
    icm[2][2] = (1.76084248287+((((.5464*((rnk[4][0]*rnk[4][0])+(rnk[4][1]*
      rnk[4][1])))+((.0030585*(cnk[4][2][2]*cnk[4][2][2]))+((.00045325*(
      cnk[4][2][1]*cnk[4][2][1]))+(.0030585*(cnk[4][2][0]*cnk[4][2][0])))))+
      temp[0])-(24.0061*((com[0]*com[0])+(com[1]*com[1])))));
/*
 Used -0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain   90 adds/subtracts/negates
                    168 multiplies
                      0 divides
                     19 assignments
*/
}

void sdpos(int body,
    double pt[3],
    double loc[3])
{
/*
Return inertial frame location of a point on a body.

*/
    double pv[3];

    if (sdchkbnum(21,body) != 0) {
        return;
    }
    if ((roustate != 2) && (roustate != 3)) {
        sdseterr(21,23);
        return;
    }
    if (body  ==  -1) {
        loc[0] = pt[0];
        loc[1] = pt[1];
        loc[2] = pt[2];
    } else {
        pv[0] = rnb[body][0]+pt[0]*cnb[body][0][0]+pt[1]*cnb[body][0][1]+pt[2]*
          cnb[body][0][2];
        pv[1] = rnb[body][1]+pt[0]*cnb[body][1][0]+pt[1]*cnb[body][1][1]+pt[2]*
          cnb[body][1][2];
        pv[2] = rnb[body][2]+pt[0]*cnb[body][2][0]+pt[1]*cnb[body][2][1]+pt[2]*
          cnb[body][2][2];
        loc[0] = pv[0];
        loc[1] = pv[1];
        loc[2] = pv[2];
    }
}

void sdvel(int body,
    double pt[3],
    double velo[3])
{
/*
Return inertial frame velocity of a point on a body.

*/
    double pv[3];

    if (sdchkbnum(22,body) != 0) {
        return;
    }
    if ((roustate != 2) && (roustate != 3)) {
        sdseterr(22,23);
        return;
    }
    if (body  ==  -1) {
        velo[0] = 0.;
        velo[1] = 0.;
        velo[2] = 0.;
    } else {
        pv[0] = wb[body][1]*pt[2]-wb[body][2]*pt[1];
        pv[1] = wb[body][2]*pt[0]-wb[body][0]*pt[2];
        pv[2] = wb[body][0]*pt[1]-wb[body][1]*pt[0];
        velo[0] = vnb[body][0]+pv[0]*cnb[body][0][0]+pv[1]*cnb[body][0][1]+pv[2]
          *cnb[body][0][2];
        velo[1] = vnb[body][1]+pv[0]*cnb[body][1][0]+pv[1]*cnb[body][1][1]+pv[2]
          *cnb[body][1][2];
        velo[2] = vnb[body][2]+pv[0]*cnb[body][2][0]+pv[1]*cnb[body][2][1]+pv[2]
          *cnb[body][2][2];
    }
}

void sdorient(int body,
    double dircos[3][3])
{
/*
Return orientation of body w.r.t. ground frame.

*/

    if (sdchkbnum(23,body) != 0) {
        return;
    }
    if ((roustate != 2) && (roustate != 3)) {
        sdseterr(23,23);
        return;
    }
    if (body == -1) {
        dircos[0][0] = 1.;
        dircos[0][1] = 0.;
        dircos[0][2] = 0.;
        dircos[1][0] = 0.;
        dircos[1][1] = 1.;
        dircos[1][2] = 0.;
        dircos[2][0] = 0.;
        dircos[2][1] = 0.;
        dircos[2][2] = 1.;
    } else {
        dircos[0][0] = cnb[body][0][0];
        dircos[0][1] = cnb[body][0][1];
        dircos[0][2] = cnb[body][0][2];
        dircos[1][0] = cnb[body][1][0];
        dircos[1][1] = cnb[body][1][1];
        dircos[1][2] = cnb[body][1][2];
        dircos[2][0] = cnb[body][2][0];
        dircos[2][1] = cnb[body][2][1];
        dircos[2][2] = cnb[body][2][2];
    }
}

void sdangvel(int body,
    double avel[3])
{
/*
Return angular velocity of the body.

*/

    if (sdchkbnum(24,body) != 0) {
        return;
    }
    if ((roustate != 2) && (roustate != 3)) {
        sdseterr(24,23);
        return;
    }
    if (body == -1) {
        avel[0] = 0.;
        avel[1] = 0.;
        avel[2] = 0.;
    } else {
        avel[0] = wb[body][0];
        avel[1] = wb[body][1];
        avel[2] = wb[body][2];
    }
}

void sdtrans(int frbod,
    double ivec[3],
    int tobod,
    double ovec[3])
{
/*
Transform ivec from frbod frame to tobod frame.

*/
    double pv[3];

    if (sdchkbnum(25,frbod) != 0) {
        return;
    }
    if (sdchkbnum(25,tobod) != 0) {
        return;
    }
    if ((roustate != 2) && (roustate != 3)) {
        sdseterr(25,23);
        return;
    }
    if (frbod == tobod) {
        sdvcopy(ivec,ovec);
        return;
    }
    if (frbod == -1) {
        sdvcopy(ivec,pv);
        ovec[0] = pv[0]*cnb[tobod][0][0]+pv[1]*cnb[tobod][1][0]+pv[2]*cnb[tobod
          ][2][0];
        ovec[1] = pv[0]*cnb[tobod][0][1]+pv[1]*cnb[tobod][1][1]+pv[2]*cnb[tobod
          ][2][1];
        ovec[2] = pv[0]*cnb[tobod][0][2]+pv[1]*cnb[tobod][1][2]+pv[2]*cnb[tobod
          ][2][2];
        return;
    }
    if (tobod == -1) {
        sdvcopy(ivec,pv);
        ovec[0] = pv[0]*cnb[frbod][0][0]+pv[1]*cnb[frbod][0][1]+pv[2]*cnb[frbod
          ][0][2];
        ovec[1] = pv[0]*cnb[frbod][1][0]+pv[1]*cnb[frbod][1][1]+pv[2]*cnb[frbod
          ][1][2];
        ovec[2] = pv[0]*cnb[frbod][2][0]+pv[1]*cnb[frbod][2][1]+pv[2]*cnb[frbod
          ][2][2];
        return;
    }
    pv[0] = ivec[0]*cnb[frbod][0][0]+ivec[1]*cnb[frbod][0][1]+ivec[2]*cnb[frbod
      ][0][2];
    pv[1] = ivec[0]*cnb[frbod][1][0]+ivec[1]*cnb[frbod][1][1]+ivec[2]*cnb[frbod
      ][1][2];
    pv[2] = ivec[0]*cnb[frbod][2][0]+ivec[1]*cnb[frbod][2][1]+ivec[2]*cnb[frbod
      ][2][2];
    ovec[0] = pv[0]*cnb[tobod][0][0]+pv[1]*cnb[tobod][1][0]+pv[2]*cnb[tobod][2][
      0];
    ovec[1] = pv[0]*cnb[tobod][0][1]+pv[1]*cnb[tobod][1][1]+pv[2]*cnb[tobod][2][
      1];
    ovec[2] = pv[0]*cnb[tobod][0][2]+pv[1]*cnb[tobod][1][2]+pv[2]*cnb[tobod][2][
      2];
}

void sdrel2cart(int coord,
    int body,
    double point[3],
    double linchg[3],
    double rotchg[3])
{
/* Return derivative of pt loc and body orient w.r.t. hinge rate
*/
    int x,i,gnd;
    double lin[3],pv[3];
    double pink[3],ptvec[3];

    if ((coord < 0) || (coord > 4)) {
        sdseterr(59,45);
        return;
    }
    if (sdchkbnum(59,body) != 0) {
        return;
    }
    if ((roustate != 2) && (roustate != 3)) {
        sdseterr(59,23);
        return;
    }
    gnd = -1;
    sdvset(0.,0.,0.,linchg);
    sdvset(0.,0.,0.,rotchg);
    i = body;
    for (;;) {
        if (i == gnd) {
            return;
        }
        x = firstq[i];
        if (x <= coord) {
            if (coord >= x+njntdof[i]) {
                return;
            }
            break;
        }
        i = inb[i];
    }
    sddoping();
    for (i = 0; i < 3; i++) {
        pink[i] = ping[coord][i];
        lin[i] = hngpt[coord][i];
    }
    sdtrans(gnd,pink,body,pink);
    if (trans[coord] != 0) {
        sdvcopy(pink,linchg);
    } else {
        sdvcopy(pink,rotchg);
        sdpos(body,point,ptvec);
        sdvsub(ptvec,lin,ptvec);
        sdtrans(gnd,ptvec,body,ptvec);
        sdvcross(pink,ptvec,linchg);
    }
}

void sdacc(int body,
    double pt[3],
    double accel[3])
{
/*
Return linear acceleration a point of the specified body.

*/
    double pv[3];

    if (sdchkbnum(32,body) != 0) {
        return;
    }
    if (roustate != 3) {
        sdseterr(32,24);
        return;
    }
    if (body  ==  -1) {
        accel[0] = 0.;
        accel[1] = 0.;
        accel[2] = 0.;
    } else {
        pv[0] = pt[0]*dyad[body][0][0]+pt[1]*dyad[body][0][1]+pt[2]*dyad[body][0
          ][2];
        pv[1] = pt[0]*dyad[body][1][0]+pt[1]*dyad[body][1][1]+pt[2]*dyad[body][1
          ][2];
        pv[2] = pt[0]*dyad[body][2][0]+pt[1]*dyad[body][2][1]+pt[2]*dyad[body][2
          ][2];
        accel[0] = anb[body][0]+pv[0]*cnb[body][0][0]+pv[1]*cnb[body][0][1]+pv[2
          ]*cnb[body][0][2];
        accel[1] = anb[body][1]+pv[0]*cnb[body][1][0]+pv[1]*cnb[body][1][1]+pv[2
          ]*cnb[body][1][2];
        accel[2] = anb[body][2]+pv[0]*cnb[body][2][0]+pv[1]*cnb[body][2][1]+pv[2
          ]*cnb[body][2][2];
    }
}

void sdangacc(int body,
    double aacc[3])
{
/*
Return angular acceleration of the body.

*/

    if (sdchkbnum(33,body) != 0) {
        return;
    }
    if (roustate != 3) {
        sdseterr(33,24);
        return;
    }
    if (body == -1) {
        aacc[0] = 0.;
        aacc[1] = 0.;
        aacc[2] = 0.;
    } else {
        aacc[0] = onb[body][0];
        aacc[1] = onb[body][1];
        aacc[2] = onb[body][2];
    }
}

void sdgrav(double gravin[3])
{

    sdseterr(1,19);
    roustate = 0;
}

void sdmass(int body,
    double massin)
{

    if (sdchkbnum(2,body) != 0) {
        return;
    }
    if (body == -1) {
        sdseterr(2,15);
        return;
    }
    if (mkq[body] != 0) {
        mk[body] = massin;
        mkq[body] = 3;
    } else {
        sdseterr(2,19);
    }
    roustate = 0;
}

void sdiner(int body,
    double inerin[3][3])
{
    int anyques;

    if (sdchkbnum(3,body) != 0) {
        return;
    }
    if (body == -1) {
        sdseterr(3,15);
        return;
    }
    anyques = 0;
    if (ikq[body][0][0]  !=  0) {
        ik[body][0][0] = inerin[0][0];
        ikq[body][0][0] = 3;
        anyques = 1;
    }
    if (ikq[body][0][1]  !=  0) {
        ik[body][0][1] = inerin[0][1];
        ikq[body][0][1] = 3;
        ik[body][1][0] = inerin[0][1];
        ikq[body][1][0] = 3;
        anyques = 1;
    }
    if (ikq[body][0][2]  !=  0) {
        ik[body][0][2] = inerin[0][2];
        ikq[body][0][2] = 3;
        ik[body][2][0] = inerin[0][2];
        ikq[body][2][0] = 3;
        anyques = 1;
    }
    if (ikq[body][1][1]  !=  0) {
        ik[body][1][1] = inerin[1][1];
        ikq[body][1][1] = 3;
        anyques = 1;
    }
    if (ikq[body][1][2]  !=  0) {
        ik[body][1][2] = inerin[1][2];
        ikq[body][1][2] = 3;
        ik[body][2][1] = inerin[1][2];
        ikq[body][2][1] = 3;
        anyques = 1;
    }
    if (ikq[body][2][2]  !=  0) {
        ik[body][2][2] = inerin[2][2];
        ikq[body][2][2] = 3;
        anyques = 1;
    }
    if (anyques == 0) {
        sdseterr(3,19);
    }
    roustate = 0;
}

void sdbtj(int joint,
    double btjin[3])
{
    int anyques;

    if (sdchkjnum(4,joint) != 0) {
        return;
    }
    anyques = 0;
    if (rkq[joint][0]  !=  0) {
        rk[joint][0] = btjin[0];
        rkq[joint][0] = 3;
        anyques = 1;
    }
    if (rkq[joint][1]  !=  0) {
        rk[joint][1] = btjin[1];
        rkq[joint][1] = 3;
        anyques = 1;
    }
    if (rkq[joint][2]  !=  0) {
        rk[joint][2] = btjin[2];
        rkq[joint][2] = 3;
        anyques = 1;
    }
    if (anyques == 0) {
        sdseterr(4,19);
    }
    roustate = 0;
}

void sditj(int joint,
    double itjin[3])
{
    int anyques;

    if (sdchkjnum(5,joint) != 0) {
        return;
    }
    anyques = 0;
    if (riq[joint][0]  !=  0) {
        ri[joint][0] = itjin[0];
        riq[joint][0] = 3;
        anyques = 1;
    }
    if (riq[joint][1]  !=  0) {
        ri[joint][1] = itjin[1];
        riq[joint][1] = 3;
        anyques = 1;
    }
    if (riq[joint][2]  !=  0) {
        ri[joint][2] = itjin[2];
        riq[joint][2] = 3;
        anyques = 1;
    }
    if (anyques == 0) {
        sdseterr(5,19);
    }
    roustate = 0;
}

void sdpin(int joint,
    int pinno,
    double pinin[3])
{
    int anyques,offs;

    if (sdchkjpin(6,joint,pinno) != 0) {
        return;
    }
    anyques = 0;
    offs = firstq[joint]+pinno;
    if (jtype[joint] == 21) {
        offs = offs+3;
    }
    if (jtype[joint] == 11) {
        offs = offs+1;
    }
    if (pinq[offs][0]  !=  0) {
        pin[offs][0] = pinin[0];
        pinq[offs][0] = 3;
        anyques = 1;
    }
    if (pinq[offs][1]  !=  0) {
        pin[offs][1] = pinin[1];
        pinq[offs][1] = 3;
        anyques = 1;
    }
    if (pinq[offs][2]  !=  0) {
        pin[offs][2] = pinin[2];
        pinq[offs][2] = 3;
        anyques = 1;
    }
    if (anyques == 0) {
        sdseterr(6,19);
    }
    roustate = 0;
}

void sdpres(int joint,
    int axis,
    int presin)
{
    int anyques;

    if (sdchkjaxis(37,joint,axis) != 0) {
        return;
    }
    if ((presin != 0) && (presin != 1)) {
        sdseterr(37,20);
    }
    anyques = 0;
    if (presq[sdindx(joint,axis)]  !=  0) {
        if (presin  !=  0) {
            pres[sdindx(joint,axis)] = 1.;
        } else {
            pres[sdindx(joint,axis)] = 0.;
        }
        presq[sdindx(joint,axis)] = 3;
        anyques = 1;
    }
    if (anyques == 0) {
        sdseterr(37,19);
    }
    wwflg = 0;
}

void sdconschg(void)
{

    wwflg = 0;
}

void sdstab(double velin,
    double posin)
{

    stabvel = velin;
    stabvelq = 3;
    stabpos = posin;
    stabposq = 3;
}

void sdgetgrav(double gravout[3])
{

    gravout[0] = grav[0];
    gravout[1] = grav[1];
    gravout[2] = grav[2];
}

void sdgetmass(int body,
    double *massout)
{

    if (sdchkbnum(40,body) != 0) {
        return;
    }
    if (body == -1) {
        sdseterr(40,15);
        return;
    }
    *massout = mk[body];
}

void sdgetiner(int body,
    double inerout[3][3])
{

    if (sdchkbnum(41,body) != 0) {
        return;
    }
    if (body == -1) {
        sdseterr(41,15);
        return;
    }
    inerout[0][0] = ik[body][0][0];
    inerout[0][1] = ik[body][0][1];
    inerout[0][2] = ik[body][0][2];
    inerout[1][0] = ik[body][1][0];
    inerout[1][1] = ik[body][1][1];
    inerout[1][2] = ik[body][1][2];
    inerout[2][0] = ik[body][2][0];
    inerout[2][1] = ik[body][2][1];
    inerout[2][2] = ik[body][2][2];
}

void sdgetbtj(int joint,
    double btjout[3])
{

    if (sdchkjnum(42,joint) != 0) {
        return;
    }
    btjout[0] = rk[joint][0];
    btjout[1] = rk[joint][1];
    btjout[2] = rk[joint][2];
}

void sdgetitj(int joint,
    double itjout[3])
{

    if (sdchkjnum(43,joint) != 0) {
        return;
    }
    itjout[0] = ri[joint][0];
    itjout[1] = ri[joint][1];
    itjout[2] = ri[joint][2];
}

void sdgetpin(int joint,
    int pinno,
    double pinout[3])
{
    int offs;

    if (sdchkjpin(44,joint,pinno) != 0) {
        return;
    }
    offs = firstq[joint]+pinno;
    if (jtype[joint] == 21) {
        offs = offs+3;
    }
    if (jtype[joint] == 11) {
        offs = offs+1;
    }
    pinout[0] = pin[offs][0];
    pinout[1] = pin[offs][1];
    pinout[2] = pin[offs][2];
}

void sdgetpres(int joint,
    int axis,
    int *presout)
{

    if (sdchkjaxis(45,joint,axis) != 0) {
        return;
    }
    if (pres[sdindx(joint,axis)]  !=  0.) {
        *presout = 1;
    } else {
        *presout = 0;
    }
}

void sdgetstab(double *velout,
    double *posout)
{

    *velout = stabvel;
    *posout = stabpos;
}

void sdinfo(int info[50])
{

    info[0] = ground;
    info[1] = nbod;
    info[2] = ndof;
    info[3] = ncons;
    info[4] = nloop;
    info[5] = nldof;
    info[6] = nloopc;
    info[7] = nball;
    info[8] = nlball;
    info[9] = npres;
    info[10] = nuser;
    info[11] = 0;
/* info entries from 12-49 are reserved */
}

void sdjnt(int joint,
    int info[50],
    int tran[6])
{
    int i,offs;

    if (sdchkjnum(48,joint) != 0) {
        return;
    }
    info[0] = jtype[joint];
    info[1] = 0;
    offs = 0;
    info[2] = inb[joint];
    info[3] = outb[joint];
    info[4] = njntdof[joint];
    info[5] = njntc[joint];
    info[6] = njntp[joint];
    info[7] = firstq[joint];
    info[8] = ballq[joint];
    info[9] = firstm[joint];
    info[10] = firstp[joint];
/* info entries from 11-49 are reserved */

    for (i = 0; i <= 5; i++) {
        if (i  <  njntdof[joint]) {
            tran[i] = trans[offs+firstq[joint]+i];
        } else {
            tran[i] = -1;
        }
    }
}

void sdcons(int consno,
    int info[50])
{

    if (sdchkucnum(49,consno) != 0) {
        return;
    }
/* There are no user constraints in this problem. */
}

void sdgentime(int *gentm)
{

    *gentm = 165748;
}
/*
Done. CPU seconds used: 0.09  Memory used: 1687552 bytes.
Equation complexity:
  sdstate:   297 adds   384 multiplies     0 divides   480 assignments
  sdderiv:  1030 adds  1343 multiplies    19 divides   900 assignments
  sdresid:   366 adds   344 multiplies     0 divides   337 assignments
  sdreac:    278 adds   159 multiplies     0 divides   138 assignments
  sdmom:      71 adds   127 multiplies     0 divides    11 assignments
  sdsys:      90 adds   168 multiplies     0 divides    19 assignments
*/
