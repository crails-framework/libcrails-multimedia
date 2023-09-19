#ifndef  CRAILS_VIDEOFILE_HPP
# define CRAILS_VIDEOFILE_HPP

# include <crails/attachment.hpp>

namespace Crails
{
  class VideoFile : public Attachment
  {
  public:
    enum Format
    {
      OggFormat,
      WebmFormat,
      Mp4Format
    };

    VideoFile() {}
    VideoFile(const std::string& uid) : Attachment(uid) {}

    VideoFile as_format(Format);
  private:
    void convert(const std::string& extension, const std::string& mimetype, const std::string& video_codec, const std::string& audio_codec);
  };
}

#endif
