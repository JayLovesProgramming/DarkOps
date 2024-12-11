//#include <fstream>
//#include <string>
//#include <regex>
//#include <ctime>
//#include <iomanip>
//#include <filesystem>
//#include <memory>
//#include <array>
//#include <sstream>
//#include <windows.h>
//
//class BuildWarningLogger {
//private:
//    std::ofstream logFile;
//    const std::string warningPattern = R"(warning C\d+:.*$)";
//    std::regex warningRegex;
//
//    std::string executeCommand(const std::string& command) {
//        std::array<char, 128> buffer;
//        std::string result;
//
//        // Create pipes for stdout and stderr
//        HANDLE hReadPipe, hWritePipe;
//        SECURITY_ATTRIBUTES saAttr;
//        saAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
//        saAttr.bInheritHandle = TRUE;
//        saAttr.lpSecurityDescriptor = NULL;
//
//        if (!CreatePipe(&hReadPipe, &hWritePipe, &saAttr, 0)) {
//            return "Failed to create pipe";
//        }
//
//        // Ensure the read handle is not inherited
//        SetHandleInformation(hReadPipe, HANDLE_FLAG_INHERIT, 0);
//
//        // Create the child process
//        STARTUPINFO si;
//        PROCESS_INFORMATION pi;
//        ZeroMemory(&si, sizeof(si));
//        si.cb = sizeof(si);
//        si.hStdError = hWritePipe;
//        si.hStdOutput = hWritePipe;
//        si.dwFlags |= STARTF_USESTDHANDLES;
//        ZeroMemory(&pi, sizeof(pi));
//
//        // Start the child process
//        if (CreateProcess(
//            NULL,                               // No module name (use command line)
//            const_cast<LPSTR>(command.c_str()), // Command line
//            NULL,                               // Process handle not inheritable
//            NULL,                               // Thread handle not inheritable
//            TRUE,                               // Handle inheritance
//            CREATE_NO_WINDOW,                   // Creation flags
//            NULL,                               // Use parent's environment block
//            NULL,                               // Use parent's starting directory 
//            &si,                                // Pointer to STARTUPINFO structure
//            &pi                                 // Pointer to PROCESS_INFORMATION structure
//        )) {
//            // Close write end of pipe
//            CloseHandle(hWritePipe);
//
//            // Read output from the child process
//            DWORD dwRead;
//            CHAR chBuf[4096];
//            BOOL bSuccess = FALSE;
//            HANDLE hParentStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
//
//            while (true) {
//                bSuccess = ReadFile(hReadPipe, chBuf, 4096, &dwRead, NULL);
//                if (!bSuccess || dwRead == 0) break;
//
//                result.append(chBuf, dwRead);
//                WriteFile(hParentStdOut, chBuf, dwRead, &dwRead, NULL); // Echo to console
//            }
//
//            // Wait for the process to finish
//            WaitForSingleObject(pi.hProcess, INFINITE);
//
//            // Close process and thread handles
//            CloseHandle(pi.hProcess);
//            CloseHandle(pi.hThread);
//        }
//
//        CloseHandle(hReadPipe);
//        return result;
//    }
//
//public:
//    BuildWarningLogger(const std::string& outputPath = "build_warnings.txt") {
//        warningRegex = std::regex(warningPattern);
//
//        // Create timestamp for the log file
//        auto now = std::time(nullptr);
//        auto tm = *std::localtime(&now);
//        std::ostringstream timestamp;
//        timestamp << std::put_time(&tm, "%Y%m%d_%H%M%S_");
//
//        // Create the full path with timestamp
//        std::string fullPath = timestamp.str() + outputPath;
//
//        logFile.open(fullPath, std::ios::out | std::ios::app);
//
//        if (logFile.is_open()) {
//            logFile << "Build Warning Log - " << std::put_time(&tm, "%Y-%m-%d %H:%M:%S") << "\n";
//            logFile << "============================================\n\n";
//        }
//    }
//
//    ~BuildWarningLogger() {
//        if (logFile.is_open()) {
//            logFile.close();
//        }
//    }
//
//    bool monitorBuild(const std::string& solutionPath, const std::string& configuration = "Release", const std::string& platform = "x64") {
//        std::string buildCommand = "MSBuild.exe \"" + solutionPath + "\" /p:Configuration=" + configuration + " /p:Platform=" + platform;
//
//        logFile << "Starting build with command: " << buildCommand << "\n\n";
//
//        std::string buildOutput = executeCommand(buildCommand);
//        logWarning(buildOutput);
//
//        return true;
//    }
//
//    void logWarning(const std::string& buildOutput) {
//        if (!logFile.is_open()) return;
//
//        std::string line;
//        std::istringstream stream(buildOutput);
//        std::string currentFile;
//
//        while (std::getline(stream, line)) {
//            // Check if line contains a file path
//            if (line.find(".cpp") != std::string::npos ||
//                line.find(".hpp") != std::string::npos ||
//                line.find(".h") != std::string::npos) {
//                if (line.find("compiling source file") != std::string::npos) {
//                    currentFile = line;
//                }
//            }
//
//            // Check for warning using regex
//            std::smatch match;
//            if (std::regex_search(line, match, warningRegex)) {
//                // If we have a current file context, log it
//                if (!currentFile.empty()) {
//                    logFile << "File: " << currentFile << "\n";
//                }
//
//                // Log the warning
//                logFile << line << "\n";
//
//                // Add any additional context lines that follow
//                std::string nextLine;
//                while (std::getline(stream, nextLine)) {
//                    if (nextLine.find("see declaration") != std::string::npos ||
//                        nextLine.find("with") != std::string::npos ||
//                        nextLine.find("and") != std::string::npos ||
//                        nextLine.find("[") != std::string::npos ||
//                        nextLine.find("]") != std::string::npos) {
//                        logFile << nextLine << "\n";
//                    }
//                    else {
//                        // Put the line back in the stream
//                        stream.seekg(-static_cast<int>(nextLine.length()) - 1, std::ios_base::cur);
//                        break;
//                    }
//                }
//                logFile << "\n";
//            }
//        }
//
//        logFile.flush();
//    }
//
//    void addSeparator() {
//        if (logFile.is_open()) {
//            logFile << "\n----------------------------------------\n\n";
//        }
//    }
//};