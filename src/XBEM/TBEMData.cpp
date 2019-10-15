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

#include "TBEMData.h"
#include "../Globals.h"
#include "BEM.h"


TBEMData::TBEMData()
{

    m_bShowPoints   =   false;
    m_bIsVisible    =   true;
    m_Style        =   0;
    m_Width        =   1;

    K=1.7;
    A=4.0;

    elements = 100;
    epsilon = 0.001;
    iterations = 1000;
    relax = 0.3;
    m_bTipLoss = false;
    m_bRootLoss = false;
    m_b3DCorrection = false;
    m_b3DEquilibrium = false;
    m_bInterpolation = false;
    m_bNewTipLoss = false;
    m_bNewRootLoss = false;
    visc = 0.0000178;
    rho = 1.2;

    OuterRadius = 0;
}

TBEMData::~TBEMData()
{

}

void TBEMData::Clear()
{
    m_Omega.clear();
    m_V.clear();
    for (int i=0;i<m_BData.size();i++)
    {
        if (m_BData.at(i)) delete m_BData.at(i);
    }
    m_BData.clear();
    m_P.clear();
    m_Cp.clear();
    m_Cp_prop.clear();
    m_Ct.clear();
    m_Ct_prop.clear();
    m_Lambda.clear();
    m_S.clear();
    m_Pitch.clear();
    m_Weibull.clear();
    m_WeibullV3.clear();
    m_one_over_lambda.clear();
    m_Kp.clear();
    m_Bending.clear();
    m_Torque.clear();
    m_Advance_Ratio.clear();
    m_Eta.clear();
}

void TBEMData::Compute(BData *pBData, CBlade *pWing, double lambda, double pitch, double windspeed)
{

    pBData->elements = elements;
    pBData->epsilon = epsilon;
    pBData->iterations = iterations;
    pBData->m_bTipLoss = m_bTipLoss;
    pBData->m_bRootLoss = m_bRootLoss;
    pBData->m_b3DCorrection = m_b3DCorrection;
    pBData->m_b3DEquilibrium = m_b3DEquilibrium;
    pBData->m_bInterpolation = m_bInterpolation;
    pBData->relax = relax;
    pBData->rho = rho;
    pBData->visc = visc;
    pBData->m_bNewRootLoss = m_bNewRootLoss;
    pBData->m_bNewTipLoss = m_bNewTipLoss;

    pBData->windspeed = windspeed;


    pBData->Init(pWing,lambda);
    pBData->OnBEM(pitch);


}

void TBEMData::Serialize(QDataStream &ar, bool bIsStoring, int ArchiveFormat)
{
    int i,n,j;
    float f;

    if (bIsStoring)
    {
        n= (int) m_P.size();

        if (m_bIsVisible)  ar<<1; else ar<<0;
        if (m_bShowPoints) ar<<1; else ar<<0;
        ar << (int) m_Style;
        ar << (int) m_Width;
        ar << (float) elements;
        ar << (float) rho;
        ar << (float) epsilon;
        ar << (float) iterations;
        ar << (float) relax;
        ar << (float) K;
        ar << (float) A;
        ar << (float) visc;

        if (m_bTipLoss) ar << 1; else ar<<0;
        if (m_bRootLoss) ar << 1; else ar<<0;
        if (m_b3DCorrection) ar << 1; else ar<<0;
        if (m_b3DEquilibrium) ar << 1; else ar<<0;
        if (m_bInterpolation) ar << 1; else ar<<0;
        if (m_bNewTipLoss) ar << 1; else ar<<0;
        if (m_bNewRootLoss) ar << 1; else ar<<0;

        WriteCOLORREF(ar,m_Color);
        WriteCString(ar, m_TurbineName);
        WriteCString(ar, m_SimName);
        ar << (int) n;

        for (i=0;i<n;i++)
        {
            ar<< (float) m_P[i] << (float) m_S [i] << (float) m_V[i] << (float) m_Omega[i];
            ar << (float) m_Lambda[i] << (float) m_Cp[i] << (float) m_Cp_prop[i] << (float) m_Ct[i] << (float) m_Ct_prop[i] << (float)m_Pitch[i];
            ar << (float) m_Weibull[i] << (float) m_WeibullV3[i] << (float) m_Bending[i];
            ar << (float)m_Cp_loss[i] << (float) m_Kp[i] << (float) m_one_over_lambda[i] << (float) m_Torque[i] << (float) m_Advance_Ratio[i] << (float) m_Eta[i];
        }
        for (i=0;i<n;i++)
        {
            m_BData.at(i)->Serialize(ar,bIsStoring);
        }

        ar << (float) OuterRadius;
    }
    else
    {
        ar >> f;
        if (f) m_bIsVisible = true; else m_bIsVisible = false;
        ar >> f;
        if (f) m_bShowPoints = true; else m_bShowPoints = false;
        ar >> j;
        m_Style = j;
        ar >> j;
        m_Width = j;
        ar >> f;
        elements = f;
        ar >> f;
        rho = f;
        ar >> f;
        epsilon = f;
        ar >> f;
        iterations = f;
        ar >> f;
        relax = f;
        ar >> f;
        K = f;
        ar >> f;
        A = f;
        ar >> f;
        visc = f;
        ar >> f;
        if (f) m_bTipLoss = true; else m_bTipLoss = false;
        ar >> f;
        if (f) m_bRootLoss = true; else m_bRootLoss = false;
        ar >> f;
        if (f) m_b3DCorrection = true; else m_b3DCorrection = false;
        ar >> f;
        if(f) m_b3DEquilibrium = true; else m_b3DEquilibrium = false;
        ar >> f;
        if (f) m_bInterpolation = true; else m_bInterpolation = false;
        ar >> f;
        if (f) m_bNewTipLoss = true; else m_bNewTipLoss = false;
        ar >> f;
        if (f) m_bNewRootLoss = true; else m_bNewRootLoss = false;
        ReadCOLORREF(ar,m_Color);
        ReadCString(ar,m_TurbineName);
        ReadCString(ar,m_SimName);

        ar >> n;

        for (i=0;i<n;i++)
        {
            ar >> f;
            m_P.append(f);
            ar >> f;
            m_S.append(f);
            ar >> f;
            m_V.append(f);
            ar >> f;
            m_Omega.append(f);
            ar >> f;
            m_Lambda.append(f);
            ar >> f;
            m_Cp.append(f);
            ar >> f;
            m_Cp_prop.append(f);
            ar >> f;
            m_Ct.append(f);
            ar >> f;
            m_Ct_prop.append(f);
            ar >> f;
            m_Pitch.append(f);
            ar >> f;
            m_Weibull.append(f);
            ar >> f;
            m_WeibullV3.append(f);
            ar >> f;
            m_Bending.append(f);
            ar >> f;
            m_Cp_loss.append(f);
            ar >> f;
            m_Kp.append(f);
            ar >> f;
            m_one_over_lambda.append(f);
            if (ArchiveFormat >= 100015)
            {
                ar >> f;
                m_Torque.append(f);
            }
            else m_Torque.append(0);
            ar >> f;
            m_Advance_Ratio.append(f);
            ar >> f;
            m_Eta.append(f);
        }

        for (i=0;i<n;i++)
        {
            BData *pBData = new BData;
            pBData->Serialize(ar,bIsStoring);
            m_BData.append(pBData);
        }

        ar >> f;
        OuterRadius = f;
    }


}

