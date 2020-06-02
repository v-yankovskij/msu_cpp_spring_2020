#ifndef sort_h
#define sort_h

#include <algorithm>
#include <condition_variable>
#include <filesystem>
#include <fstream>
#include <mutex>
#include <queue>
#include <string>
#include <thread>
#include <vector>

class FileSorter
{
public:
    size_t buffer_size;
    std::vector<uint64_t> buffers[2];
    std::queue<std::vector<uint64_t>*> sort_queue;
    std::queue<std::vector<uint64_t>*> write_queue;
    std::mutex queue_mutex;
    std::priority_queue<SortedFile> sorted_files;
    std::mutex cond_mutex;
    std::condition_variable _cond;
    std::atomic<bool> _finished;
    
    FileSorter(size_t buffer_size_in_bytes)
    {
        buffer_size = buffer_size_in_bytes / sizeof(uint64_t) / 2;
        _finished = false;
        buffers[0].resize(buffer_size);
        buffers[1].resize(buffer_size);
    }
    
    void Run(const std::string& file_path, const std::string& save_path)
    {
        std::thread read_write_thread([this, &file_path](){ this->ReadWriteLoop(file_path);});
        std::thread sort_thread([this]() { this->SortLoop(); });
        read_write_thread.join();
        sort_thread.join();
        MergeFiles(save_path);
    }
    
    class SortedFile
    {
    public:
        uint64_t _elem;
        std::shared_ptr<std::ifstream> _file;
        std::string file_path;
        SortedFile(const std::string& FilePath)
        {
            _file = std::make_shared<std::ifstream>(filePath, std::ios::in | std::ios::binary)
            file_path = FilePath;
            d_file->read(reinterpret_cast<char*>(&_elem), sizeof(_elem));
        }
        bool operator<(const SortedFile& file) const
        {
            return _elem > file._elem;
        }
        void DeleteFile()
        {
            d_file->close();
            std::error_code error;
            std::experimental::filesystem::remove(std::experimental::filesystem::path(file_path), error);
        }
    };
    
    void ReadWriteLoop(const std::string& FilePath)
    {
        std::ifstream input_file(FilePath, std::ios::binary);
        if (!input_file.is_open())
        {
            throw std::runtime_error("Cannot open the file: " + FilePath);
        }
        auto read_to_buffer = [this](std::ifstream& file, std::vector<uint64_t>& buffer)
        {
            size_t elements_read = 0;
            while (elements_read < buffer.size() && file.read(reinterpret_cast<char*>(buffer.data() + elements_read), sizeof(uint64_t)))
            {
                elements_read++;
            }
            bool finished = elementsRead != buffer.size();
            if (finished)
            {
                buffer.resize(elements_read);
                std::lock_guard<std::mutex> lock(queue_mutex);
                sort_queue.push(&buffer);
            }
            _cond.notify_one();
            return finished;
        };
        auto write_file = [this, &FilePath](size_t file_index)
        {
            std::unique_lock<std::mutex> lock(cond_mutex);
            _cond.wait(lock, [this]() { return !write_queue.empty(); });
            std::vector<uint64_t>* sorted_buffer = nullptr;
            std::lock_guard<std::mutex> lock(queue_mutex);
            sorted_buffer = write_queue.front();
            write_queue.pop();
            if (!sorted_buffer->empty())
            {
                auto save_path = std::experimental::filesystem::path(FilePath).parent_path() / std::experimental::filesystem::path("tmp_" + std::to_string(file_index));
                std::ofstream tmp_file(save_path, std::ios::binary | std::ios::out);
                if (!tmp_file.is_open())
                {
                    throw std::runtime_error("Cannot open the file: " + save_path.string());
                }
                tmp_file.write(reinterpret_cast<const char*>(sortedBuffer->data()), sorted_buffer->size() * sizeof(uint64_t));
                tmp_file.close();
                sorted_files.push(SortedFile(save_path.string()));
            }
        };
        auto* read_buffer = &buffers[0];
        auto* sort_buffer = &buffers[1];
        _finished = readToBuffer(input_file, *readBuffer);
        std::swap(read_buffer, sort_buffer);
        size_t filesProcessed = 1;
        while(!_finished)
        {
            _finished = readToBuffer(inputFile, *readBuffer);
            std::swap(readBuffer, sortBuffer);
            
            writeFile(filesProcessed);
            ++filesProcessed;
        }
        writeFile(filesProcessed);
    }
    
    void SortLoop()
    {
        while (!_finished || !sort_queue.empty())
        {
            std::unique_lock<std::mutex> lock(cond_mutex);
            _cond.wait(lock, [this]() {return !sort_queue.empty(); });
            std::vector<uint64_t>* buffer = nullptr;
            {
                std::lock_guard<std::mutex> lock(queue_mutex);
                buffer = sort_queue.front();
                sort_queue.pop();
            }
            std::sort(buffer->begin(), buffer->end());
            {
                std::lock_guard<std::mutex> lock(queue_mutex);
                write_queue.push(buffer);
            }
            lock.unlock();
            _cond.notify_one();
        }
    }
    
    void MergeFiles(const std::string& save_path)
    {
        std::ofstream result(save_path, std::ios::binary | std::ios::out);
        while (!sorted_files.empty())
        {
            auto elem = sorted_files.top();
            sorted_files.pop();
            result.write(reinterpret_cast<char*>(&elem._elem), sizeof(elem._elem));
            if (elem.d_file->read(reinterpret_cast<char*>(&elem._elem), sizeof(uint64_t)))
            {
                sorted_files.push(elem);
            }
            else
            {
                elem.DeleteFile();
            }
        }
    }
};

#endif
