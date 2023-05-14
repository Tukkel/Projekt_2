g++ -c ../PC.cpp ../User.cpp ../User.h ../dbHandler.cpp ../dbHandler.h ../PCHandler.cpp ../PCHandler.h;
g++ -o main.exe PC.o dbHandler.o User.o PCHandler.o;