#ifndef COMMAND_PARSER_H
#define COMMAND_PARSER_H

#define BUFSIZE 32

class CommandParser {
public:
  CommandParser();

  bool put(char c);

  char *command();
  int argsN() const;
  char *arg(int n);

  void reset();

private:
  char buf[BUFSIZE];
  int n_args;
  int len;
};

#endif
