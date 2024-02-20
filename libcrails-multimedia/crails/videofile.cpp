#include "videofile.hpp"
#include "multimedia_convert_failure.hpp"
#include <boost/process.hpp>
#include <crails/logger.hpp>
#include <filesystem>

using namespace std;
using namespace Crails;

VideoFile VideoFile::as_format(Format format)
{
  VideoFile copy(*this);

  switch (format)
  {
  case Mp4Format:
    copy.convert("mp4", "video/mp4", "libx264", "libmp3lame");
    break ;
  case WebmFormat:
    copy.convert("webm", "video/webm", "libvpx-vp9", "libopus");
    break ;
  case OggFormat:
    copy.convert("ogv", "video/ogg", "libtheora", "libvorbis");
    break ;
  }
  return copy;
}

void VideoFile::convert(const string& extension, const string& mimetype, const string& vcodec, const string& acodec)
{
  string command;
  string source = get_filepath();
  string output;

  this->extension = extension;
  this->mimetype = mimetype;
  this->operator=(this->name + '.' + this->mimetype + '.' + this->extension);
  output = get_filepath();

  if (filesystem::exists(source))
  {
    command = "ffmpeg -y -i \"" + source + "\" -c:v " + vcodec + " -a:v " + acodec + " \"" + output + '"';
  
    logger << Logger::Info << "Converting videofile:\n" << command << Logger::endl;

    boost::process::child process(command);

    process.wait();
    if (process.exit_code() != 0)
      throw MultimediaConvertFailure("could not convert video file to " + mimetype);
  }
  else
    throw MultimediaConvertFailure("source file does not exist: " + source);
}
