#pragma once
#include <fstream>
#include <string>
#include "utils.hpp"
namespace cinatra {
    static bool use_raw_file_name = true;
    class upload_file {
    public:
        void write(const char* data, size_t size) {
            file_size_ += size;
            file_.write(data, size);
        }

        bool open(const std::string& file_name, const std::string& raw_file_name = "") {
            file_.open(file_name, std::ios::binary | std::ios::app);
            bool r = file_.is_open();
            if (r)
            {
                file_path_ = std::string(&file_name[0], file_name.length());
                raw_file_name_ = raw_file_name;
            }

            return r;
        }

        bool remove()
        {
            file_.close();
            bool flag = fs::remove(fs::path(file_path_.c_str()));
            file_path_ = "";
            file_size_ = 0;
            return flag;
        }

        bool copy_to(const std::string& directory_path, const std::string& file_name = "") const
        {
            check_and_create_directory(directory_path);
            auto write_file_name = file_path_.substr(file_path_.rfind("/") + 1);
            if (!file_name.empty()){
                write_file_name = file_name;
            }
            auto write_directory_path = directory_path.back() == '/' ? directory_path : directory_path + "/";
            bool flag = fs::copy_file(fs::path(file_path_.c_str()), fs::path(write_directory_path + write_file_name));
            return flag;
        }

        bool move_to(const std::string& directory_path, const std::string& file_name = "")
        {
            check_and_create_directory(directory_path);
            auto write_file_name = file_path_.substr(file_path_.rfind("/") + 1);
            if (!file_name.empty()){
                write_file_name = file_name;
            }
            auto write_directory_path = directory_path.back() == '/' ? directory_path : directory_path + "/";
            bool flag0 = fs::copy_file(fs::path(file_path_.c_str()), fs::path(write_directory_path + write_file_name));
            file_.close();
            bool flag1 = fs::remove(fs::path(file_path_.c_str()));
            file_path_ = write_directory_path + write_file_name;
            return (flag0 && flag1);
        }

        void rename_file(const std::string& new_file_name)
        {
            //auto directory_path = file_path_.substr(0,file_path_.rfind("/"));
            //auto new_file_path = directory_path+"/"+new_file_name;

            if (use_raw_file_name)
            {
                std::filesystem::path directory_path = file_path_;
                auto new_file_path = directory_path.parent_path() / raw_file_name_;
                std::error_code code;
                fs::rename(file_path_, new_file_path, code);
                if (!code) {
                    file_path_ = new_file_path.string();
                }
            }
            else
            {
                std::error_code code;
                fs::rename(file_path_, new_file_name, code);
                if (!code) {
                    file_path_ = new_file_name;
                }
            }
        }


        void close() {
            file_.close();
        }

        size_t get_file_size() const{
            return file_size_;
        }

        std::string get_file_path() const{
            return file_path_;
        }
        std::string get_raw_file_name() const{
            return raw_file_name_;
        }

        bool is_open() const {
            return file_.is_open();
        }

    private:
        void check_and_create_directory(const std::string& direcotry_path) const
        {
            auto vec = cinatra::split(std::string_view(direcotry_path.data(), direcotry_path.size()), "/");
            std::string tmp_directory = "";
            for (auto iter = vec.begin(); iter != vec.end(); ++iter){
                tmp_directory += std::string(iter->data(), iter->size()) + "/";
                if (iter != vec.begin()){
                    auto current_direcotry = tmp_directory.substr(0, tmp_directory.size() - 1);
                    if (!fs::exists(current_direcotry)){
                        fs::create_directory(current_direcotry.data());
                    }
                }
            }
        }
    private:
        //std::string file_name_;
        std::string file_path_;
        std::ofstream file_;
        size_t file_size_ = 0;
        std::string raw_file_name_;
    };
}
