/*
 This file is part of the VRender library.
 Copyright (C) 2005 Cyril Soler (Cyril.Soler@imag.fr)
 Version 1.0.0, released on June 27, 2005.

 http://artis.imag.fr/Members/Cyril.Soler/VRender

 VRender is free software; you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation; either version 2 of the License, or
 (at your option) any later version.

 VRender is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with VRender; if not, write to the Free Software Foundation, Inc.,
 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
*/

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

#ifndef _VRENDER_EXPORTER_H
#define _VRENDER_EXPORTER_H

// Set of classes for exporting in various formats, like EPS, XFig3.2, SVG.

#include "Primitive.h"

#include "../config.h"
#if QT_VERSION >= 0x040000
# include <QTextStream>
#else
# include <qtextstream.h>
#endif

namespace vrender
{
	class VRenderParams ;
	class Exporter
	{
		public:
			Exporter() ;
			virtual ~Exporter() {};

			virtual void exportToFile(const char *filename,const std::vector<PtrPrimitive>&,VRenderParams&) ;

			void setBoundingBox(float xmin,float ymin,float xmax,float ymax) ;
			void setClearColor(float r,float g,float b) ;
			void setClearBackground(bool b) ;
			void setBlackAndWhite(bool b) ;

		protected:
			virtual void spewPoint(const Point *, QTextStream& out) = 0 ;
			virtual void spewSegment(const Segment *, QTextStream& out) = 0 ;
			virtual void spewPolygone(const Polygone *, QTextStream& out) = 0 ;

			virtual void writeHeader(QTextStream& out) const = 0 ;
			virtual void writeFooter(QTextStream& out) const = 0 ;

			float _clearR,_clearG,_clearB ;
			float _pointSize ;
			float _lineWidth ;

			GLfloat _xmin,_xmax,_ymin,_ymax,_zmin,_zmax ;

			bool _clearBG,_blackAndWhite ;
	};

	// Exports to encapsulated postscript.

	class EPSExporter: public Exporter
	{
		public:
			EPSExporter() ;
			virtual ~EPSExporter() {};

		protected:
			virtual void spewPoint(const Point *, QTextStream& out) ;
			virtual void spewSegment(const Segment *, QTextStream& out) ;
			virtual void spewPolygone(const Polygone *, QTextStream& out) ;

			virtual void writeHeader(QTextStream& out) const ;
			virtual void writeFooter(QTextStream& out) const ;

		private:
			void setColor(QTextStream& out,float,float,float) ;

			static const double EPS_GOURAUD_THRESHOLD ;
			static const char *GOURAUD_TRIANGLE_EPS[] ;
			static const char *CREATOR ;

			static float last_r ;
			static float last_g ;
			static float last_b ;
	};

	//  Exports to postscript. The only difference is the filename extension and
	// the showpage at the end.

	class PSExporter: public EPSExporter
	{
		public:
			virtual ~PSExporter() {};
		protected:
			virtual void writeFooter(QTextStream& out) const ;
	};

	class FIGExporter: public Exporter
	{
		public:
			FIGExporter() ;
			virtual ~FIGExporter() {};

		protected:
			virtual void spewPoint(const Point *, QTextStream& out) ;
			virtual void spewSegment(const Segment *, QTextStream& out) ;
			virtual void spewPolygone(const Polygone *, QTextStream& out) ;

			virtual void writeHeader(QTextStream& out) const ;
			virtual void writeFooter(QTextStream& out) const ;

		private:
			mutable int _sizeX ;
			mutable int _sizeY ;
			mutable int _depth ;

			int FigCoordX(double) const ;
			int FigCoordY(double) const ;
			int FigGrayScaleIndex(float red, float green, float blue) const ;
	};
#ifdef A_FAIRE
	class SVGExporter: public Exporter
	{
		protected:
			virtual void spewPoint(const Point *, QTextStream& out) ;
			virtual void spewSegment(const Segment *, QTextStream& out) ;
			virtual void spewPolygone(const Polygone *, QTextStream& out) ;

			virtual void writeHeader(QTextStream& out) const ;
			virtual void writeFooter(QTextStream& out) const ;
	};
#endif
}

#endif
