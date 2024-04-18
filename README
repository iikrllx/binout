# binout
This simple program works with decimal numbers converting them to binary.
The input data are decimal numbers, and the output is binary numbers.
This program can help beginners understand binary numbers. However,
I would recommend using a ```gdb``` shell instead, as ```gdb``` has more functions
for working with numbers. For example:

```
$ gdb
$ help x                 # for familarization
$ print /t 3             # 11 (binary)
$ print /x 255           # oxff (hexadecimal)
$ print /o 255           # 0377 (octal)
$ print /d 0XFF          # 255 (decimal)
$ print 0b11111111       # 255 (decimal)
```

## Testing
Let's go back to ```binout``` =)

Project cloning, preparation and testing:
```
$ git clone https://github.com/iikrllx/binout.git
$ cd binout; make; cd src
$ ./binout --help
```

Check bit:
```
$ ./binout -c 4294967295
11111111111111111111111111111111(4294967295)
```

Find the flag between the two decimal numbers:
```
$ ./binout -f 4294967295 12
Flag found:
                            1100(12)
11111111111111111111111111111111(4294967295)
```

Unset the bit in the desired position:
```
$ ./binout -p 5 -u 32
(0)
```

Set the bit in the desired position:
```
$ ./binout -p 18 -s 32
1000000000000100000(262176)
```

## Installing the package in Debian
If necessary, you can build a ```deb``` package with this program:
$ fakeroot dpkg-buildpackage -b -uc
$ sudo apt install ../binout_1.0_amd64.deb

## License
This project is licensed under the GPLv3 License - see the LICENSE file for details
