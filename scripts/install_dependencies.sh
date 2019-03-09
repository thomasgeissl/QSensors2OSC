#!/bin/sh
cd ../
mkdir libs
cd libs
git clone https://github.com/thomasgeissl/QOSC.git
git clone https://github.com/nlohmann/json.git

git clone git://code.qt.io/qt/qtmqtt.git
cd qtmqtt
qmake
make
make install
