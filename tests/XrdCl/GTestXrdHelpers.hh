/** Contains some of the macros found in CppUnitXrdHelpers.hh,
 *  converted into GTest equivalent. 
 * 
 *  Created by Angelo Galavotti in 2023.
 */

#include <gtest/gtest.h>
#include <XrdCl/XrdClXRootDResponses.hh>
#include <cerrno>
#include <cstring>

/** @brief Equivalent of CPPUNIT_ASSERT_XRDST
 * 
 * Shows the code that we are asserting and its value 
 * in the final evaluation. 
 */
#define GTEST_ASSERT_XRDST( x )                    \
{                                                    \
  XrdCl::XRootDStatus _st = x;                       \
  EXPECT_TRUE(_st.IsOK()) << "[" << #x << "]: " << _st.ToStr() << std::endl; \
}
