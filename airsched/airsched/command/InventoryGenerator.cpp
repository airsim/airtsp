// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// STDAIR
#include <stdair/basic/BasConst_BookingClass.hpp>
#include <stdair/basic/BasConst_Yield.hpp>
#include <stdair/bom/BomRoot.hpp>
#include <stdair/bom/Inventory.hpp>
#include <stdair/bom/FlightDate.hpp>
#include <stdair/bom/LegDate.hpp>
#include <stdair/bom/SegmentDate.hpp>
#include <stdair/bom/LegCabin.hpp>
#include <stdair/bom/SegmentCabin.hpp>
#include <stdair/bom/AirlineFeatureSet.hpp>
#include <stdair/bom/AirlineFeature.hpp>
#include <stdair/factory/FacBomContent.hpp>
// AIRSCHED
#include <boost/date_time/date_iterator.hpp>
//#include <airsched/basic/BasConst_BOOST_DateTime.hpp>
// #include <airsched/bom/FareFamily.hpp>
// #include <airsched/bom/PolicyHolder.hpp>
// #include <airsched/bom/PolicyList.hpp>
// #include <airsched/bom/Policy.hpp>
#include <airsched/bom/FlightPeriodStruct.hpp>
#include <airsched/command/InventoryGenerator.hpp>

namespace AIRSCHED {

//   // //////////////////////////////////////////////////////////////////////
//   void InventoryGenerator::
//   createFlightDates (stdair::BomRoot& ioBomRoot,
//                      const Date_T& iStartAnalysisDate,
//                      const FlightPeriodStruct_T& iFlightPeriod) {
//     const AirlineCode_T& lAirlineCode = iFlightPeriod._airlineCode;
//     //AIRSCHED_LOG_DEBUG ("Airline Code: " << lAirlineCode);
//     stdair::Inventory* lInventory_ptr =
//       ioBomRoot.getInventory (lAirlineCode);
      
//     if (lInventory_ptr == NULL) {
//       // Instantiate an Inventory object for the given key (airline code)
//       lInventory_ptr = &createInventory (ioBomRoot, lAirlineCode);
//       assert (lInventory_ptr != NULL);
//     }

//     // Generate all the dates corresponding to the period
//     // and create the corresponding flight-dates.
//     const DatePeriod_T lDateRange = iFlightPeriod._dateRange;

//     for (boost::gregorian::day_iterator itDate = lDateRange.begin();
//          itDate != lDateRange.end(); ++itDate) {
//       const Date_T currentDate = *itDate;

//       // Retrieve, for the current day, the Day-Of-the-Week (thanks to Boost)
//       const unsigned short currentDOW = currentDate.day_of_week().as_number();
        
//       // The FlightPeriod structure stores which Days (-Of-the-Week) are
//       // active within the week. For each day (Mon., Tue., etc.), a boolean
//       // states whether the Flight is active for that day.
//       const DOWStruct_T& lDOWList = iFlightPeriod._dow;
//       const bool isDOWActive = lDOWList.getStandardDayOfWeek (currentDOW);

//       if (isDOWActive == true) {
//         stdair::FlightDate& lFlightDate = createFlightDate (*lInventory_ptr,
//                                                             currentDate,
//                                                             iStartAnalysisDate,
//                                                             iFlightPeriod);

//         // Update the number of generated flight dates
//         ioBomRoot.updateFlightDateCounter();

//         // Create the list of references on previous built similar flight dates
//         const Date_T& lStartDateRange = lDateRange.begin();
//         createSimilarFlightDateList (lFlightDate, *lInventory_ptr,
//                                      currentDate, lStartDateRange);
//       }
//     }
//   }
    
//   // //////////////////////////////////////////////////////////////////////
//   void InventoryGenerator::
//   createRouting (stdair::BomRoot& ioBomRoot) {
//     FacBomRoot::createRouting (ioBomRoot);
//   }

//   // //////////////////////////////////////////////////////////////////////
//   void InventoryGenerator::
//   recalculateAvailabilities (stdair::BomRoot& ioBomRoot) {
//     ioBomRoot.recalculateAvailabilities ();      
//   }
      
//   // //////////////////////////////////////////////////////////////////////
//   Inventory& InventoryGenerator::
//   createInventory (stdair::BomRoot& ioBomRoot,
//                    const AirlineCode_T& iAirlineCode) {
//     const stdair::InventoryKey_T lInventoryKey (iAirlineCode);

//     // Instantiate an Inventory object with the given airline code
//     stdair::Inventory& lInventory =
//       FacBomContent::instance().create<stdair::Inventory> (ioBomRoot,
//                                                            lInventoryKey);
      
//     // Set the AirlineFeature for the inventory.
//     const stdair::AirlineFeatureSet& lAirlineFeatureSet =
//       ioBomRoot.getAirlineFeatureSet ();
//     const stdair::AirlineFeature* lAirlineFeature_ptr =
//       lAirlineFeatureSet.getAirlineFeatures(iAirlineCode);
//     //AIRSCHED_LOG_DEBUG (lAirlineFeatureSet.display()
//     //                 << "needed airline code: " << iAirlineCode);
//     assert (lAirlineFeature_ptr != NULL);
      
//     lInventory.setAirlineFeature (lAirlineFeature_ptr);
      
//     return lInventory;
//   }
      
//   // //////////////////////////////////////////////////////////////////////
//   stdair::FlightDate& InventoryGenerator::
//   createFlightDate (stdair::Inventory& ioInventory,
//                     const Date_T& iFlightDate,
//                     const Date_T& iStartAnalysisDate,
//                     const FlightPeriodStruct_T& iFlightPeriod) {
//     // Create the FlightDateKey
//     const stdair::InventoryKey_T& lInventoryKey = ioInventory.getPrimaryKey();
//     const FlightNumber_T& lFlightNumber = iFlightPeriod._flightNumber;
//     const FlightKey_T lFlightKey (lInventoryKey, lFlightNumber);
//     const FlightDateKey_T lFlightDateKey (lFlightKey, iFlightDate);

//     // Check that the FlightDate object is not already existing. If a
//     // FlightDate object with the same key has already been created,
//     // it means that the schedule input file is invalid (two flight-periods
//     // are overlapping).
//     stdair::FlightDate* lFlightDate_ptr =
//       ioInventory.getFlightDate (lFlightNumber, iFlightDate);

//     if (lFlightDate_ptr != NULL) {
//       // TODO: transform that error into an exception (duplicated
//       // entry in schedule input file), as there should not be any
//       // duplicated Flight-Date.
//       AIRSCHED_LOG_ERROR ("The flight-date: " << lFlightDateKey
//                           << " is duplicated within the schedule input file.");
//       //return;
//     }
//     assert (lFlightDate_ptr == NULL);
      
//     // Instantiate a FlightDate object for the given key (flight number and
//     // flight date)
//     lFlightDate_ptr = &FacFlightDate::instance().create (lFlightDateKey);
//     assert (lFlightDate_ptr != NULL);
        
//     // Link the FlightDate with the Inventory
//     FacInventory::initLinkWithFlightDate (ioInventory, *lFlightDate_ptr);

//     // Link the FlightNumber with the Inventory
//     FacInventory::initLinkWithFlightNumber (ioInventory, lFlightNumber);

//     // Define the boolean stating whether the flight date is in the
//     // analysis window or not
//     AnalysisStatus_T lAnalysisStatus = false;
//     if (iStartAnalysisDate <= iFlightDate) {
//       lAnalysisStatus = true;
//     }
      
//     // Iterate on the Leg-Dates
//     Duration_T currentOffTime (0, 0, 0);
//     AirportCode_T previousOffPoint;
//     const LegStructList_T& lLegList = iFlightPeriod._legList;
//     for (LegStructList_T::const_iterator itLeg = lLegList.begin();
//          itLeg != lLegList.end(); ++itLeg) {
//       const LegStruct_T& lLeg = *itLeg;

//       // Create the Leg-branch of the FlightDate BOM
//       LegDate& lLegDate =
//         createLegDate (*lFlightDate_ptr, iFlightDate,
//                        lLeg, lAnalysisStatus);

//       // TODO: Check that the board date/time of the next leg is greated
//       // than the off date/time of the current leg. Throw an exception
//       // otherwise.

//       // TODO: specify, in the schedule input file specifications, that the
//       // legs should be given in their natural order.
//       // Then, replace the assertion by a thrown exception.
//       //
//       // Check that the legs are given in their natural order. If the schedule
//       // input does not respect that assumption, the following assertion will
//       // fail.
//       if (itLeg != lLegList.begin()) {
//         const AirportCode_T& currentBoardPoint =
//           lLegDate.getBoardPoint();
//         assert (currentBoardPoint == previousOffPoint);
//       }
        
//       // Set the local variable for the next iteration
//       previousOffPoint = lLegDate.getOffPoint();
//     }

//     // Iterate on the Segment structures
//     const SegmentStructList_T& lSegmentList = iFlightPeriod._segmentList;
//     for (SegmentStructList_T::const_iterator itSegment = lSegmentList.begin();
//          itSegment != lSegmentList.end(); ++itSegment) {
//       const SegmentStruct_T& lSegment = *itSegment;

//       createSegmentDate (*lFlightDate_ptr, lSegment);
//     }

//     assert (lFlightDate_ptr != NULL);

//     return *lFlightDate_ptr;
//   }

//   // //////////////////////////////////////////////////////////////////////
//   LegDate& InventoryGenerator::
//   createLegDate (FlightDate& ioFlightDate,
//                  const Date_T& iReferenceDate,
//                  const LegStruct_T& iLeg,
//                  const AnalysisStatus_T& iAnalysisStatus) {
//     // Set the Leg-Date primary key
//     const FlightDateKey_T& lFlightDateKey = ioFlightDate.getPrimaryKey();
//     const AirportCode_T& lBoardPoint = iLeg._boardPoint;
//     const LegDateKey_T lLegDateKey (lFlightDateKey, lBoardPoint);

//     // Create the Leg-Date object
//     LegDate& lLegDate =
//       FacLegDate::instance().create (lLegDateKey);

//     // Link the Flight-Date and Leg-Date objects
//     FacFlightDate::initLinkWithLegDate (ioFlightDate, lLegDate);

//     // Set the Leg-Date attributes
//     iLeg.fill (iReferenceDate, lLegDate);
      
//     // Iterate on the Cabins
//     const LegCabinStructList_T& lCabinList = iLeg._cabinList;
//     for (LegCabinStructList_T::const_iterator itCabin = lCabinList.begin();
//          itCabin != lCabinList.end(); ++itCabin) {
//       const LegCabinStruct_T& lCabin = *itCabin;

//       // Create the Leg-cabin-branch of the FlightDate BOM
//       createLegCabin (lLegDate, lCabin, iAnalysisStatus);
//     }

//     return lLegDate;
//   }

//   // //////////////////////////////////////////////////////////////////////
//   void InventoryGenerator::
//   createLegCabin (LegDate& ioLegDate,
//                   const LegCabinStruct_T& iCabin,
//                   const AnalysisStatus_T& iAnalysisStatus) {
//     // Set the Leg-Cabin primary key
//     const LegDateKey_T& lLegDateKey = ioLegDate.getPrimaryKey();
//     const CabinCode_T& lCabinCode = iCabin._cabinCode;
//     const LegCabinKey_T lLegCabinKey (lLegDateKey, lCabinCode);
      
//     // Create the Leg-Cabin object
//     LegCabin& lLegCabin =
//       FacLegCabin::instance().create (lLegCabinKey);
      
//     // Link the Flight-Date and Leg-Date objects
//     FacLegDate::initLinkWithLegCabin (ioLegDate, lLegCabin);

//     // Set the Leg-Cabin attributes
//     iCabin.fill (lLegCabin, iAnalysisStatus);
//   }
    
//   // //////////////////////////////////////////////////////////////////////
//   void InventoryGenerator::
//   createSegmentDate (FlightDate& ioFlightDate,
//                      const SegmentStruct_T& iSegment) {
//     // Set the Segment-Date primary key
//     const FlightDateKey_T& lFlightDateKey = ioFlightDate.getPrimaryKey();
//     const AirportCode_T& lBoardPoint = iSegment._boardPoint;
//     const AirportCode_T& lOffPoint = iSegment._offPoint;
//     const AirportPairKey_T lAirportPAirKey (lBoardPoint, lOffPoint);
//     const SegmentDateKey_T lSegmentDateKey (lFlightDateKey,
//                                             lAirportPAirKey);

//     // Create the Segment-Date object
//     SegmentDate& lSegmentDate =
//       FacSegmentDate::instance().create (lSegmentDateKey);

//     // Link the Flight-Date and Segment-Date objects
//     FacFlightDate::initLinkWithSegmentDate (ioFlightDate, lSegmentDate);

//     // Set the Segment-Date attributes
//     iSegment.fill (lSegmentDate);
      
//     // Iterate on the Cabins
//     const SegmentCabinStructList_T& lCabinList = iSegment._cabinList;
//     for (SegmentCabinStructList_T::const_iterator itCabin =
//            lCabinList.begin(); itCabin != lCabinList.end(); ++itCabin) {
//       const SegmentCabinStruct_T& lCabin = *itCabin;

//       // Create the Segment-cabin-branch of the FlightDate BOM
//       createSegmentCabin (ioFlightDate, lSegmentDate, lCabin);
//     }
//   }
    
//   // //////////////////////////////////////////////////////////////////////
//   void InventoryGenerator::
//   createSegmentCabin (FlightDate& ioFlightDate,
//                       SegmentDate& ioSegmentDate,
//                       const SegmentCabinStruct_T& iCabin) {
//     // Set the Segment-Cabin primary key
//     const SegmentDateKey_T& lSegmentDateKey =
//       ioSegmentDate.getPrimaryKey();
//     const CabinCode_T& lCabinCode = iCabin._cabinCode;
//     const SegmentCabinKey_T lSegmentCabinKey (lSegmentDateKey,
//                                               lCabinCode);
      
//     // Create the Segment-Cabin object
//     SegmentCabin& lSegmentCabin =
//       FacSegmentCabin::instance().create (lSegmentCabinKey);
      
//     // Link the Flight-Date and Segment-Date objects
//     FacSegmentDate::initLinkWithSegmentCabin (ioSegmentDate,
//                                               lSegmentCabin);

//     // Set the Segment-Cabin attributes
//     iCabin.fill (lSegmentCabin);

//     // Iterate on the Classes
//     const ClassList_String_T& lClassList = iCabin._classes;
//     for (ClassList_String_T::const_iterator itClass =
//            lClassList.begin(); itClass != lClassList.end(); ++itClass) {
//       // Transform the single-character class code into a STL string
//       std::ostringstream ostr;
//       ostr << *itClass;
//       const ClassCode_T lClassCode (ostr.str());

//       // Create the map linking each class to each SegmentCabin
//       FacSegmentDate::initLinkClassWithSegmentCabin (ioSegmentDate,
//                                                      lSegmentCabin,
//                                                      lClassCode);

//       // Create the Segment-class-branch of the FlightDate BOM
//       createClass (lSegmentCabin, lClassCode);
//     }

//     // Create the map linking class short name and class structure
//     const bool buildCabinStatus =
//       FacSegmentCabin::buildClassMap(lSegmentCabin);
//     assert (buildCabinStatus != false);

//     // Create a map linking class name and class structure 
//     const bool buildFlightStatus =
//       FacFlightDate::buildClassMap(ioFlightDate, lSegmentCabin);
//     assert (buildFlightStatus != false);

//     // Create the list of fare families if they exist
//     if (iCabin._fareFamilies.size() > 0) {
//       for (FareFamilyStructList_T::const_iterator itFareFamily =
//              iCabin._fareFamilies.begin();
//            itFareFamily != iCabin._fareFamilies.end(); itFareFamily++) {
//         const FareFamilyStruct_T& lFareFamilyStruct = *itFareFamily;

//         const SegmentCabinKey_T& lSegmentCabinKey =
//           lSegmentCabin.getSegmentCabinKey();

//         const FareFamilyKey_T lFareFamilyKey (lSegmentCabinKey,
//                                               lFareFamilyStruct._familyCode);

//         // Create the fare-family object
//         FareFamily& lFareFamily =
//           FacFareFamily::instance().create (lFareFamilyKey);

//         // Iterate on the Classes
//         const ClassList_String_T& lClassList = lFareFamilyStruct._classes;
//         for (ClassList_String_T::const_iterator itClass =
//                lClassList.begin(); itClass != lClassList.end(); ++itClass) {
            
//           // Transform the single-character class code into a STL string
//           std::ostringstream ostr;
//           ostr << *itClass;

//           // Build the BookingClass key
//           const ClassCode_T lClassCode (ostr.str());
//           BookingClassKey_T lClassKey (lSegmentCabinKey, lClassCode);

//           // Retrieve the BookingClass object
//           BookingClass* lBookingClass_ptr =
//             lSegmentCabin.getBookingClass (lClassKey);

//           if (lBookingClass_ptr == NULL) {
//             AIRSCHED_LOG_ERROR ("The class " << lClassKey
//                                 << " can not be found in the following "
//                                 << "SegmentCabin: "
//                                 << lSegmentCabin.getPrimaryKey());
//           }
//           assert (lBookingClass_ptr != NULL);
            
//           // Create the map linking each class to each SegmentCabin
//           FacFareFamily::initLinkWithClass (lFareFamily,
//                                             *lBookingClass_ptr);
//         }

//         // Create the map linking each fare family to each SegmentCabin
//         FacSegmentCabin::initLinkWithFareFamily (lSegmentCabin,
//                                                  lFareFamily);
//       }
        
//       //Output for debug
//       /*AIRSCHED_LOG_DEBUG ("fare family description for "
//         << lSegmentCabin.describeKey());
//         for (lSegmentCabin.fareFamilyListBegin();
//         lSegmentCabin.fareFamilyListHasNotReachedEnd();
//         lSegmentCabin.fareFamilyListIterate()) {
//         const FareFamily& lFareFamily =
//         lSegmentCabin.getCurrentFareFamily();
//         AIRSCHED_LOG_DEBUG("FF display : " << lFareFamily.display());
          
//         }*/
//       // end output for debug

//       // Create the set of policies and store them in the Segment Cabin
//       createPolicies(lSegmentCabin); 
//     }
//   }
    
//   // //////////////////////////////////////////////////////////////////////
//   void InventoryGenerator::
//   createClass (SegmentCabin& ioSegmentCabin,
//                const ClassCode_T& iClassCode) {
//     // Set the Class primary key
//     const SegmentCabinKey_T& lSegmentCabinKey =
//       ioSegmentCabin.getPrimaryKey();      
//     const BookingClassKey_T lClassKey (lSegmentCabinKey, iClassCode);
      
//     // Create the Class structure
//     BookingClass& lClass =
//       FacBookingClass::instance().create (lClassKey);
      
//     // Link the Segment-Cabin and the BookingClass objects
//     FacSegmentCabin::initLinkWithClass (ioSegmentCabin, lClass);
//   }

//   // //////////////////////////////////////////////////////////////////////
//   void InventoryGenerator::createSimilarFlightDateList
//   (FlightDate& ioFlightDate,
//    Inventory& iInventory,
//    const Date_T& iCurrentDate,
//    const Date_T& iStartDateRange) {
//     const FlightNumber_T& lFlightNumber =
//       ioFlightDate.getFlightNumber();
//     const DateOffSet_T lSemaine(7);
//     Date_T lSimilarDate = iCurrentDate - lSemaine;
//     while (!(iStartDateRange > lSimilarDate)) {
//       FlightDate* lFlightDate_ptr =
//         iInventory.getFlightDate (lFlightNumber, lSimilarDate);
//       if (lFlightDate_ptr != NULL) {
//         // Link the Flight-Date and the similar flight date
//         FacFlightDate::
//           initLinkWithFlightDate (ioFlightDate, *lFlightDate_ptr);
//       }
//       lSimilarDate = lSimilarDate - lSemaine;
//     }

//     // DEBUG
//     /*AIRSCHED_LOG_DEBUG("FlightDate" << ioFlightDate.describeKey()
//       << ", Similar flight date list size: "
//       << ioFlightDate.getSimilarFlightDateListSize ());*/
//   }

//   // //////////////////////////////////////////////////////////////////////
//   void InventoryGenerator::createPolicies(SegmentCabin& ioSegmentCabin) {

//     // Create the Policy holder
//     PolicyHolder& lPolicyHolder =
//       FacPolicyHolder::instance().create ();

//     // Link the PolicyHolder and the SegmentCabin
//     ioSegmentCabin.setPolicyHolder(lPolicyHolder);

//     // Create list of policies used in the algorithm of policy generation
//     OrderedPolicyList_T lOldPolicyList;
//     OrderedPolicyList_T lPolicyList;

//     // Build an iterator on the list of FareFamily objects
//     const FareFamilyList_T& lFareFamilyList =
//       ioSegmentCabin.getFareFamilyList();

//     BomMapIterator_T<FareFamily,
//       FareFamilyList_T> lFareFamilyIterator (lFareFamilyList);

//     // Initialisation of the list of policies with the first fare family
//     lFareFamilyIterator.begin();
//     FareFamily* lFareFamily_ptr = lFareFamilyIterator.getCurrent();
//     assert (lFareFamily_ptr != NULL);

//     // TODO: remove this "get"
//     const BookingClassList_T& lBookingClassList =
//       lFareFamily_ptr->getBookingClassList();

//     /** Generation of a "closed virtual class" necessary to
//         represent policies where a family would be closed. */

//     Policy& lClosedClassPolicy =
//       FacPolicy::instance().create ();

//     /** The Key given to such a closed class is the key of a segment
//         cabin+a two characters classCode "CC" (usual classCodes are
//         only one letter long). */

//     SegmentCabinKey_T lSegmentCabinKey = ioSegmentCabin.getPrimaryKey();
//     BookingClassKey_T lClosedBookingClassKey =
//       BookingClassKey_T(lSegmentCabinKey,
//                         DEFAULT_CLOSED_CLASS_CODE);
//     BookingClass& lVirtualClosedClass =
//       FacBookingClass::instance().create (lClosedBookingClassKey);

//     lVirtualClosedClass.setSegmentCabin (ioSegmentCabin);
//     lVirtualClosedClass.setFareFamily (*lFareFamily_ptr);
//     lVirtualClosedClass.setYield (DEFAULT_YIELD_MAX_VALUE);

//     lClosedClassPolicy.addBookingClass(lVirtualClosedClass);
//     lOldPolicyList.push_back(&lClosedClassPolicy);


//     BomMapIterator_T<BookingClass, BookingClassList_T>
//       lBookingClassIterator (lBookingClassList);

//     for (lBookingClassIterator.begin();
//          lBookingClassIterator.hasNotReachedEnd();
//          lBookingClassIterator.iterate())  {

//       BookingClass* lCurrentBookingClass_ptr =
//         lBookingClassIterator.getCurrent();
//       assert (lCurrentBookingClass_ptr != NULL);

//       Policy& lTempPolicy =
//         FacPolicy::instance().create ();

//       lTempPolicy.addBookingClass(*lCurrentBookingClass_ptr);
//       lOldPolicyList.push_back(&lTempPolicy);
//     }

//     if (lFareFamilyIterator.hasNotReachedEnd()) {
       
//       lFareFamilyIterator.iterate();
       
//       BomListIterator_T<Policy, OrderedPolicyList_T>
//         lPolicyIterator (lOldPolicyList);
       
//       while (lFareFamilyIterator.hasNotReachedEnd()) {
//         FareFamily* llFareFamily_ptr =
//           lFareFamilyIterator.getCurrent();
//         assert (llFareFamily_ptr != NULL);
         
//         const BookingClassList_T& lNewBookingClassList =
//           llFareFamily_ptr->getBookingClassList();
//         BomMapIterator_T<BookingClass, BookingClassList_T>
//           lNewBookingClassIterator (lNewBookingClassList);
         
//         for (lPolicyIterator.begin();
//              lPolicyIterator.hasNotReachedEnd();
//              lPolicyIterator.iterate())  {
//           Policy* lPolicy_ptr =
//             lPolicyIterator.getCurrent();
//           assert (lPolicy_ptr != NULL);
           
//           Policy& ldTempPolicy = FacPolicy::instance().create ();
//           FacPolicy::copyClassList (*lPolicy_ptr, ldTempPolicy);
           
//           // TODO: create a method for that
//           /**Generation of a "closed virtual class" necessary to
//              represent policies where a family would be closed. */
//           SegmentCabinKey_T lSegmentCabinKey = 
//             ioSegmentCabin.getPrimaryKey();
//           BookingClassKey_T lClosedBookingClassKey = 
//             BookingClassKey_T(lSegmentCabinKey,
//                               DEFAULT_CLOSED_CLASS_CODE);
//           BookingClass& lVirtualClosedClass =
//             FacBookingClass::instance().create (lClosedBookingClassKey);
           
//           lVirtualClosedClass.setSegmentCabin (ioSegmentCabin);
//           lVirtualClosedClass.setFareFamily (*llFareFamily_ptr);
//           lVirtualClosedClass.setYield (DEFAULT_YIELD_MAX_VALUE);
           
//           //add this "closed FF class" to the already existing policies.
//           ldTempPolicy.addBookingClass(lVirtualClosedClass);
//           lPolicyList.push_back(&ldTempPolicy);
           
//           //else create new policies by adding the classes of the
//           //current family introduced.
//           for (lNewBookingClassIterator.begin();
//                lNewBookingClassIterator.hasNotReachedEnd();
//                lNewBookingClassIterator.iterate()) {
//             BookingClass* lBookingClass_ptr =
//               lNewBookingClassIterator.getCurrent();
//             assert (lBookingClass_ptr != NULL);
             
//             Policy& llTempPolicy = FacPolicy::instance().create ();
//             FacPolicy::copyClassList (*lPolicy_ptr, llTempPolicy);
//             llTempPolicy.addBookingClass(*lBookingClass_ptr);
//             lPolicyList.push_back(&llTempPolicy);
//           }
//         }
         
//         lOldPolicyList.clear();
//         lOldPolicyList = lPolicyList;
//         lPolicyList.clear();
//         lFareFamilyIterator.iterate() ;
         
//       }
//     }
//     if (lOldPolicyList.empty() == false) {
//       lPolicyHolder.setList (lOldPolicyList);
//     }
     
//     // DEBUG
//     // AIRSCHED_LOG_DEBUG("Policies" << lPolicyHolder.describe());
     
//   }

}
