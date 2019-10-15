/****************************************************************************

    BData Class
        Copyright (C) 2010 David Marten qblade@web.de

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

*****************************************************************************/

#ifndef BDATA_H
#define BDATA_H


#include <QList>
#include <QColor>
#include <QLabel>
#include "../XBEM/Blade.h"
#include "../Objects/Polar.h"

class BData
{

    friend class QBEM;
    friend class MainFrame;
    friend class BEMData;

public:

    bool m_bTipLoss;
    bool m_bRootLoss;
    bool m_b3DCorrection;
    bool m_b3DEquilibrium;
    bool m_bInterpolation;
    bool m_bNewRootLoss;
    bool m_bNewTipLoss;

    double elements;
    double epsilon;
    double iterations;
    double relax;
    double rho;
    double visc;
    double position75;      //position of 75% of radius
    double value75;         //value of a_r at 75% for 3D equilibrium

    BData();
    BData(CBlade *pWing, int lambda, int sec);

    virtual ~BData();

    void Serialize(QDataStream &ar, bool bIsStoring);
    void Init(CBlade *pWing, double lambda);
    void OnBEM(double pitch);
    CPolar* Get360Polar(QString m_FoilName, QString PolarName);
public:

    double windspeed;
    QString windspeedStr;

private:

    QString m_WingName;
    QString m_BEMName;
    QString lambdaglobal;
    //QString advanceratio;

    double lambda_global;
    double length;
    double delta;
    double outer_radius, inner_radius;
    double cp;
    double ct;
    ///////new code JM ////////
    double cp_prop;
    double ct_prop;
    double eta;
    double advance_ratio;
    double eps3d;
 ///// end new code JM ////////
    int from, to;
    double blades;


    QList <double> m_pos;
    QList <double> m_c_local;       //local chord
    QList <double> m_lambda_local;  //local lambda
    QList <double> m_p_tangential;  //tangential thrust
    QList <double> m_p_normal;      //radial thrust
    QList <double> m_a_axial;       //axial induction factor
    QList <double> m_a_radial;      //radial induction factor
    QList <double> m_Fa_axial;      //averaged axial induction factor
    QList <double> m_Fa_radial;     //averaged radial induction factor
    QList <double> m_circ;          // circulation
    QList <double> m_theta;         //angles in the wind triangle
    QList <double> m_alpha;         //angles in the wind triangle
    QList <double> m_phi;           //angles in the wind triangle
    QList <double> m_CL;            //lift coeff
    QList <double> m_CD;            //drag coeff
    QList <double> m_LD;            //lift to drag coeff
    QList <double> m_Cn;            //normal coefficient
    QList <double> m_Ct;            //thrust coefficient
    QList <double> m_F;             //Tip Loss Coefficient
    QList <double> m_between;       //the percentage of foils for foil interpolation
    QList <double> m_Reynolds;      //Reynolds Number
    QList <double> m_DeltaReynolds; //Delta between local Re and Re of Polar
    QList <QString> m_polar;        //list of polar at sections
    QList <QString> m_foil;         //list of foils at sections
    QList <QString> m_polarTO;      //list of polars at next sections for interpolation
    QList <QString> m_foilTO;       //list of foils at next sections for interpolation
    QList <double>  m_Roughness;    //the critical roughness for the blade surface
    QList <double>  m_Windspeed;    //windspeed at station (turbine calc)
    QList <double>  m_Iterations;   //total number of iterations required to converge
    QList <double>  m_Mach;         //Mach Number

    QList <double> m_dot_element;
    QList <double> m_total;
    QList <double> dm_i;
    QList <double> torq;
    QList <double> m_ca;
    QList <double> m_cw;
    QList <double> m_c_w_new;
    QList <double> m_cw_old;
    QList <double> m_ca_old;
    QList <double> m_p_tangential2;


    QList <CPolar *> m_PolarPointers;
    QList <CPolar *> m_PolarPointersTO;

    QList <double> deltas;
    QList <double> dist;



    bool m_bShowPoints;
    bool m_bIsVisible;
    int m_Style;
    int m_Width;
    QColor m_Color;


    static QList <void*> *s_poa360Polar;








protected:





public:

};





#endif // BDATA_H
