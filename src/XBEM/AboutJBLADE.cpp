/****************************************************************************

    AboutJBLADE Class
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

#include <QtWidgets>
#include "AboutJBLADE.h"
#include "../XBEM/BEM.h"
#include <QBitmap>

AboutJBLADE::AboutJBLADE(void *parent)
{
        setWindowTitle(tr("About JBLADE"));

        m_pBEM = parent;

        SetupLayout();
        connect(OKButton, SIGNAL(clicked()),this, SLOT(accept()));
}

AboutJBLADE::~AboutJBLADE()
{
}

void AboutJBLADE::SetupLayout()
{
        QBEM *pBEM = (QBEM*)m_pBEM;
        QHBoxLayout *LogoLayout = new QHBoxLayout;
        m_IconUBI = new QLabel;
        m_IconUBI->setObjectName("iconUBI");
        m_IconUBI->setGeometry(QRect(20, 0, 61, 71));
        m_IconUBI->setPixmap(QPixmap(QString::fromUtf8(":/images/UBI.png")));

        m_IconJBLADE = new QLabel;
        m_IconJBLADE->setObjectName("iconRotor");
        m_IconJBLADE->setGeometry(QRect(20, 0, 61, 71));
        m_IconJBLADE->setPixmap(QPixmap(QString::fromUtf8(":/images/JBLADE_160.jpg")));

        m_IconCAST= new QLabel;
        m_IconCAST->setObjectName("iconCAST");
        m_IconCAST->setGeometry(QRect(20, 0, 61, 71));
        m_IconCAST->setPixmap(QPixmap(QString::fromUtf8(":/images/CAST.png")));

        QLabel *lab1  = new QLabel(pBEM->m_VersionName);
        lab1->setAlignment(Qt::AlignLeft);
        LogoLayout->addWidget(m_IconUBI);
        LogoLayout->addStretch(1);
        LogoLayout->addWidget(m_IconJBLADE);
        LogoLayout->addStretch(1);
        LogoLayout->addWidget(m_IconCAST);



        QLabel *lab2  = new QLabel(tr("Copyright (C) João Morgado (jmorgado@ubi.pt) - Propeller Analysis and Design 2012"));
        QLabel *lab3  = new QLabel(tr("This program is distributed in the hope that it will be useful,"));
        QLabel *lab4  = new QLabel(tr("but WITHOUT ANY WARRANTY; without even the implied warranty of"));
        QLabel *lab5  = new QLabel(tr("MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE."));
        QLabel *lab6  = new QLabel(tr("This program has been developped in cooperation with "));
        QLabel *lab7  = new QLabel(tr("Professor Miguel Silvestre at the Aerospace Sciences Department"));
        QLabel *lab8  = new QLabel(tr("at the University of Beira Interior, Covilhã"));
        QLabel *lab9  = new QLabel(tr("Program distributed under the terms of the GNU General Public License"));


        m_pUBILink = new QLabel;
        m_pUBILink->setText("<a href=http://www.ubi.pt>http://www.ubi.pt/</a>");
        m_pUBILink->setOpenExternalLinks(true);
        m_pUBILink->setTextInteractionFlags(Qt::LinksAccessibleByKeyboard|Qt::LinksAccessibleByMouse);

        m_pJBladeLink = new QLabel;
        m_pJBladeLink->setText("<a href=http://sites.google.com/site/joaomorgado23/Home>http://sites.google.com/site/joaomorgado23/Home</a>");
        m_pJBladeLink->setOpenExternalLinks(true);
        m_pJBladeLink->setTextInteractionFlags(Qt::LinksAccessibleByKeyboard|Qt::LinksAccessibleByMouse);

        QHBoxLayout *LinkLayout = new QHBoxLayout;
        LinkLayout->addWidget(m_pJBladeLink);
        LinkLayout->addStretch(1);
        LinkLayout->addWidget(m_pUBILink);

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


