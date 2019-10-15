/****************************************************************************

    TBEMData Class
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

#ifndef TBEMDATA_H
#define TBEMDATA_H


#include <QList>
#include <QString>
#include <QColor>
#include "BData.h"
#include "TData.h"

class TBEMData
{

    friend class QBEM;
    friend class MainFrame;
public:

    void Compute(BData *pBData, CBlade *pWing, double lambda, double pitch, double windspeed);
    void Clear();
    void Serialize(QDataStream &ar, bool bIsStoring, int ArchiveFormat);


private:

    QString m_TurbineName;
    QString m_SimName;

    QList <BData *> m_BData;                //stores the blade data
    QList <double> m_P;                     //power
    QList <double> m_S;                     //thrust
    QList <double> m_V;                     //wind speed
    QList <double> m_Omega;                 //rotational speed
    QList <double> m_Lambda;                //tip-speed ratio
    QList <double> m_Cp;                    //power coefficient
    QList <double> m_Cp_prop;
    QList <double> m_Ct;                    //thrust coefficient
    QList <double> m_Ct_prop;
    QList <double> m_Pitch;                 //pitch angle
    QList <double> m_Weibull;               //weibullprobability
    QList <double> m_WeibullV3;             //weibullprobability x windspeed^3
    QList <double> m_Bending;               //bending moment
    QList <double> m_Cp_loss;               //power coefficient including losses
    QList <double> m_Kp;                    //dimensionless
    QList <double> m_one_over_lambda;       // 1/ tip speed ratio
    QList <double> m_Torque;                // rotor torque
    QList <double> m_Advance_Ratio;         // advance ratio (PI/lambda_global)
    QList <double> m_Eta;                   //Propeller Efficiency


    double OuterRadius;

    bool m_bShowPoints;
    bool m_bIsVisible;
    int m_Style;
    int m_Width;
    QColor m_Color;

    double K;
    double A;

    //simulation parameters//
    double elements;
    double epsilon;
    double iterations;
    double relax;
    bool m_bTipLoss;
    bool m_bRootLoss;
    bool m_b3DCorrection;
    bool m_b3DEquilibrium;
    bool m_bInterpolation;
    bool m_bNewTipLoss;
    bool m_bNewRootLoss;
    double rho;
    double visc;




    TBEMData();


    virtual ~TBEMData();

protected:





public:

};
#endif // TBEMDATA_H
