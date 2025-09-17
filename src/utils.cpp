#ifdef WIN32
// 选择单个文件
void SelectFile() {

}

// 选择多个文件
void SelectFiles() {

}

// 选择目录
void SelectDirectory() {

}

// 保存文件
void SaveFile() {

}
#else
// 选择单个文件
void SelectFile(char* filename) {

}

// 选择多个文件
void SelectFiles() {

}

// 选择目录
void SelectDirectory(char* dirname) {

}

// 保存文件
void SaveFile() {

}
#endif
