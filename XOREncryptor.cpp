//
//  main.c
//  XOREncryptor
//
//  Created by Filip Busic on 10/20/20.
//

#include <string>
#include <boost/iostreams/device/mapped_file.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/filesystem.hpp>

namespace fs = boost::filesystem;
namespace bio = boost::iostreams;

char *__attribute__((noinline)) process_chunk(const char *inputBuffer, const size_t size, const std::string& key) {
    char *output = new char[size];
    // XOR inputBuffer by key
    for (size_t i = 0; i < size; i++) {
        output[i] = inputBuffer[i] ^ key[i % key.size()];
    }
    return output;
}

void read_in_chunks(bio::stream<bio::mapped_file_source> &inputStream, const std::string &key, const bio::mapped_file_source &mmap, bio::stream<bio::mapped_file_sink> &outputStream) {
    // Allocate buffer
    size_t bufferSize = mmap.size(); // MISTAKE: intended to be read by chunks, e.g, 4096
    char *buffer = new char[bufferSize];
    
    // Read, process, output
    do {
        inputStream.read(buffer, bufferSize);
        char *processedChunk = process_chunk(buffer, bufferSize, key);
        outputStream.write(processedChunk, bufferSize);
//        delete[] processedChunk; // whoops
    } while (inputStream);
    
    // Delete the buffer
    delete[] buffer;
}

int xor_transform(const std::string& filename, const std::string& outputFilename, const std::string& key = "ABC") {
    // Input
    bio::mapped_file_source mmap(filename);
    bio::stream<bio::mapped_file_source> inputStream(mmap, std::ios::binary);
    
    // Output
    bio::mapped_file_params outputParams(outputFilename);
    outputParams.new_file_size = mmap.size();
    outputParams.flags = bio::mapped_file::mapmode::readwrite;
    bio::stream<bio::mapped_file_sink> outputStream(outputParams);
    
    // Read in chunks
    read_in_chunks(inputStream, key, mmap, outputStream);
    
    // Close both streams
    inputStream.close();
    outputStream.close();
    
    return 0;
}

int main() {
    std::string prefix("xor_");
    fs::path path = fs::current_path();
    path += "/data"; // directory of random sized files
    for (const auto & entry : fs::directory_iterator(path)) {
        // Get files that match "xor_"
        if (entry.path().filename().string().substr(0, prefix.size()) == prefix) {
            int result = xor_transform(entry.path().string(), path.string() + "/encrypted/" + entry.path().filename().string());
            if (result != 0) {
                return result;
            }
        }
    }
    return 0;
}
