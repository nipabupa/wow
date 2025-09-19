#include "common.h"
#include <vector>

#ifdef WIN32
#include <commdlg.h>
// 选择单个文件
void FileManager::SelectFile() {

}

// 选择多个文件
void FileManager::SelectFiles() {

}

// 选择目录
void FileManager::SelectDirectory() {

}

// 保存文件
void FileManager::SaveFile() {

}
#else
// 选择单个文件
std::string FileManager::SelectFile() {
    return "";
}

// 选择多个文件
std::vector<std::string> FileManager::SelectFiles() {
    std::vector<std::string> tmp;
    return tmp;
}

// 选择目录
std::string FileManager::SelectDirectory() {
    return "";
}

// 保存文件
std::string FileManager::SaveFile() {
    return "";
}
#endif
