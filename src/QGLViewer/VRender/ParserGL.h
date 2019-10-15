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

#ifndef _VRENDER_PARSERGL_H
#define _VRENDER_PARSERGL_H

//  This class implements the conversion from OpenGL feedback buffer into more
// usable data structures such as points, segments, and polygons (See Primitive.h)

#include <vector>
#include "Primitive.h"

namespace vrender
{
	class ParserGL
	{
		public:
			void parseFeedbackBuffer(	GLfloat *,
												int size,
												std::vector<PtrPrimitive>& primitive_tab,
												VRenderParams& vparams) ;
			void printStats() const ;

			inline GLfloat xmin() const { return _xmin ; }
			inline GLfloat ymin() const { return _ymin ; }
			inline GLfloat zmin() const { return _zmin ; }
			inline GLfloat xmax() const { return _xmax ; }
			inline GLfloat ymax() const { return _ymax ; }
			inline GLfloat zmax() const { return _zmax ; }
		private:
			int nb_lines ;
			int nb_polys ;
			int nb_points ;
			int nb_degenerated_lines ;
			int nb_degenerated_polys ;
			int nb_degenerated_points ;

			GLfloat _xmin ;
			GLfloat _ymin ;
			GLfloat _zmin ;
			GLfloat _xmax ;
			GLfloat _ymax ;
			GLfloat _zmax ;
	};
}

#endif
