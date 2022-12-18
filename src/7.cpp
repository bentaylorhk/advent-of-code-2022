/**
 * Benjamin Michael Taylor
 * 2022
 */

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

class File {
   public:
    std::string name;
    int size;

    File(std::string name, int size) : name(std::move(name)), size(size) {
    }
};

class Dir {
   public:
    std::string name;
    std::vector<File*> files;
    std::vector<Dir*> dirs;
    Dir* parent;
    int size;

    Dir(std::string name, Dir* parent)
        : name(std::move(name)), parent(parent), size(0) {
    }

    void addFile(File* file) {
        files.push_back(file);
        this->propagateFileSize(file->size);
    }

    void addDir(Dir* dir) {
        dirs.push_back(dir);
    }

    bool containsFile(const std::string& fileName) {
        for (const File* file : files) {
            if (file->name == fileName) {
                return true;
            }
        }
        return false;
    }

    bool containsDir(const std::string& fileName) {
        for (const Dir* dir : dirs) {
            if (dir->name == fileName) {
                return true;
            }
        }
        return false;
    }

    Dir* getDir(const std::string& dirName) {
        for (Dir* dir : dirs) {
            if (dir->name == dirName) {
                return dir;
            }
        }
        return nullptr;
    }

    std::string toString(int indentCount) {
        std::string dirString;
        for (int i = 0; i < indentCount; i++) {
            dirString += " ";
        }
        dirString = "- " + this->name + " (dir)\n";
        for (Dir* dir : dirs) {
            for (int i = 0; i < indentCount + 2; i++) {
                dirString += " ";
            }
            dirString += dir->toString(indentCount + 2);
        }
        for (File* file : files) {
            for (int i = 0; i < indentCount + 2; i++) {
                dirString += " ";
            }
            dirString += "- " + file->name + " (file)\n";
        }
        return dirString;
    }

    void free() {
        for (Dir* dir : dirs) {
            dir->free();
            delete dir;
        }
    }

    void propagateFileSize(int sizeIncrease) {
        this->size += sizeIncrease;
        if (parent != nullptr) {
            parent->propagateFileSize(sizeIncrease);
        }
    }

    int getDeleteSize(int maxSize = 100000) {
        if (this->size <= maxSize) {
            return this->size;
        } else {
            int sum = 0;
            for (Dir* dir : this->dirs) {
                sum += dir->getDeleteSize();
            }
            return sum;
        }
    }
};

std::vector<std::string> split(const std::string& string) {
    std::vector<std::string> words;
    std::stringstream ss(string);
    std::string word;
    while (std::getline(ss, word, ' ')) {
        words.push_back(word);
    }
    return words;
}

int main(int argc, char* argv[]) {
    std::ifstream file(INPUT_FILENAME);
    std::string line;

    Dir* rootDir = new Dir("/", nullptr);
    Dir* currentDir = rootDir;

    while (std::getline(file, line)) {
        std::vector<std::string> words = split(line);

        if (words[0] == "$") {
            if (words[1] == "cd") {
                std::string dirName = words[2];
                if (dirName == "/") {
                    currentDir = rootDir;
                } else if (dirName == "..") {
                    currentDir = currentDir->parent;
                } else {
                    if (currentDir->containsDir(dirName)) {
                        currentDir = currentDir->getDir(dirName);
                    } else {
                        Dir newDir(dirName, currentDir);
                        currentDir = &newDir;
                    }
                }
            }
        } else {
            std::string fileName = words[1];
            if (currentDir->containsFile(fileName) ||
                currentDir->containsDir(fileName)) {
                continue;
            }
            if (words[0] == "dir") {
                Dir* newDir = new Dir(fileName, currentDir);
                currentDir->addDir(newDir);
            } else {
                File* newFile = new File(fileName, std::stoi(words[0]));
                currentDir->addFile(newFile);
            }
        }
    }

    std::printf(rootDir->toString(0).c_str());

    std::printf("Sum: %d\n", rootDir->size);

    std::printf("Delete Size: %d\n", rootDir->getDeleteSize());

    rootDir->free();
    delete rootDir;

    return EXIT_SUCCESS;
}