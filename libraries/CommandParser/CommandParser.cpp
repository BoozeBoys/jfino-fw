#include <CommandParser.h>

#include <Arduino.h>

CommandParser::CommandParser()
{
  reset();
}

bool CommandParser::put(char c)
{
  if ((this->len + 1) > BUFSIZE) {
    reset();
  }

  if (c == ' ') {
    this->n_args++;
  }

  this->buf[this->len] = c == ' ' ? '\0' : c;
  this->len++;

  return c == '\n';
}

char *CommandParser::command()
{
  return this->buf;
}

int CommandParser::argsN() const {
  return this->n_args;
}

char *CommandParser::arg(int n)
{
  for(int i = 0; i < this->len; i++) {
    if (this->buf[i] == '\0') {
      n--;
      if (n == 0) {
        return &(this->buf[i+1]);
      }
    }
  }

  return NULL;
}

void CommandParser::reset()
{
  memset(this->buf, 0, BUFSIZE);
  this->len = 0;
  this->n_args = 0;
}
