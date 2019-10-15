/****************************************************************************

 Copyright (C) 2002-2007 Gilles Debunne (Gilles.Debunne@imag.fr)

 This file is part of the QGLViewer library.
 Version 2.3.0, released on September 21, 2008.

 http://www.libqglviewer.com

 libQGLViewer is free software; you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation; either version 2 of the License, or
 (at your option) any later version.

 libQGLViewer is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with libQGLViewer; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

*****************************************************************************/

#ifndef QGLVIEWER_QKEYSEQUENCE_H
#define QGLVIEWER_QKEYSEQUENCE_H

#if QT_VERSION >= 0x040000
# include <QString>
#else
# include <qstring.h>
#endif

class QKeySequence
{
public:
    QKeySequence(int key);
    operator QString() const;

private:
	int key_;
};

#endif // QGLVIEWER_QKEYSEQUENCE_H
