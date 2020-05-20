#include "../include/qb.h"

static int32_t ERR = 0, ERL = 0;

static double P[40 + 1][11 + 1];
static double Px[40 + 1][3 + 1];
static double Py[40 + 1][3 + 1];
static double Vx[40 + 1];
static double Vy[40 + 1];
static double B[1 + 1][250 + 1];
static double Ztel[33 + 1];
static QBSTR Znme_str[42 + 1]; // initialized to 0 filled bytes
static double panel[2 + 1][265 + 1];
static double TSflagVECTOR[20 + 1];

static float Pz[3021 + 1][2 + 1];

static double i, j;

static double year, day, hr, min, sec;

static double PH5;
static double ENGsetFLAG;

static double mag;

static double ref, trail, ts, fuel, AYSEfuel;

static double AU, RAD, G, pi, pi2;

static double TSindex;
static double OLDts;

static double tttt;

static double DISPflag;
static double Atarg;

static double cenX, cenY;

static double vflag;

static double Sangle;

static double CONtarg, RcritL, atm, LtrA, COLeventTRIG, MARSelev;
static double CONflag, CONflag2, CONflag3, CONflag4;
static double explFLAG1, explFLAG2;

static double ufo1;
static double ufo2;
static double AYSE;

static double r;
static double difX, difY;

static double a;

static double angle, ELEVangle, h;

static double Vhab;

static double Dcon, Acon, CONacc;

static double Ratm;

static double explCENTER;

static double targ, Dtarg, Acctarg;
static double Vref, Aref, Dref;

static double Ltr;

static double AYSEdist, OCESSdist;

static double cen, cenXoff, cenYoff;

static double Vvangle;
static double VxDEL, VyDEL;

static double MODULEflag;

static double tr;

static double clr, vnSa, oldSa, clrMASK, HPdisp;

static double dist;

static double arcANGLE, stepANGLE;

static double ii;
static double CirX, CirY;

static double startANGLE, stopANGLE;

static double AYSEangle;
static double Ax1, Ax2, Ax3, Ax4, Ax8, Ax9;
static double Ay1, Ay2, Ay3, Ay4, Ay8, Ay9;

static double Ad1, Ad2, Ad3;

static double clr1, clr2;

static double AYSEscrape;

static double x, y, st;

static double P1x, P1y;
static double Px2, Py2;

static double Rmin, AtargPRIME;

static double Rcrit;

static double rD;
static double PH5prime;

static double Acon1;

static double RcritL2;

static double eng;

static double MATCHaacc, CONSTacc, vector, THRUSTangle;
static double Aacc, Av, Are;

static double Pvx, THRUSTx, THRUSTy;

static double HABmass;

static double ALTdel;

static double OLDcenX, OLDcenY;

static double pld;

static double angleALT;

static double Ltx, Lty;

static double Atargref;

static double Atr;

static double VangleDIFF;
static double explosion, explosion1;

static double dayNUM;

static double dte;

static double oldAcctarg;

static double PROBEflag;

// MATCHaacc only appears once, and only an assignment target in the source
// Most likely a typo, but left unchanged here
static double MATCHacc, MATCHaacc;

static double targDISP, LOS, RADAR, INS;
static double NAVmalf;

static double Vrefhab, Vreftarg;

// Dfatctor only appears once, and only an assignment target in the source
// Most likely a typo, but left unchanged here
static double Dfactor, Dfatctor;

static double Cdh;

static double Dfuel;

static double refuel, ventfuel, AYSErefuel, AYSEventfuel;

static double DIFFangle;

static double bkt;

static double Aflag, Sflag;

static double OFFSET;

static double Accel;

static double z;

static double vern, vernA;

static double ORref;

static double angleOFFSET;

static double PROJflag;

static double SRBtimer, SRB;

static double HABrotMALF, HABrotate;

static double vernCNT;

static double Aoffset;

static double Vvtangle;

static double Aa;

static double Wangle;

static double VwindX, VwindY;

static double dSangle;

static double diffSangle;

static double massDEL;

static double VvRangle;

static double AOA, AOAx, AOAy;

static double VVr, Pr;

static double Agrav;

static double DEBUGflag;

static double k;

static double Eflag;

static double LONGtarg;

static double chkBYTE;

static double fileINwarn;

static double MST, EST;

static double Zx;

static double Zt;

static double ufoTIMER;

static double L, orbA;

static double ecc, ORrefOBJ;

static double term, num, eccFLAG, dem;

static double difA, stp;

static double lim1, lim2;

static double FRAMEflag;

static double d;

static double difX1, difX2, difX3;
static double difY1, difY2, difY3;

static double ORrefD;

static double orbEk;

static double orbEp;

static double orbD;

static double L2;

static double Vtan, Vcen;

static double orbE;

static double term2;

static double PROJmax, PROJmin;

static double AtoAPOAPSIS;

static double Xexpl, Yexpl;

static double Xj, Xi;

static double explANGLE;

static double Xexpl1, Yexpl1;

static double V, Vt;

static double time, etime, dtime;

static double dyr, dday, dhr, dmin, dsec;

static double x1, y1;

static double lngW, latW;

static double lng, lat;

static double ja;

static double h1, h2, h3, h4;

static double TIMEsgn;

static double LATdel, LNGdel;

// LNDdel only appears once, and only an assignment target in the source
// Most likely a typo, but left unchanged here
static double LNDdel;

static float vernP_float;

static int16_t HABrotateADJ_i16;

QBM_new_str(z_str)
QBM_new_str(filename_str)
QBM_new_str(y_str)
QBM_new_str(zDISP_str)
QBM_new_str(rotSYMB_str)
QBM_new_str(inpSTR_str)
QBM_new_str(chkCHAR1_str)
QBM_new_str(chkCHAR2_str)
QBM_new_str(ORBITversion_str)
QBM_new_str(outSTR_str)

int main() {
  QBENV *_Q_env = _qb_create_env(stdin, stdout, &ERR, &ERL);

  LABEL_1111: __attribute__((unused));
  // this line is left unimplemented for now
  // ON ERROR GOTO 9000

  qb_screen(_Q_env, 12);
  qb_palette(_Q_env, 8, 19 + (19 * 256) + (19 * 65536));
  qb_palette(_Q_env, 15, 42 + (42 * 256) + (42 * 65536));

  LABEL_91: __attribute__((unused));

  QBFILE *_Q_file1 = qb_open_cstr(_Q_env, "starsr", "I");

  for (i = 1; i <= 3021; i++) {
    qb_finput_float(_Q_file1, &Pz[ (size_t)i ][0]);
    qb_finput_float(_Q_file1, &Pz[ (size_t)i ][1]);
    qb_finput_float(_Q_file1, &Pz[ (size_t)i ][2]);
  }

  for (i = 1; i <= 241; i++) {
    qb_finput_double(_Q_file1, &B[0][ (size_t)i ]);
    qb_finput_double(_Q_file1, &B[1][ (size_t)i ]);
  }

  for (i = 0; i <= 39; i++) {
    qb_finput_double(_Q_file1, &P[ (size_t)i ][0]);
    qb_finput_double(_Q_file1, &P[ (size_t)i ][4]);
    qb_finput_double(_Q_file1, &P[ (size_t)i ][5]);
    qb_finput_double(_Q_file1, &P[ (size_t)i ][8]);
    qb_finput_double(_Q_file1, &P[ (size_t)i ][9]);
    qb_finput_double(_Q_file1, &P[ (size_t)i ][10]);
  }

  qb_finput_double(_Q_file1, &year);
  qb_finput_double(_Q_file1, &day);
  qb_finput_double(_Q_file1, &hr);
  qb_finput_double(_Q_file1, &min);
  qb_finput_double(_Q_file1, &sec);

  for (i = 0; i <= 35; i++) {
    qb_finput_double(_Q_file1, &Px[ (size_t)i ][3]);
    qb_finput_double(_Q_file1, &Py[ (size_t)i ][3]);
    qb_finput_double(_Q_file1, &Vx[ (size_t)i ]);
    qb_finput_double(_Q_file1, &Vy[ (size_t)i ]);
    qb_finput_double(_Q_file1, &P[ (size_t)i ][1]);
    qb_finput_double(_Q_file1, &P[ (size_t)i ][2]);
  }

  for (i = 0; i <= 39; i++) {
    qb_finput_str(_Q_file1, &Znme_str[ (size_t)i ]);
  }

  for (i = 1; i <= 265; i++) {
    for (j = 0; j <= 2; j++) {
      qb_finput_double(_Q_file1, &panel[ (size_t)j ][ (size_t)i ]);
    }
  }

  _qb_set_str_const(&Znme_str[40], "TARGET", 6);
  _qb_set_str_const(&Znme_str[42], "Vtg", 3);
  _qb_set_str_const(&Znme_str[41], "Pch", 3);

  Px[37][3] = 4446370.8284487 + Px[3][3];
  Py[37][3] = 4446370.8284487 + Py[3][3];
  Vx[37] = Vx[3];
  Vy[37] = Vy[3];

  qb_close(_Q_file1);
  QBFILE *_Q_file3 = qb_open_reclen_cstr(_Q_env, "marsTOPOLG.RND", "R", 2);

  PH5 = P[12][5];

  ENGsetFLAG = 1;

  mag = 25;

  ref = 3;
  trail = 1;
  ts = 0.25;
  fuel = 2000;
  AYSEfuel = 15120000;

  AU = 149597890000.0;
  RAD = 57.295779515;
  G = 6.673e-11;
  pi = 3.14159;
  pi2 = 2 * pi;

  TSflagVECTOR[1] = 0.015625;
  TSflagVECTOR[2] = 0.03125;
  TSflagVECTOR[3] = 0.0625;
  TSflagVECTOR[4] = 0.125;
  TSflagVECTOR[5] = 0.25;
  TSflagVECTOR[6] = 0.25;
  TSflagVECTOR[7] = 0.25;
  TSflagVECTOR[8] = 0.5;
  TSflagVECTOR[9] = 1;
  TSflagVECTOR[10] = 2;
  TSflagVECTOR[11] = 5;
  TSflagVECTOR[12] = 10;
  TSflagVECTOR[13] = 20;
  TSflagVECTOR[14] = 30;
  TSflagVECTOR[15] = 40;
  TSflagVECTOR[16] = 50;
  TSflagVECTOR[17] = 60;

  TSindex = 5;
  OLDts = 0.25;

  // 'load situation file
  _Q_file1 = qb_open_cstr(_Q_env, "orbitstr.txt", "I");
  if (qbf_eof(_Q_file1)) {
    _qb_set_str_const(&z_str, "", 0);
    qb_close(_Q_file1);
    goto LABEL_51;
  }
  qb_finput_str(_Q_file1, &z_str);
  if (_qb_str_equals_const(z_str, "normal", 6)) {
    _qb_set_str_const(&z_str, "", 0);
  }
  qb_close(_Q_file1);
  _Q_file1 = qb_open_cstr(_Q_env, "orbitstr.txt", "O");
  if (_qb_str_equals_const(z_str, "RESTART", 7)) {
    QBM_new_const_str(_Q_tmp, "OSBACKUP", 8);
    qb_fprint_str(_Q_file1, _Q_tmp);
    _qb_free_str(&_Q_tmp);
  }
  qb_close(_Q_file1);
  if (_qb_str_nequals_const(z_str, "", 0)) {
    goto LABEL_52;
  }

  LABEL_51:;
  qb_locate(_Q_env, 5, 5);
  if (_qb_str_equals_const(z_str, "", 0)) {
      // wrap = false, question = false
      QBM_new_const_str(_Q_tmp, "Restart previous state (or type filename)? ", 43);
      qb_stdinput_str_const(
        _Q_env,
        "Restart previous state (or type filename)? ",
        43,
        &y_str,
        FALSE,
        FALSE
      );
      _qb_free_str(&_Q_tmp);
  }
  {
    QBM_new_str(_Q_tmp_1);
    QBM_new_str(_Q_tmp_2);
    qbf_left_str_direct(&_Q_tmp_1, y_str, 1);
    qbf_ucase_str_direct(&_Q_tmp_2, _Q_tmp_1);
    if (_qb_str_equals_const(_Q_tmp_2, "Q", 1)) {
      qb_end(_Q_env);
    }
    _qb_free_str(&_Q_tmp_1);
    _qb_free_str(&_Q_tmp_2);
  }
  {
    QBM_new_str(_Q_tmp_1);
    QBM_new_str(_Q_tmp_2);
    qbf_left_str_direct(&_Q_tmp_1, y_str, 1);
    qbf_ucase_str_direct(&_Q_tmp_2, _Q_tmp_1);
    int _Q_cond = _qb_str_equals_const(_Q_tmp_2, "Y", 1);
    _qb_free_str(&_Q_tmp_1);
    _qb_free_str(&_Q_tmp_2);
    if (_Q_cond) {
      _qb_set_str_const(&z_str, "OSBACKUP", 8);
      goto LABEL_52;
    }
  }
  if (_qb_str_equals_const(y_str, "", 0)) {
    _qb_set_str_const(&z_str, "OSBACKUP", 8);
    goto LABEL_52;
  }
  _qb_set_str(&z_str, y_str);

  if (_qb_str_equals_const(z_str, "", 0)) {
    qb_end(_Q_env);
  }

  LABEL_52:;
  _qb_set_str(&filename_str, z_str);
  QBM_gosub(_Q_env, LABEL_701)
  QBM_gosub(_Q_env, LABEL_405)

  LABEL_100:;
  // 'Initialize frame rate timer
  tttt = qbf_timer();

  // 'Zero acceleration variables
  for (i = 0; i <= 35; i++) {
    P[ (size_t)i ][1] = 0;
    P[ (size_t)i ][2] = 0;
  }
  P[38][1] = 0;
  P[38][2] = 0;
  P[39][1] = 0;
  P[39][2] = 0;

  // 'Erase target vector
  if (DISPflag == 0) {
    qb_line(
        _Q_env,
        30,
        120,
        30 + (20 * qbf_sin(Atarg)),
        120 + (20 * qbf_cos(Atarg)),
        0
      );
  }
  if (
    qbf_sqr(
      _qbf_pow(
        (Px[28][3] - cenX) * mag / AU,
        2
      ) +
      _qbf_pow(
        (Py[28][3] - cenY) * mag * 1 / AU,
        2
      )
    ) > 400) {
    goto LABEL_131;
  }
  if (vflag == 1) {
    qb_line(
      _Q_env,
      300 + (Px[28][3] - cenX) * mag / AU,
      220 + (Py[28][3] - cenY) * mag * 1 / AU,
      300 + (30 * qbf_sin(Atarg)) + (Px[28][3] - cenX) * mag / AU,
      220 + (30 * qbf_cos(Atarg)) + (Py[28][3] - cenY) * mag * 1 / AU,
      0
    );
  }
  if (vflag == 1) {
    qb_line(_Q_env,
      300 + (Px[28][3] - cenX) * mag / AU,
      220 + (Py[28][3] - cenY) * mag * 1 / AU,
      300 + (10 * qbf_sin(Sangle)) + (Px[28][3] - cenX) * mag / AU,
      220 + (10 * qbf_cos(Sangle)) + (Py[28][3] - cenY) * mag * 1 / AU,
      0
    );
  }

  LABEL_131:;
  CONflag = 0;
  CONtarg = 0;
  RcritL = 0;
  atm = 40;
  LtrA = 0;
  explFLAG1 = 0;
  COLeventTRIG = 0;
  MARSelev = 0;
  CONflag2 = 0;

  // 'Calculate gravitational acceleration for each object pair
  for (i = 1; i <= 241; i++) {
    if (B[1][ (size_t)i ] == B[0][ (size_t)i ]) { goto LABEL_106; }
    if (ufo1 == 0 && (B[1][ (size_t)i ] == 38 || B[0][ (size_t)i ] == 38)) { goto LABEL_106; }
    if (ufo2 == 0 && (B[1][ (size_t)i ] == 39 || B[0][ (size_t)i ] == 39)) { goto LABEL_106; }
    if (B[1][ (size_t)i ] == 32 && AYSE == 150) { goto LABEL_106; }

    difX = Px[ (size_t)B[1][ (size_t)i ] ][3] - Px[ (size_t)B[0][ (size_t)i ] ][3];
    difY = Py[ (size_t)B[1][ (size_t)i ] ][3] - Py[ (size_t)B[0][ (size_t)i ] ][3];

    QBM_gosub(_Q_env, LABEL_5000);

    r = qbf_sqr(_qbf_pow(difY, 2) + _qbf_pow(difX, 2));
    if (r < 0.01) {
      r = 0.01;
    }

    a = G * P[ (size_t)B[0][ (size_t)i ] ][4] / _qbf_pow(r, 2);

    P[ (size_t)B[1][ (size_t)i ] ][1] = P[ (size_t)B[1][ (size_t)i ] ][1] + (a * qbf_sin(angle));
    P[ (size_t)B[1][ (size_t)i ] ][2] = P[ (size_t)B[1][ (size_t)i ] ][2] + (a * qbf_cos(angle));

    if (i == 79 || i == 136 || i == 195 || i == 230) { QBM_gosub(_Q_env, LABEL_166) }

    if (i == 67 && r < 3443500) {
      ELEVangle = angle;
      QBM_gosub(_Q_env, LABEL_8500);
      MARSelev = h;
      r = r - h;
    }

    if (
      B[1][ (size_t)i ] != 28 &&
      B[1][ (size_t)i ] != 32 &&
      B[1][ (size_t)i ] != 38
    ) { goto LABEL_2; }
    if (
      (
        qbf_sgn(difX) !=
          -1 *
          qbf_sgn(
            Vx[ (size_t)B[1][ (size_t)i ] ] - Vx[ (size_t)B[0][ (size_t)i ] ]
          )
      ) ||
      (
        qbf_sgn(difY) !=
          -1 *
          qbf_sgn(
            Vy[ (size_t)B[1][ (size_t)i ] ] - Vy[ (size_t)B[0][ (size_t)i ] ]
          )
      )
    ) { goto LABEL_2; }
    Vhab = qbf_sqr(
      _qbf_pow(Vx[ (size_t)B[1][ (size_t)i ] ] - Vx[ (size_t)B[0][ (size_t)i ] ], 2) +
      _qbf_pow(Vy[ (size_t)B[1][ (size_t)i ] ] - Vy[ (size_t)B[0][ (size_t)i ] ], 2)
    );
    if (r < ts * Vhab) {
      ts = (r - (P[ (size_t)B[0][ (size_t)i ] ][5] / 2)) / Vhab;
    }

    LABEL_2:;
    if (B[1][ (size_t)i ] == 32 && r <= P[ (size_t)B[0][ (size_t)i ] ][5] + P[32][5]) {
      CONflag2 = 1;
      CONflag3 = B[0][ (size_t)i ];
      // ': targ = 32
    }

    if (
      B[1][ (size_t)i ] == 28 &&
      P[ (size_t)B[0][ (size_t)i ] ][10] > -150 &&
      r <= P[ (size_t)B[0][ (size_t)i ] ][5] + P[28][5]
    ) {
      CONflag = 1;
      CONtarg = B[0][ (size_t)i ];
      Dcon = r;
      Acon = angle;
      CONacc = a;
    }

    if (
      B[1][ (size_t)i ] == 28 &&
      B[0][ (size_t)i ] != 32 &&
      r <= P[ (size_t)B[0][ (size_t)i ] ][5] + (1000 * P[ (size_t)B[0][ (size_t)i ] ][10])
    ) {
      atm = B[0][ (size_t)i ];
      Ratm = (r - P[ (size_t)B[0][ (size_t)i ] ][5]) / 1000;
    }

    if (B[1][ (size_t)i ] == 39 && r <= P[ (size_t)B[0][ (size_t)i ] ][5] + P[39][5]) {
      explCENTER = 39;
      QBM_gosub(_Q_env, LABEL_6000);
    }
    if (B[1][ (size_t)i ] == 38 && r <= P[ (size_t)B[0][ (size_t)i ] ][5] + P[38][5]) {
      explCENTER = 38;
      QBM_gosub(_Q_env, LABEL_6000);
    }

    if ((B[1][ (size_t)i ] == 32 && B[0][ (size_t)i ] == 15) && r < 1000000 + P[15][5]) {
      Px[15][3] = 1e30;
      Py[15][3] = 1e30;
    }

    LABEL_5:;
    if (B[0][ (size_t)i ] == targ && B[1][ (size_t)i ] == 28) {
      Atarg = angle;
      Dtarg = r;
      Acctarg = a;
    }

    LABEL_6: __attribute__((unused));
    if (B[0][ (size_t)i ] == ref && B[1][ (size_t)i ] == 28) {
      Vref = qbf_sqr(G * P[ (size_t)B[0][ (size_t)i ] ][4] / r);
      Aref = angle;
      Dref = r;
    }

    if (B[0][ (size_t)i ] == Ltr) {
      LtrA = a;
    }

    if (i == 163) { AYSEdist = r; }
    if (i == 166) { OCESSdist = r; }

    LABEL_106:;
  }

  if (AYSEdist > 320) { AYSE = 0; }

  if (CONflag == 1 && CONtarg == 12) { CONflag = 0.25; }
  // 'IF CONflag = 1 AND CONtarg = 14 THEN 9111

  LABEL_101: __attribute__((unused));
  // 'Record old center position
  cenX = Px[ (size_t)cen ][3] + cenXoff;
  cenY = Py[ (size_t)cen ][3] + cenYoff;

  // 'Erase velocity, approach velocity, and orientation vectors
  if (DISPflag == 0) {
    qb_line(
      _Q_env,
      30,
      120,
      30 + (5 * qbf_sin(Sangle)),
      120 + (5 * qbf_cos(Sangle)),
      0
    );
  }
  if (DISPflag == 0) {
    qb_line(
      _Q_env,
      30,
      120,
      30 + (10 * qbf_sin(Vvangle)),
      120 + (10 * qbf_cos(Vvangle)),
      0
    );
  }
  if (
    qbf_sqr(
      _qbf_pow(((Px[28][3] - cenX) * mag / AU), 2) +
      _qbf_pow(((Py[28][3] - cenY) * mag * 1 / AU), 2)
    ) > 400
  ) { goto LABEL_132; }
  if (vflag == 1) {
    qb_line(
      _Q_env,
      300 + (Px[28][3] - cenX) * mag / AU,
      220 + (Py[28][3] - cenY) * mag * 1 / AU,
      300 + (20 * qbf_sin(Vvangle)) + (Px[28][3] - cenX) * mag / AU,
      220 + (20 * qbf_cos(Vvangle)) + (Py[28][3] - cenY) * mag * 1 / AU,
      0
    );
  }

  // 'Update object velocities and erase old positions
  LABEL_132:;
  for (i = 37 + ufo1 + ufo2; i >= 0; i--) {

    if (i == 28) { QBM_gosub(_Q_env, LABEL_301); }
    if (i == 38) { QBM_gosub(_Q_env, LABEL_7200); }

    VxDEL = Vx[ (size_t)i ] + (P[ (size_t)i ][1] * OLDts);
    VyDEL = Vy[ (size_t)i ] + (P[ (size_t)i ][2] * OLDts);
    if (qbf_sqr(_qbf_pow(VxDEL, 2) + _qbf_pow(VyDEL, 2)) > 299999999.999) { goto LABEL_117; }
    Vx[ (size_t)i ] = VxDEL;
    Vy[ (size_t)i ] = VyDEL;

    LABEL_117:;
    if (i == 36 && MODULEflag == 0) { goto LABEL_108; }

    if (i == 4) { goto LABEL_11811; }

    if (
        qbf_sqr(
          _qbf_pow(((Px[ (size_t)i ][3] - cenX) * mag / AU), 2) +
          _qbf_pow(((Py[ (size_t)i ][3] - cenY) * mag * 1 / AU), 2)
        ) -
        (P[ (size_t)i ][5] * mag / AU)
      > 400
    ) { goto LABEL_108; }

    LABEL_11811:;
    if (cen * tr > 0) { goto LABEL_108; }

    if (mag * P[ (size_t)i ][5] / AU < 1.1) {
      qb_circle(
        _Q_env,
        300 + (Px[ (size_t)i ][3] - cenX) * mag / AU,
        220 + (Py[ (size_t)i ][3] - cenY) * mag / AU,
        1,
        8 * trail
      );
      goto LABEL_108;
    }
    clr = 8 * trail;

    if (i == 28) {
      vnSa = oldSa;
      QBM_gosub(_Q_env, LABEL_128);
      goto LABEL_108;
    }
    if (i == 35) {
      QBM_gosub(_Q_env, LABEL_138);
      goto LABEL_108;
    }
    if (i == 37) {
      QBM_gosub(_Q_env, LABEL_148);
      goto LABEL_108;
    }
    if (i == 32) {
      clrMASK = 0;
      QBM_gosub(_Q_env, LABEL_158);
      goto LABEL_108;
    }
    if (i == 12 && HPdisp == 1) { goto LABEL_108; }

    if (P[ (size_t)i ][5] * mag / AU > 300) { goto LABEL_118; }

    qb_circle(
      _Q_env,
      300 + (Px[ (size_t)i ][3] - cenX) * mag / AU,
      220 + (Py[ (size_t)i ][3] - cenY) * mag * 1 / AU,
      mag * P[ (size_t)i ][5] / AU,
      8 * trail
    );
    goto LABEL_108;

    LABEL_118:;
    difX = cenX - Px[ (size_t)i ][3];
    difY = cenY - Py[ (size_t)i ][3];

    dist = (qbf_sqr(_qbf_pow(difY, 2) + _qbf_pow(difX, 2)) - P[ (size_t)i ][5]) * mag / AU;

    QBM_gosub(_Q_env, LABEL_5000);

    angle = angle * RAD * 160; // '32
    angle = qbf_fix(angle + 0.5) / RAD / 160; // '32

    arcANGLE = pi * 800 / (P[ (size_t)i ][5] * pi2 * mag / AU);
    if (arcANGLE > pi) { arcANGLE = pi; }

    stepANGLE = arcANGLE / 90;

    stepANGLE = RAD * 160 * arcANGLE / 90;
    stepANGLE = qbf_fix(stepANGLE + 1) / RAD / 160;

    ii = angle - (90 * stepANGLE);

    if (i != 4) {
      h = 0;
      goto LABEL_1181;
    }
    ELEVangle = ii;
    QBM_gosub(_Q_env, LABEL_8500);

    LABEL_1181:;
    CirX = Px[ (size_t)i ][3] + ((h + P[ (size_t)i ][5]) * qbf_sin(ii + pi)) - cenX;
    CirX = CirX * mag / AU;
    CirY = Py[ (size_t)i ][3] + ((h + P[ (size_t)i ][5]) * qbf_cos(ii + pi)) - cenY;
    CirY = CirY * mag / AU;
    qb_pset(_Q_env, 300 + CirX, 220 + CirY, 8 * trail);

    startANGLE = angle - (90 * stepANGLE);
    stopANGLE = angle + (90 * stepANGLE);
    QBM_bidifor(ii, startANGLE, stopANGLE, stepANGLE) {
      if (i != 4) {
        h = 0;
        goto LABEL_1182;
      }
      ELEVangle = ii;
      QBM_gosub(_Q_env, LABEL_8500);

      LABEL_1182:;
      CirX = Px[ (size_t)i ][3] + ((h + P[ (size_t)i ][5]) * qbf_sin(ii + pi)) - cenX;
      CirX = CirX * mag / AU;
      CirY = Py[ (size_t)i ][3] + ((h + P[ (size_t)i ][5]) * qbf_cos(ii + pi)) - cenY;
      CirY = CirY * mag / AU;
      qb_lineto(_Q_env, 300 + CirX, 220 + CirY, 8 * trail);
    }

    LABEL_108:;
  }
  goto LABEL_102;

  // 'Paint Habitat
  LABEL_128:;
  qb_circle(
    _Q_env,
    300 + (Px[ (size_t)i ][3] - cenX) * mag / AU,
    220 + (Py[ (size_t)i ][3] - cenY) * mag * 1 / AU,
    mag * P[ (size_t)i ][5] / AU,
    clr
  );
  qb_circle(
    _Q_env,
    300 + (Px[ (size_t)i ][3] - cenX - (P[ (size_t)i ][5] * 0.8 * qbf_sin(vnSa))) * mag / AU,
    220 + (Py[ (size_t)i ][3] - cenY - (P[ (size_t)i ][5] * 0.8 * qbf_cos(vnSa))) * mag * 1 / AU,
    mag * P[ (size_t)i ][5] * 0.2 / AU,
    clr
  );
  qb_circle(
    _Q_env,
    300 + (Px[ (size_t)i ][3] - cenX - (P[ (size_t)i ][5] * 1.2 * qbf_sin(vnSa + 0.84))) * mag / AU,
    220 + (Py[ (size_t)i ][3] - cenY - (P[ (size_t)i ][5] * 1.2 * qbf_cos(vnSa + 0.84))) * mag * 1 / AU,
    mag * P[ (size_t)i ][5] * 0.2 / AU,
    clr
  );
  qb_circle(
    _Q_env,
    300 + (Px[ (size_t)i ][3] - cenX - (P[ (size_t)i ][5] * 1.2 * qbf_sin(vnSa - 0.84))) * mag / AU,
    220 + (Py[ (size_t)i ][3] - cenY - (P[ (size_t)i ][5] * 1.2 * qbf_cos(vnSa - 0.84))) * mag * 1 / AU,
    mag * P[ (size_t)i ][5] * 0.2 / AU,
    clr
  );
  _qb_gosub_return(_Q_env);

  // 'Paint ISS
  LABEL_138:;
  for (j = 215; j <= 227; j += 2) {
    qb_linebox(
      _Q_env,
      300 + (Px[ (size_t)i ][3] - cenX + panel[0][ (size_t)j ]) * mag / AU,
      220 + (Py[ (size_t)i ][3] - cenY + panel[1][ (size_t)j ]) * mag * 1 / AU,
      300 + (Px[ (size_t)i ][3] - cenX + panel[0][ (size_t)j + 1 ]) * mag / AU,
      220 + (Py[ (size_t)i ][3] - cenY + panel[1][1 + (size_t)j ]) * mag * 1 / AU,
      clr,
      QB_LINE_BOX_B
    );
  }
  _qb_gosub_return(_Q_env);

  // 'Paint OCESS
  LABEL_148:;
  qb_pset(
    _Q_env,
    300 + (((Px[37][3] + panel[0][229]) - cenX) * mag / AU),
    220 + (((Py[37][3] + panel[1][229]) - cenY) * mag / AU),
    clr
  );
  for (j = 230; j <= 238; j++) {
    qb_lineto(
      _Q_env,
      300 + (((Px[37][3] + panel[0][ (size_t)j ]) - cenX) * mag / AU),
      220 + (((Py[37][3] + panel[1][ (size_t)j ]) - cenY) * mag / AU),
      clr
    );
  }
  _qb_gosub_return(_Q_env);

  // 'Paint AYSE
  LABEL_158:;
  Ax1 = Px[32][3] + (500 * qbf_sin(AYSEangle + 0.19 + pi));
  Ax2 = Px[32][3] + (500 * qbf_sin(AYSEangle - 0.19 + pi));
  Ay1 = Py[32][3] + (500 * qbf_cos(AYSEangle + 0.19 + pi));
  Ay2 = Py[32][3] + (500 * qbf_cos(AYSEangle - 0.19 + pi));
  Ax3 = Px[32][3] + (95 * qbf_sin(AYSEangle + (pi / 2)));
  Ax4 = Px[32][3] + (95 * qbf_sin(AYSEangle - (pi / 2)));
  Ay3 = Py[32][3] + (95 * qbf_cos(AYSEangle + (pi / 2)));
  Ay4 = Py[32][3] + (95 * qbf_cos(AYSEangle - (pi / 2)));
  Ax8 = Px[32][3] + (100095.3 * qbf_sin(AYSEangle + 1.5732935));
  Ay8 = Py[32][3] + (100095.3 * qbf_cos(AYSEangle + 1.5732935));
  Ax9 = Px[32][3] + (100095.3 * qbf_sin(AYSEangle - 1.5732935));
  Ay9 = Py[32][3] + (100095.3 * qbf_cos(AYSEangle - 1.5732935));

  LABEL_159: __attribute__((unused));
  Ad1 = qbf_sqr(
    _qbf_pow((Px[28][3] - Ax8), 2) +
    _qbf_pow((Py[28][3] - Ay8), 2)
  );
  Ad2 = qbf_sqr(
    _qbf_pow((Px[28][3] - Ax9), 2) +
    _qbf_pow((Py[28][3] - Ay9), 2)
  );
  Ad3 = qbf_sqr(
    _qbf_pow((Px[28][3] - Ax1), 2) +
    _qbf_pow((Py[28][3] - Ay1), 2)
  );
  clr1 = 2;
  clr2 = 2;
  if (Ad2 < 100090) { clr1 = 14; }
  if (Ad2 < 100085) { clr1 = 4; }
  if (Ad1 < 100090) { clr2 = 14; }
  if (Ad1 < 100085) { clr2 = 4; }
  if (Ad1 > 100080 && Ad2 > 100080 && Ad3 < 501) { goto LABEL_156; }
  if (AYSEdist > 580) { goto LABEL_156; }
  AYSEscrape = 10;
  Vx[28] = Vx[32];
  Vy[28] = Vy[32];
  if (Ad3 > 501) {
    Px[28][3] = Px[32][3];
    Py[28][3] = Py[32][3];
    goto LABEL_157;
  }
  P[28][1] = Px[32][3] + (AYSEdist * qbf_sin(AYSEangle - 3.1415926));
  P[28][2] = Py[32][3] + (AYSEdist * qbf_cos(AYSEangle - 3.1415926));
  LABEL_157:;
  QBM_gosub(_Q_env, LABEL_405);
  CONflag = 0;

  LABEL_156:;
  if (AYSEdist < 5) {
    clr = 10;
  } else {
    clr = 12;
  }
  qb_pset(
    _Q_env,
    300 + ((Ax1 - cenX) * mag / AU),
    220 + ((Ay1 - cenY) * mag / AU),
    12
  );
  for (j = -2.9; j <= 2.9; j += 0.2) {
    x = Px[32][3] + (500 * qbf_sin(j + AYSEangle));
    y = Py[32][3] + (500 * qbf_cos(j + AYSEangle));
    qb_lineto(
      _Q_env,
      300 + ((x - cenX) * mag / AU),
      220 + ((y - cenY) * mag / AU),
      12
    );
  }
  qb_lineto(
    _Q_env,
    300 + ((Ax2 - cenX) * mag / AU),
    220 + ((Ay2 - cenY) * mag / AU),
    12
  );
  qb_pset(
    _Q_env,
    300 + ((Ax4 - cenX) * mag / AU),
    220 + ((Ay4 - cenY) * mag / AU),
    12
  );
  for (j = -1.5; j <= 1.5; j += 0.2) {
    x = Px[32][3] + (95 * qbf_sin(j + AYSEangle));
    y = Py[32][3] + (95 * qbf_cos(j + AYSEangle));
    qb_lineto(
      _Q_env,
      300 + ((x - cenX) * mag / AU),
      220 + ((y - cenY) * mag / AU),
      12
    );
  }
  qb_lineto(
    _Q_env,
    300 + ((Ax3 - cenX) * mag / AU),
    220 + ((Ay3 - cenY) * mag / AU),
    12
  );
  qb_line(
    _Q_env,
    300 + ((Ax1 - cenX) * mag / AU),
    220 + ((Ay1 - cenY) * mag / AU),
    300 + ((Ax4 - cenX) * mag / AU),
    220 + ((Ay4 - cenY) * mag / AU),
    12 * clrMASK
  );
  qb_line(
    _Q_env,
    300 + ((Ax2 - cenX) * mag / AU),
    220 + ((Ay2 - cenY) * mag / AU),
    300 + ((Ax3 - cenX) * mag / AU),
    220 + ((Ay3 - cenY) * mag / AU),
    12 * clrMASK
  );
  if (mag < 5e+9) { goto LABEL_154; }
  qb_circle(
    _Q_env,
    300 + ((Ax1 - cenX) * mag / AU),
    220 + ((Ay1 - cenY) * mag / AU),
    2,
    clr1 * clrMASK
  );
  qb_circle(
    _Q_env,
    300 + ((Ax1 - cenX) * mag / AU),
    220 + ((Ay1 - cenY) * mag / AU),
    1,
    clr1 * clrMASK
  );
  LABEL_154:;
  if (mag < 5e+9) { goto LABEL_153; }
  qb_circle(
    _Q_env,
    300 + ((Ax2 - cenX) * mag / AU),
    220 + ((Ay2 - cenY) * mag / AU),
    2,
    clr2 * clrMASK
  );
  qb_circle(
    _Q_env,
    300 + ((Ax2 - cenX) * mag / AU),
    220 + ((Ay2 - cenY) * mag / AU),
    1,
    clr2 * clrMASK
  );
  LABEL_153:;
  _qb_gosub_return(_Q_env);

  LABEL_160:;
  if (mag < 2500000) { _qb_gosub_return(_Q_env); }
  if (mag > 13812331090.38165) { mag = 13812331090.38165; }
  if (mag > 4000000000.0) {
    st = 241;
  } else {
    st = 239;
  }
  if (HPdisp == 1) { goto LABEL_165; }
  qb_cls(_Q_env);
  if (cen != 12) {
    cenXoff = Px[ (size_t)cen ][3] - Px[12][3];
    cenYoff = Py[ (size_t)cen ][3] - Py[12][3];
  }
  cen = 12;
  HPdisp = 1;
  QBM_bidifor(j, st, 265, 1) {
    P1x = 300 + (((Px[12][3] + (P[12][5] * panel[1][ (size_t)j ])) - cenX) * mag / AU);
    P1y = 220 + (((Py[12][3] + (P[12][5] * panel[2][ (size_t)j ])) - cenY) * mag / AU);
    Px2 = P1x;
    Py2 = P1y;
    if (Px2 < 0) { Px2 = 0; }
    if (Px2 > 639) { Px2 = 639; }
    if (Py2 < 0) { Py2 = 0; }
    if (Py2 > 479) { Py2 = 479; }
    dist = qbf_sqr(_qbf_pow((Px2 - P1x), 2) + _qbf_pow((Py2 - P1y), 2));
    if (dist > (mag * (panel[0][ (size_t)j ] * P[12][5]) / AU) - 1) { goto LABEL_164; }
    qb_circle(
      _Q_env,
      P1x,
      P1y,
      (mag * P[12][5] * panel[0][ (size_t)j ] / AU),
      15
    );
    qb_paint(_Q_env, Px2, Py2, 0, 15);
    qb_paint(_Q_env, Px2, Py2, 7, 15);
    qb_circle(
      _Q_env,
      P1x,
      P1y,
      (mag * P[12][5] * panel[0][ (size_t)j ] / AU),
      7
    );
    LABEL_164:;
  }
  if (DISPflag == 0) {
    qb_locate(_Q_env, 7, 2);
    qb_stdprint_str_const(_Q_env, "      ", 6, FALSE);
    qb_locate(_Q_env, 8, 2);
    qb_stdprint_str_const(_Q_env, "      ", 6, FALSE);
    qb_locate(_Q_env, 9, 2);
    qb_stdprint_str_const(_Q_env, "      ", 6, FALSE);
  }
  if (DISPflag == 0) { QBM_gosub(_Q_env, LABEL_400); }
  LABEL_165:;
  _qb_gosub_pop(_Q_env); goto LABEL_109;

  // 'Landing on Hyperion
  LABEL_166:;
  Rmin = 1e+26;
  AtargPRIME = angle;
  if (ref == 12 && B[1][ (size_t)i ] == 28) {
    Vref = qbf_sqr(G * P[ (size_t)B[0][ (size_t)i ] ][4] / r);
    Aref = angle;
    Dref = r;
  }
  if (Ltr == 12) { LtrA = a; }
  for (j = 241; j <= 265; j++) {
    Px2 = (Px[12][3] + (P[12][5] * panel[1][ (size_t)j ]));
    Py2 = (Py[12][3] + (P[12][5] * panel[2][ (size_t)j ]));
    Rcrit = (P[12][5] * panel[0][ (size_t)j ]) + P[ (size_t)B[1][ (size_t)i ] ][5];
    difX = Px[ (size_t)B[1][ (size_t)i ] ][3] - Px2;
    difY = Py[ (size_t)B[1][ (size_t)i ] ][3] - Py2;
    r = qbf_sqr(_qbf_pow(difY, 2) + _qbf_pow(difX, 2));
    if (r - Rcrit < Rmin) {
      Rmin = r - Rcrit;
      rD = r;
      PH5prime = P[12][5] * panel[0][ (size_t)j ];
    }
    if (r > Rcrit) { goto LABEL_167; }
    if (i == 136) {
      CONflag2 = 1;
      CONflag3 = 12;
      _qb_gosub_pop(_Q_env); goto LABEL_5; // ' targ = 32: RETURN 5
    }
    if (i == 230) {
      explCENTER = 39;
      QBM_gosub(_Q_env, LABEL_6000);
      _qb_gosub_pop(_Q_env); goto LABEL_5;
    }
    if (i == 195) {
      explCENTER = 39;
      QBM_gosub(_Q_env, LABEL_6000);
      _qb_gosub_pop(_Q_env); goto LABEL_5;
    }
    CONflag = 1;
    Acon1 = angle;
    CONacc = a;
    RcritL2 = P[12][5] - PH5prime;
    Vx[28] = Vx[12];
    Vy[28] = Vy[12];
    QBM_gosub(_Q_env, LABEL_5000);
    CONflag = 1;
    CONtarg = 12;
    Dcon = r;
    Acon = angle;
    if (r >= Rcrit - 0.5) { goto LABEL_169; }
    eng = 0;
    explFLAG1 = 1;
    Px[28][3] = Px2 + ((Rcrit - 0.1) * qbf_sin(Acon + 3.1415926));
    Py[28][3] = Py2 + ((Rcrit - 0.1) * qbf_cos(Acon + 3.1415926));
    LABEL_169:;
    if (qbf_cos(Acon - Acon1) > 0) { goto LABEL_168; }
    Px[28][3] = Px2 + ((Rcrit + 0.1) * qbf_sin(Acon + 3.1415926));
    Py[28][3] = Py2 + ((Rcrit + 0.1) * qbf_cos(Acon + 3.1415926));
    goto LABEL_168;
    LABEL_167:;
  }
  LABEL_168:;
  if (i == 79 && targ == 12) {
    Dtarg = rD;
    RcritL = P[12][5] - PH5prime;
    Atarg = AtargPRIME;
    Acctarg = a;
  }
  _qb_gosub_pop(_Q_env); goto LABEL_106;

  // 'Detect contact with an object
  LABEL_102:;
  if (CONflag == 0) { goto LABEL_112; }
  MATCHaacc = 0;
  CONSTacc = 0;
  vector = qbf_cos(THRUSTangle - Acon);
  if (CONtarg > 37) {
    ufo2 = 0;
    explFLAG1 = 1;
    eng = 0;
    targ = ref;
    goto LABEL_112;
  }
  if (
    ((Dcon - P[ (size_t)CONtarg ][5] - P[28][5] + RcritL2) <= 0) &&
    ((Aacc + Av + Are) * vector < CONacc * 1.01)
  ) {
    Vx[28] = Vx[ (size_t)CONtarg ];
    Vy[28] = Vy[ (size_t)CONtarg ];
  }
  if (CONtarg == 12) { goto LABEL_112; }
  if (vector >= 0) { goto LABEL_193; }
  Pvx = P[ (size_t)CONtarg ][4];
  if (Pvx < 1) { Pvx = 1; }
  Vx[ (size_t)CONtarg ] = Vx[ (size_t)CONtarg ] + (THRUSTx * ts * HABmass / Pvx);
  Vx[28] = Vx[ (size_t)CONtarg ];
  Vy[ (size_t)CONtarg ] = Vy[ (size_t)CONtarg ] + (THRUSTy * ts * HABmass / Pvx);
  Vy[28] = Vy[ (size_t)CONtarg ];
  LABEL_193:;
  if ((Dcon - P[ (size_t)CONtarg ][5] - P[28][5]) > -0.5) { goto LABEL_112; }
  LABEL_194: __attribute__((unused));
  eng = 0;
  ALTdel = 0;
  if (CONtarg == 4) { ALTdel = MARSelev; }
  Px[28][3] = Px[ (size_t)CONtarg ][3] + ((P[ (size_t)CONtarg ][5] + P[28][5] - 0.1 + ALTdel) * qbf_sin(Acon + 3.1415926));
  Py[28][3] = Py[ (size_t)CONtarg ][3] + ((P[ (size_t)CONtarg ][5] + P[28][5] - 0.1 + ALTdel) * qbf_cos(Acon + 3.1415926));
  explFLAG1 = 1;

  // 'Docked with AYSE drive module
  LABEL_112:;
  explFLAG2 = 0;
  if (AYSE == 150) {
    Vx[32] = Vx[28];
    Vy[32] = Vy[28];
    Px[32][3] = Px[28][3];
    Py[32][3] = Py[28][3];
    AYSEangle = Sangle;
  }
  if (CONflag2 == 1 && CONflag4 == 0) {
    CONflag4 = 1;
    explFLAG2 = 1;
  }
  if (CONflag2 == 1 && CONflag3 < 38) {
    Vx[32] = Vx[ (size_t)CONflag3 ];
    Vy[32] = Vy[ (size_t)CONflag3 ];
  }

  // 'Update object positions
  for (i = 0; i <= 37 + ufo1 + ufo2; i++) {
    Px[ (size_t)i ][3] = Px[ (size_t)i ][3] + (Vx[ (size_t)i ] * ts);
    Py[ (size_t)i ][3] = Py[ (size_t)i ][3] + (Vy[ (size_t)i ] * ts);
  }

  if (ts > 10) { QBM_gosub(_Q_env, LABEL_3100); }
  if (MODULEflag > 0) {
    Px[36][3] = P[36][1] + Px[ (size_t)MODULEflag ][3];
    Py[36][3] = P[36][2] + Py[ (size_t)MODULEflag ][3];
    Vx[36] = Vx[ (size_t)MODULEflag ];
    Vy[36] = Vy[ (size_t)MODULEflag ];
  }
  Px[37][3] = 4446370.8284487 + Px[3][3];
  Py[37][3] = 4446370.8284487 + Py[3][3];
  Vx[37] = Vx[3];
  Vy[37] = Vy[3];

  // 'Record new center position
  OLDcenX = cenX;
  OLDcenY = cenY;
  cenX = Px[ (size_t)cen ][3] + cenXoff;
  cenY = Py[ (size_t)cen ][3] + cenYoff;

  // 'Repaint objects to the screen
  LABEL_111: __attribute__((unused));
  for (i = 37 + ufo1 + ufo2; i >= 0; i--) {
    if (i == 36 && MODULEflag == 0) { goto LABEL_109; }
    if (i == 4) { goto LABEL_11911; }
    if (
        qbf_sqr(
          _qbf_pow(((Px[ (size_t)i ][3] - cenX) * mag / AU), 2) +
          _qbf_pow(((Py[ (size_t)i ][3] - cenY) * mag * 1 / AU), 2)
        ) -
        (P[ (size_t)i ][5] * mag / AU)
      > 400
    ) { goto LABEL_109; }

    LABEL_11911:;
    pld = 0;
    if (i == 28) { pld = 2 * qbf_abs(qbf_sgn(eng)); }
    if (mag * P[ (size_t)i ][5] / AU < 1.1) {
      qb_circle(
        _Q_env,
        300 + (Px[ (size_t)i ][3] - cenX) * mag / AU,
        220 + (Py[ (size_t)i ][3] - cenY) * mag * 1 / AU,
        1,
        P[ (size_t)i ][0] + pld
      );
      goto LABEL_109;
    }
    if (i == 28) {
      clr = 12 + pld;
      vnSa = Sangle;
      QBM_gosub(_Q_env, LABEL_128);
      goto LABEL_109;
    }
    if (i == 35) {
      clr = 12;
      QBM_gosub(_Q_env, LABEL_138);
      goto LABEL_109;
    }
    if (i == 37) {
      clr = 12;
      QBM_gosub(_Q_env, LABEL_148);
      goto LABEL_109;
    }
    if (i == 32) {
      clrMASK = 1;
      QBM_gosub(_Q_env, LABEL_158);
      goto LABEL_109;
    }
    if (i == 12) { QBM_gosub(_Q_env, LABEL_160); }
    if (P[ (size_t)i ][5] * mag / AU > 300) { goto LABEL_119; }
    qb_circle(
      _Q_env,
      300 + (Px[ (size_t)i ][3] - cenX) * mag / AU,
      220 + (Py[ (size_t)i ][3] - cenY) * mag * 1 / AU,
      mag * P[ (size_t)i ][5] / AU,
      P[ (size_t)i ][0] + pld
    );
    goto LABEL_109;

    LABEL_119:;
    difX = cenX - Px[ (size_t)i ][3];
    difY = cenY - Py[ (size_t)i ][3];
    dist = (qbf_sqr(_qbf_pow(difY, 2) + _qbf_pow(difX, 2)) - P[ (size_t)i ][5]) * mag / AU;
    QBM_gosub(_Q_env, LABEL_5000);

    angle = angle * RAD * 160;
    angleALT = angle;
    angle = qbf_fix(angle + 0.5) / RAD / 160;
    arcANGLE = pi * 800 / (P[ (size_t)i ][5] * pi2 * mag / AU);
    if (arcANGLE > pi) { arcANGLE = pi; }

    stepANGLE = RAD * 160 * arcANGLE / 90;
    stepANGLE = qbf_fix(stepANGLE + 1) / RAD / 160;
    ii = angle - (90 * stepANGLE);
    if (i != 4) {
      h = 0;
      goto LABEL_1191;
    }
    ELEVangle = ii;
    QBM_gosub(_Q_env, LABEL_8500);

    LABEL_1191:;
    CirX = Px[ (size_t)i ][3] + ((h + P[ (size_t)i ][5]) * qbf_sin(ii + pi)) - cenX;
    CirX = CirX * mag / AU;
    CirY = Py[ (size_t)i ][3] + ((h + P[ (size_t)i ][5]) * qbf_cos(ii + pi)) - cenY;
    CirY = CirY * mag / AU;
    qb_pset(
      _Q_env,
      300 + CirX,
      220 + CirY,
      P[ (size_t)i ][0]
    );

    startANGLE = angle - (90 * stepANGLE);
    stopANGLE = angle  +  (90 * stepANGLE);
    QBM_bidifor(ii, startANGLE, stopANGLE, stepANGLE) {
      if (i != 4) {
        h = 0;
        goto LABEL_1192;
      }
      ELEVangle=ii;
      QBM_gosub(_Q_env, LABEL_8500);

      LABEL_1192:;
      CirX = Px[ (size_t)i ][3] + ((h + P[ (size_t)i ][5]) * qbf_sin(ii + pi)) - cenX;
      CirX = CirX * mag / AU;
      CirY = Py[ (size_t)i ][3] + ((h + P[ (size_t)i ][5]) * qbf_cos(ii + pi)) - cenY;
      CirY = CirY * mag / AU;
      qb_lineto(
        _Q_env,
        300 + CirX,
        220 + CirY,
        P[ (size_t)i ][0]
      );
    }

    LABEL_109:;
  }

  // 'Calculate parameters for landing target
  if (targ < 40) { goto LABEL_179; }
  if (qbf_sqr(
      _qbf_pow(((Px[40][3] - OLDcenX) * mag / AU), 2) +
      _qbf_pow(((Py[40][3] - OLDcenY) * mag * 1 / AU), 2)
    ) < 401) {
    qb_pset(
      _Q_env,
      300 + (Px[40][3] - OLDcenX) * mag / AU,
      220 + (Py[40][3] - OLDcenY) * mag * 1 / AU,
      8 * trail
    );
  }
  Px[40][3] = Px[ (size_t)Ltr ][3] + Ltx;
  Py[40][3] = Py[ (size_t)Ltr ][3] + Lty;
  if (
    qbf_sqr(
      _qbf_pow(((Px[40][3] - cenX) * mag / AU), 2) +
      _qbf_pow(((Py[40][3] - cenY) * mag * 1 / AU), 2)
    ) < 401
  ) {
    qb_pset(
      _Q_env,
      300 + (Px[40][3] - cenX) * mag / AU,
      220 + (Py[40][3] - cenY) * mag * 1 / AU,
      14
    );
  }
  Vx[40] = Vx[ (size_t)Ltr ];
  Vy[40] = Vy[ (size_t)Ltr ];
  difX = Px[28][3] - Px[40][3];
  difY = Py[28][3] - Py[40][3];
  Dtarg = qbf_sqr(_qbf_pow(difY, 2) + _qbf_pow(difX, 2));
  QBM_gosub(_Q_env, LABEL_5000);
  Atarg = angle;
  if (Dtarg == 0) { goto LABEL_179; }
  Acctarg = LtrA + (
    (
      _qbf_pow(Vx[28] - Vx[ (size_t)targ ], 2) +
      _qbf_pow(Vy[28] - Vy[ (size_t)targ ], 2)
    ) / (2 * Dtarg)
  );

  LABEL_179:;
  oldSa = Sangle;

  // 'Calculate angle from target to reference object
  if (targ == ref) {
    Atargref = 0;
    goto LABEL_114;
  }
  difX = Px[ (size_t)targ ][3] - Px[ (size_t)ref ][3];
  difY = Py[ (size_t)targ ][3] - Py[ (size_t)ref ][3];
  r = qbf_sqr(_qbf_pow(difY, 2) + _qbf_pow(difX, 2));
  QBM_gosub(_Q_env, LABEL_5000);
  Atr = angle;
  Atargref = qbf_abs(angle - Aref);
  if (Atargref > 3.1415926535) { Atargref = 6.283185307 - Atargref; }

  // 'Re-paint target vector
  LABEL_114:;
  if (DISPflag == 0) {
    qb_line(
      _Q_env,
      30,
      120,
      30 + (20 * qbf_sin(Atarg)),
      120 + (20 * qbf_cos(Atarg)),
      8
    );
  }

  // 'Repaint velocity and orientation vectors
  difX = Vx[ (size_t)targ ] - Vx[28];
  difY = Vy[ (size_t)targ ] - Vy[28];
  QBM_gosub(_Q_env, LABEL_5000);
  Vvangle = angle;

  if (DISPflag == 0) {
    qb_line(
      _Q_env,
      30,
      120,
      30 + (10 * qbf_sin(Vvangle)),
      120 + (10 * qbf_cos(Vvangle)),
      12
    );
  }
  if (DISPflag == 0) {
    qb_line(
      _Q_env,
      30,
      120,
      30 + (5 * qbf_sin(Sangle)),
      120 + (5 * qbf_cos(Sangle)),
      10
    );
  }
  if (DISPflag == 0) { qb_pset(_Q_env, 30, 120, 1); }
  if (
    qbf_sqr(
      _qbf_pow((Px[28][3] - cenX) * mag / AU, 2) +
      _qbf_pow((Py[28][3] - cenY) * mag * 1 / AU, 2)
    ) > 400
  ) { goto LABEL_133; }
  if (vflag == 1) {
    qb_line(
      _Q_env,
      300 + (Px[28][3] - cenX) * mag / AU,
      220 + (Py[28][3] - cenY) * mag * 1 / AU,
      300 + (30 * qbf_sin(Atarg)) + (Px[28][3] - cenX) * mag / AU,
      220 + (30 * qbf_cos(Atarg)) + (Py[28][3] - cenY) * mag * 1 / AU,
      8
    );
  }
  if (vflag == 1) {
    qb_line(
      _Q_env,
      300 + (Px[28][3] - cenX) * mag / AU,
      220 + (Py[28][3] - cenY) * mag * 1 / AU,
      300 + (20 * qbf_sin(Vvangle)) + (Px[28][3] - cenX) * mag / AU,
      220 + (20 * qbf_cos(Vvangle)) + (Py[28][3] - cenY) * mag * 1 / AU,
      12
    );
  }
  if (vflag == 1) {
    qb_line(
      _Q_env,
      300 + (Px[28][3] - cenX) * mag / AU,
      220 + (Py[28][3] - cenY) * mag * 1 / AU,
      300 + (10 * qbf_sin(Sangle)) + (Px[28][3] - cenX) * mag / AU,
      220 + (10 * qbf_cos(Sangle)) + (Py[28][3] - cenY) * mag * 1 / AU,
      10
    );
  }
  LABEL_133:;
  VangleDIFF = Atarg - Vvangle;

  // 'Cause explosion
  if (Ztel[5] == 1) {
    Ztel[5] = 0;
    explFLAG1 = 1;
    explosion = 0;
  }
  if (Ztel[6] == 1) {
    Ztel[6] = 0;
    explFLAG2 = 1;
    explosion1 = 0;
  }
  if (explFLAG1 == 1 && explosion == 0) {
    explCENTER = 28;
    QBM_gosub(_Q_env, LABEL_6000);
  }
  if (explFLAG2 == 1 && explosion1 == 0) {
    explCENTER = 32;
    QBM_gosub(_Q_env, LABEL_6000);
  }

  // 'Update simulation time
  sec = sec + ts;
  if (sec > 60) {
    min = min + 1;
    sec = sec - 60;
  }
  if (min == 60) {
    hr = hr + 1;
    min = 0;
    }
  if (hr == 24) {
    day = day + 1;
    hr = 0;
  }
  dayNUM = 365;
  if (qbf_int(year / 4) * 4 == year) { dayNUM = 366; }
  if (qbf_int(year / 100) * 100 == year) { dayNUM = 365; }
  if (qbf_int(year / 400) * 400 == year) { dayNUM = 366; }
  if (day == dayNUM + 1) {
    year = year + 1;
    day = 1;
  }

  if (dte == 0) { goto LABEL_121; }
  if (dte > 1) {
    QBM_gosub(_Q_env, LABEL_8100);
    goto LABEL_121;
  }
  qb_locate(_Q_env, 25, 58);
  qb_stdprint_str_const(_Q_env, "   ", 3, FALSE);
  QBM_std_pu_const_double(_Q_env, "####_ ", 6, year, FALSE);
  qb_locate(_Q_env, 25, 66);
  {
    QBPUI *_Q_ps = _qb_get_pu_ctx();
    _Q_ps = _qb_pu_add_double(_Q_ps, day, FALSE);
    _Q_ps = _qb_pu_add_double(_Q_ps, hr, FALSE);
    _Q_ps = _qb_pu_add_double(_Q_ps, min, FALSE);
    qb_stdprintusing_const(_Q_env, "###", 3, _Q_ps);
  }
  if (ts < 60) {
    qb_locate(_Q_env, 25, 75);
    QBM_std_pu_const_double(_Q_env, "###", 3, sec, FALSE);
  }

  // 'Print Simulation data
  LABEL_121:;
  if (targ == 40) { goto LABEL_123; }
  if (qbf_cos(VangleDIFF) != 0 && Dtarg - P[ (size_t)targ ][5] != 0) {
    Acctarg = Acctarg + (
      (
        (_qbf_pow(Vx[28] - Vx[ (size_t)targ ], 2) + _qbf_pow(Vy[28] - Vy[ (size_t)targ ], 2)) /
        (2 * (Dtarg - P[ (size_t)targ ][5]))
      ) * qbf_cos(VangleDIFF)
    );
  }
  LABEL_123:;
  oldAcctarg = Acctarg;
  if (DISPflag == 1) { goto LABEL_113; }
  qb_color(_Q_env, 12);
  qb_locate(_Q_env, 23, 8);
  if (Ztel[17] == 1) {
    qb_stdprint_str_const(_Q_env, "P", 1, FALSE);
  } else {
    qb_stdprint_str_const(_Q_env, " ", 1, FALSE);
  }
  qb_locate(_Q_env, 24, 8);
  if (PROBEflag == 1) {
    qb_stdprint_str_const(_Q_env, "L", 1, FALSE);
  } else {
    qb_stdprint_str_const(_Q_env, " ", 1, FALSE);
  }
  qb_locate(_Q_env, 8, 16);
  if (CONSTacc == 1) {
    QBM_new_str(_Q_tmp);
    qbf_chr_str_direct(&_Q_tmp, 67 + (10 * MATCHacc));
    qb_stdprint_str(_Q_env, _Q_tmp, FALSE);
    _qb_free_str(&_Q_tmp);
  } else {
    qb_stdprint_str_const(_Q_env, " ", 1, FALSE);
  }
  qb_color(_Q_env, 15);
  targDISP = 1;
  if (LOS + RADAR + INS == 0) { targDISP = 0; }
  if (LOS + INS == 0 && Dtarg > 1e+9) { targDISP = 0; }
  if (targDISP == 0) { goto LABEL_129; }
  qb_locate(_Q_env, 2, 12);
  if ((64 & (int32_t)NAVmalf) == 64) {
    qb_stdprint_str_const(_Q_env, "-----------", 11, FALSE);
    goto LABEL_143;
  }
  if (Vref > 9999999) {
    QBM_std_pu_const_double(_Q_env, "##.####^^^^", 11, Vref, FALSE);
  } else {
    QBM_std_pu_const_double(_Q_env, "########.##", 11, Vref, FALSE);
  }
  LABEL_143:;
  Vrefhab = qbf_sqr(
    _qbf_pow(Vx[28] - Vx[ (size_t)ref ], 2) +
    _qbf_pow(Vy[28] - Vy[ (size_t)ref ], 2)
  );
  qb_locate(_Q_env, 3, 12);
  if (Vrefhab > 9999999) {
    QBM_std_pu_const_double(_Q_env, "##.####^^^^", 11, Vrefhab, FALSE);
  } else {
    QBM_std_pu_const_double(_Q_env, "########.##", 11, Vrefhab, FALSE);
  }
  Vreftarg = qbf_sqr(
    _qbf_pow(Vx[ (size_t)targ ] - Vx[ (size_t)ref ], 2) +
    _qbf_pow(Vy[ (size_t)targ ] - Vy[ (size_t)ref ], 2)
  );
  qb_locate(_Q_env, 4, 12);
  if (Vreftarg > 9999999) {
    QBM_std_pu_const_double(_Q_env, "##.####^^^^", 11, Vreftarg, FALSE);
  } else {
    QBM_std_pu_const_double(_Q_env, "########.##", 11, Vreftarg, FALSE);
  }
  qb_locate(_Q_env, 14, 7);
  if ((32 & (int32_t)NAVmalf) == 32) {
    qb_stdprint_str_const(_Q_env, "---------", 9, FALSE);
    goto LABEL_144;
  }
  if (qbf_abs(Acctarg) > 9999) {
    QBM_std_pu_const_double(_Q_env, "##.##^^^^", 9, Acctarg, FALSE);
  } else {
    QBM_std_pu_const_double(_Q_env, "######.##", 9, Acctarg, FALSE);
  }
  LABEL_144:;
  qb_locate(_Q_env, 13, 2);
  Dfactor = 1000;
  if (Dtarg > 9.9e+11) {
    _qb_set_str_const(&zDISP_str, "##.########^^^^", 15);
    goto LABEL_125;
  }
  if (INS == 0) {
    _qb_set_str_const(&zDISP_str, "#########_00.000", 16);
    Dfatctor = 100000;
  } else {
    _qb_set_str_const(&zDISP_str, "##########_0.000", 16);
    Dfactor = 10000;
  }
  if (RADAR == 2 && Dtarg < 1e+9) {
    _qb_set_str_const(&zDISP_str, "###########.###", 15);
    Dfactor = 1000;
  }
  LABEL_125:;
  QBM_std_pu_double(
    _Q_env,
    zDISP_str,
    (Dtarg - P[ (size_t)targ ][5] - P[28][5] + RcritL) / Dfactor,
    FALSE
  );
  qb_locate(_Q_env, 15, 9);
  QBM_std_pu_const_double(_Q_env, "####.##", 7, Atargref * RAD, FALSE);
  LABEL_129:;
  if (Cdh > 0.0005) { qb_color(_Q_env, 14); }
  qb_locate(_Q_env, 7, 8);
  if (Cdh < 0.0005) {
    QBM_std_pu_const_double(_Q_env, "#####.###", 9, Are, FALSE);
  } else {
    QBM_std_pu_const_double(_Q_env, "#####.##", 8, Are, FALSE);
    qb_stdprint_str_const(_Q_env, "P", 1, FALSE);
  }
  qb_color(_Q_env, 15);
  qb_locate(_Q_env, 8, 8);
  QBM_std_pu_const_double(_Q_env, "#####.##", 8, Aacc, FALSE);
  qb_locate(_Q_env, 11, 6);
  if (Dfuel == 0) {
    qb_stdprint_str_const(_Q_env, "H", 1, FALSE);
    QBM_std_pu_const_double(_Q_env, "#########", 9, fuel, FALSE);
    {
      QBM_new_str(_Q_tmp);
      qbf_chr_str_direct(&_Q_tmp, 32 + (refuel * 11) + (ventfuel * 13));
      qb_stdprint_str(_Q_env, _Q_tmp, FALSE);
      _qb_free_str(&_Q_tmp);
    }
  }
  if (Dfuel == 1) {
    qb_stdprint_str_const(_Q_env, "A", 1, FALSE);
    QBM_std_pu_const_double(_Q_env, "#########", 9, AYSEfuel, FALSE);
    {
      QBM_new_str(_Q_tmp);
      qbf_chr_str_direct(&_Q_tmp, 32 + (AYSErefuel * 11) + (AYSEventfuel * 13));
      qb_stdprint_str(_Q_env, _Q_tmp, FALSE);
      _qb_free_str(&_Q_tmp);
    }
  }
  if (Dfuel == 2) {
    qb_stdprint_str_const(_Q_env, "RCS", 3, FALSE);
    QBM_std_pu_const_float(_Q_env, "#######", 7, vernP_float, FALSE);
  }
  qb_locate(_Q_env, 18, 9);
  if ((16 & (int32_t)NAVmalf) == 16) {
    qb_stdprint_str_const(_Q_env, "-------", 7, FALSE);
    goto LABEL_124;
  }
  QBM_std_pu_const_double(_Q_env, "####.##", 7, DIFFangle, FALSE);

  LABEL_124:;
  qb_color(_Q_env, 15);
  QBM_gosub(_Q_env, LABEL_3005);
  QBM_gosub(_Q_env, LABEL_3008);
  QBM_gosub(_Q_env, LABEL_3006);

  LABEL_113:;
  // 'Timed back-up
  if (bkt - qbf_timer() > 120) { bkt = qbf_timer(); }
  if (bkt + 1 < qbf_timer()) {
    bkt = qbf_timer();
    QBM_gosub(_Q_env, LABEL_800);
  }
  if (ufo2 == 1) { Px[39][1] = Px[39][1] - 1; }
  if (ufo2 == 1 && Px[39][1] < 1) {
    explCENTER = 39;
    QBM_gosub(_Q_env, LABEL_6000;);
  }
  if (COLeventTRIG == 1) {
    ts = 0.125;
    TSindex = 4;
  }
  OLDts = ts;

  // 'Control input
  LABEL_103:;
  qbf_inkey_str(_Q_env, &z_str);
  if (_qb_str_equals_const(z_str, "", 0)) { goto LABEL_105; }
  if (_qb_str_equals_const(z_str, "q", 1)) { QBM_gosub(_Q_env, LABEL_900); }
  if (_qb_str_equals_const(z_str, "`", 1)) {
    DISPflag = 1 - DISPflag;
    qb_cls(_Q_env);
    HPdisp = 0;
    if (DISPflag == 0) { QBM_gosub(_Q_env, LABEL_405); }
  }
  // 'IF z$ = CHR$(27) THEN GOSUB 910
  if (_qb_str_equals_const(z_str, " ", 1)) {
    cen = targ;
    cenXoff = Px[28][3] - Px[ (size_t)cen ][3];
    cenYoff = Py[28][3] - Py[ (size_t)cen ][3];
  }
  if (_qb_str_equals_const(z_str, "\x09", 1)) {
    Aflag = Aflag + 1;
    if (Aflag == 3) {
      Aflag = 0;
      QBM_gosub(_Q_env, LABEL_400);
    } else {
      QBM_gosub(_Q_env, LABEL_400);
    }
  }
  if (_qb_str_equals_const(z_str, "\0;", 2)) {
    Sflag = 1;
    QBM_gosub(_Q_env, LABEL_400);
  }
  if (_qb_str_equals_const(z_str, "\0<", 2)) {
    Sflag = 0;
    QBM_gosub(_Q_env, LABEL_400);
  }
  if (_qb_str_equals_const(z_str, "\0=", 2)) {
    Sflag = 4;
    QBM_gosub(_Q_env, LABEL_400);
  }
  if (_qb_str_equals_const(z_str, "\0>", 2)) {
    Sflag = 2;
    QBM_gosub(_Q_env, LABEL_400);
  }
  if (_qb_str_equals_const(z_str, "\0?", 2)) {
    Sflag = 3;
    QBM_gosub(_Q_env, LABEL_400);
  }
  if (_qb_str_equals_const(z_str, "b", 1)) {
    Dfuel = Dfuel + 1;
    QBM_gosub(_Q_env, LABEL_400);
  }
  if (_qb_str_equals_const(z_str, "\0A", 2)) {
    Sflag = 5;
    QBM_gosub(_Q_env, LABEL_400);
  }
  if (_qb_str_equals_const(z_str, "\0B", 2)) {
    Sflag = 6;
    QBM_gosub(_Q_env, LABEL_400);
  }
  if (_qb_str_equals_const(z_str, "\0C", 2)) {
    OFFSET = -1 * (1 - qbf_abs(OFFSET));
    QBM_gosub(_Q_env, LABEL_400);
  }
  if (_qb_str_equals_const(z_str, "\0D", 2)) {
    OFFSET = 1 - qbf_abs(OFFSET);
    QBM_gosub(_Q_env, LABEL_400);
  }
  if (_qb_str_equals_const(z_str, "\0\x86", 2)) {
    CONSTacc = 1 - CONSTacc;
    Accel = Aacc;
    MATCHacc = 0;
  }
  if (_qb_str_equals_const(z_str, "\0\x85", 2)) {
    MATCHacc = 1 - MATCHacc;
    CONSTacc = MATCHacc;
  }

  if (_qb_str_equals_const(z_str, "+", 1) && mag < 130000000000.0) {
    mag = mag / 0.75;
    QBM_gosub(_Q_env, LABEL_405);
  }
  if (_qb_str_equals_const(z_str, "-", 1) && mag > 6.8e-11) {
    mag = mag * 0.75;
    QBM_gosub(_Q_env, LABEL_405);
  }

  if (vernP_float <= 0) { goto LABEL_115; }
  if (_qb_str_nequals_const(z_str, "\0I", 2)) { goto LABEL_116; }
  if ((8192 & (int32_t)NAVmalf) == 8192) { goto LABEL_115; }
  HABrotateADJ_i16 = HABrotateADJ_i16 - 1;
  vernP_float = vernP_float - 1;
  LABEL_116:;
  if (_qb_str_nequals_const(z_str, "\0G", 2)) { goto LABEL_115; }
  if ((4096 & (int32_t)NAVmalf) == 4096) { goto LABEL_115; }
  HABrotateADJ_i16 = HABrotateADJ_i16 + 1;
  vernP_float = vernP_float - 1;

  LABEL_115:;
  if (_qb_str_equals_const(z_str, "[", 1)) { QBM_gosub(_Q_env, LABEL_460); }
  if (_qb_str_equals_const(z_str, "]", 1)) { QBM_gosub(_Q_env, LABEL_465); }
  if (
    _qb_str_lessthan_const(z_str, "0", 1) ||
    _qb_str_greaterthan_const(z_str, "U", 1)
  ) { goto LABEL_110; }
  z = qbf_asc(z_str) - 48;
  if (z == 36 && MODULEflag == 0) { goto LABEL_110; }
  if (Aflag == 0) {
    cen = z;
    cenXoff = 0;
    cenYoff = 0;
    QBM_gosub(_Q_env, LABEL_405);
  }
  if (z == 28) { goto LABEL_110; }
  if (Aflag == 1) {
    targ = z;
    QBM_gosub(_Q_env, LABEL_400);;
  }
  if (Aflag == 2) {
    ref = z;
    QBM_gosub(_Q_env, LABEL_400);;
  }

  LABEL_110:;
  if (_qb_str_equals_const(z_str, "e", 1)) {
     ENGsetFLAG = 1 - ENGsetFLAG;
  }
  if (_qb_str_equals_const(z_str, "\0S", 2)) {
     eng = eng + 0.1;
     QBM_gosub(_Q_env, LABEL_400);
  }
  if (_qb_str_equals_const(z_str, "\0R", 2)) {
     eng = eng - 0.1;
     QBM_gosub(_Q_env, LABEL_400);
  }
  if (_qb_str_equals_const(z_str, "\0Q", 2)) {
     eng = eng + 1;
     QBM_gosub(_Q_env, LABEL_400);
  }
  if (_qb_str_equals_const(z_str, "\0O", 2)) {
     eng = eng - 1;
     QBM_gosub(_Q_env, LABEL_400);
  }
  if (_qb_str_equals_const(z_str, "\\", 1)) {
     eng = eng * -1;
     QBM_gosub(_Q_env, LABEL_400);
  }
  if (_qb_str_equals_const(z_str, "\x0d", 1)) {
     eng = 100;
     QBM_gosub(_Q_env, LABEL_400);
  }
  if (_qb_str_equals_const(z_str, "\x08", 1)) {
     eng = 0;
     MATCHacc = 0;
     CONSTacc = 0;
     QBM_gosub(_Q_env, LABEL_400);
  }
  if (_qb_str_equals_const(z_str, "\0H", 2)) {
     vern = 0.1;
     vernA = 0;
  }
  if (_qb_str_equals_const(z_str, "\0K", 2)) {
     vern = 0.1;
     vernA = 90;
  }
  if (_qb_str_equals_const(z_str, "\0M", 2)) {
     vern = 0.1;
     vernA = -90;
  }
  if (_qb_str_equals_const(z_str, "\0P", 2)) {
     vern = 0.1;
     vernA = 180;
  }

  if (_qb_str_nequals_const(z_str, "v", 1)) { goto LABEL_107; }
  vflag = 1 - vflag;
  qb_line(
    _Q_env,
    300 + (Px[28][3] - cenX) * mag / AU,
    220 + (Py[28][3] - cenY) * mag * 1 / AU,
    300 + (20 * qbf_sin(Vvangle)) + (Px[28][3] - cenX) * mag / AU,
    220 + (20 * qbf_cos(Vvangle)) + (Py[28][3] - cenY) * mag * 1 / AU,
    0
  );
  qb_line(
    _Q_env,
    300 + (Px[28][3] - cenX) * mag / AU,
    220 + (Py[28][3] - cenY) * mag * 1 / AU,
    300 + (30 * qbf_sin(Atarg)) + (Px[28][3] - cenX) * mag / AU,
    220 + (30 * qbf_cos(Atarg)) + (Py[28][3] - cenY) * mag * 1 / AU,
    0
  );
  qb_line(
    _Q_env,
    300 + (Px[28][3] - cenX) * mag / AU,
    220 + (Py[28][3] - cenY) * mag * 1 / AU,
    300 + (10 * qbf_sin(Sangle)) + (Px[28][3] - cenX) * mag / AU,
    220 + (10 * qbf_cos(Sangle)) + (Py[28][3] - cenY) * mag * 1 / AU,
    0
  );
  LABEL_107:;
  if (_qb_str_equals_const(z_str, "t", 1)) { trail = 1 - trail; }
  if (_qb_str_equals_const(z_str, "l", 1)) {
    ORref = 1 - ORref;
    QBM_gosub(_Q_env, LABEL_405);
  }
  if (_qb_str_equals_const(z_str, "a", 1)) { PROBEflag = 1 - PROBEflag; }
  if (_qb_str_equals_const(z_str, "\0@", 2)) {
    Sflag = 7;
    angleOFFSET = (Atarg - Sangle);
    QBM_gosub(_Q_env, LABEL_400);
  }
  if (_qb_str_equals_const(z_str, "u", 1)) { tr = 1 - tr; }
  if (_qb_str_equals_const(z_str, "d", 1)) {
    dte = dte + 1;
    qb_locate(_Q_env, 25, 58);
    {
      QBM_new_str(_Q_tmp);
      qbf_space_str_direct(&_Q_tmp, 20);
      qb_stdprint_str(_Q_env, _Q_tmp, FALSE);
      _qb_free_str(&_Q_tmp);
    }
    QBM_gosub(_Q_env, LABEL_400);
  }
  if (dte == 4) { dte = 0; }
  if (_qb_str_equals_const(z_str, "p", 1)) {
    PROJflag = 1 - PROJflag;
    QBM_gosub(_Q_env, LABEL_400); }
  if (_qb_str_equals_const(z_str, "o", 1)) { QBM_gosub(_Q_env, LABEL_3000); }
  if (_qb_str_equals_const(z_str, "c", 1)) { QBM_gosub(_Q_env, LABEL_405); }
  // 'IF z$ = "z" THEN Ztel(7) = 1 - SGN(Ztel(7))
  // 'IF z$ = "x" THEN Ztel(7) = 2 - (SGN(Ztel(7)) * 2)
  // 'IF z$ = "w" THEN SRBtimer = 220
  if (Ztel[8] == 1) { goto LABEL_105; }
  if (_qb_str_nequals_const(z_str, "/", 1)) { goto LABEL_104; }
  if (TSindex < 2) { goto LABEL_105; }
  TSindex = TSindex - 1;
  ts = TSflagVECTOR[ (size_t)TSindex ];
  QBM_gosub(_Q_env, LABEL_400);

  LABEL_104:;
  if (_qb_str_nequals_const(z_str, "*", 1)) { goto LABEL_105; }
  if (TSindex > 16) { goto LABEL_105; }
  TSindex = TSindex + 1;
  ts = TSflagVECTOR[ (size_t)TSindex ];
  QBM_gosub(_Q_env, LABEL_400);

  LABEL_105:;
  if (_qb_str_equals_const(z_str, "s", 1)) { QBM_gosub(_Q_env, LABEL_600); }
  if (_qb_str_equals_const(z_str, "r", 1)) { QBM_gosub(_Q_env, LABEL_700); }
  if (tttt - qbf_timer() > ts * 10) { tttt = qbf_timer() + (ts / 2); }
  if (TSindex < 6 && qbf_timer() - tttt < ts) { goto LABEL_103; }
  if (TSindex == 6 && qbf_timer() - tttt < 0.01) { goto LABEL_103; }
  goto LABEL_100;

  // 'SUBROUTINE Automatic space craft orientation calculations
  LABEL_301:;
  if (explosion > 1) {
    Ztel[2] = 0;
    Ztel[1] = 1;
  }
  if (ufo1 == 0 && Ztel[17] == 1 && PROBEflag == 1) {
    QBM_gosub(_Q_env, LABEL_7000);
    PROBEflag = 0;
  }
  if (explosion1 > 1 && AYSE == 150) { Ztel[2] = 0; }
  if (Ztel[1] == 1) {
    Sflag = 1;
    MATCHacc = 0;
    CONSTacc = 0;
  }
  if (SRBtimer > 0) { SRBtimer = SRBtimer - ts; }
  if (SRBtimer > 100) {
    SRB = 131250;
  } else {
    SRB = 0;
  }
  if (vernP_float < 0.01) { vernP_float = 0; }
  if (qbf_abs(HABrotMALF) * qbf_abs(eng) > 0.0001) { Sflag = 1; }
  if (((int32_t)NAVmalf & 3840) > 0) { Sflag = 1; }
  if (
    qbf_abs(HABrotate + 0.5) <
    0.5 * (1 - (vernCNT * 0.8))
  ) {
    HABrotate = 0;
  }
  HABrotate = HABrotate + (HABrotateADJ_i16 * _qbf_pow(10, (-1 * vernCNT)));
  HABrotateADJ_i16 = HABrotateADJ_i16 * vernCNT;
  HABrotate = HABrotate + (eng * HABrotMALF * 0.0095 * qbf_sgn(Ztel[2]));
  HABrotate =
    HABrotate +
    (
      qbf_sgn(vernP_float) *
      (((double)(768 & (int32_t)NAVmalf) / 256) * 0.015)
    );
  HABrotate =
    HABrotate -
    (
      qbf_sgn(vernP_float) *
      (((double)(3072 & (int32_t)NAVmalf) / 1024) * 0.015)
    );
  if (qbf_abs(HABrotate) > 99) {
    HABrotate = qbf_sgn(HABrotate) * 99;
  }
  if (qbf_abs(HABrotateADJ_i16) > 10) {
    HABrotateADJ_i16 = qbf_sgn(HABrotateADJ_i16) * 10;
  }

  qb_color(_Q_env, 15);
  Aoffset = qbf_atn((P[ (size_t)targ ][5] * 1.01) / (Dtarg + 0.0001));
  Atarg = Atarg - (Aoffset * OFFSET);
  difX = Vx[ (size_t)targ ] - Vx[28];
  difY = Vy[ (size_t)targ ] - Vy[28];
  QBM_gosub(_Q_env, LABEL_5000);
  Vvtangle = angle;
  if (ORref == 1) {
    Aa = Atarg;
  } else {
    Aa = Aref;
  }
  if (PROJflag == 0) {
    DIFFangle = (Aa - Sangle) * RAD;
  } else {
    DIFFangle = (Atarg - Vvtangle) * RAD;
  }
  if (DIFFangle > 180) { DIFFangle = -360 + DIFFangle; }
  if (DIFFangle < -180) { DIFFangle = 360 + DIFFangle; }

  difX = Px[28][3] - Px[ (size_t)Ztel [14]][3];
  difY = Py[28][3] - Py[ (size_t)Ztel [14]][3];
  QBM_gosub(_Q_env, LABEL_5000);
  Wangle = angle;
  VwindX = (Ztel[15] * qbf_sin(Wangle + Ztel[16]));
  VwindY = (Ztel[15] * qbf_cos(Wangle + Ztel[16]));

  if (CONflag < 0.5) { goto LABEL_303; }
  if (CONtarg == 32) { goto LABEL_303; }
  HABrotate = 0;
  if (Sflag == 3) {
    Sangle = Aref - (180 / RAD);
  } else {
    Sflag = 1;
    qb_locate(_Q_env, 25, 11);
    qb_stdprint_str_const(_Q_env, "MAN      ", 9, FALSE);
  }
  LABEL_303:;
  if ((3840 & (int32_t)NAVmalf) > 0) {
    vernP_float = vernP_float - 0.5;
    Sflag = 10;
  }
  if (Sflag == 2 && (1 & (int32_t)NAVmalf) == 1) { Sflag = 10; }
  if (Sflag == 7 && (1 & (int32_t)NAVmalf) == 1) { Sflag = 10; }
  if (Sflag == 5 && (1 & (int32_t)NAVmalf) == 1) { Sflag = 10; }
  if (Sflag == 6 && (1 & (int32_t)NAVmalf) == 1) { Sflag = 10; }
  if (Sflag == 0 && (4 & (int32_t)NAVmalf) == 4) { Sflag = 10; }
  if (Sflag == 4 && (4 & (int32_t)NAVmalf) == 4) { Sflag = 10; }
  if (Sflag == 3 && (4 & (int32_t)NAVmalf) == 4) { Sflag = 10; }
  if (vernP_float < 0.01 && Sflag != 1) { Sflag = 10; }
  if (Sflag == 10) {
    Sflag = 1;
    qb_locate(_Q_env, 25, 11);
    qb_stdprint_str_const(_Q_env, "MAN      ", 9, FALSE);
  }
  if (Sflag == 1) {
    Sangle = Sangle + (HABrotate * 0.0086853 * ts);
    goto LABEL_302;
  }
  vernP_float = vernP_float - 0.01;
  if (Sflag == 2) {
    dSangle = Atarg;
  } else {
    dSangle = Aref;
  }
  if (Sflag == 7) { dSangle = Atarg; }
  dSangle = dSangle - (Aoffset * OFFSET);
  if (Sflag == 5) { dSangle = Vvtangle; }
  if (Sflag == 6) { dSangle = Vvtangle + 3.1415926535; }
  if (Sflag == 0) { dSangle = dSangle - (90 / RAD); }
  if (Sflag == 4) { dSangle = dSangle + (90 / RAD); }
  if (Sflag == 3) { dSangle = dSangle - (180 / RAD); }
  if (Sflag == 7) { dSangle = dSangle - angleOFFSET; }
  diffSangle = dSangle - Sangle;
  if (diffSangle > pi) { diffSangle = (-1 * pi2) + diffSangle; }
  if (diffSangle < (-1 * pi)) { diffSangle = pi2 + diffSangle; }
  if (qbf_abs(diffSangle) < 0.24 * ts) {
    Sangle = dSangle;
    HABrotate = 0;
    goto LABEL_302;
  }
  Sangle = Sangle + (0.2 * ts * qbf_sgn(diffSangle));
  HABrotate = 23 * qbf_sgn(diffSangle);

  LABEL_302:;
  if (Sangle < 0) { Sangle = Sangle + pi2; }
  if (Sangle > pi2) { Sangle = Sangle - pi2; }
  if (oldAcctarg < 0) { MATCHacc = 0; }
  if (DISPflag == 1) { goto LABEL_307; }
  qb_locate(_Q_env, 5, 16);
  qb_color(_Q_env, 8 + (7 * ENGsetFLAG));
  QBM_std_pu_const_double(_Q_env, "####.#_ ", 8, eng, FALSE);
  if (Sflag != 1) { goto LABEL_307; }
  if (HABrotate != 0) {
    qb_color(_Q_env, 15);
  } else {
    qb_color(_Q_env, 8);
  }
  qb_locate(_Q_env, 25, 15);
  QBM_std_pu_const_double(_Q_env, "##.#", 4, qbf_abs(HABrotate) / 2, FALSE);
  if (((int32_t)NAVmalf & 11264) > 0) {
    qb_color(_Q_env, 12);
    _qb_set_str_const(&rotSYMB_str, ">", 1);
  } else {
    qb_color(_Q_env, 10);
    _qb_set_str_const(&rotSYMB_str, " ", 1);
  }
  qb_locate(_Q_env, 25, 19);
  if (HABrotate < 0) {
    qb_stdprint_str_const(_Q_env, ">", 1, FALSE);
  } else {
    qb_stdprint_str(_Q_env, rotSYMB_str, FALSE);
  }
  if (((int32_t)NAVmalf & 4864) > 0) {
    qb_color(_Q_env, 12);
    _qb_set_str_const(&rotSYMB_str, "<", 1);
  } else {
    qb_color(_Q_env, 10);
    _qb_set_str_const(&rotSYMB_str, " ", 1);
  }
  qb_locate(_Q_env, 25, 14);
  if (HABrotate > 0) {
    qb_stdprint_str_const(_Q_env, "<", 1, FALSE);
  } else {
    qb_stdprint_str(_Q_env, rotSYMB_str, FALSE);
  }

  LABEL_307:;
  qb_color(_Q_env, 15);
  if (Ztel[2] == 0) {
    MATCHacc = 0;
    CONSTacc = 0;
  }
  if (MATCHacc == 1) { Accel = oldAcctarg; }
  HABmass = 275000 + fuel;
  if (AYSE == 150) { HABmass = HABmass + 20000000 + AYSEfuel; }
  massDEL = (
    1 -
    ((_qbf_pow(Vx[28], 2) + _qbf_pow(Vy[28], 2)) / _qbf_pow(300000000, 2))
  );
  if (massDEL < 9.999946e-41) { massDEL = 9.999946e-41; }
  HABmass = HABmass / qbf_sqr(massDEL);
  if (CONSTacc == 1) {
    Aacc = Accel;
    eng = ENGsetFLAG * Aacc * HABmass / Ztel[2];
  } else {
    Aacc = (ENGsetFLAG * Ztel[2] * eng) / HABmass;
  }
  Av = (175000 * vern) / HABmass;
  if (AYSE == 150) { Av = 0; }
  if (vernP_float <= 0) { Av = 0; }
  if (Av > 0) { vernP_float = vernP_float - 1; }
  vern = 0;

  LABEL_304: __attribute__((unused));
  Aacc = Aacc + (SRB / HABmass) * 100;
  P[ (size_t)i ][1] = P[ (size_t)i ][1] + (Aacc * qbf_sin(Sangle));
  P[ (size_t)i ][2] = P[ (size_t)i ][2] + (Aacc * qbf_cos(Sangle));
  P[ (size_t)i ][1] = P[ (size_t)i ][1] + Av * qbf_sin(Sangle + (vernA / RAD));
  P[ (size_t)i ][2] = P[ (size_t)i ][2] + Av * qbf_cos(Sangle + (vernA / RAD));

  THRUSTx = (Aacc * qbf_sin(Sangle));
  THRUSTy = (Aacc * qbf_cos(Sangle));
  THRUSTx = THRUSTx + (Av * qbf_sin(Sangle + (vernA / RAD)));
  THRUSTy = THRUSTy + (Av * qbf_cos(Sangle + (vernA / RAD)));

  Are = 0;
  if (atm == 40 && Ztel[16] != 3.141593) {
    Are = 0;
    goto LABEL_319;
  }
  difX = Vx[ (size_t)atm ] - Vx[28] + VwindX;
  difY = Vy[ (size_t)atm ] - Vy[28] + VwindY;
  QBM_gosub(_Q_env, LABEL_5000);
  VvRangle = angle;
  AOA =
    qbf_cos(VvRangle - Sangle) *
    qbf_sgn(qbf_sgn(qbf_cos(VvRangle - Sangle)) - 1);
  AOA = AOA * AOA * AOA;
  if (AOA > 0.5) { AOA = 1 - AOA; }
  AOA = (AOA * qbf_sgn(qbf_sin(VvRangle - Sangle))) * 0.5;
  AOAx = -1 * qbf_abs(AOA) * qbf_sin(VvRangle + (1.5708 * qbf_sgn(AOA)));
  AOAy = -1 * qbf_abs(AOA) * qbf_cos(VvRangle + (1.5708 * qbf_sgn(AOA)));
  VVr = qbf_sqr(_qbf_pow(difX, 2) + _qbf_pow(difY, 2));
  if (atm == 40) {
    Pr = 0.01;
    goto LABEL_320;
  }
  if (Ratm < 0) {
    Pr = P[ (size_t)atm ][8];
  }
  else {
    Pr = P[ (size_t)atm ][8] * _qbf_pow(2.71828, (-1 * Ratm / P[ (size_t)atm ][9]));
  }
  LABEL_320:;
  Are = Pr * VVr * VVr * Cdh;
  if (Are * ts > VVr / 2) { Are = (VVr / 2) / ts; }
  if (CONflag == 1 && Ztel[16] == 0) { Are = 0; }
  P[ (size_t)i ][1] = P[ (size_t)i ][1] - (Are * qbf_sin(VvRangle)) + (Are * AOAx);
  P[ (size_t)i ][2] = P[ (size_t)i ][2] - (Are * qbf_cos(VvRangle)) + (Are * AOAy);
  THRUSTx = THRUSTx - (Are * qbf_sin(VvRangle));
  THRUSTy = THRUSTy - (Are * qbf_cos(VvRangle));
  LABEL_321: __attribute__((unused));
  if (Pr > 100 && Pr / 200 > qbf_rnd()) { explFLAG1 = 1; }

  LABEL_319:;
  Agrav = _qbf_pow(THRUSTx - (Are * qbf_sin(VvRangle)), 2);
  Agrav = Agrav + _qbf_pow(THRUSTy - (Are * qbf_cos(VvRangle)), 2);
  Agrav = qbf_sqr(Agrav);
  if (CONflag == 1) { Agrav = CONacc; }

  if (THRUSTy == 0) {
    if (THRUSTy < 0) {
      THRUSTangle = 0.5 * 3.1415926535;
    } else {
      THRUSTangle = 1.5 * 3.1415926535;
    }
  } else {
    THRUSTangle = qbf_atn(THRUSTx / THRUSTy);
  }
  if (THRUSTy > 0) { THRUSTangle = THRUSTangle + 3.1415926535; }
  if (THRUSTx > 0 && THRUSTy < 0) { THRUSTangle = THRUSTangle + 6.283185307; }

  if (DISPflag == 1) { goto LABEL_330; }
  qb_locate(_Q_env, 5, 8);
  qb_color(_Q_env, 14);
  if (SRB > 10) {
    qb_stdprint_str_const(_Q_env, "SRB", 3, FALSE);
  }
  else {
    qb_stdprint_str_const(_Q_env, "   ", 3, FALSE);
  }
  if (AYSE == 150) {
    qb_color(_Q_env, 10);
  } else {
    qb_color(_Q_env, 0);
  }
  qb_locate(_Q_env, 5, 12);
  qb_stdprint_str_const(_Q_env, "AYSE", 4, FALSE);
  qb_color(_Q_env, 7);

  LABEL_330:;
  _qb_gosub_return(_Q_env);

  // 'SUBROUTINE print control variable names to screen
  LABEL_405:;
  qb_cls(_Q_env);

  HPdisp = 0;
  LABEL_400:;
  if (mag < 0.1) { QBM_gosub(_Q_env, LABEL_8000); }

  if (ts < 0.015625) {
    ts = 0.015626;
    TSindex = 1;
  }
  if (ts > 60) {
    ts = 60;
    TSindex = 17;
  }

  if (Dfuel > 2) { Dfuel = 0; }
  if (ufo2 == 1) {
    ts = 0.25;
    TSindex = 5;
  }
  qb_color(_Q_env, 8);

  for (j = 1; j <= 214; j++) {
    qb_locate(_Q_env, panel[0][ (size_t)j ], panel[1][ (size_t)j ]);
    {
      QBM_new_str(_Q_tmp);
      qbf_chr_str_direct(&_Q_tmp, panel[2][ (size_t)j ]);
      qb_stdprint_str(_Q_env, _Q_tmp, FALSE);
      _qb_free_str(&_Q_tmp);
    }
    if (dte == 0 && j == 168) { goto LABEL_403; }
  }

  LABEL_403:;
  qb_color(_Q_env, 7);

  if (Ztel[1] == 1) { Sflag = 1; }

  qb_locate(_Q_env, 2, 2);
  qb_stdprint_str_const(_Q_env, "ref Vo   ", 9, FALSE);
  qb_locate(_Q_env, 3, 2);
  qb_stdprint_str_const(_Q_env, "V hab-ref", 9, FALSE);
  qb_locate(_Q_env, 4, 2);
  qb_stdprint_str_const(_Q_env, "Vtarg-ref", 9, FALSE);

  qb_color(_Q_env, 7);

  qb_locate(_Q_env, 5, 2);
  qb_stdprint_str_const(_Q_env, "Engine", 6, FALSE);
  qb_locate(_Q_env, 5, 16);
  qb_color(_Q_env, 8 + (7 * ENGsetFLAG));
  QBM_std_pu_const_double(_Q_env, "####.#_ ", 8, eng, FALSE);
  qb_color(_Q_env, 7 + (5 * Ztel[1]));
  qb_locate(_Q_env, 25, 2);
  qb_stdprint_str_const(_Q_env, "NAVmode", 7, FALSE);
  qb_color(_Q_env, 14);
  qb_locate(_Q_env, 25, 10);
  if (OFFSET == -1) {
    qb_stdprint_str_const(_Q_env, "-", 1, FALSE);
  }
  if (OFFSET == 0) {
    qb_stdprint_str_const(_Q_env, " ", 1, FALSE);
  }
  if (OFFSET == 1) {
    qb_stdprint_str_const(_Q_env, "+", 1, FALSE);
  }
  qb_color(_Q_env, 15);
  qb_locate(_Q_env, 25, 11);
  if (Sflag == 0) {
    qb_stdprint_str_const(_Q_env, "ccw prog ", 9, FALSE);
    goto LABEL_401;
  }
  if (Sflag == 4) {
    qb_stdprint_str_const(_Q_env, "ccw retro", 9, FALSE);
    goto LABEL_401;
  }
  if (Sflag == 1) {
    qb_stdprint_str_const(_Q_env, "MAN      ", 9, FALSE);
    goto LABEL_401;
  }
  if (Sflag == 2) {
    qb_stdprint_str_const(_Q_env, "app targ ", 9, FALSE);
    goto LABEL_401;
  }
  if (Sflag == 5) {
    qb_stdprint_str_const(_Q_env, "pro Vtrg ", 9, FALSE);
    goto LABEL_401;
  }
  if (Sflag == 6) {
    qb_stdprint_str_const(_Q_env, "retr Vtrg", 9, FALSE);
    goto LABEL_401;
  }
  if (Sflag == 7) {
    qb_stdprint_str_const(_Q_env, "hold Atrg", 9, FALSE);
    goto LABEL_401;
  }
  if (Sflag == 3) {
    qb_stdprint_str_const(_Q_env, "deprt ref", 9, FALSE);
  }
  LABEL_401:;
  qb_color(_Q_env, 8);
  if (Aflag == 0) {
    qb_color(_Q_env, 10);
  } else {
    qb_color(_Q_env, 7);
  }
  qb_locate(_Q_env, 22, 2);
  qb_stdprint_str_const(_Q_env, "center ", 7, FALSE);
  qb_locate(_Q_env, 22, 10);
  qb_color(_Q_env, 15);
  {
    qb_stdprint_str_const(_Q_env, " ", 1, FALSE);
    qb_stdprint_str(_Q_env, Znme_str[ (size_t)cen ], FALSE);
    qb_stdprint_str_const(_Q_env, " ", 1, FALSE);
  }
  if (Aflag == 1) {
    qb_color(_Q_env, 10);
  } else {
    qb_color(_Q_env, 7);
  }
  qb_locate(_Q_env, 23, 2);
  qb_stdprint_str_const(_Q_env, "target ", 7, FALSE);
  qb_locate(_Q_env, 23, 10);
  qb_color(_Q_env, 15);
  {
    qb_stdprint_str_const(_Q_env, " ", 1, FALSE);
    qb_stdprint_str(_Q_env, Znme_str[ (size_t)targ ], FALSE);
    qb_stdprint_str_const(_Q_env, " ", 1, FALSE);
  }
  if (Aflag == 2) {
    qb_color(_Q_env, 10);
  } else {
    qb_color(_Q_env, 7);
  }
  qb_locate(_Q_env, 24, 2);
  qb_stdprint_str_const(_Q_env, "ref    ", 7, FALSE);
  qb_locate(_Q_env, 24, 10);
  qb_color(_Q_env, 15);
  {
    qb_stdprint_str_const(_Q_env, " ", 1, FALSE);
    qb_stdprint_str(_Q_env, Znme_str[ (size_t)ref ], FALSE);
    qb_stdprint_str_const(_Q_env, " ", 1, FALSE);
  }
  qb_color(_Q_env, 15);
  qb_locate(_Q_env, 9, 8);
  QBM_std_pu_const_double(_Q_env, "#####.###", 9, ts, FALSE);
  qb_color(_Q_env, 7);
  qb_locate(_Q_env, 11, 2);
  qb_stdprint_str_const(_Q_env, "Fuel", 4, FALSE);
  qb_locate(_Q_env, 14, 2);
  qb_stdprint_str_const(_Q_env, "Acc            ", 15, FALSE);
  qb_locate(_Q_env, 15, 2);
  qb_stdprint_str_const(_Q_env, "\xe9 Hrt          ", 15, FALSE);
  qb_locate(_Q_env, 16, 2);
  qb_stdprint_str_const(_Q_env, "Vcen          ", 14, FALSE);
  if (ORref == 0) {
    qb_stdprint_str_const(_Q_env, "R", 1, FALSE);
  }
  qb_locate(_Q_env, 17, 2);
  qb_stdprint_str_const(_Q_env, "Vtan          ", 14, FALSE);
  if (ORref == 0) {
    qb_stdprint_str_const(_Q_env, "R", 1, FALSE);
  }
  qb_locate(_Q_env, 18, 2);
  {
    qb_stdprint_str_const(_Q_env, "\xe9", 1, FALSE);
    qb_stdprint_str(_Q_env, Znme_str[41 + (int32_t)PROJflag], FALSE);
    qb_stdprint_str_const(_Q_env, "         ", 9, FALSE);
  }
  if (PROJflag == 0 && ORref == 0) {
    qb_stdprint_str_const(_Q_env, "R", 1, FALSE);
  } else {
    qb_stdprint_str_const(_Q_env, " ", 1, FALSE);
  }
  qb_locate(_Q_env, 19, 2);
  qb_stdprint_str_const(_Q_env, "Peri          ", 14, FALSE);
  if (ORref == 0) {
    qb_stdprint_str_const(_Q_env, "R", 1, FALSE);
  }
  qb_locate(_Q_env, 20, 2);
  qb_stdprint_str_const(_Q_env, "Apo           ", 14, FALSE);
  if (ORref == 0) {
    qb_stdprint_str_const(_Q_env, "R", 1, FALSE);
  }
  qb_color(_Q_env, 15);
  LABEL_402: __attribute__((unused));
  // 'IF dte = 1 THEN LOCATE 25, 60: PRINT USING "####"; year; : LOCATE 25, 66: PRINT USING "###"; day; hr; min; sec;
  _qb_gosub_return(_Q_env);

  LABEL_460:;
  switch ((int32_t)Aflag + 1) {
    case 1:
      goto LABEL_461;
    case 2:
      goto LABEL_462;
    case 3:
      goto LABEL_463;
  }
  LABEL_461:;
  if (cen == 40) { cen = 38; }
  if (cen - 1 == 36 && MODULEflag == 0) { cen = 36; }
  if (cen - 1 < 0) { cen = 41; }
  cen = cen - 1;
  cenXoff = 0;
  cenYoff = 0;
  QBM_gosub(_Q_env, LABEL_405);
  _qb_gosub_return(_Q_env);

  LABEL_462:;
  if (targ - 1 == 28) { targ = 28; }
  if (targ - 1 == 36 && MODULEflag == 0) { targ = 36; }
  if (targ - 1 < 0) { targ = 41; }
  if (targ == 40) { targ = 38 + ufo1 + ufo2; }
  targ = targ - 1;
  QBM_gosub(_Q_env, LABEL_400);
  _qb_gosub_return(_Q_env);

  LABEL_463:;
  if (ref - 1 == 28) { ref = 28; }
  if (ref - 1 == 36 && MODULEflag == 0) { ref = 36; }
  if (ref - 1 < 0) { ref = 35; }
  ref = ref - 1;
  QBM_gosub(_Q_env, LABEL_400);
  _qb_gosub_return(_Q_env);


  LABEL_465:;
  switch ((int32_t)Aflag + 1) {
    case 1:
      goto LABEL_466;
    case 2:
      goto LABEL_467;
    case 3:
      goto LABEL_468;
  }
  LABEL_466:;
  if (cen == 40) { cen = -1; }
  if (cen + 1 == 36 && MODULEflag == 0) { cen = 36; }
  if (cen + 1 > 37) { cen = 39; }
  cen = cen + 1;
  cenXoff = 0;
  cenYoff = 0;
  QBM_gosub(_Q_env, LABEL_405);
  _qb_gosub_return(_Q_env);

  LABEL_467:;
  if (targ == 40) { targ = -1; }
  if (targ + 1 == 28) { targ = 28; }
  if (targ + 1 == 36 && MODULEflag == 0) { targ = 36; }
  if (targ + 1 > 37 + ufo1 + ufo2) { targ = 39; }
  targ = targ + 1;
  QBM_gosub(_Q_env, LABEL_400);
  _qb_gosub_return(_Q_env);

  LABEL_468:;
  if (ref + 1 == 28) { ref = 28; }
  if (ref + 1 == 35) { ref = -1; }
  if (ref + 1 > 37) { ref = 36; }
  ref = ref + 1;
  QBM_gosub(_Q_env, LABEL_400);
  _qb_gosub_return(_Q_env);

  // 'SUBROUTINE Restore data from file
  LABEL_700:;
  qb_locate(_Q_env, 10, 60);
  qb_stdprint_str_const(_Q_env, "Load File: ", 11, FALSE);
  qb_stdinput_str_const(_Q_env, "", 0, &filename_str, FALSE, FALSE);
  if (_qb_str_equals_const(filename_str, "", 0)) { goto LABEL_703; }
  DEBUGflag = 1;
  goto LABEL_701;

  LABEL_702:;
  qb_locate(_Q_env, 10, 60);
  qb_stdprint_str_const(_Q_env, "                  ", 18, FALSE);
  goto LABEL_700;

  LABEL_701:;
  {
    QBM_new_str(_Q_tmp);
    QBM_new_const_str(_Q_tmp_rnd, ".RND", 4);
    _qb_str_concat_direct(&_Q_tmp, filename_str, _Q_tmp_rnd);
    _Q_file1 = qb_open_reclen(_Q_env, _Q_tmp, "R", 1427);
    _qb_free_str(&_Q_tmp);
    _qb_free_str(&_Q_tmp_rnd);
  }
  qbf_space_str(&inpSTR_str, 1427);
  qb_fget(_Q_file1, 1, &inpSTR_str);
  qb_close(_Q_file1);

  if (qbf_len(inpSTR_str) != 1427) {
    qb_locate(_Q_env, 11, 60);
    qb_stdprint_str(_Q_env, filename_str, FALSE);
    qb_stdprint_str_const(_Q_env, " is unusable", 12, FALSE);
    goto LABEL_702;
  }
  qbf_left_str(&chkCHAR1_str, inpSTR_str, 1);
  qbf_right_str(&chkCHAR2_str, inpSTR_str, 1);
  qbf_mid_str(&ORBITversion_str, inpSTR_str, 2, 7);
  if (_qb_str_nequals(chkCHAR1_str, chkCHAR2_str)) {
    qb_locate(_Q_env, 11, 60);
    qb_stdprint_str(_Q_env, filename_str, FALSE);
    qb_stdprint_str_const(_Q_env, " is unusable", 12, FALSE);
    goto LABEL_702;
  }
  if (_qb_str_nequals_const(ORBITversion_str, "ORBIT5S", 7)) {
    qb_locate(_Q_env, 11, 60);
    qb_stdprint_str(_Q_env, filename_str, FALSE);
    qb_stdprint_str_const(_Q_env, " is unusable", 12, FALSE);
    goto LABEL_702;
  }

  k = 2 + 15;

  {
    QBM_new_str(_Q_tmp);
    qbf_mid_str(&_Q_tmp, inpSTR_str, k, 4);
    eng = qbf_cvs(_Q_tmp);
    _qb_free_str(&_Q_tmp);
    k = k + 4;
  }

  {
    QBM_new_str(_Q_tmp);
    qbf_mid_str(&_Q_tmp, inpSTR_str, k, 2);
    vflag = qbf_cvi(_Q_tmp);
    _qb_free_str(&_Q_tmp);
    k = k + 2;
  }

  {
    QBM_new_str(_Q_tmp);
    qbf_mid_str(&_Q_tmp, inpSTR_str, k, 2);
    Aflag = qbf_cvi(_Q_tmp);
    _qb_free_str(&_Q_tmp);
    k = k + 2;
  }

  {
    QBM_new_str(_Q_tmp);
    qbf_mid_str(&_Q_tmp, inpSTR_str, k, 2);
    Sflag = qbf_cvi(_Q_tmp);
    _qb_free_str(&_Q_tmp);
    k = k + 2;
  }

  {
    QBM_new_str(_Q_tmp);
    qbf_mid_str(&_Q_tmp, inpSTR_str, k, 8);
    Are = qbf_cvd(_Q_tmp);
    _qb_free_str(&_Q_tmp);
    k = k + 8;
  }

  {
    QBM_new_str(_Q_tmp);
    qbf_mid_str(&_Q_tmp, inpSTR_str, k, 8);
    mag = qbf_cvd(_Q_tmp);
    _qb_free_str(&_Q_tmp);
    k = k + 8;
  }

  {
    QBM_new_str(_Q_tmp);
    qbf_mid_str(&_Q_tmp, inpSTR_str, k, 4);
    Sangle = qbf_cvs(_Q_tmp);
    _qb_free_str(&_Q_tmp);
    k = k + 4;
  }

  {
    QBM_new_str(_Q_tmp);
    qbf_mid_str(&_Q_tmp, inpSTR_str, k, 2);
    cen = qbf_cvi(_Q_tmp);
    _qb_free_str(&_Q_tmp);
    k = k + 2;
  }

  {
    QBM_new_str(_Q_tmp);
    qbf_mid_str(&_Q_tmp, inpSTR_str, k, 2);
    targ = qbf_cvi(_Q_tmp);
    _qb_free_str(&_Q_tmp);
    k = k + 2;
  }

  {
    QBM_new_str(_Q_tmp);
    qbf_mid_str(&_Q_tmp, inpSTR_str, k, 2);
    ref = qbf_cvi(_Q_tmp);
    _qb_free_str(&_Q_tmp);
    k = k + 2;
  }

  {
    QBM_new_str(_Q_tmp);
    qbf_mid_str(&_Q_tmp, inpSTR_str, k, 2);
    trail = qbf_cvi(_Q_tmp);
    _qb_free_str(&_Q_tmp);
    k = k + 2;
  }

  {
    QBM_new_str(_Q_tmp);
    qbf_mid_str(&_Q_tmp, inpSTR_str, k, 4);
    Cdh = qbf_cvs(_Q_tmp);
    _qb_free_str(&_Q_tmp);
    k = k + 4;
  }

  {
    QBM_new_str(_Q_tmp);
    qbf_mid_str(&_Q_tmp, inpSTR_str, k, 4);
    SRB = qbf_cvs(_Q_tmp);
    _qb_free_str(&_Q_tmp);
    k = k + 4;
  }

  {
    QBM_new_str(_Q_tmp);
    qbf_mid_str(&_Q_tmp, inpSTR_str, k, 2);
    tr = qbf_cvi(_Q_tmp);
    _qb_free_str(&_Q_tmp);
    k = k + 2;
  }

  {
    QBM_new_str(_Q_tmp);
    qbf_mid_str(&_Q_tmp, inpSTR_str, k, 2);
    dte = qbf_cvi(_Q_tmp);
    _qb_free_str(&_Q_tmp);
    k = k + 2;
  }

  {
    QBM_new_str(_Q_tmp);
    qbf_mid_str(&_Q_tmp, inpSTR_str, k, 8);
    ts = qbf_cvd(_Q_tmp);
    _qb_free_str(&_Q_tmp);
    k = k + 8;
  }

  {
    QBM_new_str(_Q_tmp);
    qbf_mid_str(&_Q_tmp, inpSTR_str, k, 8);
    OLDts = qbf_cvd(_Q_tmp);
    _qb_free_str(&_Q_tmp);
    k = k + 8;
  }

  {
    QBM_new_str(_Q_tmp);
    qbf_mid_str(&_Q_tmp, inpSTR_str, k, 4);
    vernP_float = qbf_cvs(_Q_tmp);
    _qb_free_str(&_Q_tmp);
    k = k + 4;
  }

  {
    QBM_new_str(_Q_tmp);
    qbf_mid_str(&_Q_tmp, inpSTR_str, k, 2);
    Eflag = qbf_cvi(_Q_tmp);
    _qb_free_str(&_Q_tmp);
    k = k + 2;
  }

  {
    QBM_new_str(_Q_tmp);
    qbf_mid_str(&_Q_tmp, inpSTR_str, k, 2);
    year = qbf_cvi(_Q_tmp);
    _qb_free_str(&_Q_tmp);
    k = k + 2;
  }

  {
    QBM_new_str(_Q_tmp);
    qbf_mid_str(&_Q_tmp, inpSTR_str, k, 2);
    day = qbf_cvi(_Q_tmp);
    _qb_free_str(&_Q_tmp);
    k = k + 2;
  }

  {
    QBM_new_str(_Q_tmp);
    qbf_mid_str(&_Q_tmp, inpSTR_str, k, 2);
    hr = qbf_cvi(_Q_tmp);
    _qb_free_str(&_Q_tmp);
    k = k + 2;
  }

  {
    QBM_new_str(_Q_tmp);
    qbf_mid_str(&_Q_tmp, inpSTR_str, k, 2);
    min = qbf_cvi(_Q_tmp);
    _qb_free_str(&_Q_tmp);
    k = k + 2;
  }

  {
    QBM_new_str(_Q_tmp);
    qbf_mid_str(&_Q_tmp, inpSTR_str, k, 8);
    sec = qbf_cvd(_Q_tmp);
    _qb_free_str(&_Q_tmp);
    k = k + 8;
  }

  {
    QBM_new_str(_Q_tmp);
    qbf_mid_str(&_Q_tmp, inpSTR_str, k, 4);
    AYSEangle = qbf_cvs(_Q_tmp);
    _qb_free_str(&_Q_tmp);
    k = k + 4;
  }

  {
    QBM_new_str(_Q_tmp);
    qbf_mid_str(&_Q_tmp, inpSTR_str, k, 2);
    AYSEscrape = qbf_cvi(_Q_tmp);
    _qb_free_str(&_Q_tmp);
    k = k + 2;
  }

  {
    QBM_new_str(_Q_tmp);
    qbf_mid_str(&_Q_tmp, inpSTR_str, k, 4);
    Ztel[15] = qbf_cvs(_Q_tmp);
    _qb_free_str(&_Q_tmp);
    k = k + 4;
  }

  {
    QBM_new_str(_Q_tmp);
    qbf_mid_str(&_Q_tmp, inpSTR_str, k, 4);
    Ztel[16] = qbf_cvs(_Q_tmp);
    _qb_free_str(&_Q_tmp);
    k = k + 4;
  }

  {
    QBM_new_str(_Q_tmp);
    qbf_mid_str(&_Q_tmp, inpSTR_str, k, 4);
    HABrotate = qbf_cvs(_Q_tmp);
    _qb_free_str(&_Q_tmp);
    k = k + 4;
  }

  {
    QBM_new_str(_Q_tmp);
    qbf_mid_str(&_Q_tmp, inpSTR_str, k, 2);
    AYSE = qbf_cvi(_Q_tmp);
    _qb_free_str(&_Q_tmp);
    k = k + 2;
  }

  {
    QBM_new_str(_Q_tmp);
    qbf_mid_str(&_Q_tmp, inpSTR_str, k, 4);
    Ztel[9] = qbf_cvs(_Q_tmp);
    _qb_free_str(&_Q_tmp);
    k = k + 4;
  }

  {
    QBM_new_str(_Q_tmp);
    qbf_mid_str(&_Q_tmp, inpSTR_str, k, 2);
    MODULEflag = qbf_cvi(_Q_tmp);
    _qb_free_str(&_Q_tmp);
    k = k + 2;
  }

  {
    QBM_new_str(_Q_tmp);
    qbf_mid_str(&_Q_tmp, inpSTR_str, k, 4);
    AYSEdist = qbf_cvs(_Q_tmp);
    _qb_free_str(&_Q_tmp);
    k = k + 4;
  }

  {
    QBM_new_str(_Q_tmp);
    qbf_mid_str(&_Q_tmp, inpSTR_str, k, 4);
    OCESSdist = qbf_cvs(_Q_tmp);
    _qb_free_str(&_Q_tmp);
    k = k + 4;
  }

  {
    QBM_new_str(_Q_tmp);
    qbf_mid_str(&_Q_tmp, inpSTR_str, k, 2);
    explosion = qbf_cvi(_Q_tmp);
    _qb_free_str(&_Q_tmp);
    k = k + 2;
  }

  {
    QBM_new_str(_Q_tmp);
    qbf_mid_str(&_Q_tmp, inpSTR_str, k, 2);
    explosion1 = qbf_cvi(_Q_tmp);
    _qb_free_str(&_Q_tmp);
    k = k + 2;
  }

  {
    QBM_new_str(_Q_tmp);
    qbf_mid_str(&_Q_tmp, inpSTR_str, k, 4);
    Ztel[1] = qbf_cvs(_Q_tmp);
    _qb_free_str(&_Q_tmp);
    k = k + 4;
  }

  {
    QBM_new_str(_Q_tmp);
    qbf_mid_str(&_Q_tmp, inpSTR_str, k, 4);
    Ztel[2] = qbf_cvs(_Q_tmp);
    _qb_free_str(&_Q_tmp);
    k = k + 4;
  }

  {
    QBM_new_str(_Q_tmp);
    qbf_mid_str(&_Q_tmp, inpSTR_str, k, 4);
    NAVmalf = qbf_cvl(_Q_tmp);
    _qb_free_str(&_Q_tmp);
    k = k + 4;
  }

  {
    QBM_new_str(_Q_tmp);
    qbf_mid_str(&_Q_tmp, inpSTR_str, k, 4);
    Ztel[14] = qbf_cvs(_Q_tmp);
    _qb_free_str(&_Q_tmp);
    k = k + 4;
  }

  {
    QBM_new_str(_Q_tmp);
    qbf_mid_str(&_Q_tmp, inpSTR_str, k, 4);
    LONGtarg = qbf_cvs(_Q_tmp);
    _qb_free_str(&_Q_tmp);
    k = k + 4;
  }

  {
    QBM_new_str(_Q_tmp);
    qbf_mid_str(&_Q_tmp, inpSTR_str, k, 4);
    Pr = qbf_cvs(_Q_tmp);
    _qb_free_str(&_Q_tmp);
    k = k + 4;
  }

  {
    QBM_new_str(_Q_tmp);
    qbf_mid_str(&_Q_tmp, inpSTR_str, k, 4);
    Agrav = qbf_cvs(_Q_tmp);
    _qb_free_str(&_Q_tmp);
    k = k + 4;
  }

  for (i = 1; i <= 39; i++) {
    {
      QBM_new_str(_Q_tmp);
      qbf_mid_str(&_Q_tmp, inpSTR_str, k, 8);
      Px[ (size_t)i ][3] = qbf_cvd(_Q_tmp);
      _qb_free_str(&_Q_tmp);
      k = k + 8;
    }
    {
      QBM_new_str(_Q_tmp);
      qbf_mid_str(&_Q_tmp, inpSTR_str, k, 8);
      Py[ (size_t)i ][3] = qbf_cvd(_Q_tmp);
      _qb_free_str(&_Q_tmp);
      k = k + 8;
    }
    {
      QBM_new_str(_Q_tmp);
      qbf_mid_str(&_Q_tmp, inpSTR_str, k, 8);
      Vx[ (size_t)i ] = qbf_cvd(_Q_tmp);
      _qb_free_str(&_Q_tmp);
      k = k + 8;
    }
    {
      QBM_new_str(_Q_tmp);
      qbf_mid_str(&_Q_tmp, inpSTR_str, k, 8);
      Vy[ (size_t)i ] = qbf_cvd(_Q_tmp);
      _qb_free_str(&_Q_tmp);
      k = k + 8;
    }
  }

  {
    QBM_new_str(_Q_tmp);
    qbf_mid_str(&_Q_tmp, inpSTR_str, k, 4);
    fuel = qbf_cvs(_Q_tmp);
    _qb_free_str(&_Q_tmp);
    k = k + 4;
  }
  {
    QBM_new_str(_Q_tmp);
    qbf_mid_str(&_Q_tmp, inpSTR_str, k, 4);
    AYSEfuel = qbf_cvs(_Q_tmp);
    _qb_free_str(&_Q_tmp);
    k = k + 4;
  }

  TSindex = 5;
  for (i = 1; i <= 17; i++) {
      if (TSflagVECTOR[ (size_t)i ] == ts) {
        TSindex = i;
        goto LABEL_713;
      }
  }

  LABEL_713:;
  Px[37][3] = 4446370.8284487 + Px[3][3];
  Py[37][3] = 4446370.8284487 + Py[3][3];
  Vx[37] = Vx[3];
  Vy[37] = Vy[3];

  Px[38][3] = 0;
  Py[38][3] = 0;
  Vx[38] = 0;
  Vy[38] = 0;
  P[38][1] = 0;
  P[38][2] = 0;
  Px[39][3] = 0;
  Py[39][3] = 0;
  Vx[39] = 0;
  Vy[39] = 0;
  P[39][1] = 0;
  P[39][2] = 0;

  tttt = qbf_timer() + ts;
  ufo1 = 0;
  ufo2 = 0;
  cenXoff = 0;
  cenYoff = 0;

  cenX = Px[ (size_t)cen ][3];
  cenY = Py[ (size_t)cen ][3];

  LABEL_703:;
  explosion = 0;
  explosion1 = 0;
  QBM_gosub(_Q_env, LABEL_405);
  _qb_gosub_return(_Q_env);

  // 'SUBROUTINE save data to file
  LABEL_600:;
  qb_locate(_Q_env, 9, 60);
  qb_stdprint_str_const(_Q_env, "8 charaters a-z 0-9", 19, FALSE);
  qb_locate(_Q_env, 10, 60);
  qb_stdprint_str_const(_Q_env, "Save File: ", 11, FALSE);
  qb_stdinput_str_const(_Q_env, "", 0, &filename_str, FALSE, FALSE);
  if (_qb_str_equals_const(filename_str, "", 0)) {
    QBM_gosub(_Q_env, LABEL_405);
    _qb_gosub_return(_Q_env);
  }
  {
    QBM_new_str(_Q_tmp);
    QBM_new_const_str(_Q_tmp_rnd, ".rnd", 4);
    _qb_str_concat_direct(&_Q_tmp, filename_str, _Q_tmp_rnd);
    _Q_file1 = qb_open_reclen(_Q_env, _Q_tmp, "R", 1427);
    _qb_free_str(&_Q_tmp);
    _qb_free_str(&_Q_tmp_rnd);
  }
  if (qbf_lof(_Q_file1) < 1) { goto LABEL_601; }
  qb_locate(_Q_env, 11, 60);
  qb_stdprint_str_const(_Q_env, "File exists", 11, FALSE);;
  qb_locate(_Q_env, 12, 60);
  qb_stdprint_str_const(_Q_env, "overwrite? ", 11, FALSE);
  qb_stdinput_str_const(_Q_env, "", 0, &z_str, FALSE, FALSE);
  {
    QBM_new_str(_Q_tmp_1);
    QBM_new_str(_Q_tmp_2);
    qbf_left_str_direct(&_Q_tmp_1, y_str, 1);
    qbf_ucase_str_direct(&_Q_tmp_2, _Q_tmp_1);
    int _Q_cond = _qb_str_equals_const(_Q_tmp_2, "Y", 1);
    _qb_free_str(&_Q_tmp_1);
    _qb_free_str(&_Q_tmp_2);
    if (_Q_cond) {
      goto LABEL_601;
    }
  }
  for (i = 9; i <= 12; i++) {
      qb_locate(_Q_env, i, 60);
      qb_stdprint_str_const(_Q_env, "                  ", 18, FALSE);
  }
  qb_close(_Q_file1);
  goto LABEL_600;
  LABEL_601:;
  qb_close(_Q_file1);
  LABEL_620: __attribute__((unused));
  QBM_gosub(_Q_env, LABEL_405);
  goto LABEL_801;

  // 'SUBROUTINE Timed back-up
  LABEL_800:;
  _qb_set_str_const(&filename_str, "OSBACKUP", 8);
  LABEL_801:;
  chkBYTE = chkBYTE + 1;
  if (chkBYTE > 58) { chkBYTE = 1; }
  qbf_chr_str(&outSTR_str, chkBYTE + 64);
  {
    QBM_new_const_str(_Q_tmp, "ORBIT5S        ", 15);
    _qb_str_concat(&outSTR_str, outSTR_str, _Q_tmp);
    _qb_free_str(&_Q_tmp);
  }
  {
    QBM_new_str(_Q_tmp);
    qbf_mks_str(&_Q_tmp, eng);
    _qb_str_concat(&outSTR_str, outSTR_str, _Q_tmp);
    _qb_free_str(&_Q_tmp);
  }
  {
    QBM_new_str(_Q_tmp);
    qbf_mki_str(&_Q_tmp, vflag);
    _qb_str_concat(&outSTR_str, outSTR_str, _Q_tmp);
    _qb_free_str(&_Q_tmp);
  }
  {
    QBM_new_str(_Q_tmp);
    qbf_mki_str(&_Q_tmp, Aflag);
    _qb_str_concat(&outSTR_str, outSTR_str, _Q_tmp);
    _qb_free_str(&_Q_tmp);
  }
  {
    QBM_new_str(_Q_tmp);
    qbf_mki_str(&_Q_tmp, Sflag);
    _qb_str_concat(&outSTR_str, outSTR_str, _Q_tmp);
    _qb_free_str(&_Q_tmp);
  }
  {
    QBM_new_str(_Q_tmp);
    qbf_mkd_str(&_Q_tmp, Are);
    _qb_str_concat(&outSTR_str, outSTR_str, _Q_tmp);
    _qb_free_str(&_Q_tmp);
  }
  {
    QBM_new_str(_Q_tmp);
    qbf_mkd_str(&_Q_tmp, mag);
    _qb_str_concat(&outSTR_str, outSTR_str, _Q_tmp);
    _qb_free_str(&_Q_tmp);
  }
  {
    QBM_new_str(_Q_tmp);
    qbf_mks_str(&_Q_tmp, Sangle);
    _qb_str_concat(&outSTR_str, outSTR_str, _Q_tmp);
    _qb_free_str(&_Q_tmp);
  }
  {
    QBM_new_str(_Q_tmp);
    qbf_mki_str(&_Q_tmp, cen);
    _qb_str_concat(&outSTR_str, outSTR_str, _Q_tmp);
    _qb_free_str(&_Q_tmp);
  }
  {
    QBM_new_str(_Q_tmp);
    qbf_mki_str(&_Q_tmp, targ);
    _qb_str_concat(&outSTR_str, outSTR_str, _Q_tmp);
    _qb_free_str(&_Q_tmp);
  }
  {
    QBM_new_str(_Q_tmp);
    qbf_mki_str(&_Q_tmp, ref);
    _qb_str_concat(&outSTR_str, outSTR_str, _Q_tmp);
    _qb_free_str(&_Q_tmp);
  }
  {
    QBM_new_str(_Q_tmp);
    qbf_mki_str(&_Q_tmp, trail);
    _qb_str_concat(&outSTR_str, outSTR_str, _Q_tmp);
    _qb_free_str(&_Q_tmp);
  }
  {
    QBM_new_str(_Q_tmp);
    qbf_mks_str(&_Q_tmp, Cdh);
    _qb_str_concat(&outSTR_str, outSTR_str, _Q_tmp);
    _qb_free_str(&_Q_tmp);
  }
  {
    QBM_new_str(_Q_tmp);
    qbf_mks_str(&_Q_tmp, SRB);
    _qb_str_concat(&outSTR_str, outSTR_str, _Q_tmp);
    _qb_free_str(&_Q_tmp);
  }
  {
    QBM_new_str(_Q_tmp);
    qbf_mki_str(&_Q_tmp, tr);
    _qb_str_concat(&outSTR_str, outSTR_str, _Q_tmp);
    _qb_free_str(&_Q_tmp);
  }
  {
    QBM_new_str(_Q_tmp);
    qbf_mki_str(&_Q_tmp, dte);
    _qb_str_concat(&outSTR_str, outSTR_str, _Q_tmp);
    _qb_free_str(&_Q_tmp);
  }
  {
    QBM_new_str(_Q_tmp);
    qbf_mkd_str(&_Q_tmp, ts);
    _qb_str_concat(&outSTR_str, outSTR_str, _Q_tmp);
    _qb_free_str(&_Q_tmp);
  }
  {
    QBM_new_str(_Q_tmp);
    qbf_mkd_str(&_Q_tmp, OLDts);
    _qb_str_concat(&outSTR_str, outSTR_str, _Q_tmp);
    _qb_free_str(&_Q_tmp);
  }
  {
    QBM_new_str(_Q_tmp);
    qbf_mks_str(&_Q_tmp, vernP_float);
    _qb_str_concat(&outSTR_str, outSTR_str, _Q_tmp);
    _qb_free_str(&_Q_tmp);
  }
  {
    QBM_new_str(_Q_tmp);
    qbf_mki_str(&_Q_tmp, Eflag);
    _qb_str_concat(&outSTR_str, outSTR_str, _Q_tmp);
    _qb_free_str(&_Q_tmp);
  }
  {
    QBM_new_str(_Q_tmp);
    qbf_mki_str(&_Q_tmp, year);
    _qb_str_concat(&outSTR_str, outSTR_str, _Q_tmp);
    _qb_free_str(&_Q_tmp);
  }
  {
    QBM_new_str(_Q_tmp);
    qbf_mki_str(&_Q_tmp, day);
    _qb_str_concat(&outSTR_str, outSTR_str, _Q_tmp);
    _qb_free_str(&_Q_tmp);
  }
  {
    QBM_new_str(_Q_tmp);
    qbf_mki_str(&_Q_tmp, hr);
    _qb_str_concat(&outSTR_str, outSTR_str, _Q_tmp);
    _qb_free_str(&_Q_tmp);
  }
  {
    QBM_new_str(_Q_tmp);
    qbf_mki_str(&_Q_tmp, min);
    _qb_str_concat(&outSTR_str, outSTR_str, _Q_tmp);
    _qb_free_str(&_Q_tmp);
  }
  {
    QBM_new_str(_Q_tmp);
    qbf_mkd_str(&_Q_tmp, sec);
    _qb_str_concat(&outSTR_str, outSTR_str, _Q_tmp);
    _qb_free_str(&_Q_tmp);
  }
  {
    QBM_new_str(_Q_tmp);
    qbf_mks_str(&_Q_tmp, AYSEangle);
    _qb_str_concat(&outSTR_str, outSTR_str, _Q_tmp);
    _qb_free_str(&_Q_tmp);
  }
  {
    QBM_new_str(_Q_tmp);
    qbf_mki_str(&_Q_tmp, AYSEscrape);
    _qb_str_concat(&outSTR_str, outSTR_str, _Q_tmp);
    _qb_free_str(&_Q_tmp);
  }
  {
    QBM_new_str(_Q_tmp);
    qbf_mks_str(&_Q_tmp, Ztel[15]);
    _qb_str_concat(&outSTR_str, outSTR_str, _Q_tmp);
    _qb_free_str(&_Q_tmp);
  }
  {
    QBM_new_str(_Q_tmp);
    qbf_mks_str(&_Q_tmp, Ztel[16]);
    _qb_str_concat(&outSTR_str, outSTR_str, _Q_tmp);
    _qb_free_str(&_Q_tmp);
  }
  {
    QBM_new_str(_Q_tmp);
    qbf_mks_str(&_Q_tmp, HABrotate);
    _qb_str_concat(&outSTR_str, outSTR_str, _Q_tmp);
    _qb_free_str(&_Q_tmp);
  }
  {
    QBM_new_str(_Q_tmp);
    qbf_mki_str(&_Q_tmp, AYSE);
    _qb_str_concat(&outSTR_str, outSTR_str, _Q_tmp);
    _qb_free_str(&_Q_tmp);
  }
  {
    QBM_new_str(_Q_tmp);
    qbf_mks_str(&_Q_tmp, Ztel[9]);
    _qb_str_concat(&outSTR_str, outSTR_str, _Q_tmp);
    _qb_free_str(&_Q_tmp);
  }
  {
    QBM_new_str(_Q_tmp);
    qbf_mki_str(&_Q_tmp, MODULEflag);
    _qb_str_concat(&outSTR_str, outSTR_str, _Q_tmp);
    _qb_free_str(&_Q_tmp);
  }
  {
    QBM_new_str(_Q_tmp);
    qbf_mks_str(&_Q_tmp, AYSEdist);
    _qb_str_concat(&outSTR_str, outSTR_str, _Q_tmp);
    _qb_free_str(&_Q_tmp);
  }
  {
    QBM_new_str(_Q_tmp);
    qbf_mks_str(&_Q_tmp, OCESSdist);
    _qb_str_concat(&outSTR_str, outSTR_str, _Q_tmp);
    _qb_free_str(&_Q_tmp);
  }
  {
    QBM_new_str(_Q_tmp);
    qbf_mki_str(&_Q_tmp, explosion);
    _qb_str_concat(&outSTR_str, outSTR_str, _Q_tmp);
    _qb_free_str(&_Q_tmp);
  }
  {
    QBM_new_str(_Q_tmp);
    qbf_mki_str(&_Q_tmp, explosion1);
    _qb_str_concat(&outSTR_str, outSTR_str, _Q_tmp);
    _qb_free_str(&_Q_tmp);
  }
  {
    QBM_new_str(_Q_tmp);
    qbf_mks_str(&_Q_tmp, Ztel[1]);
    _qb_str_concat(&outSTR_str, outSTR_str, _Q_tmp);
    _qb_free_str(&_Q_tmp);
  }
  {
    QBM_new_str(_Q_tmp);
    qbf_mks_str(&_Q_tmp, Ztel[2]);
    _qb_str_concat(&outSTR_str, outSTR_str, _Q_tmp);
    _qb_free_str(&_Q_tmp);
  }
  {
    QBM_new_str(_Q_tmp);
    qbf_mkl_str(&_Q_tmp, NAVmalf);
    _qb_str_concat(&outSTR_str, outSTR_str, _Q_tmp);
    _qb_free_str(&_Q_tmp);
  }
  {
    QBM_new_str(_Q_tmp);
    qbf_mks_str(&_Q_tmp, Ztel[14]);
    _qb_str_concat(&outSTR_str, outSTR_str, _Q_tmp);
    _qb_free_str(&_Q_tmp);
  }
  {
    QBM_new_str(_Q_tmp);
    qbf_mks_str(&_Q_tmp, LONGtarg);
    _qb_str_concat(&outSTR_str, outSTR_str, _Q_tmp);
    _qb_free_str(&_Q_tmp);
  }
  {
    QBM_new_str(_Q_tmp);
    qbf_mks_str(&_Q_tmp, Pr);
    _qb_str_concat(&outSTR_str, outSTR_str, _Q_tmp);
    _qb_free_str(&_Q_tmp);
  }
  {
    QBM_new_str(_Q_tmp);
    qbf_mks_str(&_Q_tmp, Agrav);
    _qb_str_concat(&outSTR_str, outSTR_str, _Q_tmp);
    _qb_free_str(&_Q_tmp);
  }
  for (i = 1; i <= 39; i++) {
    {
      QBM_new_str(_Q_tmp);
      qbf_mkd_str(&_Q_tmp, Px[ (size_t)i ][3]);
      _qb_str_concat(&outSTR_str, outSTR_str, _Q_tmp);
      _qb_free_str(&_Q_tmp);
    }
    {
      QBM_new_str(_Q_tmp);
      qbf_mkd_str(&_Q_tmp, Py[ (size_t)i ][3]);
      _qb_str_concat(&outSTR_str, outSTR_str, _Q_tmp);
      _qb_free_str(&_Q_tmp);
    }
    {
      QBM_new_str(_Q_tmp);
      qbf_mkd_str(&_Q_tmp, Vx[ (size_t)i ]);
      _qb_str_concat(&outSTR_str, outSTR_str, _Q_tmp);
      _qb_free_str(&_Q_tmp);
    }
    {
      QBM_new_str(_Q_tmp);
      qbf_mkd_str(&_Q_tmp, Vy[ (size_t)i ]);
      _qb_str_concat(&outSTR_str, outSTR_str, _Q_tmp);
      _qb_free_str(&_Q_tmp);
    }
  }
  {
    QBM_new_str(_Q_tmp);
    qbf_mks_str(&_Q_tmp, fuel);
    _qb_str_concat(&outSTR_str, outSTR_str, _Q_tmp);
    _qb_free_str(&_Q_tmp);
  }
  {
    QBM_new_str(_Q_tmp);
    qbf_mks_str(&_Q_tmp, AYSEfuel);
    _qb_str_concat(&outSTR_str, outSTR_str, _Q_tmp);
    _qb_free_str(&_Q_tmp);
  }
  {
    QBM_new_str(_Q_tmp);
    qbf_chr_str(&_Q_tmp, chkBYTE + 64);
    _qb_str_concat(&outSTR_str, outSTR_str, _Q_tmp);
    _qb_free_str(&_Q_tmp);
  }
  {
    QBM_new_str(_Q_tmp);
    QBM_new_const_str(_Q_tmp_rnd, ".RND", 4);
    _qb_str_concat_direct(&_Q_tmp, filename_str, _Q_tmp_rnd);
    _Q_file1 = qb_open_reclen(_Q_env, _Q_tmp, "R", 1427);
    _qb_free_str(&_Q_tmp);
    _qb_free_str(&_Q_tmp_rnd);
  }
  qb_fput(_Q_file1, 1, outSTR_str);
  qb_close(_Q_file1);

  k = 1;
  LABEL_813:;
  _Q_file1 = qb_open_reclen_cstr(_Q_env, "MST.RND", "R", 26);
  qbf_space_str(&inpSTR_str, 26);
  qb_fget(_Q_file1, 1, &inpSTR_str);
  qb_close(_Q_file1);
  if (qbf_len(inpSTR_str) != 26) { goto LABEL_811; }
  qbf_left_str(&chkCHAR1_str, inpSTR_str, 1);
  qbf_right_str(&chkCHAR2_str, inpSTR_str, 1);
  if (_qb_str_equals(chkCHAR1_str, chkCHAR2_str)) { goto LABEL_816; }
  k = k + 1;
  if (k < 5) {
    goto LABEL_813;
  } else {
    fileINwarn = 1;
    goto LABEL_811;
  }
  LABEL_816:;
  k = 2;
  {
    QBM_new_str(_Q_tmp);
    qbf_mid_str(&_Q_tmp, inpSTR_str, k, 8);
    MST = qbf_cvd(_Q_tmp);
    _qb_free_str(&_Q_tmp);
    k = k + 8;
  }
  {
    QBM_new_str(_Q_tmp);
    qbf_mid_str(&_Q_tmp, inpSTR_str, k, 8);
    EST = qbf_cvd(_Q_tmp);
    _qb_free_str(&_Q_tmp);
    k = k + 8;
  }
  {
    QBM_new_str(_Q_tmp);
    qbf_mid_str(&_Q_tmp, inpSTR_str, k, 8);
    LONGtarg = qbf_cvd(_Q_tmp) / RAD;
    _qb_free_str(&_Q_tmp);
  }
  LONGtarg = LONGtarg + pi;
  Ltx = (P[ (size_t)ref ][5] * qbf_sin(LONGtarg));
  Lty = (P[ (size_t)ref ][5] * qbf_cos(LONGtarg));
  Ltr = ref;

  LABEL_811:;
  k = 1;
  LABEL_819:;
  _Q_file1 = qb_open_reclen_cstr(_Q_env, "ORBITSSE.RND", "R", 210);
  qbf_space_str(&inpSTR_str, 210);
  qb_fget(_Q_file1, 1, &inpSTR_str);
  qb_close(_Q_file1);
  if (qbf_len(inpSTR_str) != 210) {
    qb_locate(_Q_env, 25, 1);
    qb_color(_Q_env, 12);
    qb_stdprint_str_const(_Q_env, "ENG telem", 9, FALSE);
    goto LABEL_812;
  }
  qbf_left_str(&chkCHAR1_str, inpSTR_str, 1);
  qbf_right_str(&chkCHAR2_str, inpSTR_str, 1);
  if (_qb_str_equals(chkCHAR1_str, chkCHAR2_str)) { goto LABEL_818; }
  k = k + 1;
  if (k < 3) { goto LABEL_819; }
  qb_locate(_Q_env, 25, 1);
  qb_color(_Q_env, 12);
  qb_stdprint_str_const(_Q_env, "ENG telem*", 10, FALSE);
  goto LABEL_812;
  LABEL_818:;
  k = 2;
  for (i = 1; i <= 26; i++) {
    QBM_new_str(_Q_tmp);
    qbf_mid_str(&_Q_tmp, inpSTR_str, k, 8);
    Ztel[ (size_t)i ] = qbf_cvd(_Q_tmp);
    _qb_free_str(&_Q_tmp);
    k = k + 8;
  }
  RADAR = (2 & (int32_t)Ztel[8]);
  INS = 4 & ((int32_t)Ztel[8]);
  LOS = 8 & ((int32_t)Ztel[8]);
  Ztel[8] = (1 & (int32_t)Ztel[8]);
  if ((8 & (int32_t)Ztel[26]) == 8) { goto LABEL_9100; }
  NAVmalf = Ztel[1];
  Ztel[1] = (2 & (int32_t)Ztel[1]) / 2;
  // 'Ztel(2) = engine force factor
  fuel = Ztel[3]; // 'HAB fuel mass
  AYSEfuel = Ztel[4]; // 'AYSE fuel mass
  // 'Ztel(5) = HAB explosion
  // 'Ztel(6) = AYSE explosion
  // 'Ztel(7) = Ztel7: Ztel7 = 0
  if (Ztel[7] == 2 && MODULEflag == 0) { QBM_gosub(_Q_env, LABEL_3200); }
  if (Ztel[7] == 1 && MODULEflag > 0) { QBM_gosub(_Q_env, LABEL_3200); }
  if (Ztel[8] == 1) {
    ts = 0.125;
    TSindex = 4;
  }
  // 'Ztel(9) = rshield

  if ((1 & (int32_t)Ztel[10]) == 1 && vernP_float < 100) {
    vernP_float = vernP_float + 25 * ts;
  }
  if (vernP_float > 120) { vernP_float = 120; }
  if (vernP_float < 0) { vernP_float = 0; }
  vernCNT = (16 & (int32_t)Ztel[10]) / 16;
  if ((2 & (int32_t)Ztel[10]) == 2) {
    Cdh = 0.0006;
  } else {
    Cdh = 0.0002;
  }
  if ((4 & (int32_t)Ztel[10]) == 4 && SRBtimer < 1) { SRBtimer = 220; }
  Zx = (224 & (int32_t)Ztel[10]);
  if (Zx > 0) {
    HABrotMALF = (Zx - 128) / 32;
  } else {
    HABrotMALF = 0;
  }
  Zx = (7680 & (int32_t)Ztel[10]);

  if (explosion > 0) { explosion = explosion - 1; }
  if (explosion1 > 0) { explosion1 = explosion1 - 1; }
  if (Ztel[1] == 1) { Sflag = 1; }
  if (DISPflag == 0) {
    qb_color(_Q_env, 7 + (5 * Ztel[1]));
    qb_locate(_Q_env, 25, 2);
    qb_stdprint_str_const(_Q_env, "NAVmode", 7, FALSE);
  }
  qb_color(_Q_env, 15);
  if (ufoTIMER > 0) {
    ufoTIMER = ufoTIMER - 1;
    goto LABEL_812;
  }

  if (Ztel[17] == 2) {
    ufo1 = 0;
    Px[38][3] = 0;
    Py[38][3] = 0;
    ufo2 = 0;
    Px[39][3] = 0;
    Py[39][3] = 0;
  }
  if (Ztel[23] >= 0) { goto LABEL_815; }
  ufoTIMER = 10;
  ufo1 = 0;
  ufo2 = 0;
  Zt = qbf_abs(Ztel[23]);
  Px[ (size_t)Zt ][3] = Px[38][3];
  Py[ (size_t)Zt ][3] = Py[38][3];
  Vx[ (size_t)Zt ] = Vx[38];
  Vy[ (size_t)Zt ] = Vy[38];
  P[ (size_t)Zt ][1] = P[38][1];
  P[ (size_t)Zt ][2] = P[38][2];
  Px[38][3] = 0;
  Py[38][3] = 0;
  Px[39][3] = 0;
  Py[39][3] = 0;
  CONflag2 = 0;
  goto LABEL_812;
  LABEL_815:;
  if (Ztel[23] < 38 && ufo2 == 0 && ufo1 == 1) { QBM_gosub(_Q_env, LABEL_7100); }
  if (Ztel[23] == 39 && ufo2 == 1) {
    explCENTER = 39;
    QBM_gosub(_Q_env, LABEL_6000);
  }
  LABEL_812:;
  qb_color(_Q_env, 15);
  _qb_gosub_return(_Q_env);

  // 'Confirm end program
  LABEL_900:;
  qb_locate(_Q_env, 10, 60);
  qb_stdinput_str_const(_Q_env, "End Program ", 12, &z_str, FALSE, FALSE);
  {
    QBM_new_str(_Q_tmp);
    qbf_ucase_str_direct(&_Q_tmp, z_str);
    if (_qb_str_equals_const(_Q_tmp, "Y", 1)) {
      qb_end(_Q_env);
    }
    _qb_free_str(&_Q_tmp);
  }
  qb_locate(_Q_env, 10, 60);
  qb_stdprint_str_const(_Q_env, "                   ", 19, FALSE);
  _qb_gosub_return(_Q_env);

  // 'Orbit Projection
  LABEL_3000:;
  QBM_gosub(_Q_env, LABEL_3005);
  QBM_gosub(_Q_env, LABEL_3008);
  QBM_gosub(_Q_env, LABEL_3006);
  L = 2 * orbA;
  if (ecc < 1) { L = (1 - _qbf_pow(ecc, 2)) * orbA; }
  if (ecc > 1) { L = (_qbf_pow(ecc, 2) - 1) * orbA; }
  difX = Px[ (size_t)ORrefOBJ ][3] - Px[28][3];
  difY = Py[ (size_t)ORrefOBJ ][3] - Py[28][3];
  QBM_gosub(_Q_env, LABEL_5000);
  r = qbf_sqr(_qbf_pow(difX, 2) + _qbf_pow(difY, 2));
  term = (L / r) - 1;
  if (qbf_abs(ecc) < 0.0000001) { ecc = qbf_sgn(ecc) * 0.0000001; }
  term = term / ecc;
  if (qbf_abs(term) > 1) {
    num = 0;
  } else {
    num = eccFLAG * qbf_sqr(1 - _qbf_pow(term, 2));
  }
  dem = 1 - term;
  difA = 2 * qbf_atn(num / dem);
  difA = 3.1415926 - difA - angle;
  stp = 0.1;
  lim1 = -180;
  lim2 = 180;
  if (ecc < 1) {
    lim1 = 0;
    lim2 = 179;
  }
  if (ecc > 1) { QBM_gosub(_Q_env, LABEL_3010); }
  FRAMEflag = 0;
  LABEL_3003:;
  QBM_bidifor(i, lim1, lim2, stp) {
    angle = i / 57.29578;
    d = 1 + (ecc * qbf_cos(angle));
    r = L / d;
    difX = (r * qbf_sin(angle - difA)) + Px[ (size_t)ORrefOBJ ][3];
    difY = (r * qbf_cos(angle - difA)) + Py[ (size_t)ORrefOBJ ][3];
    if (ecc < 1) { goto LABEL_3018; }
    if (qbf_abs(i - lim1) < stp) {
      difX1 = difX;
      difY1 = difY;
    }
    if (qbf_abs(i - lim2) < stp) {
      difX2 = difX;
      difY2 = difY;
    }
    if (qbf_abs(i - 0) < stp) {
      difX3 = difX;
      difY3 = difY;
    }
    goto LABEL_3019;
    LABEL_3018:;
    if (qbf_abs(i - 180) < stp) {
      difX1 = difX;
      difY1 = difY;
    }
    if (qbf_abs(i - lim2) < stp) {
      difX3 = difX;
      difY3 = difY;
    }
    LABEL_3019:;
    difX = 300 + ((difX - cenX) * mag / AU);
    difY = 220 + ((difY - cenY) * mag / AU);
    if (qbf_abs(300 - difX) > 400 || qbf_abs(220 - difY) > 300) {
      FRAMEflag = 0;
      goto LABEL_3002;
    }
    if (FRAMEflag == 0) {
      qb_pset(_Q_env, difX, difY, 15);
    } else {
      qb_lineto(_Q_env, difX, difY, 15);
    }
    qb_pset(_Q_env, difX, difY, 15);
    FRAMEflag = 1;
    LABEL_3002:;
  }
  if (ecc < 1 && lim2 == 179) {
    lim1 = 179;
    lim2 = 181;
    stp = 0.001;
    goto LABEL_3003;
  }
  if (ecc < 1 && lim2 == 181) {
    lim1 = 181;
    lim2 = 359.9;
    stp = 0.1;
    goto LABEL_3003;
  }
  QBM_gosub(_Q_env, LABEL_3020);
  _qb_gosub_return(_Q_env);

  LABEL_3005:;
  if (ORref == 1) {
    ORrefD = Dtarg;
    ORrefOBJ = targ;
    goto LABEL_3009;
  }
  difX = Vx[ (size_t)ref ] - Vx[28];
  difY = Vy[ (size_t)ref ] - Vy[28];
  QBM_gosub(_Q_env, LABEL_5000);
  ORrefOBJ = ref;
  VangleDIFF = Aref - angle;
  ORrefD = Dref;
  LABEL_3009:;
  _qb_gosub_return(_Q_env);

  LABEL_3006:;
  orbEk =
    (
      (
        _qbf_pow(Vx[28] - Vx[ (size_t)ORrefOBJ ], 2) +
        _qbf_pow(Vy[28] - Vy[ (size_t)ORrefOBJ ], 2)
      )
    ) / 2;
  orbEp = -1 * G * P[ (size_t)ORrefOBJ ][4] / ORrefD;
  orbD = G * P[ (size_t)ORrefOBJ ][4];
  if (orbD == 0) { orbD = G * 1; }
  L2 = _qbf_pow(ORrefD * Vtan, 2);
  orbE = orbEk + orbEp;
  term2 = 2 * orbE * L2 / (orbD * orbD);
  ecc = qbf_sqr(1 + term2);
  if (orbE == 0) {
    qb_locate(_Q_env, 20, 7);
    {
      QBM_new_str(_Q_tmp);
      qbf_space_str_direct(&_Q_tmp, 9);
      qb_stdprint_str(_Q_env, _Q_tmp, FALSE);
      _qb_free_str(&_Q_tmp);
    }
    qb_locate(_Q_env, 19, 7);
    {
      QBM_new_str(_Q_tmp);
      qbf_space_str_direct(&_Q_tmp, 9);
      qb_stdprint_str(_Q_env, _Q_tmp, FALSE);
      _qb_free_str(&_Q_tmp);
    }
    goto LABEL_3007;
  }
  orbA = orbD / qbf_abs(2 * orbE);
  PROJmax = orbA * (1 + ecc);
  PROJmin = orbA * (1 - ecc);
  if (ecc == 1) { PROJmin = orbA; }
  if (ecc > 1) { PROJmin = orbA * (ecc - 1); }
  if (DISPflag == 1) { _qb_gosub_return(_Q_env); }
  if (targDISP == 0) { _qb_gosub_return(_Q_env); }
  if ((8 & (int32_t)NAVmalf) == 8) { _qb_gosub_return(_Q_env); }
  PROJmin = (PROJmin - P[ (size_t)ORrefOBJ ][5]) / 1000;
  PROJmax = (PROJmax - P[ (size_t)ORrefOBJ ][5]) / 1000;
  qb_locate(_Q_env, 19, 7);
  if (qbf_abs(PROJmin) > 899999) {
    QBM_std_pu_const_double(_Q_env, "##.##^^^^", 9, PROJmin, FALSE);
  } else {
    QBM_std_pu_const_double(_Q_env, "######.##", 9, PROJmin, FALSE);
  }
  qb_locate(_Q_env, 20, 7);
  if (ecc >= 1) {
    qb_stdprint_str_const(_Q_env, "  -------", 9, FALSE);
    goto LABEL_3007;
  }
  if (qbf_abs(PROJmax) > 899999) {
    QBM_std_pu_const_double(_Q_env, "##.##^^^^", 9, PROJmax, FALSE);
  } else {
    QBM_std_pu_const_double(_Q_env, "######.##", 9, PROJmax, FALSE);
  }
  LABEL_3007:;
  _qb_gosub_return(_Q_env);

  LABEL_3008:;
  Vcen =
    qbf_sqr(
      _qbf_pow(Vx[28] - Vx[ (size_t)ORrefOBJ ], 2) +
      _qbf_pow(Vy[28] - Vy[ (size_t)ORrefOBJ ], 2)
    ) *
    -1 *
    qbf_cos(VangleDIFF);
  Vtan =
    qbf_sqr(
      _qbf_pow(Vx[28] - Vx[ (size_t)ORrefOBJ ], 2) +
      _qbf_pow(Vy[28] - Vy[ (size_t)ORrefOBJ ], 2)
    ) *
    qbf_sin(VangleDIFF);
  if (DISPflag == 1) { _qb_gosub_return(_Q_env); }
  if (targDISP == 0) { _qb_gosub_return(_Q_env); }
  if ((16384 & (int32_t)NAVmalf) == 16384) { _qb_gosub_return(_Q_env); }
  qb_locate(_Q_env, 16, 7);
  if (qbf_abs(Vcen) > 99999) {
    QBM_std_pu_const_double(_Q_env, "##.##^^^^", 9, Vcen, FALSE);
  } else {
    QBM_std_pu_const_double(_Q_env, "######.##", 9, Vcen, FALSE);
  }
  qb_locate(_Q_env, 17, 7);
  if (qbf_abs(Vtan) > 99999) {
    QBM_std_pu_const_double(_Q_env, "##.##^^^^", 9, Vtan, FALSE);
  } else {
    QBM_std_pu_const_double(_Q_env, "######.##", 9, Vtan, FALSE);
  }
  eccFLAG = qbf_sgn(Vcen) * qbf_sgn(Vtan);
  if (Vcen == 0) { eccFLAG = qbf_sgn(Vtan); }
  if (Vtan == 0) { eccFLAG = qbf_sgn(Vcen); }
  _qb_gosub_return(_Q_env);

  LABEL_3010:;
  term = 1 / ecc;
  dem = 1 + qbf_sqr(1 - _qbf_pow(term, 2));
  term = term / dem;
  term = (2 * qbf_atn(term) * 57.29578) + 90;
  lim1 = -1 * term;
  lim2 = term;
  _qb_gosub_return(_Q_env);

  LABEL_3020:;
  if (targ == ref) { _qb_gosub_return(_Q_env); }
  difX = difX1 - Px[ (size_t)ref ][3];
  difY = difY1 - Py[ (size_t)ref ][3];
  r = qbf_sqr(_qbf_pow(difY, 2) + _qbf_pow(difX, 2));
  QBM_gosub(_Q_env, LABEL_5000);
  AtoAPOAPSIS = qbf_abs(angle - Atr);
  if (AtoAPOAPSIS > 3.1415926535) { AtoAPOAPSIS = 6.283185307 - AtoAPOAPSIS; }
  qb_locate(_Q_env, 27, 2);
  qb_stdprint_str_const(_Q_env, "\xe9 tRa", 5, FALSE);
  qb_locate(_Q_env, 27, 10);
  QBM_std_pu_const_double(_Q_env, "###", 3, AtoAPOAPSIS * RAD, FALSE);
  qb_stdprint_str_const(_Q_env, "\xf8", 1, FALSE);
  if (ecc < 1) { goto LABEL_3021; }
  difX = difX2 - Px[ (size_t)ref ][3];
  difY = difY2 - Py[ (size_t)ref ][3];
  r = qbf_sqr(_qbf_pow(difY, 2) + _qbf_pow(difX, 2));
  QBM_gosub(_Q_env, LABEL_5000);
  AtoAPOAPSIS = qbf_abs(angle - Atr);
  if (AtoAPOAPSIS > 3.1415926535) { AtoAPOAPSIS = 6.283185307 - AtoAPOAPSIS; }
  QBM_std_pu_const_double(_Q_env, "#####", 5, AtoAPOAPSIS * RAD, FALSE);
  qb_stdprint_str_const(_Q_env, "\xf8", 1, FALSE);
  LABEL_3021:;
  difX = difX3 - Px[ (size_t)ref ][3];
  difY = difY3 - Py[ (size_t)ref ][3];
  r = qbf_sqr(_qbf_pow(difY, 2) + _qbf_pow(difX, 2));
  QBM_gosub(_Q_env, LABEL_5000);
  AtoAPOAPSIS = qbf_abs(angle - Atr);
  if (AtoAPOAPSIS > 3.1415926535) { AtoAPOAPSIS = 6.283185307 - AtoAPOAPSIS; }
  qb_locate(_Q_env, 28, 2);
  qb_stdprint_str_const(_Q_env, "\xe9 tRp", 5, FALSE);
  qb_locate(_Q_env, 28, 10);
  QBM_std_pu_const_double(_Q_env, "###", 3, AtoAPOAPSIS * RAD, FALSE);
  qb_stdprint_str_const(_Q_env, "\xf8", 1, FALSE);
  _qb_gosub_return(_Q_env);
  // '****************************************************

  // 'Restore orbital altitude of ISS after large time step
  LABEL_3100:;
  difX = Px[3][3] - Px[35][3];
  difY = Py[3][3] - Py[35][3];
  QBM_gosub(_Q_env, LABEL_5000);
  Px[35][3] = Px[3][3] + ((P[3][5] + 365000) * qbf_sin(angle));
  Py[35][3] = Py[3][3] + ((P[3][5] + 365000) * qbf_cos(angle));
  Vx[35] = Vx[3] + (qbf_sin(angle + 1.570796) * qbf_sqr(G * P[3][4] / (P[3][5] + 365000)));
  Vy[35] = Vy[3] + (qbf_cos(angle + 1.570796) * qbf_sqr(G * P[3][4] / (P[3][5] + 365000)));
  _qb_gosub_return(_Q_env);

  LABEL_3200:;
  // 'LOCATE 23, 40: PRINT CONflag;
  if (CONflag == 0) { goto LABEL_3299; }
  if (MODULEflag == 0) { goto LABEL_3210; }
  difX = Px[28][3] - Px[36][3];
  difY = Py[28][3] - Py[36][3];
  r = qbf_sqr(_qbf_pow(difY, 2) + _qbf_pow(difX, 2));
  if (r > 90) { goto LABEL_3299; }
  if (targ == 36) { targ = CONtarg; }
  if (ref == 36) { ref = CONtarg; }
  if (cen == 36) { cen = 28; }
  MODULEflag = 0;
  QBM_gosub(_Q_env, LABEL_405);
  goto LABEL_3299;

  LABEL_3210:;
  Px[36][3] = Px[28][3] - ((80 - P[36][5]) * qbf_sin(Sangle));
  Py[36][3] = Py[28][3] - ((80 - P[36][5]) * qbf_cos(Sangle));
  P[36][1] = Px[36][3] - Px[ (size_t)CONtarg ][3];
  P[36][2] = Py[36][3] - Py[ (size_t)CONtarg ][3];
  MODULEflag = CONtarg;
  Vx[36] = Vx[ (size_t)MODULEflag ];
  Vy[36] = Vy[ (size_t)MODULEflag ];

  LABEL_3299:;
  _qb_gosub_return(_Q_env);

  LABEL_5000:;
  if (difY == 0) {
    if (difX < 0) {
      angle = 0.5 * 3.1415926535;
    } else {
      angle = 1.5 * 3.1415926535;
    }
  } else {
    angle = qbf_atn(difX / difY);
  }
  if (difY > 0) { angle = angle + 3.1415926535; }
  if (difX > 0 && difY < 0) { angle = angle + 6.283185307; }
  _qb_gosub_return(_Q_env);

  // 'Explosions
  LABEL_6000:;
  Xexpl = 300 + (Px[ (size_t)explCENTER ][3] - cenX) * mag / AU;
  Yexpl = 220 + (Py[ (size_t)explCENTER ][3] - cenY) * mag / AU;
  // 'PLAY "ML L25 GD MB"
  if (qbf_abs(Xexpl) > 1000 || qbf_abs(Yexpl) > 1000) { goto LABEL_6001; }
  for (Xj = 0; Xj <= 14; Xj++) {
    for (Xi = 1; Xi <= (49 - (2 * Xj)); Xi++) {
      explANGLE = qbf_rnd() * 2 * 3.1415926535;
      Xexpl1 = Xexpl + (qbf_sin(explANGLE) * Xj * 2);
      Yexpl1 = Yexpl + (qbf_cos(explANGLE) * Xj * 2);

      qb_preset(_Q_env, Xexpl1, Yexpl1, 14);
    }
    for (Xi = 1; Xi <= 100000; Xi++) {}
  }
  for (Xj = 1; Xj <= 56; Xj++) {
    qb_circle(_Q_env, Xexpl, Yexpl, Xj / 2, 0);
    qb_linebox(
      _Q_env,
      Xexpl - Xj / 3,
      Yexpl - Xj / 3,
      Xexpl + Xj / 3,
      Yexpl + Xj / 3,
      0,
      QB_LINE_BOX_BF
    );
  }
  LABEL_6001:;
  // 'LOCATE 1, 35
  if (i < 0) { i = 0; }
  if (i > 39) { i = 0; }
  if (explCENTER == 39) {
    ufo2 = 0;
    Px[39][3] = 0;
    Py[39][3] = 0;
  }
  if (explCENTER == 39 && B[ (size_t)i ][0] != 28) {
    ufo1 = 0;
    Px[38][3] = 0;
    Py[38][3] = 0;
  }
  if (explCENTER == 39 && B[ (size_t)i ][0] == 28) {
    CONflag = 1;
    CONtarg = B[0][ (size_t)i ];
    Dcon = r;
    Acon = angle;
    CONacc = a;
  }
  if (explCENTER == 38 && B[ (size_t)i ][0] == 28) {
    CONflag = 1;
    CONtarg = B[0][ (size_t)i ];
    Dcon = r;
    Acon = angle;
    CONacc = a;
  }
  if (explCENTER == 38) {
    ufo1 = 0;
    Px[38][3] = 0;
    Py[38][3] = 0;
  }
  if (explCENTER == 28 || explCENTER == 32) {
    ts = 0.25;
    TSindex = 5;
  }
  if (explCENTER == 28) {
    explosion = 12;
    Ztel[2] = 0;
    Ztel[1] = 0;
    qb_locate(_Q_env, 25, 2);
    qb_stdprint_str_const(_Q_env, "NAVmode", 7, FALSE);
    qb_locate(_Q_env, 25, 11);
    qb_stdprint_str_const(_Q_env, "manual   ", 9, FALSE);
  }
  if (explCENTER == 32) { explosion1 = 12; }
  qb_color(_Q_env, 15);
  qb_locate(_Q_env, 8, 10);
  QBM_std_pu_const_double(_Q_env, "##.###", 6, ts, FALSE);
  _qb_gosub_return(_Q_env);

  LABEL_7000:;
  qb_beep(_Q_env);
  r = 100 + P[ (size_t)(Ztel[18]) ][5];

  Vx[38] = Vx[ (size_t)(Ztel[18]) ] + (200 * qbf_sin(Sangle + 3.14159));
  Vy[38] = Vy[ (size_t)(Ztel[18]) ] + (200 * qbf_cos(Sangle + 3.14159));

  Px[38][3] = Px[ (size_t)(Ztel[18]) ][3] + (r * qbf_sin(Sangle + 3.14159));
  Py[38][3] = Py[ (size_t)(Ztel[18]) ][3] + (r * qbf_cos(Sangle + 3.14159));
  ufo1 = 1;

  _qb_set_str_const(&z_str, "", 0);
  _qb_gosub_return(_Q_env);

  LABEL_7100:;
  Px[39][3] = Px[38][3];
  Py[39][3] = Py[38][3];
  difX = Px[39][3] - Px[ (size_t)(Ztel[23]) ][3];
  difY = Py[39][3] - Py[ (size_t)(Ztel[23]) ][3];
  r = qbf_sqr(_qbf_pow(difY, 2) + _qbf_pow(difX, 2));
  QBM_gosub(_Q_env, LABEL_5000);
  Vt = r / 10000;
  if (Vt > 1000) { goto LABEL_7110; }
  Vt = qbf_cint(Vt);
  V = r / Vt;
  Vx[39] = Vx[ (size_t)(Ztel[23]) ] + (V * qbf_sin(angle));
  Vy[39] = Vy[ (size_t)(Ztel[23]) ] + (V * qbf_cos(angle));
  ufo2 = 1;
  Px[39][1] = 4000;
  LABEL_7110:;
  _qb_gosub_return(_Q_env);

  LABEL_7200:;
  difX = Px[38][3] - Px[ (size_t)(Ztel[18]) ][3];
  difY = Py[38][3] - Py[ (size_t)(Ztel[18]) ][3];
  QBM_gosub(_Q_env, LABEL_5000);
  if (Ztel[21] == 0) { angle = angle - (90 / RAD); }
  if (Ztel[21] == 1) { angle = angle + (90 / RAD); }
  if (Ztel[21] == 2) { angle = angle + (180 / RAD); }
  Vx[38] = Vx[38] + (Ztel[22] * ts * qbf_sin(angle));
  Vy[38] = Vy[38] + (Ztel[22] * ts * qbf_cos(angle));
  _qb_gosub_return(_Q_env);

  LABEL_8000:;
  for (i = 1; i <= 3021; i++) {
    if (qbf_abs(300 + (Pz[ (size_t)i ][1] - cenX) * mag / AU) > 1000) { goto LABEL_8001; }
    if (qbf_abs(220 + (Pz[ (size_t)i ][2] - cenY) * mag / AU) > 1000) { goto LABEL_8001; }
    qb_pset(
      _Q_env,
      300 + (Pz[ (size_t)i ][1] - cenX) * mag / AU,
      220 + (Pz[ (size_t)i ][2] - cenY) * mag * 1 / AU,
      Pz[ (size_t)i ][0]
    );
    LABEL_8001:;
  }
  _qb_gosub_return(_Q_env);


  LABEL_8100:;
  time = (year * 31536000) + (day * 86400) + (hr * 3600) + (min * 60) + sec;
  if (dte == 2) {
    etime = MST;
  } else {
    etime = EST;
  }
  if (time > etime) {
    dtime = time - etime;
    TIMEsgn = 1;
  } else {
    dtime = etime - time;
    TIMEsgn = -1;
  }

  if (TIMEsgn == -1 && dtime < 121) {
    ts = 0.125;
    TSindex = 4;
  }
  dyr = qbf_int(dtime / 31536000);
  dday = dtime - (dyr * 31536000);
  dday = qbf_int(dday / 86400);
  dhr = dtime - (dyr * 31536000) - (dday * 86400);
  dhr = qbf_int(dhr / 3600);
  dmin = dtime - (dyr * 31536000) - (dday * 86400) - (dhr * 3600);
  dmin = qbf_int(dmin / 60);
  dsec = dtime - (dyr * 31536000) - (dday * 86400) - (dhr * 3600) - (dmin * 60);
  qb_locate(_Q_env, 25, 58);
  if (dte == 2) {
    qb_stdprint_str_const(_Q_env, "M:", 2, FALSE);
  } else {
    qb_stdprint_str_const(_Q_env, "E:", 2, FALSE);
  }
  if (TIMEsgn == -1) {
    qb_stdprint_str_const(_Q_env, "-", 1, FALSE);
  } else {
    qb_stdprint_str_const(_Q_env, " ", 1, FALSE);
  }
  qb_locate(_Q_env, 25, 61);
  QBM_std_pu_const_double(_Q_env, "####_ ", 6, dyr, FALSE);
  qb_locate(_Q_env, 25, 66);
  {
    QBPUI *_Q_ps = _qb_get_pu_ctx();
    _Q_ps = _qb_pu_add_double(_Q_ps, dday, FALSE);
    _Q_ps = _qb_pu_add_double(_Q_ps, dhr, FALSE);
    _Q_ps = _qb_pu_add_double(_Q_ps, dmin, FALSE);
    qb_stdprintusing_const(_Q_env, "###", 3, _Q_ps);
  }
  if (ts < 60) {
    qb_locate(_Q_env, 25, 75);
    QBM_std_pu_const_double(_Q_env, "###", 3, dsec, FALSE);
  }

  _qb_gosub_return(_Q_env);

  LABEL_8500:;
  _qb_set_str_const(&z_str, "  ", 2);
  x1 = 640 * ((ELEVangle * RAD) + 59.25 + 180) / 360;
  if (x1 > 640) { x1 = x1 - 640; }
  y1 = 50 * qbf_sin((x1 - 174.85) / 101.859164);
  lngW = 11520 * x1 / 640;
  latW = 5760 * (y1 + 160) / 320;
  lng = qbf_int(lngW);
  lat = qbf_int(latW);

  ja = 1 + (lng) + (lat * 11520);
  qb_fget(_Q_file3, ja, &z_str);
  h1 = qbf_cvi(z_str);

  ja = 1 + (lng) + ((lat + 1) * 11520);
  qb_fget(_Q_file3, ja, &z_str);
  h2 = qbf_cvi(z_str);


  if (lng == 11519) {
    ja = 1 + (lat * 11520);
  } else {
    ja = 1 + (lng + 1) + (lat * 11520);
  }
  qb_fget(_Q_file3, ja, &z_str);
  h3 = qbf_cvi(z_str);

  if (lng == 11519) {
    ja = 1 + ((lat + 1) * 11520);
  } else {
    ja = 1 + (lng + 1) + ((lat + 1) * 11520);
  }
  qb_fget(_Q_file3, ja, &z_str);
  h4 = qbf_cvi(z_str);

  LATdel = latW - lat;
  LNDdel = lngW - lng;
  h = h1 * (1 - LATdel) * (1 - LNGdel);
  h = h + (h2 * (LATdel) * (1 - LNGdel));
  h = h + (h3 * (1 - LATdel) * (LNGdel));
  h = h + (h4 * (LATdel) * (LNGdel));
  _qb_gosub_return(_Q_env);


  LABEL_9000: __attribute__((unused));
  qb_locate(_Q_env, 1, 30);
  if (ERL == 91) {
    qb_close(_Q_file1);
    qb_cls(_Q_env);
    qb_stdprint_str_const(_Q_env, "'stars' file is missing or incomplete", 37, FALSE);
  }

  qb_stdprint_i32(_Q_env, ERR, TRUE);
  qb_stdprint_i32(_Q_env, ERL, FALSE);

  qbf_input_str(_Q_env, &z_str, 1);
  qb_end(_Q_env);

  LABEL_9100:;
  _Q_file1 = qb_open_reclen_cstr(_Q_env, "ORBITSSE.RND", "R", 210);
  qbf_space_str(&inpSTR_str, 210);
  qb_fget(_Q_file1, 1, &inpSTR_str);
  {
    QBM_new_str(_Q_tmp);
    qbf_mkd_str(&_Q_tmp, 0);
    _qb_mid_str_set(&inpSTR_str, 202, 8, _Q_tmp);
    _qb_free_str(&_Q_tmp);
  }
  qb_fput(_Q_file1, 1, inpSTR_str);
  qb_close(_Q_file1);
  _Q_file1 = qb_open_cstr(_Q_env, "orbitstr.txt", "O");
  if (Ztel[26] == 8) {
    QBM_new_const_str(_Q_tmp, "OSBACKUP", 8);
    qb_fprint_str(_Q_file1, _Q_tmp);
    _qb_free_str(&_Q_tmp);
  }
  if (Ztel[26] == 24) {
    QBM_new_const_str(_Q_tmp, "RESTART", 7);
    qb_fprint_str(_Q_file1, _Q_tmp);
    _qb_free_str(&_Q_tmp);
  }
  qb_close(_Q_file1);
  qb_run_const(_Q_env, "orbit5va", 8);

  return 0;
}
