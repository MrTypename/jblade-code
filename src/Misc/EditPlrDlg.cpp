/****************************************************************************

	EditPlrDlg Class
	Copyright (C) 2009 Andre Deperrois adeperrois@xflr5.com

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

#include "EditPlrDlg.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QStringList>
#include <QHeaderView>

#include "../XDirect/XDirect.h"
#include "../Miarex/Miarex.h"
#include "../Graph/Curve.h"

EditPlrDlg::EditPlrDlg()
{
	setWindowTitle(tr("Polar Points Edition"));
	m_pMiarex     = NULL;
	m_pXDirect    = NULL;
	m_pPolar      = NULL;
	m_pWPolar     = NULL;

	SetupLayout();
}

void EditPlrDlg::InitDialog()
{
	FillTable();
}

void EditPlrDlg::FillTable()
{
	QString strong;

	m_pctrlAlphaList->clear();
	if(m_pXDirect && m_pPolar)
	{
		if(m_pPolar->m_PolarType!=FIXEDAOAPOLAR)
		{
			for (int i=0; i<m_pPolar->m_Alpha.size(); i++)
			{
				strong = QString("%1").arg(m_pPolar->m_Alpha.at(i),8,'f',3);
				m_pctrlAlphaList->addItem(strong);
			}
		}
		else
		{
			for (int i=0; i<m_pPolar->m_Alpha.size(); i++)
			{
				strong = QString("%1").arg(m_pPolar->m_Re.at(i),8,'f',0);
				m_pctrlAlphaList->addItem(strong);
			}
		}
	}

  else if(m_pMiarex && m_pWPolar)
    {
        if(m_pWPolar->m_WPolarType!=FIXEDAOAPOLAR)
        {
            for (int i=0; i<m_pWPolar->m_Alpha.size(); i++)
            {
                strong = QString("%1").arg(m_pWPolar->m_Alpha.at(i),8,'f',3);
                m_pctrlAlphaList->addItem(strong);
            }
        }
        else
        {
            for (int i=0; i<m_pWPolar->m_Alpha.size(); i++)
            {
                strong = QString("%1").arg(m_pWPolar->m_QInfinite.at(i),12,'f',3);
                m_pctrlAlphaList->addItem(strong);
            }
        }
    }
     m_pctrlAlphaList->setCurrentRow(curIndex1);
}


void EditPlrDlg::keyPressEvent(QKeyEvent *event)
{
	// Prevent Return Key from closing App
	switch (event->key())
	{
		case Qt::Key_Return:
		{
			if(!OKButton->hasFocus() && !CancelButton->hasFocus())
			{
				OKButton->setFocus();
			}
			else
			{
				QDialog::accept();
			}
			break;
		}
		case Qt::Key_Escape:
		{
			QDialog::reject();
			return;
		}
		default:
			event->ignore();
	}
}

void EditPlrDlg::OnDeletePoint()
{
	QXDirect *pXDirect = (QXDirect*)m_pXDirect;
	QMiarex *pMiarex = (QMiarex*)m_pMiarex;


    curIndex1 = m_pctrlAlphaList->currentRow();
	if(pXDirect)
	{
        m_pPolar->m_Alpha.removeAt(curIndex1);
        m_pPolar->m_Cd.removeAt(curIndex1);
        m_pPolar->m_Cl.removeAt(curIndex1);
        FillTable();
        if (curIndex1 >=0) CreateGraphs(curIndex1);
        FillTable();
        pXDirect->UpdateView();

	}
    else if(pMiarex)
    {
        m_pWPolar->Remove(curIndex1);
        FillTable();
        pMiarex->CreateWPolarCurves();
        pMiarex->UpdateView();
    }
    if(curIndex1>=m_pctrlAlphaList->count()-1)
	{
        curIndex1 = m_pctrlAlphaList->count()-1;
	}
    if (m_pctrlAlphaList->count()) m_pctrlAlphaList->setCurrentRow(curIndex1);

}

void EditPlrDlg::SetupLayout()
{
	QVBoxLayout *CommandButtons = new QVBoxLayout;
	m_pctrlDeletePoint	= new QPushButton(tr("Delete Point"));
	OKButton            = new QPushButton(tr("OK"));
	CancelButton        = new QPushButton(tr("Cancel"));

    m_pctrlCdBox = new QDoubleSpinBox;
    m_pctrlClBox = new QDoubleSpinBox;
    m_pctrlClLabel=new QLabel(tr("Cl"));
    m_pctrlCdLabel=new QLabel(tr("Cd"));

    m_pctrlCdBox->setSingleStep(0.0001);
    m_pctrlClBox->setSingleStep(0.001);
    m_pctrlCdBox->setDecimals(4);
    m_pctrlClBox->setDecimals(3);
    m_pctrlClBox->setMinimum(-300);
    m_pctrlCdBox->setMinimum(-300);
    m_pctrlClBox->setMaximum(300);
    m_pctrlCdBox->setMaximum(300);

    QGridLayout *BoxLayout = new QGridLayout;
    BoxLayout->addWidget(m_pctrlClLabel,1,1);
    BoxLayout->addWidget(m_pctrlCdLabel,1,2);
    BoxLayout->addWidget(m_pctrlClBox,2,1);
    BoxLayout->addWidget(m_pctrlCdBox,2,2);

      CommandButtons->addLayout(BoxLayout);
      CommandButtons->addStretch(1);
      CommandButtons->addWidget(m_pctrlDeletePoint);
      CommandButtons->addStretch(2);
      CommandButtons->addWidget(OKButton);
      CommandButtons->addWidget(CancelButton);
      CommandButtons->addStretch(1);

	m_pctrlAlphaList = new QListWidget;

	QHBoxLayout * MainLayout = new QHBoxLayout(this);
	MainLayout->addStretch(1);
	MainLayout->addWidget(m_pctrlAlphaList);
	MainLayout->addStretch(1);
	MainLayout->addLayout(CommandButtons);
	MainLayout->addStretch(1);

	setLayout(MainLayout);

	connect(m_pctrlDeletePoint, SIGNAL(clicked()),this, SLOT(OnDeletePoint()));

    connect(OKButton, SIGNAL(clicked()),this, SLOT(accept()));
    connect(CancelButton, SIGNAL(clicked()), this, SLOT(reject()));

    connect(m_pctrlAlphaList, SIGNAL(currentRowChanged(int)), this, SLOT(UpdateSpinBox1(int)));
    connect(m_pctrlClBox, SIGNAL(valueChanged(double)), this, SLOT(ClChanged1(double)));
    connect(m_pctrlCdBox, SIGNAL(valueChanged(double)), this, SLOT(CdChanged1(double)));

}

void EditPlrDlg::UpdateSpinBox1(int row)
{

    QXDirect *pXDirect = (QXDirect *) m_pXDirect;

    if (row >=0 && m_pctrlAlphaList->count())
    {
    m_pctrlClBox->setEnabled(true);
    m_pctrlCdBox->setEnabled(true);
    m_pctrlClBox->setValue(m_pPolar->m_Cl.at(row));
    m_pctrlCdBox->setValue(m_pPolar->m_Cd.at(row));

    CreateGraphs(row);

    }
    else
    {
    m_pctrlClBox->setEnabled(false);
    m_pctrlCdBox->setEnabled(false);
    }

}
void EditPlrDlg::ClChanged1(double val)
{
    QXDirect *pXDirect = (QXDirect *) m_pXDirect;

    if (fabs(val) < 0.000001) val = 0.0001;

    m_pPolar->m_Cl[m_pctrlAlphaList->currentRow()] = val;

    CreateGraphs(m_pctrlAlphaList->currentRow());

}

void EditPlrDlg::CdChanged1(double val)
{
    QXDirect *pXDirect = (QXDirect *) m_pXDirect;

    if (fabs(val) < 0.000001) val = 0.0001;

    m_pPolar->m_Cd[m_pctrlAlphaList->currentRow()] = val;

    CreateGraphs(m_pctrlAlphaList->currentRow());
}


void EditPlrDlg::CreateGraphs(int row)
{
    QXDirect *pXDirect = (QXDirect *) m_pXDirect;
    QList <double> ClCd;



    pXDirect->CreatePolarCurves();

    for (int i=0;i<m_pPolar->m_Cl.size();i++)
    {

        ClCd.append(m_pPolar->m_Cl.at(i)/m_pPolar->m_Cd.at(i));
    }



    CCurve* pPolarCurve = pXDirect->m_pPolarGraph->AddCurve();
    pPolarCurve->ShowPoints(true);
    pPolarCurve->SetWidth(4);
    pPolarCurve->SetColor(QColor(0,255,0));
    QList <double> *X = (QList <double> *) pXDirect->GetVariable(m_pPolar, pXDirect->m_pPolarGraph->GetXVariable());
    QList <double> *Y = (QList <double> *) pXDirect->GetVariable(m_pPolar, pXDirect->m_pPolarGraph->GetYVariable());

    if (pXDirect->m_pPolarGraph->GetXVariable() == 3 && pXDirect->m_pPolarGraph->GetYVariable() == 3) pPolarCurve->AddPoint(ClCd.at(row),ClCd.at(row));
    else if (pXDirect->m_pPolarGraph->GetXVariable() == 3) pPolarCurve->AddPoint(ClCd.at(row), Y->at(row));
    else if (pXDirect->m_pPolarGraph->GetYVariable() == 3) pPolarCurve->AddPoint(X->at(row),ClCd.at(row));
    else pPolarCurve->AddPoint(X->at(row),Y->at(row));



    pXDirect->UpdateView();
}
