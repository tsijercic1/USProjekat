echo "Building..."
sudo g++ $1.cpp -o $1 -lpthread -lwiringPi -Wno-psabi