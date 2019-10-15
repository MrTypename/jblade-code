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

#ifndef _SORTMETHOD_H
#define _SORTMETHOD_H

#include <vector>
#include "Types.h"

namespace vrender
{
	// Class which implements the sorting of the primitives. An object of
	class VRenderParams ;
	class SortMethod
	{
		public:
			SortMethod() {}
			virtual ~SortMethod() {}

			virtual void sortPrimitives(std::vector<PtrPrimitive>&,VRenderParams&) = 0 ;

			void SetZDepth(FLOAT s) { zSize = s ; }
			FLOAT ZDepth() const { return zSize ; }

		protected:
			FLOAT zSize ;
	};

	class DontSortMethod: public SortMethod
	{
		public:
			DontSortMethod() {}
			virtual ~DontSortMethod() {}

			virtual void sortPrimitives(std::vector<PtrPrimitive>&,VRenderParams&) {}
	};

	class BSPSortMethod: public SortMethod
	{
		public:
			BSPSortMethod() {} ;
			virtual ~BSPSortMethod() {}

			virtual void sortPrimitives(std::vector<PtrPrimitive>&,VRenderParams&) ;
	};

	class TopologicalSortMethod: public SortMethod
	{
		public:
			TopologicalSortMethod() ;
			virtual ~TopologicalSortMethod() {}

			virtual void sortPrimitives(std::vector<PtrPrimitive>&,VRenderParams&) ;

			void setBreakCycles(bool b) { _break_cycles = b ; }
		private:
			bool _break_cycles ;
	};
}

#endif
