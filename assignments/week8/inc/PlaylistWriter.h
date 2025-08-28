#ifndef PlaylistWriter_H
#define PlaylistWriter_H

#include <string>

#include "IPlaylistWriter.h"

class PlaylistWriter : public IPlaylistWriter {
private:
    std::string basePath;

public:
    PlaylistWriter(const std::string& path);
    void save(const std::vector<std::string>& songs, const std::string& name) override;
    std::vector<std::string> load(const std::string& name) override;
    std::vector<std::string> getAllPlaylists() const override;
};

#endif