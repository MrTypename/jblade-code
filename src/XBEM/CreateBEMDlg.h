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

#ifndef CREATEBEMDLG_H
#define CREATEBEMDLG_H


#include "BEM.h"
#include <QtWidgets>
#include "../Misc/FloatEdit.h"

class CreateBEMDlg : public QDialog
{

    Q_OBJECT

    friend class XBEM;

private slots:



public:

    CreateBEMDlg(void *pParent);
    void SetupLayout();
    void Connect();

    FloatEdit *IterationsEdit, *EpsilonEdit, *ElementsEdit, *RhoEdit, *RelaxEdit, *ViscEdit;
    QLabel *IterationsLabel, *ElementsLabel, *EpsilonLabel, *RhoEditLabel, *RelaxEditLabel, *ViscEditLabel;
    QCheckBox *TipLossBox, *RootLossBox, *ThreeDBox, *InterpolationBox, *NewTipLossBox, *NewRootLossBox;
    QCheckBox *ThreeDEquilibriumBox;
    QPushButton *OkButton;
    QLineEdit *SimName;



public slots:

    void CheckButtons();


private:

    double relax;
    double elements;
    double epsilon;
    double iterations;
    double rho;
    double visc;
    bool TipLoss;
    bool RootLoss;
    bool ThreeDCorrection;
    bool ThreeDEquilibrium;
    bool Interpolation;
    bool NewTipLoss;
    bool NewRootLoss;










};


#endif // CREATEBEMDLG_H
