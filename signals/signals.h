#ifndef SIGNALS_H
#define SIGNALS_H

#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int handle_signal(void);
void (*current_handler_signal(void))(int);
void set_print_hello(void);
int handle_sigaction(void);
void (*current_handler_sigaction(void))(int);

#endif
