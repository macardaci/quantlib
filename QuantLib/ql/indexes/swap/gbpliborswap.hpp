/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*
 Copyright (C) 2008, 2011, 2015 Ferdinando Ametrano

 This file is part of QuantLib, a free-software/open-source library
 for financial quantitative analysts and developers - http://quantlib.org/

 QuantLib is free software: you can redistribute it and/or modify it
 under the terms of the QuantLib license.  You should have received a
 copy of the license along with this program; if not, please email
 <quantlib-dev@lists.sf.net>. The license is also available online at
 <http://quantlib.org/license.shtml>.

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
*/

/*! \file gbpliborswap.hpp
    \brief %GBP %Libor %Swap indexes
*/

#ifndef quantlib_gbpliborswap_hpp
#define quantlib_gbpliborswap_hpp

#include <ql/indexes/swapindex.hpp>

namespace QuantLib {

    //! %GbpLiborSwapIsdaFix index base class
    /*! %GBP %Libor %Swap indexes fixed by ISDA in cooperation with
        Reuters and Intercapital Brokers at 11am London.
        Semiannual Actual/365F vs 6M Libor, 1Y Annual vs 3M Libor.
        Reuters page ISDAFIX4 or GBPSFIX=.

        Further info can be found at <http://www.isda.org/fix/isdafix.html> or
        Reuters page ISDAFIX.

    */
    class GbpLiborSwapIsdaFix : public SwapIndex {
      public:
        GbpLiborSwapIsdaFix(const Period& tenor,
                            const Handle<ForwardRateCurve>& h =
                                    Handle<ForwardRateCurve>());
        GbpLiborSwapIsdaFix(const Period& tenor,
                            const Handle<YieldTermStructure>& h);
        GbpLiborSwapIsdaFix(const Period& tenor,
                            const Handle<ForwardRateCurve>& forwarding,
                            const Handle<YieldTermStructure>& discounting);
    };

}

#endif
