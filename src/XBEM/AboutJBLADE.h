/****************************************************************************

    AboutJBLADE Class
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

#ifndef ABOUTJBLADE_H
#define ABOUTJBLADE_H

#include <QDialog>
#include <QLabel>

class AboutJBLADE : public QDialog
{
    Q_OBJECT

public:
        explicit AboutJBLADE(void *parent = 0);
        virtual ~AboutJBLADE();


private:
        void SetupLayout();

        QPushButton *OKButton;
        QLabel * m_pUBILink, *m_pJBladeLink;
        QLabel *m_IconUBI;
        QLabel *m_IconJBLADE;
        QLabel *m_IconCAST;


        void *m_pBEM;
};

#endif // ABOUTJBLADE_H
