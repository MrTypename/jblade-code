/****************************************************************************

    OptimizeDlg Class
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

#include "OptimizeDlg.h"
#include "BEM.h"
#include <QtWidgets>
#include "../Misc/FloatEdit.h"
#include <QDebug>
#include "../Objects/Wing.h"
#include "../Objects/Polar.h"
#include "../MainFrame.h"
#include "../Globals.h"





OptimizeDlg::OptimizeDlg(void *pParent)
{
    setWindowTitle(tr("Optimize Blade Geometry"));
    m_pParent = pParent;


    SetupLayout();

    Connect();


}


void OptimizeDlg::SetupLayout()       
{
    QBEM* pBEM = (QBEM *) m_pParent;
    MainFrame *pMainFrame = (MainFrame *) pBEM->s_pMainFrame;

    QButtonGroup *Group1 = new QButtonGroup;
    QButtonGroup *Group2 = new QButtonGroup;

    QSizePolicy szPolicyMinimum;
    szPolicyMinimum.setHorizontalPolicy(QSizePolicy::Minimum);
    szPolicyMinimum.setVerticalPolicy(QSizePolicy::Minimum);

    OptNone = new QRadioButton(tr("None"));

    OptSchmitz = new QRadioButton(tr("Schmitz"));
    OptBetz = new QRadioButton(tr("Betz"));
    OptLinear = new QRadioButton(tr("Linear"));

    FromPosChord = new QComboBox;
    FromPosChordLabel = new QLabel(tr("From Position"));
    ToPosChord = new QComboBox;
    ToPosChordLabel = new QLabel(tr("to Position"));

    FromChord = new FloatEdit;
    FromChordLabel = new QLabel(tr("C at Pos 1"));
    ToChord = new FloatEdit;
    ToChordLabel = new QLabel(tr("C at Pos 2"));


    QGridLayout *OptChordLayout = new QGridLayout;
    QGridLayout *OptTwistLayout = new QGridLayout;

    QHBoxLayout *LambdaLayout = new QHBoxLayout;
    Lambda0 = new FloatEdit;
    Lambda0->setSizePolicy(szPolicyMinimum);
    Lambda0Label = new QLabel(tr("Optimize for Tip Speed Ratio"));
    LambdaLayout->addWidget(Lambda0Label);
    LambdaLayout->addWidget(Lambda0);
    LambdaLayout->addWidget(FromPosChordLabel);
    LambdaLayout->addWidget(FromPosChord);
    LambdaLayout->addWidget(ToPosChordLabel);
    LambdaLayout->addWidget(ToPosChord);

    Lambda0->SetMin(0.1);
    Lambda0->SetPrecision(1);

    OptNone2 = new QRadioButton(tr("None"));
    OptStall = new QRadioButton(tr("Stall"));
    OptGlide = new QRadioButton(tr("Opt Lift/Drag"));
    OptLinear2 = new QRadioButton(tr("Linear"));
    FromTwist = new FloatEdit;
    ToTwist = new FloatEdit;
    FromTwistLabel = new QLabel(tr("T at Pos 1"));
    ToTwistLabel = new QLabel(tr("T at Pos 2"));
    DeltaTwist = new FloatEdit;
    DeltaTwistLabel = new QLabel(tr("+  -"));

    LambdaStall = new FloatEdit;
    LambdaStallLabel = new QLabel(tr("at Tip Speed Ratio"));

    QString str;
    GetLengthUnit(str, pMainFrame->m_LengthUnit);

    LT1 = new QLabel(tr("°"));
    LT2 = new QLabel(tr("°"));
    LT3 = new QLabel(tr("°"));
    LT4 = new QLabel(tr("°"));
    LC1 = new QLabel;
    LC2 = new QLabel;
    LC1->setText(str);
    LC2->setText(str);

    Group1->addButton(OptNone);
    Group1->addButton(OptSchmitz);
    Group1->addButton(OptBetz);
    Group1->addButton(OptLinear);

    Group2->addButton(OptNone2);
    Group2->addButton(OptGlide);
    Group2->addButton(OptStall);
    Group2->addButton(OptLinear2);




    OptTwistLayout->addWidget(OptNone2,1,1);
    OptTwistLayout->addWidget(OptGlide,2,1);
    OptTwistLayout->addWidget(DeltaTwistLabel,2,2);
    OptTwistLayout->addWidget(DeltaTwist,2,3);
    OptTwistLayout->addWidget(LT1,2,4);
    OptTwistLayout->addWidget(OptStall,3,1);
    OptTwistLayout->addWidget(LambdaStallLabel,3,2);
    OptTwistLayout->addWidget(LambdaStall,3,3);
    OptTwistLayout->addWidget(LT2,3,4);
    OptTwistLayout->addWidget(OptLinear2,4,1);
    OptTwistLayout->addWidget(FromTwistLabel,4,2);
    OptTwistLayout->addWidget(FromTwist,4,3);
    OptTwistLayout->addWidget(LT3,4,4);
    OptTwistLayout->addWidget(ToTwistLabel,5,2);
    OptTwistLayout->addWidget(ToTwist,5,3);
    OptTwistLayout->addWidget(LT4,5,4);




    FromChord->SetMin(0.001);
    FromChord->SetPrecision(2);

    OptChordLayout->addWidget(OptNone,1,1);
    OptChordLayout->addWidget(OptSchmitz,2,1);
    OptChordLayout->addWidget(OptBetz,3,1);
    OptChordLayout->addWidget(OptLinear,4,1);
    OptChordLayout->addWidget(FromChord,4,3);
    OptChordLayout->addWidget(ToChord,5,3);
    OptChordLayout->addWidget(LC1,4,4);
    OptChordLayout->addWidget(LC2,5,4);
    OptChordLayout->addWidget(FromChordLabel,4,2);
    OptChordLayout->addWidget(ToChordLabel,5,2);

    Optimize = new QPushButton(tr("Optimize"));
    Done = new QPushButton(tr("Done"));

    QGroupBox *TwistGroup = new QGroupBox(tr("Opt Twist"));
    TwistGroup->setLayout(OptTwistLayout);

    QGroupBox *ChordGroup = new QGroupBox(tr("Opt Chord"));
    ChordGroup->setLayout(OptChordLayout);



    QVBoxLayout *mainLayout = new QVBoxLayout;

    QHBoxLayout *optLayout = new QHBoxLayout;

    optLayout->addWidget(TwistGroup);
    optLayout->addWidget(ChordGroup);

    mainLayout->addLayout(LambdaLayout);
    mainLayout->addLayout(optLayout);
    mainLayout->addWidget(Optimize);
    mainLayout->addWidget(Done);

    setLayout(mainLayout);









}


void OptimizeDlg::InitDialog()
{
    int positions;
    QString pos;

    QBEM* pBEM = (QBEM *) m_pParent;

    positions = pBEM->m_pWing->m_NPanel;

    for (int i=1;i<=positions+1;i++)
    {
        pos.sprintf("%.1f",double(i));
        FromPosChord->addItem(pos);
        ToPosChord->addItem(pos);
    }

    ToPosChord->setCurrentIndex(positions);

    Lambda0->SetValue(pBEM->dlg_lambda);
    OptNone->setChecked(true);
    OptNone2->setChecked(true);
    FromChord->setEnabled(false);
    ToChord->setEnabled(false);
    FromTwist->setEnabled(false);
    ToTwist->setEnabled(false);
    LambdaStall->setEnabled(false);
    DeltaTwist->setEnabled(false);




}


void OptimizeDlg::CheckButtons()
{

    if (OptBetz->isChecked())
    {
        FromChord->setEnabled(false);
        ToChord->setEnabled(false);
    }

    if (OptSchmitz->isChecked())
    {
        FromChord->setEnabled(false);
        ToChord->setEnabled(false);
    }

    if (OptLinear->isChecked())
    {
        FromChord->setEnabled(true);
        ToChord->setEnabled(true);
    }
    if (OptNone->isChecked())
    {
        FromChord->setEnabled(false);
        ToChord->setEnabled(false);
    }
    if (OptNone2->isChecked())
    {
        FromTwist->setEnabled(false);
        ToTwist->setEnabled(false);
        LambdaStall->setEnabled(false);
        DeltaTwist->setEnabled(false);
    }
    if (OptGlide->isChecked())
    {
        FromTwist->setEnabled(false);
        ToTwist->setEnabled(false);
        LambdaStall->setEnabled(false);
        DeltaTwist->setEnabled(true);
    }
    if (OptStall->isChecked())
    {
        FromTwist->setEnabled(false);
        ToTwist->setEnabled(false);
        LambdaStall->setEnabled(true);
        DeltaTwist->setEnabled(false);
    }
    if (OptLinear2->isChecked())
    {
        FromTwist->setEnabled(true);
        ToTwist->setEnabled(true);
        LambdaStall->setEnabled(false);
        DeltaTwist->setEnabled(false);
    }



}

void OptimizeDlg::Connect()
{
    connect(OptBetz, SIGNAL(clicked()), SLOT(CheckButtons()));
    connect(OptSchmitz, SIGNAL(clicked()), SLOT(CheckButtons()));
    connect(OptLinear, SIGNAL(clicked()), SLOT(CheckButtons()));
    connect(OptNone, SIGNAL(clicked()), SLOT(CheckButtons()));
    connect(OptNone2, SIGNAL(clicked()), SLOT(CheckButtons()));
    connect(OptLinear2, SIGNAL(clicked()), SLOT(CheckButtons()));
    connect(OptGlide, SIGNAL(clicked()), SLOT(CheckButtons()));
    connect(OptStall, SIGNAL(clicked()), SLOT(CheckButtons()));


    connect(Optimize, SIGNAL(clicked()), SLOT(OnOptimize()));
    connect(Done, SIGNAL(clicked()), SLOT(accept()));







}


void OptimizeDlg::OnOptimize()
{



    QBEM* pBEM = (QBEM *) m_pParent;
    MainFrame *pMainFrame = (MainFrame *) pBEM->s_pMainFrame;

    pBEM->InitDialog(pBEM->m_pWing);

    QString strong;
    double alpha,alphalocal, max, lambdalocal, alphaplus=DeltaTwist->Value();
    double lambda = Lambda0->Value();
    double lambdastall = LambdaStall->Value();

    if (OptGlide->isChecked())
    {

    for (int i=int(FromPosChord->currentText().toDouble()-1);i <= int(ToPosChord->currentText().toDouble()-1);i++)
    {
       strong = pBEM->m_pWing->m_Polar.at(i);

       if (strong != pBEM->m_cylPolarName)
       {
       for (int j=0;j<pBEM->s_poa360Polar->size();j++)
       {
           CPolar *pPolar = (CPolar *) pBEM->s_poa360Polar->at(j);
           if (strong == pPolar->m_PlrName && pBEM->m_pWing->m_RFoil.at(i) == pPolar->m_FoilName)
           {
               max=0;
               alpha=0;
               for (int k=0;k < pPolar->m_Cl.size();k++)
               {
                   if (pPolar->m_Alpha.at(k)>0 && pPolar->m_Alpha.at(k) < 80)
                   {

                           if (pPolar->m_Cl[k]/pPolar->m_Cd[k] > max)
                           {
                           max=pPolar->m_Cl[k]/pPolar->m_Cd[k];
                           alpha=pPolar->m_Alpha[k];
                           }

                   }
               }
               lambdalocal=lambda*pBEM->m_pWing->m_TPos[i]/pBEM->m_pWing->m_TPos[pBEM->m_pWing->m_NPanel];
               alphalocal = atan(1/lambdalocal*2/3)/2/PI*360;
               pBEM->m_pWing->m_TTwist[i]=alphalocal-(alpha+alphaplus);

           }

       }

    }

    }
    }

    if (OptStall->isChecked())
    {
        for (int i=int(FromPosChord->currentText().toDouble()-1);i <= int(ToPosChord->currentText().toDouble()-1);i++)
        {
           strong = pBEM->m_pWing->m_Polar.at(i);


           if (strong != pBEM->m_cylPolarName)
           {


           for (int j=0;j<pBEM->s_poa360Polar->size();j++)
           {
               CPolar *pPolar = (CPolar *) pBEM->s_poa360Polar->at(j);
               if (strong == pPolar->m_PlrName && pBEM->m_pWing->m_RFoil.at(i) == pPolar->m_FoilName)
               {
                   max=0;
                   alpha=0;
                   for (int k=0;k < pPolar->m_Cl.size();k++)
                   {
                       if (pPolar->m_Alpha.at(k)>0 && pPolar->m_Alpha.at(k) < 80)
                       {

                               if (pPolar->m_Cl[k] > max)
                               {
                               max=pPolar->m_Cl[k];
                               alpha=pPolar->m_Alpha[k];
                               }

                       }
                   }
                   lambdalocal=lambdastall*pBEM->m_pWing->m_TPos[i]/pBEM->m_pWing->m_TPos[pBEM->m_pWing->m_NPanel];
                   alphalocal = atan(1/lambdalocal*2/3)/2/PI*360;
                   pBEM->m_pWing->m_TTwist[i]=alphalocal-alpha;

               }

           }

         }

        }

    }

    if(OptLinear2->isChecked())
    {

       for (int i=int(FromPosChord->currentText().toDouble()-1);i <= int(ToPosChord->currentText().toDouble()-1);i++)
       {

           int from,to;
           CBlade *pWing = pBEM->m_pWing;
           from = int(FromPosChord->currentText().toDouble()-1);
           to = int(ToPosChord->currentText().toDouble()-1);
           pWing->m_TTwist[i] = (FromTwist->Value()+(ToTwist->Value()-FromTwist->Value())/(pWing->m_TPos[to]-pWing->m_TPos[from])*(pWing->m_TPos[i]-pWing->m_TPos[from]));

       }

    }


    double CL=0;
    double blades = double(pBEM->m_pctrlBlades->value());

    if (OptBetz->isChecked() || OptSchmitz->isChecked())
    {

        for (int i=int(FromPosChord->currentText().toDouble()-1);i <= int(ToPosChord->currentText().toDouble()-1);i++)
        {


            strong = pBEM->m_pWing->m_Polar.at(i);


            if (strong != pBEM->m_cylPolarName)
            {



            double DeltaAlpha = Get360Polar(pBEM->m_pWing->m_RFoil[i],pBEM->m_pWing->m_Polar.at(i))->m_Alpha.at(1)-Get360Polar(pBEM->m_pWing->m_RFoil[i],pBEM->m_pWing->m_Polar.at(i))->m_Alpha.at(0);
            alpha = atan(1/Lambda0->Value()*pBEM->m_pWing->m_TPos[pBEM->m_pWing->m_NPanel]/pBEM->m_pWing->m_TPos[i]*2/3)/2/PI*360-pBEM->m_pWing->m_TTwist[i];
            bool found=false;
            for (int j=0; j< Get360Polar(pBEM->m_pWing->m_RFoil[i],pBEM->m_pWing->m_Polar.at(i))->m_Alpha.size();j++)
            {
                if (Get360Polar(pBEM->m_pWing->m_RFoil[i],pBEM->m_pWing->m_Polar.at(i))->m_Alpha.at(j) >= alpha && !found)
                {
                CL = Get360Polar(pBEM->m_pWing->m_RFoil[i],pBEM->m_pWing->m_Polar.at(i))->m_Cl.at(j-1)+(Get360Polar(pBEM->m_pWing->m_RFoil[i],pBEM->m_pWing->m_Polar.at(i))->m_Cl.at(j)-Get360Polar(pBEM->m_pWing->m_RFoil[i],pBEM->m_pWing->m_Polar.at(i))->m_Cl.at(j-1))/DeltaAlpha*(alpha-Get360Polar(pBEM->m_pWing->m_RFoil[i],pBEM->m_pWing->m_Polar.at(i))->m_Alpha.at(j-1));
                found = true;
                }
            }
             if (OptBetz->isChecked()&& CL != 0) pBEM->m_pWing->m_TChord[i] = (pBEM->m_pWing->m_TPos[pBEM->m_pWing->m_NPanel]/blades*16*PI/9/CL/Lambda0->Value()/pow(pow(pBEM->m_pWing->m_TPos[i]/pBEM->m_pWing->m_TPos[pBEM->m_pWing->m_NPanel]*Lambda0->Value(),2)+double(4/9),0.5));
             if (OptSchmitz->isChecked() && CL != 0) pBEM->m_pWing->m_TChord[i] = 16*PI/CL/blades*pBEM->m_pWing->m_TPos[i]*pow(sin(0.3333*atan(pBEM->m_pWing->m_TPos[pBEM->m_pWing->m_NPanel]/Lambda0->Value()/pBEM->m_pWing->m_TPos[i])),2);
            }
          }

    }

    if (OptLinear->isChecked())
    {
        for (int i=int(FromPosChord->currentText().toDouble()-1);i <= int(ToPosChord->currentText().toDouble()-1);i++)
        {
            int from,to;
            CBlade *pWing = pBEM->m_pWing;
            from = int(FromPosChord->currentText().toDouble()-1);
            to = int(ToPosChord->currentText().toDouble()-1);
            pWing->m_TChord[i] = (FromChord->Value()+(ToChord->Value()-FromChord->Value())/(pWing->m_TPos[to]-pWing->m_TPos[from])*(pWing->m_TPos[i]-pWing->m_TPos[from]))/pMainFrame->m_mtoUnit;
        }
    }




    pBEM->InitDialog(pBEM->m_pWing);

}

CPolar* OptimizeDlg::Get360Polar(QString m_FoilName, QString PolarName)
{

        QBEM* pBEM = (QBEM *) m_pParent;
        CPolar *pPolar;
        for (int i=0; i < pBEM->s_poa360Polar->size() ; i++)
        {
                pPolar = (CPolar *) pBEM->s_poa360Polar->at(i);
                if (pPolar->m_FoilName == m_FoilName && pPolar->m_PlrName == PolarName)
                {
                        return pPolar;

                }
        }
        return NULL;
}

