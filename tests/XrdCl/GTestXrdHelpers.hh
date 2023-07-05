#include <gtest/gtest.h>
#include <XrdCl/XrdClXRootDResponses.hh>
#include <cerrno>
#include <cstring>

#define GTEST_ASSERT_XRDST( x )                    \
{                                                    \
  XrdCl::XRootDStatus _st = x;                       \
  EXPECT_TRUE(_st.IsOK()) << "[" << #x << "]: " << _st.ToStr() << std::endl; \
}
