#include "paths.h"

bool nameEndWithAsmExtension(const char *name) {
    return !strcmp(".asm", name + strlen(name) - 4) && name[0] != '.';
}

bool isAsmFile(const struct dirent *file) {
    return nameEndWithAsmExtension(file->d_name);
}

std::string cleanPathTrailFromString(std::string path) {
    path.pop_back();
    return path;
}

void set_paths_relative_to(const char **path, const char *arg0) {

    if (*path == nullptr)
        return;

    std::filesystem::path absBasePath(std::filesystem::absolute(arg0));
    absBasePath.remove_filename();
#ifdef DEBUGMSG
    debug_print("Absolute base path: %s ", absBasePath.generic_string().c_str());
#endif
    std::filesystem::path filePath(*path);
    std::string newPath{};
    if (filePath.is_relative()) {
        newPath = absBasePath.generic_string() + filePath.generic_string();
    } else {
        newPath = filePath.generic_string();
    }
#ifdef DEBUGMSG
    debug_print("%s\n", newPath.c_str());
#endif

    if (std::filesystem::is_directory(newPath) && newPath.back() != '/') {
        char *newCharPath = new char[newPath.length() + 2];
        strcpy(newCharPath, newPath.c_str());
        strcat(newCharPath, "/");
        *path = newCharPath;
    } else {
        char *newCharPath = new char[newPath.length() + 1];
        strcpy(newCharPath, newPath.c_str());
        *path = newCharPath;
    }
}