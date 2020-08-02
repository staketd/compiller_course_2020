import sys


def bytes_from_file(filename, chunksize=8192):
    with open(filename, "rb") as f:
        while True:
            chunk = f.read(chunksize)
            if chunk:
                yield chunk
            else:
                break


for word in bytes_from_file(sys.argv[1], 8):
    print(int.from_bytes(word, "little"))
