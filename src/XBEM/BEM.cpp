/****************************************************************************

    BEM Class
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

#include "BEM.h"


#include <QWidget>
#include "../GLWidget.h"
#include "../MainFrame.h"
#include "../Miarex/ArcBall.h"
#include "../Globals.h"
#include "../Misc/RenameDlg.h"
#include "../Misc/FloatEdit.h"
#include "../XDirect/XDirect.h"
#include "BData.h"
#include "BEMData.h"
#include "../Graph/GraphDlg.cpp"

#include <math.h>
#include <QDebug>
#include <qstring.h>
#include <complex>
#include "TData.h"
#include "OptimizeDlg.h"
#include "CreateBEMDlg.h"
#include "TBEMData.h"
#include "BladeScaleDlg.h"
#include "BladeStructureDlg.h"
#include "Edit360PolarDlg.h"
#include "../Design/AFoil.h"
#include "AboutBEM.h"



#include <QProgressDialog>



#define SIDEPOINTS 51


using namespace std;

extern CFoil *g_pCurFoil;


QBEM::QBEM(QWidget *parent)
    : QWidget(parent)
{

    m_VersionName="JBlade v17";


    m_CurveStyle = 0;
    m_CurveWidth = 1;
    m_CurveColor = QColor(0,0,0);
    selected_windspeed = -1;
    selected_lambda = 0;

    m_360CLGraph.SetXMajGrid(true, QColor(120,120,120),2,1);
    m_360CLGraph.SetYMajGrid(true, QColor(120,120,120),2,1);
    m_360CLGraph.SetXMin(-0.0);
    m_360CLGraph.SetXMax( 0.1);
    m_360CLGraph.SetYMin(-0.01);
    m_360CLGraph.SetYMax( 0.01);
    m_360CLGraph.SetType(0);
    m_360CLGraph.SetMargin(50);
    m_360CLGraph.SetXVariable(0);
    m_360CLGraph.SetYVariable(1);
    m_360CLGraph.SetGraphName(tr("360 CL Graph"));
    SetGraphTitles(&m_360CLGraph);

    m_360CDGraph.SetXMajGrid(true, QColor(120,120,120),2,1);
    m_360CDGraph.SetYMajGrid(true, QColor(120,120,120),2,1);
    m_360CDGraph.SetXMin(-0.0);
    m_360CDGraph.SetXMax( 0.1);
    m_360CDGraph.SetYMin(-0.01);
    m_360CDGraph.SetYMax( 0.01);
    m_360CDGraph.SetType(0);
    m_360CDGraph.SetMargin(50);
    m_360CDGraph.SetXVariable(0);
    m_360CDGraph.SetYVariable(2);
    m_360CDGraph.SetGraphName(tr("360 CD Graph"));



    m_CharGraph1.SetXMajGrid(true, QColor(120,120,120),2,1);
    m_CharGraph1.SetYMajGrid(true, QColor(120,120,120),2,1);
    m_CharGraph1.SetXMin(-0.0);
    m_CharGraph1.SetXMax( 0.1);
    m_CharGraph1.SetYMin(-0.01);
    m_CharGraph1.SetYMax( 0.01);
    m_CharGraph1.SetType(0);
    m_CharGraph1.SetMargin(50);
    m_CharGraph1.SetXVariable(0);
    m_CharGraph1.SetYVariable(2);
    m_CharGraph1.SetGraphName(tr("Char Graph 1"));
    m_CharGraph1.m_Type=0;


    m_CharGraph2.SetXMajGrid(true, QColor(120,120,120),2,1);
    m_CharGraph2.SetYMajGrid(true, QColor(120,120,120),2,1);
    m_CharGraph2.SetXMin(-0.0);
    m_CharGraph2.SetXMax( 0.1);
    m_CharGraph2.SetYMin(-0.01);
    m_CharGraph2.SetYMax( 0.01);
    m_CharGraph2.SetType(0);
    m_CharGraph2.SetMargin(50);
    m_CharGraph2.SetXVariable(0);
    m_CharGraph2.SetYVariable(3);
    m_CharGraph2.SetGraphName(tr("Char Graph 2"));
    m_CharGraph2.m_Type=0;


    m_CharGraph3.SetXMajGrid(true, QColor(120,120,120),2,1);
    m_CharGraph3.SetYMajGrid(true, QColor(120,120,120),2,1);
    m_CharGraph3.SetXMin(-0.0);
    m_CharGraph3.SetXMax( 0.1);
    m_CharGraph3.SetYMin(-0.01);
    m_CharGraph3.SetYMax( 0.01);
    m_CharGraph3.SetType(0);
    m_CharGraph3.SetMargin(50);
    m_CharGraph3.SetXVariable(1);
    m_CharGraph3.SetYVariable(0);
    m_CharGraph3.SetGraphName(tr("Char Graph 3"));
    m_CharGraph3.m_Type=1;



    m_PowerGraph1.SetXMajGrid(true, QColor(120,120,120),2,1);
    m_PowerGraph1.SetYMajGrid(true, QColor(120,120,120),2,1);
    m_PowerGraph1.SetXMin(-0.0);
    m_PowerGraph1.SetXMax( 0.1);
    m_PowerGraph1.SetYMin(-0.01);
    m_PowerGraph1.SetYMax( 0.01);
    m_PowerGraph1.SetType(0);
    m_PowerGraph1.SetMargin(50);
    m_PowerGraph1.SetXVariable(2);
    m_PowerGraph1.SetYVariable(0);
    m_PowerGraph1.SetGraphName(tr("Power Graph 1"));
    m_PowerGraph1.m_Type=0;


    m_PowerGraph2.SetXMajGrid(true, QColor(120,120,120),2,1);
    m_PowerGraph2.SetYMajGrid(true, QColor(120,120,120),2,1);
    m_PowerGraph2.SetXMin(-0.0);
    m_PowerGraph2.SetXMax( 0.1);
    m_PowerGraph2.SetYMin(-0.01);
    m_PowerGraph2.SetYMax( 0.01);
    m_PowerGraph2.SetType(0);
    m_PowerGraph2.SetMargin(50);
    m_PowerGraph2.SetXVariable(2);
    m_PowerGraph2.SetYVariable(1);
    m_PowerGraph2.SetGraphName(tr("Power Graph 2"));
    m_PowerGraph2.m_Type=0;


    m_PowerGraph3.SetXMajGrid(true, QColor(120,120,120),2,1);
    m_PowerGraph3.SetYMajGrid(true, QColor(120,120,120),2,1);
    m_PowerGraph3.SetXMin(-0.0);
    m_PowerGraph3.SetXMax( 0.1);
    m_PowerGraph3.SetYMin(-0.01);
    m_PowerGraph3.SetYMax( 0.01);
    m_PowerGraph3.SetType(0);
    m_PowerGraph3.SetMargin(50);
    m_PowerGraph3.SetXVariable(12);
    m_PowerGraph3.SetYVariable(10);
    m_PowerGraph3.SetGraphName(tr("Power Graph 3"));
    m_PowerGraph3.m_Type=1;

    SetPowerGraphTitles(&m_PowerGraph1);
    SetPowerGraphTitles(&m_PowerGraph2);
    SetPowerGraphTitles(&m_PowerGraph3);
    SetGraphTitles(&m_CharGraph1);
    SetGraphTitles(&m_CharGraph2);
    SetGraphTitles(&m_CharGraph3);
    SetPolarGraphTitles(&m_360CLGraph);
    SetPolarGraphTitles(&m_360CDGraph);


    dlg_lambda = 7;
    dlg_blades = 3;

    dlg_relax = 0.35;
    dlg_rho = 1.2041;
    dlg_epsilon = 0.001;
    dlg_iterations = 1000;
    dlg_elements = 50;
    dlg_tiploss = false;
    dlg_rootloss = false;
    dlg_3dcorrection = false;
    dlg_3dequilibrium = false;
    dlg_interpolation = false;
    dlg_newtiploss = false;
    dlg_newrootloss = false;

    dlg_lambdastart     = 1;
    dlg_lambdaend       = 10;
    dlg_lambdadelta     = 0.5;

    dlg_windstart       = 1;
    dlg_windend         = 20;
    dlg_winddelta       = 0.5;

    dlg_visc = 0.0000178;

    pitch_old = 0;
    pitch_new = 0;

    //a_radius = 0.1;

    //m_CD90 = 1.8;

    m_d_cl= 0.1;

    m_bAbsoluteBlade = false;



    SetupLayout();   
    Connect();

    m_pctrlCurveColor->setEnabled(false);
    m_pctrlCurveStyle->setEnabled(false);
    m_pctrlCurveWidth->setEnabled(false);

    m_pWing=NULL;
    m_pTData=NULL;
    m_pCurPolar = NULL;
    m_pCurGraph = NULL;
    m_pWingModel = NULL;


    m_bShowOpPoint              = true;
    m_bChanged                  = false;
    m_bRightSide                = false;
    m_bResetglGeom              = true;
    m_bShowLight                = false;
    m_bCrossPoint               = false;
    m_bOutline                  = true;
    m_bglLight                  = true;
    m_bSurfaces                 = true;
    m_bResetglLegend            = false;
    m_bResetglSectionHighlight  = true;
    m_b360PolarChanged          = true;
    m_bNew360Polar              = false;
    m_bXPressed                 = false;
    m_bYPressed                 = false;
    m_WingEdited                = false;
    m_TurbineEdited             = false;
    m_bIsolateBladeCurve        = false;
    m_bCompareBladeCurve        = false;
    m_bIs2DScaleSet             = false;
    m_bAutoScales               = false;
    m_bComparePolarCurves       = false;
    m_bHideWidgets              = false;
    m_bAdvancedEdit             = false;
    m_cylName = "";
    m_cylPolarName = "";


    m_GLScale       = 1.0;
    m_ClipPlanePos  = 15.0;
    m_glScaled      = 1.0;
    m_OutlineWidth  = 1;
    m_OutlineStyle  = 0;
    m_OutlineColor  = QColor(0,0,255);

    m_iView = PolarView;


    m_rCltRect.setWidth(0);
    m_rCltRect.setHeight(0);
    m_rSingleRect.setWidth(0);
    m_rSingleRect.setHeight(0);

    m_glViewportTrans.x  = 0.0;
    m_glViewportTrans.y  = 0.0;
    m_glViewportTrans.z  = 0.0;

    m_LastPoint.setX(0);
    m_LastPoint.setY(0);
    m_PointDown.setX(0);
    m_PointDown.setY(0);




}

void QBEM::AboutTheBEM()
{
        AboutBEM dlg(this);
        dlg.exec();
}

double QBEM::CD90(CFoil *pFoil, double alpha)
{

  double res;
    res=m_CD90-1.46*pFoil->m_fThickness/2+1.46*pFoil->m_fCamber*sin(alpha/360*2*PI);
    return res;
}

double QBEM::CDPlate(double alpha)
{
    double res;
    res=CD90(m_pFoil,alpha)*pow(sin(alpha/360*2*PI),2);
    return res;
}

void QBEM::CheckButtons()
{
    MainFrame *pMainFrame = (MainFrame *) s_pMainFrame;

    SimuWidget *pSimuWidget = (SimuWidget *) m_pSimuWidget;

    m_pctrlBladeCoordinates->setChecked(!m_bAbsoluteBlade);

    UpdateUnits();
    ///context menu///

    pMainFrame->current360PolarMenu->setEnabled(m_pCur360Polar);
    pMainFrame->currentBladeMenu->setEnabled(m_pWing);
    pMainFrame->currentTurbineMenu->setEnabled(m_pTData);
    pMainFrame->DeleteCurrentRotorSimAct->setEnabled(m_pBEMData);
    pMainFrame->DeleteCurrentTurbineSimAct->setEnabled(m_pTBEMData);
    ///

    InitTurbineData(m_pTData);

    pSimuWidget->m_pctrlLSLineEdit->SetValue(dlg_lambdastart);
    pSimuWidget->m_pctrlLELineEdit->SetValue(dlg_lambdaend);
    pSimuWidget->m_pctrlLDLineEdit->SetValue(dlg_lambdadelta);

    pSimuWidget->m_pctrlWind1->SetValue(dlg_windstart);
    pSimuWidget->m_pctrlWind2->SetValue(dlg_windend);
    pSimuWidget->m_pctrlWindDelta->SetValue(dlg_winddelta);





    pSimuWidget->m_pctrlDefineTurbineSim->setEnabled(m_pTData);
    pSimuWidget->m_pctrlStartTurbineSim->setEnabled(m_pTBEMData);
    pSimuWidget->m_pctrlWind1->setEnabled(m_pTBEMData);
    pSimuWidget->m_pctrlWind2->setEnabled(m_pTBEMData);
    pSimuWidget->m_pctrlWindDelta->setEnabled(m_pTBEMData);

    pSimuWidget->m_pctrlCreateBEM->setEnabled(m_pWing);
    pSimuWidget->m_pctrlStartBEM->setEnabled(m_pBEMData);
    pSimuWidget->m_pctrlLSLineEdit->setEnabled(m_pBEMData);
    pSimuWidget->m_pctrlLELineEdit->setEnabled(m_pBEMData);
    pSimuWidget->m_pctrlLDLineEdit->setEnabled(m_pBEMData);


    m_pctrlNewTurbine->setEnabled(s_poaBEMWings->size());
    m_pctrlEditTurbine->setEnabled(m_pTData);

    m_pctrlEditWing->setEnabled(m_pWing);


    m_pctrlNewWing->setEnabled(s_poa360Polar->size());


    if (m_pCurPolar && m_pCurPolar->m_Alpha.size() > 10)
    {
         m_pctrlNew360->setEnabled(!m_bNew360Polar);
         if(m_pCurPolar->m_FoilName == m_cylName ) m_pctrlNew360->setEnabled(false);
    }
    else m_pctrlNew360->setEnabled(false);
    m_pctrlSave360->setEnabled(m_bNew360Polar);

    QString str;
    GetLengthUnit(str, pMainFrame->m_LengthUnit);
    m_pctrlHubRadiusUnitLabel->setText(str);

    if (m_iView == CharView) pSimuWidget->middleControls->setCurrentIndex(0);
    if (m_iView == PowerView) pSimuWidget->middleControls->setCurrentIndex(1);

    pMainFrame->m_pctrl3DView->setChecked(m_iView==WingView);
    pMainFrame->m_pctrlGraphView->setChecked(m_iView==PolarView);
    pMainFrame->m_pctrlCharView->setChecked(m_iView==CharView);
    pMainFrame->m_pctrlPowerView->setChecked(m_iView==PowerView);

    pMainFrame->m_pctrl3DView2->setChecked(m_iView==WingView);
    pMainFrame->m_pctrlGraphView2->setChecked(m_iView==PolarView);
    pMainFrame->m_pctrlCharView2->setChecked(m_iView==CharView);
    pMainFrame->m_pctrlPowerView2->setChecked(m_iView==PowerView);

    pMainFrame->m_pctrl3DView3->setChecked(m_iView==WingView);
    pMainFrame->m_pctrlGraphView3->setChecked(m_iView==PolarView);
    pMainFrame->m_pctrlCharView3->setChecked(m_iView==CharView);
    pMainFrame->m_pctrlPowerView3->setChecked(m_iView==PowerView);



    if(!m_pCurGraph)
    {
        pMainFrame->BladeGraphAct->setEnabled(false);
        pMainFrame->RotorGraphAct->setEnabled(false);
        pMainFrame->BladeGraphAct->setChecked(false);
        pMainFrame->RotorGraphAct->setChecked(false);
    }
    else if(m_pCurGraph->m_Type == 1)
    {
        pMainFrame->BladeGraphAct->setEnabled(true);
        pMainFrame->RotorGraphAct->setEnabled(true);
        pMainFrame->BladeGraphAct->setChecked(true);
        pMainFrame->RotorGraphAct->setChecked(false);
    }
    else if(m_pCurGraph->m_Type == 0)
    {
        pMainFrame->BladeGraphAct->setEnabled(true);
        pMainFrame->RotorGraphAct->setEnabled(true);
        pMainFrame->BladeGraphAct->setChecked(false);
        pMainFrame->RotorGraphAct->setChecked(true);
    }

    if (m_iView==WingView)
    {
        mainWidget->setCurrentIndex(0);
        if (m_WingEdited) bladeWidget->setCurrentIndex(1);
        else if (!m_WingEdited) bladeWidget->setCurrentIndex(0);
    }
    else if (m_iView == PolarView)
    {
        mainWidget->setCurrentIndex(1);
    }
    else if (m_iView == PowerView)
    {
        if (m_TurbineEdited) mainWidget->setCurrentIndex(3);
        else if (!m_TurbineEdited) mainWidget->setCurrentIndex(2);
    }

    if (m_bHideWidgets)
    {
        pMainFrame->m_pctrlBEMWidget->hide();
        pMainFrame->m_pctrlSimuWidget->hide();
    }
    else if (m_iView == WingView)
    {
    pMainFrame->m_pctrlBEMToolBar->show();
    pMainFrame->m_pctrlBEM360ToolBar->hide();
    pMainFrame->m_pctrlTurbineToolBar->hide();
    pMainFrame->m_pctrlBEMWidget->show();
    pMainFrame->m_pctrlSimuWidget->hide();
    }
    else if (m_iView == PolarView )
    {
    pMainFrame->m_pctrlBEMToolBar->hide();
    pMainFrame->m_pctrlBEM360ToolBar->show();
    pMainFrame->m_pctrlTurbineToolBar->hide();
    pMainFrame->m_pctrlSimuWidget->hide();
    pMainFrame->m_pctrlBEMWidget->show();
    }
    else if (m_iView == CharView )
    {      
    pMainFrame->m_pctrlBEMToolBar->show();
    pMainFrame->m_pctrlBEM360ToolBar->hide();
    pMainFrame->m_pctrlTurbineToolBar->hide();
    pMainFrame->m_pctrlSimuWidget->show();
    pMainFrame->m_pctrlBEMWidget->hide();
    }

    else if (m_iView == PowerView )
    {
    pMainFrame->m_pctrlBEMToolBar->hide();
    pMainFrame->m_pctrlBEM360ToolBar->hide();
    pMainFrame->m_pctrlTurbineToolBar->show();
    pMainFrame->m_pctrlSimuWidget->show();
    pMainFrame->m_pctrlBEMWidget->show();
    }



    if (!m_pCur360Polar) m_360Name->clear();

    m_pctrlA->setEnabled(m_bNew360Polar);
    m_pctrlB->setEnabled(m_bNew360Polar);
    m_pctrlAm->setEnabled(m_bNew360Polar);
    m_pctrlBm->setEnabled(m_bNew360Polar);
    m_360Name->setEnabled(m_bNew360Polar);
    m_CD90YCoordinate->setEnabled(m_bNew360Polar);
    m_CD90LERadius->setEnabled(m_bNew360Polar);
//    if (m_pCur360Polar)
//    {
//    if (m_pCur360Polar->m_PlrName == m_cylPolarName) //m_pctrlCD90->setDisabled(false);
//    }


}

void QBEM::CheckWing()
{
    bool finished = true;
    double max = -10000;
    int station;
    QString text, var, var2;

    for (int i=0;i<m_pWing->m_NPanel;i++)
    {
        if (m_pWing->m_Polar.at(i) == "") finished = false;
        if (m_pWing->m_RFoil.at(i) == "") finished = false;
    }

    //// check if solidity < 1 at all stations
    for (int i=0;i<=m_pWing->m_NPanel;i++)
    {
        if (m_pWing->blades*m_pWing->m_TChord[i]/(m_pWing->m_TPos[i]*2*PI) > max)
        {
        max = m_pWing->blades*m_pWing->m_TChord[i]/(m_pWing->m_TPos[i]*2*PI);
        station = i;
        }
    }

    if (max >= 1)
    {
        text = "<font color='Red'> Solidity is " +var.sprintf("%.2f",double(max))+ " at station " +var2.sprintf("%.0f",double(station+1))+" it has to be smaller than one - reduce the chord length at station " +var2+"</font>";
        finished = false;
    }

    //// check if stations are in ascending order

    for (int i=0;i<m_pWing->m_NPanel;i++)
    {
        if (m_pWing->m_TPos[i] > m_pWing->m_TPos[i+1])
        {
            text = "<font color='Red'>Positions are not in ascending order";
            finished = false;
        }
    }

    //// check if stations are not at the same position

    for (int i=0;i<=m_pWing->m_NPanel;i++)
    {
        for (int j=0;j<=m_pWing->m_NPanel;j++)
        {
            if (i!=j)
            {
                qDebug() << m_pWing->m_TPos[i] << m_pWing->m_TPos[j]<<m_pWing->m_TPos[i] - m_pWing->m_TPos[j];

                if (fabs(m_pWing->m_TPos[i] - m_pWing->m_TPos[j]) <= 0.000001)
                {
                    text = "<font color='Red'> Two stations are at the same position";
                    finished = false;
                }
            }
        }
    }



    if (finished) text = "";

    m_pctrlSolidityLabel->setText(text);

    m_pctrlSave->setEnabled(finished);
    m_pctrlOptimize->setEnabled(finished);
    m_pctrlBladeStructure->setEnabled(finished);

}

void QBEM::CheckTurbineButtons()
{
    m_pctrlSwitch->setEnabled(m_pctrl2Step->isChecked());
    m_pctrlRot2->setEnabled(!m_pctrlFixed->isChecked());
    m_pctrlLambda->setEnabled(m_pctrlVariable->isChecked());

    if (m_pctrlPitch->isChecked())
    {
        m_pctrlGenerator->hide();
        m_pctrlGeneratorLabel->hide();
        power1->hide();
    }
    else
    {
        m_pctrlGenerator->hide();
        m_pctrlGeneratorLabel->hide();
        power1->hide();
    }

    if (m_pctrlVariable->isChecked())
    {
        m_pctrlRot1Label->setText(tr("Rotational Speed Min"));
        m_pctrlRot2Label->setText(tr("Rotational Speed Max"));
        m_pctrlSwitchLabel->setText("");
        m_pctrlLambdaLabel->setText("Tip Speed Ratio at Design Point");
        m_pctrlRot1->hide();
        m_pctrlRot2->hide();

        rotspeed1->hide();
        rotspeed2->hide();

        m_pctrlSwitch->hide();

        speed3->hide();

        m_pctrlLambda->hide();

    }
    if (m_pctrl2Step->isChecked())
    {
        m_pctrlRot1Label->setText(tr("Rotational Speed 1"));
        m_pctrlRot2Label->setText(tr("Rotational Speed 2"));
        m_pctrlSwitchLabel->setText("V Switch");
        m_pctrlLambdaLabel->setText("");
        m_pctrlRot1->hide();
        m_pctrlRot2->hide();
        rotspeed1->hide();
        rotspeed2->hide();
        m_pctrlSwitch->hide();
        speed3->hide();

        m_pctrlLambda->hide();

    }
    if (m_pctrlFixed->isChecked())
    {
        m_pctrlRot1Label->setText(tr("Rotational Speed"));
        m_pctrlRot2Label->setText(tr(""));
        m_pctrlSwitchLabel->setText("");
        m_pctrlLambdaLabel->setText("");
        m_pctrlRot1->show();
        rotspeed1->show();

        m_pctrlRot2->hide();
        rotspeed2->hide();

        m_pctrlSwitch->hide();
        speed3->hide();

        m_pctrlLambda->hide();

    }
}


void QBEM::Compute360Polar()
{
    double CLmax=0, CLmin=100, CLabsmin=100, alphamax, alphamin, CLzero, CL180;
    double alphazero, slope, deltaCD;
    double deltaalpha = (m_pCurPolar->m_Alpha.at(2)-m_pCurPolar->m_Alpha.at(1));
    double smallestalpha = 100, smallestAlpha=100;

    ///////////// COORDENADA A 0.0125 PARA METODO 1 /////////////////////

    double yc4 = m_pFoil->GetUpperY(0.0125);

///////////// METODO DOS MINIMOS QUADRADOS PARA OBTER UM CIRCULO /////////////////////
            double y_circle_1, y_circle_2, y_circle_3, y_circle_4, y_circle_5;

            radius.clear();
            min_q.clear();

            radius.append(0.2);
            double deltaradius= 0.00001;

            double x_airfoil_1 = 0.0005;
            //double x_airfoil_2 = 0.0017;
            double x_airfoil_3 = 0.0;
            double x_airfoil_4 = 0.0005;
           // double x_airfoil_5 = 0.0017;
            //double sum_min_q=0;
            //double y_airfoil_1;

//            y_airfoil.clear();
//            x_airfoil.clear();

//            while (x_airfoil_low > 0.001 )
//            {
                double y_airfoil_1 = ((m_pFoil->GetLowerY(x_airfoil_1)));
               // double y_airfoil_2 = ((m_pFoil->GetLowerY(x_airfoil_2)));


                double y_airfoil_3 = ((m_pFoil->GetUpperY(x_airfoil_3)));
                double y_airfoil_4 = ((m_pFoil->GetUpperY(x_airfoil_4)));
               // double y_airfoil_5 = ((m_pFoil->GetUpperY(x_airfoil_5)));



    min_q.append(1.0);
    int ii = 1;
    while( ii<100000 )
    //while (sum_min_q > 0.000000001) // 1e-7
    {
        //sum_min_q = 0;

        y_circle_1 = -pow(pow(radius.at(ii-1),2)-pow((x_airfoil_1-radius.at(ii-1)),2),0.5);
       // y_circle_2 = -pow(pow(radius.at(ii-1),2)-pow((x_airfoil_2-radius.at(ii-1)),2),0.5);
        y_circle_3 = (pow(pow(radius.at(ii-1),2)-pow(x_airfoil_3-radius.at(ii-1),2),0.5));
        y_circle_4 = (pow(pow(radius.at(ii-1),2)-pow(x_airfoil_4-radius.at(ii-1),2),0.5));
       // y_circle_5 = (pow(pow(radius.at(ii-1),2)-pow(x_airfoil_5-radius.at(ii-1),2),0.5));

             double min_q_1 = fabs(pow(y_airfoil_1,2)-pow(y_circle_1,2));
         //    double min_q_2 = fabs(pow(y_airfoil_2,2)-pow(y_circle_2,2));
             double min_q_3 = fabs(pow(y_airfoil_3,2)-pow(y_circle_3,2));
             double min_q_4 = fabs(pow(y_airfoil_4,2)-pow(y_circle_4,2));
         //   double min_q_5 = fabs(pow(y_airfoil_5,2)-pow(y_circle_5,2));


             min_q.append(min_q_1+min_q_3+min_q_4);

           if (min_q.at(ii)<min_q.at(ii-1))
           {
             radius.append(radius.at(ii-1)-deltaradius);

             //deltaradius=deltaradius*0.8;
           }
           else
           {
               radius.append(radius.at(ii-2)+deltaradius);
            //  deltaradius = deltaradius*0.8;
           }
            airfoil_radius=radius.at(ii-1);
           ii++;


    }

  //    QString text2, text3, var, var2, var3, var4, var5, var6, var7;

     // text2 = "<font color='Black'> y_airfoil_1  " +var.sprintf("%.10f",double (y_airfoil_1)) + "<font color='Red'> y_airfoil_2  " +var2.sprintf("%.10f",double(y_airfoil_2)) +"<font color='Red'> y_airfoil_3  " +var3.sprintf("%.10f",double(y_airfoil_3));
 // text3 = "<font color='Black'> y_circle_1  " +var4.sprintf("%.10f",double (y_circle_1)) + "<font color='Red'> y_circle_2  " +var5.sprintf("%.10f",double(y_circle_3)) +"<font color='Red'> y_circle_3  " +var6.sprintf("%.10f",double(y_circle_4))+"<font color='Red'> radius  " +var7.sprintf("%.10f",double(airfoil_radius));


  //    QLabel *yc2 = new QLabel;
  //         yc2->setText(text3);
  //         yc2->show();

    if (m_CD90YCoordinate->isChecked())
    {
          // m_CD90 = 1.994-5.4375*yc4;       //CD 90 calculated using Y coordinate at 0.0125
            m_CD90 = 2.086-4.6313*yc4;
    }
    else
    {
           m_CD90 = 2.0858-3.8736*airfoil_radius;    // CD 90 calculated using LE Radius
    }



  //  QString text2, text3, var, var2, var3, var4, var5, var6, var7;

 //   text2 = "<font color='Black'> y_airfoil_1  " +var.sprintf("%.10f",double (y_airfoil_1)) + "<font color='Red'> y_airfoil_2  " +var2.sprintf("%.10f",double(y_airfoil_2)) +"<font color='Red'> y_airfoil_3  " +var3.sprintf("%.10f",double(y_airfoil_3));
 //   text3 = "<font color='Black'> y_circle_1  " +var4.sprintf("%.10f",double (y_circle_1)) + "<font color='Red'> y_circle_2  " +var5.sprintf("%.10f",double(y_circle_2)) +"<font color='Red'> y_circle_3  " +var6.sprintf("%.10f",double(y_circle_3))+"<font color='Red'> radius  " +var7.sprintf("%.10f",double(airfoil_radius));

//       QLabel *alpha2 = new QLabel();
//              // alpha2->setText(text2);
//            alpha2->setNum(airfoil_radius);
//               alpha2->show();

//       QLabel *yc2 = new QLabel();
//               yc2->setText(text3);
//            alpha2->setNum(m_CD90);
//               yc2->show();



//            QLabel *yc2 = new QLabel();
//                    yc2->setNum(radius);
//                    yc2->show();

    int posalphamax, posalphamin, possmallestalpha;

    double a1plus,a1minus,a2plus,a2minus;
    double CL1plus, CL1minus,CL2plus,CL2minus;
    double f1plus,f1minus,f2plus,f2minus;

    double Cl_xfoil, Cl_linear;


    double am, G , k;

    m_pCur360Polar->m_Alpha.clear();
    m_pCur360Polar->m_Cl.clear();
    m_pCur360Polar->m_Cd.clear();


    //get important variables from current polar

    for (int i=0; i<m_pCurPolar->m_Alpha.size(); i++)
    {

        if (m_pCurPolar->m_Alpha.at(i) > -25 && m_pCurPolar->m_Alpha.at(i) < 25)
        {

            if (m_pCurPolar->m_Cl.at(i) > CLmax)
            {
                CLmax = m_pCurPolar->m_Cl.at(i);
                alphamax = m_pCurPolar->m_Alpha.at(i);   // alpha maximo do XFOIL
                posalphamax=i;

            }

            if (m_pCurPolar->m_Cl.at(i) < CLmin)
            {
                CLmin = m_pCurPolar->m_Cl.at(i);
                alphamin = m_pCurPolar->m_Alpha.at(i);
                posalphamin=i;
            }

            if (fabs(m_pCurPolar->m_Alpha.at(i)) < smallestAlpha)
            {
                smallestAlpha = fabs(m_pCurPolar->m_Alpha.at(i));
                smallestalpha=m_pCurPolar->m_Alpha.at(i);
                slope = (m_pCurPolar->m_Cl.at(i+3)-m_pCurPolar->m_Cl.at(i))/(m_pCurPolar->m_Alpha.at(i+3)-m_pCurPolar->m_Alpha.at(i));
            }
        }

    }

    for (int i=0; i<m_pCurPolar->m_Alpha.size(); i++)
    {
        alpha_xfoil = m_pCurPolar->m_Alpha.at(i);
        pos_alpha_xfoil=m_pCurPolar->m_Alpha.size();

        if (m_pCurPolar->m_Alpha.at(i) > -25 && m_pCurPolar->m_Alpha.at(i) < 25)
        {
            if (m_pCurPolar->m_Alpha.at(i) == smallestalpha)
            {
                CLzero = m_pCurPolar->m_Cl.at(i)-slope*smallestalpha;
            }

            if (fabs(m_pCurPolar->m_Cl.at(i)) < CLabsmin)
            {
                CLabsmin=fabs(m_pCurPolar->m_Cl.at(i));
                possmallestalpha=i;
                alphazero = m_pCurPolar->m_Alpha.at(i)-m_pCurPolar->m_Cl.at(i)/slope;
            }


            Cl_xfoil = m_pCurPolar->m_Cl.at(i);
            Cl_linear = CLzero+ slope*m_pCurPolar->m_Alpha.at(i);
            Cd_xfoil.append(m_pCurPolar->m_Cd.at(i));

            d_cl = Cl_linear - Cl_xfoil;

            if (d_cl < double (0.1) )
            {
                    alpha_ast = m_pCurPolar->m_Alpha.at(i);
                    pos_alpha_ast= i;
            }

        }
    }
//    QString text2, text3, var, var2, var3;

    //text2 = "<font color='Black'> Position of Alpha Ast " +var.sprintf("%.2f",list(36360)) + "<font color='Red'> Position of Alpha XFOIL " +var2.sprintf("%.2f",double(pos_alpha_xfoil));

//   QLabel *alpha2 = new QLabel();
//        alpha2->setText(text2);
//        //alpha2->setNum(pos_alp);
//        alpha2->show();


    m_pCur360Polar->m_ASpec = slope;
    m_pCur360Polar->m_ACrit = alphazero;

    //start constructing the positive extrapolation

        m_pctrlA->setMaximum(30);
        m_pctrlA->setMinimum(-10);

    if (m_pctrlA->value()+posalphamax+2 < m_pCurPolar->m_Alpha.size())
    {
    a1plus = m_pCurPolar->m_Alpha.at(posalphamax+m_pctrlA->value());
    CL1plus= m_pCurPolar->m_Cl.at(posalphamax+m_pctrlA->value());
    }
    else
    {
    a1plus = (posalphamax+m_pctrlA->value())*deltaalpha;
    CL1plus = PlateFlow(alphazero,CLzero, a1plus)+0.03;
    }


    if (m_pCurPolar->m_Alpha.size()-(posalphamax+m_pctrlB->value()+m_pctrlA->value()) > 0)
    {
    a2plus = m_pCurPolar->m_Alpha.at(posalphamax+m_pctrlB->value()+m_pctrlA->value());
    CL2plus =m_pCurPolar->m_Cl.at(posalphamax+m_pctrlB->value()+m_pctrlA->value());
    }
    else
    {
    a2plus = (posalphamax+m_pctrlB->value()+m_pctrlA->value())*deltaalpha;
    CL2plus = PlateFlow(alphazero,CLzero, a2plus)+0.03;
    }

    f1plus=((CL1plus-PlateFlow(alphazero, CLzero, a1plus))/(PotFlow(CLzero, slope, a1plus)-PlateFlow(alphazero, CLzero, a1plus)));
    f2plus=((CL2plus-PlateFlow(alphazero, CLzero, a2plus))/(PotFlow(CLzero, slope, a2plus)-PlateFlow(alphazero, CLzero, a2plus)));

    G=pow((fabs((1/f1plus-1)/(1/f2plus-1))),0.25);


    am=(a1plus-G*a2plus)/(1-G);


    k=(1/f2plus-1)*1/pow((a2plus-am),4);

    /////////rear end flying first

    double deltaCL, Re, slope2 ,am2, k2, G2 ;

    CL180 = PlateFlow(alphazero, CLzero, 180);

    slope2 = 0.8*slope;
    Re=m_pCurPolar->m_Reynolds;
    deltaCL=1.324*pow((1-exp(Re/1000000*(-0.2))), 0.7262);

    CL1plus=CL180-deltaCL;
    a1plus = 170+CL180/slope2;
    a2plus=a1plus-15;
    CL2plus = PlateFlow(alphazero, CLzero, a2plus)-0.01;


    f1plus=(CL1plus-PlateFlow(alphazero, CLzero, a1plus))/(PotFlow(CL180, slope2, a1plus-180)-PlateFlow(alphazero, CLzero, a1plus));
    f2plus=(CL2plus-PlateFlow(alphazero, CLzero, a2plus))/(PotFlow(CL180, slope2, a2plus-180)-PlateFlow(alphazero, CLzero, a2plus));

    G2=pow(fabs(((1/f1plus-1)/(1/f2plus-1))),0.25);

    am2=(a1plus-G2*a2plus)/(1-G2);

    k2=(1/f2plus-1)*1/pow((a2plus-am2),4);

    // construct the positive extrapolation

    double f,delta,alpha=int(1);
    m_cd_360.clear();

   while (alpha <= 180)
    {
        if (alpha >= 40)
        {
            deltaalpha = 3;
        }
        else
        {
            deltaalpha =deltaalpha;
        }

        if (alpha < am2 - 70)
        {

        if (alpha<am)
        {
        delta=0;
        }
        else
        {
        delta=am-alpha;
        }
        f=1/(1+k*pow(delta,4));
        m_pCur360Polar->m_Alpha.append(alpha);
        m_pCur360Polar->m_Cl.append(f*PotFlow(CLzero,slope,alpha)+(1-f)*PlateFlow(alphazero, CLzero, alpha));

        }
        else if (alpha < am2)
        {
        delta=am2-alpha;
        f=1/(1+k2*pow(delta,4));
        m_pCur360Polar->m_Alpha.append(alpha);
        m_pCur360Polar->m_Cl.append(f*PotFlow(CL180,slope2,alpha-180)+(1-f)*PlateFlow(alphazero, CLzero, alpha));

        }
        else
        {
        m_pCur360Polar->m_Alpha.append(alpha);
        m_pCur360Polar->m_Cl.append(PotFlow(CL180,slope2,alpha-180));

        }
         /////////////CD Curve/////

        if (alpha<am)
        {
        delta=0;
        }
        else
        {
        delta=am-alpha;
        }
        f=1/(1+k*pow(delta,4));
        deltaCD=0.13*((f-1)*PotFlow(CLzero,slope,alpha)-(1-f)*PlateFlow(alphazero, CLzero, alpha));
        if (deltaCD <=0) deltaCD=0;


        m_pCur360Polar->m_Cd.append(f*(deltaCD+0.006+1.25*pow(m_pFoil->m_fThickness,2)/180*fabs(alpha))+(1-f)*CDPlate(alpha)+0.006);



         if (alpha >=alpha_ast && alpha<alpha_xfoil)
            {
              m_cd_360.append((f*(deltaCD+0.006+1.25*pow(m_pFoil->m_fThickness,2)/180*fabs(alpha))+(1-f)*CDPlate(alpha)+0.006));
            }

                 alpha=alpha+deltaalpha;

    }

  // start constructing the negative extrapolation

m_pctrlAm->setMinimum(1);
m_pctrlAm->setMaximum(80);




a1minus = (-double(m_pctrlAm->value())/20-CLzero)/slope-4;
CL1minus= -double(m_pctrlAm->value())/20;


a2minus = a1minus-m_pctrlBm->value()*2;
CL2minus = PlateFlow(alphazero,CLzero, a2minus)-0.03;




f1minus=(CL1minus-PlateFlow(alphazero, CLzero, a1minus))/(PotFlow(CLzero, slope, a1minus)-PlateFlow(alphazero, CLzero, a1minus));
f2minus=(CL2minus-PlateFlow(alphazero, CLzero, a2minus))/(PotFlow(CLzero, slope, a2minus)-PlateFlow(alphazero, CLzero, a2minus));

G=pow(fabs((1/f1minus-1)/(1/f2minus-1)),0.25);


am=(a1minus-G*a2minus)/(1-G);


k=(1/f2minus-1)*1/pow((a2minus-am),4);



//////////////////rear end flying first//////////

CL1minus=CL180+deltaCL;
a1minus = -170+CL180/slope2;
a2minus=a1minus+15;
CL2minus = PlateFlow(alphazero, CLzero, a2minus)-0.01;

f1minus=(CL1minus-PlateFlow(alphazero, CLzero, a1minus))/(PotFlow(CL180, slope2, a1minus+180)-PlateFlow(alphazero, CLzero, a1minus));
f2minus=(CL2minus-PlateFlow(alphazero, CLzero, a2minus))/(PotFlow(CL180, slope2, a2minus+180)-PlateFlow(alphazero, CLzero, a2minus));

G2=pow(fabs(((1/f1minus-1)/(1/f2minus-1))),0.25);


am2=(a1minus-G2*a2minus)/(1-G2);



k2=(1/f2minus-1)*1/pow((a2minus-am2),4);


///////////create curve/////////////

alpha=int(0);

while (alpha >= -180)
{

    if (alpha <=-40)
    {
        deltaalpha=3;
    }
    else
    {
        deltaalpha=deltaalpha;
    }

    if (alpha > am2 + 70)
    {
    if (alpha > am)
    {
        delta=0;
    }
    else
    {
    delta=am-alpha;
    }
    f=1/(1+fabs(k*pow(delta,4)));
    m_pCur360Polar->m_Alpha.prepend(alpha);
    m_pCur360Polar->m_Cl.prepend(f*PotFlow(CLzero,slope,alpha)+(1-f)*PlateFlow(alphazero, CLzero, alpha));

    }
    else if (alpha > am2)
    {
    delta=am2-alpha;
    f=1/(1+fabs(k2*pow(delta,4)));
    m_pCur360Polar->m_Alpha.prepend(alpha);
    m_pCur360Polar->m_Cl.prepend(f*PotFlow(CL180,slope2,alpha+180)+(1-f)*PlateFlow(alphazero, CLzero, alpha));

    }
    else
    {
    m_pCur360Polar->m_Alpha.prepend(alpha);
    m_pCur360Polar->m_Cl.prepend(PotFlow(CL180,slope2,alpha+180));

    }

    //////CD Curve/////
    if (alpha > am)
    {
        delta=0;
    }
    else
    {
    delta=am-alpha;
    }
    f=1/(1+k*pow(delta,4));
    deltaCD=0.13*(PotFlow(CLzero,slope,alpha)-f*PotFlow(CLzero,slope,alpha)-(1-f)*PlateFlow(alphazero, CLzero, alpha));
    if (deltaCD <=0) deltaCD=0;
     m_pCur360Polar->m_Cd.prepend(f*(deltaCD+0.006+1.25*pow(m_pFoil->m_fThickness,2)/180*fabs(alpha))+(1-f)*CDPlate(alpha)+0.006);
    ////////////

    alpha=alpha-deltaalpha;
}


}

void QBEM::ComputeGeometry()
{
        // Computes the wing's characteristics from the panel data

        m_pWing->CreateSurfaces(CVector(0.0,0.0,0.0), 0.0, 0.0);
        m_pWing->ComputeGeometry();
        for (int i=0; i<m_pWing->m_NSurfaces; i++) m_pWing->m_Surface[i].SetSidePoints(NULL, 0.0, 0.0);
        OnShowTurbine();
}



void QBEM::Connect()
{
connect(m_pctrlInsertBefore, SIGNAL(clicked()),this, SLOT(OnInsertBefore()));
connect(m_pctrlInsertAfter, SIGNAL(clicked()),this, SLOT(OnInsertAfter()));
connect(m_pctrlDeleteSection, SIGNAL(clicked()),this, SLOT(OnDeleteSection()));

connect(m_pctrlInsertBefore2, SIGNAL(clicked()),this, SLOT(OnInsertBefore()));
connect(m_pctrlInsertAfter2, SIGNAL(clicked()),this, SLOT(OnInsertAfter()));
connect(m_pctrlDeleteSection2, SIGNAL(clicked()),this, SLOT(OnDeleteSection()));

connect(m_pctrlIsOrtho, SIGNAL(clicked()),this, SLOT(OnOrtho()));
connect(m_pctrlWingColor, SIGNAL(clicked()),this, SLOT(OnBladeColor()));
connect(m_pctrlSectionColor, SIGNAL(clicked()),this, SLOT(OnSectionColor()));

connect(m_pctrlSurfaces, SIGNAL(clicked()),this, SLOT(UpdateGeom()));
connect(m_pctrlOutline, SIGNAL(clicked()),this, SLOT(UpdateGeom()));
connect(m_pctrlAirfoils, SIGNAL(clicked()),this, SLOT(UpdateGeom()));
connect(m_pctrlAxes, SIGNAL(clicked()),this, SLOT(UpdateGeom()));
connect(m_pctrlPositions, SIGNAL(clicked()),this, SLOT(UpdateGeom()));
connect(m_pctrlFoilNames, SIGNAL(clicked()),this, SLOT(UpdateGeom()));

connect(m_pctrlCurveStyle, SIGNAL(activated(int)), this, SLOT(OnCurveStyle(int)));
connect(m_pctrlCurveWidth, SIGNAL(activated(int)), this, SLOT(OnCurveWidth(int)));
connect(m_pctrlCurveColor, SIGNAL(clicked()), this, SLOT(OnCurveColor()));









connect(m_pctrlSave, SIGNAL(clicked()),this, SLOT (OnSaveWing()));
connect(m_pctrlAdvancedDesign, SIGNAL(clicked()),this, SLOT(OnAdvancedDesign()));

connect(m_pctrlHubRadius,  SIGNAL(editingFinished()), this, SLOT(OnHubChanged()));
connect(m_pctrlBlades,  SIGNAL(valueChanged(int)), this, SLOT(OnCellChanged()));


connect(m_pctrlNew360, SIGNAL(clicked()),this, SLOT (OnNew360Polar()));
connect(m_pctrlA, SIGNAL(valueChanged(int)), this, SLOT (Compute360Polar()));
connect(m_pctrlB, SIGNAL(valueChanged(int)), this, SLOT (Compute360Polar()));
connect(m_pctrlAm, SIGNAL(valueChanged(int)), this, SLOT (Compute360Polar()));
connect(m_pctrlBm, SIGNAL(valueChanged(int)), this, SLOT (Compute360Polar()));

connect(m_pctrlA, SIGNAL(valueChanged(int)), this, SLOT (CreatePolarCurve()));
connect(m_pctrlB, SIGNAL(valueChanged(int)), this, SLOT (CreatePolarCurve()));
connect(m_pctrlAm, SIGNAL(valueChanged(int)), this, SLOT (CreatePolarCurve()));
connect(m_pctrlBm, SIGNAL(valueChanged(int)), this, SLOT (CreatePolarCurve()));

connect(m_CD90YCoordinate, SIGNAL(clicked()), this, SLOT (Compute360Polar()));
connect(m_CD90LERadius, SIGNAL(clicked()), this, SLOT (Compute360Polar()));

connect(m_CD90YCoordinate, SIGNAL(clicked()), this, SLOT (CreatePolarCurve()));
connect(m_CD90LERadius, SIGNAL(clicked()), this, SLOT (CreatePolarCurve()));


connect(m_pctrlPitchBladeButton, SIGNAL(clicked()), this, SLOT (PitchBlade()));

connect(m_pctrlSave360, SIGNAL(clicked()), this, SLOT (OnSave360Polar()));



//---------------//
connect(m_pctrlNewWing, SIGNAL(clicked()), this, SLOT (OnNewWing()));
connect(m_pctrlEditWing, SIGNAL(clicked()), this, SLOT (OnEditWing()));

connect(m_pctrlScale, SIGNAL(clicked()), this, SLOT (OnScaleBlade()));

connect(m_pctrlBladeStructure, SIGNAL(clicked()),this, SLOT (OnBladeStructure()));



connect(m_pctrlBladeCoordinates, SIGNAL(clicked()), SLOT(OnChangeCoordinates()));


connect(m_pctrlPerspective, SIGNAL(clicked()), SLOT(UpdateView()));

connect(m_pctrlShowTurbine, SIGNAL(clicked()), SLOT(OnShowTurbine()));



connect(m_pctrlPitch, SIGNAL(clicked()), SLOT(CheckTurbineButtons()));
connect(m_pctrlStall, SIGNAL(clicked()), SLOT(CheckTurbineButtons()));
connect(m_pctrlFixed, SIGNAL(clicked()), SLOT(CheckTurbineButtons()));
connect(m_pctrl2Step, SIGNAL(clicked()), SLOT(CheckTurbineButtons()));
connect(m_pctrlVariable, SIGNAL(clicked()), SLOT(CheckTurbineButtons()));

connect(m_pctrlSaveTurbine, SIGNAL(clicked()), SLOT(OnSaveTurbine()));
connect(m_pctrlDiscardTurbine, SIGNAL(clicked()), SLOT(OnDiscardTurbine()));

connect(m_pctrlNewTurbine, SIGNAL(clicked()), SLOT(OnNewTurbine()));
connect(m_pctrlEditTurbine, SIGNAL(clicked()), SLOT(OnEditTurbine()));

connect(m_pctrlOptimize, SIGNAL(clicked()), SLOT(OnOptimize()));
connect(m_pctrlBack, SIGNAL(clicked()), SLOT(OnDiscardWing()));


connect(m_pctrla, SIGNAL(valueChanged(double)), SLOT(OnSetWeibullA(double)));
connect(m_pctrlk, SIGNAL(valueChanged(double)), SLOT(OnSetWeibullK(double)));

//connect(m_pctrl_d_cl, SIGNAL(valueChanged(double)), SLOT(OnSetD_Cl(double)));


connect(m_ComparePolars, SIGNAL(clicked()), SLOT(OnComparePolars()));

connect(m_pctrlSimpleDesign, SIGNAL(clicked()), SLOT(OnSimpleDesign()));

}








void QBEM::CreatePolarCurve()
{

    m_360CLGraph.DeleteCurves();
    m_360CDGraph.DeleteCurves();

    m_360CDGraph.SetAuto(true);
    m_360CLGraph.SetAuto(true);


    if (m_pCurPolar)
    {
        if (m_pCurPolar->m_bIsVisible && m_pCurPolar->m_Alpha.size()>0)
        {

                        CCurve* pPolarCurve = m_360CLGraph.AddCurve();

                        pPolarCurve->ShowPoints(m_pCurPolar->m_bShowPoints);
                        pPolarCurve->SetStyle(m_pCurPolar->m_Style);
                        pPolarCurve->SetColor(m_pCurPolar->m_Color);
                        pPolarCurve->SetWidth(m_pCurPolar->m_Width);
                        FillPolarCurve(pPolarCurve, m_pCurPolar, m_360CLGraph.GetXVariable(), m_360CLGraph.GetYVariable());
                        pPolarCurve->SetTitle(m_pCurPolar->m_PlrName);


                        pPolarCurve = m_360CDGraph.AddCurve();

                        pPolarCurve->ShowPoints(m_pCurPolar->m_bShowPoints);
                        pPolarCurve->SetStyle(m_pCurPolar->m_Style);
                        pPolarCurve->SetColor(m_pCurPolar->m_Color);
                        pPolarCurve->SetWidth(m_pCurPolar->m_Width);
                        FillPolarCurve(pPolarCurve, m_pCurPolar, m_360CDGraph.GetXVariable(), m_360CDGraph.GetYVariable());
                        pPolarCurve->SetTitle(m_pCurPolar->m_PlrName);


        }

    }

    if (m_pCur360Polar)
    {
        if (m_pCur360Polar->m_bIsVisible && m_pCur360Polar->m_Alpha.size()>0)
        {
                       CCurve* pPolarCurve2 = m_360CLGraph.AddCurve();

                        pPolarCurve2->ShowPoints(m_pCur360Polar->m_bShowPoints);
                        pPolarCurve2->SetStyle(m_pCur360Polar->m_Style);
                        pPolarCurve2->SetColor(m_pCur360Polar->m_Color);
                        pPolarCurve2->SetWidth(m_pCur360Polar->m_Width);



                        FillPolarCurve(pPolarCurve2, m_pCur360Polar, m_360CLGraph.GetXVariable(), m_360CLGraph.GetYVariable());
                        pPolarCurve2->SetTitle(m_pCur360Polar->m_PlrName);



                        pPolarCurve2= m_360CDGraph.AddCurve();

                        pPolarCurve2->ShowPoints(m_pCur360Polar->m_bShowPoints);
                        pPolarCurve2->SetStyle(m_pCur360Polar->m_Style);
                        pPolarCurve2->SetColor(m_pCur360Polar->m_Color);
                        pPolarCurve2->SetWidth(m_pCur360Polar->m_Width);
                        FillPolarCurve(pPolarCurve2, m_pCur360Polar, m_360CDGraph.GetXVariable(), m_360CDGraph.GetYVariable());
                        pPolarCurve2->SetTitle(m_pCur360Polar->m_PlrName);

                        if (m_bComparePolarCurves)
                        {
                            for (int i=0;i<s_poa360Polar->size();i++)
                            {
                                CPolar *pPolar = (CPolar *) s_poa360Polar->at(i);

                                if (pPolar->m_FoilName == m_pCur360Polar->m_FoilName)
                                {
                                CCurve* pPolarCurve2 = m_360CLGraph.AddCurve();

                                pPolarCurve2->ShowPoints(pPolar->m_bShowPoints);
                                pPolarCurve2->SetStyle(pPolar->m_Style);
                                pPolarCurve2->SetColor(pPolar->m_Color);
                                pPolarCurve2->SetWidth(pPolar->m_Width);
                                FillPolarCurve(pPolarCurve2, pPolar, m_360CLGraph.GetXVariable(), m_360CLGraph.GetYVariable());
                                pPolarCurve2->SetTitle(pPolar->m_PlrName);



                                pPolarCurve2= m_360CDGraph.AddCurve();

                                pPolarCurve2->ShowPoints(pPolar->m_bShowPoints);
                                pPolarCurve2->SetStyle(pPolar->m_Style);
                                pPolarCurve2->SetColor(pPolar->m_Color);
                                pPolarCurve2->SetWidth(pPolar->m_Width);
                                FillPolarCurve(pPolarCurve2, pPolar, m_360CDGraph.GetXVariable(), m_360CDGraph.GetYVariable());
                                pPolarCurve2->SetTitle(pPolar->m_PlrName);
                                }

                            }
                        }

        }

    }

    if (m_b360PolarChanged)
    {
        m_360CLGraph.SetAutoY(true);
        m_360CLGraph.SetXMin(-180);
        m_360CLGraph.SetXMax(180);

        m_360CDGraph.SetAutoY(true);
        m_360CDGraph.SetXMin(-180);
        m_360CDGraph.SetXMax(180);

        m_b360PolarChanged = false;
    }

        UpdateView();



}

void QBEM::CreateRotorCurves()
{
    m_CharGraph1.DeleteCurves();
    m_CharGraph2.DeleteCurves();
    m_CharGraph3.DeleteCurves();

    m_CharGraph1.SetAuto(true);
    m_CharGraph2.SetAuto(true);
    m_CharGraph3.SetAuto(true);

    for (int i=0;i<s_poaBEMData.size();i++)
    {
        if (m_CharGraph1.m_Type == 0)
        {

            if (s_poaBEMData.at(i)->m_bIsVisible)
            {

            CCurve *pCurve = m_CharGraph1.AddCurve();

            pCurve->ShowPoints(s_poaBEMData.at(i)->m_bShowPoints);
            pCurve->SetStyle(s_poaBEMData.at(i)->m_Style);
            pCurve->SetColor(s_poaBEMData.at(i)->m_Color);
            pCurve->SetWidth(s_poaBEMData.at(i)->m_Width);
            FillRotorCurve(pCurve, s_poaBEMData.at(i), m_CharGraph1.GetXVariable(), m_CharGraph1.GetYVariable());
            pCurve->SetTitle(s_poaBEMData.at(i)->m_BEMName);
            }

        }
        else if (m_pBEMData && m_pBData)

        {

            if(m_bIsolateBladeCurve)
            {
                if (m_pBEMData->m_bIsVisible)
                {
                CCurve *pCurve = m_CharGraph1.AddCurve();
                pCurve->ShowPoints(m_pBEMData->m_bShowPoints);
                pCurve->SetStyle(m_pBEMData->m_Style);
                pCurve->SetColor(m_pBEMData->m_Color);
                pCurve->SetWidth(m_pBEMData->m_Width);
                FillRotorCurve(pCurve, m_pBData, m_CharGraph1.GetXVariable(), m_CharGraph1.GetYVariable());
                pCurve->SetTitle(m_pBData->m_BEMName);
                }

                if (m_bCompareBladeCurve)
                {
                     for (int k=0; k<s_poaBEMData.size();k++)
                        {
                        for (int l=0;l<s_poaBEMData.at(k)->m_BData.size();l++)
                         {
                         if (s_poaBEMData.at(k)->m_BData.at(l)->lambdaglobal == m_pBData->lambdaglobal)
                            {
                            if (s_poaBEMData.at(k)->m_bIsVisible)
                             {
                                CCurve *pCurve = m_CharGraph1.AddCurve();

                                pCurve->ShowPoints(s_poaBEMData.at(k)->m_bShowPoints);
                                pCurve->SetStyle(s_poaBEMData.at(k)->m_Style);
                                pCurve->SetColor(s_poaBEMData.at(k)->m_Color);
                                pCurve->SetWidth(s_poaBEMData.at(k)->m_Width);
                                FillRotorCurve(pCurve, s_poaBEMData.at(k)->m_BData.at(l), m_CharGraph1.GetXVariable(), m_CharGraph1.GetYVariable());
                                pCurve->SetTitle(s_poaBEMData.at(k)->m_BData.at(l)->m_BEMName);

                             }
                            }
                         }
                        }
                }
            }
            else
            {
            for (int j=0; j< m_pBEMData->m_BData.size();j++)
                {

                CCurve *pCurve = m_CharGraph1.AddCurve();

                pCurve->ShowPoints(m_pBEMData->m_BData.at(j)->m_bShowPoints);
                pCurve->SetStyle(m_pBEMData->m_BData.at(j)->m_Style);
                pCurve->SetColor(m_pBEMData->m_BData.at(j)->m_Color);
                if (m_pBEMData->m_BData.at(j)==m_pBData)
                {
                pCurve->SetWidth(m_pBEMData->m_BData.at(j)->m_Width+4);
                }
                else
                {
                pCurve->SetWidth(m_pBEMData->m_BData.at(j)->m_Width);
                }
                FillRotorCurve(pCurve, m_pBEMData->m_BData.at(j), m_CharGraph1.GetXVariable(), m_CharGraph1.GetYVariable());
                pCurve->SetTitle(m_pBEMData->m_BData.at(j)->m_BEMName);
                }
            }
        }
    }

    for (int i=0;i<s_poaBEMData.size();i++)
    {

        if (m_CharGraph2.m_Type == 0)
        {

            if (s_poaBEMData.at(i)->m_bIsVisible)
            {

            CCurve *pCurve = m_CharGraph2.AddCurve();

            pCurve->ShowPoints(s_poaBEMData.at(i)->m_bShowPoints);
            pCurve->SetStyle(s_poaBEMData.at(i)->m_Style);
            pCurve->SetColor(s_poaBEMData.at(i)->m_Color);
            pCurve->SetWidth(s_poaBEMData.at(i)->m_Width);
            FillRotorCurve(pCurve, s_poaBEMData.at(i), m_CharGraph2.GetXVariable(), m_CharGraph2.GetYVariable());
            pCurve->SetTitle(s_poaBEMData.at(i)->m_BEMName);
            }
        }
        else if (m_pBEMData && m_pBData)
        {
            if(m_bIsolateBladeCurve)
            {
                if (m_pBEMData->m_bIsVisible)
                {
                CCurve *pCurve = m_CharGraph2.AddCurve();

                pCurve->ShowPoints(m_pBEMData->m_bShowPoints);
                pCurve->SetStyle(m_pBEMData->m_Style);
                pCurve->SetColor(m_pBEMData->m_Color);
                pCurve->SetWidth(m_pBEMData->m_Width);
                FillRotorCurve(pCurve, m_pBData, m_CharGraph2.GetXVariable(), m_CharGraph2.GetYVariable());
                pCurve->SetTitle(m_pBData->m_BEMName);
                }

                if (m_bCompareBladeCurve)
                {
                     for (int k=0; k<s_poaBEMData.size();k++)
                        {
                        for (int l=0;l<s_poaBEMData.at(k)->m_BData.size();l++)
                         {
                         if (s_poaBEMData.at(k)->m_BData.at(l)->lambdaglobal == m_pBData->lambdaglobal)
                            {
                            if (s_poaBEMData.at(k)->m_bIsVisible)
                             {
                                CCurve *pCurve = m_CharGraph2.AddCurve();

                                pCurve->ShowPoints(s_poaBEMData.at(k)->m_bShowPoints);
                                pCurve->SetStyle(s_poaBEMData.at(k)->m_Style);
                                pCurve->SetColor(s_poaBEMData.at(k)->m_Color);
                                pCurve->SetWidth(s_poaBEMData.at(k)->m_Width);
                                FillRotorCurve(pCurve, s_poaBEMData.at(k)->m_BData.at(l), m_CharGraph2.GetXVariable(), m_CharGraph2.GetYVariable());
                                pCurve->SetTitle(s_poaBEMData.at(k)->m_BData.at(l)->m_BEMName);

                             }
                            }
                         }
                        }
                }
            }
            else
            {
            for (int j=0; j< m_pBEMData->m_BData.size();j++)
            {

            CCurve *pCurve = m_CharGraph2.AddCurve();
            pCurve->ShowPoints(m_pBEMData->m_BData.at(j)->m_bShowPoints);
            pCurve->SetStyle(m_pBEMData->m_BData.at(j)->m_Style);
            pCurve->SetColor(m_pBEMData->m_BData.at(j)->m_Color);
            if (m_pBEMData->m_BData.at(j)==m_pBData)
            {
            pCurve->SetWidth(m_pBEMData->m_BData.at(j)->m_Width+4);
            }
            else
            {
            pCurve->SetWidth(m_pBEMData->m_BData.at(j)->m_Width);
            }
            FillRotorCurve(pCurve, m_pBEMData->m_BData.at(j), m_CharGraph2.GetXVariable(), m_CharGraph2.GetYVariable());
            pCurve->SetTitle(m_pBEMData->m_BData.at(j)->m_BEMName);
            }
            }
        }
    }


    for (int i=0;i<s_poaBEMData.size();i++)
    {
        if (m_CharGraph3.m_Type == 0)
        {

            if (s_poaBEMData.at(i)->m_bIsVisible)
            {

            CCurve *pCurve = m_CharGraph3.AddCurve();

            pCurve->ShowPoints(s_poaBEMData.at(i)->m_bShowPoints);
            pCurve->SetStyle(s_poaBEMData.at(i)->m_Style);
            pCurve->SetColor(s_poaBEMData.at(i)->m_Color);
            pCurve->SetWidth(m_pBEMData->m_BData.at(i)->m_Width);
            FillRotorCurve(pCurve, s_poaBEMData.at(i), m_CharGraph3.GetXVariable(), m_CharGraph3.GetYVariable());
            pCurve->SetTitle(s_poaBEMData.at(i)->m_BEMName);
            }
        }
        else if (m_pBEMData && m_pBData)
        {
            if(m_bIsolateBladeCurve)
            {
                if (m_pBEMData->m_bIsVisible)
                {
                CCurve *pCurve = m_CharGraph3.AddCurve();

                pCurve->ShowPoints(m_pBEMData->m_bShowPoints);
                pCurve->SetStyle(m_pBEMData->m_Style);
                pCurve->SetColor(m_pBEMData->m_Color);
                pCurve->SetWidth(m_pBEMData->m_Width);
                FillRotorCurve(pCurve, m_pBData, m_CharGraph3.GetXVariable(), m_CharGraph3.GetYVariable());
                pCurve->SetTitle(m_pBData->m_BEMName);
                }

                if (m_bCompareBladeCurve)
                {
                     for (int k=0; k<s_poaBEMData.size();k++)
                        {
                        for (int l=0;l<s_poaBEMData.at(k)->m_BData.size();l++)
                         {
                         if (s_poaBEMData.at(k)->m_BData.at(l)->lambdaglobal == m_pBData->lambdaglobal)
                            {
                            if (s_poaBEMData.at(k)->m_bIsVisible)
                             {
                                CCurve *pCurve = m_CharGraph3.AddCurve();

                                pCurve->ShowPoints(s_poaBEMData.at(k)->m_bShowPoints);
                                pCurve->SetStyle(s_poaBEMData.at(k)->m_Style);
                                pCurve->SetColor(s_poaBEMData.at(k)->m_Color);
                                pCurve->SetWidth(s_poaBEMData.at(k)->m_Width);
                                FillRotorCurve(pCurve, s_poaBEMData.at(k)->m_BData.at(l), m_CharGraph3.GetXVariable(), m_CharGraph3.GetYVariable());
                                pCurve->SetTitle(s_poaBEMData.at(k)->m_BData.at(l)->m_BEMName);

                             }
                            }
                         }
                        }
                }
            }
            else
            {
            for (int j=0; j< m_pBEMData->m_BData.size();j++)
            {

            CCurve *pCurve = m_CharGraph3.AddCurve();

            pCurve->ShowPoints(m_pBEMData->m_BData.at(j)->m_bShowPoints);
            pCurve->SetStyle(m_pBEMData->m_BData.at(j)->m_Style);
            pCurve->SetColor(m_pBEMData->m_BData.at(j)->m_Color);
            if (m_pBEMData->m_BData.at(j)==m_pBData)
            {
            pCurve->SetWidth(m_pBEMData->m_BData.at(j)->m_Width+4);
            }
            else
            {
            pCurve->SetWidth(m_pBEMData->m_BData.at(j)->m_Width);
            }
            FillRotorCurve(pCurve, m_pBEMData->m_BData.at(j), m_CharGraph3.GetXVariable(), m_CharGraph3.GetYVariable());
            pCurve->SetTitle(m_pBEMData->m_BData.at(j)->m_BEMName);
            }
            }
        }
    }

    if (m_pBEMData && selected_lambda >= 0 && m_bShowOpPoint)
    {

    if (m_pBEMData->m_bIsVisible && m_CharGraph1.m_Type == 0)
    {
    CCurve* pPolarCurve = m_CharGraph1.AddCurve();
    pPolarCurve->ShowPoints(true);
    pPolarCurve->SetWidth(m_pBEMData->m_Width+3);
    pPolarCurve->SetColor(m_pBEMData->m_Color);
    QList <double> *X = (QList <double> *) GetRotorVariable(m_pBEMData, m_CharGraph1.GetXVariable());
    QList <double> *Y = (QList <double> *) GetRotorVariable(m_pBEMData, m_CharGraph1.GetYVariable());
    pPolarCurve->AddPoint(X->at(selected_lambda),Y->at(selected_lambda));
    }

    if (m_pBEMData->m_bIsVisible && m_CharGraph2.m_Type == 0)
    {
    CCurve* pPolarCurve = m_CharGraph2.AddCurve();
    pPolarCurve->ShowPoints(true);
    pPolarCurve->SetWidth(m_pBEMData->m_Width+3);
    pPolarCurve->SetColor(m_pBEMData->m_Color);
    QList <double> *X = (QList <double> *) GetRotorVariable(m_pBEMData, m_CharGraph2.GetXVariable());
    QList <double> *Y = (QList <double> *) GetRotorVariable(m_pBEMData, m_CharGraph2.GetYVariable());
    pPolarCurve->AddPoint(X->at(selected_lambda),Y->at(selected_lambda));
    }

    if (m_pBEMData->m_bIsVisible && m_CharGraph3.m_Type == 0)
    {
    CCurve* pPolarCurve = m_CharGraph3.AddCurve();
    pPolarCurve->ShowPoints(true);
    pPolarCurve->SetWidth(m_pBEMData->m_Width+3);
    pPolarCurve->SetColor(m_pBEMData->m_Color);
    QList <double> *X = (QList <double> *) GetRotorVariable(m_pBEMData, m_CharGraph3.GetXVariable());
    QList <double> *Y = (QList <double> *) GetRotorVariable(m_pBEMData, m_CharGraph3.GetYVariable());
    pPolarCurve->AddPoint(X->at(selected_lambda),Y->at(selected_lambda));
    }

    }


    UpdateView();
}

void QBEM::CreatePowerCurves()
{

    m_PowerGraph1.DeleteCurves();
    m_PowerGraph2.DeleteCurves();
    m_PowerGraph3.DeleteCurves();

    m_PowerGraph1.SetAuto(true);
    m_PowerGraph2.SetAuto(true);
    m_PowerGraph3.SetAuto(true);


    for (int i=0;i<s_poaTBEMData.size();i++)
    {
        if (m_PowerGraph1.m_Type == 0)
        {

            if (s_poaTBEMData.at(i)->m_bIsVisible)
            {

            CCurve *pCurve = m_PowerGraph1.AddCurve();

            pCurve->ShowPoints(s_poaTBEMData.at(i)->m_bShowPoints);
            pCurve->SetStyle(s_poaTBEMData.at(i)->m_Style);
            pCurve->SetColor(s_poaTBEMData.at(i)->m_Color);
            pCurve->SetWidth(s_poaTBEMData.at(i)->m_Width);
            FillPowerCurve(pCurve, s_poaTBEMData.at(i), m_PowerGraph1.GetXVariable(), m_PowerGraph1.GetYVariable());
            pCurve->SetTitle(s_poaTBEMData.at(i)->m_TurbineName);


            }
        }
        else if (m_pTBEMData && m_pTurbineBData)

        {
            if(m_bIsolateBladeCurve)
            {
                if (m_pTBEMData->m_bIsVisible)
                {
                CCurve *pCurve = m_PowerGraph1.AddCurve();

                pCurve->ShowPoints(m_pTBEMData->m_bShowPoints);
                pCurve->SetStyle(m_pTBEMData->m_Style);
                pCurve->SetColor(m_pTBEMData->m_Color);
                pCurve->SetWidth(m_pTBEMData->m_Width);
                FillPowerCurve(pCurve, m_pTurbineBData, m_PowerGraph1.GetXVariable(), m_PowerGraph1.GetYVariable());
                pCurve->SetTitle(m_pTurbineBData->m_BEMName);
                }

                if (m_bCompareBladeCurve)
                {
                     for (int k=0; k<s_poaTBEMData.size();k++)
                        {
                        for (int l=0;l<s_poaTBEMData.at(k)->m_BData.size();l++)
                         {
                         if (s_poaTBEMData.at(k)->m_BData.at(l)->windspeedStr == m_pTurbineBData->windspeedStr)
                            {
                            if (s_poaTBEMData.at(k)->m_bIsVisible)
                             {
                                CCurve *pCurve = m_PowerGraph1.AddCurve();

                                pCurve->ShowPoints(s_poaTBEMData.at(k)->m_bShowPoints);
                                pCurve->SetStyle(s_poaTBEMData.at(k)->m_Style);
                                pCurve->SetColor(s_poaTBEMData.at(k)->m_Color);
                                pCurve->SetWidth(s_poaTBEMData.at(k)->m_Width);
                                FillPowerCurve(pCurve, s_poaTBEMData.at(k)->m_BData.at(l), m_PowerGraph1.GetXVariable(), m_PowerGraph1.GetYVariable());
                                pCurve->SetTitle(s_poaTBEMData.at(k)->m_BData.at(l)->m_BEMName);

                             }
                            }
                         }
                        }
                }
            }
            else
            {
            for (int j=0; j< m_pTBEMData->m_BData.size();j++)
            {

            CCurve *pCurve = m_PowerGraph1.AddCurve();

            pCurve->ShowPoints(m_pTBEMData->m_BData.at(j)->m_bShowPoints);
            pCurve->SetStyle(m_pTBEMData->m_BData.at(j)->m_Style);
            pCurve->SetColor(m_pTBEMData->m_BData.at(j)->m_Color);
            if (m_pTBEMData->m_BData.at(j)==m_pTurbineBData)
            {
            pCurve->SetWidth(m_pTBEMData->m_BData.at(j)->m_Width+4);
            }
            else
            {
            pCurve->SetWidth(m_pTBEMData->m_BData.at(j)->m_Width);
            }
            FillPowerCurve(pCurve, m_pTBEMData->m_BData.at(j), m_PowerGraph1.GetXVariable(), m_PowerGraph1.GetYVariable());
            pCurve->SetTitle(m_pTBEMData->m_BData.at(j)->m_BEMName);
            }
            }
        }
    }

    for (int i=0;i<s_poaTBEMData.size();i++)
    {
        if (m_PowerGraph2.m_Type == 0)
        {

            if (s_poaTBEMData.at(i)->m_bIsVisible)
            {

            CCurve *pCurve = m_PowerGraph2.AddCurve();

            pCurve->ShowPoints(s_poaTBEMData.at(i)->m_bShowPoints);
            pCurve->SetStyle(s_poaTBEMData.at(i)->m_Style);
            pCurve->SetColor(s_poaTBEMData.at(i)->m_Color);
            pCurve->SetWidth(s_poaTBEMData.at(i)->m_Width);
            FillPowerCurve(pCurve, s_poaTBEMData.at(i), m_PowerGraph2.GetXVariable(), m_PowerGraph2.GetYVariable());
            pCurve->SetTitle(s_poaTBEMData.at(i)->m_TurbineName);

            }
        }
        else if (m_pTBEMData && m_pTurbineBData)

        {
            if(m_bIsolateBladeCurve)
            {
                CCurve *pCurve = m_PowerGraph2.AddCurve();

                if (m_pTBEMData->m_bIsVisible)
                {
                pCurve->ShowPoints(m_pTBEMData->m_bShowPoints);
                pCurve->SetStyle(m_pTBEMData->m_Style);
                pCurve->SetColor(m_pTBEMData->m_Color);
                pCurve->SetWidth(m_pTBEMData->m_Width);
                FillPowerCurve(pCurve, m_pTurbineBData, m_PowerGraph2.GetXVariable(), m_PowerGraph2.GetYVariable());
                pCurve->SetTitle(m_pTurbineBData->m_BEMName);
                }

                if (m_bCompareBladeCurve)
                {
                     for (int k=0; k<s_poaTBEMData.size();k++)
                        {
                        for (int l=0;l<s_poaTBEMData.at(k)->m_BData.size();l++)
                         {
                         if (s_poaTBEMData.at(k)->m_BData.at(l)->windspeedStr == m_pTurbineBData->windspeedStr)
                            {
                            if (s_poaTBEMData.at(k)->m_bIsVisible)
                             {
                                CCurve *pCurve = m_PowerGraph2.AddCurve();

                                pCurve->ShowPoints(s_poaTBEMData.at(k)->m_bShowPoints);
                                pCurve->SetStyle(s_poaTBEMData.at(k)->m_Style);
                                pCurve->SetColor(s_poaTBEMData.at(k)->m_Color);
                                pCurve->SetWidth(s_poaTBEMData.at(k)->m_Width);
                                FillPowerCurve(pCurve, s_poaTBEMData.at(k)->m_BData.at(l), m_PowerGraph2.GetXVariable(), m_PowerGraph2.GetYVariable());
                                pCurve->SetTitle(s_poaTBEMData.at(k)->m_BData.at(l)->m_BEMName);

                             }
                            }
                         }
                        }
                }

            }
            else
            {
            for (int j=0; j< m_pTBEMData->m_BData.size();j++)
            {

            CCurve *pCurve = m_PowerGraph2.AddCurve();

            pCurve->ShowPoints(m_pTBEMData->m_BData.at(j)->m_bShowPoints);
            pCurve->SetStyle(m_pTBEMData->m_BData.at(j)->m_Style);
            pCurve->SetColor(m_pTBEMData->m_BData.at(j)->m_Color);
            if (m_pTBEMData->m_BData.at(j)==m_pTurbineBData)
            {
            pCurve->SetWidth(m_pTBEMData->m_BData.at(j)->m_Width+4);
            }
            else
            {
            pCurve->SetWidth(m_pTBEMData->m_BData.at(j)->m_Width);
            }
            FillPowerCurve(pCurve, m_pTBEMData->m_BData.at(j), m_PowerGraph2.GetXVariable(), m_PowerGraph2.GetYVariable());
            pCurve->SetTitle(m_pTBEMData->m_BData.at(j)->m_BEMName);
            }
            }
        }
    }

    for (int i=0;i<s_poaTBEMData.size();i++)
    {
        if (m_PowerGraph3.m_Type == 0)
        {

            if (s_poaTBEMData.at(i)->m_bIsVisible)
            {

            CCurve *pCurve = m_PowerGraph3.AddCurve();

            pCurve->ShowPoints(s_poaTBEMData.at(i)->m_bShowPoints);
            pCurve->SetStyle(s_poaTBEMData.at(i)->m_Style);
            pCurve->SetColor(s_poaTBEMData.at(i)->m_Color);
            pCurve->SetWidth(s_poaTBEMData.at(i)->m_Width);
            FillPowerCurve(pCurve, s_poaTBEMData.at(i), m_PowerGraph3.GetXVariable(), m_PowerGraph3.GetYVariable());
            pCurve->SetTitle(s_poaTBEMData.at(i)->m_TurbineName);

            }
        }
        else if (m_pTBEMData && m_pTurbineBData)

        {
            if(m_bIsolateBladeCurve)
            {
                if (m_pTBEMData->m_bIsVisible)
                {
                CCurve *pCurve = m_PowerGraph3.AddCurve();

                pCurve->ShowPoints(m_pTBEMData->m_bShowPoints);
                pCurve->SetStyle(m_pTBEMData->m_Style);
                pCurve->SetColor(m_pTBEMData->m_Color);
                pCurve->SetWidth(m_pTBEMData->m_Width);
                FillPowerCurve(pCurve, m_pTurbineBData, m_PowerGraph3.GetXVariable(), m_PowerGraph3.GetYVariable());
                pCurve->SetTitle(m_pTurbineBData->m_BEMName);
                }

                if (m_bCompareBladeCurve)
                {
                     for (int k=0; k<s_poaTBEMData.size();k++)
                        {
                        for (int l=0;l<s_poaTBEMData.at(k)->m_BData.size();l++)
                         {
                         if (s_poaTBEMData.at(k)->m_BData.at(l)->windspeedStr == m_pTurbineBData->windspeedStr)
                            {
                            if (s_poaTBEMData.at(k)->m_bIsVisible)
                             {
                                CCurve *pCurve = m_PowerGraph3.AddCurve();

                                pCurve->ShowPoints(s_poaTBEMData.at(k)->m_bShowPoints);
                                pCurve->SetStyle(s_poaTBEMData.at(k)->m_Style);
                                pCurve->SetColor(s_poaTBEMData.at(k)->m_Color);
                                pCurve->SetWidth(s_poaTBEMData.at(k)->m_Width);
                                FillPowerCurve(pCurve, s_poaTBEMData.at(k)->m_BData.at(l), m_PowerGraph3.GetXVariable(), m_PowerGraph3.GetYVariable());
                                pCurve->SetTitle(s_poaTBEMData.at(k)->m_BData.at(l)->m_BEMName);

                             }
                            }
                         }
                        }
                }
            }
            else
            {
            for (int j=0; j< m_pTBEMData->m_BData.size();j++)
            {

            CCurve *pCurve = m_PowerGraph3.AddCurve();

            pCurve->ShowPoints(m_pTBEMData->m_BData.at(j)->m_bShowPoints);
            pCurve->SetStyle(m_pTBEMData->m_BData.at(j)->m_Style);
            pCurve->SetColor(m_pTBEMData->m_BData.at(j)->m_Color);
            if (m_pTBEMData->m_BData.at(j)==m_pTurbineBData)
            {
            pCurve->SetWidth(m_pTBEMData->m_BData.at(j)->m_Width+4);
            }
            else
            {
            pCurve->SetWidth(m_pTBEMData->m_BData.at(j)->m_Width);
            }
            FillPowerCurve(pCurve, m_pTBEMData->m_BData.at(j), m_PowerGraph3.GetXVariable(), m_PowerGraph3.GetYVariable());
            pCurve->SetTitle(m_pTBEMData->m_BData.at(j)->m_BEMName);
            }
            }
        }
    }

    if (m_pTBEMData && selected_windspeed >= 0 && m_bShowOpPoint)
    {

        if (m_pTBEMData->m_bIsVisible && m_PowerGraph1.m_Type == 0)
        {
        CCurve* pPolarCurve = m_PowerGraph1.AddCurve();
        pPolarCurve->ShowPoints(true);
        pPolarCurve->SetWidth(m_pTBEMData->m_Width+3);
        pPolarCurve->SetColor(m_pTBEMData->m_Color);
        QList <double> *X = (QList <double> *) GetTurbineRotorVariable(m_pTBEMData, m_PowerGraph1.GetXVariable());
        QList <double> *Y = (QList <double> *) GetTurbineRotorVariable(m_pTBEMData, m_PowerGraph1.GetYVariable());
        pPolarCurve->AddPoint(X->at(selected_windspeed),Y->at(selected_windspeed));
        }

        if (m_pTBEMData->m_bIsVisible && m_PowerGraph2.m_Type == 0)
        {
        CCurve* pPolarCurve = m_PowerGraph2.AddCurve();
        pPolarCurve->ShowPoints(true);
        pPolarCurve->SetWidth(m_pTBEMData->m_Width+3);
        pPolarCurve->SetColor(m_pTBEMData->m_Color);
        QList <double> *X = (QList <double> *) GetTurbineRotorVariable(m_pTBEMData, m_PowerGraph2.GetXVariable());
        QList <double> *Y = (QList <double> *) GetTurbineRotorVariable(m_pTBEMData, m_PowerGraph2.GetYVariable());
        pPolarCurve->AddPoint(X->at(selected_windspeed),Y->at(selected_windspeed));
        }

        if (m_pTBEMData->m_bIsVisible && m_PowerGraph3.m_Type == 0)
        {
        CCurve* pPolarCurve = m_PowerGraph3.AddCurve();
        pPolarCurve->ShowPoints(true);
        pPolarCurve->SetWidth(m_pTBEMData->m_Width+3);
        pPolarCurve->SetColor(m_pTBEMData->m_Color);
        QList <double> *X = (QList <double> *) GetTurbineRotorVariable(m_pTBEMData, m_PowerGraph3.GetXVariable());
        QList <double> *Y = (QList <double> *) GetTurbineRotorVariable(m_pTBEMData, m_PowerGraph3.GetYVariable());
        pPolarCurve->AddPoint(X->at(selected_windspeed),Y->at(selected_windspeed));
    }

    }







    UpdateView();
}

void QBEM::Delete360Polar(CPolar *pPolar)
{


    if (pPolar)
    {

    for (int i=0;i<s_poaBEMWings->size();i++)
    {

        CBlade *pWing = (CBlade *) s_poaBEMWings->at(i);

        for (int j=0;j<pWing->m_Polar.size();j++)
        {
            if(pWing->m_Polar.at(j) == pPolar->m_PlrName)
            {
                DeleteWing(pWing);
                i--;
                break;
            }
        }

    }


    for (int i=0;i<s_poa360Polar->size();i++)
    {
        CPolar *cPolar = (CPolar *) s_poa360Polar->at(i);

        if (pPolar->m_PlrName == cPolar->m_PlrName)
        {
            delete pPolar;
            s_poa360Polar->removeAt(i);
        }

    }


    m_pCur360Polar = NULL;

    Update360Polars();
    }

}

void QBEM::DeletePolar(CPolar *pPolar)
{
    if (pPolar)
    {

        for (int i=0; i<s_poa360Polar->size();i++)
        {
            CPolar *cPolar = (CPolar *) s_poa360Polar->at(i);
            if (pPolar->m_PlrName == cPolar->m_ParentPlrName)
            {
                Delete360Polar(cPolar);
                i--;
            }

        }
        m_pCur360Polar = NULL;
        m_pCurPolar = NULL;
        m_pFoil = NULL;
        UpdateFoils();
    }

}

void QBEM::DeleteWing(CBlade *pWing)
{
    ////Delete Turbine Sims
    m_pWing = pWing;

    for (int i=0;i<s_poaTData.size();i++)
    {
        if (s_poaTData.at(i)->m_WingName == m_pWing->m_WingName)
        {
            for (int j=0; j<s_poaTBEMData.size();j++)
            {
                if (s_poaTBEMData.at(j)->m_TurbineName == s_poaTData.at(i)->m_TurbineName)
                {
                    for (int l=0;l<s_poaTBEMData.at(j)->m_BData.size();l++)
                    {
                        delete s_poaTBEMData.at(j)->m_BData.at(l);
                    }

                    delete s_poaTBEMData.at(j);
                    s_poaTBEMData.removeAt(j);
                    j--;
                }
            }

            delete s_poaTData.at(i);
            s_poaTData.removeAt(i);
            i--;
        }
    }


    ////Delete Rotor Sims
    for (int i=0; i<s_poaBEMData.size();i++)
    {
        if (s_poaBEMData.at(i)->m_WingName == m_pWing->m_WingName)
        {
            for (int j=0; j < s_poaBEMData.at(i)->m_BData.size();j++)
            {
                delete s_poaBEMData.at(i)->m_BData.at(j);
            }

        delete s_poaBEMData.at(i);
        s_poaBEMData.removeAt(i);
        i--;

        }
    }



    for (int i=0;i<s_poaBEMWings->size();i++)
    {
        CBlade *pWing = (CBlade *) s_poaBEMWings->at(i);
        if (pWing->m_WingName == m_pWing->m_WingName)
        {
            s_poaBEMWings->removeAt(i);
            delete pWing;
            break;
        }
    }

    m_pWing = NULL;
    m_pTData = NULL;
    m_pTBEMData = NULL;
    m_pTurbineBData = NULL;
    m_pBData = NULL;
    UpdateWings();
    UpdateTurbines();


}

void QBEM::DeleteTurbine(TData *pTData)
{
if (pTData)
{
    for (int i=0;i<s_poaTBEMData.size();i++)
    {
        if (s_poaTBEMData.at(i)->m_TurbineName == pTData->m_TurbineName)
        {
            for (int j=0;j<s_poaTBEMData.at(i)->m_BData.size();j++)
            {
                delete s_poaTBEMData.at(i)->m_BData.at(j);
            }
            delete s_poaTBEMData.at(i);
            s_poaTBEMData.removeAt(i);
            i--;
        }
    }

    for (int i=0;i<s_poaTData.size();i++)
    {
        if (s_poaTData.at(i)->m_TurbineName == pTData->m_TurbineName)
        {
            delete s_poaTData.at(i);
            s_poaTData.removeAt(i);
        }
    }

    m_pTData = NULL;

    UpdateTurbines();
}

}

void QBEM::DisableAllButtons()
{
    MainFrame *pMainFrame = (MainFrame *) s_pMainFrame;
    SimuWidget *pSimuWidget = (SimuWidget *) m_pSimuWidget;

    pMainFrame->BEMViewMenu->setEnabled(false);
    pMainFrame->BEM360PolarMenu->setEnabled(false);
    pMainFrame->BEMBladeMenu->setEnabled(false);
    pMainFrame->BEMCtxMenu->setEnabled(false);
    pMainFrame->BEMTurbine->setEnabled(false);
    pMainFrame->optionsMenu->setEnabled(false);

    pMainFrame->m_pctrlBEMToolBar->setEnabled(false);
    pMainFrame->m_pctrlBEM360ToolBar->setEnabled(false);
    pMainFrame->m_pctrlTurbineToolBar->setEnabled(false);

    pMainFrame->fileMenu->setEnabled(false);


    pSimuWidget->m_pctrlDefineTurbineSim->setEnabled(false);
    pSimuWidget->m_pctrlStartTurbineSim->setEnabled(false);
    pSimuWidget->m_pctrlWind1->setEnabled(false);
    pSimuWidget->m_pctrlWind2->setEnabled(false);
    pSimuWidget->m_pctrlWindDelta->setEnabled(false);


    pSimuWidget->m_pctrlCreateBEM->setEnabled(false);
    pSimuWidget->m_pctrlStartBEM->setEnabled(false);
    pSimuWidget->m_pctrlLSLineEdit->setEnabled(false);
    pSimuWidget->m_pctrlLELineEdit->setEnabled(false);
    pSimuWidget->m_pctrlLDLineEdit->setEnabled(false);
}

void QBEM::EnableAllButtons()
{
    MainFrame *pMainFrame = (MainFrame *) s_pMainFrame;

    pMainFrame->BEMViewMenu->setEnabled(true);
    pMainFrame->BEM360PolarMenu->setEnabled(true);
    pMainFrame->BEMBladeMenu->setEnabled(true);
    pMainFrame->BEMCtxMenu->setEnabled(true);
    pMainFrame->BEMTurbine->setEnabled(true);

    pMainFrame->m_pctrlBEMToolBar->setEnabled(true);
    pMainFrame->m_pctrlBEM360ToolBar->setEnabled(true);
    pMainFrame->m_pctrlTurbineToolBar->setEnabled(true);

    pMainFrame->fileMenu->setEnabled(true);
    pMainFrame->optionsMenu->setEnabled(true);



}

void QBEM::FillComboBoxes(bool bEnable)
{

        SimuWidget *pSimuWidget = (SimuWidget *) m_pSimuWidget;

        if(!bEnable)
        {
                pSimuWidget->m_pctrlCurveColor->setEnabled(false);
                pSimuWidget->m_pctrlCurveStyle->setEnabled(false);
                pSimuWidget->m_pctrlCurveWidth->setEnabled(false);
                pSimuWidget->m_pctrlShowCurve->setEnabled(false);
                pSimuWidget->m_pctrlShowPoints->setEnabled(false);
                pSimuWidget->m_pctrlShowOpPoint->setEnabled(false);
        }
        else
        {
                pSimuWidget->m_pctrlCurveColor->setEnabled(true);
                pSimuWidget->m_pctrlCurveStyle->setEnabled(true);
                pSimuWidget->m_pctrlCurveWidth->setEnabled(true);
                pSimuWidget->m_pctrlShowCurve->setEnabled(true);
                pSimuWidget->m_pctrlShowPoints->setEnabled(true);
                pSimuWidget->m_pctrlShowOpPoint->setEnabled(true);
        }
        int LineWidth[5];
        for (int i=0; i<5;i++) LineWidth[i] = m_CurveWidth;
        pSimuWidget->m_pStyleDelegate->SetLineWidth(LineWidth); // the same selected width for all styles
        pSimuWidget->m_pStyleDelegate->SetLineColor(m_CurveColor);

        int LineStyle[5];
        for (int i=0; i<5;i++) LineStyle[i] = m_CurveStyle;
        pSimuWidget->m_pWidthDelegate->SetLineStyle(LineStyle); //the same selected style for all widths
        pSimuWidget->m_pWidthDelegate->SetLineColor(m_CurveColor);

        pSimuWidget->m_pctrlCurveStyle->SetLine(m_CurveStyle, m_CurveWidth, m_CurveColor);
        pSimuWidget->m_pctrlCurveWidth->SetLine(m_CurveStyle, m_CurveWidth, m_CurveColor);

        pSimuWidget->m_pctrlCurveColor->SetColor(m_CurveColor);
        pSimuWidget->m_pctrlCurveColor->SetStyle(m_CurveStyle);
        pSimuWidget->m_pctrlCurveColor->SetWidth(m_CurveWidth);

        pSimuWidget->m_pctrlCurveStyle->update();
        pSimuWidget->m_pctrlCurveWidth->update();
        pSimuWidget->m_pctrlCurveColor->update();

        pSimuWidget->m_pctrlCurveStyle->setCurrentIndex(m_CurveStyle);
        pSimuWidget->m_pctrlCurveWidth->setCurrentIndex(m_CurveWidth-1);

        if (m_iView == PolarView)
        {

            if(!bEnable)
            {
                    m_pctrlCurveColor->setEnabled(false);
                    m_pctrlCurveStyle->setEnabled(false);
                    m_pctrlCurveWidth->setEnabled(false);

            }
            else
            {
                    m_pctrlCurveColor->setEnabled(true);
                    m_pctrlCurveStyle->setEnabled(true);
                    m_pctrlCurveWidth->setEnabled(true);
            }
            int LineWidth[5];
            for (int i=0; i<5;i++) LineWidth[i] = m_CurveWidth;
            m_pStyleDelegate->SetLineWidth(LineWidth); // the same selected width for all styles
            m_pStyleDelegate->SetLineColor(m_CurveColor);

            int LineStyle[5];
            for (int i=0; i<5;i++) LineStyle[i] = m_CurveStyle;
            m_pWidthDelegate->SetLineStyle(LineStyle); //the same selected style for all widths
            m_pWidthDelegate->SetLineColor(m_CurveColor);

            m_pctrlCurveStyle->SetLine(m_CurveStyle, m_CurveWidth, m_CurveColor);
            m_pctrlCurveWidth->SetLine(m_CurveStyle, m_CurveWidth, m_CurveColor);

            m_pctrlCurveColor->SetColor(m_CurveColor);
            m_pctrlCurveColor->SetStyle(m_CurveStyle);
            m_pctrlCurveColor->SetWidth(m_CurveWidth);

            m_pctrlCurveStyle->update();
            m_pctrlCurveWidth->update();
            m_pctrlCurveColor->update();

            m_pctrlCurveStyle->setCurrentIndex(m_CurveStyle);
            m_pctrlCurveWidth->setCurrentIndex(m_CurveWidth-1);
        }

}

void QBEM::FillDataTable()
{
        if(!m_pWing) return;
        int i;
        if (!m_bAdvancedEdit) m_pWingModel->setRowCount(m_pWing->m_NPanel+1);
        if (m_bAdvancedEdit)  m_pBladeAxisModel->setRowCount(m_pWing->m_NPanel+1);

        for(i=0; i<=m_pWing->m_NPanel; i++)
        {
            if (m_bAdvancedEdit)
            {
                FillAdvancedTableRow(i);
            }
            else
            {
                FillTableRow(i);
            }
        }


}



void QBEM::FillPolarCurve(CCurve *pCurve, CPolar *pPolar, int XVar, int YVar)
{
        int i;
        QList <double> *pX;
        QList <double> *pY;
        QList <double> ClCd;

        pX = (QList <double> *) GetVariable(pPolar, XVar);
        pY = (QList <double> *) GetVariable(pPolar, YVar);

        for (int i=0;i<pPolar->m_Cl.size();i++)
        {
            ClCd.append(pPolar->m_Cl.at(i)/pPolar->m_Cd.at(i));
        }



        pCurve->SetSelected(-1);

        for (i=0; i<pPolar->m_Alpha.size(); i++)
        {
        if (XVar == 3 && YVar == 3) pCurve->AddPoint(ClCd.at(i),ClCd.at(i));
        else if (XVar == 3) pCurve->AddPoint(ClCd.at(i), pY->at(i));
        else if (YVar == 3) pCurve->AddPoint(pX->at(i), ClCd.at(i));
        else pCurve->AddPoint(pX->at(i),pY->at(i));
        }
}

void QBEM::FillTableRow(int row)
{
        //QString str, strong;
        QModelIndex ind;
        MainFrame *pMainFrame = (MainFrame*)s_pMainFrame;

        if (m_bAbsoluteBlade)
        {
            ind = m_pWingModel->index(row, 0, QModelIndex());
            m_pWingModel->setData(ind, m_pWing->m_TPos[row] * pMainFrame->m_mtoUnit);
        }
        else
        {
            ind = m_pWingModel->index(row, 0, QModelIndex());
            if (m_pWing->m_TRelPos[row] <= 0.0000000001) m_pWing->m_TRelPos[row] = 0;
            m_pWingModel->setData(ind, m_pWing->m_TRelPos[row] * pMainFrame->m_mtoUnit);
        }

        ind = m_pWingModel->index(row, 1, QModelIndex());
        m_pWingModel->setData(ind, m_pWing->m_TChord[row] * pMainFrame->m_mtoUnit);

        ind = m_pWingModel->index(row, 2, QModelIndex());
        m_pWingModel->setData(ind, m_pWing->m_TTwist[row]);

        ind = m_pWingModel->index(row, 3, QModelIndex());
        m_pWingModel->setData(ind, m_pWing->m_LFoil[row]);


        ind = m_pWingModel->index(row, 4, QModelIndex());

        if (m_pWing->m_Polar.length()>row)
        {
        m_pWingModel->setData(ind, m_pWing->m_Polar.at(row));
        }
        else
        {
        QString strong = "";
        m_pWingModel->setData(ind, strong);
        }


}

void QBEM::FillAdvancedTableRow(int row)
{
        //QString str, strong;
        QModelIndex ind;
        MainFrame *pMainFrame = (MainFrame*)s_pMainFrame;

        if (m_bAbsoluteBlade)
        {
            ind = m_pBladeAxisModel->index(row, 0, QModelIndex());
            m_pBladeAxisModel->setData(ind, m_pWing->m_TPos[row] * pMainFrame->m_mtoUnit);
        }
        else
        {
            ind = m_pBladeAxisModel->index(row, 0, QModelIndex());
            m_pBladeAxisModel->setData(ind, m_pWing->m_TRelPos[row] * pMainFrame->m_mtoUnit);
        }

        ind = m_pBladeAxisModel->index(row, 1, QModelIndex());
        m_pBladeAxisModel->setData(ind, m_pWing->m_TOffset[row] * pMainFrame->m_mtoUnit);

        ind = m_pBladeAxisModel->index(row, 2, QModelIndex());
        m_pBladeAxisModel->setData(ind, m_pWing->m_TDihedral[row]);

        ind = m_pBladeAxisModel->index(row, 3, QModelIndex());
        m_pBladeAxisModel->setData(ind, m_pWing->m_TFoilPAxisX[row]);

        ind = m_pBladeAxisModel->index(row, 4, QModelIndex());
        m_pBladeAxisModel->setData(ind, m_pWing->m_TFoilPAxisZ[row]);





}

void QBEM::FillRotorCurve(CCurve *pCurve, void *Data, int XVar, int YVar)
{
        QList <double> *pX;
        QList <double> *pY;
        Graph *pGraph = (Graph *) pCurve->m_pParentGraph;

        if (pGraph->m_Type == 0)
        {
        pX = (QList <double> *) GetRotorVariable(Data, XVar);
        pY = (QList <double> *) GetRotorVariable(Data, YVar);
        }
        else
        {
        pX = (QList <double> *) GetBladeVariable(Data, XVar);
        pY = (QList <double> *) GetBladeVariable(Data, YVar);
        }

        pCurve->SetSelected(-1);

        for (int i=0;i<pX->size();i++)
        {
            pCurve->AddPoint(pX->at(i),pY->at(i));
        }



}

void QBEM::FillPowerCurve(CCurve *pCurve, void *Data, int XVar, int YVar)
{
        QList <double> *pX;
        QList <double> *pY;
        Graph *pGraph = (Graph *) pCurve->m_pParentGraph;

        if(pGraph->m_Type == 0)
        {
        pX = (QList <double> *) GetTurbineRotorVariable(Data, XVar);
        pY = (QList <double> *) GetTurbineRotorVariable(Data, YVar);
        }
        else
        {
        pX = (QList <double> *) GetTurbineBladeVariable(Data, XVar);
        pY = (QList <double> *) GetTurbineBladeVariable(Data, YVar);
        }

        pCurve->SetSelected(-1);

        for (int i=0;i<pX->size();i++)
        {
            pCurve->AddPoint(pX->at(i),pY->at(i));
        }

}

CPolar* QBEM::Get360Polar(QString m_FoilName, QString PolarName)
{



        MainFrame *pMainFrame = (MainFrame *) s_pMainFrame;

        if (!PolarName.length())
        {
                //try to get the first from the Combobox
                if(!pMainFrame->m_pctrlBEM360Polars->count()) return NULL;        //nothing more to try
                PolarName = pMainFrame->m_pctrlBEM360Polars->itemText(0); //... and carry on
        }

        CPolar *pPolar;
        for (int i=0; i < s_poa360Polar->size() ; i++)
        {
                pPolar = (CPolar *) s_poa360Polar->at(i);
                if (pPolar->m_FoilName == m_FoilName && pPolar->m_PlrName == PolarName)
                {
                        return pPolar;

                }
        }
        return NULL;
}

CFoil* QBEM::GetFoil(QString strFoilName)
{
        //returns a pointer to the foil with the corresponding name
        // returns NULL if not found
        if(!strFoilName.length()) return NULL;
        CFoil* pFoil;
        for (int i=0; i < s_poaFoil->size(); i++)
        {
                pFoil = (CFoil*) s_poaFoil->at(i);
                if (pFoil->m_FoilName == strFoilName)
                {
                        return pFoil;
                }
        }

        return NULL;
}

QGraph* QBEM::GetGraph(QPoint &pt)
{
//	//returns a pointer to the graph in which the point pt lies
        if(m_iView==PolarView)
        {

                        if(m_360CLGraph.IsInDrawRect(pt)){return &m_360CLGraph;}
                        else if(m_360CDGraph.IsInDrawRect(pt)){return &m_360CDGraph;}
                        else return NULL;

        }
        if(m_iView==CharView)
        {         
                        if(m_CharGraph1.IsInDrawRect(pt)){return &m_CharGraph1;}
                        if(m_CharGraph2.IsInDrawRect(pt)){return &m_CharGraph2;}
                        if(m_CharGraph3.IsInDrawRect(pt)){return &m_CharGraph3;}
                        else return NULL;
        }
        if(m_iView==PowerView)
        {
                        if(m_PowerGraph1.IsInDrawRect(pt)){return &m_PowerGraph1;}
                        if(m_PowerGraph2.IsInDrawRect(pt)){return &m_PowerGraph2;}
                        if(m_PowerGraph3.IsInDrawRect(pt)){return &m_PowerGraph3;}
                        else return NULL;
        }




return NULL;
}

CPolar* QBEM::GetPolar(QString m_FoilName, QString PolarName)
{

        MainFrame *pMainFrame = (MainFrame *) s_pMainFrame;

        if (!PolarName.length())
        {
                //try to get the first from the Combobox
                if(!pMainFrame->m_pctrlBEMPolars->count()) return NULL;        //nothing more to try
                PolarName = pMainFrame->m_pctrlBEMPolars->itemText(0); //... and carry on
        }

        CPolar *pPolar;
        for (int i=0; i < s_poaPolar->size() ; i++)
        {
                pPolar = (CPolar *) s_poaPolar->at(i);
                if (pPolar->m_FoilName == m_FoilName &&  pPolar->m_PlrName == PolarName)
                {
                        return pPolar;
                }
        }
        return NULL;
}

BEMData* QBEM::GetRotorSimulation(QString WingName, QString BEMName)
{

    if (!WingName.length() || !BEMName.length()) return NULL;

    for (int i=0; i<s_poaBEMData.size(); i++)
    {
        if (s_poaBEMData.at(i)->m_WingName == WingName && s_poaBEMData.at(i)->m_BEMName == BEMName)
        {
            return s_poaBEMData.at(i);
        }
    }

    return NULL;
}

void * QBEM::GetRotorVariable(void *Data, int iVar)
{
        // returns a pointer to the variable array defined by its index iVar
        void * pVar;
        BEMData *pBEMData = (BEMData *) Data;

        switch (iVar){
                case 0:

                        pVar = &pBEMData->m_Lambda;
                        break;
                case 1:

                        pVar = &pBEMData->m_one_over_Lambda;
                        break;
                case 2:

                        pVar = &pBEMData->m_Cp;
                        break;
                case 3:

                        pVar = &pBEMData->m_Cp_prop;
                        break;

                case 4:

                        pVar = &pBEMData->m_Ct;
                        break;
                case 5:

                        pVar = &pBEMData->m_Ct_prop;
                        break;
                case 6:

                        pVar = &pBEMData->m_Kp;
                        break;
                case 7:

                        pVar = &pBEMData->m_Advance_Ratio;
                        break;
                case 8:

                        pVar = &pBEMData->m_Eta;
                        break;

                default:

                        pVar = &pBEMData->m_Lambda;
                        break;
        }
        return pVar;
}

void * QBEM::GetBladeVariable(void *Data, int iVar)
{
    // returns a pointer to the variable array defined by its index iVar
    void * pVar;
    BData *pBData = (BData *) Data;

    switch (iVar){

            case 0:

                    pVar = &pBData->m_a_axial;
                    break;
            case 1:

                    pVar = &pBData->m_pos;
                    break;
            case 2:

                    pVar = &pBData->m_a_radial;
                    break;
            case 3:

                    pVar = &pBData->m_lambda_local;
                    break;
            case 4:

                    pVar = &pBData->m_Cn;
                    break;
            case 5:

                    pVar = &pBData->m_Ct;
                    break;
            case 6:

                    pVar = &pBData->m_phi;
                    break;
            case 7:

                    pVar = &pBData->m_alpha;
                    break;
            case 8:

                    pVar = &pBData->m_theta;
                    break;
            case 9:

                    pVar = &pBData->m_c_local;
                    break;
            case 10:

                    pVar = &pBData->m_CL;
                    break;
            case 11:

                    pVar = &pBData->m_CD;
                    break;
            case 12:

                    pVar = &pBData->m_LD;
                    break;
            case 13:

                    pVar = &pBData->m_F;
                    break;
            case 14:

                    pVar = &pBData->m_Iterations;
                    break;
            case 15:

                    pVar = &pBData->m_Fa_axial;
                    break;
            case 16:

                    pVar = &pBData->m_Fa_radial;
                    break;
            default:

                    pVar = &pBData->m_pos;
                    break;
    }
    return pVar;
}

BData* QBEM::GetBladeData(QString Lambda)
{

    if (!m_pBEMData->m_BData.size()) return NULL;

    for (int i=0; i<m_pBEMData->m_BData.size(); i++)
    {
        if (m_pBEMData->m_BData.at(i)->lambdaglobal==Lambda)
        {
            return m_pBEMData->m_BData.at(i);
        }
    }

    return NULL;
}

TData * QBEM::GetTurbine(QString m_TurbineName)
{
    for (int i=0;i<s_poaTData.size();i++)
    {
        if (s_poaTData.at(i)->m_TurbineName == m_TurbineName) return s_poaTData.at(i);
    }
    return NULL;
}

BData* QBEM::GetTurbineBladeData(QString Windspeed)
{

    if (!m_pTBEMData->m_BData.size()) return NULL;

    for (int i=0; i<m_pTBEMData->m_BData.size(); i++)
    {
        if (m_pTBEMData->m_BData.at(i)->windspeedStr==Windspeed)
        {
            return m_pTBEMData->m_BData.at(i);
        }
    }

    return NULL;
}


TBEMData* QBEM::GetTurbineSimulation(QString TurbineName, QString SimName)
{

    if (!TurbineName.length() || !SimName.length()) return NULL;

    for (int i=0; i<s_poaTBEMData.size(); i++)
    {
        if (s_poaTBEMData.at(i)->m_TurbineName == TurbineName && s_poaTBEMData.at(i)->m_SimName == SimName)
        {
            return s_poaTBEMData.at(i);
        }
    }

    return NULL;
}

void * QBEM::GetTurbineRotorVariable(void *Data, int iVar)
{
        // returns a pointer to the variable array defined by its index iVar
        void * pVar;
        TBEMData *pTBEMData = (TBEMData *) Data;

        switch (iVar){
                case 0:

                        pVar = &pTBEMData->m_P;
                        break;
                case 1:

                        pVar = &pTBEMData->m_S;
                        break;
                case 2:

                        pVar = &pTBEMData->m_V;
                        break;
                case 3:

                        pVar = &pTBEMData->m_Torque;
                        break;
                case 4:

                        pVar = &pTBEMData->m_Lambda;
                        break;
                case 5:

                        pVar = &pTBEMData->m_Omega;
                        break;
                case 6:

                        pVar = &pTBEMData->m_Cp;
                        break;
                case 7:

                        pVar = &pTBEMData->m_Cp_prop;
                        break;
                case 8:

                        pVar = &pTBEMData->m_Ct;
                        break;
                case 9:

                        pVar = &pTBEMData->m_Ct_prop;
                        break;
                case 10:

                        pVar = &pTBEMData->m_Pitch;
                        break;
                case 11:

                        pVar = &pTBEMData->m_Weibull;
                        break;
                case 12:

                        pVar = &pTBEMData->m_WeibullV3;
                        break;
                case 13:

                        pVar = &pTBEMData->m_Bending;
                        break;
                case 14:

                        pVar = &pTBEMData->m_Cp_loss;
                        break;
                case 15:

                        pVar = &pTBEMData->m_Kp;
                        break;
                case 16:

                        pVar = &pTBEMData->m_one_over_lambda;
                        break;
                case 17:

                        pVar = &pTBEMData->m_Advance_Ratio;
                        break;
                case 18:

                        pVar = &pTBEMData->m_Eta;
                        break;

                default:

                        pVar = &pTBEMData->m_Lambda;
                        break;
        }
        return pVar;
}

void * QBEM::GetTurbineBladeVariable(void *Data, int iVar)
{
    void * pVar;
    BData *pBData = (BData *) Data;



    switch (iVar){

            case 0:

                    pVar = &pBData->m_Cn;
                    break;
            case 1:

                    pVar = &pBData->m_Ct;
                    break;
            case 2:

                    pVar = &pBData->m_phi;
                    break;
            case 3:

                    pVar = &pBData->m_alpha;
                    break;
            case 4:

                    pVar = &pBData->m_theta;
                    break;
            case 5:

                    pVar = &pBData->m_c_local;
                    break;
            case 6:

                    pVar = &pBData->m_CL;
                    break;
            case 7:

                    pVar = &pBData->m_CD;
                    break;
            case 8:

                    pVar = &pBData->m_LD;
                    break;
            case 9:

                    pVar = &pBData->m_F;
                    break;
            case 10:

                    pVar = &pBData->m_a_axial;
                    break;
            case 11:

                    pVar = &pBData->m_a_radial;
                    break;
            case 12:

                    pVar = &pBData->m_pos;
                    break;
            case 13:

                    pVar = &pBData->m_lambda_local;
                    break;
            case 14:

                    pVar = &pBData->m_Reynolds;
                    break;
            case 15:

                    pVar = &pBData->m_DeltaReynolds;
                    break;
            case 16:

                    pVar = &pBData->m_Roughness;
                    break;
            case 17:

                    pVar = &pBData->m_Windspeed;
                    break;
            case 18:

                    pVar = &pBData->m_p_tangential;
                    break;
            case 19:

                    pVar = &pBData->m_p_normal;
                    break;
            case 20:

                    pVar = &pBData->m_Iterations;
                    break;
            case 21:

                    pVar = &pBData->m_Mach;
                    break;
            case 22:

                    pVar = &pBData->m_circ;
                    break;
            case 23:

                    pVar = &pBData->m_Fa_axial;
                    break;
            case 24:

                    pVar = &pBData->m_Fa_radial;
                    break;
            default:

                    pVar = &pBData->m_pos;
                    break;
    }
    return pVar;
}


void * QBEM::GetVariable(CPolar *pPolar, int iVar)
{
        // returns a pointer to the variable array defined by its index iVar
        void * pVar;
        switch (iVar){
                case 0:
                        pVar = &pPolar->m_Alpha;
                        break;
                case 1:
                        pVar = &pPolar->m_Cl;
                        break;
                case 2:
                        pVar = &pPolar->m_Cd;
                        break;
                case 3:
                        pVar = &pPolar->m_Cd;
                        break;

                default:
                        pVar = &pPolar->m_Alpha;
                        break;
        }
        return pVar;
}

CBlade * QBEM::GetWing(QString WingName)
{
        int i;
        CBlade* pWing;
        for (i=0; i<s_poaBEMWings->size(); i++)
        {
                pWing = (CBlade*)s_poaBEMWings->at(i);
                if (pWing->m_WingName == WingName) return pWing;
        }
        return NULL;
}

void QBEM::GLCallViewLists()
{
        glDisable(GL_LIGHTING);
        glDisable(GL_LIGHT0);




        if(m_bglLight)
        {
                glEnable(GL_LIGHTING);
                glEnable(GL_LIGHT0);
        }
        else
        {
                glDisable(GL_LIGHTING);
                glDisable(GL_LIGHT0);
        }

        if(m_bSurfaces)
        {
                if(m_pWing)  glCallList(WINGSURFACES);


        }

        if(m_bOutline)
        {
                if(m_pWing)  glCallList(WINGOUTLINE);

        }

                        if(m_iSection>=0)
                        {
                               glCallList(SECTIONHIGHLIGHT);
                       }



        glDisable(GL_LIGHTING);
        glDisable(GL_LIGHT0);




}



void QBEM::GLCreateGeom(CBlade *pWing, int List)
{
        if(!pWing) return;

        static int j, l, style, width;
        static CVector Pt, PtNormal, A, B, C, D, N, BD, AC, LATB, TALB;
        static QColor color;
        static CFoil * pFoilA, *pFoilB;

        static double x, xDistrib[SIDEPOINTS];
        double xx;
        double param = 50;// increase to refine L.E. and T.E.
        for(int i=0; i<SIDEPOINTS; i++)
        {
                xx = (double)i/(double)(SIDEPOINTS-1);
                xDistrib[i] = (asinh(param*(xx-0.5))/asinh(param/2.)+1.)/2.;
        }

        N.Set(0.0, 0.0, 0.0);


        glNewList(List,GL_COMPILE);
        {
                glLineWidth(1.0);

                color = pWing->m_WingColor;
                style = 0;
                width = 0;

//              glColor3d(color.redF(),color.greenF(),color.blueF());


                glColor4d(color.redF(),color.greenF(),color.blueF(),color.alphaF());
                glEnable (GL_BLEND);
                glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                glEnable(GL_POLYGON_OFFSET_FILL);
                glPolygonOffset(1.0, 1.0);
                glEnable(GL_DEPTH_TEST);

//                top surface

                if (!m_bAdvancedEdit && m_pctrlSurfaces->isChecked())
                {
                    for (j=0; j<pWing->m_NSurfaces; j++)
                    {
                            glBegin(GL_QUAD_STRIP);
                            {
                                    for (l=0; l<=100; l++)
                                    {

                                            x = (double)l/100.0;

                                            pWing->m_Surface[j].GetPoint(x,x,0.0,Pt, PtNormal,1);
                                            glNormal3d(PtNormal.x, PtNormal.y, PtNormal.z);
                                            glVertex3d(Pt.x, Pt.y, Pt.z);

                                            pWing->m_Surface[j].GetPoint(x,x,1.0,Pt, PtNormal,1);
                                            glVertex3d(Pt.x, Pt.y, Pt.z);

                                    }
                            }
                            glEnd();
                    }
                }

//                bottom surface
                        if (m_pctrlSurfaces->isChecked())
                        {
                                for (j=0; j<pWing->m_NSurfaces; j++)
                                {
                                        glBegin(GL_QUAD_STRIP);
                                        {
                                                for (l=0; l<=100; l++)
                                                {
                                                    x = (double)l/100.0;

                                                    pWing->m_Surface[j].GetPoint(x,x,0.0,Pt, PtNormal,-1);
                                                    glNormal3d(PtNormal.x, PtNormal.y, PtNormal.z);
                                                    glVertex3d(Pt.x, Pt.y, Pt.z);

                                                    pWing->m_Surface[j].GetPoint(x,x,1.0,Pt, PtNormal,-1);
                                                    glVertex3d(Pt.x, Pt.y, Pt.z);
                                                }
                                        }
                                        glEnd();

                                }

                        }






//                for (j=0; j<pWing->m_NSurfaces; j++)
//                {
//                        glBegin(GL_QUAD_STRIP);
//                        {
//                                for (l=0; l<=100; l++)
//                                {
//                                    x = (double)l/100.0;

//                                    pWing->m_Surface[j].GetPoint(x,x,0.0,Pt, PtNormal,-1);
//                                    glNormal3d(PtNormal.x, PtNormal.y, PtNormal.z);
//                                    glVertex3d(Pt.x, Pt.y, Pt.z);

//                                    pWing->m_Surface[j].GetPoint(x,x,1.0,Pt, PtNormal,-1);
//                                    glVertex3d(Pt.x, Pt.y, Pt.z);
//                                }
//                        }
//                        glEnd();

//                }


                for (j=0; j<pWing->m_NSurfaces; j++)
                {                  
//                    glEnable (GL_BLEND);
//                    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

//left tip surface
                        if (j==0 && !m_bAdvancedEdit && m_pctrlSurfaces->isChecked())
                        {

                            glBegin(GL_QUAD_STRIP);
                            {
                                    pWing->m_Surface[j].GetPanel(0, 0, BOTSURFACE);
                                    C. Copy(pWing->m_Surface[0].LA);
                                    D. Copy(pWing->m_Surface[0].TA);
                                    pWing->m_Surface[j].GetPanel(0, 0, TOPSURFACE);
                                    A. Copy(pWing->m_Surface[0].TA);
                                    B. Copy(pWing->m_Surface[0].LA);

                                    BD = D-B;
                                    AC = C-A;
                                    N  = AC*BD;
                                    N.Normalize();
                                    glNormal3d( N.x, N.y, N.z);

                                    for (l=0; l<SIDEPOINTS; l++)
                                    {
                                            x = xDistrib[l];
                                            pWing->m_Surface[j].GetPoint(x,x,0.0,Pt, PtNormal,1);

                                            glVertex3d(Pt.x, Pt.y, Pt.z);

                                            pWing->m_Surface[j].GetPoint(x,x,0.0,Pt, PtNormal,-1);
                                            glVertex3d(Pt.x, Pt.y, Pt.z);
                                    }
                            }
                            glEnd();

                        }

                        // right tip surface
                        if (j==pWing->m_NSurfaces-1 && !m_bAdvancedEdit && m_pctrlSurfaces->isChecked())
                        {
                                      glBegin(GL_QUAD_STRIP);
                                      {
                                              pWing->m_Surface[j].GetPanel(pWing->m_Surface[j].m_NYPanels-1,0, TOPSURFACE);
                                              A. Copy(pWing->m_Surface[0].TB);
                                              B. Copy(pWing->m_Surface[0].LB);
                                              pWing->m_Surface[j].GetPanel(pWing->m_Surface[j].m_NYPanels-1,0, BOTSURFACE);
                                              C. Copy(pWing->m_Surface[0].LB);
                                              D. Copy(pWing->m_Surface[0].TB);

                                              BD = D-B;
                                              AC = C-A;
                                              N  = BD * AC;
                                              N.Normalize();
                                              glNormal3d( N.x,  N.y,  N.z);

                                              for (l=0; l<SIDEPOINTS; l++)
                                              {
                                                      x = xDistrib[l];
                                                      pWing->m_Surface[j].GetPoint(x,x,1.0,Pt, PtNormal,1);

                                                      glVertex3d(Pt.x, Pt.y, Pt.z);
                                                      pWing->m_Surface[j].GetPoint(x,x,1.0,Pt, PtNormal,-1);
                                                      glVertex3d(Pt.x, Pt.y, Pt.z);
                                              }
                                      }
                                      glEnd();
                        }

                        if (m_bAdvancedEdit || m_pctrlAirfoils->isChecked())
                        {
                                      glColor3d(m_OutlineColor.redF(),m_OutlineColor.greenF(),m_OutlineColor.blueF());
                                      glBegin(GL_QUAD_STRIP);
                                      {
                                              pWing->m_Surface[j].GetPanel(pWing->m_Surface[j].m_NYPanels-1,0, TOPSURFACE);
                                              A. Copy(pWing->m_Surface[0].TB);
                                              B. Copy(pWing->m_Surface[0].LB);
                                              pWing->m_Surface[j].GetPanel(pWing->m_Surface[j].m_NYPanels-1,0, BOTSURFACE);
                                              C. Copy(pWing->m_Surface[0].LB);
                                              D. Copy(pWing->m_Surface[0].TB);

                                              BD = D-B;
                                              AC = C-A;
                                              N  = BD * AC;
                                              N.Normalize();
                                              glNormal3d( N.x,  N.y,  N.z);

                                              for (l=0; l<SIDEPOINTS; l++)
                                              {
                                                      x = xDistrib[l];
                                                      pWing->m_Surface[j].GetPoint(x,x,1.0,Pt, PtNormal,1);

                                                      glVertex3d(Pt.x, Pt.y, Pt.z);
                                                      pWing->m_Surface[j].GetPoint(x,x,1.0,Pt, PtNormal,-1);
                                                      glVertex3d(Pt.x, Pt.y, Pt.z);
                                              }
                                      }
                                      glEnd();

                                      if (j==0)
                                      {
                                          glBegin(GL_QUAD_STRIP);
                                          {
                                                  pWing->m_Surface[j].GetPanel(0, 0, BOTSURFACE);
                                                  C. Copy(pWing->m_Surface[0].LA);
                                                  D. Copy(pWing->m_Surface[0].TA);
                                                  pWing->m_Surface[j].GetPanel(0, 0, TOPSURFACE);
                                                  A. Copy(pWing->m_Surface[0].TA);
                                                  B. Copy(pWing->m_Surface[0].LA);

                                                  BD = D-B;
                                                  AC = C-A;
                                                  N  = AC*BD;
                                                  N.Normalize();
                                                  glNormal3d( N.x, N.y, N.z);

                                                  for (l=0; l<SIDEPOINTS; l++)
                                                  {
                                                          x = xDistrib[l];
                                                          pWing->m_Surface[j].GetPoint(x,x,0.0,Pt, PtNormal,1);

                                                          glVertex3d(Pt.x, Pt.y, Pt.z);

                                                          pWing->m_Surface[j].GetPoint(x,x,0.0,Pt, PtNormal,-1);
                                                          glVertex3d(Pt.x, Pt.y, Pt.z);
                                                  }
                                          }
                                          glEnd();
                                      }
                        }
                }
                glDisable(GL_POLYGON_OFFSET_FILL);
                glDisable (GL_LINE_STIPPLE);
        }
        glEndList();

        //OUTLINE
        glNewList(WINGOUTLINE,GL_COMPILE);
        {

                glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
                glEnable (GL_LINE_STIPPLE);
                glLineWidth((GLfloat)m_OutlineWidth);

                color = m_OutlineColor;
                style = m_OutlineStyle;
                width = m_OutlineWidth;

                if     (style == 1) 	glLineStipple (1, 0x1111);
                else if(style == 2) 	glLineStipple (1, 0x0F0F);
                else if(style == 3) 	glLineStipple (1, 0x1C47);
                else					glLineStipple (1, 0xFFFF);

                glColor3d(color.redF(),color.greenF(),color.blueF());
                glLineWidth((GLfloat)width);

                if (m_pctrlOutline->isChecked())
                {
                //TOP outline
                for (j=0; j<pWing->m_NSurfaces; j++)
                {
                        glBegin(GL_LINE_STRIP);
                        {
                                for (l=0; l<=100; l++)
                                {
                                        x = (double)l/100.0;
                                        pWing->m_Surface[j].GetPoint(x,x,0.0,Pt, PtNormal,1);
                                        glVertex3d(Pt.x, Pt.y, Pt.z);
                                }
                        }
                        glEnd();

                        glBegin(GL_LINE_STRIP);
                        {
                                for (l=0; l<=100; l++)
                                {
                                        x = (double)l/100.0;
                                        pWing->m_Surface[j].GetPoint(x,x,1.0,Pt, PtNormal,1);
                                        glVertex3d(Pt.x, Pt.y, Pt.z);
                                }
                        }
                        glEnd();
                }

                //BOTTOM outline
                for (j=0; j<pWing->m_NSurfaces; j++)
                {
                        glBegin(GL_LINE_STRIP);
                        {
                                for (l=0; l<=100; l++)
                                {
                                        x = (double)l/100.0;
                                        pWing->m_Surface[j].GetPoint(x,x,0.0,Pt, PtNormal,-1);
                                        glVertex3d(Pt.x, Pt.y, Pt.z);
                                }
                        }
                        glEnd();

                        glBegin(GL_LINE_STRIP);
                        {
                                for (l=0; l<=100; l++)
                                {
                                        x = (double)l/100.0;
                                        pWing->m_Surface[j].GetPoint(x,x,1.0,Pt, PtNormal,-1);
                                        glVertex3d(Pt.x, Pt.y, Pt.z);
                                }
                        }
                        glEnd();

                }



                glLineWidth((GLfloat)1);


                //WingContour
                //Leading edge outline
                for (j=0; j<pWing->m_NSurfaces; j++)
                {
                        glBegin(GL_LINES);
                        {
                                pWing->m_Surface[j].GetPanel(0,pWing->m_Surface[j].m_NXPanels-1, MIDSURFACE);
                                glVertex3d(pWing->m_Surface[j].LA.x,
                                                   pWing->m_Surface[j].LA.y,
                                                   pWing->m_Surface[j].LA.z);
                                pWing->m_Surface[j].GetPanel( pWing->m_Surface[j].m_NYPanels-1,pWing->m_Surface[j].m_NXPanels-1, MIDSURFACE);
                                glVertex3d(pWing->m_Surface[j].LB.x,
                                                   pWing->m_Surface[j].LB.y,
                                                   pWing->m_Surface[j].LB.z);
                        }
                        glEnd();
                }
                //Trailing edge outline
                for (j=0; j<pWing->m_NSurfaces; j++)
                {
                        glBegin(GL_LINES);
                        {
                                pWing->m_Surface[j].GetPanel(0,0, MIDSURFACE);
                                glVertex3d(pWing->m_Surface[j].TA.x,
                                                   pWing->m_Surface[j].TA.y,
                                                   pWing->m_Surface[j].TA.z);
                                pWing->m_Surface[j].GetPanel( pWing->m_Surface[j].m_NYPanels-1, 0, MIDSURFACE);
                                glVertex3d(pWing->m_Surface[j].TB.x,
                                                   pWing->m_Surface[j].TB.y,
                                                   pWing->m_Surface[j].TB.z);
                        }
                        glEnd();
                }
                //flap outline....
                for (j=0; j<pWing->m_NSurfaces; j++)
                {
                        pFoilA = pWing->m_Surface[j].m_pFoilA;
                        pFoilB = pWing->m_Surface[j].m_pFoilB;
                        if(pFoilA && pFoilB && pFoilA->m_bTEFlap && pFoilB->m_bTEFlap)
                        {
                                glBegin(GL_LINES);
                                {
                                        if(pFoilA->m_bTEFlap)
                                                pWing->m_Surface[j].GetPoint(pWing->m_Surface[j].m_pFoilA->m_TEXHinge/100.0,
                                                                                                         pWing->m_Surface[j].m_pFoilA->m_TEXHinge/100.0,
                                                                                                         0.0, Pt, 1);
                                        else 	pWing->m_Surface[j].GetPoint(1.0, 1.0, 0.0, Pt, 1);
                                        glVertex3d(Pt.x, Pt.y, Pt.z);

                                        if(pFoilB->m_bTEFlap)
                                                pWing->m_Surface[j].GetPoint(pWing->m_Surface[j].m_pFoilB->m_TEXHinge/100.0,
                                                                                                         pWing->m_Surface[j].m_pFoilB->m_TEXHinge/100.0,
                                                                                                         1.0, Pt, 1);
                                        else 	pWing->m_Surface[j].GetPoint(1.0, 1.0, 1.0, Pt, 1);
                                        glVertex3d(Pt.x, Pt.y, Pt.z);
                                }
                                glEnd();
                                glBegin(GL_LINES);
                                {
                                        if(pFoilA->m_bTEFlap)
                                                pWing->m_Surface[j].GetPoint(pWing->m_Surface[j].m_pFoilA->m_TEXHinge/100.0,
                                                                                                         pWing->m_Surface[j].m_pFoilA->m_TEXHinge/100.0,
                                                                                                         0.0, Pt, -1);
                                        else 	pWing->m_Surface[j].GetPoint(1.0, 1.0, 0.0, Pt, -1);
                                        glVertex3d(Pt.x, Pt.y, Pt.z);

                                        if(pFoilB->m_bTEFlap)
                                                pWing->m_Surface[j].GetPoint(pWing->m_Surface[j].m_pFoilB->m_TEXHinge/100.0,
                                                                                                         pWing->m_Surface[j].m_pFoilB->m_TEXHinge/100.0,
                                                                                                         1.0, Pt, -1);
                                        else 	pWing->m_Surface[j].GetPoint(1.0, 1.0, 1.0, Pt, -1);
                                        glVertex3d(Pt.x, Pt.y, Pt.z);
                                }
                                glEnd();
                        }
                }
                for (j=0; j<pWing->m_NSurfaces; j++)
                {
                        pFoilA = pWing->m_Surface[j].m_pFoilA;
                        pFoilB = pWing->m_Surface[j].m_pFoilB;
                        if(pFoilA && pFoilB && pFoilA->m_bLEFlap && pFoilB->m_bLEFlap)
                        {
                                glBegin(GL_LINES);
                                {
                                        if(pFoilA->m_bLEFlap)
                                                pWing->m_Surface[j].GetPoint(pWing->m_Surface[j].m_pFoilA->m_LEXHinge/100.0,
                                                                                                         pWing->m_Surface[j].m_pFoilA->m_LEXHinge/100.0,
                                                                                                         0.0, Pt, 1);
                                        else 	pWing->m_Surface[j].GetPoint(1.0, 1.0, 0.0, Pt, 1);
                                        glVertex3d(Pt.x, Pt.y, Pt.z);

                                        if(pFoilB->m_bLEFlap)
                                                pWing->m_Surface[j].GetPoint(pWing->m_Surface[j].m_pFoilB->m_LEXHinge/100.0,
                                                                                                         pWing->m_Surface[j].m_pFoilB->m_LEXHinge/100.0,
                                                                                                         1.0, Pt, 1);
                                        else 	pWing->m_Surface[j].GetPoint(1.0, 1.0, 1.0, Pt, 1);
                                        glVertex3d(Pt.x, Pt.y, Pt.z);
                                }
                                glEnd();
                                glBegin(GL_LINES);
                                {
                                        if(pFoilA->m_bLEFlap)
                                                pWing->m_Surface[j].GetPoint(pWing->m_Surface[j].m_pFoilA->m_LEXHinge/100.0,
                                                                                                         pWing->m_Surface[j].m_pFoilA->m_LEXHinge/100.0,
                                                                                                         0.0, Pt, -1);
                                        else 	pWing->m_Surface[j].GetPoint(1.0, 1.0, 0.0, Pt, -1);
                                        glVertex3d(Pt.x, Pt.y, Pt.z);

                                        if(pFoilB->m_bLEFlap)
                                                pWing->m_Surface[j].GetPoint(pWing->m_Surface[j].m_pFoilB->m_LEXHinge/100.0,
                                                                                                         pWing->m_Surface[j].m_pFoilB->m_LEXHinge/100.0,
                                                                                                         1.0, Pt, -1);
                                        else 	pWing->m_Surface[j].GetPoint(1.0, 1.0, 1.0, Pt, -1);
                                        glVertex3d(Pt.x, Pt.y, Pt.z);
                                }
                                glEnd();
                        }
                }
                }
                if (m_bAdvancedEdit)
                {
                MainFrame * pMainFrame =(MainFrame*)s_pMainFrame;

                glLineWidth((GLfloat)5);
                glColor3d(pMainFrame->m_TextColor.redF(),pMainFrame->m_TextColor.greenF(),pMainFrame->m_TextColor.blueF());

                glBegin(GL_LINE_STRIP);
                {
                    for (j=0; j<=pWing->m_NPanel; j++)
                    {
                        Pt=CVector(pWing->m_TPAxisX[j],pWing->m_TPAxisY[j],pWing->m_TPAxisZ[j]);
                        glVertex3d(Pt.x, Pt.y, Pt.z);
                    }
                }
                glEnd();
                }
                glDisable (GL_LINE_STIPPLE);
        }
        glEndList();

}


void QBEM::GLCreateTurbine(int List)
{

        CBlade *pWing;
        static int j, l, style, width;
        static CVector Pt, PtNormal, A, B, C, D, N, BD, AC, LATB, TALB;
        static QColor color;
        static CFoil * pFoilA, *pFoilB;

        static double x, xDistrib[SIDEPOINTS];
        double xx;
        double param = 50;// increase to refine L.E. and T.E.
        for(int i=0; i<SIDEPOINTS; i++)
        {
                xx = (double)i/(double)(SIDEPOINTS-1);
                xDistrib[i] = (asinh(param*(xx-0.5))/asinh(param/2.)+1.)/2.;
        }

        N.Set(0.0, 0.0, 0.0);



        glNewList(List,GL_COMPILE);
        {
            for (int jj=0;jj<m_pWing->blades;jj++)
            {
                pWing = s_poaTurbineBlades[jj];

                glLineWidth(1.0);

                color = pWing->m_WingColor;
                style = 0;
                width = 0;

//              glColor3d(color.redF(),color.greenF(),color.blueF());


                glColor4d(color.redF(),color.greenF(),color.blueF(),color.alphaF());
                glEnable (GL_BLEND);
                glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                glEnable(GL_POLYGON_OFFSET_FILL);
                glPolygonOffset(1.0, 1.0);
                glEnable(GL_DEPTH_TEST);

//                top surface

                if (!m_bAdvancedEdit && m_pctrlSurfaces->isChecked())
                {
                    for (j=0; j<pWing->m_NSurfaces; j++)
                    {
                            glBegin(GL_QUAD_STRIP);
                            {
                                    for (l=0; l<=100; l++)
                                    {

                                            x = (double)l/100.0;

                                            pWing->m_Surface[j].GetPoint(x,x,0.0,Pt, PtNormal,1);
                                            glNormal3d(PtNormal.x, PtNormal.y, PtNormal.z);
                                            glVertex3d(Pt.x, Pt.y, Pt.z);

                                            pWing->m_Surface[j].GetPoint(x,x,1.0,Pt, PtNormal,1);
                                            glVertex3d(Pt.x, Pt.y, Pt.z);

                                    }
                            }
                            glEnd();
                    }
                }

//                bottom surface
                        if (m_pctrlSurfaces->isChecked())
                        {
                                for (j=0; j<pWing->m_NSurfaces; j++)
                                {
                                        glBegin(GL_QUAD_STRIP);
                                        {
                                                for (l=0; l<=100; l++)
                                                {
                                                    x = (double)l/100.0;

                                                    pWing->m_Surface[j].GetPoint(x,x,0.0,Pt, PtNormal,-1);
                                                    glNormal3d(PtNormal.x, PtNormal.y, PtNormal.z);
                                                    glVertex3d(Pt.x, Pt.y, Pt.z);

                                                    pWing->m_Surface[j].GetPoint(x,x,1.0,Pt, PtNormal,-1);
                                                    glVertex3d(Pt.x, Pt.y, Pt.z);
                                                }
                                        }
                                        glEnd();

                                }

                        }






//                for (j=0; j<pWing->m_NSurfaces; j++)
//                {
//                        glBegin(GL_QUAD_STRIP);
//                        {
//                                for (l=0; l<=100; l++)
//                                {
//                                    x = (double)l/100.0;

//                                    pWing->m_Surface[j].GetPoint(x,x,0.0,Pt, PtNormal,-1);
//                                    glNormal3d(PtNormal.x, PtNormal.y, PtNormal.z);
//                                    glVertex3d(Pt.x, Pt.y, Pt.z);

//                                    pWing->m_Surface[j].GetPoint(x,x,1.0,Pt, PtNormal,-1);
//                                    glVertex3d(Pt.x, Pt.y, Pt.z);
//                                }
//                        }
//                        glEnd();

//                }


                for (j=0; j<pWing->m_NSurfaces; j++)
                {
//                    glEnable (GL_BLEND);
//                    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

//left tip surface
                        if (j==0 && !m_bAdvancedEdit && m_pctrlSurfaces->isChecked())
                        {

                            glBegin(GL_QUAD_STRIP);
                            {
                                    pWing->m_Surface[j].GetPanel(0, 0, BOTSURFACE);
                                    C. Copy(pWing->m_Surface[0].LA);
                                    D. Copy(pWing->m_Surface[0].TA);
                                    pWing->m_Surface[j].GetPanel(0, 0, TOPSURFACE);
                                    A. Copy(pWing->m_Surface[0].TA);
                                    B. Copy(pWing->m_Surface[0].LA);

                                    BD = D-B;
                                    AC = C-A;
                                    N  = AC*BD;
                                    N.Normalize();
                                    glNormal3d( N.x, N.y, N.z);

                                    for (l=0; l<SIDEPOINTS; l++)
                                    {
                                            x = xDistrib[l];
                                            pWing->m_Surface[j].GetPoint(x,x,0.0,Pt, PtNormal,1);

                                            glVertex3d(Pt.x, Pt.y, Pt.z);

                                            pWing->m_Surface[j].GetPoint(x,x,0.0,Pt, PtNormal,-1);
                                            glVertex3d(Pt.x, Pt.y, Pt.z);
                                    }
                            }
                            glEnd();

                        }

                        // right tip surface
                        if (j==pWing->m_NSurfaces-1 && !m_bAdvancedEdit && m_pctrlSurfaces->isChecked())
                        {
                                      glBegin(GL_QUAD_STRIP);
                                      {
                                              pWing->m_Surface[j].GetPanel(pWing->m_Surface[j].m_NYPanels-1,0, TOPSURFACE);
                                              A. Copy(pWing->m_Surface[0].TB);
                                              B. Copy(pWing->m_Surface[0].LB);
                                              pWing->m_Surface[j].GetPanel(pWing->m_Surface[j].m_NYPanels-1,0, BOTSURFACE);
                                              C. Copy(pWing->m_Surface[0].LB);
                                              D. Copy(pWing->m_Surface[0].TB);

                                              BD = D-B;
                                              AC = C-A;
                                              N  = BD * AC;
                                              N.Normalize();
                                              glNormal3d( N.x,  N.y,  N.z);

                                              for (l=0; l<SIDEPOINTS; l++)
                                              {
                                                      x = xDistrib[l];
                                                      pWing->m_Surface[j].GetPoint(x,x,1.0,Pt, PtNormal,1);

                                                      glVertex3d(Pt.x, Pt.y, Pt.z);
                                                      pWing->m_Surface[j].GetPoint(x,x,1.0,Pt, PtNormal,-1);
                                                      glVertex3d(Pt.x, Pt.y, Pt.z);
                                              }
                                      }
                                      glEnd();
                        }

                        if (m_bAdvancedEdit || m_pctrlAirfoils->isChecked())
                        {
                                      glColor3d(m_OutlineColor.redF(),m_OutlineColor.greenF(),m_OutlineColor.blueF());
                                      glBegin(GL_QUAD_STRIP);
                                      {
                                              pWing->m_Surface[j].GetPanel(pWing->m_Surface[j].m_NYPanels-1,0, TOPSURFACE);
                                              A. Copy(pWing->m_Surface[0].TB);
                                              B. Copy(pWing->m_Surface[0].LB);
                                              pWing->m_Surface[j].GetPanel(pWing->m_Surface[j].m_NYPanels-1,0, BOTSURFACE);
                                              C. Copy(pWing->m_Surface[0].LB);
                                              D. Copy(pWing->m_Surface[0].TB);

                                              BD = D-B;
                                              AC = C-A;
                                              N  = BD * AC;
                                              N.Normalize();
                                              glNormal3d( N.x,  N.y,  N.z);

                                              for (l=0; l<SIDEPOINTS; l++)
                                              {
                                                      x = xDistrib[l];
                                                      pWing->m_Surface[j].GetPoint(x,x,1.0,Pt, PtNormal,1);

                                                      glVertex3d(Pt.x, Pt.y, Pt.z);
                                                      pWing->m_Surface[j].GetPoint(x,x,1.0,Pt, PtNormal,-1);
                                                      glVertex3d(Pt.x, Pt.y, Pt.z);
                                              }
                                      }
                                      glEnd();

                                      if (j==0)
                                      {
                                          glBegin(GL_QUAD_STRIP);
                                          {
                                                  pWing->m_Surface[j].GetPanel(0, 0, BOTSURFACE);
                                                  C. Copy(pWing->m_Surface[0].LA);
                                                  D. Copy(pWing->m_Surface[0].TA);
                                                  pWing->m_Surface[j].GetPanel(0, 0, TOPSURFACE);
                                                  A. Copy(pWing->m_Surface[0].TA);
                                                  B. Copy(pWing->m_Surface[0].LA);

                                                  BD = D-B;
                                                  AC = C-A;
                                                  N  = AC*BD;
                                                  N.Normalize();
                                                  glNormal3d( N.x, N.y, N.z);

                                                  for (l=0; l<SIDEPOINTS; l++)
                                                  {
                                                          x = xDistrib[l];
                                                          pWing->m_Surface[j].GetPoint(x,x,0.0,Pt, PtNormal,1);

                                                          glVertex3d(Pt.x, Pt.y, Pt.z);

                                                          pWing->m_Surface[j].GetPoint(x,x,0.0,Pt, PtNormal,-1);
                                                          glVertex3d(Pt.x, Pt.y, Pt.z);
                                                  }
                                          }
                                          glEnd();
                                      }
                        }
                }
                glDisable(GL_POLYGON_OFFSET_FILL);
                glDisable (GL_LINE_STIPPLE);
        }
        }
        glEndList();

        //OUTLINE
        glNewList(WINGOUTLINE,GL_COMPILE);
        {
            for (int jj=0;jj<m_pWing->blades;jj++)
            {
                pWing = s_poaTurbineBlades[jj];

                glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
                glEnable (GL_LINE_STIPPLE);
                glLineWidth((GLfloat)m_OutlineWidth);

                color = m_OutlineColor;
                style = m_OutlineStyle;
                width = m_OutlineWidth;

                if     (style == 1) 	glLineStipple (1, 0x1111);
                else if(style == 2) 	glLineStipple (1, 0x0F0F);
                else if(style == 3) 	glLineStipple (1, 0x1C47);
                else					glLineStipple (1, 0xFFFF);

                glColor3d(color.redF(),color.greenF(),color.blueF());
                glLineWidth((GLfloat)width);

                if (m_pctrlOutline->isChecked())
                {
                //TOP outline
                for (j=0; j<pWing->m_NSurfaces; j++)
                {
                        glBegin(GL_LINE_STRIP);
                        {
                                for (l=0; l<=100; l++)
                                {
                                        x = (double)l/100.0;
                                        pWing->m_Surface[j].GetPoint(x,x,0.0,Pt, PtNormal,1);
                                        glVertex3d(Pt.x, Pt.y, Pt.z);
                                }
                        }
                        glEnd();

                        glBegin(GL_LINE_STRIP);
                        {
                                for (l=0; l<=100; l++)
                                {
                                        x = (double)l/100.0;
                                        pWing->m_Surface[j].GetPoint(x,x,1.0,Pt, PtNormal,1);
                                        glVertex3d(Pt.x, Pt.y, Pt.z);
                                }
                        }
                        glEnd();
                }

                //BOTTOM outline
                for (j=0; j<pWing->m_NSurfaces; j++)
                {
                        glBegin(GL_LINE_STRIP);
                        {
                                for (l=0; l<=100; l++)
                                {
                                        x = (double)l/100.0;
                                        pWing->m_Surface[j].GetPoint(x,x,0.0,Pt, PtNormal,-1);
                                        glVertex3d(Pt.x, Pt.y, Pt.z);
                                }
                        }
                        glEnd();

                        glBegin(GL_LINE_STRIP);
                        {
                                for (l=0; l<=100; l++)
                                {
                                        x = (double)l/100.0;
                                        pWing->m_Surface[j].GetPoint(x,x,1.0,Pt, PtNormal,-1);
                                        glVertex3d(Pt.x, Pt.y, Pt.z);
                                }
                        }
                        glEnd();

                }



                glLineWidth((GLfloat)1);


                //WingContour
                //Leading edge outline
                for (j=0; j<pWing->m_NSurfaces; j++)
                {
                        glBegin(GL_LINES);
                        {
                                pWing->m_Surface[j].GetPanel(0,pWing->m_Surface[j].m_NXPanels-1, MIDSURFACE);
                                glVertex3d(pWing->m_Surface[j].LA.x,
                                                   pWing->m_Surface[j].LA.y,
                                                   pWing->m_Surface[j].LA.z);
                                pWing->m_Surface[j].GetPanel( pWing->m_Surface[j].m_NYPanels-1,pWing->m_Surface[j].m_NXPanels-1, MIDSURFACE);
                                glVertex3d(pWing->m_Surface[j].LB.x,
                                                   pWing->m_Surface[j].LB.y,
                                                   pWing->m_Surface[j].LB.z);
                        }
                        glEnd();
                }
                //Trailing edge outline
                for (j=0; j<pWing->m_NSurfaces; j++)
                {
                        glBegin(GL_LINES);
                        {
                                pWing->m_Surface[j].GetPanel(0,0, MIDSURFACE);
                                glVertex3d(pWing->m_Surface[j].TA.x,
                                                   pWing->m_Surface[j].TA.y,
                                                   pWing->m_Surface[j].TA.z);
                                pWing->m_Surface[j].GetPanel( pWing->m_Surface[j].m_NYPanels-1, 0, MIDSURFACE);
                                glVertex3d(pWing->m_Surface[j].TB.x,
                                                   pWing->m_Surface[j].TB.y,
                                                   pWing->m_Surface[j].TB.z);
                        }
                        glEnd();
                }
                //flap outline....
                for (j=0; j<pWing->m_NSurfaces; j++)
                {
                        pFoilA = pWing->m_Surface[j].m_pFoilA;
                        pFoilB = pWing->m_Surface[j].m_pFoilB;
                        if(pFoilA && pFoilB && pFoilA->m_bTEFlap && pFoilB->m_bTEFlap)
                        {
                                glBegin(GL_LINES);
                                {
                                        if(pFoilA->m_bTEFlap)
                                                pWing->m_Surface[j].GetPoint(pWing->m_Surface[j].m_pFoilA->m_TEXHinge/100.0,
                                                                                                         pWing->m_Surface[j].m_pFoilA->m_TEXHinge/100.0,
                                                                                                         0.0, Pt, 1);
                                        else 	pWing->m_Surface[j].GetPoint(1.0, 1.0, 0.0, Pt, 1);
                                        glVertex3d(Pt.x, Pt.y, Pt.z);

                                        if(pFoilB->m_bTEFlap)
                                                pWing->m_Surface[j].GetPoint(pWing->m_Surface[j].m_pFoilB->m_TEXHinge/100.0,
                                                                                                         pWing->m_Surface[j].m_pFoilB->m_TEXHinge/100.0,
                                                                                                         1.0, Pt, 1);
                                        else 	pWing->m_Surface[j].GetPoint(1.0, 1.0, 1.0, Pt, 1);
                                        glVertex3d(Pt.x, Pt.y, Pt.z);
                                }
                                glEnd();
                                glBegin(GL_LINES);
                                {
                                        if(pFoilA->m_bTEFlap)
                                                pWing->m_Surface[j].GetPoint(pWing->m_Surface[j].m_pFoilA->m_TEXHinge/100.0,
                                                                                                         pWing->m_Surface[j].m_pFoilA->m_TEXHinge/100.0,
                                                                                                         0.0, Pt, -1);
                                        else 	pWing->m_Surface[j].GetPoint(1.0, 1.0, 0.0, Pt, -1);
                                        glVertex3d(Pt.x, Pt.y, Pt.z);

                                        if(pFoilB->m_bTEFlap)
                                                pWing->m_Surface[j].GetPoint(pWing->m_Surface[j].m_pFoilB->m_TEXHinge/100.0,
                                                                                                         pWing->m_Surface[j].m_pFoilB->m_TEXHinge/100.0,
                                                                                                         1.0, Pt, -1);
                                        else 	pWing->m_Surface[j].GetPoint(1.0, 1.0, 1.0, Pt, -1);
                                        glVertex3d(Pt.x, Pt.y, Pt.z);
                                }
                                glEnd();
                        }
                }
                for (j=0; j<pWing->m_NSurfaces; j++)
                {
                        pFoilA = pWing->m_Surface[j].m_pFoilA;
                        pFoilB = pWing->m_Surface[j].m_pFoilB;
                        if(pFoilA && pFoilB && pFoilA->m_bLEFlap && pFoilB->m_bLEFlap)
                        {
                                glBegin(GL_LINES);
                                {
                                        if(pFoilA->m_bLEFlap)
                                                pWing->m_Surface[j].GetPoint(pWing->m_Surface[j].m_pFoilA->m_LEXHinge/100.0,
                                                                                                         pWing->m_Surface[j].m_pFoilA->m_LEXHinge/100.0,
                                                                                                         0.0, Pt, 1);
                                        else 	pWing->m_Surface[j].GetPoint(1.0, 1.0, 0.0, Pt, 1);
                                        glVertex3d(Pt.x, Pt.y, Pt.z);

                                        if(pFoilB->m_bLEFlap)
                                                pWing->m_Surface[j].GetPoint(pWing->m_Surface[j].m_pFoilB->m_LEXHinge/100.0,
                                                                                                         pWing->m_Surface[j].m_pFoilB->m_LEXHinge/100.0,
                                                                                                         1.0, Pt, 1);
                                        else 	pWing->m_Surface[j].GetPoint(1.0, 1.0, 1.0, Pt, 1);
                                        glVertex3d(Pt.x, Pt.y, Pt.z);
                                }
                                glEnd();
                                glBegin(GL_LINES);
                                {
                                        if(pFoilA->m_bLEFlap)
                                                pWing->m_Surface[j].GetPoint(pWing->m_Surface[j].m_pFoilA->m_LEXHinge/100.0,
                                                                                                         pWing->m_Surface[j].m_pFoilA->m_LEXHinge/100.0,
                                                                                                         0.0, Pt, -1);
                                        else 	pWing->m_Surface[j].GetPoint(1.0, 1.0, 0.0, Pt, -1);
                                        glVertex3d(Pt.x, Pt.y, Pt.z);

                                        if(pFoilB->m_bLEFlap)
                                                pWing->m_Surface[j].GetPoint(pWing->m_Surface[j].m_pFoilB->m_LEXHinge/100.0,
                                                                                                         pWing->m_Surface[j].m_pFoilB->m_LEXHinge/100.0,
                                                                                                         1.0, Pt, -1);
                                        else 	pWing->m_Surface[j].GetPoint(1.0, 1.0, 1.0, Pt, -1);
                                        glVertex3d(Pt.x, Pt.y, Pt.z);
                                }
                                glEnd();
                        }
                }
                }
                if (m_bAdvancedEdit)
                {
                glLineWidth((GLfloat)5);
                glColor3d(255,0,0);

                glBegin(GL_LINE_STRIP);
                {
                    for (j=0; j<=pWing->m_NPanel; j++)
                    {
                        Pt=CVector(pWing->m_TPAxisX[j],pWing->m_TPAxisY[j],pWing->m_TPAxisZ[j]);
                        glVertex3d(Pt.x, Pt.y, Pt.z);
                    }
                }
                glEnd();
                }
                glDisable (GL_LINE_STIPPLE);
        }
        }
        glEndList();

}

void QBEM::GLCreateSectionHighlight()
{
        int j,l;

        if (m_pWing)
        {


        glNewList(SECTIONHIGHLIGHT,GL_COMPILE);
        {

                glPolygonMode(GL_FRONT,GL_LINE);
                glDisable (GL_LINE_STIPPLE);
                glColor3d(1.0, 0.0, 0.0);
                glLineWidth(5);



                        if(m_iSection<m_pWing->m_NPanel)
                        {
                                j = m_iSection;
                                glBegin(GL_LINE_STRIP);
                                {
                                        for (l=0; l<m_pWing->m_Surface[j].m_NXPanels; l++)
                                        {
                                                m_pWing->m_Surface[j].GetPanel(0, l, TOPSURFACE);
                                                glVertex3d(m_pWing->m_Surface[j].TA.x,
                                                                   m_pWing->m_Surface[j].TA.y,
                                                                   m_pWing->m_Surface[j].TA.z);
                                        }

                                        glVertex3d(m_pWing->m_Surface[j].LA.x,
                                                           m_pWing->m_Surface[j].LA.y,
                                                           m_pWing->m_Surface[j].LA.z);

                                        for (l=m_pWing->m_Surface[j].m_NXPanels-1; l>=0; l--)
                                        {
                                                m_pWing->m_Surface[j].GetPanel(0, l, BOTSURFACE);
                                                glVertex3d(m_pWing->m_Surface[j].TA.x,
                                                                   m_pWing->m_Surface[j].TA.y,
                                                                   m_pWing->m_Surface[j].TA.z);
                                        }
                                }
                                glEnd();
                        }
                        else
                        {
                                j = m_iSection-1;
                                glBegin(GL_LINE_STRIP);
                                {
                                        for (l=0; l<m_pWing->m_Surface[j].m_NXPanels; l++)
                                        {
                                                m_pWing->m_Surface[j].GetPanel(m_pWing->m_Surface[j].m_NYPanels-1, l, TOPSURFACE);
                                                glVertex3d(m_pWing->m_Surface[j].TB.x,
                                                                   m_pWing->m_Surface[j].TB.y,
                                                                   m_pWing->m_Surface[j].TB.z);
                                        }

                                        glVertex3d(m_pWing->m_Surface[j].LB.x,
                                                           m_pWing->m_Surface[j].LB.y,
                                                           m_pWing->m_Surface[j].LB.z);

                                        for (l=m_pWing->m_Surface[j].m_NXPanels-1; l>=0; l--)
                                        {
                                                m_pWing->m_Surface[j].GetPanel(m_pWing->m_Surface[j].m_NYPanels-1, l, BOTSURFACE);
                                                glVertex3d(m_pWing->m_Surface[j].TB.x,
                                                                   m_pWing->m_Surface[j].TB.y,
                                                                   m_pWing->m_Surface[j].TB.z);
                                        }
                                }
                                glEnd();
                        }

//                if(!m_bRightSide)
//                {
//                        if(m_iSection>0 )
//                        {
//                                if(!m_pWing->m_bIsFin) j = m_pWing->m_NSurfaces/2 - section;
//                                else                   j = m_pWing->m_NSurfaces - section;
//                                glBegin(GL_LINE_STRIP);
//                                {
//                                        for (l=0; l<m_pWing->m_Surface[j].m_NXPanels; l++)
//                                        {
//                                                m_pWing->m_Surface[j].GetPanel(0, l, TOPSURFACE);
//                                                glVertex3d(m_pWing->m_Surface[j].TA.x,
//                                                                   m_pWing->m_Surface[j].TA.y,
//                                                                   m_pWing->m_Surface[j].TA.z);
//                                        }

//                                        glVertex3d(m_pWing->m_Surface[j].LA.x,
//                                                           m_pWing->m_Surface[j].LA.y,
//                                                           m_pWing->m_Surface[j].LA.z);

//                                        for (l=m_pWing->m_Surface[j].m_NXPanels-1; l>=0; l--)
//                                        {
//                                                m_pWing->m_Surface[j].GetPanel(0, l, BOTSURFACE);
//                                                glVertex3d(m_pWing->m_Surface[j].TA.x,
//                                                                   m_pWing->m_Surface[j].TA.y,
//                                                                   m_pWing->m_Surface[j].TA.z);
//                                        }
//                                }
//                                glEnd();
//                        }
//                        else
//                        {
//                                if(!m_pWing->m_bIsFin) j = m_pWing->m_NSurfaces/2 - 1;
//                                else                   j = m_pWing->m_NSurfaces - 1;
//                                glBegin(GL_LINE_STRIP);
//                                {
//                                        for (l=0; l<m_pWing->m_Surface[j].m_NXPanels; l++)
//                                        {
//                                                m_pWing->m_Surface[j].GetPanel(m_pWing->m_Surface[j].m_NYPanels-1, l, TOPSURFACE);
//                                                glVertex3d(m_pWing->m_Surface[j].TB.x,
//                                                                   m_pWing->m_Surface[j].TB.y,
//                                                                   m_pWing->m_Surface[j].TB.z);
//                                        }

//                                        glVertex3d(m_pWing->m_Surface[j].LB.x,
//                                                           m_pWing->m_Surface[j].LB.y,
//                                                           m_pWing->m_Surface[j].LB.z);

//                                        for (l=m_pWing->m_Surface[j].m_NXPanels-1; l>=0; l--)
//                                        {
//                                                m_pWing->m_Surface[j].GetPanel(m_pWing->m_Surface[j].m_NYPanels-1, l, BOTSURFACE);
//                                                glVertex3d(m_pWing->m_Surface[j].TB.x,
//                                                                   m_pWing->m_Surface[j].TB.y,
//                                                                   m_pWing->m_Surface[j].TB.z);
//                                        }
//                                }
//                                glEnd();
//                        }
//                }
        }
        glEndList();
    }
}

void QBEM::GLDraw3D()
{
        if (!m_pWing)
        {
                m_bResetglGeom = true;

        }
        MainFrame * pMainFrame =(MainFrame*)s_pMainFrame;

        glClearColor(pMainFrame->m_BackgroundColor.redF(), pMainFrame->m_BackgroundColor.greenF(), pMainFrame->m_BackgroundColor.blueF(),0.0);


        if(m_bResetglGeom  && m_iView==WingView)
        {
                if(m_pWing)
                {
                        if(glIsList(WINGSURFACES))
                        {
                                glDeleteLists(WINGSURFACES,2);
                        }
                        if (m_pctrlShowTurbine->isChecked()) GLCreateTurbine(WINGSURFACES);
                        else GLCreateGeom(m_pWing,WINGSURFACES);
                }





                m_bResetglGeom = false;
        }
        if(m_bResetglSectionHighlight)
        {
                if(glIsList(SECTIONHIGHLIGHT))
                {
                        glDeleteLists(SECTIONHIGHLIGHT,1);
                }
                if(m_iSection>=0)
                {
                        GLCreateSectionHighlight();
                        m_bResetglSectionHighlight = false;
                }
        }

        m_bResetglGeom=false;

}

void QBEM::OnShowTurbine()
{
    if (m_pctrlShowTurbine->isChecked())
    {

        for (int l=0;l<s_poaTurbineBlades.size();l++)
        {
            if (s_poaTurbineBlades[l]) delete s_poaTurbineBlades[l];
        }

        s_poaTurbineBlades.clear();


        CBlade *blade;

        for (int i=0;i<m_pWing->blades;i++)
        {
            blade = new CBlade;
            blade->Duplicate(m_pWing);
            blade->CreateSurfaces(CVector(0,0,0),0,0);

            for (int j=0;j<blade->m_NSurfaces;j++)
            {
                blade->m_Surface[j].RotateZ(CVector(0,0,0),360/m_pWing->blades*i);
                blade->m_Surface[j].SetSidePoints(NULL,0,0);
            }

            s_poaTurbineBlades.append(blade);

        }

    }

    m_bResetglGeom = true;
    UpdateView();
}


void QBEM::GLRenderView()
{

        static GLdouble pts[4];
        pts[0]= 0.0; pts[1]=0.0; pts[2]=-1.0; pts[3]= m_ClipPlanePos;  //x=m_VerticalSplit
        glClipPlane(GL_CLIP_PLANE1, pts);
        if(m_ClipPlanePos>4.9999) 	glDisable(GL_CLIP_PLANE1);
        else						glEnable(GL_CLIP_PLANE1);




        // Clear the viewport
        glFlush();
        glEnable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



        glPushMatrix();
        {


                if(m_pWing)			glCallList(WINGLEGEND);

                double LightFactor;
                if(m_pWing) LightFactor =  (GLfloat)pow(m_pWing->m_PlanformSpan/2.0,0.1);
                else           LightFactor = 1.0;
                m_pGLWidget->GLSetupLight(m_GLLightDlg, 0, LightFactor);

                GLCallViewLists();
        }
        glPopMatrix();
        glDisable(GL_CLIP_PLANE1);



}



bool QBEM::InitDialog(CBlade *pWing)
{
        m_bResetglSectionHighlight = true;

        QString str;
        m_iSection = 0;
        MainFrame *pMainFrame = (MainFrame*)s_pMainFrame;

        delete m_pWingModel;

        m_pWing = pWing;

        m_pctrlSave->setEnabled(false);
        m_pctrlOptimize->setEnabled(false);


        if(!m_pWing) return false;
        ComputeGeometry();

        GetLengthUnit(str, pMainFrame->m_LengthUnit);

        m_pctrlWingName->setText(m_pWing->m_WingName);


        m_pWingModel = new QStandardItemModel;
        m_pWingModel->setRowCount(100);//temporary
        m_pWingModel->setColumnCount(5);

        m_pWingModel->setHeaderData(0, Qt::Horizontal, tr("Pos (")+str+")");
        m_pWingModel->setHeaderData(1, Qt::Horizontal, tr("Chord (")+str+")");
        m_pWingModel->setHeaderData(2, Qt::Horizontal, tr("Twist in °"));
        m_pWingModel->setHeaderData(3, Qt::Horizontal, QObject::tr("Foil"));
        m_pWingModel->setHeaderData(4, Qt::Horizontal, QObject::tr("Polar"));




        m_pctrlBladeTable->setModel(m_pWingModel);

        for (int i=0;i<5;i++)
        {
        if (i==0) m_pctrlBladeTable->setColumnWidth(i,80);
        if (i==1) m_pctrlBladeTable->setColumnWidth(i,75);
        if (i==2) m_pctrlBladeTable->setColumnWidth(i,75);
        if (i==3) m_pctrlBladeTable->setColumnWidth(i,100);
        if (i==4) m_pctrlBladeTable->setColumnWidth(i,160);
        }



        QItemSelectionModel *selectionModel = new QItemSelectionModel(m_pWingModel);
        m_pctrlBladeTable->setSelectionModel(selectionModel);
        connect(selectionModel, SIGNAL(currentChanged(QModelIndex,QModelIndex)), this, SLOT(OnItemClicked(QModelIndex)));



        m_pBladeDelegate = new BladeDelegate;
        m_pctrlBladeTable->setItemDelegate(m_pBladeDelegate);
        connect(m_pBladeDelegate,  SIGNAL(closeEditor(QWidget *)), this, SLOT(OnCellChanged()));



        int  *precision = new int[3];
        precision[0] = 2;
        precision[1] = 2;
        precision[2] = 2;



        m_pBladeDelegate->SetPointers(precision,&m_pWing->m_NPanel);


        m_pBladeDelegate->m_poaFoil = s_poaFoil;
        m_pBladeDelegate->m_poaPolar= s_poa360Polar;
        m_pBladeDelegate->itemmodel = m_pWingModel;

        FillDataTable();
        m_pctrlBladeTable->selectRow(m_iSection);
        SetCurrentSection(m_iSection);
        m_bResetglGeom = true;
        UpdateView();
        return true;
}

bool QBEM::InitAdvancedDialog(CBlade *pWing)
{

    m_bResetglSectionHighlight = true;

    QString str;
    m_iSection = 0;
    MainFrame *pMainFrame = (MainFrame*)s_pMainFrame;

    delete m_pBladeAxisModel;

    m_pWing = pWing;

    m_pctrlSave->setEnabled(false);
    m_pctrlOptimize->setEnabled(false);


    if(!m_pWing) return false;
    ComputeGeometry();

    GetLengthUnit(str, pMainFrame->m_LengthUnit);

    m_pctrlWingName->setText(m_pWing->m_WingName);


    m_pBladeAxisModel = new QStandardItemModel;
    m_pBladeAxisModel->setRowCount(100);//temporary
    m_pBladeAxisModel->setColumnCount(5);

    m_pBladeAxisModel->setHeaderData(0, Qt::Horizontal, tr("Position (")+str+")");
    m_pBladeAxisModel->setHeaderData(1, Qt::Horizontal, tr("Offset (")+str+")");
    m_pBladeAxisModel->setHeaderData(2, Qt::Horizontal, tr("Dihedral (in °)"));
    m_pBladeAxisModel->setHeaderData(3, Qt::Horizontal, tr("Thread Axis X (% chord)"));
    m_pBladeAxisModel->setHeaderData(4, Qt::Horizontal, tr("Thread Axis Z (% chord)"));

    m_pctrlBladeAxisTable->setModel(m_pBladeAxisModel);

    for (int i=0;i<3;i++)
    {
    m_pctrlBladeAxisTable->setColumnWidth(i,95);
    }
    m_pctrlBladeAxisTable->setColumnWidth(3,105);
    m_pctrlBladeAxisTable->setColumnWidth(4,105);


    QItemSelectionModel *selectionModel = new QItemSelectionModel(m_pBladeAxisModel);
    m_pctrlBladeAxisTable->setSelectionModel(selectionModel);
    connect(selectionModel, SIGNAL(currentChanged(QModelIndex,QModelIndex)), this, SLOT(OnItemClicked(QModelIndex)));

    m_pBladeAxisDelegate = new BladeAxisDelegate;
    m_pctrlBladeAxisTable->setItemDelegate(m_pBladeAxisDelegate);

    connect(m_pBladeAxisDelegate,  SIGNAL(closeEditor(QWidget *)), this, SLOT(OnCellChanged()));


    int  *precision = new int[5];
    precision[0] = 2;
    precision[1] = 2;
    precision[2] = 2;
    precision[3] = 2;
    precision[4] = 2;

    m_pBladeAxisDelegate->SetPointers(precision,&m_pWing->m_NPanel);

    m_pBladeAxisDelegate->itemmodel = m_pWingModel;

    FillDataTable();
    m_pctrlBladeAxisTable->selectRow(m_iSection);
    SetCurrentSection(m_iSection);
    m_bResetglGeom = true;
    UpdateView();
    return true;
}


void QBEM::InitWingTable()
{
    m_bResetglSectionHighlight = true;

    MainFrame *pMainFrame = (MainFrame *) s_pMainFrame;

    if (m_pWing)
    {
    if (m_pWingModel) delete m_pWingModel;

    m_pctrlWingNameLabel->setText(m_pWing->m_WingName);


    QString str;
    GetLengthUnit(str, pMainFrame->m_LengthUnit);

    QString text, blades, hub;
    blades.sprintf("%.0f",double(m_pWing->blades));
    hub.sprintf("%.2f",m_pWing->m_HubRadius*pMainFrame->m_mtoUnit);
    text = "Rotor has "+blades+" blades and "+hub+" "+str+" hub radius";
    if (m_bAbsoluteBlade) text += " and is shown in absolute (hub center) coordinates";
    else text += " and is shown in relative (blade root) coordinates";
    m_pctrlBladesAndHubLabel->setText(text);


    m_pWingModel = new QStandardItemModel;
    m_pWingModel->setRowCount(100);//temporary
    m_pWingModel->setColumnCount(5);

    m_pWingModel->setHeaderData(0, Qt::Horizontal, tr("Pos (")+str+")");
    m_pWingModel->setHeaderData(1, Qt::Horizontal, tr("Chord (")+str+")");
    m_pWingModel->setHeaderData(2, Qt::Horizontal, tr("Twist"));
    m_pWingModel->setHeaderData(3, Qt::Horizontal, QObject::tr("Foil"));
    m_pWingModel->setHeaderData(4, Qt::Horizontal, QObject::tr("Polar"));

    m_pctrlBladeTableView->setModel(m_pWingModel);

    for (int i=0;i<5;i++)
    {
    if (i==0) m_pctrlBladeTableView->setColumnWidth(i,80);
    if (i==1) m_pctrlBladeTableView->setColumnWidth(i,75);
    if (i==2) m_pctrlBladeTableView->setColumnWidth(i,75);
    if (i==3) m_pctrlBladeTableView->setColumnWidth(i,100);
    if (i==4) m_pctrlBladeTableView->setColumnWidth(i,150);
    }

    m_iSection = -1;
    FillDataTable();
    ComputeGeometry();
    m_bResetglGeom = true;
    UpdateView();
    }
    else
    {
    if (m_pWingModel) delete m_pWingModel;
    m_pWingModel = new QStandardItemModel;
    m_pWingModel->setRowCount(0);
    m_pWingModel->setColumnCount(0);
    m_pctrlBladeTableView->setModel(m_pWingModel);
    }
}

void QBEM::InitTurbineData(TData *pTData)
{
    MainFrame *pMainFrame = (MainFrame *) s_pMainFrame;
    QString strong, str;

    if (pTData)
    {
    if (pTData->isStall) Type->setText("Stall");
    if (pTData->isPitch) Type->setText("Pitch");
    if (pTData->isFixed) Trans->setText("Single");
    if (pTData->is2Step) Trans->setText("2 Step");
    if (pTData->isVariable) Trans->setText("Variable");

    Rot1->setText(strong.number(pTData->Rot1,'f',2));
    Rot2->setText(strong.number(pTData->Rot2,'f',2));
    Lambda0->setText(strong.number(pTData->Lambda0,'f',2));
    Generator->setText(strong.number(pTData->Generator*pMainFrame->m_WtoUnit,'f',2));
    CutIn->setText(strong.number(pTData->CutIn*pMainFrame->m_mstoUnit,'f',2));
    CutOut->setText(strong.number(pTData->CutOut*pMainFrame->m_mstoUnit,'f',2));
    Switch->setText(strong.number(pTData->Switch*pMainFrame->m_mstoUnit,'f',2));
    FixedLosses->setText(strong.number(pTData->FixedLosses*pMainFrame->m_WtoUnit,'f',2));
    VariableLosses->setText(strong.number(pTData->VariableLosses,'f',3));
    OuterRadius->setText(strong.number(pTData->OuterRadius*pMainFrame->m_mtoUnit,'f',2));
    Blade->setText(pTData->m_WingName);
    FixedPitch->setText(strong.number(pTData->FixedPitch,'f',2));

    GetLengthUnit(str, pMainFrame->m_LengthUnit);
    Length1->setText(str);
    GetSpeedUnit(str, pMainFrame->m_SpeedUnit);
    Speed1->setText(str);
    Speed2->setText(str);
    Speed3->setText(str);
    GetPowerUnit(str, pMainFrame->m_PowerUnit);
    Power1->setText(str);
    Power2->setText(str);


    if (pTData->isPitch)
    {
        Generator->hide();
        GeneratorLabel->hide();
    }
    else
    {
        Generator->hide();
        GeneratorLabel->hide();
    }

    Rot1->show();
    Rot2->hide();
    Lambda0->hide();
    Generator->hide();
    CutIn->show();
    CutOut->show();
    Switch->hide();
    Blade->show();
    Type->hide();
    Trans->hide();

    Rot1Label->show();
    Rot2Label->hide();
    LambdaLabel->hide();
    GeneratorLabel->hide();
    CutInLabel->show();
    CutOutLabel->show();
    SwitchLabel->hide();
    BladeLabel->show();
    TypeLabel->hide();
    GeneratorTypeLabel->hide();

    /////////unit labels////
    Speed1->show();
    Speed2->show();
    Speed3->hide();
    Rotspeed1->show();
    Rotspeed2->hide();
    Power1->hide();
    Power2->hide();
    Length1->show();


    if (pTData->isVariable)
    {
        Rot1Label->setText(tr("Rotational Speed Min"));
        Rot2Label->setText(tr("Rotational Speed Max"));
        SwitchLabel->setText("");
        LambdaLabel->setText("Tip Speed Ratio at Design Point");
        Rot1->show();
        Speed1->show();
        Rot2->show();
        Speed2->show();
        Switch->hide();
        Speed3->show();
        Lambda0->show();

    }
    if (pTData->is2Step)
    {
        Rot1Label->setText(tr("Rotational Speed 1"));
        Rot2Label->setText(tr("Rotational Speed 2"));
        SwitchLabel->setText("V Switch");
        LambdaLabel->setText("");
        Rot1->show();
        Rotspeed1->show();
        Rot2->show();
        Rotspeed2->show();
        Switch->show();
        Speed3->show();
        Lambda0->hide();
    }
    if (pTData->isFixed)
    {
        Rot1Label->setText(tr("Rotational Speed"));
        Rot2Label->setText(tr(""));
        SwitchLabel->setText("");
        LambdaLabel->setText("");
        Rot1->show();
        Rotspeed1->show();
        Rot2->hide();
        Rotspeed2->hide();
        Switch->hide();
        Speed3->hide();
        Lambda0->hide();
    }
    }
    else
    {
        Rot1->hide();
        Rotspeed1->hide();
        Rot2->hide();
        Rotspeed2->hide();

        Lambda0->hide();
        Generator->hide();
        Power1->hide();
        CutIn->hide();
        CutOut->hide();
        Switch->hide();
        Speed1->hide();
        Speed2->hide();
        Speed3->hide();

        Blade->hide();
        Type->hide();
        Trans->hide();

        Rot1Label->hide();
        Rot2Label->hide();
        LambdaLabel->hide();
        GeneratorLabel->hide();
        CutInLabel->hide();
        CutOutLabel->hide();
        SwitchLabel->hide();
        BladeLabel->hide();
        TypeLabel->hide();
        GeneratorTypeLabel->hide();

        Power1->hide();
        Power2->hide();
        Length1->hide();
    }


}

void QBEM::InitTurbineSimulationParams(TBEMData *bladedata)
{

    SimuWidget *pSimuWidget = (SimuWidget *) m_pSimuWidget;

    QString strong;

    if(bladedata)
    {
    pSimuWidget->m_pctrlRhoVal->setText(strong.number(bladedata->rho,'f',4));
    pSimuWidget->m_pctrlElementsVal->setText(strong.number(bladedata->elements,'f',0));
    pSimuWidget->m_pctrlIterationVal->setText(strong.number(bladedata->iterations,'f',0));
    pSimuWidget->m_pctrlEpsilonVal->setText(strong.number(bladedata->epsilon,'f',4));
    pSimuWidget->m_pctrlRelaxVal->setText(strong.number(bladedata->relax,'f',1));
    pSimuWidget->m_pctrlViscVal->setText(strong.number(bladedata->visc,'e',8));
    pSimuWidget->m_pctrlTipLoss->setChecked(bladedata->m_bTipLoss);
    pSimuWidget->m_pctrlRootLoss->setChecked(bladedata->m_bRootLoss);
    pSimuWidget->m_pctrl3DCorrection->setChecked(bladedata->m_b3DCorrection);
    pSimuWidget->m_pctrl3DEquilibrium->setChecked(bladedata->m_b3DEquilibrium);
    pSimuWidget->m_pctrlInterpolation->setChecked(bladedata->m_bInterpolation);
    pSimuWidget->m_pctrlNewRootLoss->setChecked(bladedata->m_bNewRootLoss);
    pSimuWidget->m_pctrlNewTipLoss->setChecked(bladedata->m_bNewTipLoss);
    }
    if(!bladedata)
    {
    pSimuWidget->m_pctrlRhoVal->setText("");
    pSimuWidget->m_pctrlElementsVal->setText("");
    pSimuWidget->m_pctrlIterationVal->setText("");
    pSimuWidget->m_pctrlEpsilonVal->setText("");
    pSimuWidget->m_pctrlRelaxVal->setText("");
    pSimuWidget->m_pctrlViscVal->setText("");
    pSimuWidget->m_pctrlTipLoss->setChecked(false);
    pSimuWidget->m_pctrlRootLoss->setChecked(false);
    pSimuWidget->m_pctrl3DCorrection->setChecked(false);
    pSimuWidget->m_pctrl3DEquilibrium->setChecked(false);
    pSimuWidget->m_pctrlInterpolation->setChecked(false);
    pSimuWidget->m_pctrlNewRootLoss->setChecked(false);
    pSimuWidget->m_pctrlNewTipLoss->setChecked(false);
    }

    if(bladedata)
    {
    m_pctrla->setValue(bladedata->A);
    m_pctrlk->setValue(bladedata->K);
    m_pctrla->setEnabled(true);
    m_pctrlk->setEnabled(true);
    }
    if(!bladedata)
    {
    m_pctrla->setValue(2);
    m_pctrlk->setValue(9);
    m_pctrla->setEnabled(false);
    m_pctrlk->setEnabled(false);
    m_pctrlYield->setText("");
    }



}

void QBEM::InitBladeSimulationParams(BEMData *bladedata)
{
    SimuWidget *pSimuWidget = (SimuWidget *) m_pSimuWidget;

    QString strong;

    if(bladedata)
    {
    pSimuWidget->m_pctrlRhoVal->setText(strong.number(bladedata->rho,'f',4));
    pSimuWidget->m_pctrlElementsVal->setText(strong.number(bladedata->elements,'f',0));
    pSimuWidget->m_pctrlIterationVal->setText(strong.number(bladedata->iterations,'f',0));
    pSimuWidget->m_pctrlEpsilonVal->setText(strong.number(bladedata->epsilon,'f',4));
    pSimuWidget->m_pctrlRelaxVal->setText(strong.number(bladedata->relax,'f',1));
    pSimuWidget->m_pctrlViscVal->setText(strong.number(bladedata->visc,'e',8));
    pSimuWidget->m_pctrlTipLoss->setChecked(bladedata->m_bTipLoss);
    pSimuWidget->m_pctrlRootLoss->setChecked(bladedata->m_bRootLoss);
    pSimuWidget->m_pctrl3DCorrection->setChecked(bladedata->m_b3DCorrection);
    pSimuWidget->m_pctrl3DEquilibrium->setChecked(bladedata->m_b3DEquilibrium);
    pSimuWidget->m_pctrlInterpolation->setChecked(bladedata->m_bInterpolation);
    pSimuWidget->m_pctrlNewRootLoss->setChecked(bladedata->m_bNewRootLoss);
    pSimuWidget->m_pctrlNewTipLoss->setChecked(bladedata->m_bNewTipLoss);
    }
    if(!bladedata)
    {
    pSimuWidget->m_pctrlRhoVal->setText("");
    pSimuWidget->m_pctrlElementsVal->setText("");
    pSimuWidget->m_pctrlIterationVal->setText("");
    pSimuWidget->m_pctrlEpsilonVal->setText("");
    pSimuWidget->m_pctrlRelaxVal->setText("");
    pSimuWidget->m_pctrlViscVal->setText("");
    pSimuWidget->m_pctrlTipLoss->setChecked(false);
    pSimuWidget->m_pctrlRootLoss->setChecked(false);
    pSimuWidget->m_pctrl3DCorrection->setChecked(false);
    pSimuWidget->m_pctrl3DEquilibrium->setChecked(false);
    pSimuWidget->m_pctrlInterpolation->setChecked(false);
    pSimuWidget->m_pctrlNewRootLoss->setChecked(false);
    pSimuWidget->m_pctrlNewTipLoss->setChecked(false);
    }



}

void QBEM::keyPressEvent(QKeyEvent *event)
{

        //MainFrame *pMainFrame = (MainFrame*)m_pMainFrame;
        switch (event->key())
        {
         case Qt::Key_Control:
         {
                 UpdateView();
                 break;
         }

        case Qt::Key_X:
                m_bXPressed = true;
                break;

        case Qt::Key_Y:
                m_bYPressed = true;
                break;

         default:
                 QWidget::keyPressEvent(event);

         }
}

void QBEM::keyReleaseEvent(QKeyEvent *event)
{

        switch (event->key())
        {
                case Qt::Key_Control:
                {
                        UpdateView();
                        break;
                }

                case Qt::Key_X:
                        if(!event->isAutoRepeat()) m_bXPressed = false;
                        break;

                case Qt::Key_Y:
                        if(!event->isAutoRepeat()) m_bYPressed = false;
                        break;

                default:
                    event->ignore();
        }
}

void QBEM::LoadSettings(QSettings *pSettings)
{


        pSettings->beginGroup("XBEM");
        {
            dlg_lambda      =       pSettings->value("Lambda").toDouble();
            dlg_blades      =       pSettings->value("Blades").toInt();
            dlg_epsilon     =       pSettings->value("Epsilon").toDouble();
            dlg_iterations  =       pSettings->value("Interations").toInt();
            dlg_elements    =       pSettings->value("Elements").toInt();
            dlg_rho         =       pSettings->value("Rho").toDouble();
            dlg_relax       =       pSettings->value("Relax").toDouble();
            dlg_tiploss     =       pSettings->value("TipLoss").toBool();
            dlg_rootloss    =       pSettings->value("RootLoss").toBool();
            dlg_3dcorrection=       pSettings->value("3DCorrection").toBool();
            dlg_3dequilibrium=      pSettings->value("3DEquilibrium").toBool();
            dlg_interpolation=      pSettings->value("Interpolation").toBool();
            //m_iView         =       pSettings->value("iView").toInt();
            dlg_lambdastart =       pSettings->value("lambdastart").toDouble();
            dlg_lambdaend   =       pSettings->value("lambdaend").toDouble();
            dlg_lambdadelta =       pSettings->value("lambdadelta").toDouble();
            dlg_windstart   =       pSettings->value("windstart").toDouble();
            dlg_windend     =       pSettings->value("windend").toDouble();
            dlg_winddelta   =       pSettings->value("winddelta").toDouble();
            m_cylName       =       pSettings->value("cylName").toString();
            m_cylPolarName  =       pSettings->value("cylPolarName").toString();
            dlg_newtiploss  =       pSettings->value("newtiploss").toBool();
            dlg_newrootloss =       pSettings->value("newrootloss").toBool();
            dlg_visc        =       pSettings->value("visc").toDouble();


        }
        pSettings->endGroup();

        m_CharGraph1.LoadSettings(pSettings);
        m_CharGraph2.LoadSettings(pSettings);
        m_CharGraph3.LoadSettings(pSettings);
        m_PowerGraph1.LoadSettings(pSettings);
        m_PowerGraph2.LoadSettings(pSettings);
        m_PowerGraph3.LoadSettings(pSettings);
        m_360CLGraph.LoadSettings(pSettings);
        m_360CDGraph.LoadSettings(pSettings);

SetPowerGraphTitles(&m_PowerGraph1);
SetPowerGraphTitles(&m_PowerGraph2);
SetPowerGraphTitles(&m_PowerGraph3);
SetGraphTitles(&m_CharGraph1);
SetGraphTitles(&m_CharGraph2);
SetGraphTitles(&m_CharGraph3);
SetPolarGraphTitles(&m_360CLGraph);
SetPolarGraphTitles(&m_360CDGraph);

}

void QBEM::mouseDoubleClickEvent ( QMouseEvent * event )
{
        if(!m_pCurGraph) return;

        OnGraphSettings();
}

void QBEM::MouseMoveEvent(QMouseEvent *event)
{
        if(!hasFocus()) setFocus();
        static CVector Real;
        static QPoint Delta, point;
        static bool bCtrl;
        QPoint pt(event->pos().x(), event->pos().y());

        Delta.setX(event->pos().x() - m_LastPoint.x());
        Delta.setY(event->pos().y() - m_LastPoint.y());
        point = event->pos();
        m_pCurGraph = GetGraph(point);
        bCtrl = false;
        if(event->modifiers() & Qt::ControlModifier) bCtrl =true;

        {

                m_pCurGraph = GetGraph(pt);
                if ((event->buttons() & Qt::LeftButton))// &&  ((m_iView==PolarView) || (m_iView==CharView)))
                {
                        if(m_pCurGraph)
                        {

                                // we translate the curves inside the graph
                                double xu, yu;
                                m_pCurGraph->SetAuto(false);
                                double x1 =  m_pCurGraph->ClientTox(m_LastPoint.x()) ;
                                double y1 =  m_pCurGraph->ClientToy(m_LastPoint.y()) ;

                                xu = m_pCurGraph->ClientTox(point.x());
                                yu = m_pCurGraph->ClientToy(point.y());

                                double xmin = m_pCurGraph->GetXMin() - xu+x1;
                                double xmax = m_pCurGraph->GetXMax() - xu+x1;
                                double ymin = m_pCurGraph->GetYMin() - yu+y1;
                                double ymax = m_pCurGraph->GetYMax() - yu+y1;

                                m_pCurGraph->SetWindow(xmin, xmax, ymin, ymax);
                                UpdateView();
                        }
                        else if(m_iView == CharView)
                        {
                                m_CharLegendOffset.rx() += Delta.x();
                                m_CharLegendOffset.ry() += Delta.y();
                                UpdateView();
                        }
                        else if(m_iView == PowerView)
                        {
                                m_PowerLegendOffset.rx() += Delta.x();
                                m_PowerLegendOffset.ry() += Delta.y();
                                UpdateView();
                        }
                    }
            }
        m_LastPoint = point;
}

void QBEM::MousePressEvent(QMouseEvent *event)
{
        QPoint pt(event->x(), event->y()); //client coordinates

        m_pCurGraph = GetGraph(pt);

        if (event->buttons() & Qt::LeftButton)
        {
                QPoint point = event->pos();

                m_PointDown = point;
                m_LastPoint = point;
          }
          if (event->buttons() & Qt::RightButton)
          {
          m_pCurGraph = GetGraph(pt);
          }
    }

void QBEM::MouseReleaseEvent(QMouseEvent *event)
{

}

void QBEM::NormalVector(GLdouble p1[3], GLdouble p2[3],  GLdouble p3[3], GLdouble n[3])
{
        GLdouble v1[3], v2[3], d;
        // calculate two vectors, using the middle point
        // as the common origin
        v1[0] = p3[0] - p1[0];
        v1[1] = p3[1] - p1[1];
        v1[2] = p3[2] - p1[2];
        v2[0] = p3[0] - p2[0];
        v2[1] = p3[1] - p2[1];
        v2[2] = p3[2] - p2[2];

        // calculate the cross product of the two vectors
        n[0] = v1[1] * v2[2] - v2[1] * v1[2];
        n[1] = v1[2] * v2[0] - v2[2] * v1[0];
        n[2] = v1[0] * v2[1] - v2[0] * v1[1];

        // normalize the vector
        d = ( n[0] * n[0] + n[1] * n[1] + n[2] * n[2] );
        // try to catch very small vectors
        if (d < (GLdouble)0.00000001)
        {
                d = (GLdouble)100000000.0;
        }
        else
        {
                d = (GLdouble)1.0 / sqrt(d);
        }

        n[0] *= d;
        n[1] *= d;
        n[2] *= d;
}

void QBEM::OnSimpleDesign()
{
    m_bAdvancedEdit = false;
    InitDialog(m_pWing);
    mainWidget->setCurrentIndex(0);
    bladeWidget->setCurrentIndex(1);
}

void QBEM::OnHubChanged()
{
    /////if the hub radius was changed, the blade positions are updated

    MainFrame *pMainFrame = (MainFrame *) s_pMainFrame;

    m_pWing->m_HubRadius = m_pctrlHubRadius->Value() / pMainFrame->m_mtoUnit;
    double add;
    add = m_pWing->m_HubRadius-m_pWing->m_TPos[0];

    for (int i = 0;i<=m_pWing->m_NPanel;i++)
    {
    m_pWing->m_TPos[i]+=add;
    FillTableRow(i);
    }

    ReadParams();
}

void QBEM::OnBladeColor()
{
    if(!m_pWing) return;

    QColor WingColor = QColorDialog::getColor(m_pWing->m_WingColor,
                                      this, "Select the wing color", QColorDialog::ShowAlphaChannel);
    if(WingColor.isValid()) m_pWing->m_WingColor = WingColor;

    m_pctrlWingColor->SetColor(m_pWing->m_WingColor);
    m_bResetglGeom = true;
    ComputeGeometry();
    UpdateView();

}

void QBEM::OnSectionColor()
{
    if(!m_pWing) return;

    QColor SectionColor = QColorDialog::getColor(m_OutlineColor,
                                      this, "Select the section color", QColorDialog::ShowAlphaChannel);
    if(SectionColor.isValid()) m_OutlineColor = SectionColor;

    m_pctrlSectionColor->SetColor(m_OutlineColor);
    m_bResetglGeom = true;
    ComputeGeometry();
    UpdateView();

}

void QBEM::OnLightDlg()
{

    GLWidget *pGLWidget = (GLWidget*)m_pGLWidget;

    GLLightDlg::s_bLight = m_bglLight;
    m_GLLightDlg.m_pGLWidget = m_pGLWidget;

    m_GLLightDlg.show();

    m_bglLight = GLLightDlg::s_bLight;


    double LightFactor;
    if(m_pWing) LightFactor =  (GLfloat)pow(m_pWing->m_PlanformSpan/2.0,0.1);
    else           LightFactor = 1.0;
    pGLWidget->GLSetupLight(m_GLLightDlg, 0, LightFactor);
    UpdateView();

}

void QBEM::OnSelChangeTurbine(int i)
{

        MainFrame* pMainFrame = (MainFrame *) s_pMainFrame;
        QString strong;
        bool changed=false;
        if (i >=0) strong = pMainFrame->m_pctrlTurbine->itemText(i);

        for (int j=0;j<s_poaTData.size();j++)
        {
            if (s_poaTData.at(j)->m_TurbineName==strong)
            {
                m_pTData = s_poaTData.at(j);
                changed=true;
            }
        }

        if (changed)
        {

            InitTurbineData(m_pTData);
            UpdateTurbines();
            m_bChanged=false;
            CheckButtons();
        }

}


void QBEM::OnStartRotorSimulation()
{

    MainFrame *pMainFrame = (MainFrame *) s_pMainFrame;
    SimuWidget *pSimuWidget = (SimuWidget *) m_pSimuWidget;

    double lstart, lend, ldelta;
    int times;

    lstart  =   pSimuWidget->m_pctrlLSLineEdit->Value();
    lend    =   pSimuWidget->m_pctrlLELineEdit->Value();
    ldelta  =   pSimuWidget->m_pctrlLDLineEdit->Value();
    times   =   int((lend-lstart)/ldelta);


    dlg_lambdastart = pSimuWidget->m_pctrlLSLineEdit->Value();
    dlg_lambdaend   = pSimuWidget->m_pctrlLELineEdit->Value();
    dlg_lambdadelta = pSimuWidget->m_pctrlLDLineEdit->Value();

    m_pBEMData->Clear();

    QProgressDialog progress("", "Abort BEM", 0, times, this);
    progress.setMinimumDuration(1000);
    progress.setModal(true);

    for (int i=0;i<=times;i++)
    {
    if (progress.wasCanceled()) break;


    QString curlambda;
    curlambda.sprintf("%.1f",lstart+i*ldelta);
    QString text = "Compute BEM for Lambda " + curlambda;
    progress.setLabelText(text);
    progress.setValue(i);


    m_pBladeData = new BData;
    m_pBEMData->Compute(m_pBladeData,m_pWing,lstart+i*ldelta,0);
    m_pBladeData->m_Color = pMainFrame->GetColor(9);

    m_pBData = m_pBEMData->m_BData[0];

    CreateRotorCurves();

    }


    UpdateWings();
    SetCurveParams();
    FillComboBoxes();


}

void QBEM::OnStartTurbineSimulation()
{

    MainFrame *pMainFrame = (MainFrame *) s_pMainFrame;
    SimuWidget *pSimuWidget = (SimuWidget *) m_pSimuWidget;

    double vstart, vend, vdelta, windspeed, lambda, rot;
    int times;
    double pitch = m_pTData->FixedPitch;



    vstart  =   pSimuWidget->m_pctrlWind1->Value()/pMainFrame->m_mstoUnit;
    vend    =   pSimuWidget->m_pctrlWind2->Value()/pMainFrame->m_mstoUnit;;
    vdelta  =   pSimuWidget->m_pctrlWindDelta->Value()/pMainFrame->m_mstoUnit;;
    times   =   int((vend-vstart)/vdelta);

    dlg_windstart   = pSimuWidget->m_pctrlWind1->Value();
    dlg_windend     = pSimuWidget->m_pctrlWind2->Value();
    dlg_winddelta   = pSimuWidget->m_pctrlWindDelta->Value();

    m_pTBEMData->Clear();

    ////////get wing and associated polars;
    CBlade *pWing;
    for (int i=0; i<s_poaBEMWings->size(); i++)
    {
            pWing = (CBlade*)s_poaBEMWings->at(i);
            if (pWing->m_WingName == m_pTData->m_WingName)
            {
                break;
            }
    }
    /////////////////

    QProgressDialog progress("", "Abort BEM", 0, times, this);
    progress.setMinimumDuration(1000);
    progress.setModal(true);

    for (int i=0;i<=times;i++)
    {

        m_pBladeData = new BData;

        if (progress.wasCanceled()) break;

        windspeed = vstart+vdelta*i;

        //// check which rotational speed is used (for fixed, 2step and variable)////
        if (m_pTData->isFixed) rot = m_pTData->Rot1;

        if (m_pTData->is2Step)
        {
            if (windspeed < m_pTData->Switch) rot = m_pTData->Rot1;
            if (windspeed >= m_pTData->Switch) rot = m_pTData->Rot2;
        }

        if (m_pTData->isVariable)
        {
            rot = m_pTData->Lambda0*windspeed*60/2/PI/m_pTData->OuterRadius;
            if (rot<m_pTData->Rot1) rot = m_pTData->Rot1;
            if (rot>m_pTData->Rot2) rot = m_pTData->Rot2;

        }

        ////////////////////////////////////////////////////////////
        QString curwind;
        curwind.sprintf("%.1f",windspeed);
        QString text = "Compute BEM for Windspeed " + curwind;
        progress.setLabelText(text);
        progress.setValue(i);

        lambda = m_pTData->OuterRadius*2*PI/60/windspeed*rot;


        if (windspeed>=m_pTData->CutIn && windspeed<=m_pTData->CutOut)
        {
            m_pTBEMData->Compute(m_pBladeData,pWing,lambda,pitch,windspeed);

            int oo=0;


            if (m_pTData->isPitch)
                {
//if pitch controll is enabled compute pitch angles to reduce power output

                if ((1-m_pTData->VariableLosses)*PI/2*pow(m_pTData->OuterRadius,2)*m_pTBEMData->rho*pow(windspeed,3)*m_pBladeData->cp-m_pTData->FixedLosses > m_pTData->Generator)
                    {

                        while ((1-m_pTData->VariableLosses)*PI/2*pow(m_pTData->OuterRadius,2)*m_pTBEMData->rho*pow(windspeed,3)*m_pBladeData->cp-m_pTData->FixedLosses > m_pTData->Generator)
                            {
                                if (m_pBladeData) delete m_pBladeData;
                                m_pBladeData= new BData;
                                pitch = pitch + 0.05;
                                m_pTBEMData->Compute(m_pBladeData,pWing,lambda,pitch,windspeed);
                                oo++;
                                QString curpitch;
                                curpitch.sprintf("%.1f",pitch);
                                text = "Now Pitching at " + curpitch +"°";
                                progress.setLabelText(text);
                                progress.setValue(i+oo);
                                if (progress.wasCanceled()) break;
                            }
                                m_pBladeData->cp = (m_pTData->Generator + m_pTData->FixedLosses)/((1-m_pTData->VariableLosses)*PI/2*pow(m_pTData->OuterRadius,2)*m_pTBEMData->rho*pow(windspeed,3));
                      }

                }

// fill turbine data



                m_pTBEMData->m_Omega.append(rot);
                m_pTBEMData->m_V.append(windspeed);
                m_pTBEMData->m_BData.append(m_pBladeData);
                if ((1-m_pTData->VariableLosses)*PI/2*pow(m_pTData->OuterRadius,2)*m_pTBEMData->rho*pow(windspeed,3)*m_pBladeData->cp-m_pTData->FixedLosses > 0)
                {
                m_pTBEMData->m_P.append((1-m_pTData->VariableLosses)*PI/2*pow(m_pTData->OuterRadius,2)*m_pTBEMData->rho*pow(windspeed,3)*m_pBladeData->cp-m_pTData->FixedLosses);
                }
                else m_pTBEMData->m_P.append(0);
                m_pTBEMData->m_Torque.append(PI/2*pow(m_pTData->OuterRadius,2)*m_pTBEMData->rho*pow(windspeed,3)*m_pBladeData->cp/rot*60);
                m_pTBEMData->m_Cp_loss.append(((1-m_pTData->VariableLosses)*PI/2*pow(m_pTData->OuterRadius,2)*m_pTBEMData->rho*pow(windspeed,3)*m_pBladeData->cp-m_pTData->FixedLosses)/(PI/2*pow(m_pTData->OuterRadius,2)*m_pTBEMData->rho*pow(windspeed,3)));
                m_pTBEMData->m_Ct.append(m_pBladeData->ct);
                m_pTBEMData->m_Ct_prop.append(m_pBladeData->ct_prop);
                m_pTBEMData->m_Lambda.append(lambda);
                m_pTBEMData->m_S.append(pow(m_pTData->OuterRadius,2)*PI*m_pTBEMData->rho/2*pow(windspeed,2)*m_pBladeData->ct);
                m_pTBEMData->m_Pitch.append(pitch);
                m_pTBEMData->m_Weibull.append(0);
                m_pTBEMData->m_WeibullV3.append(0);
                m_pTBEMData->m_Cp.append(m_pBladeData->cp);
                m_pTBEMData->m_Cp_prop.append(m_pBladeData->cp_prop);
                m_pTBEMData->m_Kp.append(m_pBladeData->cp/pow(m_pBladeData->lambda_global,3));
                m_pTBEMData->m_one_over_lambda.append(1/m_pBladeData->lambda_global);
                m_pTBEMData->m_Advance_Ratio.append(m_pBladeData->advance_ratio);
                m_pTBEMData->m_Eta.append(m_pBladeData->eta);

                double bending = 0;
                for (int d=0;d<m_pBladeData->m_Reynolds.size();d++)
                {
                    m_pBladeData->m_Reynolds[d] = pow((pow(windspeed*(1+m_pBladeData->m_a_axial.at(d)),2)+pow(windspeed*m_pBladeData->m_lambda_local.at(d)*(1-m_pBladeData->m_a_radial.at(d)),2)),0.5)*m_pBladeData->m_c_local[d]/dlg_visc*m_pTBEMData->rho;
                    m_pBladeData->m_DeltaReynolds[d] = m_pBladeData->m_DeltaReynolds[d]-m_pBladeData->m_Reynolds[d];
                    m_pBladeData->m_Roughness[d] = 1000*100*dlg_visc/m_pTBEMData->rho/pow((pow(windspeed*(1+m_pBladeData->m_a_axial.at(d)),2)+pow(windspeed*m_pBladeData->m_lambda_local.at(d)*(1-m_pBladeData->m_a_radial.at(d)),2)),0.5);
                    m_pBladeData->m_Windspeed[d] = pow((pow(windspeed*(1+m_pBladeData->m_a_axial.at(d)),2)+pow(windspeed*m_pBladeData->m_lambda_local.at(d)*(1-m_pBladeData->m_a_radial.at(d)),2)),0.5);
                    m_pBladeData->m_p_normal[d] = pow(m_pBladeData->m_Windspeed[d],2)*m_pTBEMData->rho*0.5*m_pBladeData->m_c_local[d]*m_pBladeData->m_Cn[d];
                    m_pBladeData->m_p_tangential[d] = pow(m_pBladeData->m_Windspeed[d],2)*m_pTBEMData->rho*0.5*m_pBladeData->m_c_local[d]*m_pBladeData->m_Ct[d];
                    bending = bending - m_pBladeData->m_p_normal.at(d)*m_pBladeData->deltas.at(d)*m_pBladeData->m_pos.at(d);
                    m_pBladeData->m_Mach[d] = (m_pBladeData->m_Windspeed[d]/1235);
                    m_pBladeData->m_circ[d] = (0.5*m_pBladeData->m_c_local.at(d)*m_pBladeData->m_CL.at(d)*m_pBladeData->m_Windspeed.at(d));
                }

                m_pTBEMData->m_Bending.append(bending);


                m_pBladeData->m_Color = pMainFrame->GetColor(10);

                m_pTurbineBData = m_pTBEMData->m_BData[0];




                CreatePowerCurves();


        }

    }



    UpdateTurbines();
    SetCurveParams();
    FillComboBoxes();


}

void QBEM::OnOptimize()
{
    MainFrame *pMainFrame = (MainFrame *) s_pMainFrame;

    OptimizeDlg OptDlg(this);
    OptDlg.move(pMainFrame->m_DlgPos);
    OptDlg.InitDialog();
    if (OptDlg.exec())
    {
    dlg_lambda = OptDlg.Lambda0->Value();
    }
}

void QBEM::OnOrtho()
{
    if (m_pctrlIsOrtho->isChecked()) m_pWing->m_bIsOrtho = true;
    else m_pWing->m_bIsOrtho = false;

    m_bResetglGeom = true;
    m_bResetglSectionHighlight = true;
//    m_pWing->CreateSurfaces(CVector(0.0,0.0,0.0), 0.0, 0.0);
    m_pWing->CreateSurfaces(CVector(0.0,0.0,0.0), 0.0, 0.0);
    ComputeGeometry();
    UpdateView();



}


void QBEM::OnCreateTurbineSimulation()
{
 QString strong, num;

 MainFrame *pMainFrame = (MainFrame *) s_pMainFrame;

 strong = m_pTData->m_TurbineName + " Simulation";

 int j=1;

 for (int i=0;i<s_poaTBEMData.size();i++)
 {
        if (strong == s_poaTBEMData.at(i)->m_SimName)
        {
        j++;
        num.sprintf("%1.0f",double(j));
        strong = m_pTData->m_TurbineName + " Simulation" + " ("+num+")";
        i=0;
        }
 }


 CreateBEMDlg pBEMDlg(this);

 pBEMDlg.SimName->setText(strong);

 if (pBEMDlg.exec())
 {

 TBEMData *pTBEMData = new TBEMData;

 pTBEMData->m_TurbineName = m_pTData->m_TurbineName;
 pTBEMData->m_SimName = pBEMDlg.SimName->text();
 pTBEMData->OuterRadius = m_pTData->OuterRadius;
 pTBEMData->relax = pBEMDlg.RelaxEdit->Value();
 pTBEMData->elements = pBEMDlg.ElementsEdit->Value();
 pTBEMData->iterations = pBEMDlg.IterationsEdit->Value();
 pTBEMData->epsilon = pBEMDlg.EpsilonEdit->Value();
 pTBEMData->m_bTipLoss = pBEMDlg.TipLossBox->isChecked();
 pTBEMData->m_bRootLoss = pBEMDlg.RootLossBox->isChecked();
 pTBEMData->m_b3DCorrection = pBEMDlg.ThreeDBox->isChecked();
 pTBEMData->m_b3DEquilibrium = pBEMDlg.ThreeDEquilibriumBox->isChecked();
 pTBEMData->m_bInterpolation = pBEMDlg.InterpolationBox->isChecked();
 pTBEMData->rho = pBEMDlg.RhoEdit->Value();
 pTBEMData->visc = pBEMDlg.ViscEdit->Value();
 pTBEMData->m_bNewRootLoss = pBEMDlg.NewRootLossBox->isChecked();
 pTBEMData->m_bNewTipLoss=pBEMDlg.NewTipLossBox->isChecked();

 pTBEMData->m_Color = pMainFrame->GetColor(8);

 s_poaTBEMData.append(pTBEMData);

 m_pTBEMData = pTBEMData;
 m_pTurbineBData = NULL;
 selected_windspeed = -1;

 dlg_rho = pTBEMData->rho;
 dlg_relax = pTBEMData->relax;
 dlg_iterations = pTBEMData->iterations;
 dlg_elements = pTBEMData->elements;
 dlg_tiploss = pTBEMData->m_bTipLoss;
 dlg_epsilon = pTBEMData->epsilon;
 dlg_rootloss = pTBEMData->m_bRootLoss;
 dlg_3dcorrection = pTBEMData->m_b3DCorrection;
 dlg_3dequilibrium = pTBEMData->m_b3DEquilibrium;
 dlg_interpolation = pTBEMData->m_bInterpolation;
 dlg_visc = pTBEMData->visc;
 dlg_newrootloss = pTBEMData->m_bNewRootLoss;
 dlg_newtiploss = pTBEMData->m_bNewTipLoss;

 CheckButtons();
 UpdateTurbines();
 InitTurbineSimulationParams(m_pTBEMData);
 }



}




void QBEM::OnCurveColor()
{
        bool bOK;
        QRgb rgb = m_CurveColor.rgba();
        rgb = QColorDialog::getRgba(rgb, &bOK);
        m_CurveColor = QColor::fromRgba(rgb);

        FillComboBoxes();

        UpdateCurve();
}

void QBEM::OnCurveStyle(int index)
{
        m_CurveStyle = index;
        FillComboBoxes();
        UpdateCurve();
}
void QBEM::OnCurveWidth(int index)
{
        m_CurveWidth = index+1;
        FillComboBoxes();
        UpdateCurve();
}





void QBEM::OnShowPoints()
{
        SimuWidget *pSimuWidget = (SimuWidget *) m_pSimuWidget;
        MainFrame *pMainFrame = (MainFrame*)s_pMainFrame;

        if(m_iView == CharView)
        {
                if (m_pBEMData)
                {
                        m_pBEMData->m_bShowPoints = pSimuWidget->m_pctrlShowPoints->isChecked();
                }
                CreateRotorCurves();
        }
        else if (m_iView == PowerView)
        {
            if (m_pTBEMData)
            {
                m_pTBEMData->m_bShowPoints = pSimuWidget->m_pctrlShowPoints->isChecked();
            }
                CreatePowerCurves();
        }

        pMainFrame->SetSaveState(false);
        UpdateView();
}

void QBEM::OnShowCurve()
{
        //user has toggled visible switch
        SimuWidget *pSimuWidget = (SimuWidget *) m_pSimuWidget;
        MainFrame *pMainFrame = (MainFrame*)s_pMainFrame;

        if(m_iView == CharView)
        {
                if (m_pBEMData)
                {
                        m_pBEMData->m_bIsVisible = pSimuWidget->m_pctrlShowCurve->isChecked();

                }
                CreateRotorCurves();
        }
        else if (m_iView == PowerView)
        {
            if (m_pTBEMData)
            {
                m_pTBEMData->m_bIsVisible = pSimuWidget->m_pctrlShowCurve->isChecked();
            }
                CreatePowerCurves();
        }
        pMainFrame->SetSaveState(false);
        UpdateView();
}

void QBEM::OnShowOpPoint()
{
        //user has toggled visible switch
        SimuWidget *pSimuWidget = (SimuWidget *) m_pSimuWidget;

        m_bShowOpPoint = pSimuWidget->m_pctrlShowOpPoint->isChecked();


        if(m_iView == CharView)
        {
                CreateRotorCurves();
        }
        else if (m_iView == PowerView)
        {
                CreatePowerCurves();
        }
        UpdateView();

}






void QBEM::OnBladeGraph()
{
m_pCurGraph->m_Type = 1;
m_pCurGraph->SetXVariable(12);
m_pCurGraph->SetYVariable(2);

m_pCurGraph->SetAutoX(true);
m_pCurGraph->SetAutoY(true);

SetGraphTitles(m_pCurGraph);
SetPowerGraphTitles(m_pCurGraph);


CreateRotorCurves();
CreatePowerCurves();
CreatePolarCurve();
}

void QBEM::OnRotorGraph()
{
m_pCurGraph->m_Type = 0;
m_pCurGraph->SetXVariable(2);
m_pCurGraph->SetYVariable(0);

m_pCurGraph->SetAutoX(true);
m_pCurGraph->SetAutoY(true);

SetGraphTitles(m_pCurGraph);
SetPowerGraphTitles(m_pCurGraph);

CreateRotorCurves();
CreatePowerCurves();
}

void QBEM::OnShowAllRotorCurves()
{
    if (m_iView == CharView)
    {
        for (int i=0; i< s_poaBEMData.size();i++)
        {
            s_poaBEMData.at(i)->m_bIsVisible = true;
        }
    }
    if (m_iView == PowerView)
    {
        for( int i=0;i<s_poaTBEMData.size();i++)
        {
            s_poaTBEMData.at(i)->m_bIsVisible = true;
        }
    }

    CreateRotorCurves();
    CreatePowerCurves();
    SetCurveParams();
}

void QBEM::OnHideAllRotorCurves()
{
    if (m_iView == CharView)
    {
        for (int i=0; i< s_poaBEMData.size();i++)
        {
            s_poaBEMData.at(i)->m_bIsVisible = false;
        }
    }
    if (m_iView == PowerView)
    {
        for (int i=0;i<s_poaTBEMData.size();i++)
        {
            s_poaTBEMData.at(i)->m_bIsVisible = false;
        }
    }

    CreateRotorCurves();
    CreatePowerCurves();
    SetCurveParams();
}

void QBEM::OnIsolateCurrentBladeCurve()
{
    MainFrame *pMainFrame = (MainFrame *) s_pMainFrame;

    if (m_bIsolateBladeCurve)
    {
       pMainFrame->IsolateCurrentBladeCurveAct->setChecked(false);
       m_bIsolateBladeCurve = false;
    }
    else
    {
       pMainFrame->IsolateCurrentBladeCurveAct->setChecked(true);
       m_bIsolateBladeCurve = true;
    }
    CreateRotorCurves();
    CreatePowerCurves();

}

void QBEM::OnCompareIsolatedBladeCurves()
{
    MainFrame *pMainFrame = (MainFrame *) s_pMainFrame;

    if (m_bCompareBladeCurve)
    {
       pMainFrame->CompareCurrentBladeCurveAct->setChecked(false);
       m_bCompareBladeCurve = false;
    }
    else
    {
       pMainFrame->CompareCurrentBladeCurveAct->setChecked(true);
       m_bCompareBladeCurve = true;
    }
    CreateRotorCurves();
    CreatePowerCurves();
}

void QBEM::OnDeleteRotorSim()
{
    if(m_pBEMData)
    {
        for (int i=0;i<s_poaBEMData.size();i++)
        {
            if(s_poaBEMData.at(i)->m_BEMName == m_pBEMData->m_BEMName)
            {
               for (int j=0;j<s_poaBEMData.at(i)->m_BData.size();j++)
               {
               delete s_poaBEMData.at(i)->m_BData.at(j);
               }
               delete s_poaBEMData.at(i);
               s_poaBEMData.removeAt(i);
               i--;
            }
        }
        m_pBEMData = NULL;
        UpdateWings();
    }

}


void QBEM::OnDeleteTurbineSim()
{
    if(m_pTBEMData)
    {
        for (int i=0;i<s_poaTBEMData.size();i++)
        {
            if(s_poaTBEMData.at(i)->m_SimName == m_pTBEMData->m_SimName)
            {
               for (int j=0;j<s_poaTBEMData.at(i)->m_BData.size();j++)
               {
               delete s_poaTBEMData.at(i)->m_BData.at(j);
               }
               delete s_poaTBEMData.at(i);
               s_poaTBEMData.removeAt(i);
               i--;
            }
        }
        m_pTBEMData = NULL;
        UpdateTurbines();
    }


}
void QBEM::OnSetWeibullA(double A)
{
    MainFrame *pMainFrame = (MainFrame *) s_pMainFrame;
    double K,V,f,energy = 0;

    K=m_pctrlk->value();

    if (m_pTBEMData)
    {

        m_pTBEMData->A=A;

        m_pTBEMData->m_Weibull.clear();
        m_pTBEMData->m_WeibullV3.clear();


        for (int i=0;i<m_pTBEMData->m_V.size();i++)
        {
           V=m_pTBEMData->m_V.at(i);

           f=K/A*pow((V/A),(K-1))*exp(-pow((V/A),K));
           m_pTBEMData->m_Weibull.append(f);
           m_pTBEMData->m_WeibullV3.append(f*V*V);

        }

        for (int i=0;i<m_pTBEMData->m_V.size()-1;i++)
        {
            f = exp(-pow(m_pTBEMData->m_V.at(i)/A,K))-exp(-pow(m_pTBEMData->m_V.at(i+1)/A,K));

            energy = energy + 0.5*(m_pTBEMData->m_P.at(i)+m_pTBEMData->m_P.at(i+1))*f*8760;
        }

        QString yield,str;
        GetPowerUnit(str, pMainFrame->m_PowerUnit);
        yield.sprintf("%.0f",energy*pMainFrame->m_WtoUnit);
        m_pctrlYield->setText(yield+" "+str+"h");

        CreatePowerCurves();
    }
}

void QBEM::OnSetWeibullK(double K)
{
    MainFrame *pMainFrame = (MainFrame *) s_pMainFrame;
    double A,V,f,energy=0;

    A=m_pctrla->value();

    if (m_pTBEMData)
    {

        m_pTBEMData->K=K;

        m_pTBEMData->m_Weibull.clear();
        m_pTBEMData->m_WeibullV3.clear();


        for (int i=0;i<m_pTBEMData->m_V.size();i++)
        {
           V=m_pTBEMData->m_V.at(i);

           f=K/A*pow((V/A),(K-1))*exp(-pow((V/A),K));
           m_pTBEMData->m_Weibull.append(f);
           m_pTBEMData->m_WeibullV3.append(f*V*V);
        }

        for (int i=0;i<m_pTBEMData->m_V.size()-1;i++)
        {
            f = exp(-pow(m_pTBEMData->m_V.at(i)/A,K))-exp(-pow(m_pTBEMData->m_V.at(i+1)/A,K));

            energy = energy + 0.5*(m_pTBEMData->m_P.at(i)+m_pTBEMData->m_P.at(i+1))*f*8760;
        }

        QString yield,str;
        GetPowerUnit(str, pMainFrame->m_PowerUnit);
        yield.sprintf("%.0f",energy*pMainFrame->m_WtoUnit);
        m_pctrlYield->setText(yield+" "+str+"h");

        CreatePowerCurves();
    }
}

void QBEM::OnSetCD90(double val)
{
    m_CD90 = val;

    if (m_bNew360Polar)
    {
    Compute360Polar();
    CreatePolarCurve();
    }

    if (m_pCur360Polar->m_PlrName == m_cylPolarName)
    {
    m_pCur360Polar->m_Cd.clear();
    for (int i=0;i<m_pCur360Polar->m_Alpha.size();i++)
    {
    m_pCur360Polar->m_Cd.append(val);
    }
    m_pCur360Polar->m_XTop = m_CD90;
    CreatePolarCurve();
    }
UpdateView();
}

//void QBEM::OnSetD_Cl(double val2)
//{
//    m_d_cl = val2;

//    if (m_bNew360Polar)
//    {
//    Compute360Polar();
//    CreatePolarCurve();
//    }
//}

void QBEM::OnDiscardWing()
{
    m_WingEdited = false;
    delete m_pWing;
    m_pWing = NULL;
    UpdateWings();
    EnableAllButtons();
    CheckButtons();
}

void QBEM::OnDiscardTurbine()
{
    m_TurbineEdited = false;

    EnableAllButtons();
    UpdateTurbines();
    CheckButtons();
}

void QBEM::OnScaleBlade()
{

    MainFrame *pMainFrame = (MainFrame *) s_pMainFrame;

    BladeScaleDlg dlg;
    dlg.move(pMainFrame->m_DlgPos);
    dlg.s_pMainFrame = s_pMainFrame;
    dlg.InitDialog(m_pWing->m_TPos[m_pWing->m_NPanel], m_pWing->m_TChord[m_pWing->m_NPanel], m_pWing->m_TTwist[m_pWing->m_NPanel]);

    if(QDialog::Accepted == dlg.exec())
    {
            if (dlg.m_bSpan || dlg.m_bChord || dlg.m_bTwist)
            {
                    if(m_pWing)
                    {
                            if(dlg.m_bSpan)  m_pWing->ScaleSpan(dlg.m_NewSpan*2);
                            if(dlg.m_bChord) m_pWing->ScaleChord(dlg.m_NewChord);
                            if(dlg.m_bTwist) m_pWing->ScaleTwist(dlg.m_NewTwist);
                    }

            }

            m_pctrlHubRadius->SetValue(m_pWing->m_TPos[0]*pMainFrame->m_mtoUnit);
            FillDataTable();
            m_bChanged = true;
            m_bResetglGeom = true;
            m_bResetglSectionHighlight = true;
            ComputeGeometry();
            UpdateView();
    }


}
void QBEM::OnBladeStructure()
{

        MainFrame *pMainFrame = (MainFrame *) s_pMainFrame;

        BladeStructureDlg Strdlg(this);
        Strdlg.move(pMainFrame->m_DlgPos);
        //dlg.s_pMainFrame = s_pMainFrame;
        Strdlg.InitDialog();
        Strdlg.exec();

//        if(QDialog::Accepted == Strdlg.exec())
//        {
//          //  m_bNewMaterial = true;

//        }

}

void QBEM::OnComparePolars()
{
    m_bComparePolarCurves = m_ComparePolars->isChecked();

    CreatePolarCurve();
}


void QBEM::OnLoadCylindricFoil()
{
    MainFrame *pMainFrame = (MainFrame *) s_pMainFrame;



    m_cylName = "circle";

    for (int i=0;i<s_poaFoil->size();i++)
    {
    CFoil *pFoil = (CFoil *) s_poaFoil->at(i);
    if (pFoil->m_FoilName == m_cylName) return;
    }

    QDir circle;
    if (!circle.exists("circle.dat")) return;
    circle.currentPath();
    QString strong = circle.currentPath()+"/circle.dat";


    //////
    QFile XFile(strong);
    if (!XFile.open(QIODevice::ReadOnly))
    {
            QString strange = tr("Could not read the file\n")+strong;
            QMessageBox::information(window(), tr("Info"), strange);
            return;
    }

    QXDirect * pXDirect = (QXDirect*)s_pXDirect;

            QTextStream ar(&XFile);
            CFoil *pFoil = pMainFrame->ReadFoilFile(ar);
            XFile.close();

            if(pFoil)
            {
                    pMainFrame->AddFoil(pFoil);
                    g_pCurFoil  = pFoil;
                    pXDirect->m_pCurPolar = NULL;
                    pXDirect->m_pCurOpp   = NULL;
                    g_pCurFoil = pXDirect->SetFoil(pFoil);
                    pXDirect->SetPolar();
                    QAFoil *pAFoil= (QAFoil*)s_pAFoil;
                    pAFoil->SelectFoil(pFoil);
                    XFile.close();
                    pMainFrame->SetSaveState(false);
                    pXDirect->SetControls();
            }


    //

    CPolar *pPolar = new CPolar;

    pPolar->m_FoilName = m_cylName;

    pPolar->m_PlrName = m_cylName +" empty Polar";

    s_poaPolar->append(pPolar);

    pPolar = new CPolar;

    pPolar->m_ASpec = 0;

    pPolar->m_ACrit = 0;

    pPolar->m_FoilName = m_cylName;

    m_cylPolarName = m_cylName + " 360° Polar";

    pPolar->m_PlrName = m_cylPolarName;

    pPolar->m_ParentPlrName = m_cylName +" empty Polar";

    for (int i=-180;i<=180;i++)
    {
        pPolar->m_Alpha.append(i);
        pPolar->m_Cd.append(1);
        pPolar->m_Cl.append(0);
    }
    pPolar->m_Color = QColor(255,0,0);


    s_poa360Polar->append(pPolar);

    UpdateFoils();


}




void QBEM::OnExportGeometry()
{
if (m_pWing)
    {

        MainFrame *pMainFrame = (MainFrame *) s_pMainFrame;

        QString FileName;
        QString SelectedFilter;
        QFileDialog::Options options;
        int type;


        FileName = m_pWing->m_WingName;
        FileName.replace("/", " ");
        FileName = QFileDialog::getSaveFileName(this, tr("Export Blade Geometry"), pMainFrame->m_LastDirName,
                                                                                        tr("STL File (*.stl);;Coordinates in Text File (*.txt)"),
                                                                                        &SelectedFilter, options);

        if(!FileName.length()) return;

        int pos;
        pos = FileName.lastIndexOf("/");
        if(pos>0) pMainFrame->m_LastDirName = FileName.left(pos);

        pos = FileName.indexOf(".stl");
        if(pos>0) type=1; else type=0;



        QFile XFile(FileName);

        if (!XFile.open(QIODevice::WriteOnly | QIODevice::Text)) return ;

        QTextStream out(&XFile);
        QString strong;

        double x, xp;
        CVector Pt, PtNormal, A,B,C,D,BD,AC,N;
        int j,l;
        int num_tri = 100;

        static double  xDistrib[500];
        double xx;
        double param = 50;// increase to refine L.E. and T.E.
        for(int i=0; i<num_tri; i++)
        {
                xx = (double)i/(double)(num_tri-1);
                xDistrib[i] = (asinh(param*(xx-0.5))/asinh(param/2.)+1.)/2.;
        }


        if (type == 1)
        {

        out << "solid " <<m_pWing->m_WingName <<"\n";

        // create the trinangles for the blade

        for (j=0; j<m_pWing->m_NSurfaces; j++)
        {


                        for (l=0; l<num_tri-1; l++)
                        {
                                //top surface
                                x= xDistrib[l];
                                xp = xDistrib[l+1];

                                m_pWing->m_Surface[j].GetPoint(x,x,0.0,Pt, PtNormal,1);
                                strong = QString("%1 %2 %3\n").arg(PtNormal.x,14,'e',5).arg(PtNormal.y,14,'e',5).arg(PtNormal.z,14,'e',5);
                                out << "facet normal "+strong;

                                out << "outer loop\n";

                                strong = QString("%1 %2 %3\n").arg(Pt.x+1,14,'e',5).arg(Pt.y,14,'e',5).arg(Pt.z+1,14,'e',5);
                                out << "vertex " + strong;

                                m_pWing->m_Surface[j].GetPoint(xp,xp,1.0,Pt, PtNormal,1);
                                strong = QString("%1 %2 %3\n").arg(Pt.x+1,14,'e',5).arg(Pt.y,14,'e',5).arg(Pt.z+1,14,'e',5);
                                out << "vertex " + strong;

                                m_pWing->m_Surface[j].GetPoint(x,x,1.0,Pt, PtNormal,1);
                                strong = QString("%1 %2 %3\n").arg(Pt.x+1,14,'e',5).arg(Pt.y,14,'e',5).arg(Pt.z+1,14,'e',5);
                                out << "vertex " + strong;

                                out << "endloop\nendfacet\n";


                                m_pWing->m_Surface[j].GetPoint(xp,xp,1.0,Pt, PtNormal,1);
                                strong = QString("%1 %2 %3\n").arg(PtNormal.x,14,'e',5).arg(PtNormal.y,14,'e',5).arg(PtNormal.z,14,'e',5);
                                out << "facet normal "+strong;

                                out << "outer loop\n";

                                strong = QString("%1 %2 %3\n").arg(Pt.x+1,14,'e',5).arg(Pt.y,14,'e',5).arg(Pt.z+1,14,'e',5);
                                out << "vertex " + strong;

                                m_pWing->m_Surface[j].GetPoint(x,x,0.0,Pt, PtNormal,1);
                                strong = QString("%1 %2 %3\n").arg(Pt.x+1,14,'e',5).arg(Pt.y,14,'e',5).arg(Pt.z+1,14,'e',5);
                                out << "vertex " + strong;

                                m_pWing->m_Surface[j].GetPoint(xp,xp,0.0,Pt, PtNormal,1);
                                strong = QString("%1 %2 %3\n").arg(Pt.x+1,14,'e',5).arg(Pt.y,14,'e',5).arg(Pt.z+1,14,'e',5);
                                out << "vertex " + strong;

                                out << "endloop\nendfacet\n";

                        }

                        for (l=0; l<num_tri-1; l++)
                        {
                        //bottom surface
                                x= xDistrib[l];
                                xp = xDistrib[l+1];

                                m_pWing->m_Surface[j].GetPoint(x,x,0.0,Pt, PtNormal,-1);
                                strong = QString("%1 %2 %3\n").arg(PtNormal.x,14,'e',5).arg(PtNormal.y,14,'e',5).arg(PtNormal.z,14,'e',5);
                                out << "facet normal "+strong;

                                out << "outer loop\n";

                                strong = QString("%1 %2 %3\n").arg(Pt.x+1,14,'e',5).arg(Pt.y,14,'e',5).arg(Pt.z+1,14,'e',5);
                                out << "vertex " + strong;

                                m_pWing->m_Surface[j].GetPoint(x,x,1.0,Pt, PtNormal,-1);
                                strong = QString("%1 %2 %3\n").arg(Pt.x+1,14,'e',5).arg(Pt.y,14,'e',5).arg(Pt.z+1,14,'e',5);
                                out << "vertex " + strong;

                                m_pWing->m_Surface[j].GetPoint(xp,xp,1.0,Pt, PtNormal,-1);
                                strong = QString("%1 %2 %3\n").arg(Pt.x+1,14,'e',5).arg(Pt.y,14,'e',5).arg(Pt.z+1,14,'e',5);
                                out << "vertex " + strong;

                                out << "endloop\nendfacet\n";


                                m_pWing->m_Surface[j].GetPoint(xp,xp,1.0,Pt, PtNormal,-1);
                                strong = QString("%1 %2 %3\n").arg(PtNormal.x,14,'e',5).arg(PtNormal.y,14,'e',5).arg(PtNormal.z,14,'e',5);
                                out << "facet normal "+strong;

                                out << "outer loop\n";

                                strong = QString("%1 %2 %3\n").arg(Pt.x+1,14,'e',5).arg(Pt.y,14,'e',5).arg(Pt.z+1,14,'e',5);
                                out << "vertex " + strong;

                                m_pWing->m_Surface[j].GetPoint(xp,xp,0.0,Pt, PtNormal,-1);
                                strong = QString("%1 %2 %3\n").arg(Pt.x+1,14,'e',5).arg(Pt.y,14,'e',5).arg(Pt.z+1,14,'e',5);
                                out << "vertex " + strong;

                                m_pWing->m_Surface[j].GetPoint(x,x,0.0,Pt, PtNormal,-1);
                                strong = QString("%1 %2 %3\n").arg(Pt.x+1,14,'e',5).arg(Pt.y,14,'e',5).arg(Pt.z+1,14,'e',5);
                                out << "vertex " + strong;

                                out << "endloop\nendfacet\n";

                        }

                        //////now check for a gap at the TE, if there is one close it!

                        x=xDistrib[num_tri-1];

                        m_pWing->m_Surface[j].GetPoint(x,x,0.0,A, PtNormal,1);
                        m_pWing->m_Surface[j].GetPoint(x,x,0.0,B, PtNormal,-1);
                        m_pWing->m_Surface[j].GetPoint(x,x,1.0,C, PtNormal,1);
                        m_pWing->m_Surface[j].GetPoint(x,x,1.0,D, PtNormal,-1);


                        if (CVector(A-B).VAbs()>0.001 || CVector(C-D).VAbs()>0.001)
                        {

                            N = CVector(A-D)*CVector(B-C);
                            N.Normalize();

                            strong = QString("%1 %2 %3\n").arg(N.x,14,'e',5).arg(N.y,14,'e',5).arg(N.z,14,'e',5);
                            out << "facet normal "+strong;

                            out << "outer loop\n";

                            strong = QString("%1 %2 %3\n").arg(A.x+1,14,'e',5).arg(A.y,14,'e',5).arg(A.z+1,14,'e',5);
                            out << "vertex " + strong;

                            m_pWing->m_Surface[j].GetPoint(x,x,0.0,Pt, PtNormal,-1);
                            strong = QString("%1 %2 %3\n").arg(B.x+1,14,'e',5).arg(B.y,14,'e',5).arg(B.z+1,14,'e',5);
                            out << "vertex " + strong;

                            m_pWing->m_Surface[j].GetPoint(xp,xp,0.0,Pt, PtNormal,-1);
                            strong = QString("%1 %2 %3\n").arg(D.x+1,14,'e',5).arg(D.y,14,'e',5).arg(D.z+1,14,'e',5);
                            out << "vertex " + strong;

                            out << "endloop\nendfacet\n";


                            strong = QString("%1 %2 %3\n").arg(N.x,14,'e',5).arg(N.y,14,'e',5).arg(N.z,14,'e',5);

                            out << "facet normal "+strong;
                            out << "outer loop\n";

                            strong = QString("%1 %2 %3\n").arg(A.x+1,14,'e',5).arg(A.y,14,'e',5).arg(A.z+1,14,'e',5);
                            out << "vertex " + strong;

                            m_pWing->m_Surface[j].GetPoint(x,x,0.0,Pt, PtNormal,-1);
                            strong = QString("%1 %2 %3\n").arg(D.x+1,14,'e',5).arg(D.y,14,'e',5).arg(D.z+1,14,'e',5);
                            out << "vertex " + strong;

                            m_pWing->m_Surface[j].GetPoint(xp,xp,0.0,Pt, PtNormal,-1);
                            strong = QString("%1 %2 %3\n").arg(C.x+1,14,'e',5).arg(C.y,14,'e',5).arg(C.z+1,14,'e',5);
                            out << "vertex " + strong;

                            out << "endloop\nendfacet\n";

                        }

        }
                    ///////hub surface triangles
                    j=0;

                    m_pWing->m_Surface[j].GetPanel(0, 0, BOTSURFACE);
                    C. Copy(m_pWing->m_Surface[0].LA);
                    D. Copy(m_pWing->m_Surface[0].TA);
                    m_pWing->m_Surface[j].GetPanel(0, 0, TOPSURFACE);
                    A. Copy(m_pWing->m_Surface[0].TA);
                    B. Copy(m_pWing->m_Surface[0].LA);

                    BD = D-B;
                    AC = C-A;
                    N  = AC*BD;
                    N.Normalize();

                    for (l=0; l<num_tri-1; l++)
                    {

                        x= xDistrib[l];
                        xp = xDistrib[l+1];

                        m_pWing->m_Surface[j].GetPoint(x,x,0.0,Pt, PtNormal,1);
                        strong = QString("%1 %2 %3\n").arg(N.x,14,'e',5).arg(N.y,14,'e',5).arg(N.z,14,'e',5);

                        out << "facet normal "+strong;
                        out << "outer loop\n";

                        strong = QString("%1 %2 %3\n").arg(Pt.x+1,14,'e',5).arg(Pt.y,14,'e',5).arg(Pt.z+1,14,'e',5);
                        out << "vertex " + strong;

                        m_pWing->m_Surface[j].GetPoint(x,x,0.0,Pt, PtNormal,-1);
                        strong = QString("%1 %2 %3\n").arg(Pt.x+1,14,'e',5).arg(Pt.y,14,'e',5).arg(Pt.z+1,14,'e',5);
                        out << "vertex " + strong;

                        m_pWing->m_Surface[j].GetPoint(xp,xp,0.0,Pt, PtNormal,-1);
                        strong = QString("%1 %2 %3\n").arg(Pt.x+1,14,'e',5).arg(Pt.y,14,'e',5).arg(Pt.z+1,14,'e',5);
                        out << "vertex " + strong;

                        out << "endloop\nendfacet\n";


                        m_pWing->m_Surface[j].GetPoint(x,x,0.0,Pt, PtNormal,1);
                        strong = QString("%1 %2 %3\n").arg(N.x,14,'e',5).arg(N.y,14,'e',5).arg(N.z,14,'e',5);
                        out << "facet normal "+strong;

                        out << "outer loop\n";
                        strong = QString("%1 %2 %3\n").arg(Pt.x+1,14,'e',5).arg(Pt.y,14,'e',5).arg(Pt.z+1,14,'e',5);
                        out << "vertex " + strong;

                        m_pWing->m_Surface[j].GetPoint(xp,xp,0.0,Pt, PtNormal,-1);
                        strong = QString("%1 %2 %3\n").arg(Pt.x+1,14,'e',5).arg(Pt.y,14,'e',5).arg(Pt.z+1,14,'e',5);
                        out << "vertex " + strong;

                        m_pWing->m_Surface[j].GetPoint(xp,xp,0.0,Pt, PtNormal,1);
                        strong = QString("%1 %2 %3\n").arg(Pt.x+1,14,'e',5).arg(Pt.y,14,'e',5).arg(Pt.z+1,14,'e',5);
                        out << "vertex " + strong;

                        out << "endloop\nendfacet\n";

                    }

                    ///////right tip surface triangles

                    j= m_pWing->m_NSurfaces-1;

                    for (l=0; l<num_tri-1; l++)
                    {
                        x= xDistrib[l];
                        xp = xDistrib[l+1];

                        m_pWing->m_Surface[j].GetPoint(x,x,1.0,Pt, PtNormal,1);
                        strong = QString("%1 %2 %3\n").arg(-N.x,14,'e',5).arg(-N.y,14,'e',5).arg(-N.z,14,'e',5);

                        out << "facet normal "+strong;
                        out << "outer loop\n";

                        strong = QString("%1 %2 %3\n").arg(Pt.x+1,14,'e',5).arg(Pt.y,14,'e',5).arg(Pt.z+1,14,'e',5);
                        out << "vertex " + strong;

                        m_pWing->m_Surface[j].GetPoint(xp,xp,1.0,Pt, PtNormal,-1);
                        strong = QString("%1 %2 %3\n").arg(Pt.x+1,14,'e',5).arg(Pt.y,14,'e',5).arg(Pt.z+1,14,'e',5);
                        out << "vertex " + strong;

                        m_pWing->m_Surface[j].GetPoint(x,x,1.0,Pt, PtNormal,-1);
                        strong = QString("%1 %2 %3\n").arg(Pt.x+1,14,'e',5).arg(Pt.y,14,'e',5).arg(Pt.z+1,14,'e',5);
                        out << "vertex " + strong;

                        out << "endloop\nendfacet\n";



                        m_pWing->m_Surface[j].GetPoint(x,x,1.0,Pt, PtNormal,1);
                        strong = QString("%1 %2 %3\n").arg(N.x,14,'e',5).arg(N.y,14,'e',5).arg(N.z,14,'e',5);

                        out << "facet normal "+strong;
                        out << "outer loop\n";

                        strong = QString("%1 %2 %3\n").arg(Pt.x+1,14,'e',5).arg(Pt.y,14,'e',5).arg(Pt.z+1,14,'e',5);
                        out << "vertex " + strong;

                        m_pWing->m_Surface[j].GetPoint(xp,xp,1.0,Pt, PtNormal,1);
                        strong = QString("%1 %2 %3\n").arg(Pt.x+1,14,'e',5).arg(Pt.y,14,'e',5).arg(Pt.z+1,14,'e',5);
                        out << "vertex " + strong;

                        m_pWing->m_Surface[j].GetPoint(xp,xp,1.0,Pt, PtNormal,-1);
                        strong = QString("%1 %2 %3\n").arg(Pt.x+1,14,'e',5).arg(Pt.y,14,'e',5).arg(Pt.z+1,14,'e',5);
                        out << "vertex " + strong;

                        out << "endloop\nendfacet\n";
                    }


        out << "endsolid "<<m_pWing->m_WingName <<"\n";;

        }
        else
        {

            out << m_pWing->m_WingName +"\n";
            out << "             x                       y                       z\n";

            for (int i=0; i<m_pWing->m_NSurfaces;i++)
            {

                for (int j=0;j<num_tri;j++)
                {
                x= xDistrib[j];
                m_pWing->m_Surface[i].GetPoint(x,x,0.0,Pt, PtNormal,1);

                strong = QString("%1          %2          %3\n").arg(Pt.x,14,'e',5).arg(Pt.y,14,'e',5).arg(Pt.z,14,'e',5);

                out << strong;
                }

                out << "\n";

                if (i == m_pWing->m_NSurfaces-1)
                {
                    for (int j=0;j<num_tri;j++)
                    {
                    x= xDistrib[j];
                    m_pWing->m_Surface[i].GetPoint(x,x,1.0,Pt, PtNormal,1);

                    strong = QString("%1          %2          %3\n").arg(Pt.x,14,'e',5).arg(Pt.y,14,'e',5).arg(Pt.z,14,'e',5);

                    out << strong;
                    }
                }

        }
        }

        XFile.close();
    }

}


void QBEM::OnEditCur360Polar()
{



        if (!m_pCurPolar) return;

        if (m_iView != PolarView) On360View();

        MainFrame* pMainFrame = (MainFrame*)s_pMainFrame;

        CPolar MemPolar;


        for (int i=0; i<m_pCur360Polar->m_Alpha.size();i++)
        {
            MemPolar.m_Alpha.append(m_pCur360Polar->m_Alpha.at(i));
            MemPolar.m_Cl.append(m_pCur360Polar->m_Cl.at(i));
            MemPolar.m_Cd.append(m_pCur360Polar->m_Cd.at(i));
        }



        Edit360PolarDlg dlg;
        dlg.m_pPolar = m_pCur360Polar;
        dlg.m_pBEM = this;
        dlg.InitDialog();

        bool bPoints = m_pCur360Polar->m_bShowPoints;
        m_pCur360Polar->m_bShowPoints = true;

        CreatePolarCurve();
        UpdateView();

        if(dlg.exec() == QDialog::Accepted)
        {
                pMainFrame->SetSaveState(false);
        }
        else
        {

                m_pCur360Polar->m_Alpha.clear();
                m_pCur360Polar->m_Cl.clear();
                m_pCur360Polar->m_Cd.clear();
                    for (int i=0; i<MemPolar.m_Alpha.size();i++)
                    {
                        m_pCur360Polar->m_Alpha.append(MemPolar.m_Alpha.at(i));
                        m_pCur360Polar->m_Cl.append(MemPolar.m_Cl.at(i));
                        m_pCur360Polar->m_Cd.append(MemPolar.m_Cd.at(i));

                    }





        }
        m_pCur360Polar->m_bShowPoints = bPoints;
        CreatePolarCurve();
        UpdateView();
}









void QBEM::OnHideWidgets()
{
    MainFrame *pMainFrame = (MainFrame *) s_pMainFrame;

    if (m_bHideWidgets)
    {
        pMainFrame->m_pctrlHideWidgets->setChecked(false);
        pMainFrame->m_pctrlHideWidgets2->setChecked(false);
        pMainFrame->m_pctrlHideWidgets3->setChecked(false);
        m_bHideWidgets = false;
    }
    else
    {
        pMainFrame->m_pctrlHideWidgets->setChecked(true);
        pMainFrame->m_pctrlHideWidgets2->setChecked(true);
        pMainFrame->m_pctrlHideWidgets3->setChecked(true);
        m_bHideWidgets = true;
    }

    CheckButtons();

}






void QBEM::OnChangeCoordinates()
{

        if (m_pctrlBladeCoordinates->isChecked())
        {
            m_bAbsoluteBlade=false;
        }
        else
        {
            m_bAbsoluteBlade = true;
        }

        FillDataTable();


        UpdateView();
}


void QBEM::On3DReset()
{
        m_glViewportTrans.Set(0.0, 0.0, 0.0);
        Set3DScale();
        UpdateView();
}

void QBEM::OnCreateRotorSimulation()
{

 QString strong, num;



 MainFrame *pMainFrame = (MainFrame *) s_pMainFrame;

 CreateBEMDlg pBEMDlg(this);

 strong = m_pWing->m_WingName + " Simulation";

 int j=1;

 for (int i=0;i<s_poaBEMData.size();i++)
 {
        if (strong == s_poaBEMData.at(i)->m_BEMName)
        {
        j++;
        num.sprintf("%1.0f",double(j));
        strong = m_pWing->m_WingName + " Simulation" + " ("+num+")";
        i=0;
        }
 }

 pBEMDlg.SimName->setText(strong);

 if (pBEMDlg.exec())
 {
 BEMData *pBEMData = new BEMData;


 pBEMData->elements = pBEMDlg.ElementsEdit->Value();
 pBEMData->iterations = pBEMDlg.IterationsEdit->Value();
 pBEMData->epsilon = pBEMDlg.EpsilonEdit->Value();
 pBEMData->m_bTipLoss = pBEMDlg.TipLossBox->isChecked();
 pBEMData->m_bRootLoss = pBEMDlg.RootLossBox->isChecked();
 pBEMData->m_b3DCorrection = pBEMDlg.ThreeDBox->isChecked();
 pBEMData->m_b3DEquilibrium = pBEMDlg.ThreeDEquilibriumBox->isChecked();
 pBEMData->m_bInterpolation = pBEMDlg.InterpolationBox->isChecked();
 pBEMData->relax = pBEMDlg.RelaxEdit->Value();
 pBEMData->m_Color = pMainFrame->GetColor(7);
 pBEMData->m_WingName = m_pWing->m_WingName;
 pBEMData->m_BEMName = pBEMDlg.SimName->text();
 pBEMData->visc = pBEMDlg.ViscEdit->Value();
 pBEMData->m_bNewRootLoss = pBEMDlg.NewRootLossBox->isChecked();
 pBEMData->m_bNewTipLoss=pBEMDlg.NewTipLossBox->isChecked();
 s_poaBEMData.append(pBEMData);
 m_pBEMData = pBEMData;

 //////set the selected values as standart values for next definition of a simulation///
 dlg_rho = pBEMData->rho;
 dlg_relax = pBEMData->relax;
 dlg_iterations = pBEMData->iterations;
 dlg_elements = pBEMData->elements;
 dlg_tiploss = pBEMData->m_bTipLoss;
 dlg_epsilon = pBEMData->epsilon;
 dlg_rootloss = pBEMData->m_bRootLoss;
 dlg_3dcorrection = pBEMData->m_b3DCorrection;
 dlg_3dequilibrium = pBEMData->m_b3DEquilibrium;
 dlg_interpolation = pBEMData->m_bInterpolation;
 dlg_visc = pBEMData->visc;
 dlg_newrootloss = pBEMData->m_bNewRootLoss;
 dlg_newtiploss = pBEMData->m_bNewTipLoss;
 ////
 CheckButtons();
 UpdateRotorSimulation();
 }



}

void QBEM::OnCellChanged()
{
    if (m_WingEdited)
    {
        m_bChanged = true;
        ReadParams();
    }
}

void QBEM::OnDeleteSection()
{
        if(m_iSection <0 || m_iSection>m_pWing->m_NPanel) return;

        if(m_iSection==0)
        {
                QMessageBox::warning(this, tr("Warning"),tr("The first section cannot be deleted"));
                return;
        }

        int ny, k, size;

        size = m_pWingModel->rowCount();
        if(size<=2) return;
        int n=m_iSection;
        ny = m_pWing->m_NYPanels[m_iSection-1] + m_pWing->m_NYPanels[m_iSection];

        for (k=m_iSection; k<size; k++)
        {
                m_pWing->m_TRelPos[k]      = m_pWing->m_TRelPos[k+1];
                m_pWing->m_TChord[k]    = m_pWing->m_TChord[k+1];
                m_pWing->m_TOffset[k]   = m_pWing->m_TOffset[k+1];
                m_pWing->m_TTwist[k]     = m_pWing->m_TTwist[k+1];
                m_pWing->m_TDihedral[k]  = m_pWing->m_TDihedral[k+1];
                m_pWing->m_NXPanels[k]   = m_pWing->m_NXPanels[k+1];
                m_pWing->m_NYPanels[k]   = m_pWing->m_NYPanels[k+1];
                m_pWing->m_XPanelDist[k] = m_pWing->m_XPanelDist[k+1];
                m_pWing->m_YPanelDist[k] = m_pWing->m_YPanelDist[k+1];
                m_pWing->m_RFoil[k]      = m_pWing->m_RFoil[k+1];
                m_pWing->m_LFoil[k]      = m_pWing->m_LFoil[k+1];
                m_pWing->m_TPos[k]      = m_pWing->m_TPos[k+1];
                m_pWing->m_TPAxisX[k] =   m_pWing->m_TPAxisX[k+1];
                m_pWing->m_TPAxisZ[k] =   m_pWing->m_TPAxisZ[k+1];
                m_pWing->m_TFoilPAxisX[k] = m_pWing->m_TFoilPAxisX[k+1];
                m_pWing->m_TFoilPAxisZ[k] = m_pWing->m_TFoilPAxisZ[k+1];
        }
        m_pWing->m_NPanel--;

        m_pWing->m_NYPanels[m_iSection-1] = ny;
        m_pWing->m_Polar.removeAt(n);
        FillDataTable();
        ComputeGeometry();
        m_bChanged = true;
        ReadParams();
}

void QBEM::OnInsertBefore()
{
        if(m_iSection <0 || m_iSection>m_pWing->m_NPanel) return;

        if (m_pWing->m_NPanel==VLMMAXMATSIZE-1)
        {
                QMessageBox::warning(this, tr("Warning"), tr("The maximum number of panels has been reached"));
                return;
        }
        if(m_iSection<=0)
        {
                QMessageBox::warning(this, tr("Warning"), tr("No insertion possible before the first section"));
                return;
        }
        int k,n,ny;

        n  = m_iSection;
        for (k=m_pWing->m_NPanel; k>=n; k--)
        {
                m_pWing->m_TRelPos[k+1]      = m_pWing->m_TRelPos[k];
                m_pWing->m_TChord[k+1]    = m_pWing->m_TChord[k];
                m_pWing->m_TOffset[k+1]   = m_pWing->m_TOffset[k];
                m_pWing->m_TTwist[k+1]     = m_pWing->m_TTwist[k];
                m_pWing->m_TDihedral[k+1]  = m_pWing->m_TDihedral[k];
                m_pWing->m_NXPanels[k+1]   = m_pWing->m_NXPanels[k];
                m_pWing->m_NYPanels[k+1]   = m_pWing->m_NYPanels[k];
                m_pWing->m_XPanelDist[k+1] = m_pWing->m_XPanelDist[k];
                m_pWing->m_YPanelDist[k+1] = m_pWing->m_YPanelDist[k];
                m_pWing->m_RFoil[k+1]      = m_pWing->m_RFoil[k];
                m_pWing->m_LFoil[k+1]      = m_pWing->m_LFoil[k];
                m_pWing->m_TPos[k+1]      = m_pWing->m_TPos[k];
                m_pWing->m_TPAxisX[k+1] =   m_pWing->m_TPAxisX[k];
                m_pWing->m_TPAxisZ[k+1] =   m_pWing->m_TPAxisZ[k];
                m_pWing->m_TFoilPAxisX[k+1] = m_pWing->m_TFoilPAxisX[k];
                m_pWing->m_TFoilPAxisZ[k+1] = m_pWing->m_TFoilPAxisZ[k];
        }

        ny = m_pWing->m_NYPanels[n-1];
        m_pWing->m_TRelPos[n]    = (m_pWing->m_TRelPos[n+1]    + m_pWing->m_TRelPos[n-1])   /2.0;
        m_pWing->m_TChord[n]  = (m_pWing->m_TChord[n+1]  + m_pWing->m_TChord[n-1]) /2.0;
        m_pWing->m_TOffset[n] = 0;//(m_pWing->m_TOffset[n+1] + m_pWing->m_TOffset[n-1])/2.0;

        m_pWing->m_TPos[n]    = (m_pWing->m_TPos[n+1]    + m_pWing->m_TPos[n-1])   /2.0;
        m_pWing->m_TPAxisX[n] = (m_pWing->m_TPAxisX[n+1]+m_pWing->m_TPAxisX[n-1]) /2.0;
        m_pWing->m_TPAxisZ[n] = (m_pWing->m_TPAxisZ[n+1]+m_pWing->m_TPAxisZ[n-1]) / 2.0;
        m_pWing->m_TFoilPAxisX[n] = (m_pWing->m_TFoilPAxisX[n+1]+ m_pWing->m_TFoilPAxisX[n-1]) /2.0;
        m_pWing->m_TFoilPAxisZ[n] = (m_pWing->m_TFoilPAxisZ[n+1] + m_pWing->m_TFoilPAxisZ[n-1]) / 2.0;

        m_pWing->m_NXPanels[n]   = m_pWing->m_NXPanels[n-1];
        m_pWing->m_NYPanels[n]   = (int)(ny/2);
        m_pWing->m_NYPanels[n-1] = ny-m_pWing->m_NYPanels[n];
        if(m_pWing->m_NYPanels[n]==0)   m_pWing->m_NYPanels[n]++;
        if(m_pWing->m_NYPanels[n-1]==0) m_pWing->m_NYPanels[n-1]++;

        m_pWing->m_NPanel++;
        m_pWing->m_Polar.insert(n,"");;

        FillDataTable();
        ComputeGeometry();

        //SetWingData();

        m_bChanged = true;
        m_bResetglSectionHighlight = true;
        ReadParams();
}

void QBEM::OnInsertAfter()
{
        if(m_iSection <0 || m_iSection>m_pWing->m_NPanel) return;
        if (m_pWing->m_NPanel==VLMMAXMATSIZE-1)
        {
                QMessageBox::warning(this, tr("Warning"), tr("The maximum number of panels has been reached"));
                return;
        }
        int k,n,ny;

        n  = m_iSection;

        if(n<0) n=m_pWing->m_NPanel;
        ny = m_pWing->m_NYPanels[n];


        for (k=m_pWing->m_NPanel+1; k>n; k--)
        {
                m_pWing->m_TRelPos[k]       = m_pWing->m_TRelPos[k-1];
                m_pWing->m_TChord[k]     = m_pWing->m_TChord[k-1];
                m_pWing->m_TOffset[k]    = m_pWing->m_TOffset[k-1];
                m_pWing->m_TTwist[k]     = m_pWing->m_TTwist[k-1];
                m_pWing->m_TDihedral[k]  = m_pWing->m_TDihedral[k-1];
                m_pWing->m_NXPanels[k]   = m_pWing->m_NXPanels[k-1];
                m_pWing->m_NYPanels[k]   = m_pWing->m_NYPanels[k-1];
                m_pWing->m_XPanelDist[k] = m_pWing->m_XPanelDist[k-1];
                m_pWing->m_YPanelDist[k] = m_pWing->m_YPanelDist[k-1];
                m_pWing->m_RFoil[k]      = m_pWing->m_RFoil[k-1];
                m_pWing->m_LFoil[k]      = m_pWing->m_LFoil[k-1];

                m_pWing->m_TPos[k]      = m_pWing->m_TPos[k-1];
                m_pWing->m_TPAxisX[k] =   m_pWing->m_TPAxisX[k-1];
                m_pWing->m_TPAxisZ[k] =   m_pWing->m_TPAxisZ[k-1];
                m_pWing->m_TFoilPAxisX[k] = m_pWing->m_TFoilPAxisX[k-1];
                m_pWing->m_TFoilPAxisZ[k] = m_pWing->m_TFoilPAxisZ[k-1];
        }

        if(n<m_pWing->m_NPanel)
        {
                m_pWing->m_TRelPos[n+1]    = (m_pWing->m_TRelPos[n]    + m_pWing->m_TRelPos[n+2])   /2.0;
                m_pWing->m_TChord[n+1]  = (m_pWing->m_TChord[n]  + m_pWing->m_TChord[n+2]) /2.0;
                m_pWing->m_TOffset[n+1] = (m_pWing->m_TOffset[n] + m_pWing->m_TOffset[n+2])/2.0;

                m_pWing->m_TPos[n+1]    = (m_pWing->m_TPos[n]    + m_pWing->m_TPos[n+2])   /2.0;
                m_pWing->m_TPAxisX[n+1] = (m_pWing->m_TPAxisX[n]+m_pWing->m_TPAxisX[n+2]) /2.0;
                m_pWing->m_TPAxisZ[n+1] = (m_pWing->m_TPAxisZ[n]+m_pWing->m_TPAxisZ[n+2]) / 2.0;
                m_pWing->m_TFoilPAxisX[n+1] = (m_pWing->m_TFoilPAxisX[n]+ m_pWing->m_TFoilPAxisX[n+2]) /2.0;
                m_pWing->m_TFoilPAxisZ[n+1] = (m_pWing->m_TFoilPAxisZ[n] + m_pWing->m_TFoilPAxisZ[n+2]) / 2.0;
        }
        else
        {
                m_pWing->m_TRelPos[n+1]     = m_pWing->m_TRelPos[n+1]*1.1;
                m_pWing->m_TChord[n+1]   = m_pWing->m_TChord[n+1]/1.1;
                m_pWing->m_TOffset[n+1]  = 0;//m_pWing->m_TOffset[n+1] + m_pWing->m_TChord[n] - m_pWing->m_TChord[n+1] ;
        }

        m_pWing->m_TTwist[n+1]     = m_pWing->m_TTwist[n];
        m_pWing->m_TDihedral[n+1]  = m_pWing->m_TDihedral[n];
        m_pWing->m_NXPanels[n+1]   = m_pWing->m_NXPanels[n];
        m_pWing->m_NYPanels[n+1]   = m_pWing->m_NYPanels[n];
        m_pWing->m_XPanelDist[n+1] = m_pWing->m_XPanelDist[n];
        m_pWing->m_YPanelDist[n+1] = m_pWing->m_YPanelDist[n];
        m_pWing->m_RFoil[n+1]      = m_pWing->m_RFoil[n];
        m_pWing->m_LFoil[n+1]      = m_pWing->m_LFoil[n];       

        m_pWing->m_NYPanels[n+1] = qMax(1,(int)(ny/2));
        m_pWing->m_NYPanels[n]   = qMax(1,ny-m_pWing->m_NYPanels[n+1]);

        m_pWing->m_NPanel++;


        m_pWing->m_Polar.insert(n+1,"");;
        FillDataTable();
        ComputeGeometry();
        //SetWingData();
        m_bChanged = true;
        ReadParams();
}

void QBEM::OnItemClicked(const QModelIndex &index)
{
        if(index.row()>m_pWing->m_NPanel)
        {
                //the user has filled a cell in the last line
                if(index.row()<VLMMAXMATSIZE-1)
                {
                        //so add an item before reading
                        m_pWing->m_NPanel++;
                        m_pWingModel->setRowCount(m_pWing->m_NPanel+2);
                        FillTableRow(m_pWing->m_NPanel);
                }
        }
        SetCurrentSection(index.row());

        UpdateView();
        CheckWing();



}

void QBEM::OnNewTurbine()
{

        QString str;
        MainFrame *pMainFrame = (MainFrame *) s_pMainFrame;
        GetPowerUnit(str,pMainFrame->m_PowerUnit);
        power1->setText(str);
        power2->setText(str);
        GetSpeedUnit(str, pMainFrame->m_SpeedUnit);
        speed1->setText(str);
        speed2->setText(str);
        speed3->setText(str);


        m_TurbineEdited = true;


        CheckButtons();
        DisableAllButtons();

        m_pctrlStall->setChecked(true);
        m_pctrlFixed->setChecked(true);
        CheckTurbineButtons();
        m_pctrlTurbineName->setText("New Propeller");
        CBlade *pWing;
        WingSelection->clear();
        for (int i=0;i < s_poaBEMWings->size();i++)
        {
            pWing = (CBlade *) s_poaBEMWings->at(i);
            WingSelection->addItem(pWing->m_WingName);
        }


}

void QBEM::OnEditTurbine()
{

QString str;
MainFrame *pMainFrame = (MainFrame *) s_pMainFrame;
GetPowerUnit(str,pMainFrame->m_PowerUnit);
power1->setText(str);
power2->setText(str);
GetSpeedUnit(str, pMainFrame->m_SpeedUnit);
speed1->setText(str);
speed2->setText(str);
speed3->setText(str);



if (!m_pTData) return;

if (m_iView != PowerView) OnPowerView();
m_TurbineEdited = true;

CheckButtons();
DisableAllButtons();

m_pctrlTurbineName->setText(m_pTData->m_TurbineName);

m_pctrlStall->setChecked(m_pTData->isStall);
m_pctrlPitch->setChecked(m_pTData->isPitch);
m_pctrlFixed->setChecked(m_pTData->isFixed);
m_pctrl2Step->setChecked(m_pTData->is2Step);
m_pctrlVariable->setChecked(m_pTData->isVariable);

m_pctrlCutIn->SetValue(m_pTData->CutIn*pMainFrame->m_mstoUnit);
m_pctrlCutOut->SetValue(m_pTData->CutOut*pMainFrame->m_mstoUnit);
m_pctrlSwitch->SetValue(m_pTData->Switch*pMainFrame->m_mstoUnit);

m_pctrlRot1->SetValue(m_pTData->Rot1);
m_pctrlRot2->SetValue(m_pTData->Rot2);
m_pctrlLambda->SetValue(m_pTData->Lambda0);
m_pctrlGenerator->SetValue(m_pTData->Generator*pMainFrame->m_WtoUnit);
m_pctrlFixedPitch->SetValue(m_pTData->FixedPitch);

m_pctrlVariableLosses->SetValue(m_pTData->VariableLosses);
m_pctrlFixedLosses->SetValue(m_pTData->FixedLosses*pMainFrame->m_WtoUnit);


CBlade *pWing;
WingSelection->clear();
for (int i=0;i < s_poaBEMWings->size();i++)
{
    pWing = (CBlade *) s_poaBEMWings->at(i);
    WingSelection->addItem(pWing->m_WingName);
}

int pos = WingSelection->findText(m_pTData->m_WingName);
WingSelection->setCurrentIndex(pos);

CheckTurbineButtons();


}

void QBEM::OnDeleteTurbine()
{
    QMessageBox msgBox;
    msgBox.setText(tr("Do you want to Delete this Turbine?"));
    msgBox.setInformativeText(tr("This will delete associated Simulation Data too!!"));
    QPushButton *okButton = msgBox.addButton(tr("Delete"), QMessageBox::ActionRole);
    QPushButton *cancelButton = msgBox.addButton(tr("Cancel"), QMessageBox::ActionRole);


    msgBox.exec();

    if (msgBox.clickedButton() == okButton)
    {
        for (int i=0;i<s_poaTBEMData.size();i++)
        {
            if (s_poaTBEMData.at(i)->m_TurbineName == m_pTData->m_TurbineName)
            {
                for (int j=0;j<s_poaTBEMData.at(i)->m_BData.size();j++)
                {
                    delete s_poaTBEMData.at(i)->m_BData.at(j);
                }
                delete s_poaTBEMData.at(i);
                s_poaTBEMData.removeAt(i);
                i--;
            }
        }

        for (int i=0;i<s_poaTData.size();i++)
        {
            if (s_poaTData.at(i)->m_TurbineName == m_pTData->m_TurbineName)
            {
                delete s_poaTData.at(i);
                s_poaTData.removeAt(i);
            }
        }

        m_pTData = NULL;

        UpdateTurbines();
    }
    if (msgBox.clickedButton() == cancelButton)
    {
        return;
    }

}

void QBEM::OnSaveTurbine()
{
        MainFrame *pMainFrame = (MainFrame *) s_pMainFrame;

        bool bExists = false;
        TData *pTData = new TData;
        CBlade *pWing;

        pWing=GetWing(WingSelection->currentText());


        pTData->m_TurbineName = m_pctrlTurbineName->text();
        pTData->m_WingName = pWing->m_WingName;
        pTData->OuterRadius = pWing->m_TPos[pWing->m_NPanel];
        pTData->Generator = m_pctrlGenerator->Value()/pMainFrame->m_WtoUnit;
        pTData->CutIn = m_pctrlCutIn->Value()/pMainFrame->m_mstoUnit;
        pTData->CutOut = m_pctrlCutOut->Value()/pMainFrame->m_mstoUnit;
        pTData->Lambda0 = m_pctrlLambda->Value();
        pTData->Rot1 = m_pctrlRot1->Value();
        pTData->Rot2 = m_pctrlRot2->Value();
        pTData->Switch = m_pctrlSwitch->Value()/pMainFrame->m_mstoUnit;
        pTData->is2Step = m_pctrl2Step->isChecked();
        pTData->isFixed = m_pctrlFixed->isChecked();
        pTData->isVariable = m_pctrlVariable->isChecked();
        pTData->isPitch = m_pctrlPitch->isChecked();
        pTData->isStall = m_pctrlStall->isChecked();
        pTData->FixedLosses = m_pctrlFixedLosses->Value()/pMainFrame->m_WtoUnit;
        pTData->VariableLosses = m_pctrlVariableLosses->Value();
        pTData->FixedPitch = m_pctrlFixedPitch->Value();



        for (int i=0;i<s_poaTData.size();i++)
        {
            if (s_poaTData.at(i)->m_TurbineName==pTData->m_TurbineName) bExists=true;
        }

        if (bExists)
        {
            if (!SetModTurbine(pTData)) return;
        }

        s_poaTData.append(pTData);

        m_pTData = pTData;

        InitTurbineData(m_pTData);
        m_TurbineEdited = false;

        EnableAllButtons();
        UpdateTurbines();
        CheckButtons();
        CreatePowerCurves();


}

void QBEM::OnNew360Polar()
{

    MainFrame *pMainFrame = (MainFrame *) s_pMainFrame;
    CPolar *pPolar = new CPolar;
    QString strong, num;


    strong = m_pFoil->m_FoilName + " 360° Polar";

    int j=1;

    for (int i=0;i<s_poa360Polar->size();i++)
    {
        CPolar *pPolar = (CPolar *) s_poa360Polar->at(i);
           if (strong == pPolar->m_PlrName)
           {
           j++;
           num.sprintf("%1.0f",double(j));
           strong = m_pFoil->m_FoilName + " 360° Polar" + " ("+num+")";
           i=0;
           }
    }

    m_360Name->setText(strong);


    pPolar->m_FoilName=m_pFoil->m_FoilName;
    pPolar->m_ParentPlrName=m_pCurPolar->m_PlrName;
    pPolar->m_Color =  pMainFrame->GetColor(11);

    pPolar->m_PlrName = strong;

    m_pCur360Polar = pPolar;

    Compute360Polar();

    CreatePolarCurve();

    m_bNew360Polar = true;

    m_pctrlA->setValue(0);


    CheckButtons();
    SetCurveParams();
    FillComboBoxes();





}

void QBEM::OnAdvancedDesign()
{
        m_bAdvancedEdit = true;
        InitAdvancedDialog(m_pWing);
        mainWidget->setCurrentIndex(0);
        bladeWidget->setCurrentIndex(2);

}

void QBEM::OnNewWing()
{
        MainFrame *pMainFrame = (MainFrame *) s_pMainFrame;
        QString strong;

        pitch_old = 0;
        pitch_new = 0;
        m_pctrlPitchBlade->setValue(0);

        m_WingEdited = true;

        DisableAllButtons();

        CBlade *pWing = new CBlade;

        for (int i=0;i<2;i++) pWing->m_Polar.append("");

        pWing->m_WingName = "New Blade";

        m_pctrlHubRadius->SetValue(pWing->m_HubRadius * pMainFrame->m_mtoUnit);

        m_pWing=pWing;

        m_pctrlIsOrtho->setChecked(false);

        InitDialog(pWing);

        mainWidget->setCurrentIndex(0);
        bladeWidget->setCurrentIndex(1);



}

void QBEM::OnEditWing()
{

        pitch_old = 0;
        pitch_new = 0;
        m_pctrlPitchBlade->setValue(0);

        if (!m_pWing) return;       

        DisableAllButtons();

        if (m_iView != WingView) OnWingView();

        MainFrame *pMainFrame = (MainFrame *) s_pMainFrame;

        m_WingEdited = true;



        CBlade *pWing = new CBlade;

        pWing->Duplicate(m_pWing);

        m_pctrlHubRadius->SetValue(pWing->m_HubRadius * pMainFrame->m_mtoUnit);

        m_pctrlIsOrtho->setChecked(m_pWing->m_bIsOrtho);

        InitDialog(pWing);

        mainWidget->setCurrentIndex(0);
        bladeWidget->setCurrentIndex(1);



}

void QBEM::OnDeleteWing()
{
    QMessageBox msgBox;
    msgBox.setText(tr("Do you want to Delete this Blade?"));
    msgBox.setInformativeText(tr("This will delete associated Simulation Data too!!"));
    QPushButton *okButton = msgBox.addButton(tr("Delete"), QMessageBox::ActionRole);
    QPushButton *cancelButton = msgBox.addButton(tr("Cancel"), QMessageBox::ActionRole);


    msgBox.exec();

    if (msgBox.clickedButton() == okButton)
    {

        ////Delete Turbine Sims
        for (int i=0;i<s_poaTData.size();i++)
        {
            if (s_poaTData.at(i)->m_WingName == m_pWing->m_WingName)
            {
                for (int j=0; j<s_poaTBEMData.size();j++)
                {
                    if (s_poaTBEMData.at(j)->m_TurbineName == s_poaTData.at(i)->m_TurbineName)
                    {
                        for (int l=0;l<s_poaTBEMData.at(j)->m_BData.size();l++)
                        {
                            delete s_poaTBEMData.at(j)->m_BData.at(l);
                        }

                        delete s_poaTBEMData.at(j);
                        s_poaTBEMData.removeAt(j);
                        j--;
                    }
                }

                delete s_poaTData.at(i);
                s_poaTData.removeAt(i);
                i--;
            }
        }


        ////Delete Rotor Sims
        for (int i=0; i<s_poaBEMData.size();i++)
        {
            if (s_poaBEMData.at(i)->m_WingName == m_pWing->m_WingName)
            {
                for (int j=0; j < s_poaBEMData.at(i)->m_BData.size();j++)
                {
                    delete s_poaBEMData.at(i)->m_BData.at(j);
                }

            delete s_poaBEMData.at(i);
            s_poaBEMData.removeAt(i);
            i--;

            }
        }



        for (int i=0;i<s_poaBEMWings->size();i++)
        {
            CBlade *pWing = (CBlade *) s_poaBEMWings->at(i);
            if (pWing->m_WingName == m_pWing->m_WingName)
            {
                s_poaBEMWings->removeAt(i);
                delete pWing;
                break;
            }
        }

        m_pWing         = NULL;
        m_pBData        = NULL;
        m_pTurbineBData = NULL;
        m_pBEMData      = NULL;
        m_pTData        = NULL;
        m_pTBEMData     = NULL;

        UpdateWings();
        UpdateTurbines();


    }
    if (msgBox.clickedButton() == cancelButton)
    {
        return;
    }




}

void QBEM::OnDelete360Polar()
{


    QMessageBox msgBox;
    msgBox.setText(tr("Do you really want to Delete this Polar?"));
    msgBox.setInformativeText(tr("This will delete associated Blades and Simulation Data too!!!"));
    QPushButton *okButton = msgBox.addButton(tr("Delete"), QMessageBox::ActionRole);
    QPushButton *cancelButton = msgBox.addButton(tr("Cancel"), QMessageBox::ActionRole);


    msgBox.exec();

    if (msgBox.clickedButton() == okButton)
    {

    if (m_pCur360Polar)
    {

    for (int i=0;i<s_poaBEMWings->size();i++)
    {

        CBlade *pWing = (CBlade *) s_poaBEMWings->at(i);

        for (int j=0;j<pWing->m_Polar.size();j++)
        {
            if(pWing->m_Polar.at(j) == m_pCur360Polar->m_PlrName)
            {
                DeleteWing(pWing);
                i--;
                break;
            }
        }

    }


    for (int i=0;i<s_poa360Polar->size();i++)
    {
        CPolar *pPolar = (CPolar *) s_poa360Polar->at(i);

        if (m_pCur360Polar->m_PlrName == pPolar->m_PlrName)
        {
            delete pPolar;
            s_poa360Polar->removeAt(i);
        }

    }


    m_pCur360Polar = NULL;

    UpdatePolars();
    CheckButtons();
    }
    }
    else if (msgBox.clickedButton() == cancelButton)
    {
     return;
    }
}

void QBEM::OnSave360Polar()
{
    bool NameExists = false;


    CPolar *pPolar = new CPolar;

    pPolar->m_Alpha.clear();
    pPolar->m_Cl.clear();
    pPolar->m_Cd.clear();

    cd_360.clear();
    Cd_tot.clear();

    pPolar->m_Color= m_pCur360Polar->m_Color;
    pPolar->m_Style= m_pCur360Polar->m_Style;
    pPolar->m_Width= m_pCur360Polar->m_Width;


    pPolar->m_bIsVisible = true;
    pPolar->m_PlrName = m_360Name->text();
    pPolar->m_FoilName = m_pFoil->m_FoilName;
    pPolar->m_ParentPlrName = m_pCurPolar->m_PlrName;
    pPolar->m_Reynolds = m_pCurPolar->m_Reynolds;


    for (int i=0; i<s_poa360Polar->size();i++)
    {
       CPolar *cPolar = (CPolar *) s_poa360Polar->at(i);
       if (cPolar->m_PlrName == pPolar->m_PlrName) NameExists = true;
    }

    if(NameExists)
    {
        QMessageBox msgBox;
        msgBox.setText(tr("There exists a 360° Polar with the same name"));
        msgBox.setInformativeText(tr("Please change the name"));
        QPushButton *okButton = msgBox.addButton(tr("Ok"), QMessageBox::ActionRole);

        msgBox.exec();

        if (msgBox.clickedButton() == okButton)
        {
        return;
        }
    }

    m_bNew360Polar = false;

        pPolar->m_XTop = m_CD90;

     for (int i=0; i<m_pCurPolar->m_Alpha.size(); i++)
       {
           if (i<(m_pCurPolar->m_Alpha.size()-m_cd_360.size()))
           {
               double fgh = 1.0;
               cd_360.append(fgh);
           }
           else
           {
               cd_360.append(m_cd_360.at(i-(m_pCurPolar->m_Alpha.size()-m_cd_360.size())));
           }
       }

      double aa_function;


    for (int i=0; i<m_pCurPolar->m_Alpha.size(); i++)
    {
        if (m_pCurPolar->m_Alpha.at(i)<alpha_ast)
        {
             aa_function = 1.0;
        }
        else
       {
            aa_function = (alpha_xfoil-m_pCurPolar->m_Alpha.at(i))/(alpha_xfoil-alpha_ast);
       }

        Cd_tot.append(m_pCurPolar->m_Cd.at(i)*(aa_function) + (1-aa_function)*cd_360.at(i));
    }

    for (int i=0; i <m_pCurPolar->m_Alpha.size()-1; i++)
    {
        pPolar->m_Alpha.append(m_pCurPolar->m_Alpha.at(i));
        pPolar->m_Cl.append(m_pCurPolar->m_Cl.at(i));
        pPolar->m_Cd.append(Cd_tot.at(i));
    }

//Negative part of Polar

    int num=0;
    for (int i=0; i< m_pCur360Polar->m_Alpha.size(); i++)
    {
        if (m_pCur360Polar->m_Alpha.at(i) < pPolar->m_Alpha.at(num))
        {
            pPolar->m_Alpha.insert(num,m_pCur360Polar->m_Alpha.at(i));
           pPolar->m_Cl.insert(num,m_pCur360Polar->m_Cl.at(i));
            pPolar->m_Cd.insert(num,m_pCur360Polar->m_Cd.at(i));

            num++;
        }

 //positive part of 360 Polar

        if (m_pCur360Polar->m_Alpha.at(i) > pPolar->m_Alpha.at(pPolar->m_Alpha.size()-1))
        {
            pPolar->m_Alpha.append(m_pCur360Polar->m_Alpha.at(i));
            pPolar->m_Cl.append(m_pCur360Polar->m_Cl.at(i));
            pPolar->m_Cd.append(m_pCur360Polar->m_Cd.at(i));
        }

    }

    pPolar->m_ASpec = m_pCur360Polar->m_ASpec; // used to store the slope
    pPolar->m_ACrit = m_pCur360Polar->m_ACrit; // used to store the zero lift angle

    delete m_pCur360Polar;

    s_poa360Polar->append(pPolar);

    m_pCur360Polar = pPolar;




    Update360Polars();

    CheckButtons();

}

void QBEM::OnSaveWing()
{
    ReadParams();

    CBlade *pWing;
    CBlade *pOldWing;
    bool bExists=false;

    pWing  = m_pWing;
    pWing->blades = m_pctrlBlades->value();



    for (int i=0;i<s_poaBEMWings->size();i++)
    {
        pOldWing= (CBlade *) s_poaBEMWings->at(i);
        if (pWing->m_WingName==pOldWing->m_WingName)
            {
            bExists=true;
            break;
            }
    }

    if (bExists)
    {
        if (!SetModWing(pWing)) return;
    }

    s_poaBEMWings->append(pWing);

    m_pWing = pWing;

    m_bChanged=false;

    m_WingEdited = false;

    UpdateWings();

    EnableAllButtons();

    CheckButtons();


}




void QBEM::OnSelChangeWing(int i)
{

        // Gets the new selected wing name and notifies Miarex
        // then updates WPolar combobox
        // and selects either the current WPolar
        // or the first one in the list, if any
        MainFrame* pMainFrame = (MainFrame *) s_pMainFrame;
        QString strong;
        bool changed=false;
        if (i >=0) strong = pMainFrame->m_pctrlBEMWing->itemText(i);
        CBlade *pWing;
        for (int i=0;i<s_poaBEMWings->count();i++)
        {
            pWing=(CBlade *) s_poaBEMWings->at(i);
            if (pWing->m_WingName==strong)
            {
                m_pWing=pWing;
                changed=true;
            }
        }

        if (changed)
        {

            InitWingTable();
            SetScale();
            UpdateWings();
            CheckButtons();
            m_bChanged=false;
        }

}

void QBEM::OnSelChangeFoil(int i)
{
    QString strong;
    MainFrame *pMainFrame = (MainFrame *) s_pMainFrame;

    m_bNew360Polar=false;


    if (i>=0) strong = pMainFrame->m_pctrlBEMFoils->itemText(i);

    m_pFoil = GetFoil(strong);
    UpdateFoils();

    CheckButtons();
    SetCurveParams();





}

void QBEM::OnSelChangePolar(int i)
{

    QString strong;
    MainFrame *pMainFrame = (MainFrame *) s_pMainFrame;

    m_bNew360Polar=false;


    if (i>=0) strong = pMainFrame->m_pctrlBEMPolars->itemText(i);

    m_pCurPolar = GetPolar(m_pFoil->m_FoilName, strong);

    UpdatePolars();

    CheckButtons();
    SetCurveParams();






}

void QBEM::OnSelChange360Polar(int i)
{

    QString strong;
    MainFrame *pMainFrame = (MainFrame *) s_pMainFrame;

    m_bNew360Polar=false;



    if (i>=0) strong = pMainFrame->m_pctrlBEM360Polars->itemText(i);

    m_pCur360Polar = Get360Polar(m_pFoil->m_FoilName, strong);

    Update360Polars();

    CheckButtons();
    SetCurveParams();



}

void QBEM::OnSelChangeBladeData(int i)
{

    QString strong;
    MainFrame *pMainFrame = (MainFrame *) s_pMainFrame;

    CheckButtons();

    if (i>=0) strong = pMainFrame->m_pctrlBEMPoint->itemText(i);

    m_pBData = GetBladeData(strong);

    UpdateBladeData();

    CheckButtons();


}

void QBEM::OnSelChangeTurbineBladeData(int i)
{

    QString strong;

    MainFrame *pMainFrame = (MainFrame *) s_pMainFrame;

    if (i>=0) strong = pMainFrame->m_pctrlTurbinePoint->itemText(i);

    m_pTurbineBData = GetTurbineBladeData(strong);

    UpdateTurbineBladeData();

    CheckButtons();


}

void QBEM::OnWingView()
{
    MainFrame *pMainFrame = (MainFrame *) s_pMainFrame;
    pMainFrame->m_pctrlBEM360ToolBar->hide();
    pMainFrame->m_pctrlBEMToolBar->show();
    pMainFrame->m_pctrlBEMWidget->show();
    pMainFrame->m_pctrlBEMWidget->setMaximumWidth(700);
    pMainFrame->m_pctrlBEMWidget->setMaximumHeight(4000);
    pMainFrame->m_pctrlSimuWidget->hide();

    m_iView = WingView;
    if (!m_WingEdited) UpdateWings();
    CheckButtons();
    UpdateView();

}

void QBEM::On360View()
{
    MainFrame *pMainFrame = (MainFrame *) s_pMainFrame;
    pMainFrame->m_pctrlBEM360ToolBar->show();
    pMainFrame->m_pctrlBEMToolBar->hide();
    pMainFrame->m_pctrlBEMWidget->show();
    pMainFrame->m_pctrlBEMWidget->setMaximumWidth(200);
    pMainFrame->m_pctrlBEMWidget->setMaximumHeight(450);
    pMainFrame->m_pctrlSimuWidget->hide();
    



    m_iView = PolarView;
    if (!m_bNew360Polar) UpdateFoils();
    CheckButtons();
    UpdateView();

}

void QBEM::OnPowerView()
{
    MainFrame *pMainFrame = (MainFrame *) s_pMainFrame;
    pMainFrame->m_pctrlBEM360ToolBar->hide();
    pMainFrame->m_pctrlBEMToolBar->show();
    pMainFrame->m_pctrlBEMWidget->show();
    pMainFrame->m_pctrlBEMWidget->setMaximumWidth(300);
    pMainFrame->m_pctrlBEMWidget->setMaximumHeight(1000);
    pMainFrame->m_pctrlSimuWidget->show();
    

    int h  = m_rCltRect.height();
    int h2  = (int)(h/2);


    m_PowerLegendOffset.rx() = 10;
    m_PowerLegendOffset.ry() = h2 + 30;


    m_iView = PowerView;
    if (!m_TurbineEdited) UpdateTurbines();
    CheckButtons();
    UpdateView();




}


void QBEM::OnCharView()
{
    MainFrame *pMainFrame = (MainFrame *) s_pMainFrame;
    pMainFrame->m_pctrlBEM360ToolBar->hide();
    pMainFrame->m_pctrlBEMToolBar->show();
    pMainFrame->m_pctrlBEMWidget->hide();
    pMainFrame->m_pctrlSimuWidget->show();
    

    int h  = m_rCltRect.height();
    int h2  = (int)(h/2);


    m_CharLegendOffset.rx() = 10;
    m_CharLegendOffset.ry() = h2 + 30;



    m_iView = CharView;


    if(!m_WingEdited) UpdateWings();
    CheckButtons();
    UpdateView();


}

void QBEM::OnSelChangeRotorSimulation(int i)
{

    QString strong;
    MainFrame *pMainFrame = (MainFrame *) s_pMainFrame;


    CheckButtons();


    if (i>=0) strong = pMainFrame->m_pctrlBEMSim->itemText(i);

    m_pBEMData = GetRotorSimulation(m_pWing->m_WingName, strong);

    UpdateRotorSimulation();

    SetCurveParams();

    CheckButtons();


}

void QBEM::OnSelChangeTurbineSimulation(int i)
{

    QString strong;
    MainFrame *pMainFrame = (MainFrame *) s_pMainFrame;


    CheckButtons();


    if (i>=0) strong = pMainFrame->m_pctrlTurbineSim->itemText(i);

    m_pTBEMData = GetTurbineSimulation(m_pTData->m_TurbineName, strong);

    UpdateTurbineSimulation();

    SetCurveParams();

    CheckButtons();



}

void QBEM::OnGraphSettings()
{
        MainFrame* pMainFrame = (MainFrame*)s_pMainFrame;
        QGraph *pGraph = NULL;
        GraphDlg dlg;
        dlg.move(pMainFrame->m_DlgPos);

        pGraph = m_pCurGraph;
        if(!pGraph) return;

        if (m_iView == CharView && m_pCurGraph->m_Type == 0)  dlg.m_iGraphType = 70;
        if (m_iView == CharView && m_pCurGraph->m_Type == 1)  dlg.m_iGraphType = 71;

        if (m_iView == PowerView && m_pCurGraph->m_Type == 0) dlg.m_iGraphType = 80;
        if (m_iView == PowerView && m_pCurGraph->m_Type == 1) dlg.m_iGraphType = 81;

        if (m_iView == PolarView) dlg.m_iGraphType = 90;

        QGraph graph;
        graph.CopySettings(pGraph);
        dlg.m_pMemGraph = &graph;
        dlg.m_pGraph = pGraph;

        dlg.SetParams();
        int res = dlg.exec();
        pMainFrame->m_DlgPos = dlg.pos();

        if(res == QDialog::Accepted)
        {

                        if(&m_CharGraph1 == pGraph)
                        {
                                SetGraphTitles(&m_CharGraph1);
                        }
                        else if(&m_CharGraph2 == pGraph)
                        {
                                SetGraphTitles(&m_CharGraph2);
                        }
                        else if(&m_CharGraph3 == pGraph)
                        {
                                SetGraphTitles(&m_CharGraph3);
                        }
                        else if(&m_PowerGraph1 == pGraph)
                        {
                                SetPowerGraphTitles(&m_PowerGraph1);
                        }
                        else if(&m_PowerGraph2 == pGraph)
                        {
                                SetPowerGraphTitles(&m_PowerGraph2);
                        }
                        else if(&m_PowerGraph3 == pGraph)
                        {
                                SetPowerGraphTitles(&m_PowerGraph3);
                        }
                        else if(&m_360CLGraph == pGraph)
                        {
                                SetPolarGraphTitles(&m_360CLGraph);
                        }
                        else if(&m_360CDGraph == pGraph)
                        {
                                SetPolarGraphTitles(&m_360CDGraph);
                        }

                        if(dlg.m_bVariableChanged)
                        {
                                pGraph->SetAuto(true);
                                pGraph->SetAutoYMinUnit(true);
                        }
                        CreateRotorCurves();
                        CreatePowerCurves();
                        CreatePolarCurve();

        }
        else
        {
                pGraph->CopySettings(&graph);
        }
        UpdateView();
}

void QBEM::PitchBlade()
{
        double delta;

        pitch_new = m_pctrlPitchBlade->value();

        delta = pitch_new - pitch_old;

        for (int i=0;i<=m_pWing->m_NPanel;i++)
        {
            m_pWing->m_TTwist[i] = m_pWing->m_TTwist[i]+delta;
        }

        pitch_old = pitch_new;

        InitDialog(m_pWing);
}

void QBEM::PaintCharLegend(QPoint place, int bottom, QPainter &painter)
{
    MainFrame *pMainFrame = (MainFrame*) s_pMainFrame;

        int LegendSize, LegendWidth, ypos, x1;
        int i,j,k,l,nc,ny,nFoils;

        LegendSize = 30;
        LegendWidth = 210;

        QFont TextFont;
        painter.setFont(pMainFrame->m_TextFont);

        QFontMetrics fm(TextFont);
        ypos = fm.height();

        QPen TextPen(pMainFrame->m_TextColor);
        painter.setPen(TextPen);
        TextPen.setWidth(1);

        QStringList str; // we need to make an inventory of wings

        for (j=0; j<s_poaBEMWings->size(); j++)
        {
                CBlade *pWing = (CBlade*)s_poaBEMWings->at(j);
                for (i=0; i<s_poaBEMData.size(); i++)
                {
                        if (s_poaBEMData.at(i)->m_WingName == pWing->m_WingName && s_poaBEMData.at(i)->m_Cp.size())
                        {
                                str.append(pWing->m_WingName);
                                break;
                        }
                }// finished inventory
        }

        nFoils= str.size();

        painter.setBackgroundMode(Qt::TransparentMode);

        QPen LegendPen;
        LegendPen.setWidth(1);

        ny =0;
        for (k = 0; k<nFoils; k++)
        {
                int FoilPlrs = 0;
                for (l=0; l < s_poaBEMData.size(); l++)
                {
                        if (s_poaBEMData.at(l)->m_Cp.size() &&
                                s_poaBEMData.at(l)->m_Cp.length() &&
                                s_poaBEMData.at(l)->m_bIsVisible &&
                                s_poaBEMData.at(l)->m_WingName == str.at(k))
                                        FoilPlrs++;
                }
                if (FoilPlrs)
                {
                        int YPos = place.y() + (ny+FoilPlrs+2) * ypos;// bottom line of this foil's legend
                        if(abs(bottom) > abs(YPos))
                        {
                                ny++;
                        }
                        else if (k>0)
                        {
                        // move rigth if less than client bottom area
                                place.rx() += LegendWidth;
                                ny=1;
                        }
                        painter.setPen(TextPen);
                        painter.drawText(place.x() + (int)(0.5*LegendSize), place.y() + ypos*ny-(int)(ypos/2),
                                                         str.at(k));
                }
                for (nc=0; nc < s_poaBEMData.size(); nc++)
                {
                        if(str.at(k) == s_poaBEMData.at(nc)->m_WingName)
                        {
                                if (s_poaBEMData.at(nc)->m_Cp.size() && s_poaBEMData.at(nc)->m_WingName.length() && s_poaBEMData.at(nc)->m_bIsVisible)

                                {
                                        //is there anything to draw ?
                                        LegendPen.setColor(s_poaBEMData.at(nc)->m_Color);
                                        LegendPen.setStyle(GetStyle(s_poaBEMData.at(nc)->m_Style));
                                        LegendPen.setWidth(s_poaBEMData.at(nc)->m_Width);
                                        painter.setPen(LegendPen);

                                        painter.drawLine(place.x() + (int)(1.0*LegendSize), place.y() + (int)(1.*ypos*ny)+2,
                                                                         place.x() + (int)(2.0*LegendSize), place.y() + (int)(1.*ypos*ny)+2);
                                        if(s_poaBEMData.at(nc)->m_bShowPoints)
                                        {
                                                x1 = place.x() + (int)(1.5*LegendSize);
                                                painter.drawRect(x1-2, place.y() + (int)(1.*ypos*ny), 4, 4);
                                        }

                                        painter.setPen(TextPen);
                                        painter.drawText(place.x() + (int)(2.5*LegendSize), place.y() + (int)(1.*ypos*ny)+(int)(ypos/3),
                                                                         s_poaBEMData.at(nc)->m_BEMName);
                                        ny++ ;
                                }
                        }
                }
                if (FoilPlrs) ny++;
        }

}

void QBEM::PaintPowerLegend(QPoint place, int bottom, QPainter &painter)
{
        MainFrame *pMainFrame = (MainFrame*) s_pMainFrame;
        int LegendSize, LegendWidth, ypos, x1;
        QColor color;
        int i,j,k,l,nc,ny,nFoils;

        LegendSize = 30;
        LegendWidth = 210;

        painter.setFont(pMainFrame->m_TextFont);

        QFontMetrics fm(pMainFrame->m_TextFont);
        ypos = fm.height();

        QPen TextPen(pMainFrame->m_TextColor);
        painter.setPen(TextPen);
        TextPen.setWidth(1);

        QStringList str; // we need to make an inventory of foils

        for (j=0; j<s_poaTData.size(); j++)
        {

                for (i=0; i<s_poaTBEMData.size(); i++)
                {
                        if (s_poaTBEMData.at(i)->m_TurbineName == s_poaTData.at(j)->m_TurbineName && s_poaTBEMData.at(i)->m_P.size())
                        {
                                str.append(s_poaTData.at(j)->m_TurbineName);
                                break;
                        }
                }// finished inventory
        }

        nFoils= str.size();

        painter.setBackgroundMode(Qt::TransparentMode);

        QPen LegendPen;
        LegendPen.setWidth(1);

        ny =0;
        for (k = 0; k<nFoils; k++)
        {
                int FoilPlrs = 0;
                for (l=0; l < s_poaTBEMData.size(); l++)
                {
                        if (s_poaTBEMData.at(l)->m_P.size() &&
                                s_poaTBEMData.at(l)->m_P.length() &&
                                s_poaTBEMData.at(l)->m_bIsVisible &&
                                s_poaTBEMData.at(l)->m_TurbineName == str.at(k))
                                        FoilPlrs++;
                }
                if (FoilPlrs)
                {
                        int YPos = place.y() + (ny+FoilPlrs+2) * ypos;// bottom line of this foil's legend
                        if(abs(bottom) > abs(YPos))
                        {
                                ny++;
                        }
                        else if (k>0)
                        {
                        // move rigth if less than client bottom area
                                place.rx() += LegendWidth;
                                ny=1;
                        }
                        painter.setPen(TextPen);
                        painter.drawText(place.x() + (int)(0.5*LegendSize), place.y() + ypos*ny-(int)(ypos/2),
                                                         str.at(k));
                }
                for (nc=0; nc < s_poaTBEMData.size(); nc++)
                {
                        if(str.at(k) == s_poaTBEMData.at(nc)->m_TurbineName)
                        {
                                if (s_poaTBEMData.at(nc)->m_P.size() && s_poaTBEMData.at(nc)->m_TurbineName.length() && s_poaTBEMData.at(nc)->m_bIsVisible)

                                {
                                        //is there anything to draw ?
                                        LegendPen.setColor(s_poaTBEMData.at(nc)->m_Color);
                                        LegendPen.setStyle(GetStyle(s_poaTBEMData.at(nc)->m_Style));
                                        LegendPen.setWidth(s_poaTBEMData.at(nc)->m_Width);
                                        painter.setPen(LegendPen);

                                        painter.drawLine(place.x() + (int)(1.0*LegendSize), place.y() + (int)(1.*ypos*ny)+2,
                                                                         place.x() + (int)(2.0*LegendSize), place.y() + (int)(1.*ypos*ny)+2);
                                        if(s_poaTBEMData.at(nc)->m_bShowPoints)
                                        {
                                                x1 = place.x() + (int)(1.5*LegendSize);
                                                painter.drawRect(x1-2, place.y() + (int)(1.*ypos*ny), 4, 4);
                                        }

                                        painter.setPen(TextPen);
                                        painter.drawText(place.x() + (int)(2.5*LegendSize), place.y() + (int)(1.*ypos*ny)+(int)(ypos/3),
                                                                         s_poaTBEMData.at(nc)->m_SimName);
                                        ny++ ;
                                }
                        }
                }
                if (FoilPlrs) ny++;
        }

}


void QBEM::Paint360Graphs(QPainter &painter)
{
        if(!m_pCurGraph)
        {
                m_pCurGraph = &m_360CLGraph;
//		return;
        }

        int h  = m_rCltRect.height();
        int w  = m_rCltRect.width();
        int h2 = (int)(h/2);



        QRect Rect1(0,0,w,h2);
        QRect Rect2(0,h2,w,h2);
        if(w>200 && h2>250)
        {
                m_360CLGraph.DrawGraph(Rect1,painter);
                m_360CDGraph.DrawGraph(Rect2,painter);
        }
}

void QBEM::PaintCharacteristicsGraphs(QPainter &painter)
{

        if(!m_pCurGraph)
        {
                m_pCurGraph = &m_CharGraph1;
//		return;
        }

        int h  = m_rCltRect.height();
        int w  = m_rCltRect.width();
        int w2 = (int)(w/2);



        QRect Rect1(0,0,w2,m_rCltRect.bottom()/2);
        QRect Rect2(w2,0,w2,m_rCltRect.bottom()/2);
        QRect Rect3(w2,m_rCltRect.bottom()/2,w2,m_rCltRect.bottom()/2);
        QRect Rect4(0,m_rCltRect.bottom()/2,w2,m_rCltRect.bottom()/2);
        if(w2/2>100 && h/2>100)
        {
                m_CharGraph1.DrawGraph(Rect1,painter);
                m_CharGraph2.DrawGraph(Rect2,painter);
                m_CharGraph3.DrawGraph(Rect3,painter);
        }
        PaintCharLegend(m_CharLegendOffset, h, painter);

}

void QBEM::PaintPowerGraphs(QPainter &painter)
{

        if(!m_pCurGraph)
        {
                m_pCurGraph = &m_PowerGraph1;
        }

        int h  = m_rCltRect.height();
        int w  = m_rCltRect.width();
        int w2 = (int)(w/2);



        QRect Rect1(0,0,w2,m_rCltRect.bottom()/2);
        QRect Rect2(w2,0,w2,m_rCltRect.bottom()/2);
        QRect Rect3(w2,m_rCltRect.bottom()/2,w2,m_rCltRect.bottom()/2);
        QRect Rect4(0,m_rCltRect.bottom()/2,w2,m_rCltRect.bottom()/2);
        if(w2/2>100 && h/2>100)
        {
                m_PowerGraph1.DrawGraph(Rect1,painter);
                m_PowerGraph2.DrawGraph(Rect2,painter);
                m_PowerGraph3.DrawGraph(Rect3,painter);

        }

        PaintPowerLegend(m_PowerLegendOffset, h, painter);

}

void QBEM::PaintView(QPainter &painter)
{
        MainFrame* pMainFrame = (MainFrame*)s_pMainFrame;

        //Refresh the active view
        painter.fillRect(m_rCltRect, pMainFrame->m_BackgroundColor);

        if (m_iView==PolarView)
        {
                Paint360Graphs(painter);

        }
        if (m_iView == CharView)
        {
                PaintCharacteristicsGraphs(painter);
        }
        if (m_iView == PowerView)
        {
                PaintPowerGraphs(painter);
        }
}

double QBEM::PlateFlow(double alphazero,double CLzero, double alpha)
{
    double res;
    res = (1+CLzero/sin(PI/4)*sin(alpha/360*2*PI))* CD90(m_pFoil, alpha) * sin((alpha-57.6*0.08*sin(alpha/360*2*PI) - alphazero*cos(alpha/360*2*PI))/360*2*PI) * cos((alpha-57.6*0.08*sin(alpha/360*2*PI) - alphazero*cos(alpha/360*2*PI))/360*2*PI);
    return res;
}


double QBEM::PotFlow(double CLzero, double slope, double alpha)
{
   double res;
   res = CLzero+slope*alpha;
   return res;
}


void QBEM::ReadParams()
{

    if(!m_pWing) return;

        QBrush brush;

        m_pWing->m_WingName        = m_pctrlWingName->text();

//        if (!m_bAdvancedEdit)
//        {
//        //check if 2 sections are at the same position, if true - breaks!!
//        for (int i=0; i< m_pWingModel->rowCount();  i++)
//        {


//                    if (m_iSection != i && m_pWingModel->item(m_iSection,0)->text() == m_pWingModel->item(i,0)->text())
//                    {


//                        QMessageBox msgBox;
//                        msgBox.setText(tr("2 Blade Sections cant have the same radial Position"));
//                        msgBox.setInformativeText(tr("Please change one Position"));
//                        QPushButton *okButton = msgBox.addButton(tr("Ok"), QMessageBox::ActionRole);

//                        msgBox.exec();

//                        if (msgBox.clickedButton() == okButton)
//                        {

//                        return;

//                        }

//                    }

//        }
//        }
//        else
//        {
//            for (int i=0; i< m_pBladeAxisModel->rowCount();  i++)
//            {


//                        if (m_iSection != i && m_pBladeAxisModel->item(m_iSection,0)->text() == m_pBladeAxisModel->item(i,0)->text())
//                        {
//                            QMessageBox msgBox;
//                            msgBox.setText(tr("2 Blade Sections cant have the same radial Position"));
//                            msgBox.setInformativeText(tr("Please change one Position"));
//                            QPushButton *okButton = msgBox.addButton(tr("Ok"), QMessageBox::ActionRole);


//                            msgBox.exec();

//                            if (msgBox.clickedButton() == okButton)
//                            {

//                            return;

//                            }

//                        }

//            }
//        }

        if(!m_bAdvancedEdit)
        {
            for (int i=0; i< m_pWingModel->rowCount();  i++)
            {

                    ReadSectionData(i);
            }
        }
        else
        {
            for (int i=0; i< m_pBladeAxisModel->rowCount();  i++)
            {

                    ReadAdvancedSectionData(i);
            }
        }

        m_bResetglGeom = true;
        m_bResetglSectionHighlight = true;
        ComputeGeometry();
        UpdateView();





}
void QBEM::ReadAdvancedSectionData(int sel)
{

    if(sel>=m_pBladeAxisModel->rowCount()) return;
    double d;

    bool bOK;
    MainFrame *pMainFrame = (MainFrame*)s_pMainFrame;
    QString strong;
    QStandardItem *pItem;

    pItem = m_pBladeAxisModel->item(sel,0);

    strong =pItem->text();
    strong.replace(" ","");
    d =strong.toDouble(&bOK);
    if(bOK)
    {
        if (m_bAbsoluteBlade)
        {
            m_pWing->m_TRelPos[sel] =d / pMainFrame->m_mtoUnit - m_pWing->m_HubRadius;
            m_pWing->m_TPos[sel] =d / pMainFrame->m_mtoUnit;
        }
        else
        {
            m_pWing->m_TRelPos[sel] =d / pMainFrame->m_mtoUnit;
            m_pWing->m_TPos[sel] =d / pMainFrame->m_mtoUnit + m_pWing->m_HubRadius;
        }
    }

    pItem = m_pBladeAxisModel->item(sel,1);
    strong =pItem->text();
    strong.replace(" ","");
    d =strong.toDouble(&bOK);
    if(bOK) m_pWing->m_TOffset[sel] =d / pMainFrame->m_mtoUnit;

    pItem = m_pBladeAxisModel->item(sel,2);
    strong =pItem->text();
    strong.replace(" ","");
    d =strong.toDouble(&bOK);
    if(bOK) m_pWing->m_TDihedral[sel] =d;

    pItem = m_pBladeAxisModel->item(sel,3);
    strong =pItem->text();
    strong.replace(" ","");
    d =strong.toDouble(&bOK);
    if(bOK) m_pWing->m_TFoilPAxisX[sel] = d;

    pItem = m_pBladeAxisModel->item(sel,4);
    strong =pItem->text();
    strong.replace(" ","");
    d =strong.toDouble(&bOK);
    if(bOK) m_pWing->m_TFoilPAxisZ[sel] = d;
}

void QBEM::ReadSectionData(int sel)
{

        if(sel>=m_pWingModel->rowCount()) return;
        double d;

        bool bOK;
        MainFrame *pMainFrame = (MainFrame*)s_pMainFrame;
        QString strong;
        QStandardItem *pItem;

        pItem = m_pWingModel->item(sel,0);

        strong =pItem->text();
        strong.replace(" ","");
        d =strong.toDouble(&bOK);
        if(bOK)
        {
            if (m_bAbsoluteBlade)
            {
                m_pWing->m_TRelPos[sel] =d / pMainFrame->m_mtoUnit - m_pWing->m_HubRadius;
                m_pWing->m_TPos[sel] =d / pMainFrame->m_mtoUnit;
            }
            else
            {
                m_pWing->m_TRelPos[sel] =d / pMainFrame->m_mtoUnit;
                m_pWing->m_TPos[sel] =d / pMainFrame->m_mtoUnit + m_pWing->m_HubRadius;
            }
        }


        pItem = m_pWingModel->item(sel,1);
        strong =pItem->text();
        strong.replace(" ","");
        d =strong.toDouble(&bOK);
        if(bOK) m_pWing->m_TChord[sel] =d / pMainFrame->m_mtoUnit;


        pItem = m_pWingModel->item(sel,2);
        strong =pItem->text();
        strong.replace(" ","");
        d =strong.toDouble(&bOK);
        if(bOK) m_pWing->m_TTwist[sel] =d;


        pItem = m_pWingModel->item(sel,3);
        strong =pItem->text();
        m_pWing->m_RFoil[sel] = strong;
        m_pWing->m_LFoil[sel] = strong;


        QModelIndex ind;
        ind = m_pWingModel->index(sel, 4, QModelIndex());


        pItem = m_pWingModel->item(sel,4);
        strong =pItem->text();
        if (Get360Polar(m_pWing->m_LFoil[sel],strong))
        {
            if (Get360Polar(m_pWing->m_LFoil[sel],strong)->m_FoilName == m_pWing->m_LFoil[sel])
            {
            m_pWing->m_Polar.replace(sel,strong);
            }
            else
            {
                QModelIndex ind;
                ind = m_pWingModel->index(sel, 4, QModelIndex());
                m_pWingModel->setData(ind,"");
                m_pWing->m_Polar.replace(sel,"");
            }
        }
        else
        {
            QModelIndex ind;
            ind = m_pWingModel->index(sel, 4, QModelIndex());
            m_pWingModel->setData(ind,"");
            m_pWing->m_Polar.replace(sel,"");
        }

        m_pWing->blades = m_pctrlBlades->value();



        CheckWing();



}

void QBEM::SnapClient(QString const &FileName)
{
    int NbBytes, bitsPerPixel;
    MainFrame *pMainFrame = (MainFrame*)s_pMainFrame;
    GLWidget * pGLWidget = (GLWidget*)m_pGLWidget;

    QRect m_r3DCltRect;

    m_r3DCltRect = pGLWidget->geometry();

    QSize size(m_r3DCltRect.width(),m_r3DCltRect.height());
    QGLFormat GLFormat = pGLWidget->format();

    if(!GLFormat.rgba())
    {
        QMessageBox::warning(pMainFrame,tr("Warning"),tr("OpenGL color format is not recognized... Sorry"));
        return;
    }

    bitsPerPixel = 24;
    int width = size.width();
    switch(bitsPerPixel)
    {
        case 8:
        {
            QMessageBox::warning(pMainFrame,tr("Warning"),tr("Cannot (yet ?) save 8 bit depth opengl screen images... Sorry"));
            return;
        }
        case 16:
        {
            QMessageBox::warning(pMainFrame,tr("Warning"),tr("Cannot (yet ?) save 16 bit depth opengl screen images... Sorry"));
            size.setWidth(width - size.width() % 2);
            return;
        }
        case 24:
        {
            NbBytes = 4 * size.width() * size.height();//24 bits type BMP
//			size.setWidth(width - size.width() % 4);
            break;
        }
        case 32:
        {
            NbBytes = 4 * size.width() * size.height();//32 bits type BMP
            break;
        }
        default:
        {
            QMessageBox::warning(pMainFrame,tr("Warning"),tr("Unidentified bit depth... Sorry"));
            return;
        }
    }
    uchar *pPixelData = new uchar[NbBytes];

    // Copy from OpenGL
    glReadBuffer(GL_FRONT);
    switch(bitsPerPixel)
    {
        case 8: return;
        case 16: return;
        case 24:
        {
#if QT_VERSION >= 0x040400
              glReadPixels(0,0,size.width(),size.height(),GL_RGB,GL_UNSIGNED_BYTE,pPixelData);
              QImage Image(pPixelData, size.width(),size.height(), QImage::Format_RGB888);
              QImage FlippedImaged;
              FlippedImaged = Image.mirrored();	//flip vertically
              FlippedImaged.save(FileName);
#else
              QMessageBox::warning(pMainFrame,tr("Warning"),"The version of Qt used to compile the code is older than 4.4 and does not support 24 bit images... Sorry");
#endif
              break;
        }
        case 32:
        {
            glReadPixels(0,0,size.width(),size.height(),GL_RGBA,GL_UNSIGNED_BYTE,pPixelData);
            QImage Image(pPixelData, size.width(),size.height(), QImage::Format_ARGB32);
            QImage FlippedImaged;
            FlippedImaged = Image.mirrored();	//flip vertically
            FlippedImaged.save(FileName);
            break;
        }
        default: break;
    }
}



void QBEM::SetCurveParams()
{

    SimuWidget *pSimuWidget = (SimuWidget *) m_pSimuWidget;

        if(m_iView == CharView)
        {
                if(m_pBEMData)
                {
                        if(m_pBEMData->m_bIsVisible)  pSimuWidget->m_pctrlShowCurve->setChecked(true);  else  pSimuWidget->m_pctrlShowCurve->setChecked(false);
                        if(m_pBEMData->m_bShowPoints) pSimuWidget->m_pctrlShowPoints->setChecked(true); else  pSimuWidget->m_pctrlShowPoints->setChecked(false);
                        if(m_bShowOpPoint) pSimuWidget->m_pctrlShowOpPoint->setChecked(true); else  pSimuWidget->m_pctrlShowOpPoint->setChecked(false);


                        m_CurveColor = m_pBEMData->m_Color;
                        m_CurveStyle = m_pBEMData->m_Style;
                        m_CurveWidth = m_pBEMData->m_Width;
                        FillComboBoxes();
                }
                else
                {
                        FillComboBoxes(false);
                }
        }
        else if(m_iView == PolarView)
        {
                if(m_pCur360Polar)
                {


                        m_CurveColor = m_pCur360Polar->m_Color;
                        m_CurveStyle = m_pCur360Polar->m_Style;
                        m_CurveWidth = m_pCur360Polar->m_Width;
                        FillComboBoxes();
                }
                else
                {
                        FillComboBoxes(false);
                }
        }
        else
        {
                if (m_iView == PowerView)
                {
                    if(m_pTBEMData)
                    {
                            if(m_pTBEMData->m_bIsVisible)  pSimuWidget->m_pctrlShowCurve->setChecked(true);  else  pSimuWidget->m_pctrlShowCurve->setChecked(false);
                            if(m_pTBEMData->m_bShowPoints) pSimuWidget->m_pctrlShowPoints->setChecked(true); else  pSimuWidget->m_pctrlShowPoints->setChecked(false);
                            if(m_bShowOpPoint) pSimuWidget->m_pctrlShowOpPoint->setChecked(true); else  pSimuWidget->m_pctrlShowOpPoint->setChecked(false);

                            m_CurveColor = m_pTBEMData->m_Color;
                            m_CurveStyle = m_pTBEMData->m_Style;
                            m_CurveWidth = m_pTBEMData->m_Width;
                            FillComboBoxes();
                    }
                    else
                    {
                            FillComboBoxes(false);
                    }
                }
        }

}


void QBEM::SaveSettings(QSettings *pSettings)
{
        pSettings->beginGroup("XBEM");
        {
                pSettings->setValue("Lambda", dlg_lambda);
                pSettings->setValue("Blades", dlg_blades);
                pSettings->setValue("Epsilon", dlg_epsilon);
                pSettings->setValue("Interations", dlg_iterations);
                pSettings->setValue("Elements", dlg_elements);
                pSettings->setValue("Rho", dlg_rho);
                pSettings->setValue("Relax", dlg_relax);
                pSettings->setValue("TipLoss", dlg_tiploss);
                pSettings->setValue("RootLoss", dlg_rootloss);
                pSettings->setValue("3DCorrection", dlg_3dcorrection);
                pSettings->setValue("3DEquilibrium", dlg_3dequilibrium);
                pSettings->setValue("Interpolation", dlg_interpolation);
                pSettings->setValue("lambdastart", dlg_lambdastart);
                pSettings->setValue("lambdaend", dlg_lambdaend);
                pSettings->setValue("lambdadelta", dlg_lambdadelta);
                pSettings->setValue("windstart", dlg_windstart);
                pSettings->setValue("windend", dlg_windend);
                pSettings->setValue("winddelta", dlg_winddelta);
                pSettings->setValue("cylName", m_cylName);
                pSettings->setValue("cylPolarName", m_cylPolarName);
                pSettings->setValue("newtiploss", dlg_newtiploss);
                pSettings->setValue("newrootloss", dlg_newrootloss);
                pSettings->setValue("visc", dlg_visc);



        }
        pSettings->endGroup();

        m_CharGraph1.SaveSettings(pSettings);
        m_CharGraph2.SaveSettings(pSettings);
        m_CharGraph3.SaveSettings(pSettings);
        m_PowerGraph1.SaveSettings(pSettings);
        m_PowerGraph2.SaveSettings(pSettings);
        m_PowerGraph3.SaveSettings(pSettings);
        m_360CLGraph.SaveSettings(pSettings);
        m_360CDGraph.SaveSettings(pSettings);

}

void QBEM::SetupLayout()     
{

    bladeWidget = new QStackedWidget;


    QSizePolicy szPolicyExpanding;
    szPolicyExpanding.setHorizontalPolicy(QSizePolicy::Expanding);
    szPolicyExpanding.setVerticalPolicy(QSizePolicy::Expanding);

    QSizePolicy szPolicyMinimum;
    szPolicyMinimum.setHorizontalPolicy(QSizePolicy::Minimum);
    szPolicyMinimum.setVerticalPolicy(QSizePolicy::Minimum);

    QSizePolicy szPolicyMaximum;
    szPolicyMaximum.setHorizontalPolicy(QSizePolicy::Maximum);
    szPolicyMaximum.setVerticalPolicy(QSizePolicy::Maximum);




    //--------------------Wing Table Layout--------------//

    QVBoxLayout *BottomLayout = new QVBoxLayout;
    QHBoxLayout *EditNewLayout = new QHBoxLayout;

    m_pctrlWingNameLabel = new QLabel;
    m_pctrlBladesAndHubLabel = new QLabel;
    m_pctrlBladeTableView = new QTableView;

    m_pctrlBladeTableView->setSelectionMode(QAbstractItemView::NoSelection);
    m_pctrlBladeTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_pctrlBladeTableView->setMinimumWidth(500);

    m_pctrlEditWing = new QPushButton(tr("Edit Blade"));
    m_pctrlNewWing = new QPushButton(tr("New Blade"));

    BottomLayout->addWidget(m_pctrlWingNameLabel);
    BottomLayout->addWidget(m_pctrlBladesAndHubLabel);
    BottomLayout->addWidget(m_pctrlBladeTableView);

    EditNewLayout->addWidget(m_pctrlEditWing);
    EditNewLayout->addWidget(m_pctrlNewWing);

    BottomLayout->addLayout(EditNewLayout);

    QGroupBox *WingDataBox = new QGroupBox(tr("Blade Data"));
    WingDataBox->setLayout(BottomLayout);


    //-----------Wing Edit Layout-------------//
    QVBoxLayout *EditLayout = new QVBoxLayout;


    QHBoxLayout *InsertLayout = new QHBoxLayout;
    m_pctrlInsertBefore   = new QPushButton(tr("Insert Before"));
    m_pctrlInsertAfter    = new QPushButton(tr("Insert After"));
    m_pctrlDeleteSection  = new QPushButton(tr("Delete Section"));
    InsertLayout->addWidget(m_pctrlInsertBefore);
    InsertLayout->addWidget(m_pctrlInsertAfter);
    InsertLayout->addWidget(m_pctrlDeleteSection);


    QHBoxLayout *NameLayout = new QHBoxLayout;  
    m_pctrlWingName     = new QLineEdit(tr("Blade Name"));
    m_pctrlWingColor    = new ColorButton;
    m_pctrlSectionColor    = new ColorButton;
    m_pctrlSectionColor->SetColor(QColor(0,0,255));

    NameLayout->addWidget(m_pctrlWingColor);
    NameLayout->addWidget(m_pctrlWingName);
    NameLayout->addWidget(m_pctrlSectionColor);


    QHBoxLayout *ParamLayout = new QHBoxLayout;
    m_pctrlBlades = new QSpinBox;
    m_pctrlBladesLabel = new QLabel("Number of Blades");
    m_pctrlHubRadius = new FloatEdit;
    m_pctrlHubRadiusLabel = new QLabel(tr("Hub Radius"));
    m_pctrlHubRadiusUnitLabel = new QLabel;

    m_pctrlBladeCoordinates = new QCheckBox(tr("Blade Coordinates"));

    m_pctrlSolidityLabel = new QLabel;



    m_pctrlBlades->setMinimum(1);
    m_pctrlBlades->setValue(dlg_blades);

    ParamLayout->addWidget(m_pctrlBladesLabel);
    ParamLayout->addWidget(m_pctrlBlades);
    ParamLayout->addWidget(m_pctrlHubRadiusLabel);
    ParamLayout->addWidget(m_pctrlHubRadius);
    ParamLayout->addWidget(m_pctrlHubRadiusUnitLabel);
    ParamLayout->addWidget(m_pctrlBladeCoordinates);




    m_pctrlBladeTable = new QTableView(this);
    m_pctrlBladeTable->setWindowTitle(QObject::tr("Blade definition"));
    m_pctrlBladeTable->setMinimumWidth(500);
    m_pctrlBladeTable->setSelectionMode(QAbstractItemView::SingleSelection);
    m_pctrlBladeTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_pctrlBladeTable->setEditTriggers(QAbstractItemView::CurrentChanged |
                                                                              QAbstractItemView::DoubleClicked |
                                                                              QAbstractItemView::SelectedClicked |
                                                                              QAbstractItemView::EditKeyPressed);


    m_pctrlSave           = new QPushButton(tr("Save"));
    m_pctrlOptimize       = new QPushButton(tr("Optimize"));
    m_pctrlBack           = new QPushButton(tr("Back"));
    m_pctrlScale          = new QPushButton(tr("Scale"));
    m_pctrlPitchBlade     = new QDoubleSpinBox;
    m_pctrlPitchBlade->setMaximum(180);
    m_pctrlPitchBlade->setMinimum(-180);
    m_pctrlPitchBlade->setSingleStep(0.1);
    m_pctrlPitchBladeButton= new QPushButton(tr("Pitch Blade"));
    m_pctrlAdvancedDesign = new QPushButton(tr("Advanced Design"));

    QHBoxLayout *OptScale = new QHBoxLayout;
    QHBoxLayout *BackSave = new QHBoxLayout;
    QHBoxLayout *PitchBlade = new QHBoxLayout;
    QGridLayout *StrBlade = new QGridLayout;


    m_pctrlBladeMassLabel = new QLabel(tr("Mass per Blade [kg] = "));
    m_pctrlBladeMass = new QLabel;

    m_pctrlBladeVolumeLabel = new QLabel(tr("Volume per Blade [dm^3] = "));
    m_pctrlBladeVolume = new QLabel;


    m_pctrlBladeStructure = new QPushButton(tr("Blade Structure"));

    StrBlade->addWidget(m_pctrlBladeStructure,1,1);
    StrBlade->addWidget(m_pctrlBladeMassLabel,1,2);
    StrBlade->addWidget(m_pctrlBladeMass,1,3);
    StrBlade->addWidget(m_pctrlBladeVolumeLabel,2,2);
    StrBlade->addWidget(m_pctrlBladeVolume,2,3);


    QGroupBox *StrBox = new QGroupBox(tr("Modify Structure"));
    StrBox->setLayout(StrBlade);

    PitchBlade->addWidget(m_pctrlPitchBladeButton);
    PitchBlade->addWidget(m_pctrlPitchBlade);

    OptScale->addWidget(m_pctrlScale);
    OptScale->addLayout(PitchBlade);
    //OptScale->addWidget(m_pctrlOptimize);
    QGroupBox *OptBox = new QGroupBox(tr("Modify Shape"));
    OptBox->setLayout(OptScale);



    BackSave->addWidget(m_pctrlBack);
    BackSave->addWidget(m_pctrlAdvancedDesign);
    BackSave->addWidget(m_pctrlSave);

    EditLayout->addLayout(NameLayout);
    EditLayout->addLayout(ParamLayout);
    EditLayout->addWidget(m_pctrlSolidityLabel);
    EditLayout->addLayout(InsertLayout);
    EditLayout->addWidget(m_pctrlBladeTable);
    EditLayout->addWidget(OptBox);
    EditLayout->addWidget(StrBox);
    EditLayout->addLayout(BackSave);

    //---------------------Advanced Blade Design--------------------//

    QHBoxLayout *Insert2Layout = new QHBoxLayout;
    m_pctrlInsertBefore2   = new QPushButton(tr("Insert Before"));
    m_pctrlInsertAfter2    = new QPushButton(tr("Insert After"));
    m_pctrlDeleteSection2  = new QPushButton(tr("Delete Section"));

    m_pctrlIsOrtho             = new QCheckBox(tr("Orthogonal Sections"));

    Insert2Layout->addWidget(m_pctrlInsertBefore2);
    Insert2Layout->addWidget(m_pctrlInsertAfter2);
    Insert2Layout->addWidget(m_pctrlDeleteSection2);

    m_pctrlBladeAxisTable = new QTableView(this);
    m_pctrlBladeAxisTable->setWindowTitle(QObject::tr("Advanced Blade definition"));
    m_pctrlBladeAxisTable->setMinimumWidth(500);
    m_pctrlBladeAxisTable->setSelectionMode(QAbstractItemView::SingleSelection);
    m_pctrlBladeAxisTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_pctrlBladeAxisTable->setEditTriggers(QAbstractItemView::CurrentChanged |
                                                                              QAbstractItemView::DoubleClicked |
                                                                              QAbstractItemView::SelectedClicked |
                                                                              QAbstractItemView::EditKeyPressed);
    m_pctrlSimpleDesign = new QPushButton(tr("Back"));

    QVBoxLayout *AdvancedEditLayout = new QVBoxLayout;
    QHBoxLayout *BottomButtons = new QHBoxLayout;
    BottomButtons->addWidget(m_pctrlSimpleDesign);
    BottomButtons->addWidget(m_pctrlIsOrtho);

    AdvancedEditLayout->addLayout(Insert2Layout);
    AdvancedEditLayout->addWidget(m_pctrlBladeAxisTable);
    AdvancedEditLayout->addLayout(BottomButtons);


    //---------------------3D View Layout ---------------------------//

    QGridLayout *ThreeDView = new QGridLayout;

    m_pctrlPerspective = new QCheckBox(tr("Perspective Projection"));
    m_pctrlShowTurbine = new QCheckBox(tr("Propeller"));
    m_pctrlSurfaces = new QCheckBox(tr("Surfaces"));
    m_pctrlOutline = new QCheckBox(tr("Outlines"));
    m_pctrlAirfoils = new QCheckBox(tr("Airfoils"));
    m_pctrlAxes = new QCheckBox(tr("Axes"));
    m_pctrlPositions = new QCheckBox(tr("Positions"));
    m_pctrlFoilNames = new QCheckBox(tr("Foil Names"));


    Showlabel = new QLabel(tr("Show:"));

    m_pctrlSurfaces->setChecked(true);
    m_pctrlOutline->setChecked(true);
    m_pctrlAirfoils->setChecked(false);
    m_pctrlPositions->setChecked(false);
    m_pctrlFoilNames->setChecked(false);

    ThreeDView->addWidget(Showlabel,1,1);
    ThreeDView->addWidget(m_pctrlShowTurbine,1,2);
    ThreeDView->addWidget(m_pctrlSurfaces,1,3);
    ThreeDView->addWidget(m_pctrlOutline,1,4);
    ThreeDView->addWidget(m_pctrlAirfoils,1,5);
    ThreeDView->addWidget(m_pctrlPerspective,2,2);
    ThreeDView->addWidget(m_pctrlAxes,2,3);
    ThreeDView->addWidget(m_pctrlPositions,2,4);
    ThreeDView->addWidget(m_pctrlFoilNames,2,5);


    QVBoxLayout *ViewLayout = new QVBoxLayout;
    ViewLayout->addLayout(ThreeDView);

    QGroupBox *ViewControl = new QGroupBox(tr("3D View Control"));
    ViewControl->setLayout(ViewLayout);

    QHBoxLayout *ViewLayout2 = new QHBoxLayout;
    ViewLayout2->addWidget(ViewControl);


    //--------------------360 Polar Layout--------------------//

            QVBoxLayout *SaveDelete = new QVBoxLayout;
            QGridLayout *Sliders = new QGridLayout;
            QVBoxLayout *Layout360 = new QVBoxLayout;

            m_pctrlSave360 = new QPushButton(tr("Save 360 Polar"));
            m_pctrlNew360 = new QPushButton(tr("Create New 360 Polar"));


            m_360Name = new QLineEdit;

            m_LabelA = new QLabel(tr("A+"));

            m_pctrlA = new QSlider(Qt::Horizontal);
            m_pctrlA->setMinimum(1);
            m_pctrlA->setMaximum(1);
            m_pctrlA->setValue(0);

            m_LabelB = new QLabel(tr("B+"));

            m_pctrlB = new QSlider(Qt::Horizontal);
            m_pctrlB->setMinimum(1);
            m_pctrlB->setMaximum(100);
            m_pctrlB->setValue(5);

            m_LabelAm = new QLabel(tr("A-"));

            m_pctrlAm = new QSlider(Qt::Horizontal);
            m_pctrlAm->setMinimum(1);
            m_pctrlAm->setMaximum(30);
            m_pctrlAm->setValue(15);

            m_LabelBm = new QLabel(tr("B-"));

            m_pctrlBm = new QSlider(Qt::Horizontal);
            m_pctrlBm->setMinimum(1);
            m_pctrlBm->setMaximum(70);
            m_pctrlBm->setValue(5);

            SaveDelete->addWidget(m_pctrlSave360);
            SaveDelete->addWidget(m_pctrlNew360);

             //m_pctrl_d_cl = new QDoubleSpinBox;
             //m_pctrl_d_cl->setValue(m_d_cl);

           // m_pctrlCD90Label = new QLabel(tr("Delta Cl"));




            m_CD90YCoordinateLabel = new QLabel (tr("CD90 w/ Y(0.0125)"));

            m_CD90YCoordinate = new QRadioButton();
            m_CD90YCoordinate->setChecked(false);

            m_CD90LERadiusLabel = new QLabel (tr("CD90 w/ LE Radius"));

            m_CD90LERadius = new QRadioButton();
            m_CD90LERadius->setChecked(true);


            QButtonGroup *Group3 = new QButtonGroup;

            Group3->addButton(m_CD90YCoordinate);
            Group3->addButton(m_CD90LERadius);

            m_ComparePolars = new QCheckBox(tr("Compare 360° Polars"));
            m_ComparePolars->setChecked(m_bComparePolarCurves);

            Sliders->addWidget(m_LabelA,1,1);
            Sliders->addWidget(m_pctrlA,1,2);
            Sliders->addWidget(m_LabelB,2,1);
            Sliders->addWidget(m_pctrlB,2,2);
            Sliders->addWidget(m_LabelAm,3,1);
            Sliders->addWidget(m_pctrlAm,3,2);
            Sliders->addWidget(m_LabelBm,4,1);
            Sliders->addWidget(m_pctrlBm,4,2);
            Sliders->addWidget(m_CD90YCoordinate,5,1);
            Sliders->addWidget(m_CD90YCoordinateLabel,5,2);
            Sliders->addWidget(m_CD90LERadius,6,1);
            Sliders->addWidget(m_CD90LERadiusLabel,6,2);


            QGroupBox *SaveDeleteGroup = new QGroupBox(tr("Create 360 Polar"));
            QGroupBox *SliderGroup = new QGroupBox(tr("Finetuning of Polar"));

//            m_pctrl_d_cl->setMinimum(0.01);
//            m_pctrl_d_cl->setMaximum(1);
//            m_pctrl_d_cl->setSingleStep(0.01);
//            m_pctrl_d_cl->setValue(m_d_cl);

            ///////////////////curve style


            m_pctrlCurveStyle = new LineCbBox();
            m_pctrlCurveWidth = new LineCbBox();
            m_pctrlCurveColor = new LineButton;
            for (int i=0; i<5; i++)
            {
                    m_pctrlCurveStyle->addItem("item");
                    m_pctrlCurveWidth->addItem("item");
            }
            m_pStyleDelegate = new LineDelegate;
            m_pWidthDelegate = new LineDelegate;
            m_pctrlCurveStyle->setItemDelegate(m_pStyleDelegate);
            m_pctrlCurveWidth->setItemDelegate(m_pWidthDelegate);

            QGridLayout *CurveStyleLayout = new QGridLayout;
            QLabel *lab200 = new QLabel(tr("Style"));
            QLabel *lab201 = new QLabel(tr("Width"));
            QLabel *lab202 = new QLabel(tr("Color"));
            lab200->setAlignment(Qt::AlignRight |Qt::AlignVCenter);
            lab201->setAlignment(Qt::AlignRight |Qt::AlignVCenter);
            lab202->setAlignment(Qt::AlignRight |Qt::AlignVCenter);
            CurveStyleLayout->addWidget(lab200,1,1);
            CurveStyleLayout->addWidget(lab201,2,1);
            CurveStyleLayout->addWidget(lab202,3,1);
            CurveStyleLayout->addWidget(m_pctrlCurveStyle,1,2);
            CurveStyleLayout->addWidget(m_pctrlCurveWidth,2,2);
            CurveStyleLayout->addWidget(m_pctrlCurveColor,3,2);
            CurveStyleLayout->setColumnStretch(2,5);

            /////////////

            SaveDeleteGroup->setLayout(SaveDelete);
            SliderGroup->setLayout(Sliders);

            Layout360->addWidget(m_360Name);
            Layout360->addWidget(SaveDeleteGroup);
            Layout360->addWidget(SliderGroup);
            Layout360->addWidget(m_ComparePolars);
            Layout360->addLayout(CurveStyleLayout);

//---------------Turbine Edit Layout------------------//

    m_pctrlTypeLabel = new QLabel(tr("Regulation"));
    m_pctrlGeneratorTypeLabel = new QLabel(tr("Transmission"));
    m_pctrlStall = new QRadioButton(tr("Stall"));
    m_pctrlPitch = new QRadioButton(tr("Pitch"));
    m_pctrlFixed = new QRadioButton(tr("Single"));
    m_pctrl2Step = new QRadioButton(tr("2 Step"));
    m_pctrlVariable = new QRadioButton(tr("Variable"));
    m_pctrlFixedPitch = new FloatEdit;
    m_pctrlFixedPitch->SetMin(-180);
    m_pctrlFixedPitch->SetMax(180);
    m_pctrlFixedPitch->SetPrecision(1);
    m_pctrlFixedPitch->SetValue(0);
    m_pctrlFixedPitchLabel = new QLabel(tr("Fixed Pitch"));




    m_pctrlCutIn = new FloatEdit;
    m_pctrlCutIn->SetValue(0);
    m_pctrlCutInLabel = new QLabel(tr("V Initial"));
    m_pctrlSwitch = new FloatEdit;
    m_pctrlSwitch->SetValue(0);
    m_pctrlSwitchLabel = new QLabel(tr("V Switch"));
    m_pctrlCutOut = new FloatEdit;
    m_pctrlCutOut->SetValue(0);
    m_pctrlCutOutLabel = new QLabel(tr("V Final"));

    m_pctrlVariableLossesLabel = new QLabel(tr("Loss Factor"));
    m_pctrlFixedLossesLabel = new QLabel(tr("Fixed Losses"));

    m_pctrlVariableLosses = new FloatEdit;
    m_pctrlFixedLosses = new FloatEdit;
    m_pctrlFixedLosses->SetValue(0);
    m_pctrlVariableLosses->SetMin(0);
    m_pctrlVariableLosses->SetMax(1);
    m_pctrlVariableLosses->SetPrecision(3);
    m_pctrlVariableLosses->SetValue(0);

    speed1 = new QLabel;
    speed2 = new QLabel;
    speed3 = new QLabel;
    rotspeed1 = new QLabel(tr("Rpm"));
    rotspeed2 = new QLabel(tr("Rpm"));
    power1 = new QLabel();
    power2 = new QLabel();








    m_pctrlRot1  = new FloatEdit;
    m_pctrlRot1->SetValue(0);
    m_pctrlRot1Label = new QLabel(tr("Rotational Speed Min"));
    m_pctrlRot2  = new FloatEdit;
    m_pctrlRot2->SetValue(0);
    m_pctrlRot2Label = new QLabel(tr("Rotational Speed Max"));

    m_pctrlLambda = new FloatEdit;
    m_pctrlLambdaLabel = new QLabel(tr("Tip Speed Ratio at Design Point"));
    m_pctrlLambda->SetValue(0);

    m_pctrlGenerator = new FloatEdit;
    m_pctrlGeneratorLabel = new QLabel(tr("Generator nom. Capacity"));
    m_pctrlGenerator->SetValue(0);

    m_pctrlSaveTurbine = new QPushButton(tr("Save"));
    m_pctrlDiscardTurbine = new QPushButton(tr("Back"));

    QHBoxLayout *SaveOrBackLayout = new QHBoxLayout;
    SaveOrBackLayout->addWidget(m_pctrlDiscardTurbine);
    SaveOrBackLayout->addWidget(m_pctrlSaveTurbine);

    QButtonGroup *Group1 = new QButtonGroup;
    QButtonGroup *Group2 = new QButtonGroup;

    Group1->addButton(m_pctrlStall);
    Group1->addButton(m_pctrlPitch);
    Group2->addButton(m_pctrlFixed);
    Group2->addButton(m_pctrl2Step);
    Group2->addButton(m_pctrlVariable);

    QGridLayout *TypeLayout = new QGridLayout;
  //  TypeLayout->addWidget(m_pctrlTypeLabel,1,1);
  //  TypeLayout->addWidget(m_pctrlStall,2,1);
  //  TypeLayout->addWidget(m_pctrlPitch,2,2);
  //  TypeLayout->addWidget(m_pctrlGeneratorTypeLabel,3,1);
  //  TypeLayout->addWidget(m_pctrlFixed,4,1);
  //  TypeLayout->addWidget(m_pctrl2Step,4,2);
  //  TypeLayout->addWidget(m_pctrlVariable,4,3);
    QGroupBox *TypeGroup = new QGroupBox(tr("Turbine Type"));
    TypeGroup->setLayout(TypeLayout);

    QGridLayout *SpeciLayout = new QGridLayout;
//    SpeciLayout->addWidget(m_pctrlGeneratorLabel,1,1);
//    SpeciLayout->addWidget(m_pctrlGenerator,1,2);
//    SpeciLayout->addWidget(power1,1,3);
    SpeciLayout->addWidget(m_pctrlRot1Label,2,1);
    SpeciLayout->addWidget(m_pctrlRot1,2,2);
    SpeciLayout->addWidget(rotspeed1,2,3);
//    SpeciLayout->addWidget(m_pctrlRot2Label,3,1);
//    SpeciLayout->addWidget(m_pctrlRot2,3,2);
//    SpeciLayout->addWidget(rotspeed2,3,3);
    SpeciLayout->addWidget(m_pctrlLambdaLabel,4,1);
    SpeciLayout->addWidget(m_pctrlLambda,4,2);
    SpeciLayout->addWidget(m_pctrlCutInLabel,5,1);
    SpeciLayout->addWidget(m_pctrlCutIn,5,2);
    SpeciLayout->addWidget(speed1,5,3);
//    SpeciLayout->addWidget(m_pctrlSwitchLabel,6,1);
//    SpeciLayout->addWidget(m_pctrlSwitch,6,2);
//    SpeciLayout->addWidget(speed3,6,3);
    SpeciLayout->addWidget(m_pctrlCutOutLabel,6,1);
    SpeciLayout->addWidget(m_pctrlCutOut,6,2);
    SpeciLayout->addWidget(speed2,6,3);
    SpeciLayout->addWidget(m_pctrlFixedPitch,8,2);
    SpeciLayout->addWidget(m_pctrlFixedPitchLabel,8,1);
//    SpeciLayout->addWidget(m_pctrlVariableLossesLabel,9,1);
//    SpeciLayout->addWidget(m_pctrlFixedLossesLabel,10,1);
//    SpeciLayout->addWidget(m_pctrlVariableLosses,9,2);
//    SpeciLayout->addWidget(m_pctrlFixedLosses,10,2);
//    SpeciLayout->addWidget(power2,10,3);

    QGroupBox *SpeciGroup = new QGroupBox(tr("Propeller Specifications"));
    SpeciGroup->setLayout(SpeciLayout);

    WingSelection = new QComboBox;
    QGridLayout *WingLayout = new QGridLayout;
    WingLayout->addWidget(WingSelection);
    QGroupBox *WingGroup = new QGroupBox(tr("Propeller Blade"));
    WingGroup->setLayout(WingLayout);

    m_pctrlTurbineName = new QLineEdit;
    QGridLayout *TNameLayout = new QGridLayout;
    TNameLayout->addWidget(m_pctrlTurbineName);
    QGroupBox *TNameGroup = new QGroupBox(tr("Propeller Name"));
    TNameGroup->setLayout(TNameLayout);


    //----------------Turbine Show Layout----------//
    TypeLabel = new QLabel(tr("Regulation"));
    GeneratorTypeLabel = new QLabel(tr("Transmission"));
    CutInLabel = new QLabel(tr("V Initial"));
    SwitchLabel = new QLabel(tr("V Switch"));
    CutOutLabel = new QLabel(tr("V Final"));
    Rot1Label = new QLabel(tr("Rotational Speed Min"));
    Rot2Label = new QLabel(tr("Rotational Speed Max"));
    LambdaLabel = new QLabel(tr("Tip Speed Ratio at Design Point"));
    GeneratorLabel = new QLabel(tr("Pitch from Power Output"));

    FixedLossesLabel = new QLabel(tr("Fixed Losses"));
    VariableLossesLabel = new QLabel(tr("VariableLosses"));
    FixedPitchLabel = new QLabel(tr("Fixed Pitch"));



    OuterRadiusLabel = new QLabel(tr("Outer Radius"));

    Speed1 = new QLabel;
    Speed2 = new QLabel;
    Speed3 = new QLabel;
    Rotspeed1 = new QLabel(tr("rpm"));
    Rotspeed2 = new QLabel(tr("rpm"));
    Length1 = new QLabel;
    Power1 = new QLabel;
    Power2 = new QLabel;







    Type = new QLabel;
    Type->setAlignment(Qt::AlignRight);
    Trans = new QLabel;
    Trans->setAlignment(Qt::AlignRight);
    Capacity= new QLabel;
    Capacity->setAlignment(Qt::AlignRight);
    Rot1 = new QLabel;
    Rot1->setAlignment(Qt::AlignRight);
    Rot2 = new QLabel;
    Rot2->setAlignment(Qt::AlignRight);
    Lambda0 = new QLabel;
    Lambda0->setAlignment(Qt::AlignRight);
    CutIn = new QLabel;
    CutIn->setAlignment(Qt::AlignRight);
    CutOut = new QLabel;
    CutOut->setAlignment(Qt::AlignRight);
    Switch = new QLabel;
    Switch->setAlignment(Qt::AlignRight);
    Generator = new QLabel;
    Generator->setAlignment(Qt::AlignRight);
    Blade = new QLabel;
    Blade->setAlignment(Qt::AlignRight);
    OuterRadius = new QLabel;
    OuterRadius->setAlignment(Qt::AlignRight);
    BladeLabel = new QLabel(tr("Propeller Blade"));

    FixedLosses = new QLabel;
    FixedLosses->setAlignment(Qt::AlignRight);
    VariableLosses = new QLabel;
    VariableLosses->setAlignment(Qt::AlignRight);
    FixedPitch = new QLabel;
    FixedPitch->setAlignment(Qt::AlignRight);




    QGridLayout *TurbineDataLayout = new QGridLayout;

//    TurbineDataLayout->addWidget(TypeLabel,1,1);
//    TurbineDataLayout->addWidget(Type,1,2);
//    TurbineDataLayout->addWidget(GeneratorTypeLabel,2,1);
//    TurbineDataLayout->addWidget(Trans,2,2);
//    TurbineDataLayout->addWidget(GeneratorLabel,3,1);
//    TurbineDataLayout->addWidget(Generator,3,2);
//    TurbineDataLayout->addWidget(Power1,3,3);
    TurbineDataLayout->addWidget(Rot1Label,4,1);
    TurbineDataLayout->addWidget(Rot1,4,2);
    TurbineDataLayout->addWidget(Rotspeed1,4,3);
//    TurbineDataLayout->addWidget(Rot2Label,5,1);
//    TurbineDataLayout->addWidget(Rot2,5,2);
    TurbineDataLayout->addWidget(Rotspeed2,5,3);
    TurbineDataLayout->addWidget(LambdaLabel,6,1);
    TurbineDataLayout->addWidget(Lambda0,6,2);
    TurbineDataLayout->addWidget(CutInLabel,7,1);
    TurbineDataLayout->addWidget(CutIn,7,2);
    TurbineDataLayout->addWidget(Speed1,7,3);
    TurbineDataLayout->addWidget(CutOutLabel,8,1);
    TurbineDataLayout->addWidget(CutOut,8,2);
    TurbineDataLayout->addWidget(Speed2,8,3);
//    TurbineDataLayout->addWidget(SwitchLabel,9,1);
//    TurbineDataLayout->addWidget(Switch,9,2);
//    TurbineDataLayout->addWidget(Speed3,9,3);
    TurbineDataLayout->addWidget(BladeLabel,11,1);
    TurbineDataLayout->addWidget(Blade,11,2);
    TurbineDataLayout->addWidget(OuterRadiusLabel,12,1);
    TurbineDataLayout->addWidget(OuterRadius,12,2);
    TurbineDataLayout->addWidget(Length1,12,3);
    TurbineDataLayout->addWidget(FixedPitchLabel,13,1);
    TurbineDataLayout->addWidget(FixedPitch,13,2);
//    TurbineDataLayout->addWidget(VariableLossesLabel,14,1);
//    TurbineDataLayout->addWidget(FixedLossesLabel,15,1);
//    TurbineDataLayout->addWidget(Power2,15,3);
//    TurbineDataLayout->addWidget(VariableLosses,14,2);
//    TurbineDataLayout->addWidget(FixedLosses,15,2);

    QGroupBox *TurbineDataGroup = new QGroupBox(tr("Propeller Data"));
    TurbineDataGroup->setLayout(TurbineDataLayout);

    QGridLayout *SDLayout = new QGridLayout;
    m_pctrlNewTurbine = new QPushButton("Create");
    m_pctrlEditTurbine = new QPushButton(tr("Edit"));
    SDLayout->addWidget(m_pctrlNewTurbine,1,1);
    SDLayout->addWidget(m_pctrlEditTurbine,1,2);
    QGroupBox *SDGroup = new QGroupBox(tr("Create/Edit/Delete Propeller"));
    SDGroup->setLayout(SDLayout);


//////////////////WIND TURBINE ENEGRGY PREDICTION - UNUSED ///////////////////////
    QGridLayout *WeibullLayout = new QGridLayout;
    m_pctrlk = new QDoubleSpinBox;
    m_pctrlk->setMinimum(0.01);
    m_pctrlk->setSingleStep(0.01);
    m_pctrlKLabel = new QLabel(tr("k"));
    m_pctrla = new QDoubleSpinBox;
    m_pctrla->setMinimum(0.01);
    m_pctrla->setSingleStep(0.01);
    m_pctrlALabel = new QLabel(tr("A"));
    m_pctrlYield = new QLabel;
    m_pctrlYieldLabel = new QLabel(tr("Annual Yield"));
    POwer = new QLabel;
    WeibullLayout->addWidget(m_pctrlKLabel,1,1);
    WeibullLayout->addWidget(m_pctrlk,1,2);
    WeibullLayout->addWidget(m_pctrlALabel,2,1);
    WeibullLayout->addWidget(m_pctrla,2,2);
    WeibullLayout->addWidget(m_pctrlYieldLabel,3,1);
    WeibullLayout->addWidget(m_pctrlYield,3,2);
    WeibullLayout->addWidget(POwer,3,3);
    QGroupBox *WeibullGroup = new QGroupBox(tr("Weibull Settings"));
    WeibullGroup->setLayout(WeibullLayout);

//////////////////EDN OF WIND TURBINE ENEGRGY PREDICTION///////////////////////
   //---------------------------------------------//

    QVBoxLayout *SimLayout = new QVBoxLayout;
    QVBoxLayout *mainLayout = new QVBoxLayout;

    QVBoxLayout *PowerEditLayout = new QVBoxLayout;
    QVBoxLayout *PowerLayout = new QVBoxLayout;


    PowerLayout->addWidget(TurbineDataGroup);
    PowerLayout->addWidget(SDGroup);
   // PowerLayout->addWidget(WeibullGroup);
    PowerLayout->addStretch(1000);

    PowerEditLayout->addWidget(TNameGroup);
    //PowerEditLayout->addWidget(TypeGroup);
    PowerEditLayout->addWidget(SpeciGroup);
    PowerEditLayout->addWidget(WingGroup);
    PowerEditLayout->addLayout(SaveOrBackLayout);
    PowerEditLayout->addStretch(1000);


    mainWidget = new QStackedWidget;






    EditWidget = new QWidget;
    EditWidget->setLayout(EditLayout);

    PolarWidget = new QWidget;
    PolarWidget->setLayout(Layout360);
    PowerEditWidget = new QWidget;
    PowerEditWidget->setLayout(PowerEditLayout);
    PowerWidget = new QWidget;
    PowerWidget->setLayout(PowerLayout);
    AdvancedEditWidget = new QWidget;
    AdvancedEditWidget->setLayout(AdvancedEditLayout);

    bladeWidget->addWidget(WingDataBox);
    bladeWidget->addWidget(EditWidget);
    bladeWidget->addWidget(AdvancedEditWidget);

    SimLayout->addLayout(ViewLayout2);
    SimLayout->addWidget(bladeWidget);

    SimWidget  = new QWidget;
    SimWidget->setLayout(SimLayout);

    mainWidget->addWidget(SimWidget);
    mainWidget->addWidget(PolarWidget);
    mainWidget->addWidget(PowerWidget);
    mainWidget->addWidget(PowerEditWidget);

    mainLayout->addWidget(mainWidget);

    setLayout(mainLayout);
}





void QBEM::SetCurrentSection(int section)
{
        m_iSection = section;
        if(m_iSection <0 || m_iSection>m_pWing->m_NPanel)
        {
                m_pctrlInsertAfter->setEnabled(false);
                m_pctrlInsertBefore->setEnabled(false);
                m_pctrlDeleteSection->setEnabled(false);
        }
        else
        {
                m_pctrlInsertAfter->setEnabled(true);
                m_pctrlInsertBefore->setEnabled(true);
                m_pctrlDeleteSection->setEnabled(true);

                QString str;
                str = QString(tr("Insert after section %1")).arg(m_iSection+1);
                m_pctrlInsertAfter->setText(str);
                str = QString(tr("Insert before section %1")).arg(m_iSection+1);
                m_pctrlInsertBefore->setText(str);
                str = QString(tr("Delete section %1")).arg(m_iSection+1);
                m_pctrlDeleteSection->setText(str);
        }
        m_bResetglSectionHighlight = true;
}



bool QBEM::SetModWing(CBlade *pModWing)
{
        MainFrame *pMainFrame = (MainFrame*)s_pMainFrame;
        if(!pModWing) pModWing = m_pWing;
        CBlade *pWing;

        bool bExists = true;
        int resp, k;

        QStringList NameList;
        for(k=0; k<s_poaBEMWings->size(); k++)
        {
                pWing = (CBlade*)s_poaBEMWings->at(k);
                NameList.append(pWing->m_WingName);
        }

        RenameDlg RDlg(this);
        RDlg.move(pMainFrame->m_DlgPos);
        RDlg.m_pstrArray = &NameList;
        RDlg.m_strQuestion = tr("Enter the new name for the wing :");
        RDlg.m_strName = pModWing->m_WingName;
        RDlg.InitDialog();

        while (bExists)
        {
                resp = RDlg.exec();
                pMainFrame->m_DlgPos = RDlg.pos();
                if(resp==QDialog::Accepted)
                {
                        //Is the new name already used ?
                        bExists = false;
                        for (k=0; k<s_poaBEMWings->size(); k++)
                        {
                                pWing = (CBlade*)s_poaBEMWings->at(k);
                                if (pWing->m_WingName == RDlg.m_strName)
                                {
                                        bExists = true;
                                        break;
                                }
                        }

                        if(!bExists)
                        {
                                pModWing->m_WingName = RDlg.m_strName;
                                pMainFrame->SetSaveState(false);
                                return true;
                        }
                }
                else if(resp ==10)
                {
                        //user wants to overwrite
                        pModWing->m_WingName = RDlg.m_strName;
                        for (int i=0;i<s_poaBEMWings->size();i++)
                        {
                            pWing=(CBlade *) s_poaBEMWings->at(i);
                            if (pModWing->m_WingName==pWing->m_WingName)
                            {
                                DeleteWing(pWing);
                                break;
                            }


                        }
                        pMainFrame->SetSaveState(false);
                        return true;
                }
                else
                {
                        return false;//cancelled
                }
        }
        return false ;//useless...
}



bool QBEM::SetModTurbine(TData *pModTData)
{
        MainFrame *pMainFrame = (MainFrame*)s_pMainFrame;
        if(!pModTData) pModTData = m_pTData;
        TData *pTData;

        bool bExists = true;
        int resp, k;

        QStringList NameList;
        for(k=0; k<s_poaTData.size(); k++)
        {
                pTData = s_poaTData.at(k);
                NameList.append(pTData->m_TurbineName);
        }

        RenameDlg RDlg(this);
        RDlg.move(pMainFrame->m_DlgPos);
        RDlg.m_pstrArray = &NameList;
        RDlg.m_strQuestion = tr("Enter the new name for the Propeller :");
        RDlg.m_strName = pModTData->m_TurbineName;
        RDlg.InitDialog();

        while (bExists)
        {
                resp = RDlg.exec();
                pMainFrame->m_DlgPos = RDlg.pos();
                if(resp==QDialog::Accepted)
                {
                        //Is the new name already used ?
                        bExists = false;
                        for (k=0; k<s_poaTData.size(); k++)
                        {
                                pTData = s_poaTData.at(k);
                                if (pTData->m_TurbineName == RDlg.m_strName)
                                {
                                        bExists = true;
                                        break;
                                }
                        }

                        if(!bExists)
                        {
                                pModTData->m_TurbineName = RDlg.m_strName;
                                pMainFrame->SetSaveState(false);
                                return true;
                        }
                }
                else if(resp ==10)
                {
                        //user wants to overwrite
                        pModTData->m_TurbineName = RDlg.m_strName;
                        for (int i=0;i<s_poaTData.size();i++)
                        {
                            pTData = s_poaTData.at(i);
                            if (pModTData->m_TurbineName == pTData->m_TurbineName)
                            {
                                DeleteTurbine(pTData);
                                break;
                            }


                        }
                        pMainFrame->SetSaveState(false);
                        return true;
                }
                else
                {
                        return false;//cancelled
                }
        }
        return false ;//useless...
}

void QBEM::SetGraphTitles(Graph* pGraph)
{
        if(!pGraph) return;
        if (pGraph->m_Type == 0)
        {
            switch (pGraph->GetXVariable())
            {
                    case 0:
                            pGraph->SetXTitle(tr("TSR"));
                            break;
                    case 1:
                            pGraph->SetXTitle(tr("1/TSR"));
                            break;
                    case 2:
                            pGraph->SetXTitle(tr("Cp"));
                            break;
                    case 3:
                            pGraph->SetXTitle(tr("Propeller Cp"));
                            break;
                    case 4:
                            pGraph->SetXTitle(tr("Ct"));
                            break;
                    case 5:
                            pGraph->SetXTitle(tr("Propeller Ct"));
                            break;
                    case 6:
                            pGraph->SetXTitle(tr("Kp"));
                            break;

                    case 7:
                            pGraph->SetXTitle(tr("Advance Ratio"));
                            break;

                    case 8:
                            pGraph->SetXTitle(tr("Propeller Efficiency"));
                            break;

                    default:
                            pGraph->SetXTitle(tr("Alpha"));
                            break;
            }
        }
        if (pGraph->m_Type == 1)
        {
            switch (pGraph->GetXVariable())
            {
                    case 0:
                            pGraph->SetXTitle(tr("a_a"));
                            break;
                    case 1:
                            pGraph->SetXTitle(tr("pos [m]"));
                            break;
                    case 2:
                            pGraph->SetXTitle(tr("a_t"));
                            break;
                    case 3:
                            pGraph->SetXTitle(tr("lambda_local"));
                            break;
                    case 4:
                            pGraph->SetXTitle(tr("Cn"));
                            break;
                    case 5:
                            pGraph->SetXTitle(tr("Ct"));
                            break;
                    case 6:
                            pGraph->SetXTitle(tr("Phi"));
                            break;
                    case 7:
                            pGraph->SetXTitle(tr("Alpha"));
                            break;
                    case 8:
                            pGraph->SetXTitle(tr("Theta"));
                            break;
                    case 9:
                            pGraph->SetXTitle(tr("Chord [m]"));
                            break;
                    case 10:
                            pGraph->SetXTitle(tr("Lift Coeff"));
                            break;
                    case 11:
                            pGraph->SetXTitle(tr("Drag Coeff"));
                            break;
                    case 12:
                            pGraph->SetXTitle(tr("L/D Ratio"));
                            break;
                    case 13:
                            pGraph->SetXTitle(tr("F"));
                            break;
                    case 14:
                            pGraph->SetXTitle(tr("It"));
                            break;
                    case 15:
                            pGraph->SetXTitle(tr("Fa_a"));
                            break;
                    case 16:
                            pGraph->SetXTitle(tr("Fa_t"));
                            break;
                    default:
                            pGraph->SetXTitle(tr("pos [m]"));
                            break;
            }
        }
        if (pGraph->m_Type == 0)
        {
            switch (pGraph->GetYVariable())
            {
                    case 0:
                            pGraph->SetYTitle(tr("TSR"));
                            break;
                    case 1:
                            pGraph->SetYTitle(tr("1/TSR"));
                            break;
                    case 2:
                            pGraph->SetYTitle(tr("Cp"));
                            break;
                    case 3:
                            pGraph->SetYTitle(tr("Propeller Cp"));
                            break;
                    case 4:
                            pGraph->SetYTitle(tr("Ct"));
                            break;
                    case 5:
                            pGraph->SetYTitle(tr("Propeller Ct"));
                            break;
                    case 6:
                            pGraph->SetYTitle(tr("Kp"));
                            break;

                    case 7:
                            pGraph->SetYTitle(tr("Advance Ratio"));
                            break;

                    case 8:
                            pGraph->SetYTitle(tr("Propeller Efficiency"));
                            break;

                    default:
                            pGraph->SetYTitle(tr("Alpha"));
                            break;
            }
        }
        if (pGraph->m_Type == 1)
        {
            switch (pGraph->GetYVariable())
            {
                    case 0:
                            pGraph->SetYTitle(tr("a_a"));
                            break;
                    case 1:
                            pGraph->SetYTitle(tr("pos [m]"));
                            break;
                    case 2:
                            pGraph->SetYTitle(tr("a_t"));
                            break;
                    case 3:
                            pGraph->SetYTitle(tr("lambda_local"));
                            break;
                    case 4:
                            pGraph->SetYTitle(tr("Cn"));
                            break;
                    case 5:
                            pGraph->SetYTitle(tr("Ct"));
                            break;
                    case 6:
                            pGraph->SetYTitle(tr("Phi"));
                            break;
                    case 7:
                            pGraph->SetYTitle(tr("Alpha"));
                            break;
                    case 8:
                            pGraph->SetYTitle(tr("Theta"));
                            break;
                    case 9:
                            pGraph->SetYTitle(tr("Chord [m]"));
                            break;
                    case 10:
                            pGraph->SetYTitle(tr("Lift Coeff"));
                            break;
                    case 11:
                            pGraph->SetYTitle(tr("Drag Coeff"));
                            break;
                    case 12:
                            pGraph->SetYTitle(tr("L/D Ratio"));
                            break;

                    case 13:
                            pGraph->SetYTitle(tr("F"));
                            break;
                    case 14:
                            pGraph->SetYTitle(tr("It"));
                            break;
                    case 15:
                            pGraph->SetYTitle(tr("Fa_a"));
                            break;
                    case 16:
                            pGraph->SetYTitle(tr("Fa_t"));
                            break;
                    default:
                            pGraph->SetYTitle(tr("pos [m]"));
                            break;
            }
        }
}

void QBEM::SetPowerGraphTitles(Graph* pGraph)
{
        if(!pGraph) return;
        if (pGraph->m_Type == 0)
        {
        switch (pGraph->GetXVariable())
        {
                    case 0:
                            pGraph->SetXTitle(tr("P [W]"));
                            break;
                    case 1:
                            pGraph->SetXTitle(tr("T [N]"));
                            break;
                    case 2:
                            pGraph->SetXTitle(tr("V [m/s]"));
                            break;
                    case 3:
                            pGraph->SetXTitle(tr("Torque [Nm]"));
                            break;
                    case 4:
                            pGraph->SetXTitle(tr("TSR"));
                            break;
                    case 5:
                            pGraph->SetXTitle(tr("Omega [rpm]"));
                            break;
                    case 6:
                            pGraph->SetXTitle(tr("Cp"));
                            break;
                    case 7:
                            pGraph->SetXTitle(tr("Propeller Cp"));
                            break;
                    case 8:
                            pGraph->SetXTitle(tr("Ct"));
                            break;
                    case 9:
                            pGraph->SetXTitle(tr("Propeller Ct"));
                            break;
                    case 10:
                            pGraph->SetXTitle(tr("Pitch"));
                            break;
                    case 11:
                            pGraph->SetXTitle(tr("f Wei"));
                            break;
                    case 12:
                            pGraph->SetXTitle(tr("f x V^3"));
                            break;
                    case 13:
                            pGraph->SetXTitle(tr("M_b [Nm]"));
                            break;
                    case 14:
                            pGraph->SetXTitle(tr("Cp_loss"));
                            break;
                    case 15:
                            pGraph->SetXTitle(tr("Kp"));
                            break;
                    case 16:
                            pGraph->SetXTitle(tr("1/TSR"));
                            break;
                    case 17:
                            pGraph->SetXTitle(tr("Advance Ratio"));
                            break;
                    case 18:
                            pGraph->SetXTitle(tr("Propeller Efficiency"));
                            break;
                    default:
                            pGraph->SetXTitle(tr("Alpha"));
                            break;
                }
        }
        if(pGraph->m_Type == 1)
        {
            switch (pGraph->GetXVariable())
            {

                case 0:
                        pGraph->SetXTitle(tr("Cn"));
                        break;
                case 1:
                        pGraph->SetXTitle(tr("Ct"));
                        break;
                case 2:
                        pGraph->SetXTitle(tr("Phi [°]"));
                        break;
                case 3:
                        pGraph->SetXTitle(tr("Alpha [°]"));
                        break;
                case 4:
                        pGraph->SetXTitle(tr("Theta [°]"));
                        break;
                case 5:
                        pGraph->SetXTitle(tr("Chord [m]"));
                        break;
                case 6:
                        pGraph->SetXTitle(tr("Cl"));
                        break;
                case 7:
                        pGraph->SetXTitle(tr("Cd"));
                        break;
                case 8:
                        pGraph->SetXTitle(tr("Cl / Cd"));
                        break;
                case 9:
                        pGraph->SetXTitle(tr("F"));
                        break;
                case 10:
                        pGraph->SetXTitle(tr("a_a"));
                        break;
                case 11:
                        pGraph->SetXTitle(tr("a_t"));
                        break;
                case 12:
                        pGraph->SetXTitle(tr("pos [m]"));
                        break;
                case 13:
                        pGraph->SetXTitle(tr("TSR"));
                        break;
                case 14:
                        pGraph->SetXTitle(tr("Re"));
                        break;
                case 15:
                        pGraph->SetXTitle(tr("Delta Re"));
                        break;
                case 16:
                        pGraph->SetXTitle(tr("k [mm]"));
                        break;
                case 17:
                        pGraph->SetXTitle(tr("V [m/s]"));
                        break;
                case 18:
                        pGraph->SetXTitle(tr("F_t [N/m]"));
                        break;
                case 19:
                        pGraph->SetXTitle(tr("F_n [N/m]"));
                        break;
                case 20:
                        pGraph->SetXTitle(tr("It"));
                        break;
                case 21:
                        pGraph->SetXTitle(tr("Mach"));
                        break;
                case 22:
                        pGraph->SetXTitle(tr("Gam.[m2/s]"));
                        break;
                case 23:
                        pGraph->SetXTitle(tr("Fa_a"));
                        break;
                case 24:
                        pGraph->SetXTitle(tr("Fa_t"));
                        break;
                default:
                        pGraph->SetXTitle(tr("Pos [m]"));
                        break;
                }
        }
        if (pGraph->m_Type == 0)
        {
        switch (pGraph->GetYVariable())
        {
                    case 0:
                            pGraph->SetYTitle(tr("P [W]"));
                            break;
                    case 1:
                            pGraph->SetYTitle(tr("T [N]"));
                            break;
                    case 2:
                            pGraph->SetYTitle(tr("V [m/s]"));
                            break;
                    case 3:
                            pGraph->SetYTitle(tr("Torque [Nm]"));
                            break;
                    case 4:
                            pGraph->SetYTitle(tr("TSR"));
                            break;
                    case 5:
                            pGraph->SetYTitle(tr("Omega [rpm]"));
                            break;
                    case 6:
                            pGraph->SetYTitle(tr("Cp"));
                            break;
                    case 7:
                            pGraph->SetYTitle(tr("Propeller Cp"));
                            break;
                    case 8:
                            pGraph->SetYTitle(tr("Ct"));
                            break;
                    case 9:
                            pGraph->SetYTitle(tr("Propeller Ct"));
                            break;
                    case 10:
                            pGraph->SetYTitle(tr("Pitch"));
                            break;
                    case 11:
                            pGraph->SetYTitle(tr("f Wei"));
                            break;
                    case 12:
                            pGraph->SetYTitle(tr("f x V^3"));
                            break;
                    case 13:
                            pGraph->SetYTitle(tr("M_b [Nm]"));
                            break;
                    case 14:
                            pGraph->SetYTitle(tr("Cp_loss"));
                            break;
                    case 15:
                            pGraph->SetYTitle(tr("Kp"));
                            break;
                    case 16:
                            pGraph->SetYTitle(tr("1/TSR"));
                            break;
                    case 17:
                            pGraph->SetYTitle(tr("Advance Ratio"));
                            break;
                    case 18:
                            pGraph->SetYTitle(tr("Propeller Efficiency"));
                            break;
                    default:
                            pGraph->SetYTitle(tr("Alpha [°]"));
                            break;
                }
        }
        if(pGraph->m_Type == 1)
        {
            switch (pGraph->GetYVariable())
            {

                case 0:
                        pGraph->SetYTitle(tr("Cn"));
                        break;
                case 1:
                        pGraph->SetYTitle(tr("Ct"));
                        break;
                case 2:
                        pGraph->SetYTitle(tr("Phi [°]"));
                        break;
                case 3:
                        pGraph->SetYTitle(tr("Alpha [°]"));
                        break;
                case 4:
                        pGraph->SetYTitle(tr("Theta [°]"));
                        break;
                case 5:
                        pGraph->SetYTitle(tr("Chord [m]"));
                        break;
                case 6:
                        pGraph->SetYTitle(tr("Cl"));
                        break;
                case 7:
                        pGraph->SetYTitle(tr("Cd"));
                        break;
                case 8:
                        pGraph->SetYTitle(tr("Cl / Cd"));
                        break;
                case 9:
                        pGraph->SetYTitle(tr("F"));
                        break;
                case 10:
                        pGraph->SetYTitle(tr("a_a"));
                        break;
                case 11:
                        pGraph->SetYTitle(tr("a_t"));
                        break;
                case 12:
                        pGraph->SetYTitle(tr("Pos [m]"));
                        break;
                case 13:
                        pGraph->SetYTitle(tr("TSR"));
                        break;
                case 14:
                        pGraph->SetYTitle(tr("Re"));
                        break;
                case 15:
                        pGraph->SetYTitle(tr("Delta Re"));
                        break;
                case 16:
                        pGraph->SetYTitle(tr("k [mm]"));
                        break;
                case 17:
                        pGraph->SetYTitle(tr("V [m/s]"));
                        break;
                case 18:
                        pGraph->SetYTitle(tr("F_t [N/m]"));
                        break;
                case 19:
                        pGraph->SetYTitle(tr("F_n [N/m]"));
                        break;
                case 20:
                        pGraph->SetYTitle(tr("It"));
                        break;
                case 21:
                        pGraph->SetYTitle(tr("Mach"));
                        break;
                case 22:
                        pGraph->SetYTitle(tr("Gam.[m2/s]"));
                        break;
                case 23:
                        pGraph->SetYTitle(tr("Fa_a"));
                        break;
                case 24:
                        pGraph->SetYTitle(tr("Fa_t"));
                        break;
                default:
                        pGraph->SetYTitle(tr("Pos [m]"));
                        break;
                }
        }
}

void QBEM::SetPolarGraphTitles(Graph* pGraph)
{
        if(!pGraph) return;
        switch (pGraph->GetXVariable())
        {
                case 0:
                        pGraph->SetXTitle(tr("Alpha [°]"));
                        break;
                case 1:
                        pGraph->SetXTitle(tr("Cl"));
                        break;
                case 2:
                        pGraph->SetXTitle(tr("Cd"));
                        break;
                case 3:
                        pGraph->SetXTitle(tr("Cl / Cd"));
                        break;
                default:
                        pGraph->SetXTitle(tr("Alpha [°]"));
                        break;
        }
        switch (pGraph->GetYVariable())
        {
                 case 0:
                         pGraph->SetYTitle(tr("Alpha [°]"));
                         break;
                 case 1:
                         pGraph->SetYTitle(tr("Cl"));
                         break;
                 case 2:
                         pGraph->SetYTitle(tr("Cd"));
                         break;
                 case 3:
                         pGraph->SetYTitle(tr("Cl / Cd"));
                         break;
                 default:
                         pGraph->SetYTitle(tr("Alpha [°]"));
                         break;
        }
}

void QBEM::SetScale()
{
        Set2DScale();
        Set3DScale();
}

void QBEM::SetScale(QRect CltRect)
{
        m_rCltRect = CltRect;
        m_rSingleRect.setRect(CltRect.x(), CltRect.y(), CltRect.width(), CltRect.height());

        Set2DScale();
        Set3DScale();
}

void QBEM::Set3DScale()
{
        if(m_iView==WingView) m_bResetglLegend = true;

        if(m_pWing)
        {
                //wing along X axis will take 3/4 of the screen
                m_glScaled = (GLfloat)(3./4.*2.0*m_GLScale/m_pWing->m_PlanformSpan);
                m_glViewportTrans.x = 0.0;
                m_glViewportTrans.y = 0.0;
                m_glViewportTrans.z = 0.0;
        }

}

















void QBEM::Set2DScale()
{
        if(m_bIs2DScaleSet && !m_bAutoScales) return;

        int w,h;

        h = m_rCltRect.height();
        w = m_rCltRect.width();
        int w2  = (int)(w/2);
        int h34  = (int)(3*h/4);

        QRect CpRect(0,0,w,h34);


        m_rSingleRect.setRect(40,10,m_rCltRect.right()-80,m_rCltRect.bottom()-230);


        QRect Rect1(0,0,w2,m_rCltRect.bottom()-00);
        QRect Rect2(w2,0,w2,m_rCltRect.bottom()-00);

        m_360CLGraph.SetDrawRect(Rect1);
        m_360CLGraph.SetDrawRect(Rect2);

        m_360CLGraph.Init();
        m_360CLGraph.Init();


        m_360CLGraph.SetAutoXUnit();
        m_360CLGraph.SetAutoXUnit();

}

void QBEM::UpdateBladeData()

{
        // fills combobox with blade associated to XBEM's current blade
        MainFrame *pMainFrame = (MainFrame *) s_pMainFrame;
        int i, size, pos;
        QString strong;
        pMainFrame->m_pctrlBEMPoint->clear();
        bool exists=false;




        if(!m_pBEMData || !m_pBEMData->m_BData.size())
        {

                pMainFrame->m_pctrlBEMPoint->setEnabled(false);

                selected_lambda = -1;


        }

        size = 0;
        if (m_pBEMData)
        {
        //count the number of simulations associated to the current blade
        for (i=0; i<m_pBEMData->m_BData.size(); i++)
        {

        pMainFrame->m_pctrlBEMPoint->addItem(m_pBEMData->m_BData.at(i)->lambdaglobal);
        exists=true;
        }

        if (exists)
        {

                // if any
                pMainFrame->m_pctrlBEMPoint->setEnabled(true);

                if(m_pBData)
                {

                        pos = pMainFrame->m_pctrlBEMPoint->findText(m_pBData->lambdaglobal);
                        if(pos>=0)
                        {
                            pMainFrame->m_pctrlBEMPoint->setCurrentIndex(pos);
                            strong = pMainFrame->m_pctrlBEMPoint->itemText(pos);
                            m_pBData = GetBladeData(strong);
                            selected_lambda = pos;
                        }
                        else
                        {
                            pMainFrame->m_pctrlBEMPoint->setCurrentIndex(0);
                            strong = pMainFrame->m_pctrlBEMPoint->itemText(0);
                            m_pBData = GetBladeData(strong);
                            selected_lambda = -1;
                        }
                }
                else
                {
                    pMainFrame->m_pctrlBEMPoint->setCurrentIndex(0);
                    strong = pMainFrame->m_pctrlBEMPoint->itemText(0);
                    m_pBData = GetBladeData(strong);
                    selected_lambda = -1;
                }

        }

    }

        if (!exists)
        {
                // otherwise disable control
                pMainFrame->m_pctrlBEMPoint->setEnabled(false);
                m_pBData = NULL;
                selected_lambda = -1;
        }



        CreateRotorCurves();


}

void QBEM::UpdateCurve()
{
        MainFrame *pMainFrame = (MainFrame*)s_pMainFrame;

        if(m_iView == CharView && m_pBEMData)
        {
                m_pBEMData->m_Color = m_CurveColor;
                m_pBEMData->m_Style = m_CurveStyle;
                m_pBEMData->m_Width = (int)m_CurveWidth;
                CreateRotorCurves();
        }
        else if (m_iView == PowerView && m_pTBEMData)
        {
                m_pTBEMData->m_Color = m_CurveColor;
                m_pTBEMData->m_Style = m_CurveStyle;
                m_pTBEMData->m_Width = (int)m_CurveWidth;
                CreatePowerCurves();
        }
        else if (m_iView == PolarView && m_pCur360Polar)
        {
                m_pCur360Polar->m_Color = m_CurveColor;
                m_pCur360Polar->m_Style = m_CurveStyle;
                m_pCur360Polar->m_Width = (int)m_CurveWidth;
                CreatePolarCurve();
        }

        UpdateView();
        pMainFrame->SetSaveState(false);
}

void QBEM::UpdateTurbineBladeData()

{


        MainFrame *pMainFrame = (MainFrame *) s_pMainFrame;
        int i, size, pos;
        QString strong;
        pMainFrame->m_pctrlTurbinePoint->clear();
        bool exists=false;




        if(!m_pTBEMData || !m_pTBEMData->m_BData.size())
        {
                pMainFrame->m_pctrlTurbinePoint->setEnabled(false);
                selected_windspeed = -1;
        }

        size = 0;

        if (m_pTBEMData)
        {
        //count the number of simulations associated to the current wing
        for (i=0; i<m_pTBEMData->m_BData.size(); i++)
        {
        pMainFrame->m_pctrlTurbinePoint->addItem(m_pTBEMData->m_BData.at(i)->windspeedStr);
        exists=true;
        }

        if (exists)
        {

                // if any
                pMainFrame->m_pctrlTurbinePoint->setEnabled(true);

                if(m_pTurbineBData)
                {

                        pos = pMainFrame->m_pctrlTurbinePoint->findText(m_pTurbineBData->windspeedStr);
                        if(pos>=0)
                        {
                            pMainFrame->m_pctrlTurbinePoint->setCurrentIndex(pos);
                            strong = pMainFrame->m_pctrlTurbinePoint->itemText(pos);
                            m_pTurbineBData = GetTurbineBladeData(strong);
                            selected_windspeed = pos;
                        }
                        else
                        {
                            pMainFrame->m_pctrlTurbinePoint->setCurrentIndex(0);
                            strong = pMainFrame->m_pctrlTurbinePoint->itemText(0);
                            m_pTurbineBData = GetTurbineBladeData(strong);
                            selected_windspeed = -1;
                        }
                }
                else
                {
                    pMainFrame->m_pctrlTurbinePoint->setCurrentIndex(0);
                    strong = pMainFrame->m_pctrlTurbinePoint->itemText(0);
                    m_pTurbineBData = GetTurbineBladeData(strong);
                    selected_windspeed = -1;
                }

        }

    }

        if (!exists)
        {


                // otherwise disable control
                pMainFrame->m_pctrlTurbinePoint->setEnabled(false);
                m_pTurbineBData = NULL;
                selected_windspeed = -1;
        }

        OnSetWeibullA(m_pctrla->value());
        OnSetWeibullK(m_pctrlk->value());
}

void QBEM::Update360Polars()
{

        MainFrame *pMainFrame = (MainFrame *) s_pMainFrame;
        int i, size, pos;
        CPolar *pPolar;
        QString strong;
        pMainFrame->m_pctrlBEM360Polars->clear();





        if(!m_pFoil || !m_pFoil->m_FoilName.length())
        {
                pMainFrame->m_pctrlBEM360Polars->setEnabled(false);
                pMainFrame->m_pctrlBEM360Polars->clear();
                return;
        }



        size = 0;

        for (i=0; i < s_poa360Polar->size(); i++)
        {
                pPolar = (CPolar*) s_poa360Polar->at(i);
                if(pPolar->m_FoilName == m_pFoil->m_FoilName)
                {
                        size++;
                }
        }
        if (size)
        {

                // if any
                pMainFrame->m_pctrlBEM360Polars->setEnabled(true);

                for (i=0; i < s_poa360Polar->size() ; i++)
                {
                        pPolar = (CPolar*)s_poa360Polar->at(i);
                        if(pPolar->m_FoilName == m_pFoil->m_FoilName && pPolar->m_ParentPlrName == m_pCurPolar->m_PlrName)
                        {
                                pMainFrame->m_pctrlBEM360Polars->addItem(pPolar->m_PlrName);
                        }
                }
                if(m_pCur360Polar)
                {
                        pos = pMainFrame->m_pctrlBEM360Polars->findText(m_pCur360Polar->m_PlrName);



                        if(pos>=0)
                        {
                            pMainFrame->m_pctrlBEM360Polars->setCurrentIndex(pos);
                            strong = pMainFrame->m_pctrlBEM360Polars->itemText(pos);
                            m_pCur360Polar = Get360Polar(m_pFoil->m_FoilName, strong);


                        }
                        else
                        {
                                pMainFrame->m_pctrlBEM360Polars->setCurrentIndex(0);
                                strong = pMainFrame->m_pctrlBEM360Polars->itemText(0);
                                m_pCur360Polar = Get360Polar(m_pFoil->m_FoilName, strong);
                        }
                }
                else
                {


                    pMainFrame->m_pctrlBEM360Polars->setCurrentIndex(0);
                    strong = pMainFrame->m_pctrlBEM360Polars->itemText(0);
                    m_pCur360Polar = Get360Polar(m_pFoil->m_FoilName, strong);
                }
        }
        else
        {
                // otherwise disable control
                m_pCur360Polar = NULL;
                pMainFrame->m_pctrlBEM360Polars->setEnabled(false);
        }

     CreatePolarCurve();

     if (m_pCur360Polar) SetCurveParams();
     else FillComboBoxes(false);


     if (m_pCur360Polar)
     {
         m_360Name->setText(m_pCur360Polar->m_PlrName);
        //m_pctrlCD90->setValue(m_pCur360Polar->m_XTop);
     }
}

void QBEM::UpdateFoils()
{

        MainFrame *pMainFrame = (MainFrame * ) s_pMainFrame;
        int posi;
        QString strong;

        pMainFrame->m_pctrlBEMFoils->clear();

        for (int i=0;i<s_poaFoil->size();i++)
        {
            CFoil *pFoil = (CFoil *) s_poaFoil->at(i);

            pMainFrame->m_pctrlBEMFoils->addItem(pFoil->m_FoilName);


        }


        if (pMainFrame->m_pctrlBEMFoils->count())
        {
                pMainFrame->m_pctrlBEMFoils->setEnabled(true);
                //select the current foil, if any...
                if (m_pFoil)
                {
                        posi = pMainFrame->m_pctrlBEMFoils->findText(m_pFoil->m_FoilName);
                        if (posi>=0) pMainFrame->m_pctrlBEMFoils->setCurrentIndex(posi);

                }
                //... else select the first
                else
                {
                        // if error, select the first...
                        pMainFrame->m_pctrlBEMFoils->setCurrentIndex(0);
                        strong = pMainFrame->m_pctrlBEMFoils->itemText(0);
                        m_pFoil = GetFoil(strong);
                }
        }
        else
        {
                pMainFrame->m_pctrlBEMFoils->clear();
                pMainFrame->m_pctrlBEMFoils->setEnabled(false);
                m_pFoil = NULL;

        }

        UpdatePolars();





}

void QBEM::UpdatePolars()
{

        MainFrame *pMainFrame = (MainFrame *) s_pMainFrame;
        int i, size, pos;
        CPolar *pPolar;
        QString strong;
        pMainFrame->m_pctrlBEMPolars->clear();

        m_b360PolarChanged = true;

        if(!m_pFoil || !m_pFoil->m_FoilName.length())
        {
                pMainFrame->m_pctrlBEMPolars->setEnabled(false);
                pMainFrame->m_pctrlBEMPolars->clear();
                pMainFrame->m_pctrlBEMPolars->setEnabled(false);
        }

        size = 0;
        //count the number of polars associated to the current foil
        for (i=0; i<s_poaPolar->size(); i++)
        {
                pPolar = (CPolar*) s_poaPolar->at(i);
                if(pPolar->m_FoilName == m_pFoil->m_FoilName)
                {
                        size++;
                }
        }
        if (size)
        {

                // if any
                pMainFrame->m_pctrlBEMPolars->setEnabled(true);

                for (i=0; i < s_poaPolar->size() ; i++)
                {
                        pPolar = (CPolar*)s_poaPolar->at(i);
                        if(pPolar->m_FoilName == m_pFoil->m_FoilName)
                        {
                                pMainFrame->m_pctrlBEMPolars->addItem(pPolar->m_PlrName);
                        }
                }
                if(m_pCurPolar)
                {
                        pos = pMainFrame->m_pctrlBEMPolars->findText(m_pCurPolar->m_PlrName);
                        if(pos>=0)
                        {
                            pMainFrame->m_pctrlBEMPolars->setCurrentIndex(pos);
                            strong = pMainFrame->m_pctrlBEMPolars->itemText(pos);
                            m_pCurPolar = GetPolar(m_pFoil->m_FoilName, strong);
                        }
                        else
                        {
                                pMainFrame->m_pctrlBEMPolars->setCurrentIndex(0);
                                strong = pMainFrame->m_pctrlBEMPolars->itemText(0);
                                m_pCurPolar = GetPolar(m_pFoil->m_FoilName, strong);

                        }
                }
                else
                {
                        pMainFrame->m_pctrlBEMPolars->setCurrentIndex(0);
                        strong = pMainFrame->m_pctrlBEMPolars->itemText(0);
                        m_pCurPolar = GetPolar(m_pFoil->m_FoilName, strong);

                }
        }
        else
        {
                // otherwise disable control
                pMainFrame->m_pctrlBEMPolars->setEnabled(false);
                m_pCurPolar = NULL;
        }


        Update360Polars();
}

void QBEM::UpdateRotorSimulation()

{

        MainFrame *pMainFrame = (MainFrame *) s_pMainFrame;
        int i, size, pos;
        QString strong;
        pMainFrame->m_pctrlBEMSim->clear();



        if(!m_pWing || !m_pWing->m_WingName.length())
        {
                pMainFrame->m_pctrlBEMSim->setEnabled(false);

        }

        size = 0;

        //count the number of simulations associated to the current blade
        for (i=0; i<s_poaBEMData.size(); i++)
        {
            if (m_pWing)
            {
                if(m_pWing->m_WingName == s_poaBEMData.at(i)->m_WingName)
                {
                        size++;
                }
            }
        }

        if (size)
        {

                // if any
                pMainFrame->m_pctrlBEMSim->setEnabled(true);

                for (i=0; i < s_poaBEMData.size() ; i++)
                {
                        if(m_pWing->m_WingName == s_poaBEMData.at(i)->m_WingName)
                        {
                                pMainFrame->m_pctrlBEMSim->addItem(s_poaBEMData.at(i)->m_BEMName);
                        }
                }
                if(m_pBEMData)
                {
                        pos = pMainFrame->m_pctrlBEMSim->findText(m_pBEMData->m_BEMName);
                        if(pos>=0)
                        {
                            pMainFrame->m_pctrlBEMSim->setCurrentIndex(pos);
                            strong = pMainFrame->m_pctrlBEMSim->itemText(pos);
                            m_pBEMData = GetRotorSimulation(m_pWing->m_WingName, strong);
                        }
                        else
                        {
                            pMainFrame->m_pctrlBEMSim->setCurrentIndex(0);
                            strong = pMainFrame->m_pctrlBEMSim->itemText(0);
                            m_pBEMData = GetRotorSimulation(m_pWing->m_WingName, strong);
                        }
                }
                else
                {
                        pMainFrame->m_pctrlBEMSim->setCurrentIndex(0);
                        strong = pMainFrame->m_pctrlBEMSim->itemText(0);
                        m_pBEMData = GetRotorSimulation(m_pWing->m_WingName, strong);
                }
        }
        else
        {
                // otherwise disable control
                pMainFrame->m_pctrlBEMSim->setEnabled(false);
                m_pBEMData = NULL;
        }





        UpdateBladeData();

        InitBladeSimulationParams(m_pBEMData);

        if (m_pBEMData) SetCurveParams();
        else FillComboBoxes(false);





}

void QBEM::UpdateTurbines()
{
    QString strong;

    MainFrame *pMainFrame = (MainFrame*) s_pMainFrame;

    pMainFrame->m_pctrlTurbine->clear();;


    for (int i=0;i<s_poaTData.size();i++)
    {
       pMainFrame->m_pctrlTurbine->addItem(s_poaTData.at(i)->m_TurbineName);;
    }

   if(pMainFrame->m_pctrlTurbine->count())
   {
       pMainFrame->m_pctrlTurbine->setEnabled(true);

       if (m_pTData)
       {
           int pos = pMainFrame->m_pctrlTurbine->findText(m_pTData->m_TurbineName);
           if (pos>=0)
           {
               pMainFrame->m_pctrlTurbine->setCurrentIndex(pos);
               strong = pMainFrame->m_pctrlTurbine->itemText(pos);
               m_pTData = GetTurbine(strong);
           }
           else
           {
               pMainFrame->m_pctrlTurbine->setCurrentIndex(0);
               strong = pMainFrame->m_pctrlTurbine->itemText(0);
               m_pTData = GetTurbine(strong);
           }
       }
       else
       {
               pMainFrame->m_pctrlTurbine->setCurrentIndex(0);
               strong = pMainFrame->m_pctrlTurbine->itemText(0);
               m_pTData = GetTurbine(strong);
       }
   }
   else
   {
       pMainFrame->m_pctrlTurbine->setEnabled(false);
       m_pTData = NULL;
   }



    InitTurbineData(m_pTData);


    UpdateTurbineSimulation();


}

void QBEM::UpdateUnits()
{
    MainFrame *pMainFrame = (MainFrame *) s_pMainFrame;
    SimuWidget *pSimuWidget = (SimuWidget * ) m_pSimuWidget;
    QString str;
    GetSpeedUnit(str, pMainFrame->m_SpeedUnit);
    pSimuWidget->speed1->setText(str);
    pSimuWidget->speed2->setText(str);
    pSimuWidget->speed3->setText(str);

    InitTurbineData(m_pTData);

}

void QBEM::UpdateGeom()
{
    m_bResetglGeom = true;

    UpdateView();
}

void QBEM::UpdateView()
{

    MainFrame *pMainFrame = (MainFrame*)s_pMainFrame;
    pMainFrame->SetCentralWidget();

    if (m_iView==WingView)
    {
      m_pGLWidget->m_iView=WingView;
      m_pGLWidget->draw();
      m_pGLWidget->updateGL();
    }
    else
    {
       m_p2DWidget->update();
    }




}

void QBEM::UpdateWings()
{


    QString strong;
    MainFrame *pMainFrame = (MainFrame*) s_pMainFrame;
    CBlade *pWing;

    pMainFrame->m_pctrlBEMWing->clear();


   for (int i=0;i<s_poaBEMWings->size();i++)
    {
       pWing= (CBlade *) s_poaBEMWings->at(i);
       pMainFrame->m_pctrlBEMWing->addItem(pWing->m_WingName);
    }

   if(pMainFrame->m_pctrlBEMWing->count())
   {
       pMainFrame->m_pctrlBEMWing->setEnabled(true);

       if (m_pWing)
       {
           int pos = pMainFrame->m_pctrlBEMWing->findText(m_pWing->m_WingName);
           if(pos>=0)
           {
               pMainFrame->m_pctrlBEMWing->setCurrentIndex(pos);
               strong = pMainFrame->m_pctrlBEMWing->itemText(pos);
               m_pWing = GetWing(strong);
           }
           else
           {
               pMainFrame->m_pctrlBEMWing->setCurrentIndex(0);
               strong = pMainFrame->m_pctrlBEMWing->itemText(0);
               m_pWing = GetWing(strong);
           }
       }
       else
       {
               pMainFrame->m_pctrlBEMWing->setCurrentIndex(0);
               strong = pMainFrame->m_pctrlBEMWing->itemText(0);
               m_pWing = GetWing(strong);
       }
   }
   else
   {
   pMainFrame->m_pctrlBEMWing->setEnabled(false);
   m_pWing = NULL;
   }

   UpdateRotorSimulation();

   InitWingTable();

}

void QBEM::UpdateTurbineSimulation()

{
        MainFrame *pMainFrame = (MainFrame *) s_pMainFrame;
        int i, size, pos;
        QString strong;
        pMainFrame->m_pctrlTurbineSim->clear();



        if(!m_pTBEMData)
        {
                pMainFrame->m_pctrlTurbineSim->setEnabled(false);

        }

        size = 0;

        //count the number of simulations associated to the current turbine
        for (i=0; i<s_poaTBEMData.size(); i++)
        {
            if (m_pTData)
            {
                if(m_pTData->m_TurbineName == s_poaTBEMData.at(i)->m_TurbineName)
                {
                        size++;
                }
            }
        }

        if (size)
        {

                // if any
                pMainFrame->m_pctrlTurbineSim->setEnabled(true);

                for (i=0; i < s_poaTBEMData.size() ; i++)
                {
                        if(m_pTData->m_TurbineName == s_poaTBEMData.at(i)->m_TurbineName)
                        {
                                pMainFrame->m_pctrlTurbineSim->addItem(s_poaTBEMData.at(i)->m_SimName);
                        }
                }
                if(m_pTBEMData)
                {
                        pos = pMainFrame->m_pctrlTurbineSim->findText(m_pTBEMData->m_SimName);
                        if(pos>=0)
                        {
                            pMainFrame->m_pctrlTurbineSim->setCurrentIndex(pos);
                            strong = pMainFrame->m_pctrlTurbineSim->itemText(pos);
                            m_pTBEMData = GetTurbineSimulation(m_pTData->m_TurbineName, strong);
                        }
                        else
                        {
                            pMainFrame->m_pctrlTurbineSim->setCurrentIndex(0);
                            strong = pMainFrame->m_pctrlTurbineSim->itemText(0);
                            m_pTBEMData = GetTurbineSimulation(m_pTData->m_TurbineName, strong);
                        }
                }
                else
                {
                    pMainFrame->m_pctrlTurbineSim->setCurrentIndex(0);
                    strong = pMainFrame->m_pctrlTurbineSim->itemText(0);
                    m_pTBEMData = GetTurbineSimulation(m_pTData->m_TurbineName, strong);
                }
        }
        else
        {
                // otherwise disable control
                pMainFrame->m_pctrlTurbineSim->setEnabled(false);
                m_pTBEMData = NULL;
        }


        if (m_pTBEMData) SetCurveParams();
        else FillComboBoxes(false);

        UpdateTurbineBladeData();

        InitTurbineSimulationParams(m_pTBEMData);






}

void QBEM::WheelEvent(QWheelEvent *event)
{
        //The mouse button has been wheeled
        //Process the message
        QPoint pt(event->x(), event->y()); //client coordinates

        if(m_iView==WingView)
        {
                if(m_pWing)
                {
                        //zoom wing
                        if(event->delta()>0) m_glScaled /= (GLfloat)1.06;
                        else                 m_glScaled *= (GLfloat)1.06;
                        UpdateView();
                }
        }
        else if(m_iView == PolarView || m_iView==CharView || m_iView == PowerView )
        {
                m_pCurGraph = GetGraph(pt);
                if(m_pCurGraph && m_pCurGraph->IsInDrawRect(pt))
                {
                        if (m_bXPressed)
                        {
                                //zoom x scale
                                m_pCurGraph->SetAutoX(false);
                                if(event->delta()>0) m_pCurGraph->Scalex(1.06);
                                else                 m_pCurGraph->Scalex(1.0/1.06);
                        }
                        else if(m_bYPressed)
                        {
                                //zoom y scale
                                m_pCurGraph->SetAutoY(false);
                                if(event->delta()>0) m_pCurGraph->Scaley(1.06);
                                else                 m_pCurGraph->Scaley(1.0/1.06);
                        }
                        else
                        {
                                //zoom both
                                m_pCurGraph->SetAuto(false);
                                if(event->delta()>0) m_pCurGraph->Scale(1.06);
                                else                 m_pCurGraph->Scale(1.0/1.06);
                        }

                        m_pCurGraph->SetAutoXUnit();
                        m_pCurGraph->SetAutoYUnit();
                        UpdateView();

                }
            }


}
