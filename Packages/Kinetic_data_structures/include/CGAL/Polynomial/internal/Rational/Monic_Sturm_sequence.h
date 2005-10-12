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

#ifndef CGAL_POLYNOMIAL_INTERNAL_MONIC_STURM_SEQUENCE_H
#define CGAL_POLYNOMIAL_INTERNAL_MONIC_STURM_SEQUENCE_H

#include <CGAL/Polynomial/basic.h>
#include <CGAL/Polynomial/internal/Sign_variations_counter.h>
#include <CGAL/Polynomial/internal/Rational/Sturm_sequence_base.h>
/*!
  \file Monic_Sturm_sequence.h A non-filtered Sturm sequence class
  that consists monic polynomials.
*/

CGAL_POLYNOMIAL_BEGIN_INTERNAL_NAMESPACE
template<class Kernel_t>
class Monic_Sturm_sequence
  : public Sturm_sequence_base<Kernel_t>
{
protected:
  typedef Sturm_sequence_base<Kernel_t>    Base;

 public:
  typedef typename Base::Kernel            Kernel;

  typedef typename Base::Polynomial        Polynomial;
  typedef typename Base::NT                NT;

 protected:

  static NT abs(const NT& x) {
    return CGAL::abs(x);
  }

  void compute_sequence(const Polynomial& p, const Polynomial& q)
  {
    // I HAVE TO FIX THE BUG THAT EXISTS HERE; THE FOLLOWING CODE MAY
    // NOT WORK CORRECTLY IF p IS THE ZERO POLYNOMIAL AND q IS NOT
    // IN GENERAL I HAVE TO CONSIDER ALL THE LIMITING CASES
    if ( p.degree() >= 0 ) {
      add( p / abs(p[p.degree()]) );
      this->size_++;
    }

    if ( q.degree() == -1 ) { return; }

    this->add( q / abs(q[q.degree()]) );
    this->size_++;

    if ( p.degree() < q.degree() ) {
      Polynomial r = -this->seq_[0];
      this->add( r );
      this->size_++;
    }

    Polynomial r;

    while ( true ) {
      r = -this->k_.remainder_object()(this->seq_[this->size_ - 2],
				       this->seq_[this->size_ - 1]);
      if ( r.is_zero() ) { break; }

      // THE FOLLOWING HACK HAS BEEN DONE SO THAT MP_Float HOPEFULLY
      // DOES NOT RUN OUT OF EXPONENT BITS WHEN THE STURM SEQUENCE IS
      // COMPUTED
      this->normalize(r, NT());

      this->add( r / abs(r[r.degree()]) );
      this->size_++;
    }
  }

public:
  Monic_Sturm_sequence() : Base() {}

  Monic_Sturm_sequence(const Polynomial& p, const Polynomial& q,
		       const Kernel &k)
    : Base(p, q, k)
  {
    compute_sequence(p, q);
  }
};


CGAL_POLYNOMIAL_END_INTERNAL_NAMESPACE

#endif // CGAL_POLYNOMIAL_INTERNAL_MONIC_STURM_SEQUENCE_H
