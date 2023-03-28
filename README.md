# macset

macset is a command-line tool for changing the MAC (Media Access Control) address of a network interface in Linux and UNIX like operating systems.

## Features

- Randomize the MAC address of a network interface using the `-r` flag.
- Set the MAC address of a network interface to a specific value using the `-s` flag and specifying the MAC address as an argument.

## Installation

To install macset, clone the repository and build the source code:
git clone https://github.com/mara101/macset.git


## Usage

To use macset, invoke the `macset` executable with the desired flags and arguments.

### Randomize the MAC address

To randomize the MAC address of a network interface, use the `-r` flag and specify the name of the interface as an argument:
./macset eth0 -r


This will randomize the MAC address of the `eth0` interface.

### Set the MAC address

To set the MAC address of a network interface to a specific value, use the `-s` flag and specify the MAC address and the name of the interface as arguments:

./macset eth0 -s 00:11:22:33:44:55 

This will set the MAC address of the `eth0` interface to 00:11:22:33:44:55.

## License

macset is released under the MIT License. See the LICENSE file for details.

## Credits

macset was developed by FILIPPO MARANGONI.



