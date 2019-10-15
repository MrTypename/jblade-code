/****************************************************************************

    Blade Structure Class
        Copyright (C) 2013 Joao Morgado jmorgado@ubi.pt

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

#ifndef BLADESTRUCTUREDLG_H
#define BLADESTRUCTUREDLG_H

#include <QList>
#include <QString>
#include <QColor>
#include <QDialog>
#include <QCheckBox>
#include <QLabel>
#include <QRadioButton>
#include <QLineEdit>
#include "BEM.h"
#include "BData.h"
#include "BladeDelegate.h"
#include "../Misc/FloatEdit.h"
#include "../Objects/Surface.h"

#include "Objects/WPolar.h"
#include "Objects/Surface.h"
#include "Objects/Panel.h"
#include <QFile>

class BladeStructureDlg : public QDialog
{
        Q_OBJECT
        friend class QMiarex;
        friend class MainFrame;
        friend class XBEM;
        friend class QBEM;
        friend class CBlade;
        friend class Foil;
        friend class CSurface;


            friend class WingDlg;
            friend class LLTAnalysisDlg;
            friend class LLTAnalysis;
            friend class PanelAnalysisDlg;
            friend class PlaneDlg;
            friend class ImportWingDlg;
            friend class WPolarDlg;
            friend class StabPolarDlg;
            friend class GL3dWingDlg;
            friend class ManageUFOsDlg;
            friend class InertiaDlg;
            friend class StabViewDlg;
                //////////////new code DM//////////////
                friend class BData;
                friend class OptimizeDlg;
                friend class GLWidget;

        //friend class QMiarex;


private slots:
        void OnOK();
        void Connect();
        void OnNewMaterial();
        void OnSaveNewMaterial();
        void OnMaterialDatabase();
        void OnCancelButton();
        void OnApplyMaterial();
        void OnSelectMaterialOK();
        void OnComputeVolume();
        void OnCheckButtons();
        void OnApply2ndMaterial();

public:
        BladeStructureDlg(void *pParent);
        void InitDialog();
        void SetupLayout();

       //CPolar* Get360Polar(QString m_FoilName, QString PolarName);

        void *m_pParent;

        QComboBox *m_pctrlMaterialSelection;
        QLabel *m_pctrlMaterialProperties, *m_pctrlMaterialSelectionLabel;
        QLabel *m_pctrlNewMaterialNameLabel, *m_pctrlNewMaterialDensityLabel;
        QLabel *m_pctrlSelectMaterialLabel;
        QLabel *m_pctrlLabelEmpty, *m_pctrlLabelEmpty2, *m_pctrlLabelEmpty3;
        QLabel *m_StructureOption1, *m_StructureOption2, *m_StructureOption3;

        QLabel *MatNameLabel1, *MatName1, *MatDensityLabel1, *MatDensity1;
        QLabel *MatNameLabel2, *MatName2, *MatDensityLabel2, *MatDensity2;
        QLabel *MatNameLabel3, *MatName3, *MatDensityLabel3, *MatDensity3;
        QLabel *MatNameLabel4, *MatName4, *MatDensityLabel4, *MatDensity4;

        QLabel *m_pctrlMaterialThicknessLabel, *m_pctrlMaterialThicknessLabel2;

        QLineEdit *m_pctrlNewMaterialName;
        FloatEdit *m_pctrlNewMaterialDensity, *m_pctrlMaterialThickness, *m_pctrlMaterialThickness2;

        QRadioButton *m_pctrlStructureOption1, *m_pctrlStructureOption2, *m_pctrlStructureOption3;
        QPushButton *m_pctrlNewMaterialButton,  *m_pctrlNewMaterialSaveButton, *m_pctrlMaterialCancelButton;
        QPushButton *m_pctrlSelectMaterialButton, *m_pctrlSelectMaterialApplyButton, *m_pctrlSelectMaterialOKButton;
        QPushButton *m_pctrlSelectMaterialApplyButton2, *m_pctrlSelect2ndMaterialButton;



        QList <QString> m_pctrlMatName;
        QList <double> m_pctrlMatDensity;
        QList <int> m_pctrlMatPosition;

        double BladeVolume, BladeMass;
        QString MaterialName;
        double MaterialDensity;

        int PositionMaterial1, PositionMaterial2;


        void *s_pMainFrame;


private:

        //CFoil* GetFoil(QString strFoilName);
        //CBlade * GetWing(QString WingName);

       // CFoil *m_pFoil;

        CSurface *m_pSurface;

        QList <double> *m_FoilArea;


        QPushButton *OKButton, *CancelButton;
        QString m_WingName;



};


#endif // BLADESTRUCTUREDLG_H
