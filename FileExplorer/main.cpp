#include <iostream>
#include <windows.h>
#include <filesystem>
#include <string> 

namespace fs = std::filesystem;

int main() {
	int ind = 0;
	int historyInd = -1;
	fs::path filePath;
	std::string pick, arr[1000];
	fs::path currentPath = fs::current_path();
	fs::path history[100];


  	while (true) {
		std::cout << "Current directory is " << currentPath.string() << std::endl;
		std::cout << "Directory list: " << std::endl;

		// Create directory of this path
		for (const auto& entry : fs::directory_iterator(currentPath)) {
			arr[ind] = entry.path().string();
			std::cout << entry.path().string() << std::endl;
			ind++;
		}

		ind = 0;

		std::cout << "\n Name of the file, type 'exit' to exit current path, or type 'back' to retur previous path: ";
		std::cin >> pick;

		// If user decided to go back
		if (pick == "back") {
			// Check if array is "Empty"
			if (historyInd < 0) {
				continue;
			}
			std::cout << history[historyInd].string() << std::endl;
			// Assign current path to the last path in history
			currentPath = history[historyInd];
			// Reduce previous path index
			historyInd--;
			continue;
		}
		// If user decided to exit to the parent path
		if (pick == "exit") {
			// Add current path to the history
			historyInd++;
			history[historyInd] = currentPath;
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
			if (filePath.extension().string() != "") {
				// Execute file
				ShellExecute(NULL, L"open", filePath.wstring().c_str(), NULL, NULL, SW_SHOW);
			}
			else {
				// Save current path 
				historyInd++;
				history[historyInd] = currentPath;
				// Change current path to be opened file
				currentPath = filePath;
			}
		}		
	}
	
	return 0;
}