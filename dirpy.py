import os
import sys
import stat

# dato un file 'f' passato come argomento e la cwd
# trova i symlink di 'f'
# trova gli hardlink di 'f'
# li stampa

def main():
    f = sys.argv[1]
    pathf = os.path.abspath(f)

    sb = os.stat(pathf)

    if sb.st_nlink == 1:
        print(f"il file {f} non ha HARDLINK")

    curdir = os.getcwd()
    for entry in os.listdir(curdir):
        filepath = os.path.join(curdir, entry)

        fileinfo = os.lstat(filepath)

        if stat.S_ISREG(fileinfo.st_mode):
            if sb.st_dev == fileinfo.st_dev and sb.st_ino == fileinfo.st_ino and filepath != pathf:
                print(f"Il file {filepath} e' un HARDLINK di {f}")

        elif stat.S_ISLNK(fileinfo.st_mode):
            fullfilepath = os.path.realpath(filepath)
            if fullfilepath == pathf:
                print(f"Il file {filepath} e' un SYMLINK di {f}")

if __name__ == "__main__":
    main()