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

#if QT_VERSION > 0x040000
# include <QDom>
# include <QString>
# include <QStringList>
# include <QColor>
#else
# include <QtXml/qdom.h>
# include <qstring.h>
# include <qstringlist.h>
# include <qcolor.h>
#endif

#include <math.h>

#ifndef DOXYGEN

// QDomElement loading with syntax checking.
class DomUtils
{
private:
  static void warning(const QString& message)
  {
#if QT_VERSION >= 0x040000
    qWarning(message.toLatin1().constData());
#else
    qWarning(message.latin1());
#endif
  }

public:
  static float floatFromDom(const QDomElement& e, const QString& attribute, float defValue)
  {
    float value = defValue;
    if (e.hasAttribute(attribute))
      {
	const QString s = e.attribute(attribute);
	bool ok;
	s.toFloat(&ok);
	if (ok)
	  value = s.toFloat();
	else
	  warning("Bad float syntax for attribute \""+attribute+"\" in initialization of \""+e.tagName()+"\". Setting value to "+QString::number(value)+".");
      }
    else
      warning("\""+attribute+"\" attribute missing in initialization of \""+e.tagName()+"\". Setting value to "+QString::number(value)+".");

#if defined(isnan)
    // The "isnan" method may not be available on all platforms.
    // Find its equivalent or simply remove these two lines
    if (isnan(value))
      warning("Warning, attribute \""+attribute+"\" initialized to Not a Number in \""+e.tagName()+"\"");
#endif

    return value;
  }

  static int intFromDom(const QDomElement& e, const QString& attribute, int defValue)
  {
    int value = defValue;
    if (e.hasAttribute(attribute))
      {
	const QString s = e.attribute(attribute);
	bool ok;
	s.toInt(&ok);
	if (ok)
	  value = s.toInt();
	else
	  warning("Bad integer syntax for attribute \""+attribute+"\" in initialization of \""+e.tagName()+"\". Setting value to "+QString::number(value)+".");
      }
    else
      warning("\""+attribute+"\" attribute missing in initialization of \""+e.tagName()+"\". Setting value to "+QString::number(value)+".");
    return value;
  }

  static bool boolFromDom(const QDomElement& e, const QString& attribute, bool defValue)
  {
    bool value = defValue;
    if (e.hasAttribute(attribute))
      {
	const QString s = e.attribute(attribute);
#if QT_VERSION >= 0x040000
	if (s.toLower() == QString("true"))
#else
	if (s.lower() == QString("true"))
#endif
	  value = true;
#if QT_VERSION >= 0x040000
	else if (s.toLower() == QString("false"))
#else
	else if (s.lower() == QString("false"))
#endif
	  value = false;
	else
	  {
	    warning("Bad boolean syntax for attribute \""+attribute+"\" in initialization of \""+e.tagName()+"\" (should be \"true\" or \"false\").");
	    warning("Setting value to "+(value?QString("true."):QString("false.")));
	  }
      }
    else
      warning("\""+attribute+"\" attribute missing in initialization of \""+e.tagName()+"\". Setting value to "+(value?QString("true."):QString("false.")));
    return value;
  }

  static QDomElement QColorDomElement(const QColor& color, const QString& name, QDomDocument& doc)
  {
    QDomElement de = doc.createElement(name);
    de.setAttribute("red", QString::number(color.red()));
    de.setAttribute("green", QString::number(color.green()));
    de.setAttribute("blue", QString::number(color.blue()));
    return de;
  }

  static QColor QColorFromDom(const QDomElement& e)
  {
    int color[3];
    QStringList attribute;
    attribute << "red" << "green" << "blue";
#if QT_VERSION >= 0x040000
    for (int i=0; i<attribute.count(); ++i)
#else
    for (unsigned int i=0; i<attribute.count(); ++i)
#endif
      color[i] = DomUtils::intFromDom(e, attribute[i], 0);
    return QColor(color[0], color[1], color[2]);
  }
};

#endif // DOXYGEN
