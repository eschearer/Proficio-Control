/*
Generated 24-May-2007 16:22:11 by SD/FAST, Order(N) formulation
(sdfast B.2.8 #30123) on machine ID unknown
Copyright (c) 1990-1997 Symbolic Dynamics, Inc.
Copyright (c) 1990-1997 Parametric Technology Corp.
RESTRICTED RIGHTS LEGEND: Use, duplication, or disclosure by the U.S.
Government is subject to restrictions as set forth in subparagraph
(c)(1)(ii) of the Rights in Technical Data and Computer Software
clause at DFARS 52.227-7013 and similar clauses in the FAR and NASA
FAR Supplement.  Symbolic Dynamics, Inc., Mountain View, CA 94041


ROADMAP (../../model/trunk/dynsim/src/modelinv.sd)

Bodies         Inb
No  Name       body Joint type  Coords q         Multipliers
--- ---------- ---- ----------- ---------------- -----------------------
 -1 $ground                                     |
  0 thorax      -1  Weld                        |
  1 clavicle_1   0  Weld                        |
  2 clavicle_2   1  Weld                        |
  3 clavicle_r   2  Weld                        |
  4 scapula_1    3  Weld                        |
  5 scapula_2    4  Weld                        |
  6 scapula_r    5  Weld                        |
  7 humerus_1    6  Pin           0p            |  0p
  8 humerus_2    7  Pin           1p            |  1p
  9 humerus_r    8  Pin           2p            |  2p
 10 ulna_r       9  Pin           3p            |  3p
 11 radius_r    10  Pin           4p            |  4p

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
    double perr_[5],verr_[5],aerr_[5],mult_[5],ufk_[12][3],utk_[12][3],mfk_[12][
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
    double w00w11_[12],w00w22_[12],w11w22_[12],ww_[5][5],qraux_[5];
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
    int wmap_[5],multmap_[5],jpvt_[5],wsiz_,wrank_;
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
    /* ncons */ 5,
    /* nloop */ 0,
    /* nldof */ 0,
    /* nloopc */ 0,
    /* nball */ 0,
    /* nlball */ 0,
    /* npres */ 5,
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
    /* njntp[7] */ 1,
    /* njntp[8] */ 1,
    /* njntp[9] */ 1,
    /* njntp[10] */ 1,
    /* njntp[11] */ 1,
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
    /* firstp[7] */ 0,
    /* firstp[8] */ 1,
    /* firstp[9] */ 2,
    /* firstp[10] */ 3,
    /* firstp[11] */ 4,
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
    /* ik[10][0][0] */ .006117,
    /* ik[10][0][1] */ 0.,
    /* ik[10][0][2] */ 0.,
    /* ik[10][1][0] */ 0.,
    /* ik[10][1][1] */ .0009065,
    /* ik[10][1][2] */ 0.,
    /* ik[10][2][0] */ 0.,
    /* ik[10][2][1] */ 0.,
    /* ik[10][2][2] */ .006117,
    /* ik[11][0][0] */ .006117,
    /* ik[11][0][1] */ 0.,
    /* ik[11][0][2] */ 0.,
    /* ik[11][1][0] */ 0.,
    /* ik[11][1][1] */ .0009065,
    /* ik[11][1][2] */ 0.,
    /* ik[11][2][0] */ 0.,
    /* ik[11][2][1] */ 0.,
    /* ik[11][2][2] */ .006117,

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
    /* pres[0] */ 1.,
    /* pres[1] */ 1.,
    /* pres[2] */ 1.,
    /* pres[3] */ 1.,
    /* pres[4] */ 1.,

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
    /* gravq[0] */ 3,
    /* gravq[1] */ 3,
    /* gravq[2] */ 3,
    /* mkq[0] */ 3,
    /* mkq[1] */ 3,
    /* mkq[2] */ 3,
    /* mkq[3] */ 3,
    /* mkq[4] */ 3,
    /* mkq[5] */ 3,
    /* mkq[6] */ 3,
    /* mkq[7] */ 3,
    /* mkq[8] */ 3,
    /* mkq[9] */ 3,
    /* mkq[10] */ 3,
    /* mkq[11] */ 3,
    /* ikq[0][0][0] */ 3,
    /* ikq[0][0][1] */ 3,
    /* ikq[0][0][2] */ 3,
    /* ikq[0][1][0] */ 3,
    /* ikq[0][1][1] */ 3,
    /* ikq[0][1][2] */ 3,
    /* ikq[0][2][0] */ 3,
    /* ikq[0][2][1] */ 3,
    /* ikq[0][2][2] */ 3,
    /* ikq[1][0][0] */ 3,
    /* ikq[1][0][1] */ 3,
    /* ikq[1][0][2] */ 3,
    /* ikq[1][1][0] */ 3,
    /* ikq[1][1][1] */ 3,
    /* ikq[1][1][2] */ 3,
    /* ikq[1][2][0] */ 3,
    /* ikq[1][2][1] */ 3,
    /* ikq[1][2][2] */ 3,
    /* ikq[2][0][0] */ 3,
    /* ikq[2][0][1] */ 3,
    /* ikq[2][0][2] */ 3,
    /* ikq[2][1][0] */ 3,
    /* ikq[2][1][1] */ 3,
    /* ikq[2][1][2] */ 3,
    /* ikq[2][2][0] */ 3,
    /* ikq[2][2][1] */ 3,
    /* ikq[2][2][2] */ 3,
    /* ikq[3][0][0] */ 3,
    /* ikq[3][0][1] */ 3,
    /* ikq[3][0][2] */ 3,
    /* ikq[3][1][0] */ 3,
    /* ikq[3][1][1] */ 3,
    /* ikq[3][1][2] */ 3,
    /* ikq[3][2][0] */ 3,
    /* ikq[3][2][1] */ 3,
    /* ikq[3][2][2] */ 3,
    /* ikq[4][0][0] */ 3,
    /* ikq[4][0][1] */ 3,
    /* ikq[4][0][2] */ 3,
    /* ikq[4][1][0] */ 3,
    /* ikq[4][1][1] */ 3,
    /* ikq[4][1][2] */ 3,
    /* ikq[4][2][0] */ 3,
    /* ikq[4][2][1] */ 3,
    /* ikq[4][2][2] */ 3,
    /* ikq[5][0][0] */ 3,
    /* ikq[5][0][1] */ 3,
    /* ikq[5][0][2] */ 3,
    /* ikq[5][1][0] */ 3,
    /* ikq[5][1][1] */ 3,
    /* ikq[5][1][2] */ 3,
    /* ikq[5][2][0] */ 3,
    /* ikq[5][2][1] */ 3,
    /* ikq[5][2][2] */ 3,
    /* ikq[6][0][0] */ 3,
    /* ikq[6][0][1] */ 3,
    /* ikq[6][0][2] */ 3,
    /* ikq[6][1][0] */ 3,
    /* ikq[6][1][1] */ 3,
    /* ikq[6][1][2] */ 3,
    /* ikq[6][2][0] */ 3,
    /* ikq[6][2][1] */ 3,
    /* ikq[6][2][2] */ 3,
    /* ikq[7][0][0] */ 3,
    /* ikq[7][0][1] */ 3,
    /* ikq[7][0][2] */ 3,
    /* ikq[7][1][0] */ 3,
    /* ikq[7][1][1] */ 3,
    /* ikq[7][1][2] */ 3,
    /* ikq[7][2][0] */ 3,
    /* ikq[7][2][1] */ 3,
    /* ikq[7][2][2] */ 3,
    /* ikq[8][0][0] */ 3,
    /* ikq[8][0][1] */ 3,
    /* ikq[8][0][2] */ 3,
    /* ikq[8][1][0] */ 3,
    /* ikq[8][1][1] */ 3,
    /* ikq[8][1][2] */ 3,
    /* ikq[8][2][0] */ 3,
    /* ikq[8][2][1] */ 3,
    /* ikq[8][2][2] */ 3,
    /* ikq[9][0][0] */ 3,
    /* ikq[9][0][1] */ 3,
    /* ikq[9][0][2] */ 3,
    /* ikq[9][1][0] */ 3,
    /* ikq[9][1][1] */ 3,
    /* ikq[9][1][2] */ 3,
    /* ikq[9][2][0] */ 3,
    /* ikq[9][2][1] */ 3,
    /* ikq[9][2][2] */ 3,
    /* ikq[10][0][0] */ 3,
    /* ikq[10][0][1] */ 3,
    /* ikq[10][0][2] */ 3,
    /* ikq[10][1][0] */ 3,
    /* ikq[10][1][1] */ 3,
    /* ikq[10][1][2] */ 3,
    /* ikq[10][2][0] */ 3,
    /* ikq[10][2][1] */ 3,
    /* ikq[10][2][2] */ 3,
    /* ikq[11][0][0] */ 3,
    /* ikq[11][0][1] */ 3,
    /* ikq[11][0][2] */ 3,
    /* ikq[11][1][0] */ 3,
    /* ikq[11][1][1] */ 3,
    /* ikq[11][1][2] */ 3,
    /* ikq[11][2][0] */ 3,
    /* ikq[11][2][1] */ 3,
    /* ikq[11][2][2] */ 3,
    /* pinq[0][0] */ 3,
    /* pinq[0][1] */ 3,
    /* pinq[0][2] */ 3,
    /* pinq[1][0] */ 3,
    /* pinq[1][1] */ 3,
    /* pinq[1][2] */ 3,
    /* pinq[2][0] */ 3,
    /* pinq[2][1] */ 3,
    /* pinq[2][2] */ 3,
    /* pinq[3][0] */ 3,
    /* pinq[3][1] */ 3,
    /* pinq[3][2] */ 3,
    /* pinq[4][0] */ 3,
    /* pinq[4][1] */ 3,
    /* pinq[4][2] */ 3,
    /* rkq[0][0] */ 3,
    /* rkq[0][1] */ 3,
    /* rkq[0][2] */ 3,
    /* rkq[1][0] */ 3,
    /* rkq[1][1] */ 3,
    /* rkq[1][2] */ 3,
    /* rkq[2][0] */ 3,
    /* rkq[2][1] */ 3,
    /* rkq[2][2] */ 3,
    /* rkq[3][0] */ 3,
    /* rkq[3][1] */ 3,
    /* rkq[3][2] */ 3,
    /* rkq[4][0] */ 3,
    /* rkq[4][1] */ 3,
    /* rkq[4][2] */ 3,
    /* rkq[5][0] */ 3,
    /* rkq[5][1] */ 3,
    /* rkq[5][2] */ 3,
    /* rkq[6][0] */ 3,
    /* rkq[6][1] */ 3,
    /* rkq[6][2] */ 3,
    /* rkq[7][0] */ 3,
    /* rkq[7][1] */ 3,
    /* rkq[7][2] */ 3,
    /* rkq[8][0] */ 3,
    /* rkq[8][1] */ 3,
    /* rkq[8][2] */ 3,
    /* rkq[9][0] */ 3,
    /* rkq[9][1] */ 3,
    /* rkq[9][2] */ 3,
    /* rkq[10][0] */ 3,
    /* rkq[10][1] */ 3,
    /* rkq[10][2] */ 3,
    /* rkq[11][0] */ 3,
    /* rkq[11][1] */ 3,
    /* rkq[11][2] */ 3,
    /* riq[0][0] */ 3,
    /* riq[0][1] */ 3,
    /* riq[0][2] */ 3,
    /* riq[1][0] */ 3,
    /* riq[1][1] */ 3,
    /* riq[1][2] */ 3,
    /* riq[2][0] */ 3,
    /* riq[2][1] */ 3,
    /* riq[2][2] */ 3,
    /* riq[3][0] */ 3,
    /* riq[3][1] */ 3,
    /* riq[3][2] */ 3,
    /* riq[4][0] */ 3,
    /* riq[4][1] */ 3,
    /* riq[4][2] */ 3,
    /* riq[5][0] */ 3,
    /* riq[5][1] */ 3,
    /* riq[5][2] */ 3,
    /* riq[6][0] */ 3,
    /* riq[6][1] */ 3,
    /* riq[6][2] */ 3,
    /* riq[7][0] */ 3,
    /* riq[7][1] */ 3,
    /* riq[7][2] */ 3,
    /* riq[8][0] */ 3,
    /* riq[8][1] */ 3,
    /* riq[8][2] */ 3,
    /* riq[9][0] */ 3,
    /* riq[9][1] */ 3,
    /* riq[9][2] */ 3,
    /* riq[10][0] */ 3,
    /* riq[10][1] */ 3,
    /* riq[10][2] */ 3,
    /* riq[11][0] */ 3,
    /* riq[11][1] */ 3,
    /* riq[11][2] */ 3,
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

    sumsq = ((pin[0][2]*pin[0][2])+((pin[0][0]*pin[0][0])+(pin[0][1]*pin[0][1]))
      );
    if ((sumsq < 1e-10)  ) {
        norminv = 0.;
        sdseterr(7,1);
    } else {
        norminv = (1./sqrt(sumsq));
    }
    pin[0][0] = (norminv*pin[0][0]);
    pin[0][1] = (norminv*pin[0][1]);
    pin[0][2] = (norminv*pin[0][2]);
    sumsq = ((pin[1][2]*pin[1][2])+((pin[1][0]*pin[1][0])+(pin[1][1]*pin[1][1]))
      );
    if ((sumsq < 1e-10)  ) {
        norminv = 0.;
        sdseterr(7,1);
    } else {
        norminv = (1./sqrt(sumsq));
    }
    pin[1][0] = (norminv*pin[1][0]);
    pin[1][1] = (norminv*pin[1][1]);
    pin[1][2] = (norminv*pin[1][2]);
    sumsq = ((pin[2][2]*pin[2][2])+((pin[2][0]*pin[2][0])+(pin[2][1]*pin[2][1]))
      );
    if ((sumsq < 1e-10)  ) {
        norminv = 0.;
        sdseterr(7,1);
    } else {
        norminv = (1./sqrt(sumsq));
    }
    pin[2][0] = (norminv*pin[2][0]);
    pin[2][1] = (norminv*pin[2][1]);
    pin[2][2] = (norminv*pin[2][2]);
    sumsq = ((pin[3][2]*pin[3][2])+((pin[3][0]*pin[3][0])+(pin[3][1]*pin[3][1]))
      );
    if ((sumsq < 1e-10)  ) {
        norminv = 0.;
        sdseterr(7,1);
    } else {
        norminv = (1./sqrt(sumsq));
    }
    pin[3][0] = (norminv*pin[3][0]);
    pin[3][1] = (norminv*pin[3][1]);
    pin[3][2] = (norminv*pin[3][2]);
    sumsq = ((pin[4][2]*pin[4][2])+((pin[4][0]*pin[4][0])+(pin[4][1]*pin[4][1]))
      );
    if ((sumsq < 1e-10)  ) {
        norminv = 0.;
        sdseterr(7,1);
    } else {
        norminv = (1./sqrt(sumsq));
    }
    pin[4][0] = (norminv*pin[4][0]);
    pin[4][1] = (norminv*pin[4][1]);
    pin[4][2] = (norminv*pin[4][2]);

/* Zero out ping and hngpt */

    for (i = 0; i < 5; i++) {
        for (j = 0; j < 3; j++) {
            ping[i][j] = 0.;
            hngpt[i][j] = 0.;
        }
    }

/* Compute pseudobody-related constants */

    psmkg = (mk[6]+(mk[5]+(mk[4]+(mk[3]+(mk[2]+(mk[0]+mk[1]))))));
    rhead[0][0] = (ri[0][0]-rk[0][0]);
    rhead[0][1] = (ri[0][1]-rk[0][1]);
    rhead[0][2] = (ri[0][2]-rk[0][2]);
    rhead[1][0] = (rhead[0][0]+(ri[1][0]-rk[1][0]));
    rhead[1][1] = (rhead[0][1]+(ri[1][1]-rk[1][1]));
    rhead[1][2] = (rhead[0][2]+(ri[1][2]-rk[1][2]));
    rhead[2][0] = (rhead[1][0]+(ri[2][0]-rk[2][0]));
    rhead[2][1] = (rhead[1][1]+(ri[2][1]-rk[2][1]));
    rhead[2][2] = (rhead[1][2]+(ri[2][2]-rk[2][2]));
    rhead[3][0] = (rhead[2][0]+(ri[3][0]-rk[3][0]));
    rhead[3][1] = (rhead[2][1]+(ri[3][1]-rk[3][1]));
    rhead[3][2] = (rhead[2][2]+(ri[3][2]-rk[3][2]));
    rhead[4][0] = (rhead[3][0]+(ri[4][0]-rk[4][0]));
    rhead[4][1] = (rhead[3][1]+(ri[4][1]-rk[4][1]));
    rhead[4][2] = (rhead[3][2]+(ri[4][2]-rk[4][2]));
    rhead[5][0] = (rhead[4][0]+(ri[5][0]-rk[5][0]));
    rhead[5][1] = (rhead[4][1]+(ri[5][1]-rk[5][1]));
    rhead[5][2] = (rhead[4][2]+(ri[5][2]-rk[5][2]));
    rhead[6][0] = (rhead[5][0]+(ri[6][0]-rk[6][0]));
    rhead[6][1] = (rhead[5][1]+(ri[6][1]-rk[6][1]));
    rhead[6][2] = (rhead[5][2]+(ri[6][2]-rk[6][2]));
    if (psmkg != 0.) {
        psrcomg[0] = ((-((mk[6]*rhead[6][0])+((mk[5]*rhead[5][0])+((mk[4]*
          rhead[4][0])+((mk[3]*rhead[3][0])+((mk[2]*rhead[2][0])+((mk[0]*
          rhead[0][0])+(mk[1]*rhead[1][0]))))))))/psmkg);
        psrcomg[1] = ((-((mk[6]*rhead[6][1])+((mk[5]*rhead[5][1])+((mk[4]*
          rhead[4][1])+((mk[3]*rhead[3][1])+((mk[2]*rhead[2][1])+((mk[0]*
          rhead[0][1])+(mk[1]*rhead[1][1]))))))))/psmkg);
        psrcomg[2] = ((-((mk[6]*rhead[6][2])+((mk[5]*rhead[5][2])+((mk[4]*
          rhead[4][2])+((mk[3]*rhead[3][2])+((mk[2]*rhead[2][2])+((mk[0]*
          rhead[0][2])+(mk[1]*rhead[1][2]))))))))/psmkg);
    } else {
        psrcomg[0] = 0.;
        psrcomg[1] = 0.;
        psrcomg[2] = 0.;
    }
    rcom[0][0] = (psrcomg[0]+rhead[0][0]);
    rcom[0][1] = (psrcomg[1]+rhead[0][1]);
    rcom[0][2] = (psrcomg[2]+rhead[0][2]);
    rcom[1][0] = (psrcomg[0]+rhead[1][0]);
    rcom[1][1] = (psrcomg[1]+rhead[1][1]);
    rcom[1][2] = (psrcomg[2]+rhead[1][2]);
    rcom[2][0] = (psrcomg[0]+rhead[2][0]);
    rcom[2][1] = (psrcomg[1]+rhead[2][1]);
    rcom[2][2] = (psrcomg[2]+rhead[2][2]);
    rcom[3][0] = (psrcomg[0]+rhead[3][0]);
    rcom[3][1] = (psrcomg[1]+rhead[3][1]);
    rcom[3][2] = (psrcomg[2]+rhead[3][2]);
    rcom[4][0] = (psrcomg[0]+rhead[4][0]);
    rcom[4][1] = (psrcomg[1]+rhead[4][1]);
    rcom[4][2] = (psrcomg[2]+rhead[4][2]);
    rcom[5][0] = (psrcomg[0]+rhead[5][0]);
    rcom[5][1] = (psrcomg[1]+rhead[5][1]);
    rcom[5][2] = (psrcomg[2]+rhead[5][2]);
    rcom[6][0] = (psrcomg[0]+rhead[6][0]);
    rcom[6][1] = (psrcomg[1]+rhead[6][1]);
    rcom[6][2] = (psrcomg[2]+rhead[6][2]);
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
    psri[0][0] = (rcom[6][0]+ri[7][0]);
    psri[0][1] = (rcom[6][1]+ri[7][1]);
    psri[0][2] = (rcom[6][2]+ri[7][2]);
    mkrcomt[0][0][1] = -(mk[0]*rcom[0][2]);
    mkrcomt[0][0][2] = (mk[0]*rcom[0][1]);
    mkrcomt[0][1][0] = (mk[0]*rcom[0][2]);
    mkrcomt[0][1][2] = -(mk[0]*rcom[0][0]);
    mkrcomt[0][2][0] = -(mk[0]*rcom[0][1]);
    mkrcomt[0][2][1] = (mk[0]*rcom[0][0]);
    mkrcomt[1][0][1] = -(mk[1]*rcom[1][2]);
    mkrcomt[1][0][2] = (mk[1]*rcom[1][1]);
    mkrcomt[1][1][0] = (mk[1]*rcom[1][2]);
    mkrcomt[1][1][2] = -(mk[1]*rcom[1][0]);
    mkrcomt[1][2][0] = -(mk[1]*rcom[1][1]);
    mkrcomt[1][2][1] = (mk[1]*rcom[1][0]);
    mkrcomt[2][0][1] = -(mk[2]*rcom[2][2]);
    mkrcomt[2][0][2] = (mk[2]*rcom[2][1]);
    mkrcomt[2][1][0] = (mk[2]*rcom[2][2]);
    mkrcomt[2][1][2] = -(mk[2]*rcom[2][0]);
    mkrcomt[2][2][0] = -(mk[2]*rcom[2][1]);
    mkrcomt[2][2][1] = (mk[2]*rcom[2][0]);
    mkrcomt[3][0][1] = -(mk[3]*rcom[3][2]);
    mkrcomt[3][0][2] = (mk[3]*rcom[3][1]);
    mkrcomt[3][1][0] = (mk[3]*rcom[3][2]);
    mkrcomt[3][1][2] = -(mk[3]*rcom[3][0]);
    mkrcomt[3][2][0] = -(mk[3]*rcom[3][1]);
    mkrcomt[3][2][1] = (mk[3]*rcom[3][0]);
    mkrcomt[4][0][1] = -(mk[4]*rcom[4][2]);
    mkrcomt[4][0][2] = (mk[4]*rcom[4][1]);
    mkrcomt[4][1][0] = (mk[4]*rcom[4][2]);
    mkrcomt[4][1][2] = -(mk[4]*rcom[4][0]);
    mkrcomt[4][2][0] = -(mk[4]*rcom[4][1]);
    mkrcomt[4][2][1] = (mk[4]*rcom[4][0]);
    mkrcomt[5][0][1] = -(mk[5]*rcom[5][2]);
    mkrcomt[5][0][2] = (mk[5]*rcom[5][1]);
    mkrcomt[5][1][0] = (mk[5]*rcom[5][2]);
    mkrcomt[5][1][2] = -(mk[5]*rcom[5][0]);
    mkrcomt[5][2][0] = -(mk[5]*rcom[5][1]);
    mkrcomt[5][2][1] = (mk[5]*rcom[5][0]);
    mkrcomt[6][0][1] = -(mk[6]*rcom[6][2]);
    mkrcomt[6][0][2] = (mk[6]*rcom[6][1]);
    mkrcomt[6][1][0] = (mk[6]*rcom[6][2]);
    mkrcomt[6][1][2] = -(mk[6]*rcom[6][0]);
    mkrcomt[6][2][0] = -(mk[6]*rcom[6][1]);
    mkrcomt[6][2][1] = (mk[6]*rcom[6][0]);
    temp[0] = ((ik[4][0][0]-((mkrcomt[4][0][1]*rcom[4][2])-(mkrcomt[4][0][2]*
      rcom[4][1])))+((ik[3][0][0]-((mkrcomt[3][0][1]*rcom[3][2])-(
      mkrcomt[3][0][2]*rcom[3][1])))+((ik[2][0][0]-((mkrcomt[2][0][1]*rcom[2][2]
      )-(mkrcomt[2][0][2]*rcom[2][1])))+((ik[0][0][0]-((mkrcomt[0][0][1]*
      rcom[0][2])-(mkrcomt[0][0][2]*rcom[0][1])))+(ik[1][0][0]-((
      mkrcomt[1][0][1]*rcom[1][2])-(mkrcomt[1][0][2]*rcom[1][1])))))));
    psikg[0][0] = ((ik[6][0][0]-((mkrcomt[6][0][1]*rcom[6][2])-(mkrcomt[6][0][2]
      *rcom[6][1])))+((ik[5][0][0]-((mkrcomt[5][0][1]*rcom[5][2])-(
      mkrcomt[5][0][2]*rcom[5][1])))+temp[0]));
    psikg[0][1] = ((ik[6][0][1]-(mkrcomt[6][0][2]*rcom[6][0]))+((ik[5][0][1]-(
      mkrcomt[5][0][2]*rcom[5][0]))+((ik[4][0][1]-(mkrcomt[4][0][2]*rcom[4][0]))
      +((ik[3][0][1]-(mkrcomt[3][0][2]*rcom[3][0]))+((ik[2][0][1]-(
      mkrcomt[2][0][2]*rcom[2][0]))+((ik[0][0][1]-(mkrcomt[0][0][2]*rcom[0][0]))
      +(ik[1][0][1]-(mkrcomt[1][0][2]*rcom[1][0]))))))));
    psikg[0][2] = ((ik[6][0][2]+(mkrcomt[6][0][1]*rcom[6][0]))+((ik[5][0][2]+(
      mkrcomt[5][0][1]*rcom[5][0]))+((ik[4][0][2]+(mkrcomt[4][0][1]*rcom[4][0]))
      +((ik[3][0][2]+(mkrcomt[3][0][1]*rcom[3][0]))+((ik[2][0][2]+(
      mkrcomt[2][0][1]*rcom[2][0]))+((ik[0][0][2]+(mkrcomt[0][0][1]*rcom[0][0]))
      +(ik[1][0][2]+(mkrcomt[1][0][1]*rcom[1][0]))))))));
    psikg[1][0] = ((ik[6][1][0]+(mkrcomt[6][1][2]*rcom[6][1]))+((ik[5][1][0]+(
      mkrcomt[5][1][2]*rcom[5][1]))+((ik[4][1][0]+(mkrcomt[4][1][2]*rcom[4][1]))
      +((ik[3][1][0]+(mkrcomt[3][1][2]*rcom[3][1]))+((ik[2][1][0]+(
      mkrcomt[2][1][2]*rcom[2][1]))+((ik[0][1][0]+(mkrcomt[0][1][2]*rcom[0][1]))
      +(ik[1][1][0]+(mkrcomt[1][1][2]*rcom[1][1]))))))));
    temp[0] = ((ik[4][1][1]-((mkrcomt[4][1][2]*rcom[4][0])-(mkrcomt[4][1][0]*
      rcom[4][2])))+((ik[3][1][1]-((mkrcomt[3][1][2]*rcom[3][0])-(
      mkrcomt[3][1][0]*rcom[3][2])))+((ik[2][1][1]-((mkrcomt[2][1][2]*rcom[2][0]
      )-(mkrcomt[2][1][0]*rcom[2][2])))+((ik[0][1][1]-((mkrcomt[0][1][2]*
      rcom[0][0])-(mkrcomt[0][1][0]*rcom[0][2])))+(ik[1][1][1]-((
      mkrcomt[1][1][2]*rcom[1][0])-(mkrcomt[1][1][0]*rcom[1][2])))))));
    psikg[1][1] = ((ik[6][1][1]-((mkrcomt[6][1][2]*rcom[6][0])-(mkrcomt[6][1][0]
      *rcom[6][2])))+((ik[5][1][1]-((mkrcomt[5][1][2]*rcom[5][0])-(
      mkrcomt[5][1][0]*rcom[5][2])))+temp[0]));
    psikg[1][2] = ((ik[6][1][2]-(mkrcomt[6][1][0]*rcom[6][1]))+((ik[5][1][2]-(
      mkrcomt[5][1][0]*rcom[5][1]))+((ik[4][1][2]-(mkrcomt[4][1][0]*rcom[4][1]))
      +((ik[3][1][2]-(mkrcomt[3][1][0]*rcom[3][1]))+((ik[2][1][2]-(
      mkrcomt[2][1][0]*rcom[2][1]))+((ik[0][1][2]-(mkrcomt[0][1][0]*rcom[0][1]))
      +(ik[1][1][2]-(mkrcomt[1][1][0]*rcom[1][1]))))))));
    psikg[2][0] = ((ik[6][2][0]-(mkrcomt[6][2][1]*rcom[6][2]))+((ik[5][2][0]-(
      mkrcomt[5][2][1]*rcom[5][2]))+((ik[4][2][0]-(mkrcomt[4][2][1]*rcom[4][2]))
      +((ik[3][2][0]-(mkrcomt[3][2][1]*rcom[3][2]))+((ik[2][2][0]-(
      mkrcomt[2][2][1]*rcom[2][2]))+((ik[0][2][0]-(mkrcomt[0][2][1]*rcom[0][2]))
      +(ik[1][2][0]-(mkrcomt[1][2][1]*rcom[1][2]))))))));
    psikg[2][1] = ((ik[6][2][1]+(mkrcomt[6][2][0]*rcom[6][2]))+((ik[5][2][1]+(
      mkrcomt[5][2][0]*rcom[5][2]))+((ik[4][2][1]+(mkrcomt[4][2][0]*rcom[4][2]))
      +((ik[3][2][1]+(mkrcomt[3][2][0]*rcom[3][2]))+((ik[2][2][1]+(
      mkrcomt[2][2][0]*rcom[2][2]))+((ik[0][2][1]+(mkrcomt[0][2][0]*rcom[0][2]))
      +(ik[1][2][1]+(mkrcomt[1][2][0]*rcom[1][2]))))))));
    temp[0] = ((ik[4][2][2]-((mkrcomt[4][2][0]*rcom[4][1])-(mkrcomt[4][2][1]*
      rcom[4][0])))+((ik[3][2][2]-((mkrcomt[3][2][0]*rcom[3][1])-(
      mkrcomt[3][2][1]*rcom[3][0])))+((ik[2][2][2]-((mkrcomt[2][2][0]*rcom[2][1]
      )-(mkrcomt[2][2][1]*rcom[2][0])))+((ik[0][2][2]-((mkrcomt[0][2][0]*
      rcom[0][1])-(mkrcomt[0][2][1]*rcom[0][0])))+(ik[1][2][2]-((
      mkrcomt[1][2][0]*rcom[1][1])-(mkrcomt[1][2][1]*rcom[1][0])))))));
    psikg[2][2] = ((ik[6][2][2]-((mkrcomt[6][2][0]*rcom[6][1])-(mkrcomt[6][2][1]
      *rcom[6][0])))+((ik[5][2][2]-((mkrcomt[5][2][0]*rcom[5][1])-(
      mkrcomt[5][2][1]*rcom[5][0])))+temp[0]));
    rkWkk[0][0] = ((pin[0][2]*rk[7][1])-(pin[0][1]*rk[7][2]));
    rkWkk[0][1] = ((pin[0][0]*rk[7][2])-(pin[0][2]*rk[7][0]));
    rkWkk[0][2] = ((pin[0][1]*rk[7][0])-(pin[0][0]*rk[7][1]));
    rkWkk[1][0] = ((pin[1][2]*rk[8][1])-(pin[1][1]*rk[8][2]));
    rkWkk[1][1] = ((pin[1][0]*rk[8][2])-(pin[1][2]*rk[8][0]));
    rkWkk[1][2] = ((pin[1][1]*rk[8][0])-(pin[1][0]*rk[8][1]));
    rkWkk[2][0] = ((pin[2][2]*rk[9][1])-(pin[2][1]*rk[9][2]));
    rkWkk[2][1] = ((pin[2][0]*rk[9][2])-(pin[2][2]*rk[9][0]));
    rkWkk[2][2] = ((pin[2][1]*rk[9][0])-(pin[2][0]*rk[9][1]));
    rkWkk[3][0] = ((pin[3][2]*rk[10][1])-(pin[3][1]*rk[10][2]));
    rkWkk[3][1] = ((pin[3][0]*rk[10][2])-(pin[3][2]*rk[10][0]));
    rkWkk[3][2] = ((pin[3][1]*rk[10][0])-(pin[3][0]*rk[10][1]));
    rkWkk[4][0] = ((pin[4][2]*rk[11][1])-(pin[4][1]*rk[11][2]));
    rkWkk[4][1] = ((pin[4][0]*rk[11][2])-(pin[4][2]*rk[11][0]));
    rkWkk[4][2] = ((pin[4][1]*rk[11][0])-(pin[4][0]*rk[11][1]));
    dik[1][0] = (ri[8][0]-rk[7][0]);
    dik[1][1] = (ri[8][1]-rk[7][1]);
    dik[1][2] = (ri[8][2]-rk[7][2]);
    dik[2][0] = (ri[9][0]-rk[8][0]);
    dik[2][1] = (ri[9][1]-rk[8][1]);
    dik[2][2] = (ri[9][2]-rk[8][2]);
    dik[3][0] = (ri[10][0]-rk[9][0]);
    dik[3][1] = (ri[10][1]-rk[9][1]);
    dik[3][2] = (ri[10][2]-rk[9][2]);
    dik[4][0] = (ri[11][0]-rk[10][0]);
    dik[4][1] = (ri[11][1]-rk[10][1]);
    dik[4][2] = (ri[11][2]-rk[10][2]);

/* Compute mass properties-related constants */

    mtot = (mk[11]+(mk[10]+(mk[9]+(mk[8]+(mk[7]+(mk[6]+(mk[5]+(mk[4]+(mk[3]+(
      mk[2]+(mk[0]+mk[1])))))))))));
    mkrk[0][0][1] = -(mk[7]*rk[7][2]);
    mkrk[0][0][2] = (mk[7]*rk[7][1]);
    mkrk[0][1][0] = (mk[7]*rk[7][2]);
    mkrk[0][1][2] = -(mk[7]*rk[7][0]);
    mkrk[0][2][0] = -(mk[7]*rk[7][1]);
    mkrk[0][2][1] = (mk[7]*rk[7][0]);
    mkrk[1][0][1] = -(mk[8]*rk[8][2]);
    mkrk[1][0][2] = (mk[8]*rk[8][1]);
    mkrk[1][1][0] = (mk[8]*rk[8][2]);
    mkrk[1][1][2] = -(mk[8]*rk[8][0]);
    mkrk[1][2][0] = -(mk[8]*rk[8][1]);
    mkrk[1][2][1] = (mk[8]*rk[8][0]);
    mkrk[2][0][1] = -(mk[9]*rk[9][2]);
    mkrk[2][0][2] = (mk[9]*rk[9][1]);
    mkrk[2][1][0] = (mk[9]*rk[9][2]);
    mkrk[2][1][2] = -(mk[9]*rk[9][0]);
    mkrk[2][2][0] = -(mk[9]*rk[9][1]);
    mkrk[2][2][1] = (mk[9]*rk[9][0]);
    mkrk[3][0][1] = -(mk[10]*rk[10][2]);
    mkrk[3][0][2] = (mk[10]*rk[10][1]);
    mkrk[3][1][0] = (mk[10]*rk[10][2]);
    mkrk[3][1][2] = -(mk[10]*rk[10][0]);
    mkrk[3][2][0] = -(mk[10]*rk[10][1]);
    mkrk[3][2][1] = (mk[10]*rk[10][0]);
    mkrk[4][0][1] = -(mk[11]*rk[11][2]);
    mkrk[4][0][2] = (mk[11]*rk[11][1]);
    mkrk[4][1][0] = (mk[11]*rk[11][2]);
    mkrk[4][1][2] = -(mk[11]*rk[11][0]);
    mkrk[4][2][0] = -(mk[11]*rk[11][1]);
    mkrk[4][2][1] = (mk[11]*rk[11][0]);
    Iko[0][0][0] = (ik[7][0][0]-((mkrk[0][0][1]*rk[7][2])-(mkrk[0][0][2]*
      rk[7][1])));
    Iko[0][0][1] = (ik[7][0][1]-(mkrk[0][0][2]*rk[7][0]));
    Iko[0][0][2] = (ik[7][0][2]+(mkrk[0][0][1]*rk[7][0]));
    Iko[0][1][0] = (ik[7][1][0]+(mkrk[0][1][2]*rk[7][1]));
    Iko[0][1][1] = (ik[7][1][1]-((mkrk[0][1][2]*rk[7][0])-(mkrk[0][1][0]*
      rk[7][2])));
    Iko[0][1][2] = (ik[7][1][2]-(mkrk[0][1][0]*rk[7][1]));
    Iko[0][2][0] = (ik[7][2][0]-(mkrk[0][2][1]*rk[7][2]));
    Iko[0][2][1] = (ik[7][2][1]+(mkrk[0][2][0]*rk[7][2]));
    Iko[0][2][2] = (ik[7][2][2]-((mkrk[0][2][0]*rk[7][1])-(mkrk[0][2][1]*
      rk[7][0])));
    Iko[1][0][0] = (ik[8][0][0]-((mkrk[1][0][1]*rk[8][2])-(mkrk[1][0][2]*
      rk[8][1])));
    Iko[1][0][1] = (ik[8][0][1]-(mkrk[1][0][2]*rk[8][0]));
    Iko[1][0][2] = (ik[8][0][2]+(mkrk[1][0][1]*rk[8][0]));
    Iko[1][1][0] = (ik[8][1][0]+(mkrk[1][1][2]*rk[8][1]));
    Iko[1][1][1] = (ik[8][1][1]-((mkrk[1][1][2]*rk[8][0])-(mkrk[1][1][0]*
      rk[8][2])));
    Iko[1][1][2] = (ik[8][1][2]-(mkrk[1][1][0]*rk[8][1]));
    Iko[1][2][0] = (ik[8][2][0]-(mkrk[1][2][1]*rk[8][2]));
    Iko[1][2][1] = (ik[8][2][1]+(mkrk[1][2][0]*rk[8][2]));
    Iko[1][2][2] = (ik[8][2][2]-((mkrk[1][2][0]*rk[8][1])-(mkrk[1][2][1]*
      rk[8][0])));
    Iko[2][0][0] = (ik[9][0][0]-((mkrk[2][0][1]*rk[9][2])-(mkrk[2][0][2]*
      rk[9][1])));
    Iko[2][0][1] = (ik[9][0][1]-(mkrk[2][0][2]*rk[9][0]));
    Iko[2][0][2] = (ik[9][0][2]+(mkrk[2][0][1]*rk[9][0]));
    Iko[2][1][0] = (ik[9][1][0]+(mkrk[2][1][2]*rk[9][1]));
    Iko[2][1][1] = (ik[9][1][1]-((mkrk[2][1][2]*rk[9][0])-(mkrk[2][1][0]*
      rk[9][2])));
    Iko[2][1][2] = (ik[9][1][2]-(mkrk[2][1][0]*rk[9][1]));
    Iko[2][2][0] = (ik[9][2][0]-(mkrk[2][2][1]*rk[9][2]));
    Iko[2][2][1] = (ik[9][2][1]+(mkrk[2][2][0]*rk[9][2]));
    Iko[2][2][2] = (ik[9][2][2]-((mkrk[2][2][0]*rk[9][1])-(mkrk[2][2][1]*
      rk[9][0])));
    Iko[3][0][0] = (ik[10][0][0]-((mkrk[3][0][1]*rk[10][2])-(mkrk[3][0][2]*
      rk[10][1])));
    Iko[3][0][1] = (ik[10][0][1]-(mkrk[3][0][2]*rk[10][0]));
    Iko[3][0][2] = (ik[10][0][2]+(mkrk[3][0][1]*rk[10][0]));
    Iko[3][1][0] = (ik[10][1][0]+(mkrk[3][1][2]*rk[10][1]));
    Iko[3][1][1] = (ik[10][1][1]-((mkrk[3][1][2]*rk[10][0])-(mkrk[3][1][0]*
      rk[10][2])));
    Iko[3][1][2] = (ik[10][1][2]-(mkrk[3][1][0]*rk[10][1]));
    Iko[3][2][0] = (ik[10][2][0]-(mkrk[3][2][1]*rk[10][2]));
    Iko[3][2][1] = (ik[10][2][1]+(mkrk[3][2][0]*rk[10][2]));
    Iko[3][2][2] = (ik[10][2][2]-((mkrk[3][2][0]*rk[10][1])-(mkrk[3][2][1]*
      rk[10][0])));
    Iko[4][0][0] = (ik[11][0][0]-((mkrk[4][0][1]*rk[11][2])-(mkrk[4][0][2]*
      rk[11][1])));
    Iko[4][0][1] = (ik[11][0][1]-(mkrk[4][0][2]*rk[11][0]));
    Iko[4][0][2] = (ik[11][0][2]+(mkrk[4][0][1]*rk[11][0]));
    Iko[4][1][0] = (ik[11][1][0]+(mkrk[4][1][2]*rk[11][1]));
    Iko[4][1][1] = (ik[11][1][1]-((mkrk[4][1][2]*rk[11][0])-(mkrk[4][1][0]*
      rk[11][2])));
    Iko[4][1][2] = (ik[11][1][2]-(mkrk[4][1][0]*rk[11][1]));
    Iko[4][2][0] = (ik[11][2][0]-(mkrk[4][2][1]*rk[11][2]));
    Iko[4][2][1] = (ik[11][2][1]+(mkrk[4][2][0]*rk[11][2]));
    Iko[4][2][2] = (ik[11][2][2]-((mkrk[4][2][0]*rk[11][1])-(mkrk[4][2][1]*
      rk[11][0])));
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

Generated 24-May-2007 16:22:11 by SD/FAST, Order(N) formulation
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
    Cik[0][0][0] = ((pin[0][0]*pin[0][0])+(c0*(1.-(pin[0][0]*pin[0][0]))));
    Cik[0][0][1] = (((pin[0][0]*pin[0][1])-(pin[0][2]*s0))-(c0*(pin[0][0]*
      pin[0][1])));
    Cik[0][0][2] = (((pin[0][0]*pin[0][2])+(pin[0][1]*s0))-(c0*(pin[0][0]*
      pin[0][2])));
    Cik[0][1][0] = (((pin[0][0]*pin[0][1])+(pin[0][2]*s0))-(c0*(pin[0][0]*
      pin[0][1])));
    Cik[0][1][1] = ((pin[0][1]*pin[0][1])+(c0*(1.-(pin[0][1]*pin[0][1]))));
    Cik[0][1][2] = (((pin[0][1]*pin[0][2])-(pin[0][0]*s0))-(c0*(pin[0][1]*
      pin[0][2])));
    Cik[0][2][0] = (((pin[0][0]*pin[0][2])-(pin[0][1]*s0))-(c0*(pin[0][0]*
      pin[0][2])));
    Cik[0][2][1] = (((pin[0][0]*s0)+(pin[0][1]*pin[0][2]))-(c0*(pin[0][1]*
      pin[0][2])));
    Cik[0][2][2] = ((pin[0][2]*pin[0][2])+(c0*(1.-(pin[0][2]*pin[0][2]))));
    Cik[1][0][0] = ((pin[1][0]*pin[1][0])+(c1*(1.-(pin[1][0]*pin[1][0]))));
    Cik[1][0][1] = (((pin[1][0]*pin[1][1])-(pin[1][2]*s1))-(c1*(pin[1][0]*
      pin[1][1])));
    Cik[1][0][2] = (((pin[1][0]*pin[1][2])+(pin[1][1]*s1))-(c1*(pin[1][0]*
      pin[1][2])));
    Cik[1][1][0] = (((pin[1][0]*pin[1][1])+(pin[1][2]*s1))-(c1*(pin[1][0]*
      pin[1][1])));
    Cik[1][1][1] = ((pin[1][1]*pin[1][1])+(c1*(1.-(pin[1][1]*pin[1][1]))));
    Cik[1][1][2] = (((pin[1][1]*pin[1][2])-(pin[1][0]*s1))-(c1*(pin[1][1]*
      pin[1][2])));
    Cik[1][2][0] = (((pin[1][0]*pin[1][2])-(pin[1][1]*s1))-(c1*(pin[1][0]*
      pin[1][2])));
    Cik[1][2][1] = (((pin[1][0]*s1)+(pin[1][1]*pin[1][2]))-(c1*(pin[1][1]*
      pin[1][2])));
    Cik[1][2][2] = ((pin[1][2]*pin[1][2])+(c1*(1.-(pin[1][2]*pin[1][2]))));
    Cik[2][0][0] = ((pin[2][0]*pin[2][0])+(c2*(1.-(pin[2][0]*pin[2][0]))));
    Cik[2][0][1] = (((pin[2][0]*pin[2][1])-(pin[2][2]*s2))-(c2*(pin[2][0]*
      pin[2][1])));
    Cik[2][0][2] = (((pin[2][0]*pin[2][2])+(pin[2][1]*s2))-(c2*(pin[2][0]*
      pin[2][2])));
    Cik[2][1][0] = (((pin[2][0]*pin[2][1])+(pin[2][2]*s2))-(c2*(pin[2][0]*
      pin[2][1])));
    Cik[2][1][1] = ((pin[2][1]*pin[2][1])+(c2*(1.-(pin[2][1]*pin[2][1]))));
    Cik[2][1][2] = (((pin[2][1]*pin[2][2])-(pin[2][0]*s2))-(c2*(pin[2][1]*
      pin[2][2])));
    Cik[2][2][0] = (((pin[2][0]*pin[2][2])-(pin[2][1]*s2))-(c2*(pin[2][0]*
      pin[2][2])));
    Cik[2][2][1] = (((pin[2][0]*s2)+(pin[2][1]*pin[2][2]))-(c2*(pin[2][1]*
      pin[2][2])));
    Cik[2][2][2] = ((pin[2][2]*pin[2][2])+(c2*(1.-(pin[2][2]*pin[2][2]))));
    Cik[3][0][0] = ((pin[3][0]*pin[3][0])+(c3*(1.-(pin[3][0]*pin[3][0]))));
    Cik[3][0][1] = (((pin[3][0]*pin[3][1])-(pin[3][2]*s3))-(c3*(pin[3][0]*
      pin[3][1])));
    Cik[3][0][2] = (((pin[3][0]*pin[3][2])+(pin[3][1]*s3))-(c3*(pin[3][0]*
      pin[3][2])));
    Cik[3][1][0] = (((pin[3][0]*pin[3][1])+(pin[3][2]*s3))-(c3*(pin[3][0]*
      pin[3][1])));
    Cik[3][1][1] = ((pin[3][1]*pin[3][1])+(c3*(1.-(pin[3][1]*pin[3][1]))));
    Cik[3][1][2] = (((pin[3][1]*pin[3][2])-(pin[3][0]*s3))-(c3*(pin[3][1]*
      pin[3][2])));
    Cik[3][2][0] = (((pin[3][0]*pin[3][2])-(pin[3][1]*s3))-(c3*(pin[3][0]*
      pin[3][2])));
    Cik[3][2][1] = (((pin[3][0]*s3)+(pin[3][1]*pin[3][2]))-(c3*(pin[3][1]*
      pin[3][2])));
    Cik[3][2][2] = ((pin[3][2]*pin[3][2])+(c3*(1.-(pin[3][2]*pin[3][2]))));
    Cik[4][0][0] = ((pin[4][0]*pin[4][0])+(c4*(1.-(pin[4][0]*pin[4][0]))));
    Cik[4][0][1] = (((pin[4][0]*pin[4][1])-(pin[4][2]*s4))-(c4*(pin[4][0]*
      pin[4][1])));
    Cik[4][0][2] = (((pin[4][0]*pin[4][2])+(pin[4][1]*s4))-(c4*(pin[4][0]*
      pin[4][2])));
    Cik[4][1][0] = (((pin[4][0]*pin[4][1])+(pin[4][2]*s4))-(c4*(pin[4][0]*
      pin[4][1])));
    Cik[4][1][1] = ((pin[4][1]*pin[4][1])+(c4*(1.-(pin[4][1]*pin[4][1]))));
    Cik[4][1][2] = (((pin[4][1]*pin[4][2])-(pin[4][0]*s4))-(c4*(pin[4][1]*
      pin[4][2])));
    Cik[4][2][0] = (((pin[4][0]*pin[4][2])-(pin[4][1]*s4))-(c4*(pin[4][0]*
      pin[4][2])));
    Cik[4][2][1] = (((pin[4][0]*s4)+(pin[4][1]*pin[4][2]))-(c4*(pin[4][1]*
      pin[4][2])));
    Cik[4][2][2] = ((pin[4][2]*pin[4][2])+(c4*(1.-(pin[4][2]*pin[4][2]))));
/*
Compute across-joint direction cosines Cib
*/
/*
Compute gravity
*/
    gk[0][0] = ((Cik[0][2][0]*grav[2])+((Cik[0][0][0]*grav[0])+(Cik[0][1][0]*
      grav[1])));
    gk[0][1] = ((Cik[0][2][1]*grav[2])+((Cik[0][0][1]*grav[0])+(Cik[0][1][1]*
      grav[1])));
    gk[0][2] = ((Cik[0][2][2]*grav[2])+((Cik[0][0][2]*grav[0])+(Cik[0][1][2]*
      grav[1])));
    gk[1][0] = ((Cik[1][2][0]*gk[0][2])+((Cik[1][0][0]*gk[0][0])+(Cik[1][1][0]*
      gk[0][1])));
    gk[1][1] = ((Cik[1][2][1]*gk[0][2])+((Cik[1][0][1]*gk[0][0])+(Cik[1][1][1]*
      gk[0][1])));
    gk[1][2] = ((Cik[1][2][2]*gk[0][2])+((Cik[1][0][2]*gk[0][0])+(Cik[1][1][2]*
      gk[0][1])));
    gk[2][0] = ((Cik[2][2][0]*gk[1][2])+((Cik[2][0][0]*gk[1][0])+(Cik[2][1][0]*
      gk[1][1])));
    gk[2][1] = ((Cik[2][2][1]*gk[1][2])+((Cik[2][0][1]*gk[1][0])+(Cik[2][1][1]*
      gk[1][1])));
    gk[2][2] = ((Cik[2][2][2]*gk[1][2])+((Cik[2][0][2]*gk[1][0])+(Cik[2][1][2]*
      gk[1][1])));
    gk[3][0] = ((Cik[3][2][0]*gk[2][2])+((Cik[3][0][0]*gk[2][0])+(Cik[3][1][0]*
      gk[2][1])));
    gk[3][1] = ((Cik[3][2][1]*gk[2][2])+((Cik[3][0][1]*gk[2][0])+(Cik[3][1][1]*
      gk[2][1])));
    gk[3][2] = ((Cik[3][2][2]*gk[2][2])+((Cik[3][0][2]*gk[2][0])+(Cik[3][1][2]*
      gk[2][1])));
    gk[4][0] = ((Cik[4][2][0]*gk[3][2])+((Cik[4][0][0]*gk[3][0])+(Cik[4][1][0]*
      gk[3][1])));
    gk[4][1] = ((Cik[4][2][1]*gk[3][2])+((Cik[4][0][1]*gk[3][0])+(Cik[4][1][1]*
      gk[3][1])));
    gk[4][2] = ((Cik[4][2][2]*gk[3][2])+((Cik[4][0][2]*gk[3][0])+(Cik[4][1][2]*
      gk[3][1])));
/*
Compute cnk & cnb (direction cosines in N)
*/
    cnk[1][0][0] = ((Cik[0][0][2]*Cik[1][2][0])+((Cik[0][0][0]*Cik[1][0][0])+(
      Cik[0][0][1]*Cik[1][1][0])));
    cnk[1][0][1] = ((Cik[0][0][2]*Cik[1][2][1])+((Cik[0][0][0]*Cik[1][0][1])+(
      Cik[0][0][1]*Cik[1][1][1])));
    cnk[1][0][2] = ((Cik[0][0][2]*Cik[1][2][2])+((Cik[0][0][0]*Cik[1][0][2])+(
      Cik[0][0][1]*Cik[1][1][2])));
    cnk[1][1][0] = ((Cik[0][1][2]*Cik[1][2][0])+((Cik[0][1][0]*Cik[1][0][0])+(
      Cik[0][1][1]*Cik[1][1][0])));
    cnk[1][1][1] = ((Cik[0][1][2]*Cik[1][2][1])+((Cik[0][1][0]*Cik[1][0][1])+(
      Cik[0][1][1]*Cik[1][1][1])));
    cnk[1][1][2] = ((Cik[0][1][2]*Cik[1][2][2])+((Cik[0][1][0]*Cik[1][0][2])+(
      Cik[0][1][1]*Cik[1][1][2])));
    cnk[1][2][0] = ((Cik[0][2][2]*Cik[1][2][0])+((Cik[0][2][0]*Cik[1][0][0])+(
      Cik[0][2][1]*Cik[1][1][0])));
    cnk[1][2][1] = ((Cik[0][2][2]*Cik[1][2][1])+((Cik[0][2][0]*Cik[1][0][1])+(
      Cik[0][2][1]*Cik[1][1][1])));
    cnk[1][2][2] = ((Cik[0][2][2]*Cik[1][2][2])+((Cik[0][2][0]*Cik[1][0][2])+(
      Cik[0][2][1]*Cik[1][1][2])));
    cnk[2][0][0] = ((Cik[2][2][0]*cnk[1][0][2])+((Cik[2][0][0]*cnk[1][0][0])+(
      Cik[2][1][0]*cnk[1][0][1])));
    cnk[2][0][1] = ((Cik[2][2][1]*cnk[1][0][2])+((Cik[2][0][1]*cnk[1][0][0])+(
      Cik[2][1][1]*cnk[1][0][1])));
    cnk[2][0][2] = ((Cik[2][2][2]*cnk[1][0][2])+((Cik[2][0][2]*cnk[1][0][0])+(
      Cik[2][1][2]*cnk[1][0][1])));
    cnk[2][1][0] = ((Cik[2][2][0]*cnk[1][1][2])+((Cik[2][0][0]*cnk[1][1][0])+(
      Cik[2][1][0]*cnk[1][1][1])));
    cnk[2][1][1] = ((Cik[2][2][1]*cnk[1][1][2])+((Cik[2][0][1]*cnk[1][1][0])+(
      Cik[2][1][1]*cnk[1][1][1])));
    cnk[2][1][2] = ((Cik[2][2][2]*cnk[1][1][2])+((Cik[2][0][2]*cnk[1][1][0])+(
      Cik[2][1][2]*cnk[1][1][1])));
    cnk[2][2][0] = ((Cik[2][2][0]*cnk[1][2][2])+((Cik[2][0][0]*cnk[1][2][0])+(
      Cik[2][1][0]*cnk[1][2][1])));
    cnk[2][2][1] = ((Cik[2][2][1]*cnk[1][2][2])+((Cik[2][0][1]*cnk[1][2][0])+(
      Cik[2][1][1]*cnk[1][2][1])));
    cnk[2][2][2] = ((Cik[2][2][2]*cnk[1][2][2])+((Cik[2][0][2]*cnk[1][2][0])+(
      Cik[2][1][2]*cnk[1][2][1])));
    cnk[3][0][0] = ((Cik[3][2][0]*cnk[2][0][2])+((Cik[3][0][0]*cnk[2][0][0])+(
      Cik[3][1][0]*cnk[2][0][1])));
    cnk[3][0][1] = ((Cik[3][2][1]*cnk[2][0][2])+((Cik[3][0][1]*cnk[2][0][0])+(
      Cik[3][1][1]*cnk[2][0][1])));
    cnk[3][0][2] = ((Cik[3][2][2]*cnk[2][0][2])+((Cik[3][0][2]*cnk[2][0][0])+(
      Cik[3][1][2]*cnk[2][0][1])));
    cnk[3][1][0] = ((Cik[3][2][0]*cnk[2][1][2])+((Cik[3][0][0]*cnk[2][1][0])+(
      Cik[3][1][0]*cnk[2][1][1])));
    cnk[3][1][1] = ((Cik[3][2][1]*cnk[2][1][2])+((Cik[3][0][1]*cnk[2][1][0])+(
      Cik[3][1][1]*cnk[2][1][1])));
    cnk[3][1][2] = ((Cik[3][2][2]*cnk[2][1][2])+((Cik[3][0][2]*cnk[2][1][0])+(
      Cik[3][1][2]*cnk[2][1][1])));
    cnk[3][2][0] = ((Cik[3][2][0]*cnk[2][2][2])+((Cik[3][0][0]*cnk[2][2][0])+(
      Cik[3][1][0]*cnk[2][2][1])));
    cnk[3][2][1] = ((Cik[3][2][1]*cnk[2][2][2])+((Cik[3][0][1]*cnk[2][2][0])+(
      Cik[3][1][1]*cnk[2][2][1])));
    cnk[3][2][2] = ((Cik[3][2][2]*cnk[2][2][2])+((Cik[3][0][2]*cnk[2][2][0])+(
      Cik[3][1][2]*cnk[2][2][1])));
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
    cnb[7][0][0] = Cik[0][0][0];
    cnb[7][0][1] = Cik[0][0][1];
    cnb[7][0][2] = Cik[0][0][2];
    cnb[7][1][0] = Cik[0][1][0];
    cnb[7][1][1] = Cik[0][1][1];
    cnb[7][1][2] = Cik[0][1][2];
    cnb[7][2][0] = Cik[0][2][0];
    cnb[7][2][1] = Cik[0][2][1];
    cnb[7][2][2] = Cik[0][2][2];
    cnb[8][0][0] = cnk[1][0][0];
    cnb[8][0][1] = cnk[1][0][1];
    cnb[8][0][2] = cnk[1][0][2];
    cnb[8][1][0] = cnk[1][1][0];
    cnb[8][1][1] = cnk[1][1][1];
    cnb[8][1][2] = cnk[1][1][2];
    cnb[8][2][0] = cnk[1][2][0];
    cnb[8][2][1] = cnk[1][2][1];
    cnb[8][2][2] = cnk[1][2][2];
    cnb[9][0][0] = cnk[2][0][0];
    cnb[9][0][1] = cnk[2][0][1];
    cnb[9][0][2] = cnk[2][0][2];
    cnb[9][1][0] = cnk[2][1][0];
    cnb[9][1][1] = cnk[2][1][1];
    cnb[9][1][2] = cnk[2][1][2];
    cnb[9][2][0] = cnk[2][2][0];
    cnb[9][2][1] = cnk[2][2][1];
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
    rik[0][0] = (((Cik[0][2][0]*psri[0][2])+((Cik[0][0][0]*psri[0][0])+(
      Cik[0][1][0]*psri[0][1])))-rk[7][0]);
    rik[0][1] = (((Cik[0][2][1]*psri[0][2])+((Cik[0][0][1]*psri[0][0])+(
      Cik[0][1][1]*psri[0][1])))-rk[7][1]);
    rik[0][2] = (((Cik[0][2][2]*psri[0][2])+((Cik[0][0][2]*psri[0][0])+(
      Cik[0][1][2]*psri[0][1])))-rk[7][2]);
    rik[1][0] = (((Cik[1][2][0]*ri[8][2])+((Cik[1][0][0]*ri[8][0])+(Cik[1][1][0]
      *ri[8][1])))-rk[8][0]);
    rik[1][1] = (((Cik[1][2][1]*ri[8][2])+((Cik[1][0][1]*ri[8][0])+(Cik[1][1][1]
      *ri[8][1])))-rk[8][1]);
    rik[1][2] = (((Cik[1][2][2]*ri[8][2])+((Cik[1][0][2]*ri[8][0])+(Cik[1][1][2]
      *ri[8][1])))-rk[8][2]);
    rik[2][0] = (((Cik[2][2][0]*ri[9][2])+((Cik[2][0][0]*ri[9][0])+(Cik[2][1][0]
      *ri[9][1])))-rk[9][0]);
    rik[2][1] = (((Cik[2][2][1]*ri[9][2])+((Cik[2][0][1]*ri[9][0])+(Cik[2][1][1]
      *ri[9][1])))-rk[9][1]);
    rik[2][2] = (((Cik[2][2][2]*ri[9][2])+((Cik[2][0][2]*ri[9][0])+(Cik[2][1][2]
      *ri[9][1])))-rk[9][2]);
    rik[3][0] = (((Cik[3][2][0]*ri[10][2])+((Cik[3][0][0]*ri[10][0])+(
      Cik[3][1][0]*ri[10][1])))-rk[10][0]);
    rik[3][1] = (((Cik[3][2][1]*ri[10][2])+((Cik[3][0][1]*ri[10][0])+(
      Cik[3][1][1]*ri[10][1])))-rk[10][1]);
    rik[3][2] = (((Cik[3][2][2]*ri[10][2])+((Cik[3][0][2]*ri[10][0])+(
      Cik[3][1][2]*ri[10][1])))-rk[10][2]);
    rik[4][0] = (((Cik[4][2][0]*ri[11][2])+((Cik[4][0][0]*ri[11][0])+(
      Cik[4][1][0]*ri[11][1])))-rk[11][0]);
    rik[4][1] = (((Cik[4][2][1]*ri[11][2])+((Cik[4][0][1]*ri[11][0])+(
      Cik[4][1][1]*ri[11][1])))-rk[11][1]);
    rik[4][2] = (((Cik[4][2][2]*ri[11][2])+((Cik[4][0][2]*ri[11][0])+(
      Cik[4][1][2]*ri[11][1])))-rk[11][2]);
    rikt[0][0][0] = ((Cik[0][2][0]*psri[0][1])-(Cik[0][1][0]*psri[0][2]));
    rikt[0][0][1] = ((Cik[0][2][1]*psri[0][1])-(Cik[0][1][1]*psri[0][2]));
    rikt[0][0][2] = ((Cik[0][2][2]*psri[0][1])-(Cik[0][1][2]*psri[0][2]));
    rikt[0][1][0] = ((Cik[0][0][0]*psri[0][2])-(Cik[0][2][0]*psri[0][0]));
    rikt[0][1][1] = ((Cik[0][0][1]*psri[0][2])-(Cik[0][2][1]*psri[0][0]));
    rikt[0][1][2] = ((Cik[0][0][2]*psri[0][2])-(Cik[0][2][2]*psri[0][0]));
    rikt[0][2][0] = ((Cik[0][1][0]*psri[0][0])-(Cik[0][0][0]*psri[0][1]));
    rikt[0][2][1] = ((Cik[0][1][1]*psri[0][0])-(Cik[0][0][1]*psri[0][1]));
    rikt[0][2][2] = ((Cik[0][1][2]*psri[0][0])-(Cik[0][0][2]*psri[0][1]));
    rikt[1][0][0] = ((Cik[1][2][0]*dik[1][1])-(Cik[1][1][0]*dik[1][2]));
    rikt[1][0][1] = ((Cik[1][2][1]*dik[1][1])-(Cik[1][1][1]*dik[1][2]));
    rikt[1][0][2] = ((Cik[1][2][2]*dik[1][1])-(Cik[1][1][2]*dik[1][2]));
    rikt[1][1][0] = ((Cik[1][0][0]*dik[1][2])-(Cik[1][2][0]*dik[1][0]));
    rikt[1][1][1] = ((Cik[1][0][1]*dik[1][2])-(Cik[1][2][1]*dik[1][0]));
    rikt[1][1][2] = ((Cik[1][0][2]*dik[1][2])-(Cik[1][2][2]*dik[1][0]));
    rikt[1][2][0] = ((Cik[1][1][0]*dik[1][0])-(Cik[1][0][0]*dik[1][1]));
    rikt[1][2][1] = ((Cik[1][1][1]*dik[1][0])-(Cik[1][0][1]*dik[1][1]));
    rikt[1][2][2] = ((Cik[1][1][2]*dik[1][0])-(Cik[1][0][2]*dik[1][1]));
    rikt[2][0][0] = ((Cik[2][2][0]*dik[2][1])-(Cik[2][1][0]*dik[2][2]));
    rikt[2][0][1] = ((Cik[2][2][1]*dik[2][1])-(Cik[2][1][1]*dik[2][2]));
    rikt[2][0][2] = ((Cik[2][2][2]*dik[2][1])-(Cik[2][1][2]*dik[2][2]));
    rikt[2][1][0] = ((Cik[2][0][0]*dik[2][2])-(Cik[2][2][0]*dik[2][0]));
    rikt[2][1][1] = ((Cik[2][0][1]*dik[2][2])-(Cik[2][2][1]*dik[2][0]));
    rikt[2][1][2] = ((Cik[2][0][2]*dik[2][2])-(Cik[2][2][2]*dik[2][0]));
    rikt[2][2][0] = ((Cik[2][1][0]*dik[2][0])-(Cik[2][0][0]*dik[2][1]));
    rikt[2][2][1] = ((Cik[2][1][1]*dik[2][0])-(Cik[2][0][1]*dik[2][1]));
    rikt[2][2][2] = ((Cik[2][1][2]*dik[2][0])-(Cik[2][0][2]*dik[2][1]));
    rikt[3][0][0] = ((Cik[3][2][0]*dik[3][1])-(Cik[3][1][0]*dik[3][2]));
    rikt[3][0][1] = ((Cik[3][2][1]*dik[3][1])-(Cik[3][1][1]*dik[3][2]));
    rikt[3][0][2] = ((Cik[3][2][2]*dik[3][1])-(Cik[3][1][2]*dik[3][2]));
    rikt[3][1][0] = ((Cik[3][0][0]*dik[3][2])-(Cik[3][2][0]*dik[3][0]));
    rikt[3][1][1] = ((Cik[3][0][1]*dik[3][2])-(Cik[3][2][1]*dik[3][0]));
    rikt[3][1][2] = ((Cik[3][0][2]*dik[3][2])-(Cik[3][2][2]*dik[3][0]));
    rikt[3][2][0] = ((Cik[3][1][0]*dik[3][0])-(Cik[3][0][0]*dik[3][1]));
    rikt[3][2][1] = ((Cik[3][1][1]*dik[3][0])-(Cik[3][0][1]*dik[3][1]));
    rikt[3][2][2] = ((Cik[3][1][2]*dik[3][0])-(Cik[3][0][2]*dik[3][1]));
    rikt[4][0][0] = ((Cik[4][2][0]*dik[4][1])-(Cik[4][1][0]*dik[4][2]));
    rikt[4][0][1] = ((Cik[4][2][1]*dik[4][1])-(Cik[4][1][1]*dik[4][2]));
    rikt[4][0][2] = ((Cik[4][2][2]*dik[4][1])-(Cik[4][1][2]*dik[4][2]));
    rikt[4][1][0] = ((Cik[4][0][0]*dik[4][2])-(Cik[4][2][0]*dik[4][0]));
    rikt[4][1][1] = ((Cik[4][0][1]*dik[4][2])-(Cik[4][2][1]*dik[4][0]));
    rikt[4][1][2] = ((Cik[4][0][2]*dik[4][2])-(Cik[4][2][2]*dik[4][0]));
    rikt[4][2][0] = ((Cik[4][1][0]*dik[4][0])-(Cik[4][0][0]*dik[4][1]));
    rikt[4][2][1] = ((Cik[4][1][1]*dik[4][0])-(Cik[4][0][1]*dik[4][1]));
    rikt[4][2][2] = ((Cik[4][1][2]*dik[4][0])-(Cik[4][0][2]*dik[4][1]));
/*
Compute rnk & rnb (mass center locations in N)
*/
    rnk[0][0] = ((psri[0][0]-psrcomg[0])-((Cik[0][0][2]*rk[7][2])+((Cik[0][0][0]
      *rk[7][0])+(Cik[0][0][1]*rk[7][1]))));
    rnk[0][1] = ((psri[0][1]-psrcomg[1])-((Cik[0][1][2]*rk[7][2])+((Cik[0][1][0]
      *rk[7][0])+(Cik[0][1][1]*rk[7][1]))));
    rnk[0][2] = ((psri[0][2]-psrcomg[2])-((Cik[0][2][2]*rk[7][2])+((Cik[0][2][0]
      *rk[7][0])+(Cik[0][2][1]*rk[7][1]))));
    rnk[1][0] = ((rnk[0][0]+((Cik[0][0][2]*ri[8][2])+((Cik[0][0][0]*ri[8][0])+(
      Cik[0][0][1]*ri[8][1]))))-((cnk[1][0][2]*rk[8][2])+((cnk[1][0][0]*rk[8][0]
      )+(cnk[1][0][1]*rk[8][1]))));
    rnk[1][1] = ((rnk[0][1]+((Cik[0][1][2]*ri[8][2])+((Cik[0][1][0]*ri[8][0])+(
      Cik[0][1][1]*ri[8][1]))))-((cnk[1][1][2]*rk[8][2])+((cnk[1][1][0]*rk[8][0]
      )+(cnk[1][1][1]*rk[8][1]))));
    rnk[1][2] = ((rnk[0][2]+((Cik[0][2][2]*ri[8][2])+((Cik[0][2][0]*ri[8][0])+(
      Cik[0][2][1]*ri[8][1]))))-((cnk[1][2][2]*rk[8][2])+((cnk[1][2][0]*rk[8][0]
      )+(cnk[1][2][1]*rk[8][1]))));
    rnk[2][0] = ((rnk[1][0]+((cnk[1][0][2]*ri[9][2])+((cnk[1][0][0]*ri[9][0])+(
      cnk[1][0][1]*ri[9][1]))))-((cnk[2][0][2]*rk[9][2])+((cnk[2][0][0]*rk[9][0]
      )+(cnk[2][0][1]*rk[9][1]))));
    rnk[2][1] = ((rnk[1][1]+((cnk[1][1][2]*ri[9][2])+((cnk[1][1][0]*ri[9][0])+(
      cnk[1][1][1]*ri[9][1]))))-((cnk[2][1][2]*rk[9][2])+((cnk[2][1][0]*rk[9][0]
      )+(cnk[2][1][1]*rk[9][1]))));
    rnk[2][2] = ((rnk[1][2]+((cnk[1][2][2]*ri[9][2])+((cnk[1][2][0]*ri[9][0])+(
      cnk[1][2][1]*ri[9][1]))))-((cnk[2][2][2]*rk[9][2])+((cnk[2][2][0]*rk[9][0]
      )+(cnk[2][2][1]*rk[9][1]))));
    rnk[3][0] = ((rnk[2][0]+((cnk[2][0][2]*ri[10][2])+((cnk[2][0][0]*ri[10][0])+
      (cnk[2][0][1]*ri[10][1]))))-((cnk[3][0][2]*rk[10][2])+((cnk[3][0][0]*
      rk[10][0])+(cnk[3][0][1]*rk[10][1]))));
    rnk[3][1] = ((rnk[2][1]+((cnk[2][1][2]*ri[10][2])+((cnk[2][1][0]*ri[10][0])+
      (cnk[2][1][1]*ri[10][1]))))-((cnk[3][1][2]*rk[10][2])+((cnk[3][1][0]*
      rk[10][0])+(cnk[3][1][1]*rk[10][1]))));
    rnk[3][2] = ((rnk[2][2]+((cnk[2][2][2]*ri[10][2])+((cnk[2][2][0]*ri[10][0])+
      (cnk[2][2][1]*ri[10][1]))))-((cnk[3][2][2]*rk[10][2])+((cnk[3][2][0]*
      rk[10][0])+(cnk[3][2][1]*rk[10][1]))));
    rnk[4][0] = ((rnk[3][0]+((cnk[3][0][2]*ri[11][2])+((cnk[3][0][0]*ri[11][0])+
      (cnk[3][0][1]*ri[11][1]))))-((cnk[4][0][2]*rk[11][2])+((cnk[4][0][0]*
      rk[11][0])+(cnk[4][0][1]*rk[11][1]))));
    rnk[4][1] = ((rnk[3][1]+((cnk[3][1][2]*ri[11][2])+((cnk[3][1][0]*ri[11][0])+
      (cnk[3][1][1]*ri[11][1]))))-((cnk[4][1][2]*rk[11][2])+((cnk[4][1][0]*
      rk[11][0])+(cnk[4][1][1]*rk[11][1]))));
    rnk[4][2] = ((rnk[3][2]+((cnk[3][2][2]*ri[11][2])+((cnk[3][2][0]*ri[11][0])+
      (cnk[3][2][1]*ri[11][1]))))-((cnk[4][2][2]*rk[11][2])+((cnk[4][2][0]*
      rk[11][0])+(cnk[4][2][1]*rk[11][1]))));
    rnb[0][0] = (rcom[0][0]-psrcomg[0]);
    rnb[0][1] = (rcom[0][1]-psrcomg[1]);
    rnb[0][2] = (rcom[0][2]-psrcomg[2]);
    rnb[1][0] = (rcom[1][0]-psrcomg[0]);
    rnb[1][1] = (rcom[1][1]-psrcomg[1]);
    rnb[1][2] = (rcom[1][2]-psrcomg[2]);
    rnb[2][0] = (rcom[2][0]-psrcomg[0]);
    rnb[2][1] = (rcom[2][1]-psrcomg[1]);
    rnb[2][2] = (rcom[2][2]-psrcomg[2]);
    rnb[3][0] = (rcom[3][0]-psrcomg[0]);
    rnb[3][1] = (rcom[3][1]-psrcomg[1]);
    rnb[3][2] = (rcom[3][2]-psrcomg[2]);
    rnb[4][0] = (rcom[4][0]-psrcomg[0]);
    rnb[4][1] = (rcom[4][1]-psrcomg[1]);
    rnb[4][2] = (rcom[4][2]-psrcomg[2]);
    rnb[5][0] = (rcom[5][0]-psrcomg[0]);
    rnb[5][1] = (rcom[5][1]-psrcomg[1]);
    rnb[5][2] = (rcom[5][2]-psrcomg[2]);
    rnb[6][0] = (rcom[6][0]-psrcomg[0]);
    rnb[6][1] = (rcom[6][1]-psrcomg[1]);
    rnb[6][2] = (rcom[6][2]-psrcomg[2]);
    rnb[7][0] = rnk[0][0];
    rnb[7][1] = rnk[0][1];
    rnb[7][2] = rnk[0][2];
    rnb[8][0] = rnk[1][0];
    rnb[8][1] = rnk[1][1];
    rnb[8][2] = rnk[1][2];
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
    com[0] = ((1./mtot)*((mk[11]*rnk[4][0])+((mk[10]*rnk[3][0])+((mk[9]*
      rnk[2][0])+((mk[8]*rnk[1][0])+((mk[7]*rnk[0][0])-(psmkg*psrcomg[0])))))));
    com[1] = ((1./mtot)*((mk[11]*rnk[4][1])+((mk[10]*rnk[3][1])+((mk[9]*
      rnk[2][1])+((mk[8]*rnk[1][1])+((mk[7]*rnk[0][1])-(psmkg*psrcomg[1])))))));
    com[2] = ((1./mtot)*((mk[11]*rnk[4][2])+((mk[10]*rnk[3][2])+((mk[9]*
      rnk[2][2])+((mk[8]*rnk[1][2])+((mk[7]*rnk[0][2])-(psmkg*psrcomg[2])))))));
/*
Compute constraint position errors
*/
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
    Wik[0][0] = (pin[0][0]*u[0]);
    Wik[0][1] = (pin[0][1]*u[0]);
    Wik[0][2] = (pin[0][2]*u[0]);
    Wik[1][0] = (pin[1][0]*u[1]);
    Wik[1][1] = (pin[1][1]*u[1]);
    Wik[1][2] = (pin[1][2]*u[1]);
    Wik[2][0] = (pin[2][0]*u[2]);
    Wik[2][1] = (pin[2][1]*u[2]);
    Wik[2][2] = (pin[2][2]*u[2]);
    Wik[3][0] = (pin[3][0]*u[3]);
    Wik[3][1] = (pin[3][1]*u[3]);
    Wik[3][2] = (pin[3][2]*u[3]);
    Wik[4][0] = (pin[4][0]*u[4]);
    Wik[4][1] = (pin[4][1]*u[4]);
    Wik[4][2] = (pin[4][2]*u[4]);
/*
Compute wk & wb (angular velocities)
*/
    wk[1][0] = (Wik[1][0]+((Cik[1][2][0]*Wik[0][2])+((Cik[1][0][0]*Wik[0][0])+(
      Cik[1][1][0]*Wik[0][1]))));
    wk[1][1] = (Wik[1][1]+((Cik[1][2][1]*Wik[0][2])+((Cik[1][0][1]*Wik[0][0])+(
      Cik[1][1][1]*Wik[0][1]))));
    wk[1][2] = (Wik[1][2]+((Cik[1][2][2]*Wik[0][2])+((Cik[1][0][2]*Wik[0][0])+(
      Cik[1][1][2]*Wik[0][1]))));
    wk[2][0] = (Wik[2][0]+((Cik[2][2][0]*wk[1][2])+((Cik[2][0][0]*wk[1][0])+(
      Cik[2][1][0]*wk[1][1]))));
    wk[2][1] = (Wik[2][1]+((Cik[2][2][1]*wk[1][2])+((Cik[2][0][1]*wk[1][0])+(
      Cik[2][1][1]*wk[1][1]))));
    wk[2][2] = (Wik[2][2]+((Cik[2][2][2]*wk[1][2])+((Cik[2][0][2]*wk[1][0])+(
      Cik[2][1][2]*wk[1][1]))));
    wk[3][0] = (Wik[3][0]+((Cik[3][2][0]*wk[2][2])+((Cik[3][0][0]*wk[2][0])+(
      Cik[3][1][0]*wk[2][1]))));
    wk[3][1] = (Wik[3][1]+((Cik[3][2][1]*wk[2][2])+((Cik[3][0][1]*wk[2][0])+(
      Cik[3][1][1]*wk[2][1]))));
    wk[3][2] = (Wik[3][2]+((Cik[3][2][2]*wk[2][2])+((Cik[3][0][2]*wk[2][0])+(
      Cik[3][1][2]*wk[2][1]))));
    wk[4][0] = (Wik[4][0]+((Cik[4][2][0]*wk[3][2])+((Cik[4][0][0]*wk[3][0])+(
      Cik[4][1][0]*wk[3][1]))));
    wk[4][1] = (Wik[4][1]+((Cik[4][2][1]*wk[3][2])+((Cik[4][0][1]*wk[3][0])+(
      Cik[4][1][1]*wk[3][1]))));
    wk[4][2] = (Wik[4][2]+((Cik[4][2][2]*wk[3][2])+((Cik[4][0][2]*wk[3][0])+(
      Cik[4][1][2]*wk[3][1]))));
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
    wb[7][0] = Wik[0][0];
    wb[7][1] = Wik[0][1];
    wb[7][2] = Wik[0][2];
    wb[8][0] = wk[1][0];
    wb[8][1] = wk[1][1];
    wb[8][2] = wk[1][2];
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
    Wirk[1][0] = ((ri[8][2]*Wik[0][1])-(ri[8][1]*Wik[0][2]));
    Wirk[1][1] = ((ri[8][0]*Wik[0][2])-(ri[8][2]*Wik[0][0]));
    Wirk[1][2] = ((ri[8][1]*Wik[0][0])-(ri[8][0]*Wik[0][1]));
    Wirk[2][0] = ((ri[9][2]*wk[1][1])-(ri[9][1]*wk[1][2]));
    Wirk[2][1] = ((ri[9][0]*wk[1][2])-(ri[9][2]*wk[1][0]));
    Wirk[2][2] = ((ri[9][1]*wk[1][0])-(ri[9][0]*wk[1][1]));
    Wirk[3][0] = ((ri[10][2]*wk[2][1])-(ri[10][1]*wk[2][2]));
    Wirk[3][1] = ((ri[10][0]*wk[2][2])-(ri[10][2]*wk[2][0]));
    Wirk[3][2] = ((ri[10][1]*wk[2][0])-(ri[10][0]*wk[2][1]));
    Wirk[4][0] = ((ri[11][2]*wk[3][1])-(ri[11][1]*wk[3][2]));
    Wirk[4][1] = ((ri[11][0]*wk[3][2])-(ri[11][2]*wk[3][0]));
    Wirk[4][2] = ((ri[11][1]*wk[3][0])-(ri[11][0]*wk[3][1]));
    Wkrpk[0][0] = ((rk[7][1]*Wik[0][2])-(rk[7][2]*Wik[0][1]));
    Wkrpk[0][1] = ((rk[7][2]*Wik[0][0])-(rk[7][0]*Wik[0][2]));
    Wkrpk[0][2] = ((rk[7][0]*Wik[0][1])-(rk[7][1]*Wik[0][0]));
    Wkrpk[1][0] = ((rk[8][1]*wk[1][2])-(rk[8][2]*wk[1][1]));
    Wkrpk[1][1] = ((rk[8][2]*wk[1][0])-(rk[8][0]*wk[1][2]));
    Wkrpk[1][2] = ((rk[8][0]*wk[1][1])-(rk[8][1]*wk[1][0]));
    Wkrpk[2][0] = ((rk[9][1]*wk[2][2])-(rk[9][2]*wk[2][1]));
    Wkrpk[2][1] = ((rk[9][2]*wk[2][0])-(rk[9][0]*wk[2][2]));
    Wkrpk[2][2] = ((rk[9][0]*wk[2][1])-(rk[9][1]*wk[2][0]));
    Wkrpk[3][0] = ((rk[10][1]*wk[3][2])-(rk[10][2]*wk[3][1]));
    Wkrpk[3][1] = ((rk[10][2]*wk[3][0])-(rk[10][0]*wk[3][2]));
    Wkrpk[3][2] = ((rk[10][0]*wk[3][1])-(rk[10][1]*wk[3][0]));
    Wkrpk[4][0] = ((rk[11][1]*wk[4][2])-(rk[11][2]*wk[4][1]));
    Wkrpk[4][1] = ((rk[11][2]*wk[4][0])-(rk[11][0]*wk[4][2]));
    Wkrpk[4][2] = ((rk[11][0]*wk[4][1])-(rk[11][1]*wk[4][0]));
    IkWk[0][0] = ((ik[7][0][2]*Wik[0][2])+((ik[7][0][0]*Wik[0][0])+(ik[7][0][1]*
      Wik[0][1])));
    IkWk[0][1] = ((ik[7][1][2]*Wik[0][2])+((ik[7][1][0]*Wik[0][0])+(ik[7][1][1]*
      Wik[0][1])));
    IkWk[0][2] = ((ik[7][2][2]*Wik[0][2])+((ik[7][2][0]*Wik[0][0])+(ik[7][2][1]*
      Wik[0][1])));
    WkIkWk[0][0] = ((IkWk[0][2]*Wik[0][1])-(IkWk[0][1]*Wik[0][2]));
    WkIkWk[0][1] = ((IkWk[0][0]*Wik[0][2])-(IkWk[0][2]*Wik[0][0]));
    WkIkWk[0][2] = ((IkWk[0][1]*Wik[0][0])-(IkWk[0][0]*Wik[0][1]));
    IkWk[1][0] = ((ik[8][0][2]*wk[1][2])+((ik[8][0][0]*wk[1][0])+(ik[8][0][1]*
      wk[1][1])));
    IkWk[1][1] = ((ik[8][1][2]*wk[1][2])+((ik[8][1][0]*wk[1][0])+(ik[8][1][1]*
      wk[1][1])));
    IkWk[1][2] = ((ik[8][2][2]*wk[1][2])+((ik[8][2][0]*wk[1][0])+(ik[8][2][1]*
      wk[1][1])));
    WkIkWk[1][0] = ((IkWk[1][2]*wk[1][1])-(IkWk[1][1]*wk[1][2]));
    WkIkWk[1][1] = ((IkWk[1][0]*wk[1][2])-(IkWk[1][2]*wk[1][0]));
    WkIkWk[1][2] = ((IkWk[1][1]*wk[1][0])-(IkWk[1][0]*wk[1][1]));
    IkWk[2][0] = ((ik[9][0][2]*wk[2][2])+((ik[9][0][0]*wk[2][0])+(ik[9][0][1]*
      wk[2][1])));
    IkWk[2][1] = ((ik[9][1][2]*wk[2][2])+((ik[9][1][0]*wk[2][0])+(ik[9][1][1]*
      wk[2][1])));
    IkWk[2][2] = ((ik[9][2][2]*wk[2][2])+((ik[9][2][0]*wk[2][0])+(ik[9][2][1]*
      wk[2][1])));
    WkIkWk[2][0] = ((IkWk[2][2]*wk[2][1])-(IkWk[2][1]*wk[2][2]));
    WkIkWk[2][1] = ((IkWk[2][0]*wk[2][2])-(IkWk[2][2]*wk[2][0]));
    WkIkWk[2][2] = ((IkWk[2][1]*wk[2][0])-(IkWk[2][0]*wk[2][1]));
    IkWk[3][0] = ((ik[10][0][2]*wk[3][2])+((ik[10][0][0]*wk[3][0])+(ik[10][0][1]
      *wk[3][1])));
    IkWk[3][1] = ((ik[10][1][2]*wk[3][2])+((ik[10][1][0]*wk[3][0])+(ik[10][1][1]
      *wk[3][1])));
    IkWk[3][2] = ((ik[10][2][2]*wk[3][2])+((ik[10][2][0]*wk[3][0])+(ik[10][2][1]
      *wk[3][1])));
    WkIkWk[3][0] = ((IkWk[3][2]*wk[3][1])-(IkWk[3][1]*wk[3][2]));
    WkIkWk[3][1] = ((IkWk[3][0]*wk[3][2])-(IkWk[3][2]*wk[3][0]));
    WkIkWk[3][2] = ((IkWk[3][1]*wk[3][0])-(IkWk[3][0]*wk[3][1]));
    IkWk[4][0] = ((ik[11][0][2]*wk[4][2])+((ik[11][0][0]*wk[4][0])+(ik[11][0][1]
      *wk[4][1])));
    IkWk[4][1] = ((ik[11][1][2]*wk[4][2])+((ik[11][1][0]*wk[4][0])+(ik[11][1][1]
      *wk[4][1])));
    IkWk[4][2] = ((ik[11][2][2]*wk[4][2])+((ik[11][2][0]*wk[4][0])+(ik[11][2][1]
      *wk[4][1])));
    WkIkWk[4][0] = ((IkWk[4][2]*wk[4][1])-(IkWk[4][1]*wk[4][2]));
    WkIkWk[4][1] = ((IkWk[4][0]*wk[4][2])-(IkWk[4][2]*wk[4][0]));
    WkIkWk[4][2] = ((IkWk[4][1]*wk[4][0])-(IkWk[4][0]*wk[4][1]));
/*
Compute temporaries for use in SDRHS
*/
    w0w0[7] = (Wik[0][0]*Wik[0][0]);
    w0w0[8] = (wk[1][0]*wk[1][0]);
    w0w0[9] = (wk[2][0]*wk[2][0]);
    w0w0[10] = (wk[3][0]*wk[3][0]);
    w0w0[11] = (wk[4][0]*wk[4][0]);
    w1w1[7] = (Wik[0][1]*Wik[0][1]);
    w1w1[8] = (wk[1][1]*wk[1][1]);
    w1w1[9] = (wk[2][1]*wk[2][1]);
    w1w1[10] = (wk[3][1]*wk[3][1]);
    w1w1[11] = (wk[4][1]*wk[4][1]);
    w2w2[7] = (Wik[0][2]*Wik[0][2]);
    w2w2[8] = (wk[1][2]*wk[1][2]);
    w2w2[9] = (wk[2][2]*wk[2][2]);
    w2w2[10] = (wk[3][2]*wk[3][2]);
    w2w2[11] = (wk[4][2]*wk[4][2]);
    w0w1[7] = (Wik[0][0]*Wik[0][1]);
    w0w1[8] = (wk[1][0]*wk[1][1]);
    w0w1[9] = (wk[2][0]*wk[2][1]);
    w0w1[10] = (wk[3][0]*wk[3][1]);
    w0w1[11] = (wk[4][0]*wk[4][1]);
    w0w2[7] = (Wik[0][0]*Wik[0][2]);
    w0w2[8] = (wk[1][0]*wk[1][2]);
    w0w2[9] = (wk[2][0]*wk[2][2]);
    w0w2[10] = (wk[3][0]*wk[3][2]);
    w0w2[11] = (wk[4][0]*wk[4][2]);
    w1w2[7] = (Wik[0][1]*Wik[0][2]);
    w1w2[8] = (wk[1][1]*wk[1][2]);
    w1w2[9] = (wk[2][1]*wk[2][2]);
    w1w2[10] = (wk[3][1]*wk[3][2]);
    w1w2[11] = (wk[4][1]*wk[4][2]);
    w00w11[7] = -(w0w0[7]+w1w1[7]);
    w00w11[8] = -(w0w0[8]+w1w1[8]);
    w00w11[9] = -(w0w0[9]+w1w1[9]);
    w00w11[10] = -(w0w0[10]+w1w1[10]);
    w00w11[11] = -(w0w0[11]+w1w1[11]);
    w00w22[7] = -(w0w0[7]+w2w2[7]);
    w00w22[8] = -(w0w0[8]+w2w2[8]);
    w00w22[9] = -(w0w0[9]+w2w2[9]);
    w00w22[10] = -(w0w0[10]+w2w2[10]);
    w00w22[11] = -(w0w0[11]+w2w2[11]);
    w11w22[7] = -(w1w1[7]+w2w2[7]);
    w11w22[8] = -(w1w1[8]+w2w2[8]);
    w11w22[9] = -(w1w1[9]+w2w2[9]);
    w11w22[10] = -(w1w1[10]+w2w2[10]);
    w11w22[11] = -(w1w1[11]+w2w2[11]);
/*
Compute vnk & vnb (mass center linear velocities in N)
*/
    vnk[0][0] = ((Cik[0][0][2]*Wkrpk[0][2])+((Cik[0][0][0]*Wkrpk[0][0])+(
      Cik[0][0][1]*Wkrpk[0][1])));
    vnk[0][1] = ((Cik[0][1][2]*Wkrpk[0][2])+((Cik[0][1][0]*Wkrpk[0][0])+(
      Cik[0][1][1]*Wkrpk[0][1])));
    vnk[0][2] = ((Cik[0][2][2]*Wkrpk[0][2])+((Cik[0][2][0]*Wkrpk[0][0])+(
      Cik[0][2][1]*Wkrpk[0][1])));
    vnk[1][0] = ((vnk[0][0]+((Cik[0][0][2]*Wirk[1][2])+((Cik[0][0][0]*Wirk[1][0]
      )+(Cik[0][0][1]*Wirk[1][1]))))+((cnk[1][0][2]*Wkrpk[1][2])+((cnk[1][0][0]*
      Wkrpk[1][0])+(cnk[1][0][1]*Wkrpk[1][1]))));
    vnk[1][1] = ((vnk[0][1]+((Cik[0][1][2]*Wirk[1][2])+((Cik[0][1][0]*Wirk[1][0]
      )+(Cik[0][1][1]*Wirk[1][1]))))+((cnk[1][1][2]*Wkrpk[1][2])+((cnk[1][1][0]*
      Wkrpk[1][0])+(cnk[1][1][1]*Wkrpk[1][1]))));
    vnk[1][2] = ((vnk[0][2]+((Cik[0][2][2]*Wirk[1][2])+((Cik[0][2][0]*Wirk[1][0]
      )+(Cik[0][2][1]*Wirk[1][1]))))+((cnk[1][2][2]*Wkrpk[1][2])+((cnk[1][2][0]*
      Wkrpk[1][0])+(cnk[1][2][1]*Wkrpk[1][1]))));
    vnk[2][0] = ((vnk[1][0]+((cnk[1][0][2]*Wirk[2][2])+((cnk[1][0][0]*Wirk[2][0]
      )+(cnk[1][0][1]*Wirk[2][1]))))+((cnk[2][0][2]*Wkrpk[2][2])+((cnk[2][0][0]*
      Wkrpk[2][0])+(cnk[2][0][1]*Wkrpk[2][1]))));
    vnk[2][1] = ((vnk[1][1]+((cnk[1][1][2]*Wirk[2][2])+((cnk[1][1][0]*Wirk[2][0]
      )+(cnk[1][1][1]*Wirk[2][1]))))+((cnk[2][1][2]*Wkrpk[2][2])+((cnk[2][1][0]*
      Wkrpk[2][0])+(cnk[2][1][1]*Wkrpk[2][1]))));
    vnk[2][2] = ((vnk[1][2]+((cnk[1][2][2]*Wirk[2][2])+((cnk[1][2][0]*Wirk[2][0]
      )+(cnk[1][2][1]*Wirk[2][1]))))+((cnk[2][2][2]*Wkrpk[2][2])+((cnk[2][2][0]*
      Wkrpk[2][0])+(cnk[2][2][1]*Wkrpk[2][1]))));
    vnk[3][0] = ((vnk[2][0]+((cnk[2][0][2]*Wirk[3][2])+((cnk[2][0][0]*Wirk[3][0]
      )+(cnk[2][0][1]*Wirk[3][1]))))+((cnk[3][0][2]*Wkrpk[3][2])+((cnk[3][0][0]*
      Wkrpk[3][0])+(cnk[3][0][1]*Wkrpk[3][1]))));
    vnk[3][1] = ((vnk[2][1]+((cnk[2][1][2]*Wirk[3][2])+((cnk[2][1][0]*Wirk[3][0]
      )+(cnk[2][1][1]*Wirk[3][1]))))+((cnk[3][1][2]*Wkrpk[3][2])+((cnk[3][1][0]*
      Wkrpk[3][0])+(cnk[3][1][1]*Wkrpk[3][1]))));
    vnk[3][2] = ((vnk[2][2]+((cnk[2][2][2]*Wirk[3][2])+((cnk[2][2][0]*Wirk[3][0]
      )+(cnk[2][2][1]*Wirk[3][1]))))+((cnk[3][2][2]*Wkrpk[3][2])+((cnk[3][2][0]*
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
    vnb[7][0] = vnk[0][0];
    vnb[7][1] = vnk[0][1];
    vnb[7][2] = vnk[0][2];
    vnb[8][0] = vnk[1][0];
    vnb[8][1] = vnk[1][1];
    vnb[8][2] = vnk[1][2];
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
/*
Compute constraint velocity errors
*/
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
Initialize prescribed motions
*/
    uacc[0] = 0.;
    uvel[0] = u[0];
    upos[0] = q[0];
    uacc[1] = 0.;
    uvel[1] = u[1];
    upos[1] = q[1];
    uacc[2] = 0.;
    uvel[2] = u[2];
    upos[2] = q[2];
    uacc[3] = 0.;
    uvel[3] = u[3];
    upos[3] = q[3];
    uacc[4] = 0.;
    uvel[4] = u[4];
    upos[4] = q[4];
/*
 Used 0.02 seconds CPU time,
 0 additional bytes of memory.
 Equations contain  618 adds/subtracts/negates
                    846 multiplies
                      3 divides
                    641 assignments
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
 Used -0.00 seconds CPU time,
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
        ping[0][0] = ((Cik[0][0][2]*pin[0][2])+((Cik[0][0][0]*pin[0][0])+(
          Cik[0][0][1]*pin[0][1])));
        ping[0][1] = ((Cik[0][1][2]*pin[0][2])+((Cik[0][1][0]*pin[0][0])+(
          Cik[0][1][1]*pin[0][1])));
        ping[0][2] = ((Cik[0][2][2]*pin[0][2])+((Cik[0][2][0]*pin[0][0])+(
          Cik[0][2][1]*pin[0][1])));
        ping[1][0] = ((cnk[1][0][2]*pin[1][2])+((cnk[1][0][0]*pin[1][0])+(
          cnk[1][0][1]*pin[1][1])));
        ping[1][1] = ((cnk[1][1][2]*pin[1][2])+((cnk[1][1][0]*pin[1][0])+(
          cnk[1][1][1]*pin[1][1])));
        ping[1][2] = ((cnk[1][2][2]*pin[1][2])+((cnk[1][2][0]*pin[1][0])+(
          cnk[1][2][1]*pin[1][1])));
        ping[2][0] = ((cnk[2][0][2]*pin[2][2])+((cnk[2][0][0]*pin[2][0])+(
          cnk[2][0][1]*pin[2][1])));
        ping[2][1] = ((cnk[2][1][2]*pin[2][2])+((cnk[2][1][0]*pin[2][0])+(
          cnk[2][1][1]*pin[2][1])));
        ping[2][2] = ((cnk[2][2][2]*pin[2][2])+((cnk[2][2][0]*pin[2][0])+(
          cnk[2][2][1]*pin[2][1])));
        ping[3][0] = ((cnk[3][0][2]*pin[3][2])+((cnk[3][0][0]*pin[3][0])+(
          cnk[3][0][1]*pin[3][1])));
        ping[3][1] = ((cnk[3][1][2]*pin[3][2])+((cnk[3][1][0]*pin[3][0])+(
          cnk[3][1][1]*pin[3][1])));
        ping[3][2] = ((cnk[3][2][2]*pin[3][2])+((cnk[3][2][0]*pin[3][0])+(
          cnk[3][2][1]*pin[3][1])));
        ping[4][0] = ((cnk[4][0][2]*pin[4][2])+((cnk[4][0][0]*pin[4][0])+(
          cnk[4][0][1]*pin[4][1])));
        ping[4][1] = ((cnk[4][1][2]*pin[4][2])+((cnk[4][1][0]*pin[4][0])+(
          cnk[4][1][1]*pin[4][1])));
        ping[4][2] = ((cnk[4][2][2]*pin[4][2])+((cnk[4][2][0]*pin[4][0])+(
          cnk[4][2][1]*pin[4][1])));
/*
Compute hngpt (hinge pts in ground frame)
*/
        hngpt[0][0] = (rnk[0][0]+((Cik[0][0][2]*rk[7][2])+((Cik[0][0][0]*
          rk[7][0])+(Cik[0][0][1]*rk[7][1]))));
        hngpt[0][1] = (rnk[0][1]+((Cik[0][1][2]*rk[7][2])+((Cik[0][1][0]*
          rk[7][0])+(Cik[0][1][1]*rk[7][1]))));
        hngpt[0][2] = (rnk[0][2]+((Cik[0][2][2]*rk[7][2])+((Cik[0][2][0]*
          rk[7][0])+(Cik[0][2][1]*rk[7][1]))));
        hngpt[1][0] = (rnk[1][0]+((cnk[1][0][2]*rk[8][2])+((cnk[1][0][0]*
          rk[8][0])+(cnk[1][0][1]*rk[8][1]))));
        hngpt[1][1] = (rnk[1][1]+((cnk[1][1][2]*rk[8][2])+((cnk[1][1][0]*
          rk[8][0])+(cnk[1][1][1]*rk[8][1]))));
        hngpt[1][2] = (rnk[1][2]+((cnk[1][2][2]*rk[8][2])+((cnk[1][2][0]*
          rk[8][0])+(cnk[1][2][1]*rk[8][1]))));
        hngpt[2][0] = (rnk[2][0]+((cnk[2][0][2]*rk[9][2])+((cnk[2][0][0]*
          rk[9][0])+(cnk[2][0][1]*rk[9][1]))));
        hngpt[2][1] = (rnk[2][1]+((cnk[2][1][2]*rk[9][2])+((cnk[2][1][0]*
          rk[9][0])+(cnk[2][1][1]*rk[9][1]))));
        hngpt[2][2] = (rnk[2][2]+((cnk[2][2][2]*rk[9][2])+((cnk[2][2][0]*
          rk[9][0])+(cnk[2][2][1]*rk[9][1]))));
        hngpt[3][0] = (rnk[3][0]+((cnk[3][0][2]*rk[10][2])+((cnk[3][0][0]*
          rk[10][0])+(cnk[3][0][1]*rk[10][1]))));
        hngpt[3][1] = (rnk[3][1]+((cnk[3][1][2]*rk[10][2])+((cnk[3][1][0]*
          rk[10][0])+(cnk[3][1][1]*rk[10][1]))));
        hngpt[3][2] = (rnk[3][2]+((cnk[3][2][2]*rk[10][2])+((cnk[3][2][0]*
          rk[10][0])+(cnk[3][2][1]*rk[10][1]))));
        hngpt[4][0] = (rnk[4][0]+((cnk[4][0][2]*rk[11][2])+((cnk[4][0][0]*
          rk[11][0])+(cnk[4][0][1]*rk[11][1]))));
        hngpt[4][1] = (rnk[4][1]+((cnk[4][1][2]*rk[11][2])+((cnk[4][1][0]*
          rk[11][0])+(cnk[4][1][1]*rk[11][1]))));
        hngpt[4][2] = (rnk[4][2]+((cnk[4][2][2]*rk[11][2])+((cnk[4][2][0]*
          rk[11][0])+(cnk[4][2][1]*rk[11][1]))));
        vpkflg = 1;
    }
/*
 Used -0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain   75 adds/subtracts/negates
                     90 multiplies
                      0 divides
                     30 assignments
*/
}

void sddoltau(void)
{

/*
Compute effect of loop hinge torques
*/
/*
 Used -0.00 seconds CPU time,
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
        Otk[1][0] = ((Wik[1][2]*wk[1][1])-(Wik[1][1]*wk[1][2]));
        Otk[1][1] = ((Wik[1][0]*wk[1][2])-(Wik[1][2]*wk[1][0]));
        Otk[1][2] = ((Wik[1][1]*wk[1][0])-(Wik[1][0]*wk[1][1]));
        Otk[2][0] = (((Cik[2][2][0]*Otk[1][2])+((Cik[2][0][0]*Otk[1][0])+(
          Cik[2][1][0]*Otk[1][1])))+((Wik[2][2]*wk[2][1])-(Wik[2][1]*wk[2][2])))
          ;
        Otk[2][1] = (((Cik[2][2][1]*Otk[1][2])+((Cik[2][0][1]*Otk[1][0])+(
          Cik[2][1][1]*Otk[1][1])))+((Wik[2][0]*wk[2][2])-(Wik[2][2]*wk[2][0])))
          ;
        Otk[2][2] = (((Cik[2][2][2]*Otk[1][2])+((Cik[2][0][2]*Otk[1][0])+(
          Cik[2][1][2]*Otk[1][1])))+((Wik[2][1]*wk[2][0])-(Wik[2][0]*wk[2][1])))
          ;
        Otk[3][0] = (((Cik[3][2][0]*Otk[2][2])+((Cik[3][0][0]*Otk[2][0])+(
          Cik[3][1][0]*Otk[2][1])))+((Wik[3][2]*wk[3][1])-(Wik[3][1]*wk[3][2])))
          ;
        Otk[3][1] = (((Cik[3][2][1]*Otk[2][2])+((Cik[3][0][1]*Otk[2][0])+(
          Cik[3][1][1]*Otk[2][1])))+((Wik[3][0]*wk[3][2])-(Wik[3][2]*wk[3][0])))
          ;
        Otk[3][2] = (((Cik[3][2][2]*Otk[2][2])+((Cik[3][0][2]*Otk[2][0])+(
          Cik[3][1][2]*Otk[2][1])))+((Wik[3][1]*wk[3][0])-(Wik[3][0]*wk[3][1])))
          ;
        Otk[4][0] = (((Cik[4][2][0]*Otk[3][2])+((Cik[4][0][0]*Otk[3][0])+(
          Cik[4][1][0]*Otk[3][1])))+((Wik[4][2]*wk[4][1])-(Wik[4][1]*wk[4][2])))
          ;
        Otk[4][1] = (((Cik[4][2][1]*Otk[3][2])+((Cik[4][0][1]*Otk[3][0])+(
          Cik[4][1][1]*Otk[3][1])))+((Wik[4][0]*wk[4][2])-(Wik[4][2]*wk[4][0])))
          ;
        Otk[4][2] = (((Cik[4][2][2]*Otk[3][2])+((Cik[4][0][2]*Otk[3][0])+(
          Cik[4][1][2]*Otk[3][1])))+((Wik[4][1]*wk[4][0])-(Wik[4][0]*wk[4][1])))
          ;
/*
Compute Atk (inertial linear acceleration)
*/
        Atk[0][0] = ((Wik[0][1]*Wkrpk[0][2])-(Wik[0][2]*Wkrpk[0][1]));
        Atk[0][1] = ((Wik[0][2]*Wkrpk[0][0])-(Wik[0][0]*Wkrpk[0][2]));
        Atk[0][2] = ((Wik[0][0]*Wkrpk[0][1])-(Wik[0][1]*Wkrpk[0][0]));
        AiOiWi[1][0] = (Atk[0][0]+((Wik[0][1]*Wirk[1][2])-(Wik[0][2]*Wirk[1][1])
          ));
        AiOiWi[1][1] = (Atk[0][1]+((Wik[0][2]*Wirk[1][0])-(Wik[0][0]*Wirk[1][2])
          ));
        AiOiWi[1][2] = (Atk[0][2]+((Wik[0][0]*Wirk[1][1])-(Wik[0][1]*Wirk[1][0])
          ));
        Atk[1][0] = (((AiOiWi[1][2]*Cik[1][2][0])+((AiOiWi[1][0]*Cik[1][0][0])+(
          AiOiWi[1][1]*Cik[1][1][0])))+(((Otk[1][2]*rk[8][1])-(Otk[1][1]*
          rk[8][2]))+((wk[1][1]*Wkrpk[1][2])-(wk[1][2]*Wkrpk[1][1]))));
        Atk[1][1] = (((AiOiWi[1][2]*Cik[1][2][1])+((AiOiWi[1][0]*Cik[1][0][1])+(
          AiOiWi[1][1]*Cik[1][1][1])))+(((Otk[1][0]*rk[8][2])-(Otk[1][2]*
          rk[8][0]))+((wk[1][2]*Wkrpk[1][0])-(wk[1][0]*Wkrpk[1][2]))));
        Atk[1][2] = (((AiOiWi[1][2]*Cik[1][2][2])+((AiOiWi[1][0]*Cik[1][0][2])+(
          AiOiWi[1][1]*Cik[1][1][2])))+(((Otk[1][1]*rk[8][0])-(Otk[1][0]*
          rk[8][1]))+((wk[1][0]*Wkrpk[1][1])-(wk[1][1]*Wkrpk[1][0]))));
        AiOiWi[2][0] = (Atk[1][0]+(((Otk[1][1]*ri[9][2])-(Otk[1][2]*ri[9][1]))+(
          (Wirk[2][2]*wk[1][1])-(Wirk[2][1]*wk[1][2]))));
        AiOiWi[2][1] = (Atk[1][1]+(((Otk[1][2]*ri[9][0])-(Otk[1][0]*ri[9][2]))+(
          (Wirk[2][0]*wk[1][2])-(Wirk[2][2]*wk[1][0]))));
        AiOiWi[2][2] = (Atk[1][2]+(((Otk[1][0]*ri[9][1])-(Otk[1][1]*ri[9][0]))+(
          (Wirk[2][1]*wk[1][0])-(Wirk[2][0]*wk[1][1]))));
        Atk[2][0] = (((AiOiWi[2][2]*Cik[2][2][0])+((AiOiWi[2][0]*Cik[2][0][0])+(
          AiOiWi[2][1]*Cik[2][1][0])))+(((Otk[2][2]*rk[9][1])-(Otk[2][1]*
          rk[9][2]))+((wk[2][1]*Wkrpk[2][2])-(wk[2][2]*Wkrpk[2][1]))));
        Atk[2][1] = (((AiOiWi[2][2]*Cik[2][2][1])+((AiOiWi[2][0]*Cik[2][0][1])+(
          AiOiWi[2][1]*Cik[2][1][1])))+(((Otk[2][0]*rk[9][2])-(Otk[2][2]*
          rk[9][0]))+((wk[2][2]*Wkrpk[2][0])-(wk[2][0]*Wkrpk[2][2]))));
        Atk[2][2] = (((AiOiWi[2][2]*Cik[2][2][2])+((AiOiWi[2][0]*Cik[2][0][2])+(
          AiOiWi[2][1]*Cik[2][1][2])))+(((Otk[2][1]*rk[9][0])-(Otk[2][0]*
          rk[9][1]))+((wk[2][0]*Wkrpk[2][1])-(wk[2][1]*Wkrpk[2][0]))));
        AiOiWi[3][0] = (Atk[2][0]+(((Otk[2][1]*ri[10][2])-(Otk[2][2]*ri[10][1]))
          +((Wirk[3][2]*wk[2][1])-(Wirk[3][1]*wk[2][2]))));
        AiOiWi[3][1] = (Atk[2][1]+(((Otk[2][2]*ri[10][0])-(Otk[2][0]*ri[10][2]))
          +((Wirk[3][0]*wk[2][2])-(Wirk[3][2]*wk[2][0]))));
        AiOiWi[3][2] = (Atk[2][2]+(((Otk[2][0]*ri[10][1])-(Otk[2][1]*ri[10][0]))
          +((Wirk[3][1]*wk[2][0])-(Wirk[3][0]*wk[2][1]))));
        Atk[3][0] = (((AiOiWi[3][2]*Cik[3][2][0])+((AiOiWi[3][0]*Cik[3][0][0])+(
          AiOiWi[3][1]*Cik[3][1][0])))+(((Otk[3][2]*rk[10][1])-(Otk[3][1]*
          rk[10][2]))+((wk[3][1]*Wkrpk[3][2])-(wk[3][2]*Wkrpk[3][1]))));
        Atk[3][1] = (((AiOiWi[3][2]*Cik[3][2][1])+((AiOiWi[3][0]*Cik[3][0][1])+(
          AiOiWi[3][1]*Cik[3][1][1])))+(((Otk[3][0]*rk[10][2])-(Otk[3][2]*
          rk[10][0]))+((wk[3][2]*Wkrpk[3][0])-(wk[3][0]*Wkrpk[3][2]))));
        Atk[3][2] = (((AiOiWi[3][2]*Cik[3][2][2])+((AiOiWi[3][0]*Cik[3][0][2])+(
          AiOiWi[3][1]*Cik[3][1][2])))+(((Otk[3][1]*rk[10][0])-(Otk[3][0]*
          rk[10][1]))+((wk[3][0]*Wkrpk[3][1])-(wk[3][1]*Wkrpk[3][0]))));
        AiOiWi[4][0] = (Atk[3][0]+(((Otk[3][1]*ri[11][2])-(Otk[3][2]*ri[11][1]))
          +((Wirk[4][2]*wk[3][1])-(Wirk[4][1]*wk[3][2]))));
        AiOiWi[4][1] = (Atk[3][1]+(((Otk[3][2]*ri[11][0])-(Otk[3][0]*ri[11][2]))
          +((Wirk[4][0]*wk[3][2])-(Wirk[4][2]*wk[3][0]))));
        AiOiWi[4][2] = (Atk[3][2]+(((Otk[3][0]*ri[11][1])-(Otk[3][1]*ri[11][0]))
          +((Wirk[4][1]*wk[3][0])-(Wirk[4][0]*wk[3][1]))));
        Atk[4][0] = (((AiOiWi[4][2]*Cik[4][2][0])+((AiOiWi[4][0]*Cik[4][0][0])+(
          AiOiWi[4][1]*Cik[4][1][0])))+(((Otk[4][2]*rk[11][1])-(Otk[4][1]*
          rk[11][2]))+((wk[4][1]*Wkrpk[4][2])-(wk[4][2]*Wkrpk[4][1]))));
        Atk[4][1] = (((AiOiWi[4][2]*Cik[4][2][1])+((AiOiWi[4][0]*Cik[4][0][1])+(
          AiOiWi[4][1]*Cik[4][1][1])))+(((Otk[4][0]*rk[11][2])-(Otk[4][2]*
          rk[11][0]))+((wk[4][2]*Wkrpk[4][0])-(wk[4][0]*Wkrpk[4][2]))));
        Atk[4][2] = (((AiOiWi[4][2]*Cik[4][2][2])+((AiOiWi[4][0]*Cik[4][0][2])+(
          AiOiWi[4][1]*Cik[4][1][2])))+(((Otk[4][1]*rk[11][0])-(Otk[4][0]*
          rk[11][1]))+((wk[4][0]*Wkrpk[4][1])-(wk[4][1]*Wkrpk[4][0]))));
        inerflg = 1;
    }
/*
 Used -0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain  156 adds/subtracts/negates
                    183 multiplies
                      0 divides
                     39 assignments
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
        Fstar[0][0] = ((mk[7]*(Atk[0][0]-gk[0][0]))-ufk[7][0]);
        Fstar[0][1] = ((mk[7]*(Atk[0][1]-gk[0][1]))-ufk[7][1]);
        Fstar[0][2] = ((mk[7]*(Atk[0][2]-gk[0][2]))-ufk[7][2]);
        Fstar[1][0] = ((mk[8]*(Atk[1][0]-gk[1][0]))-ufk[8][0]);
        Fstar[1][1] = ((mk[8]*(Atk[1][1]-gk[1][1]))-ufk[8][1]);
        Fstar[1][2] = ((mk[8]*(Atk[1][2]-gk[1][2]))-ufk[8][2]);
        Fstar[2][0] = ((mk[9]*(Atk[2][0]-gk[2][0]))-ufk[9][0]);
        Fstar[2][1] = ((mk[9]*(Atk[2][1]-gk[2][1]))-ufk[9][1]);
        Fstar[2][2] = ((mk[9]*(Atk[2][2]-gk[2][2]))-ufk[9][2]);
        Fstar[3][0] = ((mk[10]*(Atk[3][0]-gk[3][0]))-ufk[10][0]);
        Fstar[3][1] = ((mk[10]*(Atk[3][1]-gk[3][1]))-ufk[10][1]);
        Fstar[3][2] = ((mk[10]*(Atk[3][2]-gk[3][2]))-ufk[10][2]);
        Fstar[4][0] = ((mk[11]*(Atk[4][0]-gk[4][0]))-ufk[11][0]);
        Fstar[4][1] = ((mk[11]*(Atk[4][1]-gk[4][1]))-ufk[11][1]);
        Fstar[4][2] = ((mk[11]*(Atk[4][2]-gk[4][2]))-ufk[11][2]);
/*
Compute Tstar (torques)
*/
        Tstar[0][0] = (WkIkWk[0][0]-utk[7][0]);
        Tstar[0][1] = (WkIkWk[0][1]-utk[7][1]);
        Tstar[0][2] = (WkIkWk[0][2]-utk[7][2]);
        Tstar[1][0] = ((WkIkWk[1][0]+((ik[8][0][2]*Otk[1][2])+((ik[8][0][0]*
          Otk[1][0])+(ik[8][0][1]*Otk[1][1]))))-utk[8][0]);
        Tstar[1][1] = ((WkIkWk[1][1]+((ik[8][1][2]*Otk[1][2])+((ik[8][1][0]*
          Otk[1][0])+(ik[8][1][1]*Otk[1][1]))))-utk[8][1]);
        Tstar[1][2] = ((WkIkWk[1][2]+((ik[8][2][2]*Otk[1][2])+((ik[8][2][0]*
          Otk[1][0])+(ik[8][2][1]*Otk[1][1]))))-utk[8][2]);
        Tstar[2][0] = ((WkIkWk[2][0]+((ik[9][0][2]*Otk[2][2])+((ik[9][0][0]*
          Otk[2][0])+(ik[9][0][1]*Otk[2][1]))))-utk[9][0]);
        Tstar[2][1] = ((WkIkWk[2][1]+((ik[9][1][2]*Otk[2][2])+((ik[9][1][0]*
          Otk[2][0])+(ik[9][1][1]*Otk[2][1]))))-utk[9][1]);
        Tstar[2][2] = ((WkIkWk[2][2]+((ik[9][2][2]*Otk[2][2])+((ik[9][2][0]*
          Otk[2][0])+(ik[9][2][1]*Otk[2][1]))))-utk[9][2]);
        Tstar[3][0] = ((WkIkWk[3][0]+((ik[10][0][2]*Otk[3][2])+((ik[10][0][0]*
          Otk[3][0])+(ik[10][0][1]*Otk[3][1]))))-utk[10][0]);
        Tstar[3][1] = ((WkIkWk[3][1]+((ik[10][1][2]*Otk[3][2])+((ik[10][1][0]*
          Otk[3][0])+(ik[10][1][1]*Otk[3][1]))))-utk[10][1]);
        Tstar[3][2] = ((WkIkWk[3][2]+((ik[10][2][2]*Otk[3][2])+((ik[10][2][0]*
          Otk[3][0])+(ik[10][2][1]*Otk[3][1]))))-utk[10][2]);
        Tstar[4][0] = ((WkIkWk[4][0]+((ik[11][0][2]*Otk[4][2])+((ik[11][0][0]*
          Otk[4][0])+(ik[11][0][1]*Otk[4][1]))))-utk[11][0]);
        Tstar[4][1] = ((WkIkWk[4][1]+((ik[11][1][2]*Otk[4][2])+((ik[11][1][0]*
          Otk[4][0])+(ik[11][1][1]*Otk[4][1]))))-utk[11][1]);
        Tstar[4][2] = ((WkIkWk[4][2]+((ik[11][2][2]*Otk[4][2])+((ik[11][2][0]*
          Otk[4][0])+(ik[11][2][1]*Otk[4][1]))))-utk[11][2]);
/*
Compute fs0 (RHS ignoring constraints)
*/
        fs0[4] = (utau[4]-(((Fstar[4][2]*rkWkk[4][2])+((Fstar[4][0]*rkWkk[4][0])
          +(Fstar[4][1]*rkWkk[4][1])))+((pin[4][2]*Tstar[4][2])+((pin[4][0]*
          Tstar[4][0])+(pin[4][1]*Tstar[4][1])))));
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
        fs0[3] = (utau[3]-(((Fstark[3][2]*rkWkk[3][2])+((Fstark[3][0]*
          rkWkk[3][0])+(Fstark[3][1]*rkWkk[3][1])))+((pin[3][2]*Tstark[3][2])+((
          pin[3][0]*Tstark[3][0])+(pin[3][1]*Tstark[3][1])))));
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
        fs0[2] = (utau[2]-(((Fstark[2][2]*rkWkk[2][2])+((Fstark[2][0]*
          rkWkk[2][0])+(Fstark[2][1]*rkWkk[2][1])))+((pin[2][2]*Tstark[2][2])+((
          pin[2][0]*Tstark[2][0])+(pin[2][1]*Tstark[2][1])))));
        Fstark[1][0] = (Fstar[1][0]+((Cik[2][0][2]*Fstark[2][2])+((Cik[2][0][0]*
          Fstark[2][0])+(Cik[2][0][1]*Fstark[2][1]))));
        Fstark[1][1] = (Fstar[1][1]+((Cik[2][1][2]*Fstark[2][2])+((Cik[2][1][0]*
          Fstark[2][0])+(Cik[2][1][1]*Fstark[2][1]))));
        Fstark[1][2] = (Fstar[1][2]+((Cik[2][2][2]*Fstark[2][2])+((Cik[2][2][0]*
          Fstark[2][0])+(Cik[2][2][1]*Fstark[2][1]))));
        tvec1[0] = (Tstark[2][0]+((Fstark[2][2]*rik[2][1])-(Fstark[2][1]*
          rik[2][2])));
        tvec1[1] = (Tstark[2][1]+((Fstark[2][0]*rik[2][2])-(Fstark[2][2]*
          rik[2][0])));
        tvec1[2] = (Tstark[2][2]+((Fstark[2][1]*rik[2][0])-(Fstark[2][0]*
          rik[2][1])));
        Tstark[1][0] = (Tstar[1][0]+((Cik[2][0][2]*tvec1[2])+((Cik[2][0][0]*
          tvec1[0])+(Cik[2][0][1]*tvec1[1]))));
        Tstark[1][1] = (Tstar[1][1]+((Cik[2][1][2]*tvec1[2])+((Cik[2][1][0]*
          tvec1[0])+(Cik[2][1][1]*tvec1[1]))));
        Tstark[1][2] = (Tstar[1][2]+((Cik[2][2][2]*tvec1[2])+((Cik[2][2][0]*
          tvec1[0])+(Cik[2][2][1]*tvec1[1]))));
        fs0[1] = (utau[1]-(((Fstark[1][2]*rkWkk[1][2])+((Fstark[1][0]*
          rkWkk[1][0])+(Fstark[1][1]*rkWkk[1][1])))+((pin[1][2]*Tstark[1][2])+((
          pin[1][0]*Tstark[1][0])+(pin[1][1]*Tstark[1][1])))));
        Fstark[0][0] = (Fstar[0][0]+((Cik[1][0][2]*Fstark[1][2])+((Cik[1][0][0]*
          Fstark[1][0])+(Cik[1][0][1]*Fstark[1][1]))));
        Fstark[0][1] = (Fstar[0][1]+((Cik[1][1][2]*Fstark[1][2])+((Cik[1][1][0]*
          Fstark[1][0])+(Cik[1][1][1]*Fstark[1][1]))));
        Fstark[0][2] = (Fstar[0][2]+((Cik[1][2][2]*Fstark[1][2])+((Cik[1][2][0]*
          Fstark[1][0])+(Cik[1][2][1]*Fstark[1][1]))));
        tvec1[0] = (Tstark[1][0]+((Fstark[1][2]*rik[1][1])-(Fstark[1][1]*
          rik[1][2])));
        tvec1[1] = (Tstark[1][1]+((Fstark[1][0]*rik[1][2])-(Fstark[1][2]*
          rik[1][0])));
        tvec1[2] = (Tstark[1][2]+((Fstark[1][1]*rik[1][0])-(Fstark[1][0]*
          rik[1][1])));
        Tstark[0][0] = (Tstar[0][0]+((Cik[1][0][2]*tvec1[2])+((Cik[1][0][0]*
          tvec1[0])+(Cik[1][0][1]*tvec1[1]))));
        Tstark[0][1] = (Tstar[0][1]+((Cik[1][1][2]*tvec1[2])+((Cik[1][1][0]*
          tvec1[0])+(Cik[1][1][1]*tvec1[1]))));
        Tstark[0][2] = (Tstar[0][2]+((Cik[1][2][2]*tvec1[2])+((Cik[1][2][0]*
          tvec1[0])+(Cik[1][2][1]*tvec1[1]))));
        fs0[0] = (utau[0]-(((Fstark[0][2]*rkWkk[0][2])+((Fstark[0][0]*
          rkWkk[0][0])+(Fstark[0][1]*rkWkk[0][1])))+((pin[0][2]*Tstark[0][2])+((
          pin[0][0]*Tstark[0][0])+(pin[0][1]*Tstark[0][1])))));
        fs0flg = 1;
    }
/*
 Used -0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain  207 adds/subtracts/negates
                    177 multiplies
                      0 divides
                     71 assignments
*/
}

void sddomm(int routine)
{
    int dumroutine,errnum;

    if (mmflg == 0) {
/*
Compute gains (DD, G)
*/
        PH1[4][0] = ((mkrk[4][0][1]*pin[4][1])+(mkrk[4][0][2]*pin[4][2]));
        PH1[4][1] = ((mkrk[4][1][0]*pin[4][0])+(mkrk[4][1][2]*pin[4][2]));
        PH1[4][2] = ((mkrk[4][2][0]*pin[4][0])+(mkrk[4][2][1]*pin[4][1]));
        PH2[4][0] = ((Iko[4][0][2]*pin[4][2])+((Iko[4][0][0]*pin[4][0])+(
          Iko[4][0][1]*pin[4][1])));
        PH2[4][1] = ((Iko[4][1][2]*pin[4][2])+((Iko[4][1][0]*pin[4][0])+(
          Iko[4][1][1]*pin[4][1])));
        PH2[4][2] = ((Iko[4][2][2]*pin[4][2])+((Iko[4][2][0]*pin[4][0])+(
          Iko[4][2][1]*pin[4][1])));
        DD[4] = ((PH2[4][2]*pin[4][2])+((PH2[4][0]*pin[4][0])+(PH2[4][1]*
          pin[4][1])));
        if (DD[4] < 1e-13) {
            sdseterr(17,47);
        } else {
            DD[4] = (1./DD[4]);
        }
        G1[4][0] = (DD[4]*PH1[4][0]);
        G1[4][1] = (DD[4]*PH1[4][1]);
        G1[4][2] = (DD[4]*PH1[4][2]);
        G2[4][0] = (DD[4]*PH2[4][0]);
        G2[4][1] = (DD[4]*PH2[4][1]);
        G2[4][2] = (DD[4]*PH2[4][2]);
        P11[4][0][0] = (mk[11]-(G1[4][0]*PH1[4][0]));
        P11[4][0][1] = -(G1[4][1]*PH1[4][0]);
        P11[4][0][2] = -(G1[4][2]*PH1[4][0]);
        P11[4][1][1] = (mk[11]-(G1[4][1]*PH1[4][1]));
        P11[4][1][2] = -(G1[4][2]*PH1[4][1]);
        P11[4][2][2] = (mk[11]-(G1[4][2]*PH1[4][2]));
        Pd[4][0][0] = -(G2[4][0]*PH1[4][0]);
        Pd[4][0][1] = (mkrk[4][0][1]-(G2[4][1]*PH1[4][0]));
        Pd[4][0][2] = (mkrk[4][0][2]-(G2[4][2]*PH1[4][0]));
        Pd[4][1][0] = (mkrk[4][1][0]-(G2[4][0]*PH1[4][1]));
        Pd[4][1][1] = -(G2[4][1]*PH1[4][1]);
        Pd[4][1][2] = (mkrk[4][1][2]-(G2[4][2]*PH1[4][1]));
        Pd[4][2][0] = (mkrk[4][2][0]-(G2[4][0]*PH1[4][2]));
        Pd[4][2][1] = (mkrk[4][2][1]-(G2[4][1]*PH1[4][2]));
        Pd[4][2][2] = -(G2[4][2]*PH1[4][2]);
        P22[4][0][0] = (Iko[4][0][0]-(G2[4][0]*PH2[4][0]));
        P22[4][0][1] = (Iko[4][0][1]-(G2[4][1]*PH2[4][0]));
        P22[4][0][2] = (Iko[4][0][2]-(G2[4][2]*PH2[4][0]));
        P22[4][1][1] = (Iko[4][1][1]-(G2[4][1]*PH2[4][1]));
        P22[4][1][2] = (Iko[4][1][2]-(G2[4][2]*PH2[4][1]));
        P22[4][2][2] = (Iko[4][2][2]-(G2[4][2]*PH2[4][2]));
        sD1INV[0][0] = 0.;
        if (P11[4][0][0] >= 1e-13) {
            sD1INV[0][0] = (1./P11[4][0][0]);
        }
        sL11[1][0] = (P11[4][0][1]*sD1INV[0][0]);
        sL11[2][0] = (P11[4][0][2]*sD1INV[0][0]);
        sL11D1[1][1] = (P11[4][1][1]-(P11[4][0][1]*sL11[1][0]));
        sL11D1[2][1] = (P11[4][1][2]-(P11[4][0][2]*sL11[1][0]));
        sL11D1[2][2] = (P11[4][2][2]-(P11[4][0][2]*sL11[2][0]));
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
        sD1L21[1][0] = (Pd[4][1][0]-(Pd[4][0][0]*sL11[1][0]));
        sD1L21[1][1] = (Pd[4][1][1]-(Pd[4][0][1]*sL11[1][0]));
        sD1L21[1][2] = (Pd[4][1][2]-(Pd[4][0][2]*sL11[1][0]));
        sD1L21[2][0] = (Pd[4][2][0]-((Pd[4][0][0]*sL11[2][0])+(sD1L21[1][0]*
          sL11[2][1])));
        sD1L21[2][1] = (Pd[4][2][1]-((Pd[4][0][1]*sL11[2][0])+(sD1L21[1][1]*
          sL11[2][1])));
        sD1L21[2][2] = (Pd[4][2][2]-((Pd[4][0][2]*sL11[2][0])+(sD1L21[1][2]*
          sL11[2][1])));
        sL21[0][0] = (Pd[4][0][0]*sD1INV[0][0]);
        sL21[0][1] = (sD1INV[1][1]*sD1L21[1][0]);
        sL21[0][2] = (sD1INV[2][2]*sD1L21[2][0]);
        sL21[1][0] = (Pd[4][0][1]*sD1INV[0][0]);
        sL21[1][1] = (sD1INV[1][1]*sD1L21[1][1]);
        sL21[1][2] = (sD1INV[2][2]*sD1L21[2][1]);
        sL21[2][0] = (Pd[4][0][2]*sD1INV[0][0]);
        sL21[2][1] = (sD1INV[1][1]*sD1L21[1][2]);
        sL21[2][2] = (sD1INV[2][2]*sD1L21[2][2]);
        sL22D2[0][0] = (P22[4][0][0]-((sD1L21[2][0]*sL21[0][2])+((Pd[4][0][0]*
          sL21[0][0])+(sD1L21[1][0]*sL21[0][1]))));
        sL22D2[1][0] = (P22[4][0][1]-((sD1L21[2][0]*sL21[1][2])+((Pd[4][0][0]*
          sL21[1][0])+(sD1L21[1][0]*sL21[1][1]))));
        sL22D2[1][1] = (P22[4][1][1]-((sD1L21[2][1]*sL21[1][2])+((Pd[4][0][1]*
          sL21[1][0])+(sD1L21[1][1]*sL21[1][1]))));
        sL22D2[2][0] = (P22[4][0][2]-((sD1L21[2][0]*sL21[2][2])+((Pd[4][0][0]*
          sL21[2][0])+(sD1L21[1][0]*sL21[2][1]))));
        sL22D2[2][1] = (P22[4][1][2]-((sD1L21[2][1]*sL21[2][2])+((Pd[4][0][1]*
          sL21[2][0])+(sD1L21[1][1]*sL21[2][1]))));
        sL22D2[2][2] = (P22[4][2][2]-((sD1L21[2][2]*sL21[2][2])+((Pd[4][0][2]*
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
        N11[4][0][0] = ((Cik[4][0][0]+(Cik[4][0][1]*sL11[1][0]))+(Cik[4][0][2]*
          sL11[2][0]));
        N11[4][0][1] = (Cik[4][0][1]+(Cik[4][0][2]*sL11[2][1]));
        N11[4][1][0] = ((Cik[4][1][0]+(Cik[4][1][1]*sL11[1][0]))+(Cik[4][1][2]*
          sL11[2][0]));
        N11[4][1][1] = (Cik[4][1][1]+(Cik[4][1][2]*sL11[2][1]));
        N11[4][2][0] = ((Cik[4][2][0]+(Cik[4][2][1]*sL11[1][0]))+(Cik[4][2][2]*
          sL11[2][0]));
        N11[4][2][1] = (Cik[4][2][1]+(Cik[4][2][2]*sL11[2][1]));
        N21[4][0][0] = (((Cik[4][0][2]*sL21[2][0])+((Cik[4][0][0]*sL21[0][0])+(
          Cik[4][0][1]*sL21[1][0])))+((rikt[4][0][0]+(rikt[4][0][1]*sL11[1][0]))
          +(rikt[4][0][2]*sL11[2][0])));
        N21[4][0][1] = ((rikt[4][0][1]+(rikt[4][0][2]*sL11[2][1]))+((
          Cik[4][0][2]*sL21[2][1])+((Cik[4][0][0]*sL21[0][1])+(Cik[4][0][1]*
          sL21[1][1]))));
        N21[4][0][2] = (rikt[4][0][2]+((Cik[4][0][2]*sL21[2][2])+((Cik[4][0][0]*
          sL21[0][2])+(Cik[4][0][1]*sL21[1][2]))));
        N21[4][1][0] = (((Cik[4][1][2]*sL21[2][0])+((Cik[4][1][0]*sL21[0][0])+(
          Cik[4][1][1]*sL21[1][0])))+((rikt[4][1][0]+(rikt[4][1][1]*sL11[1][0]))
          +(rikt[4][1][2]*sL11[2][0])));
        N21[4][1][1] = ((rikt[4][1][1]+(rikt[4][1][2]*sL11[2][1]))+((
          Cik[4][1][2]*sL21[2][1])+((Cik[4][1][0]*sL21[0][1])+(Cik[4][1][1]*
          sL21[1][1]))));
        N21[4][1][2] = (rikt[4][1][2]+((Cik[4][1][2]*sL21[2][2])+((Cik[4][1][0]*
          sL21[0][2])+(Cik[4][1][1]*sL21[1][2]))));
        N21[4][2][0] = (((Cik[4][2][2]*sL21[2][0])+((Cik[4][2][0]*sL21[0][0])+(
          Cik[4][2][1]*sL21[1][0])))+((rikt[4][2][0]+(rikt[4][2][1]*sL11[1][0]))
          +(rikt[4][2][2]*sL11[2][0])));
        N21[4][2][1] = ((rikt[4][2][1]+(rikt[4][2][2]*sL11[2][1]))+((
          Cik[4][2][2]*sL21[2][1])+((Cik[4][2][0]*sL21[0][1])+(Cik[4][2][1]*
          sL21[1][1]))));
        N21[4][2][2] = (rikt[4][2][2]+((Cik[4][2][2]*sL21[2][2])+((Cik[4][2][0]*
          sL21[0][2])+(Cik[4][2][1]*sL21[1][2]))));
        N22[4][0][0] = ((Cik[4][0][0]+(Cik[4][0][1]*sL22[1][0]))+(Cik[4][0][2]*
          sL22[2][0]));
        N22[4][0][1] = (Cik[4][0][1]+(Cik[4][0][2]*sL22[2][1]));
        N22[4][1][0] = ((Cik[4][1][0]+(Cik[4][1][1]*sL22[1][0]))+(Cik[4][1][2]*
          sL22[2][0]));
        N22[4][1][1] = (Cik[4][1][1]+(Cik[4][1][2]*sL22[2][1]));
        N22[4][2][0] = ((Cik[4][2][0]+(Cik[4][2][1]*sL22[1][0]))+(Cik[4][2][2]*
          sL22[2][0]));
        N22[4][2][1] = (Cik[4][2][1]+(Cik[4][2][2]*sL22[2][1]));
        psiD11[4][0][0] = (N11[4][0][0]*P11[4][0][0]);
        psiD11[4][0][1] = (N11[4][0][1]*sL11D1[1][1]);
        psiD11[4][0][2] = (Cik[4][0][2]*sL11D1[2][2]);
        psiD11[4][1][0] = (N11[4][1][0]*P11[4][0][0]);
        psiD11[4][1][1] = (N11[4][1][1]*sL11D1[1][1]);
        psiD11[4][1][2] = (Cik[4][1][2]*sL11D1[2][2]);
        psiD11[4][2][0] = (N11[4][2][0]*P11[4][0][0]);
        psiD11[4][2][1] = (N11[4][2][1]*sL11D1[1][1]);
        psiD11[4][2][2] = (Cik[4][2][2]*sL11D1[2][2]);
        psiD21[4][0][0] = (N21[4][0][0]*P11[4][0][0]);
        psiD21[4][0][1] = (N21[4][0][1]*sL11D1[1][1]);
        psiD21[4][0][2] = (N21[4][0][2]*sL11D1[2][2]);
        psiD21[4][1][0] = (N21[4][1][0]*P11[4][0][0]);
        psiD21[4][1][1] = (N21[4][1][1]*sL11D1[1][1]);
        psiD21[4][1][2] = (N21[4][1][2]*sL11D1[2][2]);
        psiD21[4][2][0] = (N21[4][2][0]*P11[4][0][0]);
        psiD21[4][2][1] = (N21[4][2][1]*sL11D1[1][1]);
        psiD21[4][2][2] = (N21[4][2][2]*sL11D1[2][2]);
        psiD22[4][0][0] = (N22[4][0][0]*sL22D2[0][0]);
        psiD22[4][0][1] = (N22[4][0][1]*sL22D2[1][1]);
        psiD22[4][0][2] = (Cik[4][0][2]*sL22D2[2][2]);
        psiD22[4][1][0] = (N22[4][1][0]*sL22D2[0][0]);
        psiD22[4][1][1] = (N22[4][1][1]*sL22D2[1][1]);
        psiD22[4][1][2] = (Cik[4][1][2]*sL22D2[2][2]);
        psiD22[4][2][0] = (N22[4][2][0]*sL22D2[0][0]);
        psiD22[4][2][1] = (N22[4][2][1]*sL22D2[1][1]);
        psiD22[4][2][2] = (Cik[4][2][2]*sL22D2[2][2]);
        P11[3][0][0] = (mk[10]+((Cik[4][0][2]*psiD11[4][0][2])+((N11[4][0][0]*
          psiD11[4][0][0])+(N11[4][0][1]*psiD11[4][0][1]))));
        P11[3][0][1] = ((Cik[4][1][2]*psiD11[4][0][2])+((N11[4][1][0]*
          psiD11[4][0][0])+(N11[4][1][1]*psiD11[4][0][1])));
        P11[3][0][2] = ((Cik[4][2][2]*psiD11[4][0][2])+((N11[4][2][0]*
          psiD11[4][0][0])+(N11[4][2][1]*psiD11[4][0][1])));
        P11[3][1][0] = P11[3][0][1];
        P11[3][1][1] = (mk[10]+((Cik[4][1][2]*psiD11[4][1][2])+((N11[4][1][0]*
          psiD11[4][1][0])+(N11[4][1][1]*psiD11[4][1][1]))));
        P11[3][1][2] = ((Cik[4][2][2]*psiD11[4][1][2])+((N11[4][2][0]*
          psiD11[4][1][0])+(N11[4][2][1]*psiD11[4][1][1])));
        P11[3][2][0] = P11[3][0][2];
        P11[3][2][1] = P11[3][1][2];
        P11[3][2][2] = (mk[10]+((Cik[4][2][2]*psiD11[4][2][2])+((N11[4][2][0]*
          psiD11[4][2][0])+(N11[4][2][1]*psiD11[4][2][1]))));
        Pd[3][0][0] = ((N21[4][0][2]*psiD11[4][0][2])+((N21[4][0][0]*
          psiD11[4][0][0])+(N21[4][0][1]*psiD11[4][0][1])));
        Pd[3][0][1] = (mkrk[3][0][1]+((N21[4][1][2]*psiD11[4][0][2])+((
          N21[4][1][0]*psiD11[4][0][0])+(N21[4][1][1]*psiD11[4][0][1]))));
        Pd[3][0][2] = (mkrk[3][0][2]+((N21[4][2][2]*psiD11[4][0][2])+((
          N21[4][2][0]*psiD11[4][0][0])+(N21[4][2][1]*psiD11[4][0][1]))));
        Pd[3][1][0] = (mkrk[3][1][0]+((N21[4][0][2]*psiD11[4][1][2])+((
          N21[4][0][0]*psiD11[4][1][0])+(N21[4][0][1]*psiD11[4][1][1]))));
        Pd[3][1][1] = ((N21[4][1][2]*psiD11[4][1][2])+((N21[4][1][0]*
          psiD11[4][1][0])+(N21[4][1][1]*psiD11[4][1][1])));
        Pd[3][1][2] = (mkrk[3][1][2]+((N21[4][2][2]*psiD11[4][1][2])+((
          N21[4][2][0]*psiD11[4][1][0])+(N21[4][2][1]*psiD11[4][1][1]))));
        Pd[3][2][0] = (mkrk[3][2][0]+((N21[4][0][2]*psiD11[4][2][2])+((
          N21[4][0][0]*psiD11[4][2][0])+(N21[4][0][1]*psiD11[4][2][1]))));
        Pd[3][2][1] = (mkrk[3][2][1]+((N21[4][1][2]*psiD11[4][2][2])+((
          N21[4][1][0]*psiD11[4][2][0])+(N21[4][1][1]*psiD11[4][2][1]))));
        Pd[3][2][2] = ((N21[4][2][2]*psiD11[4][2][2])+((N21[4][2][0]*
          psiD11[4][2][0])+(N21[4][2][1]*psiD11[4][2][1])));
        P22[3][0][0] = (Iko[3][0][0]+(((Cik[4][0][2]*psiD22[4][0][2])+((
          N22[4][0][0]*psiD22[4][0][0])+(N22[4][0][1]*psiD22[4][0][1])))+((
          N21[4][0][2]*psiD21[4][0][2])+((N21[4][0][0]*psiD21[4][0][0])+(
          N21[4][0][1]*psiD21[4][0][1])))));
        P22[3][0][1] = (Iko[3][0][1]+(((Cik[4][1][2]*psiD22[4][0][2])+((
          N22[4][1][0]*psiD22[4][0][0])+(N22[4][1][1]*psiD22[4][0][1])))+((
          N21[4][1][2]*psiD21[4][0][2])+((N21[4][1][0]*psiD21[4][0][0])+(
          N21[4][1][1]*psiD21[4][0][1])))));
        P22[3][0][2] = (Iko[3][0][2]+(((Cik[4][2][2]*psiD22[4][0][2])+((
          N22[4][2][0]*psiD22[4][0][0])+(N22[4][2][1]*psiD22[4][0][1])))+((
          N21[4][2][2]*psiD21[4][0][2])+((N21[4][2][0]*psiD21[4][0][0])+(
          N21[4][2][1]*psiD21[4][0][1])))));
        P22[3][1][0] = P22[3][0][1];
        P22[3][1][1] = (Iko[3][1][1]+(((Cik[4][1][2]*psiD22[4][1][2])+((
          N22[4][1][0]*psiD22[4][1][0])+(N22[4][1][1]*psiD22[4][1][1])))+((
          N21[4][1][2]*psiD21[4][1][2])+((N21[4][1][0]*psiD21[4][1][0])+(
          N21[4][1][1]*psiD21[4][1][1])))));
        P22[3][1][2] = (Iko[3][1][2]+(((Cik[4][2][2]*psiD22[4][1][2])+((
          N22[4][2][0]*psiD22[4][1][0])+(N22[4][2][1]*psiD22[4][1][1])))+((
          N21[4][2][2]*psiD21[4][1][2])+((N21[4][2][0]*psiD21[4][1][0])+(
          N21[4][2][1]*psiD21[4][1][1])))));
        P22[3][2][0] = P22[3][0][2];
        P22[3][2][1] = P22[3][1][2];
        P22[3][2][2] = (Iko[3][2][2]+(((Cik[4][2][2]*psiD22[4][2][2])+((
          N22[4][2][0]*psiD22[4][2][0])+(N22[4][2][1]*psiD22[4][2][1])))+((
          N21[4][2][2]*psiD21[4][2][2])+((N21[4][2][0]*psiD21[4][2][0])+(
          N21[4][2][1]*psiD21[4][2][1])))));
        PH1[3][0] = ((Pd[3][0][2]*pin[3][2])+((Pd[3][0][0]*pin[3][0])+(
          Pd[3][0][1]*pin[3][1])));
        PH1[3][1] = ((Pd[3][1][2]*pin[3][2])+((Pd[3][1][0]*pin[3][0])+(
          Pd[3][1][1]*pin[3][1])));
        PH1[3][2] = ((Pd[3][2][2]*pin[3][2])+((Pd[3][2][0]*pin[3][0])+(
          Pd[3][2][1]*pin[3][1])));
        PH2[3][0] = ((P22[3][0][2]*pin[3][2])+((P22[3][0][0]*pin[3][0])+(
          P22[3][0][1]*pin[3][1])));
        PH2[3][1] = ((P22[3][1][2]*pin[3][2])+((P22[3][1][0]*pin[3][0])+(
          P22[3][1][1]*pin[3][1])));
        PH2[3][2] = ((P22[3][2][2]*pin[3][2])+((P22[3][2][0]*pin[3][0])+(
          P22[3][2][1]*pin[3][1])));
        DD[3] = ((PH2[3][2]*pin[3][2])+((PH2[3][0]*pin[3][0])+(PH2[3][1]*
          pin[3][1])));
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
        P11[2][0][0] = (mk[9]+((Cik[3][0][2]*psiD11[3][0][2])+((N11[3][0][0]*
          psiD11[3][0][0])+(N11[3][0][1]*psiD11[3][0][1]))));
        P11[2][0][1] = ((Cik[3][1][2]*psiD11[3][0][2])+((N11[3][1][0]*
          psiD11[3][0][0])+(N11[3][1][1]*psiD11[3][0][1])));
        P11[2][0][2] = ((Cik[3][2][2]*psiD11[3][0][2])+((N11[3][2][0]*
          psiD11[3][0][0])+(N11[3][2][1]*psiD11[3][0][1])));
        P11[2][1][0] = P11[2][0][1];
        P11[2][1][1] = (mk[9]+((Cik[3][1][2]*psiD11[3][1][2])+((N11[3][1][0]*
          psiD11[3][1][0])+(N11[3][1][1]*psiD11[3][1][1]))));
        P11[2][1][2] = ((Cik[3][2][2]*psiD11[3][1][2])+((N11[3][2][0]*
          psiD11[3][1][0])+(N11[3][2][1]*psiD11[3][1][1])));
        P11[2][2][0] = P11[2][0][2];
        P11[2][2][1] = P11[2][1][2];
        P11[2][2][2] = (mk[9]+((Cik[3][2][2]*psiD11[3][2][2])+((N11[3][2][0]*
          psiD11[3][2][0])+(N11[3][2][1]*psiD11[3][2][1]))));
        Pd[2][0][0] = ((N21[3][0][2]*psiD11[3][0][2])+((N21[3][0][0]*
          psiD11[3][0][0])+(N21[3][0][1]*psiD11[3][0][1])));
        Pd[2][0][1] = (mkrk[2][0][1]+((N21[3][1][2]*psiD11[3][0][2])+((
          N21[3][1][0]*psiD11[3][0][0])+(N21[3][1][1]*psiD11[3][0][1]))));
        Pd[2][0][2] = (mkrk[2][0][2]+((N21[3][2][2]*psiD11[3][0][2])+((
          N21[3][2][0]*psiD11[3][0][0])+(N21[3][2][1]*psiD11[3][0][1]))));
        Pd[2][1][0] = (mkrk[2][1][0]+((N21[3][0][2]*psiD11[3][1][2])+((
          N21[3][0][0]*psiD11[3][1][0])+(N21[3][0][1]*psiD11[3][1][1]))));
        Pd[2][1][1] = ((N21[3][1][2]*psiD11[3][1][2])+((N21[3][1][0]*
          psiD11[3][1][0])+(N21[3][1][1]*psiD11[3][1][1])));
        Pd[2][1][2] = (mkrk[2][1][2]+((N21[3][2][2]*psiD11[3][1][2])+((
          N21[3][2][0]*psiD11[3][1][0])+(N21[3][2][1]*psiD11[3][1][1]))));
        Pd[2][2][0] = (mkrk[2][2][0]+((N21[3][0][2]*psiD11[3][2][2])+((
          N21[3][0][0]*psiD11[3][2][0])+(N21[3][0][1]*psiD11[3][2][1]))));
        Pd[2][2][1] = (mkrk[2][2][1]+((N21[3][1][2]*psiD11[3][2][2])+((
          N21[3][1][0]*psiD11[3][2][0])+(N21[3][1][1]*psiD11[3][2][1]))));
        Pd[2][2][2] = ((N21[3][2][2]*psiD11[3][2][2])+((N21[3][2][0]*
          psiD11[3][2][0])+(N21[3][2][1]*psiD11[3][2][1])));
        P22[2][0][0] = (Iko[2][0][0]+(((Cik[3][0][2]*psiD22[3][0][2])+((
          N22[3][0][0]*psiD22[3][0][0])+(N22[3][0][1]*psiD22[3][0][1])))+((
          N21[3][0][2]*psiD21[3][0][2])+((N21[3][0][0]*psiD21[3][0][0])+(
          N21[3][0][1]*psiD21[3][0][1])))));
        P22[2][0][1] = (Iko[2][0][1]+(((Cik[3][1][2]*psiD22[3][0][2])+((
          N22[3][1][0]*psiD22[3][0][0])+(N22[3][1][1]*psiD22[3][0][1])))+((
          N21[3][1][2]*psiD21[3][0][2])+((N21[3][1][0]*psiD21[3][0][0])+(
          N21[3][1][1]*psiD21[3][0][1])))));
        P22[2][0][2] = (Iko[2][0][2]+(((Cik[3][2][2]*psiD22[3][0][2])+((
          N22[3][2][0]*psiD22[3][0][0])+(N22[3][2][1]*psiD22[3][0][1])))+((
          N21[3][2][2]*psiD21[3][0][2])+((N21[3][2][0]*psiD21[3][0][0])+(
          N21[3][2][1]*psiD21[3][0][1])))));
        P22[2][1][0] = P22[2][0][1];
        P22[2][1][1] = (Iko[2][1][1]+(((Cik[3][1][2]*psiD22[3][1][2])+((
          N22[3][1][0]*psiD22[3][1][0])+(N22[3][1][1]*psiD22[3][1][1])))+((
          N21[3][1][2]*psiD21[3][1][2])+((N21[3][1][0]*psiD21[3][1][0])+(
          N21[3][1][1]*psiD21[3][1][1])))));
        P22[2][1][2] = (Iko[2][1][2]+(((Cik[3][2][2]*psiD22[3][1][2])+((
          N22[3][2][0]*psiD22[3][1][0])+(N22[3][2][1]*psiD22[3][1][1])))+((
          N21[3][2][2]*psiD21[3][1][2])+((N21[3][2][0]*psiD21[3][1][0])+(
          N21[3][2][1]*psiD21[3][1][1])))));
        P22[2][2][0] = P22[2][0][2];
        P22[2][2][1] = P22[2][1][2];
        P22[2][2][2] = (Iko[2][2][2]+(((Cik[3][2][2]*psiD22[3][2][2])+((
          N22[3][2][0]*psiD22[3][2][0])+(N22[3][2][1]*psiD22[3][2][1])))+((
          N21[3][2][2]*psiD21[3][2][2])+((N21[3][2][0]*psiD21[3][2][0])+(
          N21[3][2][1]*psiD21[3][2][1])))));
        PH1[2][0] = ((Pd[2][0][2]*pin[2][2])+((Pd[2][0][0]*pin[2][0])+(
          Pd[2][0][1]*pin[2][1])));
        PH1[2][1] = ((Pd[2][1][2]*pin[2][2])+((Pd[2][1][0]*pin[2][0])+(
          Pd[2][1][1]*pin[2][1])));
        PH1[2][2] = ((Pd[2][2][2]*pin[2][2])+((Pd[2][2][0]*pin[2][0])+(
          Pd[2][2][1]*pin[2][1])));
        PH2[2][0] = ((P22[2][0][2]*pin[2][2])+((P22[2][0][0]*pin[2][0])+(
          P22[2][0][1]*pin[2][1])));
        PH2[2][1] = ((P22[2][1][2]*pin[2][2])+((P22[2][1][0]*pin[2][0])+(
          P22[2][1][1]*pin[2][1])));
        PH2[2][2] = ((P22[2][2][2]*pin[2][2])+((P22[2][2][0]*pin[2][0])+(
          P22[2][2][1]*pin[2][1])));
        DD[2] = ((PH2[2][2]*pin[2][2])+((PH2[2][0]*pin[2][0])+(PH2[2][1]*
          pin[2][1])));
        if (DD[2] < 1e-13) {
            sdseterr(17,47);
        } else {
            DD[2] = (1./DD[2]);
        }
        G1[2][0] = (DD[2]*PH1[2][0]);
        G1[2][1] = (DD[2]*PH1[2][1]);
        G1[2][2] = (DD[2]*PH1[2][2]);
        G2[2][0] = (DD[2]*PH2[2][0]);
        G2[2][1] = (DD[2]*PH2[2][1]);
        G2[2][2] = (DD[2]*PH2[2][2]);
        P11[2][0][0] = (P11[2][0][0]-(G1[2][0]*PH1[2][0]));
        P11[2][0][1] = (P11[2][0][1]-(G1[2][1]*PH1[2][0]));
        P11[2][0][2] = (P11[2][0][2]-(G1[2][2]*PH1[2][0]));
        P11[2][1][1] = (P11[2][1][1]-(G1[2][1]*PH1[2][1]));
        P11[2][1][2] = (P11[2][1][2]-(G1[2][2]*PH1[2][1]));
        P11[2][2][2] = (P11[2][2][2]-(G1[2][2]*PH1[2][2]));
        Pd[2][0][0] = (Pd[2][0][0]-(G2[2][0]*PH1[2][0]));
        Pd[2][0][1] = (Pd[2][0][1]-(G2[2][1]*PH1[2][0]));
        Pd[2][0][2] = (Pd[2][0][2]-(G2[2][2]*PH1[2][0]));
        Pd[2][1][0] = (Pd[2][1][0]-(G2[2][0]*PH1[2][1]));
        Pd[2][1][1] = (Pd[2][1][1]-(G2[2][1]*PH1[2][1]));
        Pd[2][1][2] = (Pd[2][1][2]-(G2[2][2]*PH1[2][1]));
        Pd[2][2][0] = (Pd[2][2][0]-(G2[2][0]*PH1[2][2]));
        Pd[2][2][1] = (Pd[2][2][1]-(G2[2][1]*PH1[2][2]));
        Pd[2][2][2] = (Pd[2][2][2]-(G2[2][2]*PH1[2][2]));
        P22[2][0][0] = (P22[2][0][0]-(G2[2][0]*PH2[2][0]));
        P22[2][0][1] = (P22[2][0][1]-(G2[2][1]*PH2[2][0]));
        P22[2][0][2] = (P22[2][0][2]-(G2[2][2]*PH2[2][0]));
        P22[2][1][1] = (P22[2][1][1]-(G2[2][1]*PH2[2][1]));
        P22[2][1][2] = (P22[2][1][2]-(G2[2][2]*PH2[2][1]));
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
        N11[2][0][0] = ((Cik[2][0][0]+(Cik[2][0][1]*sL11[1][0]))+(Cik[2][0][2]*
          sL11[2][0]));
        N11[2][0][1] = (Cik[2][0][1]+(Cik[2][0][2]*sL11[2][1]));
        N11[2][1][0] = ((Cik[2][1][0]+(Cik[2][1][1]*sL11[1][0]))+(Cik[2][1][2]*
          sL11[2][0]));
        N11[2][1][1] = (Cik[2][1][1]+(Cik[2][1][2]*sL11[2][1]));
        N11[2][2][0] = ((Cik[2][2][0]+(Cik[2][2][1]*sL11[1][0]))+(Cik[2][2][2]*
          sL11[2][0]));
        N11[2][2][1] = (Cik[2][2][1]+(Cik[2][2][2]*sL11[2][1]));
        N21[2][0][0] = (((Cik[2][0][2]*sL21[2][0])+((Cik[2][0][0]*sL21[0][0])+(
          Cik[2][0][1]*sL21[1][0])))+((rikt[2][0][0]+(rikt[2][0][1]*sL11[1][0]))
          +(rikt[2][0][2]*sL11[2][0])));
        N21[2][0][1] = ((rikt[2][0][1]+(rikt[2][0][2]*sL11[2][1]))+((
          Cik[2][0][2]*sL21[2][1])+((Cik[2][0][0]*sL21[0][1])+(Cik[2][0][1]*
          sL21[1][1]))));
        N21[2][0][2] = (rikt[2][0][2]+((Cik[2][0][2]*sL21[2][2])+((Cik[2][0][0]*
          sL21[0][2])+(Cik[2][0][1]*sL21[1][2]))));
        N21[2][1][0] = (((Cik[2][1][2]*sL21[2][0])+((Cik[2][1][0]*sL21[0][0])+(
          Cik[2][1][1]*sL21[1][0])))+((rikt[2][1][0]+(rikt[2][1][1]*sL11[1][0]))
          +(rikt[2][1][2]*sL11[2][0])));
        N21[2][1][1] = ((rikt[2][1][1]+(rikt[2][1][2]*sL11[2][1]))+((
          Cik[2][1][2]*sL21[2][1])+((Cik[2][1][0]*sL21[0][1])+(Cik[2][1][1]*
          sL21[1][1]))));
        N21[2][1][2] = (rikt[2][1][2]+((Cik[2][1][2]*sL21[2][2])+((Cik[2][1][0]*
          sL21[0][2])+(Cik[2][1][1]*sL21[1][2]))));
        N21[2][2][0] = (((Cik[2][2][2]*sL21[2][0])+((Cik[2][2][0]*sL21[0][0])+(
          Cik[2][2][1]*sL21[1][0])))+((rikt[2][2][0]+(rikt[2][2][1]*sL11[1][0]))
          +(rikt[2][2][2]*sL11[2][0])));
        N21[2][2][1] = ((rikt[2][2][1]+(rikt[2][2][2]*sL11[2][1]))+((
          Cik[2][2][2]*sL21[2][1])+((Cik[2][2][0]*sL21[0][1])+(Cik[2][2][1]*
          sL21[1][1]))));
        N21[2][2][2] = (rikt[2][2][2]+((Cik[2][2][2]*sL21[2][2])+((Cik[2][2][0]*
          sL21[0][2])+(Cik[2][2][1]*sL21[1][2]))));
        N22[2][0][0] = ((Cik[2][0][0]+(Cik[2][0][1]*sL22[1][0]))+(Cik[2][0][2]*
          sL22[2][0]));
        N22[2][0][1] = (Cik[2][0][1]+(Cik[2][0][2]*sL22[2][1]));
        N22[2][1][0] = ((Cik[2][1][0]+(Cik[2][1][1]*sL22[1][0]))+(Cik[2][1][2]*
          sL22[2][0]));
        N22[2][1][1] = (Cik[2][1][1]+(Cik[2][1][2]*sL22[2][1]));
        N22[2][2][0] = ((Cik[2][2][0]+(Cik[2][2][1]*sL22[1][0]))+(Cik[2][2][2]*
          sL22[2][0]));
        N22[2][2][1] = (Cik[2][2][1]+(Cik[2][2][2]*sL22[2][1]));
        psiD11[2][0][0] = (N11[2][0][0]*P11[2][0][0]);
        psiD11[2][0][1] = (N11[2][0][1]*sL11D1[1][1]);
        psiD11[2][0][2] = (Cik[2][0][2]*sL11D1[2][2]);
        psiD11[2][1][0] = (N11[2][1][0]*P11[2][0][0]);
        psiD11[2][1][1] = (N11[2][1][1]*sL11D1[1][1]);
        psiD11[2][1][2] = (Cik[2][1][2]*sL11D1[2][2]);
        psiD11[2][2][0] = (N11[2][2][0]*P11[2][0][0]);
        psiD11[2][2][1] = (N11[2][2][1]*sL11D1[1][1]);
        psiD11[2][2][2] = (Cik[2][2][2]*sL11D1[2][2]);
        psiD21[2][0][0] = (N21[2][0][0]*P11[2][0][0]);
        psiD21[2][0][1] = (N21[2][0][1]*sL11D1[1][1]);
        psiD21[2][0][2] = (N21[2][0][2]*sL11D1[2][2]);
        psiD21[2][1][0] = (N21[2][1][0]*P11[2][0][0]);
        psiD21[2][1][1] = (N21[2][1][1]*sL11D1[1][1]);
        psiD21[2][1][2] = (N21[2][1][2]*sL11D1[2][2]);
        psiD21[2][2][0] = (N21[2][2][0]*P11[2][0][0]);
        psiD21[2][2][1] = (N21[2][2][1]*sL11D1[1][1]);
        psiD21[2][2][2] = (N21[2][2][2]*sL11D1[2][2]);
        psiD22[2][0][0] = (N22[2][0][0]*sL22D2[0][0]);
        psiD22[2][0][1] = (N22[2][0][1]*sL22D2[1][1]);
        psiD22[2][0][2] = (Cik[2][0][2]*sL22D2[2][2]);
        psiD22[2][1][0] = (N22[2][1][0]*sL22D2[0][0]);
        psiD22[2][1][1] = (N22[2][1][1]*sL22D2[1][1]);
        psiD22[2][1][2] = (Cik[2][1][2]*sL22D2[2][2]);
        psiD22[2][2][0] = (N22[2][2][0]*sL22D2[0][0]);
        psiD22[2][2][1] = (N22[2][2][1]*sL22D2[1][1]);
        psiD22[2][2][2] = (Cik[2][2][2]*sL22D2[2][2]);
        P11[1][0][0] = (mk[8]+((Cik[2][0][2]*psiD11[2][0][2])+((N11[2][0][0]*
          psiD11[2][0][0])+(N11[2][0][1]*psiD11[2][0][1]))));
        P11[1][0][1] = ((Cik[2][1][2]*psiD11[2][0][2])+((N11[2][1][0]*
          psiD11[2][0][0])+(N11[2][1][1]*psiD11[2][0][1])));
        P11[1][0][2] = ((Cik[2][2][2]*psiD11[2][0][2])+((N11[2][2][0]*
          psiD11[2][0][0])+(N11[2][2][1]*psiD11[2][0][1])));
        P11[1][1][0] = P11[1][0][1];
        P11[1][1][1] = (mk[8]+((Cik[2][1][2]*psiD11[2][1][2])+((N11[2][1][0]*
          psiD11[2][1][0])+(N11[2][1][1]*psiD11[2][1][1]))));
        P11[1][1][2] = ((Cik[2][2][2]*psiD11[2][1][2])+((N11[2][2][0]*
          psiD11[2][1][0])+(N11[2][2][1]*psiD11[2][1][1])));
        P11[1][2][0] = P11[1][0][2];
        P11[1][2][1] = P11[1][1][2];
        P11[1][2][2] = (mk[8]+((Cik[2][2][2]*psiD11[2][2][2])+((N11[2][2][0]*
          psiD11[2][2][0])+(N11[2][2][1]*psiD11[2][2][1]))));
        Pd[1][0][0] = ((N21[2][0][2]*psiD11[2][0][2])+((N21[2][0][0]*
          psiD11[2][0][0])+(N21[2][0][1]*psiD11[2][0][1])));
        Pd[1][0][1] = (mkrk[1][0][1]+((N21[2][1][2]*psiD11[2][0][2])+((
          N21[2][1][0]*psiD11[2][0][0])+(N21[2][1][1]*psiD11[2][0][1]))));
        Pd[1][0][2] = (mkrk[1][0][2]+((N21[2][2][2]*psiD11[2][0][2])+((
          N21[2][2][0]*psiD11[2][0][0])+(N21[2][2][1]*psiD11[2][0][1]))));
        Pd[1][1][0] = (mkrk[1][1][0]+((N21[2][0][2]*psiD11[2][1][2])+((
          N21[2][0][0]*psiD11[2][1][0])+(N21[2][0][1]*psiD11[2][1][1]))));
        Pd[1][1][1] = ((N21[2][1][2]*psiD11[2][1][2])+((N21[2][1][0]*
          psiD11[2][1][0])+(N21[2][1][1]*psiD11[2][1][1])));
        Pd[1][1][2] = (mkrk[1][1][2]+((N21[2][2][2]*psiD11[2][1][2])+((
          N21[2][2][0]*psiD11[2][1][0])+(N21[2][2][1]*psiD11[2][1][1]))));
        Pd[1][2][0] = (mkrk[1][2][0]+((N21[2][0][2]*psiD11[2][2][2])+((
          N21[2][0][0]*psiD11[2][2][0])+(N21[2][0][1]*psiD11[2][2][1]))));
        Pd[1][2][1] = (mkrk[1][2][1]+((N21[2][1][2]*psiD11[2][2][2])+((
          N21[2][1][0]*psiD11[2][2][0])+(N21[2][1][1]*psiD11[2][2][1]))));
        Pd[1][2][2] = ((N21[2][2][2]*psiD11[2][2][2])+((N21[2][2][0]*
          psiD11[2][2][0])+(N21[2][2][1]*psiD11[2][2][1])));
        P22[1][0][0] = (Iko[1][0][0]+(((Cik[2][0][2]*psiD22[2][0][2])+((
          N22[2][0][0]*psiD22[2][0][0])+(N22[2][0][1]*psiD22[2][0][1])))+((
          N21[2][0][2]*psiD21[2][0][2])+((N21[2][0][0]*psiD21[2][0][0])+(
          N21[2][0][1]*psiD21[2][0][1])))));
        P22[1][0][1] = (Iko[1][0][1]+(((Cik[2][1][2]*psiD22[2][0][2])+((
          N22[2][1][0]*psiD22[2][0][0])+(N22[2][1][1]*psiD22[2][0][1])))+((
          N21[2][1][2]*psiD21[2][0][2])+((N21[2][1][0]*psiD21[2][0][0])+(
          N21[2][1][1]*psiD21[2][0][1])))));
        P22[1][0][2] = (Iko[1][0][2]+(((Cik[2][2][2]*psiD22[2][0][2])+((
          N22[2][2][0]*psiD22[2][0][0])+(N22[2][2][1]*psiD22[2][0][1])))+((
          N21[2][2][2]*psiD21[2][0][2])+((N21[2][2][0]*psiD21[2][0][0])+(
          N21[2][2][1]*psiD21[2][0][1])))));
        P22[1][1][0] = P22[1][0][1];
        P22[1][1][1] = (Iko[1][1][1]+(((Cik[2][1][2]*psiD22[2][1][2])+((
          N22[2][1][0]*psiD22[2][1][0])+(N22[2][1][1]*psiD22[2][1][1])))+((
          N21[2][1][2]*psiD21[2][1][2])+((N21[2][1][0]*psiD21[2][1][0])+(
          N21[2][1][1]*psiD21[2][1][1])))));
        P22[1][1][2] = (Iko[1][1][2]+(((Cik[2][2][2]*psiD22[2][1][2])+((
          N22[2][2][0]*psiD22[2][1][0])+(N22[2][2][1]*psiD22[2][1][1])))+((
          N21[2][2][2]*psiD21[2][1][2])+((N21[2][2][0]*psiD21[2][1][0])+(
          N21[2][2][1]*psiD21[2][1][1])))));
        P22[1][2][0] = P22[1][0][2];
        P22[1][2][1] = P22[1][1][2];
        P22[1][2][2] = (Iko[1][2][2]+(((Cik[2][2][2]*psiD22[2][2][2])+((
          N22[2][2][0]*psiD22[2][2][0])+(N22[2][2][1]*psiD22[2][2][1])))+((
          N21[2][2][2]*psiD21[2][2][2])+((N21[2][2][0]*psiD21[2][2][0])+(
          N21[2][2][1]*psiD21[2][2][1])))));
        PH1[1][0] = ((Pd[1][0][2]*pin[1][2])+((Pd[1][0][0]*pin[1][0])+(
          Pd[1][0][1]*pin[1][1])));
        PH1[1][1] = ((Pd[1][1][2]*pin[1][2])+((Pd[1][1][0]*pin[1][0])+(
          Pd[1][1][1]*pin[1][1])));
        PH1[1][2] = ((Pd[1][2][2]*pin[1][2])+((Pd[1][2][0]*pin[1][0])+(
          Pd[1][2][1]*pin[1][1])));
        PH2[1][0] = ((P22[1][0][2]*pin[1][2])+((P22[1][0][0]*pin[1][0])+(
          P22[1][0][1]*pin[1][1])));
        PH2[1][1] = ((P22[1][1][2]*pin[1][2])+((P22[1][1][0]*pin[1][0])+(
          P22[1][1][1]*pin[1][1])));
        PH2[1][2] = ((P22[1][2][2]*pin[1][2])+((P22[1][2][0]*pin[1][0])+(
          P22[1][2][1]*pin[1][1])));
        DD[1] = ((PH2[1][2]*pin[1][2])+((PH2[1][0]*pin[1][0])+(PH2[1][1]*
          pin[1][1])));
        if (DD[1] < 1e-13) {
            sdseterr(17,47);
        } else {
            DD[1] = (1./DD[1]);
        }
        G1[1][0] = (DD[1]*PH1[1][0]);
        G1[1][1] = (DD[1]*PH1[1][1]);
        G1[1][2] = (DD[1]*PH1[1][2]);
        G2[1][0] = (DD[1]*PH2[1][0]);
        G2[1][1] = (DD[1]*PH2[1][1]);
        G2[1][2] = (DD[1]*PH2[1][2]);
        P11[1][0][0] = (P11[1][0][0]-(G1[1][0]*PH1[1][0]));
        P11[1][0][1] = (P11[1][0][1]-(G1[1][1]*PH1[1][0]));
        P11[1][0][2] = (P11[1][0][2]-(G1[1][2]*PH1[1][0]));
        P11[1][1][1] = (P11[1][1][1]-(G1[1][1]*PH1[1][1]));
        P11[1][1][2] = (P11[1][1][2]-(G1[1][2]*PH1[1][1]));
        P11[1][2][2] = (P11[1][2][2]-(G1[1][2]*PH1[1][2]));
        Pd[1][0][0] = (Pd[1][0][0]-(G2[1][0]*PH1[1][0]));
        Pd[1][0][1] = (Pd[1][0][1]-(G2[1][1]*PH1[1][0]));
        Pd[1][0][2] = (Pd[1][0][2]-(G2[1][2]*PH1[1][0]));
        Pd[1][1][0] = (Pd[1][1][0]-(G2[1][0]*PH1[1][1]));
        Pd[1][1][1] = (Pd[1][1][1]-(G2[1][1]*PH1[1][1]));
        Pd[1][1][2] = (Pd[1][1][2]-(G2[1][2]*PH1[1][1]));
        Pd[1][2][0] = (Pd[1][2][0]-(G2[1][0]*PH1[1][2]));
        Pd[1][2][1] = (Pd[1][2][1]-(G2[1][1]*PH1[1][2]));
        Pd[1][2][2] = (Pd[1][2][2]-(G2[1][2]*PH1[1][2]));
        P22[1][0][0] = (P22[1][0][0]-(G2[1][0]*PH2[1][0]));
        P22[1][0][1] = (P22[1][0][1]-(G2[1][1]*PH2[1][0]));
        P22[1][0][2] = (P22[1][0][2]-(G2[1][2]*PH2[1][0]));
        P22[1][1][1] = (P22[1][1][1]-(G2[1][1]*PH2[1][1]));
        P22[1][1][2] = (P22[1][1][2]-(G2[1][2]*PH2[1][1]));
        P22[1][2][2] = (P22[1][2][2]-(G2[1][2]*PH2[1][2]));
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
        N11[1][0][0] = ((Cik[1][0][0]+(Cik[1][0][1]*sL11[1][0]))+(Cik[1][0][2]*
          sL11[2][0]));
        N11[1][0][1] = (Cik[1][0][1]+(Cik[1][0][2]*sL11[2][1]));
        N11[1][1][0] = ((Cik[1][1][0]+(Cik[1][1][1]*sL11[1][0]))+(Cik[1][1][2]*
          sL11[2][0]));
        N11[1][1][1] = (Cik[1][1][1]+(Cik[1][1][2]*sL11[2][1]));
        N11[1][2][0] = ((Cik[1][2][0]+(Cik[1][2][1]*sL11[1][0]))+(Cik[1][2][2]*
          sL11[2][0]));
        N11[1][2][1] = (Cik[1][2][1]+(Cik[1][2][2]*sL11[2][1]));
        N21[1][0][0] = (((Cik[1][0][2]*sL21[2][0])+((Cik[1][0][0]*sL21[0][0])+(
          Cik[1][0][1]*sL21[1][0])))+((rikt[1][0][0]+(rikt[1][0][1]*sL11[1][0]))
          +(rikt[1][0][2]*sL11[2][0])));
        N21[1][0][1] = ((rikt[1][0][1]+(rikt[1][0][2]*sL11[2][1]))+((
          Cik[1][0][2]*sL21[2][1])+((Cik[1][0][0]*sL21[0][1])+(Cik[1][0][1]*
          sL21[1][1]))));
        N21[1][0][2] = (rikt[1][0][2]+((Cik[1][0][2]*sL21[2][2])+((Cik[1][0][0]*
          sL21[0][2])+(Cik[1][0][1]*sL21[1][2]))));
        N21[1][1][0] = (((Cik[1][1][2]*sL21[2][0])+((Cik[1][1][0]*sL21[0][0])+(
          Cik[1][1][1]*sL21[1][0])))+((rikt[1][1][0]+(rikt[1][1][1]*sL11[1][0]))
          +(rikt[1][1][2]*sL11[2][0])));
        N21[1][1][1] = ((rikt[1][1][1]+(rikt[1][1][2]*sL11[2][1]))+((
          Cik[1][1][2]*sL21[2][1])+((Cik[1][1][0]*sL21[0][1])+(Cik[1][1][1]*
          sL21[1][1]))));
        N21[1][1][2] = (rikt[1][1][2]+((Cik[1][1][2]*sL21[2][2])+((Cik[1][1][0]*
          sL21[0][2])+(Cik[1][1][1]*sL21[1][2]))));
        N21[1][2][0] = (((Cik[1][2][2]*sL21[2][0])+((Cik[1][2][0]*sL21[0][0])+(
          Cik[1][2][1]*sL21[1][0])))+((rikt[1][2][0]+(rikt[1][2][1]*sL11[1][0]))
          +(rikt[1][2][2]*sL11[2][0])));
        N21[1][2][1] = ((rikt[1][2][1]+(rikt[1][2][2]*sL11[2][1]))+((
          Cik[1][2][2]*sL21[2][1])+((Cik[1][2][0]*sL21[0][1])+(Cik[1][2][1]*
          sL21[1][1]))));
        N21[1][2][2] = (rikt[1][2][2]+((Cik[1][2][2]*sL21[2][2])+((Cik[1][2][0]*
          sL21[0][2])+(Cik[1][2][1]*sL21[1][2]))));
        N22[1][0][0] = ((Cik[1][0][0]+(Cik[1][0][1]*sL22[1][0]))+(Cik[1][0][2]*
          sL22[2][0]));
        N22[1][0][1] = (Cik[1][0][1]+(Cik[1][0][2]*sL22[2][1]));
        N22[1][1][0] = ((Cik[1][1][0]+(Cik[1][1][1]*sL22[1][0]))+(Cik[1][1][2]*
          sL22[2][0]));
        N22[1][1][1] = (Cik[1][1][1]+(Cik[1][1][2]*sL22[2][1]));
        N22[1][2][0] = ((Cik[1][2][0]+(Cik[1][2][1]*sL22[1][0]))+(Cik[1][2][2]*
          sL22[2][0]));
        N22[1][2][1] = (Cik[1][2][1]+(Cik[1][2][2]*sL22[2][1]));
        psiD11[1][0][0] = (N11[1][0][0]*P11[1][0][0]);
        psiD11[1][0][1] = (N11[1][0][1]*sL11D1[1][1]);
        psiD11[1][0][2] = (Cik[1][0][2]*sL11D1[2][2]);
        psiD11[1][1][0] = (N11[1][1][0]*P11[1][0][0]);
        psiD11[1][1][1] = (N11[1][1][1]*sL11D1[1][1]);
        psiD11[1][1][2] = (Cik[1][1][2]*sL11D1[2][2]);
        psiD11[1][2][0] = (N11[1][2][0]*P11[1][0][0]);
        psiD11[1][2][1] = (N11[1][2][1]*sL11D1[1][1]);
        psiD11[1][2][2] = (Cik[1][2][2]*sL11D1[2][2]);
        psiD21[1][0][0] = (N21[1][0][0]*P11[1][0][0]);
        psiD21[1][0][1] = (N21[1][0][1]*sL11D1[1][1]);
        psiD21[1][0][2] = (N21[1][0][2]*sL11D1[2][2]);
        psiD21[1][1][0] = (N21[1][1][0]*P11[1][0][0]);
        psiD21[1][1][1] = (N21[1][1][1]*sL11D1[1][1]);
        psiD21[1][1][2] = (N21[1][1][2]*sL11D1[2][2]);
        psiD21[1][2][0] = (N21[1][2][0]*P11[1][0][0]);
        psiD21[1][2][1] = (N21[1][2][1]*sL11D1[1][1]);
        psiD21[1][2][2] = (N21[1][2][2]*sL11D1[2][2]);
        psiD22[1][0][0] = (N22[1][0][0]*sL22D2[0][0]);
        psiD22[1][0][1] = (N22[1][0][1]*sL22D2[1][1]);
        psiD22[1][0][2] = (Cik[1][0][2]*sL22D2[2][2]);
        psiD22[1][1][0] = (N22[1][1][0]*sL22D2[0][0]);
        psiD22[1][1][1] = (N22[1][1][1]*sL22D2[1][1]);
        psiD22[1][1][2] = (Cik[1][1][2]*sL22D2[2][2]);
        psiD22[1][2][0] = (N22[1][2][0]*sL22D2[0][0]);
        psiD22[1][2][1] = (N22[1][2][1]*sL22D2[1][1]);
        psiD22[1][2][2] = (Cik[1][2][2]*sL22D2[2][2]);
        P11[0][0][0] = (mk[7]+((Cik[1][0][2]*psiD11[1][0][2])+((N11[1][0][0]*
          psiD11[1][0][0])+(N11[1][0][1]*psiD11[1][0][1]))));
        P11[0][0][1] = ((Cik[1][1][2]*psiD11[1][0][2])+((N11[1][1][0]*
          psiD11[1][0][0])+(N11[1][1][1]*psiD11[1][0][1])));
        P11[0][0][2] = ((Cik[1][2][2]*psiD11[1][0][2])+((N11[1][2][0]*
          psiD11[1][0][0])+(N11[1][2][1]*psiD11[1][0][1])));
        P11[0][1][0] = P11[0][0][1];
        P11[0][1][1] = (mk[7]+((Cik[1][1][2]*psiD11[1][1][2])+((N11[1][1][0]*
          psiD11[1][1][0])+(N11[1][1][1]*psiD11[1][1][1]))));
        P11[0][1][2] = ((Cik[1][2][2]*psiD11[1][1][2])+((N11[1][2][0]*
          psiD11[1][1][0])+(N11[1][2][1]*psiD11[1][1][1])));
        P11[0][2][0] = P11[0][0][2];
        P11[0][2][1] = P11[0][1][2];
        P11[0][2][2] = (mk[7]+((Cik[1][2][2]*psiD11[1][2][2])+((N11[1][2][0]*
          psiD11[1][2][0])+(N11[1][2][1]*psiD11[1][2][1]))));
        Pd[0][0][0] = ((N21[1][0][2]*psiD11[1][0][2])+((N21[1][0][0]*
          psiD11[1][0][0])+(N21[1][0][1]*psiD11[1][0][1])));
        Pd[0][0][1] = (mkrk[0][0][1]+((N21[1][1][2]*psiD11[1][0][2])+((
          N21[1][1][0]*psiD11[1][0][0])+(N21[1][1][1]*psiD11[1][0][1]))));
        Pd[0][0][2] = (mkrk[0][0][2]+((N21[1][2][2]*psiD11[1][0][2])+((
          N21[1][2][0]*psiD11[1][0][0])+(N21[1][2][1]*psiD11[1][0][1]))));
        Pd[0][1][0] = (mkrk[0][1][0]+((N21[1][0][2]*psiD11[1][1][2])+((
          N21[1][0][0]*psiD11[1][1][0])+(N21[1][0][1]*psiD11[1][1][1]))));
        Pd[0][1][1] = ((N21[1][1][2]*psiD11[1][1][2])+((N21[1][1][0]*
          psiD11[1][1][0])+(N21[1][1][1]*psiD11[1][1][1])));
        Pd[0][1][2] = (mkrk[0][1][2]+((N21[1][2][2]*psiD11[1][1][2])+((
          N21[1][2][0]*psiD11[1][1][0])+(N21[1][2][1]*psiD11[1][1][1]))));
        Pd[0][2][0] = (mkrk[0][2][0]+((N21[1][0][2]*psiD11[1][2][2])+((
          N21[1][0][0]*psiD11[1][2][0])+(N21[1][0][1]*psiD11[1][2][1]))));
        Pd[0][2][1] = (mkrk[0][2][1]+((N21[1][1][2]*psiD11[1][2][2])+((
          N21[1][1][0]*psiD11[1][2][0])+(N21[1][1][1]*psiD11[1][2][1]))));
        Pd[0][2][2] = ((N21[1][2][2]*psiD11[1][2][2])+((N21[1][2][0]*
          psiD11[1][2][0])+(N21[1][2][1]*psiD11[1][2][1])));
        P22[0][0][0] = (Iko[0][0][0]+(((Cik[1][0][2]*psiD22[1][0][2])+((
          N22[1][0][0]*psiD22[1][0][0])+(N22[1][0][1]*psiD22[1][0][1])))+((
          N21[1][0][2]*psiD21[1][0][2])+((N21[1][0][0]*psiD21[1][0][0])+(
          N21[1][0][1]*psiD21[1][0][1])))));
        P22[0][0][1] = (Iko[0][0][1]+(((Cik[1][1][2]*psiD22[1][0][2])+((
          N22[1][1][0]*psiD22[1][0][0])+(N22[1][1][1]*psiD22[1][0][1])))+((
          N21[1][1][2]*psiD21[1][0][2])+((N21[1][1][0]*psiD21[1][0][0])+(
          N21[1][1][1]*psiD21[1][0][1])))));
        P22[0][0][2] = (Iko[0][0][2]+(((Cik[1][2][2]*psiD22[1][0][2])+((
          N22[1][2][0]*psiD22[1][0][0])+(N22[1][2][1]*psiD22[1][0][1])))+((
          N21[1][2][2]*psiD21[1][0][2])+((N21[1][2][0]*psiD21[1][0][0])+(
          N21[1][2][1]*psiD21[1][0][1])))));
        P22[0][1][0] = P22[0][0][1];
        P22[0][1][1] = (Iko[0][1][1]+(((Cik[1][1][2]*psiD22[1][1][2])+((
          N22[1][1][0]*psiD22[1][1][0])+(N22[1][1][1]*psiD22[1][1][1])))+((
          N21[1][1][2]*psiD21[1][1][2])+((N21[1][1][0]*psiD21[1][1][0])+(
          N21[1][1][1]*psiD21[1][1][1])))));
        P22[0][1][2] = (Iko[0][1][2]+(((Cik[1][2][2]*psiD22[1][1][2])+((
          N22[1][2][0]*psiD22[1][1][0])+(N22[1][2][1]*psiD22[1][1][1])))+((
          N21[1][2][2]*psiD21[1][1][2])+((N21[1][2][0]*psiD21[1][1][0])+(
          N21[1][2][1]*psiD21[1][1][1])))));
        P22[0][2][0] = P22[0][0][2];
        P22[0][2][1] = P22[0][1][2];
        P22[0][2][2] = (Iko[0][2][2]+(((Cik[1][2][2]*psiD22[1][2][2])+((
          N22[1][2][0]*psiD22[1][2][0])+(N22[1][2][1]*psiD22[1][2][1])))+((
          N21[1][2][2]*psiD21[1][2][2])+((N21[1][2][0]*psiD21[1][2][0])+(
          N21[1][2][1]*psiD21[1][2][1])))));
        PH1[0][0] = ((Pd[0][0][2]*pin[0][2])+((Pd[0][0][0]*pin[0][0])+(
          Pd[0][0][1]*pin[0][1])));
        PH1[0][1] = ((Pd[0][1][2]*pin[0][2])+((Pd[0][1][0]*pin[0][0])+(
          Pd[0][1][1]*pin[0][1])));
        PH1[0][2] = ((Pd[0][2][2]*pin[0][2])+((Pd[0][2][0]*pin[0][0])+(
          Pd[0][2][1]*pin[0][1])));
        PH2[0][0] = ((P22[0][0][2]*pin[0][2])+((P22[0][0][0]*pin[0][0])+(
          P22[0][0][1]*pin[0][1])));
        PH2[0][1] = ((P22[0][1][2]*pin[0][2])+((P22[0][1][0]*pin[0][0])+(
          P22[0][1][1]*pin[0][1])));
        PH2[0][2] = ((P22[0][2][2]*pin[0][2])+((P22[0][2][0]*pin[0][0])+(
          P22[0][2][1]*pin[0][1])));
        DD[0] = ((PH2[0][2]*pin[0][2])+((PH2[0][0]*pin[0][0])+(PH2[0][1]*
          pin[0][1])));
        if (DD[0] < 1e-13) {
            sdseterr(17,47);
        } else {
            DD[0] = (1./DD[0]);
        }
        sderror(&dumroutine,&errnum);
        if (errnum == 0) {
            mmflg = 1;
        }
    }
/*
 Used 0.03 seconds CPU time,
 0 additional bytes of memory.
 Equations contain  807 adds/subtracts/negates
                   1058 multiplies
                     25 divides
                    628 assignments
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

void sdmfrc(double imult[5])
{
/*
Calculate forces due to constraint multipliers.

*/

    mtau[0] = imult[0];
    mtau[1] = imult[1];
    mtau[2] = imult[2];
    mtau[3] = imult[3];
    mtau[4] = imult[4];
/*
 Used -0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain    0 adds/subtracts/negates
                      0 multiplies
                      0 divides
                      5 assignments
*/
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
    fstareq[0][0] = -(ufk[7][0]+(gk[0][0]*mk[7]));
    fstareq[0][1] = -(ufk[7][1]+(gk[0][1]*mk[7]));
    fstareq[0][2] = -(ufk[7][2]+(gk[0][2]*mk[7]));
    fstareq[1][0] = -(ufk[8][0]+(gk[1][0]*mk[8]));
    fstareq[1][1] = -(ufk[8][1]+(gk[1][1]*mk[8]));
    fstareq[1][2] = -(ufk[8][2]+(gk[1][2]*mk[8]));
    fstareq[2][0] = -(ufk[9][0]+(gk[2][0]*mk[9]));
    fstareq[2][1] = -(ufk[9][1]+(gk[2][1]*mk[9]));
    fstareq[2][2] = -(ufk[9][2]+(gk[2][2]*mk[9]));
    fstareq[3][0] = -(ufk[10][0]+(gk[3][0]*mk[10]));
    fstareq[3][1] = -(ufk[10][1]+(gk[3][1]*mk[10]));
    fstareq[3][2] = -(ufk[10][2]+(gk[3][2]*mk[10]));
    fstareq[4][0] = -(ufk[11][0]+(gk[4][0]*mk[11]));
    fstareq[4][1] = -(ufk[11][1]+(gk[4][1]*mk[11]));
    fstareq[4][2] = -(ufk[11][2]+(gk[4][2]*mk[11]));
/*
Compute tstareq (torques)
*/
/*
Compute taus (RHS ignoring constraints and inertial forces)
*/
    tau[4] = (utau[4]-(((fstareq[4][2]*rkWkk[4][2])+((fstareq[4][0]*rkWkk[4][0])
      +(fstareq[4][1]*rkWkk[4][1])))-((pin[4][2]*utk[11][2])+((pin[4][0]*
      utk[11][0])+(pin[4][1]*utk[11][1])))));
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
    tau[3] = (utau[3]-(((Fstark[3][2]*rkWkk[3][2])+((Fstark[3][0]*rkWkk[3][0])+(
      Fstark[3][1]*rkWkk[3][1])))+((pin[3][2]*Tstark[3][2])+((pin[3][0]*
      Tstark[3][0])+(pin[3][1]*Tstark[3][1])))));
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
    tau[2] = (utau[2]-(((Fstark[2][2]*rkWkk[2][2])+((Fstark[2][0]*rkWkk[2][0])+(
      Fstark[2][1]*rkWkk[2][1])))+((pin[2][2]*Tstark[2][2])+((pin[2][0]*
      Tstark[2][0])+(pin[2][1]*Tstark[2][1])))));
    Fstark[1][0] = (fstareq[1][0]+((Cik[2][0][2]*Fstark[2][2])+((Cik[2][0][0]*
      Fstark[2][0])+(Cik[2][0][1]*Fstark[2][1]))));
    Fstark[1][1] = (fstareq[1][1]+((Cik[2][1][2]*Fstark[2][2])+((Cik[2][1][0]*
      Fstark[2][0])+(Cik[2][1][1]*Fstark[2][1]))));
    Fstark[1][2] = (fstareq[1][2]+((Cik[2][2][2]*Fstark[2][2])+((Cik[2][2][0]*
      Fstark[2][0])+(Cik[2][2][1]*Fstark[2][1]))));
    tvec1[0] = (Tstark[2][0]+((Fstark[2][2]*rik[2][1])-(Fstark[2][1]*rik[2][2]))
      );
    tvec1[1] = (Tstark[2][1]+((Fstark[2][0]*rik[2][2])-(Fstark[2][2]*rik[2][0]))
      );
    tvec1[2] = (Tstark[2][2]+((Fstark[2][1]*rik[2][0])-(Fstark[2][0]*rik[2][1]))
      );
    Tstark[1][0] = (((Cik[2][0][2]*tvec1[2])+((Cik[2][0][0]*tvec1[0])+(
      Cik[2][0][1]*tvec1[1])))-utk[8][0]);
    Tstark[1][1] = (((Cik[2][1][2]*tvec1[2])+((Cik[2][1][0]*tvec1[0])+(
      Cik[2][1][1]*tvec1[1])))-utk[8][1]);
    Tstark[1][2] = (((Cik[2][2][2]*tvec1[2])+((Cik[2][2][0]*tvec1[0])+(
      Cik[2][2][1]*tvec1[1])))-utk[8][2]);
    tau[1] = (utau[1]-(((Fstark[1][2]*rkWkk[1][2])+((Fstark[1][0]*rkWkk[1][0])+(
      Fstark[1][1]*rkWkk[1][1])))+((pin[1][2]*Tstark[1][2])+((pin[1][0]*
      Tstark[1][0])+(pin[1][1]*Tstark[1][1])))));
    Fstark[0][0] = (fstareq[0][0]+((Cik[1][0][2]*Fstark[1][2])+((Cik[1][0][0]*
      Fstark[1][0])+(Cik[1][0][1]*Fstark[1][1]))));
    Fstark[0][1] = (fstareq[0][1]+((Cik[1][1][2]*Fstark[1][2])+((Cik[1][1][0]*
      Fstark[1][0])+(Cik[1][1][1]*Fstark[1][1]))));
    Fstark[0][2] = (fstareq[0][2]+((Cik[1][2][2]*Fstark[1][2])+((Cik[1][2][0]*
      Fstark[1][0])+(Cik[1][2][1]*Fstark[1][1]))));
    tvec1[0] = (Tstark[1][0]+((Fstark[1][2]*rik[1][1])-(Fstark[1][1]*rik[1][2]))
      );
    tvec1[1] = (Tstark[1][1]+((Fstark[1][0]*rik[1][2])-(Fstark[1][2]*rik[1][0]))
      );
    tvec1[2] = (Tstark[1][2]+((Fstark[1][1]*rik[1][0])-(Fstark[1][0]*rik[1][1]))
      );
    Tstark[0][0] = (((Cik[1][0][2]*tvec1[2])+((Cik[1][0][0]*tvec1[0])+(
      Cik[1][0][1]*tvec1[1])))-utk[7][0]);
    Tstark[0][1] = (((Cik[1][1][2]*tvec1[2])+((Cik[1][1][0]*tvec1[0])+(
      Cik[1][1][1]*tvec1[1])))-utk[7][1]);
    Tstark[0][2] = (((Cik[1][2][2]*tvec1[2])+((Cik[1][2][0]*tvec1[0])+(
      Cik[1][2][1]*tvec1[1])))-utk[7][2]);
    tau[0] = (utau[0]-(((Fstark[0][2]*rkWkk[0][2])+((Fstark[0][0]*rkWkk[0][0])+(
      Fstark[0][1]*rkWkk[0][1])))+((pin[0][2]*Tstark[0][2])+((pin[0][0]*
      Tstark[0][0])+(pin[0][1]*Tstark[0][1])))));
/*
Op counts below do not include called subroutines
*/
/*
 Used -0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain  156 adds/subtracts/negates
                    141 multiplies
                      0 divides
                     56 assignments
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
 Used -0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain    0 adds/subtracts/negates
                      0 multiplies
                      0 divides
                      5 assignments
*/
}

void sdfsmult(void)
{

/*
Compute Fs (multiplier-generated forces only)
*/
    fs[4] = mtau[4];
    fs[3] = mtau[3];
    fs[2] = mtau[2];
    fs[1] = mtau[1];
    fs[0] = mtau[0];
/*
 Used -0.00 seconds CPU time,
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
 Used -0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain    5 adds/subtracts/negates
                      0 multiplies
                      0 divides
                      5 assignments
*/
}

void sdfsgenmult(void)
{

/*
Compute Fs (generic multiplier-generated forces)
*/
    fs[4] = (mtau[4]+(((mfk[11][2]*rkWkk[4][2])+((mfk[11][0]*rkWkk[4][0])+(
      mfk[11][1]*rkWkk[4][1])))+((mtk[11][2]*pin[4][2])+((mtk[11][0]*pin[4][0])+
      (mtk[11][1]*pin[4][1])))));
    Fstark[3][0] = -(mfk[10][0]+((Cik[4][0][2]*mfk[11][2])+((Cik[4][0][0]*
      mfk[11][0])+(Cik[4][0][1]*mfk[11][1]))));
    Fstark[3][1] = -(mfk[10][1]+((Cik[4][1][2]*mfk[11][2])+((Cik[4][1][0]*
      mfk[11][0])+(Cik[4][1][1]*mfk[11][1]))));
    Fstark[3][2] = -(mfk[10][2]+((Cik[4][2][2]*mfk[11][2])+((Cik[4][2][0]*
      mfk[11][0])+(Cik[4][2][1]*mfk[11][1]))));
    tvec1[0] = (((mfk[11][1]*rik[4][2])-(mfk[11][2]*rik[4][1]))-mtk[11][0]);
    tvec1[1] = (((mfk[11][2]*rik[4][0])-(mfk[11][0]*rik[4][2]))-mtk[11][1]);
    tvec1[2] = (((mfk[11][0]*rik[4][1])-(mfk[11][1]*rik[4][0]))-mtk[11][2]);
    Tstark[3][0] = (((Cik[4][0][2]*tvec1[2])+((Cik[4][0][0]*tvec1[0])+(
      Cik[4][0][1]*tvec1[1])))-mtk[10][0]);
    Tstark[3][1] = (((Cik[4][1][2]*tvec1[2])+((Cik[4][1][0]*tvec1[0])+(
      Cik[4][1][1]*tvec1[1])))-mtk[10][1]);
    Tstark[3][2] = (((Cik[4][2][2]*tvec1[2])+((Cik[4][2][0]*tvec1[0])+(
      Cik[4][2][1]*tvec1[1])))-mtk[10][2]);
    fs[3] = (mtau[3]-(((Fstark[3][2]*rkWkk[3][2])+((Fstark[3][0]*rkWkk[3][0])+(
      Fstark[3][1]*rkWkk[3][1])))+((pin[3][2]*Tstark[3][2])+((pin[3][0]*
      Tstark[3][0])+(pin[3][1]*Tstark[3][1])))));
    Fstark[2][0] = (((Cik[3][0][2]*Fstark[3][2])+((Cik[3][0][0]*Fstark[3][0])+(
      Cik[3][0][1]*Fstark[3][1])))-mfk[9][0]);
    Fstark[2][1] = (((Cik[3][1][2]*Fstark[3][2])+((Cik[3][1][0]*Fstark[3][0])+(
      Cik[3][1][1]*Fstark[3][1])))-mfk[9][1]);
    Fstark[2][2] = (((Cik[3][2][2]*Fstark[3][2])+((Cik[3][2][0]*Fstark[3][0])+(
      Cik[3][2][1]*Fstark[3][1])))-mfk[9][2]);
    tvec1[0] = (Tstark[3][0]+((Fstark[3][2]*rik[3][1])-(Fstark[3][1]*rik[3][2]))
      );
    tvec1[1] = (Tstark[3][1]+((Fstark[3][0]*rik[3][2])-(Fstark[3][2]*rik[3][0]))
      );
    tvec1[2] = (Tstark[3][2]+((Fstark[3][1]*rik[3][0])-(Fstark[3][0]*rik[3][1]))
      );
    Tstark[2][0] = (((Cik[3][0][2]*tvec1[2])+((Cik[3][0][0]*tvec1[0])+(
      Cik[3][0][1]*tvec1[1])))-mtk[9][0]);
    Tstark[2][1] = (((Cik[3][1][2]*tvec1[2])+((Cik[3][1][0]*tvec1[0])+(
      Cik[3][1][1]*tvec1[1])))-mtk[9][1]);
    Tstark[2][2] = (((Cik[3][2][2]*tvec1[2])+((Cik[3][2][0]*tvec1[0])+(
      Cik[3][2][1]*tvec1[1])))-mtk[9][2]);
    fs[2] = (mtau[2]-(((Fstark[2][2]*rkWkk[2][2])+((Fstark[2][0]*rkWkk[2][0])+(
      Fstark[2][1]*rkWkk[2][1])))+((pin[2][2]*Tstark[2][2])+((pin[2][0]*
      Tstark[2][0])+(pin[2][1]*Tstark[2][1])))));
    Fstark[1][0] = (((Cik[2][0][2]*Fstark[2][2])+((Cik[2][0][0]*Fstark[2][0])+(
      Cik[2][0][1]*Fstark[2][1])))-mfk[8][0]);
    Fstark[1][1] = (((Cik[2][1][2]*Fstark[2][2])+((Cik[2][1][0]*Fstark[2][0])+(
      Cik[2][1][1]*Fstark[2][1])))-mfk[8][1]);
    Fstark[1][2] = (((Cik[2][2][2]*Fstark[2][2])+((Cik[2][2][0]*Fstark[2][0])+(
      Cik[2][2][1]*Fstark[2][1])))-mfk[8][2]);
    tvec1[0] = (Tstark[2][0]+((Fstark[2][2]*rik[2][1])-(Fstark[2][1]*rik[2][2]))
      );
    tvec1[1] = (Tstark[2][1]+((Fstark[2][0]*rik[2][2])-(Fstark[2][2]*rik[2][0]))
      );
    tvec1[2] = (Tstark[2][2]+((Fstark[2][1]*rik[2][0])-(Fstark[2][0]*rik[2][1]))
      );
    Tstark[1][0] = (((Cik[2][0][2]*tvec1[2])+((Cik[2][0][0]*tvec1[0])+(
      Cik[2][0][1]*tvec1[1])))-mtk[8][0]);
    Tstark[1][1] = (((Cik[2][1][2]*tvec1[2])+((Cik[2][1][0]*tvec1[0])+(
      Cik[2][1][1]*tvec1[1])))-mtk[8][1]);
    Tstark[1][2] = (((Cik[2][2][2]*tvec1[2])+((Cik[2][2][0]*tvec1[0])+(
      Cik[2][2][1]*tvec1[1])))-mtk[8][2]);
    fs[1] = (mtau[1]-(((Fstark[1][2]*rkWkk[1][2])+((Fstark[1][0]*rkWkk[1][0])+(
      Fstark[1][1]*rkWkk[1][1])))+((pin[1][2]*Tstark[1][2])+((pin[1][0]*
      Tstark[1][0])+(pin[1][1]*Tstark[1][1])))));
    Fstark[0][0] = (((Cik[1][0][2]*Fstark[1][2])+((Cik[1][0][0]*Fstark[1][0])+(
      Cik[1][0][1]*Fstark[1][1])))-mfk[7][0]);
    Fstark[0][1] = (((Cik[1][1][2]*Fstark[1][2])+((Cik[1][1][0]*Fstark[1][0])+(
      Cik[1][1][1]*Fstark[1][1])))-mfk[7][1]);
    Fstark[0][2] = (((Cik[1][2][2]*Fstark[1][2])+((Cik[1][2][0]*Fstark[1][0])+(
      Cik[1][2][1]*Fstark[1][1])))-mfk[7][2]);
    tvec1[0] = (Tstark[1][0]+((Fstark[1][2]*rik[1][1])-(Fstark[1][1]*rik[1][2]))
      );
    tvec1[1] = (Tstark[1][1]+((Fstark[1][0]*rik[1][2])-(Fstark[1][2]*rik[1][0]))
      );
    tvec1[2] = (Tstark[1][2]+((Fstark[1][1]*rik[1][0])-(Fstark[1][0]*rik[1][1]))
      );
    Tstark[0][0] = (((Cik[1][0][2]*tvec1[2])+((Cik[1][0][0]*tvec1[0])+(
      Cik[1][0][1]*tvec1[1])))-mtk[7][0]);
    Tstark[0][1] = (((Cik[1][1][2]*tvec1[2])+((Cik[1][1][0]*tvec1[0])+(
      Cik[1][1][1]*tvec1[1])))-mtk[7][1]);
    Tstark[0][2] = (((Cik[1][2][2]*tvec1[2])+((Cik[1][2][0]*tvec1[0])+(
      Cik[1][2][1]*tvec1[1])))-mtk[7][2]);
    fs[0] = (mtau[0]-(((Fstark[0][2]*rkWkk[0][2])+((Fstark[0][0]*rkWkk[0][0])+(
      Fstark[0][1]*rkWkk[0][1])))+((pin[0][2]*Tstark[0][2])+((pin[0][0]*
      Tstark[0][0])+(pin[0][1]*Tstark[0][1])))));
/*
 Used -0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain  129 adds/subtracts/negates
                    126 multiplies
                      0 divides
                     41 assignments
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
 Used 0.01 seconds CPU time,
 0 additional bytes of memory.
 Equations contain    5 adds/subtracts/negates
                      0 multiplies
                      0 divides
                      5 assignments
*/
}

void sdfulltrq(double udotin[5],
    double multin[5],
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
Compute multiplier-generated forces
*/
    sdmfrc(multin);
/*
Account for inertial accelerations and supplied udots
*/
    Otkr[0][0] = (pin[0][0]*udotin[0]);
    Otkr[0][1] = (pin[0][1]*udotin[0]);
    Otkr[0][2] = (pin[0][2]*udotin[0]);
    Otkr[1][0] = (((Cik[1][2][0]*Otkr[0][2])+((Cik[1][0][0]*Otkr[0][0])+(
      Cik[1][1][0]*Otkr[0][1])))+((pin[1][0]*udotin[1])+((Wik[1][2]*wk[1][1])-(
      Wik[1][1]*wk[1][2]))));
    Otkr[1][1] = (((Cik[1][2][1]*Otkr[0][2])+((Cik[1][0][1]*Otkr[0][0])+(
      Cik[1][1][1]*Otkr[0][1])))+((pin[1][1]*udotin[1])+((Wik[1][0]*wk[1][2])-(
      Wik[1][2]*wk[1][0]))));
    Otkr[1][2] = (((Cik[1][2][2]*Otkr[0][2])+((Cik[1][0][2]*Otkr[0][0])+(
      Cik[1][1][2]*Otkr[0][1])))+((pin[1][2]*udotin[1])+((Wik[1][1]*wk[1][0])-(
      Wik[1][0]*wk[1][1]))));
    Otkr[2][0] = (((Cik[2][2][0]*Otkr[1][2])+((Cik[2][0][0]*Otkr[1][0])+(
      Cik[2][1][0]*Otkr[1][1])))+((pin[2][0]*udotin[2])+((Wik[2][2]*wk[2][1])-(
      Wik[2][1]*wk[2][2]))));
    Otkr[2][1] = (((Cik[2][2][1]*Otkr[1][2])+((Cik[2][0][1]*Otkr[1][0])+(
      Cik[2][1][1]*Otkr[1][1])))+((pin[2][1]*udotin[2])+((Wik[2][0]*wk[2][2])-(
      Wik[2][2]*wk[2][0]))));
    Otkr[2][2] = (((Cik[2][2][2]*Otkr[1][2])+((Cik[2][0][2]*Otkr[1][0])+(
      Cik[2][1][2]*Otkr[1][1])))+((pin[2][2]*udotin[2])+((Wik[2][1]*wk[2][0])-(
      Wik[2][0]*wk[2][1]))));
    Otkr[3][0] = (((Cik[3][2][0]*Otkr[2][2])+((Cik[3][0][0]*Otkr[2][0])+(
      Cik[3][1][0]*Otkr[2][1])))+((pin[3][0]*udotin[3])+((Wik[3][2]*wk[3][1])-(
      Wik[3][1]*wk[3][2]))));
    Otkr[3][1] = (((Cik[3][2][1]*Otkr[2][2])+((Cik[3][0][1]*Otkr[2][0])+(
      Cik[3][1][1]*Otkr[2][1])))+((pin[3][1]*udotin[3])+((Wik[3][0]*wk[3][2])-(
      Wik[3][2]*wk[3][0]))));
    Otkr[3][2] = (((Cik[3][2][2]*Otkr[2][2])+((Cik[3][0][2]*Otkr[2][0])+(
      Cik[3][1][2]*Otkr[2][1])))+((pin[3][2]*udotin[3])+((Wik[3][1]*wk[3][0])-(
      Wik[3][0]*wk[3][1]))));
    Otkr[4][0] = (((Cik[4][2][0]*Otkr[3][2])+((Cik[4][0][0]*Otkr[3][0])+(
      Cik[4][1][0]*Otkr[3][1])))+((pin[4][0]*udotin[4])+((Wik[4][2]*wk[4][1])-(
      Wik[4][1]*wk[4][2]))));
    Otkr[4][1] = (((Cik[4][2][1]*Otkr[3][2])+((Cik[4][0][1]*Otkr[3][0])+(
      Cik[4][1][1]*Otkr[3][1])))+((pin[4][1]*udotin[4])+((Wik[4][0]*wk[4][2])-(
      Wik[4][2]*wk[4][0]))));
    Otkr[4][2] = (((Cik[4][2][2]*Otkr[3][2])+((Cik[4][0][2]*Otkr[3][0])+(
      Cik[4][1][2]*Otkr[3][1])))+((pin[4][2]*udotin[4])+((Wik[4][1]*wk[4][0])-(
      Wik[4][0]*wk[4][1]))));
    Atkr[0][0] = (((Otkr[0][2]*rk[7][1])-(Otkr[0][1]*rk[7][2]))+((Wik[0][1]*
      Wkrpk[0][2])-(Wik[0][2]*Wkrpk[0][1])));
    Atkr[0][1] = (((Otkr[0][0]*rk[7][2])-(Otkr[0][2]*rk[7][0]))+((Wik[0][2]*
      Wkrpk[0][0])-(Wik[0][0]*Wkrpk[0][2])));
    Atkr[0][2] = (((Otkr[0][1]*rk[7][0])-(Otkr[0][0]*rk[7][1]))+((Wik[0][0]*
      Wkrpk[0][1])-(Wik[0][1]*Wkrpk[0][0])));
    Atir[1][0] = (Atkr[0][0]+(((Otkr[0][1]*ri[8][2])-(Otkr[0][2]*ri[8][1]))+((
      Wik[0][1]*Wirk[1][2])-(Wik[0][2]*Wirk[1][1]))));
    Atir[1][1] = (Atkr[0][1]+(((Otkr[0][2]*ri[8][0])-(Otkr[0][0]*ri[8][2]))+((
      Wik[0][2]*Wirk[1][0])-(Wik[0][0]*Wirk[1][2]))));
    Atir[1][2] = (Atkr[0][2]+(((Otkr[0][0]*ri[8][1])-(Otkr[0][1]*ri[8][0]))+((
      Wik[0][0]*Wirk[1][1])-(Wik[0][1]*Wirk[1][0]))));
    Atkr[1][0] = (((Atir[1][2]*Cik[1][2][0])+((Atir[1][0]*Cik[1][0][0])+(
      Atir[1][1]*Cik[1][1][0])))+(((Otkr[1][2]*rk[8][1])-(Otkr[1][1]*rk[8][2]))+
      ((wk[1][1]*Wkrpk[1][2])-(wk[1][2]*Wkrpk[1][1]))));
    Atkr[1][1] = (((Atir[1][2]*Cik[1][2][1])+((Atir[1][0]*Cik[1][0][1])+(
      Atir[1][1]*Cik[1][1][1])))+(((Otkr[1][0]*rk[8][2])-(Otkr[1][2]*rk[8][0]))+
      ((wk[1][2]*Wkrpk[1][0])-(wk[1][0]*Wkrpk[1][2]))));
    Atkr[1][2] = (((Atir[1][2]*Cik[1][2][2])+((Atir[1][0]*Cik[1][0][2])+(
      Atir[1][1]*Cik[1][1][2])))+(((Otkr[1][1]*rk[8][0])-(Otkr[1][0]*rk[8][1]))+
      ((wk[1][0]*Wkrpk[1][1])-(wk[1][1]*Wkrpk[1][0]))));
    Atir[2][0] = (Atkr[1][0]+(((Otkr[1][1]*ri[9][2])-(Otkr[1][2]*ri[9][1]))+((
      Wirk[2][2]*wk[1][1])-(Wirk[2][1]*wk[1][2]))));
    Atir[2][1] = (Atkr[1][1]+(((Otkr[1][2]*ri[9][0])-(Otkr[1][0]*ri[9][2]))+((
      Wirk[2][0]*wk[1][2])-(Wirk[2][2]*wk[1][0]))));
    Atir[2][2] = (Atkr[1][2]+(((Otkr[1][0]*ri[9][1])-(Otkr[1][1]*ri[9][0]))+((
      Wirk[2][1]*wk[1][0])-(Wirk[2][0]*wk[1][1]))));
    Atkr[2][0] = (((Atir[2][2]*Cik[2][2][0])+((Atir[2][0]*Cik[2][0][0])+(
      Atir[2][1]*Cik[2][1][0])))+(((Otkr[2][2]*rk[9][1])-(Otkr[2][1]*rk[9][2]))+
      ((wk[2][1]*Wkrpk[2][2])-(wk[2][2]*Wkrpk[2][1]))));
    Atkr[2][1] = (((Atir[2][2]*Cik[2][2][1])+((Atir[2][0]*Cik[2][0][1])+(
      Atir[2][1]*Cik[2][1][1])))+(((Otkr[2][0]*rk[9][2])-(Otkr[2][2]*rk[9][0]))+
      ((wk[2][2]*Wkrpk[2][0])-(wk[2][0]*Wkrpk[2][2]))));
    Atkr[2][2] = (((Atir[2][2]*Cik[2][2][2])+((Atir[2][0]*Cik[2][0][2])+(
      Atir[2][1]*Cik[2][1][2])))+(((Otkr[2][1]*rk[9][0])-(Otkr[2][0]*rk[9][1]))+
      ((wk[2][0]*Wkrpk[2][1])-(wk[2][1]*Wkrpk[2][0]))));
    Atir[3][0] = (Atkr[2][0]+(((Otkr[2][1]*ri[10][2])-(Otkr[2][2]*ri[10][1]))+((
      Wirk[3][2]*wk[2][1])-(Wirk[3][1]*wk[2][2]))));
    Atir[3][1] = (Atkr[2][1]+(((Otkr[2][2]*ri[10][0])-(Otkr[2][0]*ri[10][2]))+((
      Wirk[3][0]*wk[2][2])-(Wirk[3][2]*wk[2][0]))));
    Atir[3][2] = (Atkr[2][2]+(((Otkr[2][0]*ri[10][1])-(Otkr[2][1]*ri[10][0]))+((
      Wirk[3][1]*wk[2][0])-(Wirk[3][0]*wk[2][1]))));
    Atkr[3][0] = (((Atir[3][2]*Cik[3][2][0])+((Atir[3][0]*Cik[3][0][0])+(
      Atir[3][1]*Cik[3][1][0])))+(((Otkr[3][2]*rk[10][1])-(Otkr[3][1]*rk[10][2])
      )+((wk[3][1]*Wkrpk[3][2])-(wk[3][2]*Wkrpk[3][1]))));
    Atkr[3][1] = (((Atir[3][2]*Cik[3][2][1])+((Atir[3][0]*Cik[3][0][1])+(
      Atir[3][1]*Cik[3][1][1])))+(((Otkr[3][0]*rk[10][2])-(Otkr[3][2]*rk[10][0])
      )+((wk[3][2]*Wkrpk[3][0])-(wk[3][0]*Wkrpk[3][2]))));
    Atkr[3][2] = (((Atir[3][2]*Cik[3][2][2])+((Atir[3][0]*Cik[3][0][2])+(
      Atir[3][1]*Cik[3][1][2])))+(((Otkr[3][1]*rk[10][0])-(Otkr[3][0]*rk[10][1])
      )+((wk[3][0]*Wkrpk[3][1])-(wk[3][1]*Wkrpk[3][0]))));
    Atir[4][0] = (Atkr[3][0]+(((Otkr[3][1]*ri[11][2])-(Otkr[3][2]*ri[11][1]))+((
      Wirk[4][2]*wk[3][1])-(Wirk[4][1]*wk[3][2]))));
    Atir[4][1] = (Atkr[3][1]+(((Otkr[3][2]*ri[11][0])-(Otkr[3][0]*ri[11][2]))+((
      Wirk[4][0]*wk[3][2])-(Wirk[4][2]*wk[3][0]))));
    Atir[4][2] = (Atkr[3][2]+(((Otkr[3][0]*ri[11][1])-(Otkr[3][1]*ri[11][0]))+((
      Wirk[4][1]*wk[3][0])-(Wirk[4][0]*wk[3][1]))));
    Atkr[4][0] = (((Atir[4][2]*Cik[4][2][0])+((Atir[4][0]*Cik[4][0][0])+(
      Atir[4][1]*Cik[4][1][0])))+(((Otkr[4][2]*rk[11][1])-(Otkr[4][1]*rk[11][2])
      )+((wk[4][1]*Wkrpk[4][2])-(wk[4][2]*Wkrpk[4][1]))));
    Atkr[4][1] = (((Atir[4][2]*Cik[4][2][1])+((Atir[4][0]*Cik[4][0][1])+(
      Atir[4][1]*Cik[4][1][1])))+(((Otkr[4][0]*rk[11][2])-(Otkr[4][2]*rk[11][0])
      )+((wk[4][2]*Wkrpk[4][0])-(wk[4][0]*Wkrpk[4][2]))));
    Atkr[4][2] = (((Atir[4][2]*Cik[4][2][2])+((Atir[4][0]*Cik[4][0][2])+(
      Atir[4][1]*Cik[4][1][2])))+(((Otkr[4][1]*rk[11][0])-(Otkr[4][0]*rk[11][1])
      )+((wk[4][0]*Wkrpk[4][1])-(wk[4][1]*Wkrpk[4][0]))));
/*
Accumulate all forces and torques
*/
    fstarr[0][0] = (ufk[7][0]+(mk[7]*(gk[0][0]-Atkr[0][0])));
    fstarr[0][1] = (ufk[7][1]+(mk[7]*(gk[0][1]-Atkr[0][1])));
    fstarr[0][2] = (ufk[7][2]+(mk[7]*(gk[0][2]-Atkr[0][2])));
    fstarr[1][0] = (ufk[8][0]+(mk[8]*(gk[1][0]-Atkr[1][0])));
    fstarr[1][1] = (ufk[8][1]+(mk[8]*(gk[1][1]-Atkr[1][1])));
    fstarr[1][2] = (ufk[8][2]+(mk[8]*(gk[1][2]-Atkr[1][2])));
    fstarr[2][0] = (ufk[9][0]+(mk[9]*(gk[2][0]-Atkr[2][0])));
    fstarr[2][1] = (ufk[9][1]+(mk[9]*(gk[2][1]-Atkr[2][1])));
    fstarr[2][2] = (ufk[9][2]+(mk[9]*(gk[2][2]-Atkr[2][2])));
    fstarr[3][0] = (ufk[10][0]+(mk[10]*(gk[3][0]-Atkr[3][0])));
    fstarr[3][1] = (ufk[10][1]+(mk[10]*(gk[3][1]-Atkr[3][1])));
    fstarr[3][2] = (ufk[10][2]+(mk[10]*(gk[3][2]-Atkr[3][2])));
    fstarr[4][0] = (ufk[11][0]+(mk[11]*(gk[4][0]-Atkr[4][0])));
    fstarr[4][1] = (ufk[11][1]+(mk[11]*(gk[4][1]-Atkr[4][1])));
    fstarr[4][2] = (ufk[11][2]+(mk[11]*(gk[4][2]-Atkr[4][2])));
    tstarr[0][0] = (utk[7][0]-(WkIkWk[0][0]+((ik[7][0][2]*Otkr[0][2])+((
      ik[7][0][0]*Otkr[0][0])+(ik[7][0][1]*Otkr[0][1])))));
    tstarr[0][1] = (utk[7][1]-(WkIkWk[0][1]+((ik[7][1][2]*Otkr[0][2])+((
      ik[7][1][0]*Otkr[0][0])+(ik[7][1][1]*Otkr[0][1])))));
    tstarr[0][2] = (utk[7][2]-(WkIkWk[0][2]+((ik[7][2][2]*Otkr[0][2])+((
      ik[7][2][0]*Otkr[0][0])+(ik[7][2][1]*Otkr[0][1])))));
    tstarr[1][0] = (utk[8][0]-(WkIkWk[1][0]+((ik[8][0][2]*Otkr[1][2])+((
      ik[8][0][0]*Otkr[1][0])+(ik[8][0][1]*Otkr[1][1])))));
    tstarr[1][1] = (utk[8][1]-(WkIkWk[1][1]+((ik[8][1][2]*Otkr[1][2])+((
      ik[8][1][0]*Otkr[1][0])+(ik[8][1][1]*Otkr[1][1])))));
    tstarr[1][2] = (utk[8][2]-(WkIkWk[1][2]+((ik[8][2][2]*Otkr[1][2])+((
      ik[8][2][0]*Otkr[1][0])+(ik[8][2][1]*Otkr[1][1])))));
    tstarr[2][0] = (utk[9][0]-(WkIkWk[2][0]+((ik[9][0][2]*Otkr[2][2])+((
      ik[9][0][0]*Otkr[2][0])+(ik[9][0][1]*Otkr[2][1])))));
    tstarr[2][1] = (utk[9][1]-(WkIkWk[2][1]+((ik[9][1][2]*Otkr[2][2])+((
      ik[9][1][0]*Otkr[2][0])+(ik[9][1][1]*Otkr[2][1])))));
    tstarr[2][2] = (utk[9][2]-(WkIkWk[2][2]+((ik[9][2][2]*Otkr[2][2])+((
      ik[9][2][0]*Otkr[2][0])+(ik[9][2][1]*Otkr[2][1])))));
    tstarr[3][0] = (utk[10][0]-(WkIkWk[3][0]+((ik[10][0][2]*Otkr[3][2])+((
      ik[10][0][0]*Otkr[3][0])+(ik[10][0][1]*Otkr[3][1])))));
    tstarr[3][1] = (utk[10][1]-(WkIkWk[3][1]+((ik[10][1][2]*Otkr[3][2])+((
      ik[10][1][0]*Otkr[3][0])+(ik[10][1][1]*Otkr[3][1])))));
    tstarr[3][2] = (utk[10][2]-(WkIkWk[3][2]+((ik[10][2][2]*Otkr[3][2])+((
      ik[10][2][0]*Otkr[3][0])+(ik[10][2][1]*Otkr[3][1])))));
    tstarr[4][0] = (utk[11][0]-(WkIkWk[4][0]+((ik[11][0][2]*Otkr[4][2])+((
      ik[11][0][0]*Otkr[4][0])+(ik[11][0][1]*Otkr[4][1])))));
    tstarr[4][1] = (utk[11][1]-(WkIkWk[4][1]+((ik[11][1][2]*Otkr[4][2])+((
      ik[11][1][0]*Otkr[4][0])+(ik[11][1][1]*Otkr[4][1])))));
    tstarr[4][2] = (utk[11][2]-(WkIkWk[4][2]+((ik[11][2][2]*Otkr[4][2])+((
      ik[11][2][0]*Otkr[4][0])+(ik[11][2][1]*Otkr[4][1])))));
/*
Now calculate the torques
*/
    trqout[4] = -((mtau[4]+utau[4])+(((fstarr[4][2]*rkWkk[4][2])+((fstarr[4][0]*
      rkWkk[4][0])+(fstarr[4][1]*rkWkk[4][1])))+((pin[4][2]*tstarr[4][2])+((
      pin[4][0]*tstarr[4][0])+(pin[4][1]*tstarr[4][1])))));
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
    trqout[3] = -((mtau[3]+utau[3])+(((Fstark[3][2]*rkWkk[3][2])+((Fstark[3][0]*
      rkWkk[3][0])+(Fstark[3][1]*rkWkk[3][1])))+((pin[3][2]*Tstark[3][2])+((
      pin[3][0]*Tstark[3][0])+(pin[3][1]*Tstark[3][1])))));
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
    trqout[2] = -((mtau[2]+utau[2])+(((Fstark[2][2]*rkWkk[2][2])+((Fstark[2][0]*
      rkWkk[2][0])+(Fstark[2][1]*rkWkk[2][1])))+((pin[2][2]*Tstark[2][2])+((
      pin[2][0]*Tstark[2][0])+(pin[2][1]*Tstark[2][1])))));
    Fstark[1][0] = (fstarr[1][0]+((Cik[2][0][2]*Fstark[2][2])+((Cik[2][0][0]*
      Fstark[2][0])+(Cik[2][0][1]*Fstark[2][1]))));
    Fstark[1][1] = (fstarr[1][1]+((Cik[2][1][2]*Fstark[2][2])+((Cik[2][1][0]*
      Fstark[2][0])+(Cik[2][1][1]*Fstark[2][1]))));
    Fstark[1][2] = (fstarr[1][2]+((Cik[2][2][2]*Fstark[2][2])+((Cik[2][2][0]*
      Fstark[2][0])+(Cik[2][2][1]*Fstark[2][1]))));
    tvec1[0] = (Tstark[2][0]+((Fstark[2][2]*rik[2][1])-(Fstark[2][1]*rik[2][2]))
      );
    tvec1[1] = (Tstark[2][1]+((Fstark[2][0]*rik[2][2])-(Fstark[2][2]*rik[2][0]))
      );
    tvec1[2] = (Tstark[2][2]+((Fstark[2][1]*rik[2][0])-(Fstark[2][0]*rik[2][1]))
      );
    Tstark[1][0] = (tstarr[1][0]+((Cik[2][0][2]*tvec1[2])+((Cik[2][0][0]*
      tvec1[0])+(Cik[2][0][1]*tvec1[1]))));
    Tstark[1][1] = (tstarr[1][1]+((Cik[2][1][2]*tvec1[2])+((Cik[2][1][0]*
      tvec1[0])+(Cik[2][1][1]*tvec1[1]))));
    Tstark[1][2] = (tstarr[1][2]+((Cik[2][2][2]*tvec1[2])+((Cik[2][2][0]*
      tvec1[0])+(Cik[2][2][1]*tvec1[1]))));
    trqout[1] = -((mtau[1]+utau[1])+(((Fstark[1][2]*rkWkk[1][2])+((Fstark[1][0]*
      rkWkk[1][0])+(Fstark[1][1]*rkWkk[1][1])))+((pin[1][2]*Tstark[1][2])+((
      pin[1][0]*Tstark[1][0])+(pin[1][1]*Tstark[1][1])))));
    Fstark[0][0] = (fstarr[0][0]+((Cik[1][0][2]*Fstark[1][2])+((Cik[1][0][0]*
      Fstark[1][0])+(Cik[1][0][1]*Fstark[1][1]))));
    Fstark[0][1] = (fstarr[0][1]+((Cik[1][1][2]*Fstark[1][2])+((Cik[1][1][0]*
      Fstark[1][0])+(Cik[1][1][1]*Fstark[1][1]))));
    Fstark[0][2] = (fstarr[0][2]+((Cik[1][2][2]*Fstark[1][2])+((Cik[1][2][0]*
      Fstark[1][0])+(Cik[1][2][1]*Fstark[1][1]))));
    tvec1[0] = (Tstark[1][0]+((Fstark[1][2]*rik[1][1])-(Fstark[1][1]*rik[1][2]))
      );
    tvec1[1] = (Tstark[1][1]+((Fstark[1][0]*rik[1][2])-(Fstark[1][2]*rik[1][0]))
      );
    tvec1[2] = (Tstark[1][2]+((Fstark[1][1]*rik[1][0])-(Fstark[1][0]*rik[1][1]))
      );
    Tstark[0][0] = (tstarr[0][0]+((Cik[1][0][2]*tvec1[2])+((Cik[1][0][0]*
      tvec1[0])+(Cik[1][0][1]*tvec1[1]))));
    Tstark[0][1] = (tstarr[0][1]+((Cik[1][1][2]*tvec1[2])+((Cik[1][1][0]*
      tvec1[0])+(Cik[1][1][1]*tvec1[1]))));
    Tstark[0][2] = (tstarr[0][2]+((Cik[1][2][2]*tvec1[2])+((Cik[1][2][0]*
      tvec1[0])+(Cik[1][2][1]*tvec1[1]))));
    trqout[0] = -((mtau[0]+utau[0])+(((Fstark[0][2]*rkWkk[0][2])+((Fstark[0][0]*
      rkWkk[0][0])+(Fstark[0][1]*rkWkk[0][1])))+((pin[0][2]*Tstark[0][2])+((
      pin[0][0]*Tstark[0][0])+(pin[0][1]*Tstark[0][1])))));
/*
Op counts below do not include called subroutines
*/
/*
 Used -0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain  415 adds/subtracts/negates
                    405 multiplies
                      0 divides
                    113 assignments
*/
}

void sdcomptrq(double udotin[5],
    double trqout[5])
{
/* Compute hinge torques to produce these udots, ignoring constraints
*/
    int i;
    double multin[5];

    if ((roustate != 2) && (roustate != 3)) {
        sdseterr(60,23);
        return;
    }
    for (i = 0; i < 5; i++) {
        multin[i] = 0.;
    }
    sdfulltrq(udotin,multin,trqout);
}

void sdmulttrq(double multin[5],
    double trqout[5])
{
/* Compute hinge trqs which would be produced by these mults.
*/
    int i;

    if ((roustate != 2) && (roustate != 3)) {
        sdseterr(65,23);
        return;
    }
    sdmfrc(multin);
    sdfsmult();
    for (i = 0; i < 5; i++) {
        trqout[i] = fs[i];
    }
}

void sdrhs(void)
{
/*
Generated 24-May-2007 16:22:11 by SD/FAST, Order(N) formulation
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
    tauc[0] = (mtau[0]+utau[0]);
    tauc[1] = (mtau[1]+utau[1]);
    tauc[2] = (mtau[2]+utau[2]);
    tauc[3] = (mtau[3]+utau[3]);
    tauc[4] = (mtau[4]+utau[4]);
    sddoiner();
/*
Compute onk & onb (angular accels in N)
*/
    Onkb[0][0] = (pin[0][0]*udot[0]);
    Onkb[0][1] = (pin[0][1]*udot[0]);
    Onkb[0][2] = (pin[0][2]*udot[0]);
    Onkb[1][0] = ((pin[1][0]*udot[1])+((Cik[1][2][0]*Onkb[0][2])+((Cik[1][0][0]*
      Onkb[0][0])+(Cik[1][1][0]*Onkb[0][1]))));
    Onkb[1][1] = ((pin[1][1]*udot[1])+((Cik[1][2][1]*Onkb[0][2])+((Cik[1][0][1]*
      Onkb[0][0])+(Cik[1][1][1]*Onkb[0][1]))));
    Onkb[1][2] = ((pin[1][2]*udot[1])+((Cik[1][2][2]*Onkb[0][2])+((Cik[1][0][2]*
      Onkb[0][0])+(Cik[1][1][2]*Onkb[0][1]))));
    Onkb[2][0] = ((pin[2][0]*udot[2])+((Cik[2][2][0]*Onkb[1][2])+((Cik[2][0][0]*
      Onkb[1][0])+(Cik[2][1][0]*Onkb[1][1]))));
    Onkb[2][1] = ((pin[2][1]*udot[2])+((Cik[2][2][1]*Onkb[1][2])+((Cik[2][0][1]*
      Onkb[1][0])+(Cik[2][1][1]*Onkb[1][1]))));
    Onkb[2][2] = ((pin[2][2]*udot[2])+((Cik[2][2][2]*Onkb[1][2])+((Cik[2][0][2]*
      Onkb[1][0])+(Cik[2][1][2]*Onkb[1][1]))));
    Onkb[3][0] = ((pin[3][0]*udot[3])+((Cik[3][2][0]*Onkb[2][2])+((Cik[3][0][0]*
      Onkb[2][0])+(Cik[3][1][0]*Onkb[2][1]))));
    Onkb[3][1] = ((pin[3][1]*udot[3])+((Cik[3][2][1]*Onkb[2][2])+((Cik[3][0][1]*
      Onkb[2][0])+(Cik[3][1][1]*Onkb[2][1]))));
    Onkb[3][2] = ((pin[3][2]*udot[3])+((Cik[3][2][2]*Onkb[2][2])+((Cik[3][0][2]*
      Onkb[2][0])+(Cik[3][1][2]*Onkb[2][1]))));
    Onkb[4][0] = ((pin[4][0]*udot[4])+((Cik[4][2][0]*Onkb[3][2])+((Cik[4][0][0]*
      Onkb[3][0])+(Cik[4][1][0]*Onkb[3][1]))));
    Onkb[4][1] = ((pin[4][1]*udot[4])+((Cik[4][2][1]*Onkb[3][2])+((Cik[4][0][1]*
      Onkb[3][0])+(Cik[4][1][1]*Onkb[3][1]))));
    Onkb[4][2] = ((pin[4][2]*udot[4])+((Cik[4][2][2]*Onkb[3][2])+((Cik[4][0][2]*
      Onkb[3][0])+(Cik[4][1][2]*Onkb[3][1]))));
    onk[1][0] = (Onkb[1][0]+Otk[1][0]);
    onk[1][1] = (Onkb[1][1]+Otk[1][1]);
    onk[1][2] = (Onkb[1][2]+Otk[1][2]);
    onk[2][0] = (Onkb[2][0]+Otk[2][0]);
    onk[2][1] = (Onkb[2][1]+Otk[2][1]);
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
    onb[7][0] = Onkb[0][0];
    onb[7][1] = Onkb[0][1];
    onb[7][2] = Onkb[0][2];
    onb[8][0] = onk[1][0];
    onb[8][1] = onk[1][1];
    onb[8][2] = onk[1][2];
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
    dyad[7][0][0] = w11w22[7];
    dyad[7][0][1] = (w0w1[7]-Onkb[0][2]);
    dyad[7][0][2] = (Onkb[0][1]+w0w2[7]);
    dyad[7][1][0] = (Onkb[0][2]+w0w1[7]);
    dyad[7][1][1] = w00w22[7];
    dyad[7][1][2] = (w1w2[7]-Onkb[0][0]);
    dyad[7][2][0] = (w0w2[7]-Onkb[0][1]);
    dyad[7][2][1] = (Onkb[0][0]+w1w2[7]);
    dyad[7][2][2] = w00w11[7];
    dyad[8][0][0] = w11w22[8];
    dyad[8][0][1] = (w0w1[8]-onk[1][2]);
    dyad[8][0][2] = (onk[1][1]+w0w2[8]);
    dyad[8][1][0] = (onk[1][2]+w0w1[8]);
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
    Ankb[0][0] = ((Onkb[0][2]*rk[7][1])-(Onkb[0][1]*rk[7][2]));
    Ankb[0][1] = ((Onkb[0][0]*rk[7][2])-(Onkb[0][2]*rk[7][0]));
    Ankb[0][2] = ((Onkb[0][1]*rk[7][0])-(Onkb[0][0]*rk[7][1]));
    AOnkri[1][0] = (Ankb[0][0]+((Onkb[0][1]*ri[8][2])-(Onkb[0][2]*ri[8][1])));
    AOnkri[1][1] = (Ankb[0][1]+((Onkb[0][2]*ri[8][0])-(Onkb[0][0]*ri[8][2])));
    AOnkri[1][2] = (Ankb[0][2]+((Onkb[0][0]*ri[8][1])-(Onkb[0][1]*ri[8][0])));
    Ankb[1][0] = (((AOnkri[1][2]*Cik[1][2][0])+((AOnkri[1][0]*Cik[1][0][0])+(
      AOnkri[1][1]*Cik[1][1][0])))+((Onkb[1][2]*rk[8][1])-(Onkb[1][1]*rk[8][2]))
      );
    Ankb[1][1] = (((AOnkri[1][2]*Cik[1][2][1])+((AOnkri[1][0]*Cik[1][0][1])+(
      AOnkri[1][1]*Cik[1][1][1])))+((Onkb[1][0]*rk[8][2])-(Onkb[1][2]*rk[8][0]))
      );
    Ankb[1][2] = (((AOnkri[1][2]*Cik[1][2][2])+((AOnkri[1][0]*Cik[1][0][2])+(
      AOnkri[1][1]*Cik[1][1][2])))+((Onkb[1][1]*rk[8][0])-(Onkb[1][0]*rk[8][1]))
      );
    AOnkri[2][0] = (Ankb[1][0]+((Onkb[1][1]*ri[9][2])-(Onkb[1][2]*ri[9][1])));
    AOnkri[2][1] = (Ankb[1][1]+((Onkb[1][2]*ri[9][0])-(Onkb[1][0]*ri[9][2])));
    AOnkri[2][2] = (Ankb[1][2]+((Onkb[1][0]*ri[9][1])-(Onkb[1][1]*ri[9][0])));
    Ankb[2][0] = (((AOnkri[2][2]*Cik[2][2][0])+((AOnkri[2][0]*Cik[2][0][0])+(
      AOnkri[2][1]*Cik[2][1][0])))+((Onkb[2][2]*rk[9][1])-(Onkb[2][1]*rk[9][2]))
      );
    Ankb[2][1] = (((AOnkri[2][2]*Cik[2][2][1])+((AOnkri[2][0]*Cik[2][0][1])+(
      AOnkri[2][1]*Cik[2][1][1])))+((Onkb[2][0]*rk[9][2])-(Onkb[2][2]*rk[9][0]))
      );
    Ankb[2][2] = (((AOnkri[2][2]*Cik[2][2][2])+((AOnkri[2][0]*Cik[2][0][2])+(
      AOnkri[2][1]*Cik[2][1][2])))+((Onkb[2][1]*rk[9][0])-(Onkb[2][0]*rk[9][1]))
      );
    AOnkri[3][0] = (Ankb[2][0]+((Onkb[2][1]*ri[10][2])-(Onkb[2][2]*ri[10][1])));
    AOnkri[3][1] = (Ankb[2][1]+((Onkb[2][2]*ri[10][0])-(Onkb[2][0]*ri[10][2])));
    AOnkri[3][2] = (Ankb[2][2]+((Onkb[2][0]*ri[10][1])-(Onkb[2][1]*ri[10][0])));
    Ankb[3][0] = (((AOnkri[3][2]*Cik[3][2][0])+((AOnkri[3][0]*Cik[3][0][0])+(
      AOnkri[3][1]*Cik[3][1][0])))+((Onkb[3][2]*rk[10][1])-(Onkb[3][1]*rk[10][2]
      )));
    Ankb[3][1] = (((AOnkri[3][2]*Cik[3][2][1])+((AOnkri[3][0]*Cik[3][0][1])+(
      AOnkri[3][1]*Cik[3][1][1])))+((Onkb[3][0]*rk[10][2])-(Onkb[3][2]*rk[10][0]
      )));
    Ankb[3][2] = (((AOnkri[3][2]*Cik[3][2][2])+((AOnkri[3][0]*Cik[3][0][2])+(
      AOnkri[3][1]*Cik[3][1][2])))+((Onkb[3][1]*rk[10][0])-(Onkb[3][0]*rk[10][1]
      )));
    AOnkri[4][0] = (Ankb[3][0]+((Onkb[3][1]*ri[11][2])-(Onkb[3][2]*ri[11][1])));
    AOnkri[4][1] = (Ankb[3][1]+((Onkb[3][2]*ri[11][0])-(Onkb[3][0]*ri[11][2])));
    AOnkri[4][2] = (Ankb[3][2]+((Onkb[3][0]*ri[11][1])-(Onkb[3][1]*ri[11][0])));
    Ankb[4][0] = (((AOnkri[4][2]*Cik[4][2][0])+((AOnkri[4][0]*Cik[4][0][0])+(
      AOnkri[4][1]*Cik[4][1][0])))+((Onkb[4][2]*rk[11][1])-(Onkb[4][1]*rk[11][2]
      )));
    Ankb[4][1] = (((AOnkri[4][2]*Cik[4][2][1])+((AOnkri[4][0]*Cik[4][0][1])+(
      AOnkri[4][1]*Cik[4][1][1])))+((Onkb[4][0]*rk[11][2])-(Onkb[4][2]*rk[11][0]
      )));
    Ankb[4][2] = (((AOnkri[4][2]*Cik[4][2][2])+((AOnkri[4][0]*Cik[4][0][2])+(
      AOnkri[4][1]*Cik[4][1][2])))+((Onkb[4][1]*rk[11][0])-(Onkb[4][0]*rk[11][1]
      )));
    AnkAtk[0][0] = (Ankb[0][0]+Atk[0][0]);
    AnkAtk[0][1] = (Ankb[0][1]+Atk[0][1]);
    AnkAtk[0][2] = (Ankb[0][2]+Atk[0][2]);
    ank[0][0] = ((AnkAtk[0][2]*Cik[0][0][2])+((AnkAtk[0][0]*Cik[0][0][0])+(
      AnkAtk[0][1]*Cik[0][0][1])));
    ank[0][1] = ((AnkAtk[0][2]*Cik[0][1][2])+((AnkAtk[0][0]*Cik[0][1][0])+(
      AnkAtk[0][1]*Cik[0][1][1])));
    ank[0][2] = ((AnkAtk[0][2]*Cik[0][2][2])+((AnkAtk[0][0]*Cik[0][2][0])+(
      AnkAtk[0][1]*Cik[0][2][1])));
    AnkAtk[1][0] = (Ankb[1][0]+Atk[1][0]);
    AnkAtk[1][1] = (Ankb[1][1]+Atk[1][1]);
    AnkAtk[1][2] = (Ankb[1][2]+Atk[1][2]);
    ank[1][0] = ((AnkAtk[1][2]*cnk[1][0][2])+((AnkAtk[1][0]*cnk[1][0][0])+(
      AnkAtk[1][1]*cnk[1][0][1])));
    ank[1][1] = ((AnkAtk[1][2]*cnk[1][1][2])+((AnkAtk[1][0]*cnk[1][1][0])+(
      AnkAtk[1][1]*cnk[1][1][1])));
    ank[1][2] = ((AnkAtk[1][2]*cnk[1][2][2])+((AnkAtk[1][0]*cnk[1][2][0])+(
      AnkAtk[1][1]*cnk[1][2][1])));
    AnkAtk[2][0] = (Ankb[2][0]+Atk[2][0]);
    AnkAtk[2][1] = (Ankb[2][1]+Atk[2][1]);
    AnkAtk[2][2] = (Ankb[2][2]+Atk[2][2]);
    ank[2][0] = ((AnkAtk[2][2]*cnk[2][0][2])+((AnkAtk[2][0]*cnk[2][0][0])+(
      AnkAtk[2][1]*cnk[2][0][1])));
    ank[2][1] = ((AnkAtk[2][2]*cnk[2][1][2])+((AnkAtk[2][0]*cnk[2][1][0])+(
      AnkAtk[2][1]*cnk[2][1][1])));
    ank[2][2] = ((AnkAtk[2][2]*cnk[2][2][2])+((AnkAtk[2][0]*cnk[2][2][0])+(
      AnkAtk[2][1]*cnk[2][2][1])));
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
    anb[7][0] = ank[0][0];
    anb[7][1] = ank[0][1];
    anb[7][2] = ank[0][2];
    anb[8][0] = ank[1][0];
    anb[8][1] = ank[1][1];
    anb[8][2] = ank[1][2];
    anb[9][0] = ank[2][0];
    anb[9][1] = ank[2][1];
    anb[9][2] = ank[2][2];
    anb[10][0] = ank[3][0];
    anb[10][1] = ank[3][1];
    anb[10][2] = ank[3][2];
    anb[11][0] = ank[4][0];
    anb[11][1] = ank[4][1];
    anb[11][2] = ank[4][2];
/*
Compute constraint acceleration errors
*/
    roustate = 3;
/*
 Used -0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain  203 adds/subtracts/negates
                    186 multiplies
                      0 divides
                    269 assignments
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

void sdperr(double errs[5])
{
/*
Return position constraint errors.

*/

    if ((roustate != 2) && (roustate != 3)) {
        sdseterr(26,23);
        return;
    }
    perr[0] = (q[0]-upos[0]);
    perr[1] = (q[1]-upos[1]);
    perr[2] = (q[2]-upos[2]);
    perr[3] = (q[3]-upos[3]);
    perr[4] = (q[4]-upos[4]);
    errs[0] = perr[0];
    errs[1] = perr[1];
    errs[2] = perr[2];
    errs[3] = perr[3];
    errs[4] = perr[4];
}

void sdverr(double errs[5])
{
/*
Return velocity constraint errors.

*/

    if ((roustate != 2) && (roustate != 3)) {
        sdseterr(27,23);
        return;
    }
    verr[0] = (u[0]-uvel[0]);
    verr[1] = (u[1]-uvel[1]);
    verr[2] = (u[2]-uvel[2]);
    verr[3] = (u[3]-uvel[3]);
    verr[4] = (u[4]-uvel[4]);
    errs[0] = verr[0];
    errs[1] = verr[1];
    errs[2] = verr[2];
    errs[3] = verr[3];
    errs[4] = verr[4];
}

void sdaerr(double errs[5])
{
/*
Return acceleration constraint errors.

*/

    if (roustate != 3) {
        sdseterr(35,24);
        return;
    }
    aerr[0] = (udot[0]-uacc[0]);
    aerr[1] = (udot[1]-uacc[1]);
    aerr[2] = (udot[2]-uacc[2]);
    aerr[3] = (udot[3]-uacc[3]);
    aerr[4] = (udot[4]-uacc[4]);
    errs[0] = aerr[0];
    errs[1] = aerr[1];
    errs[2] = aerr[2];
    errs[3] = aerr[3];
    errs[4] = aerr[4];
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

    if (sdchkjaxis(13,joint,axis) != 0) {
        return;
    }
    if (roustate != 2) {
        sdseterr(13,23);
        return;
    }
    if (pres[sdindx(joint,axis)]  !=  0.) {
        uacc[sdindx(joint,axis)] = prval;
    }
}

void sdpresvel(int joint,
    int axis,
    double prval)
{

    if (sdchkjaxis(14,joint,axis) != 0) {
        return;
    }
    if (roustate != 2) {
        sdseterr(14,23);
        return;
    }
    if (pres[sdindx(joint,axis)]  !=  0.) {
        uvel[sdindx(joint,axis)] = prval;
    }
}

void sdprespos(int joint,
    int axis,
    double prval)
{

    if (sdchkjaxis(15,joint,axis) != 0) {
        return;
    }
    if (roustate != 2) {
        sdseterr(15,23);
        return;
    }
    if (pres[sdindx(joint,axis)]  !=  0.) {
        upos[sdindx(joint,axis)] = prval;
    }
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
    double pp[5][5],dpp[5][5];
    int i,j,c;
    double sum;
    double dfk[12][3],dtk[12][3],dtau[5],dltci[1][3],dltc[1][3],dlfci[1][3],dlfc
      [1][3];
    double dTinb[1][3],dToutb[1][3],dltaufi[1][3],dltaufo[1][3],dltauti[1][3],
      dltauto[1][3];
    double deps[5],dZ1[5][3],dZ2[5][3];

    roustate = 2;
    if (wwflg == 0) {
/*
Compute constraint effects
*/
        sddomm(routine);
/*
Constraint 0 (prescribed motion)
*/
        deps[4] = 0.;
        deps[3] = 0.;
        deps[2] = 0.;
        deps[1] = 0.;
        deps[0] = 1.;
        for (i = 0; i <= 4; i++) {
            pp[0][i] = deps[i];
            dpp[i][0] = DD[i]*deps[i];
        }
        wmap[0] = 0;
/*
Constraint 1 (prescribed motion)
*/
        deps[4] = 0.;
        deps[3] = 0.;
        deps[2] = 0.;
        deps[1] = 1.;
        dZ1[0][0] = ((Cik[1][0][2]*G1[1][2])+((Cik[1][0][0]*G1[1][0])+(
          Cik[1][0][1]*G1[1][1])));
        dZ1[0][1] = ((Cik[1][1][2]*G1[1][2])+((Cik[1][1][0]*G1[1][0])+(
          Cik[1][1][1]*G1[1][1])));
        dZ1[0][2] = ((Cik[1][2][2]*G1[1][2])+((Cik[1][2][0]*G1[1][0])+(
          Cik[1][2][1]*G1[1][1])));
        dZ2[0][0] = (((Cik[1][0][2]*G2[1][2])+((Cik[1][0][0]*G2[1][0])+(
          Cik[1][0][1]*G2[1][1])))+((G1[1][2]*rikt[1][0][2])+((G1[1][0]*
          rikt[1][0][0])+(G1[1][1]*rikt[1][0][1]))));
        dZ2[0][1] = (((Cik[1][1][2]*G2[1][2])+((Cik[1][1][0]*G2[1][0])+(
          Cik[1][1][1]*G2[1][1])))+((G1[1][2]*rikt[1][1][2])+((G1[1][0]*
          rikt[1][1][0])+(G1[1][1]*rikt[1][1][1]))));
        dZ2[0][2] = (((Cik[1][2][2]*G2[1][2])+((Cik[1][2][0]*G2[1][0])+(
          Cik[1][2][1]*G2[1][1])))+((G1[1][2]*rikt[1][2][2])+((G1[1][0]*
          rikt[1][2][0])+(G1[1][1]*rikt[1][2][1]))));
        deps[0] = -((dZ2[0][2]*pin[0][2])+((dZ2[0][0]*pin[0][0])+(dZ2[0][1]*
          pin[0][1])));
        for (i = 0; i <= 4; i++) {
            pp[1][i] = deps[i];
            dpp[i][1] = DD[i]*deps[i];
        }
        wmap[1] = 1;
/*
Constraint 2 (prescribed motion)
*/
        deps[4] = 0.;
        deps[3] = 0.;
        deps[2] = 1.;
        dZ1[1][0] = ((Cik[2][0][2]*G1[2][2])+((Cik[2][0][0]*G1[2][0])+(
          Cik[2][0][1]*G1[2][1])));
        dZ1[1][1] = ((Cik[2][1][2]*G1[2][2])+((Cik[2][1][0]*G1[2][0])+(
          Cik[2][1][1]*G1[2][1])));
        dZ1[1][2] = ((Cik[2][2][2]*G1[2][2])+((Cik[2][2][0]*G1[2][0])+(
          Cik[2][2][1]*G1[2][1])));
        dZ2[1][0] = (((Cik[2][0][2]*G2[2][2])+((Cik[2][0][0]*G2[2][0])+(
          Cik[2][0][1]*G2[2][1])))+((G1[2][2]*rikt[2][0][2])+((G1[2][0]*
          rikt[2][0][0])+(G1[2][1]*rikt[2][0][1]))));
        dZ2[1][1] = (((Cik[2][1][2]*G2[2][2])+((Cik[2][1][0]*G2[2][0])+(
          Cik[2][1][1]*G2[2][1])))+((G1[2][2]*rikt[2][1][2])+((G1[2][0]*
          rikt[2][1][0])+(G1[2][1]*rikt[2][1][1]))));
        dZ2[1][2] = (((Cik[2][2][2]*G2[2][2])+((Cik[2][2][0]*G2[2][0])+(
          Cik[2][2][1]*G2[2][1])))+((G1[2][2]*rikt[2][2][2])+((G1[2][0]*
          rikt[2][2][0])+(G1[2][1]*rikt[2][2][1]))));
        deps[1] = -((dZ2[1][2]*pin[1][2])+((dZ2[1][0]*pin[1][0])+(dZ2[1][1]*
          pin[1][1])));
        dZ1[1][0] = (dZ1[1][0]+(deps[1]*G1[1][0]));
        dZ1[1][1] = (dZ1[1][1]+(deps[1]*G1[1][1]));
        dZ1[1][2] = (dZ1[1][2]+(deps[1]*G1[1][2]));
        dZ2[1][0] = (dZ2[1][0]+(deps[1]*G2[1][0]));
        dZ2[1][1] = (dZ2[1][1]+(deps[1]*G2[1][1]));
        dZ2[1][2] = (dZ2[1][2]+(deps[1]*G2[1][2]));
        dZ1[0][0] = ((Cik[1][0][2]*dZ1[1][2])+((Cik[1][0][0]*dZ1[1][0])+(
          Cik[1][0][1]*dZ1[1][1])));
        dZ1[0][1] = ((Cik[1][1][2]*dZ1[1][2])+((Cik[1][1][0]*dZ1[1][0])+(
          Cik[1][1][1]*dZ1[1][1])));
        dZ1[0][2] = ((Cik[1][2][2]*dZ1[1][2])+((Cik[1][2][0]*dZ1[1][0])+(
          Cik[1][2][1]*dZ1[1][1])));
        dZ2[0][0] = (((Cik[1][0][2]*dZ2[1][2])+((Cik[1][0][0]*dZ2[1][0])+(
          Cik[1][0][1]*dZ2[1][1])))+((dZ1[1][2]*rikt[1][0][2])+((dZ1[1][0]*
          rikt[1][0][0])+(dZ1[1][1]*rikt[1][0][1]))));
        dZ2[0][1] = (((Cik[1][1][2]*dZ2[1][2])+((Cik[1][1][0]*dZ2[1][0])+(
          Cik[1][1][1]*dZ2[1][1])))+((dZ1[1][2]*rikt[1][1][2])+((dZ1[1][0]*
          rikt[1][1][0])+(dZ1[1][1]*rikt[1][1][1]))));
        dZ2[0][2] = (((Cik[1][2][2]*dZ2[1][2])+((Cik[1][2][0]*dZ2[1][0])+(
          Cik[1][2][1]*dZ2[1][1])))+((dZ1[1][2]*rikt[1][2][2])+((dZ1[1][0]*
          rikt[1][2][0])+(dZ1[1][1]*rikt[1][2][1]))));
        deps[0] = -((dZ2[0][2]*pin[0][2])+((dZ2[0][0]*pin[0][0])+(dZ2[0][1]*
          pin[0][1])));
        for (i = 0; i <= 4; i++) {
            pp[2][i] = deps[i];
            dpp[i][2] = DD[i]*deps[i];
        }
        wmap[2] = 2;
/*
Constraint 3 (prescribed motion)
*/
        deps[4] = 0.;
        deps[3] = 1.;
        dZ1[2][0] = ((Cik[3][0][2]*G1[3][2])+((Cik[3][0][0]*G1[3][0])+(
          Cik[3][0][1]*G1[3][1])));
        dZ1[2][1] = ((Cik[3][1][2]*G1[3][2])+((Cik[3][1][0]*G1[3][0])+(
          Cik[3][1][1]*G1[3][1])));
        dZ1[2][2] = ((Cik[3][2][2]*G1[3][2])+((Cik[3][2][0]*G1[3][0])+(
          Cik[3][2][1]*G1[3][1])));
        dZ2[2][0] = (((Cik[3][0][2]*G2[3][2])+((Cik[3][0][0]*G2[3][0])+(
          Cik[3][0][1]*G2[3][1])))+((G1[3][2]*rikt[3][0][2])+((G1[3][0]*
          rikt[3][0][0])+(G1[3][1]*rikt[3][0][1]))));
        dZ2[2][1] = (((Cik[3][1][2]*G2[3][2])+((Cik[3][1][0]*G2[3][0])+(
          Cik[3][1][1]*G2[3][1])))+((G1[3][2]*rikt[3][1][2])+((G1[3][0]*
          rikt[3][1][0])+(G1[3][1]*rikt[3][1][1]))));
        dZ2[2][2] = (((Cik[3][2][2]*G2[3][2])+((Cik[3][2][0]*G2[3][0])+(
          Cik[3][2][1]*G2[3][1])))+((G1[3][2]*rikt[3][2][2])+((G1[3][0]*
          rikt[3][2][0])+(G1[3][1]*rikt[3][2][1]))));
        deps[2] = -((dZ2[2][2]*pin[2][2])+((dZ2[2][0]*pin[2][0])+(dZ2[2][1]*
          pin[2][1])));
        dZ1[2][0] = (dZ1[2][0]+(deps[2]*G1[2][0]));
        dZ1[2][1] = (dZ1[2][1]+(deps[2]*G1[2][1]));
        dZ1[2][2] = (dZ1[2][2]+(deps[2]*G1[2][2]));
        dZ2[2][0] = (dZ2[2][0]+(deps[2]*G2[2][0]));
        dZ2[2][1] = (dZ2[2][1]+(deps[2]*G2[2][1]));
        dZ2[2][2] = (dZ2[2][2]+(deps[2]*G2[2][2]));
        dZ1[1][0] = ((Cik[2][0][2]*dZ1[2][2])+((Cik[2][0][0]*dZ1[2][0])+(
          Cik[2][0][1]*dZ1[2][1])));
        dZ1[1][1] = ((Cik[2][1][2]*dZ1[2][2])+((Cik[2][1][0]*dZ1[2][0])+(
          Cik[2][1][1]*dZ1[2][1])));
        dZ1[1][2] = ((Cik[2][2][2]*dZ1[2][2])+((Cik[2][2][0]*dZ1[2][0])+(
          Cik[2][2][1]*dZ1[2][1])));
        dZ2[1][0] = (((Cik[2][0][2]*dZ2[2][2])+((Cik[2][0][0]*dZ2[2][0])+(
          Cik[2][0][1]*dZ2[2][1])))+((dZ1[2][2]*rikt[2][0][2])+((dZ1[2][0]*
          rikt[2][0][0])+(dZ1[2][1]*rikt[2][0][1]))));
        dZ2[1][1] = (((Cik[2][1][2]*dZ2[2][2])+((Cik[2][1][0]*dZ2[2][0])+(
          Cik[2][1][1]*dZ2[2][1])))+((dZ1[2][2]*rikt[2][1][2])+((dZ1[2][0]*
          rikt[2][1][0])+(dZ1[2][1]*rikt[2][1][1]))));
        dZ2[1][2] = (((Cik[2][2][2]*dZ2[2][2])+((Cik[2][2][0]*dZ2[2][0])+(
          Cik[2][2][1]*dZ2[2][1])))+((dZ1[2][2]*rikt[2][2][2])+((dZ1[2][0]*
          rikt[2][2][0])+(dZ1[2][1]*rikt[2][2][1]))));
        deps[1] = -((dZ2[1][2]*pin[1][2])+((dZ2[1][0]*pin[1][0])+(dZ2[1][1]*
          pin[1][1])));
        dZ1[1][0] = (dZ1[1][0]+(deps[1]*G1[1][0]));
        dZ1[1][1] = (dZ1[1][1]+(deps[1]*G1[1][1]));
        dZ1[1][2] = (dZ1[1][2]+(deps[1]*G1[1][2]));
        dZ2[1][0] = (dZ2[1][0]+(deps[1]*G2[1][0]));
        dZ2[1][1] = (dZ2[1][1]+(deps[1]*G2[1][1]));
        dZ2[1][2] = (dZ2[1][2]+(deps[1]*G2[1][2]));
        dZ1[0][0] = ((Cik[1][0][2]*dZ1[1][2])+((Cik[1][0][0]*dZ1[1][0])+(
          Cik[1][0][1]*dZ1[1][1])));
        dZ1[0][1] = ((Cik[1][1][2]*dZ1[1][2])+((Cik[1][1][0]*dZ1[1][0])+(
          Cik[1][1][1]*dZ1[1][1])));
        dZ1[0][2] = ((Cik[1][2][2]*dZ1[1][2])+((Cik[1][2][0]*dZ1[1][0])+(
          Cik[1][2][1]*dZ1[1][1])));
        dZ2[0][0] = (((Cik[1][0][2]*dZ2[1][2])+((Cik[1][0][0]*dZ2[1][0])+(
          Cik[1][0][1]*dZ2[1][1])))+((dZ1[1][2]*rikt[1][0][2])+((dZ1[1][0]*
          rikt[1][0][0])+(dZ1[1][1]*rikt[1][0][1]))));
        dZ2[0][1] = (((Cik[1][1][2]*dZ2[1][2])+((Cik[1][1][0]*dZ2[1][0])+(
          Cik[1][1][1]*dZ2[1][1])))+((dZ1[1][2]*rikt[1][1][2])+((dZ1[1][0]*
          rikt[1][1][0])+(dZ1[1][1]*rikt[1][1][1]))));
        dZ2[0][2] = (((Cik[1][2][2]*dZ2[1][2])+((Cik[1][2][0]*dZ2[1][0])+(
          Cik[1][2][1]*dZ2[1][1])))+((dZ1[1][2]*rikt[1][2][2])+((dZ1[1][0]*
          rikt[1][2][0])+(dZ1[1][1]*rikt[1][2][1]))));
        deps[0] = -((dZ2[0][2]*pin[0][2])+((dZ2[0][0]*pin[0][0])+(dZ2[0][1]*
          pin[0][1])));
        for (i = 0; i <= 4; i++) {
            pp[3][i] = deps[i];
            dpp[i][3] = DD[i]*deps[i];
        }
        wmap[3] = 3;
/*
Constraint 4 (prescribed motion)
*/
        deps[4] = 1.;
        dZ1[3][0] = ((Cik[4][0][2]*G1[4][2])+((Cik[4][0][0]*G1[4][0])+(
          Cik[4][0][1]*G1[4][1])));
        dZ1[3][1] = ((Cik[4][1][2]*G1[4][2])+((Cik[4][1][0]*G1[4][0])+(
          Cik[4][1][1]*G1[4][1])));
        dZ1[3][2] = ((Cik[4][2][2]*G1[4][2])+((Cik[4][2][0]*G1[4][0])+(
          Cik[4][2][1]*G1[4][1])));
        dZ2[3][0] = (((Cik[4][0][2]*G2[4][2])+((Cik[4][0][0]*G2[4][0])+(
          Cik[4][0][1]*G2[4][1])))+((G1[4][2]*rikt[4][0][2])+((G1[4][0]*
          rikt[4][0][0])+(G1[4][1]*rikt[4][0][1]))));
        dZ2[3][1] = (((Cik[4][1][2]*G2[4][2])+((Cik[4][1][0]*G2[4][0])+(
          Cik[4][1][1]*G2[4][1])))+((G1[4][2]*rikt[4][1][2])+((G1[4][0]*
          rikt[4][1][0])+(G1[4][1]*rikt[4][1][1]))));
        dZ2[3][2] = (((Cik[4][2][2]*G2[4][2])+((Cik[4][2][0]*G2[4][0])+(
          Cik[4][2][1]*G2[4][1])))+((G1[4][2]*rikt[4][2][2])+((G1[4][0]*
          rikt[4][2][0])+(G1[4][1]*rikt[4][2][1]))));
        deps[3] = -((dZ2[3][2]*pin[3][2])+((dZ2[3][0]*pin[3][0])+(dZ2[3][1]*
          pin[3][1])));
        dZ1[3][0] = (dZ1[3][0]+(deps[3]*G1[3][0]));
        dZ1[3][1] = (dZ1[3][1]+(deps[3]*G1[3][1]));
        dZ1[3][2] = (dZ1[3][2]+(deps[3]*G1[3][2]));
        dZ2[3][0] = (dZ2[3][0]+(deps[3]*G2[3][0]));
        dZ2[3][1] = (dZ2[3][1]+(deps[3]*G2[3][1]));
        dZ2[3][2] = (dZ2[3][2]+(deps[3]*G2[3][2]));
        dZ1[2][0] = ((Cik[3][0][2]*dZ1[3][2])+((Cik[3][0][0]*dZ1[3][0])+(
          Cik[3][0][1]*dZ1[3][1])));
        dZ1[2][1] = ((Cik[3][1][2]*dZ1[3][2])+((Cik[3][1][0]*dZ1[3][0])+(
          Cik[3][1][1]*dZ1[3][1])));
        dZ1[2][2] = ((Cik[3][2][2]*dZ1[3][2])+((Cik[3][2][0]*dZ1[3][0])+(
          Cik[3][2][1]*dZ1[3][1])));
        dZ2[2][0] = (((Cik[3][0][2]*dZ2[3][2])+((Cik[3][0][0]*dZ2[3][0])+(
          Cik[3][0][1]*dZ2[3][1])))+((dZ1[3][2]*rikt[3][0][2])+((dZ1[3][0]*
          rikt[3][0][0])+(dZ1[3][1]*rikt[3][0][1]))));
        dZ2[2][1] = (((Cik[3][1][2]*dZ2[3][2])+((Cik[3][1][0]*dZ2[3][0])+(
          Cik[3][1][1]*dZ2[3][1])))+((dZ1[3][2]*rikt[3][1][2])+((dZ1[3][0]*
          rikt[3][1][0])+(dZ1[3][1]*rikt[3][1][1]))));
        dZ2[2][2] = (((Cik[3][2][2]*dZ2[3][2])+((Cik[3][2][0]*dZ2[3][0])+(
          Cik[3][2][1]*dZ2[3][1])))+((dZ1[3][2]*rikt[3][2][2])+((dZ1[3][0]*
          rikt[3][2][0])+(dZ1[3][1]*rikt[3][2][1]))));
        deps[2] = -((dZ2[2][2]*pin[2][2])+((dZ2[2][0]*pin[2][0])+(dZ2[2][1]*
          pin[2][1])));
        dZ1[2][0] = (dZ1[2][0]+(deps[2]*G1[2][0]));
        dZ1[2][1] = (dZ1[2][1]+(deps[2]*G1[2][1]));
        dZ1[2][2] = (dZ1[2][2]+(deps[2]*G1[2][2]));
        dZ2[2][0] = (dZ2[2][0]+(deps[2]*G2[2][0]));
        dZ2[2][1] = (dZ2[2][1]+(deps[2]*G2[2][1]));
        dZ2[2][2] = (dZ2[2][2]+(deps[2]*G2[2][2]));
        dZ1[1][0] = ((Cik[2][0][2]*dZ1[2][2])+((Cik[2][0][0]*dZ1[2][0])+(
          Cik[2][0][1]*dZ1[2][1])));
        dZ1[1][1] = ((Cik[2][1][2]*dZ1[2][2])+((Cik[2][1][0]*dZ1[2][0])+(
          Cik[2][1][1]*dZ1[2][1])));
        dZ1[1][2] = ((Cik[2][2][2]*dZ1[2][2])+((Cik[2][2][0]*dZ1[2][0])+(
          Cik[2][2][1]*dZ1[2][1])));
        dZ2[1][0] = (((Cik[2][0][2]*dZ2[2][2])+((Cik[2][0][0]*dZ2[2][0])+(
          Cik[2][0][1]*dZ2[2][1])))+((dZ1[2][2]*rikt[2][0][2])+((dZ1[2][0]*
          rikt[2][0][0])+(dZ1[2][1]*rikt[2][0][1]))));
        dZ2[1][1] = (((Cik[2][1][2]*dZ2[2][2])+((Cik[2][1][0]*dZ2[2][0])+(
          Cik[2][1][1]*dZ2[2][1])))+((dZ1[2][2]*rikt[2][1][2])+((dZ1[2][0]*
          rikt[2][1][0])+(dZ1[2][1]*rikt[2][1][1]))));
        dZ2[1][2] = (((Cik[2][2][2]*dZ2[2][2])+((Cik[2][2][0]*dZ2[2][0])+(
          Cik[2][2][1]*dZ2[2][1])))+((dZ1[2][2]*rikt[2][2][2])+((dZ1[2][0]*
          rikt[2][2][0])+(dZ1[2][1]*rikt[2][2][1]))));
        deps[1] = -((dZ2[1][2]*pin[1][2])+((dZ2[1][0]*pin[1][0])+(dZ2[1][1]*
          pin[1][1])));
        dZ1[1][0] = (dZ1[1][0]+(deps[1]*G1[1][0]));
        dZ1[1][1] = (dZ1[1][1]+(deps[1]*G1[1][1]));
        dZ1[1][2] = (dZ1[1][2]+(deps[1]*G1[1][2]));
        dZ2[1][0] = (dZ2[1][0]+(deps[1]*G2[1][0]));
        dZ2[1][1] = (dZ2[1][1]+(deps[1]*G2[1][1]));
        dZ2[1][2] = (dZ2[1][2]+(deps[1]*G2[1][2]));
        dZ1[0][0] = ((Cik[1][0][2]*dZ1[1][2])+((Cik[1][0][0]*dZ1[1][0])+(
          Cik[1][0][1]*dZ1[1][1])));
        dZ1[0][1] = ((Cik[1][1][2]*dZ1[1][2])+((Cik[1][1][0]*dZ1[1][0])+(
          Cik[1][1][1]*dZ1[1][1])));
        dZ1[0][2] = ((Cik[1][2][2]*dZ1[1][2])+((Cik[1][2][0]*dZ1[1][0])+(
          Cik[1][2][1]*dZ1[1][1])));
        dZ2[0][0] = (((Cik[1][0][2]*dZ2[1][2])+((Cik[1][0][0]*dZ2[1][0])+(
          Cik[1][0][1]*dZ2[1][1])))+((dZ1[1][2]*rikt[1][0][2])+((dZ1[1][0]*
          rikt[1][0][0])+(dZ1[1][1]*rikt[1][0][1]))));
        dZ2[0][1] = (((Cik[1][1][2]*dZ2[1][2])+((Cik[1][1][0]*dZ2[1][0])+(
          Cik[1][1][1]*dZ2[1][1])))+((dZ1[1][2]*rikt[1][1][2])+((dZ1[1][0]*
          rikt[1][1][0])+(dZ1[1][1]*rikt[1][1][1]))));
        dZ2[0][2] = (((Cik[1][2][2]*dZ2[1][2])+((Cik[1][2][0]*dZ2[1][0])+(
          Cik[1][2][1]*dZ2[1][1])))+((dZ1[1][2]*rikt[1][2][2])+((dZ1[1][0]*
          rikt[1][2][0])+(dZ1[1][1]*rikt[1][2][1]))));
        deps[0] = -((dZ2[0][2]*pin[0][2])+((dZ2[0][0]*pin[0][0])+(dZ2[0][1]*
          pin[0][1])));
        for (i = 0; i <= 4; i++) {
            pp[4][i] = deps[i];
            dpp[i][4] = DD[i]*deps[i];
        }
        wmap[4] = 4;
/*
Produce constraint coefficient matrix WW
*/
        for (c = 0; c <= 4; c++) {
            for (i = c; i <= 4; i++) {
                sum = 0.;
                for (j = 0; j <= 4; j++) {
                    sum = sum+pp[wmap[c]][j]*dpp[j][wmap[i]];
                }
                ww[wmap[c]][wmap[i]] = sum;
                ww[wmap[i]][wmap[c]] = sum;
            }
        }
/*
Form QR decomposition of WW
*/
        sdqrdcomp(5,5,5,5,wmap,wmap,ww,qraux,jpvt);
        wwflg = 1;
    }
/*
 Used 0.02 seconds CPU time,
 0 additional bytes of memory.
 Equations contain  351 adds/subtracts/negates
                    436 multiplies
                      0 divides
                    291 assignments
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
Solve equations ignoring constraints
*/
    eps[4] = fs0[4];
    Z1[4][0] = (eps[4]*G1[4][0]);
    Z1[4][1] = (eps[4]*G1[4][1]);
    Z1[4][2] = (eps[4]*G1[4][2]);
    Z2[4][0] = (eps[4]*G2[4][0]);
    Z2[4][1] = (eps[4]*G2[4][1]);
    Z2[4][2] = (eps[4]*G2[4][2]);
    Z1[3][0] = ((Cik[4][0][2]*Z1[4][2])+((Cik[4][0][0]*Z1[4][0])+(Cik[4][0][1]*
      Z1[4][1])));
    Z1[3][1] = ((Cik[4][1][2]*Z1[4][2])+((Cik[4][1][0]*Z1[4][0])+(Cik[4][1][1]*
      Z1[4][1])));
    Z1[3][2] = ((Cik[4][2][2]*Z1[4][2])+((Cik[4][2][0]*Z1[4][0])+(Cik[4][2][1]*
      Z1[4][1])));
    Z2[3][0] = (((Cik[4][0][2]*Z2[4][2])+((Cik[4][0][0]*Z2[4][0])+(Cik[4][0][1]*
      Z2[4][1])))+((rikt[4][0][2]*Z1[4][2])+((rikt[4][0][0]*Z1[4][0])+(
      rikt[4][0][1]*Z1[4][1]))));
    Z2[3][1] = (((Cik[4][1][2]*Z2[4][2])+((Cik[4][1][0]*Z2[4][0])+(Cik[4][1][1]*
      Z2[4][1])))+((rikt[4][1][2]*Z1[4][2])+((rikt[4][1][0]*Z1[4][0])+(
      rikt[4][1][1]*Z1[4][1]))));
    Z2[3][2] = (((Cik[4][2][2]*Z2[4][2])+((Cik[4][2][0]*Z2[4][0])+(Cik[4][2][1]*
      Z2[4][1])))+((rikt[4][2][2]*Z1[4][2])+((rikt[4][2][0]*Z1[4][0])+(
      rikt[4][2][1]*Z1[4][1]))));
    eps[3] = (fs0[3]-((pin[3][2]*Z2[3][2])+((pin[3][0]*Z2[3][0])+(pin[3][1]*
      Z2[3][1]))));
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
    eps[2] = (fs0[2]-((pin[2][2]*Z2[2][2])+((pin[2][0]*Z2[2][0])+(pin[2][1]*
      Z2[2][1]))));
    Z1[2][0] = (Z1[2][0]+(eps[2]*G1[2][0]));
    Z1[2][1] = (Z1[2][1]+(eps[2]*G1[2][1]));
    Z1[2][2] = (Z1[2][2]+(eps[2]*G1[2][2]));
    Z2[2][0] = (Z2[2][0]+(eps[2]*G2[2][0]));
    Z2[2][1] = (Z2[2][1]+(eps[2]*G2[2][1]));
    Z2[2][2] = (Z2[2][2]+(eps[2]*G2[2][2]));
    Z1[1][0] = ((Cik[2][0][2]*Z1[2][2])+((Cik[2][0][0]*Z1[2][0])+(Cik[2][0][1]*
      Z1[2][1])));
    Z1[1][1] = ((Cik[2][1][2]*Z1[2][2])+((Cik[2][1][0]*Z1[2][0])+(Cik[2][1][1]*
      Z1[2][1])));
    Z1[1][2] = ((Cik[2][2][2]*Z1[2][2])+((Cik[2][2][0]*Z1[2][0])+(Cik[2][2][1]*
      Z1[2][1])));
    Z2[1][0] = (((Cik[2][0][2]*Z2[2][2])+((Cik[2][0][0]*Z2[2][0])+(Cik[2][0][1]*
      Z2[2][1])))+((rikt[2][0][2]*Z1[2][2])+((rikt[2][0][0]*Z1[2][0])+(
      rikt[2][0][1]*Z1[2][1]))));
    Z2[1][1] = (((Cik[2][1][2]*Z2[2][2])+((Cik[2][1][0]*Z2[2][0])+(Cik[2][1][1]*
      Z2[2][1])))+((rikt[2][1][2]*Z1[2][2])+((rikt[2][1][0]*Z1[2][0])+(
      rikt[2][1][1]*Z1[2][1]))));
    Z2[1][2] = (((Cik[2][2][2]*Z2[2][2])+((Cik[2][2][0]*Z2[2][0])+(Cik[2][2][1]*
      Z2[2][1])))+((rikt[2][2][2]*Z1[2][2])+((rikt[2][2][0]*Z1[2][0])+(
      rikt[2][2][1]*Z1[2][1]))));
    eps[1] = (fs0[1]-((pin[1][2]*Z2[1][2])+((pin[1][0]*Z2[1][0])+(pin[1][1]*
      Z2[1][1]))));
    Z1[1][0] = (Z1[1][0]+(eps[1]*G1[1][0]));
    Z1[1][1] = (Z1[1][1]+(eps[1]*G1[1][1]));
    Z1[1][2] = (Z1[1][2]+(eps[1]*G1[1][2]));
    Z2[1][0] = (Z2[1][0]+(eps[1]*G2[1][0]));
    Z2[1][1] = (Z2[1][1]+(eps[1]*G2[1][1]));
    Z2[1][2] = (Z2[1][2]+(eps[1]*G2[1][2]));
    Z1[0][0] = ((Cik[1][0][2]*Z1[1][2])+((Cik[1][0][0]*Z1[1][0])+(Cik[1][0][1]*
      Z1[1][1])));
    Z1[0][1] = ((Cik[1][1][2]*Z1[1][2])+((Cik[1][1][0]*Z1[1][0])+(Cik[1][1][1]*
      Z1[1][1])));
    Z1[0][2] = ((Cik[1][2][2]*Z1[1][2])+((Cik[1][2][0]*Z1[1][0])+(Cik[1][2][1]*
      Z1[1][1])));
    Z2[0][0] = (((Cik[1][0][2]*Z2[1][2])+((Cik[1][0][0]*Z2[1][0])+(Cik[1][0][1]*
      Z2[1][1])))+((rikt[1][0][2]*Z1[1][2])+((rikt[1][0][0]*Z1[1][0])+(
      rikt[1][0][1]*Z1[1][1]))));
    Z2[0][1] = (((Cik[1][1][2]*Z2[1][2])+((Cik[1][1][0]*Z2[1][0])+(Cik[1][1][1]*
      Z2[1][1])))+((rikt[1][1][2]*Z1[1][2])+((rikt[1][1][0]*Z1[1][0])+(
      rikt[1][1][1]*Z1[1][1]))));
    Z2[0][2] = (((Cik[1][2][2]*Z2[1][2])+((Cik[1][2][0]*Z2[1][0])+(Cik[1][2][1]*
      Z2[1][1])))+((rikt[1][2][2]*Z1[1][2])+((rikt[1][2][0]*Z1[1][0])+(
      rikt[1][2][1]*Z1[1][1]))));
    eps[0] = (fs0[0]-((pin[0][2]*Z2[0][2])+((pin[0][0]*Z2[0][0])+(pin[0][1]*
      Z2[0][1]))));
    udot[0] = (DD[0]*eps[0]);
    A2[0][0] = (pin[0][0]*udot[0]);
    A2[0][1] = (pin[0][1]*udot[0]);
    A2[0][2] = (pin[0][2]*udot[0]);
    K1[1][0] = ((A2[0][2]*rikt[1][2][0])+((A2[0][0]*rikt[1][0][0])+(A2[0][1]*
      rikt[1][1][0])));
    K1[1][1] = ((A2[0][2]*rikt[1][2][1])+((A2[0][0]*rikt[1][0][1])+(A2[0][1]*
      rikt[1][1][1])));
    K1[1][2] = ((A2[0][2]*rikt[1][2][2])+((A2[0][0]*rikt[1][0][2])+(A2[0][1]*
      rikt[1][1][2])));
    K2[1][0] = ((A2[0][2]*Cik[1][2][0])+((A2[0][0]*Cik[1][0][0])+(A2[0][1]*
      Cik[1][1][0])));
    K2[1][1] = ((A2[0][2]*Cik[1][2][1])+((A2[0][0]*Cik[1][0][1])+(A2[0][1]*
      Cik[1][1][1])));
    K2[1][2] = ((A2[0][2]*Cik[1][2][2])+((A2[0][0]*Cik[1][0][2])+(A2[0][1]*
      Cik[1][1][2])));
    udot[1] = ((DD[1]*eps[1])-(((G1[1][2]*K1[1][2])+((G1[1][0]*K1[1][0])+(
      G1[1][1]*K1[1][1])))+((G2[1][2]*K2[1][2])+((G2[1][0]*K2[1][0])+(G2[1][1]*
      K2[1][1])))));
    A2[1][0] = (K2[1][0]+(pin[1][0]*udot[1]));
    A2[1][1] = (K2[1][1]+(pin[1][1]*udot[1]));
    A2[1][2] = (K2[1][2]+(pin[1][2]*udot[1]));
    K1[2][0] = (((A2[1][2]*rikt[2][2][0])+((A2[1][0]*rikt[2][0][0])+(A2[1][1]*
      rikt[2][1][0])))+((Cik[2][2][0]*K1[1][2])+((Cik[2][0][0]*K1[1][0])+(
      Cik[2][1][0]*K1[1][1]))));
    K1[2][1] = (((A2[1][2]*rikt[2][2][1])+((A2[1][0]*rikt[2][0][1])+(A2[1][1]*
      rikt[2][1][1])))+((Cik[2][2][1]*K1[1][2])+((Cik[2][0][1]*K1[1][0])+(
      Cik[2][1][1]*K1[1][1]))));
    K1[2][2] = (((A2[1][2]*rikt[2][2][2])+((A2[1][0]*rikt[2][0][2])+(A2[1][1]*
      rikt[2][1][2])))+((Cik[2][2][2]*K1[1][2])+((Cik[2][0][2]*K1[1][0])+(
      Cik[2][1][2]*K1[1][1]))));
    K2[2][0] = ((A2[1][2]*Cik[2][2][0])+((A2[1][0]*Cik[2][0][0])+(A2[1][1]*
      Cik[2][1][0])));
    K2[2][1] = ((A2[1][2]*Cik[2][2][1])+((A2[1][0]*Cik[2][0][1])+(A2[1][1]*
      Cik[2][1][1])));
    K2[2][2] = ((A2[1][2]*Cik[2][2][2])+((A2[1][0]*Cik[2][0][2])+(A2[1][1]*
      Cik[2][1][2])));
    udot[2] = ((DD[2]*eps[2])-(((G1[2][2]*K1[2][2])+((G1[2][0]*K1[2][0])+(
      G1[2][1]*K1[2][1])))+((G2[2][2]*K2[2][2])+((G2[2][0]*K2[2][0])+(G2[2][1]*
      K2[2][1])))));
    A2[2][0] = (K2[2][0]+(pin[2][0]*udot[2]));
    A2[2][1] = (K2[2][1]+(pin[2][1]*udot[2]));
    A2[2][2] = (K2[2][2]+(pin[2][2]*udot[2]));
    K1[3][0] = (((A2[2][2]*rikt[3][2][0])+((A2[2][0]*rikt[3][0][0])+(A2[2][1]*
      rikt[3][1][0])))+((Cik[3][2][0]*K1[2][2])+((Cik[3][0][0]*K1[2][0])+(
      Cik[3][1][0]*K1[2][1]))));
    K1[3][1] = (((A2[2][2]*rikt[3][2][1])+((A2[2][0]*rikt[3][0][1])+(A2[2][1]*
      rikt[3][1][1])))+((Cik[3][2][1]*K1[2][2])+((Cik[3][0][1]*K1[2][0])+(
      Cik[3][1][1]*K1[2][1]))));
    K1[3][2] = (((A2[2][2]*rikt[3][2][2])+((A2[2][0]*rikt[3][0][2])+(A2[2][1]*
      rikt[3][1][2])))+((Cik[3][2][2]*K1[2][2])+((Cik[3][0][2]*K1[2][0])+(
      Cik[3][1][2]*K1[2][1]))));
    K2[3][0] = ((A2[2][2]*Cik[3][2][0])+((A2[2][0]*Cik[3][0][0])+(A2[2][1]*
      Cik[3][1][0])));
    K2[3][1] = ((A2[2][2]*Cik[3][2][1])+((A2[2][0]*Cik[3][0][1])+(A2[2][1]*
      Cik[3][1][1])));
    K2[3][2] = ((A2[2][2]*Cik[3][2][2])+((A2[2][0]*Cik[3][0][2])+(A2[2][1]*
      Cik[3][1][2])));
    udot[3] = ((DD[3]*eps[3])-(((G1[3][2]*K1[3][2])+((G1[3][0]*K1[3][0])+(
      G1[3][1]*K1[3][1])))+((G2[3][2]*K2[3][2])+((G2[3][0]*K2[3][0])+(G2[3][1]*
      K2[3][1])))));
    A2[3][0] = (K2[3][0]+(pin[3][0]*udot[3]));
    A2[3][1] = (K2[3][1]+(pin[3][1]*udot[3]));
    A2[3][2] = (K2[3][2]+(pin[3][2]*udot[3]));
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
    udot[4] = ((DD[4]*eps[4])-(((G1[4][2]*K1[4][2])+((G1[4][0]*K1[4][0])+(
      G1[4][1]*K1[4][1])))+((G2[4][2]*K2[4][2])+((G2[4][0]*K2[4][0])+(G2[4][1]*
      K2[4][1])))));
    A2[4][0] = (K2[4][0]+(pin[4][0]*udot[4]));
    A2[4][1] = (K2[4][1]+(pin[4][1]*udot[4]));
    A2[4][2] = (K2[4][2]+(pin[4][2]*udot[4]));
    for (i = 0; i <= 4; i++) {
        oudot0[i] = udot[i];
    }
/*
 Used 0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain  225 adds/subtracts/negates
                    287 multiplies
                      0 divides
                    102 assignments
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
    double imult[5],
    double oudotm[5])
{
/*
Compute udots due only to multipliers
*/
    int i;
    double eps[5],Z1[5][3],Z2[5][3],A1[5][3],A2[5][3],K1[5][3],K2[5][3];

    sdlhs(routine);
    sdmfrc(imult);
    eps[4] = mtau[4];
    Z1[4][0] = (eps[4]*G1[4][0]);
    Z1[4][1] = (eps[4]*G1[4][1]);
    Z1[4][2] = (eps[4]*G1[4][2]);
    Z2[4][0] = (eps[4]*G2[4][0]);
    Z2[4][1] = (eps[4]*G2[4][1]);
    Z2[4][2] = (eps[4]*G2[4][2]);
    Z1[3][0] = ((Cik[4][0][2]*Z1[4][2])+((Cik[4][0][0]*Z1[4][0])+(Cik[4][0][1]*
      Z1[4][1])));
    Z1[3][1] = ((Cik[4][1][2]*Z1[4][2])+((Cik[4][1][0]*Z1[4][0])+(Cik[4][1][1]*
      Z1[4][1])));
    Z1[3][2] = ((Cik[4][2][2]*Z1[4][2])+((Cik[4][2][0]*Z1[4][0])+(Cik[4][2][1]*
      Z1[4][1])));
    Z2[3][0] = (((Cik[4][0][2]*Z2[4][2])+((Cik[4][0][0]*Z2[4][0])+(Cik[4][0][1]*
      Z2[4][1])))+((rikt[4][0][2]*Z1[4][2])+((rikt[4][0][0]*Z1[4][0])+(
      rikt[4][0][1]*Z1[4][1]))));
    Z2[3][1] = (((Cik[4][1][2]*Z2[4][2])+((Cik[4][1][0]*Z2[4][0])+(Cik[4][1][1]*
      Z2[4][1])))+((rikt[4][1][2]*Z1[4][2])+((rikt[4][1][0]*Z1[4][0])+(
      rikt[4][1][1]*Z1[4][1]))));
    Z2[3][2] = (((Cik[4][2][2]*Z2[4][2])+((Cik[4][2][0]*Z2[4][0])+(Cik[4][2][1]*
      Z2[4][1])))+((rikt[4][2][2]*Z1[4][2])+((rikt[4][2][0]*Z1[4][0])+(
      rikt[4][2][1]*Z1[4][1]))));
    eps[3] = (mtau[3]-((pin[3][2]*Z2[3][2])+((pin[3][0]*Z2[3][0])+(pin[3][1]*
      Z2[3][1]))));
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
    eps[2] = (mtau[2]-((pin[2][2]*Z2[2][2])+((pin[2][0]*Z2[2][0])+(pin[2][1]*
      Z2[2][1]))));
    Z1[2][0] = (Z1[2][0]+(eps[2]*G1[2][0]));
    Z1[2][1] = (Z1[2][1]+(eps[2]*G1[2][1]));
    Z1[2][2] = (Z1[2][2]+(eps[2]*G1[2][2]));
    Z2[2][0] = (Z2[2][0]+(eps[2]*G2[2][0]));
    Z2[2][1] = (Z2[2][1]+(eps[2]*G2[2][1]));
    Z2[2][2] = (Z2[2][2]+(eps[2]*G2[2][2]));
    Z1[1][0] = ((Cik[2][0][2]*Z1[2][2])+((Cik[2][0][0]*Z1[2][0])+(Cik[2][0][1]*
      Z1[2][1])));
    Z1[1][1] = ((Cik[2][1][2]*Z1[2][2])+((Cik[2][1][0]*Z1[2][0])+(Cik[2][1][1]*
      Z1[2][1])));
    Z1[1][2] = ((Cik[2][2][2]*Z1[2][2])+((Cik[2][2][0]*Z1[2][0])+(Cik[2][2][1]*
      Z1[2][1])));
    Z2[1][0] = (((Cik[2][0][2]*Z2[2][2])+((Cik[2][0][0]*Z2[2][0])+(Cik[2][0][1]*
      Z2[2][1])))+((rikt[2][0][2]*Z1[2][2])+((rikt[2][0][0]*Z1[2][0])+(
      rikt[2][0][1]*Z1[2][1]))));
    Z2[1][1] = (((Cik[2][1][2]*Z2[2][2])+((Cik[2][1][0]*Z2[2][0])+(Cik[2][1][1]*
      Z2[2][1])))+((rikt[2][1][2]*Z1[2][2])+((rikt[2][1][0]*Z1[2][0])+(
      rikt[2][1][1]*Z1[2][1]))));
    Z2[1][2] = (((Cik[2][2][2]*Z2[2][2])+((Cik[2][2][0]*Z2[2][0])+(Cik[2][2][1]*
      Z2[2][1])))+((rikt[2][2][2]*Z1[2][2])+((rikt[2][2][0]*Z1[2][0])+(
      rikt[2][2][1]*Z1[2][1]))));
    eps[1] = (mtau[1]-((pin[1][2]*Z2[1][2])+((pin[1][0]*Z2[1][0])+(pin[1][1]*
      Z2[1][1]))));
    Z1[1][0] = (Z1[1][0]+(eps[1]*G1[1][0]));
    Z1[1][1] = (Z1[1][1]+(eps[1]*G1[1][1]));
    Z1[1][2] = (Z1[1][2]+(eps[1]*G1[1][2]));
    Z2[1][0] = (Z2[1][0]+(eps[1]*G2[1][0]));
    Z2[1][1] = (Z2[1][1]+(eps[1]*G2[1][1]));
    Z2[1][2] = (Z2[1][2]+(eps[1]*G2[1][2]));
    Z1[0][0] = ((Cik[1][0][2]*Z1[1][2])+((Cik[1][0][0]*Z1[1][0])+(Cik[1][0][1]*
      Z1[1][1])));
    Z1[0][1] = ((Cik[1][1][2]*Z1[1][2])+((Cik[1][1][0]*Z1[1][0])+(Cik[1][1][1]*
      Z1[1][1])));
    Z1[0][2] = ((Cik[1][2][2]*Z1[1][2])+((Cik[1][2][0]*Z1[1][0])+(Cik[1][2][1]*
      Z1[1][1])));
    Z2[0][0] = (((Cik[1][0][2]*Z2[1][2])+((Cik[1][0][0]*Z2[1][0])+(Cik[1][0][1]*
      Z2[1][1])))+((rikt[1][0][2]*Z1[1][2])+((rikt[1][0][0]*Z1[1][0])+(
      rikt[1][0][1]*Z1[1][1]))));
    Z2[0][1] = (((Cik[1][1][2]*Z2[1][2])+((Cik[1][1][0]*Z2[1][0])+(Cik[1][1][1]*
      Z2[1][1])))+((rikt[1][1][2]*Z1[1][2])+((rikt[1][1][0]*Z1[1][0])+(
      rikt[1][1][1]*Z1[1][1]))));
    Z2[0][2] = (((Cik[1][2][2]*Z2[1][2])+((Cik[1][2][0]*Z2[1][0])+(Cik[1][2][1]*
      Z2[1][1])))+((rikt[1][2][2]*Z1[1][2])+((rikt[1][2][0]*Z1[1][0])+(
      rikt[1][2][1]*Z1[1][1]))));
    eps[0] = (mtau[0]-((pin[0][2]*Z2[0][2])+((pin[0][0]*Z2[0][0])+(pin[0][1]*
      Z2[0][1]))));
    udot[0] = (DD[0]*eps[0]);
    A2[0][0] = (pin[0][0]*udot[0]);
    A2[0][1] = (pin[0][1]*udot[0]);
    A2[0][2] = (pin[0][2]*udot[0]);
    K1[1][0] = ((A2[0][2]*rikt[1][2][0])+((A2[0][0]*rikt[1][0][0])+(A2[0][1]*
      rikt[1][1][0])));
    K1[1][1] = ((A2[0][2]*rikt[1][2][1])+((A2[0][0]*rikt[1][0][1])+(A2[0][1]*
      rikt[1][1][1])));
    K1[1][2] = ((A2[0][2]*rikt[1][2][2])+((A2[0][0]*rikt[1][0][2])+(A2[0][1]*
      rikt[1][1][2])));
    K2[1][0] = ((A2[0][2]*Cik[1][2][0])+((A2[0][0]*Cik[1][0][0])+(A2[0][1]*
      Cik[1][1][0])));
    K2[1][1] = ((A2[0][2]*Cik[1][2][1])+((A2[0][0]*Cik[1][0][1])+(A2[0][1]*
      Cik[1][1][1])));
    K2[1][2] = ((A2[0][2]*Cik[1][2][2])+((A2[0][0]*Cik[1][0][2])+(A2[0][1]*
      Cik[1][1][2])));
    udot[1] = ((DD[1]*eps[1])-(((G1[1][2]*K1[1][2])+((G1[1][0]*K1[1][0])+(
      G1[1][1]*K1[1][1])))+((G2[1][2]*K2[1][2])+((G2[1][0]*K2[1][0])+(G2[1][1]*
      K2[1][1])))));
    A2[1][0] = (K2[1][0]+(pin[1][0]*udot[1]));
    A2[1][1] = (K2[1][1]+(pin[1][1]*udot[1]));
    A2[1][2] = (K2[1][2]+(pin[1][2]*udot[1]));
    K1[2][0] = (((A2[1][2]*rikt[2][2][0])+((A2[1][0]*rikt[2][0][0])+(A2[1][1]*
      rikt[2][1][0])))+((Cik[2][2][0]*K1[1][2])+((Cik[2][0][0]*K1[1][0])+(
      Cik[2][1][0]*K1[1][1]))));
    K1[2][1] = (((A2[1][2]*rikt[2][2][1])+((A2[1][0]*rikt[2][0][1])+(A2[1][1]*
      rikt[2][1][1])))+((Cik[2][2][1]*K1[1][2])+((Cik[2][0][1]*K1[1][0])+(
      Cik[2][1][1]*K1[1][1]))));
    K1[2][2] = (((A2[1][2]*rikt[2][2][2])+((A2[1][0]*rikt[2][0][2])+(A2[1][1]*
      rikt[2][1][2])))+((Cik[2][2][2]*K1[1][2])+((Cik[2][0][2]*K1[1][0])+(
      Cik[2][1][2]*K1[1][1]))));
    K2[2][0] = ((A2[1][2]*Cik[2][2][0])+((A2[1][0]*Cik[2][0][0])+(A2[1][1]*
      Cik[2][1][0])));
    K2[2][1] = ((A2[1][2]*Cik[2][2][1])+((A2[1][0]*Cik[2][0][1])+(A2[1][1]*
      Cik[2][1][1])));
    K2[2][2] = ((A2[1][2]*Cik[2][2][2])+((A2[1][0]*Cik[2][0][2])+(A2[1][1]*
      Cik[2][1][2])));
    udot[2] = ((DD[2]*eps[2])-(((G1[2][2]*K1[2][2])+((G1[2][0]*K1[2][0])+(
      G1[2][1]*K1[2][1])))+((G2[2][2]*K2[2][2])+((G2[2][0]*K2[2][0])+(G2[2][1]*
      K2[2][1])))));
    A2[2][0] = (K2[2][0]+(pin[2][0]*udot[2]));
    A2[2][1] = (K2[2][1]+(pin[2][1]*udot[2]));
    A2[2][2] = (K2[2][2]+(pin[2][2]*udot[2]));
    K1[3][0] = (((A2[2][2]*rikt[3][2][0])+((A2[2][0]*rikt[3][0][0])+(A2[2][1]*
      rikt[3][1][0])))+((Cik[3][2][0]*K1[2][2])+((Cik[3][0][0]*K1[2][0])+(
      Cik[3][1][0]*K1[2][1]))));
    K1[3][1] = (((A2[2][2]*rikt[3][2][1])+((A2[2][0]*rikt[3][0][1])+(A2[2][1]*
      rikt[3][1][1])))+((Cik[3][2][1]*K1[2][2])+((Cik[3][0][1]*K1[2][0])+(
      Cik[3][1][1]*K1[2][1]))));
    K1[3][2] = (((A2[2][2]*rikt[3][2][2])+((A2[2][0]*rikt[3][0][2])+(A2[2][1]*
      rikt[3][1][2])))+((Cik[3][2][2]*K1[2][2])+((Cik[3][0][2]*K1[2][0])+(
      Cik[3][1][2]*K1[2][1]))));
    K2[3][0] = ((A2[2][2]*Cik[3][2][0])+((A2[2][0]*Cik[3][0][0])+(A2[2][1]*
      Cik[3][1][0])));
    K2[3][1] = ((A2[2][2]*Cik[3][2][1])+((A2[2][0]*Cik[3][0][1])+(A2[2][1]*
      Cik[3][1][1])));
    K2[3][2] = ((A2[2][2]*Cik[3][2][2])+((A2[2][0]*Cik[3][0][2])+(A2[2][1]*
      Cik[3][1][2])));
    udot[3] = ((DD[3]*eps[3])-(((G1[3][2]*K1[3][2])+((G1[3][0]*K1[3][0])+(
      G1[3][1]*K1[3][1])))+((G2[3][2]*K2[3][2])+((G2[3][0]*K2[3][0])+(G2[3][1]*
      K2[3][1])))));
    A2[3][0] = (K2[3][0]+(pin[3][0]*udot[3]));
    A2[3][1] = (K2[3][1]+(pin[3][1]*udot[3]));
    A2[3][2] = (K2[3][2]+(pin[3][2]*udot[3]));
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
    udot[4] = ((DD[4]*eps[4])-(((G1[4][2]*K1[4][2])+((G1[4][0]*K1[4][0])+(
      G1[4][1]*K1[4][1])))+((G2[4][2]*K2[4][2])+((G2[4][0]*K2[4][0])+(G2[4][1]*
      K2[4][1])))));
    A2[4][0] = (K2[4][0]+(pin[4][0]*udot[4]));
    A2[4][1] = (K2[4][1]+(pin[4][1]*udot[4]));
    A2[4][2] = (K2[4][2]+(pin[4][2]*udot[4]));
    for (i = 0; i <= 4; i++) {
        oudotm[i] = udot[i];
    }
/*
 Used 0.02 seconds CPU time,
 0 additional bytes of memory.
 Equations contain  225 adds/subtracts/negates
                    287 multiplies
                      0 divides
                    102 assignments
*/
}

void sdudotm(double imult[5],
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
5 of the degrees of freedom follow(s) prescribed motion.
There are 5 constraints.
*/
    double workr[5],bb[5],b0[5],v0[5],p0[5];
    int iwork[5];
    int i,j;
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
    wsiz = 5;
/*
Compute unconstrained equations
*/
    sdxudot0(17,udot0);
    sdrhs();
    sdaerr(b0);
    if (stabvel  !=  0.) {
        sdverr(v0);
    }
    if (stabpos  !=  0.) {
        sdperr(p0);
    }
/*
Stabilize constraints using Baumgarte's method
*/
    for (i = 0; i <= 4; i++) {
        bb[i] = -b0[i];
    }
    if (stabvel  !=  0.) {
        for (i = 0; i <= 4; i++) {
            bb[i] = bb[i]-stabvel*v0[i];
        }
    }
    if (stabpos  !=  0.) {
        for (i = 0; i <= 4; i++) {
            bb[i] = bb[i]-stabpos*p0[i];
        }
    }
/*
Compute and decompose constraint matrix WW
*/
    sddoww(17);
/*
Numerically solve for constraint multipliers
*/
    sdqrbslv(5,5,5,5,wmap,wmap,1e-13,workr,iwork,ww,qraux,jpvt,bb,mult,&wrank);
    for (i = 0; i <= 4; i++) {
        multmap[i] = 0;
    }
    for (i = 0; i < wrank; i++) {
        multmap[jpvt[i]] = 1;
    }
    j = 0;
    for (i = 0; i <= 4; i++) {
        if (multmap[i] != 0) {
            multmap[j] = wmap[i];
            j = j+1;
        }
    }
/*
Compute final udots
*/
    sdxudotm(17,mult,udot1);
    for (i = 0; i <= 4; i++) {
        udot[i] = udot0[i]+udot1[i];
    }
    sdrhs();
    for (i = 0; i <= 4; i++) {
        oqdot[i] = qdot[i];
    }
    for (i = 0; i <= 4; i++) {
        oudot[i] = udot[i];
    }
/*
 Used 0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain   20 adds/subtracts/negates
                     10 multiplies
                      0 divides
                     30 assignments
*/
}
/*
Compute residuals for use with DAE integrator
*/

void sdresid(double eqdot[5],
    double eudot[5],
    double emults[5],
    double resid[15])
{
    int i;
    double uderrs[5],p0[5];

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
    sdverr(&resid[10]);
    if (stabpos  !=  0.) {
        sdperr(p0);
        for (i = 0; i < 5; i++) {
            resid[10+i] = resid[10+i]+stabpos*p0[i];
        }
    }
    for (i = 0; i < 5; i++) {
        udot[i] = eudot[i];
    }
    for (i = 0; i < 5; i++) {
        mult[i] = emults[i];
    }
    sdrhs();
/*
 Used 0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain   10 adds/subtracts/negates
                      5 multiplies
                      0 divides
                     25 assignments
*/
}

void sdmult(double omults[5],
    int *owrank,
    int omultmap[5])
{
    int i;

    if (roustate != 3) {
        sdseterr(34,24);
        return;
    }
    for (i = 0; i < 5; i++) {
        omults[i] = mult[i];
        if (i <= wrank-1) {
            omultmap[i] = multmap[i];
        } else {
            omultmap[i] = -1;
        }
    }
    *owrank = wrank;
}

void sdreac(double force[12][3],
    double torque[12][3])
{
/*
Generated 24-May-2007 16:22:11 by SD/FAST, Order(N) formulation
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
    fc[4][0] = ((mk[11]*(AnkAtk[4][0]-gk[4][0]))-ufk[11][0]);
    fc[4][1] = ((mk[11]*(AnkAtk[4][1]-gk[4][1]))-ufk[11][1]);
    fc[4][2] = ((mk[11]*(AnkAtk[4][2]-gk[4][2]))-ufk[11][2]);
    tc[4][0] = ((WkIkWk[4][0]+((ik[11][0][2]*onk[4][2])+((ik[11][0][0]*onk[4][0]
      )+(ik[11][0][1]*onk[4][1]))))-(utk[11][0]+((fc[4][2]*rk[11][1])-(fc[4][1]*
      rk[11][2]))));
    tc[4][1] = ((WkIkWk[4][1]+((ik[11][1][2]*onk[4][2])+((ik[11][1][0]*onk[4][0]
      )+(ik[11][1][1]*onk[4][1]))))-(utk[11][1]+((fc[4][0]*rk[11][2])-(fc[4][2]*
      rk[11][0]))));
    tc[4][2] = ((WkIkWk[4][2]+((ik[11][2][2]*onk[4][2])+((ik[11][2][0]*onk[4][0]
      )+(ik[11][2][1]*onk[4][1]))))-(utk[11][2]+((fc[4][1]*rk[11][0])-(fc[4][0]*
      rk[11][1]))));
    fccikt[4][0] = ((Cik[4][0][2]*fc[4][2])+((Cik[4][0][0]*fc[4][0])+(
      Cik[4][0][1]*fc[4][1])));
    fccikt[4][1] = ((Cik[4][1][2]*fc[4][2])+((Cik[4][1][0]*fc[4][0])+(
      Cik[4][1][1]*fc[4][1])));
    fccikt[4][2] = ((Cik[4][2][2]*fc[4][2])+((Cik[4][2][0]*fc[4][0])+(
      Cik[4][2][1]*fc[4][1])));
    ffk[3][0] = (ufk[10][0]-fccikt[4][0]);
    ffk[3][1] = (ufk[10][1]-fccikt[4][1]);
    ffk[3][2] = (ufk[10][2]-fccikt[4][2]);
    ttk[3][0] = (utk[10][0]-(((Cik[4][0][2]*tc[4][2])+((Cik[4][0][0]*tc[4][0])+(
      Cik[4][0][1]*tc[4][1])))+((fccikt[4][2]*ri[11][1])-(fccikt[4][1]*ri[11][2]
      ))));
    ttk[3][1] = (utk[10][1]-(((Cik[4][1][2]*tc[4][2])+((Cik[4][1][0]*tc[4][0])+(
      Cik[4][1][1]*tc[4][1])))+((fccikt[4][0]*ri[11][2])-(fccikt[4][2]*ri[11][0]
      ))));
    ttk[3][2] = (utk[10][2]-(((Cik[4][2][2]*tc[4][2])+((Cik[4][2][0]*tc[4][0])+(
      Cik[4][2][1]*tc[4][1])))+((fccikt[4][1]*ri[11][0])-(fccikt[4][0]*ri[11][1]
      ))));
    fc[3][0] = ((mk[10]*(AnkAtk[3][0]-gk[3][0]))-ffk[3][0]);
    fc[3][1] = ((mk[10]*(AnkAtk[3][1]-gk[3][1]))-ffk[3][1]);
    fc[3][2] = ((mk[10]*(AnkAtk[3][2]-gk[3][2]))-ffk[3][2]);
    tc[3][0] = ((WkIkWk[3][0]+((ik[10][0][2]*onk[3][2])+((ik[10][0][0]*onk[3][0]
      )+(ik[10][0][1]*onk[3][1]))))-(ttk[3][0]+((fc[3][2]*rk[10][1])-(fc[3][1]*
      rk[10][2]))));
    tc[3][1] = ((WkIkWk[3][1]+((ik[10][1][2]*onk[3][2])+((ik[10][1][0]*onk[3][0]
      )+(ik[10][1][1]*onk[3][1]))))-(ttk[3][1]+((fc[3][0]*rk[10][2])-(fc[3][2]*
      rk[10][0]))));
    tc[3][2] = ((WkIkWk[3][2]+((ik[10][2][2]*onk[3][2])+((ik[10][2][0]*onk[3][0]
      )+(ik[10][2][1]*onk[3][1]))))-(ttk[3][2]+((fc[3][1]*rk[10][0])-(fc[3][0]*
      rk[10][1]))));
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
      Cik[3][0][1]*tc[3][1])))+((fccikt[3][2]*ri[10][1])-(fccikt[3][1]*ri[10][2]
      ))));
    ttk[2][1] = (utk[9][1]-(((Cik[3][1][2]*tc[3][2])+((Cik[3][1][0]*tc[3][0])+(
      Cik[3][1][1]*tc[3][1])))+((fccikt[3][0]*ri[10][2])-(fccikt[3][2]*ri[10][0]
      ))));
    ttk[2][2] = (utk[9][2]-(((Cik[3][2][2]*tc[3][2])+((Cik[3][2][0]*tc[3][0])+(
      Cik[3][2][1]*tc[3][1])))+((fccikt[3][1]*ri[10][0])-(fccikt[3][0]*ri[10][1]
      ))));
    fc[2][0] = ((mk[9]*(AnkAtk[2][0]-gk[2][0]))-ffk[2][0]);
    fc[2][1] = ((mk[9]*(AnkAtk[2][1]-gk[2][1]))-ffk[2][1]);
    fc[2][2] = ((mk[9]*(AnkAtk[2][2]-gk[2][2]))-ffk[2][2]);
    tc[2][0] = ((WkIkWk[2][0]+((ik[9][0][2]*onk[2][2])+((ik[9][0][0]*onk[2][0])+
      (ik[9][0][1]*onk[2][1]))))-(ttk[2][0]+((fc[2][2]*rk[9][1])-(fc[2][1]*
      rk[9][2]))));
    tc[2][1] = ((WkIkWk[2][1]+((ik[9][1][2]*onk[2][2])+((ik[9][1][0]*onk[2][0])+
      (ik[9][1][1]*onk[2][1]))))-(ttk[2][1]+((fc[2][0]*rk[9][2])-(fc[2][2]*
      rk[9][0]))));
    tc[2][2] = ((WkIkWk[2][2]+((ik[9][2][2]*onk[2][2])+((ik[9][2][0]*onk[2][0])+
      (ik[9][2][1]*onk[2][1]))))-(ttk[2][2]+((fc[2][1]*rk[9][0])-(fc[2][0]*
      rk[9][1]))));
    fccikt[2][0] = ((Cik[2][0][2]*fc[2][2])+((Cik[2][0][0]*fc[2][0])+(
      Cik[2][0][1]*fc[2][1])));
    fccikt[2][1] = ((Cik[2][1][2]*fc[2][2])+((Cik[2][1][0]*fc[2][0])+(
      Cik[2][1][1]*fc[2][1])));
    fccikt[2][2] = ((Cik[2][2][2]*fc[2][2])+((Cik[2][2][0]*fc[2][0])+(
      Cik[2][2][1]*fc[2][1])));
    ffk[1][0] = (ufk[8][0]-fccikt[2][0]);
    ffk[1][1] = (ufk[8][1]-fccikt[2][1]);
    ffk[1][2] = (ufk[8][2]-fccikt[2][2]);
    ttk[1][0] = (utk[8][0]-(((Cik[2][0][2]*tc[2][2])+((Cik[2][0][0]*tc[2][0])+(
      Cik[2][0][1]*tc[2][1])))+((fccikt[2][2]*ri[9][1])-(fccikt[2][1]*ri[9][2]))
      ));
    ttk[1][1] = (utk[8][1]-(((Cik[2][1][2]*tc[2][2])+((Cik[2][1][0]*tc[2][0])+(
      Cik[2][1][1]*tc[2][1])))+((fccikt[2][0]*ri[9][2])-(fccikt[2][2]*ri[9][0]))
      ));
    ttk[1][2] = (utk[8][2]-(((Cik[2][2][2]*tc[2][2])+((Cik[2][2][0]*tc[2][0])+(
      Cik[2][2][1]*tc[2][1])))+((fccikt[2][1]*ri[9][0])-(fccikt[2][0]*ri[9][1]))
      ));
    fc[1][0] = ((mk[8]*(AnkAtk[1][0]-gk[1][0]))-ffk[1][0]);
    fc[1][1] = ((mk[8]*(AnkAtk[1][1]-gk[1][1]))-ffk[1][1]);
    fc[1][2] = ((mk[8]*(AnkAtk[1][2]-gk[1][2]))-ffk[1][2]);
    tc[1][0] = ((WkIkWk[1][0]+((ik[8][0][2]*onk[1][2])+((ik[8][0][0]*onk[1][0])+
      (ik[8][0][1]*onk[1][1]))))-(ttk[1][0]+((fc[1][2]*rk[8][1])-(fc[1][1]*
      rk[8][2]))));
    tc[1][1] = ((WkIkWk[1][1]+((ik[8][1][2]*onk[1][2])+((ik[8][1][0]*onk[1][0])+
      (ik[8][1][1]*onk[1][1]))))-(ttk[1][1]+((fc[1][0]*rk[8][2])-(fc[1][2]*
      rk[8][0]))));
    tc[1][2] = ((WkIkWk[1][2]+((ik[8][2][2]*onk[1][2])+((ik[8][2][0]*onk[1][0])+
      (ik[8][2][1]*onk[1][1]))))-(ttk[1][2]+((fc[1][1]*rk[8][0])-(fc[1][0]*
      rk[8][1]))));
    fccikt[1][0] = ((Cik[1][0][2]*fc[1][2])+((Cik[1][0][0]*fc[1][0])+(
      Cik[1][0][1]*fc[1][1])));
    fccikt[1][1] = ((Cik[1][1][2]*fc[1][2])+((Cik[1][1][0]*fc[1][0])+(
      Cik[1][1][1]*fc[1][1])));
    fccikt[1][2] = ((Cik[1][2][2]*fc[1][2])+((Cik[1][2][0]*fc[1][0])+(
      Cik[1][2][1]*fc[1][1])));
    ffk[0][0] = (ufk[7][0]-fccikt[1][0]);
    ffk[0][1] = (ufk[7][1]-fccikt[1][1]);
    ffk[0][2] = (ufk[7][2]-fccikt[1][2]);
    ttk[0][0] = (utk[7][0]-(((Cik[1][0][2]*tc[1][2])+((Cik[1][0][0]*tc[1][0])+(
      Cik[1][0][1]*tc[1][1])))+((fccikt[1][2]*ri[8][1])-(fccikt[1][1]*ri[8][2]))
      ));
    ttk[0][1] = (utk[7][1]-(((Cik[1][1][2]*tc[1][2])+((Cik[1][1][0]*tc[1][0])+(
      Cik[1][1][1]*tc[1][1])))+((fccikt[1][0]*ri[8][2])-(fccikt[1][2]*ri[8][0]))
      ));
    ttk[0][2] = (utk[7][2]-(((Cik[1][2][2]*tc[1][2])+((Cik[1][2][0]*tc[1][0])+(
      Cik[1][2][1]*tc[1][1])))+((fccikt[1][1]*ri[8][0])-(fccikt[1][0]*ri[8][1]))
      ));
    fc[0][0] = ((mk[7]*(AnkAtk[0][0]-gk[0][0]))-ffk[0][0]);
    fc[0][1] = ((mk[7]*(AnkAtk[0][1]-gk[0][1]))-ffk[0][1]);
    fc[0][2] = ((mk[7]*(AnkAtk[0][2]-gk[0][2]))-ffk[0][2]);
    tc[0][0] = ((WkIkWk[0][0]+((ik[7][0][2]*Onkb[0][2])+((ik[7][0][0]*Onkb[0][0]
      )+(ik[7][0][1]*Onkb[0][1]))))-(ttk[0][0]+((fc[0][2]*rk[7][1])-(fc[0][1]*
      rk[7][2]))));
    tc[0][1] = ((WkIkWk[0][1]+((ik[7][1][2]*Onkb[0][2])+((ik[7][1][0]*Onkb[0][0]
      )+(ik[7][1][1]*Onkb[0][1]))))-(ttk[0][1]+((fc[0][0]*rk[7][2])-(fc[0][2]*
      rk[7][0]))));
    tc[0][2] = ((WkIkWk[0][2]+((ik[7][2][2]*Onkb[0][2])+((ik[7][2][0]*Onkb[0][0]
      )+(ik[7][2][1]*Onkb[0][1]))))-(ttk[0][2]+((fc[0][1]*rk[7][0])-(fc[0][0]*
      rk[7][1]))));
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
    force[6][0] = -((ufk[6][0]+(grav[0]*mk[6]))-((Cik[0][0][2]*force[7][2])+((
      Cik[0][0][0]*force[7][0])+(Cik[0][0][1]*force[7][1]))));
    temp[0] = (utk[6][0]+(((ri[7][2]*((Cik[0][1][2]*force[7][2])+((Cik[0][1][0]*
      force[7][0])+(Cik[0][1][1]*force[7][1]))))-(ri[7][1]*((Cik[0][2][2]*
      force[7][2])+((Cik[0][2][0]*force[7][0])+(Cik[0][2][1]*force[7][1])))))-((
      Cik[0][0][2]*torque[7][2])+((Cik[0][0][0]*torque[7][0])+(Cik[0][0][1]*
      torque[7][1])))));
    torque[6][0] = (((rk[6][1]*((ufk[6][2]+(grav[2]*mk[6]))-((Cik[0][2][2]*
      force[7][2])+((Cik[0][2][0]*force[7][0])+(Cik[0][2][1]*force[7][1])))))-(
      rk[6][2]*((ufk[6][1]+(grav[1]*mk[6]))-((Cik[0][1][2]*force[7][2])+((
      Cik[0][1][0]*force[7][0])+(Cik[0][1][1]*force[7][1]))))))-temp[0]);
    force[6][1] = -((ufk[6][1]+(grav[1]*mk[6]))-((Cik[0][1][2]*force[7][2])+((
      Cik[0][1][0]*force[7][0])+(Cik[0][1][1]*force[7][1]))));
    temp[0] = (utk[6][1]+(((ri[7][0]*((Cik[0][2][2]*force[7][2])+((Cik[0][2][0]*
      force[7][0])+(Cik[0][2][1]*force[7][1]))))-(ri[7][2]*((Cik[0][0][2]*
      force[7][2])+((Cik[0][0][0]*force[7][0])+(Cik[0][0][1]*force[7][1])))))-((
      Cik[0][1][2]*torque[7][2])+((Cik[0][1][0]*torque[7][0])+(Cik[0][1][1]*
      torque[7][1])))));
    torque[6][1] = (((rk[6][2]*((ufk[6][0]+(grav[0]*mk[6]))-((Cik[0][0][2]*
      force[7][2])+((Cik[0][0][0]*force[7][0])+(Cik[0][0][1]*force[7][1])))))-(
      rk[6][0]*((ufk[6][2]+(grav[2]*mk[6]))-((Cik[0][2][2]*force[7][2])+((
      Cik[0][2][0]*force[7][0])+(Cik[0][2][1]*force[7][1]))))))-temp[0]);
    force[6][2] = -((ufk[6][2]+(grav[2]*mk[6]))-((Cik[0][2][2]*force[7][2])+((
      Cik[0][2][0]*force[7][0])+(Cik[0][2][1]*force[7][1]))));
    temp[0] = (utk[6][2]+(((ri[7][1]*((Cik[0][0][2]*force[7][2])+((Cik[0][0][0]*
      force[7][0])+(Cik[0][0][1]*force[7][1]))))-(ri[7][0]*((Cik[0][1][2]*
      force[7][2])+((Cik[0][1][0]*force[7][0])+(Cik[0][1][1]*force[7][1])))))-((
      Cik[0][2][2]*torque[7][2])+((Cik[0][2][0]*torque[7][0])+(Cik[0][2][1]*
      torque[7][1])))));
    torque[6][2] = (((rk[6][0]*((ufk[6][1]+(grav[1]*mk[6]))-((Cik[0][1][2]*
      force[7][2])+((Cik[0][1][0]*force[7][0])+(Cik[0][1][1]*force[7][1])))))-(
      rk[6][1]*((ufk[6][0]+(grav[0]*mk[6]))-((Cik[0][0][2]*force[7][2])+((
      Cik[0][0][0]*force[7][0])+(Cik[0][0][1]*force[7][1]))))))-temp[0]);
    force[5][0] = -((ufk[5][0]+(grav[0]*mk[5]))-force[6][0]);
    torque[5][0] = (((rk[5][1]*((ufk[5][2]+(grav[2]*mk[5]))-force[6][2]))-(
      rk[5][2]*((ufk[5][1]+(grav[1]*mk[5]))-force[6][1])))-(utk[5][0]+(((
      force[6][1]*ri[6][2])-(force[6][2]*ri[6][1]))-torque[6][0])));
    force[5][1] = -((ufk[5][1]+(grav[1]*mk[5]))-force[6][1]);
    torque[5][1] = (((rk[5][2]*((ufk[5][0]+(grav[0]*mk[5]))-force[6][0]))-(
      rk[5][0]*((ufk[5][2]+(grav[2]*mk[5]))-force[6][2])))-(utk[5][1]+(((
      force[6][2]*ri[6][0])-(force[6][0]*ri[6][2]))-torque[6][1])));
    force[5][2] = -((ufk[5][2]+(grav[2]*mk[5]))-force[6][2]);
    torque[5][2] = (((rk[5][0]*((ufk[5][1]+(grav[1]*mk[5]))-force[6][1]))-(
      rk[5][1]*((ufk[5][0]+(grav[0]*mk[5]))-force[6][0])))-(utk[5][2]+(((
      force[6][0]*ri[6][1])-(force[6][1]*ri[6][0]))-torque[6][2])));
    force[4][0] = -((ufk[4][0]+(grav[0]*mk[4]))-force[5][0]);
    torque[4][0] = (((rk[4][1]*((ufk[4][2]+(grav[2]*mk[4]))-force[5][2]))-(
      rk[4][2]*((ufk[4][1]+(grav[1]*mk[4]))-force[5][1])))-(utk[4][0]+(((
      force[5][1]*ri[5][2])-(force[5][2]*ri[5][1]))-torque[5][0])));
    force[4][1] = -((ufk[4][1]+(grav[1]*mk[4]))-force[5][1]);
    torque[4][1] = (((rk[4][2]*((ufk[4][0]+(grav[0]*mk[4]))-force[5][0]))-(
      rk[4][0]*((ufk[4][2]+(grav[2]*mk[4]))-force[5][2])))-(utk[4][1]+(((
      force[5][2]*ri[5][0])-(force[5][0]*ri[5][2]))-torque[5][1])));
    force[4][2] = -((ufk[4][2]+(grav[2]*mk[4]))-force[5][2]);
    torque[4][2] = (((rk[4][0]*((ufk[4][1]+(grav[1]*mk[4]))-force[5][1]))-(
      rk[4][1]*((ufk[4][0]+(grav[0]*mk[4]))-force[5][0])))-(utk[4][2]+(((
      force[5][0]*ri[5][1])-(force[5][1]*ri[5][0]))-torque[5][2])));
    force[3][0] = -((ufk[3][0]+(grav[0]*mk[3]))-force[4][0]);
    torque[3][0] = (((rk[3][1]*((ufk[3][2]+(grav[2]*mk[3]))-force[4][2]))-(
      rk[3][2]*((ufk[3][1]+(grav[1]*mk[3]))-force[4][1])))-(utk[3][0]+(((
      force[4][1]*ri[4][2])-(force[4][2]*ri[4][1]))-torque[4][0])));
    force[3][1] = -((ufk[3][1]+(grav[1]*mk[3]))-force[4][1]);
    torque[3][1] = (((rk[3][2]*((ufk[3][0]+(grav[0]*mk[3]))-force[4][0]))-(
      rk[3][0]*((ufk[3][2]+(grav[2]*mk[3]))-force[4][2])))-(utk[3][1]+(((
      force[4][2]*ri[4][0])-(force[4][0]*ri[4][2]))-torque[4][1])));
    force[3][2] = -((ufk[3][2]+(grav[2]*mk[3]))-force[4][2]);
    torque[3][2] = (((rk[3][0]*((ufk[3][1]+(grav[1]*mk[3]))-force[4][1]))-(
      rk[3][1]*((ufk[3][0]+(grav[0]*mk[3]))-force[4][0])))-(utk[3][2]+(((
      force[4][0]*ri[4][1])-(force[4][1]*ri[4][0]))-torque[4][2])));
    force[2][0] = -((ufk[2][0]+(grav[0]*mk[2]))-force[3][0]);
    torque[2][0] = (((rk[2][1]*((ufk[2][2]+(grav[2]*mk[2]))-force[3][2]))-(
      rk[2][2]*((ufk[2][1]+(grav[1]*mk[2]))-force[3][1])))-(utk[2][0]+(((
      force[3][1]*ri[3][2])-(force[3][2]*ri[3][1]))-torque[3][0])));
    force[2][1] = -((ufk[2][1]+(grav[1]*mk[2]))-force[3][1]);
    torque[2][1] = (((rk[2][2]*((ufk[2][0]+(grav[0]*mk[2]))-force[3][0]))-(
      rk[2][0]*((ufk[2][2]+(grav[2]*mk[2]))-force[3][2])))-(utk[2][1]+(((
      force[3][2]*ri[3][0])-(force[3][0]*ri[3][2]))-torque[3][1])));
    force[2][2] = -((ufk[2][2]+(grav[2]*mk[2]))-force[3][2]);
    torque[2][2] = (((rk[2][0]*((ufk[2][1]+(grav[1]*mk[2]))-force[3][1]))-(
      rk[2][1]*((ufk[2][0]+(grav[0]*mk[2]))-force[3][0])))-(utk[2][2]+(((
      force[3][0]*ri[3][1])-(force[3][1]*ri[3][0]))-torque[3][2])));
    force[1][0] = -((ufk[1][0]+(grav[0]*mk[1]))-force[2][0]);
    torque[1][0] = (((rk[1][1]*((ufk[1][2]+(grav[2]*mk[1]))-force[2][2]))-(
      rk[1][2]*((ufk[1][1]+(grav[1]*mk[1]))-force[2][1])))-(utk[1][0]+(((
      force[2][1]*ri[2][2])-(force[2][2]*ri[2][1]))-torque[2][0])));
    force[1][1] = -((ufk[1][1]+(grav[1]*mk[1]))-force[2][1]);
    torque[1][1] = (((rk[1][2]*((ufk[1][0]+(grav[0]*mk[1]))-force[2][0]))-(
      rk[1][0]*((ufk[1][2]+(grav[2]*mk[1]))-force[2][2])))-(utk[1][1]+(((
      force[2][2]*ri[2][0])-(force[2][0]*ri[2][2]))-torque[2][1])));
    force[1][2] = -((ufk[1][2]+(grav[2]*mk[1]))-force[2][2]);
    torque[1][2] = (((rk[1][0]*((ufk[1][1]+(grav[1]*mk[1]))-force[2][1]))-(
      rk[1][1]*((ufk[1][0]+(grav[0]*mk[1]))-force[2][0])))-(utk[1][2]+(((
      force[2][0]*ri[2][1])-(force[2][1]*ri[2][0]))-torque[2][2])));
    force[0][0] = -((ufk[0][0]+(grav[0]*mk[0]))-force[1][0]);
    torque[0][0] = (((rk[0][1]*((ufk[0][2]+(grav[2]*mk[0]))-force[1][2]))-(
      rk[0][2]*((ufk[0][1]+(grav[1]*mk[0]))-force[1][1])))-(utk[0][0]+(((
      force[1][1]*ri[1][2])-(force[1][2]*ri[1][1]))-torque[1][0])));
    force[0][1] = -((ufk[0][1]+(grav[1]*mk[0]))-force[1][1]);
    torque[0][1] = (((rk[0][2]*((ufk[0][0]+(grav[0]*mk[0]))-force[1][0]))-(
      rk[0][0]*((ufk[0][2]+(grav[2]*mk[0]))-force[1][2])))-(utk[0][1]+(((
      force[1][2]*ri[1][0])-(force[1][0]*ri[1][2]))-torque[1][1])));
    force[0][2] = -((ufk[0][2]+(grav[2]*mk[0]))-force[1][2]);
    torque[0][2] = (((rk[0][0]*((ufk[0][1]+(grav[1]*mk[0]))-force[1][1]))-(
      rk[0][1]*((ufk[0][0]+(grav[0]*mk[0]))-force[1][0])))-(utk[0][2]+(((
      force[1][0]*ri[1][1])-(force[1][1]*ri[1][0]))-torque[1][2])));
/*
 Used 0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain  504 adds/subtracts/negates
                    387 multiplies
                      0 divides
                    141 assignments
*/
}

void sdmom(double lm[3],
    double am[3],
    double *ke)
{
/*
Compute system linear and angular momentum, and kinetic energy.

Generated 24-May-2007 16:22:11 by SD/FAST, Order(N) formulation
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
    lk[7][0] = (mk[7]*vnk[0][0]);
    lk[7][1] = (mk[7]*vnk[0][1]);
    lk[7][2] = (mk[7]*vnk[0][2]);
    lk[8][0] = (mk[8]*vnk[1][0]);
    lk[8][1] = (mk[8]*vnk[1][1]);
    lk[8][2] = (mk[8]*vnk[1][2]);
    lk[9][0] = (mk[9]*vnk[2][0]);
    lk[9][1] = (mk[9]*vnk[2][1]);
    lk[9][2] = (mk[9]*vnk[2][2]);
    lk[10][0] = (mk[10]*vnk[3][0]);
    lk[10][1] = (mk[10]*vnk[3][1]);
    lk[10][2] = (mk[10]*vnk[3][2]);
    lk[11][0] = (mk[11]*vnk[4][0]);
    lk[11][1] = (mk[11]*vnk[4][1]);
    lk[11][2] = (mk[11]*vnk[4][2]);
    hnk[7][0] = ((ik[7][0][2]*Wik[0][2])+((ik[7][0][0]*Wik[0][0])+(ik[7][0][1]*
      Wik[0][1])));
    hnk[7][1] = ((ik[7][1][2]*Wik[0][2])+((ik[7][1][0]*Wik[0][0])+(ik[7][1][1]*
      Wik[0][1])));
    hnk[7][2] = ((ik[7][2][2]*Wik[0][2])+((ik[7][2][0]*Wik[0][0])+(ik[7][2][1]*
      Wik[0][1])));
    hnk[8][0] = ((ik[8][0][2]*wk[1][2])+((ik[8][0][0]*wk[1][0])+(ik[8][0][1]*
      wk[1][1])));
    hnk[8][1] = ((ik[8][1][2]*wk[1][2])+((ik[8][1][0]*wk[1][0])+(ik[8][1][1]*
      wk[1][1])));
    hnk[8][2] = ((ik[8][2][2]*wk[1][2])+((ik[8][2][0]*wk[1][0])+(ik[8][2][1]*
      wk[1][1])));
    hnk[9][0] = ((ik[9][0][2]*wk[2][2])+((ik[9][0][0]*wk[2][0])+(ik[9][0][1]*
      wk[2][1])));
    hnk[9][1] = ((ik[9][1][2]*wk[2][2])+((ik[9][1][0]*wk[2][0])+(ik[9][1][1]*
      wk[2][1])));
    hnk[9][2] = ((ik[9][2][2]*wk[2][2])+((ik[9][2][0]*wk[2][0])+(ik[9][2][1]*
      wk[2][1])));
    hnk[10][0] = ((ik[10][0][2]*wk[3][2])+((ik[10][0][0]*wk[3][0])+(ik[10][0][1]
      *wk[3][1])));
    hnk[10][1] = ((ik[10][1][2]*wk[3][2])+((ik[10][1][0]*wk[3][0])+(ik[10][1][1]
      *wk[3][1])));
    hnk[10][2] = ((ik[10][2][2]*wk[3][2])+((ik[10][2][0]*wk[3][0])+(ik[10][2][1]
      *wk[3][1])));
    hnk[11][0] = ((ik[11][0][2]*wk[4][2])+((ik[11][0][0]*wk[4][0])+(ik[11][0][1]
      *wk[4][1])));
    hnk[11][1] = ((ik[11][1][2]*wk[4][2])+((ik[11][1][0]*wk[4][0])+(ik[11][1][1]
      *wk[4][1])));
    hnk[11][2] = ((ik[11][2][2]*wk[4][2])+((ik[11][2][0]*wk[4][0])+(ik[11][2][1]
      *wk[4][1])));
    lm[0] = (lk[11][0]+(lk[10][0]+(lk[9][0]+(lk[7][0]+lk[8][0]))));
    lm[1] = (lk[11][1]+(lk[10][1]+(lk[9][1]+(lk[7][1]+lk[8][1]))));
    lm[2] = (lk[11][2]+(lk[10][2]+(lk[9][2]+(lk[7][2]+lk[8][2]))));
    temp[0] = ((((cnk[2][0][2]*hnk[9][2])+((cnk[2][0][0]*hnk[9][0])+(
      cnk[2][0][1]*hnk[9][1])))+((lk[9][2]*rnk[2][1])-(lk[9][1]*rnk[2][2])))+(((
      (Cik[0][0][2]*hnk[7][2])+((Cik[0][0][0]*hnk[7][0])+(Cik[0][0][1]*hnk[7][1]
      )))+((lk[7][2]*rnk[0][1])-(lk[7][1]*rnk[0][2])))+(((cnk[1][0][2]*hnk[8][2]
      )+((cnk[1][0][0]*hnk[8][0])+(cnk[1][0][1]*hnk[8][1])))+((lk[8][2]*
      rnk[1][1])-(lk[8][1]*rnk[1][2])))));
    am[0] = (((((cnk[4][0][2]*hnk[11][2])+((cnk[4][0][0]*hnk[11][0])+(
      cnk[4][0][1]*hnk[11][1])))+((lk[11][2]*rnk[4][1])-(lk[11][1]*rnk[4][2])))+
      ((((cnk[3][0][2]*hnk[10][2])+((cnk[3][0][0]*hnk[10][0])+(cnk[3][0][1]*
      hnk[10][1])))+((lk[10][2]*rnk[3][1])-(lk[10][1]*rnk[3][2])))+temp[0]))-((
      com[1]*lm[2])-(com[2]*lm[1])));
    temp[0] = ((((cnk[2][1][2]*hnk[9][2])+((cnk[2][1][0]*hnk[9][0])+(
      cnk[2][1][1]*hnk[9][1])))+((lk[9][0]*rnk[2][2])-(lk[9][2]*rnk[2][0])))+(((
      (Cik[0][1][2]*hnk[7][2])+((Cik[0][1][0]*hnk[7][0])+(Cik[0][1][1]*hnk[7][1]
      )))+((lk[7][0]*rnk[0][2])-(lk[7][2]*rnk[0][0])))+(((cnk[1][1][2]*hnk[8][2]
      )+((cnk[1][1][0]*hnk[8][0])+(cnk[1][1][1]*hnk[8][1])))+((lk[8][0]*
      rnk[1][2])-(lk[8][2]*rnk[1][0])))));
    am[1] = (((((cnk[4][1][2]*hnk[11][2])+((cnk[4][1][0]*hnk[11][0])+(
      cnk[4][1][1]*hnk[11][1])))+((lk[11][0]*rnk[4][2])-(lk[11][2]*rnk[4][0])))+
      ((((cnk[3][1][2]*hnk[10][2])+((cnk[3][1][0]*hnk[10][0])+(cnk[3][1][1]*
      hnk[10][1])))+((lk[10][0]*rnk[3][2])-(lk[10][2]*rnk[3][0])))+temp[0]))-((
      com[2]*lm[0])-(com[0]*lm[2])));
    temp[0] = ((((cnk[2][2][2]*hnk[9][2])+((cnk[2][2][0]*hnk[9][0])+(
      cnk[2][2][1]*hnk[9][1])))+((lk[9][1]*rnk[2][0])-(lk[9][0]*rnk[2][1])))+(((
      (Cik[0][2][2]*hnk[7][2])+((Cik[0][2][0]*hnk[7][0])+(Cik[0][2][1]*hnk[7][1]
      )))+((lk[7][1]*rnk[0][0])-(lk[7][0]*rnk[0][1])))+(((cnk[1][2][2]*hnk[8][2]
      )+((cnk[1][2][0]*hnk[8][0])+(cnk[1][2][1]*hnk[8][1])))+((lk[8][1]*
      rnk[1][0])-(lk[8][0]*rnk[1][1])))));
    am[2] = (((((cnk[4][2][2]*hnk[11][2])+((cnk[4][2][0]*hnk[11][0])+(
      cnk[4][2][1]*hnk[11][1])))+((lk[11][1]*rnk[4][0])-(lk[11][0]*rnk[4][1])))+
      ((((cnk[3][2][2]*hnk[10][2])+((cnk[3][2][0]*hnk[10][0])+(cnk[3][2][1]*
      hnk[10][1])))+((lk[10][1]*rnk[3][0])-(lk[10][0]*rnk[3][1])))+temp[0]))-((
      com[0]*lm[1])-(com[1]*lm[0])));
    temp[0] = ((((hnk[7][2]*Wik[0][2])+((hnk[7][0]*Wik[0][0])+(hnk[7][1]*
      Wik[0][1])))+((lk[7][2]*vnk[0][2])+((lk[7][0]*vnk[0][0])+(lk[7][1]*
      vnk[0][1]))))+(((hnk[8][2]*wk[1][2])+((hnk[8][0]*wk[1][0])+(hnk[8][1]*
      wk[1][1])))+((lk[8][2]*vnk[1][2])+((lk[8][0]*vnk[1][0])+(lk[8][1]*
      vnk[1][1])))));
    temp[1] = ((((hnk[10][2]*wk[3][2])+((hnk[10][0]*wk[3][0])+(hnk[10][1]*
      wk[3][1])))+((lk[10][2]*vnk[3][2])+((lk[10][0]*vnk[3][0])+(lk[10][1]*
      vnk[3][1]))))+((((hnk[9][2]*wk[2][2])+((hnk[9][0]*wk[2][0])+(hnk[9][1]*
      wk[2][1])))+((lk[9][2]*vnk[2][2])+((lk[9][0]*vnk[2][0])+(lk[9][1]*
      vnk[2][1]))))+temp[0]));
    *ke = (.5*((((hnk[11][2]*wk[4][2])+((hnk[11][0]*wk[4][0])+(hnk[11][1]*
      wk[4][1])))+((lk[11][2]*vnk[4][2])+((lk[11][0]*vnk[4][0])+(lk[11][1]*
      vnk[4][1]))))+temp[1]));
/*
 Used 0.00 seconds CPU time,
 0 additional bytes of memory.
 Equations contain  149 adds/subtracts/negates
                    172 multiplies
                      0 divides
                     42 assignments
*/
}

void sdsys(double *mtoto,
    double cm[3],
    double icm[3][3])
{
/*
Compute system total mass, and instantaneous center of mass and
inertia matrix.

Generated 24-May-2007 16:22:11 by SD/FAST, Order(N) formulation
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
    *mtoto = mtot;
    cm[0] = com[0];
    cm[1] = com[1];
    cm[2] = com[2];
    ikcnkt[0][0][0] = ((Cik[0][0][2]*ik[7][0][2])+((Cik[0][0][0]*ik[7][0][0])+(
      Cik[0][0][1]*ik[7][0][1])));
    ikcnkt[0][0][1] = ((Cik[0][1][2]*ik[7][0][2])+((Cik[0][1][0]*ik[7][0][0])+(
      Cik[0][1][1]*ik[7][0][1])));
    ikcnkt[0][0][2] = ((Cik[0][2][2]*ik[7][0][2])+((Cik[0][2][0]*ik[7][0][0])+(
      Cik[0][2][1]*ik[7][0][1])));
    ikcnkt[0][1][0] = ((Cik[0][0][2]*ik[7][1][2])+((Cik[0][0][0]*ik[7][1][0])+(
      Cik[0][0][1]*ik[7][1][1])));
    ikcnkt[0][1][1] = ((Cik[0][1][2]*ik[7][1][2])+((Cik[0][1][0]*ik[7][1][0])+(
      Cik[0][1][1]*ik[7][1][1])));
    ikcnkt[0][1][2] = ((Cik[0][2][2]*ik[7][1][2])+((Cik[0][2][0]*ik[7][1][0])+(
      Cik[0][2][1]*ik[7][1][1])));
    ikcnkt[0][2][0] = ((Cik[0][0][2]*ik[7][2][2])+((Cik[0][0][0]*ik[7][2][0])+(
      Cik[0][0][1]*ik[7][2][1])));
    ikcnkt[0][2][1] = ((Cik[0][1][2]*ik[7][2][2])+((Cik[0][1][0]*ik[7][2][0])+(
      Cik[0][1][1]*ik[7][2][1])));
    ikcnkt[0][2][2] = ((Cik[0][2][2]*ik[7][2][2])+((Cik[0][2][0]*ik[7][2][0])+(
      Cik[0][2][1]*ik[7][2][1])));
    ikcnkt[1][0][0] = ((cnk[1][0][2]*ik[8][0][2])+((cnk[1][0][0]*ik[8][0][0])+(
      cnk[1][0][1]*ik[8][0][1])));
    ikcnkt[1][0][1] = ((cnk[1][1][2]*ik[8][0][2])+((cnk[1][1][0]*ik[8][0][0])+(
      cnk[1][1][1]*ik[8][0][1])));
    ikcnkt[1][0][2] = ((cnk[1][2][2]*ik[8][0][2])+((cnk[1][2][0]*ik[8][0][0])+(
      cnk[1][2][1]*ik[8][0][1])));
    ikcnkt[1][1][0] = ((cnk[1][0][2]*ik[8][1][2])+((cnk[1][0][0]*ik[8][1][0])+(
      cnk[1][0][1]*ik[8][1][1])));
    ikcnkt[1][1][1] = ((cnk[1][1][2]*ik[8][1][2])+((cnk[1][1][0]*ik[8][1][0])+(
      cnk[1][1][1]*ik[8][1][1])));
    ikcnkt[1][1][2] = ((cnk[1][2][2]*ik[8][1][2])+((cnk[1][2][0]*ik[8][1][0])+(
      cnk[1][2][1]*ik[8][1][1])));
    ikcnkt[1][2][0] = ((cnk[1][0][2]*ik[8][2][2])+((cnk[1][0][0]*ik[8][2][0])+(
      cnk[1][0][1]*ik[8][2][1])));
    ikcnkt[1][2][1] = ((cnk[1][1][2]*ik[8][2][2])+((cnk[1][1][0]*ik[8][2][0])+(
      cnk[1][1][1]*ik[8][2][1])));
    ikcnkt[1][2][2] = ((cnk[1][2][2]*ik[8][2][2])+((cnk[1][2][0]*ik[8][2][0])+(
      cnk[1][2][1]*ik[8][2][1])));
    ikcnkt[2][0][0] = ((cnk[2][0][2]*ik[9][0][2])+((cnk[2][0][0]*ik[9][0][0])+(
      cnk[2][0][1]*ik[9][0][1])));
    ikcnkt[2][0][1] = ((cnk[2][1][2]*ik[9][0][2])+((cnk[2][1][0]*ik[9][0][0])+(
      cnk[2][1][1]*ik[9][0][1])));
    ikcnkt[2][0][2] = ((cnk[2][2][2]*ik[9][0][2])+((cnk[2][2][0]*ik[9][0][0])+(
      cnk[2][2][1]*ik[9][0][1])));
    ikcnkt[2][1][0] = ((cnk[2][0][2]*ik[9][1][2])+((cnk[2][0][0]*ik[9][1][0])+(
      cnk[2][0][1]*ik[9][1][1])));
    ikcnkt[2][1][1] = ((cnk[2][1][2]*ik[9][1][2])+((cnk[2][1][0]*ik[9][1][0])+(
      cnk[2][1][1]*ik[9][1][1])));
    ikcnkt[2][1][2] = ((cnk[2][2][2]*ik[9][1][2])+((cnk[2][2][0]*ik[9][1][0])+(
      cnk[2][2][1]*ik[9][1][1])));
    ikcnkt[2][2][0] = ((cnk[2][0][2]*ik[9][2][2])+((cnk[2][0][0]*ik[9][2][0])+(
      cnk[2][0][1]*ik[9][2][1])));
    ikcnkt[2][2][1] = ((cnk[2][1][2]*ik[9][2][2])+((cnk[2][1][0]*ik[9][2][0])+(
      cnk[2][1][1]*ik[9][2][1])));
    ikcnkt[2][2][2] = ((cnk[2][2][2]*ik[9][2][2])+((cnk[2][2][0]*ik[9][2][0])+(
      cnk[2][2][1]*ik[9][2][1])));
    ikcnkt[3][0][0] = ((cnk[3][0][2]*ik[10][0][2])+((cnk[3][0][0]*ik[10][0][0])+
      (cnk[3][0][1]*ik[10][0][1])));
    ikcnkt[3][0][1] = ((cnk[3][1][2]*ik[10][0][2])+((cnk[3][1][0]*ik[10][0][0])+
      (cnk[3][1][1]*ik[10][0][1])));
    ikcnkt[3][0][2] = ((cnk[3][2][2]*ik[10][0][2])+((cnk[3][2][0]*ik[10][0][0])+
      (cnk[3][2][1]*ik[10][0][1])));
    ikcnkt[3][1][0] = ((cnk[3][0][2]*ik[10][1][2])+((cnk[3][0][0]*ik[10][1][0])+
      (cnk[3][0][1]*ik[10][1][1])));
    ikcnkt[3][1][1] = ((cnk[3][1][2]*ik[10][1][2])+((cnk[3][1][0]*ik[10][1][0])+
      (cnk[3][1][1]*ik[10][1][1])));
    ikcnkt[3][1][2] = ((cnk[3][2][2]*ik[10][1][2])+((cnk[3][2][0]*ik[10][1][0])+
      (cnk[3][2][1]*ik[10][1][1])));
    ikcnkt[3][2][0] = ((cnk[3][0][2]*ik[10][2][2])+((cnk[3][0][0]*ik[10][2][0])+
      (cnk[3][0][1]*ik[10][2][1])));
    ikcnkt[3][2][1] = ((cnk[3][1][2]*ik[10][2][2])+((cnk[3][1][0]*ik[10][2][0])+
      (cnk[3][1][1]*ik[10][2][1])));
    ikcnkt[3][2][2] = ((cnk[3][2][2]*ik[10][2][2])+((cnk[3][2][0]*ik[10][2][0])+
      (cnk[3][2][1]*ik[10][2][1])));
    ikcnkt[4][0][0] = ((cnk[4][0][2]*ik[11][0][2])+((cnk[4][0][0]*ik[11][0][0])+
      (cnk[4][0][1]*ik[11][0][1])));
    ikcnkt[4][0][1] = ((cnk[4][1][2]*ik[11][0][2])+((cnk[4][1][0]*ik[11][0][0])+
      (cnk[4][1][1]*ik[11][0][1])));
    ikcnkt[4][0][2] = ((cnk[4][2][2]*ik[11][0][2])+((cnk[4][2][0]*ik[11][0][0])+
      (cnk[4][2][1]*ik[11][0][1])));
    ikcnkt[4][1][0] = ((cnk[4][0][2]*ik[11][1][2])+((cnk[4][0][0]*ik[11][1][0])+
      (cnk[4][0][1]*ik[11][1][1])));
    ikcnkt[4][1][1] = ((cnk[4][1][2]*ik[11][1][2])+((cnk[4][1][0]*ik[11][1][0])+
      (cnk[4][1][1]*ik[11][1][1])));
    ikcnkt[4][1][2] = ((cnk[4][2][2]*ik[11][1][2])+((cnk[4][2][0]*ik[11][1][0])+
      (cnk[4][2][1]*ik[11][1][1])));
    ikcnkt[4][2][0] = ((cnk[4][0][2]*ik[11][2][2])+((cnk[4][0][0]*ik[11][2][0])+
      (cnk[4][0][1]*ik[11][2][1])));
    ikcnkt[4][2][1] = ((cnk[4][1][2]*ik[11][2][2])+((cnk[4][1][0]*ik[11][2][0])+
      (cnk[4][1][1]*ik[11][2][1])));
    ikcnkt[4][2][2] = ((cnk[4][2][2]*ik[11][2][2])+((cnk[4][2][0]*ik[11][2][0])+
      (cnk[4][2][1]*ik[11][2][1])));
    temp[0] = (((mk[8]*((rnk[1][1]*rnk[1][1])+(rnk[1][2]*rnk[1][2])))+((
      cnk[1][0][2]*ikcnkt[1][2][0])+((cnk[1][0][0]*ikcnkt[1][0][0])+(
      cnk[1][0][1]*ikcnkt[1][1][0]))))+((psikg[0][0]+(psmkg*((psrcomg[1]*
      psrcomg[1])+(psrcomg[2]*psrcomg[2]))))+((mk[7]*((rnk[0][1]*rnk[0][1])+(
      rnk[0][2]*rnk[0][2])))+((Cik[0][0][2]*ikcnkt[0][2][0])+((Cik[0][0][0]*
      ikcnkt[0][0][0])+(Cik[0][0][1]*ikcnkt[0][1][0]))))));
    temp[1] = (((mk[10]*((rnk[3][1]*rnk[3][1])+(rnk[3][2]*rnk[3][2])))+((
      cnk[3][0][2]*ikcnkt[3][2][0])+((cnk[3][0][0]*ikcnkt[3][0][0])+(
      cnk[3][0][1]*ikcnkt[3][1][0]))))+(((mk[9]*((rnk[2][1]*rnk[2][1])+(
      rnk[2][2]*rnk[2][2])))+((cnk[2][0][2]*ikcnkt[2][2][0])+((cnk[2][0][0]*
      ikcnkt[2][0][0])+(cnk[2][0][1]*ikcnkt[2][1][0]))))+temp[0]));
    icm[0][0] = ((((mk[11]*((rnk[4][1]*rnk[4][1])+(rnk[4][2]*rnk[4][2])))+((
      cnk[4][0][2]*ikcnkt[4][2][0])+((cnk[4][0][0]*ikcnkt[4][0][0])+(
      cnk[4][0][1]*ikcnkt[4][1][0]))))+temp[1])-(mtot*((com[1]*com[1])+(com[2]*
      com[2]))));
    temp[0] = (((psikg[0][1]-(psmkg*(psrcomg[0]*psrcomg[1])))+(((Cik[0][0][2]*
      ikcnkt[0][2][1])+((Cik[0][0][0]*ikcnkt[0][0][1])+(Cik[0][0][1]*
      ikcnkt[0][1][1])))-(mk[7]*(rnk[0][0]*rnk[0][1]))))+(((cnk[1][0][2]*
      ikcnkt[1][2][1])+((cnk[1][0][0]*ikcnkt[1][0][1])+(cnk[1][0][1]*
      ikcnkt[1][1][1])))-(mk[8]*(rnk[1][0]*rnk[1][1]))));
    temp[1] = ((((cnk[4][0][2]*ikcnkt[4][2][1])+((cnk[4][0][0]*ikcnkt[4][0][1])+
      (cnk[4][0][1]*ikcnkt[4][1][1])))-(mk[11]*(rnk[4][0]*rnk[4][1])))+((((
      cnk[3][0][2]*ikcnkt[3][2][1])+((cnk[3][0][0]*ikcnkt[3][0][1])+(
      cnk[3][0][1]*ikcnkt[3][1][1])))-(mk[10]*(rnk[3][0]*rnk[3][1])))+((((
      cnk[2][0][2]*ikcnkt[2][2][1])+((cnk[2][0][0]*ikcnkt[2][0][1])+(
      cnk[2][0][1]*ikcnkt[2][1][1])))-(mk[9]*(rnk[2][0]*rnk[2][1])))+temp[0])));
    icm[0][1] = ((mtot*(com[0]*com[1]))+temp[1]);
    temp[0] = (((psikg[0][2]-(psmkg*(psrcomg[0]*psrcomg[2])))+(((Cik[0][0][2]*
      ikcnkt[0][2][2])+((Cik[0][0][0]*ikcnkt[0][0][2])+(Cik[0][0][1]*
      ikcnkt[0][1][2])))-(mk[7]*(rnk[0][0]*rnk[0][2]))))+(((cnk[1][0][2]*
      ikcnkt[1][2][2])+((cnk[1][0][0]*ikcnkt[1][0][2])+(cnk[1][0][1]*
      ikcnkt[1][1][2])))-(mk[8]*(rnk[1][0]*rnk[1][2]))));
    temp[1] = ((((cnk[4][0][2]*ikcnkt[4][2][2])+((cnk[4][0][0]*ikcnkt[4][0][2])+
      (cnk[4][0][1]*ikcnkt[4][1][2])))-(mk[11]*(rnk[4][0]*rnk[4][2])))+((((
      cnk[3][0][2]*ikcnkt[3][2][2])+((cnk[3][0][0]*ikcnkt[3][0][2])+(
      cnk[3][0][1]*ikcnkt[3][1][2])))-(mk[10]*(rnk[3][0]*rnk[3][2])))+((((
      cnk[2][0][2]*ikcnkt[2][2][2])+((cnk[2][0][0]*ikcnkt[2][0][2])+(
      cnk[2][0][1]*ikcnkt[2][1][2])))-(mk[9]*(rnk[2][0]*rnk[2][2])))+temp[0])));
    icm[0][2] = ((mtot*(com[0]*com[2]))+temp[1]);
    icm[1][0] = icm[0][1];
    temp[0] = (((mk[8]*((rnk[1][0]*rnk[1][0])+(rnk[1][2]*rnk[1][2])))+((
      cnk[1][1][2]*ikcnkt[1][2][1])+((cnk[1][1][0]*ikcnkt[1][0][1])+(
      cnk[1][1][1]*ikcnkt[1][1][1]))))+((psikg[1][1]+(psmkg*((psrcomg[0]*
      psrcomg[0])+(psrcomg[2]*psrcomg[2]))))+((mk[7]*((rnk[0][0]*rnk[0][0])+(
      rnk[0][2]*rnk[0][2])))+((Cik[0][1][2]*ikcnkt[0][2][1])+((Cik[0][1][0]*
      ikcnkt[0][0][1])+(Cik[0][1][1]*ikcnkt[0][1][1]))))));
    temp[1] = (((mk[10]*((rnk[3][0]*rnk[3][0])+(rnk[3][2]*rnk[3][2])))+((
      cnk[3][1][2]*ikcnkt[3][2][1])+((cnk[3][1][0]*ikcnkt[3][0][1])+(
      cnk[3][1][1]*ikcnkt[3][1][1]))))+(((mk[9]*((rnk[2][0]*rnk[2][0])+(
      rnk[2][2]*rnk[2][2])))+((cnk[2][1][2]*ikcnkt[2][2][1])+((cnk[2][1][0]*
      ikcnkt[2][0][1])+(cnk[2][1][1]*ikcnkt[2][1][1]))))+temp[0]));
    icm[1][1] = ((((mk[11]*((rnk[4][0]*rnk[4][0])+(rnk[4][2]*rnk[4][2])))+((
      cnk[4][1][2]*ikcnkt[4][2][1])+((cnk[4][1][0]*ikcnkt[4][0][1])+(
      cnk[4][1][1]*ikcnkt[4][1][1]))))+temp[1])-(mtot*((com[0]*com[0])+(com[2]*
      com[2]))));
    temp[0] = (((psikg[1][2]-(psmkg*(psrcomg[1]*psrcomg[2])))+(((Cik[0][1][2]*
      ikcnkt[0][2][2])+((Cik[0][1][0]*ikcnkt[0][0][2])+(Cik[0][1][1]*
      ikcnkt[0][1][2])))-(mk[7]*(rnk[0][1]*rnk[0][2]))))+(((cnk[1][1][2]*
      ikcnkt[1][2][2])+((cnk[1][1][0]*ikcnkt[1][0][2])+(cnk[1][1][1]*
      ikcnkt[1][1][2])))-(mk[8]*(rnk[1][1]*rnk[1][2]))));
    temp[1] = ((((cnk[4][1][2]*ikcnkt[4][2][2])+((cnk[4][1][0]*ikcnkt[4][0][2])+
      (cnk[4][1][1]*ikcnkt[4][1][2])))-(mk[11]*(rnk[4][1]*rnk[4][2])))+((((
      cnk[3][1][2]*ikcnkt[3][2][2])+((cnk[3][1][0]*ikcnkt[3][0][2])+(
      cnk[3][1][1]*ikcnkt[3][1][2])))-(mk[10]*(rnk[3][1]*rnk[3][2])))+((((
      cnk[2][1][2]*ikcnkt[2][2][2])+((cnk[2][1][0]*ikcnkt[2][0][2])+(
      cnk[2][1][1]*ikcnkt[2][1][2])))-(mk[9]*(rnk[2][1]*rnk[2][2])))+temp[0])));
    icm[1][2] = ((mtot*(com[1]*com[2]))+temp[1]);
    icm[2][0] = icm[0][2];
    icm[2][1] = icm[1][2];
    temp[0] = (((mk[8]*((rnk[1][0]*rnk[1][0])+(rnk[1][1]*rnk[1][1])))+((
      cnk[1][2][2]*ikcnkt[1][2][2])+((cnk[1][2][0]*ikcnkt[1][0][2])+(
      cnk[1][2][1]*ikcnkt[1][1][2]))))+((psikg[2][2]+(psmkg*((psrcomg[0]*
      psrcomg[0])+(psrcomg[1]*psrcomg[1]))))+((mk[7]*((rnk[0][0]*rnk[0][0])+(
      rnk[0][1]*rnk[0][1])))+((Cik[0][2][2]*ikcnkt[0][2][2])+((Cik[0][2][0]*
      ikcnkt[0][0][2])+(Cik[0][2][1]*ikcnkt[0][1][2]))))));
    temp[1] = (((mk[10]*((rnk[3][0]*rnk[3][0])+(rnk[3][1]*rnk[3][1])))+((
      cnk[3][2][2]*ikcnkt[3][2][2])+((cnk[3][2][0]*ikcnkt[3][0][2])+(
      cnk[3][2][1]*ikcnkt[3][1][2]))))+(((mk[9]*((rnk[2][0]*rnk[2][0])+(
      rnk[2][1]*rnk[2][1])))+((cnk[2][2][2]*ikcnkt[2][2][2])+((cnk[2][2][0]*
      ikcnkt[2][0][2])+(cnk[2][2][1]*ikcnkt[2][1][2]))))+temp[0]));
    icm[2][2] = ((((mk[11]*((rnk[4][0]*rnk[4][0])+(rnk[4][1]*rnk[4][1])))+((
      cnk[4][2][2]*ikcnkt[4][2][2])+((cnk[4][2][0]*ikcnkt[4][0][2])+(
      cnk[4][2][1]*ikcnkt[4][1][2]))))+temp[1])-(mtot*((com[0]*com[0])+(com[1]*
      com[1]))));
/*
 Used 0.02 seconds CPU time,
 0 additional bytes of memory.
 Equations contain  243 adds/subtracts/negates
                    330 multiplies
                      0 divides
                     70 assignments
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

    grav[0] = gravin[0];
    gravq[0] = 3;
    grav[1] = gravin[1];
    gravq[1] = 3;
    grav[2] = gravin[2];
    gravq[2] = 3;
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
    info[11] = 5;
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

    *gentm = 162211;
}
/*
Done. CPU seconds used: 0.14  Memory used: 1687552 bytes.
Equation complexity:
  sdstate:   618 adds   846 multiplies     3 divides   641 assignments
  sdderiv:  2633 adds  3040 multiplies    67 divides  2210 assignments
  sdresid:   628 adds   596 multiplies     0 divides   412 assignments
  sdreac:    504 adds   387 multiplies     0 divides   141 assignments
  sdmom:     149 adds   172 multiplies     0 divides    42 assignments
  sdsys:     243 adds   330 multiplies     0 divides    70 assignments
*/
