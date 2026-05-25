#ifndef  CRAILS_MULTIMEDIA_CONVERT_FAILURE_HPP
# define CRAILS_MULTIMEDIA_CONVERT_FAILURE_HPP

# include <string>
# include <crails/utils/backtrace.hpp>

namespace Crails
{
  struct MultimediaConvertFailure : public boost_ext::runtime_error
  {
    MultimediaConvertFailure(const std::string& msg) : boost_ext::runtime_error(msg)
    {}
  };
}

#endif
