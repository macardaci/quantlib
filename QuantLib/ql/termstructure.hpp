/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*
 Copyright (C) 2004, 2005, 2006, 2007 StatPro Italia srl

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

/*! \file termstructure.hpp
    \brief base class for term structures
*/

#ifndef quantlib_term_structure_hpp
#define quantlib_term_structure_hpp

#include <ql/time/calendar.hpp>
#include <ql/time/daycounters/actual365fixed.hpp>
#include <ql/settings.hpp>
#include <ql/handle.hpp>
#include <ql/math/interpolations/extrapolation.hpp>
#include <ql/utilities/null.hpp>

namespace QuantLib {

    //! Basic term-structure functionality
    class TermStructure : public virtual Observer,
                          public virtual Observable,
                          public Extrapolator {
      public:
        /*! \name Constructors

            There are three ways in which a term structure can keep
            track of its reference date.  The first is that such date
            is fixed; the second is that it is determined by advancing
            the current date of a given number of business days; and
            the third is that it is based on the reference date of
            some other structure.

            In the first case, the constructor taking a date is to be
            used; the default implementation of referenceDate() will
            then return such date. In the second case, the constructor
            taking a number of days and a calendar is to be used;
            referenceDate() will return a date calculated based on the
            current evaluation date, and the term structure and its
            observers will be notified when the evaluation date
            changes. In the last case, the referenceDate() method must
            be overridden in derived classes so that it fetches and
            return the appropriate date.
        */
        //@{
        //! initialize with a fixed reference date
        TermStructure(const Date& referenceDate);
        //! calculate the reference date based on the global evaluation date
        TermStructure(Natural settlementDays,
                      const Calendar&);
        //@}
        virtual ~TermStructure() {}
        //! \name Dates and Time
        //@{
        //! date/time conversion
        Time timeFromReference(const Date& date) const;
        //! time-to-date conversion
        Date dateFromTime(Time t) const;
        //! the latest date for which the curve can return values
        virtual Date maxDate() const = 0;
        //! the latest time for which the curve can return values
        virtual Time maxTime() const;
        //! the date at which discount = 1.0 and/or variance = 0.0
        virtual const Date& referenceDate() const;
        //! the calendar used for date calculation
        //virtual Calendar calendar() const { return calendar_; }
        //! the settlementDays used for reference date calculation
        virtual Natural settlementDays() const;
        //@}
        //! \name Observer interface
        //@{
        void update();
        //@}
      protected:
        //! date-range check
        void checkRange(const Date& d,
                        bool extrapolate) const;
        //! time-range check
        void checkRange(Time t,
                        bool extrapolate) const;
        bool moving_;
        mutable bool updated_;
      private:
        Natural settlementDays_;
        Calendar calendar_;
        mutable Date referenceDate_;
    };

    // inline definitions

    inline Time TermStructure::maxTime() const {
        return timeFromReference(maxDate());
    }

    inline Natural TermStructure::settlementDays() const {
        QL_REQUIRE(settlementDays_!=Null<Natural>(),
                   "settlement days not provided for this instance");
        return settlementDays_;
    }

}

#endif
