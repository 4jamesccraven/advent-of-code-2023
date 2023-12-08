.PHONY: all
all:
	g++ -std=c++17 -Wall -pedantic calibrationCode.cpp -o calibrationCode.exe

.PHONY: clean, cleanwin
clean:
	rm -f *.exe, *.o

cleanwin:
	powershell -command "Remove-Item *.exe; Remove-Item *.o"