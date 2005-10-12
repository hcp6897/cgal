// Copyright (c) 2005  Stanford University (USA).
// All rights reserved.
//
// This file is part of CGAL (www.cgal.org); you may redistribute it under
// the terms of the Q Public License version 1.0.
// See the file LICENSE.QPL distributed with CGAL.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $Source$
// $Revision$ $Date$
// $Name$
//
// Author(s)     : Daniel Russel <drussel@alumni.princeton.edu>

#ifndef CGAL_KDS_IO_COIN_POINTER_H
#define CGAL_KDS_IO_COIN_POINTER_H
#include <CGAL/basic.h>
#include <boost/intrusive_ptr.hpp>
#include <Inventor/nodes/SoNode.h>

//class SoNode;
void intrusive_ptr_add_ref(SoNode *n) {
  n->ref();
}
 
void intrusive_ptr_release(SoNode *n) {
  n->unref();
}

CGAL_BEGIN_NAMESPACE;


 
//! A reference counting pointer for storing pointers to Inventor objects.
/*!  Inventor objects already have reference counts built in, so I
  have to use the existing reference count.
*/
template <class T>
class Coin_pointer: public boost::intrusive_ptr<T> {
private:
  typedef boost::intrusive_ptr<T> P;
public:
  //! Pointer constructor
  Coin_pointer(T* t): P(t){}
  //! default constructor
  Coin_pointer(): P(){}
};

CGAL_END_NAMESPACE
#endif
