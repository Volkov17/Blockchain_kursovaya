
#ifndef BLOCKCHAIN_KURS_EXEPTIONS_H
#define BLOCKCHAIN_KURS_EXEPTIONS_H

class mathErr
{
  const char *What;
public:
  const char *what () { return What; }
  mathErr(const char *inp):What(inp) {}
};


class rsaErr
{
  const char *What;
public:
  const char *what () { return What; }
  rsaErr(const char *inp):What(inp) {}
};


class commandErr {};


class fileErr
{
  const char *Filename;
public:
  const char *filename () { return Filename; }
  fileErr(const char *inp):Filename (inp) {}
};

#endif
