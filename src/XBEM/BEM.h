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

#ifndef BEM_H
#define BEM_H

#include <QtGui>
#include "../GLWidget.h"
#include "../MainFrame.h"
#include "../Misc/ColorButton.h"
#include "../Objects/Wing.h"
#include "../Miarex/GLLightDlg.h"
#include "BladeDelegate.h"
#include "BladeAxisDelegate.h"
#include "../Graph/QGraph.h"
#include "BData.h"
#include "BEMData.h"
#include "../Misc/FloatEdit.h"
#include "TData.h"
#include "TBEMData.h"
#include "SimuWidget.h"
#include "../Misc/ColorButton.h"
#include "../Misc/LineCbBox.h"
#include "../Misc/LineButton.h"
#include "../Misc/LineDelegate.h"
#include "BladeStructureDlg.h"







class QBEM : public QWidget
{

    friend class MainFrame;
    friend class BData;
    friend class TBEMData;
    friend class BEMData;
    friend class GLWidget;
    friend class TwoDWidget;
    friend class OptimizeDlg;
    friend class CreateBEMDlg;
    friend class SimuWidget;
    friend class Edit360PolarDlg;
    friend class DisplaySettingsDlg;
    friend class BladeStructureDlg;

    Q_OBJECT

public:
        QBEM(QWidget *parent = NULL);
        QString m_VersionName;
private slots:

        //methods

        void OnEditCur360Polar();
        void OnItemClicked(const QModelIndex &index);
        void OnCellChanged();
        void OnInsertBefore();
        void OnInsertAfter();
        void OnDeleteSection();
        void OnDelete360Polar();
        void Delete360Polar(CPolar *pPolar);
        void OnSaveWing();
        void OnNewWing();
        void OnEditWing();
        void OnDeleteWing();
        void OnDiscardWing();
        void OnDiscardTurbine();
        void OnExportGeometry();
        void UpdateUnits();
        void OnHideWidgets();
        void AboutTheBEM();
        void OnScaleBlade();
        void OnBladeStructure();
        void OnNew360Polar();
        void Compute360Polar();
        void OnSave360Polar();
        void CreatePolarCurve();
        void OnCreateRotorSimulation();
        void UpdateRotorSimulation();
        void OnStartRotorSimulation();
        void OnGraphSettings();
        void SetGraphTitles(Graph* pGraph);
        void SetPowerGraphTitles(Graph* pGraph);
        void SetPolarGraphTitles(Graph* pGraph);
        void mouseDoubleClickEvent ( QMouseEvent * event );
        BData* GetBladeData(QString Lambda);
        BData* GetTurbineBladeData(QString Windspeed);
        void UpdateBladeData();
        void UpdateTurbineBladeData();
        void OnSelChangeBladeData(int i);
        void OnSelChangeTurbineBladeData(int i);
        void InitWingTable();
        void CheckButtons();
        void CheckTurbineButtons();
        void OnNewTurbine();
        void OnEditTurbine();
        void OnDeleteTurbine();
        void DeleteTurbine(TData *pTData);
        void OnDeleteRotorSim();
        void OnDeleteTurbineSim();
        void OnSaveTurbine();
        void OnStartTurbineSimulation();
        void OnOptimize();
        void OnOrtho();
        void OnChangeCoordinates();
        void OnCreateTurbineSimulation();
        void On3DReset();
        BEMData* GetRotorSimulation(QString WingName, QString SimName);
        TBEMData* GetTurbineSimulation(QString TurbineName, QString SimName);
        void OnSelChangeRotorSimulation(int i);
        void OnSelChangeTurbine(int i);
        void OnSelChangeTurbineSimulation(int i);
        void InitTurbineData(TData *pTData);
        void InitTurbineSimulationParams(TBEMData *bladedata);
        void InitBladeSimulationParams(BEMData *bladedata);
        void OnAdvancedDesign();
        void OnHubChanged();
        void OnSimpleDesign();
        void OnBladeColor();
        void OnSectionColor();
        void OnLightDlg();



public slots:

        void OnComparePolars();
        void DeletePolar(CPolar *pPolar);
        void UpdateWings();
        void OnSelChangeWing(int i);
        void On360View();
        void OnWingView();
        void OnCharView();
        void OnPowerView();
        void OnLoadCylindricFoil();
        void OnBladeGraph();
        void OnRotorGraph();
        void OnShowAllRotorCurves();
        void OnHideAllRotorCurves();
        void OnIsolateCurrentBladeCurve();
        void OnCompareIsolatedBladeCurves();
        void OnSetWeibullA(double A);
        void OnSetWeibullK(double K);
        void OnSetCD90(double val);
        void OnSelChangeFoil(int i);
        void OnSelChangePolar(int i);
        void OnSelChange360Polar(int i);
        void PitchBlade();
        void PaintCharLegend(QPoint place, int bottom, QPainter &painter);
        void PaintPowerLegend(QPoint place, int bottom, QPainter &painter);
        void OnCurveColor();
        void OnCurveStyle(int index);
        void OnCurveWidth(int index);
        void FillComboBoxes(bool bEnable = true);
        void UpdateCurve();
        void OnShowPoints();
        void OnShowCurve();
        void OnShowOpPoint();
        void SetCurveParams();
        void UpdateView();
        void OnShowTurbine();
        void UpdateGeom();


signals:


protected:

        void SaveSettings(QSettings *pSettings);
        void LoadSettings(QSettings *pSettings);
private:

        void DisableAllButtons();
        void EnableAllButtons();
        void CheckWing();
        CBlade * GetWing(QString WingName);
        TData * GetTurbine(QString m_TurbineName);
        void SetupLayout();
        bool InitDialog(CBlade *pWing);
        bool InitAdvancedDialog(CBlade *pWing);
        void FillDataTable();
        void FillTableRow(int row);
        void FillAdvancedTableRow(int row);
        void SetCurrentSection(int section);
        void ReadParams();
        void ReadAdvancedSectionData(int sel);
        void ReadSectionData(int sel);
        void ComputeGeometry();
        void Connect();
        bool SetModWing(CBlade *pModWing);
        bool SetModTurbine(TData *pModTData);
        void GLCreateGeom(CBlade *pWing, int List);
        void GLCallViewLists();
        void NormalVector(GLdouble p1[3], GLdouble p2[3],  GLdouble p3[3], GLdouble n[3]);
        void GLRenderView();
        void GLDraw3D();
        void MouseReleaseEvent(QMouseEvent *event);
        void MousePressEvent(QMouseEvent *event);
        void MouseMoveEvent(QMouseEvent *event);
        void WheelEvent(QWheelEvent *event);
        void keyPressEvent(QKeyEvent *event);
        void keyReleaseEvent(QKeyEvent *event);
        void GLCreateSectionHighlight();
        void SetScale();
        void SetScale(QRect CltRect);
        void Set2DScale();
        void Set3DScale();
        void Paint360Graphs(QPainter &painter);
        void PaintView(QPainter &painter);
        QGraph* GetGraph(QPoint &pt);
        void UpdateFoils();
        void UpdateTurbines();
        void UpdateTurbineSimulation();
        CFoil* GetFoil(QString strFoilName);
        void UpdatePolars();
        CPolar* GetPolar(QString m_FoilName, QString PolarName);
        void* GetVariable(CPolar *pPolar, int iVar);
        void FillPolarCurve(CCurve *pCurve, CPolar *pPolar, int XVar, int YVar);
        double PotFlow(double CLzero, double slope, double alpha);
        double PlateFlow(double alphazero, double CLzero,  double alpha);
        double CD90(CFoil *pFoil, double alpha);
        double CDPlate(double alpha);
        void Update360Polars();
        CPolar* Get360Polar(QString m_FoilName,  QString PolarName);
        void PaintCharacteristicsGraphs(QPainter &painter);
        void PaintPowerGraphs(QPainter &painter);
        void CreateRotorCurves();
        void CreatePowerCurves();
        void FillRotorCurve(CCurve *pCurve, void *Data, int XVar, int YVar);
        void FillPowerCurve(CCurve *pCurve, void *Data, int XVar, int YVar);
        void * GetRotorVariable(void *data, int iVar);
        void * GetBladeVariable(void *data, int iVar);
        void * GetTurbineRotorVariable(void *Data, int iVar);
        void * GetTurbineBladeVariable(void *Data, int iVar);
        void DeleteWing(CBlade *pWing);
        void GLCreateTurbine(int List);
        void SnapClient(QString const &FileName);

        void OnCalculateBladeMass();



private:

        //pointers

        void *s_pAFoil;
        void *s_pXDirect;
        void *s_pMainFrame;
        QList <void*> *s_poaFoil;
        QList <void*> *s_poaPolar;
        QList <void*> *s_poa360Polar;
        QList <BEMData *> s_poaBEMData;
        QList <TData *> s_poaTData;
        QList <TBEMData *> s_poaTBEMData;

        BData *m_pBData;
        BData *m_pTurbineBData;
        BEMData *m_pBEMData;
        TData *m_pTData;
        TBEMData *m_pTBEMData;

        CBlade *m_pWing;// the  wing that is edited (a copy of the selected wing)
        QList <CBlade *> s_poaTurbineBlades; //array of the blades belonging to a turbine

        CFoil *m_pFoil;
        CPolar *m_pCurPolar;
        CPolar *m_pCur360Polar;
        QList <void *> *s_poaBEMWings;
        int m_iSection;
        GLWidget *m_pGLWidget;
        TwoDWidget *m_p2DWidget;
        void *m_pSimuWidget;

        BData *m_pBladeData;



        QPushButton *m_pctrlInsertBefore, *m_pctrlInsertAfter, *m_pctrlDeleteSection, *m_pctrlOptChord, *m_pctrlOptTwist, *m_pctrlBEM, *m_pctrlBEMSim, *m_pctrlBEMRun,*m_pctrlInsertBefore2, *m_pctrlInsertAfter2, *m_pctrlDeleteSection2 ;
        QLineEdit *m_pctrlWingName, *m_pctrlBEMLambdaStart, *m_pctrlBEMLambdaEnd, *m_pctrlBEMLambdaDelta;
        QTableView *m_pctrlBladeTable, *m_pctrlBladeAxisTable;
        QWidget *m_pctrlControlsWidget, *m_pctrl360Widget;
        QStackedWidget *m_pctrBottomControls;


        QSpinBox *m_pctrlBlades;
        FloatEdit *m_pctrlFixedPitch, *m_pctrlHubRadius;
        QLabel *m_pctrlWingNameLabel, *m_pctrlBladesLabel, *m_pctrlHubRadiusLabel, *m_pctrlSolidityLabel, *m_pctrlHubRadiusUnitLabel, *m_pctrlBladesAndHubLabel, *m_pctrlFixedPitchLabel;
        QTableView *m_pctrlBladeTableView;
        QPushButton *m_pctrlNewWing, *m_pctrlPitchBladeButton, *m_pctrlEditWing, *m_pctrlSave, *m_pctrlOptimize, *m_pctrlBack, *m_pctrlScale, *m_pctrlAdvancedDesign;
        QPushButton *m_pctrlSimpleDesign;
        QStackedWidget *mainWidget, *bladeWidget;
        QWidget *SimWidget, *EditWidget, *PolarWidget, *PowerWidget, *PowerEditWidget, *AdvancedEditWidget;

        QRadioButton *m_pctrlStall, *m_pctrlPitch, *m_pctrlFixed, *m_pctrl2Step, *m_pctrlVariable;
        QLabel *m_pctrlTypeLabel;
        QLabel *m_pctrlGeneratorTypeLabel, *m_pctrlVariableLossesLabel, *m_pctrlFixedLossesLabel;
        QLabel *m_pctrlRot1Label, *m_pctrlRot2Label, *m_pctrlGeneratorLabel, *m_pctrlCutInLabel, *m_pctrlCutOutLabel, *m_pctrlSwitchLabel, *m_pctrlLambdaLabel;
        FloatEdit  *m_pctrlRot1, *m_pctrlRot2, *m_pctrlGenerator, *m_pctrlCutIn, *m_pctrlCutOut , *m_pctrlSwitch, *m_pctrlLambda, *m_pctrlVariableLosses, *m_pctrlFixedLosses;
        QLabel *Type, *Trans, *Capacity, *Rot1, *Rot2, *Lambda0, *CutIn, *CutOut, *Switch, *Generator, *Blade, *BladeLabel;
        QLabel *TypeLabel, *GeneratorTypeLabel, *CutInLabel, *SwitchLabel, *CutOutLabel, *Rot1Label, *Rot2Label, *LambdaLabel, *GeneratorLabel;
        QLabel *FixedLosses, *VariableLosses, *FixedLossesLabel, *VariableLossesLabel, *OuterRadiusLabel, *OuterRadius, *FixedPitchLabel, *FixedPitch, *Showlabel;
        QPushButton *m_pctrlNewTurbine, *m_pctrlEditTurbine, *m_pctrlSaveTurbine, *m_pctrlDiscardTurbine;
        QComboBox *WingSelection;
        QLineEdit *m_pctrlTurbineName;
        QLabel *speed1, *speed2, *speed3, *rotspeed1, *rotspeed2, *power1, *power2, *Speed1, *Speed2, *Speed3, *Power1, *Power2, *Rotspeed1, *Rotspeed2, *Length1;
        QDoubleSpinBox *m_pctrlk, *m_pctrla, *m_pctrlPitchBlade;
        QLabel *m_pctrlKLabel, *m_pctrlALabel, *m_pctrlYield, *m_pctrlYieldLabel, *POwer;
        QPushButton *m_pctrlSave360, *m_pctrlNew360;
        QLabel *m_LabelA, *m_LabelB,*m_LabelAm, *m_LabelBm, *m_pctrlBEMLS, *m_pctrlBEMLE, *m_pctrlBEMLD, *m_pctrlCD90Label;
        QSlider *m_pctrlA, *m_pctrlB, *m_pctrlAm, *m_pctrlBm;
        QLineEdit *m_360Name;
        QDoubleSpinBox *m_pctrlCD90;
        QCheckBox *m_ComparePolars, *m_pctrlIsOrtho, *m_pctrlPerspective, *m_pctrlBladeCoordinates, *m_pctrlShowTurbine, *m_pctrlSurfaces, *m_pctrlAirfoils, *m_pctrlOutline, *m_pctrlAxes, *m_pctrlPositions, *m_pctrlFoilNames;
        QStandardItemModel *m_pWingModel, *m_pBladeAxisModel;

        BladeDelegate *m_pBladeDelegate;
        BladeAxisDelegate *m_pBladeAxisDelegate;

        ColorButton *m_pctrlWingColor, *m_pctrlSectionColor;

        QPushButton *m_pctrlBladeStructure;
        QLabel *m_pctrlBladeMass, *m_pctrlBladeMassLabel;
        QLabel *m_pctrlBladeVolume, *m_pctrlBladeVolumeLabel;


///variables///////

        bool m_bChanged;
        bool m_bRightSide;
        bool m_bResetglGeom;
        bool m_bCrossPoint;
        bool m_bShowLight;
        bool m_bOutline;
        bool m_bglLight;
        bool m_bSurfaces;
        bool m_bResetglLegend;
        bool m_bResetglSectionHighlight;
        bool m_bXPressed;
        bool m_bYPressed;
        bool m_bHideWidgets;
        bool m_b360PolarChanged;
        bool m_bNew360Polar;
        bool m_bComparePolarCurves;
        bool m_WingEdited;
        bool m_TurbineEdited;
        bool m_bIsolateBladeCurve;
        bool m_bCompareBladeCurve;
        bool m_bIs2DScaleSet;
        bool m_bAutoScales;
        bool m_bAbsoluteBlade;
        bool m_bAdvancedEdit;

        bool m_bShowOpPoint;

        int m_iView;
        int selected_windspeed, selected_lambda;

        double m_GLScale;
        double m_ClipPlanePos;
        double m_glScaled;


        int m_OutlineStyle, m_OutlineWidth;
        QColor m_OutlineColor;

        QPoint m_LastPoint, m_PointDown;

        CVector m_glViewportTrans;

        GLLightDlg   m_GLLightDlg;

        QRect m_rCltRect;
        QRect m_rSingleRect;


        ////GRAPHS///////

        QGraph m_360CLGraph, m_360CDGraph,  *m_pCurGraph;
        QGraph m_CharGraph1, m_CharGraph2, m_CharGraph3;
        QGraph m_PowerGraph1, m_PowerGraph2, m_PowerGraph3;
        QPoint m_CharLegendOffset;
        QPoint m_PowerLegendOffset;
        QColor m_CurveColor;
        QString m_cylName;
        QString m_cylPolarName;
        int m_CurveStyle, m_CurveWidth;
        double m_CD90;

        double a_radius;
        double alpha_ast, alpha_xfoil, pos_alpha_ast, pos_alpha_xfoil;

        QList <double> m_cd_360, m_cd_360_1;
        QList <double> cd_360;
        QList <double> Cd_xfoil;
        QList <double> Cd_tot;
        QDoubleSpinBox *m_pctrl_d_cl;
        double d_cl, m_d_cl;
        QList <double> radius;
        double airfoil_radius;

        QList <double> y_airfoil;
        QList <double> x_airfoil;
        QList <double> y_circle;
        QList <double> min_q;
        QList <double> sum_min_q_1;
        QRadioButton *m_CD90YCoordinate, *m_CD90LERadius;
        QLabel *m_CD90YCoordinateLabel, *m_CD90LERadiusLabel;



        ///////////////variables for the dialog default values//////////

        double dlg_lambda;
        double dlg_blades;
        double dlg_epsilon;
        int dlg_iterations;
        int dlg_elements;
        double dlg_rho;
        bool dlg_tiploss;
        bool dlg_rootloss;
        bool dlg_3dcorrection;
        bool dlg_3dequilibrium;
        bool dlg_interpolation;
        bool dlg_newtiploss;
        bool dlg_newrootloss;
        double dlg_relax;
        double dlg_lambdastart;
        double dlg_lambdaend;
        double dlg_lambdadelta;
        double dlg_windstart;
        double dlg_windend;
        double dlg_winddelta;
        double dlg_visc;

        double pitch_old;
        double pitch_new;

        LineCbBox *m_pctrlCurveStyle, *m_pctrlCurveWidth;
        LineButton *m_pctrlCurveColor;
        LineDelegate *m_pStyleDelegate, *m_pWidthDelegate;

};




#endif // BEM_H
