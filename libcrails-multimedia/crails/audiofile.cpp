#include "audiofile.hpp"
#include "multimedia_convert_failure.hpp"
#include <boost/process.hpp>

using namespace std;
using namespace Crails;

AudioFile AudioFile::as_format(Format format) const
{
  AudioFile copy(*this);

  switch (format)
  {
  case Mp3Format:
    copy.convert("mp3", "audio/mpeg", "libmp3lame");
    break ;
  case WebmFormat:
    copy.convert("weba", "audio/webm", "libopus");
    break ;
  case OggFormat:
    copy.convert("oga", "audio/ogg", "libvorbis");
    break ;
  }
  return copy;
}

void AudioFile::convert(const string& extension, const string& mimetype, const string& codec)
{
  string source = get_filepath();
  string output;
  string command;

  this->extension = extension;
  this->mimetype = mimetype;
  this->operator=(this->name + '.' + this->mimetype + '.' + this->extension);
  output = get_filepath();
  command = "ffmpeg -y -i \"" + source + "\" -acodec " + codec + " \"" + output + '"';

  boost::process::child process(command);

  process.wait();
  if (process.exit_code() != 0)
    throw MultimediaConvertFailure("could not convert audio file to " + mimetype);
}
