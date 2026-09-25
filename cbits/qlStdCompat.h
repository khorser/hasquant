#ifndef QL_STD_COMPAT_H
#define QL_STD_COMPAT_H

#include <ql/version.hpp>
#include <ql/optional.hpp>
#include <ql/any.hpp>

// QuantLib's optional and any: std, or boost on a QuantLib <= 1.43 built without the std flags.
#if QL_HEX_VERSION < 0x01440000 && !defined(QL_USE_STD_OPTIONAL)
using boost::optional;
inline const boost::none_t& nullopt = boost::none;
#else
using std::optional;
using std::nullopt;
#endif
#if QL_HEX_VERSION < 0x01440000 && !defined(QL_USE_STD_ANY)
using boost::any;
using boost::any_cast;
#else
using std::any;
using std::any_cast;
#endif

#endif
