#!/bin/bash

# setup code server
sudo sh /home/student/build/code-server.sh --prefix=/usr/local/

# setup Python packages
source /opt/env/python3/bin/activate
sudo pip install jupyter   

sudo cp /home/student/build/entrypoint.sh /usr/local/bin/entrypoint.sh
sudo chmod 755 /usr/local/bin/entrypoint.sh  
