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

#ifndef CGAL_POLYNOMIAL_INTERNAL_TRANSLATE_ZERO_H
#define CGAL_POLYNOMIAL_INTERNAL_TRANSLATE_ZERO_H

#include <CGAL/Polynomial/basic.h>

CGAL_POLYNOMIAL_BEGIN_INTERNAL_NAMESPACE

//! Move 0 to -sh
template <class Polynomial>
class Rational_translate_zero {
public:
  typedef typename Polynomial::NT NT;
  typedef Polynomial argument_type;
  typedef Polynomial result_type;
  Rational_translate_zero(){}
  Rational_translate_zero(const NT &tr): tr_(tr){}
  
  void write(std::ostream &out) const {
    out << "translate_zero("<<tr_<<")";
  }

  Polynomial operator()(const Polynomial &f) const {
    if (f.degree()<1) return f;
    //    Polynomial ret= f;
    unsigned int n= f.degree();

    std::vector<NT> ret_coef(n+1);

    for (unsigned int i = 0; i <= n; i++) {
      ret_coef[i] = f[i];
    }

    for (unsigned int i=1; i<=n; ++i){
      for (unsigned int k=n-i; k<=n-1; ++k){
	ret_coef[k] = ret_coef[k]+tr_*ret_coef[k+1];
      }
    }

    Polynomial ret(ret_coef.begin(), ret_coef.end());
    return ret;
  }

protected:
  NT tr_;
};


CGAL_POLYNOMIAL_END_INTERNAL_NAMESPACE
#endif
