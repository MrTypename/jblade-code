/****************************************************************************

    CreateBEMDlg Class
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

#include "CreateBEMDlg.h"
#include "BEM.h"



CreateBEMDlg::CreateBEMDlg(void *pParent)
{


setWindowTitle(tr("Define BEM Parameters"));

QBEM *pBEM = (QBEM *) pParent;

relax = pBEM->dlg_relax;
elements = pBEM->dlg_elements;
iterations = pBEM->dlg_iterations;
epsilon = pBEM->dlg_epsilon;
rho = pBEM->dlg_rho;
TipLoss = pBEM->dlg_tiploss;
RootLoss = pBEM->dlg_rootloss;
ThreeDCorrection = pBEM->dlg_3dcorrection;
ThreeDEquilibrium = pBEM->dlg_3dequilibrium;
Interpolation = pBEM->dlg_interpolation;
NewTipLoss = pBEM->dlg_newtiploss;
NewRootLoss = pBEM->dlg_newrootloss;
visc = pBEM->dlg_visc;



SetupLayout();

Connect();

}

void CreateBEMDlg::SetupLayout()


{


QGridLayout *VarLayout = new QGridLayout;

IterationsEdit = new FloatEdit;
EpsilonEdit = new FloatEdit;
ElementsEdit = new FloatEdit;
RhoEdit = new FloatEdit;
RelaxEdit = new FloatEdit;
ViscEdit = new FloatEdit;

SimName = new QLineEdit;

IterationsEdit->SetValue(iterations);
IterationsEdit->SetPrecision(0);
IterationsEdit->SetMin(1);
EpsilonEdit->SetValue(epsilon);
EpsilonEdit->SetMin(0.000000001);
ElementsEdit->SetValue(elements);
ElementsEdit->SetPrecision(0);
ElementsEdit->SetMin(5);
ElementsEdit->SetMax(100);

RelaxEdit->SetValue(relax);
RelaxEdit->SetPrecision(2);
RhoEdit->SetValue(rho);
RhoEdit->SetPrecision(4);
ViscEdit->SetValue(visc);
ViscEdit->SetPrecision(8);

IterationsLabel = new QLabel(tr("Max Number of Iterations"));
EpsilonLabel = new QLabel(tr("Max Epsilon for Convergence"));
ElementsLabel = new QLabel("Discretize Blade into N Elements");
RhoEditLabel = new QLabel(tr("Rho"));
RelaxEditLabel = new QLabel(tr("Relax. Factor"));
ViscEditLabel = new QLabel(tr("Viscosity"));

VarLayout->addWidget(ElementsEdit,1,1);
VarLayout->addWidget(ElementsLabel,1,2);
VarLayout->addWidget(EpsilonEdit,2,1);
VarLayout->addWidget(EpsilonLabel,2,2);
VarLayout->addWidget(IterationsEdit,3,1);
VarLayout->addWidget(IterationsLabel,3,2);
VarLayout->addWidget(RhoEdit,5,1);
VarLayout->addWidget(RhoEditLabel,5,2);
VarLayout->addWidget(RelaxEdit,4,1);
VarLayout->addWidget(RelaxEditLabel,4,2);
VarLayout->addWidget(ViscEditLabel,6,2);
VarLayout->addWidget(ViscEdit,6,1);


QGroupBox *NameGroup = new QGroupBox(tr("Simulation Name"));
QHBoxLayout *NameLayout = new QHBoxLayout;
NameLayout->addWidget(SimName);
NameGroup->setLayout(NameLayout);

QGroupBox *VarGroup = new QGroupBox(tr("Variables"));
VarGroup->setLayout(VarLayout);

QGridLayout *CorLayout = new QGridLayout;

TipLossBox = new QCheckBox(tr("Prandtl Tip Loss"));
TipLossBox->setChecked(TipLoss);

RootLossBox = new QCheckBox(tr("Prandtl Root Loss"));
RootLossBox->setChecked(RootLoss);

ThreeDBox = new QCheckBox(tr("3D Correction"));
ThreeDBox->setChecked(ThreeDCorrection);

ThreeDEquilibriumBox = new QCheckBox(tr("3D Equilibrium"));
ThreeDEquilibriumBox->setChecked(ThreeDEquilibrium);

InterpolationBox = new QCheckBox(tr("Foil Interpolation"));
InterpolationBox->setChecked(Interpolation);

NewTipLossBox = new QCheckBox(tr("New Tip Loss"));
NewTipLossBox->setChecked(NewTipLoss);

NewRootLossBox = new QCheckBox(tr("New Root Loss"));
NewRootLossBox->setChecked(NewRootLoss);


CorLayout->addWidget(TipLossBox,1,1);
CorLayout->addWidget(NewTipLossBox,2,1);
CorLayout->addWidget(RootLossBox,3,1);
CorLayout->addWidget(NewRootLossBox,4,1);
CorLayout->addWidget(InterpolationBox,5,1);
CorLayout->addWidget(ThreeDBox,6,1);
CorLayout->addWidget(ThreeDEquilibriumBox,7,1);

QGroupBox *CorGroup = new QGroupBox(tr("Corrections"));
CorGroup->setLayout(CorLayout);


OkButton = new QPushButton(tr("Create"));

QVBoxLayout *mainLayout = new QVBoxLayout;
QHBoxLayout *bottomLayout = new QHBoxLayout;
bottomLayout->addWidget(CorGroup);
bottomLayout->addWidget(VarGroup);
mainLayout->addWidget(NameGroup);
mainLayout->addLayout(bottomLayout);
mainLayout->addWidget(OkButton);

setLayout(mainLayout);


}

void CreateBEMDlg::Connect()
{

    connect(OkButton, SIGNAL(clicked()), SLOT(accept()));
    connect(TipLossBox, SIGNAL(clicked()), this, SLOT(CheckButtons()));
    connect(RootLossBox, SIGNAL(clicked()), this, SLOT(CheckButtons()));
    connect(NewTipLossBox, SIGNAL(clicked()), this, SLOT(CheckButtons()));
    connect(NewRootLossBox, SIGNAL(clicked()), this, SLOT(CheckButtons()));



}

void CreateBEMDlg::CheckButtons()
{
    if (NewTipLossBox->isChecked() || NewRootLossBox->isChecked())
    {
        TipLossBox->setChecked(false);
        RootLossBox->setChecked(false);
    }


}


