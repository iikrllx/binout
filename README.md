<a href="https://github.com/iikrllx/binout">
    <img src="https://img.shields.io/badge/it's%20nothing%20serious%20here-blue?style=for-the-badge">
</a>
<a href="https://github.com/iikrllx/binout">
    <img src="https://img.shields.io/badge/simple-green?style=for-the-badge">
</a>
<a href="https://github.com/iikrllx/binout/blob/master/src/binout.c">
    <img src="https://img.shields.io/badge/binout-red?style=for-the-badge">
</a>

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
$ print /d 0Xff          # 255 (decimal)
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
$ ./binout -c 1234
10011010010(1234)
```

Find the flag between the two decimal numbers:
```
$ ./binout -f 1234 14
Flag found:
       1110(14)
10011010010(1234)
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
```
$ fakeroot dpkg-buildpackage -b -uc
$ sudo apt install ../binout_1.0_amd64.deb
```
