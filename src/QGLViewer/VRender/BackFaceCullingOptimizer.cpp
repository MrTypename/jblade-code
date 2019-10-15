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

#include <vector>
#include "VRender.h"
#include "Optimizer.h"
#include "Primitive.h"

using namespace std ;
using namespace vrender ;

// Over-simplified algorithm to check wether a polygon is front-facing or not.
// Only works for convex polygons.

void BackFaceCullingOptimizer::optimize(std::vector<PtrPrimitive>& primitives_tab,VRenderParams&)
{
	Polygone *P ;
	int nb_culled = 0 ;

	for(unsigned int i=0;i<primitives_tab.size();++i)
		if((P = dynamic_cast<Polygone *>(primitives_tab[i])) != NULL)
		{
			for(int j=0;j<P->nbVertices();++j)
				if(( (P->vertex(j+2) - P->vertex(j+1))^(P->vertex(j+1) - P->vertex(j))).z() > 0.0 )
				{
					delete primitives_tab[i] ;
					primitives_tab[i] = NULL ;
					++nb_culled ;
					break ;
				}
		}

	// Rule out gaps. This avoids testing for null primitives later.

	int j=0 ;
	for(unsigned int k=0;k<primitives_tab.size();++k)
		if(primitives_tab[k] != NULL)
			primitives_tab[j++] = primitives_tab[k] ;

	primitives_tab.resize(j) ;
#ifdef DEBUG_BFC
	cout << "Backface culling: " << nb_culled << " polygons culled." << endl ;
#endif
}
