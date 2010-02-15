// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// BOOST
#include <boost/date_time/date_iterator.hpp>
// StdAir
#include <stdair/STDAIR_Types.hpp>
#include <stdair/basic/BasConst_BookingClass.hpp>
#include <stdair/basic/BasConst_Yield.hpp>
// #include <stdair/basic/BasConst_BOOST_DateTime.hpp>
// #include <stdair/bom/FareFamily.hpp>
// #include <stdair/bom/PolicyHolder.hpp>
// #include <stdair/bom/PolicyList.hpp>
// #include <stdair/bom/Policy.hpp>
#include <stdair/bom/BomRoot.hpp>
#include <stdair/bom/Inventory.hpp>
#include <stdair/bom/FlightDate.hpp>
#include <stdair/bom/LegDate.hpp>
#include <stdair/bom/SegmentDate.hpp>
#include <stdair/bom/LegCabin.hpp>
#include <stdair/bom/SegmentCabin.hpp>
#include <stdair/bom/BookingClass.hpp>
#include <stdair/bom/AirlineFeatureSet.hpp>
#include <stdair/bom/AirlineFeature.hpp>
#include <stdair/bom/BomList.hpp>
#include <stdair/factory/FacBomContent.hpp>
#include <stdair/command/CmdBomManager.hpp>
#include <stdair/service/Logger.hpp>
// AIRSCHED
#include <airsched/bom/FlightPeriodStruct.hpp>
#include <airsched/bom/BomRoot.hpp>
#include <airsched/command/InventoryGenerator.hpp>

namespace AIRSCHED {

  // //////////////////////////////////////////////////////////////////////
  void InventoryGenerator::
  createFlightDates (stdair::BomRoot& ioBomRoot,
                     const stdair::Date_T& iStartAnalysisDate,
                     const FlightPeriodStruct_T& iFlightPeriod) {
    const stdair::AirlineCode_T& lAirlineCode = iFlightPeriod._airlineCode;
    // STDAIR_LOG_DEBUG ("Generate flight-dates for the airline: "
    // << lAirlineCode);

    // Instantiate an Inventory object for the given key (airline code)
    stdair::Inventory& lInventory =
      stdair::CmdBomManager::getOrCreateInventory (ioBomRoot, lAirlineCode);

    // Generate all the dates corresponding to the period
    // and create the corresponding flight-dates.
    const DatePeriod_T lDateRange = iFlightPeriod._dateRange;

    for (boost::gregorian::day_iterator itDate = lDateRange.begin();
         itDate != lDateRange.end(); ++itDate) {
      const stdair::Date_T& currentDate = *itDate;

      // Retrieve, for the current day, the Day-Of-the-Week (thanks to Boost)
      const unsigned short currentDoW = currentDate.day_of_week().as_number();
        
      // The FlightPeriod structure stores which Days (-Of-the-Week) are
      // active within the week. For each day (Mon., Tue., etc.), a boolean
      // states whether the Flight is active for that day.
      const stdair::DoWStruct_T& lDoWList = iFlightPeriod._dow;
      const bool isDoWActive = lDoWList.getStandardDayOfWeek (currentDoW);

      if (isDoWActive == true) {
        stdair::FlightDate& lFlightDate = createFlightDate (lInventory,
                                                            currentDate,
                                                            iStartAnalysisDate,
                                                            iFlightPeriod);
        
        // Update the number of generated flight dates
        ioBomRoot.updateFlightDateCounter();

        // Create the list of references on previous built similar flight dates
        const stdair::Date_T& lStartDateRange = lDateRange.begin();
        createSimilarFlightDateList (lFlightDate, lInventory, currentDate,
                                     lStartDateRange);
      }
    }
  }
    
  // //////////////////////////////////////////////////////////////////////
  void InventoryGenerator::createDirectAccesses (stdair::BomRoot& ioBomRoot) {
    stdair::FacBomContent::createDirectAccesses (ioBomRoot);
    // Fill some attributes of segment-date with the routing legs.
    BomRoot::fillFromRouting (ioBomRoot);
  }

   // //////////////////////////////////////////////////////////////////////
   stdair::FlightDate& InventoryGenerator::
   createFlightDate (stdair::Inventory& ioInventory,
                     const stdair::Date_T& iFlightDate,
                     const stdair::Date_T& iStartAnalysisDate,
                     const FlightPeriodStruct_T& iFlightPeriod) {
    // Create the FlightDateKey
    const stdair::FlightNumber_T& lFlightNumber = iFlightPeriod._flightNumber;
    stdair::FlightDateKey_T lFlightDateKey (lFlightNumber, iFlightDate);
    // Check that the FlightDate object is not already existing. If a
    // FlightDate object with the same key has already been created,
    // it means that the schedule input file is invalid (two flight-periods
    // are overlapping).
    stdair::FlightDate* lFlightDate_ptr =
      ioInventory.getFlightDate (lFlightDateKey);

    if (lFlightDate_ptr != NULL) {
      // TODO: transform that error into an exception (duplicated
      // entry in schedule input file), as there should not be any
      // duplicated Flight-Date.
      STDAIR_LOG_ERROR ("The flight-date: " << lFlightDateKey
                          << " is duplicated within the schedule input file.");
      //return;
    }
    assert (lFlightDate_ptr == NULL);
      
    // Instantiate a FlightDate object for the given key (flight number and
    // flight date)
    lFlightDate_ptr = &stdair::FacBomContent::instance().
      create<stdair::FlightDate> (lFlightDateKey);
    assert (lFlightDate_ptr != NULL);

    // Link the created flight-date with its parent inventory.
    stdair::FacBomContent::linkWithParent<stdair::FlightDate> (*lFlightDate_ptr,
                                                               ioInventory);
        
    // Define the boolean stating whether the flight date is in the
    // analysis window or not
    stdair::AnalysisStatus_T lAnalysisStatus = false;
    if (iStartAnalysisDate <= iFlightDate) {
      lAnalysisStatus = true;
    }
      
    // Iterate on the Leg-Dates
    stdair::Duration_T currentOffTime (0, 0, 0);
    stdair::AirportCode_T previousOffPoint;
    const LegStructList_T& lLegList = iFlightPeriod._legList;
    for (LegStructList_T::const_iterator itLeg = lLegList.begin();
         itLeg != lLegList.end(); ++itLeg) {
      const LegStruct_T& lLeg = *itLeg;

      // Create the Leg-branch of the FlightDate BOM
      stdair::LegDate& lLegDate =
        createLegDate (*lFlightDate_ptr, iFlightDate, lLeg, lAnalysisStatus);

      
      // TODO: Check that the boarding date/time of the next leg is greated
      // than the off date/time of the current leg. Throw an exception
      // otherwise.

      // TODO: specify, in the schedule input file specifications, that the
      // legs should be given in their natural order.
      // Then, replace the assertion by a thrown exception.
      //
      // Check that the legs are given in their natural order. If the schedule
      // input does not respect that assumption, the following assertion will
      // fail.
      if (itLeg != lLegList.begin()) {
        const stdair::AirportCode_T& currentBoardingPoint =
          lLegDate.getBoardingPoint();
        assert (currentBoardingPoint == previousOffPoint);
      }
        
      // Set the local variable for the next iteration
      previousOffPoint = lLegDate.getOffPoint();
    }

    // Iterate on the Segment structures
    const SegmentStructList_T& lSegmentList = iFlightPeriod._segmentList;
    for (SegmentStructList_T::const_iterator itSegment = lSegmentList.begin();
         itSegment != lSegmentList.end(); ++itSegment) {
      const SegmentStruct_T& lSegment = *itSegment;

      createSegmentDate (*lFlightDate_ptr, lSegment);
    }

    assert (lFlightDate_ptr != NULL);

    return *lFlightDate_ptr;
   }

  // //////////////////////////////////////////////////////////////////////
  stdair::LegDate& InventoryGenerator::
  createLegDate (stdair::FlightDate& ioFlightDate,
                 const stdair::Date_T& iReferenceDate,
                 const LegStruct_T& iLeg,
                 const stdair::AnalysisStatus_T& iAnalysisStatus) {
    // Set the Leg-Date primary key
    const stdair::AirportCode_T& lBoardingPoint = iLeg._boardingPoint;
    stdair::LegDateKey_T lLegDateKey (lBoardingPoint);

    // Create the Leg-Date object
    stdair::LegDate& lLegDate =
      stdair::FacBomContent::instance().create<stdair::LegDate> (lLegDateKey);

    // Link the created leg-date with its parent flight-date.
    stdair::FacBomContent::linkWithParent<stdair::LegDate> (lLegDate,
                                                            ioFlightDate);

    // Set the Leg-Date attributes
    iLeg.fill (iReferenceDate, lLegDate);
      
    // Iterate on the Cabins
    const LegCabinStructList_T& lCabinList = iLeg._cabinList;
    for (LegCabinStructList_T::const_iterator itCabin = lCabinList.begin();
         itCabin != lCabinList.end(); ++itCabin) {
      const LegCabinStruct_T& lCabin = *itCabin;

      // Create the Leg-cabin-branch of the FlightDate BOM
      createLegCabin (lLegDate, lCabin, iAnalysisStatus);
    }

    return lLegDate;
  }

  // //////////////////////////////////////////////////////////////////////
  void InventoryGenerator::
  createLegCabin (stdair::LegDate& ioLegDate,
                  const LegCabinStruct_T& iCabin,
                  const stdair::AnalysisStatus_T& iAnalysisStatus) {
    // Set the Leg-Cabin primary key
    const stdair::CabinCode_T& lCabinCode = iCabin._cabinCode;
    stdair::LegCabinKey_T lLegCabinKey (lCabinCode);
      
    // Create the Leg-Cabin object
    stdair::LegCabin& lLegCabin = 
      stdair::FacBomContent::instance().create<stdair::LegCabin> (lLegCabinKey);

    // Link the created leg-cabin with its parent leg-date.
    stdair::FacBomContent::linkWithParent<stdair::LegCabin> (lLegCabin,
                                                            ioLegDate);

    // Set the Leg-Cabin attributes
    iCabin.fill (lLegCabin, iAnalysisStatus);
  }
    
  // //////////////////////////////////////////////////////////////////////
  void InventoryGenerator::
  createSegmentDate (stdair::FlightDate& ioFlightDate,
                     const SegmentStruct_T& iSegment) {
    // Set the Segment-Date primary key
    const stdair::AirportCode_T& lBoardingPoint = iSegment._boardingPoint;
    const stdair::AirportCode_T& lOffPoint = iSegment._offPoint;
    stdair::SegmentDateKey_T lSegmentDateKey (lBoardingPoint, lOffPoint);

    // Create the Segment-Date object
    stdair::SegmentDate& lSegmentDate = stdair::FacBomContent::
      instance().create<stdair::SegmentDate> (lSegmentDateKey);
    
    // Link the created segment-date with its parent flight-date.
    stdair::FacBomContent::linkWithParent<stdair::SegmentDate> (lSegmentDate,
                                                                ioFlightDate);

    // Set the Segment-Date attributes
    iSegment.fill (lSegmentDate);
      
    // Iterate on the Cabins
    const SegmentCabinStructList_T& lCabinList = iSegment._cabinList;
    for (SegmentCabinStructList_T::const_iterator itCabin =
           lCabinList.begin(); itCabin != lCabinList.end(); ++itCabin) {
      const SegmentCabinStruct_T& lCabin = *itCabin;

      // Create the Segment-cabin-branch of the FlightDate BOM
      createSegmentCabin (ioFlightDate, lSegmentDate, lCabin);
    }
  }
    
  // //////////////////////////////////////////////////////////////////////
  void InventoryGenerator::
  createSegmentCabin (stdair::FlightDate& ioFlightDate,
                      stdair::SegmentDate& ioSegmentDate,
                      const SegmentCabinStruct_T& iCabin) {
    // Set the Segment-Cabin primary key
    const stdair::CabinCode_T& lCabinCode = iCabin._cabinCode;
    stdair::SegmentCabinKey_T lSegmentCabinKey (lCabinCode);
      
    // Create the Segment-Cabin object
    stdair::SegmentCabin& lSegmentCabin = stdair::FacBomContent::
      instance().create<stdair::SegmentCabin> (lSegmentCabinKey);

    // Link the created segment-cabin with its parent segment-date.
    stdair::FacBomContent::linkWithParent<stdair::SegmentCabin> (lSegmentCabin,
                                                                 ioSegmentDate);

    // Set the Segment-Cabin attributes
    iCabin.fill (lSegmentCabin);

    // Iterate on the Classes
    const stdair::ClassList_String_T& lClassList = iCabin._classes;
    for (stdair::ClassList_String_T::const_iterator itClass =
           lClassList.begin(); itClass != lClassList.end(); ++itClass) {
      // Transform the single-character class code into a STL string
      std::ostringstream ostr;
      ostr << *itClass;
      const stdair::ClassCode_T lClassCode (ostr.str());

      // Create the Segment-class-branch of the FlightDate BOM
      createClass (lSegmentCabin, lClassCode);
    }
  }
    
  // //////////////////////////////////////////////////////////////////////
  void InventoryGenerator::createClass (stdair::SegmentCabin& ioSegmentCabin,
                                        const stdair::ClassCode_T& iClassCode) {
    // Set the Class primary key
    stdair::BookingClassKey_T lClassKey (iClassCode);
      
    // Create the booking-class 
    stdair::BookingClass& lClass = 
      stdair::FacBomContent::instance().create<stdair::BookingClass> (lClassKey);

    // Link the created booking-class with its parent segment-cabin.
    stdair::FacBomContent::linkWithParent<stdair::BookingClass> (lClass, ioSegmentCabin);

  }

  // //////////////////////////////////////////////////////////////////////
  void InventoryGenerator::
  createSimilarFlightDateList (stdair::FlightDate& ioFlightDate,
                               stdair::Inventory& iInventory,
                               const stdair::Date_T& iCurrentDate,
                               const stdair::Date_T& iStartDateRange) {

    const stdair::FlightNumber_T& lFlightNumber = ioFlightDate.getFlightNumber();
    const stdair::DateOffSet_T lSemaine(7);
    stdair::Date_T lSimilarDate = iCurrentDate - lSemaine;
    
    while (!(iStartDateRange > lSimilarDate)) {

      const stdair::FlightDateKey_T lFlightDateKey (lFlightNumber, lSimilarDate);
      stdair::FlightDate* lFlightDate_ptr = iInventory.getFlightDate (lFlightDateKey);
      
      if (lFlightDate_ptr != NULL) {
        // Link the Flight-Date and the similar flight date
        // stdair::FacBomContent::linkSimilarFlightDates (ioFlightDate, *lFlightDate_ptr);
      }
      lSimilarDate = lSimilarDate - lSemaine;
    }

    // DEBUG
    /*STDAIR_LOG_DEBUG("FlightDate" << ioFlightDate.describeKey()
      << ", Similar flight date list size: "
      << ioFlightDate.getSimilarFlightDateListSize ());*/
  }

}
