#include "common.h"

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
void FileManager::SelectFile(char* filename) {

}

// 选择多个文件
void FileManager::SelectFiles() {

}

// 选择目录
void FileManager::SelectDirectory(char* dirname) {

}

// 保存文件
void FileManager::SaveFile() {

}
#endif
