#include <filesystem>
#include <fstream>
#include <iostream>

#include "PlaylistWriter.h"

namespace fs = std::filesystem;

PlaylistWriter::PlaylistWriter(const std::string& path) : basePath(path) {
    try {
        if (!fs::exists(basePath)) {
            fs::create_directories(basePath);
            std::cout << "Created playlists directory: " << basePath << std::endl;
        }
    } catch (const fs::filesystem_error& e) {
        std::cout << "Error: Could not create playlists directory: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Unexpected error: " << e.what() << std::endl;
    }
}

void PlaylistWriter::save(const std::vector<std::string>& songs, const std::string& name) {
    std::ofstream file(basePath + "/" + name + ".txt");
    for (const auto& song : songs) {
        file << song << "\n";
    }
}

std::vector<std::string> PlaylistWriter::load(const std::string& name) {
    std::vector<std::string> songs;
    std::ifstream file(basePath + "/" + name + ".txt");
    std::string line;
    
    while (std::getline(file, line)) {
        if (!line.empty()) {
            songs.push_back(line);
        }
    }
    
    return songs;
}

std::vector<std::string> PlaylistWriter::getAllPlaylists() const {
    std::vector<std::string> playlists;
    
    for (const auto& entry : fs::directory_iterator(basePath)) {
        if (entry.path().extension() == ".txt") {
            playlists.push_back(entry.path().stem().string());
        }
    }
    
    return playlists;
} 