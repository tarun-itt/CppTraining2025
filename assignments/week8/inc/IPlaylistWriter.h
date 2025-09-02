#ifndef IPLAYLISTSTORAGE_H
#define IPLAYLISTSTORAGE_H

#include <string>
#include <vector>

class IPlaylistWriter {
public:
    virtual ~IPlaylistWriter() = default;
    virtual void save(const std::vector<std::string>& songs, const std::string& name) = 0;
    virtual void deletePlaylist(const std::string& name) = 0;
    virtual std::vector<std::string> load(const std::string& name) = 0;
    virtual std::vector<std::string> discoverPlaylists() const = 0;
};

#endif