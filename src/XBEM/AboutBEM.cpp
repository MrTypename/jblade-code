/****************************************************************************

    AboutBEM Class
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

#include <QtGui>
#include "AboutBEM.h"
#include "../XBEM/BEM.h"
#include <QBitmap>

AboutBEM::AboutBEM(void *parent)
{
        setWindowTitle(tr("About QBlade"));

        m_pBEM = parent;

        SetupLayout();
        connect(OKButton, SIGNAL(clicked()),this, SLOT(accept()));
}

AboutBEM::~AboutBEM()
{
}

void AboutBEM::SetupLayout()
{
        QBEM *pBEM = (QBEM*)m_pBEM;
        QHBoxLayout *LogoLayout = new QHBoxLayout;
        m_IconQ5 = new QLabel;
        m_IconQ5->setObjectName("iconQBLADE");
        m_IconQ5->setGeometry(QRect(20, 0, 61, 71));
        m_IconQ5->setPixmap(QPixmap(QString::fromUtf8(":/images/TUBerlin.png")));

        m_Rotor = new QLabel;
        m_Rotor->setObjectName("iconRotor");
        m_Rotor->setGeometry(QRect(20, 0, 61, 71));
        m_Rotor->setPixmap(QPixmap(QString::fromUtf8(":/images/qblade100.png")));

        m_HFI = new QLabel;
        m_HFI->setObjectName("iconHFI");
        m_HFI->setGeometry(QRect(20, 0, 61, 71));
        m_HFI->setPixmap(QPixmap(QString::fromUtf8(":/images/hfi.png")));

        QLabel *lab1  = new QLabel(tr("QBlade v0.51"));
        lab1->setAlignment(Qt::AlignLeft);
        LogoLayout->addWidget(m_HFI);
        LogoLayout->addStretch(1);
        LogoLayout->addWidget(m_Rotor);
        LogoLayout->addStretch(1);
        LogoLayout->addWidget(m_IconQ5);



        QLabel *lab2  = new QLabel(tr("Copyright (C) David Marten (qblade@web.de) - Rotor and Turbine Design 2010-2012"));
        QLabel *lab3  = new QLabel(tr("This program is distributed in the hope that it will be useful,"));
        QLabel *lab4  = new QLabel(tr("but WITHOUT ANY WARRANTY; without even the implied warranty of"));
        QLabel *lab5  = new QLabel(tr("MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE."));
        QLabel *lab6  = new QLabel(tr("This program has been developped in cooperation with "));
        QLabel *lab7  = new QLabel(tr("Dr. Ing. Georgios Pehlivanoglou at the Wind Energy Group of the Institute"));
        QLabel *lab8  = new QLabel(tr("of Fluid Dynamics and Acoustics at the Berlin University of Technology"));
        QLabel *lab9  = new QLabel(tr("Program distributed under the terms of the GNU General Public License"));


        m_pXFLR5Link = new QLabel;
        m_pXFLR5Link->setText("<a href=http://www-hfi.pi.tu-berlin.de>http://www-hfi.pi.tu-berlin.de</a>");
        m_pXFLR5Link->setOpenExternalLinks(true);
        m_pXFLR5Link->setTextInteractionFlags(Qt::LinksAccessibleByKeyboard|Qt::LinksAccessibleByMouse);

        m_pQBladeLink = new QLabel;
        m_pQBladeLink->setText("<a href=http://qblade.de.to>http://qblade.de.to/</a>");
        m_pQBladeLink->setOpenExternalLinks(true);
        m_pQBladeLink->setTextInteractionFlags(Qt::LinksAccessibleByKeyboard|Qt::LinksAccessibleByMouse);

        QHBoxLayout *LinkLayout = new QHBoxLayout;
        LinkLayout->addWidget(m_pQBladeLink);
        LinkLayout->addStretch(1);
        LinkLayout->addWidget(m_pXFLR5Link);

        OKButton = new QPushButton(tr("OK"));
        QHBoxLayout *OKLayout = new QHBoxLayout;
        OKLayout->addStretch(1);
        OKLayout->addWidget(OKButton);
        OKLayout->addStretch(1);

        QVBoxLayout *MainLayout = new QVBoxLayout;
        MainLayout->addLayout(LogoLayout);
        MainLayout->addStretch(1);
        MainLayout->addWidget(lab1);
        MainLayout->addWidget(lab2);
        MainLayout->addStretch(1);
        MainLayout->addWidget(lab3);
        MainLayout->addWidget(lab4);
        MainLayout->addWidget(lab5);
        MainLayout->addStretch(1);
        MainLayout->addWidget(lab6);
        MainLayout->addWidget(lab7);
        MainLayout->addWidget(lab8);
        MainLayout->addStretch(1);
        MainLayout->addWidget(lab9);
        MainLayout->addStretch(1);
        MainLayout->addLayout(LinkLayout);
        MainLayout->addStretch(1);
        MainLayout->addLayout(OKLayout);
        setLayout(MainLayout);
        setMinimumHeight(400);
}
