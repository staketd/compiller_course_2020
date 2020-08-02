./myCompiller $1
gcc -nostdlib -g Asm.s
./a.out > bytes
python3 byte-reader.py bytes
