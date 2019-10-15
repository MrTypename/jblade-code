/****************************************************************************

    BladeStructureDlg Class
        Copyright (C) 2013 João Morgado jmorgado@ubi.pt

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

#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QtDebug>
#include <QtGui>
#include "BladeStructureDlg.h"
#include "BEM.h"
#include "../Miarex/Miarex.h"
#include "../Misc/FloatEdit.h"
#include "../Objects/Wing.h"
#include "../Objects/Polar.h"
#include "../Objects/Foil.h"
#include "../MainFrame.h"
#include "../Globals.h"


#include  <math.h>
#include <QtDebug>
#include "Blade.h"
#include "../MainFrame.h"
#include "../Globals.h"
#include "../Miarex/Miarex.h"
#include "../Miarex/LLTAnalysisDlg.h"



BladeStructureDlg::BladeStructureDlg(void *pParent)
{

    setWindowTitle(tr("Blade Material and Structure Options"));
    m_pParent = pParent;



   SetupLayout();

   Connect();

}


void BladeStructureDlg::SetupLayout()
{

    QHBoxLayout *CommandButtons = new QHBoxLayout;
    QGridLayout *MainLayout = new QGridLayout;
    QGridLayout *MaterialPropertiesLayout = new QGridLayout;
    QGridLayout *StructureOption1Layout = new QGridLayout;
    QGridLayout *StructureOption2Layout = new QGridLayout;
    QGridLayout *StructureOption3Layout = new QGridLayout;


    QButtonGroup *Group2 = new QButtonGroup;

    m_pctrlNewMaterialButton = new QPushButton(tr("New Material"));
    m_pctrlSelectMaterialButton = new QPushButton(tr("Select Material"));
    m_pctrlSelect2ndMaterialButton = new QPushButton(tr("Select 2nd Material"));

    m_pctrlNewMaterialSaveButton = new QPushButton(tr("Save New Material"));
    m_pctrlSelectMaterialApplyButton = new QPushButton(tr("Apply Material"));
    m_pctrlSelectMaterialApplyButton2 = new QPushButton(tr("Apply as 2nd Material"));
    m_pctrlSelectMaterialOKButton = new QPushButton(tr("OK"));
    m_pctrlMaterialCancelButton = new QPushButton(tr("Cancel"));

    m_pctrlNewMaterialNameLabel = new QLabel(tr("                           Material Name"));
    m_pctrlNewMaterialName     = new QLineEdit(tr("Material (1)"));
    m_pctrlNewMaterialName->setAlignment(Qt::AlignRight);

    m_pctrlNewMaterialDensityLabel = new QLabel(tr("                            Material Density"));
    m_pctrlNewMaterialDensity = new FloatEdit;
    m_pctrlNewMaterialDensity->SetMin(0);
    m_pctrlNewMaterialDensity->SetPrecision(3);
    m_pctrlNewMaterialDensity->SetValue(1.225);

    m_pctrlMaterialThicknessLabel = new QLabel(tr("Thickness [m]"));
    m_pctrlMaterialThickness = new FloatEdit;
    m_pctrlMaterialThickness->setAlignment(Qt::AlignLeft);
    m_pctrlMaterialThickness->SetMin(0);
    m_pctrlMaterialThickness->SetPrecision(3);
    m_pctrlMaterialThickness->SetValue(0.001);

    m_pctrlMaterialThicknessLabel2 = new QLabel(tr("Thickness [m]"));
    m_pctrlMaterialThickness2 = new FloatEdit;
    m_pctrlMaterialThickness2->setAlignment(Qt::AlignLeft);
    m_pctrlMaterialThickness2->SetMin(0);
    m_pctrlMaterialThickness2->SetPrecision(3);
    m_pctrlMaterialThickness2->SetValue(0.001);


    m_pctrlStructureOption1 = new QRadioButton(tr("Full"));
    m_StructureOption1 = new QLabel;
    m_StructureOption1->setObjectName("StructureOption1");
    m_StructureOption1->setGeometry(QRect(20, 0, 61, 71));
    m_StructureOption1->setPixmap(QPixmap(QString::fromUtf8(":/images/Airfoil_full.png")));

    m_pctrlLabelEmpty = new QLabel(tr("   "));
    m_pctrlLabelEmpty2 = new QLabel(tr("                                                     "));
    m_pctrlLabelEmpty3 = new QLabel(tr("[kg/m^3]                                             "));


    m_pctrlMaterialSelection = new QComboBox;
    m_pctrlMaterialSelectionLabel = new QLabel(tr("                 Material    "));


    m_pctrlStructureOption2 = new QRadioButton(tr("Skin Thickness"));
    m_StructureOption2 = new QLabel;
    m_StructureOption2->setObjectName("StructureOption2");
    m_StructureOption2->setGeometry(QRect(20, 0, 61, 71));
    m_StructureOption2->setPixmap(QPixmap(QString::fromUtf8(":/images/airfoil_thickness.png")));

    m_pctrlStructureOption3 = new QRadioButton(tr("Skin+Interior"));
    m_StructureOption3 = new QLabel;
    m_StructureOption3->setObjectName("StructureOption3");
    m_StructureOption3->setGeometry(QRect(20, 0, 61, 71));
    m_StructureOption3->setPixmap(QPixmap(QString::fromUtf8(":/images/airfoil_thickness_int.png")));



    MatNameLabel1 = new QLabel(tr(" Material "));
    MatName1 = new QLabel;
    MatDensityLabel1 = new QLabel(tr(" Density "));
    MatDensity1 = new QLabel;
    MatNameLabel2 = new QLabel(tr(" Skin Material "));
    MatName2 = new QLabel;
    MatDensityLabel2 = new QLabel(tr(" Skin Density "));
    MatDensity2 = new QLabel;
    MatNameLabel3 = new QLabel(tr(" Skin Material "));
    MatName3 = new QLabel;
    MatDensityLabel3 = new QLabel(tr(" Skin Density "));
    MatDensity3 = new QLabel;
    MatNameLabel4 = new QLabel(tr(" Core Material "));
    MatName4 = new QLabel;
    MatDensityLabel4 = new QLabel(tr(" Core Density "));
    MatDensity4 = new QLabel;

    Group2->addButton(m_pctrlStructureOption1);
    Group2->addButton(m_pctrlStructureOption2);
    Group2->addButton(m_pctrlStructureOption3);



    MaterialPropertiesLayout->addWidget(m_pctrlNewMaterialButton,1,1);
    MaterialPropertiesLayout->addWidget(m_pctrlSelectMaterialButton,1,2);
    MaterialPropertiesLayout->addWidget(m_pctrlSelect2ndMaterialButton,1,3);

    MaterialPropertiesLayout->addWidget(m_pctrlNewMaterialNameLabel,1,1);
    MaterialPropertiesLayout->addWidget(m_pctrlNewMaterialName,1,2);
    MaterialPropertiesLayout->addWidget(m_pctrlLabelEmpty2,1,3);
    MaterialPropertiesLayout->addWidget(m_pctrlNewMaterialDensityLabel,2,1);
    MaterialPropertiesLayout->addWidget(m_pctrlNewMaterialDensity,2,2);
    MaterialPropertiesLayout->addWidget(m_pctrlLabelEmpty3,2,3);
    MaterialPropertiesLayout->addWidget(m_pctrlMaterialCancelButton,3,1);
    MaterialPropertiesLayout->addWidget(m_pctrlNewMaterialSaveButton,3,2);
    MaterialPropertiesLayout->addWidget(m_pctrlLabelEmpty2,3,3);

    MaterialPropertiesLayout->addWidget(m_pctrlMaterialSelectionLabel,1,1);
    MaterialPropertiesLayout->addWidget(m_pctrlMaterialSelection,1,2);
    MaterialPropertiesLayout->addWidget(m_pctrlLabelEmpty2,1,3);

   // MaterialPropertiesLayout->addWidget(MatNameLabel,1,3);
   // MaterialPropertiesLayout->addWidget(MatName,1,4);
   // MaterialPropertiesLayout->addWidget(MatDensityLabel,2,3);
   // MaterialPropertiesLayout->addWidget(MatDensity,2,4);

    MaterialPropertiesLayout->addWidget(m_pctrlSelectMaterialApplyButton,3,2);
    MaterialPropertiesLayout->addWidget(m_pctrlSelectMaterialApplyButton2,3,3);
    MaterialPropertiesLayout->addWidget(m_pctrlSelectMaterialOKButton,3,4);

    StructureOption1Layout->addWidget(m_pctrlStructureOption1,1,1);
    StructureOption1Layout->addWidget(m_StructureOption1,1,2);
    StructureOption1Layout->addWidget(MatNameLabel1,1,3);
    StructureOption1Layout->addWidget(MatName1,1,4);
    StructureOption1Layout->addWidget(MatDensityLabel1,2,3);
    StructureOption1Layout->addWidget(MatDensity1,2,4);

    StructureOption2Layout->addWidget(m_pctrlStructureOption2,3,1);
    StructureOption2Layout->addWidget(m_StructureOption2,3,2);
    StructureOption2Layout->addWidget(MatNameLabel2,3,3);
    StructureOption2Layout->addWidget(MatName2,3,4);
    StructureOption2Layout->addWidget(m_pctrlMaterialThicknessLabel,4,1);
    StructureOption2Layout->addWidget(m_pctrlMaterialThickness,4,2);
    StructureOption2Layout->addWidget(MatDensityLabel2,4,3);
    StructureOption2Layout->addWidget(MatDensity2,4,4);

    StructureOption3Layout->addWidget(m_pctrlStructureOption3,7,1);
    StructureOption3Layout->addWidget(m_StructureOption3,7,2);
    StructureOption3Layout->addWidget(MatNameLabel3,7,3);
    StructureOption3Layout->addWidget(MatName3,7,4);
    StructureOption3Layout->addWidget(m_pctrlMaterialThicknessLabel2,8,1);
    StructureOption3Layout->addWidget(m_pctrlMaterialThickness2,8,2);
    StructureOption3Layout->addWidget(MatDensityLabel3,8,3);
    StructureOption3Layout->addWidget(MatDensity3,8,4);
    StructureOption3Layout->addWidget(m_pctrlLabelEmpty,9,1);
    StructureOption3Layout->addWidget(m_pctrlLabelEmpty,9,2);
    StructureOption3Layout->addWidget(MatNameLabel4,9,3);
    StructureOption3Layout->addWidget(MatName4,9,4);
    StructureOption3Layout->addWidget(m_pctrlLabelEmpty,10,1);
    StructureOption3Layout->addWidget(m_pctrlLabelEmpty,10,2);
    StructureOption3Layout->addWidget(MatDensityLabel4,10,3);
    StructureOption3Layout->addWidget(MatDensity4,10,4);



    QGroupBox *MaterialPropertiesGroup = new QGroupBox(tr("Material Properties"));
    MaterialPropertiesGroup->setLayout(MaterialPropertiesLayout);

    QGroupBox *StructureOption1Group = new QGroupBox(tr("Full Concept"));
    StructureOption1Group->setLayout(StructureOption1Layout);

    QGroupBox *StructureOption2Group = new QGroupBox(tr("Constant Skin Thickness Concept"));
    StructureOption2Group->setLayout(StructureOption2Layout);

    QGroupBox *StructureOption3Group = new QGroupBox(tr("Skin and Interior Concept"));
    StructureOption3Group->setLayout(StructureOption3Layout);


    OKButton = new QPushButton(tr("OK"));
    CancelButton = new QPushButton(tr("Cancel"));


    CommandButtons->addWidget(OKButton);
    CommandButtons->addWidget(CancelButton);


    MainLayout->addWidget(MaterialPropertiesGroup,1,1);
    MainLayout->addWidget(StructureOption1Group,2,1);
    MainLayout->addWidget(StructureOption2Group,3,1);
    MainLayout->addWidget(StructureOption3Group,4,1);
    MainLayout->addLayout(CommandButtons,5,1);

    setLayout(MainLayout);



}


void BladeStructureDlg::InitDialog()
{

/////////////////GRAPHICAL STUFF /////////////////////
    m_pctrlNewMaterialName->hide();
    m_pctrlNewMaterialDensity->hide();
    m_pctrlNewMaterialNameLabel->hide();
    m_pctrlNewMaterialDensityLabel->hide();
    m_pctrlNewMaterialSaveButton->hide();
    m_pctrlMaterialCancelButton->hide();
    m_pctrlSelectMaterialApplyButton->hide();
    m_pctrlSelectMaterialApplyButton2->hide();
    m_pctrlSelectMaterialOKButton->hide();
    m_pctrlLabelEmpty2->show();
    m_pctrlLabelEmpty3->hide();
    m_pctrlNewMaterialButton->show();
    m_pctrlSelectMaterialButton->show();
    m_pctrlSelect2ndMaterialButton->hide();
    m_pctrlMaterialSelectionLabel->hide();
    m_pctrlMaterialSelection->hide();
    m_pctrlMaterialThickness->setEnabled(false);
    m_pctrlMaterialThickness2->setEnabled(false);

////////////////////////END OF GRAPHICAL STUFF/////////////////

    if(m_pctrlMatName.size()==0)
    {
        m_pctrlSelectMaterialButton->setDisabled(true);
       // m_pctrlSelectSkinMaterialButton->setDisabled(true);
       //m_pctrlSelect2ndMaterialButton->setDisabled(true);

    }
    else if (m_pctrlMatName.size()>0)
    {
        m_pctrlSelectMaterialButton->setDisabled(false);
        //m_pctrlSelectSkinMaterialButton->setDisabled(false);
        //m_pctrlSelect2ndMaterialButton->setDisabled(false);
    }
        m_pctrlSelect2ndMaterialButton->setDisabled(true);


}

void BladeStructureDlg::OnCheckButtons()
{
    if(m_pctrlStructureOption1->isChecked())
    {
        m_pctrlMaterialThickness->setEnabled(false);
        m_pctrlMaterialThickness2->setEnabled(false);
        m_pctrlSelectMaterialApplyButton2->setEnabled(false);
       // m_pctrlSelect2ndMaterialButton->setEnabled(false);
    }

    if(m_pctrlStructureOption2->isChecked())
    {
        m_pctrlMaterialThickness->setEnabled(true);
        m_pctrlMaterialThickness2->setEnabled(false);
        m_pctrlSelectMaterialApplyButton2->setEnabled(false);
        //m_pctrlSelect2ndMaterialButton->setEnabled(false);
    }

    if(m_pctrlStructureOption3->isChecked())
    {
        m_pctrlMaterialThickness->setEnabled(false);
        m_pctrlMaterialThickness2->setEnabled(true);
        m_pctrlSelectMaterialApplyButton2->setEnabled(true);
        //m_pctrlSelect2ndMaterialButton->setEnabled(true);
    }

}


void BladeStructureDlg::Connect()
{
    connect(m_pctrlNewMaterialButton, SIGNAL(clicked()), SLOT(OnNewMaterial()));
    connect(m_pctrlSelectMaterialButton, SIGNAL(clicked()), SLOT(OnMaterialDatabase()));
    connect(m_pctrlMaterialCancelButton, SIGNAL(clicked()), SLOT (OnCancelButton()));
    connect(m_pctrlNewMaterialSaveButton, SIGNAL(clicked()), SLOT(OnSaveNewMaterial()));
    connect(m_pctrlSelectMaterialApplyButton, SIGNAL(clicked()), SLOT(OnApplyMaterial()));
    connect(m_pctrlSelectMaterialApplyButton2, SIGNAL(clicked()), SLOT(OnApply2ndMaterial()));

    connect(m_pctrlSelectMaterialOKButton, SIGNAL(clicked()), SLOT(OnSelectMaterialOK()));

    connect(m_pctrlStructureOption1, SIGNAL(clicked()), SLOT (OnCheckButtons()));
    connect(m_pctrlStructureOption2, SIGNAL(clicked()), SLOT(OnCheckButtons()));
    connect(m_pctrlStructureOption3, SIGNAL(clicked()), SLOT(OnCheckButtons()));

    connect(OKButton, SIGNAL(clicked()), SLOT(OnOK()));
    connect(CancelButton, SIGNAL(clicked()), SLOT(reject()));


}


void BladeStructureDlg::OnComputeVolume()
{

    QList <double> FoilArea;
    QList <double> FoilPos;

    QString strong;

    QBEM* pBEM = (QBEM *) m_pParent;
    MainFrame *pMainFrame = (MainFrame *) pBEM->s_pMainFrame;
    CFoil *pFoilA, *pFoilB;

    //double blades = double(pBEM->m_pctrlBlades->value());

    BladeVolume =0.0;
    double   AreaFoilAExt, AreaFoilBExt, AreaFoilAInt, AreaFoilBInt;

    int positions = pBEM->m_pWing->m_NPanel;

    if(m_pctrlStructureOption1->isChecked())
    {
       for(int i=0; i<positions; i++)
         {
          //CBlade *pWing = pBEM->m_pWing;

          pFoilA = pMainFrame->GetFoil(pBEM->m_pWing->m_RFoil[i]);
          pFoilB = pMainFrame->GetFoil(pBEM->m_pWing->m_RFoil[i+1]);

         // AreaFoilA = pFoilA->GetArea()*pBEM->m_pWing->m_TChord[i];//*pMainFrame->m_m2toUnit;
         // AreaFoilB = pFoilB->GetArea()*pBEM->m_pWing->m_TChord[i+1]*pMainFrame->m_m2toUnit;

          BladeVolume = BladeVolume + ((((pFoilA->GetArea()*pBEM->m_pWing->m_TChord[i])+(pFoilB->GetArea()*pBEM->m_pWing->m_TChord[i+1]))/2)*(pBEM->m_pWing->m_TPos[i+1]-pBEM->m_pWing->m_TPos[i]));    //m3
         }

       double Density1 = MatDensity1->text().toDouble();

       BladeMass = BladeVolume*Density1;
    }

    if(m_pctrlStructureOption2->isChecked())
    {
      for(int i=0; i<positions; i++)
       {
       // CBlade *pWing = pBEM->m_pWing;

        pFoilA = pMainFrame->GetFoil(pBEM->m_pWing->m_RFoil[i]);
        pFoilB = pMainFrame->GetFoil(pBEM->m_pWing->m_RFoil[i+1]);

//        pFoilA = pMainFrame->GetFoil(pBEM->m_pWing->m_RFoil[i]);
//        pFoilB = pMainFrame->GetFoil(pBEM->m_pWing->m_RFoil[i+1]);

        AreaFoilAExt = pFoilA->GetArea()*pBEM->m_pWing->m_TChord[i];//*pMainFrame->m_m2toUnit;
        AreaFoilAInt = pFoilA->GetArea()*(pBEM->m_pWing->m_TChord[i] - (2*m_pctrlMaterialThickness->Value()));
        AreaFoilBExt = pFoilB->GetArea()*pBEM->m_pWing->m_TChord[i+1];//*pMainFrame->m_m2toUnit;
        AreaFoilBInt = pFoilB->GetArea()*(pBEM->m_pWing->m_TChord[i+1] -(2*m_pctrlMaterialThickness->Value()));//*pMainFrame->m_m2toUnit;

        BladeVolume = BladeVolume +((((AreaFoilAExt-AreaFoilAInt)+(AreaFoilBExt-AreaFoilBInt))/2)*(pBEM->m_pWing->m_TPos[i+1]-pBEM->m_pWing->m_TPos[i]));    //m3
       }

      double Density1 = MatDensity2->text().toDouble();

      BladeMass = BladeVolume*Density1;

    }

    if(m_pctrlStructureOption3->isChecked())
    {
      double BladeVolume1=0.0, BladeVolume2=0.0;

         for(int i=0; i<positions; i++)
         {
          pFoilA = pMainFrame->GetFoil(pBEM->m_pWing->m_RFoil[i]);
          pFoilB = pMainFrame->GetFoil(pBEM->m_pWing->m_RFoil[i+1]);

    //        pFoilA = pMainFrame->GetFoil(pBEM->m_pWing->m_RFoil[i]);
    //        pFoilB = pMainFrame->GetFoil(pBEM->m_pWing->m_RFoil[i+1]);

          AreaFoilAExt = pFoilA->GetArea()*pBEM->m_pWing->m_TChord[i];//*pMainFrame->m_m2toUnit;
          AreaFoilAInt = pFoilA->GetArea()*(pBEM->m_pWing->m_TChord[i] - (2*m_pctrlMaterialThickness->Value()));
          AreaFoilBExt = pFoilB->GetArea()*pBEM->m_pWing->m_TChord[i+1];//*pMainFrame->m_m2toUnit;
          AreaFoilBInt = pFoilB->GetArea()*(pBEM->m_pWing->m_TChord[i+1] -(2*m_pctrlMaterialThickness->Value()));//*pMainFrame->m_m2toUnit;

          BladeVolume1 = BladeVolume1 +((((AreaFoilAExt-AreaFoilAInt)+(AreaFoilBExt-AreaFoilBInt))/2)*(pBEM->m_pWing->m_TPos[i+1]-pBEM->m_pWing->m_TPos[i]));    //m3
          BladeVolume2 = BladeVolume2 +(((AreaFoilAInt+AreaFoilBInt)/2)*(pBEM->m_pWing->m_TPos[i+1]-pBEM->m_pWing->m_TPos[i]));

          BladeVolume = BladeVolume1+BladeVolume2;
        }

    double Density1 = MatDensity3->text().toDouble();
    double Density2 = MatDensity4->text().toDouble();

    BladeMass = BladeVolume1*Density1+BladeVolume2*Density2;
    }

    pBEM->m_pctrlBladeMass->setNum(BladeMass); //[kg]
    pBEM->m_pctrlBladeVolume->setNum(BladeVolume*1000); //[dm^3]


}


void BladeStructureDlg::OnOK()
{
    OnComputeVolume();

    accept();
}

void BladeStructureDlg::OnCancelButton()
{
  InitDialog();
}

void BladeStructureDlg::OnNewMaterial()
{
/////////////////GRAPHICAL STUFF /////////////////////
    m_pctrlNewMaterialName->setEnabled(true);
    m_pctrlNewMaterialDensity->setEnabled(true);
    m_pctrlNewMaterialName->show();
    m_pctrlNewMaterialDensity->show();
    m_pctrlNewMaterialNameLabel->show();
    m_pctrlNewMaterialDensityLabel->show();
    m_pctrlNewMaterialSaveButton->show();
    m_pctrlMaterialCancelButton->show();
    m_pctrlNewMaterialButton->hide();
    m_pctrlSelectMaterialButton->hide();
    m_pctrlSelect2ndMaterialButton->hide();
    m_pctrlLabelEmpty2->show();
    m_pctrlLabelEmpty3->show();
    m_pctrlMaterialSelectionLabel->hide();
    m_pctrlMaterialSelection->hide();
/////////////////END OF GRAPHICAL STUFF /////////////////////

}

void BladeStructureDlg::OnMaterialDatabase()
{
///////////////// GRAPHICAL STUFF /////////////////////
     m_pctrlNewMaterialName->setEnabled(false);
     m_pctrlNewMaterialDensity->setEnabled(false);
     m_pctrlNewMaterialName->hide();
     m_pctrlNewMaterialDensity->hide();
     m_pctrlNewMaterialNameLabel->hide();
     m_pctrlNewMaterialDensityLabel->hide();
     m_pctrlNewMaterialSaveButton->hide();
     m_pctrlSelectMaterialApplyButton->show();
     m_pctrlSelectMaterialApplyButton2->show();
     m_pctrlSelectMaterialOKButton->show();
     m_pctrlMaterialCancelButton->show();
     m_pctrlNewMaterialButton->hide();
     m_pctrlSelectMaterialButton->hide();
     m_pctrlSelect2ndMaterialButton->hide();
     m_pctrlMaterialSelectionLabel->show();
     m_pctrlMaterialSelection->show();
///////////////// END OF GRAPHICAL STUFF /////////////////////


    m_pctrlMaterialSelection->clear();

   for (int i=0; i<m_pctrlMatName.size();i++)
     {
         m_pctrlMaterialSelection->addItem(m_pctrlMatName.at(i));
     }

}


void BladeStructureDlg::OnApplyMaterial()
{

    if(m_pctrlStructureOption1->isChecked())
    {
      int j= m_pctrlMaterialSelection->currentIndex();


      MatName1->setText(m_pctrlMatName.at(j));
      MatDensity1->setNum(m_pctrlMatDensity.at(j));


    }

    if(m_pctrlStructureOption2->isChecked())
    {
        int j= m_pctrlMaterialSelection->currentIndex();

        MatName2->setText(m_pctrlMatName.at(j));
        MatDensity2->setNum(m_pctrlMatDensity.at(j));


    }

    if(m_pctrlStructureOption3->isChecked())
    {
           int j= m_pctrlMaterialSelection->currentIndex();

           MatName3->setText(m_pctrlMatName.at(j));
           MatDensity3->setNum(m_pctrlMatDensity.at(j));


    }


}
void BladeStructureDlg::OnApply2ndMaterial()
{

       //m_pctrlSelectMaterialApplyButton2->setDisabled(false);

        int k= m_pctrlMaterialSelection->currentIndex();

           MatName4->setText(m_pctrlMatName.at(k));
           MatDensity4->setNum(m_pctrlMatDensity.at(k));
 }

void BladeStructureDlg::OnSaveNewMaterial()
{



    MaterialName = m_pctrlNewMaterialName->text();
    MaterialDensity = m_pctrlNewMaterialDensity->Value();

    m_pctrlMatName.append(MaterialName);
    m_pctrlMatDensity.append(MaterialDensity);


    InitDialog();


}

void BladeStructureDlg::OnSelectMaterialOK()
{
    InitDialog();
}
