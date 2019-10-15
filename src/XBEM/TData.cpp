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

#include "TData.h"
#include "../Globals.h"


TData::TData()
{
    OuterRadius = 0;
    Generator = 0;
    Rot1= 0;
    Rot2 = 0;
    Lambda0 = 0;
    CutIn = 0;
    CutOut = 0;
    Switch = 0;
    VariableLosses = 0;
    FixedLosses = 0;
    FixedPitch = 0;

}

TData::~TData()
{

}

void TData::Serialize(QDataStream &ar, bool bIsStoring, int ArchiveFormat)
{
    float f;

    if (bIsStoring)
    {
        WriteCString(ar,m_TurbineName);
        WriteCString(ar,m_WingName);

        if (isStall) ar << 1; else ar << 0;
        if (isPitch) ar << 1; else ar << 0;
        if (isFixed) ar << 1; else ar << 0;
        if (is2Step) ar << 1; else ar << 0;
        if (isVariable) ar << 1; else ar << 0;

        ar << (float) OuterRadius;
        ar << (float) Generator;
        ar << (float) Rot1;
        ar << (float) Rot2;
        ar << (float) Lambda0;
        ar << (float) CutIn;
        ar << (float) CutOut;
        ar << (float) Switch;
        ar << (float) FixedLosses;
        ar << (float) VariableLosses;
        ar << (float) FixedPitch;

    }
    else
    {
        ReadCString(ar,m_TurbineName);
        ReadCString(ar,m_WingName);
        ar >> f;
        if (f) isStall = true; else isStall = false;
        ar >> f;
        if (f) isPitch = true; else isPitch = false;
        ar >> f;
        if (f) isFixed = true; else isFixed = false;
        ar >> f;
        if (f) is2Step = true; else is2Step = false;
        ar >> f;
        if (f) isVariable = true; else isVariable = false;

        ar >> f;
        OuterRadius = f;
        ar >> f;
        Generator = f;
        ar >> f;
        Rot1 = f;
        ar >> f;
        Rot2 = f;
        ar >> f;
        Lambda0 = f;
        ar >> f;
        CutIn = f;
        ar >> f;
        CutOut = f;
        ar >> f;
        Switch = f;
        ar >> f;
        FixedLosses = f;
        ar >> f;
        VariableLosses = f;
        if (ArchiveFormat >= 100015)
        {
        ar >> f;
        FixedPitch = f;
        }


    }
}


