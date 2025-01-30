#include <iostream>
#include <fstream>
#include <string>

int main() {
    std::ifstream file("dailyEntryDatabase.txt", std::ios::binary);
    
    if (file.is_open()) {
        // Move to the last byte of the file
        file.seekg(0, std::ios::end);
        
        // Get the current position (i.e., the size of the file)
        std::streamoff fileSize = file.tellg();
        std::string lastLine;
        // Iterate backward through the file
        for (std::streamoff i = fileSize - 1; i >= 0; i--) {
            // Move the get pointer to the current position
            file.seekg(i, std::ios::beg);
            
            // Read the current byte
            char ch;
            file.get(ch);
            if(ch=='\n'){
                break;
            }
            lastLine = ch+lastLine;
        }
        
        file.close();
        std::cout<<lastLine;
    }
    
    return 0;
}
