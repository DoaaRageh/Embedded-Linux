#!/bin/bash

user="doaa"
group="elryan"

if ! grep "^${group}:" /etc/group;then
	sudo groupadd "$group"
fi

if grep "^${user}:" /etc/passwd;then
        echo ""$user" already exists."
	sudo usermod -aG "$group" "$user"
else
        sudo useradd -m -G "$group" "$user"
fi
echo ""$user" has been added to "$group" group successfully"

echo "User Information:"
id "$user"

echo "Group Information:"
getent group "$group"

