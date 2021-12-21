g++ main.cpp parser.cpp utils.cpp -o "build/main.exe" -Wall -std=c++17; 
if ($?) {
    & "./build/main.exe"
}