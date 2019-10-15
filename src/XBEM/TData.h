/****************************************************************************

    TData Class
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

#ifndef TDATA_H
#define TDATA_H


#include <QList>
#include <QString>
#include <QColor>
#include "BData.h"

class TData
{

    friend class QBEM;
    friend class MainFrame;
public:

    void Serialize(QDataStream &ar, bool bIsStoring, int ArchiveFormat);



private:

    QString m_TurbineName;
    QString m_WingName;

    bool isStall;
    bool isPitch;
    bool isFixed;
    bool is2Step;
    bool isVariable;

    double VariableLosses;
    double FixedLosses;
    double OuterRadius;
    double Generator;
    double Rot1;
    double Rot2;
    double Lambda0;
    double CutIn;
    double CutOut;
    double Switch;
    double FixedPitch;






    TData();


    virtual ~TData();

protected:





public:

};

#endif // TDATA_H
