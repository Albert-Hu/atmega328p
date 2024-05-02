#include <avr/wdt.h>
#include <stdio.h>

#include "command.h"

#define LINE_BUFFER_SIZE 128
#define ARGUMENT_BUFFER_SIZE 32

// declare the command functions
static void command_help(mcucli_t *cli, void *user_data, int argc,
                         char *argv[]);
static void command_echo(mcucli_t *cli, void *user_data, int argc,
                         char *argv[]);

static mcucli_command_t commands[] = {
    {"help", "Print this help message", command_help},
    {"?", "Print this help message", command_help},
    {"echo", "Echo the arguments", command_echo}};

static mcucli_command_set_t command_set = {
    .commands = commands,
    .num_commands = sizeof(commands) / sizeof(mcucli_command_t),
};

static char line_buffer[LINE_BUFFER_SIZE];
static char *argument_buffer[ARGUMENT_BUFFER_SIZE];
static mcucli_buffer_t buffer = {line_buffer, LINE_BUFFER_SIZE, argument_buffer,
                                 ARGUMENT_BUFFER_SIZE};

static void unknown_command(mcucli_t *cli, void *user_data,
                            const char *command) {
  UNUSED(cli);
  UNUSED(user_data);
  printf("Unknown command: %s\r\n", command);
}

static void command_help(mcucli_t *cli, void *user_data, int argc,
                         char *argv[]) {
  for (size_t i = 0; i < command_set.num_commands; i++) {
    printf("- %s\r\n", command_set.commands[i].name);
    printf("%s\r\n\r\n", command_set.commands[i].help);
  }
}

static void command_echo(mcucli_t *cli, void *user_data, int argc,
                         char *argv[]) {
  UNUSED(cli);
  UNUSED(user_data);
  for (int i = 0; i < argc; i++) {
    printf("%s ", argv[i]);
  }
  printf("\r\n");
}

void command_init(mcucli_t *cli, bytes_write_t write) {
  mcucli_init(cli, NULL, &buffer, &command_set, write, unknown_command);
  mcucli_set_prefix(cli, "> ");
}
