#ifndef  CRAILS_AUDIOFILE_HPP
# define CRAILS_AUDIOFILE_HPP

# include <crails/attachment.hpp>

namespace Crails
{
  class AudioFile : public Attachment
  {
  public:
    enum Format
    {
      OggFormat,
      WebmFormat,
      Mp3Format
    };

    AudioFile() {}
    AudioFile(const std::string& uid) : Attachment(uid) {}

    AudioFile as_format(Format) const;
  private:
    void convert(const std::string& extension, const std::string& mimetype, const std::string& codec);
  };
}

#endif
