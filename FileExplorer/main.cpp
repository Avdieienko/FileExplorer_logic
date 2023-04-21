#include <iostream>
#include <windows.h>
#include <filesystem>
#include <string>
#include <vector>

namespace fs = std::filesystem;

int main() {
	fs::path filePath;
	std::string pick;
	std::vector<std::string> arr;
	fs::path currentPath = fs::current_path();
	std::vector<fs::path> history;


  	while (true) {
		std::cout << "Current directory is " << currentPath.string() << std::endl;
		std::cout << "Directory list: " << std::endl;

		// Create directory of this path
		for (const auto& entry : fs::directory_iterator(currentPath)) {
			arr.push_back(entry.path().string());
			std::cout << entry.path().string() << std::endl;
		}

		std::cout << "\n Name of the file, type 'exit' to exit current path, or type 'back' to retur previous path: ";
		std::cin >> pick;

		// If user decided to go back
		if (pick == "back") {
			// Check if array is "Empty"
			if (history.size() == 0) {
				continue;
			}
			std::cout << history.back().string() << std::endl;
			// Assign current path to the last path in history
			currentPath = history.back();
			history.pop_back();
			continue;
		}
		// If user decided to exit to the parent path
		if (pick == "exit") {
			// Add current path to the history
			history.push_back(currentPath);
			// Assign current path to the parent path
			currentPath = currentPath.parent_path();
			std::cout << currentPath.string() << std::endl;
		}
		else {
			// Add picked file to the current path
			filePath = currentPath;
			filePath /= pick;
			// Check if file path exists
			if (std::find(std::begin(arr), std::end(arr), filePath) == std::end(arr)) {
				std::cout << "File was not found..." << std::endl;
				continue;
			}
			// Check if file is executable
			if (fs::status(filePath).type() != fs::file_type::directory) {
				// Execute file
				ShellExecute(NULL, L"open", filePath.wstring().c_str(), NULL, NULL, SW_SHOW);
			}
			else {
				// Save current path 
				history.push_back(currentPath);
				// Change current path to be opened file
				currentPath = filePath;
			}
		}		
	}
	
	return 0;
}